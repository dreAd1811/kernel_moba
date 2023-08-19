/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _ASM_POWERPC_ARCHRANDOM_H
#define _ASM_POWERPC_ARCHRANDOM_H

#ifdef CONFIG_ARCH_RANDOM

#include <asm/machdep.h>

static inline int arch_get_random_long(unsigned long *v)
{
	return 0;
}

static inline int arch_get_random_int(unsigned int *v)
{
	return 0;
}

static inline int arch_get_random_seed_long(unsigned long *v)
{
	if (ppc_md.get_random_seed)
		return ppc_md.get_random_seed(v);

	return 0;
}
static inline int arch_get_random_seed_int(unsigned int *v)
{
	unsigned long val;
	int rc;

<<<<<<< HEAD
	rc = arch_get_random_long(&val);
=======
	rc = arch_get_random_seed_long(&val);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	if (rc)
		*v = val;

	return rc;
}

static inline int arch_has_random(void)
{
	return 0;
}

static inline int arch_has_random_seed(void)
{
	return !!ppc_md.get_random_seed;
}
#endif /* CONFIG_ARCH_RANDOM */

#ifdef CONFIG_PPC_POWERNV
int powernv_hwrng_present(void);
int powernv_get_random_long(unsigned long *v);
int powernv_get_random_real_mode(unsigned long *v);
#else
static inline int powernv_hwrng_present(void) { return 0; }
static inline int powernv_get_random_real_mode(unsigned long *v) { return 0; }
#endif

#endif /* _ASM_POWERPC_ARCHRANDOM_H */
