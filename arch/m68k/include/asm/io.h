/* SPDX-License-Identifier: GPL-2.0 */
<<<<<<< HEAD
#ifndef _M68K_IO_H
#define _M68K_IO_H

#if defined(__uClinux__) || defined(CONFIG_COLDFIRE)
=======
#ifdef __uClinux__
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
#include <asm/io_no.h>
#else
#include <asm/io_mm.h>
#endif

<<<<<<< HEAD
#include <asm-generic/io.h>

#endif /* _M68K_IO_H */
=======
#define readb_relaxed(addr)	readb(addr)
#define readw_relaxed(addr)	readw(addr)
#define readl_relaxed(addr)	readl(addr)

#define writeb_relaxed(b, addr)	writeb(b, addr)
#define writew_relaxed(b, addr)	writew(b, addr)
#define writel_relaxed(b, addr)	writel(b, addr)
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
