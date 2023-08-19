/*
 * syscalls.h - Linux syscall interfaces (arch-specific)
 *
 * Copyright (c) 2008 Jaswinder Singh Rajput
 *
 * This file is released under the GPLv2.
 * See the file COPYING for more details.
 */

#ifndef _ASM_X86_SYSCALLS_H
#define _ASM_X86_SYSCALLS_H

#include <linux/compiler.h>
#include <linux/linkage.h>
#include <linux/signal.h>
#include <linux/types.h>

/* Common in X86_32 and X86_64 */
/* kernel/ioport.c */
<<<<<<< HEAD
long ksys_ioperm(unsigned long from, unsigned long num, int turn_on);

#ifdef CONFIG_X86_32
/*
 * These definitions are only valid on pure 32-bit systems; x86-64 uses a
 * different syscall calling convention
 */
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
asmlinkage long sys_ioperm(unsigned long, unsigned long, int);
asmlinkage long sys_iopl(unsigned int);

/* kernel/ldt.c */
asmlinkage long sys_modify_ldt(int, void __user *, unsigned long);

/* kernel/signal.c */
asmlinkage long sys_rt_sigreturn(void);

/* kernel/tls.c */
asmlinkage long sys_set_thread_area(struct user_desc __user *);
asmlinkage long sys_get_thread_area(struct user_desc __user *);

/* X86_32 only */
<<<<<<< HEAD

/* kernel/signal.c */
asmlinkage long sys_sigreturn(void);
=======
#ifdef CONFIG_X86_32

/* kernel/signal.c */
asmlinkage unsigned long sys_sigreturn(void);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* kernel/vm86_32.c */
struct vm86_struct;
asmlinkage long sys_vm86old(struct vm86_struct __user *);
asmlinkage long sys_vm86(unsigned long, unsigned long);

<<<<<<< HEAD
=======
#else /* CONFIG_X86_32 */

/* X86_64 only */
/* kernel/process_64.c */
asmlinkage long sys_arch_prctl(int, unsigned long);

/* kernel/sys_x86_64.c */
asmlinkage long sys_mmap(unsigned long, unsigned long, unsigned long,
			 unsigned long, unsigned long, unsigned long);

>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
#endif /* CONFIG_X86_32 */
#endif /* _ASM_X86_SYSCALLS_H */
