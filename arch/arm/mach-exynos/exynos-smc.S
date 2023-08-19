<<<<<<< HEAD
/* SPDX-License-Identifier: GPL-2.0 */
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
/*
 * Copyright (C) 2012 Samsung Electronics.
 *
 * Copied from omap-smc.S Copyright (C) 2010 Texas Instruments, Inc.
<<<<<<< HEAD
=======
 *
 * This program is free software,you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
 */

#include <linux/linkage.h>

/*
 * Function signature: void exynos_smc(u32 cmd, u32 arg1, u32 arg2, u32 arg3)
 */

ENTRY(exynos_smc)
	stmfd	sp!, {r4-r11, lr}
	dsb
	smc	#0
	ldmfd	sp!, {r4-r11, pc}
ENDPROC(exynos_smc)
