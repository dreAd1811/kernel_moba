/*
<<<<<<< HEAD
 * Copyright (C) 2017 Samsung Electronics Co.Ltd
 * Authors:
 *	Marek Szyprowski <m.szyprowski@samsung.com>
 *
 * Exynos DRM Image Post Processing (IPP) related functions
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 */


#include <drm/drmP.h>
#include <drm/drm_mode.h>
#include <uapi/drm/exynos_drm.h>

#include "exynos_drm_drv.h"
#include "exynos_drm_gem.h"
#include "exynos_drm_ipp.h"

static int num_ipp;
static LIST_HEAD(ipp_list);

/**
 * exynos_drm_ipp_register - Register a new picture processor hardware module
 * @dev: DRM device
 * @ipp: ipp module to init
 * @funcs: callbacks for the new ipp object
 * @caps: bitmask of ipp capabilities (%DRM_EXYNOS_IPP_CAP_*)
 * @formats: array of supported formats
 * @num_formats: size of the supported formats array
 * @name: name (for debugging purposes)
 *
 * Initializes a ipp module.
 *
 * Returns:
 * Zero on success, error code on failure.
 */
int exynos_drm_ipp_register(struct drm_device *dev, struct exynos_drm_ipp *ipp,
		const struct exynos_drm_ipp_funcs *funcs, unsigned int caps,
		const struct exynos_drm_ipp_formats *formats,
		unsigned int num_formats, const char *name)
{
	WARN_ON(!ipp);
	WARN_ON(!funcs);
	WARN_ON(!formats);
	WARN_ON(!num_formats);

	spin_lock_init(&ipp->lock);
	INIT_LIST_HEAD(&ipp->todo_list);
	init_waitqueue_head(&ipp->done_wq);
	ipp->dev = dev;
	ipp->funcs = funcs;
	ipp->capabilities = caps;
	ipp->name = name;
	ipp->formats = formats;
	ipp->num_formats = num_formats;

	/* ipp_list modification is serialized by component framework */
	list_add_tail(&ipp->head, &ipp_list);
	ipp->id = num_ipp++;

	DRM_DEBUG_DRIVER("Registered ipp %d\n", ipp->id);

	return 0;
}

/**
 * exynos_drm_ipp_unregister - Unregister the picture processor module
 * @dev: DRM device
 * @ipp: ipp module
 */
void exynos_drm_ipp_unregister(struct drm_device *dev,
			       struct exynos_drm_ipp *ipp)
{
	WARN_ON(ipp->task);
	WARN_ON(!list_empty(&ipp->todo_list));
	list_del(&ipp->head);
}

/**
 * exynos_drm_ipp_ioctl_get_res_ioctl - enumerate all ipp modules
 * @dev: DRM device
 * @data: ioctl data
 * @file_priv: DRM file info
 *
 * Construct a list of ipp ids.
 *
 * Called by the user via ioctl.
 *
 * Returns:
 * Zero on success, negative errno on failure.
 */
int exynos_drm_ipp_get_res_ioctl(struct drm_device *dev, void *data,
				 struct drm_file *file_priv)
{
	struct drm_exynos_ioctl_ipp_get_res *resp = data;
	struct exynos_drm_ipp *ipp;
	uint32_t __user *ipp_ptr = (uint32_t __user *)
						(unsigned long)resp->ipp_id_ptr;
	unsigned int count = num_ipp, copied = 0;

	/*
	 * This ioctl is called twice, once to determine how much space is
	 * needed, and the 2nd time to fill it.
	 */
	if (count && resp->count_ipps >= count) {
		list_for_each_entry(ipp, &ipp_list, head) {
			if (put_user(ipp->id, ipp_ptr + copied))
				return -EFAULT;
			copied++;
		}
	}
	resp->count_ipps = count;

	return 0;
}

static inline struct exynos_drm_ipp *__ipp_get(uint32_t id)
{
	struct exynos_drm_ipp *ipp;

	list_for_each_entry(ipp, &ipp_list, head)
		if (ipp->id == id)
			return ipp;
	return NULL;
}

/**
 * exynos_drm_ipp_ioctl_get_caps - get ipp module capabilities and formats
 * @dev: DRM device
 * @data: ioctl data
 * @file_priv: DRM file info
 *
 * Construct a structure describing ipp module capabilities.
 *
 * Called by the user via ioctl.
 *
 * Returns:
 * Zero on success, negative errno on failure.
 */
int exynos_drm_ipp_get_caps_ioctl(struct drm_device *dev, void *data,
				  struct drm_file *file_priv)
{
	struct drm_exynos_ioctl_ipp_get_caps *resp = data;
	void __user *ptr = (void __user *)(unsigned long)resp->formats_ptr;
	struct exynos_drm_ipp *ipp;
	int i;

	ipp = __ipp_get(resp->ipp_id);
	if (!ipp)
		return -ENOENT;

	resp->ipp_id = ipp->id;
	resp->capabilities = ipp->capabilities;

	/*
	 * This ioctl is called twice, once to determine how much space is
	 * needed, and the 2nd time to fill it.
	 */
	if (resp->formats_count >= ipp->num_formats) {
		for (i = 0; i < ipp->num_formats; i++) {
			struct drm_exynos_ipp_format tmp = {
				.fourcc = ipp->formats[i].fourcc,
				.type = ipp->formats[i].type,
				.modifier = ipp->formats[i].modifier,
			};

			if (copy_to_user(ptr, &tmp, sizeof(tmp)))
				return -EFAULT;
			ptr += sizeof(tmp);
		}
	}
	resp->formats_count = ipp->num_formats;

	return 0;
}

static inline const struct exynos_drm_ipp_formats *__ipp_format_get(
				struct exynos_drm_ipp *ipp, uint32_t fourcc,
				uint64_t mod, unsigned int type)
{
	int i;

	for (i = 0; i < ipp->num_formats; i++) {
		if ((ipp->formats[i].type & type) &&
		    ipp->formats[i].fourcc == fourcc &&
		    ipp->formats[i].modifier == mod)
			return &ipp->formats[i];
	}
	return NULL;
}

/**
 * exynos_drm_ipp_get_limits_ioctl - get ipp module limits
 * @dev: DRM device
 * @data: ioctl data
 * @file_priv: DRM file info
 *
 * Construct a structure describing ipp module limitations for provided
 * picture format.
 *
 * Called by the user via ioctl.
 *
 * Returns:
 * Zero on success, negative errno on failure.
 */
int exynos_drm_ipp_get_limits_ioctl(struct drm_device *dev, void *data,
				    struct drm_file *file_priv)
{
	struct drm_exynos_ioctl_ipp_get_limits *resp = data;
	void __user *ptr = (void __user *)(unsigned long)resp->limits_ptr;
	const struct exynos_drm_ipp_formats *format;
	struct exynos_drm_ipp *ipp;

	if (resp->type != DRM_EXYNOS_IPP_FORMAT_SOURCE &&
	    resp->type != DRM_EXYNOS_IPP_FORMAT_DESTINATION)
		return -EINVAL;

	ipp = __ipp_get(resp->ipp_id);
	if (!ipp)
		return -ENOENT;

	format = __ipp_format_get(ipp, resp->fourcc, resp->modifier,
				  resp->type);
	if (!format)
		return -EINVAL;

	/*
	 * This ioctl is called twice, once to determine how much space is
	 * needed, and the 2nd time to fill it.
	 */
	if (format->num_limits && resp->limits_count >= format->num_limits)
		if (copy_to_user((void __user *)ptr, format->limits,
				 sizeof(*format->limits) * format->num_limits))
			return -EFAULT;
	resp->limits_count = format->num_limits;

	return 0;
}

struct drm_pending_exynos_ipp_event {
	struct drm_pending_event base;
	struct drm_exynos_ipp_event event;
};

static inline struct exynos_drm_ipp_task *
			exynos_drm_ipp_task_alloc(struct exynos_drm_ipp *ipp)
{
	struct exynos_drm_ipp_task *task;

	task = kzalloc(sizeof(*task), GFP_KERNEL);
	if (!task)
		return NULL;

	task->dev = ipp->dev;
	task->ipp = ipp;

	/* some defaults */
	task->src.rect.w = task->dst.rect.w = UINT_MAX;
	task->src.rect.h = task->dst.rect.h = UINT_MAX;
	task->transform.rotation = DRM_MODE_ROTATE_0;

	DRM_DEBUG_DRIVER("Allocated task %pK\n", task);

	return task;
}

static const struct exynos_drm_param_map {
	unsigned int id;
	unsigned int size;
	unsigned int offset;
} exynos_drm_ipp_params_maps[] = {
	{
		DRM_EXYNOS_IPP_TASK_BUFFER | DRM_EXYNOS_IPP_TASK_TYPE_SOURCE,
		sizeof(struct drm_exynos_ipp_task_buffer),
		offsetof(struct exynos_drm_ipp_task, src.buf),
	}, {
		DRM_EXYNOS_IPP_TASK_BUFFER |
			DRM_EXYNOS_IPP_TASK_TYPE_DESTINATION,
		sizeof(struct drm_exynos_ipp_task_buffer),
		offsetof(struct exynos_drm_ipp_task, dst.buf),
	}, {
		DRM_EXYNOS_IPP_TASK_RECTANGLE | DRM_EXYNOS_IPP_TASK_TYPE_SOURCE,
		sizeof(struct drm_exynos_ipp_task_rect),
		offsetof(struct exynos_drm_ipp_task, src.rect),
	}, {
		DRM_EXYNOS_IPP_TASK_RECTANGLE |
			DRM_EXYNOS_IPP_TASK_TYPE_DESTINATION,
		sizeof(struct drm_exynos_ipp_task_rect),
		offsetof(struct exynos_drm_ipp_task, dst.rect),
	}, {
		DRM_EXYNOS_IPP_TASK_TRANSFORM,
		sizeof(struct drm_exynos_ipp_task_transform),
		offsetof(struct exynos_drm_ipp_task, transform),
	}, {
		DRM_EXYNOS_IPP_TASK_ALPHA,
		sizeof(struct drm_exynos_ipp_task_alpha),
		offsetof(struct exynos_drm_ipp_task, alpha),
	},
};

static int exynos_drm_ipp_task_set(struct exynos_drm_ipp_task *task,
				   struct drm_exynos_ioctl_ipp_commit *arg)
{
	const struct exynos_drm_param_map *map = exynos_drm_ipp_params_maps;
	void __user *params = (void __user *)(unsigned long)arg->params_ptr;
	unsigned int size = arg->params_size;
	uint32_t id;
	int i;

	while (size) {
		if (get_user(id, (uint32_t __user *)params))
			return -EFAULT;

		for (i = 0; i < ARRAY_SIZE(exynos_drm_ipp_params_maps); i++)
			if (map[i].id == id)
				break;
		if (i == ARRAY_SIZE(exynos_drm_ipp_params_maps) ||
		    map[i].size > size)
			return -EINVAL;

		if (copy_from_user((void *)task + map[i].offset, params,
				   map[i].size))
			return -EFAULT;

		params += map[i].size;
		size -= map[i].size;
	}

	DRM_DEBUG_DRIVER("Got task %pK configuration from userspace\n", task);
	return 0;
}

static int exynos_drm_ipp_task_setup_buffer(struct exynos_drm_ipp_buffer *buf,
					    struct drm_file *filp)
{
	int ret = 0;
	int i;

	/* get GEM buffers and check their size */
	for (i = 0; i < buf->format->num_planes; i++) {
		unsigned int height = (i == 0) ? buf->buf.height :
			     DIV_ROUND_UP(buf->buf.height, buf->format->vsub);
		unsigned long size = height * buf->buf.pitch[i];
		struct exynos_drm_gem *gem = exynos_drm_gem_get(filp,
							    buf->buf.gem_id[i]);
		if (!gem) {
			ret = -ENOENT;
			goto gem_free;
		}
		buf->exynos_gem[i] = gem;

		if (size + buf->buf.offset[i] > buf->exynos_gem[i]->size) {
			i++;
			ret = -EINVAL;
			goto gem_free;
		}
		buf->dma_addr[i] = buf->exynos_gem[i]->dma_addr +
				   buf->buf.offset[i];
	}

	return 0;
gem_free:
	while (i--) {
		exynos_drm_gem_put(buf->exynos_gem[i]);
		buf->exynos_gem[i] = NULL;
	}
	return ret;
}

static void exynos_drm_ipp_task_release_buf(struct exynos_drm_ipp_buffer *buf)
{
	int i;

	if (!buf->exynos_gem[0])
		return;
	for (i = 0; i < buf->format->num_planes; i++)
		exynos_drm_gem_put(buf->exynos_gem[i]);
}

static void exynos_drm_ipp_task_free(struct exynos_drm_ipp *ipp,
				 struct exynos_drm_ipp_task *task)
{
	DRM_DEBUG_DRIVER("Freeing task %pK\n", task);

	exynos_drm_ipp_task_release_buf(&task->src);
	exynos_drm_ipp_task_release_buf(&task->dst);
	if (task->event)
		drm_event_cancel_free(ipp->dev, &task->event->base);
	kfree(task);
}

struct drm_ipp_limit {
	struct drm_exynos_ipp_limit_val h;
	struct drm_exynos_ipp_limit_val v;
};

enum drm_ipp_size_id {
	IPP_LIMIT_BUFFER, IPP_LIMIT_AREA, IPP_LIMIT_ROTATED, IPP_LIMIT_MAX
};

static const enum drm_exynos_ipp_limit_type limit_id_fallback[IPP_LIMIT_MAX][4] = {
	[IPP_LIMIT_BUFFER]  = { DRM_EXYNOS_IPP_LIMIT_SIZE_BUFFER },
	[IPP_LIMIT_AREA]    = { DRM_EXYNOS_IPP_LIMIT_SIZE_AREA,
				DRM_EXYNOS_IPP_LIMIT_SIZE_BUFFER },
	[IPP_LIMIT_ROTATED] = { DRM_EXYNOS_IPP_LIMIT_SIZE_ROTATED,
				DRM_EXYNOS_IPP_LIMIT_SIZE_AREA,
				DRM_EXYNOS_IPP_LIMIT_SIZE_BUFFER },
};

static inline void __limit_set_val(unsigned int *ptr, unsigned int val)
{
	if (!*ptr)
		*ptr = val;
}

static void __get_size_limit(const struct drm_exynos_ipp_limit *limits,
			     unsigned int num_limits, enum drm_ipp_size_id id,
			     struct drm_ipp_limit *res)
{
	const struct drm_exynos_ipp_limit *l = limits;
	int i = 0;

	memset(res, 0, sizeof(*res));
	for (i = 0; limit_id_fallback[id][i]; i++)
		for (l = limits; l - limits < num_limits; l++) {
			if (((l->type & DRM_EXYNOS_IPP_LIMIT_TYPE_MASK) !=
			      DRM_EXYNOS_IPP_LIMIT_TYPE_SIZE) ||
			    ((l->type & DRM_EXYNOS_IPP_LIMIT_SIZE_MASK) !=
						     limit_id_fallback[id][i]))
				continue;
			__limit_set_val(&res->h.min, l->h.min);
			__limit_set_val(&res->h.max, l->h.max);
			__limit_set_val(&res->h.align, l->h.align);
			__limit_set_val(&res->v.min, l->v.min);
			__limit_set_val(&res->v.max, l->v.max);
			__limit_set_val(&res->v.align, l->v.align);
		}
}

static inline bool __align_check(unsigned int val, unsigned int align)
{
	if (align && (val & (align - 1))) {
		DRM_DEBUG_DRIVER("Value %d exceeds HW limits (align %d)\n",
				 val, align);
		return false;
	}
	return true;
}

static inline bool __size_limit_check(unsigned int val,
				 struct drm_exynos_ipp_limit_val *l)
{
	if ((l->min && val < l->min) || (l->max && val > l->max)) {
		DRM_DEBUG_DRIVER("Value %d exceeds HW limits (min %d, max %d)\n",
				 val, l->min, l->max);
		return false;
	}
	return __align_check(val, l->align);
}

static int exynos_drm_ipp_check_size_limits(struct exynos_drm_ipp_buffer *buf,
	const struct drm_exynos_ipp_limit *limits, unsigned int num_limits,
	bool rotate, bool swap)
{
	enum drm_ipp_size_id id = rotate ? IPP_LIMIT_ROTATED : IPP_LIMIT_AREA;
	struct drm_ipp_limit l;
	struct drm_exynos_ipp_limit_val *lh = &l.h, *lv = &l.v;
	int real_width = buf->buf.pitch[0] / buf->format->cpp[0];

	if (!limits)
		return 0;

	__get_size_limit(limits, num_limits, IPP_LIMIT_BUFFER, &l);
	if (!__size_limit_check(real_width, &l.h) ||
	    !__size_limit_check(buf->buf.height, &l.v))
		return -EINVAL;

	if (swap) {
		lv = &l.h;
		lh = &l.v;
	}
	__get_size_limit(limits, num_limits, id, &l);
	if (!__size_limit_check(buf->rect.w, lh) ||
	    !__align_check(buf->rect.x, lh->align) ||
	    !__size_limit_check(buf->rect.h, lv) ||
	    !__align_check(buf->rect.y, lv->align))
		return -EINVAL;
=======
 * Copyright (C) 2012 Samsung Electronics Co.Ltd
 * Authors:
 *	Eunchul Kim <chulspro.kim@samsung.com>
 *	Jinyoung Jeon <jy0.jeon@samsung.com>
 *	Sangmin Lee <lsmin.lee@samsung.com>
 *
 * This program is free software; you can redistribute  it and/or modify it
 * under  the terms of  the GNU General  Public License as published by the
 * Free Software Foundation;  either version 2 of the  License, or (at your
 * option) any later version.
 *
 */
#include <linux/kernel.h>
#include <linux/platform_device.h>
#include <linux/types.h>
#include <linux/clk.h>
#include <linux/pm_runtime.h>

#include <drm/drmP.h>
#include <drm/exynos_drm.h>
#include "exynos_drm_drv.h"
#include "exynos_drm_gem.h"
#include "exynos_drm_ipp.h"
#include "exynos_drm_iommu.h"

/*
 * IPP stands for Image Post Processing and
 * supports image scaler/rotator and input/output DMA operations.
 * using FIMC, GSC, Rotator, so on.
 * IPP is integration device driver of same attribute h/w
 */

/*
 * TODO
 * 1. expand command control id.
 * 2. integrate	property and config.
 * 3. removed send_event id check routine.
 * 4. compare send_event id if needed.
 * 5. free subdrv_remove notifier callback list if needed.
 * 6. need to check subdrv_open about multi-open.
 * 7. need to power_on implement power and sysmmu ctrl.
 */

#define get_ipp_context(dev)	platform_get_drvdata(to_platform_device(dev))
#define ipp_is_m2m_cmd(c)	(c == IPP_CMD_M2M)

/*
 * A structure of event.
 *
 * @base: base of event.
 * @event: ipp event.
 */
struct drm_exynos_ipp_send_event {
	struct drm_pending_event	base;
	struct drm_exynos_ipp_event	event;
};

/*
 * A structure of memory node.
 *
 * @list: list head to memory queue information.
 * @ops_id: id of operations.
 * @prop_id: id of property.
 * @buf_id: id of buffer.
 * @buf_info: gem objects and dma address, size.
 * @filp: a pointer to drm_file.
 */
struct drm_exynos_ipp_mem_node {
	struct list_head	list;
	enum drm_exynos_ops_id	ops_id;
	u32	prop_id;
	u32	buf_id;
	struct drm_exynos_ipp_buf_info	buf_info;
};

/*
 * A structure of ipp context.
 *
 * @subdrv: prepare initialization using subdrv.
 * @ipp_lock: lock for synchronization of access to ipp_idr.
 * @prop_lock: lock for synchronization of access to prop_idr.
 * @ipp_idr: ipp driver idr.
 * @prop_idr: property idr.
 * @event_workq: event work queue.
 * @cmd_workq: command work queue.
 */
struct ipp_context {
	struct exynos_drm_subdrv	subdrv;
	struct mutex	ipp_lock;
	struct mutex	prop_lock;
	struct idr	ipp_idr;
	struct idr	prop_idr;
	struct workqueue_struct	*event_workq;
	struct workqueue_struct	*cmd_workq;
};

static LIST_HEAD(exynos_drm_ippdrv_list);
static DEFINE_MUTEX(exynos_drm_ippdrv_lock);
static BLOCKING_NOTIFIER_HEAD(exynos_drm_ippnb_list);

int exynos_drm_ippdrv_register(struct exynos_drm_ippdrv *ippdrv)
{
	mutex_lock(&exynos_drm_ippdrv_lock);
	list_add_tail(&ippdrv->drv_list, &exynos_drm_ippdrv_list);
	mutex_unlock(&exynos_drm_ippdrv_lock);

	return 0;
}

int exynos_drm_ippdrv_unregister(struct exynos_drm_ippdrv *ippdrv)
{
	mutex_lock(&exynos_drm_ippdrv_lock);
	list_del(&ippdrv->drv_list);
	mutex_unlock(&exynos_drm_ippdrv_lock);

	return 0;
}

static int ipp_create_id(struct idr *id_idr, struct mutex *lock, void *obj)
{
	int ret;

	mutex_lock(lock);
	ret = idr_alloc(id_idr, obj, 1, 0, GFP_KERNEL);
	mutex_unlock(lock);

	return ret;
}

static void ipp_remove_id(struct idr *id_idr, struct mutex *lock, u32 id)
{
	mutex_lock(lock);
	idr_remove(id_idr, id);
	mutex_unlock(lock);
}

static void *ipp_find_obj(struct idr *id_idr, struct mutex *lock, u32 id)
{
	void *obj;

	mutex_lock(lock);
	obj = idr_find(id_idr, id);
	mutex_unlock(lock);

	return obj;
}

static int ipp_check_driver(struct exynos_drm_ippdrv *ippdrv,
			    struct drm_exynos_ipp_property *property)
{
	if (ippdrv->dedicated || (!ipp_is_m2m_cmd(property->cmd) &&
				  !pm_runtime_suspended(ippdrv->dev)))
		return -EBUSY;

	if (ippdrv->check_property &&
	    ippdrv->check_property(ippdrv->dev, property))
		return -EINVAL;

	return 0;
}

static struct exynos_drm_ippdrv *ipp_find_driver(struct ipp_context *ctx,
		struct drm_exynos_ipp_property *property)
{
	struct exynos_drm_ippdrv *ippdrv;
	u32 ipp_id = property->ipp_id;
	int ret;

	if (ipp_id) {
		ippdrv = ipp_find_obj(&ctx->ipp_idr, &ctx->ipp_lock, ipp_id);
		if (!ippdrv) {
			DRM_DEBUG("ipp%d driver not found\n", ipp_id);
			return ERR_PTR(-ENODEV);
		}

		ret = ipp_check_driver(ippdrv, property);
		if (ret < 0) {
			DRM_DEBUG("ipp%d driver check error %d\n", ipp_id, ret);
			return ERR_PTR(ret);
		}

		return ippdrv;
	} else {
		list_for_each_entry(ippdrv, &exynos_drm_ippdrv_list, drv_list) {
			ret = ipp_check_driver(ippdrv, property);
			if (ret == 0)
				return ippdrv;
		}

		DRM_DEBUG("cannot find driver suitable for given property.\n");
	}

	return ERR_PTR(-ENODEV);
}

static struct exynos_drm_ippdrv *ipp_find_drv_by_handle(u32 prop_id)
{
	struct exynos_drm_ippdrv *ippdrv;
	struct drm_exynos_ipp_cmd_node *c_node;
	int count = 0;

	DRM_DEBUG_KMS("prop_id[%d]\n", prop_id);

	/*
	 * This case is search ipp driver by prop_id handle.
	 * sometimes, ipp subsystem find driver by prop_id.
	 * e.g PAUSE state, queue buf, command control.
	 */
	list_for_each_entry(ippdrv, &exynos_drm_ippdrv_list, drv_list) {
		DRM_DEBUG_KMS("count[%d]ippdrv[%pK]\n", count++, ippdrv);

		mutex_lock(&ippdrv->cmd_lock);
		list_for_each_entry(c_node, &ippdrv->cmd_list, list) {
			if (c_node->property.prop_id == prop_id) {
				mutex_unlock(&ippdrv->cmd_lock);
				return ippdrv;
			}
		}
		mutex_unlock(&ippdrv->cmd_lock);
	}

	return ERR_PTR(-ENODEV);
}

int exynos_drm_ipp_get_property(struct drm_device *drm_dev, void *data,
		struct drm_file *file)
{
	struct drm_exynos_file_private *file_priv = file->driver_priv;
	struct device *dev = file_priv->ipp_dev;
	struct ipp_context *ctx = get_ipp_context(dev);
	struct drm_exynos_ipp_prop_list *prop_list = data;
	struct exynos_drm_ippdrv *ippdrv;
	int count = 0;

	if (!ctx) {
		DRM_ERROR("invalid context.\n");
		return -EINVAL;
	}

	if (!prop_list) {
		DRM_ERROR("invalid property parameter.\n");
		return -EINVAL;
	}

	DRM_DEBUG_KMS("ipp_id[%d]\n", prop_list->ipp_id);

	if (!prop_list->ipp_id) {
		list_for_each_entry(ippdrv, &exynos_drm_ippdrv_list, drv_list)
			count++;

		/*
		 * Supports ippdrv list count for user application.
		 * First step user application getting ippdrv count.
		 * and second step getting ippdrv capability using ipp_id.
		 */
		prop_list->count = count;
	} else {
		/*
		 * Getting ippdrv capability by ipp_id.
		 * some device not supported wb, output interface.
		 * so, user application detect correct ipp driver
		 * using this ioctl.
		 */
		ippdrv = ipp_find_obj(&ctx->ipp_idr, &ctx->ipp_lock,
						prop_list->ipp_id);
		if (!ippdrv) {
			DRM_ERROR("not found ipp%d driver.\n",
					prop_list->ipp_id);
			return -ENODEV;
		}

		*prop_list = ippdrv->prop_list;
	}
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	return 0;
}

<<<<<<< HEAD
static inline bool __scale_limit_check(unsigned int src, unsigned int dst,
				       unsigned int min, unsigned int max)
{
	if ((max && (dst << 16) > src * max) ||
	    (min && (dst << 16) < src * min)) {
		DRM_DEBUG_DRIVER("Scale from %d to %d exceeds HW limits (ratio min %d.%05d, max %d.%05d)\n",
			 src, dst,
			 min >> 16, 100000 * (min & 0xffff) / (1 << 16),
			 max >> 16, 100000 * (max & 0xffff) / (1 << 16));
		return false;
	}
	return true;
}

static int exynos_drm_ipp_check_scale_limits(
				struct drm_exynos_ipp_task_rect *src,
				struct drm_exynos_ipp_task_rect *dst,
				const struct drm_exynos_ipp_limit *limits,
				unsigned int num_limits, bool swap)
{
	const struct drm_exynos_ipp_limit_val *lh, *lv;
	int dw, dh;

	for (; num_limits; limits++, num_limits--)
		if ((limits->type & DRM_EXYNOS_IPP_LIMIT_TYPE_MASK) ==
		    DRM_EXYNOS_IPP_LIMIT_TYPE_SCALE)
			break;
	if (!num_limits)
		return 0;

	lh = (!swap) ? &limits->h : &limits->v;
	lv = (!swap) ? &limits->v : &limits->h;
	dw = (!swap) ? dst->w : dst->h;
	dh = (!swap) ? dst->h : dst->w;

	if (!__scale_limit_check(src->w, dw, lh->min, lh->max) ||
	    !__scale_limit_check(src->h, dh, lv->min, lv->max))
		return -EINVAL;

	return 0;
}

static int exynos_drm_ipp_check_format(struct exynos_drm_ipp_task *task,
				       struct exynos_drm_ipp_buffer *buf,
				       struct exynos_drm_ipp_buffer *src,
				       struct exynos_drm_ipp_buffer *dst,
				       bool rotate, bool swap)
{
	const struct exynos_drm_ipp_formats *fmt;
	int ret, i;

	fmt = __ipp_format_get(task->ipp, buf->buf.fourcc, buf->buf.modifier,
			       buf == src ? DRM_EXYNOS_IPP_FORMAT_SOURCE :
					    DRM_EXYNOS_IPP_FORMAT_DESTINATION);
	if (!fmt) {
		DRM_DEBUG_DRIVER("Task %pK: %s format not supported\n", task,
				 buf == src ? "src" : "dst");
		return -EINVAL;
	}

	/* basic checks */
	if (buf->buf.width == 0 || buf->buf.height == 0)
		return -EINVAL;

	buf->format = drm_format_info(buf->buf.fourcc);
	for (i = 0; i < buf->format->num_planes; i++) {
		unsigned int width = (i == 0) ? buf->buf.width :
			     DIV_ROUND_UP(buf->buf.width, buf->format->hsub);

		if (buf->buf.pitch[i] == 0)
			buf->buf.pitch[i] = width * buf->format->cpp[i];
		if (buf->buf.pitch[i] < width * buf->format->cpp[i])
			return -EINVAL;
		if (!buf->buf.gem_id[i])
			return -ENOENT;
	}

	/* pitch for additional planes must match */
	if (buf->format->num_planes > 2 &&
	    buf->buf.pitch[1] != buf->buf.pitch[2])
		return -EINVAL;

	/* check driver limits */
	ret = exynos_drm_ipp_check_size_limits(buf, fmt->limits,
					       fmt->num_limits,
					       rotate,
					       buf == dst ? swap : false);
	if (ret)
		return ret;
	ret = exynos_drm_ipp_check_scale_limits(&src->rect, &dst->rect,
						fmt->limits,
						fmt->num_limits, swap);
	return ret;
}

static int exynos_drm_ipp_task_check(struct exynos_drm_ipp_task *task)
{
	struct exynos_drm_ipp *ipp = task->ipp;
	struct exynos_drm_ipp_buffer *src = &task->src, *dst = &task->dst;
	unsigned int rotation = task->transform.rotation;
	int ret = 0;
	bool swap = drm_rotation_90_or_270(rotation);
	bool rotate = (rotation != DRM_MODE_ROTATE_0);
	bool scale = false;

	DRM_DEBUG_DRIVER("Checking task %pK\n", task);

	if (src->rect.w == UINT_MAX)
		src->rect.w = src->buf.width;
	if (src->rect.h == UINT_MAX)
		src->rect.h = src->buf.height;
	if (dst->rect.w == UINT_MAX)
		dst->rect.w = dst->buf.width;
	if (dst->rect.h == UINT_MAX)
		dst->rect.h = dst->buf.height;

	if (src->rect.x + src->rect.w > (src->buf.width) ||
	    src->rect.y + src->rect.h > (src->buf.height) ||
	    dst->rect.x + dst->rect.w > (dst->buf.width) ||
	    dst->rect.y + dst->rect.h > (dst->buf.height)) {
		DRM_DEBUG_DRIVER("Task %pK: defined area is outside provided buffers\n",
				 task);
		return -EINVAL;
	}

	if ((!swap && (src->rect.w != dst->rect.w ||
		       src->rect.h != dst->rect.h)) ||
	    (swap && (src->rect.w != dst->rect.h ||
		      src->rect.h != dst->rect.w)))
		scale = true;

	if ((!(ipp->capabilities & DRM_EXYNOS_IPP_CAP_CROP) &&
	     (src->rect.x || src->rect.y || dst->rect.x || dst->rect.y)) ||
	    (!(ipp->capabilities & DRM_EXYNOS_IPP_CAP_ROTATE) && rotate) ||
	    (!(ipp->capabilities & DRM_EXYNOS_IPP_CAP_SCALE) && scale) ||
	    (!(ipp->capabilities & DRM_EXYNOS_IPP_CAP_CONVERT) &&
	     src->buf.fourcc != dst->buf.fourcc)) {
		DRM_DEBUG_DRIVER("Task %pK: hw capabilities exceeded\n", task);
		return -EINVAL;
	}

	ret = exynos_drm_ipp_check_format(task, src, src, dst, rotate, swap);
	if (ret)
		return ret;

	ret = exynos_drm_ipp_check_format(task, dst, src, dst, false, swap);
	if (ret)
		return ret;

	DRM_DEBUG_DRIVER("Task %pK: all checks done.\n", task);

	return ret;
}

static int exynos_drm_ipp_task_setup_buffers(struct exynos_drm_ipp_task *task,
				     struct drm_file *filp)
{
	struct exynos_drm_ipp_buffer *src = &task->src, *dst = &task->dst;
	int ret = 0;

	DRM_DEBUG_DRIVER("Setting buffer for task %pK\n", task);

	ret = exynos_drm_ipp_task_setup_buffer(src, filp);
	if (ret) {
		DRM_DEBUG_DRIVER("Task %pK: src buffer setup failed\n", task);
		return ret;
	}
	ret = exynos_drm_ipp_task_setup_buffer(dst, filp);
	if (ret) {
		DRM_DEBUG_DRIVER("Task %pK: dst buffer setup failed\n", task);
		return ret;
	}

	DRM_DEBUG_DRIVER("Task %pK: buffers prepared.\n", task);

	return ret;
}


static int exynos_drm_ipp_event_create(struct exynos_drm_ipp_task *task,
				 struct drm_file *file_priv, uint64_t user_data)
{
	struct drm_pending_exynos_ipp_event *e = NULL;
	int ret;

=======
static void ipp_print_property(struct drm_exynos_ipp_property *property,
		int idx)
{
	struct drm_exynos_ipp_config *config = &property->config[idx];
	struct drm_exynos_pos *pos = &config->pos;
	struct drm_exynos_sz *sz = &config->sz;

	DRM_DEBUG_KMS("prop_id[%d]ops[%s]fmt[0x%x]\n",
		property->prop_id, idx ? "dst" : "src", config->fmt);

	DRM_DEBUG_KMS("pos[%d %d %d %d]sz[%d %d]f[%d]r[%d]\n",
		pos->x, pos->y, pos->w, pos->h,
		sz->hsize, sz->vsize, config->flip, config->degree);
}

static struct drm_exynos_ipp_cmd_work *ipp_create_cmd_work(void)
{
	struct drm_exynos_ipp_cmd_work *cmd_work;

	cmd_work = kzalloc(sizeof(*cmd_work), GFP_KERNEL);
	if (!cmd_work)
		return ERR_PTR(-ENOMEM);

	INIT_WORK((struct work_struct *)cmd_work, ipp_sched_cmd);

	return cmd_work;
}

static struct drm_exynos_ipp_event_work *ipp_create_event_work(void)
{
	struct drm_exynos_ipp_event_work *event_work;

	event_work = kzalloc(sizeof(*event_work), GFP_KERNEL);
	if (!event_work)
		return ERR_PTR(-ENOMEM);

	INIT_WORK(&event_work->work, ipp_sched_event);

	return event_work;
}

int exynos_drm_ipp_set_property(struct drm_device *drm_dev, void *data,
		struct drm_file *file)
{
	struct drm_exynos_file_private *file_priv = file->driver_priv;
	struct device *dev = file_priv->ipp_dev;
	struct ipp_context *ctx = get_ipp_context(dev);
	struct drm_exynos_ipp_property *property = data;
	struct exynos_drm_ippdrv *ippdrv;
	struct drm_exynos_ipp_cmd_node *c_node;
	u32 prop_id;
	int ret, i;

	if (!ctx) {
		DRM_ERROR("invalid context.\n");
		return -EINVAL;
	}

	if (!property) {
		DRM_ERROR("invalid property parameter.\n");
		return -EINVAL;
	}

	prop_id = property->prop_id;

	/*
	 * This is log print for user application property.
	 * user application set various property.
	 */
	for_each_ipp_ops(i)
		ipp_print_property(property, i);

	/*
	 * In case prop_id is not zero try to set existing property.
	 */
	if (prop_id) {
		c_node = ipp_find_obj(&ctx->prop_idr, &ctx->prop_lock, prop_id);

		if (!c_node || c_node->filp != file) {
			DRM_DEBUG_KMS("prop_id[%d] not found\n", prop_id);
			return -EINVAL;
		}

		if (c_node->state != IPP_STATE_STOP) {
			DRM_DEBUG_KMS("prop_id[%d] not stopped\n", prop_id);
			return -EINVAL;
		}

		c_node->property = *property;

		return 0;
	}

	/* find ipp driver using ipp id */
	ippdrv = ipp_find_driver(ctx, property);
	if (IS_ERR(ippdrv)) {
		DRM_ERROR("failed to get ipp driver.\n");
		return -EINVAL;
	}

	/* allocate command node */
	c_node = kzalloc(sizeof(*c_node), GFP_KERNEL);
	if (!c_node)
		return -ENOMEM;

	ret = ipp_create_id(&ctx->prop_idr, &ctx->prop_lock, c_node);
	if (ret < 0) {
		DRM_ERROR("failed to create id.\n");
		goto err_clear;
	}
	property->prop_id = ret;

	DRM_DEBUG_KMS("created prop_id[%d]cmd[%d]ippdrv[%pK]\n",
		property->prop_id, property->cmd, ippdrv);

	/* stored property information and ippdrv in private data */
	c_node->property = *property;
	c_node->state = IPP_STATE_IDLE;
	c_node->filp = file;

	c_node->start_work = ipp_create_cmd_work();
	if (IS_ERR(c_node->start_work)) {
		DRM_ERROR("failed to create start work.\n");
		ret = PTR_ERR(c_node->start_work);
		goto err_remove_id;
	}

	c_node->stop_work = ipp_create_cmd_work();
	if (IS_ERR(c_node->stop_work)) {
		DRM_ERROR("failed to create stop work.\n");
		ret = PTR_ERR(c_node->stop_work);
		goto err_free_start;
	}

	c_node->event_work = ipp_create_event_work();
	if (IS_ERR(c_node->event_work)) {
		DRM_ERROR("failed to create event work.\n");
		ret = PTR_ERR(c_node->event_work);
		goto err_free_stop;
	}

	mutex_init(&c_node->lock);
	mutex_init(&c_node->mem_lock);
	mutex_init(&c_node->event_lock);

	init_completion(&c_node->start_complete);
	init_completion(&c_node->stop_complete);

	for_each_ipp_ops(i)
		INIT_LIST_HEAD(&c_node->mem_list[i]);

	INIT_LIST_HEAD(&c_node->event_list);
	mutex_lock(&ippdrv->cmd_lock);
	list_add_tail(&c_node->list, &ippdrv->cmd_list);
	mutex_unlock(&ippdrv->cmd_lock);

	/* make dedicated state without m2m */
	if (!ipp_is_m2m_cmd(property->cmd))
		ippdrv->dedicated = true;

	return 0;

err_free_stop:
	kfree(c_node->stop_work);
err_free_start:
	kfree(c_node->start_work);
err_remove_id:
	ipp_remove_id(&ctx->prop_idr, &ctx->prop_lock, property->prop_id);
err_clear:
	kfree(c_node);
	return ret;
}

static int ipp_validate_mem_node(struct drm_device *drm_dev,
				 struct drm_exynos_ipp_mem_node *m_node,
				 struct drm_exynos_ipp_cmd_node *c_node)
{
	struct drm_exynos_ipp_config *ipp_cfg;
	unsigned int num_plane;
	unsigned long size, buf_size = 0, plane_size, img_size = 0;
	unsigned int bpp, width, height;
	int i;

	ipp_cfg = &c_node->property.config[m_node->ops_id];
	num_plane = drm_format_num_planes(ipp_cfg->fmt);

	/**
	 * This is a rather simplified validation of a memory node.
	 * It basically verifies provided gem object handles
	 * and the buffer sizes with respect to current configuration.
	 * This is not the best that can be done
	 * but it seems more than enough
	 */
	for (i = 0; i < num_plane; ++i) {
		width = ipp_cfg->sz.hsize;
		height = ipp_cfg->sz.vsize;
		bpp = drm_format_plane_cpp(ipp_cfg->fmt, i);

		/*
		 * The result of drm_format_plane_cpp() for chroma planes must
		 * be used with drm_format_xxxx_chroma_subsampling() for
		 * correct result.
		 */
		if (i > 0) {
			width /= drm_format_horz_chroma_subsampling(
								ipp_cfg->fmt);
			height /= drm_format_vert_chroma_subsampling(
								ipp_cfg->fmt);
		}
		plane_size = width * height * bpp;
		img_size += plane_size;

		if (m_node->buf_info.handles[i]) {
			size = exynos_drm_gem_get_size(drm_dev,
					m_node->buf_info.handles[i],
					c_node->filp);
			if (plane_size > size) {
				DRM_ERROR(
					"buffer %d is smaller than required\n",
					i);
				return -EINVAL;
			}

			buf_size += size;
		}
	}

	if (buf_size < img_size) {
		DRM_ERROR("size of buffers(%lu) is smaller than image(%lu)\n",
			buf_size, img_size);
		return -EINVAL;
	}

	return 0;
}

static int ipp_put_mem_node(struct drm_device *drm_dev,
		struct drm_exynos_ipp_cmd_node *c_node,
		struct drm_exynos_ipp_mem_node *m_node)
{
	int i;

	DRM_DEBUG_KMS("node[%pK]\n", m_node);

	if (!m_node) {
		DRM_ERROR("invalid dequeue node.\n");
		return -EFAULT;
	}

	DRM_DEBUG_KMS("ops_id[%d]\n", m_node->ops_id);

	/* put gem buffer */
	for_each_ipp_planar(i) {
		unsigned long handle = m_node->buf_info.handles[i];
		if (handle)
			exynos_drm_gem_put_dma_addr(drm_dev, handle,
							c_node->filp);
	}

	list_del(&m_node->list);
	kfree(m_node);

	return 0;
}

static struct drm_exynos_ipp_mem_node
		*ipp_get_mem_node(struct drm_device *drm_dev,
		struct drm_exynos_ipp_cmd_node *c_node,
		struct drm_exynos_ipp_queue_buf *qbuf)
{
	struct drm_exynos_ipp_mem_node *m_node;
	struct drm_exynos_ipp_buf_info *buf_info;
	int i;

	m_node = kzalloc(sizeof(*m_node), GFP_KERNEL);
	if (!m_node)
		return ERR_PTR(-ENOMEM);

	buf_info = &m_node->buf_info;

	/* operations, buffer id */
	m_node->ops_id = qbuf->ops_id;
	m_node->prop_id = qbuf->prop_id;
	m_node->buf_id = qbuf->buf_id;
	INIT_LIST_HEAD(&m_node->list);

	DRM_DEBUG_KMS("m_node[%pK]ops_id[%d]\n", m_node, qbuf->ops_id);
	DRM_DEBUG_KMS("prop_id[%d]buf_id[%d]\n", qbuf->prop_id, m_node->buf_id);

	for_each_ipp_planar(i) {
		DRM_DEBUG_KMS("i[%d]handle[0x%x]\n", i, qbuf->handle[i]);

		/* get dma address by handle */
		if (qbuf->handle[i]) {
			dma_addr_t *addr;

			addr = exynos_drm_gem_get_dma_addr(drm_dev,
					qbuf->handle[i], c_node->filp);
			if (IS_ERR(addr)) {
				DRM_ERROR("failed to get addr.\n");
				ipp_put_mem_node(drm_dev, c_node, m_node);
				return ERR_PTR(-EFAULT);
			}

			buf_info->handles[i] = qbuf->handle[i];
			buf_info->base[i] = *addr;
			DRM_DEBUG_KMS("i[%d]base[%pad]hd[0x%lx]\n", i,
				      &buf_info->base[i], buf_info->handles[i]);
		}
	}

	mutex_lock(&c_node->mem_lock);
	if (ipp_validate_mem_node(drm_dev, m_node, c_node)) {
		ipp_put_mem_node(drm_dev, c_node, m_node);
		mutex_unlock(&c_node->mem_lock);
		return ERR_PTR(-EFAULT);
	}
	list_add_tail(&m_node->list, &c_node->mem_list[qbuf->ops_id]);
	mutex_unlock(&c_node->mem_lock);

	return m_node;
}

static void ipp_clean_mem_nodes(struct drm_device *drm_dev,
			       struct drm_exynos_ipp_cmd_node *c_node, int ops)
{
	struct drm_exynos_ipp_mem_node *m_node, *tm_node;
	struct list_head *head = &c_node->mem_list[ops];

	mutex_lock(&c_node->mem_lock);

	list_for_each_entry_safe(m_node, tm_node, head, list) {
		int ret;

		ret = ipp_put_mem_node(drm_dev, c_node, m_node);
		if (ret)
			DRM_ERROR("failed to put m_node.\n");
	}

	mutex_unlock(&c_node->mem_lock);
}

static int ipp_get_event(struct drm_device *drm_dev,
		struct drm_exynos_ipp_cmd_node *c_node,
		struct drm_exynos_ipp_queue_buf *qbuf)
{
	struct drm_exynos_ipp_send_event *e;
	int ret;

	DRM_DEBUG_KMS("ops_id[%d]buf_id[%d]\n", qbuf->ops_id, qbuf->buf_id);

>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	e = kzalloc(sizeof(*e), GFP_KERNEL);
	if (!e)
		return -ENOMEM;

<<<<<<< HEAD
	e->event.base.type = DRM_EXYNOS_IPP_EVENT;
	e->event.base.length = sizeof(e->event);
	e->event.user_data = user_data;

	ret = drm_event_reserve_init(task->dev, file_priv, &e->base,
				     &e->event.base);
	if (ret)
		goto free;

	task->event = e;
	return 0;
free:
	kfree(e);
	return ret;
}

static void exynos_drm_ipp_event_send(struct exynos_drm_ipp_task *task)
{
	struct timespec64 now;

	ktime_get_ts64(&now);
	task->event->event.tv_sec = now.tv_sec;
	task->event->event.tv_usec = now.tv_nsec / NSEC_PER_USEC;
	task->event->event.sequence = atomic_inc_return(&task->ipp->sequence);

	drm_send_event(task->dev, &task->event->base);
}

static int exynos_drm_ipp_task_cleanup(struct exynos_drm_ipp_task *task)
{
	int ret = task->ret;

	if (ret == 0 && task->event) {
		exynos_drm_ipp_event_send(task);
		/* ensure event won't be canceled on task free */
		task->event = NULL;
	}

	exynos_drm_ipp_task_free(task->ipp, task);
	return ret;
}

static void exynos_drm_ipp_cleanup_work(struct work_struct *work)
{
	struct exynos_drm_ipp_task *task = container_of(work,
				      struct exynos_drm_ipp_task, cleanup_work);

	exynos_drm_ipp_task_cleanup(task);
}

static void exynos_drm_ipp_next_task(struct exynos_drm_ipp *ipp);

/**
 * exynos_drm_ipp_task_done - finish given task and set return code
 * @task: ipp task to finish
 * @ret: error code or 0 if operation has been performed successfully
 */
void exynos_drm_ipp_task_done(struct exynos_drm_ipp_task *task, int ret)
{
	struct exynos_drm_ipp *ipp = task->ipp;
	unsigned long flags;

	DRM_DEBUG_DRIVER("ipp: %d, task %pK done: %d\n", ipp->id, task, ret);

	spin_lock_irqsave(&ipp->lock, flags);
	if (ipp->task == task)
		ipp->task = NULL;
	task->flags |= DRM_EXYNOS_IPP_TASK_DONE;
	task->ret = ret;
	spin_unlock_irqrestore(&ipp->lock, flags);

	exynos_drm_ipp_next_task(ipp);
	wake_up(&ipp->done_wq);

	if (task->flags & DRM_EXYNOS_IPP_TASK_ASYNC) {
		INIT_WORK(&task->cleanup_work, exynos_drm_ipp_cleanup_work);
		schedule_work(&task->cleanup_work);
	}
}

static void exynos_drm_ipp_next_task(struct exynos_drm_ipp *ipp)
{
	struct exynos_drm_ipp_task *task;
	unsigned long flags;
	int ret;

	DRM_DEBUG_DRIVER("ipp: %d, try to run new task\n", ipp->id);

	spin_lock_irqsave(&ipp->lock, flags);

	if (ipp->task || list_empty(&ipp->todo_list)) {
		spin_unlock_irqrestore(&ipp->lock, flags);
		return;
	}

	task = list_first_entry(&ipp->todo_list, struct exynos_drm_ipp_task,
				head);
	list_del_init(&task->head);
	ipp->task = task;

	spin_unlock_irqrestore(&ipp->lock, flags);

	DRM_DEBUG_DRIVER("ipp: %d, selected task %pK to run\n", ipp->id, task);

	ret = ipp->funcs->commit(ipp, task);
	if (ret)
		exynos_drm_ipp_task_done(task, ret);
}

static void exynos_drm_ipp_schedule_task(struct exynos_drm_ipp *ipp,
					 struct exynos_drm_ipp_task *task)
{
	unsigned long flags;

	spin_lock_irqsave(&ipp->lock, flags);
	list_add(&task->head, &ipp->todo_list);
	spin_unlock_irqrestore(&ipp->lock, flags);

	exynos_drm_ipp_next_task(ipp);
}

static void exynos_drm_ipp_task_abort(struct exynos_drm_ipp *ipp,
				      struct exynos_drm_ipp_task *task)
{
	unsigned long flags;

	spin_lock_irqsave(&ipp->lock, flags);
	if (task->flags & DRM_EXYNOS_IPP_TASK_DONE) {
		/* already completed task */
		exynos_drm_ipp_task_cleanup(task);
	} else if (ipp->task != task) {
		/* task has not been scheduled for execution yet */
		list_del_init(&task->head);
		exynos_drm_ipp_task_cleanup(task);
	} else {
		/*
		 * currently processed task, call abort() and perform
		 * cleanup with async worker
		 */
		task->flags |= DRM_EXYNOS_IPP_TASK_ASYNC;
		spin_unlock_irqrestore(&ipp->lock, flags);
		if (ipp->funcs->abort)
			ipp->funcs->abort(ipp, task);
		return;
	}
	spin_unlock_irqrestore(&ipp->lock, flags);
}

/**
 * exynos_drm_ipp_commit_ioctl - perform image processing operation
 * @dev: DRM device
 * @data: ioctl data
 * @file_priv: DRM file info
 *
 * Construct a ipp task from the set of properties provided from the user
 * and try to schedule it to framebuffer processor hardware.
 *
 * Called by the user via ioctl.
 *
 * Returns:
 * Zero on success, negative errno on failure.
 */
int exynos_drm_ipp_commit_ioctl(struct drm_device *dev, void *data,
				struct drm_file *file_priv)
{
	struct drm_exynos_ioctl_ipp_commit *arg = data;
	struct exynos_drm_ipp *ipp;
	struct exynos_drm_ipp_task *task;
	int ret = 0;

	if ((arg->flags & ~DRM_EXYNOS_IPP_FLAGS) || arg->reserved)
		return -EINVAL;

	/* can't test and expect an event at the same time */
	if ((arg->flags & DRM_EXYNOS_IPP_FLAG_TEST_ONLY) &&
			(arg->flags & DRM_EXYNOS_IPP_FLAG_EVENT))
		return -EINVAL;

	ipp = __ipp_get(arg->ipp_id);
	if (!ipp)
		return -ENOENT;

	task = exynos_drm_ipp_task_alloc(ipp);
	if (!task)
		return -ENOMEM;

	ret = exynos_drm_ipp_task_set(task, arg);
	if (ret)
		goto free;

	ret = exynos_drm_ipp_task_check(task);
	if (ret)
		goto free;

	ret = exynos_drm_ipp_task_setup_buffers(task, file_priv);
	if (ret || arg->flags & DRM_EXYNOS_IPP_FLAG_TEST_ONLY)
		goto free;

	if (arg->flags & DRM_EXYNOS_IPP_FLAG_EVENT) {
		ret = exynos_drm_ipp_event_create(task, file_priv,
						 arg->user_data);
		if (ret)
			goto free;
	}

	/*
	 * Queue task for processing on the hardware. task object will be
	 * then freed after exynos_drm_ipp_task_done()
	 */
	if (arg->flags & DRM_EXYNOS_IPP_FLAG_NONBLOCK) {
		DRM_DEBUG_DRIVER("ipp: %d, nonblocking processing task %pK\n",
				 ipp->id, task);

		task->flags |= DRM_EXYNOS_IPP_TASK_ASYNC;
		exynos_drm_ipp_schedule_task(task->ipp, task);
		ret = 0;
	} else {
		DRM_DEBUG_DRIVER("ipp: %d, processing task %pK\n", ipp->id,
				 task);
		exynos_drm_ipp_schedule_task(ipp, task);
		ret = wait_event_interruptible(ipp->done_wq,
					task->flags & DRM_EXYNOS_IPP_TASK_DONE);
		if (ret)
			exynos_drm_ipp_task_abort(ipp, task);
		else
			ret = exynos_drm_ipp_task_cleanup(task);
	}
	return ret;
free:
	exynos_drm_ipp_task_free(ipp, task);

	return ret;
}
=======
	/* make event */
	e->event.base.type = DRM_EXYNOS_IPP_EVENT;
	e->event.base.length = sizeof(e->event);
	e->event.user_data = qbuf->user_data;
	e->event.prop_id = qbuf->prop_id;
	e->event.buf_id[EXYNOS_DRM_OPS_DST] = qbuf->buf_id;

	ret = drm_event_reserve_init(drm_dev, c_node->filp, &e->base, &e->event.base);
	if (ret) {
		kfree(e);
		return ret;
	}

	mutex_lock(&c_node->event_lock);
	list_add_tail(&e->base.link, &c_node->event_list);
	mutex_unlock(&c_node->event_lock);

	return 0;
}

static void ipp_put_event(struct drm_exynos_ipp_cmd_node *c_node,
		struct drm_exynos_ipp_queue_buf *qbuf)
{
	struct drm_exynos_ipp_send_event *e, *te;
	int count = 0;

	mutex_lock(&c_node->event_lock);
	list_for_each_entry_safe(e, te, &c_node->event_list, base.link) {
		DRM_DEBUG_KMS("count[%d]e[%pK]\n", count++, e);

		/*
		 * qbuf == NULL condition means all event deletion.
		 * stop operations want to delete all event list.
		 * another case delete only same buf id.
		 */
		if (!qbuf) {
			/* delete list */
			list_del(&e->base.link);
			kfree(e);
		}

		/* compare buffer id */
		if (qbuf && (qbuf->buf_id ==
		    e->event.buf_id[EXYNOS_DRM_OPS_DST])) {
			/* delete list */
			list_del(&e->base.link);
			kfree(e);
			goto out_unlock;
		}
	}

out_unlock:
	mutex_unlock(&c_node->event_lock);
	return;
}

static void ipp_clean_cmd_node(struct ipp_context *ctx,
				struct drm_exynos_ipp_cmd_node *c_node)
{
	int i;

	/* cancel works */
	cancel_work_sync(&c_node->start_work->work);
	cancel_work_sync(&c_node->stop_work->work);
	cancel_work_sync(&c_node->event_work->work);

	/* put event */
	ipp_put_event(c_node, NULL);

	for_each_ipp_ops(i)
		ipp_clean_mem_nodes(ctx->subdrv.drm_dev, c_node, i);

	/* delete list */
	list_del(&c_node->list);

	ipp_remove_id(&ctx->prop_idr, &ctx->prop_lock,
			c_node->property.prop_id);

	/* destroy mutex */
	mutex_destroy(&c_node->lock);
	mutex_destroy(&c_node->mem_lock);
	mutex_destroy(&c_node->event_lock);

	/* free command node */
	kfree(c_node->start_work);
	kfree(c_node->stop_work);
	kfree(c_node->event_work);
	kfree(c_node);
}

static bool ipp_check_mem_list(struct drm_exynos_ipp_cmd_node *c_node)
{
	switch (c_node->property.cmd) {
	case IPP_CMD_WB:
		return !list_empty(&c_node->mem_list[EXYNOS_DRM_OPS_DST]);
	case IPP_CMD_OUTPUT:
		return !list_empty(&c_node->mem_list[EXYNOS_DRM_OPS_SRC]);
	case IPP_CMD_M2M:
	default:
		return !list_empty(&c_node->mem_list[EXYNOS_DRM_OPS_SRC]) &&
		       !list_empty(&c_node->mem_list[EXYNOS_DRM_OPS_DST]);
	}
}

static struct drm_exynos_ipp_mem_node
		*ipp_find_mem_node(struct drm_exynos_ipp_cmd_node *c_node,
		struct drm_exynos_ipp_queue_buf *qbuf)
{
	struct drm_exynos_ipp_mem_node *m_node;
	struct list_head *head;
	int count = 0;

	DRM_DEBUG_KMS("buf_id[%d]\n", qbuf->buf_id);

	/* source/destination memory list */
	head = &c_node->mem_list[qbuf->ops_id];

	/* find memory node from memory list */
	list_for_each_entry(m_node, head, list) {
		DRM_DEBUG_KMS("count[%d]m_node[%pK]\n", count++, m_node);

		/* compare buffer id */
		if (m_node->buf_id == qbuf->buf_id)
			return m_node;
	}

	return NULL;
}

static int ipp_set_mem_node(struct exynos_drm_ippdrv *ippdrv,
		struct drm_exynos_ipp_cmd_node *c_node,
		struct drm_exynos_ipp_mem_node *m_node)
{
	struct exynos_drm_ipp_ops *ops = NULL;
	int ret = 0;

	DRM_DEBUG_KMS("node[%pK]\n", m_node);

	if (!m_node) {
		DRM_ERROR("invalid queue node.\n");
		return -EFAULT;
	}

	DRM_DEBUG_KMS("ops_id[%d]\n", m_node->ops_id);

	/* get operations callback */
	ops = ippdrv->ops[m_node->ops_id];
	if (!ops) {
		DRM_ERROR("not support ops.\n");
		return -EFAULT;
	}

	/* set address and enable irq */
	if (ops->set_addr) {
		ret = ops->set_addr(ippdrv->dev, &m_node->buf_info,
			m_node->buf_id, IPP_BUF_ENQUEUE);
		if (ret) {
			DRM_ERROR("failed to set addr.\n");
			return ret;
		}
	}

	return ret;
}

static void ipp_handle_cmd_work(struct device *dev,
		struct exynos_drm_ippdrv *ippdrv,
		struct drm_exynos_ipp_cmd_work *cmd_work,
		struct drm_exynos_ipp_cmd_node *c_node)
{
	struct ipp_context *ctx = get_ipp_context(dev);

	cmd_work->ippdrv = ippdrv;
	cmd_work->c_node = c_node;
	queue_work(ctx->cmd_workq, &cmd_work->work);
}

static int ipp_queue_buf_with_run(struct device *dev,
		struct drm_exynos_ipp_cmd_node *c_node,
		struct drm_exynos_ipp_mem_node *m_node,
		struct drm_exynos_ipp_queue_buf *qbuf)
{
	struct exynos_drm_ippdrv *ippdrv;
	struct drm_exynos_ipp_property *property;
	struct exynos_drm_ipp_ops *ops;
	int ret;

	ippdrv = ipp_find_drv_by_handle(qbuf->prop_id);
	if (IS_ERR(ippdrv)) {
		DRM_ERROR("failed to get ipp driver.\n");
		return -EFAULT;
	}

	ops = ippdrv->ops[qbuf->ops_id];
	if (!ops) {
		DRM_ERROR("failed to get ops.\n");
		return -EFAULT;
	}

	property = &c_node->property;

	if (c_node->state != IPP_STATE_START) {
		DRM_DEBUG_KMS("bypass for invalid state.\n");
		return 0;
	}

	mutex_lock(&c_node->mem_lock);
	if (!ipp_check_mem_list(c_node)) {
		mutex_unlock(&c_node->mem_lock);
		DRM_DEBUG_KMS("empty memory.\n");
		return 0;
	}

	/*
	 * If set destination buffer and enabled clock,
	 * then m2m operations need start operations at queue_buf
	 */
	if (ipp_is_m2m_cmd(property->cmd)) {
		struct drm_exynos_ipp_cmd_work *cmd_work = c_node->start_work;

		cmd_work->ctrl = IPP_CTRL_PLAY;
		ipp_handle_cmd_work(dev, ippdrv, cmd_work, c_node);
	} else {
		ret = ipp_set_mem_node(ippdrv, c_node, m_node);
		if (ret) {
			mutex_unlock(&c_node->mem_lock);
			DRM_ERROR("failed to set m node.\n");
			return ret;
		}
	}
	mutex_unlock(&c_node->mem_lock);

	return 0;
}

static void ipp_clean_queue_buf(struct drm_device *drm_dev,
		struct drm_exynos_ipp_cmd_node *c_node,
		struct drm_exynos_ipp_queue_buf *qbuf)
{
	struct drm_exynos_ipp_mem_node *m_node, *tm_node;

	/* delete list */
	mutex_lock(&c_node->mem_lock);
	list_for_each_entry_safe(m_node, tm_node,
		&c_node->mem_list[qbuf->ops_id], list) {
		if (m_node->buf_id == qbuf->buf_id &&
		    m_node->ops_id == qbuf->ops_id)
			ipp_put_mem_node(drm_dev, c_node, m_node);
	}
	mutex_unlock(&c_node->mem_lock);
}

int exynos_drm_ipp_queue_buf(struct drm_device *drm_dev, void *data,
		struct drm_file *file)
{
	struct drm_exynos_file_private *file_priv = file->driver_priv;
	struct device *dev = file_priv->ipp_dev;
	struct ipp_context *ctx = get_ipp_context(dev);
	struct drm_exynos_ipp_queue_buf *qbuf = data;
	struct drm_exynos_ipp_cmd_node *c_node;
	struct drm_exynos_ipp_mem_node *m_node;
	int ret;

	if (!qbuf) {
		DRM_ERROR("invalid buf parameter.\n");
		return -EINVAL;
	}

	if (qbuf->ops_id >= EXYNOS_DRM_OPS_MAX) {
		DRM_ERROR("invalid ops parameter.\n");
		return -EINVAL;
	}

	DRM_DEBUG_KMS("prop_id[%d]ops_id[%s]buf_id[%d]buf_type[%d]\n",
		qbuf->prop_id, qbuf->ops_id ? "dst" : "src",
		qbuf->buf_id, qbuf->buf_type);

	/* find command node */
	c_node = ipp_find_obj(&ctx->prop_idr, &ctx->prop_lock,
		qbuf->prop_id);
	if (!c_node || c_node->filp != file) {
		DRM_ERROR("failed to get command node.\n");
		return -ENODEV;
	}

	/* buffer control */
	switch (qbuf->buf_type) {
	case IPP_BUF_ENQUEUE:
		/* get memory node */
		m_node = ipp_get_mem_node(drm_dev, c_node, qbuf);
		if (IS_ERR(m_node)) {
			DRM_ERROR("failed to get m_node.\n");
			return PTR_ERR(m_node);
		}

		/*
		 * first step get event for destination buffer.
		 * and second step when M2M case run with destination buffer
		 * if needed.
		 */
		if (qbuf->ops_id == EXYNOS_DRM_OPS_DST) {
			/* get event for destination buffer */
			ret = ipp_get_event(drm_dev, c_node, qbuf);
			if (ret) {
				DRM_ERROR("failed to get event.\n");
				goto err_clean_node;
			}

			/*
			 * M2M case run play control for streaming feature.
			 * other case set address and waiting.
			 */
			ret = ipp_queue_buf_with_run(dev, c_node, m_node, qbuf);
			if (ret) {
				DRM_ERROR("failed to run command.\n");
				goto err_clean_node;
			}
		}
		break;
	case IPP_BUF_DEQUEUE:
		mutex_lock(&c_node->lock);

		/* put event for destination buffer */
		if (qbuf->ops_id == EXYNOS_DRM_OPS_DST)
			ipp_put_event(c_node, qbuf);

		ipp_clean_queue_buf(drm_dev, c_node, qbuf);

		mutex_unlock(&c_node->lock);
		break;
	default:
		DRM_ERROR("invalid buffer control.\n");
		return -EINVAL;
	}

	return 0;

err_clean_node:
	DRM_ERROR("clean memory nodes.\n");

	ipp_clean_queue_buf(drm_dev, c_node, qbuf);
	return ret;
}

static bool exynos_drm_ipp_check_valid(struct device *dev,
		enum drm_exynos_ipp_ctrl ctrl, enum drm_exynos_ipp_state state)
{
	if (ctrl != IPP_CTRL_PLAY) {
		if (pm_runtime_suspended(dev)) {
			DRM_ERROR("pm:runtime_suspended.\n");
			goto err_status;
		}
	}

	switch (ctrl) {
	case IPP_CTRL_PLAY:
		if (state != IPP_STATE_IDLE)
			goto err_status;
		break;
	case IPP_CTRL_STOP:
		if (state == IPP_STATE_STOP)
			goto err_status;
		break;
	case IPP_CTRL_PAUSE:
		if (state != IPP_STATE_START)
			goto err_status;
		break;
	case IPP_CTRL_RESUME:
		if (state != IPP_STATE_STOP)
			goto err_status;
		break;
	default:
		DRM_ERROR("invalid state.\n");
		goto err_status;
	}

	return true;

err_status:
	DRM_ERROR("invalid status:ctrl[%d]state[%d]\n", ctrl, state);
	return false;
}

int exynos_drm_ipp_cmd_ctrl(struct drm_device *drm_dev, void *data,
		struct drm_file *file)
{
	struct drm_exynos_file_private *file_priv = file->driver_priv;
	struct exynos_drm_ippdrv *ippdrv = NULL;
	struct device *dev = file_priv->ipp_dev;
	struct ipp_context *ctx = get_ipp_context(dev);
	struct drm_exynos_ipp_cmd_ctrl *cmd_ctrl = data;
	struct drm_exynos_ipp_cmd_work *cmd_work;
	struct drm_exynos_ipp_cmd_node *c_node;

	if (!ctx) {
		DRM_ERROR("invalid context.\n");
		return -EINVAL;
	}

	if (!cmd_ctrl) {
		DRM_ERROR("invalid control parameter.\n");
		return -EINVAL;
	}

	DRM_DEBUG_KMS("ctrl[%d]prop_id[%d]\n",
		cmd_ctrl->ctrl, cmd_ctrl->prop_id);

	ippdrv = ipp_find_drv_by_handle(cmd_ctrl->prop_id);
	if (IS_ERR(ippdrv)) {
		DRM_ERROR("failed to get ipp driver.\n");
		return PTR_ERR(ippdrv);
	}

	c_node = ipp_find_obj(&ctx->prop_idr, &ctx->prop_lock,
		cmd_ctrl->prop_id);
	if (!c_node || c_node->filp != file) {
		DRM_ERROR("invalid command node list.\n");
		return -ENODEV;
	}

	if (!exynos_drm_ipp_check_valid(ippdrv->dev, cmd_ctrl->ctrl,
	    c_node->state)) {
		DRM_ERROR("invalid state.\n");
		return -EINVAL;
	}

	switch (cmd_ctrl->ctrl) {
	case IPP_CTRL_PLAY:
		if (pm_runtime_suspended(ippdrv->dev))
			pm_runtime_get_sync(ippdrv->dev);

		c_node->state = IPP_STATE_START;

		cmd_work = c_node->start_work;
		cmd_work->ctrl = cmd_ctrl->ctrl;
		ipp_handle_cmd_work(dev, ippdrv, cmd_work, c_node);
		break;
	case IPP_CTRL_STOP:
		cmd_work = c_node->stop_work;
		cmd_work->ctrl = cmd_ctrl->ctrl;
		ipp_handle_cmd_work(dev, ippdrv, cmd_work, c_node);

		if (!wait_for_completion_timeout(&c_node->stop_complete,
		    msecs_to_jiffies(300))) {
			DRM_ERROR("timeout stop:prop_id[%d]\n",
				c_node->property.prop_id);
		}

		c_node->state = IPP_STATE_STOP;
		ippdrv->dedicated = false;
		mutex_lock(&ippdrv->cmd_lock);
		ipp_clean_cmd_node(ctx, c_node);

		if (list_empty(&ippdrv->cmd_list))
			pm_runtime_put_sync(ippdrv->dev);
		mutex_unlock(&ippdrv->cmd_lock);
		break;
	case IPP_CTRL_PAUSE:
		cmd_work = c_node->stop_work;
		cmd_work->ctrl = cmd_ctrl->ctrl;
		ipp_handle_cmd_work(dev, ippdrv, cmd_work, c_node);

		if (!wait_for_completion_timeout(&c_node->stop_complete,
		    msecs_to_jiffies(200))) {
			DRM_ERROR("timeout stop:prop_id[%d]\n",
				c_node->property.prop_id);
		}

		c_node->state = IPP_STATE_STOP;
		break;
	case IPP_CTRL_RESUME:
		c_node->state = IPP_STATE_START;
		cmd_work = c_node->start_work;
		cmd_work->ctrl = cmd_ctrl->ctrl;
		ipp_handle_cmd_work(dev, ippdrv, cmd_work, c_node);
		break;
	default:
		DRM_ERROR("could not support this state currently.\n");
		return -EINVAL;
	}

	DRM_DEBUG_KMS("done ctrl[%d]prop_id[%d]\n",
		cmd_ctrl->ctrl, cmd_ctrl->prop_id);

	return 0;
}

int exynos_drm_ippnb_register(struct notifier_block *nb)
{
	return blocking_notifier_chain_register(
		&exynos_drm_ippnb_list, nb);
}

int exynos_drm_ippnb_unregister(struct notifier_block *nb)
{
	return blocking_notifier_chain_unregister(
		&exynos_drm_ippnb_list, nb);
}

int exynos_drm_ippnb_send_event(unsigned long val, void *v)
{
	return blocking_notifier_call_chain(
		&exynos_drm_ippnb_list, val, v);
}

static int ipp_set_property(struct exynos_drm_ippdrv *ippdrv,
		struct drm_exynos_ipp_property *property)
{
	struct exynos_drm_ipp_ops *ops = NULL;
	bool swap = false;
	int ret, i;

	if (!property) {
		DRM_ERROR("invalid property parameter.\n");
		return -EINVAL;
	}

	DRM_DEBUG_KMS("prop_id[%d]\n", property->prop_id);

	/* reset h/w block */
	if (ippdrv->reset &&
	    ippdrv->reset(ippdrv->dev)) {
		return -EINVAL;
	}

	/* set source,destination operations */
	for_each_ipp_ops(i) {
		struct drm_exynos_ipp_config *config =
			&property->config[i];

		ops = ippdrv->ops[i];
		if (!ops || !config) {
			DRM_ERROR("not support ops and config.\n");
			return -EINVAL;
		}

		/* set format */
		if (ops->set_fmt) {
			ret = ops->set_fmt(ippdrv->dev, config->fmt);
			if (ret)
				return ret;
		}

		/* set transform for rotation, flip */
		if (ops->set_transf) {
			ret = ops->set_transf(ippdrv->dev, config->degree,
				config->flip, &swap);
			if (ret)
				return ret;
		}

		/* set size */
		if (ops->set_size) {
			ret = ops->set_size(ippdrv->dev, swap, &config->pos,
				&config->sz);
			if (ret)
				return ret;
		}
	}

	return 0;
}

static int ipp_start_property(struct exynos_drm_ippdrv *ippdrv,
		struct drm_exynos_ipp_cmd_node *c_node)
{
	struct drm_exynos_ipp_mem_node *m_node;
	struct drm_exynos_ipp_property *property = &c_node->property;
	struct list_head *head;
	int ret, i;

	DRM_DEBUG_KMS("prop_id[%d]\n", property->prop_id);

	/* store command info in ippdrv */
	ippdrv->c_node = c_node;

	mutex_lock(&c_node->mem_lock);
	if (!ipp_check_mem_list(c_node)) {
		DRM_DEBUG_KMS("empty memory.\n");
		ret = -ENOMEM;
		goto err_unlock;
	}

	/* set current property in ippdrv */
	ret = ipp_set_property(ippdrv, property);
	if (ret) {
		DRM_ERROR("failed to set property.\n");
		ippdrv->c_node = NULL;
		goto err_unlock;
	}

	/* check command */
	switch (property->cmd) {
	case IPP_CMD_M2M:
		for_each_ipp_ops(i) {
			/* source/destination memory list */
			head = &c_node->mem_list[i];

			m_node = list_first_entry(head,
				struct drm_exynos_ipp_mem_node, list);

			DRM_DEBUG_KMS("m_node[%pK]\n", m_node);

			ret = ipp_set_mem_node(ippdrv, c_node, m_node);
			if (ret) {
				DRM_ERROR("failed to set m node.\n");
				goto err_unlock;
			}
		}
		break;
	case IPP_CMD_WB:
		/* destination memory list */
		head = &c_node->mem_list[EXYNOS_DRM_OPS_DST];

		list_for_each_entry(m_node, head, list) {
			ret = ipp_set_mem_node(ippdrv, c_node, m_node);
			if (ret) {
				DRM_ERROR("failed to set m node.\n");
				goto err_unlock;
			}
		}
		break;
	case IPP_CMD_OUTPUT:
		/* source memory list */
		head = &c_node->mem_list[EXYNOS_DRM_OPS_SRC];

		list_for_each_entry(m_node, head, list) {
			ret = ipp_set_mem_node(ippdrv, c_node, m_node);
			if (ret) {
				DRM_ERROR("failed to set m node.\n");
				goto err_unlock;
			}
		}
		break;
	default:
		DRM_ERROR("invalid operations.\n");
		ret = -EINVAL;
		goto err_unlock;
	}
	mutex_unlock(&c_node->mem_lock);

	DRM_DEBUG_KMS("cmd[%d]\n", property->cmd);

	/* start operations */
	if (ippdrv->start) {
		ret = ippdrv->start(ippdrv->dev, property->cmd);
		if (ret) {
			DRM_ERROR("failed to start ops.\n");
			ippdrv->c_node = NULL;
			return ret;
		}
	}

	return 0;

err_unlock:
	mutex_unlock(&c_node->mem_lock);
	ippdrv->c_node = NULL;
	return ret;
}

static int ipp_stop_property(struct drm_device *drm_dev,
		struct exynos_drm_ippdrv *ippdrv,
		struct drm_exynos_ipp_cmd_node *c_node)
{
	struct drm_exynos_ipp_property *property = &c_node->property;
	int i;

	DRM_DEBUG_KMS("prop_id[%d]\n", property->prop_id);

	/* stop operations */
	if (ippdrv->stop)
		ippdrv->stop(ippdrv->dev, property->cmd);

	/* check command */
	switch (property->cmd) {
	case IPP_CMD_M2M:
		for_each_ipp_ops(i)
			ipp_clean_mem_nodes(drm_dev, c_node, i);
		break;
	case IPP_CMD_WB:
		ipp_clean_mem_nodes(drm_dev, c_node, EXYNOS_DRM_OPS_DST);
		break;
	case IPP_CMD_OUTPUT:
		ipp_clean_mem_nodes(drm_dev, c_node, EXYNOS_DRM_OPS_SRC);
		break;
	default:
		DRM_ERROR("invalid operations.\n");
		return -EINVAL;
	}

	return 0;
}

void ipp_sched_cmd(struct work_struct *work)
{
	struct drm_exynos_ipp_cmd_work *cmd_work =
		container_of(work, struct drm_exynos_ipp_cmd_work, work);
	struct exynos_drm_ippdrv *ippdrv;
	struct drm_exynos_ipp_cmd_node *c_node;
	struct drm_exynos_ipp_property *property;
	int ret;

	ippdrv = cmd_work->ippdrv;
	if (!ippdrv) {
		DRM_ERROR("invalid ippdrv list.\n");
		return;
	}

	c_node = cmd_work->c_node;
	if (!c_node) {
		DRM_ERROR("invalid command node list.\n");
		return;
	}

	mutex_lock(&c_node->lock);

	property = &c_node->property;

	switch (cmd_work->ctrl) {
	case IPP_CTRL_PLAY:
	case IPP_CTRL_RESUME:
		ret = ipp_start_property(ippdrv, c_node);
		if (ret) {
			DRM_ERROR("failed to start property:prop_id[%d]\n",
				c_node->property.prop_id);
			goto err_unlock;
		}

		/*
		 * M2M case supports wait_completion of transfer.
		 * because M2M case supports single unit operation
		 * with multiple queue.
		 * M2M need to wait completion of data transfer.
		 */
		if (ipp_is_m2m_cmd(property->cmd)) {
			if (!wait_for_completion_timeout
			    (&c_node->start_complete, msecs_to_jiffies(200))) {
				DRM_ERROR("timeout event:prop_id[%d]\n",
					c_node->property.prop_id);
				goto err_unlock;
			}
		}
		break;
	case IPP_CTRL_STOP:
	case IPP_CTRL_PAUSE:
		ret = ipp_stop_property(ippdrv->drm_dev, ippdrv,
			c_node);
		if (ret) {
			DRM_ERROR("failed to stop property.\n");
			goto err_unlock;
		}

		complete(&c_node->stop_complete);
		break;
	default:
		DRM_ERROR("unknown control type\n");
		break;
	}

	DRM_DEBUG_KMS("ctrl[%d] done.\n", cmd_work->ctrl);

err_unlock:
	mutex_unlock(&c_node->lock);
}

static int ipp_send_event(struct exynos_drm_ippdrv *ippdrv,
		struct drm_exynos_ipp_cmd_node *c_node, int *buf_id)
{
	struct drm_device *drm_dev = ippdrv->drm_dev;
	struct drm_exynos_ipp_property *property = &c_node->property;
	struct drm_exynos_ipp_mem_node *m_node;
	struct drm_exynos_ipp_queue_buf qbuf;
	struct drm_exynos_ipp_send_event *e;
	struct list_head *head;
	struct timeval now;
	u32 tbuf_id[EXYNOS_DRM_OPS_MAX] = {0, };
	int ret, i;

	for_each_ipp_ops(i)
		DRM_DEBUG_KMS("%s buf_id[%d]\n", i ? "dst" : "src", buf_id[i]);

	if (!drm_dev) {
		DRM_ERROR("failed to get drm_dev.\n");
		return -EINVAL;
	}

	if (!property) {
		DRM_ERROR("failed to get property.\n");
		return -EINVAL;
	}

	mutex_lock(&c_node->event_lock);
	if (list_empty(&c_node->event_list)) {
		DRM_DEBUG_KMS("event list is empty.\n");
		ret = 0;
		goto err_event_unlock;
	}

	mutex_lock(&c_node->mem_lock);
	if (!ipp_check_mem_list(c_node)) {
		DRM_DEBUG_KMS("empty memory.\n");
		ret = 0;
		goto err_mem_unlock;
	}

	/* check command */
	switch (property->cmd) {
	case IPP_CMD_M2M:
		for_each_ipp_ops(i) {
			/* source/destination memory list */
			head = &c_node->mem_list[i];

			m_node = list_first_entry(head,
				struct drm_exynos_ipp_mem_node, list);

			tbuf_id[i] = m_node->buf_id;
			DRM_DEBUG_KMS("%s buf_id[%d]\n",
				i ? "dst" : "src", tbuf_id[i]);

			ret = ipp_put_mem_node(drm_dev, c_node, m_node);
			if (ret)
				DRM_ERROR("failed to put m_node.\n");
		}
		break;
	case IPP_CMD_WB:
		/* clear buf for finding */
		memset(&qbuf, 0x0, sizeof(qbuf));
		qbuf.ops_id = EXYNOS_DRM_OPS_DST;
		qbuf.buf_id = buf_id[EXYNOS_DRM_OPS_DST];

		/* get memory node entry */
		m_node = ipp_find_mem_node(c_node, &qbuf);
		if (!m_node) {
			DRM_ERROR("empty memory node.\n");
			ret = -ENOMEM;
			goto err_mem_unlock;
		}

		tbuf_id[EXYNOS_DRM_OPS_DST] = m_node->buf_id;

		ret = ipp_put_mem_node(drm_dev, c_node, m_node);
		if (ret)
			DRM_ERROR("failed to put m_node.\n");
		break;
	case IPP_CMD_OUTPUT:
		/* source memory list */
		head = &c_node->mem_list[EXYNOS_DRM_OPS_SRC];

		m_node = list_first_entry(head,
			struct drm_exynos_ipp_mem_node, list);

		tbuf_id[EXYNOS_DRM_OPS_SRC] = m_node->buf_id;

		ret = ipp_put_mem_node(drm_dev, c_node, m_node);
		if (ret)
			DRM_ERROR("failed to put m_node.\n");
		break;
	default:
		DRM_ERROR("invalid operations.\n");
		ret = -EINVAL;
		goto err_mem_unlock;
	}
	mutex_unlock(&c_node->mem_lock);

	if (tbuf_id[EXYNOS_DRM_OPS_DST] != buf_id[EXYNOS_DRM_OPS_DST])
		DRM_ERROR("failed to match buf_id[%d %d]prop_id[%d]\n",
			tbuf_id[1], buf_id[1], property->prop_id);

	/*
	 * command node have event list of destination buffer
	 * If destination buffer enqueue to mem list,
	 * then we make event and link to event list tail.
	 * so, we get first event for first enqueued buffer.
	 */
	e = list_first_entry(&c_node->event_list,
		struct drm_exynos_ipp_send_event, base.link);

	do_gettimeofday(&now);
	DRM_DEBUG_KMS("tv_sec[%ld]tv_usec[%ld]\n", now.tv_sec, now.tv_usec);
	e->event.tv_sec = now.tv_sec;
	e->event.tv_usec = now.tv_usec;
	e->event.prop_id = property->prop_id;

	/* set buffer id about source destination */
	for_each_ipp_ops(i)
		e->event.buf_id[i] = tbuf_id[i];

	drm_send_event(drm_dev, &e->base);
	mutex_unlock(&c_node->event_lock);

	DRM_DEBUG_KMS("done cmd[%d]prop_id[%d]buf_id[%d]\n",
		property->cmd, property->prop_id, tbuf_id[EXYNOS_DRM_OPS_DST]);

	return 0;

err_mem_unlock:
	mutex_unlock(&c_node->mem_lock);
err_event_unlock:
	mutex_unlock(&c_node->event_lock);
	return ret;
}

void ipp_sched_event(struct work_struct *work)
{
	struct drm_exynos_ipp_event_work *event_work =
		container_of(work, struct drm_exynos_ipp_event_work, work);
	struct exynos_drm_ippdrv *ippdrv;
	struct drm_exynos_ipp_cmd_node *c_node;
	int ret;

	if (!event_work) {
		DRM_ERROR("failed to get event_work.\n");
		return;
	}

	DRM_DEBUG_KMS("buf_id[%d]\n", event_work->buf_id[EXYNOS_DRM_OPS_DST]);

	ippdrv = event_work->ippdrv;
	if (!ippdrv) {
		DRM_ERROR("failed to get ipp driver.\n");
		return;
	}

	c_node = ippdrv->c_node;
	if (!c_node) {
		DRM_ERROR("failed to get command node.\n");
		return;
	}

	/*
	 * IPP supports command thread, event thread synchronization.
	 * If IPP close immediately from user land, then IPP make
	 * synchronization with command thread, so make complete event.
	 * or going out operations.
	 */
	if (c_node->state != IPP_STATE_START) {
		DRM_DEBUG_KMS("bypass state[%d]prop_id[%d]\n",
			c_node->state, c_node->property.prop_id);
		goto err_completion;
	}

	ret = ipp_send_event(ippdrv, c_node, event_work->buf_id);
	if (ret) {
		DRM_ERROR("failed to send event.\n");
		goto err_completion;
	}

err_completion:
	if (ipp_is_m2m_cmd(c_node->property.cmd))
		complete(&c_node->start_complete);
}

static int ipp_subdrv_probe(struct drm_device *drm_dev, struct device *dev)
{
	struct ipp_context *ctx = get_ipp_context(dev);
	struct exynos_drm_ippdrv *ippdrv;
	int ret, count = 0;

	/* get ipp driver entry */
	list_for_each_entry(ippdrv, &exynos_drm_ippdrv_list, drv_list) {
		ippdrv->drm_dev = drm_dev;

		ret = ipp_create_id(&ctx->ipp_idr, &ctx->ipp_lock, ippdrv);
		if (ret < 0) {
			DRM_ERROR("failed to create id.\n");
			goto err;
		}
		ippdrv->prop_list.ipp_id = ret;

		DRM_DEBUG_KMS("count[%d]ippdrv[%pK]ipp_id[%d]\n",
			count++, ippdrv, ret);

		/* store parent device for node */
		ippdrv->parent_dev = dev;

		/* store event work queue and handler */
		ippdrv->event_workq = ctx->event_workq;
		ippdrv->sched_event = ipp_sched_event;
		INIT_LIST_HEAD(&ippdrv->cmd_list);
		mutex_init(&ippdrv->cmd_lock);

		ret = drm_iommu_attach_device(drm_dev, ippdrv->dev);
		if (ret) {
			DRM_ERROR("failed to activate iommu\n");
			goto err;
		}
	}

	return 0;

err:
	/* get ipp driver entry */
	list_for_each_entry_continue_reverse(ippdrv, &exynos_drm_ippdrv_list,
						drv_list) {
		drm_iommu_detach_device(drm_dev, ippdrv->dev);

		ipp_remove_id(&ctx->ipp_idr, &ctx->ipp_lock,
				ippdrv->prop_list.ipp_id);
	}

	return ret;
}

static void ipp_subdrv_remove(struct drm_device *drm_dev, struct device *dev)
{
	struct exynos_drm_ippdrv *ippdrv, *t;
	struct ipp_context *ctx = get_ipp_context(dev);

	/* get ipp driver entry */
	list_for_each_entry_safe(ippdrv, t, &exynos_drm_ippdrv_list, drv_list) {
		drm_iommu_detach_device(drm_dev, ippdrv->dev);

		ipp_remove_id(&ctx->ipp_idr, &ctx->ipp_lock,
				ippdrv->prop_list.ipp_id);

		ippdrv->drm_dev = NULL;
		exynos_drm_ippdrv_unregister(ippdrv);
	}
}

static int ipp_subdrv_open(struct drm_device *drm_dev, struct device *dev,
		struct drm_file *file)
{
	struct drm_exynos_file_private *file_priv = file->driver_priv;

	file_priv->ipp_dev = dev;

	DRM_DEBUG_KMS("done priv[%pK]\n", dev);

	return 0;
}

static void ipp_subdrv_close(struct drm_device *drm_dev, struct device *dev,
		struct drm_file *file)
{
	struct exynos_drm_ippdrv *ippdrv = NULL;
	struct ipp_context *ctx = get_ipp_context(dev);
	struct drm_exynos_ipp_cmd_node *c_node, *tc_node;
	int count = 0;

	list_for_each_entry(ippdrv, &exynos_drm_ippdrv_list, drv_list) {
		mutex_lock(&ippdrv->cmd_lock);
		list_for_each_entry_safe(c_node, tc_node,
			&ippdrv->cmd_list, list) {
			DRM_DEBUG_KMS("count[%d]ippdrv[%pK]\n",
				count++, ippdrv);

			if (c_node->filp == file) {
				/*
				 * userland goto unnormal state. process killed.
				 * and close the file.
				 * so, IPP didn't called stop cmd ctrl.
				 * so, we are make stop operation in this state.
				 */
				if (c_node->state == IPP_STATE_START) {
					ipp_stop_property(drm_dev, ippdrv,
						c_node);
					c_node->state = IPP_STATE_STOP;
				}

				ippdrv->dedicated = false;
				ipp_clean_cmd_node(ctx, c_node);
				if (list_empty(&ippdrv->cmd_list))
					pm_runtime_put_sync(ippdrv->dev);
			}
		}
		mutex_unlock(&ippdrv->cmd_lock);
	}

	return;
}

static int ipp_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct ipp_context *ctx;
	struct exynos_drm_subdrv *subdrv;
	int ret;

	ctx = devm_kzalloc(dev, sizeof(*ctx), GFP_KERNEL);
	if (!ctx)
		return -ENOMEM;

	mutex_init(&ctx->ipp_lock);
	mutex_init(&ctx->prop_lock);

	idr_init(&ctx->ipp_idr);
	idr_init(&ctx->prop_idr);

	/*
	 * create single thread for ipp event
	 * IPP supports event thread for IPP drivers.
	 * IPP driver send event_work to this thread.
	 * and IPP event thread send event to user process.
	 */
	ctx->event_workq = create_singlethread_workqueue("ipp_event");
	if (!ctx->event_workq) {
		dev_err(dev, "failed to create event workqueue\n");
		return -EINVAL;
	}

	/*
	 * create single thread for ipp command
	 * IPP supports command thread for user process.
	 * user process make command node using set property ioctl.
	 * and make start_work and send this work to command thread.
	 * and then this command thread start property.
	 */
	ctx->cmd_workq = create_singlethread_workqueue("ipp_cmd");
	if (!ctx->cmd_workq) {
		dev_err(dev, "failed to create cmd workqueue\n");
		ret = -EINVAL;
		goto err_event_workq;
	}

	/* set sub driver informations */
	subdrv = &ctx->subdrv;
	subdrv->dev = dev;
	subdrv->probe = ipp_subdrv_probe;
	subdrv->remove = ipp_subdrv_remove;
	subdrv->open = ipp_subdrv_open;
	subdrv->close = ipp_subdrv_close;

	platform_set_drvdata(pdev, ctx);

	ret = exynos_drm_subdrv_register(subdrv);
	if (ret < 0) {
		DRM_ERROR("failed to register drm ipp device.\n");
		goto err_cmd_workq;
	}

	dev_info(dev, "drm ipp registered successfully.\n");

	return 0;

err_cmd_workq:
	destroy_workqueue(ctx->cmd_workq);
err_event_workq:
	destroy_workqueue(ctx->event_workq);
	return ret;
}

static int ipp_remove(struct platform_device *pdev)
{
	struct ipp_context *ctx = platform_get_drvdata(pdev);

	/* unregister sub driver */
	exynos_drm_subdrv_unregister(&ctx->subdrv);

	/* remove,destroy ipp idr */
	idr_destroy(&ctx->ipp_idr);
	idr_destroy(&ctx->prop_idr);

	mutex_destroy(&ctx->ipp_lock);
	mutex_destroy(&ctx->prop_lock);

	/* destroy command, event work queue */
	destroy_workqueue(ctx->cmd_workq);
	destroy_workqueue(ctx->event_workq);

	return 0;
}

struct platform_driver ipp_driver = {
	.probe		= ipp_probe,
	.remove		= ipp_remove,
	.driver		= {
		.name	= "exynos-drm-ipp",
		.owner	= THIS_MODULE,
	},
};

>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
