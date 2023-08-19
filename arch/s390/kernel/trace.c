// SPDX-License-Identifier: GPL-2.0
/*
 * Tracepoint definitions for s390
 *
 * Copyright IBM Corp. 2015
 * Author(s): Martin Schwidefsky <schwidefsky@de.ibm.com>
 */

#include <linux/percpu.h>
#define CREATE_TRACE_POINTS
#include <asm/trace/diag.h>

EXPORT_TRACEPOINT_SYMBOL(s390_diagnose);

static DEFINE_PER_CPU(unsigned int, diagnose_trace_depth);

<<<<<<< HEAD
void trace_s390_diagnose_norecursion(int diag_nr)
=======
void notrace trace_s390_diagnose_norecursion(int diag_nr)
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
{
	unsigned long flags;
	unsigned int *depth;

	/* Avoid lockdep recursion. */
	if (IS_ENABLED(CONFIG_LOCKDEP))
		return;
	local_irq_save(flags);
	depth = this_cpu_ptr(&diagnose_trace_depth);
	if (*depth == 0) {
		(*depth)++;
		trace_s390_diagnose(diag_nr);
		(*depth)--;
	}
	local_irq_restore(flags);
}
