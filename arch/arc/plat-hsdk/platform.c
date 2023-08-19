/*
 * ARC HSDK Platform support code
 *
 * Copyright (C) 2017 Synopsys, Inc. (www.synopsys.com)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/init.h>
#include <linux/smp.h>
#include <asm/arcregs.h>
#include <asm/io.h>
#include <asm/mach_desc.h>

#define ARC_CCM_UNUSED_ADDR	0x60000000

static void __init hsdk_init_per_cpu(unsigned int cpu)
{
	/*
	 * By default ICCM is mapped to 0x7z while this area is used for
	 * kernel virtual mappings, so move it to currently unused area.
	 */
	if (cpuinfo_arc700[cpu].iccm.sz)
		write_aux_reg(ARC_REG_AUX_ICCM, ARC_CCM_UNUSED_ADDR);

	/*
	 * By default DCCM is mapped to 0x8z while this area is used by kernel,
	 * so move it to currently unused area.
	 */
	if (cpuinfo_arc700[cpu].dccm.sz)
		write_aux_reg(ARC_REG_AUX_DCCM, ARC_CCM_UNUSED_ADDR);
}

#define ARC_PERIPHERAL_BASE	0xf0000000
#define CREG_BASE		(ARC_PERIPHERAL_BASE + 0x1000)
#define CREG_PAE		(CREG_BASE + 0x180)
#define CREG_PAE_UPDATE		(CREG_BASE + 0x194)

<<<<<<< HEAD
=======
#define CREG_CORE_IF_CLK_DIV	(CREG_BASE + 0x4B8)
#define CREG_CORE_IF_CLK_DIV_2	0x1
#define CGU_BASE		ARC_PERIPHERAL_BASE
#define CGU_PLL_STATUS		(ARC_PERIPHERAL_BASE + 0x4)
#define CGU_PLL_CTRL		(ARC_PERIPHERAL_BASE + 0x0)
#define CGU_PLL_STATUS_LOCK	BIT(0)
#define CGU_PLL_STATUS_ERR	BIT(1)
#define CGU_PLL_CTRL_1GHZ	0x3A10
#define HSDK_PLL_LOCK_TIMEOUT	500

#define HSDK_PLL_LOCKED() \
	!!(ioread32((void __iomem *) CGU_PLL_STATUS) & CGU_PLL_STATUS_LOCK)

#define HSDK_PLL_ERR() \
	!!(ioread32((void __iomem *) CGU_PLL_STATUS) & CGU_PLL_STATUS_ERR)

static void __init hsdk_set_cpu_freq_1ghz(void)
{
	u32 timeout = HSDK_PLL_LOCK_TIMEOUT;

	/*
	 * As we set cpu clock which exceeds 500MHz, the divider for the interface
	 * clock must be programmed to div-by-2.
	 */
	iowrite32(CREG_CORE_IF_CLK_DIV_2, (void __iomem *) CREG_CORE_IF_CLK_DIV);

	/* Set cpu clock to 1GHz */
	iowrite32(CGU_PLL_CTRL_1GHZ, (void __iomem *) CGU_PLL_CTRL);

	while (!HSDK_PLL_LOCKED() && timeout--)
		cpu_relax();

	if (!HSDK_PLL_LOCKED() || HSDK_PLL_ERR())
		pr_err("Failed to setup CPU frequency to 1GHz!");
}

>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
#define SDIO_BASE		(ARC_PERIPHERAL_BASE + 0xA000)
#define SDIO_UHS_REG_EXT	(SDIO_BASE + 0x108)
#define SDIO_UHS_REG_EXT_DIV_2	(2 << 30)

<<<<<<< HEAD
#define HSDK_GPIO_INTC          (ARC_PERIPHERAL_BASE + 0x3000)

static void __init hsdk_enable_gpio_intc_wire(void)
{
	/*
	 * Peripherals on CPU Card are wired to cpu intc via intermediate
	 * DW APB GPIO blocks (mainly for debouncing)
	 *
	 *         ---------------------
	 *        |  snps,archs-intc  |
	 *        ---------------------
	 *                  |
	 *        ----------------------
	 *        | snps,archs-idu-intc |
	 *        ----------------------
	 *         |   |     |   |    |
	 *         | [eth] [USB]    [... other peripherals]
	 *         |
	 * -------------------
	 * | snps,dw-apb-intc |
	 * -------------------
	 *  |      |   |   |
	 * [Bt] [HAPS]   [... other peripherals]
	 *
	 * Current implementation of "irq-dw-apb-ictl" driver doesn't work well
	 * with stacked INTCs. In particular problem happens if its master INTC
	 * not yet instantiated. See discussion here -
	 * https://lkml.org/lkml/2015/3/4/755
	 *
	 * So setup the first gpio block as a passive pass thru and hide it from
	 * DT hardware topology - connect intc directly to cpu intc
	 * The GPIO "wire" needs to be init nevertheless (here)
	 *
	 * One side adv is that peripheral interrupt handling avoids one nested
	 * intc ISR hop
	 *
	 * According to HSDK User's Manual [1], "Table 2 Interrupt Mapping"
	 * we have the following GPIO input lines used as sources of interrupt:
	 * - GPIO[0] - Bluetooth interrupt of RS9113 module
	 * - GPIO[2] - HAPS interrupt (on HapsTrak 3 connector)
	 * - GPIO[3] - Audio codec (MAX9880A) interrupt
	 * - GPIO[8-23] - Available on Arduino and PMOD_x headers
	 * For now there's no use of Arduino and PMOD_x headers in Linux
	 * use-case so we only enable lines 0, 2 and 3.
	 *
	 * [1] https://github.com/foss-for-synopsys-dwc-arc-processors/ARC-Development-Systems-Forum/wiki/docs/ARC_HSDK_User_Guide.pdf
	 */
#define GPIO_INTEN              (HSDK_GPIO_INTC + 0x30)
#define GPIO_INTMASK            (HSDK_GPIO_INTC + 0x34)
#define GPIO_INTTYPE_LEVEL      (HSDK_GPIO_INTC + 0x38)
#define GPIO_INT_POLARITY       (HSDK_GPIO_INTC + 0x3c)
#define GPIO_INT_CONNECTED_MASK	0x0d

	iowrite32(0xffffffff, (void __iomem *) GPIO_INTMASK);
	iowrite32(~GPIO_INT_CONNECTED_MASK, (void __iomem *) GPIO_INTMASK);
	iowrite32(0x00000000, (void __iomem *) GPIO_INTTYPE_LEVEL);
	iowrite32(0xffffffff, (void __iomem *) GPIO_INT_POLARITY);
	iowrite32(GPIO_INT_CONNECTED_MASK, (void __iomem *) GPIO_INTEN);
}

=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
static void __init hsdk_init_early(void)
{
	/*
	 * PAE remapping for DMA clients does not work due to an RTL bug, so
	 * CREG_PAE register must be programmed to all zeroes, otherwise it
	 * will cause problems with DMA to/from peripherals even if PAE40 is
	 * not used.
	 */

	/* Default is 1, which means "PAE offset = 4GByte" */
	writel_relaxed(0, (void __iomem *) CREG_PAE);

	/* Really apply settings made above */
	writel(1, (void __iomem *) CREG_PAE_UPDATE);

	/*
	 * Switch SDIO external ciu clock divider from default div-by-8 to
	 * minimum possible div-by-2.
	 */
	iowrite32(SDIO_UHS_REG_EXT_DIV_2, (void __iomem *) SDIO_UHS_REG_EXT);

<<<<<<< HEAD
	hsdk_enable_gpio_intc_wire();
=======
	/*
	 * Setup CPU frequency to 1GHz.
	 * TODO: remove it after smart hsdk pll driver will be introduced.
	 */
	hsdk_set_cpu_freq_1ghz();
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
}

static const char *hsdk_compat[] __initconst = {
	"snps,hsdk",
	NULL,
};

MACHINE_START(SIMULATION, "hsdk")
	.dt_compat	= hsdk_compat,
	.init_early     = hsdk_init_early,
	.init_per_cpu	= hsdk_init_per_cpu,
MACHINE_END
