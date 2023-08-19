<<<<<<< HEAD
/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Copyright (c) 2013-2015, 2017, 2019 The Linux Foundation. All rights reserved.
=======
/* Copyright (c) 2013-2015, 2017, The Linux Foundation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
 */
#ifndef __ADRENO_COMPAT_H
#define __ADRENO_COMPAT_H

#ifdef CONFIG_COMPAT
<<<<<<< HEAD

struct kgsl_device;
struct kgsl_device_private;

int adreno_getproperty_compat(struct kgsl_device *device,
		struct kgsl_device_getproperty *param);
=======
#include <linux/compat.h>
#include "kgsl.h"
#include "kgsl_device.h"

int adreno_getproperty_compat(struct kgsl_device *device,
			unsigned int type,
			void __user *value,
			size_t sizebytes);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

int adreno_setproperty_compat(struct kgsl_device_private *dev_priv,
				unsigned int type,
				void __user *value,
				unsigned int sizebytes);

long adreno_compat_ioctl(struct kgsl_device_private *dev_priv,
			unsigned int cmd, unsigned long arg);

#else

static inline int adreno_getproperty_compat(struct kgsl_device *device,
<<<<<<< HEAD
		struct kgsl_device_getproperty *param)
=======
				unsigned int type,
				void __user *value, size_t sizebytes)
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
{
	return -EINVAL;
}

static inline int adreno_setproperty_compat(struct kgsl_device_private
				*dev_priv, unsigned int type,
				void __user *value, unsigned int sizebytes)
{
	return -EINVAL;
}

static inline long adreno_compat_ioctl(struct kgsl_device_private *dev_priv,
				unsigned int cmd, unsigned long arg)
{
	return -EINVAL;
}

#endif /* CONFIG_COMPAT */
#endif /* __ADRENO_COMPAT_H */
