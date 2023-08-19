/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _PARISC_SECTIONS_H
#define _PARISC_SECTIONS_H

/* nothing to see, move along */
#include <asm-generic/sections.h>

#ifdef CONFIG_64BIT
<<<<<<< HEAD

#define HAVE_DEREFERENCE_FUNCTION_DESCRIPTOR 1

#undef dereference_function_descriptor
void *dereference_function_descriptor(void *);

#undef dereference_kernel_function_descriptor
void *dereference_kernel_function_descriptor(void *);
=======
#undef dereference_function_descriptor
void *dereference_function_descriptor(void *);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
#endif

#endif
