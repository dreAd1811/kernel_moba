/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _ASM_X86_PGTABLE_64_DEFS_H
#define _ASM_X86_PGTABLE_64_DEFS_H

#include <asm/sparsemem.h>

#ifndef __ASSEMBLY__
#include <linux/types.h>
#include <asm/kaslr.h>

/*
 * These are used to make use of C type-checking..
 */
typedef unsigned long	pteval_t;
typedef unsigned long	pmdval_t;
typedef unsigned long	pudval_t;
typedef unsigned long	p4dval_t;
typedef unsigned long	pgdval_t;
typedef unsigned long	pgprotval_t;

typedef struct { pteval_t pte; } pte_t;

<<<<<<< HEAD
#ifdef CONFIG_X86_5LEVEL
extern unsigned int __pgtable_l5_enabled;

#ifdef USE_EARLY_PGTABLE_L5
/*
 * cpu_feature_enabled() is not available in early boot code.
 * Use variable instead.
 */
static inline bool pgtable_l5_enabled(void)
{
	return __pgtable_l5_enabled;
}
#else
#define pgtable_l5_enabled() cpu_feature_enabled(X86_FEATURE_LA57)
#endif /* USE_EARLY_PGTABLE_L5 */

#else
#define pgtable_l5_enabled() 0
#endif /* CONFIG_X86_5LEVEL */

extern unsigned int pgdir_shift;
extern unsigned int ptrs_per_p4d;

=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
#endif	/* !__ASSEMBLY__ */

#define SHARED_KERNEL_PMD	0

#ifdef CONFIG_X86_5LEVEL

/*
 * PGDIR_SHIFT determines what a top-level page table entry can map
 */
<<<<<<< HEAD
#define PGDIR_SHIFT	pgdir_shift
=======
#define PGDIR_SHIFT	48
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
#define PTRS_PER_PGD	512

/*
 * 4th level page in 5-level paging case
 */
<<<<<<< HEAD
#define P4D_SHIFT		39
#define MAX_PTRS_PER_P4D	512
#define PTRS_PER_P4D		ptrs_per_p4d
#define P4D_SIZE		(_AC(1, UL) << P4D_SHIFT)
#define P4D_MASK		(~(P4D_SIZE - 1))

#define MAX_POSSIBLE_PHYSMEM_BITS	52
=======
#define P4D_SHIFT	39
#define PTRS_PER_P4D	512
#define P4D_SIZE	(_AC(1, UL) << P4D_SHIFT)
#define P4D_MASK	(~(P4D_SIZE - 1))
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

#else /* CONFIG_X86_5LEVEL */

/*
 * PGDIR_SHIFT determines what a top-level page table entry can map
 */
<<<<<<< HEAD
#define PGDIR_SHIFT		39
#define PTRS_PER_PGD		512
#define MAX_PTRS_PER_P4D	1
=======
#define PGDIR_SHIFT	39
#define PTRS_PER_PGD	512
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

#endif /* CONFIG_X86_5LEVEL */

/*
 * 3rd level page
 */
#define PUD_SHIFT	30
#define PTRS_PER_PUD	512

/*
 * PMD_SHIFT determines the size of the area a middle-level
 * page table can map
 */
#define PMD_SHIFT	21
#define PTRS_PER_PMD	512

/*
 * entries per page directory level
 */
#define PTRS_PER_PTE	512

#define PMD_SIZE	(_AC(1, UL) << PMD_SHIFT)
#define PMD_MASK	(~(PMD_SIZE - 1))
#define PUD_SIZE	(_AC(1, UL) << PUD_SHIFT)
#define PUD_MASK	(~(PUD_SIZE - 1))
#define PGDIR_SIZE	(_AC(1, UL) << PGDIR_SHIFT)
#define PGDIR_MASK	(~(PGDIR_SIZE - 1))

/*
 * See Documentation/x86/x86_64/mm.txt for a description of the memory map.
 *
 * Be very careful vs. KASLR when changing anything here. The KASLR address
 * range must not overlap with anything except the KASAN shadow area, which
 * is correct as KASAN disables KASLR.
 */
<<<<<<< HEAD
#define MAXMEM			(1UL << MAX_PHYSMEM_BITS)
=======
#define MAXMEM			_AC(__AC(1, UL) << MAX_PHYSMEM_BITS, UL)

#ifdef CONFIG_X86_5LEVEL
# define VMALLOC_SIZE_TB	_AC(12800, UL)
# define __VMALLOC_BASE		_AC(0xffa0000000000000, UL)
# define __VMEMMAP_BASE		_AC(0xffd4000000000000, UL)
#else
# define VMALLOC_SIZE_TB	_AC(32, UL)
# define __VMALLOC_BASE		_AC(0xffffc90000000000, UL)
# define __VMEMMAP_BASE		_AC(0xffffea0000000000, UL)
#endif
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

#define GUARD_HOLE_PGD_ENTRY	-256UL
#define GUARD_HOLE_SIZE		(16UL << PGDIR_SHIFT)
#define GUARD_HOLE_BASE_ADDR	(GUARD_HOLE_PGD_ENTRY << PGDIR_SHIFT)
#define GUARD_HOLE_END_ADDR	(GUARD_HOLE_BASE_ADDR + GUARD_HOLE_SIZE)

#define LDT_PGD_ENTRY		-240UL
#define LDT_BASE_ADDR		(LDT_PGD_ENTRY << PGDIR_SHIFT)
<<<<<<< HEAD
#define LDT_END_ADDR		(LDT_BASE_ADDR + PGDIR_SIZE)

#define __VMALLOC_BASE_L4	0xffffc90000000000UL
#define __VMALLOC_BASE_L5 	0xffa0000000000000UL

#define VMALLOC_SIZE_TB_L4	32UL
#define VMALLOC_SIZE_TB_L5	12800UL

#define __VMEMMAP_BASE_L4	0xffffea0000000000UL
#define __VMEMMAP_BASE_L5	0xffd4000000000000UL

#ifdef CONFIG_DYNAMIC_MEMORY_LAYOUT
# define VMALLOC_START		vmalloc_base
# define VMALLOC_SIZE_TB	(pgtable_l5_enabled() ? VMALLOC_SIZE_TB_L5 : VMALLOC_SIZE_TB_L4)
# define VMEMMAP_START		vmemmap_base
#else
# define VMALLOC_START		__VMALLOC_BASE_L4
# define VMALLOC_SIZE_TB	VMALLOC_SIZE_TB_L4
# define VMEMMAP_START		__VMEMMAP_BASE_L4
#endif /* CONFIG_DYNAMIC_MEMORY_LAYOUT */

#define VMALLOC_END		(VMALLOC_START + (VMALLOC_SIZE_TB << 40) - 1)
=======

#ifdef CONFIG_RANDOMIZE_MEMORY
# define VMALLOC_START		vmalloc_base
# define VMEMMAP_START		vmemmap_base
#else
# define VMALLOC_START		__VMALLOC_BASE
# define VMEMMAP_START		__VMEMMAP_BASE
#endif /* CONFIG_RANDOMIZE_MEMORY */

#define VMALLOC_END		(VMALLOC_START + _AC((VMALLOC_SIZE_TB << 40) - 1, UL))
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

#define MODULES_VADDR		(__START_KERNEL_map + KERNEL_IMAGE_SIZE)
/* The module sections ends with the start of the fixmap */
#define MODULES_END		_AC(0xffffffffff000000, UL)
#define MODULES_LEN		(MODULES_END - MODULES_VADDR)

#define ESPFIX_PGD_ENTRY	_AC(-2, UL)
#define ESPFIX_BASE_ADDR	(ESPFIX_PGD_ENTRY << P4D_SHIFT)

#define CPU_ENTRY_AREA_PGD	_AC(-4, UL)
#define CPU_ENTRY_AREA_BASE	(CPU_ENTRY_AREA_PGD << P4D_SHIFT)

#define EFI_VA_START		( -4 * (_AC(1, UL) << 30))
#define EFI_VA_END		(-68 * (_AC(1, UL) << 30))

#define EARLY_DYNAMIC_PAGE_TABLES	64

<<<<<<< HEAD
#define PGD_KERNEL_START	((PAGE_SIZE / 2) / sizeof(pgd_t))

=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
#endif /* _ASM_X86_PGTABLE_64_DEFS_H */
