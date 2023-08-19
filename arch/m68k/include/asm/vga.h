/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _ASM_M68K_VGA_H
#define _ASM_M68K_VGA_H

<<<<<<< HEAD
/*
 * Some ColdFire platforms do in fact have a PCI bus. So for those we want
 * to use the real IO access functions, don't fake them out or redirect them
 * for that case.
 */
#ifndef CONFIG_PCI

#include <asm/raw_io.h>
#include <asm/kmap.h>
=======
#include <asm/raw_io.h>
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/*
 * FIXME
 * Ugh, we don't have PCI space, so map readb() and friends to use raw I/O
 * accessors, which are identical to the z_*() Zorro bus accessors.
 * This should make cirrusfb work again on Amiga
 */
#undef inb_p
#undef inw_p
#undef outb_p
#undef outw
#undef readb
#undef writeb
#undef writew
#define inb_p(port)		0
#define inw_p(port)		0
#define outb_p(port, val)	do { } while (0)
#define outw(port, val)		do { } while (0)
#define readb			raw_inb
#define writeb			raw_outb
#define writew			raw_outw

<<<<<<< HEAD
#endif /* CONFIG_PCI */
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
#endif /* _ASM_M68K_VGA_H */
