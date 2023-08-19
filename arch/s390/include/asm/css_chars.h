/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _ASM_CSS_CHARS_H
#define _ASM_CSS_CHARS_H

#include <linux/types.h>

struct css_general_char {
	u64 : 12;
<<<<<<< HEAD
	u64 dynio : 1;	 /* bit 12 */
	u64 : 4;
	u64 eadm : 1;	 /* bit 17 */
	u64 : 23;
	u64 aif : 1;	 /* bit 41 */
	u64 : 3;
	u64 mcss : 1;	 /* bit 45 */
	u64 fcs : 1;	 /* bit 46 */
	u64 : 1;
	u64 ext_mb : 1;  /* bit 48 */
	u64 : 7;
	u64 aif_tdd : 1; /* bit 56 */
	u64 : 1;
	u64 qebsm : 1;	 /* bit 58 */
	u64 : 2;
	u64 aiv : 1;	 /* bit 61 */
	u64 : 2;

	u64 : 3;
	u64 aif_osa : 1; /* bit 67 */
	u64 : 12;
	u64 eadm_rf : 1; /* bit 80 */
	u64 : 1;
	u64 cib : 1;	 /* bit 82 */
	u64 : 5;
	u64 fcx : 1;	 /* bit 88 */
	u64 : 19;
	u64 alt_ssi : 1; /* bit 108 */
	u64 : 1;
	u64 narf : 1;	 /* bit 110 */
	u64 : 12;
	u64 util_str : 1;/* bit 123 */
=======
	u32 dynio : 1;	 /* bit 12 */
	u32 : 4;
	u32 eadm : 1;	 /* bit 17 */
	u32 : 23;
	u32 aif : 1;	 /* bit 41 */
	u32 : 3;
	u32 mcss : 1;	 /* bit 45 */
	u32 fcs : 1;	 /* bit 46 */
	u32 : 1;
	u32 ext_mb : 1;  /* bit 48 */
	u32 : 7;
	u32 aif_tdd : 1; /* bit 56 */
	u32 : 1;
	u32 qebsm : 1;	 /* bit 58 */
	u32 : 8;
	u32 aif_osa : 1; /* bit 67 */
	u32 : 12;
	u32 eadm_rf : 1; /* bit 80 */
	u32 : 1;
	u32 cib : 1;	 /* bit 82 */
	u32 : 5;
	u32 fcx : 1;	 /* bit 88 */
	u32 : 19;
	u32 alt_ssi : 1; /* bit 108 */
	u32:1;
	u32 narf:1;	 /* bit 110 */
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
} __packed;

extern struct css_general_char css_general_characteristics;

#endif
