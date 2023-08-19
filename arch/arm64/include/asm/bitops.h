/*
 * Copyright (C) 2012 ARM Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef __ASM_BITOPS_H
#define __ASM_BITOPS_H

#include <linux/compiler.h>
<<<<<<< HEAD
=======
#include <asm/barrier.h>
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

#ifndef _LINUX_BITOPS_H
#error only <linux/bitops.h> can be included directly
#endif

<<<<<<< HEAD
=======
/*
 * Little endian assembly atomic bitops.
 */
extern void set_bit(int nr, volatile unsigned long *p);
extern void clear_bit(int nr, volatile unsigned long *p);
extern void change_bit(int nr, volatile unsigned long *p);
extern int test_and_set_bit(int nr, volatile unsigned long *p);
extern int test_and_clear_bit(int nr, volatile unsigned long *p);
extern int test_and_change_bit(int nr, volatile unsigned long *p);

>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
#include <asm-generic/bitops/builtin-__ffs.h>
#include <asm-generic/bitops/builtin-ffs.h>
#include <asm-generic/bitops/builtin-__fls.h>
#include <asm-generic/bitops/builtin-fls.h>

#include <asm-generic/bitops/ffz.h>
#include <asm-generic/bitops/fls64.h>
#include <asm-generic/bitops/find.h>

#include <asm-generic/bitops/sched.h>
#include <asm-generic/bitops/hweight.h>
<<<<<<< HEAD

#include <asm-generic/bitops/atomic.h>
#include <asm-generic/bitops/lock.h>
#include <asm-generic/bitops/non-atomic.h>
#include <asm-generic/bitops/le.h>
#include <asm-generic/bitops/ext2-atomic-setbit.h>
=======
#include <asm-generic/bitops/lock.h>

#include <asm-generic/bitops/non-atomic.h>
#include <asm-generic/bitops/le.h>

/*
 * Ext2 is defined to use little-endian byte ordering.
 */
#define ext2_set_bit_atomic(lock, nr, p)	test_and_set_bit_le(nr, p)
#define ext2_clear_bit_atomic(lock, nr, p)	test_and_clear_bit_le(nr, p)
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

#endif /* __ASM_BITOPS_H */
