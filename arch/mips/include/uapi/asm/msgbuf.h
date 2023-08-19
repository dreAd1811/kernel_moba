/* SPDX-License-Identifier: GPL-2.0 WITH Linux-syscall-note */
#ifndef _ASM_MSGBUF_H
#define _ASM_MSGBUF_H


/*
 * The msqid64_ds structure for the MIPS architecture.
 * Note extra padding because this structure is passed back and forth
 * between kernel and user space.
 *
 * Pad space is left for:
<<<<<<< HEAD
 * - 2 miscellaneous unsigned long values
 */

#if defined(__mips64)
struct msqid64_ds {
	struct ipc64_perm msg_perm;
	__kernel_time_t msg_stime;	/* last msgsnd time */
	__kernel_time_t msg_rtime;	/* last msgrcv time */
	__kernel_time_t msg_ctime;	/* last change time */
	unsigned long  msg_cbytes;	/* current number of bytes on queue */
	unsigned long  msg_qnum;	/* number of messages in queue */
	unsigned long  msg_qbytes;	/* max number of bytes on queue */
	__kernel_pid_t msg_lspid;	/* pid of last msgsnd */
	__kernel_pid_t msg_lrpid;	/* last receive pid */
	unsigned long  __unused4;
	unsigned long  __unused5;
};
#elif defined (__MIPSEB__)
struct msqid64_ds {
	struct ipc64_perm msg_perm;
	unsigned long  msg_stime_high;
	unsigned long  msg_stime;	/* last msgsnd time */
	unsigned long  msg_rtime_high;
	unsigned long  msg_rtime;	/* last msgrcv time */
	unsigned long  msg_ctime_high;
	unsigned long  msg_ctime;	/* last change time */
	unsigned long  msg_cbytes;	/* current number of bytes on queue */
	unsigned long  msg_qnum;	/* number of messages in queue */
	unsigned long  msg_qbytes;	/* max number of bytes on queue */
	__kernel_pid_t msg_lspid;	/* pid of last msgsnd */
	__kernel_pid_t msg_lrpid;	/* last receive pid */
	unsigned long  __unused4;
	unsigned long  __unused5;
};
#elif defined (__MIPSEL__)
struct msqid64_ds {
	struct ipc64_perm msg_perm;
	unsigned long  msg_stime;	/* last msgsnd time */
	unsigned long  msg_stime_high;
	unsigned long  msg_rtime;	/* last msgrcv time */
	unsigned long  msg_rtime_high;
	unsigned long  msg_ctime;	/* last change time */
	unsigned long  msg_ctime_high;
	unsigned long  msg_cbytes;	/* current number of bytes on queue */
	unsigned long  msg_qnum;	/* number of messages in queue */
	unsigned long  msg_qbytes;	/* max number of bytes on queue */
	__kernel_pid_t msg_lspid;	/* pid of last msgsnd */
	__kernel_pid_t msg_lrpid;	/* last receive pid */
	unsigned long  __unused4;
	unsigned long  __unused5;
};
#else
#warning no endianess set
#endif
=======
 * - extension of time_t to 64-bit on 32-bitsystem to solve the y2038 problem
 * - 2 miscellaneous unsigned long values
 */

struct msqid64_ds {
	struct ipc64_perm msg_perm;
#if !defined(__mips64) && defined(__MIPSEB__)
	unsigned long	__unused1;
#endif
	__kernel_time_t msg_stime;	/* last msgsnd time */
#if !defined(__mips64) && defined(__MIPSEL__)
	unsigned long	__unused1;
#endif
#if !defined(__mips64) && defined(__MIPSEB__)
	unsigned long	__unused2;
#endif
	__kernel_time_t msg_rtime;	/* last msgrcv time */
#if !defined(__mips64) && defined(__MIPSEL__)
	unsigned long	__unused2;
#endif
#if !defined(__mips64) && defined(__MIPSEB__)
	unsigned long	__unused3;
#endif
	__kernel_time_t msg_ctime;	/* last change time */
#if !defined(__mips64) && defined(__MIPSEL__)
	unsigned long	__unused3;
#endif
	unsigned long  msg_cbytes;	/* current number of bytes on queue */
	unsigned long  msg_qnum;	/* number of messages in queue */
	unsigned long  msg_qbytes;	/* max number of bytes on queue */
	__kernel_pid_t msg_lspid;	/* pid of last msgsnd */
	__kernel_pid_t msg_lrpid;	/* last receive pid */
	unsigned long  __unused4;
	unsigned long  __unused5;
};
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

#endif /* _ASM_MSGBUF_H */
