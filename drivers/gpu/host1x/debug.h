/*
 * Tegra host1x Debug
 *
 * Copyright (c) 2011-2013 NVIDIA Corporation.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef __HOST1X_DEBUG_H
#define __HOST1X_DEBUG_H

#include <linux/debugfs.h>
#include <linux/seq_file.h>

struct host1x;

struct output {
<<<<<<< HEAD
	void (*fn)(void *ctx, const char *str, size_t len, bool cont);
=======
	void (*fn)(void *ctx, const char *str, size_t len);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	void *ctx;
	char buf[256];
};

<<<<<<< HEAD
static inline void write_to_seqfile(void *ctx, const char *str, size_t len,
				    bool cont)
=======
static inline void write_to_seqfile(void *ctx, const char *str, size_t len)
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
{
	seq_write((struct seq_file *)ctx, str, len);
}

<<<<<<< HEAD
static inline void write_to_printk(void *ctx, const char *str, size_t len,
				   bool cont)
{
	if (cont)
		pr_cont("%s", str);
	else
		pr_info("%s", str);
}

void __printf(2, 3) host1x_debug_output(struct output *o, const char *fmt, ...);
void __printf(2, 3) host1x_debug_cont(struct output *o, const char *fmt, ...);
=======
static inline void write_to_printk(void *ctx, const char *str, size_t len)
{
	pr_info("%s", str);
}

void __printf(2, 3) host1x_debug_output(struct output *o, const char *fmt, ...);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

extern unsigned int host1x_debug_trace_cmdbuf;

void host1x_debug_init(struct host1x *host1x);
void host1x_debug_deinit(struct host1x *host1x);
void host1x_debug_dump(struct host1x *host1x);
void host1x_debug_dump_syncpts(struct host1x *host1x);

#endif
