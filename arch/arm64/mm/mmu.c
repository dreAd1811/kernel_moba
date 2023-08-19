/*
 * Based on arch/arm/mm/mmu.c
 *
 * Copyright (C) 1995-2005 Russell King
 * Copyright (C) 2012 ARM Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <linux/cache.h>
#include <linux/export.h>
#include <linux/kernel.h>
#include <linux/errno.h>
#include <linux/init.h>
#include <linux/ioport.h>
#include <linux/kexec.h>
#include <linux/libfdt.h>
#include <linux/mman.h>
#include <linux/nodemask.h>
#include <linux/memblock.h>
#include <linux/fs.h>
#include <linux/io.h>
#include <linux/mm.h>
#include <linux/vmalloc.h>
#include <linux/dma-contiguous.h>
#include <linux/cma.h>

#include <asm/barrier.h>
#include <asm/cputype.h>
#include <asm/fixmap.h>
#include <asm/kasan.h>
#include <asm/kernel-pgtable.h>
#include <asm/sections.h>
#include <asm/setup.h>
#include <asm/sizes.h>
#include <asm/tlb.h>
#include <asm/memblock.h>
#include <asm/mmu_context.h>
#include <asm/ptdump.h>
#include <asm/tlbflush.h>

#define NO_BLOCK_MAPPINGS	BIT(0)
#define NO_CONT_MAPPINGS	BIT(1)

u64 idmap_t0sz = TCR_T0SZ(VA_BITS);
<<<<<<< HEAD
u64 idmap_ptrs_per_pgd = PTRS_PER_PGD;
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

u64 kimage_voffset __ro_after_init;
EXPORT_SYMBOL(kimage_voffset);

/*
 * Empty_zero_page is a special page that is used for zero-initialized data
 * and COW.
 */
unsigned long empty_zero_page[PAGE_SIZE / sizeof(unsigned long)] __page_aligned_bss;
EXPORT_SYMBOL(empty_zero_page);

static pte_t bm_pte[PTRS_PER_PTE] __page_aligned_bss;
static pmd_t bm_pmd[PTRS_PER_PMD] __page_aligned_bss __maybe_unused;
static pud_t bm_pud[PTRS_PER_PUD] __page_aligned_bss __maybe_unused;

struct dma_contig_early_reserve {
	phys_addr_t base;
	unsigned long size;
};

static struct dma_contig_early_reserve dma_mmu_remap[MAX_CMA_AREAS];
static int dma_mmu_remap_num;

void __init dma_contiguous_early_fixup(phys_addr_t base, unsigned long size)
{
	if (dma_mmu_remap_num >= ARRAY_SIZE(dma_mmu_remap)) {
		pr_err("ARM64: Not enough slots for DMA fixup reserved regions!\n");
		return;
	}
	dma_mmu_remap[dma_mmu_remap_num].base = base;
	dma_mmu_remap[dma_mmu_remap_num].size = size;
	dma_mmu_remap_num++;
}

static bool dma_overlap(phys_addr_t start, phys_addr_t end)
{
	int i;

	for (i = 0; i < dma_mmu_remap_num; i++) {
		phys_addr_t dma_base = dma_mmu_remap[i].base;
		phys_addr_t dma_end = dma_mmu_remap[i].base +
			dma_mmu_remap[i].size;

		if ((dma_base < end) && (dma_end > start))
			return true;
	}
	return false;
}

pgprot_t phys_mem_access_prot(struct file *file, unsigned long pfn,
			      unsigned long size, pgprot_t vma_prot)
{
	if (!pfn_valid(pfn))
		return pgprot_noncached(vma_prot);
	else if (file->f_flags & O_SYNC)
		return pgprot_writecombine(vma_prot);
	return vma_prot;
}
EXPORT_SYMBOL(phys_mem_access_prot);

static phys_addr_t __init early_pgtable_alloc(void)
{
	phys_addr_t phys;
	void *ptr;

	phys = memblock_alloc(PAGE_SIZE, PAGE_SIZE);

	/*
	 * The FIX_{PGD,PUD,PMD} slots may be in active use, but the FIX_PTE
	 * slot will be free, so we can (ab)use the FIX_PTE slot to initialise
	 * any level of table.
	 */
	ptr = pte_set_fixmap(phys);

	memset(ptr, 0, PAGE_SIZE);

	/*
	 * Implicit barriers also ensure the zeroed page is visible to the page
	 * table walker
	 */
	pte_clear_fixmap();

	return phys;
}

static bool pgattr_change_is_safe(u64 old, u64 new)
{
	/*
	 * The following mapping attributes may be updated in live
	 * kernel mappings without the need for break-before-make.
	 */
	static const pteval_t mask = PTE_PXN | PTE_RDONLY | PTE_WRITE | PTE_NG;

	/* creating or taking down mappings is always safe */
	if (old == 0 || new == 0)
		return true;

	/* live contiguous mappings may not be manipulated at all */
	if ((old | new) & PTE_CONT)
		return false;

	/* Transitioning from Non-Global to Global is unsafe */
	if (old & ~new & PTE_NG)
		return false;

	return ((old ^ new) & ~mask) == 0;
}

<<<<<<< HEAD
static void init_pte(pmd_t *pmdp, unsigned long addr, unsigned long end,
		     phys_addr_t phys, pgprot_t prot)
{
	pte_t *ptep;

	ptep = pte_set_fixmap_offset(pmdp, addr);
	do {
		pte_t old_pte = READ_ONCE(*ptep);

		set_pte(ptep, pfn_pte(__phys_to_pfn(phys), prot));
=======
static void init_pte(pmd_t *pmd, unsigned long addr, unsigned long end,
		     phys_addr_t phys, pgprot_t prot)
{
	pte_t *pte;

	pte = pte_set_fixmap_offset(pmd, addr);
	do {
		pte_t old_pte = *pte;

		set_pte(pte, pfn_pte(__phys_to_pfn(phys), prot));
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

		/*
		 * After the PTE entry has been populated once, we
		 * only allow updates to the permission attributes.
		 */
<<<<<<< HEAD
		BUG_ON(!pgattr_change_is_safe(pte_val(old_pte),
					      READ_ONCE(pte_val(*ptep))));

		phys += PAGE_SIZE;
	} while (ptep++, addr += PAGE_SIZE, addr != end);
=======
		BUG_ON(!pgattr_change_is_safe(pte_val(old_pte), pte_val(*pte)));

		phys += PAGE_SIZE;
	} while (pte++, addr += PAGE_SIZE, addr != end);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	pte_clear_fixmap();
}

<<<<<<< HEAD
static void alloc_init_cont_pte(pmd_t *pmdp, unsigned long addr,
=======
static void alloc_init_cont_pte(pmd_t *pmd, unsigned long addr,
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
				unsigned long end, phys_addr_t phys,
				pgprot_t prot,
				phys_addr_t (*pgtable_alloc)(void),
				int flags)
{
	unsigned long next;
<<<<<<< HEAD
	pmd_t pmd = READ_ONCE(*pmdp);

	BUG_ON(pmd_sect(pmd));
	if (pmd_none(pmd)) {
		phys_addr_t pte_phys;
		BUG_ON(!pgtable_alloc);
		pte_phys = pgtable_alloc();
		__pmd_populate(pmdp, pte_phys, PMD_TYPE_TABLE);
		pmd = READ_ONCE(*pmdp);
	}
	BUG_ON(pmd_bad(pmd));
=======

	BUG_ON(pmd_sect(*pmd));
	if (pmd_none(*pmd)) {
		phys_addr_t pte_phys;
		BUG_ON(!pgtable_alloc);
		pte_phys = pgtable_alloc();
		__pmd_populate(pmd, pte_phys, PMD_TYPE_TABLE);
	}
	BUG_ON(pmd_bad(*pmd));
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	do {
		pgprot_t __prot = prot;

		next = pte_cont_addr_end(addr, end);

		/* use a contiguous mapping if the range is suitably aligned */
		if ((((addr | next | phys) & ~CONT_PTE_MASK) == 0) &&
		    (flags & NO_CONT_MAPPINGS) == 0)
			__prot = __pgprot(pgprot_val(prot) | PTE_CONT);

<<<<<<< HEAD
		init_pte(pmdp, addr, next, phys, __prot);
=======
		init_pte(pmd, addr, next, phys, __prot);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

		phys += next - addr;
	} while (addr = next, addr != end);
}

<<<<<<< HEAD
static void init_pmd(pud_t *pudp, unsigned long addr, unsigned long end,
=======
static void init_pmd(pud_t *pud, unsigned long addr, unsigned long end,
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
		     phys_addr_t phys, pgprot_t prot,
		     phys_addr_t (*pgtable_alloc)(void), int flags)
{
	unsigned long next;
<<<<<<< HEAD
	pmd_t *pmdp;

	pmdp = pmd_set_fixmap_offset(pudp, addr);
	do {
		pmd_t old_pmd = READ_ONCE(*pmdp);
=======
	pmd_t *pmd;

	pmd = pmd_set_fixmap_offset(pud, addr);
	do {
		pmd_t old_pmd = *pmd;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

		next = pmd_addr_end(addr, end);

		/* try section mapping first */
		if (((addr | next | phys) & ~SECTION_MASK) == 0 &&
		    (flags & NO_BLOCK_MAPPINGS) == 0 &&
		    !dma_overlap(phys, phys + next - addr)) {
<<<<<<< HEAD
			pmd_set_huge(pmdp, phys, prot);
=======
			pmd_set_huge(pmd, phys, prot);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

			/*
			 * After the PMD entry has been populated once, we
			 * only allow updates to the permission attributes.
			 */
			BUG_ON(!pgattr_change_is_safe(pmd_val(old_pmd),
<<<<<<< HEAD
						      READ_ONCE(pmd_val(*pmdp))));
		} else {
			alloc_init_cont_pte(pmdp, addr, next, phys, prot,
					    pgtable_alloc, flags);

			BUG_ON(pmd_val(old_pmd) != 0 &&
			       pmd_val(old_pmd) != READ_ONCE(pmd_val(*pmdp)));
		}
		phys += next - addr;
	} while (pmdp++, addr = next, addr != end);
=======
						      pmd_val(*pmd)));
		} else {
			alloc_init_cont_pte(pmd, addr, next, phys, prot,
					    pgtable_alloc, flags);

			BUG_ON(pmd_val(old_pmd) != 0 &&
			       pmd_val(old_pmd) != pmd_val(*pmd));
		}
		phys += next - addr;
	} while (pmd++, addr = next, addr != end);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	pmd_clear_fixmap();
}

<<<<<<< HEAD
static void alloc_init_cont_pmd(pud_t *pudp, unsigned long addr,
=======
static void alloc_init_cont_pmd(pud_t *pud, unsigned long addr,
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
				unsigned long end, phys_addr_t phys,
				pgprot_t prot,
				phys_addr_t (*pgtable_alloc)(void), int flags)
{
	unsigned long next;
<<<<<<< HEAD
	pud_t pud = READ_ONCE(*pudp);
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	/*
	 * Check for initial section mappings in the pgd/pud.
	 */
<<<<<<< HEAD
	BUG_ON(pud_sect(pud));
	if (pud_none(pud)) {
		phys_addr_t pmd_phys;
		BUG_ON(!pgtable_alloc);
		pmd_phys = pgtable_alloc();
		__pud_populate(pudp, pmd_phys, PUD_TYPE_TABLE);
		pud = READ_ONCE(*pudp);
	}
	BUG_ON(pud_bad(pud));
=======
	BUG_ON(pud_sect(*pud));
	if (pud_none(*pud)) {
		phys_addr_t pmd_phys;
		BUG_ON(!pgtable_alloc);
		pmd_phys = pgtable_alloc();
		__pud_populate(pud, pmd_phys, PUD_TYPE_TABLE);
	}
	BUG_ON(pud_bad(*pud));
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	do {
		pgprot_t __prot = prot;

		next = pmd_cont_addr_end(addr, end);

		/* use a contiguous mapping if the range is suitably aligned */
		if ((((addr | next | phys) & ~CONT_PMD_MASK) == 0) &&
		    (flags & NO_CONT_MAPPINGS) == 0)
			__prot = __pgprot(pgprot_val(prot) | PTE_CONT);

<<<<<<< HEAD
		init_pmd(pudp, addr, next, phys, __prot, pgtable_alloc, flags);
=======
		init_pmd(pud, addr, next, phys, __prot, pgtable_alloc, flags);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

		phys += next - addr;
	} while (addr = next, addr != end);
}

static inline bool use_1G_block(unsigned long addr, unsigned long next,
			unsigned long phys)
{
	if (PAGE_SHIFT != 12)
		return false;

	if (((addr | next | phys) & ~PUD_MASK) != 0)
		return false;

	return true;
}

<<<<<<< HEAD
static void alloc_init_pud(pgd_t *pgdp, unsigned long addr, unsigned long end,
			   phys_addr_t phys, pgprot_t prot,
			   phys_addr_t (*pgtable_alloc)(void),
			   int flags)
{
	unsigned long next;
	pud_t *pudp;
	pgd_t pgd = READ_ONCE(*pgdp);

	if (pgd_none(pgd)) {
		phys_addr_t pud_phys;
		BUG_ON(!pgtable_alloc);
		pud_phys = pgtable_alloc();
		__pgd_populate(pgdp, pud_phys, PUD_TYPE_TABLE);
		pgd = READ_ONCE(*pgdp);
	}
	BUG_ON(pgd_bad(pgd));

	pudp = pud_set_fixmap_offset(pgdp, addr);
	do {
		pud_t old_pud = READ_ONCE(*pudp);
=======
static void alloc_init_pud(pgd_t *pgd, unsigned long addr, unsigned long end,
				  phys_addr_t phys, pgprot_t prot,
				  phys_addr_t (*pgtable_alloc)(void),
				  int flags)
{
	pud_t *pud;
	unsigned long next;

	if (pgd_none(*pgd)) {
		phys_addr_t pud_phys;
		BUG_ON(!pgtable_alloc);
		pud_phys = pgtable_alloc();
		__pgd_populate(pgd, pud_phys, PUD_TYPE_TABLE);
	}
	BUG_ON(pgd_bad(*pgd));

	pud = pud_set_fixmap_offset(pgd, addr);
	do {
		pud_t old_pud = *pud;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

		next = pud_addr_end(addr, end);

		/*
		 * For 4K granule only, attempt to put down a 1GB block
		 */
		if (use_1G_block(addr, next, phys) &&
		    (flags & NO_BLOCK_MAPPINGS) == 0 &&
		    !dma_overlap(phys, phys + next - addr)) {
<<<<<<< HEAD
			pud_set_huge(pudp, phys, prot);
=======
			pud_set_huge(pud, phys, prot);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

			/*
			 * After the PUD entry has been populated once, we
			 * only allow updates to the permission attributes.
			 */
			BUG_ON(!pgattr_change_is_safe(pud_val(old_pud),
<<<<<<< HEAD
						      READ_ONCE(pud_val(*pudp))));
		} else {
			alloc_init_cont_pmd(pudp, addr, next, phys, prot,
					    pgtable_alloc, flags);

			BUG_ON(pud_val(old_pud) != 0 &&
			       pud_val(old_pud) != READ_ONCE(pud_val(*pudp)));
		}
		phys += next - addr;
	} while (pudp++, addr = next, addr != end);
=======
						      pud_val(*pud)));
		} else {
			alloc_init_cont_pmd(pud, addr, next, phys, prot,
					    pgtable_alloc, flags);

			BUG_ON(pud_val(old_pud) != 0 &&
			       pud_val(old_pud) != pud_val(*pud));
		}
		phys += next - addr;
	} while (pud++, addr = next, addr != end);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	pud_clear_fixmap();
}

static void __create_pgd_mapping(pgd_t *pgdir, phys_addr_t phys,
				 unsigned long virt, phys_addr_t size,
				 pgprot_t prot,
				 phys_addr_t (*pgtable_alloc)(void),
				 int flags)
{
	unsigned long addr, length, end, next;
<<<<<<< HEAD
	pgd_t *pgdp = pgd_offset_raw(pgdir, virt);
=======
	pgd_t *pgd = pgd_offset_raw(pgdir, virt);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	/*
	 * If the virtual and physical address don't have the same offset
	 * within a page, we cannot map the region as the caller expects.
	 */
	if (WARN_ON((phys ^ virt) & ~PAGE_MASK))
		return;

	phys &= PAGE_MASK;
	addr = virt & PAGE_MASK;
	length = PAGE_ALIGN(size + (virt & ~PAGE_MASK));

	end = addr + length;
	do {
		next = pgd_addr_end(addr, end);
<<<<<<< HEAD
		alloc_init_pud(pgdp, addr, next, phys, prot, pgtable_alloc,
			       flags);
		phys += next - addr;
	} while (pgdp++, addr = next, addr != end);
=======
		alloc_init_pud(pgd, addr, next, phys, prot, pgtable_alloc,
			       flags);
		phys += next - addr;
	} while (pgd++, addr = next, addr != end);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
}

static phys_addr_t pgd_pgtable_alloc(void)
{
	void *ptr = (void *)__get_free_page(PGALLOC_GFP);
	if (!ptr || !pgtable_page_ctor(virt_to_page(ptr)))
		BUG();

	/* Ensure the zeroed page is visible to the page table walker */
	dsb(ishst);
	return __pa(ptr);
}

void create_pgtable_mapping(phys_addr_t start, phys_addr_t end)
{
	unsigned long virt = (unsigned long)phys_to_virt(start);

	__create_pgd_mapping(init_mm.pgd, start, virt, end - start,
				PAGE_KERNEL, NULL, 0);
}

/*
 * This function can only be used to modify existing table entries,
 * without allocating new levels of table. Note that this permits the
 * creation of new section or page entries.
 */
static void __init create_mapping_noalloc(phys_addr_t phys, unsigned long virt,
				  phys_addr_t size, pgprot_t prot)
{
	if (virt < VMALLOC_START) {
		pr_warn("BUG: not creating mapping for %pa at 0x%016lx - outside kernel range\n",
			&phys, virt);
		return;
	}
	__create_pgd_mapping(init_mm.pgd, phys, virt, size, prot, NULL,
			     NO_CONT_MAPPINGS);
}

void __init create_pgd_mapping(struct mm_struct *mm, phys_addr_t phys,
			       unsigned long virt, phys_addr_t size,
			       pgprot_t prot, bool page_mappings_only)
{
	int flags = 0;

	BUG_ON(mm == &init_mm);

	if (page_mappings_only)
		flags = NO_BLOCK_MAPPINGS | NO_CONT_MAPPINGS;

	__create_pgd_mapping(mm->pgd, phys, virt, size, prot,
			     pgd_pgtable_alloc, flags);
}

static void update_mapping_prot(phys_addr_t phys, unsigned long virt,
				phys_addr_t size, pgprot_t prot)
{
	if (virt < VMALLOC_START) {
		pr_warn("BUG: not updating mapping for %pa at 0x%016lx - outside kernel range\n",
			&phys, virt);
		return;
	}

	__create_pgd_mapping(init_mm.pgd, phys, virt, size, prot, NULL,
			     NO_CONT_MAPPINGS);

	/* flush the TLBs after updating live kernel mappings */
	flush_tlb_kernel_range(virt, virt + size);
}

<<<<<<< HEAD
static void __init __map_memblock(pgd_t *pgdp, phys_addr_t start,
				  phys_addr_t end, pgprot_t prot, int flags)
{
	__create_pgd_mapping(pgdp, start, __phys_to_virt(start), end - start,
=======
static void __init __map_memblock(pgd_t *pgd, phys_addr_t start,
				  phys_addr_t end, pgprot_t prot, int flags)
{
	__create_pgd_mapping(pgd, start, __phys_to_virt(start), end - start,
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
			     prot, early_pgtable_alloc, flags);
}

void __init mark_linear_text_alias_ro(void)
{
	/*
	 * Remove the write permissions from the linear alias of .text/.rodata
	 */
	update_mapping_prot(__pa_symbol(_text), (unsigned long)lm_alias(_text),
			    (unsigned long)__init_begin - (unsigned long)_text,
			    PAGE_KERNEL_RO);
}

<<<<<<< HEAD
static void __init map_mem(pgd_t *pgdp)
=======
static void __init map_mem(pgd_t *pgd)
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
{
	phys_addr_t kernel_start = __pa_symbol(_text);
	phys_addr_t kernel_end = __pa_symbol(__init_begin);
	struct memblock_region *reg;
	int flags = 0;

	if (debug_pagealloc_enabled())
		flags = NO_BLOCK_MAPPINGS | NO_CONT_MAPPINGS;

	/*
	 * Take care not to create a writable alias for the
	 * read-only text and rodata sections of the kernel image.
	 * So temporarily mark them as NOMAP to skip mappings in
	 * the following for-loop
	 */
	memblock_mark_nomap(kernel_start, kernel_end - kernel_start);
#ifdef CONFIG_KEXEC_CORE
	if (crashk_res.end)
		memblock_mark_nomap(crashk_res.start,
				    resource_size(&crashk_res));
#endif

	/* map all the memory banks */
	for_each_memblock(memory, reg) {
		phys_addr_t start = reg->base;
		phys_addr_t end = start + reg->size;

		if (start >= end)
			break;
		if (memblock_is_nomap(reg))
			continue;

<<<<<<< HEAD
		__map_memblock(pgdp, start, end, PAGE_KERNEL, flags);
=======
		__map_memblock(pgd, start, end, PAGE_KERNEL, flags);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	}

	/*
	 * Map the linear alias of the [_text, __init_begin) interval
	 * as non-executable now, and remove the write permission in
	 * mark_linear_text_alias_ro() below (which will be called after
	 * alternative patching has completed). This makes the contents
	 * of the region accessible to subsystems such as hibernate,
	 * but protects it from inadvertent modification or execution.
	 * Note that contiguous mappings cannot be remapped in this way,
	 * so we should avoid them here.
	 */
<<<<<<< HEAD
	__map_memblock(pgdp, kernel_start, kernel_end,
=======
	__map_memblock(pgd, kernel_start, kernel_end,
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
		       PAGE_KERNEL, NO_CONT_MAPPINGS);
	memblock_clear_nomap(kernel_start, kernel_end - kernel_start);

#ifdef CONFIG_KEXEC_CORE
	/*
	 * Use page-level mappings here so that we can shrink the region
	 * in page granularity and put back unused memory to buddy system
	 * through /sys/kernel/kexec_crash_size interface.
	 */
	if (crashk_res.end) {
<<<<<<< HEAD
		__map_memblock(pgdp, crashk_res.start, crashk_res.end + 1,
=======
		__map_memblock(pgd, crashk_res.start, crashk_res.end + 1,
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
			       PAGE_KERNEL,
			       NO_BLOCK_MAPPINGS | NO_CONT_MAPPINGS);
		memblock_clear_nomap(crashk_res.start,
				     resource_size(&crashk_res));
	}
#endif
}

void mark_rodata_ro(void)
{
	unsigned long section_size;

	/*
	 * mark .rodata as read only. Use __init_begin rather than __end_rodata
	 * to cover NOTES and EXCEPTION_TABLE.
	 */
	section_size = (unsigned long)__init_begin - (unsigned long)__start_rodata;
	update_mapping_prot(__pa_symbol(__start_rodata), (unsigned long)__start_rodata,
			    section_size, PAGE_KERNEL_RO);

	debug_checkwx();
}

<<<<<<< HEAD
static void __init map_kernel_segment(pgd_t *pgdp, void *va_start, void *va_end,
=======
static void __init map_kernel_segment(pgd_t *pgd, void *va_start, void *va_end,
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
				      pgprot_t prot, struct vm_struct *vma,
				      int flags, unsigned long vm_flags)
{
	phys_addr_t pa_start = __pa_symbol(va_start);
	unsigned long size = va_end - va_start;

	BUG_ON(!PAGE_ALIGNED(pa_start));
	BUG_ON(!PAGE_ALIGNED(size));

<<<<<<< HEAD
	__create_pgd_mapping(pgdp, pa_start, (unsigned long)va_start, size, prot,
=======
	__create_pgd_mapping(pgd, pa_start, (unsigned long)va_start, size, prot,
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
			     early_pgtable_alloc, flags);

	if (!(vm_flags & VM_NO_GUARD))
		size += PAGE_SIZE;

	vma->addr	= va_start;
	vma->phys_addr	= pa_start;
	vma->size	= size;
	vma->flags	= VM_MAP | vm_flags;
	vma->caller	= __builtin_return_address(0);

	vm_area_add_early(vma);
}

static int __init parse_rodata(char *arg)
{
	return strtobool(arg, &rodata_enabled);
}
early_param("rodata", parse_rodata);

#ifdef CONFIG_UNMAP_KERNEL_AT_EL0
static int __init map_entry_trampoline(void)
{
<<<<<<< HEAD
=======
	extern char __entry_tramp_text_start[];

>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	pgprot_t prot = rodata_enabled ? PAGE_KERNEL_ROX : PAGE_KERNEL_EXEC;
	phys_addr_t pa_start = __pa_symbol(__entry_tramp_text_start);

	/* The trampoline is always mapped and can therefore be global */
	pgprot_val(prot) &= ~PTE_NG;

	/* Map only the text into the trampoline page table */
	memset(tramp_pg_dir, 0, PGD_SIZE);
	__create_pgd_mapping(tramp_pg_dir, pa_start, TRAMP_VALIAS, PAGE_SIZE,
			     prot, pgd_pgtable_alloc, 0);

	/* Map both the text and data into the kernel page table */
	__set_fixmap(FIX_ENTRY_TRAMP_TEXT, pa_start, prot);
	if (IS_ENABLED(CONFIG_RANDOMIZE_BASE)) {
		extern char __entry_tramp_data_start[];

		__set_fixmap(FIX_ENTRY_TRAMP_DATA,
			     __pa_symbol(__entry_tramp_data_start),
			     PAGE_KERNEL_RO);
	}

	return 0;
}
core_initcall(map_entry_trampoline);
#endif

/*
 * Create fine-grained mappings for the kernel.
 */
<<<<<<< HEAD
static void __init map_kernel(pgd_t *pgdp)
=======
static void __init map_kernel(pgd_t *pgd)
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
{
	static struct vm_struct vmlinux_text, vmlinux_rodata, vmlinux_inittext,
				vmlinux_initdata, vmlinux_data;

	/*
	 * External debuggers may need to write directly to the text
	 * mapping to install SW breakpoints. Allow this (only) when
	 * explicitly requested with rodata=off.
	 */
	pgprot_t text_prot = rodata_enabled ? PAGE_KERNEL_ROX : PAGE_KERNEL_EXEC;

	/*
	 * Only rodata will be remapped with different permissions later on,
	 * all other segments are allowed to use contiguous mappings.
	 */
<<<<<<< HEAD
	map_kernel_segment(pgdp, _text, _etext, text_prot, &vmlinux_text, 0,
			   VM_NO_GUARD);
	map_kernel_segment(pgdp, __start_rodata, __inittext_begin, PAGE_KERNEL,
			   &vmlinux_rodata, NO_CONT_MAPPINGS, VM_NO_GUARD);
	map_kernel_segment(pgdp, __inittext_begin, __inittext_end, text_prot,
			   &vmlinux_inittext, 0, VM_NO_GUARD);
	map_kernel_segment(pgdp, __initdata_begin, __initdata_end, PAGE_KERNEL,
			   &vmlinux_initdata, 0, VM_NO_GUARD);
	map_kernel_segment(pgdp, _data, _end, PAGE_KERNEL, &vmlinux_data, 0, 0);

	if (!READ_ONCE(pgd_val(*pgd_offset_raw(pgdp, FIXADDR_START)))) {
=======
	map_kernel_segment(pgd, _text, _etext, text_prot, &vmlinux_text, 0,
			   VM_NO_GUARD);
	map_kernel_segment(pgd, __start_rodata, __inittext_begin, PAGE_KERNEL,
			   &vmlinux_rodata, NO_CONT_MAPPINGS, VM_NO_GUARD);
	map_kernel_segment(pgd, __inittext_begin, __inittext_end, text_prot,
			   &vmlinux_inittext, 0, VM_NO_GUARD);
	map_kernel_segment(pgd, __initdata_begin, __initdata_end, PAGE_KERNEL,
			   &vmlinux_initdata, 0, VM_NO_GUARD);
	map_kernel_segment(pgd, _data, _end, PAGE_KERNEL, &vmlinux_data, 0, 0);

	if (!pgd_val(*pgd_offset_raw(pgd, FIXADDR_START))) {
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
		/*
		 * The fixmap falls in a separate pgd to the kernel, and doesn't
		 * live in the carveout for the swapper_pg_dir. We can simply
		 * re-use the existing dir for the fixmap.
		 */
<<<<<<< HEAD
		set_pgd(pgd_offset_raw(pgdp, FIXADDR_START),
			READ_ONCE(*pgd_offset_k(FIXADDR_START)));
=======
		set_pgd(pgd_offset_raw(pgd, FIXADDR_START),
			*pgd_offset_k(FIXADDR_START));
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	} else if (CONFIG_PGTABLE_LEVELS > 3) {
		/*
		 * The fixmap shares its top level pgd entry with the kernel
		 * mapping. This can really only occur when we are running
		 * with 16k/4 levels, so we can simply reuse the pud level
		 * entry instead.
		 */
		BUG_ON(!IS_ENABLED(CONFIG_ARM64_16K_PAGES));
<<<<<<< HEAD
		pud_populate(&init_mm,
			     pud_set_fixmap_offset(pgdp, FIXADDR_START),
=======
		pud_populate(&init_mm, pud_set_fixmap_offset(pgd, FIXADDR_START),
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
			     lm_alias(bm_pmd));
		pud_clear_fixmap();
	} else {
		BUG();
	}

<<<<<<< HEAD
	kasan_copy_shadow(pgdp);
=======
	kasan_copy_shadow(pgd);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
}

/*
 * paging_init() sets up the page tables, initialises the zone memory
 * maps and sets up the zero page.
 */
void __init paging_init(void)
{
	phys_addr_t pgd_phys = early_pgtable_alloc();
<<<<<<< HEAD
	pgd_t *pgdp = pgd_set_fixmap(pgd_phys);

	map_kernel(pgdp);
	map_mem(pgdp);
=======
	pgd_t *pgd = pgd_set_fixmap(pgd_phys);

	map_kernel(pgd);
	map_mem(pgd);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	/*
	 * We want to reuse the original swapper_pg_dir so we don't have to
	 * communicate the new address to non-coherent secondaries in
	 * secondary_entry, and so cpu_switch_mm can generate the address with
	 * adrp+add rather than a load from some global variable.
	 *
	 * To do this we need to go via a temporary pgd.
	 */
	cpu_replace_ttbr1(__va(pgd_phys));
<<<<<<< HEAD
	memcpy(swapper_pg_dir, pgdp, PGD_SIZE);
=======
	memcpy(swapper_pg_dir, pgd, PGD_SIZE);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	cpu_replace_ttbr1(lm_alias(swapper_pg_dir));

	pgd_clear_fixmap();
	memblock_free(pgd_phys, PAGE_SIZE);

	/*
	 * We only reuse the PGD from the swapper_pg_dir, not the pud + pmd
	 * allocated with it.
	 */
	memblock_free(__pa_symbol(swapper_pg_dir) + PAGE_SIZE,
<<<<<<< HEAD
		      __pa_symbol(swapper_pg_end) - __pa_symbol(swapper_pg_dir)
		      - PAGE_SIZE);
=======
		      SWAPPER_DIR_SIZE - PAGE_SIZE);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
}

#ifdef CONFIG_MEMORY_HOTPLUG
/*
 * hotplug_paging() is used by memory hotplug to build new page tables
 * for hot added memory.
 */
void hotplug_paging(phys_addr_t start, phys_addr_t size)
{
	int flags;

	flags = debug_pagealloc_enabled() ? NO_BLOCK_MAPPINGS : 0;
	__create_pgd_mapping(swapper_pg_dir, start, __phys_to_virt(start), size,
		PAGE_KERNEL, pgd_pgtable_alloc, flags);
}

#ifdef CONFIG_MEMORY_HOTREMOVE
#define PAGE_INUSE 0xFD

static void  free_pagetable(struct page *page, int order, bool direct)
{
	unsigned long magic;
	unsigned int nr_pages = 1 << order;

	/* bootmem page has reserved flag */
	if (PageReserved(page)) {
		__ClearPageReserved(page);

		magic = (unsigned long)page->lru.next;
		if (magic == SECTION_INFO || magic == MIX_SECTION_INFO) {
			while (nr_pages--)
				put_page_bootmem(page++);
		} else {
			while (nr_pages--)
				free_reserved_page(page++);
		}
	} else {
		/*
		 * Only direct pagetable allocation (those allocated via
		 * hotplug) call the pgtable_page_ctor; vmemmap pgtable
		 * allocations don't.
		 */
		if (direct)
			pgtable_page_dtor(page);

		free_pages((unsigned long)page_address(page), order);
	}
}

static void free_pte_table(pmd_t *pmd, bool direct)
{
	pte_t *pte_start, *pte;
	struct page *page;
	int i;

	pte_start =  (pte_t *) pmd_page_vaddr(*pmd);
	/* Check if there is no valid entry in the PMD */
	for (i = 0; i < PTRS_PER_PTE; i++) {
		pte = pte_start + i;
		if (!pte_none(*pte))
			return;
	}

	page = pmd_page(*pmd);

	free_pagetable(page, 0, direct);

	/*
	 * This spin lock could be only taken in _pte_aloc_kernel
	 * in mm/memory.c and nowhere else (for arm64). Not sure if
	 * the function above can be called concurrently. In doubt,
	 * I am living it here for now, but it probably can be removed
	 */
	spin_lock(&init_mm.page_table_lock);
	pmd_clear(pmd);
	spin_unlock(&init_mm.page_table_lock);
}

static void free_pmd_table(pud_t *pud, bool direct)
{
	pmd_t *pmd_start, *pmd;
	struct page *page;
	int i;

	pmd_start = (pmd_t *) pud_page_vaddr(*pud);
	/* Check if there is no valid entry in the PMD */
	for (i = 0; i < PTRS_PER_PMD; i++) {
		pmd = pmd_start + i;
		if (!pmd_none(*pmd))
			return;
	}

	page = pud_page(*pud);

	free_pagetable(page, 0, direct);

	/*
	 * This spin lock could be only taken in _pte_aloc_kernel
	 * in mm/memory.c and nowhere else (for arm64). Not sure if
	 * the function above can be called concurrently. In doubt,
	 * I am living it here for now, but it probably can be removed
	 */
	spin_lock(&init_mm.page_table_lock);
	pud_clear(pud);
	spin_unlock(&init_mm.page_table_lock);
}

/*
 * When the PUD is folded on the PGD (three levels of paging),
 * there's no need to free PUDs
 */
#if CONFIG_PGTABLE_LEVELS > 3
static void free_pud_table(pgd_t *pgd, bool direct)
{
	pud_t *pud_start, *pud;
	struct page *page;
	int i;

	pud_start = (pud_t *) pgd_page_vaddr(*pgd);
	/* Check if there is no valid entry in the PUD */
	for (i = 0; i < PTRS_PER_PUD; i++) {
		pud = pud_start + i;
		if (!pud_none(*pud))
			return;
	}

	page = pgd_page(*pgd);

	free_pagetable(page, 0, direct);

	/*
	 * This spin lock could be only
	 * taken in _pte_aloc_kernel in
	 * mm/memory.c and nowhere else
	 * (for arm64). Not sure if the
	 * function above can be called
	 * concurrently. In doubt,
	 * I am living it here for now,
	 * but it probably can be removed.
	 */
	spin_lock(&init_mm.page_table_lock);
	pgd_clear(pgd);
	spin_unlock(&init_mm.page_table_lock);
}
#endif

static void remove_pte_table(pte_t *pte, unsigned long addr,
	unsigned long end, bool direct)
{
	unsigned long next;
	void *page_addr;

	for (; addr < end; addr = next, pte++) {
		next = (addr + PAGE_SIZE) & PAGE_MASK;
		if (next > end)
			next = end;

		if (!pte_present(*pte))
			continue;

		if (PAGE_ALIGNED(addr) && PAGE_ALIGNED(next)) {
			/*
			 * Do not free direct mapping pages since they were
			 * freed when offlining, or simplely not in use.
			 */
			if (!direct)
				free_pagetable(pte_page(*pte), 0, direct);

			/*
			 * This spin lock could be only
			 * taken in _pte_aloc_kernel in
			 * mm/memory.c and nowhere else
			 * (for arm64). Not sure if the
			 * function above can be called
			 * concurrently. In doubt,
			 * I am living it here for now,
			 * but it probably can be removed.
			 */
			spin_lock(&init_mm.page_table_lock);
			pte_clear(&init_mm, addr, pte);
			spin_unlock(&init_mm.page_table_lock);
		} else {
			/*
			 * If we are here, we are freeing vmemmap pages since
			 * direct mapped memory ranges to be freed are aligned.
			 *
			 * If we are not removing the whole page, it means
			 * other page structs in this page are being used and
			 * we canot remove them. So fill the unused page_structs
			 * with 0xFD, and remove the page when it is wholly
			 * filled with 0xFD.
			 */
			memset((void *)addr, PAGE_INUSE, next - addr);

			page_addr = page_address(pte_page(*pte));
			if (!memchr_inv(page_addr, PAGE_INUSE, PAGE_SIZE)) {
				free_pagetable(pte_page(*pte), 0, direct);

				/*
				 * This spin lock could be only
				 * taken in _pte_aloc_kernel in
				 * mm/memory.c and nowhere else
				 * (for arm64). Not sure if the
				 * function above can be called
				 * concurrently. In doubt,
				 * I am living it here for now,
				 * but it probably can be removed.
				 */
				spin_lock(&init_mm.page_table_lock);
				pte_clear(&init_mm, addr, pte);
				spin_unlock(&init_mm.page_table_lock);
			}
		}
	}

	// I am adding this flush here in simmetry to the x86 code.
	// Why do I need to call it here and not in remove_p[mu]d
	flush_tlb_all();
}

static void remove_pmd_table(pmd_t *pmd, unsigned long addr,
	unsigned long end, bool direct)
{
	unsigned long next;
	void *page_addr;
	pte_t *pte;

	for (; addr < end; addr = next, pmd++) {
		next = pmd_addr_end(addr, end);

		if (!pmd_present(*pmd))
			continue;

		// check if we are using 2MB section mappings
		if (pmd_sect(*pmd)) {
			if (PAGE_ALIGNED(addr) && PAGE_ALIGNED(next)) {
				if (!direct) {
					free_pagetable(pmd_page(*pmd),
						get_order(PMD_SIZE), direct);
				}
				/*
				 * This spin lock could be only
				 * taken in _pte_aloc_kernel in
				 * mm/memory.c and nowhere else
				 * (for arm64). Not sure if the
				 * function above can be called
				 * concurrently. In doubt,
				 * I am living it here for now,
				 * but it probably can be removed.
				 */
				spin_lock(&init_mm.page_table_lock);
				pmd_clear(pmd);
				spin_unlock(&init_mm.page_table_lock);
			} else {
				/* If here, we are freeing vmemmap pages. */
				memset((void *)addr, PAGE_INUSE, next - addr);

				page_addr = page_address(pmd_page(*pmd));
				if (!memchr_inv(page_addr, PAGE_INUSE,
						PMD_SIZE)) {
					free_pagetable(pmd_page(*pmd),
						get_order(PMD_SIZE), direct);

					/*
					 * This spin lock could be only
					 * taken in _pte_aloc_kernel in
					 * mm/memory.c and nowhere else
					 * (for arm64). Not sure if the
					 * function above can be called
					 * concurrently. In doubt,
					 * I am living it here for now,
					 * but it probably can be removed.
					 */
					spin_lock(&init_mm.page_table_lock);
					pmd_clear(pmd);
					spin_unlock(&init_mm.page_table_lock);
				}
			}
			continue;
		}

		BUG_ON(!pmd_table(*pmd));

		pte = pte_offset_map(pmd, addr);
		remove_pte_table(pte, addr, next, direct);
		free_pte_table(pmd, direct);
	}
}

static void remove_pud_table(pud_t *pud, unsigned long addr,
	unsigned long end, bool direct)
{
	unsigned long next;
	pmd_t *pmd;
	void *page_addr;

	for (; addr < end; addr = next, pud++) {
		next = pud_addr_end(addr, end);
		if (!pud_present(*pud))
			continue;
		/*
		 * If we are using 4K granules, check if we are using
		 * 1GB section mapping.
		 */
		if (pud_sect(*pud)) {
			if (PAGE_ALIGNED(addr) && PAGE_ALIGNED(next)) {
				if (!direct) {
					free_pagetable(pud_page(*pud),
						get_order(PUD_SIZE), direct);
				}

				/*
				 * This spin lock could be only
				 * taken in _pte_aloc_kernel in
				 * mm/memory.c and nowhere else
				 * (for arm64). Not sure if the
				 * function above can be called
				 * concurrently. In doubt,
				 * I am living it here for now,
				 * but it probably can be removed.
				 */
				spin_lock(&init_mm.page_table_lock);
				pud_clear(pud);
				spin_unlock(&init_mm.page_table_lock);
			} else {
				/* If here, we are freeing vmemmap pages. */
				memset((void *)addr, PAGE_INUSE, next - addr);

				page_addr = page_address(pud_page(*pud));
				if (!memchr_inv(page_addr, PAGE_INUSE,
						PUD_SIZE)) {

					free_pagetable(pud_page(*pud),
						get_order(PUD_SIZE), direct);

					/*
					 * This spin lock could be only
					 * taken in _pte_aloc_kernel in
					 * mm/memory.c and nowhere else
					 * (for arm64). Not sure if the
					 * function above can be called
					 * concurrently. In doubt,
					 * I am living it here for now,
					 * but it probably can be removed.
					 */
					spin_lock(&init_mm.page_table_lock);
					pud_clear(pud);
					spin_unlock(&init_mm.page_table_lock);
				}
			}
			continue;
		}

		BUG_ON(!pud_table(*pud));

		pmd = pmd_offset(pud, addr);
		remove_pmd_table(pmd, addr, next, direct);
		free_pmd_table(pud, direct);
	}
}

void remove_pagetable(unsigned long start, unsigned long end, bool direct)
{
	unsigned long next;
	unsigned long addr;
	pgd_t *pgd;
	pud_t *pud;

	for (addr = start; addr < end; addr = next) {
		next = pgd_addr_end(addr, end);

		pgd = pgd_offset_k(addr);
		if (pgd_none(*pgd))
			continue;

		pud = pud_offset(pgd, addr);
		remove_pud_table(pud, addr, next, direct);
		/*
		 * When the PUD is folded on the PGD (three levels of paging),
		 * I did already clear the PMD page in free_pmd_table,
		 * and reset the corresponding PGD==PUD entry.
		 */
#if CONFIG_PGTABLE_LEVELS > 3
		free_pud_table(pgd, direct);
#endif
	}

	flush_tlb_all();
}


#endif /* CONFIG_MEMORY_HOTREMOVE */
#endif /* CONFIG_MEMORY_HOTPLUG */

/*
 * Check whether a kernel address is valid (derived from arch/x86/).
 */
int kern_addr_valid(unsigned long addr)
{
<<<<<<< HEAD
	pgd_t *pgdp;
	pud_t *pudp, pud;
	pmd_t *pmdp, pmd;
	pte_t *ptep, pte;
=======
	pgd_t *pgd;
	pud_t *pud;
	pmd_t *pmd;
	pte_t *pte;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	if ((((long)addr) >> VA_BITS) != -1UL)
		return 0;

<<<<<<< HEAD
	pgdp = pgd_offset_k(addr);
	if (pgd_none(READ_ONCE(*pgdp)))
		return 0;

	pudp = pud_offset(pgdp, addr);
	pud = READ_ONCE(*pudp);
	if (pud_none(pud))
		return 0;

	if (pud_sect(pud))
		return pfn_valid(pud_pfn(pud));

	pmdp = pmd_offset(pudp, addr);
	pmd = READ_ONCE(*pmdp);
	if (pmd_none(pmd))
		return 0;

	if (pmd_sect(pmd))
		return pfn_valid(pmd_pfn(pmd));

	ptep = pte_offset_kernel(pmdp, addr);
	pte = READ_ONCE(*ptep);
	if (pte_none(pte))
		return 0;

	return pfn_valid(pte_pfn(pte));
}
#ifdef CONFIG_SPARSEMEM_VMEMMAP
#if !ARM64_SWAPPER_USES_SECTION_MAPS
int __meminit vmemmap_populate(unsigned long start, unsigned long end, int node,
		struct vmem_altmap *altmap)
=======
	pgd = pgd_offset_k(addr);
	if (pgd_none(*pgd))
		return 0;

	pud = pud_offset(pgd, addr);
	if (pud_none(*pud))
		return 0;

	if (pud_sect(*pud))
		return pfn_valid(pud_pfn(*pud));

	pmd = pmd_offset(pud, addr);
	if (pmd_none(*pmd))
		return 0;

	if (pmd_sect(*pmd))
		return pfn_valid(pmd_pfn(*pmd));

	pte = pte_offset_kernel(pmd, addr);
	if (pte_none(*pte))
		return 0;

	return pfn_valid(pte_pfn(*pte));
}
#ifdef CONFIG_SPARSEMEM_VMEMMAP
#if !ARM64_SWAPPER_USES_SECTION_MAPS
int __meminit vmemmap_populate(unsigned long start, unsigned long end, int node)
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
{
	return vmemmap_populate_basepages(start, end, node);
}
#else	/* !ARM64_SWAPPER_USES_SECTION_MAPS */
<<<<<<< HEAD
int __meminit vmemmap_populate(unsigned long start, unsigned long end, int node,
		struct vmem_altmap *altmap)
{
	unsigned long addr = start;
	unsigned long next;
	pgd_t *pgdp;
	pud_t *pudp;
	pmd_t *pmdp;
=======
int __meminit vmemmap_populate(unsigned long start, unsigned long end, int node)
{
	unsigned long addr = start;
	unsigned long next;
	pgd_t *pgd;
	pud_t *pud;
	pmd_t *pmd;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	int ret = 0;

	do {
		next = pmd_addr_end(addr, end);

<<<<<<< HEAD
		pgdp = vmemmap_pgd_populate(addr, node);
		if (!pgdp)
			return -ENOMEM;

		pudp = vmemmap_pud_populate(pgdp, addr, node);
		if (!pudp)
			return -ENOMEM;

		pmdp = pmd_offset(pudp, addr);
		if (pmd_none(READ_ONCE(*pmdp))) {
=======
		pgd = vmemmap_pgd_populate(addr, node);
		if (!pgd)
			return -ENOMEM;

		pud = vmemmap_pud_populate(pgd, addr, node);
		if (!pud)
			return -ENOMEM;

		pmd = pmd_offset(pud, addr);
		if (pmd_none(*pmd)) {
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
			void *p = NULL;

			p = vmemmap_alloc_block_buf(PMD_SIZE, node);
			if (!p) {
#ifdef CONFIG_MEMORY_HOTPLUG
<<<<<<< HEAD
				vmemmap_free(start, end, altmap);
=======
				vmemmap_free(start, end);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
#endif
				ret = -ENOMEM;
				break;
			}

<<<<<<< HEAD
			pmd_set_huge(pmdp, __pa(p), __pgprot(PROT_SECT_NORMAL));
		} else
			vmemmap_verify((pte_t *)pmdp, node, addr, next);
=======
			pmd_set_huge(pmd, __pa(p), __pgprot(PROT_SECT_NORMAL));
		} else
			vmemmap_verify((pte_t *)pmd, node, addr, next);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	} while (addr = next, addr != end);

	if (ret)
		return vmemmap_populate_basepages(start, end, node);
	else
		return ret;
}
#endif	/* CONFIG_ARM64_64K_PAGES */
<<<<<<< HEAD
void vmemmap_free(unsigned long start, unsigned long end,
		struct vmem_altmap *altmap)
=======
void vmemmap_free(unsigned long start, unsigned long end)
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
{
#ifdef CONFIG_MEMORY_HOTREMOVE
	remove_pagetable(start, end, false);
#endif
}
#endif	/* CONFIG_SPARSEMEM_VMEMMAP */

static inline pud_t * fixmap_pud(unsigned long addr)
{
<<<<<<< HEAD
	pgd_t *pgdp = pgd_offset_k(addr);
	pgd_t pgd = READ_ONCE(*pgdp);

	BUG_ON(pgd_none(pgd) || pgd_bad(pgd));

	return pud_offset_kimg(pgdp, addr);
=======
	pgd_t *pgd = pgd_offset_k(addr);

	BUG_ON(pgd_none(*pgd) || pgd_bad(*pgd));

	return pud_offset_kimg(pgd, addr);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
}

static inline pmd_t * fixmap_pmd(unsigned long addr)
{
<<<<<<< HEAD
	pud_t *pudp = fixmap_pud(addr);
	pud_t pud = READ_ONCE(*pudp);

	BUG_ON(pud_none(pud) || pud_bad(pud));

	return pmd_offset_kimg(pudp, addr);
=======
	pud_t *pud = fixmap_pud(addr);

	BUG_ON(pud_none(*pud) || pud_bad(*pud));

	return pmd_offset_kimg(pud, addr);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
}

static inline pte_t * fixmap_pte(unsigned long addr)
{
	return &bm_pte[pte_index(addr)];
}

/*
 * The p*d_populate functions call virt_to_phys implicitly so they can't be used
 * directly on kernel symbols (bm_p*d). This function is called too early to use
 * lm_alias so __p*d_populate functions must be used to populate with the
 * physical address from __pa_symbol.
 */
void __init early_fixmap_init(void)
{
<<<<<<< HEAD
	pgd_t *pgdp, pgd;
	pud_t *pudp;
	pmd_t *pmdp;
	unsigned long addr = FIXADDR_START;

	pgdp = pgd_offset_k(addr);
	pgd = READ_ONCE(*pgdp);
	if (CONFIG_PGTABLE_LEVELS > 3 &&
	    !(pgd_none(pgd) || pgd_page_paddr(pgd) == __pa_symbol(bm_pud))) {
=======
	pgd_t *pgd;
	pud_t *pud;
	pmd_t *pmd;
	unsigned long addr = FIXADDR_START;

	pgd = pgd_offset_k(addr);
	if (CONFIG_PGTABLE_LEVELS > 3 &&
	    !(pgd_none(*pgd) || pgd_page_paddr(*pgd) == __pa_symbol(bm_pud))) {
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
		/*
		 * We only end up here if the kernel mapping and the fixmap
		 * share the top level pgd entry, which should only happen on
		 * 16k/4 levels configurations.
		 */
		BUG_ON(!IS_ENABLED(CONFIG_ARM64_16K_PAGES));
<<<<<<< HEAD
		pudp = pud_offset_kimg(pgdp, addr);
	} else {
		if (pgd_none(pgd))
			__pgd_populate(pgdp, __pa_symbol(bm_pud), PUD_TYPE_TABLE);
		pudp = fixmap_pud(addr);
	}
	if (pud_none(READ_ONCE(*pudp)))
		__pud_populate(pudp, __pa_symbol(bm_pmd), PMD_TYPE_TABLE);
	pmdp = fixmap_pmd(addr);
	__pmd_populate(pmdp, __pa_symbol(bm_pte), PMD_TYPE_TABLE);
=======
		pud = pud_offset_kimg(pgd, addr);
	} else {
		if (pgd_none(*pgd))
			__pgd_populate(pgd, __pa_symbol(bm_pud), PUD_TYPE_TABLE);
		pud = fixmap_pud(addr);
	}
	if (pud_none(*pud))
		__pud_populate(pud, __pa_symbol(bm_pmd), PMD_TYPE_TABLE);
	pmd = fixmap_pmd(addr);
	__pmd_populate(pmd, __pa_symbol(bm_pte), PMD_TYPE_TABLE);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	/*
	 * The boot-ioremap range spans multiple pmds, for which
	 * we are not prepared:
	 */
	BUILD_BUG_ON((__fix_to_virt(FIX_BTMAP_BEGIN) >> PMD_SHIFT)
		     != (__fix_to_virt(FIX_BTMAP_END) >> PMD_SHIFT));

<<<<<<< HEAD
	if ((pmdp != fixmap_pmd(fix_to_virt(FIX_BTMAP_BEGIN)))
	     || pmdp != fixmap_pmd(fix_to_virt(FIX_BTMAP_END))) {
		WARN_ON(1);
		pr_warn("pmdp %p != %p, %p\n",
			pmdp, fixmap_pmd(fix_to_virt(FIX_BTMAP_BEGIN)),
=======
	if ((pmd != fixmap_pmd(fix_to_virt(FIX_BTMAP_BEGIN)))
	     || pmd != fixmap_pmd(fix_to_virt(FIX_BTMAP_END))) {
		WARN_ON(1);
		pr_warn("pmd %p != %p, %p\n",
			pmd, fixmap_pmd(fix_to_virt(FIX_BTMAP_BEGIN)),
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
			fixmap_pmd(fix_to_virt(FIX_BTMAP_END)));
		pr_warn("fix_to_virt(FIX_BTMAP_BEGIN): %08lx\n",
			fix_to_virt(FIX_BTMAP_BEGIN));
		pr_warn("fix_to_virt(FIX_BTMAP_END):   %08lx\n",
			fix_to_virt(FIX_BTMAP_END));

		pr_warn("FIX_BTMAP_END:       %d\n", FIX_BTMAP_END);
		pr_warn("FIX_BTMAP_BEGIN:     %d\n", FIX_BTMAP_BEGIN);
	}
}

<<<<<<< HEAD
/*
 * Unusually, this is also called in IRQ context (ghes_iounmap_irq) so if we
 * ever need to use IPIs for TLB broadcasting, then we're in trouble here.
 */
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
void __set_fixmap(enum fixed_addresses idx,
			       phys_addr_t phys, pgprot_t flags)
{
	unsigned long addr = __fix_to_virt(idx);
<<<<<<< HEAD
	pte_t *ptep;

	BUG_ON(idx <= FIX_HOLE || idx >= __end_of_fixed_addresses);

	ptep = fixmap_pte(addr);

	if (pgprot_val(flags)) {
		set_pte(ptep, pfn_pte(phys >> PAGE_SHIFT, flags));
	} else {
		pte_clear(&init_mm, addr, ptep);
=======
	pte_t *pte;

	BUG_ON(idx <= FIX_HOLE || idx >= __end_of_fixed_addresses);

	pte = fixmap_pte(addr);

	if (pgprot_val(flags)) {
		set_pte(pte, pfn_pte(phys >> PAGE_SHIFT, flags));
	} else {
		pte_clear(&init_mm, addr, pte);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
		flush_tlb_kernel_range(addr, addr+PAGE_SIZE);
	}
}

void *__init __fixmap_remap_fdt(phys_addr_t dt_phys, int *size, pgprot_t prot)
{
	const u64 dt_virt_base = __fix_to_virt(FIX_FDT);
	int offset;
	void *dt_virt;

	/*
	 * Check whether the physical FDT address is set and meets the minimum
	 * alignment requirement. Since we are relying on MIN_FDT_ALIGN to be
	 * at least 8 bytes so that we can always access the magic and size
	 * fields of the FDT header after mapping the first chunk, double check
	 * here if that is indeed the case.
	 */
	BUILD_BUG_ON(MIN_FDT_ALIGN < 8);
	if (!dt_phys || dt_phys % MIN_FDT_ALIGN)
		return NULL;

	/*
	 * Make sure that the FDT region can be mapped without the need to
	 * allocate additional translation table pages, so that it is safe
	 * to call create_mapping_noalloc() this early.
	 *
	 * On 64k pages, the FDT will be mapped using PTEs, so we need to
	 * be in the same PMD as the rest of the fixmap.
	 * On 4k pages, we'll use section mappings for the FDT so we only
	 * have to be in the same PUD.
	 */
	BUILD_BUG_ON(dt_virt_base % SZ_2M);

	BUILD_BUG_ON(__fix_to_virt(FIX_FDT_END) >> SWAPPER_TABLE_SHIFT !=
		     __fix_to_virt(FIX_BTMAP_BEGIN) >> SWAPPER_TABLE_SHIFT);

	offset = dt_phys % SWAPPER_BLOCK_SIZE;
	dt_virt = (void *)dt_virt_base + offset;

	/* map the first chunk so we can read the size from the header */
	create_mapping_noalloc(round_down(dt_phys, SWAPPER_BLOCK_SIZE),
			dt_virt_base, SWAPPER_BLOCK_SIZE, prot);

	if (fdt_magic(dt_virt) != FDT_MAGIC)
		return NULL;

	*size = fdt_totalsize(dt_virt);
	if (*size > MAX_FDT_SIZE)
		return NULL;

	if (offset + *size > SWAPPER_BLOCK_SIZE)
		create_mapping_noalloc(round_down(dt_phys, SWAPPER_BLOCK_SIZE), dt_virt_base,
			       round_up(offset + *size, SWAPPER_BLOCK_SIZE), prot);

	return dt_virt;
}

void *__init fixmap_remap_fdt(phys_addr_t dt_phys)
{
	void *dt_virt;
	int size;

	dt_virt = __fixmap_remap_fdt(dt_phys, &size, PAGE_KERNEL_RO);
	if (!dt_virt)
		return NULL;

	memblock_reserve(dt_phys, size);
<<<<<<< HEAD
=======

	/*
	 * memblock_dbg is not up because of parse_early_param get called after
	 * setup_machine_fd. To capture fdt reserved info below pr_info is
	 * added.
	 */
	pr_info("memblock_reserve: 0x%x %pS\n", size - 1, (void *) _RET_IP_);

>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	return dt_virt;
}

int __init arch_ioremap_pud_supported(void)
{
	/*
	 * Only 4k granule supports level 1 block mappings.
	 * SW table walks can't handle removal of intermediate entries.
	 */
	return IS_ENABLED(CONFIG_ARM64_4K_PAGES) &&
	       !IS_ENABLED(CONFIG_ARM64_PTDUMP_DEBUGFS);
}

int __init arch_ioremap_pmd_supported(void)
{
	/* See arch_ioremap_pud_supported() */
	return !IS_ENABLED(CONFIG_ARM64_PTDUMP_DEBUGFS);
}

int pud_set_huge(pud_t *pudp, phys_addr_t phys, pgprot_t prot)
{
	pgprot_t sect_prot = __pgprot(PUD_TYPE_SECT |
					pgprot_val(mk_sect_prot(prot)));
	pud_t new_pud = pfn_pud(__phys_to_pfn(phys), sect_prot);

	/* Only allow permission changes for now */
	if (!pgattr_change_is_safe(READ_ONCE(pud_val(*pudp)),
				   pud_val(new_pud)))
		return 0;

	BUG_ON(phys & ~PUD_MASK);
	set_pud(pudp, new_pud);
	return 1;
}

int pmd_set_huge(pmd_t *pmdp, phys_addr_t phys, pgprot_t prot)
{
	pgprot_t sect_prot = __pgprot(PMD_TYPE_SECT |
					pgprot_val(mk_sect_prot(prot)));
	pmd_t new_pmd = pfn_pmd(__phys_to_pfn(phys), sect_prot);

	/* Only allow permission changes for now */
	if (!pgattr_change_is_safe(READ_ONCE(pmd_val(*pmdp)),
				   pmd_val(new_pmd)))
		return 0;

	BUG_ON(phys & ~PMD_MASK);
	set_pmd(pmdp, new_pmd);
	return 1;
}

<<<<<<< HEAD
int pud_clear_huge(pud_t *pudp)
{
	if (!pud_sect(READ_ONCE(*pudp)))
		return 0;
	pud_clear(pudp);
	return 1;
}

int pmd_clear_huge(pmd_t *pmdp)
{
	if (!pmd_sect(READ_ONCE(*pmdp)))
		return 0;
	pmd_clear(pmdp);
=======
int pud_clear_huge(pud_t *pud)
{
	if (!pud_sect(*pud))
		return 0;
	pud_clear(pud);
	return 1;
}

int pmd_clear_huge(pmd_t *pmd)
{
	if (!pmd_sect(*pmd))
		return 0;
	pmd_clear(pmd);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	return 1;
}

int pmd_free_pte_page(pmd_t *pmdp, unsigned long addr)
{
	pte_t *table;
	pmd_t pmd;

	pmd = READ_ONCE(*pmdp);

	if (!pmd_present(pmd))
		return 1;
	if (!pmd_table(pmd)) {
		VM_WARN_ON(!pmd_table(pmd));
		return 1;
	}

	table = pte_offset_kernel(pmdp, addr);
	pmd_clear(pmdp);
	__flush_tlb_kernel_pgtable(addr);
	pte_free_kernel(NULL, table);
	return 1;
}

int pud_free_pmd_page(pud_t *pudp, unsigned long addr)
{
	pmd_t *table;
	pmd_t *pmdp;
	pud_t pud;
	unsigned long next, end;

	pud = READ_ONCE(*pudp);

	if (!pud_present(pud))
		return 1;
	if (!pud_table(pud)) {
		VM_WARN_ON(!pud_table(pud));
		return 1;
	}

	table = pmd_offset(pudp, addr);
	pmdp = table;
	next = addr;
	end = addr + PUD_SIZE;
	do {
		pmd_free_pte_page(pmdp, next);
	} while (pmdp++, next += PMD_SIZE, next != end);

	pud_clear(pudp);
	__flush_tlb_kernel_pgtable(addr);
	pmd_free(NULL, table);
	return 1;
}
