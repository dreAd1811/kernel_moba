/* Copyright (c) 2015-2016, The Linux Foundation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#ifndef _EMAC_SGMII_H_
#define _EMAC_SGMII_H_

struct emac_adapter;
struct platform_device;

<<<<<<< HEAD
/** emac_sgmii - internal emac phy
 * @init initialization function
 * @open called when the driver is opened
 * @close called when the driver is closed
 * @link_change called when the link state changes
 */
struct sgmii_ops {
	int (*init)(struct emac_adapter *adpt);
	int (*open)(struct emac_adapter *adpt);
	void (*close)(struct emac_adapter *adpt);
	int (*link_change)(struct emac_adapter *adpt, bool link_state);
	void (*reset)(struct emac_adapter *adpt);
};
=======
typedef int (*emac_sgmii_function)(struct emac_adapter *adpt);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/** emac_sgmii - internal emac phy
 * @base base address
 * @digital per-lane digital block
 * @irq the interrupt number
 * @decode_error_count reference count of consecutive decode errors
<<<<<<< HEAD
 * @sgmii_ops sgmii ops
=======
 * @initialize initialization function
 * @open called when the driver is opened
 * @close called when the driver is closed
 * @link_up called when the link comes up
 * @link_down called when the link comes down
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
 */
struct emac_sgmii {
	void __iomem		*base;
	void __iomem		*digital;
	unsigned int		irq;
	atomic_t		decode_error_count;
<<<<<<< HEAD
	struct	sgmii_ops	*sgmii_ops;
};

int emac_sgmii_config(struct platform_device *pdev, struct emac_adapter *adpt);
=======
	emac_sgmii_function	initialize;
	emac_sgmii_function	open;
	emac_sgmii_function	close;
	emac_sgmii_function	link_up;
	emac_sgmii_function	link_down;
};

int emac_sgmii_config(struct platform_device *pdev, struct emac_adapter *adpt);
void emac_sgmii_reset(struct emac_adapter *adpt);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

int emac_sgmii_init_fsm9900(struct emac_adapter *adpt);
int emac_sgmii_init_qdf2432(struct emac_adapter *adpt);
int emac_sgmii_init_qdf2400(struct emac_adapter *adpt);

<<<<<<< HEAD
int emac_sgmii_init(struct emac_adapter *adpt);
int emac_sgmii_open(struct emac_adapter *adpt);
void emac_sgmii_close(struct emac_adapter *adpt);
int emac_sgmii_link_change(struct emac_adapter *adpt, bool link_state);
void emac_sgmii_reset(struct emac_adapter *adpt);
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
#endif
