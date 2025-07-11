/* This table has one slot per process.  It contains scheduling information
 * for each process.
 */
#include <limits.h>

#include <minix/bitmap.h>

/* EXTERN should be extern except in main.c, where we want to keep the struct */
#ifdef _MAIN
#undef EXTERN
#define EXTERN
#endif

#ifndef CONFIG_SMP
#define CONFIG_MAX_CPUS 1
#endif

/**
 * We might later want to add more information to this table, such as the
 * process owner, process group or cpumask.
 */

EXTERN struct schedproc {
	endpoint_t endpoint;	      /* process endpoint id */
	endpoint_t parent;		      /* parent endpoint id */
	unsigned flags;		          /* flag bits */
	unsigned max_priority;	      /* highest allowed priority */
	unsigned priority;		      /* current priority */
	unsigned time_slice;	      /* time slice in ticks */
	unsigned cpu;		          /* CPU the process is running on */
	bitchunk_t cpu_mask[BITMAP_CHUNKS(CONFIG_MAX_CPUS)];

	unsigned tickets; 
} schedproc[NR_PROCS];

/* Flag values */
#define IN_USE		0x00001	/* set when 'schedproc' slot in use */
