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

#ifndef KFD_EVENTS_H_INCLUDED
#define KFD_EVENTS_H_INCLUDED

#include <linux/kernel.h>
#include <linux/hashtable.h>
#include <linux/types.h>
#include <linux/list.h>
<<<<<<< HEAD
#include <linux/wait.h>
#include "kfd_priv.h"
#include <uapi/linux/kfd_ioctl.h>

/*
 * IDR supports non-negative integer IDs. Small IDs are used for
 * signal events to match their signal slot. Use the upper half of the
 * ID space for non-signal events.
 */
#define KFD_FIRST_NONSIGNAL_EVENT_ID ((INT_MAX >> 1) + 1)
#define KFD_LAST_NONSIGNAL_EVENT_ID INT_MAX
=======
#include "kfd_priv.h"
#include <uapi/linux/kfd_ioctl.h>

#define KFD_EVENT_ID_NONSIGNAL_MASK 0x80000000U
#define KFD_FIRST_NONSIGNAL_EVENT_ID KFD_EVENT_ID_NONSIGNAL_MASK
#define KFD_LAST_NONSIGNAL_EVENT_ID UINT_MAX
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/*
 * Written into kfd_signal_slot_t to indicate that the event is not signaled.
 * Since the event protocol may need to write the event ID into memory, this
 * must not be a valid event ID.
 * For the sake of easy memset-ing, this must be a byte pattern.
 */
#define UNSIGNALED_EVENT_SLOT ((uint64_t)-1)

struct kfd_event_waiter;
struct signal_page;

struct kfd_event {
<<<<<<< HEAD
=======
	/* All events in process, rooted at kfd_process.events. */
	struct hlist_node events;

>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	u32 event_id;

	bool signaled;
	bool auto_reset;

	int type;

<<<<<<< HEAD
	wait_queue_head_t wq; /* List of event waiters. */

	/* Only for signal events. */
=======
	struct list_head waiters; /* List of kfd_event_waiter by waiters. */

	/* Only for signal events. */
	struct signal_page *signal_page;
	unsigned int signal_slot_index;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	uint64_t __user *user_signal_address;

	/* type specific data */
	union {
		struct kfd_hsa_memory_exception_data memory_exception_data;
<<<<<<< HEAD
		struct kfd_hsa_hw_exception_data hw_exception_data;
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	};
};

#define KFD_EVENT_TIMEOUT_IMMEDIATE 0
#define KFD_EVENT_TIMEOUT_INFINITE 0xFFFFFFFFu

/* Matching HSA_EVENTTYPE */
#define KFD_EVENT_TYPE_SIGNAL 0
#define KFD_EVENT_TYPE_HW_EXCEPTION 3
#define KFD_EVENT_TYPE_DEBUG 5
#define KFD_EVENT_TYPE_MEMORY 8

extern void kfd_signal_event_interrupt(unsigned int pasid, uint32_t partial_id,
					uint32_t valid_id_bits);

#endif
