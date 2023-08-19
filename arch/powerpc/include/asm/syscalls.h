/* SPDX-License-Identifier: GPL-2.0 */
#ifndef __ASM_POWERPC_SYSCALLS_H
#define __ASM_POWERPC_SYSCALLS_H
#ifdef __KERNEL__

#include <linux/compiler.h>
#include <linux/linkage.h>
#include <linux/types.h>

struct rtas_args;

asmlinkage long sys_mmap(unsigned long addr, size_t len,
		unsigned long prot, unsigned long flags,
		unsigned long fd, off_t offset);
asmlinkage long sys_mmap2(unsigned long addr, size_t len,
		unsigned long prot, unsigned long flags,
		unsigned long fd, unsigned long pgoff);
asmlinkage long ppc64_personality(unsigned long personality);
<<<<<<< HEAD
asmlinkage long sys_rtas(struct rtas_args __user *uargs);
=======
asmlinkage int ppc_rtas(struct rtas_args __user *uargs);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

#endif /* __KERNEL__ */
#endif /* __ASM_POWERPC_SYSCALLS_H */
