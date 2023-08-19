<<<<<<< HEAD
// SPDX-License-Identifier: GPL-2.0
//
// Copyright 2010 Promwad Innovation Company
//	Yauhen Kharuzhy <yauhen.kharuzhy@promwad.com>
//
// S3C2416 - Helper functions for setting up SDHCI device(s) GPIO (HSMMC)
//
// Based on mach-s3c64xx/setup-sdhci-gpio.c
=======
/* linux/arch/arm/plat-s3c2416/setup-sdhci-gpio.c
 *
 * Copyright 2010 Promwad Innovation Company
 *	Yauhen Kharuzhy <yauhen.kharuzhy@promwad.com>
 *
 * S3C2416 - Helper functions for setting up SDHCI device(s) GPIO (HSMMC)
 *
 * Based on mach-s3c64xx/setup-sdhci-gpio.c
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
*/
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/interrupt.h>
#include <linux/platform_device.h>
#include <linux/io.h>
#include <linux/gpio.h>

#include <mach/regs-gpio.h>
#include <mach/gpio-samsung.h>
#include <plat/gpio-cfg.h>

void s3c2416_setup_sdhci0_cfg_gpio(struct platform_device *dev, int width)
{
	s3c_gpio_cfgrange_nopull(S3C2410_GPE(5), 2 + width, S3C_GPIO_SFN(2));
}

void s3c2416_setup_sdhci1_cfg_gpio(struct platform_device *dev, int width)
{
	s3c_gpio_cfgrange_nopull(S3C2410_GPL(0), width, S3C_GPIO_SFN(2));
	s3c_gpio_cfgrange_nopull(S3C2410_GPL(8), 2, S3C_GPIO_SFN(2));
}
