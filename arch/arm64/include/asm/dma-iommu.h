<<<<<<< HEAD
/* SPDX-License-Identifier: GPL-2.0-only */
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
#ifndef ASMARM_DMA_IOMMU_H
#define ASMARM_DMA_IOMMU_H

#ifdef __KERNEL__

#include <linux/err.h>
#include <linux/mm_types.h>
#include <linux/scatterlist.h>
#include <linux/dma-debug.h>
#include <linux/kref.h>
#include <linux/dma-mapping-fast.h>

struct dma_iommu_mapping {
	/* iommu specific data */
	struct iommu_domain	*domain;
	bool			init;
	struct kref		kref;
	const struct dma_map_ops *ops;

	/* Protects bitmap */
	spinlock_t		lock;
	void			*bitmap;
	size_t			bits;
	dma_addr_t		base;
<<<<<<< HEAD
=======
	u32			min_iova_align;
	struct page		*guard_page;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	struct dma_fast_smmu_mapping *fast;
};

#ifdef CONFIG_ARM64_DMA_USE_IOMMU
<<<<<<< HEAD
void arm_iommu_put_dma_cookie(struct iommu_domain *domain);
#else  /* !CONFIG_ARM64_DMA_USE_IOMMU */
static inline void arm_iommu_put_dma_cookie(struct iommu_domain *domain) {}
=======

struct dma_iommu_mapping *
arm_iommu_create_mapping(struct bus_type *bus, dma_addr_t base, size_t size);

void arm_iommu_release_mapping(struct dma_iommu_mapping *mapping);

int arm_iommu_attach_device(struct device *dev,
					struct dma_iommu_mapping *mapping);
void arm_iommu_detach_device(struct device *dev);

#else  /* !CONFIG_ARM64_DMA_USE_IOMMU */

static inline struct dma_iommu_mapping *
arm_iommu_create_mapping(struct bus_type *bus, dma_addr_t base, size_t size)
{
	return NULL;
}

static inline void arm_iommu_release_mapping(struct dma_iommu_mapping *mapping)
{
}

static inline int arm_iommu_attach_device(struct device *dev,
			struct dma_iommu_mapping *mapping)
{
	return -ENODEV;
}

static inline void arm_iommu_detach_device(struct device *dev)
{
}

>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
#endif	/* CONFIG_ARM64_DMA_USE_IOMMU */

#endif /* __KERNEL__ */
#endif
