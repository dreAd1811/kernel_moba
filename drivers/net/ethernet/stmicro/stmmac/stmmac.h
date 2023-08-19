/*******************************************************************************
  Copyright (C) 2007-2009  STMicroelectronics Ltd

  This program is free software; you can redistribute it and/or modify it
  under the terms and conditions of the GNU General Public License,
  version 2, as published by the Free Software Foundation.

  This program is distributed in the hope it will be useful, but WITHOUT
  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
  more details.

  The full GNU General Public License is included in this distribution in
  the file called "COPYING".

  Author: Giuseppe Cavallaro <peppe.cavallaro@st.com>
*******************************************************************************/

#ifndef __STMMAC_H__
#define __STMMAC_H__

#define STMMAC_RESOURCE_NAME   "stmmaceth"
#define DRV_MODULE_VERSION	"Jan_2016"

#include <linux/clk.h>
#include <linux/stmmac.h>
#include <linux/phy.h>
#include <linux/pci.h>
#include "common.h"
#include <linux/ptp_clock_kernel.h>
#include <linux/reset.h>
<<<<<<< HEAD
=======
#ifdef CONFIG_MSM_BOOT_TIME_MARKER
#include <soc/qcom/boot_stats.h>
#endif
#include "dwmac-qcom-ipa-offload.h"
#include <linux/udp.h>
#include <linux/if_ether.h>
#include <linux/icmp.h>
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

struct stmmac_resources {
	void __iomem *addr;
	const char *mac;
	int wol_irq;
	int lpi_irq;
	int irq;
};

struct stmmac_tx_info {
	dma_addr_t buf;
	bool map_as_page;
	unsigned len;
	bool last_segment;
	bool is_jumbo;
};

/* Frequently used values are kept adjacent for cache effect */
struct stmmac_tx_queue {
<<<<<<< HEAD
	u32 tx_count_frames;
	struct timer_list txtimer;
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	u32 queue_index;
	struct stmmac_priv *priv_data;
	struct dma_extended_desc *dma_etx ____cacheline_aligned_in_smp;
	struct dma_desc *dma_tx;
	struct sk_buff **tx_skbuff;
	struct stmmac_tx_info *tx_skbuff_dma;
	unsigned int cur_tx;
	unsigned int dirty_tx;
	dma_addr_t dma_tx_phy;
	u32 tx_tail_addr;
<<<<<<< HEAD
	u32 mss;
=======
	bool skip_sw;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
};

struct stmmac_rx_queue {
	u32 queue_index;
	struct stmmac_priv *priv_data;
	struct dma_extended_desc *dma_erx;
	struct dma_desc *dma_rx ____cacheline_aligned_in_smp;
	struct sk_buff **rx_skbuff;
	dma_addr_t *rx_skbuff_dma;
	unsigned int cur_rx;
	unsigned int dirty_rx;
	u32 rx_zeroc_thresh;
	dma_addr_t dma_rx_phy;
	u32 rx_tail_addr;
<<<<<<< HEAD
};

struct stmmac_channel {
	struct napi_struct napi ____cacheline_aligned_in_smp;
	struct stmmac_priv *priv_data;
	u32 index;
	int has_rx;
	int has_tx;
};

struct stmmac_tc_entry {
	bool in_use;
	bool in_hw;
	bool is_last;
	bool is_frag;
	void *frag_ptr;
	unsigned int table_pos;
	u32 handle;
	u32 prio;
	struct {
		u32 match_data;
		u32 match_en;
		u8 af:1;
		u8 rf:1;
		u8 im:1;
		u8 nc:1;
		u8 res1:4;
		u8 frame_offset;
		u8 ok_index;
		u8 dma_ch_no;
		u32 res2;
	} __packed val;
};

#define STMMAC_PPS_MAX		4
struct stmmac_pps_cfg {
	bool available;
	struct timespec64 start;
	struct timespec64 period;
=======
	struct napi_struct napi ____cacheline_aligned_in_smp;
	bool skip_sw;
	bool en_fep;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
};

struct stmmac_priv {
	/* Frequently used values are kept adjacent for cache effect */
<<<<<<< HEAD
	u32 tx_coal_frames;
	u32 tx_coal_timer;
=======
	u32 tx_count_frames;
	u32 tx_coal_frames;
	u32 tx_coal_timer;
	bool tx_coal_timer_disable;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	int tx_coalesce;
	int hwts_tx_en;
	bool tx_path_in_lpi_mode;
<<<<<<< HEAD
=======
	struct timer_list txtimer;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	bool tso;

	unsigned int dma_buf_sz;
	unsigned int rx_copybreak;
	u32 rx_riwt;
	int hwts_rx_en;

	void __iomem *ioaddr;
	struct net_device *dev;
	struct device *device;
	struct mac_device_info *hw;
<<<<<<< HEAD
	int (*hwif_quirks)(struct stmmac_priv *priv);
=======
	struct phy_device *phydev;
	/* Mutex lock */
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	struct mutex lock;

	/* RX Queue */
	struct stmmac_rx_queue rx_queue[MTL_MAX_RX_QUEUES];

	/* TX Queue */
	struct stmmac_tx_queue tx_queue[MTL_MAX_TX_QUEUES];

<<<<<<< HEAD
	/* Generic channel for NAPI */
	struct stmmac_channel channel[STMMAC_CH_MAX];

	bool oldlink;
=======
	int oldlink;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	int speed;
	int oldduplex;
	unsigned int flow_ctrl;
	unsigned int pause;
	struct mii_bus *mii;
	int mii_irq[PHY_MAX_ADDR];

	struct stmmac_extra_stats xstats ____cacheline_aligned_in_smp;
<<<<<<< HEAD
	struct stmmac_safety_stats sstats;
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	struct plat_stmmacenet_data *plat;
	struct dma_features dma_cap;
	struct stmmac_counters mmc;
	int hw_cap_support;
	int synopsys_id;
	u32 msg_enable;
	int wolopts;
	int wol_irq;
	int clk_csr;
	struct timer_list eee_ctrl_timer;
	int lpi_irq;
	int eee_enabled;
	int eee_active;
	int tx_lpi_timer;
	unsigned int mode;
<<<<<<< HEAD
	unsigned int chain_mode;
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	int extend_desc;
	struct ptp_clock *ptp_clock;
	struct ptp_clock_info ptp_clock_ops;
	unsigned int default_addend;
<<<<<<< HEAD
	u32 sub_second_inc;
	u32 systime_flags;
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	u32 adv_ts;
	int use_riwt;
	int irq_wake;
	spinlock_t ptp_lock;
	void __iomem *mmcaddr;
	void __iomem *ptpaddr;
<<<<<<< HEAD

=======
	u32 mss;
	bool boot_kpi;
	int current_loopback;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
#ifdef CONFIG_DEBUG_FS
	struct dentry *dbgfs_dir;
	struct dentry *dbgfs_rings_status;
	struct dentry *dbgfs_dma_cap;
#endif
<<<<<<< HEAD

	unsigned long state;
	struct workqueue_struct *wq;
	struct work_struct service_task;

	/* TC Handling */
	unsigned int tc_entries_max;
	unsigned int tc_off_max;
	struct stmmac_tc_entry *tc_entries;

	/* Pulse Per Second output */
	struct stmmac_pps_cfg pps[STMMAC_PPS_MAX];
};

enum stmmac_state {
	STMMAC_DOWN,
	STMMAC_RESET_REQUESTED,
	STMMAC_RESETING,
	STMMAC_SERVICE_SCHED,
};

=======
	bool hw_offload_enabled;
};

struct stmmac_emb_smmu_cb_ctx {
	bool valid;
	struct platform_device *pdev_master;
	struct platform_device *smmu_pdev;
	struct dma_iommu_mapping *mapping;
	struct iommu_domain *iommu_domain;
	u32 va_start;
	u32 va_size;
	u32 va_end;
	int ret;
};

extern struct stmmac_emb_smmu_cb_ctx stmmac_emb_smmu_ctx;

#define GET_MEM_PDEV_DEV (stmmac_emb_smmu_ctx.valid ? \
			&stmmac_emb_smmu_ctx.smmu_pdev->dev : priv->device)

#define MICREL_PHY_ID 0x00221620

#define MMC_CONFIG 0x24

int ethqos_handle_prv_ioctl(struct net_device *dev, struct ifreq *rq, int cmd);
int ethqos_init_pps(struct stmmac_priv *priv);

int ethqos_phy_intr_enable(struct stmmac_priv *priv);
extern bool phy_intr_en;
void qcom_ethqos_request_phy_wol(struct plat_stmmacenet_data *plat_dat);

>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
int stmmac_mdio_unregister(struct net_device *ndev);
int stmmac_mdio_register(struct net_device *ndev);
int stmmac_mdio_reset(struct mii_bus *mii);
void stmmac_set_ethtool_ops(struct net_device *netdev);

void stmmac_ptp_register(struct stmmac_priv *priv);
void stmmac_ptp_unregister(struct stmmac_priv *priv);
int stmmac_resume(struct device *dev);
int stmmac_suspend(struct device *dev);
int stmmac_dvr_remove(struct device *dev);
int stmmac_dvr_probe(struct device *device,
		     struct plat_stmmacenet_data *plat_dat,
		     struct stmmac_resources *res);
void stmmac_disable_eee_mode(struct stmmac_priv *priv);
bool stmmac_eee_init(struct stmmac_priv *priv);
<<<<<<< HEAD

=======
bool qcom_ethqos_ipa_enabled(void);
u16 icmp_fast_csum(u16 old_csum);
void swap_ip_port(struct sk_buff *skb, unsigned int eth_type);
unsigned int dwmac_qcom_get_eth_type(unsigned char *buf);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
#endif /* __STMMAC_H__ */
