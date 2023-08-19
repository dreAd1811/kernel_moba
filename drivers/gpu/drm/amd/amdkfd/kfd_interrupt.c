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

/*
 * KFD Interrupts.
 *
 * AMD GPUs deliver interrupts by pushing an interrupt description onto the
 * interrupt ring and then sending an interrupt. KGD receives the interrupt
 * in ISR and sends us a pointer to each new entry on the interrupt ring.
 *
 * We generally can't process interrupt-signaled events from ISR, so we call
 * out to each interrupt client module (currently only the scheduler) to ask if
 * each interrupt is interesting. If they return true, then it requires further
 * processing so we copy it to an internal interrupt ring and call each
 * interrupt client again from a work-queue.
 *
 * There's no acknowledgment for the interrupts we use. The hardware simply
 * queues a new interrupt each time without waiting.
 *
 * The fixed-size internal queue means that it's possible for us to lose
 * interrupts because we have no back-pressure to the hardware.
 */

#include <linux/slab.h>
#include <linux/device.h>
<<<<<<< HEAD
#include <linux/kfifo.h>
#include "kfd_priv.h"

#define KFD_IH_NUM_ENTRIES 8192
=======
#include "kfd_priv.h"

#define KFD_INTERRUPT_RING_SIZE 1024
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

static void interrupt_wq(struct work_struct *);

int kfd_interrupt_init(struct kfd_dev *kfd)
{
<<<<<<< HEAD
	int r;

	r = kfifo_alloc(&kfd->ih_fifo,
		KFD_IH_NUM_ENTRIES * kfd->device_info->ih_ring_entry_size,
		GFP_KERNEL);
	if (r) {
		dev_err(kfd_chardev(), "Failed to allocate IH fifo\n");
		return r;
	}

	kfd->ih_wq = alloc_workqueue("KFD IH", WQ_HIGHPRI, 1);
=======
	void *interrupt_ring = kmalloc_array(KFD_INTERRUPT_RING_SIZE,
					kfd->device_info->ih_ring_entry_size,
					GFP_KERNEL);
	if (!interrupt_ring)
		return -ENOMEM;

	kfd->interrupt_ring = interrupt_ring;
	kfd->interrupt_ring_size =
		KFD_INTERRUPT_RING_SIZE * kfd->device_info->ih_ring_entry_size;
	atomic_set(&kfd->interrupt_ring_wptr, 0);
	atomic_set(&kfd->interrupt_ring_rptr, 0);

>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	spin_lock_init(&kfd->interrupt_lock);

	INIT_WORK(&kfd->interrupt_work, interrupt_wq);

	kfd->interrupts_active = true;

	/*
	 * After this function returns, the interrupt will be enabled. This
	 * barrier ensures that the interrupt running on a different processor
	 * sees all the above writes.
	 */
	smp_wmb();

	return 0;
}

void kfd_interrupt_exit(struct kfd_dev *kfd)
{
	/*
	 * Stop the interrupt handler from writing to the ring and scheduling
	 * workqueue items. The spinlock ensures that any interrupt running
	 * after we have unlocked sees interrupts_active = false.
	 */
	unsigned long flags;

	spin_lock_irqsave(&kfd->interrupt_lock, flags);
	kfd->interrupts_active = false;
	spin_unlock_irqrestore(&kfd->interrupt_lock, flags);

	/*
<<<<<<< HEAD
	 * flush_work ensures that there are no outstanding
	 * work-queue items that will access interrupt_ring. New work items
	 * can't be created because we stopped interrupt handling above.
	 */
	flush_workqueue(kfd->ih_wq);

	kfifo_free(&kfd->ih_fifo);
}

/*
 * Assumption: single reader/writer. This function is not re-entrant
 */
bool enqueue_ih_ring_entry(struct kfd_dev *kfd,	const void *ih_ring_entry)
{
	int count;

	count = kfifo_in(&kfd->ih_fifo, ih_ring_entry,
				kfd->device_info->ih_ring_entry_size);
	if (count != kfd->device_info->ih_ring_entry_size) {
		dev_err_ratelimited(kfd_chardev(),
			"Interrupt ring overflow, dropping interrupt %d\n",
			count);
		return false;
	}

=======
	 * Flush_scheduled_work ensures that there are no outstanding
	 * work-queue items that will access interrupt_ring. New work items
	 * can't be created because we stopped interrupt handling above.
	 */
	flush_scheduled_work();

	kfree(kfd->interrupt_ring);
}

/*
 * This assumes that it can't be called concurrently with itself
 * but only with dequeue_ih_ring_entry.
 */
bool enqueue_ih_ring_entry(struct kfd_dev *kfd,	const void *ih_ring_entry)
{
	unsigned int rptr = atomic_read(&kfd->interrupt_ring_rptr);
	unsigned int wptr = atomic_read(&kfd->interrupt_ring_wptr);

	if ((rptr - wptr) % kfd->interrupt_ring_size ==
					kfd->device_info->ih_ring_entry_size) {
		/* This is very bad, the system is likely to hang. */
		dev_err_ratelimited(kfd_chardev(),
			"Interrupt ring overflow, dropping interrupt.\n");
		return false;
	}

	memcpy(kfd->interrupt_ring + wptr, ih_ring_entry,
			kfd->device_info->ih_ring_entry_size);

	wptr = (wptr + kfd->device_info->ih_ring_entry_size) %
			kfd->interrupt_ring_size;
	smp_wmb(); /* Ensure memcpy'd data is visible before wptr update. */
	atomic_set(&kfd->interrupt_ring_wptr, wptr);

>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	return true;
}

/*
<<<<<<< HEAD
 * Assumption: single reader/writer. This function is not re-entrant
 */
static bool dequeue_ih_ring_entry(struct kfd_dev *kfd, void *ih_ring_entry)
{
	int count;

	count = kfifo_out(&kfd->ih_fifo, ih_ring_entry,
				kfd->device_info->ih_ring_entry_size);

	WARN_ON(count && count != kfd->device_info->ih_ring_entry_size);

	return count == kfd->device_info->ih_ring_entry_size;
=======
 * This assumes that it can't be called concurrently with itself
 * but only with enqueue_ih_ring_entry.
 */
static bool dequeue_ih_ring_entry(struct kfd_dev *kfd, void *ih_ring_entry)
{
	/*
	 * Assume that wait queues have an implicit barrier, i.e. anything that
	 * happened in the ISR before it queued work is visible.
	 */

	unsigned int wptr = atomic_read(&kfd->interrupt_ring_wptr);
	unsigned int rptr = atomic_read(&kfd->interrupt_ring_rptr);

	if (rptr == wptr)
		return false;

	memcpy(ih_ring_entry, kfd->interrupt_ring + rptr,
			kfd->device_info->ih_ring_entry_size);

	rptr = (rptr + kfd->device_info->ih_ring_entry_size) %
			kfd->interrupt_ring_size;

	/*
	 * Ensure the rptr write update is not visible until
	 * memcpy has finished reading.
	 */
	smp_mb();
	atomic_set(&kfd->interrupt_ring_rptr, rptr);

	return true;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
}

static void interrupt_wq(struct work_struct *work)
{
	struct kfd_dev *dev = container_of(work, struct kfd_dev,
						interrupt_work);
<<<<<<< HEAD
	uint32_t ih_ring_entry[KFD_MAX_RING_ENTRY_SIZE];

	if (dev->device_info->ih_ring_entry_size > sizeof(ih_ring_entry)) {
		dev_err_once(kfd_chardev(), "Ring entry too small\n");
		return;
	}
=======

	uint32_t ih_ring_entry[DIV_ROUND_UP(
				dev->device_info->ih_ring_entry_size,
				sizeof(uint32_t))];
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	while (dequeue_ih_ring_entry(dev, ih_ring_entry))
		dev->device_info->event_interrupt_class->interrupt_wq(dev,
								ih_ring_entry);
}

<<<<<<< HEAD
bool interrupt_is_wanted(struct kfd_dev *dev,
			const uint32_t *ih_ring_entry,
			uint32_t *patched_ihre, bool *flag)
=======
bool interrupt_is_wanted(struct kfd_dev *dev, const uint32_t *ih_ring_entry)
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
{
	/* integer and bitwise OR so there is no boolean short-circuiting */
	unsigned int wanted = 0;

	wanted |= dev->device_info->event_interrupt_class->interrupt_isr(dev,
<<<<<<< HEAD
					 ih_ring_entry, patched_ihre, flag);
=======
								ih_ring_entry);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	return wanted != 0;
}
