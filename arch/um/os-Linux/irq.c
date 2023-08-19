/*
<<<<<<< HEAD
 * Copyright (C) 2017 - Cambridge Greys Ltd
 * Copyright (C) 2011 - 2014 Cisco Systems Inc
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
 * Copyright (C) 2000 - 2007 Jeff Dike (jdike@{addtoit,linux.intel}.com)
 * Licensed under the GPL
 */

#include <stdlib.h>
#include <errno.h>
<<<<<<< HEAD
#include <sys/epoll.h>
=======
#include <poll.h>
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
#include <signal.h>
#include <string.h>
#include <irq_user.h>
#include <os.h>
#include <um_malloc.h>

<<<<<<< HEAD
/* Epoll support */

static int epollfd = -1;

#define MAX_EPOLL_EVENTS 64

static struct epoll_event epoll_events[MAX_EPOLL_EVENTS];

/* Helper to return an Epoll data pointer from an epoll event structure.
 * We need to keep this one on the userspace side to keep includes separate
 */

void *os_epoll_get_data_pointer(int index)
{
	return epoll_events[index].data.ptr;
}

/* Helper to compare events versus the events in the epoll structure.
 * Same as above - needs to be on the userspace side
 */


int os_epoll_triggered(int index, int events)
{
	return epoll_events[index].events & events;
}
/* Helper to set the event mask.
 * The event mask is opaque to the kernel side, because it does not have
 * access to the right includes/defines for EPOLL constants.
 */

int os_event_mask(int irq_type)
{
	if (irq_type == IRQ_READ)
		return EPOLLIN | EPOLLPRI;
	if (irq_type == IRQ_WRITE)
		return EPOLLOUT;
	return 0;
}

/*
 * Initial Epoll Setup
 */
int os_setup_epoll(void)
{
	epollfd = epoll_create(MAX_EPOLL_EVENTS);
	return epollfd;
}

/*
 * Helper to run the actual epoll_wait
 */
int os_waiting_for_events_epoll(void)
{
	int n, err;

	n = epoll_wait(epollfd,
		(struct epoll_event *) &epoll_events, MAX_EPOLL_EVENTS, 0);
	if (n < 0) {
		err = -errno;
		if (errno != EINTR)
			printk(
				UM_KERN_ERR "os_waiting_for_events:"
				" epoll returned %d, error = %s\n", n,
				strerror(errno)
			);
		return err;
	}
	return n;
}


/*
 * Helper to add a fd to epoll
 */
int os_add_epoll_fd(int events, int fd, void *data)
{
	struct epoll_event event;
	int result;

	event.data.ptr = data;
	event.events = events | EPOLLET;
	result = epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &event);
	if ((result) && (errno == EEXIST))
		result = os_mod_epoll_fd(events, fd, data);
	if (result)
		printk("epollctl add err fd %d, %s\n", fd, strerror(errno));
	return result;
}

/*
 * Helper to mod the fd event mask and/or data backreference
 */
int os_mod_epoll_fd(int events, int fd, void *data)
{
	struct epoll_event event;
	int result;

	event.data.ptr = data;
	event.events = events;
	result = epoll_ctl(epollfd, EPOLL_CTL_MOD, fd, &event);
	if (result)
		printk(UM_KERN_ERR
			"epollctl mod err fd %d, %s\n", fd, strerror(errno));
	return result;
}

/*
 * Helper to delete the epoll fd
 */
int os_del_epoll_fd(int fd)
{
	struct epoll_event event;
	int result;
	/* This is quiet as we use this as IO ON/OFF - so it is often
	 * invoked on a non-existent fd
	 */
	result = epoll_ctl(epollfd, EPOLL_CTL_DEL, fd, &event);
	return result;
=======
/*
 * Locked by irq_lock in arch/um/kernel/irq.c.  Changed by os_create_pollfd
 * and os_free_irq_by_cb, which are called under irq_lock.
 */
static struct pollfd *pollfds = NULL;
static int pollfds_num = 0;
static int pollfds_size = 0;

int os_waiting_for_events(struct irq_fd *active_fds)
{
	struct irq_fd *irq_fd;
	int i, n, err;

	n = poll(pollfds, pollfds_num, 0);
	if (n < 0) {
		err = -errno;
		if (errno != EINTR)
			printk(UM_KERN_ERR "os_waiting_for_events:"
			       " poll returned %d, errno = %d\n", n, errno);
		return err;
	}

	if (n == 0)
		return 0;

	irq_fd = active_fds;

	for (i = 0; i < pollfds_num; i++) {
		if (pollfds[i].revents != 0) {
			irq_fd->current_events = pollfds[i].revents;
			pollfds[i].fd = -1;
		}
		irq_fd = irq_fd->next;
	}
	return n;
}

int os_create_pollfd(int fd, int events, void *tmp_pfd, int size_tmpfds)
{
	if (pollfds_num == pollfds_size) {
		if (size_tmpfds <= pollfds_size * sizeof(pollfds[0])) {
			/* return min size needed for new pollfds area */
			return (pollfds_size + 1) * sizeof(pollfds[0]);
		}

		if (pollfds != NULL) {
			memcpy(tmp_pfd, pollfds,
			       sizeof(pollfds[0]) * pollfds_size);
			/* remove old pollfds */
			kfree(pollfds);
		}
		pollfds = tmp_pfd;
		pollfds_size++;
	} else
		kfree(tmp_pfd);	/* remove not used tmp_pfd */

	pollfds[pollfds_num] = ((struct pollfd) { .fd		= fd,
						  .events	= events,
						  .revents	= 0 });
	pollfds_num++;

	return 0;
}

void os_free_irq_by_cb(int (*test)(struct irq_fd *, void *), void *arg,
		struct irq_fd *active_fds, struct irq_fd ***last_irq_ptr2)
{
	struct irq_fd **prev;
	int i = 0;

	prev = &active_fds;
	while (*prev != NULL) {
		if ((*test)(*prev, arg)) {
			struct irq_fd *old_fd = *prev;
			if ((pollfds[i].fd != -1) &&
			    (pollfds[i].fd != (*prev)->fd)) {
				printk(UM_KERN_ERR "os_free_irq_by_cb - "
				       "mismatch between active_fds and "
				       "pollfds, fd %d vs %d\n",
				       (*prev)->fd, pollfds[i].fd);
				goto out;
			}

			pollfds_num--;

			/*
			 * This moves the *whole* array after pollfds[i]
			 * (though it doesn't spot as such)!
			 */
			memmove(&pollfds[i], &pollfds[i + 1],
			       (pollfds_num - i) * sizeof(pollfds[0]));
			if (*last_irq_ptr2 == &old_fd->next)
				*last_irq_ptr2 = prev;

			*prev = (*prev)->next;
			if (old_fd->type == IRQ_WRITE)
				ignore_sigio_fd(old_fd->fd);
			kfree(old_fd);
			continue;
		}
		prev = &(*prev)->next;
		i++;
	}
 out:
	return;
}

int os_get_pollfd(int i)
{
	return pollfds[i].fd;
}

void os_set_pollfd(int i, int fd)
{
	pollfds[i].fd = fd;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
}

void os_set_ioignore(void)
{
	signal(SIGIO, SIG_IGN);
}
<<<<<<< HEAD

void os_close_epoll_fd(void)
{
	/* Needed so we do not leak an fd when rebooting */
	os_close_file(epollfd);
}
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
