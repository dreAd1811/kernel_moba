/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _ASM_M68K_PCI_H
#define _ASM_M68K_PCI_H

#include <asm-generic/pci.h>

<<<<<<< HEAD
=======
/* The PCI address space does equal the physical memory
 * address space.  The networking and block device layers use
 * this boolean for bounce buffer decisions.
 */
#define PCI_DMA_BUS_IS_PHYS	(1)

>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
#define	pcibios_assign_all_busses()	1

#define	PCIBIOS_MIN_IO		0x00000100
#define	PCIBIOS_MIN_MEM		0x02000000

#endif /* _ASM_M68K_PCI_H */
