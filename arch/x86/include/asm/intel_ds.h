#ifndef _ASM_INTEL_DS_H
#define _ASM_INTEL_DS_H

#include <linux/percpu-defs.h>

#define BTS_BUFFER_SIZE		(PAGE_SIZE << 4)
#define PEBS_BUFFER_SIZE	(PAGE_SIZE << 4)

/* The maximal number of PEBS events: */
#define MAX_PEBS_EVENTS		8
<<<<<<< HEAD
#define MAX_FIXED_PEBS_EVENTS	3
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/*
 * A debug store configuration.
 *
 * We only support architectures that use 64bit fields.
 */
struct debug_store {
	u64	bts_buffer_base;
	u64	bts_index;
	u64	bts_absolute_maximum;
	u64	bts_interrupt_threshold;
	u64	pebs_buffer_base;
	u64	pebs_index;
	u64	pebs_absolute_maximum;
	u64	pebs_interrupt_threshold;
<<<<<<< HEAD
	u64	pebs_event_reset[MAX_PEBS_EVENTS + MAX_FIXED_PEBS_EVENTS];
=======
	u64	pebs_event_reset[MAX_PEBS_EVENTS];
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
} __aligned(PAGE_SIZE);

DECLARE_PER_CPU_PAGE_ALIGNED(struct debug_store, cpu_debug_store);

struct debug_store_buffers {
	char	bts_buffer[BTS_BUFFER_SIZE];
	char	pebs_buffer[PEBS_BUFFER_SIZE];
};

#endif
