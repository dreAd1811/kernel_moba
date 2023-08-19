<<<<<<< HEAD
/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Copyright (c) 2017-2020, The Linux Foundation. All rights reserved.
=======
/* Copyright (c) 2018-2019, The Linux Foundation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
 */

#ifndef _NPU_MGR_H
#define _NPU_MGR_H

/* -------------------------------------------------------------------------
 * Includes
 * -------------------------------------------------------------------------
 */
#include <linux/spinlock.h>
#include "npu_hw_access.h"
#include "npu_common.h"

/* -------------------------------------------------------------------------
 * Defines
 * -------------------------------------------------------------------------
 */
<<<<<<< HEAD
#define NW_RSC_TIMEOUT_MS (1000 * 5) /* set for 5 seconds */
#define NW_RSC_TIMEOUT msecs_to_jiffies(NW_RSC_TIMEOUT_MS)
#define NW_CMD_TIMEOUT_MS (1000 * 20) /* set for 20 seconds */
#define NW_CMD_TIMEOUT msecs_to_jiffies(NW_CMD_TIMEOUT_MS)
#define NW_PWR_UP_TIMEOUT_MS (1000 * 60) /* set for 60 seconds */
#define NW_PWR_UP_TIMEOUT msecs_to_jiffies(NW_PWR_UP_TIMEOUT_MS)
#define NW_DEBUG_TIMEOUT_MS (1000 * 60 * 30) /* set for 30 minutes */
#define NW_DEBUG_TIMEOUT msecs_to_jiffies(NW_DEBUG_TIMEOUT_MS)
#define NPU_MBOX_IDLE_TIMEOUT_MS 500 /* set for 500ms */
#define NPU_MBOX_IDLE_TIMEOUT msecs_to_jiffies(NPU_MBOX_IDLE_TIMEOUT_MS)
#define NPU_FW_TIMEOUT_POLL_INTERVAL_MS 10
#define NPU_FW_ACK_TIMEOUT_MS 5000
#define NPU_FW_BRINGUP_TIMEOUT_MS (1000 * 60) /* set for 60 seconds */
#define FIRMWARE_VERSION 0x00001000
#define MAX_LOADED_NETWORK 32
#define NPU_IPC_BUF_LENGTH 4096
=======
#define NW_CMD_TIMEOUT_MS (1000 * 60 * 5) /* set for 5 minutes */
#define NW_CMD_TIMEOUT msecs_to_jiffies(NW_CMD_TIMEOUT_MS)
#define NW_DEBUG_TIMEOUT_MS (1000 * 60 * 30) /* set for 30 minutes */
#define NW_DEBUG_TIMEOUT msecs_to_jiffies(NW_DEBUG_TIMEOUT_MS)
#define FIRMWARE_VERSION 0x00001000
#define MAX_LOADED_NETWORK 32
#define NPU_IPC_BUF_LENGTH 512
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

#define FW_DBG_MODE_PAUSE        (1 << 0)
#define FW_DBG_MODE_INC_TIMEOUT  (1 << 1)
#define FW_DBG_DISABLE_WDOG      (1 << 2)

/* -------------------------------------------------------------------------
 * Data Structures
 * -------------------------------------------------------------------------
 */
<<<<<<< HEAD

struct npu_network_cmd {
	struct list_head list;
	uint32_t cmd_type;
	uint32_t cmd_id;
	uint32_t trans_id;
	bool async;
	struct completion cmd_done;
	/* stats buf info */
	uint32_t stats_buf_size;
	void __user *stats_buf_u;
	void *stats_buf;
	int ret_status;
};

struct npu_misc_cmd {
	struct list_head list;
	uint32_t cmd_type;
	uint32_t trans_id;
	union {
		struct msm_npu_property prop;
		uint32_t data[32];
	} u;
	struct completion cmd_done;
	int ret_status;
};

=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
struct npu_network {
	uint64_t id;
	int buf_hdl;
	uint64_t phy_add;
	uint32_t size;
	uint32_t first_block_size;
	uint32_t network_hdl;
	uint32_t priority;
	uint32_t cur_perf_mode;
	uint32_t init_perf_mode;
	uint32_t num_layers;
<<<<<<< HEAD
=======
	void *stats_buf;
	void __user *stats_buf_u;
	uint32_t stats_buf_size;
	uint32_t trans_id;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	atomic_t ref_cnt;
	bool is_valid;
	bool is_active;
	bool fw_error;
<<<<<<< HEAD
	bool is_async;
	struct npu_client *client;
	struct list_head cmd_list;
};

enum fw_state {
	FW_UNLOADED = 0,
	FW_LOADED = 1,
	FW_ENABLED = 2,
=======
	bool cmd_pending;
	bool cmd_async;
	int cmd_ret_status;
	struct completion cmd_done;
	struct npu_client *client;
};

enum fw_state {
	FW_DISABLED = 0,
	FW_ENABLED = 1,
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
};

struct npu_host_ctx {
	struct mutex lock;
<<<<<<< HEAD
	struct npu_device *npu_dev;
	void *subsystem_handle;
=======
	void *subsystem_handle;
	struct npu_device *npu_dev;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	enum fw_state fw_state;
	int32_t fw_ref_cnt;
	int32_t npu_init_cnt;
	int32_t power_vote_num;
<<<<<<< HEAD
	struct work_struct ipc_irq_work;
	struct work_struct wdg_err_irq_work;
	struct work_struct bridge_mbox_work;
	struct work_struct load_fw_work;
	struct work_struct update_pwr_work;
	struct delayed_work disable_fw_work;
	struct workqueue_struct *wq;
	struct workqueue_struct *wq_pri;
	struct completion fw_deinit_done;
	struct completion fw_bringup_done;
	struct completion fw_shutdown_done;
	struct completion npu_power_up_done;
	int32_t network_num;
	struct npu_network networks[MAX_LOADED_NETWORK];
	struct kmem_cache *network_cmd_cache;
	struct kmem_cache *misc_cmd_cache;
	struct kmem_cache *stats_buf_cache;
	bool sys_cache_disable;
	bool auto_pil_disable;
	uint32_t fw_dbg_mode;
	uint32_t exec_flags_override;
	atomic_t ipc_trans_id;
	atomic_t network_execute_cnt;
=======
	struct work_struct irq_work;
	struct delayed_work fw_deinit_work;
	atomic_t fw_deinit_work_cnt;
	struct workqueue_struct *wq;
	struct completion loopback_done;
	struct completion fw_deinit_done;
	struct completion property_done;
	void *prop_buf;
	int32_t network_num;
	struct npu_network networks[MAX_LOADED_NETWORK];
	bool sys_cache_disable;
	uint32_t fw_dbg_mode;
	uint32_t exec_flags_override;
	uint32_t fw_unload_delay_ms;
	atomic_t ipc_trans_id;
	atomic_t network_execute_cnt;
	int cmd_ret_status;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	uint32_t err_irq_sts;
	uint32_t wdg_irq_sts;
	bool fw_error;
<<<<<<< HEAD
	bool cancel_work;
	bool app_crashed;
	struct notifier_block nb;
	struct notifier_block panic_nb;
	void *notif_hdle;
	spinlock_t bridge_mbox_lock;
	bool bridge_mbox_pwr_on;
	void *ipc_msg_buf;
	struct list_head misc_cmd_list;

	struct msm_npu_property fw_caps;
	bool fw_caps_valid;
	uint32_t fw_caps_err_code;
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
};

struct npu_device;

/* -------------------------------------------------------------------------
 * Function Prototypes
 * -------------------------------------------------------------------------
 */
int npu_host_init(struct npu_device *npu_dev);
void npu_host_deinit(struct npu_device *npu_dev);

/* Host Driver IPC Interface */
int npu_host_ipc_pre_init(struct npu_device *npu_dev);
int npu_host_ipc_post_init(struct npu_device *npu_dev);
void npu_host_ipc_deinit(struct npu_device *npu_dev);
int npu_host_ipc_send_cmd(struct npu_device *npu_dev, uint32_t queueIndex,
	void *pCmd);
int npu_host_ipc_read_msg(struct npu_device *npu_dev, uint32_t queueIndex,
	uint32_t *pMsg);
<<<<<<< HEAD
int npu_host_get_ipc_queue_size(struct npu_device *npu_dev, uint32_t q_idx);
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

int32_t npu_host_get_info(struct npu_device *npu_dev,
	struct msm_npu_get_info_ioctl *get_info_ioctl);
int32_t npu_host_map_buf(struct npu_client *client,
	struct msm_npu_map_buf_ioctl *map_ioctl);
int32_t npu_host_unmap_buf(struct npu_client *client,
	struct msm_npu_unmap_buf_ioctl *unmap_ioctl);
<<<<<<< HEAD
=======
int32_t npu_host_load_network(struct npu_client *client,
	struct msm_npu_load_network_ioctl *load_ioctl);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
int32_t npu_host_load_network_v2(struct npu_client *client,
	struct msm_npu_load_network_ioctl_v2 *load_ioctl,
	struct msm_npu_patch_info_v2 *patch_info);
int32_t npu_host_unload_network(struct npu_client *client,
	struct msm_npu_unload_network_ioctl *unload);
<<<<<<< HEAD
=======
int32_t npu_host_exec_network(struct npu_client *client,
	struct msm_npu_exec_network_ioctl *exec_ioctl);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
int32_t npu_host_exec_network_v2(struct npu_client *client,
	struct msm_npu_exec_network_ioctl_v2 *exec_ioctl,
	struct msm_npu_patch_buf_info *patch_buf_info);
int32_t npu_host_loopback_test(struct npu_device *npu_dev);
int32_t npu_host_set_fw_property(struct npu_device *npu_dev,
			struct msm_npu_property *property);
int32_t npu_host_get_fw_property(struct npu_device *npu_dev,
			struct msm_npu_property *property);
void npu_host_cleanup_networks(struct npu_client *client);
<<<<<<< HEAD
int npu_host_notify_fw_pwr_state(struct npu_device *npu_dev,
	uint32_t pwr_level, bool post);
int npu_host_update_power(struct npu_device *npu_dev);
int32_t npu_host_set_perf_mode(struct npu_client *client, uint32_t network_hdl,
	uint32_t perf_mode);
int32_t npu_host_get_perf_mode(struct npu_client *client, uint32_t network_hdl);
void npu_host_suspend(struct npu_device *npu_dev);
void npu_dump_debug_info(struct npu_device *npu_dev);
void npu_dump_ipc_packet(struct npu_device *npu_dev, void *cmd_ptr);
=======
int32_t npu_host_set_perf_mode(struct npu_client *client, uint32_t network_hdl,
	uint32_t perf_mode);
int32_t npu_host_get_perf_mode(struct npu_client *client, uint32_t network_hdl);
void npu_dump_debug_timeout_stats(struct npu_device *npu_dev);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

#endif /* _NPU_MGR_H */
