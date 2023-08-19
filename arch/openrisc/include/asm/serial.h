/*
 * OpenRISC Linux
 *
 * Linux architectural port borrowing liberally from similar works of
 * others.  All original copyrights apply as per the original source
 * declaration.
 *
 * OpenRISC implementation:
 * Copyright (C) 2003 Matjaz Breskvar <phoenix@bsemi.com>
 * Copyright (C) 2010-2011 Jonas Bonn <jonas@southpole.se>
 * et al.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#ifndef __ASM_OPENRISC_SERIAL_H
#define __ASM_OPENRISC_SERIAL_H

#ifdef __KERNEL__

#include <asm/cpuinfo.h>

/* There's a generic version of this file, but it assumes a 1.8MHz UART clk...
 * this, on the other hand, assumes the UART clock is tied to the system
 * clock... 8250_early.c (early 8250 serial console) actually uses this, so
 * it needs to be correct to get the early console working.
 */

<<<<<<< HEAD
#define BASE_BAUD (cpuinfo_or1k[smp_processor_id()].clock_frequency/16)
=======
#define BASE_BAUD (cpuinfo.clock_frequency/16)
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

#endif /* __KERNEL__ */

#endif /* __ASM_OPENRISC_SERIAL_H */
