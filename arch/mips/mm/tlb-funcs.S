/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 *
 * Micro-assembler generated tlb handler functions.
 *
 * Copyright (C) 2013  Broadcom Corporation.
 *
 * Based on mm/page-funcs.c
 * Copyright (C) 2012  MIPS Technologies, Inc.
 * Copyright (C) 2012  Ralf Baechle <ralf@linux-mips.org>
 */
#include <asm/asm.h>
<<<<<<< HEAD
#include <asm/export.h>
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
#include <asm/regdef.h>

#define FASTPATH_SIZE	128

<<<<<<< HEAD
=======
EXPORT(tlbmiss_handler_setup_pgd_start)
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
LEAF(tlbmiss_handler_setup_pgd)
1:	j	1b		/* Dummy, will be replaced. */
	.space	64
END(tlbmiss_handler_setup_pgd)
EXPORT(tlbmiss_handler_setup_pgd_end)
<<<<<<< HEAD
EXPORT_SYMBOL_GPL(tlbmiss_handler_setup_pgd)
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

LEAF(handle_tlbm)
	.space		FASTPATH_SIZE * 4
END(handle_tlbm)
EXPORT(handle_tlbm_end)

LEAF(handle_tlbs)
	.space		FASTPATH_SIZE * 4
END(handle_tlbs)
EXPORT(handle_tlbs_end)

LEAF(handle_tlbl)
	.space		FASTPATH_SIZE * 4
END(handle_tlbl)
EXPORT(handle_tlbl_end)
