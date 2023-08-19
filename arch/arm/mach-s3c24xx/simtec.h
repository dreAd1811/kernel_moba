<<<<<<< HEAD
/* SPDX-License-Identifier: GPL-2.0 */
/*
=======
/* linux/arch/arm/mach-s3c2410/nor-simtec.h
 *
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
 * Copyright (c) 2008 Simtec Electronics
 *	http://armlinux.simtec.co.uk/
 *	Ben Dooks <ben@simtec.co.uk>
 *
 * Simtec common functions
<<<<<<< HEAD
 */
=======
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
*/
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

struct s3c24xx_audio_simtec_pdata;

extern void nor_simtec_init(void);

extern int usb_simtec_init(void);

extern int simtec_audio_add(const char *codec_name, bool has_lr_routing,
			    struct s3c24xx_audio_simtec_pdata *pdata);
