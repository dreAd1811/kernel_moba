/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _ASM_DMA_MAPPING_H
#define _ASM_DMA_MAPPING_H

<<<<<<< HEAD
#include <linux/swiotlb.h>

extern const struct dma_map_ops jazz_dma_ops;

static inline const struct dma_map_ops *get_arch_dma_ops(struct bus_type *bus)
{
#if defined(CONFIG_MACH_JAZZ)
	return &jazz_dma_ops;
#elif defined(CONFIG_SWIOTLB)
	return &swiotlb_dma_ops;
#elif defined(CONFIG_DMA_NONCOHERENT_OPS)
	return &dma_noncoherent_ops;
#else
	return &dma_direct_ops;
#endif
}

=======
#include <linux/scatterlist.h>
#include <asm/dma-coherence.h>
#include <asm/cache.h>

#ifndef CONFIG_SGI_IP27 /* Kludge to fix 2.6.39 build for IP27 */
#include <dma-coherence.h>
#endif

extern const struct dma_map_ops *mips_dma_map_ops;

static inline const struct dma_map_ops *get_arch_dma_ops(struct bus_type *bus)
{
	return mips_dma_map_ops;
}

static inline bool dma_capable(struct device *dev, dma_addr_t addr, size_t size)
{
	if (!dev->dma_mask)
		return false;

	return addr + size <= *dev->dma_mask;
}

static inline void dma_mark_clean(void *addr, size_t size) {}

extern void dma_cache_sync(struct device *dev, void *vaddr, size_t size,
	       enum dma_data_direction direction);

>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
#define arch_setup_dma_ops arch_setup_dma_ops
static inline void arch_setup_dma_ops(struct device *dev, u64 dma_base,
				      u64 size, const struct iommu_ops *iommu,
				      bool coherent)
{
#ifdef CONFIG_DMA_PERDEV_COHERENT
	dev->archdata.dma_coherent = coherent;
#endif
}

#endif /* _ASM_DMA_MAPPING_H */
