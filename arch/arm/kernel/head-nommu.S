/*
 *  linux/arch/arm/kernel/head-nommu.S
 *
 *  Copyright (C) 1994-2002 Russell King
 *  Copyright (C) 2003-2006 Hyok S. Choi
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 *  Common kernel startup code (non-paged MM)
 *
 */
#include <linux/linkage.h>
#include <linux/init.h>
<<<<<<< HEAD
#include <linux/errno.h>
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

#include <asm/assembler.h>
#include <asm/ptrace.h>
#include <asm/asm-offsets.h>
#include <asm/memory.h>
#include <asm/cp15.h>
#include <asm/thread_info.h>
#include <asm/v7m.h>
#include <asm/mpu.h>
#include <asm/page.h>

/*
 * Kernel startup entry point.
 * ---------------------------
 *
 * This is normally called from the decompressor code.  The requirements
 * are: MMU = off, D-cache = off, I-cache = dont care, r0 = 0,
 * r1 = machine nr.
 *
 * See linux/arch/arm/tools/mach-types for the complete list of machine
 * numbers for r1.
 *
 */

	__HEAD

#ifdef CONFIG_CPU_THUMBONLY
	.thumb
ENTRY(stext)
#else
	.arm
ENTRY(stext)

 THUMB(	badr	r9, 1f		)	@ Kernel is always entered in ARM.
 THUMB(	bx	r9		)	@ If this is a Thumb-2 kernel,
 THUMB(	.thumb			)	@ switch to Thumb now.
 THUMB(1:			)
#endif

<<<<<<< HEAD
#ifdef CONFIG_ARM_VIRT_EXT
	bl	__hyp_stub_install
#endif
	@ ensure svc mode and all interrupts masked
	safe_svcmode_maskall r9
=======
	setmode	PSR_F_BIT | PSR_I_BIT | SVC_MODE, r9 @ ensure svc mode
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
						@ and irqs disabled
#if defined(CONFIG_CPU_CP15)
	mrc	p15, 0, r9, c0, c0		@ get processor id
#elif defined(CONFIG_CPU_V7M)
	ldr	r9, =BASEADDR_V7M_SCB
	ldr	r9, [r9, V7M_SCB_CPUID]
#else
	ldr	r9, =CONFIG_PROCESSOR_ID
#endif
	bl	__lookup_processor_type		@ r5=procinfo r9=cpuid
	movs	r10, r5				@ invalid processor (r5=0)?
	beq	__error_p				@ yes, error 'p'

#ifdef CONFIG_ARM_MPU
<<<<<<< HEAD
=======
	/* Calculate the size of a region covering just the kernel */
	ldr	r5, =PLAT_PHYS_OFFSET		@ Region start: PHYS_OFFSET
	ldr     r6, =(_end)			@ Cover whole kernel
	sub	r6, r6, r5			@ Minimum size of region to map
	clz	r6, r6				@ Region size must be 2^N...
	rsb	r6, r6, #31			@ ...so round up region size
	lsl	r6, r6, #MPU_RSR_SZ		@ Put size in right field
	orr	r6, r6, #(1 << MPU_RSR_EN)	@ Set region enabled bit
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	bl	__setup_mpu
#endif

	badr	lr, 1f				@ return (PIC) address
	ldr	r12, [r10, #PROCINFO_INITFUNC]
	add	r12, r12, r10
	ret	r12
<<<<<<< HEAD
1:	ldr	lr, =__mmap_switched
	b	__after_proc_init
=======
1:	bl	__after_proc_init
	b	__mmap_switched
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
ENDPROC(stext)

#ifdef CONFIG_SMP
	.text
ENTRY(secondary_startup)
	/*
	 * Common entry point for secondary CPUs.
	 *
	 * Ensure that we're in SVC mode, and IRQs are disabled.  Lookup
	 * the processor type - there is no need to check the machine type
	 * as it has already been validated by the primary processor.
	 */
<<<<<<< HEAD
#ifdef CONFIG_ARM_VIRT_EXT
	bl	__hyp_stub_install_secondary
#endif
	safe_svcmode_maskall r9

=======
	setmode	PSR_F_BIT | PSR_I_BIT | SVC_MODE, r9
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
#ifndef CONFIG_CPU_CP15
	ldr	r9, =CONFIG_PROCESSOR_ID
#else
	mrc	p15, 0, r9, c0, c0		@ get processor id
#endif
	bl	__lookup_processor_type		@ r5=procinfo r9=cpuid
	movs	r10, r5				@ invalid processor?
	beq	__error_p			@ yes, error 'p'

	ldr	r7, __secondary_data

#ifdef CONFIG_ARM_MPU
<<<<<<< HEAD
	bl      __secondary_setup_mpu		@ Initialize the MPU
=======
	/* Use MPU region info supplied by __cpu_up */
	ldr	r6, [r7]			@ get secondary_data.mpu_szr
	bl      __setup_mpu			@ Initialize the MPU
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
#endif

	badr	lr, 1f				@ return (PIC) address
	ldr	r12, [r10, #PROCINFO_INITFUNC]
	add	r12, r12, r10
	ret	r12
1:	bl	__after_proc_init
	ldr	sp, [r7, #12]			@ set up the stack pointer
	mov	fp, #0
	b	secondary_start_kernel
ENDPROC(secondary_startup)

	.type	__secondary_data, %object
__secondary_data:
	.long	secondary_data
#endif /* CONFIG_SMP */

/*
 * Set the Control Register and Read the process ID.
 */
<<<<<<< HEAD
	.text
__after_proc_init:
M_CLASS(movw	r12, #:lower16:BASEADDR_V7M_SCB)
M_CLASS(movt	r12, #:upper16:BASEADDR_V7M_SCB)
#ifdef CONFIG_ARM_MPU
M_CLASS(ldr	r3, [r12, 0x50])
AR_CLASS(mrc	p15, 0, r3, c0, c1, 4)          @ Read ID_MMFR0
	and	r3, r3, #(MMFR0_PMSA)           @ PMSA field
	teq	r3, #(MMFR0_PMSAv7)             @ PMSA v7
	beq	1f
	teq	r3, #(MMFR0_PMSAv8)		@ PMSA v8
	/*
	 * Memory region attributes for PMSAv8:
	 *
	 *   n = AttrIndx[2:0]
	 *                      n       MAIR
	 *   DEVICE_nGnRnE      000     00000000
	 *   NORMAL             001     11111111
	 */
	ldreq	r3, =PMSAv8_MAIR(0x00, PMSAv8_RGN_DEVICE_nGnRnE) | \
		     PMSAv8_MAIR(0xff, PMSAv8_RGN_NORMAL)
AR_CLASS(mcreq	p15, 0, r3, c10, c2, 0)		@ MAIR 0
M_CLASS(streq	r3, [r12, #PMSAv8_MAIR0])
	moveq	r3, #0
AR_CLASS(mcreq	p15, 0, r3, c10, c2, 1)		@ MAIR 1
M_CLASS(streq	r3, [r12, #PMSAv8_MAIR1])

1:
#endif
=======
__after_proc_init:
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
#ifdef CONFIG_CPU_CP15
	/*
	 * CP15 system control register value returned in r0 from
	 * the CPU init function.
	 */
<<<<<<< HEAD

#ifdef CONFIG_ARM_MPU
	biceq	r0, r0, #CR_BR			@ Disable the 'default mem-map'
	orreq	r0, r0, #CR_M			@ Set SCTRL.M (MPU on)
#endif
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
#if defined(CONFIG_ALIGNMENT_TRAP) && __LINUX_ARM_ARCH__ < 6
	orr	r0, r0, #CR_A
#else
	bic	r0, r0, #CR_A
#endif
#ifdef CONFIG_CPU_DCACHE_DISABLE
	bic	r0, r0, #CR_C
#endif
#ifdef CONFIG_CPU_BPREDICT_DISABLE
	bic	r0, r0, #CR_Z
#endif
#ifdef CONFIG_CPU_ICACHE_DISABLE
	bic	r0, r0, #CR_I
#endif
	mcr	p15, 0, r0, c1, c0, 0		@ write control reg
<<<<<<< HEAD
	instr_sync
#elif defined (CONFIG_CPU_V7M)
#ifdef CONFIG_ARM_MPU
	ldreq	r3, [r12, MPU_CTRL]
	biceq	r3, #MPU_CTRL_PRIVDEFENA
	orreq	r3, #MPU_CTRL_ENABLE
	streq	r3, [r12, MPU_CTRL]
	isb
#endif
=======
#elif defined (CONFIG_CPU_V7M)
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	/* For V7M systems we want to modify the CCR similarly to the SCTLR */
#ifdef CONFIG_CPU_DCACHE_DISABLE
	bic	r0, r0, #V7M_SCB_CCR_DC
#endif
#ifdef CONFIG_CPU_BPREDICT_DISABLE
	bic	r0, r0, #V7M_SCB_CCR_BP
#endif
#ifdef CONFIG_CPU_ICACHE_DISABLE
	bic	r0, r0, #V7M_SCB_CCR_IC
#endif
<<<<<<< HEAD
	str	r0, [r12, V7M_SCB_CCR]
=======
	movw	r3, #:lower16:(BASEADDR_V7M_SCB + V7M_SCB_CCR)
	movt	r3, #:upper16:(BASEADDR_V7M_SCB + V7M_SCB_CCR)
	str	r0, [r3]
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
#endif /* CONFIG_CPU_CP15 elif CONFIG_CPU_V7M */
	ret	lr
ENDPROC(__after_proc_init)
	.ltorg

#ifdef CONFIG_ARM_MPU


<<<<<<< HEAD
#ifndef CONFIG_CPU_V7M
/* Set which MPU region should be programmed */
.macro set_region_nr tmp, rgnr, unused
=======
/* Set which MPU region should be programmed */
.macro set_region_nr tmp, rgnr
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	mov	\tmp, \rgnr			@ Use static region numbers
	mcr	p15, 0, \tmp, c6, c2, 0		@ Write RGNR
.endm

/* Setup a single MPU region, either D or I side (D-side for unified) */
<<<<<<< HEAD
.macro setup_region bar, acr, sr, side = PMSAv7_DATA_SIDE, unused
=======
.macro setup_region bar, acr, sr, side = MPU_DATA_SIDE
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	mcr	p15, 0, \bar, c6, c1, (0 + \side)	@ I/DRBAR
	mcr	p15, 0, \acr, c6, c1, (4 + \side)	@ I/DRACR
	mcr	p15, 0, \sr, c6, c1, (2 + \side)		@ I/DRSR
.endm
<<<<<<< HEAD
#else
.macro set_region_nr tmp, rgnr, base
	mov	\tmp, \rgnr
	str     \tmp, [\base, #PMSAv7_RNR]
.endm

.macro setup_region bar, acr, sr, unused, base
	lsl     \acr, \acr, #16
	orr     \acr, \acr, \sr
	str     \bar, [\base, #PMSAv7_RBAR]
	str     \acr, [\base, #PMSAv7_RASR]
.endm

#endif
=======

>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
/*
 * Setup the MPU and initial MPU Regions. We create the following regions:
 * Region 0: Use this for probing the MPU details, so leave disabled.
 * Region 1: Background region - covers the whole of RAM as strongly ordered
 * Region 2: Normal, Shared, cacheable for RAM. From PHYS_OFFSET, size from r6
 * Region 3: Normal, shared, inaccessible from PL0 to protect the vectors page
 *
<<<<<<< HEAD
 * r6: Value to be written to DRSR (and IRSR if required) for PMSAv7_RAM_REGION
*/
	__HEAD
=======
 * r6: Value to be written to DRSR (and IRSR if required) for MPU_RAM_REGION
*/
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

ENTRY(__setup_mpu)

	/* Probe for v7 PMSA compliance */
<<<<<<< HEAD
M_CLASS(movw	r12, #:lower16:BASEADDR_V7M_SCB)
M_CLASS(movt	r12, #:upper16:BASEADDR_V7M_SCB)

AR_CLASS(mrc	p15, 0, r0, c0, c1, 4)		@ Read ID_MMFR0
M_CLASS(ldr	r0, [r12, 0x50])
	and	r0, r0, #(MMFR0_PMSA)		@ PMSA field
	teq	r0, #(MMFR0_PMSAv7)		@ PMSA v7
	beq	__setup_pmsa_v7
	teq	r0, #(MMFR0_PMSAv8)		@ PMSA v8
	beq	__setup_pmsa_v8

	ret	lr
ENDPROC(__setup_mpu)

ENTRY(__setup_pmsa_v7)
	/* Calculate the size of a region covering just the kernel */
	ldr	r5, =PLAT_PHYS_OFFSET		@ Region start: PHYS_OFFSET
	ldr     r6, =(_end)			@ Cover whole kernel
	sub	r6, r6, r5			@ Minimum size of region to map
	clz	r6, r6				@ Region size must be 2^N...
	rsb	r6, r6, #31			@ ...so round up region size
	lsl	r6, r6, #PMSAv7_RSR_SZ		@ Put size in right field
	orr	r6, r6, #(1 << PMSAv7_RSR_EN)	@ Set region enabled bit

	/* Determine whether the D/I-side memory map is unified. We set the
	 * flags here and continue to use them for the rest of this function */
AR_CLASS(mrc	p15, 0, r0, c0, c0, 4)		@ MPUIR
M_CLASS(ldr    r0, [r12, #MPU_TYPE])
	ands	r5, r0, #MPUIR_DREGION_SZMASK	@ 0 size d region => No MPU
	bxeq	lr
	tst	r0, #MPUIR_nU			@ MPUIR_nU = 0 for unified

	/* Setup second region first to free up r6 */
	set_region_nr r0, #PMSAv7_RAM_REGION, r12
	isb
	/* Full access from PL0, PL1, shared for CONFIG_SMP, cacheable */
	ldr	r0, =PLAT_PHYS_OFFSET		@ RAM starts at PHYS_OFFSET
	ldr	r5,=(PMSAv7_AP_PL1RW_PL0RW | PMSAv7_RGN_NORMAL)

	setup_region r0, r5, r6, PMSAv7_DATA_SIDE, r12	@ PHYS_OFFSET, shared, enabled
	beq	1f					@ Memory-map not unified
	setup_region r0, r5, r6, PMSAv7_INSTR_SIDE, r12	@ PHYS_OFFSET, shared, enabled
1:	isb

	/* First/background region */
	set_region_nr r0, #PMSAv7_BG_REGION, r12
	isb
	/* Execute Never,  strongly ordered, inaccessible to PL0, rw PL1  */
	mov	r0, #0				@ BG region starts at 0x0
	ldr	r5,=(PMSAv7_ACR_XN | PMSAv7_RGN_STRONGLY_ORDERED | PMSAv7_AP_PL1RW_PL0NA)
	mov	r6, #PMSAv7_RSR_ALL_MEM		@ 4GB region, enabled

	setup_region r0, r5, r6, PMSAv7_DATA_SIDE, r12	@ 0x0, BG region, enabled
	beq	2f					@ Memory-map not unified
	setup_region r0, r5, r6, PMSAv7_INSTR_SIDE r12	@ 0x0, BG region, enabled
2:	isb

#ifdef CONFIG_XIP_KERNEL
	set_region_nr r0, #PMSAv7_ROM_REGION, r12
	isb

	ldr	r5,=(PMSAv7_AP_PL1RO_PL0NA | PMSAv7_RGN_NORMAL)

	ldr	r0, =CONFIG_XIP_PHYS_ADDR		@ ROM start
	ldr     r6, =(_exiprom)				@ ROM end
	sub	r6, r6, r0				@ Minimum size of region to map
	clz	r6, r6					@ Region size must be 2^N...
	rsb	r6, r6, #31				@ ...so round up region size
	lsl	r6, r6, #PMSAv7_RSR_SZ			@ Put size in right field
	orr	r6, r6, #(1 << PMSAv7_RSR_EN)		@ Set region enabled bit

	setup_region r0, r5, r6, PMSAv7_DATA_SIDE, r12	@ XIP_PHYS_ADDR, shared, enabled
	beq	3f					@ Memory-map not unified
	setup_region r0, r5, r6, PMSAv7_INSTR_SIDE, r12	@ XIP_PHYS_ADDR, shared, enabled
3:	isb
#endif
	ret	lr
ENDPROC(__setup_pmsa_v7)

ENTRY(__setup_pmsa_v8)
	mov	r0, #0
AR_CLASS(mcr	p15, 0, r0, c6, c2, 1)		@ PRSEL
M_CLASS(str	r0, [r12, #PMSAv8_RNR])
	isb

#ifdef CONFIG_XIP_KERNEL
	ldr	r5, =CONFIG_XIP_PHYS_ADDR		@ ROM start
	ldr     r6, =(_exiprom)				@ ROM end
	sub	r6, r6, #1
	bic	r6, r6, #(PMSAv8_MINALIGN - 1)

	orr	r5, r5, #(PMSAv8_AP_PL1RW_PL0NA | PMSAv8_RGN_SHARED)
	orr	r6, r6, #(PMSAv8_LAR_IDX(PMSAv8_RGN_NORMAL) | PMSAv8_LAR_EN)

AR_CLASS(mcr	p15, 0, r5, c6, c8, 0)			@ PRBAR0
AR_CLASS(mcr	p15, 0, r6, c6, c8, 1)			@ PRLAR0
M_CLASS(str	r5, [r12, #PMSAv8_RBAR_A(0)])
M_CLASS(str	r6, [r12, #PMSAv8_RLAR_A(0)])
#endif

	ldr	r5, =KERNEL_START
	ldr	r6, =KERNEL_END
	sub	r6, r6, #1
	bic	r6, r6, #(PMSAv8_MINALIGN - 1)

	orr	r5, r5, #(PMSAv8_AP_PL1RW_PL0NA | PMSAv8_RGN_SHARED)
	orr	r6, r6, #(PMSAv8_LAR_IDX(PMSAv8_RGN_NORMAL) | PMSAv8_LAR_EN)

AR_CLASS(mcr	p15, 0, r5, c6, c8, 4)			@ PRBAR1
AR_CLASS(mcr	p15, 0, r6, c6, c8, 5)			@ PRLAR1
M_CLASS(str	r5, [r12, #PMSAv8_RBAR_A(1)])
M_CLASS(str	r6, [r12, #PMSAv8_RLAR_A(1)])

	/* Setup Background: 0x0 - min(KERNEL_START, XIP_PHYS_ADDR) */
#ifdef CONFIG_XIP_KERNEL
	ldr	r6, =KERNEL_START
	ldr	r5, =CONFIG_XIP_PHYS_ADDR
	cmp	r6, r5
	movcs	r6, r5
#else
	ldr	r6, =KERNEL_START
#endif
	cmp	r6, #0
	beq	1f

	mov	r5, #0
	sub	r6, r6, #1
	bic	r6, r6, #(PMSAv8_MINALIGN - 1)

	orr	r5, r5, #(PMSAv8_AP_PL1RW_PL0NA | PMSAv8_RGN_SHARED | PMSAv8_BAR_XN)
	orr	r6, r6, #(PMSAv8_LAR_IDX(PMSAv8_RGN_DEVICE_nGnRnE) | PMSAv8_LAR_EN)

AR_CLASS(mcr	p15, 0, r5, c6, c9, 0)			@ PRBAR2
AR_CLASS(mcr	p15, 0, r6, c6, c9, 1)			@ PRLAR2
M_CLASS(str	r5, [r12, #PMSAv8_RBAR_A(2)])
M_CLASS(str	r6, [r12, #PMSAv8_RLAR_A(2)])

1:
	/* Setup Background: max(KERNEL_END, _exiprom) - 0xffffffff */
#ifdef CONFIG_XIP_KERNEL
	ldr	r5, =KERNEL_END
	ldr	r6, =(_exiprom)
	cmp	r5, r6
	movcc	r5, r6
#else
	ldr	r5, =KERNEL_END
#endif
	mov	r6, #0xffffffff
	bic	r6, r6, #(PMSAv8_MINALIGN - 1)

	orr	r5, r5, #(PMSAv8_AP_PL1RW_PL0NA | PMSAv8_RGN_SHARED | PMSAv8_BAR_XN)
	orr	r6, r6, #(PMSAv8_LAR_IDX(PMSAv8_RGN_DEVICE_nGnRnE) | PMSAv8_LAR_EN)

AR_CLASS(mcr	p15, 0, r5, c6, c9, 4)			@ PRBAR3
AR_CLASS(mcr	p15, 0, r6, c6, c9, 5)			@ PRLAR3
M_CLASS(str	r5, [r12, #PMSAv8_RBAR_A(3)])
M_CLASS(str	r6, [r12, #PMSAv8_RLAR_A(3)])

#ifdef CONFIG_XIP_KERNEL
	/* Setup Background: min(_exiprom, KERNEL_END) - max(KERNEL_START, XIP_PHYS_ADDR) */
	ldr	r5, =(_exiprom)
	ldr	r6, =KERNEL_END
	cmp	r5, r6
	movcs	r5, r6

	ldr	r6, =KERNEL_START
	ldr	r0, =CONFIG_XIP_PHYS_ADDR
	cmp	r6, r0
	movcc	r6, r0

	sub	r6, r6, #1
	bic	r6, r6, #(PMSAv8_MINALIGN - 1)

	orr	r5, r5, #(PMSAv8_AP_PL1RW_PL0NA | PMSAv8_RGN_SHARED | PMSAv8_BAR_XN)
	orr	r6, r6, #(PMSAv8_LAR_IDX(PMSAv8_RGN_DEVICE_nGnRnE) | PMSAv8_LAR_EN)

#ifdef CONFIG_CPU_V7M
	/* There is no alias for n == 4 */
	mov	r0, #4
	str	r0, [r12, #PMSAv8_RNR]			@ PRSEL
	isb

	str	r5, [r12, #PMSAv8_RBAR_A(0)]
	str	r6, [r12, #PMSAv8_RLAR_A(0)]
#else
	mcr	p15, 0, r5, c6, c10, 1			@ PRBAR4
	mcr	p15, 0, r6, c6, c10, 2			@ PRLAR4
#endif
#endif
	ret	lr
ENDPROC(__setup_pmsa_v8)

#ifdef CONFIG_SMP
/*
 * r6: pointer at mpu_rgn_info
 */

	.text
ENTRY(__secondary_setup_mpu)
	/* Use MPU region info supplied by __cpu_up */
	ldr	r6, [r7]			@ get secondary_data.mpu_rgn_info

	/* Probe for v7 PMSA compliance */
	mrc	p15, 0, r0, c0, c1, 4		@ Read ID_MMFR0
	and	r0, r0, #(MMFR0_PMSA)		@ PMSA field
	teq	r0, #(MMFR0_PMSAv7)		@ PMSA v7
	beq	__secondary_setup_pmsa_v7
	teq	r0, #(MMFR0_PMSAv8)		@ PMSA v8
	beq	__secondary_setup_pmsa_v8
	b	__error_p
ENDPROC(__secondary_setup_mpu)

/*
 * r6: pointer at mpu_rgn_info
 */
ENTRY(__secondary_setup_pmsa_v7)
=======
	mrc	p15, 0, r0, c0, c1, 4		@ Read ID_MMFR0
	and	r0, r0, #(MMFR0_PMSA)		@ PMSA field
	teq	r0, #(MMFR0_PMSAv7)		@ PMSA v7
	bne	__error_p			@ Fail: ARM_MPU on NOT v7 PMSA

>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	/* Determine whether the D/I-side memory map is unified. We set the
	 * flags here and continue to use them for the rest of this function */
	mrc	p15, 0, r0, c0, c0, 4		@ MPUIR
	ands	r5, r0, #MPUIR_DREGION_SZMASK	@ 0 size d region => No MPU
<<<<<<< HEAD
	beq	__error_p

	ldr	r4, [r6, #MPU_RNG_INFO_USED]
	mov	r5, #MPU_RNG_SIZE
	add	r3, r6, #MPU_RNG_INFO_RNGS
	mla	r3, r4, r5, r3

1:
	tst	r0, #MPUIR_nU			@ MPUIR_nU = 0 for unified
	sub	r3, r3, #MPU_RNG_SIZE
	sub	r4, r4, #1

	set_region_nr r0, r4
	isb

	ldr	r0, [r3, #MPU_RGN_DRBAR]
	ldr	r6, [r3, #MPU_RGN_DRSR]
	ldr	r5, [r3, #MPU_RGN_DRACR]

	setup_region r0, r5, r6, PMSAv7_DATA_SIDE
	beq	2f
	setup_region r0, r5, r6, PMSAv7_INSTR_SIDE
2:	isb

	mrc	p15, 0, r0, c0, c0, 4		@ Reevaluate the MPUIR
	cmp	r4, #0
	bgt	1b

	ret	lr
ENDPROC(__secondary_setup_pmsa_v7)

ENTRY(__secondary_setup_pmsa_v8)
	ldr	r4, [r6, #MPU_RNG_INFO_USED]
#ifndef CONFIG_XIP_KERNEL
	add	r4, r4, #1
#endif
	mov	r5, #MPU_RNG_SIZE
	add	r3, r6, #MPU_RNG_INFO_RNGS
	mla	r3, r4, r5, r3

1:
	sub	r3, r3, #MPU_RNG_SIZE
	sub	r4, r4, #1

	mcr	p15, 0, r4, c6, c2, 1		@ PRSEL
	isb

	ldr	r5, [r3, #MPU_RGN_PRBAR]
	ldr	r6, [r3, #MPU_RGN_PRLAR]

	mcr	p15, 0, r5, c6, c3, 0		@ PRBAR
	mcr	p15, 0, r6, c6, c3, 1           @ PRLAR

	cmp	r4, #0
	bgt	1b

	ret	lr
ENDPROC(__secondary_setup_pmsa_v8)
#endif /* CONFIG_SMP */
#endif /* CONFIG_ARM_MPU */
=======
	beq	__error_p			@ Fail: ARM_MPU and no MPU
	tst	r0, #MPUIR_nU			@ MPUIR_nU = 0 for unified

	/* Setup second region first to free up r6 */
	set_region_nr r0, #MPU_RAM_REGION
	isb
	/* Full access from PL0, PL1, shared for CONFIG_SMP, cacheable */
	ldr	r0, =PLAT_PHYS_OFFSET		@ RAM starts at PHYS_OFFSET
	ldr	r5,=(MPU_AP_PL1RW_PL0RW | MPU_RGN_NORMAL)

	setup_region r0, r5, r6, MPU_DATA_SIDE	@ PHYS_OFFSET, shared, enabled
	beq	1f				@ Memory-map not unified
	setup_region r0, r5, r6, MPU_INSTR_SIDE @ PHYS_OFFSET, shared, enabled
1:	isb

	/* First/background region */
	set_region_nr r0, #MPU_BG_REGION
	isb
	/* Execute Never,  strongly ordered, inaccessible to PL0, rw PL1  */
	mov	r0, #0				@ BG region starts at 0x0
	ldr	r5,=(MPU_ACR_XN | MPU_RGN_STRONGLY_ORDERED | MPU_AP_PL1RW_PL0NA)
	mov	r6, #MPU_RSR_ALL_MEM		@ 4GB region, enabled

	setup_region r0, r5, r6, MPU_DATA_SIDE	@ 0x0, BG region, enabled
	beq	2f				@ Memory-map not unified
	setup_region r0, r5, r6, MPU_INSTR_SIDE @ 0x0, BG region, enabled
2:	isb

	/* Vectors region */
	set_region_nr r0, #MPU_VECTORS_REGION
	isb
	/* Shared, inaccessible to PL0, rw PL1 */
	mov	r0, #CONFIG_VECTORS_BASE	@ Cover from VECTORS_BASE
	ldr	r5,=(MPU_AP_PL1RW_PL0NA | MPU_RGN_NORMAL)
	/* Writing N to bits 5:1 (RSR_SZ) --> region size 2^N+1 */
	mov	r6, #(((2 * PAGE_SHIFT - 1) << MPU_RSR_SZ) | 1 << MPU_RSR_EN)

	setup_region r0, r5, r6, MPU_DATA_SIDE	@ VECTORS_BASE, PL0 NA, enabled
	beq	3f				@ Memory-map not unified
	setup_region r0, r5, r6, MPU_INSTR_SIDE	@ VECTORS_BASE, PL0 NA, enabled
3:	isb

	/* Enable the MPU */
	mrc	p15, 0, r0, c1, c0, 0		@ Read SCTLR
	bic     r0, r0, #CR_BR			@ Disable the 'default mem-map'
	orr	r0, r0, #CR_M			@ Set SCTRL.M (MPU on)
	mcr	p15, 0, r0, c1, c0, 0		@ Enable MPU
	isb
	ret	lr
ENDPROC(__setup_mpu)
#endif
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
#include "head-common.S"
