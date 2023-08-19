/*
 * Copyright © 2016 Intel Corporation
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
 */

<<<<<<< HEAD
#include <drm/drm_print.h>

=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
#include "i915_drv.h"
#include "intel_ringbuffer.h"
#include "intel_lrc.h"

/* Haswell does have the CXT_SIZE register however it does not appear to be
 * valid. Now, docs explain in dwords what is in the context object. The full
 * size is 70720 bytes, however, the power context and execlist context will
 * never be saved (power context is stored elsewhere, and execlists don't work
 * on HSW) - so the final size, including the extra state required for the
 * Resource Streamer, is 66944 bytes, which rounds to 17 pages.
 */
#define HSW_CXT_TOTAL_SIZE		(17 * PAGE_SIZE)
<<<<<<< HEAD

#define DEFAULT_LR_CONTEXT_RENDER_SIZE	(22 * PAGE_SIZE)
#define GEN8_LR_CONTEXT_RENDER_SIZE	(20 * PAGE_SIZE)
#define GEN9_LR_CONTEXT_RENDER_SIZE	(22 * PAGE_SIZE)
#define GEN10_LR_CONTEXT_RENDER_SIZE	(18 * PAGE_SIZE)
#define GEN11_LR_CONTEXT_RENDER_SIZE	(14 * PAGE_SIZE)
=======
/* Same as Haswell, but 72064 bytes now. */
#define GEN8_CXT_TOTAL_SIZE		(18 * PAGE_SIZE)

#define GEN8_LR_CONTEXT_RENDER_SIZE	(20 * PAGE_SIZE)
#define GEN9_LR_CONTEXT_RENDER_SIZE	(22 * PAGE_SIZE)
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

#define GEN8_LR_CONTEXT_OTHER_SIZE	( 2 * PAGE_SIZE)

struct engine_class_info {
	const char *name;
	int (*init_legacy)(struct intel_engine_cs *engine);
	int (*init_execlists)(struct intel_engine_cs *engine);
<<<<<<< HEAD

	u8 uabi_class;
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
};

static const struct engine_class_info intel_engine_classes[] = {
	[RENDER_CLASS] = {
		.name = "rcs",
		.init_execlists = logical_render_ring_init,
		.init_legacy = intel_init_render_ring_buffer,
<<<<<<< HEAD
		.uabi_class = I915_ENGINE_CLASS_RENDER,
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	},
	[COPY_ENGINE_CLASS] = {
		.name = "bcs",
		.init_execlists = logical_xcs_ring_init,
		.init_legacy = intel_init_blt_ring_buffer,
<<<<<<< HEAD
		.uabi_class = I915_ENGINE_CLASS_COPY,
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	},
	[VIDEO_DECODE_CLASS] = {
		.name = "vcs",
		.init_execlists = logical_xcs_ring_init,
		.init_legacy = intel_init_bsd_ring_buffer,
<<<<<<< HEAD
		.uabi_class = I915_ENGINE_CLASS_VIDEO,
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	},
	[VIDEO_ENHANCEMENT_CLASS] = {
		.name = "vecs",
		.init_execlists = logical_xcs_ring_init,
		.init_legacy = intel_init_vebox_ring_buffer,
<<<<<<< HEAD
		.uabi_class = I915_ENGINE_CLASS_VIDEO_ENHANCE,
	},
};

#define MAX_MMIO_BASES 3
=======
	},
};

>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
struct engine_info {
	unsigned int hw_id;
	unsigned int uabi_id;
	u8 class;
	u8 instance;
<<<<<<< HEAD
	/* mmio bases table *must* be sorted in reverse gen order */
	struct engine_mmio_base {
		u32 gen : 8;
		u32 base : 24;
	} mmio_bases[MAX_MMIO_BASES];
=======
	u32 mmio_base;
	unsigned irq_shift;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
};

static const struct engine_info intel_engines[] = {
	[RCS] = {
		.hw_id = RCS_HW,
		.uabi_id = I915_EXEC_RENDER,
		.class = RENDER_CLASS,
		.instance = 0,
<<<<<<< HEAD
		.mmio_bases = {
			{ .gen = 1, .base = RENDER_RING_BASE }
		},
=======
		.mmio_base = RENDER_RING_BASE,
		.irq_shift = GEN8_RCS_IRQ_SHIFT,
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	},
	[BCS] = {
		.hw_id = BCS_HW,
		.uabi_id = I915_EXEC_BLT,
		.class = COPY_ENGINE_CLASS,
		.instance = 0,
<<<<<<< HEAD
		.mmio_bases = {
			{ .gen = 6, .base = BLT_RING_BASE }
		},
=======
		.mmio_base = BLT_RING_BASE,
		.irq_shift = GEN8_BCS_IRQ_SHIFT,
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	},
	[VCS] = {
		.hw_id = VCS_HW,
		.uabi_id = I915_EXEC_BSD,
		.class = VIDEO_DECODE_CLASS,
		.instance = 0,
<<<<<<< HEAD
		.mmio_bases = {
			{ .gen = 11, .base = GEN11_BSD_RING_BASE },
			{ .gen = 6, .base = GEN6_BSD_RING_BASE },
			{ .gen = 4, .base = BSD_RING_BASE }
		},
=======
		.mmio_base = GEN6_BSD_RING_BASE,
		.irq_shift = GEN8_VCS1_IRQ_SHIFT,
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	},
	[VCS2] = {
		.hw_id = VCS2_HW,
		.uabi_id = I915_EXEC_BSD,
		.class = VIDEO_DECODE_CLASS,
		.instance = 1,
<<<<<<< HEAD
		.mmio_bases = {
			{ .gen = 11, .base = GEN11_BSD2_RING_BASE },
			{ .gen = 8, .base = GEN8_BSD2_RING_BASE }
		},
	},
	[VCS3] = {
		.hw_id = VCS3_HW,
		.uabi_id = I915_EXEC_BSD,
		.class = VIDEO_DECODE_CLASS,
		.instance = 2,
		.mmio_bases = {
			{ .gen = 11, .base = GEN11_BSD3_RING_BASE }
		},
	},
	[VCS4] = {
		.hw_id = VCS4_HW,
		.uabi_id = I915_EXEC_BSD,
		.class = VIDEO_DECODE_CLASS,
		.instance = 3,
		.mmio_bases = {
			{ .gen = 11, .base = GEN11_BSD4_RING_BASE }
		},
=======
		.mmio_base = GEN8_BSD2_RING_BASE,
		.irq_shift = GEN8_VCS2_IRQ_SHIFT,
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	},
	[VECS] = {
		.hw_id = VECS_HW,
		.uabi_id = I915_EXEC_VEBOX,
		.class = VIDEO_ENHANCEMENT_CLASS,
		.instance = 0,
<<<<<<< HEAD
		.mmio_bases = {
			{ .gen = 11, .base = GEN11_VEBOX_RING_BASE },
			{ .gen = 7, .base = VEBOX_RING_BASE }
		},
	},
	[VECS2] = {
		.hw_id = VECS2_HW,
		.uabi_id = I915_EXEC_VEBOX,
		.class = VIDEO_ENHANCEMENT_CLASS,
		.instance = 1,
		.mmio_bases = {
			{ .gen = 11, .base = GEN11_VEBOX2_RING_BASE }
		},
=======
		.mmio_base = VEBOX_RING_BASE,
		.irq_shift = GEN8_VECS_IRQ_SHIFT,
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	},
};

/**
 * ___intel_engine_context_size() - return the size of the context for an engine
 * @dev_priv: i915 device private
 * @class: engine class
 *
 * Each engine class may require a different amount of space for a context
 * image.
 *
 * Return: size (in bytes) of an engine class specific context image
 *
 * Note: this size includes the HWSP, which is part of the context image
 * in LRC mode, but does not include the "shared data page" used with
 * GuC submission. The caller should account for this if using the GuC.
 */
static u32
__intel_engine_context_size(struct drm_i915_private *dev_priv, u8 class)
{
	u32 cxt_size;

	BUILD_BUG_ON(I915_GTT_PAGE_SIZE != PAGE_SIZE);

	switch (class) {
	case RENDER_CLASS:
		switch (INTEL_GEN(dev_priv)) {
		default:
			MISSING_CASE(INTEL_GEN(dev_priv));
<<<<<<< HEAD
			return DEFAULT_LR_CONTEXT_RENDER_SIZE;
		case 11:
			return GEN11_LR_CONTEXT_RENDER_SIZE;
		case 10:
			return GEN10_LR_CONTEXT_RENDER_SIZE;
		case 9:
			return GEN9_LR_CONTEXT_RENDER_SIZE;
		case 8:
			return GEN8_LR_CONTEXT_RENDER_SIZE;
=======
		case 10:
		case 9:
			return GEN9_LR_CONTEXT_RENDER_SIZE;
		case 8:
			return i915.enable_execlists ?
			       GEN8_LR_CONTEXT_RENDER_SIZE :
			       GEN8_CXT_TOTAL_SIZE;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
		case 7:
			if (IS_HASWELL(dev_priv))
				return HSW_CXT_TOTAL_SIZE;

			cxt_size = I915_READ(GEN7_CXT_SIZE);
			return round_up(GEN7_CXT_TOTAL_SIZE(cxt_size) * 64,
					PAGE_SIZE);
		case 6:
			cxt_size = I915_READ(CXT_SIZE);
			return round_up(GEN6_CXT_TOTAL_SIZE(cxt_size) * 64,
					PAGE_SIZE);
		case 5:
		case 4:
		case 3:
		case 2:
		/* For the special day when i810 gets merged. */
		case 1:
			return 0;
		}
		break;
	default:
		MISSING_CASE(class);
<<<<<<< HEAD
		/* fall through */
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	case VIDEO_DECODE_CLASS:
	case VIDEO_ENHANCEMENT_CLASS:
	case COPY_ENGINE_CLASS:
		if (INTEL_GEN(dev_priv) < 8)
			return 0;
		return GEN8_LR_CONTEXT_OTHER_SIZE;
	}
}

<<<<<<< HEAD
static u32 __engine_mmio_base(struct drm_i915_private *i915,
			      const struct engine_mmio_base *bases)
{
	int i;

	for (i = 0; i < MAX_MMIO_BASES; i++)
		if (INTEL_GEN(i915) >= bases[i].gen)
			break;

	GEM_BUG_ON(i == MAX_MMIO_BASES);
	GEM_BUG_ON(!bases[i].base);

	return bases[i].base;
}

static void __sprint_engine_name(char *name, const struct engine_info *info)
{
	WARN_ON(snprintf(name, INTEL_ENGINE_CS_MAX_NAME, "%s%u",
			 intel_engine_classes[info->class].name,
			 info->instance) >= INTEL_ENGINE_CS_MAX_NAME);
}

=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
static int
intel_engine_setup(struct drm_i915_private *dev_priv,
		   enum intel_engine_id id)
{
	const struct engine_info *info = &intel_engines[id];
<<<<<<< HEAD
	struct intel_engine_cs *engine;

	GEM_BUG_ON(info->class >= ARRAY_SIZE(intel_engine_classes));

	BUILD_BUG_ON(MAX_ENGINE_CLASS >= BIT(GEN11_ENGINE_CLASS_WIDTH));
	BUILD_BUG_ON(MAX_ENGINE_INSTANCE >= BIT(GEN11_ENGINE_INSTANCE_WIDTH));

	if (GEM_WARN_ON(info->class > MAX_ENGINE_CLASS))
		return -EINVAL;

	if (GEM_WARN_ON(info->instance > MAX_ENGINE_INSTANCE))
		return -EINVAL;

	if (GEM_WARN_ON(dev_priv->engine_class[info->class][info->instance]))
		return -EINVAL;
=======
	const struct engine_class_info *class_info;
	struct intel_engine_cs *engine;

	GEM_BUG_ON(info->class >= ARRAY_SIZE(intel_engine_classes));
	class_info = &intel_engine_classes[info->class];
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	GEM_BUG_ON(dev_priv->engine[id]);
	engine = kzalloc(sizeof(*engine), GFP_KERNEL);
	if (!engine)
		return -ENOMEM;

	engine->id = id;
	engine->i915 = dev_priv;
<<<<<<< HEAD
	__sprint_engine_name(engine->name, info);
	engine->hw_id = engine->guc_id = info->hw_id;
	engine->mmio_base = __engine_mmio_base(dev_priv, info->mmio_bases);
	engine->class = info->class;
	engine->instance = info->instance;

	engine->uabi_id = info->uabi_id;
	engine->uabi_class = intel_engine_classes[info->class].uabi_class;

=======
	WARN_ON(snprintf(engine->name, sizeof(engine->name), "%s%u",
			 class_info->name, info->instance) >=
		sizeof(engine->name));
	engine->uabi_id = info->uabi_id;
	engine->hw_id = engine->guc_id = info->hw_id;
	engine->mmio_base = info->mmio_base;
	engine->irq_shift = info->irq_shift;
	engine->class = info->class;
	engine->instance = info->instance;

>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	engine->context_size = __intel_engine_context_size(dev_priv,
							   engine->class);
	if (WARN_ON(engine->context_size > BIT(20)))
		engine->context_size = 0;
<<<<<<< HEAD
	if (engine->context_size)
		DRIVER_CAPS(dev_priv)->has_logical_contexts = true;
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	/* Nothing to do here, execute in order of dependencies */
	engine->schedule = NULL;

<<<<<<< HEAD
	seqlock_init(&engine->stats.lock);

	ATOMIC_INIT_NOTIFIER_HEAD(&engine->context_status_notifier);

	dev_priv->engine_class[info->class][info->instance] = engine;
=======
	ATOMIC_INIT_NOTIFIER_HEAD(&engine->context_status_notifier);

>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	dev_priv->engine[id] = engine;
	return 0;
}

/**
 * intel_engines_init_mmio() - allocate and prepare the Engine Command Streamers
 * @dev_priv: i915 device private
 *
 * Return: non-zero if the initialization failed.
 */
int intel_engines_init_mmio(struct drm_i915_private *dev_priv)
{
	struct intel_device_info *device_info = mkwrite_device_info(dev_priv);
	const unsigned int ring_mask = INTEL_INFO(dev_priv)->ring_mask;
	struct intel_engine_cs *engine;
	enum intel_engine_id id;
	unsigned int mask = 0;
	unsigned int i;
	int err;

	WARN_ON(ring_mask == 0);
	WARN_ON(ring_mask &
		GENMASK(sizeof(mask) * BITS_PER_BYTE - 1, I915_NUM_ENGINES));

	for (i = 0; i < ARRAY_SIZE(intel_engines); i++) {
		if (!HAS_ENGINE(dev_priv, i))
			continue;

		err = intel_engine_setup(dev_priv, i);
		if (err)
			goto cleanup;

		mask |= ENGINE_MASK(i);
	}

	/*
	 * Catch failures to update intel_engines table when the new engines
	 * are added to the driver by a warning and disabling the forgotten
	 * engines.
	 */
	if (WARN_ON(mask != ring_mask))
		device_info->ring_mask = mask;

	/* We always presume we have at least RCS available for later probing */
	if (WARN_ON(!HAS_ENGINE(dev_priv, RCS))) {
		err = -ENODEV;
		goto cleanup;
	}

	device_info->num_rings = hweight32(mask);

<<<<<<< HEAD
	i915_check_and_clear_faults(dev_priv);

=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	return 0;

cleanup:
	for_each_engine(engine, dev_priv, id)
		kfree(engine);
	return err;
}

/**
 * intel_engines_init() - init the Engine Command Streamers
 * @dev_priv: i915 device private
 *
 * Return: non-zero if the initialization failed.
 */
int intel_engines_init(struct drm_i915_private *dev_priv)
{
	struct intel_engine_cs *engine;
	enum intel_engine_id id, err_id;
	int err;

	for_each_engine(engine, dev_priv, id) {
		const struct engine_class_info *class_info =
			&intel_engine_classes[engine->class];
		int (*init)(struct intel_engine_cs *engine);

<<<<<<< HEAD
		if (HAS_EXECLISTS(dev_priv))
=======
		if (i915.enable_execlists)
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
			init = class_info->init_execlists;
		else
			init = class_info->init_legacy;

		err = -EINVAL;
		err_id = id;

		if (GEM_WARN_ON(!init))
			goto cleanup;

		err = init(engine);
		if (err)
			goto cleanup;

		GEM_BUG_ON(!engine->submit_request);
	}

	return 0;

cleanup:
	for_each_engine(engine, dev_priv, id) {
		if (id >= err_id) {
			kfree(engine);
			dev_priv->engine[id] = NULL;
		} else {
			dev_priv->gt.cleanup_engine(engine);
		}
	}
	return err;
}

void intel_engine_init_global_seqno(struct intel_engine_cs *engine, u32 seqno)
{
	struct drm_i915_private *dev_priv = engine->i915;

	/* Our semaphore implementation is strictly monotonic (i.e. we proceed
	 * so long as the semaphore value in the register/page is greater
	 * than the sync value), so whenever we reset the seqno,
	 * so long as we reset the tracking semaphore value to 0, it will
	 * always be before the next request's seqno. If we don't reset
	 * the semaphore value, then when the seqno moves backwards all
	 * future waits will complete instantly (causing rendering corruption).
	 */
	if (IS_GEN6(dev_priv) || IS_GEN7(dev_priv)) {
		I915_WRITE(RING_SYNC_0(engine->mmio_base), 0);
		I915_WRITE(RING_SYNC_1(engine->mmio_base), 0);
		if (HAS_VEBOX(dev_priv))
			I915_WRITE(RING_SYNC_2(engine->mmio_base), 0);
	}
<<<<<<< HEAD
=======
	if (dev_priv->semaphore) {
		struct page *page = i915_vma_first_page(dev_priv->semaphore);
		void *semaphores;

		/* Semaphores are in noncoherent memory, flush to be safe */
		semaphores = kmap_atomic(page);
		memset(semaphores + GEN8_SEMAPHORE_OFFSET(engine->id, 0),
		       0, I915_NUM_ENGINES * gen8_semaphore_seqno_size);
		drm_clflush_virt_range(semaphores + GEN8_SEMAPHORE_OFFSET(engine->id, 0),
				       I915_NUM_ENGINES * gen8_semaphore_seqno_size);
		kunmap_atomic(semaphores);
	}
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	intel_write_status_page(engine, I915_GEM_HWS_INDEX, seqno);
	clear_bit(ENGINE_IRQ_BREADCRUMB, &engine->irq_posted);

	/* After manually advancing the seqno, fake the interrupt in case
	 * there are any waiters for that seqno.
	 */
	intel_engine_wakeup(engine);

	GEM_BUG_ON(intel_engine_get_seqno(engine) != seqno);
}

<<<<<<< HEAD
static void intel_engine_init_batch_pool(struct intel_engine_cs *engine)
{
	i915_gem_batch_pool_init(&engine->batch_pool, engine);
}

static void intel_engine_init_execlist(struct intel_engine_cs *engine)
{
	struct intel_engine_execlists * const execlists = &engine->execlists;

	execlists->port_mask = 1;
	BUILD_BUG_ON_NOT_POWER_OF_2(execlists_num_ports(execlists));
	GEM_BUG_ON(execlists_num_ports(execlists) > EXECLIST_MAX_PORTS);

	execlists->queue_priority = INT_MIN;
	execlists->queue = RB_ROOT_CACHED;
=======
static void intel_engine_init_timeline(struct intel_engine_cs *engine)
{
	engine->timeline = &engine->i915->gt.global_timeline.engine[engine->id];
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
}

/**
 * intel_engines_setup_common - setup engine state not requiring hw access
 * @engine: Engine to setup.
 *
 * Initializes @engine@ structure members shared between legacy and execlists
 * submission modes which do not require hardware access.
 *
 * Typically done early in the submission mode specific engine setup stage.
 */
void intel_engine_setup_common(struct intel_engine_cs *engine)
{
<<<<<<< HEAD
	i915_timeline_init(engine->i915, &engine->timeline, engine->name);
	lockdep_set_subclass(&engine->timeline.lock, TIMELINE_ENGINE);

	intel_engine_init_execlist(engine);
	intel_engine_init_hangcheck(engine);
	intel_engine_init_batch_pool(engine);
	intel_engine_init_cmd_parser(engine);
}

int intel_engine_create_scratch(struct intel_engine_cs *engine,
				unsigned int size)
=======
	engine->execlist_queue = RB_ROOT;
	engine->execlist_first = NULL;

	intel_engine_init_timeline(engine);
	intel_engine_init_hangcheck(engine);
	i915_gem_batch_pool_init(engine, &engine->batch_pool);

	intel_engine_init_cmd_parser(engine);
}

int intel_engine_create_scratch(struct intel_engine_cs *engine, int size)
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
{
	struct drm_i915_gem_object *obj;
	struct i915_vma *vma;
	int ret;

	WARN_ON(engine->scratch);

	obj = i915_gem_object_create_stolen(engine->i915, size);
	if (!obj)
		obj = i915_gem_object_create_internal(engine->i915, size);
	if (IS_ERR(obj)) {
		DRM_ERROR("Failed to allocate scratch page\n");
		return PTR_ERR(obj);
	}

<<<<<<< HEAD
	vma = i915_vma_instance(obj, &engine->i915->ggtt.vm, NULL);
=======
	vma = i915_vma_instance(obj, &engine->i915->ggtt.base, NULL);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	if (IS_ERR(vma)) {
		ret = PTR_ERR(vma);
		goto err_unref;
	}

	ret = i915_vma_pin(vma, 0, 4096, PIN_GLOBAL | PIN_HIGH);
	if (ret)
		goto err_unref;

	engine->scratch = vma;
<<<<<<< HEAD
=======
	DRM_DEBUG_DRIVER("%s pipe control offset: 0x%08x\n",
			 engine->name, i915_ggtt_offset(vma));
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	return 0;

err_unref:
	i915_gem_object_put(obj);
	return ret;
}

<<<<<<< HEAD
void intel_engine_cleanup_scratch(struct intel_engine_cs *engine)
=======
static void intel_engine_cleanup_scratch(struct intel_engine_cs *engine)
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
{
	i915_vma_unpin_and_release(&engine->scratch);
}

<<<<<<< HEAD
static void cleanup_phys_status_page(struct intel_engine_cs *engine)
{
	struct drm_i915_private *dev_priv = engine->i915;

	if (!dev_priv->status_page_dmah)
		return;

	drm_pci_free(&dev_priv->drm, dev_priv->status_page_dmah);
	engine->status_page.page_addr = NULL;
}

static void cleanup_status_page(struct intel_engine_cs *engine)
{
	struct i915_vma *vma;
	struct drm_i915_gem_object *obj;

	vma = fetch_and_zero(&engine->status_page.vma);
	if (!vma)
		return;

	obj = vma->obj;

	i915_vma_unpin(vma);
	i915_vma_close(vma);

	i915_gem_object_unpin_map(obj);
	__i915_gem_object_release_unless_active(obj);
}

static int init_status_page(struct intel_engine_cs *engine)
{
	struct drm_i915_gem_object *obj;
	struct i915_vma *vma;
	unsigned int flags;
	void *vaddr;
	int ret;

	obj = i915_gem_object_create_internal(engine->i915, PAGE_SIZE);
	if (IS_ERR(obj)) {
		DRM_ERROR("Failed to allocate status page\n");
		return PTR_ERR(obj);
	}

	ret = i915_gem_object_set_cache_level(obj, I915_CACHE_LLC);
	if (ret)
		goto err;

	vma = i915_vma_instance(obj, &engine->i915->ggtt.vm, NULL);
	if (IS_ERR(vma)) {
		ret = PTR_ERR(vma);
		goto err;
	}

	flags = PIN_GLOBAL;
	if (!HAS_LLC(engine->i915))
		/* On g33, we cannot place HWS above 256MiB, so
		 * restrict its pinning to the low mappable arena.
		 * Though this restriction is not documented for
		 * gen4, gen5, or byt, they also behave similarly
		 * and hang if the HWS is placed at the top of the
		 * GTT. To generalise, it appears that all !llc
		 * platforms have issues with us placing the HWS
		 * above the mappable region (even though we never
		 * actually map it).
		 */
		flags |= PIN_MAPPABLE;
	else
		flags |= PIN_HIGH;
	ret = i915_vma_pin(vma, 0, 4096, flags);
	if (ret)
		goto err;

	vaddr = i915_gem_object_pin_map(obj, I915_MAP_WB);
	if (IS_ERR(vaddr)) {
		ret = PTR_ERR(vaddr);
		goto err_unpin;
	}

	engine->status_page.vma = vma;
	engine->status_page.ggtt_offset = i915_ggtt_offset(vma);
	engine->status_page.page_addr = memset(vaddr, 0, PAGE_SIZE);
	return 0;

err_unpin:
	i915_vma_unpin(vma);
err:
	i915_gem_object_put(obj);
	return ret;
}

static int init_phys_status_page(struct intel_engine_cs *engine)
{
	struct drm_i915_private *dev_priv = engine->i915;

	GEM_BUG_ON(engine->id != RCS);

	dev_priv->status_page_dmah =
		drm_pci_alloc(&dev_priv->drm, PAGE_SIZE, PAGE_SIZE);
	if (!dev_priv->status_page_dmah)
		return -ENOMEM;

	engine->status_page.page_addr = dev_priv->status_page_dmah->vaddr;
	memset(engine->status_page.page_addr, 0, PAGE_SIZE);

	return 0;
}

static void __intel_context_unpin(struct i915_gem_context *ctx,
				  struct intel_engine_cs *engine)
{
	intel_context_unpin(to_intel_context(ctx, engine));
}

=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
/**
 * intel_engines_init_common - initialize cengine state which might require hw access
 * @engine: Engine to initialize.
 *
 * Initializes @engine@ structure members shared between legacy and execlists
 * submission modes which do require hardware access.
 *
 * Typcally done at later stages of submission mode specific engine setup.
 *
 * Returns zero on success or an error code on failure.
 */
int intel_engine_init_common(struct intel_engine_cs *engine)
{
<<<<<<< HEAD
	struct drm_i915_private *i915 = engine->i915;
	struct intel_context *ce;
=======
	struct intel_ring *ring;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	int ret;

	engine->set_default_submission(engine);

	/* We may need to do things with the shrinker which
	 * require us to immediately switch back to the default
	 * context. This can cause a problem as pinning the
	 * default context also requires GTT space which may not
	 * be available. To avoid this we always pin the default
	 * context.
	 */
<<<<<<< HEAD
	ce = intel_context_pin(i915->kernel_context, engine);
	if (IS_ERR(ce))
		return PTR_ERR(ce);

	/*
	 * Similarly the preempt context must always be available so that
	 * we can interrupt the engine at any time.
	 */
	if (i915->preempt_context) {
		ce = intel_context_pin(i915->preempt_context, engine);
		if (IS_ERR(ce)) {
			ret = PTR_ERR(ce);
			goto err_unpin_kernel;
		}
	}

	ret = intel_engine_init_breadcrumbs(engine);
	if (ret)
		goto err_unpin_preempt;

	if (HWS_NEEDS_PHYSICAL(i915))
		ret = init_phys_status_page(engine);
	else
		ret = init_status_page(engine);
	if (ret)
		goto err_breadcrumbs;

	return 0;

err_breadcrumbs:
	intel_engine_fini_breadcrumbs(engine);
err_unpin_preempt:
	if (i915->preempt_context)
		__intel_context_unpin(i915->preempt_context, engine);

err_unpin_kernel:
	__intel_context_unpin(i915->kernel_context, engine);
=======
	ring = engine->context_pin(engine, engine->i915->kernel_context);
	if (IS_ERR(ring))
		return PTR_ERR(ring);

	ret = intel_engine_init_breadcrumbs(engine);
	if (ret)
		goto err_unpin;

	ret = i915_gem_render_state_init(engine);
	if (ret)
		goto err_unpin;

	return 0;

err_unpin:
	engine->context_unpin(engine, engine->i915->kernel_context);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	return ret;
}

/**
 * intel_engines_cleanup_common - cleans up the engine state created by
 *                                the common initiailizers.
 * @engine: Engine to cleanup.
 *
 * This cleans up everything created by the common helpers.
 */
void intel_engine_cleanup_common(struct intel_engine_cs *engine)
{
<<<<<<< HEAD
	struct drm_i915_private *i915 = engine->i915;

	intel_engine_cleanup_scratch(engine);

	if (HWS_NEEDS_PHYSICAL(engine->i915))
		cleanup_phys_status_page(engine);
	else
		cleanup_status_page(engine);

=======
	intel_engine_cleanup_scratch(engine);

	i915_gem_render_state_fini(engine);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	intel_engine_fini_breadcrumbs(engine);
	intel_engine_cleanup_cmd_parser(engine);
	i915_gem_batch_pool_fini(&engine->batch_pool);

<<<<<<< HEAD
	if (engine->default_state)
		i915_gem_object_put(engine->default_state);

	if (i915->preempt_context)
		__intel_context_unpin(i915->preempt_context, engine);
	__intel_context_unpin(i915->kernel_context, engine);

	i915_timeline_fini(&engine->timeline);
}

u64 intel_engine_get_active_head(const struct intel_engine_cs *engine)
=======
	engine->context_unpin(engine, engine->i915->kernel_context);
}

u64 intel_engine_get_active_head(struct intel_engine_cs *engine)
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
{
	struct drm_i915_private *dev_priv = engine->i915;
	u64 acthd;

	if (INTEL_GEN(dev_priv) >= 8)
		acthd = I915_READ64_2x32(RING_ACTHD(engine->mmio_base),
					 RING_ACTHD_UDW(engine->mmio_base));
	else if (INTEL_GEN(dev_priv) >= 4)
		acthd = I915_READ(RING_ACTHD(engine->mmio_base));
	else
		acthd = I915_READ(ACTHD);

	return acthd;
}

<<<<<<< HEAD
u64 intel_engine_get_last_batch_head(const struct intel_engine_cs *engine)
=======
u64 intel_engine_get_last_batch_head(struct intel_engine_cs *engine)
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
{
	struct drm_i915_private *dev_priv = engine->i915;
	u64 bbaddr;

	if (INTEL_GEN(dev_priv) >= 8)
		bbaddr = I915_READ64_2x32(RING_BBADDR(engine->mmio_base),
					  RING_BBADDR_UDW(engine->mmio_base));
	else
		bbaddr = I915_READ(RING_BBADDR(engine->mmio_base));

	return bbaddr;
}

<<<<<<< HEAD
int intel_engine_stop_cs(struct intel_engine_cs *engine)
{
	struct drm_i915_private *dev_priv = engine->i915;
	const u32 base = engine->mmio_base;
	const i915_reg_t mode = RING_MI_MODE(base);
	int err;

	if (INTEL_GEN(dev_priv) < 3)
		return -ENODEV;

	GEM_TRACE("%s\n", engine->name);

	I915_WRITE_FW(mode, _MASKED_BIT_ENABLE(STOP_RING));

	err = 0;
	if (__intel_wait_for_register_fw(dev_priv,
					 mode, MODE_IDLE, MODE_IDLE,
					 1000, 0,
					 NULL)) {
		GEM_TRACE("%s: timed out on STOP_RING -> IDLE\n", engine->name);
		err = -ETIMEDOUT;
	}

	/* A final mmio read to let GPU writes be hopefully flushed to memory */
	POSTING_READ_FW(mode);

	return err;
}

=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
const char *i915_cache_level_str(struct drm_i915_private *i915, int type)
{
	switch (type) {
	case I915_CACHE_NONE: return " uncached";
	case I915_CACHE_LLC: return HAS_LLC(i915) ? " LLC" : " snooped";
	case I915_CACHE_L3_LLC: return " L3+LLC";
	case I915_CACHE_WT: return " WT";
	default: return "";
	}
}

<<<<<<< HEAD
u32 intel_calculate_mcr_s_ss_select(struct drm_i915_private *dev_priv)
{
	const struct sseu_dev_info *sseu = &(INTEL_INFO(dev_priv)->sseu);
	u32 mcr_s_ss_select;
	u32 slice = fls(sseu->slice_mask);
	u32 subslice = fls(sseu->subslice_mask[slice]);

	if (INTEL_GEN(dev_priv) == 10)
		mcr_s_ss_select = GEN8_MCR_SLICE(slice) |
				  GEN8_MCR_SUBSLICE(subslice);
	else if (INTEL_GEN(dev_priv) >= 11)
		mcr_s_ss_select = GEN11_MCR_SLICE(slice) |
				  GEN11_MCR_SUBSLICE(subslice);
	else
		mcr_s_ss_select = 0;

	return mcr_s_ss_select;
}

=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
static inline uint32_t
read_subslice_reg(struct drm_i915_private *dev_priv, int slice,
		  int subslice, i915_reg_t reg)
{
<<<<<<< HEAD
	uint32_t mcr_slice_subslice_mask;
	uint32_t mcr_slice_subslice_select;
	uint32_t default_mcr_s_ss_select;
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	uint32_t mcr;
	uint32_t ret;
	enum forcewake_domains fw_domains;

<<<<<<< HEAD
	if (INTEL_GEN(dev_priv) >= 11) {
		mcr_slice_subslice_mask = GEN11_MCR_SLICE_MASK |
					  GEN11_MCR_SUBSLICE_MASK;
		mcr_slice_subslice_select = GEN11_MCR_SLICE(slice) |
					    GEN11_MCR_SUBSLICE(subslice);
	} else {
		mcr_slice_subslice_mask = GEN8_MCR_SLICE_MASK |
					  GEN8_MCR_SUBSLICE_MASK;
		mcr_slice_subslice_select = GEN8_MCR_SLICE(slice) |
					    GEN8_MCR_SUBSLICE(subslice);
	}

	default_mcr_s_ss_select = intel_calculate_mcr_s_ss_select(dev_priv);

=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	fw_domains = intel_uncore_forcewake_for_reg(dev_priv, reg,
						    FW_REG_READ);
	fw_domains |= intel_uncore_forcewake_for_reg(dev_priv,
						     GEN8_MCR_SELECTOR,
						     FW_REG_READ | FW_REG_WRITE);

	spin_lock_irq(&dev_priv->uncore.lock);
	intel_uncore_forcewake_get__locked(dev_priv, fw_domains);

	mcr = I915_READ_FW(GEN8_MCR_SELECTOR);
<<<<<<< HEAD

	WARN_ON_ONCE((mcr & mcr_slice_subslice_mask) !=
		     default_mcr_s_ss_select);

	mcr &= ~mcr_slice_subslice_mask;
	mcr |= mcr_slice_subslice_select;
=======
	/*
	 * The HW expects the slice and sublice selectors to be reset to 0
	 * after reading out the registers.
	 */
	WARN_ON_ONCE(mcr & (GEN8_MCR_SLICE_MASK | GEN8_MCR_SUBSLICE_MASK));
	mcr &= ~(GEN8_MCR_SLICE_MASK | GEN8_MCR_SUBSLICE_MASK);
	mcr |= GEN8_MCR_SLICE(slice) | GEN8_MCR_SUBSLICE(subslice);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	I915_WRITE_FW(GEN8_MCR_SELECTOR, mcr);

	ret = I915_READ_FW(reg);

<<<<<<< HEAD
	mcr &= ~mcr_slice_subslice_mask;
	mcr |= default_mcr_s_ss_select;

=======
	mcr &= ~(GEN8_MCR_SLICE_MASK | GEN8_MCR_SUBSLICE_MASK);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	I915_WRITE_FW(GEN8_MCR_SELECTOR, mcr);

	intel_uncore_forcewake_put__locked(dev_priv, fw_domains);
	spin_unlock_irq(&dev_priv->uncore.lock);

	return ret;
}

/* NB: please notice the memset */
void intel_engine_get_instdone(struct intel_engine_cs *engine,
			       struct intel_instdone *instdone)
{
	struct drm_i915_private *dev_priv = engine->i915;
	u32 mmio_base = engine->mmio_base;
	int slice;
	int subslice;

	memset(instdone, 0, sizeof(*instdone));

	switch (INTEL_GEN(dev_priv)) {
	default:
		instdone->instdone = I915_READ(RING_INSTDONE(mmio_base));

		if (engine->id != RCS)
			break;

		instdone->slice_common = I915_READ(GEN7_SC_INSTDONE);
		for_each_instdone_slice_subslice(dev_priv, slice, subslice) {
			instdone->sampler[slice][subslice] =
				read_subslice_reg(dev_priv, slice, subslice,
						  GEN7_SAMPLER_INSTDONE);
			instdone->row[slice][subslice] =
				read_subslice_reg(dev_priv, slice, subslice,
						  GEN7_ROW_INSTDONE);
		}
		break;
	case 7:
		instdone->instdone = I915_READ(RING_INSTDONE(mmio_base));

		if (engine->id != RCS)
			break;

		instdone->slice_common = I915_READ(GEN7_SC_INSTDONE);
		instdone->sampler[0][0] = I915_READ(GEN7_SAMPLER_INSTDONE);
		instdone->row[0][0] = I915_READ(GEN7_ROW_INSTDONE);

		break;
	case 6:
	case 5:
	case 4:
		instdone->instdone = I915_READ(RING_INSTDONE(mmio_base));

		if (engine->id == RCS)
			/* HACK: Using the wrong struct member */
			instdone->slice_common = I915_READ(GEN4_INSTDONE1);
		break;
	case 3:
	case 2:
		instdone->instdone = I915_READ(GEN2_INSTDONE);
		break;
	}
}

<<<<<<< HEAD
=======
static int wa_add(struct drm_i915_private *dev_priv,
		  i915_reg_t addr,
		  const u32 mask, const u32 val)
{
	const u32 idx = dev_priv->workarounds.count;

	if (WARN_ON(idx >= I915_MAX_WA_REGS))
		return -ENOSPC;

	dev_priv->workarounds.reg[idx].addr = addr;
	dev_priv->workarounds.reg[idx].value = val;
	dev_priv->workarounds.reg[idx].mask = mask;

	dev_priv->workarounds.count++;

	return 0;
}

#define WA_REG(addr, mask, val) do { \
		const int r = wa_add(dev_priv, (addr), (mask), (val)); \
		if (r) \
			return r; \
	} while (0)

#define WA_SET_BIT_MASKED(addr, mask) \
	WA_REG(addr, (mask), _MASKED_BIT_ENABLE(mask))

#define WA_CLR_BIT_MASKED(addr, mask) \
	WA_REG(addr, (mask), _MASKED_BIT_DISABLE(mask))

#define WA_SET_FIELD_MASKED(addr, mask, value) \
	WA_REG(addr, mask, _MASKED_FIELD(mask, value))

#define WA_SET_BIT(addr, mask) WA_REG(addr, mask, I915_READ(addr) | (mask))
#define WA_CLR_BIT(addr, mask) WA_REG(addr, mask, I915_READ(addr) & ~(mask))

#define WA_WRITE(addr, val) WA_REG(addr, 0xffffffff, val)

static int wa_ring_whitelist_reg(struct intel_engine_cs *engine,
				 i915_reg_t reg)
{
	struct drm_i915_private *dev_priv = engine->i915;
	struct i915_workarounds *wa = &dev_priv->workarounds;
	const uint32_t index = wa->hw_whitelist_count[engine->id];

	if (WARN_ON(index >= RING_MAX_NONPRIV_SLOTS))
		return -EINVAL;

	WA_WRITE(RING_FORCE_TO_NONPRIV(engine->mmio_base, index),
		 i915_mmio_reg_offset(reg));
	wa->hw_whitelist_count[engine->id]++;

	return 0;
}

static int gen8_init_workarounds(struct intel_engine_cs *engine)
{
	struct drm_i915_private *dev_priv = engine->i915;

	WA_SET_BIT_MASKED(INSTPM, INSTPM_FORCE_ORDERING);

	/* WaDisableAsyncFlipPerfMode:bdw,chv */
	WA_SET_BIT_MASKED(MI_MODE, ASYNC_FLIP_PERF_DISABLE);

	/* WaDisablePartialInstShootdown:bdw,chv */
	WA_SET_BIT_MASKED(GEN8_ROW_CHICKEN,
			  PARTIAL_INSTRUCTION_SHOOTDOWN_DISABLE);

	/* Use Force Non-Coherent whenever executing a 3D context. This is a
	 * workaround for for a possible hang in the unlikely event a TLB
	 * invalidation occurs during a PSD flush.
	 */
	/* WaForceEnableNonCoherent:bdw,chv */
	/* WaHdcDisableFetchWhenMasked:bdw,chv */
	WA_SET_BIT_MASKED(HDC_CHICKEN0,
			  HDC_DONOT_FETCH_MEM_WHEN_MASKED |
			  HDC_FORCE_NON_COHERENT);

	/* From the Haswell PRM, Command Reference: Registers, CACHE_MODE_0:
	 * "The Hierarchical Z RAW Stall Optimization allows non-overlapping
	 *  polygons in the same 8x4 pixel/sample area to be processed without
	 *  stalling waiting for the earlier ones to write to Hierarchical Z
	 *  buffer."
	 *
	 * This optimization is off by default for BDW and CHV; turn it on.
	 */
	WA_CLR_BIT_MASKED(CACHE_MODE_0_GEN7, HIZ_RAW_STALL_OPT_DISABLE);

	/* Wa4x4STCOptimizationDisable:bdw,chv */
	WA_SET_BIT_MASKED(CACHE_MODE_1, GEN8_4x4_STC_OPTIMIZATION_DISABLE);

	/*
	 * BSpec recommends 8x4 when MSAA is used,
	 * however in practice 16x4 seems fastest.
	 *
	 * Note that PS/WM thread counts depend on the WIZ hashing
	 * disable bit, which we don't touch here, but it's good
	 * to keep in mind (see 3DSTATE_PS and 3DSTATE_WM).
	 */
	WA_SET_FIELD_MASKED(GEN7_GT_MODE,
			    GEN6_WIZ_HASHING_MASK,
			    GEN6_WIZ_HASHING_16x4);

	return 0;
}

static int bdw_init_workarounds(struct intel_engine_cs *engine)
{
	struct drm_i915_private *dev_priv = engine->i915;
	int ret;

	ret = gen8_init_workarounds(engine);
	if (ret)
		return ret;

	/* WaDisableThreadStallDopClockGating:bdw (pre-production) */
	WA_SET_BIT_MASKED(GEN8_ROW_CHICKEN, STALL_DOP_GATING_DISABLE);

	/* WaDisableDopClockGating:bdw
	 *
	 * Also see the related UCGTCL1 write in broadwell_init_clock_gating()
	 * to disable EUTC clock gating.
	 */
	WA_SET_BIT_MASKED(GEN7_ROW_CHICKEN2,
			  DOP_CLOCK_GATING_DISABLE);

	WA_SET_BIT_MASKED(HALF_SLICE_CHICKEN3,
			  GEN8_SAMPLER_POWER_BYPASS_DIS);

	WA_SET_BIT_MASKED(HDC_CHICKEN0,
			  /* WaForceContextSaveRestoreNonCoherent:bdw */
			  HDC_FORCE_CONTEXT_SAVE_RESTORE_NON_COHERENT |
			  /* WaDisableFenceDestinationToSLM:bdw (pre-prod) */
			  (IS_BDW_GT3(dev_priv) ? HDC_FENCE_DEST_SLM_DISABLE : 0));

	return 0;
}

static int chv_init_workarounds(struct intel_engine_cs *engine)
{
	struct drm_i915_private *dev_priv = engine->i915;
	int ret;

	ret = gen8_init_workarounds(engine);
	if (ret)
		return ret;

	/* WaDisableThreadStallDopClockGating:chv */
	WA_SET_BIT_MASKED(GEN8_ROW_CHICKEN, STALL_DOP_GATING_DISABLE);

	/* Improve HiZ throughput on CHV. */
	WA_SET_BIT_MASKED(HIZ_CHICKEN, CHV_HZ_8X8_MODE_IN_1X);

	return 0;
}

static int gen9_init_workarounds(struct intel_engine_cs *engine)
{
	struct drm_i915_private *dev_priv = engine->i915;
	int ret;

	/* WaConextSwitchWithConcurrentTLBInvalidate:skl,bxt,kbl,glk,cfl */
	I915_WRITE(GEN9_CSFE_CHICKEN1_RCS, _MASKED_BIT_ENABLE(GEN9_PREEMPT_GPGPU_SYNC_SWITCH_DISABLE));

	/* WaEnableLbsSlaRetryTimerDecrement:skl,bxt,kbl,glk,cfl */
	I915_WRITE(BDW_SCRATCH1, I915_READ(BDW_SCRATCH1) |
		   GEN9_LBS_SLA_RETRY_TIMER_DECREMENT_ENABLE);

	/* WaDisableKillLogic:bxt,skl,kbl */
	if (!IS_COFFEELAKE(dev_priv))
		I915_WRITE(GAM_ECOCHK, I915_READ(GAM_ECOCHK) |
			   ECOCHK_DIS_TLB);

	/* WaClearFlowControlGpgpuContextSave:skl,bxt,kbl,glk,cfl */
	/* WaDisablePartialInstShootdown:skl,bxt,kbl,glk,cfl */
	WA_SET_BIT_MASKED(GEN8_ROW_CHICKEN,
			  FLOW_CONTROL_ENABLE |
			  PARTIAL_INSTRUCTION_SHOOTDOWN_DISABLE);

	/* Syncing dependencies between camera and graphics:skl,bxt,kbl */
	if (!IS_COFFEELAKE(dev_priv))
		WA_SET_BIT_MASKED(HALF_SLICE_CHICKEN3,
				  GEN9_DISABLE_OCL_OOB_SUPPRESS_LOGIC);

	/* WaDisableDgMirrorFixInHalfSliceChicken5:bxt */
	if (IS_BXT_REVID(dev_priv, 0, BXT_REVID_A1))
		WA_CLR_BIT_MASKED(GEN9_HALF_SLICE_CHICKEN5,
				  GEN9_DG_MIRROR_FIX_ENABLE);

	/* WaSetDisablePixMaskCammingAndRhwoInCommonSliceChicken:bxt */
	if (IS_BXT_REVID(dev_priv, 0, BXT_REVID_A1)) {
		WA_SET_BIT_MASKED(GEN7_COMMON_SLICE_CHICKEN1,
				  GEN9_RHWO_OPTIMIZATION_DISABLE);
		/*
		 * WA also requires GEN9_SLICE_COMMON_ECO_CHICKEN0[14:14] to be set
		 * but we do that in per ctx batchbuffer as there is an issue
		 * with this register not getting restored on ctx restore
		 */
	}

	/* WaEnableYV12BugFixInHalfSliceChicken7:skl,bxt,kbl,glk,cfl */
	/* WaEnableSamplerGPGPUPreemptionSupport:skl,bxt,kbl,cfl */
	WA_SET_BIT_MASKED(GEN9_HALF_SLICE_CHICKEN7,
			  GEN9_ENABLE_YV12_BUGFIX |
			  GEN9_ENABLE_GPGPU_PREEMPTION);

	/* Wa4x4STCOptimizationDisable:skl,bxt,kbl,glk,cfl */
	/* WaDisablePartialResolveInVc:skl,bxt,kbl,cfl */
	WA_SET_BIT_MASKED(CACHE_MODE_1, (GEN8_4x4_STC_OPTIMIZATION_DISABLE |
					 GEN9_PARTIAL_RESOLVE_IN_VC_DISABLE));

	/* WaCcsTlbPrefetchDisable:skl,bxt,kbl,glk,cfl */
	WA_CLR_BIT_MASKED(GEN9_HALF_SLICE_CHICKEN5,
			  GEN9_CCS_TLB_PREFETCH_ENABLE);

	/* WaDisableMaskBasedCammingInRCC:bxt */
	if (IS_BXT_REVID(dev_priv, 0, BXT_REVID_A1))
		WA_SET_BIT_MASKED(SLICE_ECO_CHICKEN0,
				  PIXEL_MASK_CAMMING_DISABLE);

	/* WaForceContextSaveRestoreNonCoherent:skl,bxt,kbl,cfl */
	WA_SET_BIT_MASKED(HDC_CHICKEN0,
			  HDC_FORCE_CONTEXT_SAVE_RESTORE_NON_COHERENT |
			  HDC_FORCE_CSR_NON_COHERENT_OVR_DISABLE);

	/* WaForceEnableNonCoherent and WaDisableHDCInvalidation are
	 * both tied to WaForceContextSaveRestoreNonCoherent
	 * in some hsds for skl. We keep the tie for all gen9. The
	 * documentation is a bit hazy and so we want to get common behaviour,
	 * even though there is no clear evidence we would need both on kbl/bxt.
	 * This area has been source of system hangs so we play it safe
	 * and mimic the skl regardless of what bspec says.
	 *
	 * Use Force Non-Coherent whenever executing a 3D context. This
	 * is a workaround for a possible hang in the unlikely event
	 * a TLB invalidation occurs during a PSD flush.
	 */

	/* WaForceEnableNonCoherent:skl,bxt,kbl,cfl */
	WA_SET_BIT_MASKED(HDC_CHICKEN0,
			  HDC_FORCE_NON_COHERENT);

	/* WaDisableHDCInvalidation:skl,bxt,kbl,cfl */
	I915_WRITE(GAM_ECOCHK, I915_READ(GAM_ECOCHK) |
		   BDW_DISABLE_HDC_INVALIDATION);

	/* WaDisableSamplerPowerBypassForSOPingPong:skl,bxt,kbl,cfl */
	if (IS_SKYLAKE(dev_priv) ||
	    IS_KABYLAKE(dev_priv) ||
	    IS_COFFEELAKE(dev_priv) ||
	    IS_BXT_REVID(dev_priv, 0, BXT_REVID_B0))
		WA_SET_BIT_MASKED(HALF_SLICE_CHICKEN3,
				  GEN8_SAMPLER_POWER_BYPASS_DIS);

	/* WaDisableSTUnitPowerOptimization:skl,bxt,kbl,glk,cfl */
	WA_SET_BIT_MASKED(HALF_SLICE_CHICKEN2, GEN8_ST_PO_DISABLE);

	/* WaOCLCoherentLineFlush:skl,bxt,kbl,cfl */
	I915_WRITE(GEN8_L3SQCREG4, (I915_READ(GEN8_L3SQCREG4) |
				    GEN8_LQSC_FLUSH_COHERENT_LINES));

	/* WaClearHIZ_WM_CHICKEN3:bxt,glk */
	if (IS_GEN9_LP(dev_priv))
		WA_SET_BIT_MASKED(GEN9_WM_CHICKEN3, GEN9_FACTOR_IN_CLR_VAL_HIZ);

	/* WaVFEStateAfterPipeControlwithMediaStateClear:skl,bxt,glk,cfl */
	ret = wa_ring_whitelist_reg(engine, GEN9_CTX_PREEMPT_REG);
	if (ret)
		return ret;

	/* WaEnablePreemptionGranularityControlByUMD:skl,bxt,kbl,cfl */
	ret= wa_ring_whitelist_reg(engine, GEN8_CS_CHICKEN1);
	if (ret)
		return ret;

	/* WaAllowUMDToModifyHDCChicken1:skl,bxt,kbl,glk,cfl */
	ret = wa_ring_whitelist_reg(engine, GEN8_HDC_CHICKEN1);
	if (ret)
		return ret;

	return 0;
}

static int skl_tune_iz_hashing(struct intel_engine_cs *engine)
{
	struct drm_i915_private *dev_priv = engine->i915;
	u8 vals[3] = { 0, 0, 0 };
	unsigned int i;

	for (i = 0; i < 3; i++) {
		u8 ss;

		/*
		 * Only consider slices where one, and only one, subslice has 7
		 * EUs
		 */
		if (!is_power_of_2(INTEL_INFO(dev_priv)->sseu.subslice_7eu[i]))
			continue;

		/*
		 * subslice_7eu[i] != 0 (because of the check above) and
		 * ss_max == 4 (maximum number of subslices possible per slice)
		 *
		 * ->    0 <= ss <= 3;
		 */
		ss = ffs(INTEL_INFO(dev_priv)->sseu.subslice_7eu[i]) - 1;
		vals[i] = 3 - ss;
	}

	if (vals[0] == 0 && vals[1] == 0 && vals[2] == 0)
		return 0;

	/* Tune IZ hashing. See intel_device_info_runtime_init() */
	WA_SET_FIELD_MASKED(GEN7_GT_MODE,
			    GEN9_IZ_HASHING_MASK(2) |
			    GEN9_IZ_HASHING_MASK(1) |
			    GEN9_IZ_HASHING_MASK(0),
			    GEN9_IZ_HASHING(2, vals[2]) |
			    GEN9_IZ_HASHING(1, vals[1]) |
			    GEN9_IZ_HASHING(0, vals[0]));

	return 0;
}

static int skl_init_workarounds(struct intel_engine_cs *engine)
{
	struct drm_i915_private *dev_priv = engine->i915;
	int ret;

	ret = gen9_init_workarounds(engine);
	if (ret)
		return ret;

	/*
	 * Actual WA is to disable percontext preemption granularity control
	 * until D0 which is the default case so this is equivalent to
	 * !WaDisablePerCtxtPreemptionGranularityControl:skl
	 */
	I915_WRITE(GEN7_FF_SLICE_CS_CHICKEN1,
		   _MASKED_BIT_ENABLE(GEN9_FFSC_PERCTX_PREEMPT_CTRL));

	/* WaEnableGapsTsvCreditFix:skl */
	I915_WRITE(GEN8_GARBCNTL, (I915_READ(GEN8_GARBCNTL) |
				   GEN9_GAPS_TSV_CREDIT_DISABLE));

	/* WaDisableGafsUnitClkGating:skl */
	WA_SET_BIT(GEN7_UCGCTL4, GEN8_EU_GAUNIT_CLOCK_GATE_DISABLE);

	/* WaInPlaceDecompressionHang:skl */
	if (IS_SKL_REVID(dev_priv, SKL_REVID_H0, REVID_FOREVER))
		WA_SET_BIT(GEN9_GAMT_ECO_REG_RW_IA,
			   GAMT_ECO_ENABLE_IN_PLACE_DECOMPRESS);

	/* WaDisableLSQCROPERFforOCL:skl */
	ret = wa_ring_whitelist_reg(engine, GEN8_L3SQCREG4);
	if (ret)
		return ret;

	return skl_tune_iz_hashing(engine);
}

static int bxt_init_workarounds(struct intel_engine_cs *engine)
{
	struct drm_i915_private *dev_priv = engine->i915;
	int ret;

	ret = gen9_init_workarounds(engine);
	if (ret)
		return ret;

	/* WaStoreMultiplePTEenable:bxt */
	/* This is a requirement according to Hardware specification */
	if (IS_BXT_REVID(dev_priv, 0, BXT_REVID_A1))
		I915_WRITE(TILECTL, I915_READ(TILECTL) | TILECTL_TLBPF);

	/* WaSetClckGatingDisableMedia:bxt */
	if (IS_BXT_REVID(dev_priv, 0, BXT_REVID_A1)) {
		I915_WRITE(GEN7_MISCCPCTL, (I915_READ(GEN7_MISCCPCTL) &
					    ~GEN8_DOP_CLOCK_GATE_MEDIA_ENABLE));
	}

	/* WaDisableThreadStallDopClockGating:bxt */
	WA_SET_BIT_MASKED(GEN8_ROW_CHICKEN,
			  STALL_DOP_GATING_DISABLE);

	/* WaDisablePooledEuLoadBalancingFix:bxt */
	if (IS_BXT_REVID(dev_priv, BXT_REVID_B0, REVID_FOREVER)) {
		WA_SET_BIT_MASKED(FF_SLICE_CS_CHICKEN2,
				  GEN9_POOLED_EU_LOAD_BALANCING_FIX_DISABLE);
	}

	/* WaDisableSbeCacheDispatchPortSharing:bxt */
	if (IS_BXT_REVID(dev_priv, 0, BXT_REVID_B0)) {
		WA_SET_BIT_MASKED(
			GEN7_HALF_SLICE_CHICKEN1,
			GEN7_SBE_SS_CACHE_DISPATCH_PORT_SHARING_DISABLE);
	}

	/* WaDisableObjectLevelPreemptionForTrifanOrPolygon:bxt */
	/* WaDisableObjectLevelPreemptionForInstancedDraw:bxt */
	/* WaDisableObjectLevelPreemtionForInstanceId:bxt */
	/* WaDisableLSQCROPERFforOCL:bxt */
	if (IS_BXT_REVID(dev_priv, 0, BXT_REVID_A1)) {
		ret = wa_ring_whitelist_reg(engine, GEN9_CS_DEBUG_MODE1);
		if (ret)
			return ret;

		ret = wa_ring_whitelist_reg(engine, GEN8_L3SQCREG4);
		if (ret)
			return ret;
	}

	/* WaProgramL3SqcReg1DefaultForPerf:bxt */
	if (IS_BXT_REVID(dev_priv, BXT_REVID_B0, REVID_FOREVER)) {
		u32 val = I915_READ(GEN8_L3SQCREG1);
		val &= ~L3_PRIO_CREDITS_MASK;
		val |= L3_GENERAL_PRIO_CREDITS(62) | L3_HIGH_PRIO_CREDITS(2);
		I915_WRITE(GEN8_L3SQCREG1, val);
	}

	/* WaToEnableHwFixForPushConstHWBug:bxt */
	if (IS_BXT_REVID(dev_priv, BXT_REVID_C0, REVID_FOREVER))
		WA_SET_BIT_MASKED(COMMON_SLICE_CHICKEN2,
				  GEN8_SBE_DISABLE_REPLAY_BUF_OPTIMIZATION);

	/* WaInPlaceDecompressionHang:bxt */
	if (IS_BXT_REVID(dev_priv, BXT_REVID_C0, REVID_FOREVER))
		WA_SET_BIT(GEN9_GAMT_ECO_REG_RW_IA,
			   GAMT_ECO_ENABLE_IN_PLACE_DECOMPRESS);

	return 0;
}

static int kbl_init_workarounds(struct intel_engine_cs *engine)
{
	struct drm_i915_private *dev_priv = engine->i915;
	int ret;

	ret = gen9_init_workarounds(engine);
	if (ret)
		return ret;

	/* WaEnableGapsTsvCreditFix:kbl */
	I915_WRITE(GEN8_GARBCNTL, (I915_READ(GEN8_GARBCNTL) |
				   GEN9_GAPS_TSV_CREDIT_DISABLE));

	/* WaDisableDynamicCreditSharing:kbl */
	if (IS_KBL_REVID(dev_priv, 0, KBL_REVID_B0))
		WA_SET_BIT(GAMT_CHKN_BIT_REG,
			   GAMT_CHKN_DISABLE_DYNAMIC_CREDIT_SHARING);

	/* WaDisableFenceDestinationToSLM:kbl (pre-prod) */
	if (IS_KBL_REVID(dev_priv, KBL_REVID_A0, KBL_REVID_A0))
		WA_SET_BIT_MASKED(HDC_CHICKEN0,
				  HDC_FENCE_DEST_SLM_DISABLE);

	/* WaToEnableHwFixForPushConstHWBug:kbl */
	if (IS_KBL_REVID(dev_priv, KBL_REVID_C0, REVID_FOREVER))
		WA_SET_BIT_MASKED(COMMON_SLICE_CHICKEN2,
				  GEN8_SBE_DISABLE_REPLAY_BUF_OPTIMIZATION);

	/* WaDisableGafsUnitClkGating:kbl */
	WA_SET_BIT(GEN7_UCGCTL4, GEN8_EU_GAUNIT_CLOCK_GATE_DISABLE);

	/* WaDisableSbeCacheDispatchPortSharing:kbl */
	WA_SET_BIT_MASKED(
		GEN7_HALF_SLICE_CHICKEN1,
		GEN7_SBE_SS_CACHE_DISPATCH_PORT_SHARING_DISABLE);

	/* WaInPlaceDecompressionHang:kbl */
	WA_SET_BIT(GEN9_GAMT_ECO_REG_RW_IA,
		   GAMT_ECO_ENABLE_IN_PLACE_DECOMPRESS);

	/* WaDisableLSQCROPERFforOCL:kbl */
	ret = wa_ring_whitelist_reg(engine, GEN8_L3SQCREG4);
	if (ret)
		return ret;

	return 0;
}

static int glk_init_workarounds(struct intel_engine_cs *engine)
{
	struct drm_i915_private *dev_priv = engine->i915;
	int ret;

	ret = gen9_init_workarounds(engine);
	if (ret)
		return ret;

	/* WA #0862: Userspace has to set "Barrier Mode" to avoid hangs. */
	ret = wa_ring_whitelist_reg(engine, GEN9_SLICE_COMMON_ECO_CHICKEN1);
	if (ret)
		return ret;

	/* WaToEnableHwFixForPushConstHWBug:glk */
	WA_SET_BIT_MASKED(COMMON_SLICE_CHICKEN2,
			  GEN8_SBE_DISABLE_REPLAY_BUF_OPTIMIZATION);

	return 0;
}

static int cfl_init_workarounds(struct intel_engine_cs *engine)
{
	struct drm_i915_private *dev_priv = engine->i915;
	int ret;

	ret = gen9_init_workarounds(engine);
	if (ret)
		return ret;

	/* WaEnableGapsTsvCreditFix:cfl */
	I915_WRITE(GEN8_GARBCNTL, (I915_READ(GEN8_GARBCNTL) |
				   GEN9_GAPS_TSV_CREDIT_DISABLE));

	/* WaToEnableHwFixForPushConstHWBug:cfl */
	WA_SET_BIT_MASKED(COMMON_SLICE_CHICKEN2,
			  GEN8_SBE_DISABLE_REPLAY_BUF_OPTIMIZATION);

	/* WaDisableGafsUnitClkGating:cfl */
	WA_SET_BIT(GEN7_UCGCTL4, GEN8_EU_GAUNIT_CLOCK_GATE_DISABLE);

	/* WaDisableSbeCacheDispatchPortSharing:cfl */
	WA_SET_BIT_MASKED(
		GEN7_HALF_SLICE_CHICKEN1,
		GEN7_SBE_SS_CACHE_DISPATCH_PORT_SHARING_DISABLE);

	/* WaInPlaceDecompressionHang:cfl */
	WA_SET_BIT(GEN9_GAMT_ECO_REG_RW_IA,
		   GAMT_ECO_ENABLE_IN_PLACE_DECOMPRESS);

	return 0;
}

int init_workarounds_ring(struct intel_engine_cs *engine)
{
	struct drm_i915_private *dev_priv = engine->i915;
	int err;

	WARN_ON(engine->id != RCS);

	dev_priv->workarounds.count = 0;
	dev_priv->workarounds.hw_whitelist_count[engine->id] = 0;

	if (IS_BROADWELL(dev_priv))
		err = bdw_init_workarounds(engine);
	else if (IS_CHERRYVIEW(dev_priv))
		err = chv_init_workarounds(engine);
	else if (IS_SKYLAKE(dev_priv))
		err =  skl_init_workarounds(engine);
	else if (IS_BROXTON(dev_priv))
		err = bxt_init_workarounds(engine);
	else if (IS_KABYLAKE(dev_priv))
		err = kbl_init_workarounds(engine);
	else if (IS_GEMINILAKE(dev_priv))
		err =  glk_init_workarounds(engine);
	else if (IS_COFFEELAKE(dev_priv))
		err = cfl_init_workarounds(engine);
	else
		err = 0;
	if (err)
		return err;

	DRM_DEBUG_DRIVER("%s: Number of context specific w/a: %d\n",
			 engine->name, dev_priv->workarounds.count);
	return 0;
}

int intel_ring_workarounds_emit(struct drm_i915_gem_request *req)
{
	struct i915_workarounds *w = &req->i915->workarounds;
	u32 *cs;
	int ret, i;

	if (w->count == 0)
		return 0;

	ret = req->engine->emit_flush(req, EMIT_BARRIER);
	if (ret)
		return ret;

	cs = intel_ring_begin(req, (w->count * 2 + 2));
	if (IS_ERR(cs))
		return PTR_ERR(cs);

	*cs++ = MI_LOAD_REGISTER_IMM(w->count);
	for (i = 0; i < w->count; i++) {
		*cs++ = i915_mmio_reg_offset(w->reg[i].addr);
		*cs++ = w->reg[i].value;
	}
	*cs++ = MI_NOOP;

	intel_ring_advance(req, cs);

	ret = req->engine->emit_flush(req, EMIT_BARRIER);
	if (ret)
		return ret;

	return 0;
}

>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
static bool ring_is_idle(struct intel_engine_cs *engine)
{
	struct drm_i915_private *dev_priv = engine->i915;
	bool idle = true;

<<<<<<< HEAD
	/* If the whole device is asleep, the engine must be idle */
	if (!intel_runtime_pm_get_if_in_use(dev_priv))
		return true;
=======
	intel_runtime_pm_get(dev_priv);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	/* First check that no commands are left in the ring */
	if ((I915_READ_HEAD(engine) & HEAD_ADDR) !=
	    (I915_READ_TAIL(engine) & TAIL_ADDR))
		idle = false;

	/* No bit for gen2, so assume the CS parser is idle */
	if (INTEL_GEN(dev_priv) > 2 && !(I915_READ_MODE(engine) & MODE_IDLE))
		idle = false;

	intel_runtime_pm_put(dev_priv);

	return idle;
}

/**
 * intel_engine_is_idle() - Report if the engine has finished process all work
 * @engine: the intel_engine_cs
 *
 * Return true if there are no requests pending, nothing left to be submitted
 * to hardware, and that the engine is idle.
 */
bool intel_engine_is_idle(struct intel_engine_cs *engine)
{
	struct drm_i915_private *dev_priv = engine->i915;

	/* More white lies, if wedged, hw state is inconsistent */
	if (i915_terminally_wedged(&dev_priv->gpu_error))
		return true;

	/* Any inflight/incomplete requests? */
	if (!i915_seqno_passed(intel_engine_get_seqno(engine),
			       intel_engine_last_submit(engine)))
		return false;

	if (I915_SELFTEST_ONLY(engine->breadcrumbs.mock))
		return true;

<<<<<<< HEAD
	/* Waiting to drain ELSP? */
	if (READ_ONCE(engine->execlists.active)) {
		struct tasklet_struct *t = &engine->execlists.tasklet;

		local_bh_disable();
		if (tasklet_trylock(t)) {
			/* Must wait for any GPU reset in progress. */
			if (__tasklet_is_enabled(t))
				t->func(t->data);
			tasklet_unlock(t);
		}
		local_bh_enable();

		if (READ_ONCE(engine->execlists.active))
			return false;
	}

	/* ELSP is empty, but there are ready requests? E.g. after reset */
	if (!RB_EMPTY_ROOT(&engine->execlists.queue.rb_root))
=======
	/* Interrupt/tasklet pending? */
	if (test_bit(ENGINE_IRQ_EXECLIST, &engine->irq_posted))
		return false;

	/* Both ports drained, no more ELSP submission? */
	if (port_request(&engine->execlist_port[0]))
		return false;

	/* ELSP is empty, but there are ready requests? */
	if (READ_ONCE(engine->execlist_first))
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
		return false;

	/* Ring stopped? */
	if (!ring_is_idle(engine))
		return false;

	return true;
}

bool intel_engines_are_idle(struct drm_i915_private *dev_priv)
{
	struct intel_engine_cs *engine;
	enum intel_engine_id id;

<<<<<<< HEAD
	/*
	 * If the driver is wedged, HW state may be very inconsistent and
=======
	if (READ_ONCE(dev_priv->gt.active_requests))
		return false;

	/* If the driver is wedged, HW state may be very inconsistent and
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	 * report that it is still busy, even though we have stopped using it.
	 */
	if (i915_terminally_wedged(&dev_priv->gpu_error))
		return true;

	for_each_engine(engine, dev_priv, id) {
		if (!intel_engine_is_idle(engine))
			return false;
	}

	return true;
}

<<<<<<< HEAD
/**
 * intel_engine_has_kernel_context:
 * @engine: the engine
 *
 * Returns true if the last context to be executed on this engine, or has been
 * executed if the engine is already idle, is the kernel context
 * (#i915.kernel_context).
 */
bool intel_engine_has_kernel_context(const struct intel_engine_cs *engine)
{
	const struct intel_context *kernel_context =
		to_intel_context(engine->i915->kernel_context, engine);
	struct i915_request *rq;

	lockdep_assert_held(&engine->i915->drm.struct_mutex);

	/*
	 * Check the last context seen by the engine. If active, it will be
	 * the last request that remains in the timeline. When idle, it is
	 * the last executed context as tracked by retirement.
	 */
	rq = __i915_gem_active_peek(&engine->timeline.last_request);
	if (rq)
		return rq->hw_context == kernel_context;
	else
		return engine->last_retired_context == kernel_context;
}

=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
void intel_engines_reset_default_submission(struct drm_i915_private *i915)
{
	struct intel_engine_cs *engine;
	enum intel_engine_id id;

	for_each_engine(engine, i915, id)
		engine->set_default_submission(engine);
}

<<<<<<< HEAD
/**
 * intel_engines_sanitize: called after the GPU has lost power
 * @i915: the i915 device
 *
 * Anytime we reset the GPU, either with an explicit GPU reset or through a
 * PCI power cycle, the GPU loses state and we must reset our state tracking
 * to match. Note that calling intel_engines_sanitize() if the GPU has not
 * been reset results in much confusion!
 */
void intel_engines_sanitize(struct drm_i915_private *i915)
{
	struct intel_engine_cs *engine;
	enum intel_engine_id id;

	GEM_TRACE("\n");

	for_each_engine(engine, i915, id) {
		if (engine->reset.reset)
			engine->reset.reset(engine, NULL);
	}
}

/**
 * intel_engines_park: called when the GT is transitioning from busy->idle
 * @i915: the i915 device
 *
 * The GT is now idle and about to go to sleep (maybe never to wake again?).
 * Time for us to tidy and put away our toys (release resources back to the
 * system).
 */
void intel_engines_park(struct drm_i915_private *i915)
=======
void intel_engines_mark_idle(struct drm_i915_private *i915)
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
{
	struct intel_engine_cs *engine;
	enum intel_engine_id id;

	for_each_engine(engine, i915, id) {
<<<<<<< HEAD
		/* Flush the residual irq tasklets first. */
		intel_engine_disarm_breadcrumbs(engine);
		tasklet_kill(&engine->execlists.tasklet);

		/*
		 * We are committed now to parking the engines, make sure there
		 * will be no more interrupts arriving later and the engines
		 * are truly idle.
		 */
		if (wait_for(intel_engine_is_idle(engine), 10)) {
			struct drm_printer p = drm_debug_printer(__func__);

			dev_err(i915->drm.dev,
				"%s is not idle before parking\n",
				engine->name);
			intel_engine_dump(engine, &p, NULL);
		}

		/* Must be reset upon idling, or we may miss the busy wakeup. */
		GEM_BUG_ON(engine->execlists.queue_priority != INT_MIN);

		if (engine->park)
			engine->park(engine);

		if (engine->pinned_default_state) {
			i915_gem_object_unpin_map(engine->default_state);
			engine->pinned_default_state = NULL;
		}

		i915_gem_batch_pool_fini(&engine->batch_pool);
		engine->execlists.no_priolist = false;
	}
}

/**
 * intel_engines_unpark: called when the GT is transitioning from idle->busy
 * @i915: the i915 device
 *
 * The GT was idle and now about to fire up with some new user requests.
 */
void intel_engines_unpark(struct drm_i915_private *i915)
{
	struct intel_engine_cs *engine;
	enum intel_engine_id id;

	for_each_engine(engine, i915, id) {
		void *map;

		/* Pin the default state for fast resets from atomic context. */
		map = NULL;
		if (engine->default_state)
			map = i915_gem_object_pin_map(engine->default_state,
						      I915_MAP_WB);
		if (!IS_ERR_OR_NULL(map))
			engine->pinned_default_state = map;

		if (engine->unpark)
			engine->unpark(engine);

		intel_engine_init_hangcheck(engine);
	}
}

/**
 * intel_engine_lost_context: called when the GPU is reset into unknown state
 * @engine: the engine
 *
 * We have either reset the GPU or otherwise about to lose state tracking of
 * the current GPU logical state (e.g. suspend). On next use, it is therefore
 * imperative that we make no presumptions about the current state and load
 * from scratch.
 */
void intel_engine_lost_context(struct intel_engine_cs *engine)
{
	struct intel_context *ce;

	lockdep_assert_held(&engine->i915->drm.struct_mutex);

	ce = fetch_and_zero(&engine->last_retired_context);
	if (ce)
		intel_context_unpin(ce);
}

bool intel_engine_can_store_dword(struct intel_engine_cs *engine)
{
	switch (INTEL_GEN(engine->i915)) {
	case 2:
		return false; /* uses physical not virtual addresses */
	case 3:
		/* maybe only uses physical not virtual addresses */
		return !(IS_I915G(engine->i915) || IS_I915GM(engine->i915));
	case 6:
		return engine->class != VIDEO_DECODE_CLASS; /* b0rked */
	default:
		return true;
	}
}

unsigned int intel_engines_has_context_isolation(struct drm_i915_private *i915)
{
	struct intel_engine_cs *engine;
	enum intel_engine_id id;
	unsigned int which;

	which = 0;
	for_each_engine(engine, i915, id)
		if (engine->default_state)
			which |= BIT(engine->uabi_class);

	return which;
}

static int print_sched_attr(struct drm_i915_private *i915,
			    const struct i915_sched_attr *attr,
			    char *buf, int x, int len)
{
	if (attr->priority == I915_PRIORITY_INVALID)
		return x;

	x += snprintf(buf + x, len - x,
		      " prio=%d", attr->priority);

	return x;
}

static void print_request(struct drm_printer *m,
			  struct i915_request *rq,
			  const char *prefix)
{
	const char *name = rq->fence.ops->get_timeline_name(&rq->fence);
	char buf[80] = "";
	int x = 0;

	x = print_sched_attr(rq->i915, &rq->sched.attr, buf, x, sizeof(buf));

	drm_printf(m, "%s%x%s [%llx:%x]%s @ %dms: %s\n",
		   prefix,
		   rq->global_seqno,
		   i915_request_completed(rq) ? "!" : "",
		   rq->fence.context, rq->fence.seqno,
		   buf,
		   jiffies_to_msecs(jiffies - rq->emitted_jiffies),
		   name);
}

static void hexdump(struct drm_printer *m, const void *buf, size_t len)
{
	const size_t rowsize = 8 * sizeof(u32);
	const void *prev = NULL;
	bool skip = false;
	size_t pos;

	for (pos = 0; pos < len; pos += rowsize) {
		char line[128];

		if (prev && !memcmp(prev, buf + pos, rowsize)) {
			if (!skip) {
				drm_printf(m, "*\n");
				skip = true;
			}
			continue;
		}

		WARN_ON_ONCE(hex_dump_to_buffer(buf + pos, len - pos,
						rowsize, sizeof(u32),
						line, sizeof(line),
						false) >= sizeof(line));
		drm_printf(m, "[%04zx] %s\n", pos, line);

		prev = buf + pos;
		skip = false;
	}
}

static void intel_engine_print_registers(const struct intel_engine_cs *engine,
					 struct drm_printer *m)
{
	struct drm_i915_private *dev_priv = engine->i915;
	const struct intel_engine_execlists * const execlists =
		&engine->execlists;
	u64 addr;

	if (engine->id == RCS && IS_GEN(dev_priv, 4, 7))
		drm_printf(m, "\tCCID: 0x%08x\n", I915_READ(CCID));
	drm_printf(m, "\tRING_START: 0x%08x\n",
		   I915_READ(RING_START(engine->mmio_base)));
	drm_printf(m, "\tRING_HEAD:  0x%08x\n",
		   I915_READ(RING_HEAD(engine->mmio_base)) & HEAD_ADDR);
	drm_printf(m, "\tRING_TAIL:  0x%08x\n",
		   I915_READ(RING_TAIL(engine->mmio_base)) & TAIL_ADDR);
	drm_printf(m, "\tRING_CTL:   0x%08x%s\n",
		   I915_READ(RING_CTL(engine->mmio_base)),
		   I915_READ(RING_CTL(engine->mmio_base)) & (RING_WAIT | RING_WAIT_SEMAPHORE) ? " [waiting]" : "");
	if (INTEL_GEN(engine->i915) > 2) {
		drm_printf(m, "\tRING_MODE:  0x%08x%s\n",
			   I915_READ(RING_MI_MODE(engine->mmio_base)),
			   I915_READ(RING_MI_MODE(engine->mmio_base)) & (MODE_IDLE) ? " [idle]" : "");
	}

	if (INTEL_GEN(dev_priv) >= 6) {
		drm_printf(m, "\tRING_IMR: %08x\n", I915_READ_IMR(engine));
	}

	if (HAS_LEGACY_SEMAPHORES(dev_priv)) {
		drm_printf(m, "\tSYNC_0: 0x%08x\n",
			   I915_READ(RING_SYNC_0(engine->mmio_base)));
		drm_printf(m, "\tSYNC_1: 0x%08x\n",
			   I915_READ(RING_SYNC_1(engine->mmio_base)));
		if (HAS_VEBOX(dev_priv))
			drm_printf(m, "\tSYNC_2: 0x%08x\n",
				   I915_READ(RING_SYNC_2(engine->mmio_base)));
	}

	addr = intel_engine_get_active_head(engine);
	drm_printf(m, "\tACTHD:  0x%08x_%08x\n",
		   upper_32_bits(addr), lower_32_bits(addr));
	addr = intel_engine_get_last_batch_head(engine);
	drm_printf(m, "\tBBADDR: 0x%08x_%08x\n",
		   upper_32_bits(addr), lower_32_bits(addr));
	if (INTEL_GEN(dev_priv) >= 8)
		addr = I915_READ64_2x32(RING_DMA_FADD(engine->mmio_base),
					RING_DMA_FADD_UDW(engine->mmio_base));
	else if (INTEL_GEN(dev_priv) >= 4)
		addr = I915_READ(RING_DMA_FADD(engine->mmio_base));
	else
		addr = I915_READ(DMA_FADD_I8XX);
	drm_printf(m, "\tDMA_FADDR: 0x%08x_%08x\n",
		   upper_32_bits(addr), lower_32_bits(addr));
	if (INTEL_GEN(dev_priv) >= 4) {
		drm_printf(m, "\tIPEIR: 0x%08x\n",
			   I915_READ(RING_IPEIR(engine->mmio_base)));
		drm_printf(m, "\tIPEHR: 0x%08x\n",
			   I915_READ(RING_IPEHR(engine->mmio_base)));
	} else {
		drm_printf(m, "\tIPEIR: 0x%08x\n", I915_READ(IPEIR));
		drm_printf(m, "\tIPEHR: 0x%08x\n", I915_READ(IPEHR));
	}

	if (HAS_EXECLISTS(dev_priv)) {
		const u32 *hws = &engine->status_page.page_addr[I915_HWS_CSB_BUF0_INDEX];
		u32 ptr, read, write;
		unsigned int idx;

		drm_printf(m, "\tExeclist status: 0x%08x %08x\n",
			   I915_READ(RING_EXECLIST_STATUS_LO(engine)),
			   I915_READ(RING_EXECLIST_STATUS_HI(engine)));

		ptr = I915_READ(RING_CONTEXT_STATUS_PTR(engine));
		read = GEN8_CSB_READ_PTR(ptr);
		write = GEN8_CSB_WRITE_PTR(ptr);
		drm_printf(m, "\tExeclist CSB read %d [%d cached], write %d [%d from hws], tasklet queued? %s (%s)\n",
			   read, execlists->csb_head,
			   write,
			   intel_read_status_page(engine, intel_hws_csb_write_index(engine->i915)),
			   yesno(test_bit(TASKLET_STATE_SCHED,
					  &engine->execlists.tasklet.state)),
			   enableddisabled(!atomic_read(&engine->execlists.tasklet.count)));
		if (read >= GEN8_CSB_ENTRIES)
			read = 0;
		if (write >= GEN8_CSB_ENTRIES)
			write = 0;
		if (read > write)
			write += GEN8_CSB_ENTRIES;
		while (read < write) {
			idx = ++read % GEN8_CSB_ENTRIES;
			drm_printf(m, "\tExeclist CSB[%d]: 0x%08x [0x%08x in hwsp], context: %d [%d in hwsp]\n",
				   idx,
				   I915_READ(RING_CONTEXT_STATUS_BUF_LO(engine, idx)),
				   hws[idx * 2],
				   I915_READ(RING_CONTEXT_STATUS_BUF_HI(engine, idx)),
				   hws[idx * 2 + 1]);
		}

		rcu_read_lock();
		for (idx = 0; idx < execlists_num_ports(execlists); idx++) {
			struct i915_request *rq;
			unsigned int count;

			rq = port_unpack(&execlists->port[idx], &count);
			if (rq) {
				char hdr[80];

				snprintf(hdr, sizeof(hdr),
					 "\t\tELSP[%d] count=%d, ring->start=%08x, rq: ",
					 idx, count,
					 i915_ggtt_offset(rq->ring->vma));
				print_request(m, rq, hdr);
			} else {
				drm_printf(m, "\t\tELSP[%d] idle\n", idx);
			}
		}
		drm_printf(m, "\t\tHW active? 0x%x\n", execlists->active);
		rcu_read_unlock();
	} else if (INTEL_GEN(dev_priv) > 6) {
		drm_printf(m, "\tPP_DIR_BASE: 0x%08x\n",
			   I915_READ(RING_PP_DIR_BASE(engine)));
		drm_printf(m, "\tPP_DIR_BASE_READ: 0x%08x\n",
			   I915_READ(RING_PP_DIR_BASE_READ(engine)));
		drm_printf(m, "\tPP_DIR_DCLV: 0x%08x\n",
			   I915_READ(RING_PP_DIR_DCLV(engine)));
	}
}

static void print_request_ring(struct drm_printer *m, struct i915_request *rq)
{
	void *ring;
	int size;

	drm_printf(m,
		   "[head %04x, postfix %04x, tail %04x, batch 0x%08x_%08x]:\n",
		   rq->head, rq->postfix, rq->tail,
		   rq->batch ? upper_32_bits(rq->batch->node.start) : ~0u,
		   rq->batch ? lower_32_bits(rq->batch->node.start) : ~0u);

	size = rq->tail - rq->head;
	if (rq->tail < rq->head)
		size += rq->ring->size;

	ring = kmalloc(size, GFP_ATOMIC);
	if (ring) {
		const void *vaddr = rq->ring->vaddr;
		unsigned int head = rq->head;
		unsigned int len = 0;

		if (rq->tail < head) {
			len = rq->ring->size - head;
			memcpy(ring, vaddr + head, len);
			head = 0;
		}
		memcpy(ring + len, vaddr + head, size - len);

		hexdump(m, ring, size);
		kfree(ring);
	}
}

void intel_engine_dump(struct intel_engine_cs *engine,
		       struct drm_printer *m,
		       const char *header, ...)
{
	const int MAX_REQUESTS_TO_SHOW = 8;
	struct intel_breadcrumbs * const b = &engine->breadcrumbs;
	const struct intel_engine_execlists * const execlists = &engine->execlists;
	struct i915_gpu_error * const error = &engine->i915->gpu_error;
	struct i915_request *rq, *last;
	unsigned long flags;
	struct rb_node *rb;
	int count;

	if (header) {
		va_list ap;

		va_start(ap, header);
		drm_vprintf(m, header, &ap);
		va_end(ap);
	}

	if (i915_terminally_wedged(&engine->i915->gpu_error))
		drm_printf(m, "*** WEDGED ***\n");

	drm_printf(m, "\tcurrent seqno %x, last %x, hangcheck %x [%d ms]\n",
		   intel_engine_get_seqno(engine),
		   intel_engine_last_submit(engine),
		   engine->hangcheck.seqno,
		   jiffies_to_msecs(jiffies - engine->hangcheck.action_timestamp));
	drm_printf(m, "\tReset count: %d (global %d)\n",
		   i915_reset_engine_count(error, engine),
		   i915_reset_count(error));

	rcu_read_lock();

	drm_printf(m, "\tRequests:\n");

	rq = list_first_entry(&engine->timeline.requests,
			      struct i915_request, link);
	if (&rq->link != &engine->timeline.requests)
		print_request(m, rq, "\t\tfirst  ");

	rq = list_last_entry(&engine->timeline.requests,
			     struct i915_request, link);
	if (&rq->link != &engine->timeline.requests)
		print_request(m, rq, "\t\tlast   ");

	rq = i915_gem_find_active_request(engine);
	if (rq) {
		print_request(m, rq, "\t\tactive ");

		drm_printf(m, "\t\tring->start:  0x%08x\n",
			   i915_ggtt_offset(rq->ring->vma));
		drm_printf(m, "\t\tring->head:   0x%08x\n",
			   rq->ring->head);
		drm_printf(m, "\t\tring->tail:   0x%08x\n",
			   rq->ring->tail);
		drm_printf(m, "\t\tring->emit:   0x%08x\n",
			   rq->ring->emit);
		drm_printf(m, "\t\tring->space:  0x%08x\n",
			   rq->ring->space);

		print_request_ring(m, rq);
	}

	rcu_read_unlock();

	if (intel_runtime_pm_get_if_in_use(engine->i915)) {
		intel_engine_print_registers(engine, m);
		intel_runtime_pm_put(engine->i915);
	} else {
		drm_printf(m, "\tDevice is asleep; skipping register dump\n");
	}

	local_irq_save(flags);
	spin_lock(&engine->timeline.lock);

	last = NULL;
	count = 0;
	list_for_each_entry(rq, &engine->timeline.requests, link) {
		if (count++ < MAX_REQUESTS_TO_SHOW - 1)
			print_request(m, rq, "\t\tE ");
		else
			last = rq;
	}
	if (last) {
		if (count > MAX_REQUESTS_TO_SHOW) {
			drm_printf(m,
				   "\t\t...skipping %d executing requests...\n",
				   count - MAX_REQUESTS_TO_SHOW);
		}
		print_request(m, last, "\t\tE ");
	}

	last = NULL;
	count = 0;
	drm_printf(m, "\t\tQueue priority: %d\n", execlists->queue_priority);
	for (rb = rb_first_cached(&execlists->queue); rb; rb = rb_next(rb)) {
		struct i915_priolist *p =
			rb_entry(rb, typeof(*p), node);

		list_for_each_entry(rq, &p->requests, sched.link) {
			if (count++ < MAX_REQUESTS_TO_SHOW - 1)
				print_request(m, rq, "\t\tQ ");
			else
				last = rq;
		}
	}
	if (last) {
		if (count > MAX_REQUESTS_TO_SHOW) {
			drm_printf(m,
				   "\t\t...skipping %d queued requests...\n",
				   count - MAX_REQUESTS_TO_SHOW);
		}
		print_request(m, last, "\t\tQ ");
	}

	spin_unlock(&engine->timeline.lock);

	spin_lock(&b->rb_lock);
	for (rb = rb_first(&b->waiters); rb; rb = rb_next(rb)) {
		struct intel_wait *w = rb_entry(rb, typeof(*w), node);

		drm_printf(m, "\t%s [%d] waiting for %x\n",
			   w->tsk->comm, w->tsk->pid, w->seqno);
	}
	spin_unlock(&b->rb_lock);
	local_irq_restore(flags);

	drm_printf(m, "IRQ? 0x%lx (breadcrumbs? %s)\n",
		   engine->irq_posted,
		   yesno(test_bit(ENGINE_IRQ_BREADCRUMB,
				  &engine->irq_posted)));

	drm_printf(m, "HWSP:\n");
	hexdump(m, engine->status_page.page_addr, PAGE_SIZE);

	drm_printf(m, "Idle? %s\n", yesno(intel_engine_is_idle(engine)));
}

static u8 user_class_map[] = {
	[I915_ENGINE_CLASS_RENDER] = RENDER_CLASS,
	[I915_ENGINE_CLASS_COPY] = COPY_ENGINE_CLASS,
	[I915_ENGINE_CLASS_VIDEO] = VIDEO_DECODE_CLASS,
	[I915_ENGINE_CLASS_VIDEO_ENHANCE] = VIDEO_ENHANCEMENT_CLASS,
};

struct intel_engine_cs *
intel_engine_lookup_user(struct drm_i915_private *i915, u8 class, u8 instance)
{
	if (class >= ARRAY_SIZE(user_class_map))
		return NULL;

	class = user_class_map[class];

	GEM_BUG_ON(class > MAX_ENGINE_CLASS);

	if (instance > MAX_ENGINE_INSTANCE)
		return NULL;

	return i915->engine_class[class][instance];
}

/**
 * intel_enable_engine_stats() - Enable engine busy tracking on engine
 * @engine: engine to enable stats collection
 *
 * Start collecting the engine busyness data for @engine.
 *
 * Returns 0 on success or a negative error code.
 */
int intel_enable_engine_stats(struct intel_engine_cs *engine)
{
	struct intel_engine_execlists *execlists = &engine->execlists;
	unsigned long flags;
	int err = 0;

	if (!intel_engine_supports_stats(engine))
		return -ENODEV;

	spin_lock_irqsave(&engine->timeline.lock, flags);
	write_seqlock(&engine->stats.lock);

	if (unlikely(engine->stats.enabled == ~0)) {
		err = -EBUSY;
		goto unlock;
	}

	if (engine->stats.enabled++ == 0) {
		const struct execlist_port *port = execlists->port;
		unsigned int num_ports = execlists_num_ports(execlists);

		engine->stats.enabled_at = ktime_get();

		/* XXX submission method oblivious? */
		while (num_ports-- && port_isset(port)) {
			engine->stats.active++;
			port++;
		}

		if (engine->stats.active)
			engine->stats.start = engine->stats.enabled_at;
	}

unlock:
	write_sequnlock(&engine->stats.lock);
	spin_unlock_irqrestore(&engine->timeline.lock, flags);

	return err;
}

static ktime_t __intel_engine_get_busy_time(struct intel_engine_cs *engine)
{
	ktime_t total = engine->stats.total;

	/*
	 * If the engine is executing something at the moment
	 * add it to the total.
	 */
	if (engine->stats.active)
		total = ktime_add(total,
				  ktime_sub(ktime_get(), engine->stats.start));

	return total;
}

/**
 * intel_engine_get_busy_time() - Return current accumulated engine busyness
 * @engine: engine to report on
 *
 * Returns accumulated time @engine was busy since engine stats were enabled.
 */
ktime_t intel_engine_get_busy_time(struct intel_engine_cs *engine)
{
	unsigned int seq;
	ktime_t total;

	do {
		seq = read_seqbegin(&engine->stats.lock);
		total = __intel_engine_get_busy_time(engine);
	} while (read_seqretry(&engine->stats.lock, seq));

	return total;
}

/**
 * intel_disable_engine_stats() - Disable engine busy tracking on engine
 * @engine: engine to disable stats collection
 *
 * Stops collecting the engine busyness data for @engine.
 */
void intel_disable_engine_stats(struct intel_engine_cs *engine)
{
	unsigned long flags;

	if (!intel_engine_supports_stats(engine))
		return;

	write_seqlock_irqsave(&engine->stats.lock, flags);
	WARN_ON_ONCE(engine->stats.enabled == 0);
	if (--engine->stats.enabled == 0) {
		engine->stats.total = __intel_engine_get_busy_time(engine);
		engine->stats.active = 0;
	}
	write_sequnlock_irqrestore(&engine->stats.lock, flags);
}

#if IS_ENABLED(CONFIG_DRM_I915_SELFTEST)
#include "selftests/mock_engine.c"
#include "selftests/intel_engine_cs.c"
=======
		intel_engine_disarm_breadcrumbs(engine);
		i915_gem_batch_pool_fini(&engine->batch_pool);
		tasklet_kill(&engine->irq_tasklet);
		engine->no_priolist = false;
	}
}

#if IS_ENABLED(CONFIG_DRM_I915_SELFTEST)
#include "selftests/mock_engine.c"
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
#endif
