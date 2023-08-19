/*
 * shmob_drm.h  --  SH Mobile DRM driver
 *
 * Copyright (C) 2012 Renesas Electronics Corporation
 *
 * Laurent Pinchart (laurent.pinchart@ideasonboard.com)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#ifndef __SHMOB_DRM_DRV_H__
#define __SHMOB_DRM_DRV_H__

#include <linux/kernel.h>
#include <linux/platform_data/shmob_drm.h>
#include <linux/spinlock.h>

#include "shmob_drm_crtc.h"

struct clk;
struct device;
struct drm_device;
<<<<<<< HEAD
=======
struct sh_mobile_meram_info;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

struct shmob_drm_device {
	struct device *dev;
	const struct shmob_drm_platform_data *pdata;

	void __iomem *mmio;
	struct clk *clock;
<<<<<<< HEAD
=======
	struct sh_mobile_meram_info *meram;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	u32 lddckr;
	u32 ldmt1r;

	spinlock_t irq_lock;		/* Protects hardware LDINTR register */

	struct drm_device *ddev;

	struct shmob_drm_crtc crtc;
	struct shmob_drm_encoder encoder;
	struct shmob_drm_connector connector;
};

#endif /* __SHMOB_DRM_DRV_H__ */
