/*
 * Copyright 2015 Advanced Micro Devices, Inc.
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
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors: monk liu <monk.liu@amd.com>
 */

#include <drm/drmP.h>
<<<<<<< HEAD
#include <drm/drm_auth.h>
#include "amdgpu.h"
#include "amdgpu_sched.h"

static int amdgpu_ctx_priority_permit(struct drm_file *filp,
				      enum drm_sched_priority priority)
{
	/* NORMAL and below are accessible by everyone */
	if (priority <= DRM_SCHED_PRIORITY_NORMAL)
		return 0;

	if (capable(CAP_SYS_NICE))
		return 0;

	if (drm_is_current_master(filp))
		return 0;

	return -EACCES;
}

static int amdgpu_ctx_init(struct amdgpu_device *adev,
			   enum drm_sched_priority priority,
			   struct drm_file *filp,
			   struct amdgpu_ctx *ctx)
=======
#include "amdgpu.h"

static int amdgpu_ctx_init(struct amdgpu_device *adev, struct amdgpu_ctx *ctx)
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
{
	unsigned i, j;
	int r;

<<<<<<< HEAD
	if (priority < 0 || priority >= DRM_SCHED_PRIORITY_MAX)
		return -EINVAL;

	r = amdgpu_ctx_priority_permit(filp, priority);
	if (r)
		return r;

=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	memset(ctx, 0, sizeof(*ctx));
	ctx->adev = adev;
	kref_init(&ctx->refcount);
	spin_lock_init(&ctx->ring_lock);
	ctx->fences = kcalloc(amdgpu_sched_jobs * AMDGPU_MAX_RINGS,
			      sizeof(struct dma_fence*), GFP_KERNEL);
	if (!ctx->fences)
		return -ENOMEM;

<<<<<<< HEAD
	mutex_init(&ctx->lock);

=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	for (i = 0; i < AMDGPU_MAX_RINGS; ++i) {
		ctx->rings[i].sequence = 1;
		ctx->rings[i].fences = &ctx->fences[amdgpu_sched_jobs * i];
	}

	ctx->reset_counter = atomic_read(&adev->gpu_reset_counter);
<<<<<<< HEAD
	ctx->reset_counter_query = ctx->reset_counter;
	ctx->vram_lost_counter = atomic_read(&adev->vram_lost_counter);
	ctx->init_priority = priority;
	ctx->override_priority = DRM_SCHED_PRIORITY_UNSET;
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	/* create context entity for each ring */
	for (i = 0; i < adev->num_rings; i++) {
		struct amdgpu_ring *ring = adev->rings[i];
<<<<<<< HEAD
		struct drm_sched_rq *rq;

		rq = &ring->sched.sched_rq[priority];
=======
		struct amd_sched_rq *rq;

		rq = &ring->sched.sched_rq[AMD_SCHED_PRIORITY_NORMAL];
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

		if (ring == &adev->gfx.kiq.ring)
			continue;

<<<<<<< HEAD
		r = drm_sched_entity_init(&ctx->rings[i].entity,
					  &rq, 1, &ctx->guilty);
=======
		r = amd_sched_entity_init(&ring->sched, &ctx->rings[i].entity,
					  rq, amdgpu_sched_jobs);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
		if (r)
			goto failed;
	}

	r = amdgpu_queue_mgr_init(adev, &ctx->queue_mgr);
	if (r)
		goto failed;

	return 0;

failed:
	for (j = 0; j < i; j++)
<<<<<<< HEAD
		drm_sched_entity_destroy(&ctx->rings[j].entity);
=======
		amd_sched_entity_fini(&adev->rings[j]->sched,
				      &ctx->rings[j].entity);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	kfree(ctx->fences);
	ctx->fences = NULL;
	return r;
}

<<<<<<< HEAD
static void amdgpu_ctx_fini(struct kref *ref)
{
	struct amdgpu_ctx *ctx = container_of(ref, struct amdgpu_ctx, refcount);
=======
static void amdgpu_ctx_fini(struct amdgpu_ctx *ctx)
{
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	struct amdgpu_device *adev = ctx->adev;
	unsigned i, j;

	if (!adev)
		return;

	for (i = 0; i < AMDGPU_MAX_RINGS; ++i)
		for (j = 0; j < amdgpu_sched_jobs; ++j)
			dma_fence_put(ctx->rings[i].fences[j]);
	kfree(ctx->fences);
	ctx->fences = NULL;

<<<<<<< HEAD
	amdgpu_queue_mgr_fini(adev, &ctx->queue_mgr);

	mutex_destroy(&ctx->lock);

	kfree(ctx);
=======
	for (i = 0; i < adev->num_rings; i++)
		amd_sched_entity_fini(&adev->rings[i]->sched,
				      &ctx->rings[i].entity);

	amdgpu_queue_mgr_fini(adev, &ctx->queue_mgr);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
}

static int amdgpu_ctx_alloc(struct amdgpu_device *adev,
			    struct amdgpu_fpriv *fpriv,
<<<<<<< HEAD
			    struct drm_file *filp,
			    enum drm_sched_priority priority,
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
			    uint32_t *id)
{
	struct amdgpu_ctx_mgr *mgr = &fpriv->ctx_mgr;
	struct amdgpu_ctx *ctx;
	int r;

	ctx = kmalloc(sizeof(*ctx), GFP_KERNEL);
	if (!ctx)
		return -ENOMEM;

	mutex_lock(&mgr->lock);
	r = idr_alloc(&mgr->ctx_handles, ctx, 1, 0, GFP_KERNEL);
	if (r < 0) {
		mutex_unlock(&mgr->lock);
		kfree(ctx);
		return r;
	}
<<<<<<< HEAD

	*id = (uint32_t)r;
	r = amdgpu_ctx_init(adev, priority, filp, ctx);
=======
	*id = (uint32_t)r;
	r = amdgpu_ctx_init(adev, ctx);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	if (r) {
		idr_remove(&mgr->ctx_handles, *id);
		*id = 0;
		kfree(ctx);
	}
	mutex_unlock(&mgr->lock);
	return r;
}

static void amdgpu_ctx_do_release(struct kref *ref)
{
	struct amdgpu_ctx *ctx;
<<<<<<< HEAD
	u32 i;

	ctx = container_of(ref, struct amdgpu_ctx, refcount);

	for (i = 0; i < ctx->adev->num_rings; i++) {

		if (ctx->adev->rings[i] == &ctx->adev->gfx.kiq.ring)
			continue;

		drm_sched_entity_destroy(&ctx->rings[i].entity);
	}

	amdgpu_ctx_fini(ref);
=======

	ctx = container_of(ref, struct amdgpu_ctx, refcount);

	amdgpu_ctx_fini(ctx);

	kfree(ctx);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
}

static int amdgpu_ctx_free(struct amdgpu_fpriv *fpriv, uint32_t id)
{
	struct amdgpu_ctx_mgr *mgr = &fpriv->ctx_mgr;
	struct amdgpu_ctx *ctx;

	mutex_lock(&mgr->lock);
	ctx = idr_remove(&mgr->ctx_handles, id);
	if (ctx)
		kref_put(&ctx->refcount, amdgpu_ctx_do_release);
	mutex_unlock(&mgr->lock);
	return ctx ? 0 : -EINVAL;
}

static int amdgpu_ctx_query(struct amdgpu_device *adev,
			    struct amdgpu_fpriv *fpriv, uint32_t id,
			    union drm_amdgpu_ctx_out *out)
{
	struct amdgpu_ctx *ctx;
	struct amdgpu_ctx_mgr *mgr;
	unsigned reset_counter;

	if (!fpriv)
		return -EINVAL;

	mgr = &fpriv->ctx_mgr;
	mutex_lock(&mgr->lock);
	ctx = idr_find(&mgr->ctx_handles, id);
	if (!ctx) {
		mutex_unlock(&mgr->lock);
		return -EINVAL;
	}

	/* TODO: these two are always zero */
	out->state.flags = 0x0;
	out->state.hangs = 0x0;

	/* determine if a GPU reset has occured since the last call */
	reset_counter = atomic_read(&adev->gpu_reset_counter);
	/* TODO: this should ideally return NO, GUILTY, or INNOCENT. */
<<<<<<< HEAD
	if (ctx->reset_counter_query == reset_counter)
		out->state.reset_status = AMDGPU_CTX_NO_RESET;
	else
		out->state.reset_status = AMDGPU_CTX_UNKNOWN_RESET;
	ctx->reset_counter_query = reset_counter;

	mutex_unlock(&mgr->lock);
	return 0;
}

static int amdgpu_ctx_query2(struct amdgpu_device *adev,
	struct amdgpu_fpriv *fpriv, uint32_t id,
	union drm_amdgpu_ctx_out *out)
{
	struct amdgpu_ctx *ctx;
	struct amdgpu_ctx_mgr *mgr;

	if (!fpriv)
		return -EINVAL;

	mgr = &fpriv->ctx_mgr;
	mutex_lock(&mgr->lock);
	ctx = idr_find(&mgr->ctx_handles, id);
	if (!ctx) {
		mutex_unlock(&mgr->lock);
		return -EINVAL;
	}

	out->state.flags = 0x0;
	out->state.hangs = 0x0;

	if (ctx->reset_counter != atomic_read(&adev->gpu_reset_counter))
		out->state.flags |= AMDGPU_CTX_QUERY2_FLAGS_RESET;

	if (ctx->vram_lost_counter != atomic_read(&adev->vram_lost_counter))
		out->state.flags |= AMDGPU_CTX_QUERY2_FLAGS_VRAMLOST;

	if (atomic_read(&ctx->guilty))
		out->state.flags |= AMDGPU_CTX_QUERY2_FLAGS_GUILTY;
=======
	if (ctx->reset_counter == reset_counter)
		out->state.reset_status = AMDGPU_CTX_NO_RESET;
	else
		out->state.reset_status = AMDGPU_CTX_UNKNOWN_RESET;
	ctx->reset_counter = reset_counter;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	mutex_unlock(&mgr->lock);
	return 0;
}

int amdgpu_ctx_ioctl(struct drm_device *dev, void *data,
		     struct drm_file *filp)
{
	int r;
	uint32_t id;
<<<<<<< HEAD
	enum drm_sched_priority priority;
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	union drm_amdgpu_ctx *args = data;
	struct amdgpu_device *adev = dev->dev_private;
	struct amdgpu_fpriv *fpriv = filp->driver_priv;

	r = 0;
	id = args->in.ctx_id;
<<<<<<< HEAD
	priority = amdgpu_to_sched_priority(args->in.priority);

	/* For backwards compatibility reasons, we need to accept
	 * ioctls with garbage in the priority field */
	if (priority == DRM_SCHED_PRIORITY_INVALID)
		priority = DRM_SCHED_PRIORITY_NORMAL;

	switch (args->in.op) {
	case AMDGPU_CTX_OP_ALLOC_CTX:
		r = amdgpu_ctx_alloc(adev, fpriv, filp, priority, &id);
=======

	switch (args->in.op) {
	case AMDGPU_CTX_OP_ALLOC_CTX:
		r = amdgpu_ctx_alloc(adev, fpriv, &id);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
		args->out.alloc.ctx_id = id;
		break;
	case AMDGPU_CTX_OP_FREE_CTX:
		r = amdgpu_ctx_free(fpriv, id);
		break;
	case AMDGPU_CTX_OP_QUERY_STATE:
		r = amdgpu_ctx_query(adev, fpriv, id, &args->out);
		break;
<<<<<<< HEAD
	case AMDGPU_CTX_OP_QUERY_STATE2:
		r = amdgpu_ctx_query2(adev, fpriv, id, &args->out);
		break;
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	default:
		return -EINVAL;
	}

	return r;
}

struct amdgpu_ctx *amdgpu_ctx_get(struct amdgpu_fpriv *fpriv, uint32_t id)
{
	struct amdgpu_ctx *ctx;
	struct amdgpu_ctx_mgr *mgr;

	if (!fpriv)
		return NULL;

	mgr = &fpriv->ctx_mgr;

	mutex_lock(&mgr->lock);
	ctx = idr_find(&mgr->ctx_handles, id);
	if (ctx)
		kref_get(&ctx->refcount);
	mutex_unlock(&mgr->lock);
	return ctx;
}

int amdgpu_ctx_put(struct amdgpu_ctx *ctx)
{
	if (ctx == NULL)
		return -EINVAL;

	kref_put(&ctx->refcount, amdgpu_ctx_do_release);
	return 0;
}

<<<<<<< HEAD
int amdgpu_ctx_add_fence(struct amdgpu_ctx *ctx, struct amdgpu_ring *ring,
			      struct dma_fence *fence, uint64_t* handler)
=======
uint64_t amdgpu_ctx_add_fence(struct amdgpu_ctx *ctx, struct amdgpu_ring *ring,
			      struct dma_fence *fence)
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
{
	struct amdgpu_ctx_ring *cring = & ctx->rings[ring->idx];
	uint64_t seq = cring->sequence;
	unsigned idx = 0;
	struct dma_fence *other = NULL;

	idx = seq & (amdgpu_sched_jobs - 1);
	other = cring->fences[idx];
<<<<<<< HEAD
	if (other)
		BUG_ON(!dma_fence_is_signaled(other));
=======
	if (other) {
		signed long r;
		r = dma_fence_wait_timeout(other, false, MAX_SCHEDULE_TIMEOUT);
		if (r < 0)
			DRM_ERROR("Error (%ld) waiting for fence!\n", r);
	}
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	dma_fence_get(fence);

	spin_lock(&ctx->ring_lock);
	cring->fences[idx] = fence;
	cring->sequence++;
	spin_unlock(&ctx->ring_lock);

	dma_fence_put(other);
<<<<<<< HEAD
	if (handler)
		*handler = seq;

	return 0;
=======

	return seq;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
}

struct dma_fence *amdgpu_ctx_get_fence(struct amdgpu_ctx *ctx,
				       struct amdgpu_ring *ring, uint64_t seq)
{
	struct amdgpu_ctx_ring *cring = & ctx->rings[ring->idx];
	struct dma_fence *fence;

	spin_lock(&ctx->ring_lock);

	if (seq == ~0ull)
		seq = ctx->rings[ring->idx].sequence - 1;

	if (seq >= cring->sequence) {
		spin_unlock(&ctx->ring_lock);
		return ERR_PTR(-EINVAL);
	}


	if (seq + amdgpu_sched_jobs < cring->sequence) {
		spin_unlock(&ctx->ring_lock);
		return NULL;
	}

	fence = dma_fence_get(cring->fences[seq & (amdgpu_sched_jobs - 1)]);
	spin_unlock(&ctx->ring_lock);

	return fence;
}

<<<<<<< HEAD
void amdgpu_ctx_priority_override(struct amdgpu_ctx *ctx,
				  enum drm_sched_priority priority)
{
	int i;
	struct amdgpu_device *adev = ctx->adev;
	struct drm_sched_rq *rq;
	struct drm_sched_entity *entity;
	struct amdgpu_ring *ring;
	enum drm_sched_priority ctx_prio;

	ctx->override_priority = priority;

	ctx_prio = (ctx->override_priority == DRM_SCHED_PRIORITY_UNSET) ?
			ctx->init_priority : ctx->override_priority;

	for (i = 0; i < adev->num_rings; i++) {
		ring = adev->rings[i];
		entity = &ctx->rings[i].entity;
		rq = &ring->sched.sched_rq[ctx_prio];

		if (ring->funcs->type == AMDGPU_RING_TYPE_KIQ)
			continue;

		drm_sched_entity_set_rq(entity, rq);
	}
}

int amdgpu_ctx_wait_prev_fence(struct amdgpu_ctx *ctx, unsigned ring_id)
{
	struct amdgpu_ctx_ring *cring = &ctx->rings[ring_id];
	unsigned idx = cring->sequence & (amdgpu_sched_jobs - 1);
	struct dma_fence *other = cring->fences[idx];

	if (other) {
		signed long r;
		r = dma_fence_wait(other, true);
		if (r < 0) {
			if (r != -ERESTARTSYS)
				DRM_ERROR("Error (%ld) waiting for fence!\n", r);

			return r;
		}
	}

	return 0;
}

=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
void amdgpu_ctx_mgr_init(struct amdgpu_ctx_mgr *mgr)
{
	mutex_init(&mgr->lock);
	idr_init(&mgr->ctx_handles);
}

<<<<<<< HEAD
void amdgpu_ctx_mgr_entity_flush(struct amdgpu_ctx_mgr *mgr)
{
	struct amdgpu_ctx *ctx;
	struct idr *idp;
	uint32_t id, i;
	long max_wait = MAX_WAIT_SCHED_ENTITY_Q_EMPTY;

	idp = &mgr->ctx_handles;

	mutex_lock(&mgr->lock);
	idr_for_each_entry(idp, ctx, id) {

		if (!ctx->adev) {
			mutex_unlock(&mgr->lock);
			return;
		}

		for (i = 0; i < ctx->adev->num_rings; i++) {

			if (ctx->adev->rings[i] == &ctx->adev->gfx.kiq.ring)
				continue;

			max_wait = drm_sched_entity_flush(&ctx->rings[i].entity,
							  max_wait);
		}
	}
	mutex_unlock(&mgr->lock);
}

void amdgpu_ctx_mgr_entity_fini(struct amdgpu_ctx_mgr *mgr)
{
	struct amdgpu_ctx *ctx;
	struct idr *idp;
	uint32_t id, i;

	idp = &mgr->ctx_handles;

	idr_for_each_entry(idp, ctx, id) {

		if (!ctx->adev)
			return;

		for (i = 0; i < ctx->adev->num_rings; i++) {

			if (ctx->adev->rings[i] == &ctx->adev->gfx.kiq.ring)
				continue;

			if (kref_read(&ctx->refcount) == 1)
				drm_sched_entity_fini(&ctx->rings[i].entity);
			else
				DRM_ERROR("ctx %p is still alive\n", ctx);
		}
	}
}

=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
void amdgpu_ctx_mgr_fini(struct amdgpu_ctx_mgr *mgr)
{
	struct amdgpu_ctx *ctx;
	struct idr *idp;
	uint32_t id;

<<<<<<< HEAD
	amdgpu_ctx_mgr_entity_fini(mgr);

	idp = &mgr->ctx_handles;

	idr_for_each_entry(idp, ctx, id) {
		if (kref_put(&ctx->refcount, amdgpu_ctx_fini) != 1)
=======
	idp = &mgr->ctx_handles;

	idr_for_each_entry(idp, ctx, id) {
		if (kref_put(&ctx->refcount, amdgpu_ctx_do_release) != 1)
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
			DRM_ERROR("ctx %p is still alive\n", ctx);
	}

	idr_destroy(&mgr->ctx_handles);
	mutex_destroy(&mgr->lock);
}
