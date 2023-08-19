/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _ASM_POWERPC_PGTABLE_RADIX_4K_H
#define _ASM_POWERPC_PGTABLE_RADIX_4K_H

/*
 * For 4K page size supported index is 13/9/9/9
 */
#define RADIX_PTE_INDEX_SIZE  9  /* 2MB huge page */
#define RADIX_PMD_INDEX_SIZE  9  /* 1G huge page */
#define RADIX_PUD_INDEX_SIZE	 9
#define RADIX_PGD_INDEX_SIZE  13
<<<<<<< HEAD
/*
 * One fragment per per page
 */
#define RADIX_PTE_FRAG_SIZE_SHIFT  (RADIX_PTE_INDEX_SIZE + 3)
#define RADIX_PTE_FRAG_NR	(PAGE_SIZE >> RADIX_PTE_FRAG_SIZE_SHIFT)

#define RADIX_PMD_FRAG_SIZE_SHIFT  (RADIX_PMD_INDEX_SIZE + 3)
#define RADIX_PMD_FRAG_NR	(PAGE_SIZE >> RADIX_PMD_FRAG_SIZE_SHIFT)
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

#endif /* _ASM_POWERPC_PGTABLE_RADIX_4K_H */
