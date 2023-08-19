/* SPDX-License-Identifier: GPL-2.0 */
#ifndef ___ASM_SPARC_DMA_MAPPING_H
#define ___ASM_SPARC_DMA_MAPPING_H

#include <linux/scatterlist.h>
#include <linux/mm.h>
#include <linux/dma-debug.h>

<<<<<<< HEAD
extern const struct dma_map_ops *dma_ops;
=======
static inline void dma_cache_sync(struct device *dev, void *vaddr, size_t size,
				  enum dma_data_direction dir)
{
	/* Since dma_{alloc,free}_noncoherent() allocated coherent memory, this
	 * routine can be a nop.
	 */
}

extern const struct dma_map_ops *dma_ops;
extern const struct dma_map_ops pci32_dma_ops;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

extern struct bus_type pci_bus_type;

static inline const struct dma_map_ops *get_arch_dma_ops(struct bus_type *bus)
{
#ifdef CONFIG_SPARC_LEON
	if (sparc_cpu_model == sparc_leon)
<<<<<<< HEAD
		return &dma_noncoherent_ops;
#endif
#if defined(CONFIG_SPARC32) && defined(CONFIG_PCI)
	if (bus == &pci_bus_type)
		return &dma_noncoherent_ops;
=======
		return &pci32_dma_ops;
#endif
#if defined(CONFIG_SPARC32) && defined(CONFIG_PCI)
	if (bus == &pci_bus_type)
		return &pci32_dma_ops;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
#endif
	return dma_ops;
}

#endif
