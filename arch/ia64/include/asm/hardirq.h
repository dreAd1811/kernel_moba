/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _ASM_IA64_HARDIRQ_H
#define _ASM_IA64_HARDIRQ_H

/*
 * Modified 1998-2002, 2004 Hewlett-Packard Co
 *	David Mosberger-Tang <davidm@hpl.hp.com>
 */

/*
 * No irq_cpustat_t for IA-64.  The data is held in the per-CPU data structure.
 */

#define __ARCH_IRQ_STAT	1

<<<<<<< HEAD
#define local_softirq_pending_ref	ia64_cpu_info.softirq_pending
=======
#define local_softirq_pending()		(local_cpu_data->softirq_pending)
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

#include <linux/threads.h>
#include <linux/irq.h>

#include <asm/processor.h>

extern void __iomem *ipi_base_addr;

void ack_bad_irq(unsigned int irq);

#endif /* _ASM_IA64_HARDIRQ_H */
