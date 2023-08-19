/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 *
 * Copyright (C) 2010 Gabor Juhos <juhosg@openwrt.org>
 */

#include <linux/mm.h>
#include <linux/io.h>
#include <linux/serial_reg.h>
<<<<<<< HEAD
#include <asm/setup.h>
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

#include "devices.h"
#include "ar2315_regs.h"
#include "ar5312_regs.h"

static inline void prom_uart_wr(void __iomem *base, unsigned reg,
				unsigned char ch)
{
	__raw_writel(ch, base + 4 * reg);
}

static inline unsigned char prom_uart_rr(void __iomem *base, unsigned reg)
{
	return __raw_readl(base + 4 * reg);
}

<<<<<<< HEAD
void prom_putchar(char ch)
=======
void prom_putchar(unsigned char ch)
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
{
	static void __iomem *base;

	if (unlikely(base == NULL)) {
		if (is_ar2315())
			base = (void __iomem *)(KSEG1ADDR(AR2315_UART0_BASE));
		else
			base = (void __iomem *)(KSEG1ADDR(AR5312_UART0_BASE));
	}

	while ((prom_uart_rr(base, UART_LSR) & UART_LSR_THRE) == 0)
		;
<<<<<<< HEAD
	prom_uart_wr(base, UART_TX, (unsigned char)ch);
=======
	prom_uart_wr(base, UART_TX, ch);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	while ((prom_uart_rr(base, UART_LSR) & UART_LSR_THRE) == 0)
		;
}
