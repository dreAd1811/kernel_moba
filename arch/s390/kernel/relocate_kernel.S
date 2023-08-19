/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright IBM Corp. 2005
 *
 * Author(s): Rolf Adelsberger,
 *	      Heiko Carstens <heiko.carstens@de.ibm.com>
 *
 */

#include <linux/linkage.h>
#include <asm/page.h>
#include <asm/sigp.h>

/*
 * moves the new kernel to its destination...
 * %r2 = pointer to first kimage_entry_t
 * %r3 = start address - where to jump to after the job is done...
 *
 * %r5 will be used as temp. storage
 * %r6 holds the destination address
 * %r7 = PAGE_SIZE
 * %r8 holds the source address
 * %r9 = PAGE_SIZE
 *
 * 0xf000 is a page_mask
 */

	.text
ENTRY(relocate_kernel)
		basr	%r13,0		# base address
	.base:
<<<<<<< HEAD
=======
		stctg	%c0,%c15,ctlregs-.base(%r13)
		stmg	%r0,%r15,gprregs-.base(%r13)
		lghi	%r0,3
		sllg	%r0,%r0,31
		stg	%r0,0x1d0(%r0)
		la	%r0,.back_pgm-.base(%r13)
		stg	%r0,0x1d8(%r0)
		la	%r1,load_psw-.base(%r13)
		mvc	0(8,%r0),0(%r1)
		la	%r0,.back-.base(%r13)
		st	%r0,4(%r0)
		oi	4(%r0),0x80
		lghi	%r0,0
		diag	%r0,%r0,0x308
	.back:
		lhi	%r1,1		# mode 1 = esame
		sigp	%r1,%r0,SIGP_SET_ARCHITECTURE # switch to esame mode
		sam64			# switch to 64 bit addressing mode
		basr	%r13,0
	.back_base:
		oi	have_diag308-.back_base(%r13),0x01
		lctlg	%c0,%c15,ctlregs-.back_base(%r13)
		lmg	%r0,%r15,gprregs-.back_base(%r13)
		j	.top
	.back_pgm:
		lmg	%r0,%r15,gprregs-.base(%r13)
	.top:
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
		lghi	%r7,PAGE_SIZE	# load PAGE_SIZE in r7
		lghi	%r9,PAGE_SIZE	# load PAGE_SIZE in r9
		lg	%r5,0(%r2)	# read another word for indirection page
		aghi	%r2,8		# increment pointer
		tml	%r5,0x1		# is it a destination page?
		je	.indir_check	# NO, goto "indir_check"
		lgr	%r6,%r5		# r6 = r5
		nill	%r6,0xf000	# mask it out and...
<<<<<<< HEAD
		j	.base		# ...next iteration
=======
		j	.top		# ...next iteration
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	.indir_check:
		tml	%r5,0x2		# is it a indirection page?
		je	.done_test	# NO, goto "done_test"
		nill	%r5,0xf000	# YES, mask out,
		lgr	%r2,%r5		# move it into the right register,
<<<<<<< HEAD
		j	.base		# and read next...
=======
		j	.top		# and read next...
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	.done_test:
		tml	%r5,0x4		# is it the done indicator?
		je	.source_test	# NO! Well, then it should be the source indicator...
		j	.done		# ok, lets finish it here...
	.source_test:
		tml	%r5,0x8		# it should be a source indicator...
<<<<<<< HEAD
		je	.base		# NO, ignore it...
=======
		je	.top		# NO, ignore it...
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
		lgr	%r8,%r5		# r8 = r5
		nill	%r8,0xf000	# masking
	0:	mvcle	%r6,%r8,0x0	# copy PAGE_SIZE bytes from r8 to r6 - pad with 0
		jo	0b
<<<<<<< HEAD
		j	.base
=======
		j	.top
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	.done:
		sgr	%r0,%r0		# clear register r0
		la	%r4,load_psw-.base(%r13)	# load psw-address into the register
		o	%r3,4(%r4)	# or load address into psw
		st	%r3,4(%r4)
		mvc	0(8,%r0),0(%r4)	# copy psw to absolute address 0
<<<<<<< HEAD
		diag	%r0,%r0,0x308
=======
		tm	have_diag308-.base(%r13),0x01
		jno	.no_diag308
		diag	%r0,%r0,0x308
	.no_diag308:
		sam31			# 31 bit mode
		sr	%r1,%r1		# erase register r1
		sr	%r2,%r2		# erase register r2
		sigp	%r1,%r2,SIGP_SET_ARCHITECTURE # set cpuid to zero
		lpsw	0		# hopefully start new kernel...
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

		.align	8
	load_psw:
		.long	0x00080000,0x80000000
<<<<<<< HEAD
=======
	ctlregs:
		.rept	16
		.quad	0
		.endr
	gprregs:
		.rept	16
		.quad	0
		.endr
	have_diag308:
		.byte	0
		.align	8
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	relocate_kernel_end:
	.align 8
	.globl	relocate_kernel_len
	relocate_kernel_len:
		.quad	relocate_kernel_end - relocate_kernel
