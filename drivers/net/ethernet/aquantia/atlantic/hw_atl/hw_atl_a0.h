/*
 * aQuantia Corporation Network Driver
 * Copyright (C) 2014-2017 aQuantia Corporation. All rights reserved
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 */

/* File hw_atl_a0.h: Declaration of abstract interface for Atlantic hardware
 * specific functions.
 */

#ifndef HW_ATL_A0_H
#define HW_ATL_A0_H

#include "../aq_common.h"

<<<<<<< HEAD
extern const struct aq_hw_caps_s hw_atl_a0_caps_aqc100;
extern const struct aq_hw_caps_s hw_atl_a0_caps_aqc107;
extern const struct aq_hw_caps_s hw_atl_a0_caps_aqc108;
extern const struct aq_hw_caps_s hw_atl_a0_caps_aqc109;

extern const struct aq_hw_ops hw_atl_ops_a0;
=======
#ifndef PCI_VENDOR_ID_AQUANTIA

#define PCI_VENDOR_ID_AQUANTIA  0x1D6A
#define HW_ATL_DEVICE_ID_0001   0x0001
#define HW_ATL_DEVICE_ID_D100   0xD100
#define HW_ATL_DEVICE_ID_D107   0xD107
#define HW_ATL_DEVICE_ID_D108   0xD108
#define HW_ATL_DEVICE_ID_D109   0xD109

#define HW_ATL_NIC_NAME "aQuantia AQtion 5Gbit Network Adapter"

#endif

struct aq_hw_ops *hw_atl_a0_get_ops_by_id(struct pci_dev *pdev);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

#endif /* HW_ATL_A0_H */
