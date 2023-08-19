<<<<<<< HEAD
/* SPDX-License-Identifier: GPL-2.0 */
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
/*
 * (c) 2005 Guillaume GOURAT / NexVision
 *          guillaume.gourat@nexvision.fr
 *
 * NexVision OTOM board memory map definitions
<<<<<<< HEAD
 */
=======
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
*/
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/*
 * ok, we've used up to 0x01300000, now we need to find space for the
 * peripherals that live in the nGCS[x] areas, which are quite numerous
 * in their space.
 */

#ifndef __MACH_S3C24XX_OTOM_H
#define __MACH_S3C24XX_OTOM_H __FILE__

#define OTOM_PA_CS8900A_BASE	(S3C2410_CS3 + 0x01000000)	/* nGCS3 +0x01000000 */
#define OTOM_VA_CS8900A_BASE	S3C2410_ADDR(0x04000000)	/* 0xF4000000 */

/* physical offset addresses for the peripherals */

#define OTOM_PA_FLASH0_BASE	(S3C2410_CS0)

#endif /* __MACH_S3C24XX_OTOM_H */
