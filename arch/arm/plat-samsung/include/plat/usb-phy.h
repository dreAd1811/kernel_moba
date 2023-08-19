<<<<<<< HEAD
/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright (C) 2011 Samsung Electronics Co.Ltd
 * Author: Joonyoung Shim <jy0922.shim@samsung.com>
=======
/*
 * Copyright (C) 2011 Samsung Electronics Co.Ltd
 * Author: Joonyoung Shim <jy0922.shim@samsung.com>
 *
 * This program is free software; you can redistribute  it and/or modify it
 * under  the terms of  the GNU General  Public License as published by the
 * Free Software Foundation;  either version 2 of the  License, or (at your
 * option) any later version.
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
 */

#ifndef __PLAT_SAMSUNG_USB_PHY_H
#define __PLAT_SAMSUNG_USB_PHY_H __FILE__

#include <linux/usb/samsung_usb_phy.h>

extern int s5p_usb_phy_init(struct platform_device *pdev, int type);
extern int s5p_usb_phy_exit(struct platform_device *pdev, int type);

#endif /* __PLAT_SAMSUNG_USB_PHY_H */
