/* SPDX-License-Identifier: GPL-2.0 WITH Linux-syscall-note */
#ifndef _ASM_X86_SEMBUF_H
#define _ASM_X86_SEMBUF_H

/*
 * The semid64_ds structure for x86 architecture.
 * Note extra padding because this structure is passed back and forth
 * between kernel and user space.
 *
 * Pad space is left for:
<<<<<<< HEAD
 * - 2 miscellaneous 32-bit values
 *
 * x86_64 and x32 incorrectly added padding here, so the structures
 * are still incompatible with the padding on x86.
 */
struct semid64_ds {
	struct ipc64_perm sem_perm;	/* permissions .. see ipc.h */
#ifdef __i386__
	unsigned long	sem_otime;	/* last semop time */
	unsigned long	sem_otime_high;
	unsigned long	sem_ctime;	/* last change time */
	unsigned long	sem_ctime_high;
#else
=======
 * - 64-bit time_t to solve y2038 problem
 * - 2 miscellaneous 32-bit values
 */
struct semid64_ds {
	struct ipc64_perm sem_perm;	/* permissions .. see ipc.h */
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	__kernel_time_t	sem_otime;	/* last semop time */
	__kernel_ulong_t __unused1;
	__kernel_time_t	sem_ctime;	/* last change time */
	__kernel_ulong_t __unused2;
<<<<<<< HEAD
#endif
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	__kernel_ulong_t sem_nsems;	/* no. of semaphores in array */
	__kernel_ulong_t __unused3;
	__kernel_ulong_t __unused4;
};

#endif /* _ASM_X86_SEMBUF_H */
