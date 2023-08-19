/* SPDX-License-Identifier: GPL-2.0 */
#ifndef __RENESAS_CLK_DIV6_H__
#define __RENESAS_CLK_DIV6_H__

struct clk *cpg_div6_register(const char *name, unsigned int num_parents,
<<<<<<< HEAD
			      const char **parent_names, void __iomem *reg,
			      struct raw_notifier_head *notifiers);
=======
			      const char **parent_names, void __iomem *reg);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

#endif
