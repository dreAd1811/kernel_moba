/*
 * include/asm-xtensa/current.h
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 *
 * Copyright (C) 2001 - 2005 Tensilica Inc.
 */

#ifndef _XTENSA_CURRENT_H
#define _XTENSA_CURRENT_H

<<<<<<< HEAD
#include <asm/thread_info.h>

=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
#ifndef __ASSEMBLY__

#include <linux/thread_info.h>

struct task_struct;

static inline struct task_struct *get_current(void)
{
	return current_thread_info()->task;
}

#define current get_current()

#else

<<<<<<< HEAD
=======
#define CURRENT_SHIFT 13

>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
#define GET_CURRENT(reg,sp)		\
	GET_THREAD_INFO(reg,sp);	\
	l32i reg, reg, TI_TASK		\

#endif


#endif /* XTENSA_CURRENT_H */
