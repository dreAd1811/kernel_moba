/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _ASM_POWERPC_NOHASH_32_SLICE_H
#define _ASM_POWERPC_NOHASH_32_SLICE_H

#ifdef CONFIG_PPC_MM_SLICES

<<<<<<< HEAD
#define SLICE_LOW_SHIFT		26	/* 64 slices */
=======
#define SLICE_LOW_SHIFT		28
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
#define SLICE_LOW_TOP		(0x100000000ull)
#define SLICE_NUM_LOW		(SLICE_LOW_TOP >> SLICE_LOW_SHIFT)
#define GET_LOW_SLICE_INDEX(addr)	((addr) >> SLICE_LOW_SHIFT)

#define SLICE_HIGH_SHIFT	0
#define SLICE_NUM_HIGH		0ul
#define GET_HIGH_SLICE_INDEX(addr)	(addr & 0)

#endif /* CONFIG_PPC_MM_SLICES */

#endif /* _ASM_POWERPC_NOHASH_32_SLICE_H */
