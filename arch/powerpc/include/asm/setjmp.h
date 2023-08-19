/*
 * Copyright © 2008 Michael Neuling IBM Corporation
 *
 *      This program is free software; you can redistribute it and/or
 *      modify it under the terms of the GNU General Public License
 *      as published by the Free Software Foundation; either version
 *      2 of the License, or (at your option) any later version.
 *
 */
#ifndef _ASM_POWERPC_SETJMP_H
#define _ASM_POWERPC_SETJMP_H

#define JMP_BUF_LEN    23

<<<<<<< HEAD
extern long setjmp(long *);
extern void longjmp(long *, long);
=======
typedef long jmp_buf[JMP_BUF_LEN];

extern int setjmp(jmp_buf env) __attribute__((returns_twice));
extern void longjmp(jmp_buf env, int val) __attribute__((noreturn));
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

#endif /* _ASM_POWERPC_SETJMP_H */
