<<<<<<< HEAD
// SPDX-License-Identifier: GPL-2.0
// Copyright (c) 2009,2018 Daniel Mack <daniel@zonque.org>
=======
/*
 * LEDs driver for LT3593 controllers
 *
 * See the datasheet at http://cds.linear.com/docs/Datasheet/3593f.pdf
 *
 * Copyright (c) 2009 Daniel Mack <daniel@caiaq.de>
 *
 * Based on leds-gpio.c,
 *
 *   Copyright (C) 2007 8D Technologies inc.
 *   Raphael Assenat <raph@8d.com>
 *   Copyright (C) 2008 Freescale Semiconductor, Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

#include <linux/kernel.h>
#include <linux/platform_device.h>
#include <linux/leds.h>
#include <linux/delay.h>
#include <linux/gpio.h>
<<<<<<< HEAD
#include <linux/gpio/consumer.h>
#include <linux/slab.h>
#include <linux/module.h>
#include <linux/of.h>
#include <uapi/linux/uleds.h>

struct lt3593_led_data {
	char name[LED_MAX_NAME_SIZE];
	struct led_classdev cdev;
	struct gpio_desc *gpiod;
=======
#include <linux/slab.h>
#include <linux/module.h>

struct lt3593_led_data {
	struct led_classdev cdev;
	unsigned gpio;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
};

static int lt3593_led_set(struct led_classdev *led_cdev,
			   enum led_brightness value)
{
	struct lt3593_led_data *led_dat =
		container_of(led_cdev, struct lt3593_led_data, cdev);
	int pulses;

	/*
	 * The LT3593 resets its internal current level register to the maximum
	 * level on the first falling edge on the control pin. Each following
	 * falling edge decreases the current level by 625uA. Up to 32 pulses
	 * can be sent, so the maximum power reduction is 20mA.
	 * After a timeout of 128us, the value is taken from the register and
	 * applied is to the output driver.
	 */

	if (value == 0) {
<<<<<<< HEAD
		gpiod_set_value_cansleep(led_dat->gpiod, 0);
=======
		gpio_set_value_cansleep(led_dat->gpio, 0);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
		return 0;
	}

	pulses = 32 - (value * 32) / 255;

	if (pulses == 0) {
<<<<<<< HEAD
		gpiod_set_value_cansleep(led_dat->gpiod, 0);
		mdelay(1);
		gpiod_set_value_cansleep(led_dat->gpiod, 1);
		return 0;
	}

	gpiod_set_value_cansleep(led_dat->gpiod, 1);

	while (pulses--) {
		gpiod_set_value_cansleep(led_dat->gpiod, 0);
		udelay(1);
		gpiod_set_value_cansleep(led_dat->gpiod, 1);
=======
		gpio_set_value_cansleep(led_dat->gpio, 0);
		mdelay(1);
		gpio_set_value_cansleep(led_dat->gpio, 1);
		return 0;
	}

	gpio_set_value_cansleep(led_dat->gpio, 1);

	while (pulses--) {
		gpio_set_value_cansleep(led_dat->gpio, 0);
		udelay(1);
		gpio_set_value_cansleep(led_dat->gpio, 1);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
		udelay(1);
	}

	return 0;
}

<<<<<<< HEAD
static struct lt3593_led_data *lt3593_led_probe_pdata(struct device *dev)
{
	struct gpio_led_platform_data *pdata = dev_get_platdata(dev);
	const struct gpio_led *template = &pdata->leds[0];
	struct lt3593_led_data *led_data;
	int ret, state;

	if (pdata->num_leds != 1)
		return ERR_PTR(-EINVAL);

	led_data = devm_kzalloc(dev, sizeof(*led_data), GFP_KERNEL);
	if (!led_data)
		return ERR_PTR(-ENOMEM);

	led_data->cdev.name = template->name;
	led_data->cdev.default_trigger = template->default_trigger;
	led_data->cdev.brightness_set_blocking = lt3593_led_set;

	state = (template->default_state == LEDS_GPIO_DEFSTATE_ON);
	led_data->cdev.brightness = state ? LED_FULL : LED_OFF;

	if (!template->retain_state_suspended)
		led_data->cdev.flags |= LED_CORE_SUSPENDRESUME;

	ret = devm_gpio_request_one(dev, template->gpio, state ?
				    GPIOF_OUT_INIT_HIGH : GPIOF_OUT_INIT_LOW,
				    template->name);
	if (ret < 0)
		return ERR_PTR(ret);

	led_data->gpiod = gpio_to_desc(template->gpio);
	if (!led_data->gpiod)
		return ERR_PTR(-EPROBE_DEFER);

	ret = devm_led_classdev_register(dev, &led_data->cdev);
	if (ret < 0)
		return ERR_PTR(ret);

	dev_info(dev, "registered LT3593 LED '%s' at GPIO %d\n",
		 template->name, template->gpio);

	return led_data;
=======
static int create_lt3593_led(const struct gpio_led *template,
	struct lt3593_led_data *led_dat, struct device *parent)
{
	int ret, state;

	/* skip leds on GPIOs that aren't available */
	if (!gpio_is_valid(template->gpio)) {
		dev_info(parent, "%s: skipping unavailable LT3593 LED at gpio %d (%s)\n",
				KBUILD_MODNAME, template->gpio, template->name);
		return 0;
	}

	led_dat->cdev.name = template->name;
	led_dat->cdev.default_trigger = template->default_trigger;
	led_dat->gpio = template->gpio;

	led_dat->cdev.brightness_set_blocking = lt3593_led_set;

	state = (template->default_state == LEDS_GPIO_DEFSTATE_ON);
	led_dat->cdev.brightness = state ? LED_FULL : LED_OFF;

	if (!template->retain_state_suspended)
		led_dat->cdev.flags |= LED_CORE_SUSPENDRESUME;

	ret = devm_gpio_request_one(parent, template->gpio, state ?
				    GPIOF_OUT_INIT_HIGH : GPIOF_OUT_INIT_LOW,
				    template->name);
	if (ret < 0)
		return ret;

	ret = led_classdev_register(parent, &led_dat->cdev);
	if (ret < 0)
		return ret;

	dev_info(parent, "%s: registered LT3593 LED '%s' at GPIO %d\n",
		KBUILD_MODNAME, template->name, template->gpio);

	return 0;
}

static void delete_lt3593_led(struct lt3593_led_data *led)
{
	if (!gpio_is_valid(led->gpio))
		return;

	led_classdev_unregister(&led->cdev);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
}

static int lt3593_led_probe(struct platform_device *pdev)
{
<<<<<<< HEAD
	struct device *dev = &pdev->dev;
	struct lt3593_led_data *led_data;
	struct fwnode_handle *child;
	int ret, state = LEDS_GPIO_DEFSTATE_OFF;
	enum gpiod_flags flags = GPIOD_OUT_LOW;
	const char *tmp;

	if (dev_get_platdata(dev)) {
		led_data = lt3593_led_probe_pdata(dev);
		if (IS_ERR(led_data))
			return PTR_ERR(led_data);

		goto out;
	}

	if (!dev->of_node)
		return -ENODEV;

	led_data = devm_kzalloc(dev, sizeof(*led_data), GFP_KERNEL);
	if (!led_data)
		return -ENOMEM;

	if (device_get_child_node_count(dev) != 1) {
		dev_err(dev, "Device must have exactly one LED sub-node.");
		return -EINVAL;
	}

	led_data->gpiod = devm_gpiod_get(dev, "lltc,ctrl", 0);
	if (IS_ERR(led_data->gpiod))
		return PTR_ERR(led_data->gpiod);

	child = device_get_next_child_node(dev, NULL);

	ret = fwnode_property_read_string(child, "label", &tmp);
	if (ret < 0)
		snprintf(led_data->name, sizeof(led_data->name),
			 "lt3593::");
	else
		snprintf(led_data->name, sizeof(led_data->name),
			 "lt3593:%s", tmp);

	fwnode_property_read_string(child, "linux,default-trigger",
				    &led_data->cdev.default_trigger);

	if (!fwnode_property_read_string(child, "default-state", &tmp)) {
		if (!strcmp(tmp, "keep")) {
			state = LEDS_GPIO_DEFSTATE_KEEP;
			flags = GPIOD_ASIS;
		} else if (!strcmp(tmp, "on")) {
			state = LEDS_GPIO_DEFSTATE_ON;
			flags = GPIOD_OUT_HIGH;
		}
	}

	led_data->cdev.name = led_data->name;
	led_data->cdev.brightness_set_blocking = lt3593_led_set;
	led_data->cdev.brightness = state ? LED_FULL : LED_OFF;

	ret = devm_led_classdev_register(dev, &led_data->cdev);
	if (ret < 0) {
		fwnode_handle_put(child);
		return ret;
	}

	led_data->cdev.dev->of_node = dev->of_node;

out:
	platform_set_drvdata(pdev, led_data);
=======
	struct gpio_led_platform_data *pdata = dev_get_platdata(&pdev->dev);
	struct lt3593_led_data *leds_data;
	int i, ret = 0;

	if (!pdata)
		return -EBUSY;

	leds_data = devm_kzalloc(&pdev->dev,
			sizeof(struct lt3593_led_data) * pdata->num_leds,
			GFP_KERNEL);
	if (!leds_data)
		return -ENOMEM;

	for (i = 0; i < pdata->num_leds; i++) {
		ret = create_lt3593_led(&pdata->leds[i], &leds_data[i],
				      &pdev->dev);
		if (ret < 0)
			goto err;
	}

	platform_set_drvdata(pdev, leds_data);

	return 0;

err:
	for (i = i - 1; i >= 0; i--)
		delete_lt3593_led(&leds_data[i]);

	return ret;
}

static int lt3593_led_remove(struct platform_device *pdev)
{
	int i;
	struct gpio_led_platform_data *pdata = dev_get_platdata(&pdev->dev);
	struct lt3593_led_data *leds_data;

	leds_data = platform_get_drvdata(pdev);

	for (i = 0; i < pdata->num_leds; i++)
		delete_lt3593_led(&leds_data[i]);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	return 0;
}

<<<<<<< HEAD
#ifdef CONFIG_OF
static const struct of_device_id of_lt3593_leds_match[] = {
	{ .compatible = "lltc,lt3593", },
	{},
};
MODULE_DEVICE_TABLE(of, of_lt3593_leds_match);
#endif

static struct platform_driver lt3593_led_driver = {
	.probe		= lt3593_led_probe,
	.driver		= {
		.name	= "leds-lt3593",
		.of_match_table = of_match_ptr(of_lt3593_leds_match),
=======
static struct platform_driver lt3593_led_driver = {
	.probe		= lt3593_led_probe,
	.remove		= lt3593_led_remove,
	.driver		= {
		.name	= "leds-lt3593",
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	},
};

module_platform_driver(lt3593_led_driver);

<<<<<<< HEAD
MODULE_AUTHOR("Daniel Mack <daniel@zonque.org>");
MODULE_DESCRIPTION("LED driver for LT3593 controllers");
MODULE_LICENSE("GPL v2");
=======
MODULE_AUTHOR("Daniel Mack <daniel@caiaq.de>");
MODULE_DESCRIPTION("LED driver for LT3593 controllers");
MODULE_LICENSE("GPL");
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
MODULE_ALIAS("platform:leds-lt3593");
