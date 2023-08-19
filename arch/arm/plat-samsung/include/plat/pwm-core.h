<<<<<<< HEAD
/* SPDX-License-Identifier: GPL-2.0 */
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
/*
 * Copyright 2013 Tomasz Figa <tomasz.figa@gmail.com>
 *
 * Samsung PWM controller platform data helpers.
<<<<<<< HEAD
=======
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
 */

#ifndef __ASM_ARCH_PWM_CORE_H
#define __ASM_ARCH_PWM_CORE_H __FILE__

#include <clocksource/samsung_pwm.h>

#ifdef CONFIG_SAMSUNG_DEV_PWM
extern void samsung_pwm_set_platdata(struct samsung_pwm_variant *pd);
#else
static inline void samsung_pwm_set_platdata(struct samsung_pwm_variant *pd) { }
#endif

#endif /* __ASM_ARCH_PWM_CORE_H */
