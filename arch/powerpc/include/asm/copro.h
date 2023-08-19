/*
 * Copyright 2014 IBM Corp.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */

#ifndef _ASM_POWERPC_COPRO_H
#define _ASM_POWERPC_COPRO_H

<<<<<<< HEAD
#include <linux/mm_types.h>

=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
struct copro_slb
{
	u64 esid, vsid;
};

int copro_handle_mm_fault(struct mm_struct *mm, unsigned long ea,
<<<<<<< HEAD
			  unsigned long dsisr, vm_fault_t *flt);
=======
			  unsigned long dsisr, unsigned *flt);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

int copro_calculate_slb(struct mm_struct *mm, u64 ea, struct copro_slb *slb);


#ifdef CONFIG_PPC_COPRO_BASE
void copro_flush_all_slbs(struct mm_struct *mm);
#else
static inline void copro_flush_all_slbs(struct mm_struct *mm) {}
#endif
#endif /* _ASM_POWERPC_COPRO_H */
