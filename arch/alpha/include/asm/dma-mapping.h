/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _ALPHA_DMA_MAPPING_H
#define _ALPHA_DMA_MAPPING_H

<<<<<<< HEAD
extern const struct dma_map_ops alpha_pci_ops;

static inline const struct dma_map_ops *get_arch_dma_ops(struct bus_type *bus)
{
#ifdef CONFIG_ALPHA_JENSEN
	return &dma_direct_ops;
#else
	return &alpha_pci_ops;
#endif
}

=======
extern const struct dma_map_ops *dma_ops;

static inline const struct dma_map_ops *get_arch_dma_ops(struct bus_type *bus)
{
	return dma_ops;
}

#define dma_cache_sync(dev, va, size, dir)		  ((void)0)

>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
#endif	/* _ALPHA_DMA_MAPPING_H */
