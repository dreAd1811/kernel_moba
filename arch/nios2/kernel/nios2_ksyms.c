/*
 * Copyright (C) 2004 Microtronix Datacom Ltd
 *
 * This file is subject to the terms and conditions of the GNU General
 * Public License. See the file COPYING in the main directory of this
 * archive for more details.
 */

#include <linux/export.h>
#include <linux/string.h>

<<<<<<< HEAD
=======
#include <asm/cacheflush.h>
#include <asm/pgtable.h>

>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
/* string functions */

EXPORT_SYMBOL(memcpy);
EXPORT_SYMBOL(memset);
EXPORT_SYMBOL(memmove);

<<<<<<< HEAD
=======
/* memory management */

EXPORT_SYMBOL(empty_zero_page);
EXPORT_SYMBOL(flush_icache_range);

>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
/*
 * libgcc functions - functions that are used internally by the
 * compiler...  (prototypes are not correct though, but that
 * doesn't really matter since they're not versioned).
 */
#define DECLARE_EXPORT(name)	extern void name(void); EXPORT_SYMBOL(name)

DECLARE_EXPORT(__gcc_bcmp);
DECLARE_EXPORT(__divsi3);
DECLARE_EXPORT(__moddi3);
DECLARE_EXPORT(__modsi3);
DECLARE_EXPORT(__udivmoddi4);
DECLARE_EXPORT(__udivsi3);
DECLARE_EXPORT(__umoddi3);
DECLARE_EXPORT(__umodsi3);
DECLARE_EXPORT(__muldi3);
<<<<<<< HEAD
=======
DECLARE_EXPORT(__ucmpdi2);
DECLARE_EXPORT(__lshrdi3);
DECLARE_EXPORT(__ashldi3);
DECLARE_EXPORT(__ashrdi3);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
