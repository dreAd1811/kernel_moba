/* SPDX-License-Identifier: GPL-2.0 WITH Linux-syscall-note */
#ifndef _ASM_SEMBUF_H
#define _ASM_SEMBUF_H

/*
 * The semid64_ds structure for the MIPS architecture.
 * Note extra padding because this structure is passed back and forth
 * between kernel and user space.
 *
<<<<<<< HEAD
 * Pad space is left for 2 miscellaneous 64-bit values on mips64,
 * but used for the upper 32 bit of the time values on mips32.
 */

#ifdef __mips64
=======
 * Pad space is left for:
 * - 2 miscellaneous 64-bit values
 */

>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
struct semid64_ds {
	struct ipc64_perm sem_perm;		/* permissions .. see ipc.h */
	__kernel_time_t sem_otime;		/* last semop time */
	__kernel_time_t sem_ctime;		/* last change time */
	unsigned long	sem_nsems;		/* no. of semaphores in array */
	unsigned long	__unused1;
	unsigned long	__unused2;
};
<<<<<<< HEAD
#else
struct semid64_ds {
	struct ipc64_perm sem_perm;		/* permissions .. see ipc.h */
	unsigned long   sem_otime;		/* last semop time */
	unsigned long   sem_ctime;		/* last change time */
	unsigned long	sem_nsems;		/* no. of semaphores in array */
	unsigned long	sem_otime_high;
	unsigned long	sem_ctime_high;
};
#endif
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

#endif /* _ASM_SEMBUF_H */
