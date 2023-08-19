/*
 * DRM driver for Multi-Inno MI0283QT panels
 *
 * Copyright 2016 Noralf Trønnes
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

<<<<<<< HEAD
#include <linux/backlight.h>
=======
#include <drm/tinydrm/ili9341.h>
#include <drm/tinydrm/mipi-dbi.h>
#include <drm/tinydrm/tinydrm-helpers.h>
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
#include <linux/delay.h>
#include <linux/gpio/consumer.h>
#include <linux/module.h>
#include <linux/property.h>
#include <linux/regulator/consumer.h>
#include <linux/spi/spi.h>
<<<<<<< HEAD

#include <drm/drm_fb_helper.h>
#include <drm/drm_modeset_helper.h>
#include <drm/drm_gem_framebuffer_helper.h>
#include <drm/tinydrm/mipi-dbi.h>
#include <drm/tinydrm/tinydrm-helpers.h>
#include <video/mipi_display.h>

#define ILI9341_FRMCTR1		0xb1
#define ILI9341_DISCTRL		0xb6
#define ILI9341_ETMOD		0xb7

#define ILI9341_PWCTRL1		0xc0
#define ILI9341_PWCTRL2		0xc1
#define ILI9341_VMCTRL1		0xc5
#define ILI9341_VMCTRL2		0xc7
#define ILI9341_PWCTRLA		0xcb
#define ILI9341_PWCTRLB		0xcf

#define ILI9341_PGAMCTRL	0xe0
#define ILI9341_NGAMCTRL	0xe1
#define ILI9341_DTCTRLA		0xe8
#define ILI9341_DTCTRLB		0xea
#define ILI9341_PWRSEQ		0xed

#define ILI9341_EN3GAM		0xf2
#define ILI9341_PUMPCTRL	0xf7

#define ILI9341_MADCTL_BGR	BIT(3)
#define ILI9341_MADCTL_MV	BIT(5)
#define ILI9341_MADCTL_MX	BIT(6)
#define ILI9341_MADCTL_MY	BIT(7)

static void mi0283qt_enable(struct drm_simple_display_pipe *pipe,
			    struct drm_crtc_state *crtc_state,
			    struct drm_plane_state *plane_state)
{
	struct tinydrm_device *tdev = pipe_to_tinydrm(pipe);
	struct mipi_dbi *mipi = mipi_dbi_from_tinydrm(tdev);
=======
#include <video/mipi_display.h>

static int mi0283qt_init(struct mipi_dbi *mipi)
{
	struct tinydrm_device *tdev = &mipi->tinydrm;
	struct device *dev = tdev->drm->dev;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	u8 addr_mode;
	int ret;

	DRM_DEBUG_KMS("\n");

<<<<<<< HEAD
	ret = mipi_dbi_poweron_conditional_reset(mipi);
	if (ret < 0)
		return;
	if (ret == 1)
		goto out_enable;
=======
	ret = regulator_enable(mipi->regulator);
	if (ret) {
		dev_err(dev, "Failed to enable regulator %d\n", ret);
		return ret;
	}

	/* Avoid flicker by skipping setup if the bootloader has done it */
	if (mipi_dbi_display_is_on(mipi))
		return 0;

	mipi_dbi_hw_reset(mipi);
	ret = mipi_dbi_command(mipi, MIPI_DCS_SOFT_RESET);
	if (ret) {
		dev_err(dev, "Error sending command %d\n", ret);
		regulator_disable(mipi->regulator);
		return ret;
	}

	msleep(20);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	mipi_dbi_command(mipi, MIPI_DCS_SET_DISPLAY_OFF);

	mipi_dbi_command(mipi, ILI9341_PWCTRLB, 0x00, 0x83, 0x30);
	mipi_dbi_command(mipi, ILI9341_PWRSEQ, 0x64, 0x03, 0x12, 0x81);
	mipi_dbi_command(mipi, ILI9341_DTCTRLA, 0x85, 0x01, 0x79);
	mipi_dbi_command(mipi, ILI9341_PWCTRLA, 0x39, 0x2c, 0x00, 0x34, 0x02);
	mipi_dbi_command(mipi, ILI9341_PUMPCTRL, 0x20);
	mipi_dbi_command(mipi, ILI9341_DTCTRLB, 0x00, 0x00);

	/* Power Control */
	mipi_dbi_command(mipi, ILI9341_PWCTRL1, 0x26);
	mipi_dbi_command(mipi, ILI9341_PWCTRL2, 0x11);
	/* VCOM */
	mipi_dbi_command(mipi, ILI9341_VMCTRL1, 0x35, 0x3e);
	mipi_dbi_command(mipi, ILI9341_VMCTRL2, 0xbe);

	/* Memory Access Control */
<<<<<<< HEAD
	mipi_dbi_command(mipi, MIPI_DCS_SET_PIXEL_FORMAT, MIPI_DCS_PIXEL_FMT_16BIT);
=======
	mipi_dbi_command(mipi, MIPI_DCS_SET_PIXEL_FORMAT, 0x55);

	switch (mipi->rotation) {
	default:
		addr_mode = ILI9341_MADCTL_MV | ILI9341_MADCTL_MY |
			    ILI9341_MADCTL_MX;
		break;
	case 90:
		addr_mode = ILI9341_MADCTL_MY;
		break;
	case 180:
		addr_mode = ILI9341_MADCTL_MV;
		break;
	case 270:
		addr_mode = ILI9341_MADCTL_MX;
		break;
	}
	addr_mode |= ILI9341_MADCTL_BGR;
	mipi_dbi_command(mipi, MIPI_DCS_SET_ADDRESS_MODE, addr_mode);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	/* Frame Rate */
	mipi_dbi_command(mipi, ILI9341_FRMCTR1, 0x00, 0x1b);

	/* Gamma */
	mipi_dbi_command(mipi, ILI9341_EN3GAM, 0x08);
	mipi_dbi_command(mipi, MIPI_DCS_SET_GAMMA_CURVE, 0x01);
	mipi_dbi_command(mipi, ILI9341_PGAMCTRL,
		       0x1f, 0x1a, 0x18, 0x0a, 0x0f, 0x06, 0x45, 0x87,
		       0x32, 0x0a, 0x07, 0x02, 0x07, 0x05, 0x00);
	mipi_dbi_command(mipi, ILI9341_NGAMCTRL,
		       0x00, 0x25, 0x27, 0x05, 0x10, 0x09, 0x3a, 0x78,
		       0x4d, 0x05, 0x18, 0x0d, 0x38, 0x3a, 0x1f);

	/* DDRAM */
	mipi_dbi_command(mipi, ILI9341_ETMOD, 0x07);

	/* Display */
	mipi_dbi_command(mipi, ILI9341_DISCTRL, 0x0a, 0x82, 0x27, 0x00);
	mipi_dbi_command(mipi, MIPI_DCS_EXIT_SLEEP_MODE);
	msleep(100);

	mipi_dbi_command(mipi, MIPI_DCS_SET_DISPLAY_ON);
	msleep(100);

<<<<<<< HEAD
out_enable:
	/* The PiTFT (ili9340) has a hardware reset circuit that
	 * resets only on power-on and not on each reboot through
	 * a gpio like the rpi-display does.
	 * As a result, we need to always apply the rotation value
	 * regardless of the display "on/off" state.
	 */
	switch (mipi->rotation) {
	default:
		addr_mode = ILI9341_MADCTL_MV | ILI9341_MADCTL_MY |
			    ILI9341_MADCTL_MX;
		break;
	case 90:
		addr_mode = ILI9341_MADCTL_MY;
		break;
	case 180:
		addr_mode = ILI9341_MADCTL_MV;
		break;
	case 270:
		addr_mode = ILI9341_MADCTL_MX;
		break;
	}
	addr_mode |= ILI9341_MADCTL_BGR;
	mipi_dbi_command(mipi, MIPI_DCS_SET_ADDRESS_MODE, addr_mode);
	mipi_dbi_enable_flush(mipi, crtc_state, plane_state);
}

static const struct drm_simple_display_pipe_funcs mi0283qt_pipe_funcs = {
	.enable = mi0283qt_enable,
	.disable = mipi_dbi_pipe_disable,
	.update = tinydrm_display_pipe_update,
	.prepare_fb = drm_gem_fb_simple_display_pipe_prepare_fb,
=======
	return 0;
}

static void mi0283qt_fini(void *data)
{
	struct mipi_dbi *mipi = data;

	DRM_DEBUG_KMS("\n");
	regulator_disable(mipi->regulator);
}

static const struct drm_simple_display_pipe_funcs mi0283qt_pipe_funcs = {
	.enable = mipi_dbi_pipe_enable,
	.disable = mipi_dbi_pipe_disable,
	.update = tinydrm_display_pipe_update,
	.prepare_fb = tinydrm_display_pipe_prepare_fb,
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
};

static const struct drm_display_mode mi0283qt_mode = {
	TINYDRM_MODE(320, 240, 58, 43),
};

DEFINE_DRM_GEM_CMA_FOPS(mi0283qt_fops);

static struct drm_driver mi0283qt_driver = {
	.driver_features	= DRIVER_GEM | DRIVER_MODESET | DRIVER_PRIME |
				  DRIVER_ATOMIC,
	.fops			= &mi0283qt_fops,
	TINYDRM_GEM_DRIVER_OPS,
<<<<<<< HEAD
=======
	.lastclose		= tinydrm_lastclose,
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	.debugfs_init		= mipi_dbi_debugfs_init,
	.name			= "mi0283qt",
	.desc			= "Multi-Inno MI0283QT",
	.date			= "20160614",
	.major			= 1,
	.minor			= 0,
};

static const struct of_device_id mi0283qt_of_match[] = {
	{ .compatible = "multi-inno,mi0283qt" },
	{},
};
MODULE_DEVICE_TABLE(of, mi0283qt_of_match);

static const struct spi_device_id mi0283qt_id[] = {
	{ "mi0283qt", 0 },
	{ },
};
MODULE_DEVICE_TABLE(spi, mi0283qt_id);

static int mi0283qt_probe(struct spi_device *spi)
{
	struct device *dev = &spi->dev;
<<<<<<< HEAD
=======
	struct tinydrm_device *tdev;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	struct mipi_dbi *mipi;
	struct gpio_desc *dc;
	u32 rotation = 0;
	int ret;

	mipi = devm_kzalloc(dev, sizeof(*mipi), GFP_KERNEL);
	if (!mipi)
		return -ENOMEM;

	mipi->reset = devm_gpiod_get_optional(dev, "reset", GPIOD_OUT_HIGH);
	if (IS_ERR(mipi->reset)) {
<<<<<<< HEAD
		DRM_DEV_ERROR(dev, "Failed to get gpio 'reset'\n");
=======
		dev_err(dev, "Failed to get gpio 'reset'\n");
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
		return PTR_ERR(mipi->reset);
	}

	dc = devm_gpiod_get_optional(dev, "dc", GPIOD_OUT_LOW);
	if (IS_ERR(dc)) {
<<<<<<< HEAD
		DRM_DEV_ERROR(dev, "Failed to get gpio 'dc'\n");
=======
		dev_err(dev, "Failed to get gpio 'dc'\n");
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
		return PTR_ERR(dc);
	}

	mipi->regulator = devm_regulator_get(dev, "power");
	if (IS_ERR(mipi->regulator))
		return PTR_ERR(mipi->regulator);

<<<<<<< HEAD
	mipi->backlight = devm_of_find_backlight(dev);
=======
	mipi->backlight = tinydrm_of_find_backlight(dev);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	if (IS_ERR(mipi->backlight))
		return PTR_ERR(mipi->backlight);

	device_property_read_u32(dev, "rotation", &rotation);

	ret = mipi_dbi_spi_init(spi, mipi, dc);
	if (ret)
		return ret;

	ret = mipi_dbi_init(&spi->dev, mipi, &mi0283qt_pipe_funcs,
			    &mi0283qt_driver, &mi0283qt_mode, rotation);
	if (ret)
		return ret;

<<<<<<< HEAD
	spi_set_drvdata(spi, mipi);

	return devm_tinydrm_register(&mipi->tinydrm);
=======
	ret = mi0283qt_init(mipi);
	if (ret)
		return ret;

	/* use devres to fini after drm unregister (drv->remove is before) */
	ret = devm_add_action(dev, mi0283qt_fini, mipi);
	if (ret) {
		mi0283qt_fini(mipi);
		return ret;
	}

	tdev = &mipi->tinydrm;

	ret = devm_tinydrm_register(tdev);
	if (ret)
		return ret;

	spi_set_drvdata(spi, mipi);

	DRM_DEBUG_DRIVER("Initialized %s:%s @%uMHz on minor %d\n",
			 tdev->drm->driver->name, dev_name(dev),
			 spi->max_speed_hz / 1000000,
			 tdev->drm->primary->index);

	return 0;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
}

static void mi0283qt_shutdown(struct spi_device *spi)
{
	struct mipi_dbi *mipi = spi_get_drvdata(spi);

	tinydrm_shutdown(&mipi->tinydrm);
}

static int __maybe_unused mi0283qt_pm_suspend(struct device *dev)
{
	struct mipi_dbi *mipi = dev_get_drvdata(dev);
<<<<<<< HEAD

	return drm_mode_config_helper_suspend(mipi->tinydrm.drm);
=======
	int ret;

	ret = tinydrm_suspend(&mipi->tinydrm);
	if (ret)
		return ret;

	mi0283qt_fini(mipi);

	return 0;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
}

static int __maybe_unused mi0283qt_pm_resume(struct device *dev)
{
	struct mipi_dbi *mipi = dev_get_drvdata(dev);
<<<<<<< HEAD

	drm_mode_config_helper_resume(mipi->tinydrm.drm);

	return 0;
=======
	int ret;

	ret = mi0283qt_init(mipi);
	if (ret)
		return ret;

	return tinydrm_resume(&mipi->tinydrm);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
}

static const struct dev_pm_ops mi0283qt_pm_ops = {
	SET_SYSTEM_SLEEP_PM_OPS(mi0283qt_pm_suspend, mi0283qt_pm_resume)
};

static struct spi_driver mi0283qt_spi_driver = {
	.driver = {
		.name = "mi0283qt",
		.owner = THIS_MODULE,
		.of_match_table = mi0283qt_of_match,
		.pm = &mi0283qt_pm_ops,
	},
	.id_table = mi0283qt_id,
	.probe = mi0283qt_probe,
	.shutdown = mi0283qt_shutdown,
};
module_spi_driver(mi0283qt_spi_driver);

MODULE_DESCRIPTION("Multi-Inno MI0283QT DRM driver");
MODULE_AUTHOR("Noralf Trønnes");
MODULE_LICENSE("GPL");
