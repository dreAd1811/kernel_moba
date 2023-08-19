/*
 * Copyright (C) 2010 Broadcom
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <linux/init.h>
#include <linux/irqchip.h>
#include <linux/of_address.h>
<<<<<<< HEAD
=======
#include <linux/clk/bcm2835.h>
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

#include <asm/mach/arch.h>
#include <asm/mach/map.h>

<<<<<<< HEAD
#include "platsmp.h"
=======
static void __init bcm2835_init(void)
{
	bcm2835_init_clocks();
}
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

static const char * const bcm2835_compat[] = {
#ifdef CONFIG_ARCH_MULTI_V6
	"brcm,bcm2835",
#endif
#ifdef CONFIG_ARCH_MULTI_V7
	"brcm,bcm2836",
<<<<<<< HEAD
	"brcm,bcm2837",
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
#endif
	NULL
};

DT_MACHINE_START(BCM2835, "BCM2835")
<<<<<<< HEAD
	.dt_compat = bcm2835_compat,
	.smp = smp_ops(bcm2836_smp_ops),
=======
	.init_machine = bcm2835_init,
	.dt_compat = bcm2835_compat
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
MACHINE_END
