<<<<<<< HEAD
/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (C) 2012 Heiko Stuebner <heiko@sntech.de>
=======
/*
 * Copyright (C) 2012 Heiko Stuebner <heiko@sntech.de>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
 */

#ifndef __PLAT_S3C_SPI_CORE_H
#define __PLAT_S3C_SPI_CORE_H

/* These functions are only for use with the core support code, such as
 * the cpu specific initialisation code
 */

/* re-define device name depending on support. */
static inline void s3c64xx_spi_setname(char *name)
{
#ifdef CONFIG_S3C64XX_DEV_SPI0
	s3c64xx_device_spi0.name = name;
#endif
#ifdef CONFIG_S3C64XX_DEV_SPI1
	s3c64xx_device_spi1.name = name;
#endif
#ifdef CONFIG_S3C64XX_DEV_SPI2
	s3c64xx_device_spi2.name = name;
#endif
}

#endif /* __PLAT_S3C_SPI_CORE_H */
