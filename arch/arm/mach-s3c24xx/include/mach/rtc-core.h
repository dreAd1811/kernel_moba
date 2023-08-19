<<<<<<< HEAD
/* SPDX-License-Identifier: GPL-2.0 */
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
/*
 * Copyright (c) 2011 Heiko Stuebner <heiko@sntech.de>
 *
 * Samsung RTC Controller core functions
<<<<<<< HEAD
 */
=======
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
*/
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

#ifndef __RTC_CORE_H
#define __RTC_CORE_H __FILE__

/* These functions are only for use with the core support code, such as
 * the cpu specific initialisation code
 */

extern struct platform_device s3c_device_rtc;

/* re-define device name depending on support. */
static inline void s3c_rtc_setname(char *name)
{
	s3c_device_rtc.name = name;
}

#endif /* __RTC_CORE_H */
