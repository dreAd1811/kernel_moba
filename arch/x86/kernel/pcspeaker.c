// SPDX-License-Identifier: GPL-2.0
#include <linux/platform_device.h>
#include <linux/err.h>
#include <linux/init.h>

static __init int add_pcspkr(void)
{
	struct platform_device *pd;

	pd = platform_device_register_simple("pcspkr", -1, NULL, 0);

<<<<<<< HEAD
	return PTR_ERR_OR_ZERO(pd);
=======
	return IS_ERR(pd) ? PTR_ERR(pd) : 0;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
}
device_initcall(add_pcspkr);
