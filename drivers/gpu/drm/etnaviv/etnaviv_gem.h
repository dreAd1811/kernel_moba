<<<<<<< HEAD
/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (C) 2015-2018 Etnaviv Project
=======
/*
 * Copyright (C) 2015 Etnaviv Project
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 as published by
 * the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
 */

#ifndef __ETNAVIV_GEM_H__
#define __ETNAVIV_GEM_H__

#include <linux/reservation.h>
<<<<<<< HEAD
#include "etnaviv_cmdbuf.h"
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
#include "etnaviv_drv.h"

struct dma_fence;
struct etnaviv_gem_ops;
struct etnaviv_gem_object;

struct etnaviv_gem_userptr {
	uintptr_t ptr;
<<<<<<< HEAD
	struct mm_struct *mm;
=======
	struct task_struct *task;
	struct work_struct *work;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	bool ro;
};

struct etnaviv_vram_mapping {
	struct list_head obj_node;
	struct list_head scan_node;
	struct list_head mmu_node;
	struct etnaviv_gem_object *object;
	struct etnaviv_iommu *mmu;
	struct drm_mm_node vram_node;
	unsigned int use;
	u32 iova;
};

struct etnaviv_gem_object {
	struct drm_gem_object base;
	const struct etnaviv_gem_ops *ops;
	struct mutex lock;

	u32 flags;

	struct list_head gem_node;
	struct etnaviv_gpu *gpu;     /* non-null if active */
	atomic_t gpu_active;
	u32 access;

	struct page **pages;
	struct sg_table *sgt;
	void *vaddr;

	/* normally (resv == &_resv) except for imported bo's */
	struct reservation_object *resv;
	struct reservation_object _resv;

	struct list_head vram_list;

	/* cache maintenance */
	u32 last_cpu_prep_op;

	struct etnaviv_gem_userptr userptr;
};

static inline
struct etnaviv_gem_object *to_etnaviv_bo(struct drm_gem_object *obj)
{
	return container_of(obj, struct etnaviv_gem_object, base);
}

struct etnaviv_gem_ops {
	int (*get_pages)(struct etnaviv_gem_object *);
	void (*release)(struct etnaviv_gem_object *);
	void *(*vmap)(struct etnaviv_gem_object *);
	int (*mmap)(struct etnaviv_gem_object *, struct vm_area_struct *);
};

static inline bool is_active(struct etnaviv_gem_object *etnaviv_obj)
{
	return atomic_read(&etnaviv_obj->gpu_active) != 0;
}

#define MAX_CMDS 4

struct etnaviv_gem_submit_bo {
	u32 flags;
	struct etnaviv_gem_object *obj;
	struct etnaviv_vram_mapping *mapping;
<<<<<<< HEAD
	struct dma_fence *excl;
	unsigned int nr_shared;
	struct dma_fence **shared;
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
};

/* Created per submit-ioctl, to track bo's and cmdstream bufs, etc,
 * associated with the cmdstream submission for synchronization (and
<<<<<<< HEAD
 * make it easier to unwind when things go wrong, etc).
 */
struct etnaviv_gem_submit {
	struct drm_sched_job sched_job;
	struct kref refcount;
	struct etnaviv_gpu *gpu;
	struct dma_fence *out_fence, *in_fence;
	int out_fence_id;
	struct list_head node; /* GPU active submit list */
	struct etnaviv_cmdbuf cmdbuf;
	bool runtime_resumed;
	u32 exec_state;
	u32 flags;
	unsigned int nr_pmrs;
	struct etnaviv_perfmon_request *pmrs;
=======
 * make it easier to unwind when things go wrong, etc).  This only
 * lasts for the duration of the submit-ioctl.
 */
struct etnaviv_gem_submit {
	struct drm_device *dev;
	struct etnaviv_gpu *gpu;
	struct ww_acquire_ctx ticket;
	struct dma_fence *fence;
	u32 flags;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	unsigned int nr_bos;
	struct etnaviv_gem_submit_bo bos[0];
	/* No new members here, the previous one is variable-length! */
};

<<<<<<< HEAD
void etnaviv_submit_put(struct etnaviv_gem_submit * submit);

=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
int etnaviv_gem_wait_bo(struct etnaviv_gpu *gpu, struct drm_gem_object *obj,
	struct timespec *timeout);
int etnaviv_gem_new_private(struct drm_device *dev, size_t size, u32 flags,
	struct reservation_object *robj, const struct etnaviv_gem_ops *ops,
	struct etnaviv_gem_object **res);
<<<<<<< HEAD
void etnaviv_gem_obj_add(struct drm_device *dev, struct drm_gem_object *obj);
=======
int etnaviv_gem_obj_add(struct drm_device *dev, struct drm_gem_object *obj);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
struct page **etnaviv_gem_get_pages(struct etnaviv_gem_object *obj);
void etnaviv_gem_put_pages(struct etnaviv_gem_object *obj);

struct etnaviv_vram_mapping *etnaviv_gem_mapping_get(
	struct drm_gem_object *obj, struct etnaviv_gpu *gpu);
void etnaviv_gem_mapping_reference(struct etnaviv_vram_mapping *mapping);
void etnaviv_gem_mapping_unreference(struct etnaviv_vram_mapping *mapping);

#endif /* __ETNAVIV_GEM_H__ */
