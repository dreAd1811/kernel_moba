/*
<<<<<<< HEAD
 * Copyright (C) 2017 - Cambridge Greys Ltd
 * Copyright (C) 2011 - 2014 Cisco Systems Inc
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
 * Copyright (C) 2000 - 2007 Jeff Dike (jdike@{addtoit,linux.intel}.com)
 * Licensed under the GPL
 * Derived (i.e. mostly copied) from arch/i386/kernel/irq.c:
 *	Copyright (C) 1992, 1998 Linus Torvalds, Ingo Molnar
 */

#include <linux/cpumask.h>
#include <linux/hardirq.h>
#include <linux/interrupt.h>
#include <linux/kernel_stat.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/seq_file.h>
#include <linux/slab.h>
#include <as-layout.h>
#include <kern_util.h>
#include <os.h>
<<<<<<< HEAD
#include <irq_user.h>


/* When epoll triggers we do not know why it did so
 * we can also have different IRQs for read and write.
 * This is why we keep a small irq_fd array for each fd -
 * one entry per IRQ type
 */

struct irq_entry {
	struct irq_entry *next;
	int fd;
	struct irq_fd *irq_array[MAX_IRQ_TYPE + 1];
};

static struct irq_entry *active_fds;

static DEFINE_SPINLOCK(irq_lock);

static void irq_io_loop(struct irq_fd *irq, struct uml_pt_regs *regs)
{
/*
 * irq->active guards against reentry
 * irq->pending accumulates pending requests
 * if pending is raised the irq_handler is re-run
 * until pending is cleared
 */
	if (irq->active) {
		irq->active = false;
		do {
			irq->pending = false;
			do_IRQ(irq->irq, regs);
		} while (irq->pending && (!irq->purge));
		if (!irq->purge)
			irq->active = true;
	} else {
		irq->pending = true;
	}
}

void sigio_handler(int sig, struct siginfo *unused_si, struct uml_pt_regs *regs)
{
	struct irq_entry *irq_entry;
	struct irq_fd *irq;

	int n, i, j;

	while (1) {
		/* This is now lockless - epoll keeps back-referencesto the irqs
		 * which have trigger it so there is no need to walk the irq
		 * list and lock it every time. We avoid locking by turning off
		 * IO for a specific fd by executing os_del_epoll_fd(fd) before
		 * we do any changes to the actual data structures
		 */
		n = os_waiting_for_events_epoll();

		if (n <= 0) {
			if (n == -EINTR)
				continue;
			else
				break;
		}

		for (i = 0; i < n ; i++) {
			/* Epoll back reference is the entry with 3 irq_fd
			 * leaves - one for each irq type.
			 */
			irq_entry = (struct irq_entry *)
				os_epoll_get_data_pointer(i);
			for (j = 0; j < MAX_IRQ_TYPE ; j++) {
				irq = irq_entry->irq_array[j];
				if (irq == NULL)
					continue;
				if (os_epoll_triggered(i, irq->events) > 0)
					irq_io_loop(irq, regs);
				if (irq->purge) {
					irq_entry->irq_array[j] = NULL;
					kfree(irq);
				}
			}
		}
	}
}

static int assign_epoll_events_to_irq(struct irq_entry *irq_entry)
{
	int i;
	int events = 0;
	struct irq_fd *irq;

	for (i = 0; i < MAX_IRQ_TYPE ; i++) {
		irq = irq_entry->irq_array[i];
		if (irq != NULL)
			events = irq->events | events;
	}
	if (events > 0) {
	/* os_add_epoll will call os_mod_epoll if this already exists */
		return os_add_epoll_fd(events, irq_entry->fd, irq_entry);
	}
	/* No events - delete */
	return os_del_epoll_fd(irq_entry->fd);
}



static int activate_fd(int irq, int fd, int type, void *dev_id)
{
	struct irq_fd *new_fd;
	struct irq_entry *irq_entry;
	int i, err, events;
	unsigned long flags;
=======

/*
 * This list is accessed under irq_lock, except in sigio_handler,
 * where it is safe from being modified.  IRQ handlers won't change it -
 * if an IRQ source has vanished, it will be freed by free_irqs just
 * before returning from sigio_handler.  That will process a separate
 * list of irqs to free, with its own locking, coming back here to
 * remove list elements, taking the irq_lock to do so.
 */
static struct irq_fd *active_fds = NULL;
static struct irq_fd **last_irq_ptr = &active_fds;

extern void free_irqs(void);

void sigio_handler(int sig, struct siginfo *unused_si, struct uml_pt_regs *regs)
{
	struct irq_fd *irq_fd;
	int n;

	while (1) {
		n = os_waiting_for_events(active_fds);
		if (n <= 0) {
			if (n == -EINTR)
				continue;
			else break;
		}

		for (irq_fd = active_fds; irq_fd != NULL;
		     irq_fd = irq_fd->next) {
			if (irq_fd->current_events != 0) {
				irq_fd->current_events = 0;
				do_IRQ(irq_fd->irq, regs);
			}
		}
	}

	free_irqs();
}

static DEFINE_SPINLOCK(irq_lock);

static int activate_fd(int irq, int fd, int type, void *dev_id)
{
	struct pollfd *tmp_pfd;
	struct irq_fd *new_fd, *irq_fd;
	unsigned long flags;
	int events, err, n;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	err = os_set_fd_async(fd);
	if (err < 0)
		goto out;

<<<<<<< HEAD
	spin_lock_irqsave(&irq_lock, flags);

	/* Check if we have an entry for this fd */

	err = -EBUSY;
	for (irq_entry = active_fds;
		irq_entry != NULL; irq_entry = irq_entry->next) {
		if (irq_entry->fd == fd)
			break;
	}

	if (irq_entry == NULL) {
		/* This needs to be atomic as it may be called from an
		 * IRQ context.
		 */
		irq_entry = kmalloc(sizeof(struct irq_entry), GFP_ATOMIC);
		if (irq_entry == NULL) {
			printk(KERN_ERR
				"Failed to allocate new IRQ entry\n");
			goto out_unlock;
		}
		irq_entry->fd = fd;
		for (i = 0; i < MAX_IRQ_TYPE; i++)
			irq_entry->irq_array[i] = NULL;
		irq_entry->next = active_fds;
		active_fds = irq_entry;
	}

	/* Check if we are trying to re-register an interrupt for a
	 * particular fd
	 */

	if (irq_entry->irq_array[type] != NULL) {
		printk(KERN_ERR
			"Trying to reregister IRQ %d FD %d TYPE %d ID %p\n",
			irq, fd, type, dev_id
		);
		goto out_unlock;
	} else {
		/* New entry for this fd */

		err = -ENOMEM;
		new_fd = kmalloc(sizeof(struct irq_fd), GFP_ATOMIC);
		if (new_fd == NULL)
			goto out_unlock;

		events = os_event_mask(type);

		*new_fd = ((struct irq_fd) {
			.id		= dev_id,
			.irq		= irq,
			.type		= type,
			.events		= events,
			.active		= true,
			.pending	= false,
			.purge		= false
		});
		/* Turn off any IO on this fd - allows us to
		 * avoid locking the IRQ loop
		 */
		os_del_epoll_fd(irq_entry->fd);
		irq_entry->irq_array[type] = new_fd;
	}

	/* Turn back IO on with the correct (new) IO event mask */
	assign_epoll_events_to_irq(irq_entry);
	spin_unlock_irqrestore(&irq_lock, flags);
	maybe_sigio_broken(fd, (type != IRQ_NONE));

	return 0;
out_unlock:
	spin_unlock_irqrestore(&irq_lock, flags);
out:
	return err;
}

/*
 * Walk the IRQ list and dispose of any unused entries.
 * Should be done under irq_lock.
 */

static void garbage_collect_irq_entries(void)
{
	int i;
	bool reap;
	struct irq_entry *walk;
	struct irq_entry *previous = NULL;
	struct irq_entry *to_free;

	if (active_fds == NULL)
		return;
	walk = active_fds;
	while (walk != NULL) {
		reap = true;
		for (i = 0; i < MAX_IRQ_TYPE ; i++) {
			if (walk->irq_array[i] != NULL) {
				reap = false;
				break;
			}
		}
		if (reap) {
			if (previous == NULL)
				active_fds = walk->next;
			else
				previous->next = walk->next;
			to_free = walk;
		} else {
			to_free = NULL;
		}
		walk = walk->next;
		if (to_free != NULL)
			kfree(to_free);
	}
}

/*
 * Walk the IRQ list and get the descriptor for our FD
 */

static struct irq_entry *get_irq_entry_by_fd(int fd)
{
	struct irq_entry *walk = active_fds;

	while (walk != NULL) {
		if (walk->fd == fd)
			return walk;
		walk = walk->next;
	}
	return NULL;
}


/*
 * Walk the IRQ list and dispose of an entry for a specific
 * device, fd and number. Note - if sharing an IRQ for read
 * and writefor the same FD it will be disposed in either case.
 * If this behaviour is undesirable use different IRQ ids.
 */

#define IGNORE_IRQ 1
#define IGNORE_DEV (1<<1)

static void do_free_by_irq_and_dev(
	struct irq_entry *irq_entry,
	unsigned int irq,
	void *dev,
	int flags
)
{
	int i;
	struct irq_fd *to_free;

	for (i = 0; i < MAX_IRQ_TYPE ; i++) {
		if (irq_entry->irq_array[i] != NULL) {
			if (
			((flags & IGNORE_IRQ) ||
				(irq_entry->irq_array[i]->irq == irq)) &&
			((flags & IGNORE_DEV) ||
				(irq_entry->irq_array[i]->id == dev))
			) {
				/* Turn off any IO on this fd - allows us to
				 * avoid locking the IRQ loop
				 */
				os_del_epoll_fd(irq_entry->fd);
				to_free = irq_entry->irq_array[i];
				irq_entry->irq_array[i] = NULL;
				assign_epoll_events_to_irq(irq_entry);
				if (to_free->active)
					to_free->purge = true;
				else
					kfree(to_free);
			}
		}
	}
=======
	err = -ENOMEM;
	new_fd = kmalloc(sizeof(struct irq_fd), GFP_KERNEL);
	if (new_fd == NULL)
		goto out;

	if (type == IRQ_READ)
		events = UM_POLLIN | UM_POLLPRI;
	else events = UM_POLLOUT;
	*new_fd = ((struct irq_fd) { .next  		= NULL,
				     .id 		= dev_id,
				     .fd 		= fd,
				     .type 		= type,
				     .irq 		= irq,
				     .events 		= events,
				     .current_events 	= 0 } );

	err = -EBUSY;
	spin_lock_irqsave(&irq_lock, flags);
	for (irq_fd = active_fds; irq_fd != NULL; irq_fd = irq_fd->next) {
		if ((irq_fd->fd == fd) && (irq_fd->type == type)) {
			printk(KERN_ERR "Registering fd %d twice\n", fd);
			printk(KERN_ERR "Irqs : %d, %d\n", irq_fd->irq, irq);
			printk(KERN_ERR "Ids : 0x%p, 0x%p\n", irq_fd->id,
			       dev_id);
			goto out_unlock;
		}
	}

	if (type == IRQ_WRITE)
		fd = -1;

	tmp_pfd = NULL;
	n = 0;

	while (1) {
		n = os_create_pollfd(fd, events, tmp_pfd, n);
		if (n == 0)
			break;

		/*
		 * n > 0
		 * It means we couldn't put new pollfd to current pollfds
		 * and tmp_fds is NULL or too small for new pollfds array.
		 * Needed size is equal to n as minimum.
		 *
		 * Here we have to drop the lock in order to call
		 * kmalloc, which might sleep.
		 * If something else came in and changed the pollfds array
		 * so we will not be able to put new pollfd struct to pollfds
		 * then we free the buffer tmp_fds and try again.
		 */
		spin_unlock_irqrestore(&irq_lock, flags);
		kfree(tmp_pfd);

		tmp_pfd = kmalloc(n, GFP_KERNEL);
		if (tmp_pfd == NULL)
			goto out_kfree;

		spin_lock_irqsave(&irq_lock, flags);
	}

	*last_irq_ptr = new_fd;
	last_irq_ptr = &new_fd->next;

	spin_unlock_irqrestore(&irq_lock, flags);

	/*
	 * This calls activate_fd, so it has to be outside the critical
	 * section.
	 */
	maybe_sigio_broken(fd, (type == IRQ_READ));

	return 0;

 out_unlock:
	spin_unlock_irqrestore(&irq_lock, flags);
 out_kfree:
	kfree(new_fd);
 out:
	return err;
}

static void free_irq_by_cb(int (*test)(struct irq_fd *, void *), void *arg)
{
	unsigned long flags;

	spin_lock_irqsave(&irq_lock, flags);
	os_free_irq_by_cb(test, arg, active_fds, &last_irq_ptr);
	spin_unlock_irqrestore(&irq_lock, flags);
}

struct irq_and_dev {
	int irq;
	void *dev;
};

static int same_irq_and_dev(struct irq_fd *irq, void *d)
{
	struct irq_and_dev *data = d;

	return ((irq->irq == data->irq) && (irq->id == data->dev));
}

static void free_irq_by_irq_and_dev(unsigned int irq, void *dev)
{
	struct irq_and_dev data = ((struct irq_and_dev) { .irq  = irq,
							  .dev  = dev });

	free_irq_by_cb(same_irq_and_dev, &data);
}

static int same_fd(struct irq_fd *irq, void *fd)
{
	return (irq->fd == *((int *)fd));
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
}

void free_irq_by_fd(int fd)
{
<<<<<<< HEAD
	struct irq_entry *to_free;
	unsigned long flags;

	spin_lock_irqsave(&irq_lock, flags);
	to_free = get_irq_entry_by_fd(fd);
	if (to_free != NULL) {
		do_free_by_irq_and_dev(
			to_free,
			-1,
			NULL,
			IGNORE_IRQ | IGNORE_DEV
		);
	}
	garbage_collect_irq_entries();
	spin_unlock_irqrestore(&irq_lock, flags);
}
EXPORT_SYMBOL(free_irq_by_fd);

static void free_irq_by_irq_and_dev(unsigned int irq, void *dev)
{
	struct irq_entry *to_free;
	unsigned long flags;

	spin_lock_irqsave(&irq_lock, flags);
	to_free = active_fds;
	while (to_free != NULL) {
		do_free_by_irq_and_dev(
			to_free,
			irq,
			dev,
			0
		);
		to_free = to_free->next;
	}
	garbage_collect_irq_entries();
	spin_unlock_irqrestore(&irq_lock, flags);
}


void reactivate_fd(int fd, int irqnum)
{
	/** NOP - we do auto-EOI now **/
=======
	free_irq_by_cb(same_fd, &fd);
}

/* Must be called with irq_lock held */
static struct irq_fd *find_irq_by_fd(int fd, int irqnum, int *index_out)
{
	struct irq_fd *irq;
	int i = 0;
	int fdi;

	for (irq = active_fds; irq != NULL; irq = irq->next) {
		if ((irq->fd == fd) && (irq->irq == irqnum))
			break;
		i++;
	}
	if (irq == NULL) {
		printk(KERN_ERR "find_irq_by_fd doesn't have descriptor %d\n",
		       fd);
		goto out;
	}
	fdi = os_get_pollfd(i);
	if ((fdi != -1) && (fdi != fd)) {
		printk(KERN_ERR "find_irq_by_fd - mismatch between active_fds "
		       "and pollfds, fd %d vs %d, need %d\n", irq->fd,
		       fdi, fd);
		irq = NULL;
		goto out;
	}
	*index_out = i;
 out:
	return irq;
}

void reactivate_fd(int fd, int irqnum)
{
	struct irq_fd *irq;
	unsigned long flags;
	int i;

	spin_lock_irqsave(&irq_lock, flags);
	irq = find_irq_by_fd(fd, irqnum, &i);
	if (irq == NULL) {
		spin_unlock_irqrestore(&irq_lock, flags);
		return;
	}
	os_set_pollfd(i, irq->fd);
	spin_unlock_irqrestore(&irq_lock, flags);

	add_sigio_fd(fd);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
}

void deactivate_fd(int fd, int irqnum)
{
<<<<<<< HEAD
	struct irq_entry *to_free;
	unsigned long flags;

	os_del_epoll_fd(fd);
	spin_lock_irqsave(&irq_lock, flags);
	to_free = get_irq_entry_by_fd(fd);
	if (to_free != NULL) {
		do_free_by_irq_and_dev(
			to_free,
			irqnum,
			NULL,
			IGNORE_DEV
		);
	}
	garbage_collect_irq_entries();
	spin_unlock_irqrestore(&irq_lock, flags);
=======
	struct irq_fd *irq;
	unsigned long flags;
	int i;

	spin_lock_irqsave(&irq_lock, flags);
	irq = find_irq_by_fd(fd, irqnum, &i);
	if (irq == NULL) {
		spin_unlock_irqrestore(&irq_lock, flags);
		return;
	}

	os_set_pollfd(i, -1);
	spin_unlock_irqrestore(&irq_lock, flags);

>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	ignore_sigio_fd(fd);
}
EXPORT_SYMBOL(deactivate_fd);

/*
 * Called just before shutdown in order to provide a clean exec
 * environment in case the system is rebooting.  No locking because
 * that would cause a pointless shutdown hang if something hadn't
 * released the lock.
 */
int deactivate_all_fds(void)
{
<<<<<<< HEAD
	unsigned long flags;
	struct irq_entry *to_free;

	spin_lock_irqsave(&irq_lock, flags);
	/* Stop IO. The IRQ loop has no lock so this is our
	 * only way of making sure we are safe to dispose
	 * of all IRQ handlers
	 */
	os_set_ioignore();
	to_free = active_fds;
	while (to_free != NULL) {
		do_free_by_irq_and_dev(
			to_free,
			-1,
			NULL,
			IGNORE_IRQ | IGNORE_DEV
		);
		to_free = to_free->next;
	}
	garbage_collect_irq_entries();
	spin_unlock_irqrestore(&irq_lock, flags);
	os_close_epoll_fd();
=======
	struct irq_fd *irq;
	int err;

	for (irq = active_fds; irq != NULL; irq = irq->next) {
		err = os_clear_fd_async(irq->fd);
		if (err)
			return err;
	}
	/* If there is a signal already queued, after unblocking ignore it */
	os_set_ioignore();

>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	return 0;
}

/*
 * do_IRQ handles all normal device IRQs (the special
 * SMP cross-CPU interrupts have their own specific
 * handlers).
 */
unsigned int do_IRQ(int irq, struct uml_pt_regs *regs)
{
	struct pt_regs *old_regs = set_irq_regs((struct pt_regs *)regs);
	irq_enter();
	generic_handle_irq(irq);
	irq_exit();
	set_irq_regs(old_regs);
	return 1;
}

void um_free_irq(unsigned int irq, void *dev)
{
	free_irq_by_irq_and_dev(irq, dev);
	free_irq(irq, dev);
}
EXPORT_SYMBOL(um_free_irq);

int um_request_irq(unsigned int irq, int fd, int type,
		   irq_handler_t handler,
		   unsigned long irqflags, const char * devname,
		   void *dev_id)
{
	int err;

	if (fd != -1) {
		err = activate_fd(irq, fd, type, dev_id);
		if (err)
			return err;
	}

	return request_irq(irq, handler, irqflags, devname, dev_id);
}

EXPORT_SYMBOL(um_request_irq);
EXPORT_SYMBOL(reactivate_fd);

/*
 * irq_chip must define at least enable/disable and ack when
 * the edge handler is used.
 */
static void dummy(struct irq_data *d)
{
}

/* This is used for everything else than the timer. */
static struct irq_chip normal_irq_type = {
	.name = "SIGIO",
	.irq_disable = dummy,
	.irq_enable = dummy,
	.irq_ack = dummy,
	.irq_mask = dummy,
	.irq_unmask = dummy,
};

static struct irq_chip SIGVTALRM_irq_type = {
	.name = "SIGVTALRM",
	.irq_disable = dummy,
	.irq_enable = dummy,
	.irq_ack = dummy,
	.irq_mask = dummy,
	.irq_unmask = dummy,
};

void __init init_IRQ(void)
{
	int i;

	irq_set_chip_and_handler(TIMER_IRQ, &SIGVTALRM_irq_type, handle_edge_irq);

<<<<<<< HEAD

	for (i = 1; i < NR_IRQS; i++)
		irq_set_chip_and_handler(i, &normal_irq_type, handle_edge_irq);
	/* Initialize EPOLL Loop */
	os_setup_epoll();
=======
	for (i = 1; i < NR_IRQS; i++)
		irq_set_chip_and_handler(i, &normal_irq_type, handle_edge_irq);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
}

/*
 * IRQ stack entry and exit:
 *
 * Unlike i386, UML doesn't receive IRQs on the normal kernel stack
 * and switch over to the IRQ stack after some preparation.  We use
 * sigaltstack to receive signals on a separate stack from the start.
 * These two functions make sure the rest of the kernel won't be too
 * upset by being on a different stack.  The IRQ stack has a
 * thread_info structure at the bottom so that current et al continue
 * to work.
 *
 * to_irq_stack copies the current task's thread_info to the IRQ stack
 * thread_info and sets the tasks's stack to point to the IRQ stack.
 *
 * from_irq_stack copies the thread_info struct back (flags may have
 * been modified) and resets the task's stack pointer.
 *
 * Tricky bits -
 *
 * What happens when two signals race each other?  UML doesn't block
 * signals with sigprocmask, SA_DEFER, or sa_mask, so a second signal
 * could arrive while a previous one is still setting up the
 * thread_info.
 *
 * There are three cases -
 *     The first interrupt on the stack - sets up the thread_info and
 * handles the interrupt
 *     A nested interrupt interrupting the copying of the thread_info -
 * can't handle the interrupt, as the stack is in an unknown state
 *     A nested interrupt not interrupting the copying of the
 * thread_info - doesn't do any setup, just handles the interrupt
 *
 * The first job is to figure out whether we interrupted stack setup.
 * This is done by xchging the signal mask with thread_info->pending.
 * If the value that comes back is zero, then there is no setup in
 * progress, and the interrupt can be handled.  If the value is
 * non-zero, then there is stack setup in progress.  In order to have
 * the interrupt handled, we leave our signal in the mask, and it will
 * be handled by the upper handler after it has set up the stack.
 *
 * Next is to figure out whether we are the outer handler or a nested
 * one.  As part of setting up the stack, thread_info->real_thread is
 * set to non-NULL (and is reset to NULL on exit).  This is the
 * nesting indicator.  If it is non-NULL, then the stack is already
 * set up and the handler can run.
 */

static unsigned long pending_mask;

unsigned long to_irq_stack(unsigned long *mask_out)
{
	struct thread_info *ti;
	unsigned long mask, old;
	int nested;

	mask = xchg(&pending_mask, *mask_out);
	if (mask != 0) {
		/*
		 * If any interrupts come in at this point, we want to
		 * make sure that their bits aren't lost by our
		 * putting our bit in.  So, this loop accumulates bits
		 * until xchg returns the same value that we put in.
		 * When that happens, there were no new interrupts,
		 * and pending_mask contains a bit for each interrupt
		 * that came in.
		 */
		old = *mask_out;
		do {
			old |= mask;
			mask = xchg(&pending_mask, old);
		} while (mask != old);
		return 1;
	}

	ti = current_thread_info();
	nested = (ti->real_thread != NULL);
	if (!nested) {
		struct task_struct *task;
		struct thread_info *tti;

		task = cpu_tasks[ti->cpu].task;
		tti = task_thread_info(task);

		*ti = *tti;
		ti->real_thread = tti;
		task->stack = ti;
	}

	mask = xchg(&pending_mask, 0);
	*mask_out |= mask | nested;
	return 0;
}

unsigned long from_irq_stack(int nested)
{
	struct thread_info *ti, *to;
	unsigned long mask;

	ti = current_thread_info();

	pending_mask = 1;

	to = ti->real_thread;
	current->stack = to;
	ti->real_thread = NULL;
	*to = *ti;

	mask = xchg(&pending_mask, 0);
	return mask & ~1;
}

