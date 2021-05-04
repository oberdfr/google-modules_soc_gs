/* SPDX-License-Identifier: GPL-2.0 */
#undef TRACE_SYSTEM
#define TRACE_SYSTEM sched

#define MAX_SPAN_SIZE		128

#if !defined(_SCHED_EVENTS_H) || defined(TRACE_HEADER_MULTI_READ)
#define _SCHED_EVENTS_H

#define PATH_SIZE		64
#define __SPAN_SIZE		(round_up(NR_CPUS, 4)/4)
#define SPAN_SIZE		(__SPAN_SIZE > MAX_SPAN_SIZE ? MAX_SPAN_SIZE : __SPAN_SIZE)

#include <linux/tracepoint.h>
#include <linux/version.h>

#if LINUX_VERSION_CODE <= KERNEL_VERSION(5,6,0)
#define RBL_LOAD_ENTRY		rbl_load
#define RBL_LOAD_MEMBER		runnable_load_avg
#define RBL_LOAD_STR		"rbl_load"
#else
#define RBL_LOAD_ENTRY		runnable
#define RBL_LOAD_MEMBER		runnable_avg
#define RBL_LOAD_STR		"runnable"
#endif

TRACE_EVENT(sched_pelt_cfs,

	TP_PROTO(int cpu, char *path, const struct sched_avg *avg),

	TP_ARGS(cpu, path, avg),

	TP_STRUCT__entry(
		__field(	int,		cpu			)
		__array(	char,		path,	PATH_SIZE	)
		__field(	unsigned long,	load			)
		__field(	unsigned long,	RBL_LOAD_ENTRY		)
		__field(	unsigned long,	util			)
	),

	TP_fast_assign(
		__entry->cpu		= cpu;
		strlcpy(__entry->path, path, PATH_SIZE);
		__entry->load		= avg->load_avg;
		__entry->RBL_LOAD_ENTRY	= avg->RBL_LOAD_MEMBER;
		__entry->util		= avg->util_avg;
	),

	TP_printk("cpu=%d path=%s load=%lu " RBL_LOAD_STR "=%lu util=%lu",
		  __entry->cpu, __entry->path, __entry->load,
		  __entry->RBL_LOAD_ENTRY,__entry->util)
);

DECLARE_EVENT_CLASS(sched_pelt_rq_template,

	TP_PROTO(int cpu, const struct sched_avg *avg),

	TP_ARGS(cpu, avg),

	TP_STRUCT__entry(
		__field(	int,		cpu			)
		__field(	unsigned long,	load			)
		__field(	unsigned long,	RBL_LOAD_ENTRY		)
		__field(	unsigned long,	util			)
	),

	TP_fast_assign(
		__entry->cpu		= cpu;
		__entry->load		= avg->load_avg;
		__entry->RBL_LOAD_ENTRY	= avg->RBL_LOAD_MEMBER;
		__entry->util		= avg->util_avg;
	),

	TP_printk("cpu=%d load=%lu " RBL_LOAD_STR "=%lu util=%lu",
		  __entry->cpu, __entry->load,
		  __entry->RBL_LOAD_ENTRY,__entry->util)
);

DEFINE_EVENT(sched_pelt_rq_template, sched_pelt_rt,
	TP_PROTO(int cpu, const struct sched_avg *avg),
	TP_ARGS(cpu, avg));

DEFINE_EVENT(sched_pelt_rq_template, sched_pelt_dl,
	TP_PROTO(int cpu, const struct sched_avg *avg),
	TP_ARGS(cpu, avg));

DEFINE_EVENT(sched_pelt_rq_template, sched_pelt_irq,
	TP_PROTO(int cpu, const struct sched_avg *avg),
	TP_ARGS(cpu, avg));

TRACE_EVENT(sched_cpu_capacity,

	TP_PROTO(struct rq *rq),

	TP_ARGS(rq),

	TP_STRUCT__entry(
		__field(int, cpu)
		__field(unsigned long, capacity)
		__field(unsigned long, capacity_orig)
	),

	TP_fast_assign(
		__entry->cpu			= rq->cpu;
		__entry->capacity		= rq->cpu_capacity;
		__entry->capacity_orig		= rq->cpu_capacity_orig;
	),

	TP_printk("cpu=%d capacity=%lu, capacity_orig=%lu",
		__entry->cpu, __entry->capacity, __entry->capacity_orig)
);

TRACE_EVENT(sched_pelt_se,

	TP_PROTO(int cpu, char *path, char *comm, int pid, const struct sched_avg *avg),

	TP_ARGS(cpu, path, comm, pid, avg),

	TP_STRUCT__entry(
		__field(	int,		cpu			)
		__array(	char,		path,	PATH_SIZE	)
		__array(	char,		comm,	TASK_COMM_LEN	)
		__field(	int,		pid			)
		__field(	unsigned long,	load			)
		__field(	unsigned long,	RBL_LOAD_ENTRY		)
		__field(	unsigned long,	util			)
		__field(	unsigned long long, update_time	        )
	),

	TP_fast_assign(
		__entry->cpu		= cpu;
		strlcpy(__entry->path, path, PATH_SIZE);
		strlcpy(__entry->comm, comm, TASK_COMM_LEN);
		__entry->pid		= pid;
		__entry->load		= avg->load_avg;
		__entry->RBL_LOAD_ENTRY	= avg->RBL_LOAD_MEMBER;
		__entry->util		= avg->util_avg;
		__entry->update_time    = avg->last_update_time;
	),

	TP_printk("cpu=%d path=%s comm=%s pid=%d load=%lu " RBL_LOAD_STR "=%lu util=%lu update_time=%llu",
		  __entry->cpu, __entry->path, __entry->comm, __entry->pid,
		  __entry->load, __entry->RBL_LOAD_ENTRY,__entry->util, __entry->update_time)
);

TRACE_EVENT(sched_overutilized,

	TP_PROTO(int overutilized, char *span),

	TP_ARGS(overutilized, span),

	TP_STRUCT__entry(
		__field(	int,		overutilized		)
		__array(	char,		span,	SPAN_SIZE	)
	),

	TP_fast_assign(
		__entry->overutilized	= overutilized;
		strlcpy(__entry->span, span, SPAN_SIZE);
	),

	TP_printk("overutilized=%d span=0x%s",
		  __entry->overutilized, __entry->span)
);

TRACE_EVENT(sched_util_est_se,

	TP_PROTO(int cpu, char *path, char *comm, int pid,
		 const struct sched_avg *avg),

	TP_ARGS(cpu, path, comm, pid, avg),

	TP_STRUCT__entry(
		__field(	int,		cpu			)
		__array(	char,		path,	PATH_SIZE	)
		__array(	char,		comm,	TASK_COMM_LEN	)
		__field(	int,		pid			)
		__field( 	unsigned int,	enqueued		)
		__field( 	unsigned int,	ewma			)
		__field(	unsigned long,	util			)
	),

	TP_fast_assign(
		__entry->cpu		= cpu;
		strlcpy(__entry->path, path, PATH_SIZE);
		strlcpy(__entry->comm, comm, TASK_COMM_LEN);
		__entry->pid		= pid;
		__entry->enqueued	= avg->util_est.enqueued;
		__entry->ewma		= avg->util_est.ewma;
		__entry->util		= avg->util_avg;
	),

	TP_printk("cpu=%d path=%s comm=%s pid=%d enqueued=%u ewma=%u util=%lu",
		  __entry->cpu, __entry->path, __entry->comm, __entry->pid,
		  __entry->enqueued, __entry->ewma, __entry->util)
);

TRACE_EVENT(sched_util_est_cfs,

	TP_PROTO(int cpu, char *path, const struct sched_avg *avg),

	TP_ARGS(cpu, path, avg),

	TP_STRUCT__entry(
		__field(	int,		cpu			)
		__array(	char,		path,	PATH_SIZE	)
		__field( 	unsigned int,	enqueued		)
		__field( 	unsigned int,	ewma			)
		__field(	unsigned long,	util			)
	),

	TP_fast_assign(
		__entry->cpu		= cpu;
		strlcpy(__entry->path, path, PATH_SIZE);
		__entry->enqueued	= avg->util_est.enqueued;
		__entry->ewma		= avg->util_est.ewma;
		__entry->util		= avg->util_avg;
	),

	TP_printk("cpu=%d path=%s enqueued=%u ewma=%u util=%lu",
		  __entry->cpu, __entry->path, __entry->enqueued,
		 __entry->ewma, __entry->util)
);

TRACE_EVENT(sched_find_best_target,

	TP_PROTO(struct task_struct *tsk, bool prefer_idle,
		 bool prefer_high_cap, bool prefer_prev, bool sync_boost,
		 unsigned long task_util, int start_cpu,
		 int best_idle, int best_active, int best_importance,
		 int backup, int target),

	TP_ARGS(tsk, prefer_idle, prefer_high_cap, prefer_prev, sync_boost, task_util,
		start_cpu, best_idle, best_active, best_importance, backup, target),

	TP_STRUCT__entry(
		__array(char,		comm, TASK_COMM_LEN)
		__field(pid_t,		pid)
		__field(unsigned long,	task_util)
		__field(bool,		prefer_idle)
		__field(bool,		prefer_high_cap)
		__field(bool,		prefer_prev)
		__field(bool,		sync_boost)
		__field(int,		start_cpu)
		__field(int,		best_idle)
		__field(int,		best_active)
		__field(int,		best_importance)
		__field(int,		backup)
		__field(int,		target)
		),

	TP_fast_assign(
		memcpy(__entry->comm, tsk->comm, TASK_COMM_LEN);
		__entry->pid             = tsk->pid;
		__entry->task_util       = task_util;
		__entry->prefer_idle     = prefer_idle;
		__entry->prefer_high_cap = prefer_high_cap;
		__entry->prefer_prev     = prefer_prev;
		__entry->sync_boost      = sync_boost;
		__entry->start_cpu       = start_cpu;
		__entry->best_idle       = best_idle;
		__entry->best_active     = best_active;
		__entry->best_importance = best_importance;
		__entry->backup          = backup;
		__entry->target          = target;
		),

	TP_printk("pid=%d comm=%s task_util=%lu prefer_idle=%d prefer_high_cap=%d prefer_prev=%d " \
		  "sync_boost=%d start_cpu=%d best_idle=%d best_active=%d best_importance=%d " \
		  "backup=%d target=%d",
		  __entry->pid, __entry->comm, __entry->task_util, __entry->prefer_idle,
		  __entry->prefer_high_cap, __entry->prefer_prev, __entry->sync_boost,
		  __entry->start_cpu, __entry->best_idle, __entry->best_active,
		  __entry->best_importance, __entry->backup, __entry->target)
);

TRACE_EVENT(sched_find_energy_efficient_cpu,

	TP_PROTO(struct task_struct *tsk, bool sync_wakeup,
		 int new_cpu, int best_energy_cpu, int prev_cpu),

	TP_ARGS(tsk, sync_wakeup, new_cpu, best_energy_cpu, prev_cpu),

	TP_STRUCT__entry(
		__array(char,		comm, TASK_COMM_LEN)
		__field(pid_t,		pid)
		__field(bool,		sync_wakeup)
		__field(int,		new_cpu)
		__field(int,		best_energy_cpu)
		__field(int,		prev_cpu)
		),

	TP_fast_assign(
		memcpy(__entry->comm, tsk->comm, TASK_COMM_LEN);
		__entry->pid             = tsk->pid;
		__entry->sync_wakeup     = sync_wakeup;
		__entry->new_cpu         = new_cpu;
		__entry->best_energy_cpu = best_energy_cpu;
		__entry->prev_cpu        = prev_cpu;
		),

	TP_printk("pid=%d comm=%s sync_wakeup=%d new_cpu=%d best_energy_cpu=%d prev_cpu=%d",
		  __entry->pid, __entry->comm, __entry->sync_wakeup, __entry->new_cpu,
		  __entry->best_energy_cpu, __entry->prev_cpu)
);

TRACE_EVENT(sched_cpu_util,

	TP_PROTO(int cpu, unsigned long cpu_util, unsigned long capacity_curr,
		 unsigned long capacity, bool idle_cpu, unsigned long task_importance,
		 unsigned long cpu_importance),

	TP_ARGS(cpu, cpu_util, capacity_curr, capacity, idle_cpu, task_importance, cpu_importance),

	TP_STRUCT__entry(
		__field(unsigned int,	cpu)
		__field(unsigned int,	nr_running)
		__field(unsigned long,	cpu_util)
		__field(unsigned long,	capacity_curr)
		__field(unsigned long,	capacity)
		__field(unsigned long,	capacity_orig)
		__field(int,		    active)
		__field(bool,		    idle_cpu)
		__field(unsigned long,	task_importance)
		__field(unsigned long,	cpu_importance)
	),

	TP_fast_assign(
		__entry->cpu                = cpu;
		__entry->nr_running         = cpu_rq(cpu)->nr_running;
		__entry->cpu_util           = cpu_util;
		__entry->capacity_curr      = capacity_curr;
		__entry->capacity           = capacity;
		__entry->capacity_orig      = capacity_orig_of(cpu);
		__entry->active             = cpu_active(cpu);
		__entry->idle_cpu           = idle_cpu;
		__entry->task_importance    = task_importance;
		__entry->cpu_importance     = cpu_importance;
	),

	TP_printk("cpu=%d nr_running=%d cpu_util=%ld capacity_curr=%u capacity=%u " \
		  "capacity_orig=%u active=%u idle_cpu=%d task_importance=%llu cpu_importance=%llu",
		__entry->cpu, __entry->nr_running, __entry->cpu_util, __entry->capacity_curr,
		__entry->capacity, __entry->capacity_orig, __entry->active, __entry->idle_cpu,
		__entry->task_importance, __entry->cpu_importance)
);

TRACE_EVENT(sugov_util_update,
	    TP_PROTO(unsigned int cpu, unsigned long util, unsigned long max_cap,
		     unsigned int flags),
	    TP_ARGS(cpu, util, max_cap, flags),
	    TP_STRUCT__entry(
		    __field(unsigned int, cpu)
		    __field(unsigned long, util)
		    __field(unsigned long, max_cap)
		    __field(unsigned int, flags)
	    ),
	    TP_fast_assign(
		    __entry->cpu = cpu;
		    __entry->util = util;
		    __entry->max_cap = max_cap;
		    __entry->flags = flags;
	    ),
	    TP_printk("cpu=%u util=%lu max_cap=%lu flags=0x%x",
		      __entry->cpu, __entry->util,
		      __entry->max_cap, __entry->flags)
);

TRACE_EVENT(sugov_next_freq,
	    TP_PROTO(unsigned int cpu, unsigned long util, unsigned long max,
		     unsigned int freq),
	    TP_ARGS(cpu, util, max, freq),
	    TP_STRUCT__entry(
		    __field(unsigned int, cpu)
		    __field(unsigned long, util)
		    __field(unsigned long, max)
		    __field(unsigned int, freq)
	    ),
	    TP_fast_assign(
		    __entry->cpu = cpu;
		    __entry->util = util;
		    __entry->max = max;
		    __entry->freq = freq;
	    ),
	    TP_printk("cpu=%u util=%lu max=%lu freq=%u",
		      __entry->cpu,
		      __entry->util,
		      __entry->max,
		      __entry->freq)
);

TRACE_EVENT(schedutil_cpu_util_clamp,

	TP_PROTO(int cpu, unsigned long util_cfs, unsigned long util_rt, unsigned long util_clamp,
		 unsigned long util_max),

	TP_ARGS(cpu, util_cfs, util_rt, util_clamp, util_max),

	TP_STRUCT__entry(
		__field(int,		cpu)
		__field(unsigned long,	util_cfs)
		__field(unsigned long,	util_rt)
		__field(unsigned long,	util_clamp)
		__field(unsigned long,	util_max)
	),

	TP_fast_assign(
		__entry->cpu                = cpu;
		__entry->util_cfs           = util_cfs;
		__entry->util_rt	    = util_rt;
		__entry->util_clamp         = util_clamp;
		__entry->util_max	    = util_max;
	),

	TP_printk("cpu=%d util_cfs=%ld util_rt=%ld util_clamp=%ld util_max=%ld",
		__entry->cpu, __entry->util_cfs, __entry->util_rt, __entry->util_clamp,
		__entry->util_max)
);

#endif /* _SCHED_EVENTS_H */

/* This part must be outside protection */
#undef TRACE_INCLUDE_PATH
#define TRACE_INCLUDE_PATH .
#define TRACE_INCLUDE_FILE sched_events
#include <trace/define_trace.h>
