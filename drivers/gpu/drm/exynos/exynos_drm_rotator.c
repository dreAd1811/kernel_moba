/*
 * Copyright (C) 2012 Samsung Electronics Co.Ltd
 * Authors:
 *	YoungJun Cho <yj44.cho@samsung.com>
 *	Eunchul Kim <chulspro.kim@samsung.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundationr
 */

#include <linux/kernel.h>
<<<<<<< HEAD
#include <linux/component.h>
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
#include <linux/err.h>
#include <linux/interrupt.h>
#include <linux/io.h>
#include <linux/platform_device.h>
#include <linux/clk.h>
#include <linux/of_device.h>
#include <linux/pm_runtime.h>

#include <drm/drmP.h>
#include <drm/exynos_drm.h>
#include "regs-rotator.h"
#include "exynos_drm_drv.h"
<<<<<<< HEAD
#include "exynos_drm_iommu.h"
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
#include "exynos_drm_ipp.h"

/*
 * Rotator supports image crop/rotator and input/output DMA operations.
 * input DMA reads image data from the memory.
 * output DMA writes image data to memory.
<<<<<<< HEAD
 */

#define ROTATOR_AUTOSUSPEND_DELAY	2000

#define rot_read(offset)	readl(rot->regs + (offset))
=======
 *
 * M2M operation : supports crop/scale/rotation/csc so on.
 * Memory ----> Rotator H/W ----> Memory.
 */

/*
 * TODO
 * 1. check suspend/resume api if needed.
 * 2. need to check use case platform_device_id.
 * 3. check src/dst size with, height.
 * 4. need to add supported list in prop_list.
 */

#define get_rot_context(dev)	platform_get_drvdata(to_platform_device(dev))
#define get_ctx_from_ippdrv(ippdrv)	container_of(ippdrv,\
					struct rot_context, ippdrv);
#define rot_read(offset)		readl(rot->regs + (offset))
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
#define rot_write(cfg, offset)	writel(cfg, rot->regs + (offset))

enum rot_irq_status {
	ROT_IRQ_STATUS_COMPLETE	= 8,
	ROT_IRQ_STATUS_ILLEGAL	= 9,
};

<<<<<<< HEAD
struct rot_variant {
	const struct exynos_drm_ipp_formats *formats;
	unsigned int	num_formats;
=======
/*
 * A structure of limitation.
 *
 * @min_w: minimum width.
 * @min_h: minimum height.
 * @max_w: maximum width.
 * @max_h: maximum height.
 * @align: align size.
 */
struct rot_limit {
	u32	min_w;
	u32	min_h;
	u32	max_w;
	u32	max_h;
	u32	align;
};

/*
 * A structure of limitation table.
 *
 * @ycbcr420_2p: case of YUV.
 * @rgb888: case of RGB.
 */
struct rot_limit_table {
	struct rot_limit	ycbcr420_2p;
	struct rot_limit	rgb888;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
};

/*
 * A structure of rotator context.
 * @ippdrv: prepare initialization using ippdrv.
<<<<<<< HEAD
=======
 * @regs_res: register resources.
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
 * @regs: memory mapped io registers.
 * @clock: rotator gate clock.
 * @limit_tbl: limitation of rotator.
 * @irq: irq number.
<<<<<<< HEAD
 */
struct rot_context {
	struct exynos_drm_ipp ipp;
	struct drm_device *drm_dev;
	struct device	*dev;
	void __iomem	*regs;
	struct clk	*clock;
	const struct exynos_drm_ipp_formats *formats;
	unsigned int	num_formats;
	struct exynos_drm_ipp_task	*task;
=======
 * @cur_buf_id: current operation buffer id.
 * @suspended: suspended state.
 */
struct rot_context {
	struct exynos_drm_ippdrv	ippdrv;
	struct resource	*regs_res;
	void __iomem	*regs;
	struct clk	*clock;
	struct rot_limit_table	*limit_tbl;
	int	irq;
	int	cur_buf_id[EXYNOS_DRM_OPS_MAX];
	bool	suspended;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
};

static void rotator_reg_set_irq(struct rot_context *rot, bool enable)
{
	u32 val = rot_read(ROT_CONFIG);

	if (enable == true)
		val |= ROT_CONFIG_IRQ;
	else
		val &= ~ROT_CONFIG_IRQ;

	rot_write(val, ROT_CONFIG);
}

<<<<<<< HEAD
=======
static u32 rotator_reg_get_fmt(struct rot_context *rot)
{
	u32 val = rot_read(ROT_CONTROL);

	val &= ROT_CONTROL_FMT_MASK;

	return val;
}

>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
static enum rot_irq_status rotator_reg_get_irq_status(struct rot_context *rot)
{
	u32 val = rot_read(ROT_STATUS);

	val = ROT_STATUS_IRQ(val);

	if (val == ROT_STATUS_IRQ_VAL_COMPLETE)
		return ROT_IRQ_STATUS_COMPLETE;

	return ROT_IRQ_STATUS_ILLEGAL;
}

static irqreturn_t rotator_irq_handler(int irq, void *arg)
{
	struct rot_context *rot = arg;
<<<<<<< HEAD
=======
	struct exynos_drm_ippdrv *ippdrv = &rot->ippdrv;
	struct drm_exynos_ipp_cmd_node *c_node = ippdrv->c_node;
	struct drm_exynos_ipp_event_work *event_work = c_node->event_work;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	enum rot_irq_status irq_status;
	u32 val;

	/* Get execution result */
	irq_status = rotator_reg_get_irq_status(rot);

	/* clear status */
	val = rot_read(ROT_STATUS);
	val |= ROT_STATUS_IRQ_PENDING((u32)irq_status);
	rot_write(val, ROT_STATUS);

<<<<<<< HEAD
	if (rot->task) {
		struct exynos_drm_ipp_task *task = rot->task;

		rot->task = NULL;
		pm_runtime_mark_last_busy(rot->dev);
		pm_runtime_put_autosuspend(rot->dev);
		exynos_drm_ipp_task_done(task,
			irq_status == ROT_IRQ_STATUS_COMPLETE ? 0 : -EINVAL);
=======
	if (irq_status == ROT_IRQ_STATUS_COMPLETE) {
		event_work->ippdrv = ippdrv;
		event_work->buf_id[EXYNOS_DRM_OPS_DST] =
			rot->cur_buf_id[EXYNOS_DRM_OPS_DST];
		queue_work(ippdrv->event_workq, &event_work->work);
	} else {
		DRM_ERROR("the SFR is set illegally\n");
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	}

	return IRQ_HANDLED;
}

<<<<<<< HEAD
static void rotator_src_set_fmt(struct rot_context *rot, u32 fmt)
{
=======
static void rotator_align_size(struct rot_context *rot, u32 fmt, u32 *hsize,
		u32 *vsize)
{
	struct rot_limit_table *limit_tbl = rot->limit_tbl;
	struct rot_limit *limit;
	u32 mask, val;

	/* Get size limit */
	if (fmt == ROT_CONTROL_FMT_RGB888)
		limit = &limit_tbl->rgb888;
	else
		limit = &limit_tbl->ycbcr420_2p;

	/* Get mask for rounding to nearest aligned val */
	mask = ~((1 << limit->align) - 1);

	/* Set aligned width */
	val = ROT_ALIGN(*hsize, limit->align, mask);
	if (val < limit->min_w)
		*hsize = ROT_MIN(limit->min_w, mask);
	else if (val > limit->max_w)
		*hsize = ROT_MAX(limit->max_w, mask);
	else
		*hsize = val;

	/* Set aligned height */
	val = ROT_ALIGN(*vsize, limit->align, mask);
	if (val < limit->min_h)
		*vsize = ROT_MIN(limit->min_h, mask);
	else if (val > limit->max_h)
		*vsize = ROT_MAX(limit->max_h, mask);
	else
		*vsize = val;
}

static int rotator_src_set_fmt(struct device *dev, u32 fmt)
{
	struct rot_context *rot = dev_get_drvdata(dev);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	u32 val;

	val = rot_read(ROT_CONTROL);
	val &= ~ROT_CONTROL_FMT_MASK;

	switch (fmt) {
	case DRM_FORMAT_NV12:
		val |= ROT_CONTROL_FMT_YCBCR420_2P;
		break;
	case DRM_FORMAT_XRGB8888:
		val |= ROT_CONTROL_FMT_RGB888;
		break;
<<<<<<< HEAD
	}

	rot_write(val, ROT_CONTROL);
}

static void rotator_src_set_buf(struct rot_context *rot,
				struct exynos_drm_ipp_buffer *buf)
{
	u32 val;

	/* Set buffer size configuration */
	val = ROT_SET_BUF_SIZE_H(buf->buf.height) |
	      ROT_SET_BUF_SIZE_W(buf->buf.pitch[0] / buf->format->cpp[0]);
	rot_write(val, ROT_SRC_BUF_SIZE);

	/* Set crop image position configuration */
	val = ROT_CROP_POS_Y(buf->rect.y) | ROT_CROP_POS_X(buf->rect.x);
	rot_write(val, ROT_SRC_CROP_POS);
	val = ROT_SRC_CROP_SIZE_H(buf->rect.h) |
	      ROT_SRC_CROP_SIZE_W(buf->rect.w);
	rot_write(val, ROT_SRC_CROP_SIZE);

	/* Set buffer DMA address */
	rot_write(buf->dma_addr[0], ROT_SRC_BUF_ADDR(0));
	rot_write(buf->dma_addr[1], ROT_SRC_BUF_ADDR(1));
}

static void rotator_dst_set_transf(struct rot_context *rot,
				   unsigned int rotation)
{
=======
	default:
		DRM_ERROR("invalid image format\n");
		return -EINVAL;
	}

	rot_write(val, ROT_CONTROL);

	return 0;
}

static inline bool rotator_check_reg_fmt(u32 fmt)
{
	if ((fmt == ROT_CONTROL_FMT_YCBCR420_2P) ||
	    (fmt == ROT_CONTROL_FMT_RGB888))
		return true;

	return false;
}

static int rotator_src_set_size(struct device *dev, int swap,
		struct drm_exynos_pos *pos,
		struct drm_exynos_sz *sz)
{
	struct rot_context *rot = dev_get_drvdata(dev);
	u32 fmt, hsize, vsize;
	u32 val;

	/* Get format */
	fmt = rotator_reg_get_fmt(rot);
	if (!rotator_check_reg_fmt(fmt)) {
		DRM_ERROR("invalid format.\n");
		return -EINVAL;
	}

	/* Align buffer size */
	hsize = sz->hsize;
	vsize = sz->vsize;
	rotator_align_size(rot, fmt, &hsize, &vsize);

	/* Set buffer size configuration */
	val = ROT_SET_BUF_SIZE_H(vsize) | ROT_SET_BUF_SIZE_W(hsize);
	rot_write(val, ROT_SRC_BUF_SIZE);

	/* Set crop image position configuration */
	val = ROT_CROP_POS_Y(pos->y) | ROT_CROP_POS_X(pos->x);
	rot_write(val, ROT_SRC_CROP_POS);
	val = ROT_SRC_CROP_SIZE_H(pos->h) | ROT_SRC_CROP_SIZE_W(pos->w);
	rot_write(val, ROT_SRC_CROP_SIZE);

	return 0;
}

static int rotator_src_set_addr(struct device *dev,
		struct drm_exynos_ipp_buf_info *buf_info,
		u32 buf_id, enum drm_exynos_ipp_buf_type buf_type)
{
	struct rot_context *rot = dev_get_drvdata(dev);
	dma_addr_t addr[EXYNOS_DRM_PLANAR_MAX];
	u32 val, fmt, hsize, vsize;
	int i;

	/* Set current buf_id */
	rot->cur_buf_id[EXYNOS_DRM_OPS_SRC] = buf_id;

	switch (buf_type) {
	case IPP_BUF_ENQUEUE:
		/* Set address configuration */
		for_each_ipp_planar(i)
			addr[i] = buf_info->base[i];

		/* Get format */
		fmt = rotator_reg_get_fmt(rot);
		if (!rotator_check_reg_fmt(fmt)) {
			DRM_ERROR("invalid format.\n");
			return -EINVAL;
		}

		/* Re-set cb planar for NV12 format */
		if ((fmt == ROT_CONTROL_FMT_YCBCR420_2P) &&
		    !addr[EXYNOS_DRM_PLANAR_CB]) {

			val = rot_read(ROT_SRC_BUF_SIZE);
			hsize = ROT_GET_BUF_SIZE_W(val);
			vsize = ROT_GET_BUF_SIZE_H(val);

			/* Set cb planar */
			addr[EXYNOS_DRM_PLANAR_CB] =
				addr[EXYNOS_DRM_PLANAR_Y] + hsize * vsize;
		}

		for_each_ipp_planar(i)
			rot_write(addr[i], ROT_SRC_BUF_ADDR(i));
		break;
	case IPP_BUF_DEQUEUE:
		for_each_ipp_planar(i)
			rot_write(0x0, ROT_SRC_BUF_ADDR(i));
		break;
	default:
		/* Nothing to do */
		break;
	}

	return 0;
}

static int rotator_dst_set_transf(struct device *dev,
		enum drm_exynos_degree degree,
		enum drm_exynos_flip flip, bool *swap)
{
	struct rot_context *rot = dev_get_drvdata(dev);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	u32 val;

	/* Set transform configuration */
	val = rot_read(ROT_CONTROL);
	val &= ~ROT_CONTROL_FLIP_MASK;

<<<<<<< HEAD
	if (rotation & DRM_MODE_REFLECT_X)
		val |= ROT_CONTROL_FLIP_VERTICAL;
	if (rotation & DRM_MODE_REFLECT_Y)
		val |= ROT_CONTROL_FLIP_HORIZONTAL;

	val &= ~ROT_CONTROL_ROT_MASK;

	if (rotation & DRM_MODE_ROTATE_90)
		val |= ROT_CONTROL_ROT_90;
	else if (rotation & DRM_MODE_ROTATE_180)
		val |= ROT_CONTROL_ROT_180;
	else if (rotation & DRM_MODE_ROTATE_270)
		val |= ROT_CONTROL_ROT_270;

	rot_write(val, ROT_CONTROL);
}

static void rotator_dst_set_buf(struct rot_context *rot,
				struct exynos_drm_ipp_buffer *buf)
{
	u32 val;

	/* Set buffer size configuration */
	val = ROT_SET_BUF_SIZE_H(buf->buf.height) |
	      ROT_SET_BUF_SIZE_W(buf->buf.pitch[0] / buf->format->cpp[0]);
	rot_write(val, ROT_DST_BUF_SIZE);

	/* Set crop image position configuration */
	val = ROT_CROP_POS_Y(buf->rect.y) | ROT_CROP_POS_X(buf->rect.x);
	rot_write(val, ROT_DST_CROP_POS);

	/* Set buffer DMA address */
	rot_write(buf->dma_addr[0], ROT_DST_BUF_ADDR(0));
	rot_write(buf->dma_addr[1], ROT_DST_BUF_ADDR(1));
}

static void rotator_start(struct rot_context *rot)
{
	u32 val;

=======
	switch (flip) {
	case EXYNOS_DRM_FLIP_VERTICAL:
		val |= ROT_CONTROL_FLIP_VERTICAL;
		break;
	case EXYNOS_DRM_FLIP_HORIZONTAL:
		val |= ROT_CONTROL_FLIP_HORIZONTAL;
		break;
	default:
		/* Flip None */
		break;
	}

	val &= ~ROT_CONTROL_ROT_MASK;

	switch (degree) {
	case EXYNOS_DRM_DEGREE_90:
		val |= ROT_CONTROL_ROT_90;
		break;
	case EXYNOS_DRM_DEGREE_180:
		val |= ROT_CONTROL_ROT_180;
		break;
	case EXYNOS_DRM_DEGREE_270:
		val |= ROT_CONTROL_ROT_270;
		break;
	default:
		/* Rotation 0 Degree */
		break;
	}

	rot_write(val, ROT_CONTROL);

	/* Check degree for setting buffer size swap */
	if ((degree == EXYNOS_DRM_DEGREE_90) ||
	    (degree == EXYNOS_DRM_DEGREE_270))
		*swap = true;
	else
		*swap = false;

	return 0;
}

static int rotator_dst_set_size(struct device *dev, int swap,
		struct drm_exynos_pos *pos,
		struct drm_exynos_sz *sz)
{
	struct rot_context *rot = dev_get_drvdata(dev);
	u32 val, fmt, hsize, vsize;

	/* Get format */
	fmt = rotator_reg_get_fmt(rot);
	if (!rotator_check_reg_fmt(fmt)) {
		DRM_ERROR("invalid format.\n");
		return -EINVAL;
	}

	/* Align buffer size */
	hsize = sz->hsize;
	vsize = sz->vsize;
	rotator_align_size(rot, fmt, &hsize, &vsize);

	/* Set buffer size configuration */
	val = ROT_SET_BUF_SIZE_H(vsize) | ROT_SET_BUF_SIZE_W(hsize);
	rot_write(val, ROT_DST_BUF_SIZE);

	/* Set crop image position configuration */
	val = ROT_CROP_POS_Y(pos->y) | ROT_CROP_POS_X(pos->x);
	rot_write(val, ROT_DST_CROP_POS);

	return 0;
}

static int rotator_dst_set_addr(struct device *dev,
		struct drm_exynos_ipp_buf_info *buf_info,
		u32 buf_id, enum drm_exynos_ipp_buf_type buf_type)
{
	struct rot_context *rot = dev_get_drvdata(dev);
	dma_addr_t addr[EXYNOS_DRM_PLANAR_MAX];
	u32 val, fmt, hsize, vsize;
	int i;

	/* Set current buf_id */
	rot->cur_buf_id[EXYNOS_DRM_OPS_DST] = buf_id;

	switch (buf_type) {
	case IPP_BUF_ENQUEUE:
		/* Set address configuration */
		for_each_ipp_planar(i)
			addr[i] = buf_info->base[i];

		/* Get format */
		fmt = rotator_reg_get_fmt(rot);
		if (!rotator_check_reg_fmt(fmt)) {
			DRM_ERROR("invalid format.\n");
			return -EINVAL;
		}

		/* Re-set cb planar for NV12 format */
		if ((fmt == ROT_CONTROL_FMT_YCBCR420_2P) &&
		    !addr[EXYNOS_DRM_PLANAR_CB]) {
			/* Get buf size */
			val = rot_read(ROT_DST_BUF_SIZE);

			hsize = ROT_GET_BUF_SIZE_W(val);
			vsize = ROT_GET_BUF_SIZE_H(val);

			/* Set cb planar */
			addr[EXYNOS_DRM_PLANAR_CB] =
				addr[EXYNOS_DRM_PLANAR_Y] + hsize * vsize;
		}

		for_each_ipp_planar(i)
			rot_write(addr[i], ROT_DST_BUF_ADDR(i));
		break;
	case IPP_BUF_DEQUEUE:
		for_each_ipp_planar(i)
			rot_write(0x0, ROT_DST_BUF_ADDR(i));
		break;
	default:
		/* Nothing to do */
		break;
	}

	return 0;
}

static struct exynos_drm_ipp_ops rot_src_ops = {
	.set_fmt	=	rotator_src_set_fmt,
	.set_size	=	rotator_src_set_size,
	.set_addr	=	rotator_src_set_addr,
};

static struct exynos_drm_ipp_ops rot_dst_ops = {
	.set_transf	=	rotator_dst_set_transf,
	.set_size	=	rotator_dst_set_size,
	.set_addr	=	rotator_dst_set_addr,
};

static int rotator_init_prop_list(struct exynos_drm_ippdrv *ippdrv)
{
	struct drm_exynos_ipp_prop_list *prop_list = &ippdrv->prop_list;

	prop_list->version = 1;
	prop_list->flip = (1 << EXYNOS_DRM_FLIP_VERTICAL) |
				(1 << EXYNOS_DRM_FLIP_HORIZONTAL);
	prop_list->degree = (1 << EXYNOS_DRM_DEGREE_0) |
				(1 << EXYNOS_DRM_DEGREE_90) |
				(1 << EXYNOS_DRM_DEGREE_180) |
				(1 << EXYNOS_DRM_DEGREE_270);
	prop_list->csc = 0;
	prop_list->crop = 0;
	prop_list->scale = 0;

	return 0;
}

static inline bool rotator_check_drm_fmt(u32 fmt)
{
	switch (fmt) {
	case DRM_FORMAT_XRGB8888:
	case DRM_FORMAT_NV12:
		return true;
	default:
		DRM_DEBUG_KMS("not support format\n");
		return false;
	}
}

static inline bool rotator_check_drm_flip(enum drm_exynos_flip flip)
{
	switch (flip) {
	case EXYNOS_DRM_FLIP_NONE:
	case EXYNOS_DRM_FLIP_VERTICAL:
	case EXYNOS_DRM_FLIP_HORIZONTAL:
	case EXYNOS_DRM_FLIP_BOTH:
		return true;
	default:
		DRM_DEBUG_KMS("invalid flip\n");
		return false;
	}
}

static int rotator_ippdrv_check_property(struct device *dev,
		struct drm_exynos_ipp_property *property)
{
	struct drm_exynos_ipp_config *src_config =
					&property->config[EXYNOS_DRM_OPS_SRC];
	struct drm_exynos_ipp_config *dst_config =
					&property->config[EXYNOS_DRM_OPS_DST];
	struct drm_exynos_pos *src_pos = &src_config->pos;
	struct drm_exynos_pos *dst_pos = &dst_config->pos;
	struct drm_exynos_sz *src_sz = &src_config->sz;
	struct drm_exynos_sz *dst_sz = &dst_config->sz;
	bool swap = false;

	/* Check format configuration */
	if (src_config->fmt != dst_config->fmt) {
		DRM_DEBUG_KMS("not support csc feature\n");
		return -EINVAL;
	}

	if (!rotator_check_drm_fmt(dst_config->fmt)) {
		DRM_DEBUG_KMS("invalid format\n");
		return -EINVAL;
	}

	/* Check transform configuration */
	if (src_config->degree != EXYNOS_DRM_DEGREE_0) {
		DRM_DEBUG_KMS("not support source-side rotation\n");
		return -EINVAL;
	}

	switch (dst_config->degree) {
	case EXYNOS_DRM_DEGREE_90:
	case EXYNOS_DRM_DEGREE_270:
		swap = true;
	case EXYNOS_DRM_DEGREE_0:
	case EXYNOS_DRM_DEGREE_180:
		/* No problem */
		break;
	default:
		DRM_DEBUG_KMS("invalid degree\n");
		return -EINVAL;
	}

	if (src_config->flip != EXYNOS_DRM_FLIP_NONE) {
		DRM_DEBUG_KMS("not support source-side flip\n");
		return -EINVAL;
	}

	if (!rotator_check_drm_flip(dst_config->flip)) {
		DRM_DEBUG_KMS("invalid flip\n");
		return -EINVAL;
	}

	/* Check size configuration */
	if ((src_pos->x + src_pos->w > src_sz->hsize) ||
		(src_pos->y + src_pos->h > src_sz->vsize)) {
		DRM_DEBUG_KMS("out of source buffer bound\n");
		return -EINVAL;
	}

	if (swap) {
		if ((dst_pos->x + dst_pos->h > dst_sz->vsize) ||
			(dst_pos->y + dst_pos->w > dst_sz->hsize)) {
			DRM_DEBUG_KMS("out of destination buffer bound\n");
			return -EINVAL;
		}

		if ((src_pos->w != dst_pos->h) || (src_pos->h != dst_pos->w)) {
			DRM_DEBUG_KMS("not support scale feature\n");
			return -EINVAL;
		}
	} else {
		if ((dst_pos->x + dst_pos->w > dst_sz->hsize) ||
			(dst_pos->y + dst_pos->h > dst_sz->vsize)) {
			DRM_DEBUG_KMS("out of destination buffer bound\n");
			return -EINVAL;
		}

		if ((src_pos->w != dst_pos->w) || (src_pos->h != dst_pos->h)) {
			DRM_DEBUG_KMS("not support scale feature\n");
			return -EINVAL;
		}
	}

	return 0;
}

static int rotator_ippdrv_start(struct device *dev, enum drm_exynos_ipp_cmd cmd)
{
	struct rot_context *rot = dev_get_drvdata(dev);
	u32 val;

	if (rot->suspended) {
		DRM_ERROR("suspended state\n");
		return -EPERM;
	}

	if (cmd != IPP_CMD_M2M) {
		DRM_ERROR("not support cmd: %d\n", cmd);
		return -EINVAL;
	}

>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	/* Set interrupt enable */
	rotator_reg_set_irq(rot, true);

	val = rot_read(ROT_CONTROL);
	val |= ROT_CONTROL_START;
<<<<<<< HEAD
	rot_write(val, ROT_CONTROL);
}

static int rotator_commit(struct exynos_drm_ipp *ipp,
			  struct exynos_drm_ipp_task *task)
{
	struct rot_context *rot =
			container_of(ipp, struct rot_context, ipp);

	pm_runtime_get_sync(rot->dev);
	rot->task = task;

	rotator_src_set_fmt(rot, task->src.buf.fourcc);
	rotator_src_set_buf(rot, &task->src);
	rotator_dst_set_transf(rot, task->transform.rotation);
	rotator_dst_set_buf(rot, &task->dst);
	rotator_start(rot);
=======

	rot_write(val, ROT_CONTROL);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	return 0;
}

<<<<<<< HEAD
static const struct exynos_drm_ipp_funcs ipp_funcs = {
	.commit = rotator_commit,
};

static int rotator_bind(struct device *dev, struct device *master, void *data)
{
	struct rot_context *rot = dev_get_drvdata(dev);
	struct drm_device *drm_dev = data;
	struct exynos_drm_ipp *ipp = &rot->ipp;

	rot->drm_dev = drm_dev;
	drm_iommu_attach_device(drm_dev, dev);

	exynos_drm_ipp_register(drm_dev, ipp, &ipp_funcs,
			   DRM_EXYNOS_IPP_CAP_CROP | DRM_EXYNOS_IPP_CAP_ROTATE,
			   rot->formats, rot->num_formats, "rotator");

	dev_info(dev, "The exynos rotator has been probed successfully\n");

	return 0;
}

static void rotator_unbind(struct device *dev, struct device *master,
			void *data)
{
	struct rot_context *rot = dev_get_drvdata(dev);
	struct drm_device *drm_dev = data;
	struct exynos_drm_ipp *ipp = &rot->ipp;

	exynos_drm_ipp_unregister(drm_dev, ipp);
	drm_iommu_detach_device(rot->drm_dev, rot->dev);
}

static const struct component_ops rotator_component_ops = {
	.bind	= rotator_bind,
	.unbind = rotator_unbind,
};

static int rotator_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct resource	*regs_res;
	struct rot_context *rot;
	const struct rot_variant *variant;
	int irq;
	int ret;

=======
static struct rot_limit_table rot_limit_tbl_4210 = {
	.ycbcr420_2p = {
		.min_w = 32,
		.min_h = 32,
		.max_w = SZ_64K,
		.max_h = SZ_64K,
		.align = 3,
	},
	.rgb888 = {
		.min_w = 8,
		.min_h = 8,
		.max_w = SZ_16K,
		.max_h = SZ_16K,
		.align = 2,
	},
};

static struct rot_limit_table rot_limit_tbl_4x12 = {
	.ycbcr420_2p = {
		.min_w = 32,
		.min_h = 32,
		.max_w = SZ_32K,
		.max_h = SZ_32K,
		.align = 3,
	},
	.rgb888 = {
		.min_w = 8,
		.min_h = 8,
		.max_w = SZ_8K,
		.max_h = SZ_8K,
		.align = 2,
	},
};

static struct rot_limit_table rot_limit_tbl_5250 = {
	.ycbcr420_2p = {
		.min_w = 32,
		.min_h = 32,
		.max_w = SZ_32K,
		.max_h = SZ_32K,
		.align = 3,
	},
	.rgb888 = {
		.min_w = 8,
		.min_h = 8,
		.max_w = SZ_8K,
		.max_h = SZ_8K,
		.align = 1,
	},
};

static const struct of_device_id exynos_rotator_match[] = {
	{
		.compatible = "samsung,exynos4210-rotator",
		.data = &rot_limit_tbl_4210,
	},
	{
		.compatible = "samsung,exynos4212-rotator",
		.data = &rot_limit_tbl_4x12,
	},
	{
		.compatible = "samsung,exynos5250-rotator",
		.data = &rot_limit_tbl_5250,
	},
	{},
};
MODULE_DEVICE_TABLE(of, exynos_rotator_match);

static int rotator_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct rot_context *rot;
	struct exynos_drm_ippdrv *ippdrv;
	int ret;

	if (!dev->of_node) {
		dev_err(dev, "cannot find of_node.\n");
		return -ENODEV;
	}

>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	rot = devm_kzalloc(dev, sizeof(*rot), GFP_KERNEL);
	if (!rot)
		return -ENOMEM;

<<<<<<< HEAD
	variant = of_device_get_match_data(dev);
	rot->formats = variant->formats;
	rot->num_formats = variant->num_formats;
	rot->dev = dev;
	regs_res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	rot->regs = devm_ioremap_resource(dev, regs_res);
	if (IS_ERR(rot->regs))
		return PTR_ERR(rot->regs);

	irq = platform_get_irq(pdev, 0);
	if (irq < 0) {
		dev_err(dev, "failed to get irq\n");
		return irq;
	}

	ret = devm_request_irq(dev, irq, rotator_irq_handler, 0, dev_name(dev),
			       rot);
=======
	rot->limit_tbl = (struct rot_limit_table *)
				of_device_get_match_data(dev);
	rot->regs_res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	rot->regs = devm_ioremap_resource(dev, rot->regs_res);
	if (IS_ERR(rot->regs))
		return PTR_ERR(rot->regs);

	rot->irq = platform_get_irq(pdev, 0);
	if (rot->irq < 0) {
		dev_err(dev, "failed to get irq\n");
		return rot->irq;
	}

	ret = devm_request_threaded_irq(dev, rot->irq, NULL,
			rotator_irq_handler, IRQF_ONESHOT, "drm_rotator", rot);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	if (ret < 0) {
		dev_err(dev, "failed to request irq\n");
		return ret;
	}

	rot->clock = devm_clk_get(dev, "rotator");
	if (IS_ERR(rot->clock)) {
		dev_err(dev, "failed to get clock\n");
		return PTR_ERR(rot->clock);
	}

<<<<<<< HEAD
	pm_runtime_use_autosuspend(dev);
	pm_runtime_set_autosuspend_delay(dev, ROTATOR_AUTOSUSPEND_DELAY);
	pm_runtime_enable(dev);
	platform_set_drvdata(pdev, rot);

	ret = component_add(dev, &rotator_component_ops);
	if (ret)
		goto err_component;

	return 0;

err_component:
	pm_runtime_dont_use_autosuspend(dev);
=======
	pm_runtime_enable(dev);

	ippdrv = &rot->ippdrv;
	ippdrv->dev = dev;
	ippdrv->ops[EXYNOS_DRM_OPS_SRC] = &rot_src_ops;
	ippdrv->ops[EXYNOS_DRM_OPS_DST] = &rot_dst_ops;
	ippdrv->check_property = rotator_ippdrv_check_property;
	ippdrv->start = rotator_ippdrv_start;
	ret = rotator_init_prop_list(ippdrv);
	if (ret < 0) {
		dev_err(dev, "failed to init property list.\n");
		goto err_ippdrv_register;
	}

	DRM_DEBUG_KMS("ippdrv[%pK]\n", ippdrv);

	platform_set_drvdata(pdev, rot);

	ret = exynos_drm_ippdrv_register(ippdrv);
	if (ret < 0) {
		dev_err(dev, "failed to register drm rotator device\n");
		goto err_ippdrv_register;
	}

	dev_info(dev, "The exynos rotator is probed successfully\n");

	return 0;

err_ippdrv_register:
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	pm_runtime_disable(dev);
	return ret;
}

static int rotator_remove(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
<<<<<<< HEAD

	component_del(dev, &rotator_component_ops);
	pm_runtime_dont_use_autosuspend(dev);
=======
	struct rot_context *rot = dev_get_drvdata(dev);
	struct exynos_drm_ippdrv *ippdrv = &rot->ippdrv;

	exynos_drm_ippdrv_unregister(ippdrv);

>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	pm_runtime_disable(dev);

	return 0;
}

#ifdef CONFIG_PM
<<<<<<< HEAD
=======
static int rotator_clk_crtl(struct rot_context *rot, bool enable)
{
	if (enable) {
		clk_prepare_enable(rot->clock);
		rot->suspended = false;
	} else {
		clk_disable_unprepare(rot->clock);
		rot->suspended = true;
	}

	return 0;
}

>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
static int rotator_runtime_suspend(struct device *dev)
{
	struct rot_context *rot = dev_get_drvdata(dev);

<<<<<<< HEAD
	clk_disable_unprepare(rot->clock);
	return 0;
=======
	return  rotator_clk_crtl(rot, false);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
}

static int rotator_runtime_resume(struct device *dev)
{
	struct rot_context *rot = dev_get_drvdata(dev);

<<<<<<< HEAD
	return clk_prepare_enable(rot->clock);
}
#endif

static const struct drm_exynos_ipp_limit rotator_4210_rbg888_limits[] = {
	{ IPP_SIZE_LIMIT(BUFFER, .h = { 8, SZ_16K }, .v = { 8, SZ_16K }) },
	{ IPP_SIZE_LIMIT(AREA, .h.align = 4, .v.align = 4) },
};

static const struct drm_exynos_ipp_limit rotator_4412_rbg888_limits[] = {
	{ IPP_SIZE_LIMIT(BUFFER, .h = { 8, SZ_8K }, .v = { 8, SZ_8K }) },
	{ IPP_SIZE_LIMIT(AREA, .h.align = 4, .v.align = 4) },
};

static const struct drm_exynos_ipp_limit rotator_5250_rbg888_limits[] = {
	{ IPP_SIZE_LIMIT(BUFFER, .h = { 8, SZ_8K }, .v = { 8, SZ_8K }) },
	{ IPP_SIZE_LIMIT(AREA, .h.align = 2, .v.align = 2) },
};

static const struct drm_exynos_ipp_limit rotator_4210_yuv_limits[] = {
	{ IPP_SIZE_LIMIT(BUFFER, .h = { 32, SZ_64K }, .v = { 32, SZ_64K }) },
	{ IPP_SIZE_LIMIT(AREA, .h.align = 8, .v.align = 8) },
};

static const struct drm_exynos_ipp_limit rotator_4412_yuv_limits[] = {
	{ IPP_SIZE_LIMIT(BUFFER, .h = { 32, SZ_32K }, .v = { 32, SZ_32K }) },
	{ IPP_SIZE_LIMIT(AREA, .h.align = 8, .v.align = 8) },
};

static const struct exynos_drm_ipp_formats rotator_4210_formats[] = {
	{ IPP_SRCDST_FORMAT(XRGB8888, rotator_4210_rbg888_limits) },
	{ IPP_SRCDST_FORMAT(NV12, rotator_4210_yuv_limits) },
};

static const struct exynos_drm_ipp_formats rotator_4412_formats[] = {
	{ IPP_SRCDST_FORMAT(XRGB8888, rotator_4412_rbg888_limits) },
	{ IPP_SRCDST_FORMAT(NV12, rotator_4412_yuv_limits) },
};

static const struct exynos_drm_ipp_formats rotator_5250_formats[] = {
	{ IPP_SRCDST_FORMAT(XRGB8888, rotator_5250_rbg888_limits) },
	{ IPP_SRCDST_FORMAT(NV12, rotator_4412_yuv_limits) },
};

static const struct rot_variant rotator_4210_data = {
	.formats = rotator_4210_formats,
	.num_formats = ARRAY_SIZE(rotator_4210_formats),
};

static const struct rot_variant rotator_4412_data = {
	.formats = rotator_4412_formats,
	.num_formats = ARRAY_SIZE(rotator_4412_formats),
};

static const struct rot_variant rotator_5250_data = {
	.formats = rotator_5250_formats,
	.num_formats = ARRAY_SIZE(rotator_5250_formats),
};

static const struct of_device_id exynos_rotator_match[] = {
	{
		.compatible = "samsung,exynos4210-rotator",
		.data = &rotator_4210_data,
	}, {
		.compatible = "samsung,exynos4212-rotator",
		.data = &rotator_4412_data,
	}, {
		.compatible = "samsung,exynos5250-rotator",
		.data = &rotator_5250_data,
	}, {
	},
};
MODULE_DEVICE_TABLE(of, exynos_rotator_match);

=======
	return  rotator_clk_crtl(rot, true);
}
#endif

>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
static const struct dev_pm_ops rotator_pm_ops = {
	SET_SYSTEM_SLEEP_PM_OPS(pm_runtime_force_suspend,
				pm_runtime_force_resume)
	SET_RUNTIME_PM_OPS(rotator_runtime_suspend, rotator_runtime_resume,
									NULL)
};

struct platform_driver rotator_driver = {
	.probe		= rotator_probe,
	.remove		= rotator_remove,
	.driver		= {
<<<<<<< HEAD
		.name	= "exynos-rotator",
=======
		.name	= "exynos-rot",
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
		.owner	= THIS_MODULE,
		.pm	= &rotator_pm_ops,
		.of_match_table = exynos_rotator_match,
	},
};
