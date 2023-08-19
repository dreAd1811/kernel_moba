<<<<<<< HEAD
// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (C) Maxime Coquelin 2015
 * Copyright (C) STMicroelectronics 2017
 * Author:  Maxime Coquelin <mcoquelin.stm32@gmail.com>
 */

#include <linux/kernel.h>
#include <asm/mach/arch.h>
#ifdef CONFIG_ARM_SINGLE_ARMV7M
#include <asm/v7m.h>
#endif
=======
/*
 * Copyright (C) Maxime Coquelin 2015
 * Author:  Maxime Coquelin <mcoquelin.stm32@gmail.com>
 * License terms:  GNU General Public License (GPL), version 2
 */

#include <linux/kernel.h>
#include <asm/v7m.h>
#include <asm/mach/arch.h>
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

static const char *const stm32_compat[] __initconst = {
	"st,stm32f429",
	"st,stm32f469",
	"st,stm32f746",
<<<<<<< HEAD
	"st,stm32f769",
	"st,stm32h743",
	"st,stm32mp157",
=======
	"st,stm32h743",
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	NULL
};

DT_MACHINE_START(STM32DT, "STM32 (Device Tree Support)")
	.dt_compat = stm32_compat,
<<<<<<< HEAD
#ifdef CONFIG_ARM_SINGLE_ARMV7M
	.restart = armv7m_restart,
#endif
=======
	.restart = armv7m_restart,
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
MACHINE_END
