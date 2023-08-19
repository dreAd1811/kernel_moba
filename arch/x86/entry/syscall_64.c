// SPDX-License-Identifier: GPL-2.0
/* System call table for x86-64. */

#include <linux/linkage.h>
#include <linux/sys.h>
#include <linux/cache.h>
<<<<<<< HEAD
#include <linux/syscalls.h>
#include <asm/asm-offsets.h>
#include <asm/syscall.h>

extern asmlinkage long sys_ni_syscall(void);

SYSCALL_DEFINE0(ni_syscall)
{
	return sys_ni_syscall();
}

#define __SYSCALL_64(nr, sym, qual) extern asmlinkage long sym(const struct pt_regs *);
=======
#include <asm/asm-offsets.h>
#include <asm/syscall.h>

#define __SYSCALL_64(nr, sym, qual) extern asmlinkage long sym(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
#include <asm/syscalls_64.h>
#undef __SYSCALL_64

#define __SYSCALL_64(nr, sym, qual) [nr] = sym,

<<<<<<< HEAD
=======
extern long sys_ni_syscall(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long);

>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
asmlinkage const sys_call_ptr_t sys_call_table[__NR_syscall_max+1] = {
	/*
	 * Smells like a compiler bug -- it doesn't work
	 * when the & below is removed.
	 */
<<<<<<< HEAD
	[0 ... __NR_syscall_max] = &__x64_sys_ni_syscall,
=======
	[0 ... __NR_syscall_max] = &sys_ni_syscall,
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
#include <asm/syscalls_64.h>
};
