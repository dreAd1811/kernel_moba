/*
 * Copyright (C) 2001 - 2007 Jeff Dike (jdike@{addtoit,linux.intel}.com)
 * Licensed under the GPL
 */

#ifndef __IRQ_USER_H__
#define __IRQ_USER_H__

#include <sysdep/ptrace.h>
<<<<<<< HEAD
#include <stdbool.h>
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

struct irq_fd {
	struct irq_fd *next;
	void *id;
	int fd;
	int type;
	int irq;
	int events;
<<<<<<< HEAD
	bool active;
	bool pending;
	bool purge;
};

#define IRQ_READ  0
#define IRQ_WRITE 1
#define IRQ_NONE 2
#define MAX_IRQ_TYPE (IRQ_NONE + 1)


=======
	int current_events;
};

enum { IRQ_READ, IRQ_WRITE };
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

struct siginfo;
extern void sigio_handler(int sig, struct siginfo *unused_si, struct uml_pt_regs *regs);
extern void free_irq_by_fd(int fd);
extern void reactivate_fd(int fd, int irqnum);
extern void deactivate_fd(int fd, int irqnum);
extern int deactivate_all_fds(void);
extern int activate_ipi(int fd, int pid);

#endif
