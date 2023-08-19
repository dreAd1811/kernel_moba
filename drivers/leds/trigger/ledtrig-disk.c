/*
 * LED Disk Activity Trigger
 *
 * Copyright 2006 Openedhand Ltd.
 *
 * Author: Richard Purdie <rpurdie@openedhand.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 */

#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/leds.h>

#define BLINK_DELAY 30

DEFINE_LED_TRIGGER(ledtrig_disk);
<<<<<<< HEAD
DEFINE_LED_TRIGGER(ledtrig_disk_read);
DEFINE_LED_TRIGGER(ledtrig_disk_write);
DEFINE_LED_TRIGGER(ledtrig_ide);

void ledtrig_disk_activity(bool write)
=======
DEFINE_LED_TRIGGER(ledtrig_ide);

void ledtrig_disk_activity(void)
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
{
	unsigned long blink_delay = BLINK_DELAY;

	led_trigger_blink_oneshot(ledtrig_disk,
				  &blink_delay, &blink_delay, 0);
	led_trigger_blink_oneshot(ledtrig_ide,
				  &blink_delay, &blink_delay, 0);
<<<<<<< HEAD
	if (write)
		led_trigger_blink_oneshot(ledtrig_disk_write,
					  &blink_delay, &blink_delay, 0);
	else
		led_trigger_blink_oneshot(ledtrig_disk_read,
					  &blink_delay, &blink_delay, 0);
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
}
EXPORT_SYMBOL(ledtrig_disk_activity);

static int __init ledtrig_disk_init(void)
{
	led_trigger_register_simple("disk-activity", &ledtrig_disk);
<<<<<<< HEAD
	led_trigger_register_simple("disk-read", &ledtrig_disk_read);
	led_trigger_register_simple("disk-write", &ledtrig_disk_write);
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	led_trigger_register_simple("ide-disk", &ledtrig_ide);

	return 0;
}
device_initcall(ledtrig_disk_init);
