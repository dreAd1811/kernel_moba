/**
 * extcon-qcom-spmi-misc.c - Qualcomm USB extcon driver to support USB ID
<<<<<<< HEAD
 *				detection based on extcon-usb-gpio.c.
=======
 *			and VBUS detection based on extcon-usb-gpio.c.
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
 *
 * Copyright (C) 2016 Linaro, Ltd.
 * Stephen Boyd <stephen.boyd@linaro.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

<<<<<<< HEAD
#include <linux/extcon-provider.h>
=======
#include <linux/extcon.h>
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/kernel.h>
#include <linux/module.h>
<<<<<<< HEAD
#include <linux/mod_devicetable.h>
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
#include <linux/platform_device.h>
#include <linux/slab.h>
#include <linux/workqueue.h>

#define USB_ID_DEBOUNCE_MS	5	/* ms */

struct qcom_usb_extcon_info {
	struct extcon_dev *edev;
<<<<<<< HEAD
	int irq;
=======
	int id_irq;
	int vbus_irq;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	struct delayed_work wq_detcable;
	unsigned long debounce_jiffies;
};

static const unsigned int qcom_usb_extcon_cable[] = {
<<<<<<< HEAD
=======
	EXTCON_USB,
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	EXTCON_USB_HOST,
	EXTCON_NONE,
};

static void qcom_usb_extcon_detect_cable(struct work_struct *work)
{
<<<<<<< HEAD
	bool id;
	int ret;
=======
	bool state = 0;
	int ret;
	union extcon_property_value val;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	struct qcom_usb_extcon_info *info = container_of(to_delayed_work(work),
						    struct qcom_usb_extcon_info,
						    wq_detcable);

<<<<<<< HEAD
	/* check ID and update cable state */
	ret = irq_get_irqchip_state(info->irq, IRQCHIP_STATE_LINE_LEVEL, &id);
	if (ret)
		return;

	extcon_set_state_sync(info->edev, EXTCON_USB_HOST, !id);
=======
	if (info->id_irq > 0) {
		/* check ID and update cable state */
		ret = irq_get_irqchip_state(info->id_irq,
				IRQCHIP_STATE_LINE_LEVEL, &state);
		if (ret)
			return;

		if (!state) {
			val.intval = true;
			extcon_set_property(info->edev, EXTCON_USB_HOST,
						EXTCON_PROP_USB_SS, val);
		}
		extcon_set_state_sync(info->edev, EXTCON_USB_HOST, !state);
	}

	if (info->vbus_irq > 0) {
		/* check VBUS and update cable state */
		ret = irq_get_irqchip_state(info->vbus_irq,
				IRQCHIP_STATE_LINE_LEVEL, &state);
		if (ret)
			return;

		if (state) {
			val.intval = true;
			extcon_set_property(info->edev, EXTCON_USB,
						EXTCON_PROP_USB_SS, val);
		}
		extcon_set_state_sync(info->edev, EXTCON_USB, state);
	}
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
}

static irqreturn_t qcom_usb_irq_handler(int irq, void *dev_id)
{
	struct qcom_usb_extcon_info *info = dev_id;

	queue_delayed_work(system_power_efficient_wq, &info->wq_detcable,
			   info->debounce_jiffies);

	return IRQ_HANDLED;
}

static int qcom_usb_extcon_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct qcom_usb_extcon_info *info;
	int ret;

	info = devm_kzalloc(dev, sizeof(*info), GFP_KERNEL);
	if (!info)
		return -ENOMEM;

	info->edev = devm_extcon_dev_allocate(dev, qcom_usb_extcon_cable);
	if (IS_ERR(info->edev)) {
		dev_err(dev, "failed to allocate extcon device\n");
		return -ENOMEM;
	}

	ret = devm_extcon_dev_register(dev, info->edev);
	if (ret < 0) {
		dev_err(dev, "failed to register extcon device\n");
		return ret;
	}

<<<<<<< HEAD
	info->debounce_jiffies = msecs_to_jiffies(USB_ID_DEBOUNCE_MS);
	INIT_DELAYED_WORK(&info->wq_detcable, qcom_usb_extcon_detect_cable);

	info->irq = platform_get_irq_byname(pdev, "usb_id");
	if (info->irq < 0)
		return info->irq;

	ret = devm_request_threaded_irq(dev, info->irq, NULL,
=======
	ret = extcon_set_property_capability(info->edev,
			EXTCON_USB, EXTCON_PROP_USB_SS);
	ret |= extcon_set_property_capability(info->edev,
			EXTCON_USB_HOST, EXTCON_PROP_USB_SS);
	if (ret) {
		dev_err(dev, "failed to register extcon props rc=%d\n",
						ret);
		return ret;
	}

	info->debounce_jiffies = msecs_to_jiffies(USB_ID_DEBOUNCE_MS);
	INIT_DELAYED_WORK(&info->wq_detcable, qcom_usb_extcon_detect_cable);

	info->id_irq = platform_get_irq_byname(pdev, "usb_id");
	if (info->id_irq > 0) {
		ret = devm_request_threaded_irq(dev, info->id_irq, NULL,
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
					qcom_usb_irq_handler,
					IRQF_TRIGGER_RISING |
					IRQF_TRIGGER_FALLING | IRQF_ONESHOT,
					pdev->name, info);
<<<<<<< HEAD
	if (ret < 0) {
		dev_err(dev, "failed to request handler for ID IRQ\n");
		return ret;
=======
		if (ret < 0) {
			dev_err(dev, "failed to request handler for ID IRQ\n");
			return ret;
		}
	}

	info->vbus_irq = platform_get_irq_byname(pdev, "usb_vbus");
	if (info->vbus_irq > 0) {
		ret = devm_request_threaded_irq(dev, info->vbus_irq, NULL,
					qcom_usb_irq_handler,
					IRQF_TRIGGER_RISING |
					IRQF_TRIGGER_FALLING | IRQF_ONESHOT,
					pdev->name, info);
		if (ret < 0) {
			dev_err(dev, "failed to request handler for VBUS IRQ\n");
			return ret;
		}
	}

	if (info->id_irq < 0 && info->vbus_irq < 0) {
		dev_err(dev, "ID and VBUS IRQ not found\n");
		return -EINVAL;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	}

	platform_set_drvdata(pdev, info);
	device_init_wakeup(dev, 1);

	/* Perform initial detection */
	qcom_usb_extcon_detect_cable(&info->wq_detcable.work);

	return 0;
}

static int qcom_usb_extcon_remove(struct platform_device *pdev)
{
	struct qcom_usb_extcon_info *info = platform_get_drvdata(pdev);

	cancel_delayed_work_sync(&info->wq_detcable);

	return 0;
}

#ifdef CONFIG_PM_SLEEP
static int qcom_usb_extcon_suspend(struct device *dev)
{
	struct qcom_usb_extcon_info *info = dev_get_drvdata(dev);
	int ret = 0;

<<<<<<< HEAD
	if (device_may_wakeup(dev))
		ret = enable_irq_wake(info->irq);
=======
	if (device_may_wakeup(dev)) {
		if (info->id_irq > 0)
			ret = enable_irq_wake(info->id_irq);
		if (info->vbus_irq > 0)
			ret = enable_irq_wake(info->vbus_irq);
	}
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	return ret;
}

static int qcom_usb_extcon_resume(struct device *dev)
{
	struct qcom_usb_extcon_info *info = dev_get_drvdata(dev);
	int ret = 0;

<<<<<<< HEAD
	if (device_may_wakeup(dev))
		ret = disable_irq_wake(info->irq);
=======
	if (device_may_wakeup(dev)) {
		if (info->id_irq > 0)
			ret = disable_irq_wake(info->id_irq);
		if (info->vbus_irq > 0)
			ret = disable_irq_wake(info->vbus_irq);
	}
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	return ret;
}
#endif

static SIMPLE_DEV_PM_OPS(qcom_usb_extcon_pm_ops,
			 qcom_usb_extcon_suspend, qcom_usb_extcon_resume);

static const struct of_device_id qcom_usb_extcon_dt_match[] = {
	{ .compatible = "qcom,pm8941-misc", },
<<<<<<< HEAD
=======
	{ .compatible = "qcom,pmd-vbus-det", },
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	{ }
};
MODULE_DEVICE_TABLE(of, qcom_usb_extcon_dt_match);

static struct platform_driver qcom_usb_extcon_driver = {
	.probe		= qcom_usb_extcon_probe,
	.remove		= qcom_usb_extcon_remove,
	.driver		= {
		.name	= "extcon-pm8941-misc",
		.pm	= &qcom_usb_extcon_pm_ops,
		.of_match_table = qcom_usb_extcon_dt_match,
	},
};
module_platform_driver(qcom_usb_extcon_driver);

MODULE_DESCRIPTION("QCOM USB ID extcon driver");
MODULE_AUTHOR("Stephen Boyd <stephen.boyd@linaro.org>");
MODULE_LICENSE("GPL v2");
