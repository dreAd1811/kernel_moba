/*
 * Copyright 2010 Michael Ellerman, IBM Corp.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */

#include <linux/kernel.h>
#include <linux/jump_label.h>
#include <asm/code-patching.h>

<<<<<<< HEAD
=======
#ifdef HAVE_JUMP_LABEL
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
void arch_jump_label_transform(struct jump_entry *entry,
			       enum jump_label_type type)
{
	u32 *addr = (u32 *)(unsigned long)entry->code;

	if (type == JUMP_LABEL_JMP)
		patch_branch(addr, entry->target, 0);
	else
		patch_instruction(addr, PPC_INST_NOP);
}
<<<<<<< HEAD
=======
#endif
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
