/* SPDX-License-Identifier: GPL-2.0 WITH Linux-syscall-note */
/*
 * include/asm-xtensa/sembuf.h
 *
 * The semid64_ds structure for Xtensa architecture.
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 *
 * Copyright (C) 2001 - 2005 Tensilica Inc.
 *
 * Note extra padding because this structure is passed back and forth
 * between kernel and user space.
 *
 * Pad space is left for:
<<<<<<< HEAD
=======
 * - 64-bit time_t to solve y2038 problem
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
 * - 2 miscellaneous 32-bit values
 *
 */

#ifndef _XTENSA_SEMBUF_H
#define _XTENSA_SEMBUF_H

#include <asm/byteorder.h>

struct semid64_ds {
	struct ipc64_perm sem_perm;		/* permissions .. see ipc.h */
#ifdef __XTENSA_EL__
<<<<<<< HEAD
	unsigned long	sem_otime;		/* last semop time */
	unsigned long	sem_otime_high;
	unsigned long	sem_ctime;		/* last change time */
	unsigned long	sem_ctime_high;
#else
	unsigned long	sem_otime_high;
	unsigned long	sem_otime;		/* last semop time */
	unsigned long	sem_ctime_high;
	unsigned long	sem_ctime;		/* last change time */
=======
	__kernel_time_t	sem_otime;		/* last semop time */
	unsigned long	__unused1;
	__kernel_time_t	sem_ctime;		/* last change time */
	unsigned long	__unused2;
#else
	unsigned long	__unused1;
	__kernel_time_t	sem_otime;		/* last semop time */
	unsigned long	__unused2;
	__kernel_time_t	sem_ctime;		/* last change time */
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
#endif
	unsigned long	sem_nsems;		/* no. of semaphores in array */
	unsigned long	__unused3;
	unsigned long	__unused4;
};

#endif /* __ASM_XTENSA_SEMBUF_H */
