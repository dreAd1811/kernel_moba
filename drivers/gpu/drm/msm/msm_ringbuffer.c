/*
 * Copyright (C) 2013 Red Hat
 * Author: Rob Clark <robdclark@gmail.com>
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
 */

#include "msm_ringbuffer.h"
#include "msm_gpu.h"

<<<<<<< HEAD
struct msm_ringbuffer *msm_ringbuffer_new(struct msm_gpu *gpu, int id,
		void *memptrs, uint64_t memptrs_iova)
{
	struct msm_ringbuffer *ring;
	char name[32];
	int ret;

	/* We assume everwhere that MSM_GPU_RINGBUFFER_SZ is a power of 2 */
	BUILD_BUG_ON(!is_power_of_2(MSM_GPU_RINGBUFFER_SZ));
=======
struct msm_ringbuffer *msm_ringbuffer_new(struct msm_gpu *gpu, int size)
{
	struct msm_ringbuffer *ring;
	int ret;

	if (WARN_ON(!is_power_of_2(size)))
		return ERR_PTR(-EINVAL);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	ring = kzalloc(sizeof(*ring), GFP_KERNEL);
	if (!ring) {
		ret = -ENOMEM;
		goto fail;
	}

	ring->gpu = gpu;
<<<<<<< HEAD
	ring->id = id;
	/* Pass NULL for the iova pointer - we will map it later */
	ring->start = msm_gem_kernel_new(gpu->dev, MSM_GPU_RINGBUFFER_SZ,
		MSM_BO_WC, gpu->aspace, &ring->bo, NULL);
=======

	/* Pass NULL for the iova pointer - we will map it later */
	ring->start = msm_gem_kernel_new(gpu->dev, size, MSM_BO_WC,
		gpu->aspace, &ring->bo, NULL);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	if (IS_ERR(ring->start)) {
		ret = PTR_ERR(ring->start);
		ring->start = 0;
		goto fail;
	}
<<<<<<< HEAD
	ring->end   = ring->start + (MSM_GPU_RINGBUFFER_SZ >> 2);
	ring->next  = ring->start;
	ring->cur   = ring->start;

	ring->memptrs = memptrs;
	ring->memptrs_iova = memptrs_iova;

	INIT_LIST_HEAD(&ring->submits);
	spin_lock_init(&ring->lock);

	snprintf(name, sizeof(name), "gpu-ring-%d", ring->id);

	ring->fctx = msm_fence_context_alloc(gpu->dev, name);
=======
	ring->end   = ring->start + (size / 4);
	ring->cur   = ring->start;

	ring->size = size;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	return ring;

fail:
<<<<<<< HEAD
	msm_ringbuffer_destroy(ring);
=======
	if (ring)
		msm_ringbuffer_destroy(ring);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	return ERR_PTR(ret);
}

void msm_ringbuffer_destroy(struct msm_ringbuffer *ring)
{
<<<<<<< HEAD
	if (IS_ERR_OR_NULL(ring))
		return;

	msm_fence_context_free(ring->fctx);

	if (ring->bo) {
		msm_gem_put_iova(ring->bo, ring->gpu->aspace);
		msm_gem_put_vaddr(ring->bo);
		drm_gem_object_put_unlocked(ring->bo);
=======
	if (ring->bo) {
		msm_gem_put_vaddr(ring->bo);
		drm_gem_object_unreference_unlocked(ring->bo);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	}
	kfree(ring);
}
