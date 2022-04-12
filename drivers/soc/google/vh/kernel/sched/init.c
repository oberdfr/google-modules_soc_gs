// SPDX-License-Identifier: GPL-2.0-only
/* init.c
 *
 * Android Vendor Hook Support
 *
 * Copyright 2020 Google LLC
 */

#include <kernel/sched/sched.h>
#include <linux/cpufreq.h>
#include <linux/module.h>
#include <trace/hooks/sched.h>
#include <trace/hooks/topology.h>

#include "sched_priv.h"

extern void init_uclamp_stats(void);
extern int create_procfs_node(void);
extern void vh_arch_set_freq_scale_pixel_mod(void *data,
					     const struct cpumask *cpus,
					     unsigned long freq,
					     unsigned long max,
					     unsigned long *scale);
extern void vh_set_sugov_sched_attr_pixel_mod(void *data, struct sched_attr *attr);
extern void rvh_set_iowait_pixel_mod(void *data, struct task_struct *p, int *should_iowait_boost);
extern void rvh_select_task_rq_rt_pixel_mod(void *data, struct task_struct *p, int prev_cpu,
					    int sd_flag, int wake_flags, int *new_cpu);
extern void rvh_cpu_overutilized_pixel_mod(void *data, int cpu, int *overutilized);
extern void rvh_dequeue_task_pixel_mod(void *data, struct rq *rq, struct task_struct *p, int flags);
extern void rvh_enqueue_task_fair_pixel_mod(void *data, struct rq *rq, struct task_struct *p,
					    int flags);
extern void rvh_dequeue_task_fair_pixel_mod(void *data, struct rq *rq, struct task_struct *p,
					    int flags);
extern void rvh_uclamp_eff_get_pixel_mod(void *data, struct task_struct *p,
					 enum uclamp_id clamp_id, struct uclamp_se *uclamp_max,
					 struct uclamp_se *uclamp_eff, int *ret);
extern void rvh_post_init_entity_util_avg_pixel_mod(void *data, struct sched_entity *se);
extern void rvh_check_preempt_wakeup_pixel_mod(void *data, struct rq *rq, struct task_struct *p,
			bool *preempt, bool *nopreempt, int wake_flags, struct sched_entity *se,
			struct sched_entity *pse, int next_buddy_marked, unsigned int granularity);
extern void vh_sched_setscheduler_uclamp_pixel_mod(void *data, struct task_struct *tsk,
						   int clamp_id, unsigned int value);
extern void init_uclamp_stats(void);
extern void rvh_sched_fork_pixel_mod(void *data, struct task_struct *tsk);
extern void vh_dup_task_struct_pixel_mod(void *data, struct task_struct *tsk,
					 struct task_struct *orig);
extern void rvh_select_task_rq_fair_pixel_mod(void *data, struct task_struct *p, int prev_cpu,
					      int sd_flag, int wake_flags, int *target_cpu);
extern void init_vendor_group_data(void);
extern void rvh_attach_entity_load_avg_pixel_mod(void *data, struct cfs_rq *cfs_rq,
						 struct sched_entity *se);
extern void rvh_detach_entity_load_avg_pixel_mod(void *data, struct cfs_rq *cfs_rq,
						 struct sched_entity *se);
extern void rvh_update_load_avg_pixel_mod(void *data, u64 now, struct cfs_rq *cfs_rq,
					  struct sched_entity *se);
extern void rvh_remove_entity_load_avg_pixel_mod(void *data, struct cfs_rq *cfs_rq,
						 struct sched_entity *se);
extern void rvh_update_blocked_fair_pixel_mod(void *data, struct rq *rq);
extern void rvh_enqueue_task_pixel_mod(void *data, struct rq *rq, struct task_struct *p, int flags);
extern void rvh_dequeue_task_pixel_mod(void *data, struct rq *rq, struct task_struct *p, int flags);

extern struct cpufreq_governor sched_pixel_gov;

extern int pmu_poll_init(void);

static int vh_sched_init(void)
{
	int ret;

	ret = pmu_poll_init();
	if (ret) {
		pr_err("pmu poll init failed\n");
		return ret;
	}

	ret = create_procfs_node();
	if (ret)
		return ret;

#if IS_ENABLED(CONFIG_UCLAMP_STATS)
	init_uclamp_stats();
#endif

	init_vendor_group_data();

	ret = register_trace_android_rvh_enqueue_task_fair(rvh_enqueue_task_fair_pixel_mod, NULL);
	if (ret)
		return ret;

	ret = register_trace_android_rvh_dequeue_task_fair(rvh_dequeue_task_fair_pixel_mod, NULL);
	if (ret)
		return ret;

	ret = register_trace_android_rvh_enqueue_task(rvh_enqueue_task_pixel_mod, NULL);
	if (ret)
		return ret;

	ret = register_trace_android_rvh_dequeue_task(rvh_dequeue_task_pixel_mod, NULL);
	if (ret)
		return ret;

	ret = register_trace_android_rvh_set_iowait(rvh_set_iowait_pixel_mod, NULL);
	if (ret)
		return ret;

	ret = register_trace_android_rvh_select_task_rq_rt(rvh_select_task_rq_rt_pixel_mod, NULL);
	if (ret)
		return ret;

	ret = register_trace_android_rvh_cpu_overutilized(rvh_cpu_overutilized_pixel_mod, NULL);
	if (ret)
		return ret;

	ret = register_trace_android_rvh_dequeue_task(rvh_dequeue_task_pixel_mod, NULL);
	if (ret)
		return ret;

	ret = register_trace_android_rvh_uclamp_eff_get(rvh_uclamp_eff_get_pixel_mod, NULL);
	if (ret)
		return ret;

	ret = register_trace_android_rvh_post_init_entity_util_avg(
		rvh_post_init_entity_util_avg_pixel_mod, NULL);
	if (ret)
		return ret;

	ret = register_trace_android_rvh_check_preempt_wakeup(
		rvh_check_preempt_wakeup_pixel_mod, NULL);
	if (ret)
		return ret;

	ret = register_trace_android_rvh_sched_fork(rvh_sched_fork_pixel_mod, NULL);
	if (ret)
		return ret;

	ret = register_trace_android_rvh_select_task_rq_fair(rvh_select_task_rq_fair_pixel_mod,
							     NULL);
	if (ret)
		return ret;

	ret = register_trace_android_vh_arch_set_freq_scale(vh_arch_set_freq_scale_pixel_mod, NULL);
	if (ret)
		return ret;

	ret = register_trace_android_vh_setscheduler_uclamp(
		vh_sched_setscheduler_uclamp_pixel_mod, NULL);
	if (ret)
		return ret;

	ret = cpufreq_register_governor(&sched_pixel_gov);
	if (ret)
		return ret;

	ret = register_trace_android_rvh_sched_fork(rvh_sched_fork_pixel_mod, NULL);
	if (ret)
		return ret;

	ret = register_trace_android_vh_dup_task_struct(vh_dup_task_struct_pixel_mod, NULL);
	if (ret)
		return ret;

	ret = acpu_init();
	if (ret)
		return ret;

	ret = register_trace_android_rvh_attach_entity_load_avg(
		rvh_attach_entity_load_avg_pixel_mod, NULL);
	if (ret)
		return ret;

	ret = register_trace_android_rvh_detach_entity_load_avg(
		rvh_detach_entity_load_avg_pixel_mod, NULL);
	if (ret)
		return ret;

	ret = register_trace_android_rvh_update_load_avg(rvh_update_load_avg_pixel_mod, NULL);
	if (ret)
		return ret;

	ret = register_trace_android_rvh_remove_entity_load_avg(
		rvh_remove_entity_load_avg_pixel_mod, NULL);
	if (ret)
		return ret;

	ret = register_trace_android_rvh_update_blocked_fair(
		rvh_update_blocked_fair_pixel_mod, NULL);
	if (ret)
		return ret;

	// Disable TTWU_QUEUE.
	sysctl_sched_features &= ~(1UL << __SCHED_FEAT_TTWU_QUEUE);
	static_key_disable(&sched_feat_keys[__SCHED_FEAT_TTWU_QUEUE]);

	return 0;
}

module_init(vh_sched_init);
MODULE_LICENSE("GPL v2");
