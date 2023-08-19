/*
 * LED Kernel Default ON Trigger
 *
 * Copyright 2008 Nick Forbes <nick.forbes@incepta.com>
 *
 * Based on Richard Purdie's ledtrig-timer.c.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
<<<<<<< HEAD
=======
 *
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/leds.h>
#include "../leds.h"

<<<<<<< HEAD
static int defon_trig_activate(struct led_classdev *led_cdev)
{
	led_set_brightness_nosleep(led_cdev, led_cdev->max_brightness);
	return 0;
=======
static void defon_trig_activate(struct led_classdev *led_cdev)
{
	led_set_brightness_nosleep(led_cdev, led_cdev->max_brightness);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
}

static struct led_trigger defon_led_trigger = {
	.name     = "default-on",
	.activate = defon_trig_activate,
};
<<<<<<< HEAD
module_led_trigger(defon_led_trigger);

MODULE_AUTHOR("Nick Forbes <nick.forbes@incepta.com>");
MODULE_DESCRIPTION("Default-ON LED trigger");
MODULE_LICENSE("GPL v2");
=======

static int __init defon_trig_init(void)
{
	return led_trigger_register(&defon_led_trigger);
}

static void __exit defon_trig_exit(void)
{
	led_trigger_unregister(&defon_led_trigger);
}

module_init(defon_trig_init);
module_exit(defon_trig_exit);

MODULE_AUTHOR("Nick Forbes <nick.forbes@incepta.com>");
MODULE_DESCRIPTION("Default-ON LED trigger");
MODULE_LICENSE("GPL");
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
