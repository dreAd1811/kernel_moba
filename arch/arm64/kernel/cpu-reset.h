/*
 * CPU reset routines
 *
 * Copyright (C) 2015 Huawei Futurewei Technologies.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef _ARM64_CPU_RESET_H
#define _ARM64_CPU_RESET_H

#include <asm/virt.h>

void __cpu_soft_restart(unsigned long el2_switch, unsigned long entry,
	unsigned long arg0, unsigned long arg1, unsigned long arg2);

<<<<<<< HEAD
static inline void __noreturn cpu_soft_restart(unsigned long entry,
					       unsigned long arg0,
					       unsigned long arg1,
					       unsigned long arg2)
{
	typeof(__cpu_soft_restart) *restart;

	unsigned long el2_switch = !is_kernel_in_hyp_mode() &&
		is_hyp_mode_available();
	restart = (void *)__pa_symbol(__cpu_soft_restart);
=======
static inline void __noreturn cpu_soft_restart_kexec(unsigned long el2_switch,
	unsigned long entry, unsigned long arg0, unsigned long arg1,
	unsigned long arg2)
{
	typeof(__cpu_soft_restart) *restart;

	el2_switch = el2_switch && !is_kernel_in_hyp_mode() &&
		is_hyp_mode_available();
	restart = (void *)__pa_function(__cpu_soft_restart);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	cpu_install_idmap();
	restart(el2_switch, entry, arg0, arg1, arg2);
	unreachable();
}

#endif
