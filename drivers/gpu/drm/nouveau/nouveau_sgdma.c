// SPDX-License-Identifier: GPL-2.0
#include <linux/pagemap.h>
#include <linux/slab.h>

#include "nouveau_drv.h"
<<<<<<< HEAD
#include "nouveau_mem.h"
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
#include "nouveau_ttm.h"

struct nouveau_sgdma_be {
	/* this has to be the first field so populate/unpopulated in
	 * nouve_bo.c works properly, otherwise have to move them here
	 */
	struct ttm_dma_tt ttm;
<<<<<<< HEAD
	struct nouveau_mem *mem;
=======
	struct nvkm_mem *node;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
};

static void
nouveau_sgdma_destroy(struct ttm_tt *ttm)
{
	struct nouveau_sgdma_be *nvbe = (struct nouveau_sgdma_be *)ttm;

	if (ttm) {
		ttm_dma_tt_fini(&nvbe->ttm);
		kfree(nvbe);
	}
}

static int
nv04_sgdma_bind(struct ttm_tt *ttm, struct ttm_mem_reg *reg)
{
	struct nouveau_sgdma_be *nvbe = (struct nouveau_sgdma_be *)ttm;
<<<<<<< HEAD
	struct nouveau_mem *mem = nouveau_mem(reg);
	int ret;

	ret = nouveau_mem_host(reg, &nvbe->ttm);
	if (ret)
		return ret;

	ret = nouveau_mem_map(mem, &mem->cli->vmm.vmm, &mem->vma[0]);
	if (ret) {
		nouveau_mem_fini(mem);
		return ret;
	}

	nvbe->mem = mem;
=======
	struct nvkm_mem *node = reg->mm_node;

	if (ttm->sg) {
		node->sg    = ttm->sg;
		node->pages = NULL;
	} else {
		node->sg    = NULL;
		node->pages = nvbe->ttm.dma_address;
	}
	node->size = (reg->num_pages << PAGE_SHIFT) >> 12;

	nvkm_vm_map(&node->vma[0], node);
	nvbe->node = node;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	return 0;
}

static int
nv04_sgdma_unbind(struct ttm_tt *ttm)
{
	struct nouveau_sgdma_be *nvbe = (struct nouveau_sgdma_be *)ttm;
<<<<<<< HEAD
	nouveau_mem_fini(nvbe->mem);
=======
	nvkm_vm_unmap(&nvbe->node->vma[0]);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	return 0;
}

static struct ttm_backend_func nv04_sgdma_backend = {
	.bind			= nv04_sgdma_bind,
	.unbind			= nv04_sgdma_unbind,
	.destroy		= nouveau_sgdma_destroy
};

static int
nv50_sgdma_bind(struct ttm_tt *ttm, struct ttm_mem_reg *reg)
{
	struct nouveau_sgdma_be *nvbe = (struct nouveau_sgdma_be *)ttm;
<<<<<<< HEAD
	struct nouveau_mem *mem = nouveau_mem(reg);
	int ret;

	ret = nouveau_mem_host(reg, &nvbe->ttm);
	if (ret)
		return ret;

	nvbe->mem = mem;
=======
	struct nvkm_mem *node = reg->mm_node;

	/* noop: bound in move_notify() */
	if (ttm->sg) {
		node->sg    = ttm->sg;
		node->pages = NULL;
	} else {
		node->sg    = NULL;
		node->pages = nvbe->ttm.dma_address;
	}
	node->size = (reg->num_pages << PAGE_SHIFT) >> 12;
	return 0;
}

static int
nv50_sgdma_unbind(struct ttm_tt *ttm)
{
	/* noop: unbound in move_notify() */
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	return 0;
}

static struct ttm_backend_func nv50_sgdma_backend = {
	.bind			= nv50_sgdma_bind,
<<<<<<< HEAD
	.unbind			= nv04_sgdma_unbind,
=======
	.unbind			= nv50_sgdma_unbind,
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	.destroy		= nouveau_sgdma_destroy
};

struct ttm_tt *
<<<<<<< HEAD
nouveau_sgdma_create_ttm(struct ttm_buffer_object *bo, uint32_t page_flags)
{
	struct nouveau_drm *drm = nouveau_bdev(bo->bdev);
=======
nouveau_sgdma_create_ttm(struct ttm_bo_device *bdev,
			 unsigned long size, uint32_t page_flags,
			 struct page *dummy_read_page)
{
	struct nouveau_drm *drm = nouveau_bdev(bdev);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	struct nouveau_sgdma_be *nvbe;

	nvbe = kzalloc(sizeof(*nvbe), GFP_KERNEL);
	if (!nvbe)
		return NULL;

	if (drm->client.device.info.family < NV_DEVICE_INFO_V0_TESLA)
		nvbe->ttm.ttm.func = &nv04_sgdma_backend;
	else
		nvbe->ttm.ttm.func = &nv50_sgdma_backend;

<<<<<<< HEAD
	if (ttm_dma_tt_init(&nvbe->ttm, bo, page_flags))
=======
	if (ttm_dma_tt_init(&nvbe->ttm, bdev, size, page_flags, dummy_read_page))
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
		/*
		 * A failing ttm_dma_tt_init() will call ttm_tt_destroy()
		 * and thus our nouveau_sgdma_destroy() hook, so we don't need
		 * to free nvbe here.
		 */
		return NULL;
	return &nvbe->ttm.ttm;
}
