<<<<<<< HEAD
/* SPDX-License-Identifier: GPL-2.0 */
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
/*
 * Copyright (c) 2011 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com
 *
 * Common Header for S5PV210 machines
<<<<<<< HEAD
=======
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
 */

#ifndef __ARCH_ARM_MACH_S5PV210_COMMON_H
#define __ARCH_ARM_MACH_S5PV210_COMMON_H

#ifdef CONFIG_PM_SLEEP
u32 exynos_get_eint_wake_mask(void);
void s5pv210_cpu_resume(void);
void s5pv210_pm_init(void);
#else
static inline void s5pv210_pm_init(void) {}
#endif

#endif /* __ARCH_ARM_MACH_S5PV210_COMMON_H */
