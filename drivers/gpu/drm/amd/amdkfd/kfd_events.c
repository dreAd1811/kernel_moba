/*
 * Copyright 2014 Advanced Micro Devices, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#include <linux/mm_types.h>
#include <linux/slab.h>
#include <linux/types.h>
#include <linux/sched/signal.h>
<<<<<<< HEAD
#include <linux/sched/mm.h>
#include <linux/uaccess.h>
=======
#include <linux/uaccess.h>
#include <linux/mm.h>
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
#include <linux/mman.h>
#include <linux/memory.h>
#include "kfd_priv.h"
#include "kfd_events.h"
<<<<<<< HEAD
#include "kfd_iommu.h"
#include <linux/device.h>

/*
 * Wrapper around wait_queue_entry_t
 */
struct kfd_event_waiter {
	wait_queue_entry_t wait;
	struct kfd_event *event; /* Event to wait for */
	bool activated;		 /* Becomes true when event is signaled */
};

/*
 * Each signal event needs a 64-bit signal slot where the signaler will write
 * a 1 before sending an interrupt. (This is needed because some interrupts
 * do not contain enough spare data bits to identify an event.)
 * We get whole pages and map them to the process VA.
 * Individual signal events use their event_id as slot index.
 */
struct kfd_signal_page {
	uint64_t *kernel_address;
	uint64_t __user *user_address;
	bool need_to_free_pages;
};


static uint64_t *page_slots(struct kfd_signal_page *page)
=======
#include <linux/device.h>

/*
 * A task can only be on a single wait_queue at a time, but we need to support
 * waiting on multiple events (any/all).
 * Instead of each event simply having a wait_queue with sleeping tasks, it
 * has a singly-linked list of tasks.
 * A thread that wants to sleep creates an array of these, one for each event
 * and adds one to each event's waiter chain.
 */
struct kfd_event_waiter {
	struct list_head waiters;
	struct task_struct *sleeping_task;

	/* Transitions to true when the event this belongs to is signaled. */
	bool activated;

	/* Event */
	struct kfd_event *event;
	uint32_t input_index;
};

/*
 * Over-complicated pooled allocator for event notification slots.
 *
 * Each signal event needs a 64-bit signal slot where the signaler will write
 * a 1 before sending an interrupt.l (This is needed because some interrupts
 * do not contain enough spare data bits to identify an event.)
 * We get whole pages from vmalloc and map them to the process VA.
 * Individual signal events are then allocated a slot in a page.
 */

struct signal_page {
	struct list_head event_pages;	/* kfd_process.signal_event_pages */
	uint64_t *kernel_address;
	uint64_t __user *user_address;
	uint32_t page_index;		/* Index into the mmap aperture. */
	unsigned int free_slots;
	unsigned long used_slot_bitmap[0];
};

#define SLOTS_PER_PAGE KFD_SIGNAL_EVENT_LIMIT
#define SLOT_BITMAP_SIZE BITS_TO_LONGS(SLOTS_PER_PAGE)
#define BITS_PER_PAGE (ilog2(SLOTS_PER_PAGE)+1)
#define SIGNAL_PAGE_SIZE (sizeof(struct signal_page) + \
				SLOT_BITMAP_SIZE * sizeof(long))

/*
 * For signal events, the event ID is used as the interrupt user data.
 * For SQ s_sendmsg interrupts, this is limited to 8 bits.
 */

#define INTERRUPT_DATA_BITS 8
#define SIGNAL_EVENT_ID_SLOT_SHIFT 0

static uint64_t *page_slots(struct signal_page *page)
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
{
	return page->kernel_address;
}

<<<<<<< HEAD
static struct kfd_signal_page *allocate_signal_page(struct kfd_process *p)
{
	void *backing_store;
	struct kfd_signal_page *page;

	page = kzalloc(sizeof(*page), GFP_KERNEL);
	if (!page)
		return NULL;

	backing_store = (void *) __get_free_pages(GFP_KERNEL,
=======
static bool allocate_free_slot(struct kfd_process *process,
				struct signal_page **out_page,
				unsigned int *out_slot_index)
{
	struct signal_page *page;

	list_for_each_entry(page, &process->signal_event_pages, event_pages) {
		if (page->free_slots > 0) {
			unsigned int slot =
				find_first_zero_bit(page->used_slot_bitmap,
							SLOTS_PER_PAGE);

			__set_bit(slot, page->used_slot_bitmap);
			page->free_slots--;

			page_slots(page)[slot] = UNSIGNALED_EVENT_SLOT;

			*out_page = page;
			*out_slot_index = slot;

			pr_debug("Allocated event signal slot in page %p, slot %d\n",
					page, slot);

			return true;
		}
	}

	pr_debug("No free event signal slots were found for process %p\n",
			process);

	return false;
}

#define list_tail_entry(head, type, member) \
	list_entry((head)->prev, type, member)

static bool allocate_signal_page(struct file *devkfd, struct kfd_process *p)
{
	void *backing_store;
	struct signal_page *page;

	page = kzalloc(SIGNAL_PAGE_SIZE, GFP_KERNEL);
	if (!page)
		goto fail_alloc_signal_page;

	page->free_slots = SLOTS_PER_PAGE;

	backing_store = (void *) __get_free_pages(GFP_KERNEL | __GFP_ZERO,
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
					get_order(KFD_SIGNAL_EVENT_LIMIT * 8));
	if (!backing_store)
		goto fail_alloc_signal_store;

<<<<<<< HEAD
	/* Initialize all events to unsignaled */
	memset(backing_store, (uint8_t) UNSIGNALED_EVENT_SLOT,
	       KFD_SIGNAL_EVENT_LIMIT * 8);

	page->kernel_address = backing_store;
	page->need_to_free_pages = true;
	pr_debug("Allocated new event signal page at %p, for process %p\n",
			page, p);

	return page;

fail_alloc_signal_store:
	kfree(page);
	return NULL;
}

static int allocate_event_notification_slot(struct kfd_process *p,
					    struct kfd_event *ev)
{
	int id;

	if (!p->signal_page) {
		p->signal_page = allocate_signal_page(p);
		if (!p->signal_page)
			return -ENOMEM;
		/* Oldest user mode expects 256 event slots */
		p->signal_mapped_size = 256*8;
	}

	/*
	 * Compatibility with old user mode: Only use signal slots
	 * user mode has mapped, may be less than
	 * KFD_SIGNAL_EVENT_LIMIT. This also allows future increase
	 * of the event limit without breaking user mode.
	 */
	id = idr_alloc(&p->event_idr, ev, 0, p->signal_mapped_size / 8,
		       GFP_KERNEL);
	if (id < 0)
		return id;

	ev->event_id = id;
	page_slots(p->signal_page)[id] = UNSIGNALED_EVENT_SLOT;

	return 0;
=======
	/* prevent user-mode info leaks */
	memset(backing_store, (uint8_t) UNSIGNALED_EVENT_SLOT,
		KFD_SIGNAL_EVENT_LIMIT * 8);

	page->kernel_address = backing_store;

	if (list_empty(&p->signal_event_pages))
		page->page_index = 0;
	else
		page->page_index = list_tail_entry(&p->signal_event_pages,
						   struct signal_page,
						   event_pages)->page_index + 1;

	pr_debug("Allocated new event signal page at %p, for process %p\n",
			page, p);
	pr_debug("Page index is %d\n", page->page_index);

	list_add(&page->event_pages, &p->signal_event_pages);

	return true;

fail_alloc_signal_store:
	kfree(page);
fail_alloc_signal_page:
	return false;
}

static bool allocate_event_notification_slot(struct file *devkfd,
					struct kfd_process *p,
					struct signal_page **page,
					unsigned int *signal_slot_index)
{
	bool ret;

	ret = allocate_free_slot(p, page, signal_slot_index);
	if (!ret) {
		ret = allocate_signal_page(devkfd, p);
		if (ret)
			ret = allocate_free_slot(p, page, signal_slot_index);
	}

	return ret;
}

/* Assumes that the process's event_mutex is locked. */
static void release_event_notification_slot(struct signal_page *page,
						size_t slot_index)
{
	__clear_bit(slot_index, page->used_slot_bitmap);
	page->free_slots++;

	/* We don't free signal pages, they are retained by the process
	 * and reused until it exits.
	 */
}

static struct signal_page *lookup_signal_page_by_index(struct kfd_process *p,
						unsigned int page_index)
{
	struct signal_page *page;

	/*
	 * This is safe because we don't delete signal pages until the
	 * process exits.
	 */
	list_for_each_entry(page, &p->signal_event_pages, event_pages)
		if (page->page_index == page_index)
			return page;

	return NULL;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
}

/*
 * Assumes that p->event_mutex is held and of course that p is not going
 * away (current or locked).
 */
static struct kfd_event *lookup_event_by_id(struct kfd_process *p, uint32_t id)
{
<<<<<<< HEAD
	return idr_find(&p->event_idr, id);
}

/**
 * lookup_signaled_event_by_partial_id - Lookup signaled event from partial ID
 * @p:     Pointer to struct kfd_process
 * @id:    ID to look up
 * @bits:  Number of valid bits in @id
 *
 * Finds the first signaled event with a matching partial ID. If no
 * matching signaled event is found, returns NULL. In that case the
 * caller should assume that the partial ID is invalid and do an
 * exhaustive search of all siglaned events.
 *
 * If multiple events with the same partial ID signal at the same
 * time, they will be found one interrupt at a time, not necessarily
 * in the same order the interrupts occurred. As long as the number of
 * interrupts is correct, all signaled events will be seen by the
 * driver.
 */
static struct kfd_event *lookup_signaled_event_by_partial_id(
	struct kfd_process *p, uint32_t id, uint32_t bits)
{
	struct kfd_event *ev;

	if (!p->signal_page || id >= KFD_SIGNAL_EVENT_LIMIT)
		return NULL;

	/* Fast path for the common case that @id is not a partial ID
	 * and we only need a single lookup.
	 */
	if (bits > 31 || (1U << bits) >= KFD_SIGNAL_EVENT_LIMIT) {
		if (page_slots(p->signal_page)[id] == UNSIGNALED_EVENT_SLOT)
			return NULL;

		return idr_find(&p->event_idr, id);
	}

	/* General case for partial IDs: Iterate over all matching IDs
	 * and find the first one that has signaled.
	 */
	for (ev = NULL; id < KFD_SIGNAL_EVENT_LIMIT && !ev; id += 1U << bits) {
		if (page_slots(p->signal_page)[id] == UNSIGNALED_EVENT_SLOT)
			continue;

		ev = idr_find(&p->event_idr, id);
	}

	return ev;
=======
	struct kfd_event *ev;

	hash_for_each_possible(p->events, ev, events, id)
		if (ev->event_id == id)
			return ev;

	return NULL;
}

static u32 make_signal_event_id(struct signal_page *page,
					 unsigned int signal_slot_index)
{
	return page->page_index |
			(signal_slot_index << SIGNAL_EVENT_ID_SLOT_SHIFT);
}

/*
 * Produce a kfd event id for a nonsignal event.
 * These are arbitrary numbers, so we do a sequential search through
 * the hash table for an unused number.
 */
static u32 make_nonsignal_event_id(struct kfd_process *p)
{
	u32 id;

	for (id = p->next_nonsignal_event_id;
		id < KFD_LAST_NONSIGNAL_EVENT_ID &&
		lookup_event_by_id(p, id);
		id++)
		;

	if (id < KFD_LAST_NONSIGNAL_EVENT_ID) {

		/*
		 * What if id == LAST_NONSIGNAL_EVENT_ID - 1?
		 * Then next_nonsignal_event_id = LAST_NONSIGNAL_EVENT_ID so
		 * the first loop fails immediately and we proceed with the
		 * wraparound loop below.
		 */
		p->next_nonsignal_event_id = id + 1;

		return id;
	}

	for (id = KFD_FIRST_NONSIGNAL_EVENT_ID;
		id < KFD_LAST_NONSIGNAL_EVENT_ID &&
		lookup_event_by_id(p, id);
		id++)
		;


	if (id < KFD_LAST_NONSIGNAL_EVENT_ID) {
		p->next_nonsignal_event_id = id + 1;
		return id;
	}

	p->next_nonsignal_event_id = KFD_FIRST_NONSIGNAL_EVENT_ID;
	return 0;
}

static struct kfd_event *lookup_event_by_page_slot(struct kfd_process *p,
						struct signal_page *page,
						unsigned int signal_slot)
{
	return lookup_event_by_id(p, make_signal_event_id(page, signal_slot));
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
}

static int create_signal_event(struct file *devkfd,
				struct kfd_process *p,
				struct kfd_event *ev)
{
<<<<<<< HEAD
	int ret;

	if (p->signal_mapped_size &&
	    p->signal_event_count == p->signal_mapped_size / 8) {
=======
	if (p->signal_event_count == KFD_SIGNAL_EVENT_LIMIT) {
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
		if (!p->signal_event_limit_reached) {
			pr_warn("Signal event wasn't created because limit was reached\n");
			p->signal_event_limit_reached = true;
		}
<<<<<<< HEAD
		return -ENOSPC;
	}

	ret = allocate_event_notification_slot(p, ev);
	if (ret) {
		pr_warn("Signal event wasn't created because out of kernel memory\n");
		return ret;
=======
		return -ENOMEM;
	}

	if (!allocate_event_notification_slot(devkfd, p, &ev->signal_page,
						&ev->signal_slot_index)) {
		pr_warn("Signal event wasn't created because out of kernel memory\n");
		return -ENOMEM;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	}

	p->signal_event_count++;

<<<<<<< HEAD
	ev->user_signal_address = &p->signal_page->user_address[ev->event_id];
=======
	ev->user_signal_address =
			&ev->signal_page->user_address[ev->signal_slot_index];

	ev->event_id = make_signal_event_id(ev->signal_page,
						ev->signal_slot_index);

>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	pr_debug("Signal event number %zu created with id %d, address %p\n",
			p->signal_event_count, ev->event_id,
			ev->user_signal_address);

	return 0;
}

<<<<<<< HEAD
static int create_other_event(struct kfd_process *p, struct kfd_event *ev)
{
	/* Cast KFD_LAST_NONSIGNAL_EVENT to uint32_t. This allows an
	 * intentional integer overflow to -1 without a compiler
	 * warning. idr_alloc treats a negative value as "maximum
	 * signed integer".
	 */
	int id = idr_alloc(&p->event_idr, ev, KFD_FIRST_NONSIGNAL_EVENT_ID,
			   (uint32_t)KFD_LAST_NONSIGNAL_EVENT_ID + 1,
			   GFP_KERNEL);

	if (id < 0)
		return id;
	ev->event_id = id;
=======
/*
 * No non-signal events are supported yet.
 * We create them as events that never signal.
 * Set event calls from user-mode are failed.
 */
static int create_other_event(struct kfd_process *p, struct kfd_event *ev)
{
	ev->event_id = make_nonsignal_event_id(p);
	if (ev->event_id == 0)
		return -ENOMEM;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	return 0;
}

void kfd_event_init_process(struct kfd_process *p)
{
	mutex_init(&p->event_mutex);
<<<<<<< HEAD
	idr_init(&p->event_idr);
	p->signal_page = NULL;
=======
	hash_init(p->events);
	INIT_LIST_HEAD(&p->signal_event_pages);
	p->next_nonsignal_event_id = KFD_FIRST_NONSIGNAL_EVENT_ID;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	p->signal_event_count = 0;
}

static void destroy_event(struct kfd_process *p, struct kfd_event *ev)
{
<<<<<<< HEAD
	struct kfd_event_waiter *waiter;

	/* Wake up pending waiters. They will return failure */
	list_for_each_entry(waiter, &ev->wq.head, wait.entry)
		waiter->event = NULL;
	wake_up_all(&ev->wq);

	if (ev->type == KFD_EVENT_TYPE_SIGNAL ||
	    ev->type == KFD_EVENT_TYPE_DEBUG)
		p->signal_event_count--;

	idr_remove(&p->event_idr, ev->event_id);
=======
	if (ev->signal_page) {
		release_event_notification_slot(ev->signal_page,
						ev->signal_slot_index);
		p->signal_event_count--;
	}

	/*
	 * Abandon the list of waiters. Individual waiting threads will
	 * clean up their own data.
	 */
	list_del(&ev->waiters);

	hash_del(&ev->events);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	kfree(ev);
}

static void destroy_events(struct kfd_process *p)
{
	struct kfd_event *ev;
<<<<<<< HEAD
	uint32_t id;

	idr_for_each_entry(&p->event_idr, ev, id)
		destroy_event(p, ev);
	idr_destroy(&p->event_idr);
=======
	struct hlist_node *tmp;
	unsigned int hash_bkt;

	hash_for_each_safe(p->events, hash_bkt, tmp, ev, events)
		destroy_event(p, ev);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
}

/*
 * We assume that the process is being destroyed and there is no need to
 * unmap the pages or keep bookkeeping data in order.
 */
<<<<<<< HEAD
static void shutdown_signal_page(struct kfd_process *p)
{
	struct kfd_signal_page *page = p->signal_page;

	if (page) {
		if (page->need_to_free_pages)
			free_pages((unsigned long)page->kernel_address,
				   get_order(KFD_SIGNAL_EVENT_LIMIT * 8));
=======
static void shutdown_signal_pages(struct kfd_process *p)
{
	struct signal_page *page, *tmp;

	list_for_each_entry_safe(page, tmp, &p->signal_event_pages,
					event_pages) {
		free_pages((unsigned long)page->kernel_address,
				get_order(KFD_SIGNAL_EVENT_LIMIT * 8));
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
		kfree(page);
	}
}

void kfd_event_free_process(struct kfd_process *p)
{
	destroy_events(p);
<<<<<<< HEAD
	shutdown_signal_page(p);
=======
	shutdown_signal_pages(p);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
}

static bool event_can_be_gpu_signaled(const struct kfd_event *ev)
{
	return ev->type == KFD_EVENT_TYPE_SIGNAL ||
					ev->type == KFD_EVENT_TYPE_DEBUG;
}

static bool event_can_be_cpu_signaled(const struct kfd_event *ev)
{
	return ev->type == KFD_EVENT_TYPE_SIGNAL;
}

<<<<<<< HEAD
int kfd_event_page_set(struct kfd_process *p, void *kernel_address,
		       uint64_t size)
{
	struct kfd_signal_page *page;

	if (p->signal_page)
		return -EBUSY;

	page = kzalloc(sizeof(*page), GFP_KERNEL);
	if (!page)
		return -ENOMEM;

	/* Initialize all events to unsignaled */
	memset(kernel_address, (uint8_t) UNSIGNALED_EVENT_SLOT,
	       KFD_SIGNAL_EVENT_LIMIT * 8);

	page->kernel_address = kernel_address;

	p->signal_page = page;
	p->signal_mapped_size = size;

	return 0;
}

=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
int kfd_event_create(struct file *devkfd, struct kfd_process *p,
		     uint32_t event_type, bool auto_reset, uint32_t node_id,
		     uint32_t *event_id, uint32_t *event_trigger_data,
		     uint64_t *event_page_offset, uint32_t *event_slot_index)
{
	int ret = 0;
	struct kfd_event *ev = kzalloc(sizeof(*ev), GFP_KERNEL);

	if (!ev)
		return -ENOMEM;

	ev->type = event_type;
	ev->auto_reset = auto_reset;
	ev->signaled = false;

<<<<<<< HEAD
	init_waitqueue_head(&ev->wq);
=======
	INIT_LIST_HEAD(&ev->waiters);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	*event_page_offset = 0;

	mutex_lock(&p->event_mutex);

	switch (event_type) {
	case KFD_EVENT_TYPE_SIGNAL:
	case KFD_EVENT_TYPE_DEBUG:
		ret = create_signal_event(devkfd, p, ev);
		if (!ret) {
<<<<<<< HEAD
			*event_page_offset = KFD_MMAP_TYPE_EVENTS;
			*event_page_offset <<= PAGE_SHIFT;
			*event_slot_index = ev->event_id;
=======
			*event_page_offset = (ev->signal_page->page_index |
					KFD_MMAP_EVENTS_MASK);
			*event_page_offset <<= PAGE_SHIFT;
			*event_slot_index = ev->signal_slot_index;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
		}
		break;
	default:
		ret = create_other_event(p, ev);
		break;
	}

	if (!ret) {
<<<<<<< HEAD
=======
		hash_add(p->events, &ev->events, ev->event_id);

>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
		*event_id = ev->event_id;
		*event_trigger_data = ev->event_id;
	} else {
		kfree(ev);
	}

	mutex_unlock(&p->event_mutex);

	return ret;
}

/* Assumes that p is current. */
int kfd_event_destroy(struct kfd_process *p, uint32_t event_id)
{
	struct kfd_event *ev;
	int ret = 0;

	mutex_lock(&p->event_mutex);

	ev = lookup_event_by_id(p, event_id);

	if (ev)
		destroy_event(p, ev);
	else
		ret = -EINVAL;

	mutex_unlock(&p->event_mutex);
	return ret;
}

static void set_event(struct kfd_event *ev)
{
	struct kfd_event_waiter *waiter;
<<<<<<< HEAD

	/* Auto reset if the list is non-empty and we're waking
	 * someone. waitqueue_active is safe here because we're
	 * protected by the p->event_mutex, which is also held when
	 * updating the wait queues in kfd_wait_on_events.
	 */
	ev->signaled = !ev->auto_reset || !waitqueue_active(&ev->wq);

	list_for_each_entry(waiter, &ev->wq.head, wait.entry)
		waiter->activated = true;

	wake_up_all(&ev->wq);
=======
	struct kfd_event_waiter *next;

	/* Auto reset if the list is non-empty and we're waking someone. */
	ev->signaled = !ev->auto_reset || list_empty(&ev->waiters);

	list_for_each_entry_safe(waiter, next, &ev->waiters, waiters) {
		waiter->activated = true;

		/* _init because free_waiters will call list_del */
		list_del_init(&waiter->waiters);

		wake_up_process(waiter->sleeping_task);
	}
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
}

/* Assumes that p is current. */
int kfd_set_event(struct kfd_process *p, uint32_t event_id)
{
	int ret = 0;
	struct kfd_event *ev;

	mutex_lock(&p->event_mutex);

	ev = lookup_event_by_id(p, event_id);

	if (ev && event_can_be_cpu_signaled(ev))
		set_event(ev);
	else
		ret = -EINVAL;

	mutex_unlock(&p->event_mutex);
	return ret;
}

static void reset_event(struct kfd_event *ev)
{
	ev->signaled = false;
}

/* Assumes that p is current. */
int kfd_reset_event(struct kfd_process *p, uint32_t event_id)
{
	int ret = 0;
	struct kfd_event *ev;

	mutex_lock(&p->event_mutex);

	ev = lookup_event_by_id(p, event_id);

	if (ev && event_can_be_cpu_signaled(ev))
		reset_event(ev);
	else
		ret = -EINVAL;

	mutex_unlock(&p->event_mutex);
	return ret;

}

static void acknowledge_signal(struct kfd_process *p, struct kfd_event *ev)
{
<<<<<<< HEAD
	page_slots(p->signal_page)[ev->event_id] = UNSIGNALED_EVENT_SLOT;
=======
	page_slots(ev->signal_page)[ev->signal_slot_index] =
						UNSIGNALED_EVENT_SLOT;
}

static bool is_slot_signaled(struct signal_page *page, unsigned int index)
{
	return page_slots(page)[index] != UNSIGNALED_EVENT_SLOT;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
}

static void set_event_from_interrupt(struct kfd_process *p,
					struct kfd_event *ev)
{
	if (ev && event_can_be_gpu_signaled(ev)) {
		acknowledge_signal(p, ev);
		set_event(ev);
	}
}

void kfd_signal_event_interrupt(unsigned int pasid, uint32_t partial_id,
				uint32_t valid_id_bits)
{
<<<<<<< HEAD
	struct kfd_event *ev = NULL;
=======
	struct kfd_event *ev;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	/*
	 * Because we are called from arbitrary context (workqueue) as opposed
	 * to process context, kfd_process could attempt to exit while we are
<<<<<<< HEAD
	 * running so the lookup function increments the process ref count.
=======
	 * running so the lookup function returns a locked process.
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	 */
	struct kfd_process *p = kfd_lookup_process_by_pasid(pasid);

	if (!p)
		return; /* Presumably process exited. */

	mutex_lock(&p->event_mutex);

<<<<<<< HEAD
	if (valid_id_bits)
		ev = lookup_signaled_event_by_partial_id(p, partial_id,
							 valid_id_bits);
	if (ev) {
		set_event_from_interrupt(p, ev);
	} else if (p->signal_page) {
		/*
		 * Partial ID lookup failed. Assume that the event ID
		 * in the interrupt payload was invalid and do an
		 * exhaustive search of signaled events.
		 */
		uint64_t *slots = page_slots(p->signal_page);
		uint32_t id;

		if (valid_id_bits)
			pr_debug_ratelimited("Partial ID invalid: %u (%u valid bits)\n",
					     partial_id, valid_id_bits);

		if (p->signal_event_count < KFD_SIGNAL_EVENT_LIMIT / 64) {
			/* With relatively few events, it's faster to
			 * iterate over the event IDR
			 */
			idr_for_each_entry(&p->event_idr, ev, id) {
				if (id >= KFD_SIGNAL_EVENT_LIMIT)
					break;

				if (slots[id] != UNSIGNALED_EVENT_SLOT)
					set_event_from_interrupt(p, ev);
			}
		} else {
			/* With relatively many events, it's faster to
			 * iterate over the signal slots and lookup
			 * only signaled events from the IDR.
			 */
			for (id = 0; id < KFD_SIGNAL_EVENT_LIMIT; id++)
				if (slots[id] != UNSIGNALED_EVENT_SLOT) {
					ev = lookup_event_by_id(p, id);
					set_event_from_interrupt(p, ev);
				}
		}
	}

	mutex_unlock(&p->event_mutex);
	kfd_unref_process(p);
=======
	if (valid_id_bits >= INTERRUPT_DATA_BITS) {
		/* Partial ID is a full ID. */
		ev = lookup_event_by_id(p, partial_id);
		set_event_from_interrupt(p, ev);
	} else {
		/*
		 * Partial ID is in fact partial. For now we completely
		 * ignore it, but we could use any bits we did receive to
		 * search faster.
		 */
		struct signal_page *page;
		unsigned int i;

		list_for_each_entry(page, &p->signal_event_pages, event_pages)
			for (i = 0; i < SLOTS_PER_PAGE; i++)
				if (is_slot_signaled(page, i)) {
					ev = lookup_event_by_page_slot(p,
								page, i);
					set_event_from_interrupt(p, ev);
				}
	}

	mutex_unlock(&p->event_mutex);
	mutex_unlock(&p->mutex);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
}

static struct kfd_event_waiter *alloc_event_waiters(uint32_t num_events)
{
	struct kfd_event_waiter *event_waiters;
	uint32_t i;

	event_waiters = kmalloc_array(num_events,
					sizeof(struct kfd_event_waiter),
					GFP_KERNEL);

	for (i = 0; (event_waiters) && (i < num_events) ; i++) {
<<<<<<< HEAD
		init_wait(&event_waiters[i].wait);
=======
		INIT_LIST_HEAD(&event_waiters[i].waiters);
		event_waiters[i].sleeping_task = current;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
		event_waiters[i].activated = false;
	}

	return event_waiters;
}

<<<<<<< HEAD
static int init_event_waiter_get_status(struct kfd_process *p,
		struct kfd_event_waiter *waiter,
		uint32_t event_id)
=======
static int init_event_waiter(struct kfd_process *p,
		struct kfd_event_waiter *waiter,
		uint32_t event_id,
		uint32_t input_index)
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
{
	struct kfd_event *ev = lookup_event_by_id(p, event_id);

	if (!ev)
		return -EINVAL;

	waiter->event = ev;
<<<<<<< HEAD
	waiter->activated = ev->signaled;
	ev->signaled = ev->signaled && !ev->auto_reset;

	return 0;
}

static void init_event_waiter_add_to_waitlist(struct kfd_event_waiter *waiter)
{
	struct kfd_event *ev = waiter->event;

	/* Only add to the wait list if we actually need to
	 * wait on this event.
	 */
	if (!waiter->activated)
		add_wait_queue(&ev->wq, &waiter->wait);
}

/* test_event_condition - Test condition of events being waited for
 * @all:           Return completion only if all events have signaled
 * @num_events:    Number of events to wait for
 * @event_waiters: Array of event waiters, one per event
 *
 * Returns KFD_IOC_WAIT_RESULT_COMPLETE if all (or one) event(s) have
 * signaled. Returns KFD_IOC_WAIT_RESULT_TIMEOUT if no (or not all)
 * events have signaled. Returns KFD_IOC_WAIT_RESULT_FAIL if any of
 * the events have been destroyed.
 */
static uint32_t test_event_condition(bool all, uint32_t num_events,
=======
	waiter->input_index = input_index;
	waiter->activated = ev->signaled;
	ev->signaled = ev->signaled && !ev->auto_reset;

	list_add(&waiter->waiters, &ev->waiters);

	return 0;
}

static bool test_event_condition(bool all, uint32_t num_events,
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
				struct kfd_event_waiter *event_waiters)
{
	uint32_t i;
	uint32_t activated_count = 0;

	for (i = 0; i < num_events; i++) {
<<<<<<< HEAD
		if (!event_waiters[i].event)
			return KFD_IOC_WAIT_RESULT_FAIL;

		if (event_waiters[i].activated) {
			if (!all)
				return KFD_IOC_WAIT_RESULT_COMPLETE;
=======
		if (event_waiters[i].activated) {
			if (!all)
				return true;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

			activated_count++;
		}
	}

<<<<<<< HEAD
	return activated_count == num_events ?
		KFD_IOC_WAIT_RESULT_COMPLETE : KFD_IOC_WAIT_RESULT_TIMEOUT;
=======
	return activated_count == num_events;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
}

/*
 * Copy event specific data, if defined.
 * Currently only memory exception events have additional data to copy to user
 */
<<<<<<< HEAD
static int copy_signaled_event_data(uint32_t num_events,
=======
static bool copy_signaled_event_data(uint32_t num_events,
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
		struct kfd_event_waiter *event_waiters,
		struct kfd_event_data __user *data)
{
	struct kfd_hsa_memory_exception_data *src;
	struct kfd_hsa_memory_exception_data __user *dst;
	struct kfd_event_waiter *waiter;
	struct kfd_event *event;
	uint32_t i;

	for (i = 0; i < num_events; i++) {
		waiter = &event_waiters[i];
		event = waiter->event;
		if (waiter->activated && event->type == KFD_EVENT_TYPE_MEMORY) {
<<<<<<< HEAD
			dst = &data[i].memory_exception_data;
			src = &event->memory_exception_data;
			if (copy_to_user(dst, src,
				sizeof(struct kfd_hsa_memory_exception_data)))
				return -EFAULT;
		}
	}

	return 0;
=======
			dst = &data[waiter->input_index].memory_exception_data;
			src = &event->memory_exception_data;
			if (copy_to_user(dst, src,
				sizeof(struct kfd_hsa_memory_exception_data)))
				return false;
		}
	}

	return true;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

}



static long user_timeout_to_jiffies(uint32_t user_timeout_ms)
{
	if (user_timeout_ms == KFD_EVENT_TIMEOUT_IMMEDIATE)
		return 0;

	if (user_timeout_ms == KFD_EVENT_TIMEOUT_INFINITE)
		return MAX_SCHEDULE_TIMEOUT;

	/*
	 * msecs_to_jiffies interprets all values above 2^31-1 as infinite,
	 * but we consider them finite.
	 * This hack is wrong, but nobody is likely to notice.
	 */
	user_timeout_ms = min_t(uint32_t, user_timeout_ms, 0x7FFFFFFF);

	return msecs_to_jiffies(user_timeout_ms) + 1;
}

static void free_waiters(uint32_t num_events, struct kfd_event_waiter *waiters)
{
	uint32_t i;

	for (i = 0; i < num_events; i++)
<<<<<<< HEAD
		if (waiters[i].event)
			remove_wait_queue(&waiters[i].event->wq,
					  &waiters[i].wait);
=======
		list_del(&waiters[i].waiters);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	kfree(waiters);
}

int kfd_wait_on_events(struct kfd_process *p,
		       uint32_t num_events, void __user *data,
		       bool all, uint32_t user_timeout_ms,
<<<<<<< HEAD
		       uint32_t *wait_result)
=======
		       enum kfd_event_wait_result *wait_result)
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
{
	struct kfd_event_data __user *events =
			(struct kfd_event_data __user *) data;
	uint32_t i;
	int ret = 0;
<<<<<<< HEAD

	struct kfd_event_waiter *event_waiters = NULL;
	long timeout = user_timeout_to_jiffies(user_timeout_ms);

	event_waiters = alloc_event_waiters(num_events);
	if (!event_waiters) {
		ret = -ENOMEM;
		goto out;
	}

	mutex_lock(&p->event_mutex);

=======
	struct kfd_event_waiter *event_waiters = NULL;
	long timeout = user_timeout_to_jiffies(user_timeout_ms);

	mutex_lock(&p->event_mutex);

	event_waiters = alloc_event_waiters(num_events);
	if (!event_waiters) {
		ret = -ENOMEM;
		goto fail;
	}

>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	for (i = 0; i < num_events; i++) {
		struct kfd_event_data event_data;

		if (copy_from_user(&event_data, &events[i],
				sizeof(struct kfd_event_data))) {
			ret = -EFAULT;
<<<<<<< HEAD
			goto out_unlock;
		}

		ret = init_event_waiter_get_status(p, &event_waiters[i],
				event_data.event_id);
		if (ret)
			goto out_unlock;
	}

	/* Check condition once. */
	*wait_result = test_event_condition(all, num_events, event_waiters);
	if (*wait_result == KFD_IOC_WAIT_RESULT_COMPLETE) {
		ret = copy_signaled_event_data(num_events,
					       event_waiters, events);
		goto out_unlock;
	} else if (WARN_ON(*wait_result == KFD_IOC_WAIT_RESULT_FAIL)) {
		/* This should not happen. Events shouldn't be
		 * destroyed while we're holding the event_mutex
		 */
		goto out_unlock;
	}

	/* Add to wait lists if we need to wait. */
	for (i = 0; i < num_events; i++)
		init_event_waiter_add_to_waitlist(&event_waiters[i]);

=======
			goto fail;
		}

		ret = init_event_waiter(p, &event_waiters[i],
				event_data.event_id, i);
		if (ret)
			goto fail;
	}

>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	mutex_unlock(&p->event_mutex);

	while (true) {
		if (fatal_signal_pending(current)) {
			ret = -EINTR;
			break;
		}

		if (signal_pending(current)) {
			/*
			 * This is wrong when a nonzero, non-infinite timeout
			 * is specified. We need to use
			 * ERESTARTSYS_RESTARTBLOCK, but struct restart_block
			 * contains a union with data for each user and it's
			 * in generic kernel code that I don't want to
			 * touch yet.
			 */
			ret = -ERESTARTSYS;
			break;
		}

<<<<<<< HEAD
		/* Set task state to interruptible sleep before
		 * checking wake-up conditions. A concurrent wake-up
		 * will put the task back into runnable state. In that
		 * case schedule_timeout will not put the task to
		 * sleep and we'll get a chance to re-check the
		 * updated conditions almost immediately. Otherwise,
		 * this race condition would lead to a soft hang or a
		 * very long sleep.
		 */
		set_current_state(TASK_INTERRUPTIBLE);

		*wait_result = test_event_condition(all, num_events,
						    event_waiters);
		if (*wait_result != KFD_IOC_WAIT_RESULT_TIMEOUT)
			break;

		if (timeout <= 0)
			break;

		timeout = schedule_timeout(timeout);
	}
	__set_current_state(TASK_RUNNING);

	/* copy_signaled_event_data may sleep. So this has to happen
	 * after the task state is set back to RUNNING.
	 */
	if (!ret && *wait_result == KFD_IOC_WAIT_RESULT_COMPLETE)
		ret = copy_signaled_event_data(num_events,
					       event_waiters, events);

	mutex_lock(&p->event_mutex);
out_unlock:
	free_waiters(num_events, event_waiters);
	mutex_unlock(&p->event_mutex);
out:
	if (ret)
		*wait_result = KFD_IOC_WAIT_RESULT_FAIL;
	else if (*wait_result == KFD_IOC_WAIT_RESULT_FAIL)
		ret = -EIO;
=======
		if (test_event_condition(all, num_events, event_waiters)) {
			if (copy_signaled_event_data(num_events,
					event_waiters, events))
				*wait_result = KFD_WAIT_COMPLETE;
			else
				*wait_result = KFD_WAIT_ERROR;
			break;
		}

		if (timeout <= 0) {
			*wait_result = KFD_WAIT_TIMEOUT;
			break;
		}

		timeout = schedule_timeout_interruptible(timeout);
	}
	__set_current_state(TASK_RUNNING);

	mutex_lock(&p->event_mutex);
	free_waiters(num_events, event_waiters);
	mutex_unlock(&p->event_mutex);

	return ret;

fail:
	if (event_waiters)
		free_waiters(num_events, event_waiters);

	mutex_unlock(&p->event_mutex);

	*wait_result = KFD_WAIT_ERROR;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	return ret;
}

int kfd_event_mmap(struct kfd_process *p, struct vm_area_struct *vma)
{
<<<<<<< HEAD
	unsigned long pfn;
	struct kfd_signal_page *page;
	int ret;

	/* check required size doesn't exceed the allocated size */
	if (get_order(KFD_SIGNAL_EVENT_LIMIT * 8) <
=======

	unsigned int page_index;
	unsigned long pfn;
	struct signal_page *page;

	/* check required size is logical */
	if (get_order(KFD_SIGNAL_EVENT_LIMIT * 8) !=
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
			get_order(vma->vm_end - vma->vm_start)) {
		pr_err("Event page mmap requested illegal size\n");
		return -EINVAL;
	}

<<<<<<< HEAD
	page = p->signal_page;
	if (!page) {
		/* Probably KFD bug, but mmap is user-accessible. */
		pr_debug("Signal page could not be found\n");
=======
	page_index = vma->vm_pgoff;

	page = lookup_signal_page_by_index(p, page_index);
	if (!page) {
		/* Probably KFD bug, but mmap is user-accessible. */
		pr_debug("Signal page could not be found for page_index %u\n",
				page_index);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
		return -EINVAL;
	}

	pfn = __pa(page->kernel_address);
	pfn >>= PAGE_SHIFT;

	vma->vm_flags |= VM_IO | VM_DONTCOPY | VM_DONTEXPAND | VM_NORESERVE
		       | VM_DONTDUMP | VM_PFNMAP;

	pr_debug("Mapping signal page\n");
	pr_debug("     start user address  == 0x%08lx\n", vma->vm_start);
	pr_debug("     end user address    == 0x%08lx\n", vma->vm_end);
	pr_debug("     pfn                 == 0x%016lX\n", pfn);
	pr_debug("     vm_flags            == 0x%08lX\n", vma->vm_flags);
	pr_debug("     size                == 0x%08lX\n",
			vma->vm_end - vma->vm_start);

	page->user_address = (uint64_t __user *)vma->vm_start;

	/* mapping the page to user process */
<<<<<<< HEAD
	ret = remap_pfn_range(vma, vma->vm_start, pfn,
			vma->vm_end - vma->vm_start, vma->vm_page_prot);
	if (!ret)
		p->signal_mapped_size = vma->vm_end - vma->vm_start;

	return ret;
=======
	return remap_pfn_range(vma, vma->vm_start, pfn,
			vma->vm_end - vma->vm_start, vma->vm_page_prot);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
}

/*
 * Assumes that p->event_mutex is held and of course
 * that p is not going away (current or locked).
 */
static void lookup_events_by_type_and_signal(struct kfd_process *p,
		int type, void *event_data)
{
	struct kfd_hsa_memory_exception_data *ev_data;
	struct kfd_event *ev;
<<<<<<< HEAD
	uint32_t id;
=======
	int bkt;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	bool send_signal = true;

	ev_data = (struct kfd_hsa_memory_exception_data *) event_data;

<<<<<<< HEAD
	id = KFD_FIRST_NONSIGNAL_EVENT_ID;
	idr_for_each_entry_continue(&p->event_idr, ev, id)
=======
	hash_for_each(p->events, bkt, ev, events)
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
		if (ev->type == type) {
			send_signal = false;
			dev_dbg(kfd_device,
					"Event found: id %X type %d",
					ev->event_id, ev->type);
			set_event(ev);
			if (ev->type == KFD_EVENT_TYPE_MEMORY && ev_data)
				ev->memory_exception_data = *ev_data;
		}

<<<<<<< HEAD
	if (type == KFD_EVENT_TYPE_MEMORY) {
		dev_warn(kfd_device,
			"Sending SIGSEGV to HSA Process with PID %d ",
				p->lead_thread->pid);
		send_sig(SIGSEGV, p->lead_thread, 0);
	}

=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	/* Send SIGTERM no event of type "type" has been found*/
	if (send_signal) {
		if (send_sigterm) {
			dev_warn(kfd_device,
				"Sending SIGTERM to HSA Process with PID %d ",
					p->lead_thread->pid);
			send_sig(SIGTERM, p->lead_thread, 0);
		} else {
			dev_err(kfd_device,
				"HSA Process (PID %d) got unhandled exception",
				p->lead_thread->pid);
		}
	}
}

<<<<<<< HEAD
#ifdef KFD_SUPPORT_IOMMU_V2
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
void kfd_signal_iommu_event(struct kfd_dev *dev, unsigned int pasid,
		unsigned long address, bool is_write_requested,
		bool is_execute_requested)
{
	struct kfd_hsa_memory_exception_data memory_exception_data;
	struct vm_area_struct *vma;

	/*
	 * Because we are called from arbitrary context (workqueue) as opposed
	 * to process context, kfd_process could attempt to exit while we are
<<<<<<< HEAD
	 * running so the lookup function increments the process ref count.
	 */
	struct kfd_process *p = kfd_lookup_process_by_pasid(pasid);
	struct mm_struct *mm;
=======
	 * running so the lookup function returns a locked process.
	 */
	struct kfd_process *p = kfd_lookup_process_by_pasid(pasid);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	if (!p)
		return; /* Presumably process exited. */

<<<<<<< HEAD
	/* Take a safe reference to the mm_struct, which may otherwise
	 * disappear even while the kfd_process is still referenced.
	 */
	mm = get_task_mm(p->lead_thread);
	if (!mm) {
		kfd_unref_process(p);
		return; /* Process is exiting */
	}

	memset(&memory_exception_data, 0, sizeof(memory_exception_data));

	down_read(&mm->mmap_sem);
	vma = find_vma(mm, address);
=======
	memset(&memory_exception_data, 0, sizeof(memory_exception_data));

	down_read(&p->mm->mmap_sem);
	vma = find_vma(p->mm, address);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	memory_exception_data.gpu_id = dev->id;
	memory_exception_data.va = address;
	/* Set failure reason */
	memory_exception_data.failure.NotPresent = 1;
	memory_exception_data.failure.NoExecute = 0;
	memory_exception_data.failure.ReadOnly = 0;
<<<<<<< HEAD
	if (vma && address >= vma->vm_start) {
		memory_exception_data.failure.NotPresent = 0;

		if (is_write_requested && !(vma->vm_flags & VM_WRITE))
			memory_exception_data.failure.ReadOnly = 1;
		else
			memory_exception_data.failure.ReadOnly = 0;

		if (is_execute_requested && !(vma->vm_flags & VM_EXEC))
			memory_exception_data.failure.NoExecute = 1;
		else
			memory_exception_data.failure.NoExecute = 0;
	}

	up_read(&mm->mmap_sem);
	mmput(mm);

	pr_debug("notpresent %d, noexecute %d, readonly %d\n",
			memory_exception_data.failure.NotPresent,
			memory_exception_data.failure.NoExecute,
			memory_exception_data.failure.ReadOnly);

	/* Workaround on Raven to not kill the process when memory is freed
	 * before IOMMU is able to finish processing all the excessive PPRs
	 */
	if (dev->device_info->asic_family != CHIP_RAVEN) {
		mutex_lock(&p->event_mutex);

		/* Lookup events by type and signal them */
		lookup_events_by_type_and_signal(p, KFD_EVENT_TYPE_MEMORY,
				&memory_exception_data);

		mutex_unlock(&p->event_mutex);
	}

	kfd_unref_process(p);
}
#endif /* KFD_SUPPORT_IOMMU_V2 */
=======
	if (vma) {
		if (vma->vm_start > address) {
			memory_exception_data.failure.NotPresent = 1;
			memory_exception_data.failure.NoExecute = 0;
			memory_exception_data.failure.ReadOnly = 0;
		} else {
			memory_exception_data.failure.NotPresent = 0;
			if (is_write_requested && !(vma->vm_flags & VM_WRITE))
				memory_exception_data.failure.ReadOnly = 1;
			else
				memory_exception_data.failure.ReadOnly = 0;
			if (is_execute_requested && !(vma->vm_flags & VM_EXEC))
				memory_exception_data.failure.NoExecute = 1;
			else
				memory_exception_data.failure.NoExecute = 0;
		}
	}

	up_read(&p->mm->mmap_sem);

	mutex_lock(&p->event_mutex);

	/* Lookup events by type and signal them */
	lookup_events_by_type_and_signal(p, KFD_EVENT_TYPE_MEMORY,
			&memory_exception_data);

	mutex_unlock(&p->event_mutex);
	mutex_unlock(&p->mutex);
}
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

void kfd_signal_hw_exception_event(unsigned int pasid)
{
	/*
	 * Because we are called from arbitrary context (workqueue) as opposed
	 * to process context, kfd_process could attempt to exit while we are
<<<<<<< HEAD
	 * running so the lookup function increments the process ref count.
=======
	 * running so the lookup function returns a locked process.
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	 */
	struct kfd_process *p = kfd_lookup_process_by_pasid(pasid);

	if (!p)
		return; /* Presumably process exited. */

	mutex_lock(&p->event_mutex);

	/* Lookup events by type and signal them */
	lookup_events_by_type_and_signal(p, KFD_EVENT_TYPE_HW_EXCEPTION, NULL);

	mutex_unlock(&p->event_mutex);
<<<<<<< HEAD
	kfd_unref_process(p);
}

void kfd_signal_vm_fault_event(struct kfd_dev *dev, unsigned int pasid,
				struct kfd_vm_fault_info *info)
{
	struct kfd_event *ev;
	uint32_t id;
	struct kfd_process *p = kfd_lookup_process_by_pasid(pasid);
	struct kfd_hsa_memory_exception_data memory_exception_data;

	if (!p)
		return; /* Presumably process exited. */
	memset(&memory_exception_data, 0, sizeof(memory_exception_data));
	memory_exception_data.gpu_id = dev->id;
	memory_exception_data.failure.imprecise = 1;
	/* Set failure reason */
	if (info) {
		memory_exception_data.va = (info->page_addr) << PAGE_SHIFT;
		memory_exception_data.failure.NotPresent =
			info->prot_valid ? 1 : 0;
		memory_exception_data.failure.NoExecute =
			info->prot_exec ? 1 : 0;
		memory_exception_data.failure.ReadOnly =
			info->prot_write ? 1 : 0;
		memory_exception_data.failure.imprecise = 0;
	}
	mutex_lock(&p->event_mutex);

	id = KFD_FIRST_NONSIGNAL_EVENT_ID;
	idr_for_each_entry_continue(&p->event_idr, ev, id)
		if (ev->type == KFD_EVENT_TYPE_MEMORY) {
			ev->memory_exception_data = memory_exception_data;
			set_event(ev);
		}

	mutex_unlock(&p->event_mutex);
	kfd_unref_process(p);
}

void kfd_signal_reset_event(struct kfd_dev *dev)
{
	struct kfd_hsa_hw_exception_data hw_exception_data;
	struct kfd_process *p;
	struct kfd_event *ev;
	unsigned int temp;
	uint32_t id, idx;

	/* Whole gpu reset caused by GPU hang and memory is lost */
	memset(&hw_exception_data, 0, sizeof(hw_exception_data));
	hw_exception_data.gpu_id = dev->id;
	hw_exception_data.memory_lost = 1;

	idx = srcu_read_lock(&kfd_processes_srcu);
	hash_for_each_rcu(kfd_processes_table, temp, p, kfd_processes) {
		mutex_lock(&p->event_mutex);
		id = KFD_FIRST_NONSIGNAL_EVENT_ID;
		idr_for_each_entry_continue(&p->event_idr, ev, id)
			if (ev->type == KFD_EVENT_TYPE_HW_EXCEPTION) {
				ev->hw_exception_data = hw_exception_data;
				set_event(ev);
			}
		mutex_unlock(&p->event_mutex);
	}
	srcu_read_unlock(&kfd_processes_srcu, idx);
=======
	mutex_unlock(&p->mutex);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
}
