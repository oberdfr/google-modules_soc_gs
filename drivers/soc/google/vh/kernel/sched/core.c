// SPDX-License-Identifier: GPL-2.0-only
/* core.c
 *
 * Android Vendor Hook Support
 *
 * Copyright 2021 Google LLC
 */

#include <linux/sched.h>
#include <linux/sched/cputime.h>
#include <kernel/sched/sched.h>

#include "sched_priv.h"
#include "sched_events.h"
#include <performance/gs_perf_mon/gs_perf_mon.h>

struct vendor_group_list vendor_group_list[VG_MAX];

#if IS_ENABLED(CONFIG_UCLAMP_STATS)
extern void update_uclamp_stats(int cpu, u64 time);
#endif

extern int find_energy_efficient_cpu(struct task_struct *p, int prev_cpu,
		cpumask_t *valid_mask);
/*
 * Ignore uclamp_min for CFS tasks if
 *
 *	runtime >= sysctl_sched_uclamp_min_filter_us
 */
unsigned int sysctl_sched_uclamp_min_filter_us = 1000;

/*
 * Ignore uclamp_max for CFS tasks if
 *
 *	runtime < sched_slice() / divider
 */
unsigned int sysctl_sched_uclamp_max_filter_divider = 4;

/*
 * Ignore uclamp_min for RT tasks if
 *
 *	task_util(p) < sysctl_sched_uclamp_min_filter_rt
 */
unsigned int sysctl_sched_uclamp_min_filter_rt = 50;

/*
 * Ignore uclamp_max for RT tasks if
 *
 *	task_util(p) < sysctl_sched_uclamp_max_filter_rt
 */
unsigned int sysctl_sched_uclamp_max_filter_rt = 100;

/*
 * Enable and disable uclamp min/max filters at runtime
 */
DEFINE_STATIC_KEY_FALSE(uclamp_min_filter_enable);
DEFINE_STATIC_KEY_FALSE(uclamp_max_filter_enable);

DEFINE_STATIC_KEY_FALSE(tapered_dvfs_headroom_enable);
DEFINE_STATIC_KEY_FALSE(auto_dvfs_headroom_enable);
DEFINE_STATIC_KEY_FALSE(auto_migration_margins_enable);

DEFINE_STATIC_KEY_FALSE(skip_inefficient_opps_enable);

#define vi_set_latency_sensitive(vi, type, value) \
    do { \
        if (value) { \
            (vi)->uclamp_fork_reset |= (1 << (type)); \
        } else { \
            (vi)->uclamp_fork_reset &= ~(1 << (type)); \
        } \
    } while (0)

#define vi_set_prefer_idle(vi, type, value) \
    do { \
        if (value) { \
            (vi)->prefer_idle |= (1 << (type)); \
        } else { \
            (vi)->prefer_idle &= ~(1 << (type)); \
        } \
    } while (0)

/*****************************************************************************/
/*                       New Code Section                                    */
/*****************************************************************************/
/*
 * This part of code is new for this kernel, which are mostly helper functions.
 */

/*****************************************************************************/
/*                       Modified Code Section                               */
/*****************************************************************************/
/*
 * This part of code is vendor hook functions, which modify or extend the original
 * functions.
 */
#if IS_ENABLED(CONFIG_UCLAMP_TASK)
static inline void task_tick_uclamp(struct rq *rq, struct task_struct *curr)
{
	bool can_ignore;
	bool is_ignored;
	bool reset_filters = false;

	if (!uclamp_is_used())
		return;

	/*
	 * Condition might have changed since we enqueued the task.
	 */

	can_ignore = uclamp_can_ignore_uclamp_max(rq, curr);
	is_ignored = uclamp_is_ignore_uclamp_max(curr);

	if (is_ignored && !can_ignore)
		reset_filters = true;

	can_ignore = uclamp_can_ignore_uclamp_min(rq, curr);
	is_ignored = uclamp_is_ignore_uclamp_min(curr);

	if (is_ignored && !can_ignore)
		reset_filters = true;

	if (reset_filters) {
		uclamp_reset_ignore_uclamp_min(curr);
		uclamp_reset_ignore_uclamp_max(curr);

		uclamp_rq_inc_id(rq, curr, UCLAMP_MIN);
		uclamp_rq_inc_id(rq, curr, UCLAMP_MAX);
	}

	/* Reset clamp idle holding when there is one RUNNABLE task */
	if (reset_filters && rq->uclamp_flags & UCLAMP_FLAG_IDLE)
		rq->uclamp_flags &= ~UCLAMP_FLAG_IDLE;
}
#else
static inline void task_tick_uclamp(struct rq *rq, struct task_struct *curr) {}
#endif

void vh_scheduler_tick_pixel_mod(void *data, struct rq *rq)
{
	struct rq_flags rf;
	rq_lock(rq, &rf);
	task_tick_uclamp(rq, rq->curr);
	rq_unlock(rq, &rf);

	/* Check if an RT task needs to move to a better fitting CPU */
	check_migrate_rt_task(rq, rq->curr);

	/* Should be really done when capacity change */
	update_auto_fits_capacity();

	/*
	 * Update our performance counters for profiling per
	 * cpu performance data. Also checks if we need to wake
	 * up a helper thread to update memory frequencies.
	 */
	gs_perf_mon_tick_update_counters();
}

void rvh_tick_entry_pixel_mod(void *data, struct rq *rq)
{
	__update_util_est_invariance(rq, rq->curr, true);
}

void vh_sched_switch_pixel_mod(void *data, bool preempt, struct task_struct *prev,
			       struct task_struct *next, unsigned int prev_state)
{
	struct rq *rq = task_rq(prev);

	if (task_is_running(prev))
		__update_util_est_invariance(rq, prev, rq->nr_running > 1);
}

void rvh_enqueue_task_pixel_mod(void *data, struct rq *rq, struct task_struct *p, int flags)
{
	struct vendor_task_struct *vp = get_vendor_task_struct(p);
	int group;

	if (!static_branch_unlikely(&enqueue_dequeue_ready))
		return;

	if (static_branch_likely(&auto_dvfs_headroom_enable)) {
		if (vg[get_vendor_group(p)].disable_util_est) {
			p->se.avg.util_est.enqueued = 0;
			p->se.avg.util_est.ewma = 0;
		}
	}

	raw_spin_lock(&vp->lock);
	if (vp->queued_to_list == LIST_NOT_QUEUED) {
		group = get_vendor_group(p);
		add_to_vendor_group_list(&vp->node, group);
		vp->queued_to_list = LIST_QUEUED;
	}
	raw_spin_unlock(&vp->lock);

	/*
	 * uclamp filter for RT tasks. CFS tasks are handled in
	 * enqueue_task_fair() where we need cfs_rqs to be updated before we
	 * can read sched_slice()
	 */
	if (uclamp_is_used() && rt_task(p) && p->sched_class->uclamp_enabled)
		apply_uclamp_filters(rq, p);
}

void rvh_dequeue_task_pixel_mod(void *data, struct rq *rq, struct task_struct *p, int flags)
{
	struct vendor_task_struct *vp = get_vendor_task_struct(p);
	int group;

	if (!static_branch_unlikely(&enqueue_dequeue_ready))
		return;

#if IS_ENABLED(CONFIG_UCLAMP_STATS)
	if (rq->nr_running == 1)
		update_uclamp_stats(rq->cpu, rq_clock(rq));
#endif

	raw_spin_lock(&vp->lock);
	if (vp->queued_to_list == LIST_QUEUED) {
		group = get_vendor_group(p);
		remove_from_vendor_group_list(&vp->node, group);
		vp->queued_to_list = LIST_NOT_QUEUED;
	}
	raw_spin_unlock(&vp->lock);

	/*
	 * Reset uclamp filter flags unconditionally for both RT and CFS.
	 */
	if (uclamp_is_used()) {
		uclamp_reset_ignore_uclamp_max(p);
		uclamp_reset_ignore_uclamp_min(p);
	}
}

void rvh_set_cpus_allowed_by_task(void *data, const struct cpumask *cpu_valid_mask,
	const struct cpumask *new_mask, struct task_struct *p, unsigned int *dest_cpu)
{
	cpumask_t valid_mask;
	int best_energy_cpu = -1;

	cpumask_and(&valid_mask, cpu_valid_mask, new_mask);

	/* find a cpu again for the running/runnable/waking tasks
	 * if their current cpu are not allowed
	 */
	if ((p->on_cpu || p->__state == TASK_WAKING || task_on_rq_queued(p)) &&
		!cpumask_test_cpu(task_cpu(p), new_mask)) {
		best_energy_cpu = find_energy_efficient_cpu(p, task_cpu(p), &valid_mask);

		if (best_energy_cpu != -1)
			*dest_cpu = best_energy_cpu;
	}

	trace_set_cpus_allowed_by_task(p, &valid_mask, *dest_cpu);

	return;
}

static void set_latency_sensitive_inheritance(struct task_struct *p, unsigned int type, int val)
{
	struct vendor_inheritance_struct *vi = get_vendor_inheritance_struct(p);

	if (task_on_rq_queued(p)) {
		bool old_uclamp_fork_reset = get_uclamp_fork_reset(p, true);

		vi_set_latency_sensitive(vi, type, val);

		if (!old_uclamp_fork_reset && get_uclamp_fork_reset(p, true))
			inc_adpf_counter(p, task_rq(p));
		else if (old_uclamp_fork_reset && !get_uclamp_fork_reset(p, true))
			dec_adpf_counter(p, task_rq(p));
	} else
		vi_set_latency_sensitive(vi, type, val);
}

static void set_performance_inheritance(struct task_struct *p, struct task_struct *pi_task,
	unsigned int type)
{
	struct vendor_inheritance_struct *vi = get_vendor_inheritance_struct(p);

	if (pi_task) {
		unsigned long p_util = task_util(p);
		unsigned long p_uclamp_min = uclamp_eff_value_pixel_mod(p, UCLAMP_MIN);
		unsigned long p_uclamp_max = uclamp_eff_value_pixel_mod(p, UCLAMP_MAX);
		unsigned long pi_util = task_util(pi_task);
		unsigned long pi_uclamp_min = uclamp_eff_value_pixel_mod(pi_task, UCLAMP_MIN);
		unsigned long pi_uclamp_max = uclamp_eff_value_pixel_mod(pi_task, UCLAMP_MAX);

		lockdep_assert_held(&pi_task->pi_lock);

		/*
		 * Take task's util into consideration first to do full
		 * performance inheritance.
		 *
		 * If pi_uclamp_min = 612 but pi_util is 812, then setting
		 * p_uclamp_min to 612 is not enough as the task will still run
		 * slower.
		 *
		 * Or if pi_uclamp_min is 0 but pi_util is 800 while p_util is
		 * 100, then pi_task could wait for longer to acquire the lock
		 * because the performance of p is too low.
		 */
		p_uclamp_min = clamp(p_util, p_uclamp_min, p_uclamp_max);
		pi_uclamp_min = clamp(pi_util, pi_uclamp_min, pi_uclamp_max);

		/* Inherit unclamp_min/max if they're inverted */

		if (p_uclamp_min < pi_uclamp_min)
			vi->uclamp[type][UCLAMP_MIN] = pi_uclamp_min;

		if (p_uclamp_max < pi_uclamp_max || pi_uclamp_min > p_uclamp_max)
			vi->uclamp[type][UCLAMP_MAX] = pi_uclamp_max;

		if (!!get_uclamp_fork_reset(pi_task, true))
			set_latency_sensitive_inheritance(p, type, 1);

		if (!!get_prefer_idle(pi_task))
			vi_set_prefer_idle(vi, type, 1);
	} else {
		vi->uclamp[type][UCLAMP_MIN] = uclamp_none(UCLAMP_MIN);
		vi->uclamp[type][UCLAMP_MAX] = uclamp_none(UCLAMP_MAX);

		set_latency_sensitive_inheritance(p, type, 0);

		vi_set_prefer_idle(vi, type, 0);
	}
}

void vh_binder_set_priority_pixel_mod(void *data, struct binder_transaction *t,
	struct task_struct *p)
{
	get_vendor_task_struct(p)->is_binder_task = true;

	if (!t->from)
		return;

	set_performance_inheritance(p, current, VI_BINDER);
}

void vh_binder_restore_priority_pixel_mod(void *data, struct binder_transaction *t,
	struct task_struct *p)
{
	set_performance_inheritance(p, NULL, VI_BINDER);
}

void rvh_rtmutex_prepare_setprio_pixel_mod(void *data, struct task_struct *p,
	struct task_struct *pi_task)
{
	set_performance_inheritance(p, pi_task, VI_RTMUTEX);
}

void rvh_try_to_wake_up_success_pixel_mod(void *data, struct task_struct *p)
{
	trace_sched_wakeup_task_attr(p, p->cpus_ptr, task_util_est(p),
				     uclamp_eff_value_pixel_mod(p, UCLAMP_MIN),
				     p->se.vruntime);
}

void set_cluster_enabled_cb(int cluster, int enabled)
{
	pixel_cluster_enabled[cluster] = enabled;
}

int get_cluster_enabled(int cluster)
{
	return pixel_cluster_enabled[cluster];
}
