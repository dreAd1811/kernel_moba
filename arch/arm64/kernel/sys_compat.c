/*
 * Based on arch/arm/kernel/sys_arm.c
 *
 * Copyright (C) People who wrote linux/arch/i386/kernel/sys_i386.c
 * Copyright (C) 1995, 1996 Russell King.
 * Copyright (C) 2012 ARM Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <linux/compat.h>
#include <linux/personality.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>
#include <linux/slab.h>
#include <linux/syscalls.h>
#include <linux/uaccess.h>

#include <asm/cacheflush.h>
<<<<<<< HEAD
#include <asm/system_misc.h>
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
#include <asm/unistd.h>

static long
__do_compat_cache_op(unsigned long start, unsigned long end)
{
	long ret;

	do {
		unsigned long chunk = min(PAGE_SIZE, end - start);

		if (fatal_signal_pending(current))
			return 0;

		ret = __flush_cache_user_range(start, start + chunk);
		if (ret)
			return ret;

		cond_resched();
		start += chunk;
	} while (start < end);

	return 0;
}

static inline long
do_compat_cache_op(unsigned long start, unsigned long end, int flags)
{
	if (end < start || flags)
		return -EINVAL;

<<<<<<< HEAD
	if (!access_ok(VERIFY_READ, (const void __user *)start, end - start))
=======
	if (!access_ok(VERIFY_READ, start, end - start))
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
		return -EFAULT;

	return __do_compat_cache_op(start, end);
}
/*
 * Handle all unrecognised system calls.
 */
<<<<<<< HEAD
long compat_arm_syscall(struct pt_regs *regs, int scno)
{
	siginfo_t info;

	switch (scno) {
=======
long compat_arm_syscall(struct pt_regs *regs)
{
	unsigned int no = regs->regs[7];

	switch (no) {
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	/*
	 * Flush a region from virtual address 'r0' to virtual address 'r1'
	 * _exclusive_.  There is no alignment requirement on either address;
	 * user space does not need to know the hardware cache layout.
	 *
	 * r2 contains flags.  It should ALWAYS be passed as ZERO until it
	 * is defined to be something else.  For now we ignore it, but may
	 * the fires of hell burn in your belly if you break this rule. ;)
	 *
	 * (at a later date, we may want to allow this call to not flush
	 * various aspects of the cache.  Passing '0' will guarantee that
	 * everything necessary gets flushed to maintain consistency in
	 * the specified region).
	 */
	case __ARM_NR_compat_cacheflush:
		return do_compat_cache_op(regs->regs[0], regs->regs[1], regs->regs[2]);

	case __ARM_NR_compat_set_tls:
<<<<<<< HEAD
		current->thread.uw.tp_value = regs->regs[0];
=======
		current->thread.tp_value = regs->regs[0];
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

		/*
		 * Protect against register corruption from context switch.
		 * See comment in tls_thread_flush.
		 */
		barrier();
		write_sysreg(regs->regs[0], tpidrro_el0);
		return 0;

	default:
<<<<<<< HEAD
		/*
		 * Calls 0xf0xxx..0xf07ff are defined to return -ENOSYS
		 * if not implemented, rather than raising SIGILL. This
		 * way the calling program can gracefully determine whether
		 * a feature is supported.
		 */
		if (scno < __ARM_NR_COMPAT_END)
			return -ENOSYS;
		break;
	}

	clear_siginfo(&info);
	info.si_signo = SIGILL;
	info.si_errno = 0;
	info.si_code  = ILL_ILLTRP;
	info.si_addr  = (void __user *)instruction_pointer(regs) -
			 (compat_thumb_mode(regs) ? 2 : 4);

	arm64_notify_die("Oops - bad compat syscall(2)", regs, &info, scno);
	return 0;
=======
		return -ENOSYS;
	}
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
}
