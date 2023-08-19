<<<<<<< HEAD
// SPDX-License-Identifier:  GPL-2.0
// (C) 2018 Synopsys, Inc. (www.synopsys.com)
=======
/*
 * DMA Mapping glue for ARC
 *
 * Copyright (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

#ifndef ASM_ARC_DMA_MAPPING_H
#define ASM_ARC_DMA_MAPPING_H

<<<<<<< HEAD
#include <asm-generic/dma-mapping.h>

void arch_setup_dma_ops(struct device *dev, u64 dma_base, u64 size,
			const struct iommu_ops *iommu, bool coherent);
#define arch_setup_dma_ops arch_setup_dma_ops
=======
#ifndef CONFIG_ARC_PLAT_NEEDS_PHYS_TO_DMA
#define plat_dma_to_phys(dev, dma_handle) ((phys_addr_t)(dma_handle))
#define plat_phys_to_dma(dev, paddr) ((dma_addr_t)(paddr))
#else
#include <plat/dma.h>
#endif

extern const struct dma_map_ops arc_dma_ops;

static inline const struct dma_map_ops *get_arch_dma_ops(struct bus_type *bus)
{
	return &arc_dma_ops;
}
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

#endif
