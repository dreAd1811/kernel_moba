/* SPDX-License-Identifier: GPL-2.0+ WITH Linux-syscall-note */
#ifndef _ASM_POWERPC_SEMBUF_H
#define _ASM_POWERPC_SEMBUF_H

/*
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */

/*
 * The semid64_ds structure for PPC architecture.
 * Note extra padding because this structure is passed back and forth
 * between kernel and user space.
 *
 * Pad space is left for:
<<<<<<< HEAD
 * - 2 miscellaneous 32/64-bit values
=======
 * - 64-bit time_t to solve y2038 problem
 * - 2 miscellaneous 32-bit values
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
 */

struct semid64_ds {
	struct ipc64_perm sem_perm;	/* permissions .. see ipc.h */
#ifndef __powerpc64__
<<<<<<< HEAD
	unsigned long	sem_otime_high;
	unsigned long	sem_otime;	/* last semop time */
	unsigned long	sem_ctime_high;
	unsigned long	sem_ctime;	/* last change time */
#else
	__kernel_time_t	sem_otime;	/* last semop time */
	__kernel_time_t	sem_ctime;	/* last change time */
#endif
=======
	unsigned long	__unused1;
#endif
	__kernel_time_t	sem_otime;	/* last semop time */
#ifndef __powerpc64__
	unsigned long	__unused2;
#endif
	__kernel_time_t	sem_ctime;	/* last change time */
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	unsigned long	sem_nsems;	/* no. of semaphores in array */
	unsigned long	__unused3;
	unsigned long	__unused4;
};

#endif	/* _ASM_POWERPC_SEMBUF_H */
