/* SPDX-License-Identifier: GPL-2.0 */
#ifndef DMA_H
#define DMA_H

#include <asm/glue-cache.h>

#ifndef MULTI_CACHE
<<<<<<< HEAD

=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
/*
 * These are private to the dma-mapping API.  Do not use directly.
 * Their sole purpose is to ensure that data held in the cache
 * is visible to DMA, or data written by DMA to system memory is
 * visible to the CPU.
 */
extern void dmac_map_area(const void *, size_t, int);
extern void dmac_unmap_area(const void *, size_t, int);

#else

/*
 * These are private to the dma-mapping API.  Do not use directly.
 * Their sole purpose is to ensure that data held in the cache
 * is visible to DMA, or data written by DMA to system memory is
 * visible to the CPU.
 */
#define dmac_map_area			cpu_cache.dma_map_area
#define dmac_unmap_area 		cpu_cache.dma_unmap_area

#endif

#endif
