/*
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */
#ifndef _ASM_POWERPC_MMAN_H
#define _ASM_POWERPC_MMAN_H

#include <uapi/asm/mman.h>

#ifdef CONFIG_PPC64

#include <asm/cputable.h>
#include <linux/mm.h>
<<<<<<< HEAD
#include <linux/pkeys.h>
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
#include <asm/cpu_has_feature.h>

/*
 * This file is included by linux/mman.h, so we can't use cacl_vm_prot_bits()
 * here.  How important is the optimization?
 */
static inline unsigned long arch_calc_vm_prot_bits(unsigned long prot,
		unsigned long pkey)
{
<<<<<<< HEAD
#ifdef CONFIG_PPC_MEM_KEYS
	return (((prot & PROT_SAO) ? VM_SAO : 0) | pkey_to_vmflag_bits(pkey));
#else
	return ((prot & PROT_SAO) ? VM_SAO : 0);
#endif
=======
	return (prot & PROT_SAO) ? VM_SAO : 0;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
}
#define arch_calc_vm_prot_bits(prot, pkey) arch_calc_vm_prot_bits(prot, pkey)

static inline pgprot_t arch_vm_get_page_prot(unsigned long vm_flags)
{
<<<<<<< HEAD
#ifdef CONFIG_PPC_MEM_KEYS
	return (vm_flags & VM_SAO) ?
		__pgprot(_PAGE_SAO | vmflag_to_pte_pkey_bits(vm_flags)) :
		__pgprot(0 | vmflag_to_pte_pkey_bits(vm_flags));
#else
	return (vm_flags & VM_SAO) ? __pgprot(_PAGE_SAO) : __pgprot(0);
#endif
}
#define arch_vm_get_page_prot(vm_flags) arch_vm_get_page_prot(vm_flags)

static inline bool arch_validate_prot(unsigned long prot, unsigned long addr)
=======
	return (vm_flags & VM_SAO) ? __pgprot(_PAGE_SAO) : __pgprot(0);
}
#define arch_vm_get_page_prot(vm_flags) arch_vm_get_page_prot(vm_flags)

static inline bool arch_validate_prot(unsigned long prot)
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
{
	if (prot & ~(PROT_READ | PROT_WRITE | PROT_EXEC | PROT_SEM | PROT_SAO))
		return false;
	if ((prot & PROT_SAO) && !cpu_has_feature(CPU_FTR_SAO))
		return false;
	return true;
}
<<<<<<< HEAD
#define arch_validate_prot arch_validate_prot
=======
#define arch_validate_prot(prot) arch_validate_prot(prot)
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

#endif /* CONFIG_PPC64 */
#endif	/* _ASM_POWERPC_MMAN_H */
