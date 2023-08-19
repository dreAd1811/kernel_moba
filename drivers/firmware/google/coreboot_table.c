/*
 * coreboot_table.c
 *
 * Module providing coreboot table access.
 *
 * Copyright 2017 Google Inc.
<<<<<<< HEAD
 * Copyright 2017 Samuel Holland <samuel@sholland.org>
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License v2.0 as published by
 * the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

<<<<<<< HEAD
#include <linux/device.h>
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
#include <linux/err.h>
#include <linux/init.h>
#include <linux/io.h>
#include <linux/kernel.h>
#include <linux/module.h>
<<<<<<< HEAD
#include <linux/slab.h>

#include "coreboot_table.h"

#define CB_DEV(d) container_of(d, struct coreboot_device, dev)
#define CB_DRV(d) container_of(d, struct coreboot_driver, drv)

static struct coreboot_table_header __iomem *ptr_header;

static int coreboot_bus_match(struct device *dev, struct device_driver *drv)
{
	struct coreboot_device *device = CB_DEV(dev);
	struct coreboot_driver *driver = CB_DRV(drv);

	return device->entry.tag == driver->tag;
}

static int coreboot_bus_probe(struct device *dev)
{
	int ret = -ENODEV;
	struct coreboot_device *device = CB_DEV(dev);
	struct coreboot_driver *driver = CB_DRV(dev->driver);

	if (driver->probe)
		ret = driver->probe(device);

	return ret;
}

static int coreboot_bus_remove(struct device *dev)
{
	int ret = 0;
	struct coreboot_device *device = CB_DEV(dev);
	struct coreboot_driver *driver = CB_DRV(dev->driver);

	if (driver->remove)
		ret = driver->remove(device);

	return ret;
}

static struct bus_type coreboot_bus_type = {
	.name		= "coreboot",
	.match		= coreboot_bus_match,
	.probe		= coreboot_bus_probe,
	.remove		= coreboot_bus_remove,
};

static int __init coreboot_bus_init(void)
{
	return bus_register(&coreboot_bus_type);
}
module_init(coreboot_bus_init);

static void coreboot_device_release(struct device *dev)
{
	struct coreboot_device *device = CB_DEV(dev);

	kfree(device);
}

int coreboot_driver_register(struct coreboot_driver *driver)
{
	driver->drv.bus = &coreboot_bus_type;

	return driver_register(&driver->drv);
}
EXPORT_SYMBOL(coreboot_driver_register);

void coreboot_driver_unregister(struct coreboot_driver *driver)
{
	driver_unregister(&driver->drv);
}
EXPORT_SYMBOL(coreboot_driver_unregister);

int coreboot_table_init(struct device *dev, void __iomem *ptr)
{
	int i, ret;
	void *ptr_entry;
	struct coreboot_device *device;
	struct coreboot_table_entry entry;
	struct coreboot_table_header header;

	ptr_header = ptr;
=======

#include "coreboot_table.h"

struct coreboot_table_entry {
	u32 tag;
	u32 size;
};

static struct coreboot_table_header __iomem *ptr_header;

/*
 * This function parses the coreboot table for an entry that contains the base
 * address of the given entry tag. The coreboot table consists of a header
 * directly followed by a number of small, variable-sized entries, which each
 * contain an identifying tag and their length as the first two fields.
 */
int coreboot_table_find(int tag, void *data, size_t data_size)
{
	struct coreboot_table_header header;
	struct coreboot_table_entry entry;
	void *ptr_entry;
	int i;

	if (!ptr_header)
		return -EPROBE_DEFER;

>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	memcpy_fromio(&header, ptr_header, sizeof(header));

	if (strncmp(header.signature, "LBIO", sizeof(header.signature))) {
		pr_warn("coreboot_table: coreboot table missing or corrupt!\n");
<<<<<<< HEAD
		ret = -ENODEV;
		goto out;
	}

	ptr_entry = (void *)ptr_header + header.header_bytes;
	for (i = 0; i < header.table_entries; i++) {
		memcpy_fromio(&entry, ptr_entry, sizeof(entry));

		device = kzalloc(sizeof(struct device) + entry.size, GFP_KERNEL);
		if (!device) {
			ret = -ENOMEM;
			break;
		}

		dev_set_name(&device->dev, "coreboot%d", i);
		device->dev.parent = dev;
		device->dev.bus = &coreboot_bus_type;
		device->dev.release = coreboot_device_release;
		memcpy_fromio(&device->entry, ptr_entry, entry.size);

		ret = device_register(&device->dev);
		if (ret) {
			put_device(&device->dev);
			break;
=======
		return -ENODEV;
	}

	ptr_entry = (void *)ptr_header + header.header_bytes;

	for (i = 0; i < header.table_entries; i++) {
		memcpy_fromio(&entry, ptr_entry, sizeof(entry));
		if (entry.tag == tag) {
			if (data_size < entry.size)
				return -EINVAL;

			memcpy_fromio(data, ptr_entry, entry.size);

			return 0;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
		}

		ptr_entry += entry.size;
	}
<<<<<<< HEAD
out:
	iounmap(ptr);
	return ret;
=======

	return -ENOENT;
}
EXPORT_SYMBOL(coreboot_table_find);

int coreboot_table_init(void __iomem *ptr)
{
	ptr_header = ptr;

	return 0;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
}
EXPORT_SYMBOL(coreboot_table_init);

int coreboot_table_exit(void)
{
<<<<<<< HEAD
	if (ptr_header) {
		bus_unregister(&coreboot_bus_type);
		ptr_header = NULL;
	}
=======
	if (ptr_header)
		iounmap(ptr_header);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	return 0;
}
EXPORT_SYMBOL(coreboot_table_exit);

MODULE_AUTHOR("Google, Inc.");
MODULE_LICENSE("GPL");
