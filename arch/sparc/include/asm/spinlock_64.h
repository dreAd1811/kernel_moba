/* SPDX-License-Identifier: GPL-2.0 */
/* spinlock.h: 64-bit Sparc spinlock support.
 *
 * Copyright (C) 1997 David S. Miller (davem@caip.rutgers.edu)
 */

#ifndef __SPARC64_SPINLOCK_H
#define __SPARC64_SPINLOCK_H

#ifndef __ASSEMBLY__

#include <asm/processor.h>
#include <asm/barrier.h>
#include <asm/qrwlock.h>
#include <asm/qspinlock.h>

<<<<<<< HEAD
=======
#define arch_read_lock_flags(p, f) arch_read_lock(p)
#define arch_write_lock_flags(p, f) arch_write_lock(p)

#define arch_spin_relax(lock)	cpu_relax()
#define arch_read_relax(lock)	cpu_relax()
#define arch_write_relax(lock)	cpu_relax()

>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
#endif /* !(__ASSEMBLY__) */

#endif /* !(__SPARC64_SPINLOCK_H) */
