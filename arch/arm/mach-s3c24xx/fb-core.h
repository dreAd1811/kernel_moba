<<<<<<< HEAD
/* SPDX-License-Identifier: GPL-2.0 */
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
/*
 * Copyright 2010 Samsung Electronics Co., Ltd.
 *	Pawel Osciak <p.osciak@samsung.com>
 *
 * Samsung framebuffer driver core functions
<<<<<<< HEAD
=======
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
 */
#ifndef __ASM_PLAT_FB_CORE_H
#define __ASM_PLAT_FB_CORE_H __FILE__

/*
 * These functions are only for use with the core support code, such as
 * the CPU-specific initialization code.
 */

/* Re-define device name depending on support. */
static inline void s3c_fb_setname(char *name)
{
#ifdef CONFIG_S3C_DEV_FB
	s3c_device_fb.name = name;
#endif
}

#endif /* __ASM_PLAT_FB_CORE_H */
