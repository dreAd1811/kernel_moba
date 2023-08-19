<<<<<<< HEAD
// SPDX-License-Identifier: GPL-2.0
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

#include "common.xml.h"
#include "etnaviv_cmdbuf.h"
#include "etnaviv_drv.h"
#include "etnaviv_gem.h"
#include "etnaviv_gpu.h"
#include "etnaviv_iommu.h"
#include "etnaviv_mmu.h"

<<<<<<< HEAD
static void etnaviv_domain_unmap(struct etnaviv_iommu_domain *domain,
				 unsigned long iova, size_t size)
{
	size_t unmapped_page, unmapped = 0;
	size_t pgsize = SZ_4K;

	if (!IS_ALIGNED(iova | size, pgsize)) {
		pr_err("unaligned: iova 0x%lx size 0x%zx min_pagesz 0x%zx\n",
		       iova, size, pgsize);
		return;
	}

	while (unmapped < size) {
		unmapped_page = domain->ops->unmap(domain, iova, pgsize);
		if (!unmapped_page)
			break;

		iova += unmapped_page;
		unmapped += unmapped_page;
	}
}

static int etnaviv_domain_map(struct etnaviv_iommu_domain *domain,
			      unsigned long iova, phys_addr_t paddr,
			      size_t size, int prot)
{
	unsigned long orig_iova = iova;
	size_t pgsize = SZ_4K;
	size_t orig_size = size;
	int ret = 0;

	if (!IS_ALIGNED(iova | paddr | size, pgsize)) {
		pr_err("unaligned: iova 0x%lx pa %pa size 0x%zx min_pagesz 0x%zx\n",
		       iova, &paddr, size, pgsize);
		return -EINVAL;
	}

	while (size) {
		ret = domain->ops->map(domain, iova, paddr, pgsize, prot);
		if (ret)
			break;

		iova += pgsize;
		paddr += pgsize;
		size -= pgsize;
	}

	/* unroll mapping in case something went wrong */
	if (ret)
		etnaviv_domain_unmap(domain, orig_iova, orig_size - size);

	return ret;
}

static int etnaviv_iommu_map(struct etnaviv_iommu *iommu, u32 iova,
			     struct sg_table *sgt, unsigned len, int prot)
{
	struct etnaviv_iommu_domain *domain = iommu->domain;
=======
static int etnaviv_fault_handler(struct iommu_domain *iommu, struct device *dev,
		unsigned long iova, int flags, void *arg)
{
	DBG("*** fault: iova=%08lx, flags=%d", iova, flags);
	return 0;
}

int etnaviv_iommu_map(struct etnaviv_iommu *iommu, u32 iova,
		struct sg_table *sgt, unsigned len, int prot)
{
	struct iommu_domain *domain = iommu->domain;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	struct scatterlist *sg;
	unsigned int da = iova;
	unsigned int i, j;
	int ret;

	if (!domain || !sgt)
		return -EINVAL;

	for_each_sg(sgt->sgl, sg, sgt->nents, i) {
		u32 pa = sg_dma_address(sg) - sg->offset;
		size_t bytes = sg_dma_len(sg) + sg->offset;

		VERB("map[%d]: %08x %08x(%zx)", i, iova, pa, bytes);

<<<<<<< HEAD
		ret = etnaviv_domain_map(domain, da, pa, bytes, prot);
=======
		ret = iommu_map(domain, da, pa, bytes, prot);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
		if (ret)
			goto fail;

		da += bytes;
	}

	return 0;

fail:
	da = iova;

	for_each_sg(sgt->sgl, sg, i, j) {
		size_t bytes = sg_dma_len(sg) + sg->offset;

<<<<<<< HEAD
		etnaviv_domain_unmap(domain, da, bytes);
=======
		iommu_unmap(domain, da, bytes);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
		da += bytes;
	}
	return ret;
}

<<<<<<< HEAD
static void etnaviv_iommu_unmap(struct etnaviv_iommu *iommu, u32 iova,
				struct sg_table *sgt, unsigned len)
{
	struct etnaviv_iommu_domain *domain = iommu->domain;
=======
int etnaviv_iommu_unmap(struct etnaviv_iommu *iommu, u32 iova,
		struct sg_table *sgt, unsigned len)
{
	struct iommu_domain *domain = iommu->domain;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	struct scatterlist *sg;
	unsigned int da = iova;
	int i;

	for_each_sg(sgt->sgl, sg, sgt->nents, i) {
		size_t bytes = sg_dma_len(sg) + sg->offset;
<<<<<<< HEAD

		etnaviv_domain_unmap(domain, da, bytes);
=======
		size_t unmapped;

		unmapped = iommu_unmap(domain, da, bytes);
		if (unmapped < bytes)
			return unmapped;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

		VERB("unmap[%d]: %08x(%zx)", i, iova, bytes);

		BUG_ON(!PAGE_ALIGNED(bytes));

		da += bytes;
	}
<<<<<<< HEAD
=======

	return 0;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
}

static void etnaviv_iommu_remove_mapping(struct etnaviv_iommu *mmu,
	struct etnaviv_vram_mapping *mapping)
{
	struct etnaviv_gem_object *etnaviv_obj = mapping->object;

	etnaviv_iommu_unmap(mmu, mapping->vram_node.start,
			    etnaviv_obj->sgt, etnaviv_obj->base.size);
	drm_mm_remove_node(&mapping->vram_node);
}

static int etnaviv_iommu_find_iova(struct etnaviv_iommu *mmu,
				   struct drm_mm_node *node, size_t size)
{
	struct etnaviv_vram_mapping *free = NULL;
	enum drm_mm_insert_mode mode = DRM_MM_INSERT_LOW;
	int ret;

	lockdep_assert_held(&mmu->lock);

	while (1) {
		struct etnaviv_vram_mapping *m, *n;
		struct drm_mm_scan scan;
		struct list_head list;
		bool found;

		ret = drm_mm_insert_node_in_range(&mmu->mm, node,
<<<<<<< HEAD
						  size, 0, 0, 0, U64_MAX, mode);
		if (ret != -ENOSPC)
			break;

=======
						  size, 0, 0,
						  mmu->last_iova, U64_MAX,
						  mode);
		if (ret != -ENOSPC)
			break;

		/*
		 * If we did not search from the start of the MMU region,
		 * try again in case there are free slots.
		 */
		if (mmu->last_iova) {
			mmu->last_iova = 0;
			mmu->flush_seq++;
			continue;
		}

>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
		/* Try to retire some entries */
		drm_mm_scan_init(&scan, &mmu->mm, size, 0, 0, mode);

		found = 0;
		INIT_LIST_HEAD(&list);
		list_for_each_entry(free, &mmu->mappings, mmu_node) {
			/* If this vram node has not been used, skip this. */
			if (!free->vram_node.mm)
				continue;

			/*
			 * If the iova is pinned, then it's in-use,
			 * so we must keep its mapping.
			 */
			if (free->use)
				continue;

			list_add(&free->scan_node, &list);
			if (drm_mm_scan_add_block(&scan, &free->vram_node)) {
				found = true;
				break;
			}
		}

		if (!found) {
			/* Nothing found, clean up and fail */
			list_for_each_entry_safe(m, n, &list, scan_node)
				BUG_ON(drm_mm_scan_remove_block(&scan, &m->vram_node));
			break;
		}

		/*
		 * drm_mm does not allow any other operations while
		 * scanning, so we have to remove all blocks first.
		 * If drm_mm_scan_remove_block() returns false, we
		 * can leave the block pinned.
		 */
		list_for_each_entry_safe(m, n, &list, scan_node)
			if (!drm_mm_scan_remove_block(&scan, &m->vram_node))
				list_del_init(&m->scan_node);

		/*
		 * Unmap the blocks which need to be reaped from the MMU.
		 * Clear the mmu pointer to prevent the mapping_get finding
		 * this mapping.
		 */
		list_for_each_entry_safe(m, n, &list, scan_node) {
			etnaviv_iommu_remove_mapping(mmu, m);
			m->mmu = NULL;
			list_del_init(&m->mmu_node);
			list_del_init(&m->scan_node);
		}

		mode = DRM_MM_INSERT_EVICT;

		/*
		 * We removed enough mappings so that the new allocation will
		 * succeed, retry the allocation one more time.
		 */
	}

	return ret;
}

int etnaviv_iommu_map_gem(struct etnaviv_iommu *mmu,
	struct etnaviv_gem_object *etnaviv_obj, u32 memory_base,
	struct etnaviv_vram_mapping *mapping)
{
	struct sg_table *sgt = etnaviv_obj->sgt;
	struct drm_mm_node *node;
	int ret;

	lockdep_assert_held(&etnaviv_obj->lock);

	mutex_lock(&mmu->lock);

	/* v1 MMU can optimize single entry (contiguous) scatterlists */
	if (mmu->version == ETNAVIV_IOMMU_V1 &&
	    sgt->nents == 1 && !(etnaviv_obj->flags & ETNA_BO_FORCE_MMU)) {
		u32 iova;

		iova = sg_dma_address(sgt->sgl) - memory_base;
		if (iova < 0x80000000 - sg_dma_len(sgt->sgl)) {
			mapping->iova = iova;
			list_add_tail(&mapping->mmu_node, &mmu->mappings);
<<<<<<< HEAD
			ret = 0;
			goto unlock;
=======
			mutex_unlock(&mmu->lock);
			return 0;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
		}
	}

	node = &mapping->vram_node;

	ret = etnaviv_iommu_find_iova(mmu, node, etnaviv_obj->base.size);
<<<<<<< HEAD
	if (ret < 0)
		goto unlock;

	mapping->iova = node->start;
	ret = etnaviv_iommu_map(mmu, node->start, sgt, etnaviv_obj->base.size,
				ETNAVIV_PROT_READ | ETNAVIV_PROT_WRITE);

	if (ret < 0) {
		drm_mm_remove_node(node);
		goto unlock;
	}

	list_add_tail(&mapping->mmu_node, &mmu->mappings);
	mmu->need_flush = true;
unlock:
=======
	if (ret < 0) {
		mutex_unlock(&mmu->lock);
		return ret;
	}

	mmu->last_iova = node->start + etnaviv_obj->base.size;
	mapping->iova = node->start;
	ret = etnaviv_iommu_map(mmu, node->start, sgt, etnaviv_obj->base.size,
				IOMMU_READ | IOMMU_WRITE);

	if (ret < 0) {
		drm_mm_remove_node(node);
		mutex_unlock(&mmu->lock);
		return ret;
	}

	list_add_tail(&mapping->mmu_node, &mmu->mappings);
	mmu->flush_seq++;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	mutex_unlock(&mmu->lock);

	return ret;
}

void etnaviv_iommu_unmap_gem(struct etnaviv_iommu *mmu,
	struct etnaviv_vram_mapping *mapping)
{
	WARN_ON(mapping->use);

	mutex_lock(&mmu->lock);

	/* If the vram node is on the mm, unmap and remove the node */
	if (mapping->vram_node.mm == &mmu->mm)
		etnaviv_iommu_remove_mapping(mmu, mapping);

	list_del(&mapping->mmu_node);
<<<<<<< HEAD
	mmu->need_flush = true;
=======
	mmu->flush_seq++;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	mutex_unlock(&mmu->lock);
}

void etnaviv_iommu_destroy(struct etnaviv_iommu *mmu)
{
	drm_mm_takedown(&mmu->mm);
<<<<<<< HEAD
	mmu->domain->ops->free(mmu->domain);
=======
	iommu_domain_free(mmu->domain);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	kfree(mmu);
}

struct etnaviv_iommu *etnaviv_iommu_new(struct etnaviv_gpu *gpu)
{
	enum etnaviv_iommu_version version;
	struct etnaviv_iommu *mmu;

	mmu = kzalloc(sizeof(*mmu), GFP_KERNEL);
	if (!mmu)
		return ERR_PTR(-ENOMEM);

	if (!(gpu->identity.minor_features1 & chipMinorFeatures1_MMU_VERSION)) {
		mmu->domain = etnaviv_iommuv1_domain_alloc(gpu);
		version = ETNAVIV_IOMMU_V1;
	} else {
		mmu->domain = etnaviv_iommuv2_domain_alloc(gpu);
		version = ETNAVIV_IOMMU_V2;
	}

	if (!mmu->domain) {
		dev_err(gpu->dev, "Failed to allocate GPU IOMMU domain\n");
		kfree(mmu);
		return ERR_PTR(-ENOMEM);
	}

	mmu->gpu = gpu;
	mmu->version = version;
	mutex_init(&mmu->lock);
	INIT_LIST_HEAD(&mmu->mappings);

<<<<<<< HEAD
	drm_mm_init(&mmu->mm, mmu->domain->base, mmu->domain->size);
=======
	drm_mm_init(&mmu->mm, mmu->domain->geometry.aperture_start,
		    mmu->domain->geometry.aperture_end -
		    mmu->domain->geometry.aperture_start + 1);

	iommu_set_fault_handler(mmu->domain, etnaviv_fault_handler, gpu->dev);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	return mmu;
}

void etnaviv_iommu_restore(struct etnaviv_gpu *gpu)
{
	if (gpu->mmu->version == ETNAVIV_IOMMU_V1)
		etnaviv_iommuv1_restore(gpu);
	else
		etnaviv_iommuv2_restore(gpu);
}

int etnaviv_iommu_get_suballoc_va(struct etnaviv_gpu *gpu, dma_addr_t paddr,
				  struct drm_mm_node *vram_node, size_t size,
				  u32 *iova)
{
	struct etnaviv_iommu *mmu = gpu->mmu;

	if (mmu->version == ETNAVIV_IOMMU_V1) {
		*iova = paddr - gpu->memory_base;
		return 0;
	} else {
		int ret;

		mutex_lock(&mmu->lock);
		ret = etnaviv_iommu_find_iova(mmu, vram_node, size);
		if (ret < 0) {
			mutex_unlock(&mmu->lock);
			return ret;
		}
<<<<<<< HEAD
		ret = etnaviv_domain_map(mmu->domain, vram_node->start, paddr,
					 size, ETNAVIV_PROT_READ);
=======
		ret = iommu_map(mmu->domain, vram_node->start, paddr, size,
				IOMMU_READ);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
		if (ret < 0) {
			drm_mm_remove_node(vram_node);
			mutex_unlock(&mmu->lock);
			return ret;
		}
<<<<<<< HEAD
		gpu->mmu->need_flush = true;
=======
		mmu->last_iova = vram_node->start + size;
		mmu->flush_seq++;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
		mutex_unlock(&mmu->lock);

		*iova = (u32)vram_node->start;
		return 0;
	}
}

void etnaviv_iommu_put_suballoc_va(struct etnaviv_gpu *gpu,
				   struct drm_mm_node *vram_node, size_t size,
				   u32 iova)
{
	struct etnaviv_iommu *mmu = gpu->mmu;

	if (mmu->version == ETNAVIV_IOMMU_V2) {
		mutex_lock(&mmu->lock);
<<<<<<< HEAD
		etnaviv_domain_unmap(mmu->domain, iova, size);
=======
		iommu_unmap(mmu->domain,iova, size);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
		drm_mm_remove_node(vram_node);
		mutex_unlock(&mmu->lock);
	}
}
size_t etnaviv_iommu_dump_size(struct etnaviv_iommu *iommu)
{
<<<<<<< HEAD
	return iommu->domain->ops->dump_size(iommu->domain);
=======
	struct etnaviv_iommu_ops *ops;

	ops = container_of(iommu->domain->ops, struct etnaviv_iommu_ops, ops);

	return ops->dump_size(iommu->domain);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
}

void etnaviv_iommu_dump(struct etnaviv_iommu *iommu, void *buf)
{
<<<<<<< HEAD
	iommu->domain->ops->dump(iommu->domain, buf);
=======
	struct etnaviv_iommu_ops *ops;

	ops = container_of(iommu->domain->ops, struct etnaviv_iommu_ops, ops);

	ops->dump(iommu->domain, buf);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
}
