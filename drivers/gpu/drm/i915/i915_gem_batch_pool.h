/*
<<<<<<< HEAD
 * SPDX-License-Identifier: MIT
 *
 * Copyright © 2014-2018 Intel Corporation
=======
 * Copyright © 2014 Intel Corporation
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 *
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
 */

#ifndef I915_GEM_BATCH_POOL_H
#define I915_GEM_BATCH_POOL_H

<<<<<<< HEAD
#include <linux/types.h>
=======
#include "i915_drv.h"
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

struct intel_engine_cs;

struct i915_gem_batch_pool {
	struct intel_engine_cs *engine;
	struct list_head cache_list[4];
};

<<<<<<< HEAD
void i915_gem_batch_pool_init(struct i915_gem_batch_pool *pool,
			      struct intel_engine_cs *engine);
=======
/* i915_gem_batch_pool.c */
void i915_gem_batch_pool_init(struct intel_engine_cs *engine,
			      struct i915_gem_batch_pool *pool);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
void i915_gem_batch_pool_fini(struct i915_gem_batch_pool *pool);
struct drm_i915_gem_object*
i915_gem_batch_pool_get(struct i915_gem_batch_pool *pool, size_t size);

#endif /* I915_GEM_BATCH_POOL_H */
