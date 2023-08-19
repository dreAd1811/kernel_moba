<<<<<<< HEAD
// SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (c) 2011,2013,2015,2019 The Linux Foundation. All rights reserved.
=======
/* Copyright (c) 2011, 2013, 2015, 2019 The Linux Foundation. All rights reserved.
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

#include <linux/module.h>

<<<<<<< HEAD
=======
#include "kgsl.h"
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
#include "kgsl_device.h"

/* Instantiate tracepoints */
#define CREATE_TRACE_POINTS
#include "kgsl_trace.h"
<<<<<<< HEAD
=======
#include "kgsl_trace_power.h"
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

EXPORT_TRACEPOINT_SYMBOL(kgsl_regwrite);
EXPORT_TRACEPOINT_SYMBOL(kgsl_issueibcmds);
EXPORT_TRACEPOINT_SYMBOL(kgsl_user_pwrlevel_constraint);
EXPORT_TRACEPOINT_SYMBOL(kgsl_constraint);
<<<<<<< HEAD
=======

EXPORT_TRACEPOINT_SYMBOL(gpu_frequency);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
