/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Kernel interface for the s390 arch_random_* functions
 *
 * Copyright IBM Corp. 2017
 *
 * Author: Harald Freudenberger <freude@de.ibm.com>
 *
 */

#ifndef _ASM_S390_ARCHRANDOM_H
#define _ASM_S390_ARCHRANDOM_H

#ifdef CONFIG_ARCH_RANDOM

#include <linux/static_key.h>
#include <linux/atomic.h>
<<<<<<< HEAD
=======
#include <asm/cpacf.h>
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

DECLARE_STATIC_KEY_FALSE(s390_arch_random_available);
extern atomic64_t s390_arch_random_counter;

<<<<<<< HEAD
bool s390_arch_random_generate(u8 *buf, unsigned int nbytes);

static inline bool arch_has_random(void)
{
	return false;
}

static inline bool arch_has_random_seed(void)
=======
static void s390_arch_random_generate(u8 *buf, unsigned int nbytes)
{
	cpacf_trng(NULL, 0, buf, nbytes);
	atomic64_add(nbytes, &s390_arch_random_counter);
}

static inline bool arch_has_random(void)
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
{
	if (static_branch_likely(&s390_arch_random_available))
		return true;
	return false;
}

<<<<<<< HEAD
static inline bool arch_get_random_long(unsigned long *v)
{
=======
static inline bool arch_has_random_seed(void)
{
	return arch_has_random();
}

static inline bool arch_get_random_long(unsigned long *v)
{
	if (static_branch_likely(&s390_arch_random_available)) {
		s390_arch_random_generate((u8 *)v, sizeof(*v));
		return true;
	}
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	return false;
}

static inline bool arch_get_random_int(unsigned int *v)
{
<<<<<<< HEAD
=======
	if (static_branch_likely(&s390_arch_random_available)) {
		s390_arch_random_generate((u8 *)v, sizeof(*v));
		return true;
	}
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	return false;
}

static inline bool arch_get_random_seed_long(unsigned long *v)
{
<<<<<<< HEAD
	if (static_branch_likely(&s390_arch_random_available)) {
		return s390_arch_random_generate((u8 *)v, sizeof(*v));
	}
	return false;
=======
	return arch_get_random_long(v);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
}

static inline bool arch_get_random_seed_int(unsigned int *v)
{
<<<<<<< HEAD
	if (static_branch_likely(&s390_arch_random_available)) {
		return s390_arch_random_generate((u8 *)v, sizeof(*v));
	}
	return false;
=======
	return arch_get_random_int(v);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
}

#endif /* CONFIG_ARCH_RANDOM */
#endif /* _ASM_S390_ARCHRANDOM_H */
