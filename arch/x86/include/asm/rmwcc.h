/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _ASM_X86_RMWcc
#define _ASM_X86_RMWcc

#define __CLOBBERS_MEM(clb...)	"memory", ## clb

<<<<<<< HEAD
#if !defined(__GCC_ASM_FLAG_OUTPUTS__) && defined(CONFIG_CC_HAS_ASM_GOTO)
=======
#if !defined(__GCC_ASM_FLAG_OUTPUTS__) && defined(CC_HAVE_ASM_GOTO)
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* Use asm goto */

#define __GEN_RMWcc(fullop, var, cc, clobbers, ...)			\
do {									\
	asm_volatile_goto (fullop "; j" #cc " %l[cc_label]"		\
			: : [counter] "m" (var), ## __VA_ARGS__		\
			: clobbers : cc_label);				\
	return 0;							\
cc_label:								\
	return 1;							\
} while (0)

#define __BINARY_RMWcc_ARG	" %1, "


<<<<<<< HEAD
#else /* defined(__GCC_ASM_FLAG_OUTPUTS__) || !defined(CONFIG_CC_HAS_ASM_GOTO) */
=======
#else /* defined(__GCC_ASM_FLAG_OUTPUTS__) || !defined(CC_HAVE_ASM_GOTO) */
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* Use flags output or a set instruction */

#define __GEN_RMWcc(fullop, var, cc, clobbers, ...)			\
do {									\
	bool c;								\
	asm volatile (fullop CC_SET(cc)					\
			: [counter] "+m" (var), CC_OUT(cc) (c)		\
			: __VA_ARGS__ : clobbers);			\
	return c;							\
} while (0)

#define __BINARY_RMWcc_ARG	" %2, "

<<<<<<< HEAD
#endif /* defined(__GCC_ASM_FLAG_OUTPUTS__) || !defined(CONFIG_CC_HAS_ASM_GOTO) */
=======
#endif /* defined(__GCC_ASM_FLAG_OUTPUTS__) || !defined(CC_HAVE_ASM_GOTO) */
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

#define GEN_UNARY_RMWcc(op, var, arg0, cc)				\
	__GEN_RMWcc(op " " arg0, var, cc, __CLOBBERS_MEM())

#define GEN_UNARY_SUFFIXED_RMWcc(op, suffix, var, arg0, cc, clobbers...)\
	__GEN_RMWcc(op " " arg0 "\n\t" suffix, var, cc,			\
		    __CLOBBERS_MEM(clobbers))

#define GEN_BINARY_RMWcc(op, var, vcon, val, arg0, cc)			\
	__GEN_RMWcc(op __BINARY_RMWcc_ARG arg0, var, cc,		\
		    __CLOBBERS_MEM(), vcon (val))

#define GEN_BINARY_SUFFIXED_RMWcc(op, suffix, var, vcon, val, arg0, cc,	\
				  clobbers...)				\
	__GEN_RMWcc(op __BINARY_RMWcc_ARG arg0 "\n\t" suffix, var, cc,	\
		    __CLOBBERS_MEM(clobbers), vcon (val))

#endif /* _ASM_X86_RMWcc */
