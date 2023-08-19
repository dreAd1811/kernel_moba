// SPDX-License-Identifier: GPL-2.0
#include <linux/errno.h>
#include <linux/sched.h>
#include <linux/sched/task_stack.h>
#include <linux/mm.h>
#include <linux/smp.h>
#include <linux/sem.h>
#include <linux/msg.h>
#include <linux/shm.h>
#include <linux/stat.h>
#include <linux/syscalls.h>
#include <linux/mman.h>
#include <linux/file.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/ipc.h>
#include <asm/cacheflush.h>
#include <linux/uaccess.h>
#include <asm/unistd.h>
#include <asm/syscalls.h>

/*
 * sys_pipe() is the normal C calling standard for creating
 * a pipe. It's not the way Unix traditionally does this, though.
 */
asmlinkage int sys_sh_pipe(void)
{
	int fd[2];
	int error;

	error = do_pipe_flags(fd, 0);
	if (!error) {
		current_pt_regs()->regs[1] = fd[1];
		return fd[0];
	}
	return error;
}

asmlinkage ssize_t sys_pread_wrapper(unsigned int fd, char __user *buf,
			     size_t count, long dummy, loff_t pos)
{
<<<<<<< HEAD
	return ksys_pread64(fd, buf, count, pos);
=======
	return sys_pread64(fd, buf, count, pos);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
}

asmlinkage ssize_t sys_pwrite_wrapper(unsigned int fd, const char __user *buf,
			      size_t count, long dummy, loff_t pos)
{
<<<<<<< HEAD
	return ksys_pwrite64(fd, buf, count, pos);
=======
	return sys_pwrite64(fd, buf, count, pos);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
}

asmlinkage int sys_fadvise64_64_wrapper(int fd, u32 offset0, u32 offset1,
				u32 len0, u32 len1, int advice)
{
#ifdef  __LITTLE_ENDIAN__
<<<<<<< HEAD
	return ksys_fadvise64_64(fd, (u64)offset1 << 32 | offset0,
				 (u64)len1 << 32 | len0, advice);
#else
	return ksys_fadvise64_64(fd, (u64)offset0 << 32 | offset1,
				 (u64)len0 << 32 | len1, advice);
=======
	return sys_fadvise64_64(fd, (u64)offset1 << 32 | offset0,
				(u64)len1 << 32 | len0,	advice);
#else
	return sys_fadvise64_64(fd, (u64)offset0 << 32 | offset1,
				(u64)len0 << 32 | len1,	advice);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
#endif
}
