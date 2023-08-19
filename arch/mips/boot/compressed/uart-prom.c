// SPDX-License-Identifier: GPL-2.0
<<<<<<< HEAD
#include <asm/setup.h>
=======

extern void prom_putchar(unsigned char ch);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

void putc(char c)
{
	prom_putchar(c);
}
