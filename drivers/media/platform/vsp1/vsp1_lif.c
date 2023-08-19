<<<<<<< HEAD
// SPDX-License-Identifier: GPL-2.0+
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
/*
 * vsp1_lif.c  --  R-Car VSP1 LCD Controller Interface
 *
 * Copyright (C) 2013-2014 Renesas Electronics Corporation
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

#include <linux/device.h>
#include <linux/gfp.h>

#include <media/v4l2-subdev.h>

#include "vsp1.h"
#include "vsp1_dl.h"
#include "vsp1_lif.h"

#define LIF_MIN_SIZE				2U
#define LIF_MAX_SIZE				8190U

/* -----------------------------------------------------------------------------
 * Device Access
 */

<<<<<<< HEAD
static inline void vsp1_lif_write(struct vsp1_lif *lif,
				  struct vsp1_dl_body *dlb, u32 reg, u32 data)
{
	vsp1_dl_body_write(dlb, reg + lif->entity.index * VI6_LIF_OFFSET,
			       data);
=======
static inline void vsp1_lif_write(struct vsp1_lif *lif, struct vsp1_dl_list *dl,
				  u32 reg, u32 data)
{
	vsp1_dl_list_write(dl, reg + lif->entity.index * VI6_LIF_OFFSET, data);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
}

/* -----------------------------------------------------------------------------
 * V4L2 Subdevice Operations
 */

<<<<<<< HEAD
static const unsigned int lif_codes[] = {
	MEDIA_BUS_FMT_ARGB8888_1X32,
	MEDIA_BUS_FMT_AYUV8_1X32,
};

=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
static int lif_enum_mbus_code(struct v4l2_subdev *subdev,
			      struct v4l2_subdev_pad_config *cfg,
			      struct v4l2_subdev_mbus_code_enum *code)
{
<<<<<<< HEAD
	return vsp1_subdev_enum_mbus_code(subdev, cfg, code, lif_codes,
					  ARRAY_SIZE(lif_codes));
=======
	static const unsigned int codes[] = {
		MEDIA_BUS_FMT_ARGB8888_1X32,
		MEDIA_BUS_FMT_AYUV8_1X32,
	};

	return vsp1_subdev_enum_mbus_code(subdev, cfg, code, codes,
					  ARRAY_SIZE(codes));
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
}

static int lif_enum_frame_size(struct v4l2_subdev *subdev,
			       struct v4l2_subdev_pad_config *cfg,
			       struct v4l2_subdev_frame_size_enum *fse)
{
	return vsp1_subdev_enum_frame_size(subdev, cfg, fse, LIF_MIN_SIZE,
					   LIF_MIN_SIZE, LIF_MAX_SIZE,
					   LIF_MAX_SIZE);
}

static int lif_set_format(struct v4l2_subdev *subdev,
			  struct v4l2_subdev_pad_config *cfg,
			  struct v4l2_subdev_format *fmt)
{
<<<<<<< HEAD
	return vsp1_subdev_set_pad_format(subdev, cfg, fmt, lif_codes,
					  ARRAY_SIZE(lif_codes),
					  LIF_MIN_SIZE, LIF_MIN_SIZE,
					  LIF_MAX_SIZE, LIF_MAX_SIZE);
=======
	struct vsp1_lif *lif = to_lif(subdev);
	struct v4l2_subdev_pad_config *config;
	struct v4l2_mbus_framefmt *format;
	int ret = 0;

	mutex_lock(&lif->entity.lock);

	config = vsp1_entity_get_pad_config(&lif->entity, cfg, fmt->which);
	if (!config) {
		ret = -EINVAL;
		goto done;
	}

	/* Default to YUV if the requested format is not supported. */
	if (fmt->format.code != MEDIA_BUS_FMT_ARGB8888_1X32 &&
	    fmt->format.code != MEDIA_BUS_FMT_AYUV8_1X32)
		fmt->format.code = MEDIA_BUS_FMT_AYUV8_1X32;

	format = vsp1_entity_get_pad_format(&lif->entity, config, fmt->pad);

	if (fmt->pad == LIF_PAD_SOURCE) {
		/*
		 * The LIF source format is always identical to its sink
		 * format.
		 */
		fmt->format = *format;
		goto done;
	}

	format->code = fmt->format.code;
	format->width = clamp_t(unsigned int, fmt->format.width,
				LIF_MIN_SIZE, LIF_MAX_SIZE);
	format->height = clamp_t(unsigned int, fmt->format.height,
				 LIF_MIN_SIZE, LIF_MAX_SIZE);
	format->field = V4L2_FIELD_NONE;
	format->colorspace = V4L2_COLORSPACE_SRGB;

	fmt->format = *format;

	/* Propagate the format to the source pad. */
	format = vsp1_entity_get_pad_format(&lif->entity, config,
					    LIF_PAD_SOURCE);
	*format = fmt->format;

done:
	mutex_unlock(&lif->entity.lock);
	return ret;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
}

static const struct v4l2_subdev_pad_ops lif_pad_ops = {
	.init_cfg = vsp1_entity_init_cfg,
	.enum_mbus_code = lif_enum_mbus_code,
	.enum_frame_size = lif_enum_frame_size,
	.get_fmt = vsp1_subdev_get_pad_format,
	.set_fmt = lif_set_format,
};

static const struct v4l2_subdev_ops lif_ops = {
	.pad    = &lif_pad_ops,
};

/* -----------------------------------------------------------------------------
 * VSP1 Entity Operations
 */

<<<<<<< HEAD
static void lif_configure_stream(struct vsp1_entity *entity,
				 struct vsp1_pipeline *pipe,
				 struct vsp1_dl_body *dlb)
=======
static void lif_configure(struct vsp1_entity *entity,
			  struct vsp1_pipeline *pipe,
			  struct vsp1_dl_list *dl,
			  enum vsp1_entity_params params)
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
{
	const struct v4l2_mbus_framefmt *format;
	struct vsp1_lif *lif = to_lif(&entity->subdev);
	unsigned int hbth = 1300;
	unsigned int obth = 400;
	unsigned int lbth = 200;

<<<<<<< HEAD
=======
	if (params != VSP1_ENTITY_PARAMS_INIT)
		return;

>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	format = vsp1_entity_get_pad_format(&lif->entity, lif->entity.config,
					    LIF_PAD_SOURCE);

	obth = min(obth, (format->width + 1) / 2 * format->height - 4);

<<<<<<< HEAD
	vsp1_lif_write(lif, dlb, VI6_LIF_CSBTH,
			(hbth << VI6_LIF_CSBTH_HBTH_SHIFT) |
			(lbth << VI6_LIF_CSBTH_LBTH_SHIFT));

	vsp1_lif_write(lif, dlb, VI6_LIF_CTRL,
			(obth << VI6_LIF_CTRL_OBTH_SHIFT) |
			(format->code == 0 ? VI6_LIF_CTRL_CFMT : 0) |
			VI6_LIF_CTRL_REQSEL | VI6_LIF_CTRL_LIF_EN);

	/*
	 * On R-Car V3M the LIF0 buffer attribute register has to be set to a
	 * non-default value to guarantee proper operation (otherwise artifacts
	 * may appear on the output). The value required by the manual is not
	 * explained but is likely a buffer size or threshold.
	 */
	if ((entity->vsp1->version & VI6_IP_VERSION_MASK) ==
	    (VI6_IP_VERSION_MODEL_VSPD_V3 | VI6_IP_VERSION_SOC_V3M))
		vsp1_lif_write(lif, dlb, VI6_LIF_LBA,
			       VI6_LIF_LBA_LBA0 |
			       (1536 << VI6_LIF_LBA_LBA1_SHIFT));
}

static const struct vsp1_entity_operations lif_entity_ops = {
	.configure_stream = lif_configure_stream,
=======
	vsp1_lif_write(lif, dl, VI6_LIF_CSBTH,
			(hbth << VI6_LIF_CSBTH_HBTH_SHIFT) |
			(lbth << VI6_LIF_CSBTH_LBTH_SHIFT));

	vsp1_lif_write(lif, dl, VI6_LIF_CTRL,
			(obth << VI6_LIF_CTRL_OBTH_SHIFT) |
			(format->code == 0 ? VI6_LIF_CTRL_CFMT : 0) |
			VI6_LIF_CTRL_REQSEL | VI6_LIF_CTRL_LIF_EN);
}

static const struct vsp1_entity_operations lif_entity_ops = {
	.configure = lif_configure,
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
};

/* -----------------------------------------------------------------------------
 * Initialization and Cleanup
 */

struct vsp1_lif *vsp1_lif_create(struct vsp1_device *vsp1, unsigned int index)
{
	struct vsp1_lif *lif;
	int ret;

	lif = devm_kzalloc(vsp1->dev, sizeof(*lif), GFP_KERNEL);
	if (lif == NULL)
		return ERR_PTR(-ENOMEM);

	lif->entity.ops = &lif_entity_ops;
	lif->entity.type = VSP1_ENTITY_LIF;
	lif->entity.index = index;

	/*
	 * The LIF is never exposed to userspace, but media entity registration
	 * requires a function to be set. Use PROC_VIDEO_PIXEL_FORMATTER just to
	 * avoid triggering a WARN_ON(), the value won't be seen anywhere.
	 */
	ret = vsp1_entity_init(vsp1, &lif->entity, "lif", 2, &lif_ops,
			       MEDIA_ENT_F_PROC_VIDEO_PIXEL_FORMATTER);
	if (ret < 0)
		return ERR_PTR(ret);

	return lif;
}
