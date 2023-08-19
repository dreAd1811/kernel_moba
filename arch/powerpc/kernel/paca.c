/*
 * c 2001 PPC 64 Team, IBM Corp
 *
 *      This program is free software; you can redistribute it and/or
 *      modify it under the terms of the GNU General Public License
 *      as published by the Free Software Foundation; either version
 *      2 of the License, or (at your option) any later version.
 */

#include <linux/smp.h>
#include <linux/export.h>
#include <linux/memblock.h>
#include <linux/sched/task.h>

#include <asm/lppaca.h>
#include <asm/paca.h>
#include <asm/sections.h>
#include <asm/pgtable.h>
#include <asm/kexec.h>

<<<<<<< HEAD
#include "setup.h"

#ifndef CONFIG_SMP
#define boot_cpuid 0
#endif

static void *__init alloc_paca_data(unsigned long size, unsigned long align,
				unsigned long limit, int cpu)
{
	unsigned long pa;
	int nid;

	/*
	 * boot_cpuid paca is allocated very early before cpu_to_node is up.
	 * Set bottom-up mode, because the boot CPU should be on node-0,
	 * which will put its paca in the right place.
	 */
	if (cpu == boot_cpuid) {
		nid = -1;
		memblock_set_bottom_up(true);
	} else {
		nid = early_cpu_to_node(cpu);
	}

	pa = memblock_alloc_base_nid(size, align, limit, nid, MEMBLOCK_NONE);
	if (!pa) {
		pa = memblock_alloc_base(size, align, limit);
		if (!pa)
			panic("cannot allocate paca data");
	}

	if (cpu == boot_cpuid)
		memblock_set_bottom_up(false);

	return __va(pa);
}

#ifdef CONFIG_PPC_PSERIES

/*
 * See asm/lppaca.h for more detail.
 *
 * lppaca structures must must be 1kB in size, L1 cache line aligned,
 * and not cross 4kB boundary. A 1kB size and 1kB alignment will satisfy
 * these requirements.
 */
static inline void init_lppaca(struct lppaca *lppaca)
{
	BUILD_BUG_ON(sizeof(struct lppaca) != 640);

	*lppaca = (struct lppaca) {
		.desc = cpu_to_be32(0xd397d781),	/* "LpPa" */
		.size = cpu_to_be16(0x400),
		.fpregs_in_use = 1,
		.slb_count = cpu_to_be16(64),
		.vmxregs_in_use = 0,
		.page_ins = 0, };
};

static struct lppaca * __init new_lppaca(int cpu, unsigned long limit)
{
	struct lppaca *lp;
	size_t size = 0x400;

	BUILD_BUG_ON(size < sizeof(struct lppaca));

	if (early_cpu_has_feature(CPU_FTR_HVMODE))
		return NULL;

	lp = alloc_paca_data(size, 0x400, limit, cpu);
	init_lppaca(lp);

	return lp;
}
#endif /* CONFIG_PPC_BOOK3S */

#ifdef CONFIG_PPC_BOOK3S_64

/*
 * 3 persistent SLBs are allocated here.  The buffer will be zero
=======
#ifdef CONFIG_PPC_BOOK3S

/*
 * The structure which the hypervisor knows about - this structure
 * should not cross a page boundary.  The vpa_init/register_vpa call
 * is now known to fail if the lppaca structure crosses a page
 * boundary.  The lppaca is also used on POWER5 pSeries boxes.
 * The lppaca is 640 bytes long, and cannot readily
 * change since the hypervisor knows its layout, so a 1kB alignment
 * will suffice to ensure that it doesn't cross a page boundary.
 */
struct lppaca lppaca[] = {
	[0 ... (NR_LPPACAS-1)] = {
		.desc = cpu_to_be32(0xd397d781),	/* "LpPa" */
		.size = cpu_to_be16(sizeof(struct lppaca)),
		.fpregs_in_use = 1,
		.slb_count = cpu_to_be16(64),
		.vmxregs_in_use = 0,
		.page_ins = 0,
	},
};

static struct lppaca *extra_lppacas;
static long __initdata lppaca_size;

static void __init allocate_lppacas(int nr_cpus, unsigned long limit)
{
	if (nr_cpus <= NR_LPPACAS)
		return;

	lppaca_size = PAGE_ALIGN(sizeof(struct lppaca) *
				 (nr_cpus - NR_LPPACAS));
	extra_lppacas = __va(memblock_alloc_base(lppaca_size,
						 PAGE_SIZE, limit));
}

static struct lppaca * __init new_lppaca(int cpu)
{
	struct lppaca *lp;

	if (cpu < NR_LPPACAS)
		return &lppaca[cpu];

	lp = extra_lppacas + (cpu - NR_LPPACAS);
	*lp = lppaca[0];

	return lp;
}

static void __init free_lppacas(void)
{
	long new_size = 0, nr;

	if (!lppaca_size)
		return;
	nr = num_possible_cpus() - NR_LPPACAS;
	if (nr > 0)
		new_size = PAGE_ALIGN(nr * sizeof(struct lppaca));
	if (new_size >= lppaca_size)
		return;

	memblock_free(__pa(extra_lppacas) + new_size, lppaca_size - new_size);
	lppaca_size = new_size;
}

#else

static inline void allocate_lppacas(int nr_cpus, unsigned long limit) { }
static inline void free_lppacas(void) { }

#endif /* CONFIG_PPC_BOOK3S */

#ifdef CONFIG_PPC_STD_MMU_64

/*
 * 3 persistent SLBs are registered here.  The buffer will be zero
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
 * initially, hence will all be invaild until we actually write them.
 *
 * If you make the number of persistent SLB entries dynamic, please also
 * update PR KVM to flush and restore them accordingly.
 */
<<<<<<< HEAD
static struct slb_shadow * __init new_slb_shadow(int cpu, unsigned long limit)
{
	struct slb_shadow *s;

	if (cpu != boot_cpuid) {
		/*
		 * Boot CPU comes here before early_radix_enabled
		 * is parsed (e.g., for disable_radix). So allocate
		 * always and this will be fixed up in free_unused_pacas.
		 */
		if (early_radix_enabled())
			return NULL;
	}

	s = alloc_paca_data(sizeof(*s), L1_CACHE_BYTES, limit, cpu);
	memset(s, 0, sizeof(*s));
=======
static struct slb_shadow * __initdata slb_shadow;

static void __init allocate_slb_shadows(int nr_cpus, int limit)
{
	int size = PAGE_ALIGN(sizeof(struct slb_shadow) * nr_cpus);

	if (early_radix_enabled())
		return;

	slb_shadow = __va(memblock_alloc_base(size, PAGE_SIZE, limit));
	memset(slb_shadow, 0, size);
}

static struct slb_shadow * __init init_slb_shadow(int cpu)
{
	struct slb_shadow *s;

	if (early_radix_enabled())
		return NULL;

	s = &slb_shadow[cpu];

	/*
	 * When we come through here to initialise boot_paca, the slb_shadow
	 * buffers are not allocated yet. That's OK, we'll get one later in
	 * boot, but make sure we don't corrupt memory at 0.
	 */
	if (!slb_shadow)
		return NULL;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	s->persistent = cpu_to_be32(SLB_NUM_BOLTED);
	s->buffer_length = cpu_to_be32(sizeof(*s));

	return s;
}

<<<<<<< HEAD
#endif /* CONFIG_PPC_BOOK3S_64 */
=======
#else /* CONFIG_PPC_STD_MMU_64 */

static void __init allocate_slb_shadows(int nr_cpus, int limit) { }

#endif /* CONFIG_PPC_STD_MMU_64 */
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* The Paca is an array with one entry per processor.  Each contains an
 * lppaca, which contains the information shared between the
 * hypervisor and Linux.
 * On systems with hardware multi-threading, there are two threads
 * per processor.  The Paca array must contain an entry for each thread.
 * The VPD Areas will give a max logical processors = 2 * max physical
 * processors.  The processor VPD array needs one entry per physical
 * processor (not thread).
 */
<<<<<<< HEAD
struct paca_struct **paca_ptrs __read_mostly;
EXPORT_SYMBOL(paca_ptrs);

void __init initialise_paca(struct paca_struct *new_paca, int cpu)
{
#ifdef CONFIG_PPC_PSERIES
	new_paca->lppaca_ptr = NULL;
#endif
#ifdef CONFIG_PPC_BOOK3E
=======
struct paca_struct *paca;
EXPORT_SYMBOL(paca);

void __init initialise_paca(struct paca_struct *new_paca, int cpu)
{
#ifdef CONFIG_PPC_BOOK3S
	new_paca->lppaca_ptr = new_lppaca(cpu);
#else
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	new_paca->kernel_pgd = swapper_pg_dir;
#endif
	new_paca->lock_token = 0x8000;
	new_paca->paca_index = cpu;
	new_paca->kernel_toc = kernel_toc_addr();
	new_paca->kernelbase = (unsigned long) _stext;
	/* Only set MSR:IR/DR when MMU is initialized */
	new_paca->kernel_msr = MSR_KERNEL & ~(MSR_IR | MSR_DR);
	new_paca->hw_cpu_id = 0xffff;
	new_paca->kexec_state = KEXEC_STATE_NONE;
	new_paca->__current = &init_task;
	new_paca->data_offset = 0xfeeeeeeeeeeeeeeeULL;
<<<<<<< HEAD
#ifdef CONFIG_PPC_BOOK3S_64
	new_paca->slb_shadow_ptr = NULL;
#endif
=======
#ifdef CONFIG_PPC_STD_MMU_64
	new_paca->slb_shadow_ptr = init_slb_shadow(cpu);
#endif /* CONFIG_PPC_STD_MMU_64 */
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

#ifdef CONFIG_PPC_BOOK3E
	/* For now -- if we have threads this will be adjusted later */
	new_paca->tcd_ptr = &new_paca->tcd;
#endif
}

/* Put the paca pointer into r13 and SPRG_PACA */
void setup_paca(struct paca_struct *new_paca)
{
	/* Setup r13 */
	local_paca = new_paca;

#ifdef CONFIG_PPC_BOOK3E
	/* On Book3E, initialize the TLB miss exception frames */
	mtspr(SPRN_SPRG_TLB_EXFRAME, local_paca->extlb);
#else
	/* In HV mode, we setup both HPACA and PACA to avoid problems
	 * if we do a GET_PACA() before the feature fixups have been
	 * applied
	 */
	if (early_cpu_has_feature(CPU_FTR_HVMODE))
		mtspr(SPRN_SPRG_HPACA, local_paca);
#endif
	mtspr(SPRN_SPRG_PACA, local_paca);

}

<<<<<<< HEAD
static int __initdata paca_nr_cpu_ids;
static int __initdata paca_ptrs_size;
static int __initdata paca_struct_size;

void __init allocate_paca_ptrs(void)
{
	paca_nr_cpu_ids = nr_cpu_ids;

	paca_ptrs_size = sizeof(struct paca_struct *) * nr_cpu_ids;
	paca_ptrs = __va(memblock_alloc(paca_ptrs_size, 0));
	memset(paca_ptrs, 0x88, paca_ptrs_size);
}

void __init allocate_paca(int cpu)
{
	u64 limit;
	struct paca_struct *paca;

	BUG_ON(cpu >= paca_nr_cpu_ids);

#ifdef CONFIG_PPC_BOOK3S_64
	/*
	 * We access pacas in real mode, and cannot take SLB faults
	 * on them when in virtual mode, so allocate them accordingly.
	 */
	limit = min(ppc64_bolted_size(), ppc64_rma_size);
#else
	limit = ppc64_rma_size;
#endif

	paca = alloc_paca_data(sizeof(struct paca_struct), L1_CACHE_BYTES,
				limit, cpu);
	paca_ptrs[cpu] = paca;
	memset(paca, 0, sizeof(struct paca_struct));

	initialise_paca(paca, cpu);
#ifdef CONFIG_PPC_PSERIES
	paca->lppaca_ptr = new_lppaca(cpu, limit);
#endif
#ifdef CONFIG_PPC_BOOK3S_64
	paca->slb_shadow_ptr = new_slb_shadow(cpu, limit);
#endif
	paca_struct_size += sizeof(struct paca_struct);
=======
static int __initdata paca_size;

void __init allocate_pacas(void)
{
	u64 limit;
	int cpu;

	limit = ppc64_rma_size;

#ifdef CONFIG_PPC_BOOK3S_64
	/*
	 * We can't take SLB misses on the paca, and we want to access them
	 * in real mode, so allocate them within the RMA and also within
	 * the first segment.
	 */
	limit = min(0x10000000ULL, limit);
#endif

	paca_size = PAGE_ALIGN(sizeof(struct paca_struct) * nr_cpu_ids);

	paca = __va(memblock_alloc_base(paca_size, PAGE_SIZE, limit));
	memset(paca, 0, paca_size);

	printk(KERN_DEBUG "Allocated %u bytes for %u pacas at %p\n",
		paca_size, nr_cpu_ids, paca);

	allocate_lppacas(nr_cpu_ids, limit);

	allocate_slb_shadows(nr_cpu_ids, limit);

	/* Can't use for_each_*_cpu, as they aren't functional yet */
	for (cpu = 0; cpu < nr_cpu_ids; cpu++)
		initialise_paca(&paca[cpu], cpu);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
}

void __init free_unused_pacas(void)
{
<<<<<<< HEAD
	int new_ptrs_size;

	new_ptrs_size = sizeof(struct paca_struct *) * nr_cpu_ids;
	if (new_ptrs_size < paca_ptrs_size)
		memblock_free(__pa(paca_ptrs) + new_ptrs_size,
					paca_ptrs_size - new_ptrs_size);

	paca_nr_cpu_ids = nr_cpu_ids;
	paca_ptrs_size = new_ptrs_size;

#ifdef CONFIG_PPC_BOOK3S_64
	if (early_radix_enabled()) {
		/* Ugly fixup, see new_slb_shadow() */
		memblock_free(__pa(paca_ptrs[boot_cpuid]->slb_shadow_ptr),
				sizeof(struct slb_shadow));
		paca_ptrs[boot_cpuid]->slb_shadow_ptr = NULL;
	}
#endif

	printk(KERN_DEBUG "Allocated %u bytes for %u pacas\n",
			paca_ptrs_size + paca_struct_size, nr_cpu_ids);
=======
	int new_size;

	new_size = PAGE_ALIGN(sizeof(struct paca_struct) * nr_cpu_ids);

	if (new_size >= paca_size)
		return;

	memblock_free(__pa(paca) + new_size, paca_size - new_size);

	printk(KERN_DEBUG "Freed %u bytes for unused pacas\n",
		paca_size - new_size);

	paca_size = new_size;

	free_lppacas();
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
}

void copy_mm_to_paca(struct mm_struct *mm)
{
#ifdef CONFIG_PPC_BOOK3S
	mm_context_t *context = &mm->context;

	get_paca()->mm_ctx_id = context->id;
#ifdef CONFIG_PPC_MM_SLICES
<<<<<<< HEAD
	VM_BUG_ON(!mm->context.slb_addr_limit);
	get_paca()->mm_ctx_slb_addr_limit = mm->context.slb_addr_limit;
	memcpy(&get_paca()->mm_ctx_low_slices_psize,
	       &context->low_slices_psize, sizeof(context->low_slices_psize));
=======
	VM_BUG_ON(!mm->context.addr_limit);
	get_paca()->addr_limit = mm->context.addr_limit;
	get_paca()->mm_ctx_low_slices_psize = context->low_slices_psize;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	memcpy(&get_paca()->mm_ctx_high_slices_psize,
	       &context->high_slices_psize, TASK_SLICE_ARRAY_SZ(mm));
#else /* CONFIG_PPC_MM_SLICES */
	get_paca()->mm_ctx_user_psize = context->user_psize;
	get_paca()->mm_ctx_sllp = context->sllp;
#endif
<<<<<<< HEAD
#else /* !CONFIG_PPC_BOOK3S */
=======
#else /* CONFIG_PPC_BOOK3S */
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	return;
#endif
}
