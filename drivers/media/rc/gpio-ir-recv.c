/* Copyright (c) 2012, Code Aurora Forum. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/interrupt.h>
<<<<<<< HEAD
#include <linux/gpio/consumer.h>
=======
#include <linux/gpio.h>
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
#include <linux/slab.h>
#include <linux/of.h>
#include <linux/of_gpio.h>
#include <linux/platform_device.h>
#include <linux/irq.h>
#include <media/rc-core.h>
<<<<<<< HEAD

=======
#include <linux/platform_data/media/gpio-ir-recv.h>

#define GPIO_IR_DRIVER_NAME	"gpio-rc-recv"
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
#define GPIO_IR_DEVICE_NAME	"gpio_ir_recv"

struct gpio_rc_dev {
	struct rc_dev *rcdev;
<<<<<<< HEAD
	struct gpio_desc *gpiod;
	int irq;
};

static irqreturn_t gpio_ir_recv_irq(int irq, void *dev_id)
{
	int val;
	struct gpio_rc_dev *gpio_dev = dev_id;

	val = gpiod_get_value(gpio_dev->gpiod);
	if (val >= 0)
		ir_raw_event_store_edge(gpio_dev->rcdev, val == 1);

=======
	int gpio_nr;
	bool active_low;
};

#ifdef CONFIG_OF
/*
 * Translate OpenFirmware node properties into platform_data
 */
static int gpio_ir_recv_get_devtree_pdata(struct device *dev,
				  struct gpio_ir_recv_platform_data *pdata)
{
	struct device_node *np = dev->of_node;
	enum of_gpio_flags flags;
	int gpio;

	gpio = of_get_gpio_flags(np, 0, &flags);
	if (gpio < 0) {
		if (gpio != -EPROBE_DEFER)
			dev_err(dev, "Failed to get gpio flags (%d)\n", gpio);
		return gpio;
	}

	pdata->gpio_nr = gpio;
	pdata->active_low = (flags & OF_GPIO_ACTIVE_LOW);
	/* probe() takes care of map_name == NULL or allowed_protos == 0 */
	pdata->map_name = of_get_property(np, "linux,rc-map-name", NULL);
	pdata->allowed_protos = 0;

	return 0;
}

static const struct of_device_id gpio_ir_recv_of_match[] = {
	{ .compatible = "gpio-ir-receiver", },
	{ },
};
MODULE_DEVICE_TABLE(of, gpio_ir_recv_of_match);

#else /* !CONFIG_OF */

#define gpio_ir_recv_get_devtree_pdata(dev, pdata)	(-ENOSYS)

#endif

static irqreturn_t gpio_ir_recv_irq(int irq, void *dev_id)
{
	struct gpio_rc_dev *gpio_dev = dev_id;
	int gval;
	int rc = 0;

	gval = gpio_get_value(gpio_dev->gpio_nr);

	if (gval < 0)
		goto err_get_value;

	if (gpio_dev->active_low)
		gval = !gval;

	rc = ir_raw_event_store_edge(gpio_dev->rcdev, gval == 1);
	if (rc < 0)
		goto err_get_value;

err_get_value:
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	return IRQ_HANDLED;
}

static int gpio_ir_recv_probe(struct platform_device *pdev)
{
<<<<<<< HEAD
	struct device *dev = &pdev->dev;
	struct device_node *np = dev->of_node;
	struct gpio_rc_dev *gpio_dev;
	struct rc_dev *rcdev;
	int rc;

	if (!np)
		return -ENODEV;

	gpio_dev = devm_kzalloc(dev, sizeof(*gpio_dev), GFP_KERNEL);
	if (!gpio_dev)
		return -ENOMEM;

	gpio_dev->gpiod = devm_gpiod_get(dev, NULL, GPIOD_IN);
	if (IS_ERR(gpio_dev->gpiod)) {
		rc = PTR_ERR(gpio_dev->gpiod);
		/* Just try again if this happens */
		if (rc != -EPROBE_DEFER)
			dev_err(dev, "error getting gpio (%d)\n", rc);
		return rc;
	}
	gpio_dev->irq = gpiod_to_irq(gpio_dev->gpiod);
	if (gpio_dev->irq < 0)
		return gpio_dev->irq;

	rcdev = devm_rc_allocate_device(dev, RC_DRIVER_IR_RAW);
	if (!rcdev)
		return -ENOMEM;
=======
	struct gpio_rc_dev *gpio_dev;
	struct rc_dev *rcdev;
	const struct gpio_ir_recv_platform_data *pdata =
					pdev->dev.platform_data;
	int rc;

	if (pdev->dev.of_node) {
		struct gpio_ir_recv_platform_data *dtpdata =
			devm_kzalloc(&pdev->dev, sizeof(*dtpdata), GFP_KERNEL);
		if (!dtpdata)
			return -ENOMEM;
		rc = gpio_ir_recv_get_devtree_pdata(&pdev->dev, dtpdata);
		if (rc)
			return rc;
		pdata = dtpdata;
	}

	if (!pdata)
		return -EINVAL;

	if (pdata->gpio_nr < 0)
		return -EINVAL;

	gpio_dev = kzalloc(sizeof(struct gpio_rc_dev), GFP_KERNEL);
	if (!gpio_dev)
		return -ENOMEM;

	rcdev = rc_allocate_device(RC_DRIVER_IR_RAW);
	if (!rcdev) {
		rc = -ENOMEM;
		goto err_allocate_device;
	}
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	rcdev->priv = gpio_dev;
	rcdev->device_name = GPIO_IR_DEVICE_NAME;
	rcdev->input_phys = GPIO_IR_DEVICE_NAME "/input0";
	rcdev->input_id.bustype = BUS_HOST;
	rcdev->input_id.vendor = 0x0001;
	rcdev->input_id.product = 0x0001;
	rcdev->input_id.version = 0x0100;
<<<<<<< HEAD
	rcdev->dev.parent = dev;
	rcdev->driver_name = KBUILD_MODNAME;
	rcdev->min_timeout = 1;
	rcdev->timeout = IR_DEFAULT_TIMEOUT;
	rcdev->max_timeout = 10 * IR_DEFAULT_TIMEOUT;
	rcdev->allowed_protocols = RC_PROTO_BIT_ALL_IR_DECODER;
	rcdev->map_name = of_get_property(np, "linux,rc-map-name", NULL);
	if (!rcdev->map_name)
		rcdev->map_name = RC_MAP_EMPTY;

	gpio_dev->rcdev = rcdev;

	rc = devm_rc_register_device(dev, rcdev);
	if (rc < 0) {
		dev_err(dev, "failed to register rc device (%d)\n", rc);
		return rc;
=======
	rcdev->dev.parent = &pdev->dev;
	rcdev->driver_name = GPIO_IR_DRIVER_NAME;
	rcdev->min_timeout = 1;
	rcdev->timeout = IR_DEFAULT_TIMEOUT;
	rcdev->max_timeout = 10 * IR_DEFAULT_TIMEOUT;
	if (pdata->allowed_protos)
		rcdev->allowed_protocols = pdata->allowed_protos;
	else
		rcdev->allowed_protocols = RC_PROTO_BIT_ALL_IR_DECODER;
	rcdev->map_name = pdata->map_name ?: RC_MAP_EMPTY;

	gpio_dev->rcdev = rcdev;
	gpio_dev->gpio_nr = pdata->gpio_nr;
	gpio_dev->active_low = pdata->active_low;

	rc = gpio_request(pdata->gpio_nr, "gpio-ir-recv");
	if (rc < 0)
		goto err_gpio_request;
	rc  = gpio_direction_input(pdata->gpio_nr);
	if (rc < 0)
		goto err_gpio_direction_input;

	rc = rc_register_device(rcdev);
	if (rc < 0) {
		dev_err(&pdev->dev, "failed to register rc device\n");
		goto err_register_rc_device;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	}

	platform_set_drvdata(pdev, gpio_dev);

<<<<<<< HEAD
	return devm_request_irq(dev, gpio_dev->irq, gpio_ir_recv_irq,
				IRQF_TRIGGER_FALLING | IRQF_TRIGGER_RISING,
				"gpio-ir-recv-irq", gpio_dev);
=======
	rc = request_any_context_irq(gpio_to_irq(pdata->gpio_nr),
				gpio_ir_recv_irq,
			IRQF_TRIGGER_FALLING | IRQF_TRIGGER_RISING,
					"gpio-ir-recv-irq", gpio_dev);
	if (rc < 0)
		goto err_request_irq;

	return 0;

err_request_irq:
	rc_unregister_device(rcdev);
	rcdev = NULL;
err_register_rc_device:
err_gpio_direction_input:
	gpio_free(pdata->gpio_nr);
err_gpio_request:
	rc_free_device(rcdev);
err_allocate_device:
	kfree(gpio_dev);
	return rc;
}

static int gpio_ir_recv_remove(struct platform_device *pdev)
{
	struct gpio_rc_dev *gpio_dev = platform_get_drvdata(pdev);

	free_irq(gpio_to_irq(gpio_dev->gpio_nr), gpio_dev);
	rc_unregister_device(gpio_dev->rcdev);
	gpio_free(gpio_dev->gpio_nr);
	kfree(gpio_dev);
	return 0;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
}

#ifdef CONFIG_PM
static int gpio_ir_recv_suspend(struct device *dev)
{
<<<<<<< HEAD
	struct gpio_rc_dev *gpio_dev = dev_get_drvdata(dev);

	if (device_may_wakeup(dev))
		enable_irq_wake(gpio_dev->irq);
	else
		disable_irq(gpio_dev->irq);
=======
	struct platform_device *pdev = to_platform_device(dev);
	struct gpio_rc_dev *gpio_dev = platform_get_drvdata(pdev);

	if (device_may_wakeup(dev))
		enable_irq_wake(gpio_to_irq(gpio_dev->gpio_nr));
	else
		disable_irq(gpio_to_irq(gpio_dev->gpio_nr));
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	return 0;
}

static int gpio_ir_recv_resume(struct device *dev)
{
<<<<<<< HEAD
	struct gpio_rc_dev *gpio_dev = dev_get_drvdata(dev);

	if (device_may_wakeup(dev))
		disable_irq_wake(gpio_dev->irq);
	else
		enable_irq(gpio_dev->irq);
=======
	struct platform_device *pdev = to_platform_device(dev);
	struct gpio_rc_dev *gpio_dev = platform_get_drvdata(pdev);

	if (device_may_wakeup(dev))
		disable_irq_wake(gpio_to_irq(gpio_dev->gpio_nr));
	else
		enable_irq(gpio_to_irq(gpio_dev->gpio_nr));
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	return 0;
}

static const struct dev_pm_ops gpio_ir_recv_pm_ops = {
	.suspend        = gpio_ir_recv_suspend,
	.resume         = gpio_ir_recv_resume,
};
#endif

<<<<<<< HEAD
static const struct of_device_id gpio_ir_recv_of_match[] = {
	{ .compatible = "gpio-ir-receiver", },
	{ },
};
MODULE_DEVICE_TABLE(of, gpio_ir_recv_of_match);

static struct platform_driver gpio_ir_recv_driver = {
	.probe  = gpio_ir_recv_probe,
	.driver = {
		.name   = KBUILD_MODNAME,
=======
static struct platform_driver gpio_ir_recv_driver = {
	.probe  = gpio_ir_recv_probe,
	.remove = gpio_ir_recv_remove,
	.driver = {
		.name   = GPIO_IR_DRIVER_NAME,
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
		.of_match_table = of_match_ptr(gpio_ir_recv_of_match),
#ifdef CONFIG_PM
		.pm	= &gpio_ir_recv_pm_ops,
#endif
	},
};
module_platform_driver(gpio_ir_recv_driver);

MODULE_DESCRIPTION("GPIO IR Receiver driver");
MODULE_LICENSE("GPL v2");
