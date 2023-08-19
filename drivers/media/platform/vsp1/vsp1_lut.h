<<<<<<< HEAD
/* SPDX-License-Identifier: GPL-2.0+ */
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
/*
 * vsp1_lut.h  --  R-Car VSP1 Look-Up Table
 *
 * Copyright (C) 2013 Renesas Corporation
 *
 * Contact: Laurent Pinchart (laurent.pinchart@ideasonboard.com)
<<<<<<< HEAD
=======
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
 */
#ifndef __VSP1_LUT_H__
#define __VSP1_LUT_H__

#include <linux/spinlock.h>

#include <media/media-entity.h>
#include <media/v4l2-ctrls.h>
#include <media/v4l2-subdev.h>

#include "vsp1_entity.h"

struct vsp1_device;

#define LUT_PAD_SINK				0
#define LUT_PAD_SOURCE				1

struct vsp1_lut {
	struct vsp1_entity entity;

	struct v4l2_ctrl_handler ctrls;

	spinlock_t lock;
	struct vsp1_dl_body *lut;
<<<<<<< HEAD
	struct vsp1_dl_body_pool *pool;
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
};

static inline struct vsp1_lut *to_lut(struct v4l2_subdev *subdev)
{
	return container_of(subdev, struct vsp1_lut, entity.subdev);
}

struct vsp1_lut *vsp1_lut_create(struct vsp1_device *vsp1);

#endif /* __VSP1_LUT_H__ */
