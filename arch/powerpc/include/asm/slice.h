/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _ASM_POWERPC_SLICE_H
#define _ASM_POWERPC_SLICE_H

#ifdef CONFIG_PPC_BOOK3S_64
#include <asm/book3s/64/slice.h>
#elif defined(CONFIG_PPC64)
#include <asm/nohash/64/slice.h>
#elif defined(CONFIG_PPC_MMU_NOHASH)
#include <asm/nohash/32/slice.h>
#endif

#ifdef CONFIG_PPC_MM_SLICES

#ifdef CONFIG_HUGETLB_PAGE
#define HAVE_ARCH_HUGETLB_UNMAPPED_AREA
#endif
#define HAVE_ARCH_UNMAPPED_AREA
#define HAVE_ARCH_UNMAPPED_AREA_TOPDOWN

#ifndef __ASSEMBLY__

struct mm_struct;

unsigned long slice_get_unmapped_area(unsigned long addr, unsigned long len,
				      unsigned long flags, unsigned int psize,
				      int topdown);

unsigned int get_slice_psize(struct mm_struct *mm, unsigned long addr);

<<<<<<< HEAD
void slice_set_range_psize(struct mm_struct *mm, unsigned long start,
			   unsigned long len, unsigned int psize);

void slice_init_new_context_exec(struct mm_struct *mm);

#endif /* __ASSEMBLY__ */

=======
void slice_set_user_psize(struct mm_struct *mm, unsigned int psize);
void slice_set_range_psize(struct mm_struct *mm, unsigned long start,
			   unsigned long len, unsigned int psize);
#endif /* __ASSEMBLY__ */

#else /* CONFIG_PPC_MM_SLICES */

#define slice_set_range_psize(mm, start, len, psize)	\
	slice_set_user_psize((mm), (psize))
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
#endif /* CONFIG_PPC_MM_SLICES */

#endif /* _ASM_POWERPC_SLICE_H */
