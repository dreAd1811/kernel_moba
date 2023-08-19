<<<<<<< HEAD
// SPDX-License-Identifier: GPL-2.0+
/*
 * vsp1_dl.c  --  R-Car VSP1 Display List
=======
/*
 * vsp1_dl.h  --  R-Car VSP1 Display List
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
 *
 * Copyright (C) 2015 Renesas Corporation
 *
 * Contact: Laurent Pinchart (laurent.pinchart@ideasonboard.com)
<<<<<<< HEAD
=======
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
 */

#include <linux/device.h>
#include <linux/dma-mapping.h>
#include <linux/gfp.h>
<<<<<<< HEAD
#include <linux/refcount.h>
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
#include <linux/slab.h>
#include <linux/workqueue.h>

#include "vsp1.h"
#include "vsp1_dl.h"

#define VSP1_DL_NUM_ENTRIES		256

#define VSP1_DLH_INT_ENABLE		(1 << 1)
#define VSP1_DLH_AUTO_START		(1 << 0)

<<<<<<< HEAD
#define VSP1_DLH_EXT_PRE_CMD_EXEC	(1 << 9)
#define VSP1_DLH_EXT_POST_CMD_EXEC	(1 << 8)

struct vsp1_dl_header_list {
	u32 num_bytes;
	u32 addr;
} __packed;
=======
struct vsp1_dl_header_list {
	u32 num_bytes;
	u32 addr;
} __attribute__((__packed__));
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

struct vsp1_dl_header {
	u32 num_lists;
	struct vsp1_dl_header_list lists[8];
	u32 next_header;
	u32 flags;
<<<<<<< HEAD
} __packed;

/**
 * struct vsp1_dl_ext_header - Extended display list header
 * @padding: padding zero bytes for alignment
 * @pre_ext_dl_num_cmd: number of pre-extended command bodies to parse
 * @flags: enables or disables execution of the pre and post command
 * @pre_ext_dl_plist: start address of pre-extended display list bodies
 * @post_ext_dl_num_cmd: number of post-extended command bodies to parse
 * @post_ext_dl_plist: start address of post-extended display list bodies
 */
struct vsp1_dl_ext_header {
	u32 padding;

	/*
	 * The datasheet represents flags as stored before pre_ext_dl_num_cmd,
	 * expecting 32-bit accesses. The flags are appropriate to the whole
	 * header, not just the pre_ext command, and thus warrant being
	 * separated out. Due to byte ordering, and representing as 16 bit
	 * values here, the flags must be positioned after the
	 * pre_ext_dl_num_cmd.
	 */
	u16 pre_ext_dl_num_cmd;
	u16 flags;
	u32 pre_ext_dl_plist;

	u32 post_ext_dl_num_cmd;
	u32 post_ext_dl_plist;
} __packed;

struct vsp1_dl_header_extended {
	struct vsp1_dl_header header;
	struct vsp1_dl_ext_header ext;
} __packed;
=======
} __attribute__((__packed__));
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

struct vsp1_dl_entry {
	u32 addr;
	u32 data;
<<<<<<< HEAD
} __packed;

/**
 * struct vsp1_pre_ext_dl_body - Pre Extended Display List Body
 * @opcode: Extended display list command operation code
 * @flags: Pre-extended command flags. These are specific to each command
 * @address_set: Source address set pointer. Must have 16-byte alignment
 * @reserved: Zero bits for alignment.
 */
struct vsp1_pre_ext_dl_body {
	u32 opcode;
	u32 flags;
	u32 address_set;
	u32 reserved;
} __packed;
=======
} __attribute__((__packed__));
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/**
 * struct vsp1_dl_body - Display list body
 * @list: entry in the display list list of bodies
<<<<<<< HEAD
 * @free: entry in the pool free body list
 * @refcnt: reference tracking for the body
 * @pool: pool to which this body belongs
=======
 * @vsp1: the VSP1 device
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
 * @entries: array of entries
 * @dma: DMA address of the entries
 * @size: size of the DMA memory in bytes
 * @num_entries: number of stored entries
<<<<<<< HEAD
 * @max_entries: number of entries available
 */
struct vsp1_dl_body {
	struct list_head list;
	struct list_head free;

	refcount_t refcnt;

	struct vsp1_dl_body_pool *pool;
=======
 */
struct vsp1_dl_body {
	struct list_head list;
	struct vsp1_device *vsp1;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	struct vsp1_dl_entry *entries;
	dma_addr_t dma;
	size_t size;

	unsigned int num_entries;
<<<<<<< HEAD
	unsigned int max_entries;
};

/**
 * struct vsp1_dl_body_pool - display list body pool
 * @dma: DMA address of the entries
 * @size: size of the full DMA memory pool in bytes
 * @mem: CPU memory pointer for the pool
 * @bodies: Array of DLB structures for the pool
 * @free: List of free DLB entries
 * @lock: Protects the free list
 * @vsp1: the VSP1 device
 */
struct vsp1_dl_body_pool {
	/* DMA allocation */
	dma_addr_t dma;
	size_t size;
	void *mem;

	/* Body management */
	struct vsp1_dl_body *bodies;
	struct list_head free;
	spinlock_t lock;

	struct vsp1_device *vsp1;
};

/**
 * struct vsp1_cmd_pool - Display List commands pool
 * @dma: DMA address of the entries
 * @size: size of the full DMA memory pool in bytes
 * @mem: CPU memory pointer for the pool
 * @cmds: Array of command structures for the pool
 * @free: Free pool entries
 * @lock: Protects the free list
 * @vsp1: the VSP1 device
 */
struct vsp1_dl_cmd_pool {
	/* DMA allocation */
	dma_addr_t dma;
	size_t size;
	void *mem;

	struct vsp1_dl_ext_cmd *cmds;
	struct list_head free;

	spinlock_t lock;

	struct vsp1_device *vsp1;
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
};

/**
 * struct vsp1_dl_list - Display list
 * @list: entry in the display list manager lists
 * @dlm: the display list manager
<<<<<<< HEAD
 * @header: display list header
 * @extension: extended display list header. NULL for normal lists
 * @dma: DMA address for the header
 * @body0: first display list body
 * @bodies: list of extra display list bodies
 * @pre_cmd: pre command to be issued through extended dl header
 * @post_cmd: post command to be issued through extended dl header
 * @has_chain: if true, indicates that there's a partition chain
 * @chain: entry in the display list partition chain
 * @internal: whether the display list is used for internal purpose
=======
 * @header: display list header, NULL for headerless lists
 * @dma: DMA address for the header
 * @body0: first display list body
 * @fragments: list of extra display list bodies
 * @chain: entry in the display list partition chain
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
 */
struct vsp1_dl_list {
	struct list_head list;
	struct vsp1_dl_manager *dlm;

	struct vsp1_dl_header *header;
<<<<<<< HEAD
	struct vsp1_dl_ext_header *extension;
	dma_addr_t dma;

	struct vsp1_dl_body *body0;
	struct list_head bodies;

	struct vsp1_dl_ext_cmd *pre_cmd;
	struct vsp1_dl_ext_cmd *post_cmd;

	bool has_chain;
	struct list_head chain;

	bool internal;
=======
	dma_addr_t dma;

	struct vsp1_dl_body body0;
	struct list_head fragments;

	bool has_chain;
	struct list_head chain;
};

enum vsp1_dl_mode {
	VSP1_DL_MODE_HEADER,
	VSP1_DL_MODE_HEADERLESS,
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
};

/**
 * struct vsp1_dl_manager - Display List manager
 * @index: index of the related WPF
<<<<<<< HEAD
 * @singleshot: execute the display list in single-shot mode
 * @vsp1: the VSP1 device
 * @lock: protects the free, active, queued, and pending lists
=======
 * @mode: display list operation mode (header or headerless)
 * @singleshot: execute the display list in single-shot mode
 * @vsp1: the VSP1 device
 * @lock: protects the free, active, queued, pending and gc_fragments lists
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
 * @free: array of all free display lists
 * @active: list currently being processed (loaded) by hardware
 * @queued: list queued to the hardware (written to the DL registers)
 * @pending: list waiting to be queued to the hardware
<<<<<<< HEAD
 * @pool: body pool for the display list bodies
 * @cmdpool: commands pool for extended display list
 */
struct vsp1_dl_manager {
	unsigned int index;
=======
 * @gc_work: fragments garbage collector work struct
 * @gc_fragments: array of display list fragments waiting to be freed
 */
struct vsp1_dl_manager {
	unsigned int index;
	enum vsp1_dl_mode mode;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	bool singleshot;
	struct vsp1_device *vsp1;

	spinlock_t lock;
	struct list_head free;
	struct vsp1_dl_list *active;
	struct vsp1_dl_list *queued;
	struct vsp1_dl_list *pending;

<<<<<<< HEAD
	struct vsp1_dl_body_pool *pool;
	struct vsp1_dl_cmd_pool *cmdpool;
=======
	struct work_struct gc_work;
	struct list_head gc_fragments;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
};

/* -----------------------------------------------------------------------------
 * Display List Body Management
 */

<<<<<<< HEAD
/**
 * vsp1_dl_body_pool_create - Create a pool of bodies from a single allocation
 * @vsp1: The VSP1 device
 * @num_bodies: The number of bodies to allocate
 * @num_entries: The maximum number of entries that a body can contain
 * @extra_size: Extra allocation provided for the bodies
 *
 * Allocate a pool of display list bodies each with enough memory to contain the
 * requested number of entries plus the @extra_size.
 *
 * Return a pointer to a pool on success or NULL if memory can't be allocated.
 */
struct vsp1_dl_body_pool *
vsp1_dl_body_pool_create(struct vsp1_device *vsp1, unsigned int num_bodies,
			 unsigned int num_entries, size_t extra_size)
{
	struct vsp1_dl_body_pool *pool;
	size_t dlb_size;
	unsigned int i;

	pool = kzalloc(sizeof(*pool), GFP_KERNEL);
	if (!pool)
		return NULL;

	pool->vsp1 = vsp1;

	/*
	 * TODO: 'extra_size' is only used by vsp1_dlm_create(), to allocate
	 * extra memory for the display list header. We need only one header per
	 * display list, not per display list body, thus this allocation is
	 * extraneous and should be reworked in the future.
	 */
	dlb_size = num_entries * sizeof(struct vsp1_dl_entry) + extra_size;
	pool->size = dlb_size * num_bodies;

	pool->bodies = kcalloc(num_bodies, sizeof(*pool->bodies), GFP_KERNEL);
	if (!pool->bodies) {
		kfree(pool);
		return NULL;
	}

	pool->mem = dma_alloc_wc(vsp1->bus_master, pool->size, &pool->dma,
				 GFP_KERNEL);
	if (!pool->mem) {
		kfree(pool->bodies);
		kfree(pool);
		return NULL;
	}

	spin_lock_init(&pool->lock);
	INIT_LIST_HEAD(&pool->free);

	for (i = 0; i < num_bodies; ++i) {
		struct vsp1_dl_body *dlb = &pool->bodies[i];

		dlb->pool = pool;
		dlb->max_entries = num_entries;

		dlb->dma = pool->dma + i * dlb_size;
		dlb->entries = pool->mem + i * dlb_size;

		list_add_tail(&dlb->free, &pool->free);
	}

	return pool;
}

/**
 * vsp1_dl_body_pool_destroy - Release a body pool
 * @pool: The body pool
 *
 * Release all components of a pool allocation.
 */
void vsp1_dl_body_pool_destroy(struct vsp1_dl_body_pool *pool)
{
	if (!pool)
		return;

	if (pool->mem)
		dma_free_wc(pool->vsp1->bus_master, pool->size, pool->mem,
			    pool->dma);

	kfree(pool->bodies);
	kfree(pool);
}

/**
 * vsp1_dl_body_get - Obtain a body from a pool
 * @pool: The body pool
 *
 * Obtain a body from the pool without blocking.
 *
 * Returns a display list body or NULL if there are none available.
 */
struct vsp1_dl_body *vsp1_dl_body_get(struct vsp1_dl_body_pool *pool)
{
	struct vsp1_dl_body *dlb = NULL;
	unsigned long flags;

	spin_lock_irqsave(&pool->lock, flags);

	if (!list_empty(&pool->free)) {
		dlb = list_first_entry(&pool->free, struct vsp1_dl_body, free);
		list_del(&dlb->free);
		refcount_set(&dlb->refcnt, 1);
	}

	spin_unlock_irqrestore(&pool->lock, flags);

=======
/*
 * Initialize a display list body object and allocate DMA memory for the body
 * data. The display list body object is expected to have been initialized to
 * 0 when allocated.
 */
static int vsp1_dl_body_init(struct vsp1_device *vsp1,
			     struct vsp1_dl_body *dlb, unsigned int num_entries,
			     size_t extra_size)
{
	size_t size = num_entries * sizeof(*dlb->entries) + extra_size;

	dlb->vsp1 = vsp1;
	dlb->size = size;

	dlb->entries = dma_alloc_wc(vsp1->bus_master, dlb->size, &dlb->dma,
				    GFP_KERNEL);
	if (!dlb->entries)
		return -ENOMEM;

	return 0;
}

/*
 * Cleanup a display list body and free allocated DMA memory allocated.
 */
static void vsp1_dl_body_cleanup(struct vsp1_dl_body *dlb)
{
	dma_free_wc(dlb->vsp1->bus_master, dlb->size, dlb->entries, dlb->dma);
}

/**
 * vsp1_dl_fragment_alloc - Allocate a display list fragment
 * @vsp1: The VSP1 device
 * @num_entries: The maximum number of entries that the fragment can contain
 *
 * Allocate a display list fragment with enough memory to contain the requested
 * number of entries.
 *
 * Return a pointer to a fragment on success or NULL if memory can't be
 * allocated.
 */
struct vsp1_dl_body *vsp1_dl_fragment_alloc(struct vsp1_device *vsp1,
					    unsigned int num_entries)
{
	struct vsp1_dl_body *dlb;
	int ret;

	dlb = kzalloc(sizeof(*dlb), GFP_KERNEL);
	if (!dlb)
		return NULL;

	ret = vsp1_dl_body_init(vsp1, dlb, num_entries, 0);
	if (ret < 0) {
		kfree(dlb);
		return NULL;
	}

>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	return dlb;
}

/**
<<<<<<< HEAD
 * vsp1_dl_body_put - Return a body back to its pool
 * @dlb: The display list body
 *
 * Return a body back to the pool, and reset the num_entries to clear the list.
 */
void vsp1_dl_body_put(struct vsp1_dl_body *dlb)
{
	unsigned long flags;

	if (!dlb)
		return;

	if (!refcount_dec_and_test(&dlb->refcnt))
		return;

	dlb->num_entries = 0;

	spin_lock_irqsave(&dlb->pool->lock, flags);
	list_add_tail(&dlb->free, &dlb->pool->free);
	spin_unlock_irqrestore(&dlb->pool->lock, flags);
}

/**
 * vsp1_dl_body_write - Write a register to a display list body
 * @dlb: The body
 * @reg: The register address
 * @data: The register value
 *
 * Write the given register and value to the display list body. The maximum
 * number of entries that can be written in a body is specified when the body is
 * allocated by vsp1_dl_body_alloc().
 */
void vsp1_dl_body_write(struct vsp1_dl_body *dlb, u32 reg, u32 data)
{
	if (WARN_ONCE(dlb->num_entries >= dlb->max_entries,
		      "DLB size exceeded (max %u)", dlb->max_entries))
		return;

=======
 * vsp1_dl_fragment_free - Free a display list fragment
 * @dlb: The fragment
 *
 * Free the given display list fragment and the associated DMA memory.
 *
 * Fragments must only be freed explicitly if they are not added to a display
 * list, as the display list will take ownership of them and free them
 * otherwise. Manual free typically happens at cleanup time for fragments that
 * have been allocated but not used.
 *
 * Passing a NULL pointer to this function is safe, in that case no operation
 * will be performed.
 */
void vsp1_dl_fragment_free(struct vsp1_dl_body *dlb)
{
	if (!dlb)
		return;

	vsp1_dl_body_cleanup(dlb);
	kfree(dlb);
}

/**
 * vsp1_dl_fragment_write - Write a register to a display list fragment
 * @dlb: The fragment
 * @reg: The register address
 * @data: The register value
 *
 * Write the given register and value to the display list fragment. The maximum
 * number of entries that can be written in a fragment is specified when the
 * fragment is allocated by vsp1_dl_fragment_alloc().
 */
void vsp1_dl_fragment_write(struct vsp1_dl_body *dlb, u32 reg, u32 data)
{
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	dlb->entries[dlb->num_entries].addr = reg;
	dlb->entries[dlb->num_entries].data = data;
	dlb->num_entries++;
}

/* -----------------------------------------------------------------------------
<<<<<<< HEAD
 * Display List Extended Command Management
 */

enum vsp1_extcmd_type {
	VSP1_EXTCMD_AUTODISP,
	VSP1_EXTCMD_AUTOFLD,
};

struct vsp1_extended_command_info {
	u16 opcode;
	size_t body_size;
};

static const struct vsp1_extended_command_info vsp1_extended_commands[] = {
	[VSP1_EXTCMD_AUTODISP] = { 0x02, 96 },
	[VSP1_EXTCMD_AUTOFLD]  = { 0x03, 160 },
};

/**
 * vsp1_dl_cmd_pool_create - Create a pool of commands from a single allocation
 * @vsp1: The VSP1 device
 * @type: The command pool type
 * @num_cmds: The number of commands to allocate
 *
 * Allocate a pool of commands each with enough memory to contain the private
 * data of each command. The allocation sizes are dependent upon the command
 * type.
 *
 * Return a pointer to the pool on success or NULL if memory can't be allocated.
 */
static struct vsp1_dl_cmd_pool *
vsp1_dl_cmd_pool_create(struct vsp1_device *vsp1, enum vsp1_extcmd_type type,
			unsigned int num_cmds)
{
	struct vsp1_dl_cmd_pool *pool;
	unsigned int i;
	size_t cmd_size;

	pool = kzalloc(sizeof(*pool), GFP_KERNEL);
	if (!pool)
		return NULL;

	spin_lock_init(&pool->lock);
	INIT_LIST_HEAD(&pool->free);

	pool->cmds = kcalloc(num_cmds, sizeof(*pool->cmds), GFP_KERNEL);
	if (!pool->cmds) {
		kfree(pool);
		return NULL;
	}

	cmd_size = sizeof(struct vsp1_pre_ext_dl_body) +
		   vsp1_extended_commands[type].body_size;
	cmd_size = ALIGN(cmd_size, 16);

	pool->size = cmd_size * num_cmds;
	pool->mem = dma_alloc_wc(vsp1->bus_master, pool->size, &pool->dma,
				 GFP_KERNEL);
	if (!pool->mem) {
		kfree(pool->cmds);
		kfree(pool);
		return NULL;
	}

	for (i = 0; i < num_cmds; ++i) {
		struct vsp1_dl_ext_cmd *cmd = &pool->cmds[i];
		size_t cmd_offset = i * cmd_size;
		/* data_offset must be 16 byte aligned for DMA. */
		size_t data_offset = sizeof(struct vsp1_pre_ext_dl_body) +
				     cmd_offset;

		cmd->pool = pool;
		cmd->opcode = vsp1_extended_commands[type].opcode;

		/*
		 * TODO: Auto-disp can utilise more than one extended body
		 * command per cmd.
		 */
		cmd->num_cmds = 1;
		cmd->cmds = pool->mem + cmd_offset;
		cmd->cmd_dma = pool->dma + cmd_offset;

		cmd->data = pool->mem + data_offset;
		cmd->data_dma = pool->dma + data_offset;

		list_add_tail(&cmd->free, &pool->free);
	}

	return pool;
}

static
struct vsp1_dl_ext_cmd *vsp1_dl_ext_cmd_get(struct vsp1_dl_cmd_pool *pool)
{
	struct vsp1_dl_ext_cmd *cmd = NULL;
	unsigned long flags;

	spin_lock_irqsave(&pool->lock, flags);

	if (!list_empty(&pool->free)) {
		cmd = list_first_entry(&pool->free, struct vsp1_dl_ext_cmd,
				       free);
		list_del(&cmd->free);
	}

	spin_unlock_irqrestore(&pool->lock, flags);

	return cmd;
}

static void vsp1_dl_ext_cmd_put(struct vsp1_dl_ext_cmd *cmd)
{
	unsigned long flags;

	if (!cmd)
		return;

	/* Reset flags, these mark data usage. */
	cmd->flags = 0;

	spin_lock_irqsave(&cmd->pool->lock, flags);
	list_add_tail(&cmd->free, &cmd->pool->free);
	spin_unlock_irqrestore(&cmd->pool->lock, flags);
}

static void vsp1_dl_ext_cmd_pool_destroy(struct vsp1_dl_cmd_pool *pool)
{
	if (!pool)
		return;

	if (pool->mem)
		dma_free_wc(pool->vsp1->bus_master, pool->size, pool->mem,
			    pool->dma);

	kfree(pool->cmds);
	kfree(pool);
}

struct vsp1_dl_ext_cmd *vsp1_dl_get_pre_cmd(struct vsp1_dl_list *dl)
{
	struct vsp1_dl_manager *dlm = dl->dlm;

	if (dl->pre_cmd)
		return dl->pre_cmd;

	dl->pre_cmd = vsp1_dl_ext_cmd_get(dlm->cmdpool);

	return dl->pre_cmd;
}

/* ----------------------------------------------------------------------------
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
 * Display List Transaction Management
 */

static struct vsp1_dl_list *vsp1_dl_list_alloc(struct vsp1_dl_manager *dlm)
{
	struct vsp1_dl_list *dl;
<<<<<<< HEAD
	size_t header_offset;
=======
	size_t header_size;
	int ret;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	dl = kzalloc(sizeof(*dl), GFP_KERNEL);
	if (!dl)
		return NULL;

<<<<<<< HEAD
	INIT_LIST_HEAD(&dl->bodies);
	dl->dlm = dlm;

	/* Get a default body for our list. */
	dl->body0 = vsp1_dl_body_get(dlm->pool);
	if (!dl->body0) {
=======
	INIT_LIST_HEAD(&dl->fragments);
	dl->dlm = dlm;

	/*
	 * Initialize the display list body and allocate DMA memory for the body
	 * and the optional header. Both are allocated together to avoid memory
	 * fragmentation, with the header located right after the body in
	 * memory.
	 */
	header_size = dlm->mode == VSP1_DL_MODE_HEADER
		    ? ALIGN(sizeof(struct vsp1_dl_header), 8)
		    : 0;

	ret = vsp1_dl_body_init(dlm->vsp1, &dl->body0, VSP1_DL_NUM_ENTRIES,
				header_size);
	if (ret < 0) {
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
		kfree(dl);
		return NULL;
	}

<<<<<<< HEAD
	header_offset = dl->body0->max_entries * sizeof(*dl->body0->entries);

	dl->header = ((void *)dl->body0->entries) + header_offset;
	dl->dma = dl->body0->dma + header_offset;

	memset(dl->header, 0, sizeof(*dl->header));
	dl->header->lists[0].addr = dl->body0->dma;
=======
	if (dlm->mode == VSP1_DL_MODE_HEADER) {
		size_t header_offset = VSP1_DL_NUM_ENTRIES
				     * sizeof(*dl->body0.entries);

		dl->header = ((void *)dl->body0.entries) + header_offset;
		dl->dma = dl->body0.dma + header_offset;

		memset(dl->header, 0, sizeof(*dl->header));
		dl->header->lists[0].addr = dl->body0.dma;
	}
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	return dl;
}

<<<<<<< HEAD
static void vsp1_dl_list_bodies_put(struct vsp1_dl_list *dl)
{
	struct vsp1_dl_body *dlb, *tmp;

	list_for_each_entry_safe(dlb, tmp, &dl->bodies, list) {
		list_del(&dlb->list);
		vsp1_dl_body_put(dlb);
	}
}

static void vsp1_dl_list_free(struct vsp1_dl_list *dl)
{
	vsp1_dl_body_put(dl->body0);
	vsp1_dl_list_bodies_put(dl);

=======
static void vsp1_dl_list_free(struct vsp1_dl_list *dl)
{
	vsp1_dl_body_cleanup(&dl->body0);
	list_splice_init(&dl->fragments, &dl->dlm->gc_fragments);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	kfree(dl);
}

/**
 * vsp1_dl_list_get - Get a free display list
 * @dlm: The display list manager
 *
 * Get a display list from the pool of free lists and return it.
 *
 * This function must be called without the display list manager lock held.
 */
struct vsp1_dl_list *vsp1_dl_list_get(struct vsp1_dl_manager *dlm)
{
	struct vsp1_dl_list *dl = NULL;
	unsigned long flags;

	spin_lock_irqsave(&dlm->lock, flags);

	if (!list_empty(&dlm->free)) {
		dl = list_first_entry(&dlm->free, struct vsp1_dl_list, list);
		list_del(&dl->list);

		/*
		 * The display list chain must be initialised to ensure every
		 * display list can assert list_empty() if it is not in a chain.
		 */
		INIT_LIST_HEAD(&dl->chain);
	}

	spin_unlock_irqrestore(&dlm->lock, flags);

	return dl;
}

/* This function must be called with the display list manager lock held.*/
static void __vsp1_dl_list_put(struct vsp1_dl_list *dl)
{
<<<<<<< HEAD
	struct vsp1_dl_list *dl_next;
=======
	struct vsp1_dl_list *dl_child;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	if (!dl)
		return;

	/*
	 * Release any linked display-lists which were chained for a single
	 * hardware operation.
	 */
	if (dl->has_chain) {
<<<<<<< HEAD
		list_for_each_entry(dl_next, &dl->chain, chain)
			__vsp1_dl_list_put(dl_next);
=======
		list_for_each_entry(dl_child, &dl->chain, chain)
			__vsp1_dl_list_put(dl_child);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	}

	dl->has_chain = false;

<<<<<<< HEAD
	vsp1_dl_list_bodies_put(dl);

	vsp1_dl_ext_cmd_put(dl->pre_cmd);
	vsp1_dl_ext_cmd_put(dl->post_cmd);

	dl->pre_cmd = NULL;
	dl->post_cmd = NULL;

	/*
	 * body0 is reused as as an optimisation as presently every display list
	 * has at least one body, thus we reinitialise the entries list.
	 */
	dl->body0->num_entries = 0;
=======
	/*
	 * We can't free fragments here as DMA memory can only be freed in
	 * interruptible context. Move all fragments to the display list
	 * manager's list of fragments to be freed, they will be
	 * garbage-collected by the work queue.
	 */
	if (!list_empty(&dl->fragments)) {
		list_splice_init(&dl->fragments, &dl->dlm->gc_fragments);
		schedule_work(&dl->dlm->gc_work);
	}

	dl->body0.num_entries = 0;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	list_add_tail(&dl->list, &dl->dlm->free);
}

/**
 * vsp1_dl_list_put - Release a display list
 * @dl: The display list
 *
 * Release the display list and return it to the pool of free lists.
 *
 * Passing a NULL pointer to this function is safe, in that case no operation
 * will be performed.
 */
void vsp1_dl_list_put(struct vsp1_dl_list *dl)
{
	unsigned long flags;

	if (!dl)
		return;

	spin_lock_irqsave(&dl->dlm->lock, flags);
	__vsp1_dl_list_put(dl);
	spin_unlock_irqrestore(&dl->dlm->lock, flags);
}

/**
<<<<<<< HEAD
 * vsp1_dl_list_get_body0 - Obtain the default body for the display list
 * @dl: The display list
 *
 * Obtain a pointer to the internal display list body allowing this to be passed
 * directly to configure operations.
 */
struct vsp1_dl_body *vsp1_dl_list_get_body0(struct vsp1_dl_list *dl)
{
	return dl->body0;
}

/**
 * vsp1_dl_list_add_body - Add a body to the display list
 * @dl: The display list
 * @dlb: The body
 *
 * Add a display list body to a display list. Registers contained in bodies are
 * processed after registers contained in the main display list, in the order in
 * which bodies are added.
 *
 * Adding a body to a display list passes ownership of the body to the list. The
 * caller retains its reference to the fragment when adding it to the display
 * list, but is not allowed to add new entries to the body.
 *
 * The reference must be explicitly released by a call to vsp1_dl_body_put()
 * when the body isn't needed anymore.
 */
int vsp1_dl_list_add_body(struct vsp1_dl_list *dl, struct vsp1_dl_body *dlb)
{
	refcount_inc(&dlb->refcnt);

	list_add_tail(&dlb->list, &dl->bodies);

=======
 * vsp1_dl_list_write - Write a register to the display list
 * @dl: The display list
 * @reg: The register address
 * @data: The register value
 *
 * Write the given register and value to the display list. Up to 256 registers
 * can be written per display list.
 */
void vsp1_dl_list_write(struct vsp1_dl_list *dl, u32 reg, u32 data)
{
	vsp1_dl_fragment_write(&dl->body0, reg, data);
}

/**
 * vsp1_dl_list_add_fragment - Add a fragment to the display list
 * @dl: The display list
 * @dlb: The fragment
 *
 * Add a display list body as a fragment to a display list. Registers contained
 * in fragments are processed after registers contained in the main display
 * list, in the order in which fragments are added.
 *
 * Adding a fragment to a display list passes ownership of the fragment to the
 * list. The caller must not touch the fragment after this call, and must not
 * free it explicitly with vsp1_dl_fragment_free().
 *
 * Fragments are only usable for display lists in header mode. Attempt to
 * add a fragment to a header-less display list will return an error.
 */
int vsp1_dl_list_add_fragment(struct vsp1_dl_list *dl,
			      struct vsp1_dl_body *dlb)
{
	/* Multi-body lists are only available in header mode. */
	if (dl->dlm->mode != VSP1_DL_MODE_HEADER)
		return -EINVAL;

	list_add_tail(&dlb->list, &dl->fragments);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	return 0;
}

/**
 * vsp1_dl_list_add_chain - Add a display list to a chain
 * @head: The head display list
 * @dl: The new display list
 *
 * Add a display list to an existing display list chain. The chained lists
 * will be automatically processed by the hardware without intervention from
 * the CPU. A display list end interrupt will only complete after the last
 * display list in the chain has completed processing.
 *
 * Adding a display list to a chain passes ownership of the display list to
 * the head display list item. The chain is released when the head dl item is
 * put back with __vsp1_dl_list_put().
<<<<<<< HEAD
=======
 *
 * Chained display lists are only usable in header mode. Attempts to add a
 * display list to a chain in header-less mode will return an error.
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
 */
int vsp1_dl_list_add_chain(struct vsp1_dl_list *head,
			   struct vsp1_dl_list *dl)
{
<<<<<<< HEAD
=======
	/* Chained lists are only available in header mode. */
	if (head->dlm->mode != VSP1_DL_MODE_HEADER)
		return -EINVAL;

>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	head->has_chain = true;
	list_add_tail(&dl->chain, &head->chain);
	return 0;
}

<<<<<<< HEAD
static void vsp1_dl_ext_cmd_fill_header(struct vsp1_dl_ext_cmd *cmd)
{
	cmd->cmds[0].opcode = cmd->opcode;
	cmd->cmds[0].flags = cmd->flags;
	cmd->cmds[0].address_set = cmd->data_dma;
	cmd->cmds[0].reserved = 0;
}

=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
static void vsp1_dl_list_fill_header(struct vsp1_dl_list *dl, bool is_last)
{
	struct vsp1_dl_manager *dlm = dl->dlm;
	struct vsp1_dl_header_list *hdr = dl->header->lists;
	struct vsp1_dl_body *dlb;
	unsigned int num_lists = 0;

	/*
	 * Fill the header with the display list bodies addresses and sizes. The
	 * address of the first body has already been filled when the display
	 * list was allocated.
	 */

<<<<<<< HEAD
	hdr->num_bytes = dl->body0->num_entries
		       * sizeof(*dl->header->lists);

	list_for_each_entry(dlb, &dl->bodies, list) {
=======
	hdr->num_bytes = dl->body0.num_entries
		       * sizeof(*dl->header->lists);

	list_for_each_entry(dlb, &dl->fragments, list) {
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
		num_lists++;
		hdr++;

		hdr->addr = dlb->dma;
		hdr->num_bytes = dlb->num_entries
			       * sizeof(*dl->header->lists);
	}

	dl->header->num_lists = num_lists;

	if (!list_empty(&dl->chain) && !is_last) {
		/*
		 * If this display list's chain is not empty, we are on a list,
		 * and the next item is the display list that we must queue for
		 * automatic processing by the hardware.
		 */
		struct vsp1_dl_list *next = list_next_entry(dl, chain);

		dl->header->next_header = next->dma;
		dl->header->flags = VSP1_DLH_AUTO_START;
	} else if (!dlm->singleshot) {
		/*
		 * if the display list manager works in continuous mode, the VSP
		 * should loop over the display list continuously until
		 * instructed to do otherwise.
		 */
		dl->header->next_header = dl->dma;
		dl->header->flags = VSP1_DLH_INT_ENABLE | VSP1_DLH_AUTO_START;
	} else {
		/*
		 * Otherwise, in mem-to-mem mode, we work in single-shot mode
		 * and the next display list must not be started automatically.
		 */
		dl->header->flags = VSP1_DLH_INT_ENABLE;
	}
<<<<<<< HEAD

	if (!dl->extension)
		return;

	dl->extension->flags = 0;

	if (dl->pre_cmd) {
		dl->extension->pre_ext_dl_plist = dl->pre_cmd->cmd_dma;
		dl->extension->pre_ext_dl_num_cmd = dl->pre_cmd->num_cmds;
		dl->extension->flags |= VSP1_DLH_EXT_PRE_CMD_EXEC;

		vsp1_dl_ext_cmd_fill_header(dl->pre_cmd);
	}

	if (dl->post_cmd) {
		dl->extension->post_ext_dl_plist = dl->post_cmd->cmd_dma;
		dl->extension->post_ext_dl_num_cmd = dl->post_cmd->num_cmds;
		dl->extension->flags |= VSP1_DLH_EXT_POST_CMD_EXEC;

		vsp1_dl_ext_cmd_fill_header(dl->post_cmd);
	}
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
}

static bool vsp1_dl_list_hw_update_pending(struct vsp1_dl_manager *dlm)
{
	struct vsp1_device *vsp1 = dlm->vsp1;

	if (!dlm->queued)
		return false;

	/*
<<<<<<< HEAD
	 * Check whether the VSP1 has taken the update. The hardware indicates
	 * this by clearing the UPDHDR bit in the CMD register.
	 */
	return !!(vsp1_read(vsp1, VI6_CMD(dlm->index)) & VI6_CMD_UPDHDR);
=======
	 * Check whether the VSP1 has taken the update. In headerless mode the
	 * hardware indicates this by clearing the UPD bit in the DL_BODY_SIZE
	 * register, and in header mode by clearing the UPDHDR bit in the CMD
	 * register.
	 */
	if (dlm->mode == VSP1_DL_MODE_HEADERLESS)
		return !!(vsp1_read(vsp1, VI6_DL_BODY_SIZE)
			  & VI6_DL_BODY_SIZE_UPD);
	else
		return !!(vsp1_read(vsp1, VI6_CMD(dlm->index))
			  & VI6_CMD_UPDHDR);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
}

static void vsp1_dl_list_hw_enqueue(struct vsp1_dl_list *dl)
{
	struct vsp1_dl_manager *dlm = dl->dlm;
	struct vsp1_device *vsp1 = dlm->vsp1;

<<<<<<< HEAD
	/*
	 * Program the display list header address. If the hardware is idle
	 * (single-shot mode or first frame in continuous mode) it will then be
	 * started independently. If the hardware is operating, the
	 * VI6_DL_HDR_REF_ADDR register will be updated with the display list
	 * address.
	 */
	vsp1_write(vsp1, VI6_DL_HDR_ADDR(dlm->index), dl->dma);
=======
	if (dlm->mode == VSP1_DL_MODE_HEADERLESS) {
		/*
		 * In headerless mode, program the hardware directly with the
		 * display list body address and size and set the UPD bit. The
		 * bit will be cleared by the hardware when the display list
		 * processing starts.
		 */
		vsp1_write(vsp1, VI6_DL_HDR_ADDR(0), dl->body0.dma);
		vsp1_write(vsp1, VI6_DL_BODY_SIZE, VI6_DL_BODY_SIZE_UPD |
			   (dl->body0.num_entries * sizeof(*dl->header->lists)));
	} else {
		/*
		 * In header mode, program the display list header address. If
		 * the hardware is idle (single-shot mode or first frame in
		 * continuous mode) it will then be started independently. If
		 * the hardware is operating, the VI6_DL_HDR_REF_ADDR register
		 * will be updated with the display list address.
		 */
		vsp1_write(vsp1, VI6_DL_HDR_ADDR(dlm->index), dl->dma);
	}
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
}

static void vsp1_dl_list_commit_continuous(struct vsp1_dl_list *dl)
{
	struct vsp1_dl_manager *dlm = dl->dlm;

	/*
	 * If a previous display list has been queued to the hardware but not
	 * processed yet, the VSP can start processing it at any time. In that
	 * case we can't replace the queued list by the new one, as we could
	 * race with the hardware. We thus mark the update as pending, it will
	 * be queued up to the hardware by the frame end interrupt handler.
<<<<<<< HEAD
	 *
	 * If a display list is already pending we simply drop it as the new
	 * display list is assumed to contain a more recent configuration. It is
	 * an error if the already pending list has the internal flag set, as
	 * there is then a process waiting for that list to complete. This
	 * shouldn't happen as the waiting process should perform proper
	 * locking, but warn just in case.
	 */
	if (vsp1_dl_list_hw_update_pending(dlm)) {
		WARN_ON(dlm->pending && dlm->pending->internal);
=======
	 */
	if (vsp1_dl_list_hw_update_pending(dlm)) {
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
		__vsp1_dl_list_put(dlm->pending);
		dlm->pending = dl;
		return;
	}

	/*
	 * Pass the new display list to the hardware and mark it as queued. It
	 * will become active when the hardware starts processing it.
	 */
	vsp1_dl_list_hw_enqueue(dl);

	__vsp1_dl_list_put(dlm->queued);
	dlm->queued = dl;
}

static void vsp1_dl_list_commit_singleshot(struct vsp1_dl_list *dl)
{
	struct vsp1_dl_manager *dlm = dl->dlm;

	/*
	 * When working in single-shot mode, the caller guarantees that the
	 * hardware is idle at this point. Just commit the head display list
	 * to hardware. Chained lists will be started automatically.
	 */
	vsp1_dl_list_hw_enqueue(dl);

	dlm->active = dl;
}

<<<<<<< HEAD
void vsp1_dl_list_commit(struct vsp1_dl_list *dl, bool internal)
{
	struct vsp1_dl_manager *dlm = dl->dlm;
	struct vsp1_dl_list *dl_next;
	unsigned long flags;

	/* Fill the header for the head and chained display lists. */
	vsp1_dl_list_fill_header(dl, list_empty(&dl->chain));

	list_for_each_entry(dl_next, &dl->chain, chain) {
		bool last = list_is_last(&dl_next->chain, &dl->chain);

		vsp1_dl_list_fill_header(dl_next, last);
	}

	dl->internal = internal;

=======
void vsp1_dl_list_commit(struct vsp1_dl_list *dl)
{
	struct vsp1_dl_manager *dlm = dl->dlm;
	struct vsp1_dl_list *dl_child;
	unsigned long flags;

	if (dlm->mode == VSP1_DL_MODE_HEADER) {
		/* Fill the header for the head and chained display lists. */
		vsp1_dl_list_fill_header(dl, list_empty(&dl->chain));

		list_for_each_entry(dl_child, &dl->chain, chain) {
			bool last = list_is_last(&dl_child->chain, &dl->chain);

			vsp1_dl_list_fill_header(dl_child, last);
		}
	}

>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	spin_lock_irqsave(&dlm->lock, flags);

	if (dlm->singleshot)
		vsp1_dl_list_commit_singleshot(dl);
	else
		vsp1_dl_list_commit_continuous(dl);

	spin_unlock_irqrestore(&dlm->lock, flags);
}

/* -----------------------------------------------------------------------------
 * Display List Manager
 */

/**
 * vsp1_dlm_irq_frame_end - Display list handler for the frame end interrupt
 * @dlm: the display list manager
 *
<<<<<<< HEAD
 * Return a set of flags that indicates display list completion status.
 *
 * The VSP1_DL_FRAME_END_COMPLETED flag indicates that the previous display list
 * has completed at frame end. If the flag is not returned display list
 * completion has been delayed by one frame because the display list commit
 * raced with the frame end interrupt. The function always returns with the flag
 * set in single-shot mode as display list processing is then not continuous and
 * races never occur.
 *
 * The VSP1_DL_FRAME_END_INTERNAL flag indicates that the previous display list
 * has completed and had been queued with the internal notification flag.
 * Internal notification is only supported for continuous mode.
 */
unsigned int vsp1_dlm_irq_frame_end(struct vsp1_dl_manager *dlm)
{
	struct vsp1_device *vsp1 = dlm->vsp1;
	u32 status = vsp1_read(vsp1, VI6_STATUS);
	unsigned int flags = 0;
=======
 * Return true if the previous display list has completed at frame end, or false
 * if it has been delayed by one frame because the display list commit raced
 * with the frame end interrupt. The function always returns true in header mode
 * as display list processing is then not continuous and races never occur.
 */
bool vsp1_dlm_irq_frame_end(struct vsp1_dl_manager *dlm)
{
	bool completed = false;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	spin_lock(&dlm->lock);

	/*
	 * The mem-to-mem pipelines work in single-shot mode. No new display
	 * list can be queued, we don't have to do anything.
	 */
	if (dlm->singleshot) {
		__vsp1_dl_list_put(dlm->active);
		dlm->active = NULL;
<<<<<<< HEAD
		flags |= VSP1_DL_FRAME_END_COMPLETED;
=======
		completed = true;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
		goto done;
	}

	/*
	 * If the commit operation raced with the interrupt and occurred after
	 * the frame end event but before interrupt processing, the hardware
	 * hasn't taken the update into account yet. We have to skip one frame
	 * and retry.
	 */
	if (vsp1_dl_list_hw_update_pending(dlm))
		goto done;

	/*
<<<<<<< HEAD
	 * Progressive streams report only TOP fields. If we have a BOTTOM
	 * field, we are interlaced, and expect the frame to complete on the
	 * next frame end interrupt.
	 */
	if (status & VI6_STATUS_FLD_STD(dlm->index))
		goto done;

	/*
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	 * The device starts processing the queued display list right after the
	 * frame end interrupt. The display list thus becomes active.
	 */
	if (dlm->queued) {
<<<<<<< HEAD
		if (dlm->queued->internal)
			flags |= VSP1_DL_FRAME_END_INTERNAL;
		dlm->queued->internal = false;

		__vsp1_dl_list_put(dlm->active);
		dlm->active = dlm->queued;
		dlm->queued = NULL;
		flags |= VSP1_DL_FRAME_END_COMPLETED;
=======
		__vsp1_dl_list_put(dlm->active);
		dlm->active = dlm->queued;
		dlm->queued = NULL;
		completed = true;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	}

	/*
	 * Now that the VSP has started processing the queued display list, we
	 * can queue the pending display list to the hardware if one has been
	 * prepared.
	 */
	if (dlm->pending) {
		vsp1_dl_list_hw_enqueue(dlm->pending);
		dlm->queued = dlm->pending;
		dlm->pending = NULL;
	}

done:
	spin_unlock(&dlm->lock);

<<<<<<< HEAD
	return flags;
=======
	return completed;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
}

/* Hardware Setup */
void vsp1_dlm_setup(struct vsp1_device *vsp1)
{
<<<<<<< HEAD
	unsigned int i;
	u32 ctrl = (256 << VI6_DL_CTRL_AR_WAIT_SHIFT)
		 | VI6_DL_CTRL_DC2 | VI6_DL_CTRL_DC1 | VI6_DL_CTRL_DC0
		 | VI6_DL_CTRL_DLE;
	u32 ext_dl = (0x02 << VI6_DL_EXT_CTRL_POLINT_SHIFT)
		   | VI6_DL_EXT_CTRL_DLPRI | VI6_DL_EXT_CTRL_EXT;

	if (vsp1_feature(vsp1, VSP1_HAS_EXT_DL)) {
		for (i = 0; i < vsp1->info->wpf_count; ++i)
			vsp1_write(vsp1, VI6_DL_EXT_CTRL(i), ext_dl);
	}
=======
	u32 ctrl = (256 << VI6_DL_CTRL_AR_WAIT_SHIFT)
		 | VI6_DL_CTRL_DC2 | VI6_DL_CTRL_DC1 | VI6_DL_CTRL_DC0
		 | VI6_DL_CTRL_DLE;

	/*
	 * The DRM pipeline operates with display lists in Continuous Frame
	 * Mode, all other pipelines use manual start.
	 */
	if (vsp1->drm)
		ctrl |= VI6_DL_CTRL_CFM0 | VI6_DL_CTRL_NH0;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	vsp1_write(vsp1, VI6_DL_CTRL, ctrl);
	vsp1_write(vsp1, VI6_DL_SWAP, VI6_DL_SWAP_LWS);
}

void vsp1_dlm_reset(struct vsp1_dl_manager *dlm)
{
	unsigned long flags;

	spin_lock_irqsave(&dlm->lock, flags);

	__vsp1_dl_list_put(dlm->active);
	__vsp1_dl_list_put(dlm->queued);
	__vsp1_dl_list_put(dlm->pending);

	spin_unlock_irqrestore(&dlm->lock, flags);

	dlm->active = NULL;
	dlm->queued = NULL;
	dlm->pending = NULL;
}

<<<<<<< HEAD
struct vsp1_dl_body *vsp1_dlm_dl_body_get(struct vsp1_dl_manager *dlm)
{
	return vsp1_dl_body_get(dlm->pool);
=======
/*
 * Free all fragments awaiting to be garbage-collected.
 *
 * This function must be called without the display list manager lock held.
 */
static void vsp1_dlm_fragments_free(struct vsp1_dl_manager *dlm)
{
	unsigned long flags;

	spin_lock_irqsave(&dlm->lock, flags);

	while (!list_empty(&dlm->gc_fragments)) {
		struct vsp1_dl_body *dlb;

		dlb = list_first_entry(&dlm->gc_fragments, struct vsp1_dl_body,
				       list);
		list_del(&dlb->list);

		spin_unlock_irqrestore(&dlm->lock, flags);
		vsp1_dl_fragment_free(dlb);
		spin_lock_irqsave(&dlm->lock, flags);
	}

	spin_unlock_irqrestore(&dlm->lock, flags);
}

static void vsp1_dlm_garbage_collect(struct work_struct *work)
{
	struct vsp1_dl_manager *dlm =
		container_of(work, struct vsp1_dl_manager, gc_work);

	vsp1_dlm_fragments_free(dlm);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
}

struct vsp1_dl_manager *vsp1_dlm_create(struct vsp1_device *vsp1,
					unsigned int index,
					unsigned int prealloc)
{
	struct vsp1_dl_manager *dlm;
<<<<<<< HEAD
	size_t header_size;
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	unsigned int i;

	dlm = devm_kzalloc(vsp1->dev, sizeof(*dlm), GFP_KERNEL);
	if (!dlm)
		return NULL;

	dlm->index = index;
<<<<<<< HEAD
=======
	dlm->mode = index == 0 && !vsp1->info->uapi
		  ? VSP1_DL_MODE_HEADERLESS : VSP1_DL_MODE_HEADER;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	dlm->singleshot = vsp1->info->uapi;
	dlm->vsp1 = vsp1;

	spin_lock_init(&dlm->lock);
	INIT_LIST_HEAD(&dlm->free);
<<<<<<< HEAD

	/*
	 * Initialize the display list body and allocate DMA memory for the body
	 * and the header. Both are allocated together to avoid memory
	 * fragmentation, with the header located right after the body in
	 * memory. An extra body is allocated on top of the prealloc to account
	 * for the cached body used by the vsp1_pipeline object.
	 */
	header_size = vsp1_feature(vsp1, VSP1_HAS_EXT_DL) ?
			sizeof(struct vsp1_dl_header_extended) :
			sizeof(struct vsp1_dl_header);

	header_size = ALIGN(header_size, 8);

	dlm->pool = vsp1_dl_body_pool_create(vsp1, prealloc + 1,
					     VSP1_DL_NUM_ENTRIES, header_size);
	if (!dlm->pool)
		return NULL;
=======
	INIT_LIST_HEAD(&dlm->gc_fragments);
	INIT_WORK(&dlm->gc_work, vsp1_dlm_garbage_collect);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	for (i = 0; i < prealloc; ++i) {
		struct vsp1_dl_list *dl;

		dl = vsp1_dl_list_alloc(dlm);
<<<<<<< HEAD
		if (!dl) {
			vsp1_dlm_destroy(dlm);
			return NULL;
		}

		/* The extended header immediately follows the header. */
		if (vsp1_feature(vsp1, VSP1_HAS_EXT_DL))
			dl->extension = (void *)dl->header
				      + sizeof(*dl->header);
=======
		if (!dl)
			return NULL;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

		list_add_tail(&dl->list, &dlm->free);
	}

<<<<<<< HEAD
	if (vsp1_feature(vsp1, VSP1_HAS_EXT_DL)) {
		dlm->cmdpool = vsp1_dl_cmd_pool_create(vsp1,
					VSP1_EXTCMD_AUTOFLD, prealloc);
		if (!dlm->cmdpool) {
			vsp1_dlm_destroy(dlm);
			return NULL;
		}
	}

=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	return dlm;
}

void vsp1_dlm_destroy(struct vsp1_dl_manager *dlm)
{
	struct vsp1_dl_list *dl, *next;

	if (!dlm)
		return;

<<<<<<< HEAD
=======
	cancel_work_sync(&dlm->gc_work);

>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	list_for_each_entry_safe(dl, next, &dlm->free, list) {
		list_del(&dl->list);
		vsp1_dl_list_free(dl);
	}

<<<<<<< HEAD
	vsp1_dl_body_pool_destroy(dlm->pool);
	vsp1_dl_ext_cmd_pool_destroy(dlm->cmdpool);
=======
	vsp1_dlm_fragments_free(dlm);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
}
