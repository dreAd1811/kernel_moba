<<<<<<< HEAD
/* SPDX-License-Identifier: GPL-2.0 */
/*
=======
/* linux/arch/arm/plat-samsung/include/plat/samsung-time.h
 *
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
 * Copyright 2011 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com/
 *
 * Header file for samsung s3c and s5p time support
<<<<<<< HEAD
 */
=======
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
*/
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

#ifndef __ASM_PLAT_SAMSUNG_TIME_H
#define __ASM_PLAT_SAMSUNG_TIME_H __FILE__

/* SAMSUNG HR-Timer Clock mode */
enum samsung_timer_mode {
	SAMSUNG_PWM0,
	SAMSUNG_PWM1,
	SAMSUNG_PWM2,
	SAMSUNG_PWM3,
	SAMSUNG_PWM4,
};

extern void __init samsung_set_timer_source(enum samsung_timer_mode event,
					enum samsung_timer_mode source);

extern void __init samsung_timer_init(void);

#endif /* __ASM_PLAT_SAMSUNG_TIME_H */
