<<<<<<< HEAD
/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (C) 2015-2018 Etnaviv Project
=======
/*
 * Copyright (C) 2015 Etnaviv Project
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 as published by
 * the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
 */

#ifndef __ETNAVIV_GPU_H__
#define __ETNAVIV_GPU_H__

#include <linux/clk.h>
#include <linux/regulator/consumer.h>

<<<<<<< HEAD
#include "etnaviv_cmdbuf.h"
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
#include "etnaviv_drv.h"

struct etnaviv_gem_submit;
struct etnaviv_vram_mapping;

struct etnaviv_chip_identity {
	/* Chip model. */
	u32 model;

	/* Revision value.*/
	u32 revision;

	/* Supported feature fields. */
	u32 features;

	/* Supported minor feature fields. */
	u32 minor_features0;
<<<<<<< HEAD
	u32 minor_features1;
	u32 minor_features2;
	u32 minor_features3;
	u32 minor_features4;
	u32 minor_features5;
	u32 minor_features6;
	u32 minor_features7;
	u32 minor_features8;
	u32 minor_features9;
	u32 minor_features10;
	u32 minor_features11;
=======

	/* Supported minor feature 1 fields. */
	u32 minor_features1;

	/* Supported minor feature 2 fields. */
	u32 minor_features2;

	/* Supported minor feature 3 fields. */
	u32 minor_features3;

	/* Supported minor feature 4 fields. */
	u32 minor_features4;

	/* Supported minor feature 5 fields. */
	u32 minor_features5;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	/* Number of streams supported. */
	u32 stream_count;

	/* Total number of temporary registers per thread. */
	u32 register_max;

	/* Maximum number of threads. */
	u32 thread_count;

	/* Number of shader cores. */
	u32 shader_core_count;

	/* Size of the vertex cache. */
	u32 vertex_cache_size;

	/* Number of entries in the vertex output buffer. */
	u32 vertex_output_buffer_size;

	/* Number of pixel pipes. */
	u32 pixel_pipes;

	/* Number of instructions. */
	u32 instruction_count;

	/* Number of constants. */
	u32 num_constants;

	/* Buffer size */
	u32 buffer_size;

	/* Number of varyings */
	u8 varyings_count;
};

<<<<<<< HEAD
enum etnaviv_sec_mode {
	ETNA_SEC_NONE = 0,
	ETNA_SEC_KERNEL,
	ETNA_SEC_TZ
};

struct etnaviv_event {
	struct dma_fence *fence;
	struct etnaviv_gem_submit *submit;

	void (*sync_point)(struct etnaviv_gpu *gpu, struct etnaviv_event *event);
=======
struct etnaviv_event {
	bool used;
	struct dma_fence *fence;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
};

struct etnaviv_cmdbuf_suballoc;
struct etnaviv_cmdbuf;

<<<<<<< HEAD
#define ETNA_NR_EVENTS 30

=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
struct etnaviv_gpu {
	struct drm_device *drm;
	struct thermal_cooling_device *cooling;
	struct device *dev;
	struct mutex lock;
	struct etnaviv_chip_identity identity;
<<<<<<< HEAD
	enum etnaviv_sec_mode sec_mode;
	struct etnaviv_file_private *lastctx;
	struct workqueue_struct *wq;
	struct drm_gpu_scheduler sched;

	/* 'ring'-buffer: */
	struct etnaviv_cmdbuf buffer;
=======
	struct etnaviv_file_private *lastctx;
	bool switch_context;

	/* 'ring'-buffer: */
	struct etnaviv_cmdbuf *buffer;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	int exec_state;

	/* bus base address of memory  */
	u32 memory_base;

	/* event management: */
<<<<<<< HEAD
	DECLARE_BITMAP(event_bitmap, ETNA_NR_EVENTS);
	struct etnaviv_event event[ETNA_NR_EVENTS];
	struct completion event_free;
	spinlock_t event_spinlock;

	u32 idle_mask;

	/* Fencing support */
	struct mutex fence_lock;
	struct idr fence_idr;
	u32 next_fence;
	u32 active_fence;
	u32 completed_fence;
=======
	struct etnaviv_event event[30];
	struct completion event_free;
	spinlock_t event_spinlock;

	/* list of currently in-flight command buffers */
	struct list_head active_cmd_list;

	u32 idle_mask;

	/* Fencing support */
	u32 next_fence;
	u32 active_fence;
	u32 completed_fence;
	u32 retired_fence;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	wait_queue_head_t fence_event;
	u64 fence_context;
	spinlock_t fence_spinlock;

<<<<<<< HEAD
	/* worker for handling 'sync' points: */
	struct work_struct sync_point_work;
	int sync_point_event;

	/* hang detection */
	u32 hangcheck_dma_addr;
=======
	/* worker for handling active-list retiring: */
	struct work_struct retire_work;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	void __iomem *mmio;
	int irq;

	struct etnaviv_iommu *mmu;
	struct etnaviv_cmdbuf_suballoc *cmdbuf_suballoc;
<<<<<<< HEAD

	/* Power Control: */
	struct clk *clk_bus;
	struct clk *clk_reg;
	struct clk *clk_core;
	struct clk *clk_shader;

=======
	unsigned int flush_seq;

	/* Power Control: */
	struct clk *clk_bus;
	struct clk *clk_core;
	struct clk *clk_shader;

	/* Hang Detction: */
#define DRM_ETNAVIV_HANGCHECK_PERIOD 500 /* in ms */
#define DRM_ETNAVIV_HANGCHECK_JIFFIES msecs_to_jiffies(DRM_ETNAVIV_HANGCHECK_PERIOD)
	struct timer_list hangcheck_timer;
	u32 hangcheck_fence;
	u32 hangcheck_dma_addr;
	struct work_struct recover_work;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	unsigned int freq_scale;
	unsigned long base_rate_core;
	unsigned long base_rate_shader;
};

static inline void gpu_write(struct etnaviv_gpu *gpu, u32 reg, u32 data)
{
<<<<<<< HEAD
	writel(data, gpu->mmio + reg);
=======
	etnaviv_writel(data, gpu->mmio + reg);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
}

static inline u32 gpu_read(struct etnaviv_gpu *gpu, u32 reg)
{
<<<<<<< HEAD
	return readl(gpu->mmio + reg);
=======
	return etnaviv_readl(gpu->mmio + reg);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
}

static inline bool fence_completed(struct etnaviv_gpu *gpu, u32 fence)
{
	return fence_after_eq(gpu->completed_fence, fence);
}

<<<<<<< HEAD
int etnaviv_gpu_get_param(struct etnaviv_gpu *gpu, u32 param, u64 *value);

int etnaviv_gpu_init(struct etnaviv_gpu *gpu);
bool etnaviv_fill_identity_from_hwdb(struct etnaviv_gpu *gpu);
=======
static inline bool fence_retired(struct etnaviv_gpu *gpu, u32 fence)
{
	return fence_after_eq(gpu->retired_fence, fence);
}

int etnaviv_gpu_get_param(struct etnaviv_gpu *gpu, u32 param, u64 *value);

int etnaviv_gpu_init(struct etnaviv_gpu *gpu);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

#ifdef CONFIG_DEBUG_FS
int etnaviv_gpu_debugfs(struct etnaviv_gpu *gpu, struct seq_file *m);
#endif

<<<<<<< HEAD
void etnaviv_gpu_recover_hang(struct etnaviv_gpu *gpu);
=======
int etnaviv_gpu_fence_sync_obj(struct etnaviv_gem_object *etnaviv_obj,
	unsigned int context, bool exclusive, bool implicit);

>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
void etnaviv_gpu_retire(struct etnaviv_gpu *gpu);
int etnaviv_gpu_wait_fence_interruptible(struct etnaviv_gpu *gpu,
	u32 fence, struct timespec *timeout);
int etnaviv_gpu_wait_obj_inactive(struct etnaviv_gpu *gpu,
	struct etnaviv_gem_object *etnaviv_obj, struct timespec *timeout);
<<<<<<< HEAD
struct dma_fence *etnaviv_gpu_submit(struct etnaviv_gem_submit *submit);
=======
int etnaviv_gpu_submit(struct etnaviv_gpu *gpu,
	struct etnaviv_gem_submit *submit, struct etnaviv_cmdbuf *cmdbuf);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
int etnaviv_gpu_pm_get_sync(struct etnaviv_gpu *gpu);
void etnaviv_gpu_pm_put(struct etnaviv_gpu *gpu);
int etnaviv_gpu_wait_idle(struct etnaviv_gpu *gpu, unsigned int timeout_ms);
void etnaviv_gpu_start_fe(struct etnaviv_gpu *gpu, u32 address, u16 prefetch);

extern struct platform_driver etnaviv_gpu_driver;

#endif /* __ETNAVIV_GPU_H__ */
