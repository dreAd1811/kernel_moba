<<<<<<< HEAD
// SPDX-License-Identifier: GPL-2.0 OR MIT
/*
 * Copyright (c) 2007-2008 Tungsten Graphics, Inc., Cedar Park, TX., USA,
 * Copyright (c) 2009 VMware, Inc., Palo Alto, CA., USA,
=======
/*
 * Copyright (c) 2007-2008 Tungsten Graphics, Inc., Cedar Park, TX., USA,
 * All Rights Reserved.
 * Copyright (c) 2009 VMware, Inc., Palo Alto, CA., USA,
 * All Rights Reserved.
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sub license,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial portions
 * of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL
 * THE COPYRIGHT HOLDERS, AUTHORS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
 * USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
<<<<<<< HEAD
#include "nouveau_drv.h"
#include "nouveau_gem.h"
#include "nouveau_mem.h"
#include "nouveau_ttm.h"
=======

#include "nouveau_drv.h"
#include "nouveau_ttm.h"
#include "nouveau_gem.h"
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

#include <drm/drm_legacy.h>

#include <core/tegra.h>

static int
<<<<<<< HEAD
nouveau_manager_init(struct ttm_mem_type_manager *man, unsigned long psize)
{
=======
nouveau_vram_manager_init(struct ttm_mem_type_manager *man, unsigned long psize)
{
	struct nouveau_drm *drm = nouveau_bdev(man->bdev);
	struct nvkm_fb *fb = nvxx_fb(&drm->client.device);
	man->priv = fb;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	return 0;
}

static int
<<<<<<< HEAD
nouveau_manager_fini(struct ttm_mem_type_manager *man)
{
	return 0;
}

static void
nouveau_manager_del(struct ttm_mem_type_manager *man, struct ttm_mem_reg *reg)
{
	nouveau_mem_del(reg);
}

static void
nouveau_manager_debug(struct ttm_mem_type_manager *man,
		      struct drm_printer *printer)
{
=======
nouveau_vram_manager_fini(struct ttm_mem_type_manager *man)
{
	man->priv = NULL;
	return 0;
}

static inline void
nvkm_mem_node_cleanup(struct nvkm_mem *node)
{
	if (node->vma[0].node) {
		nvkm_vm_unmap(&node->vma[0]);
		nvkm_vm_put(&node->vma[0]);
	}

	if (node->vma[1].node) {
		nvkm_vm_unmap(&node->vma[1]);
		nvkm_vm_put(&node->vma[1]);
	}
}

static void
nouveau_vram_manager_del(struct ttm_mem_type_manager *man,
			 struct ttm_mem_reg *reg)
{
	struct nouveau_drm *drm = nouveau_bdev(man->bdev);
	struct nvkm_ram *ram = nvxx_fb(&drm->client.device)->ram;
	nvkm_mem_node_cleanup(reg->mm_node);
	ram->func->put(ram, (struct nvkm_mem **)&reg->mm_node);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
}

static int
nouveau_vram_manager_new(struct ttm_mem_type_manager *man,
			 struct ttm_buffer_object *bo,
			 const struct ttm_place *place,
			 struct ttm_mem_reg *reg)
{
<<<<<<< HEAD
	struct nouveau_bo *nvbo = nouveau_bo(bo);
	struct nouveau_drm *drm = nouveau_bdev(bo->bdev);
	struct nouveau_mem *mem;
=======
	struct nouveau_drm *drm = nouveau_bdev(man->bdev);
	struct nvkm_ram *ram = nvxx_fb(&drm->client.device)->ram;
	struct nouveau_bo *nvbo = nouveau_bo(bo);
	struct nvkm_mem *node;
	u32 size_nc = 0;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	int ret;

	if (drm->client.device.info.ram_size == 0)
		return -ENOMEM;

<<<<<<< HEAD
	ret = nouveau_mem_new(&drm->master, nvbo->kind, nvbo->comp, reg);
	mem = nouveau_mem(reg);
	if (ret)
		return ret;

	ret = nouveau_mem_vram(reg, nvbo->contig, nvbo->page);
	if (ret) {
		nouveau_mem_del(reg);
		if (ret == -ENOSPC) {
			reg->mm_node = NULL;
			return 0;
		}
		return ret;
	}

=======
	if (nvbo->tile_flags & NOUVEAU_GEM_TILE_NONCONTIG)
		size_nc = 1 << nvbo->page_shift;

	ret = ram->func->get(ram, reg->num_pages << PAGE_SHIFT,
			     reg->page_alignment << PAGE_SHIFT, size_nc,
			     (nvbo->tile_flags >> 8) & 0x3ff, &node);
	if (ret) {
		reg->mm_node = NULL;
		return (ret == -ENOSPC) ? 0 : ret;
	}

	node->page_shift = nvbo->page_shift;

	reg->mm_node = node;
	reg->start   = node->offset >> PAGE_SHIFT;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	return 0;
}

const struct ttm_mem_type_manager_func nouveau_vram_manager = {
<<<<<<< HEAD
	.init = nouveau_manager_init,
	.takedown = nouveau_manager_fini,
	.get_node = nouveau_vram_manager_new,
	.put_node = nouveau_manager_del,
	.debug = nouveau_manager_debug,
};

static int
=======
	.init = nouveau_vram_manager_init,
	.takedown = nouveau_vram_manager_fini,
	.get_node = nouveau_vram_manager_new,
	.put_node = nouveau_vram_manager_del,
};

static int
nouveau_gart_manager_init(struct ttm_mem_type_manager *man, unsigned long psize)
{
	return 0;
}

static int
nouveau_gart_manager_fini(struct ttm_mem_type_manager *man)
{
	return 0;
}

static void
nouveau_gart_manager_del(struct ttm_mem_type_manager *man,
			 struct ttm_mem_reg *reg)
{
	nvkm_mem_node_cleanup(reg->mm_node);
	kfree(reg->mm_node);
	reg->mm_node = NULL;
}

static int
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
nouveau_gart_manager_new(struct ttm_mem_type_manager *man,
			 struct ttm_buffer_object *bo,
			 const struct ttm_place *place,
			 struct ttm_mem_reg *reg)
{
<<<<<<< HEAD
	struct nouveau_bo *nvbo = nouveau_bo(bo);
	struct nouveau_drm *drm = nouveau_bdev(bo->bdev);
	struct nouveau_mem *mem;
	int ret;

	ret = nouveau_mem_new(&drm->master, nvbo->kind, nvbo->comp, reg);
	mem = nouveau_mem(reg);
	if (ret)
		return ret;

	reg->start = 0;
	return 0;
}

const struct ttm_mem_type_manager_func nouveau_gart_manager = {
	.init = nouveau_manager_init,
	.takedown = nouveau_manager_fini,
	.get_node = nouveau_gart_manager_new,
	.put_node = nouveau_manager_del,
	.debug = nouveau_manager_debug
};

=======
	struct nouveau_drm *drm = nouveau_bdev(bo->bdev);
	struct nouveau_bo *nvbo = nouveau_bo(bo);
	struct nvkm_mem *node;

	node = kzalloc(sizeof(*node), GFP_KERNEL);
	if (!node)
		return -ENOMEM;

	node->page_shift = 12;

	switch (drm->client.device.info.family) {
	case NV_DEVICE_INFO_V0_TNT:
	case NV_DEVICE_INFO_V0_CELSIUS:
	case NV_DEVICE_INFO_V0_KELVIN:
	case NV_DEVICE_INFO_V0_RANKINE:
	case NV_DEVICE_INFO_V0_CURIE:
		break;
	case NV_DEVICE_INFO_V0_TESLA:
		if (drm->client.device.info.chipset != 0x50)
			node->memtype = (nvbo->tile_flags & 0x7f00) >> 8;
		break;
	case NV_DEVICE_INFO_V0_FERMI:
	case NV_DEVICE_INFO_V0_KEPLER:
	case NV_DEVICE_INFO_V0_MAXWELL:
	case NV_DEVICE_INFO_V0_PASCAL:
		node->memtype = (nvbo->tile_flags & 0xff00) >> 8;
		break;
	default:
		NV_WARN(drm, "%s: unhandled family type %x\n", __func__,
			drm->client.device.info.family);
		break;
	}

	reg->mm_node = node;
	reg->start   = 0;
	return 0;
}

static void
nouveau_gart_manager_debug(struct ttm_mem_type_manager *man,
			   struct drm_printer *printer)
{
}

const struct ttm_mem_type_manager_func nouveau_gart_manager = {
	.init = nouveau_gart_manager_init,
	.takedown = nouveau_gart_manager_fini,
	.get_node = nouveau_gart_manager_new,
	.put_node = nouveau_gart_manager_del,
	.debug = nouveau_gart_manager_debug
};

/*XXX*/
#include <subdev/mmu/nv04.h>
static int
nv04_gart_manager_init(struct ttm_mem_type_manager *man, unsigned long psize)
{
	struct nouveau_drm *drm = nouveau_bdev(man->bdev);
	struct nvkm_mmu *mmu = nvxx_mmu(&drm->client.device);
	struct nv04_mmu *priv = (void *)mmu;
	struct nvkm_vm *vm = NULL;
	nvkm_vm_ref(priv->vm, &vm, NULL);
	man->priv = vm;
	return 0;
}

static int
nv04_gart_manager_fini(struct ttm_mem_type_manager *man)
{
	struct nvkm_vm *vm = man->priv;
	nvkm_vm_ref(NULL, &vm, NULL);
	man->priv = NULL;
	return 0;
}

static void
nv04_gart_manager_del(struct ttm_mem_type_manager *man, struct ttm_mem_reg *reg)
{
	struct nvkm_mem *node = reg->mm_node;
	if (node->vma[0].node)
		nvkm_vm_put(&node->vma[0]);
	kfree(reg->mm_node);
	reg->mm_node = NULL;
}

>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
static int
nv04_gart_manager_new(struct ttm_mem_type_manager *man,
		      struct ttm_buffer_object *bo,
		      const struct ttm_place *place,
		      struct ttm_mem_reg *reg)
{
<<<<<<< HEAD
	struct nouveau_bo *nvbo = nouveau_bo(bo);
	struct nouveau_drm *drm = nouveau_bdev(bo->bdev);
	struct nouveau_mem *mem;
	int ret;

	ret = nouveau_mem_new(&drm->master, nvbo->kind, nvbo->comp, reg);
	mem = nouveau_mem(reg);
	if (ret)
		return ret;

	ret = nvif_vmm_get(&mem->cli->vmm.vmm, PTES, false, 12, 0,
			   reg->num_pages << PAGE_SHIFT, &mem->vma[0]);
	if (ret) {
		nouveau_mem_del(reg);
		if (ret == -ENOSPC) {
			reg->mm_node = NULL;
			return 0;
		}
		return ret;
	}

	reg->start = mem->vma[0].addr >> PAGE_SHIFT;
	return 0;
}

const struct ttm_mem_type_manager_func nv04_gart_manager = {
	.init = nouveau_manager_init,
	.takedown = nouveau_manager_fini,
	.get_node = nv04_gart_manager_new,
	.put_node = nouveau_manager_del,
	.debug = nouveau_manager_debug
=======
	struct nvkm_mem *node;
	int ret;

	node = kzalloc(sizeof(*node), GFP_KERNEL);
	if (!node)
		return -ENOMEM;

	node->page_shift = 12;

	ret = nvkm_vm_get(man->priv, reg->num_pages << 12, node->page_shift,
			  NV_MEM_ACCESS_RW, &node->vma[0]);
	if (ret) {
		kfree(node);
		return ret;
	}

	reg->mm_node = node;
	reg->start   = node->vma[0].offset >> PAGE_SHIFT;
	return 0;
}

static void
nv04_gart_manager_debug(struct ttm_mem_type_manager *man,
			struct drm_printer *printer)
{
}

const struct ttm_mem_type_manager_func nv04_gart_manager = {
	.init = nv04_gart_manager_init,
	.takedown = nv04_gart_manager_fini,
	.get_node = nv04_gart_manager_new,
	.put_node = nv04_gart_manager_del,
	.debug = nv04_gart_manager_debug
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
};

int
nouveau_ttm_mmap(struct file *filp, struct vm_area_struct *vma)
{
	struct drm_file *file_priv = filp->private_data;
	struct nouveau_drm *drm = nouveau_drm(file_priv->minor->dev);

	if (unlikely(vma->vm_pgoff < DRM_FILE_PAGE_OFFSET))
#if defined(CONFIG_NOUVEAU_LEGACY_CTX_SUPPORT)
		return drm_legacy_mmap(filp, vma);
#else
		return -EINVAL;
#endif

	return ttm_bo_mmap(filp, vma, &drm->ttm.bdev);
}

static int
nouveau_ttm_mem_global_init(struct drm_global_reference *ref)
{
	return ttm_mem_global_init(ref->object);
}

static void
nouveau_ttm_mem_global_release(struct drm_global_reference *ref)
{
	ttm_mem_global_release(ref->object);
}

int
nouveau_ttm_global_init(struct nouveau_drm *drm)
{
	struct drm_global_reference *global_ref;
	int ret;

	global_ref = &drm->ttm.mem_global_ref;
	global_ref->global_type = DRM_GLOBAL_TTM_MEM;
	global_ref->size = sizeof(struct ttm_mem_global);
	global_ref->init = &nouveau_ttm_mem_global_init;
	global_ref->release = &nouveau_ttm_mem_global_release;

	ret = drm_global_item_ref(global_ref);
	if (unlikely(ret != 0)) {
		DRM_ERROR("Failed setting up TTM memory accounting\n");
		drm->ttm.mem_global_ref.release = NULL;
		return ret;
	}

	drm->ttm.bo_global_ref.mem_glob = global_ref->object;
	global_ref = &drm->ttm.bo_global_ref.ref;
	global_ref->global_type = DRM_GLOBAL_TTM_BO;
	global_ref->size = sizeof(struct ttm_bo_global);
	global_ref->init = &ttm_bo_global_init;
	global_ref->release = &ttm_bo_global_release;

	ret = drm_global_item_ref(global_ref);
	if (unlikely(ret != 0)) {
		DRM_ERROR("Failed setting up TTM BO subsystem\n");
		drm_global_item_unref(&drm->ttm.mem_global_ref);
		drm->ttm.mem_global_ref.release = NULL;
		return ret;
	}

	return 0;
}

void
nouveau_ttm_global_release(struct nouveau_drm *drm)
{
	if (drm->ttm.mem_global_ref.release == NULL)
		return;

	drm_global_item_unref(&drm->ttm.bo_global_ref.ref);
	drm_global_item_unref(&drm->ttm.mem_global_ref);
	drm->ttm.mem_global_ref.release = NULL;
}

<<<<<<< HEAD
static int
nouveau_ttm_init_host(struct nouveau_drm *drm, u8 kind)
{
	struct nvif_mmu *mmu = &drm->client.mmu;
	int typei;

	typei = nvif_mmu_type(mmu, NVIF_MEM_HOST | NVIF_MEM_MAPPABLE |
					    kind | NVIF_MEM_COHERENT);
	if (typei < 0)
		return -ENOSYS;

	drm->ttm.type_host[!!kind] = typei;

	typei = nvif_mmu_type(mmu, NVIF_MEM_HOST | NVIF_MEM_MAPPABLE | kind);
	if (typei < 0)
		return -ENOSYS;

	drm->ttm.type_ncoh[!!kind] = typei;
	return 0;
}

=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
int
nouveau_ttm_init(struct nouveau_drm *drm)
{
	struct nvkm_device *device = nvxx_device(&drm->client.device);
	struct nvkm_pci *pci = device->pci;
<<<<<<< HEAD
	struct nvif_mmu *mmu = &drm->client.mmu;
	struct drm_device *dev = drm->dev;
	int typei, ret;

	ret = nouveau_ttm_init_host(drm, 0);
	if (ret)
		return ret;

	if (drm->client.device.info.family >= NV_DEVICE_INFO_V0_TESLA &&
	    drm->client.device.info.chipset != 0x50) {
		ret = nouveau_ttm_init_host(drm, NVIF_MEM_KIND);
		if (ret)
			return ret;
	}

	if (drm->client.device.info.platform != NV_DEVICE_INFO_V0_SOC &&
	    drm->client.device.info.family >= NV_DEVICE_INFO_V0_TESLA) {
		typei = nvif_mmu_type(mmu, NVIF_MEM_VRAM | NVIF_MEM_MAPPABLE |
					   NVIF_MEM_KIND |
					   NVIF_MEM_COMP |
					   NVIF_MEM_DISP);
		if (typei < 0)
			return -ENOSYS;

		drm->ttm.type_vram = typei;
	} else {
		drm->ttm.type_vram = -1;
	}
=======
	struct drm_device *dev = drm->dev;
	u8 bits;
	int ret;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	if (pci && pci->agp.bridge) {
		drm->agp.bridge = pci->agp.bridge;
		drm->agp.base = pci->agp.base;
		drm->agp.size = pci->agp.size;
		drm->agp.cma = pci->agp.cma;
	}

<<<<<<< HEAD
=======
	bits = nvxx_mmu(&drm->client.device)->dma_bits;
	if (nvxx_device(&drm->client.device)->func->pci) {
		if (drm->agp.bridge)
			bits = 32;
	} else if (device->func->tegra) {
		struct nvkm_device_tegra *tegra = device->func->tegra(device);

		/*
		 * If the platform can use a IOMMU, then the addressable DMA
		 * space is constrained by the IOMMU bit
		 */
		if (tegra->func->iommu_bit)
			bits = min(bits, tegra->func->iommu_bit);

	}

	ret = dma_set_mask(dev->dev, DMA_BIT_MASK(bits));
	if (ret && bits != 32) {
		bits = 32;
		ret = dma_set_mask(dev->dev, DMA_BIT_MASK(bits));
	}
	if (ret)
		return ret;

	ret = dma_set_coherent_mask(dev->dev, DMA_BIT_MASK(bits));
	if (ret)
		dma_set_coherent_mask(dev->dev, DMA_BIT_MASK(32));

>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	ret = nouveau_ttm_global_init(drm);
	if (ret)
		return ret;

	ret = ttm_bo_device_init(&drm->ttm.bdev,
				  drm->ttm.bo_global_ref.ref.object,
				  &nouveau_bo_driver,
				  dev->anon_inode->i_mapping,
				  DRM_FILE_PAGE_OFFSET,
<<<<<<< HEAD
				  drm->client.mmu.dmabits <= 32 ? true : false);
=======
				  bits <= 32 ? true : false);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	if (ret) {
		NV_ERROR(drm, "error initialising bo driver, %d\n", ret);
		return ret;
	}

	/* VRAM init */
	drm->gem.vram_available = drm->client.device.info.ram_user;

	arch_io_reserve_memtype_wc(device->func->resource_addr(device, 1),
				   device->func->resource_size(device, 1));

	ret = ttm_bo_init_mm(&drm->ttm.bdev, TTM_PL_VRAM,
			      drm->gem.vram_available >> PAGE_SHIFT);
	if (ret) {
		NV_ERROR(drm, "VRAM mm init failed, %d\n", ret);
		return ret;
	}

	drm->ttm.mtrr = arch_phys_wc_add(device->func->resource_addr(device, 1),
					 device->func->resource_size(device, 1));

	/* GART init */
	if (!drm->agp.bridge) {
<<<<<<< HEAD
		drm->gem.gart_available = drm->client.vmm.vmm.limit;
=======
		drm->gem.gart_available = nvxx_mmu(&drm->client.device)->limit;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	} else {
		drm->gem.gart_available = drm->agp.size;
	}

	ret = ttm_bo_init_mm(&drm->ttm.bdev, TTM_PL_TT,
			      drm->gem.gart_available >> PAGE_SHIFT);
	if (ret) {
		NV_ERROR(drm, "GART mm init failed, %d\n", ret);
		return ret;
	}

	NV_INFO(drm, "VRAM: %d MiB\n", (u32)(drm->gem.vram_available >> 20));
	NV_INFO(drm, "GART: %d MiB\n", (u32)(drm->gem.gart_available >> 20));
	return 0;
}

void
nouveau_ttm_fini(struct nouveau_drm *drm)
{
	struct nvkm_device *device = nvxx_device(&drm->client.device);

	ttm_bo_clean_mm(&drm->ttm.bdev, TTM_PL_VRAM);
	ttm_bo_clean_mm(&drm->ttm.bdev, TTM_PL_TT);

	ttm_bo_device_release(&drm->ttm.bdev);

	nouveau_ttm_global_release(drm);

	arch_phys_wc_del(drm->ttm.mtrr);
	drm->ttm.mtrr = 0;
	arch_io_free_memtype_wc(device->func->resource_addr(device, 1),
				device->func->resource_size(device, 1));

}
