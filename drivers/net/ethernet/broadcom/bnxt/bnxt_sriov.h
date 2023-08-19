/* Broadcom NetXtreme-C/E network driver.
 *
 * Copyright (c) 2014-2016 Broadcom Corporation
<<<<<<< HEAD
 * Copyright (c) 2016-2018 Broadcom Limited
=======
 * Copyright (c) 2016-2017 Broadcom Limited
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation.
 */

#ifndef BNXT_SRIOV_H
#define BNXT_SRIOV_H

<<<<<<< HEAD
#define BNXT_FWD_RESP_SIZE_ERR(n)					\
	((offsetof(struct hwrm_fwd_resp_input, encap_resp) + n) >	\
	 sizeof(struct hwrm_fwd_resp_input))

#define BNXT_EXEC_FWD_RESP_SIZE_ERR(n)					\
	((offsetof(struct hwrm_exec_fwd_resp_input, encap_request) + n) >\
	 offsetof(struct hwrm_exec_fwd_resp_input, encap_resp_target_id))

#define BNXT_REJ_FWD_RESP_SIZE_ERR(n)					\
	((offsetof(struct hwrm_reject_fwd_resp_input, encap_request) + n) >\
	 offsetof(struct hwrm_reject_fwd_resp_input, encap_resp_target_id))

#define BNXT_VF_MIN_RSS_CTX	1
#define BNXT_VF_MAX_RSS_CTX	1
#define BNXT_VF_MIN_L2_CTX	1
#define BNXT_VF_MAX_L2_CTX	4

=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
int bnxt_get_vf_config(struct net_device *, int, struct ifla_vf_info *);
int bnxt_set_vf_mac(struct net_device *, int, u8 *);
int bnxt_set_vf_vlan(struct net_device *, int, u16, u8, __be16);
int bnxt_set_vf_bw(struct net_device *, int, int, int);
int bnxt_set_vf_link_state(struct net_device *, int, int);
int bnxt_set_vf_spoofchk(struct net_device *, int, bool);
<<<<<<< HEAD
int bnxt_set_vf_trust(struct net_device *dev, int vf_id, bool trust);
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
int bnxt_sriov_configure(struct pci_dev *pdev, int num_vfs);
void bnxt_sriov_disable(struct bnxt *);
void bnxt_hwrm_exec_fwd_req(struct bnxt *);
void bnxt_update_vf_mac(struct bnxt *);
<<<<<<< HEAD
int bnxt_approve_mac(struct bnxt *, u8 *, bool);
=======
int bnxt_approve_mac(struct bnxt *, u8 *);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
#endif
