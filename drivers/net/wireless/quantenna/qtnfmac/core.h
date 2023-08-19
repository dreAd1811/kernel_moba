/*
 * Copyright (c) 2015-2016 Quantenna Communications, Inc.
 * All rights reserved.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#ifndef _QTN_FMAC_CORE_H_
#define _QTN_FMAC_CORE_H_

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/semaphore.h>
#include <linux/ip.h>
#include <linux/skbuff.h>
#include <linux/if_arp.h>
#include <linux/etherdevice.h>
#include <net/sock.h>
#include <net/lib80211.h>
#include <net/cfg80211.h>
#include <linux/vmalloc.h>
#include <linux/firmware.h>
#include <linux/ctype.h>
#include <linux/workqueue.h>
#include <linux/slab.h>

#include "qlink.h"
#include "trans.h"

#undef pr_fmt
#define pr_fmt(fmt)	KBUILD_MODNAME ": %s: " fmt, __func__

<<<<<<< HEAD
#define QTNF_MAX_VSIE_LEN		255
#define QTNF_MAX_INTF			8
#define QTNF_MAX_EVENT_QUEUE_LEN	255
=======
#define QTNF_MAX_SSID_LIST_LENGTH	2
#define QTNF_MAX_VSIE_LEN		255
#define QTNF_MAX_INTF			8
#define QTNF_MAX_EVENT_QUEUE_LEN	255
#define QTNF_DEFAULT_BG_SCAN_PERIOD	300
#define QTNF_MAX_BG_SCAN_PERIOD		0xffff
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
#define QTNF_SCAN_TIMEOUT_SEC		15

#define QTNF_DEF_BSS_PRIORITY		0
#define QTNF_DEF_WDOG_TIMEOUT		5
#define QTNF_TX_TIMEOUT_TRSHLD		100

<<<<<<< HEAD
extern const struct net_device_ops qtnf_netdev_ops;

struct qtnf_bus;
struct qtnf_vif;

=======
#define QTNF_STATE_AP_CONFIG		BIT(2)
#define QTNF_STATE_AP_START		BIT(1)

extern const struct net_device_ops qtnf_netdev_ops;
struct qtnf_bus;
struct qtnf_vif;

struct qtnf_bss_config {
	u8 ssid[IEEE80211_MAX_SSID_LEN];
	u8 bssid[ETH_ALEN];
	size_t ssid_len;
	u8 dtim;
	u16 bcn_period;
	u16 auth_type;
	bool privacy;
	enum nl80211_mfp mfp;
	struct cfg80211_crypto_settings crypto;
	u16 bg_scan_period;
	u32 connect_flags;
};

>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
struct qtnf_sta_node {
	struct list_head list;
	u8 mac_addr[ETH_ALEN];
};

struct qtnf_sta_list {
	struct list_head head;
	atomic_t size;
};

enum qtnf_sta_state {
	QTNF_STA_DISCONNECTED,
	QTNF_STA_CONNECTING,
	QTNF_STA_CONNECTED
};

<<<<<<< HEAD
struct qtnf_vif {
	struct wireless_dev wdev;
	u8 bssid[ETH_ALEN];
	u8 mac_addr[ETH_ALEN];
=======
enum qtnf_mac_status {
	QTNF_MAC_CSA_ACTIVE	= BIT(0)
};

struct qtnf_vif {
	struct wireless_dev wdev;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	u8 vifid;
	u8 bss_priority;
	u8 bss_status;
	enum qtnf_sta_state sta_state;
	u16 mgmt_frames_bitmask;
	struct net_device *netdev;
	struct qtnf_wmac *mac;
<<<<<<< HEAD

	struct work_struct reset_work;
	struct qtnf_sta_list sta_list;
	unsigned long cons_tx_timeout_cnt;
	int generation;

	struct pcpu_sw_netstats __percpu *stats64;
=======
	u8 mac_addr[ETH_ALEN];
	struct work_struct reset_work;
	struct qtnf_bss_config bss_cfg;
	struct qtnf_sta_list sta_list;
	unsigned long cons_tx_timeout_cnt;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
};

struct qtnf_mac_info {
	u8 bands_cap;
<<<<<<< HEAD
=======
	u8 phymode_cap;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	u8 dev_mac[ETH_ALEN];
	u8 num_tx_chain;
	u8 num_rx_chain;
	u16 max_ap_assoc_sta;
	u32 frag_thr;
	u32 rts_thr;
	u8 lretry_limit;
	u8 sretry_limit;
	u8 coverage_class;
	u8 radar_detect_widths;
<<<<<<< HEAD
	u32 max_acl_mac_addrs;
	struct ieee80211_ht_cap ht_cap_mod_mask;
	struct ieee80211_vht_cap vht_cap_mod_mask;
	struct ieee80211_iface_combination *if_comb;
	size_t n_if_comb;
	u8 *extended_capabilities;
	u8 *extended_capabilities_mask;
	u8 extended_capabilities_len;
	struct wiphy_wowlan_support *wowlan;
=======
	struct ieee80211_ht_cap ht_cap;
	struct ieee80211_vht_cap vht_cap;
	struct ieee80211_iface_limit *limits;
	size_t n_limits;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
};

struct qtnf_chan_stats {
	u32 chan_num;
	u32 cca_tx;
	u32 cca_rx;
	u32 cca_busy;
	u32 cca_try;
	s8 chan_noise;
};

struct qtnf_wmac {
	u8 macid;
	u8 wiphy_registered;
	u8 macaddr[ETH_ALEN];
<<<<<<< HEAD
=======
	u32 status;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	struct qtnf_bus *bus;
	struct qtnf_mac_info macinfo;
	struct qtnf_vif iflist[QTNF_MAX_INTF];
	struct cfg80211_scan_request *scan_req;
<<<<<<< HEAD
	struct mutex mac_lock;	/* lock during wmac speicific ops */
	struct delayed_work scan_timeout;
=======
	struct cfg80211_chan_def chandef;
	struct cfg80211_chan_def csa_chandef;
	struct mutex mac_lock;	/* lock during wmac speicific ops */
	struct timer_list scan_timeout;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
};

struct qtnf_hw_info {
	u16 ql_proto_ver;
	u8 num_mac;
	u8 mac_bitmap;
	u32 fw_ver;
	u32 hw_capab;
	struct ieee80211_regdomain *rd;
	u8 total_tx_chain;
	u8 total_rx_chain;
<<<<<<< HEAD
	char fw_version[ETHTOOL_FWVERS_LEN];
	u32 hw_version;
	u8 max_scan_ssids;
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
};

struct qtnf_vif *qtnf_mac_get_free_vif(struct qtnf_wmac *mac);
struct qtnf_vif *qtnf_mac_get_base_vif(struct qtnf_wmac *mac);
<<<<<<< HEAD
void qtnf_mac_iface_comb_free(struct qtnf_wmac *mac);
struct wiphy *qtnf_wiphy_allocate(struct qtnf_bus *bus);
int qtnf_core_net_attach(struct qtnf_wmac *mac, struct qtnf_vif *priv,
			 const char *name, unsigned char name_assign_type);
=======
struct wiphy *qtnf_wiphy_allocate(struct qtnf_bus *bus);
int qtnf_core_net_attach(struct qtnf_wmac *mac, struct qtnf_vif *priv,
			 const char *name, unsigned char name_assign_type,
			 enum nl80211_iftype iftype);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
void qtnf_main_work_queue(struct work_struct *work);
int qtnf_cmd_send_update_phy_params(struct qtnf_wmac *mac, u32 changed);
int qtnf_cmd_send_get_phy_params(struct qtnf_wmac *mac);

struct qtnf_wmac *qtnf_core_get_mac(const struct qtnf_bus *bus, u8 macid);
struct net_device *qtnf_classify_skb(struct qtnf_bus *bus, struct sk_buff *skb);
<<<<<<< HEAD
void qtnf_wake_all_queues(struct net_device *ndev);
void qtnf_update_rx_stats(struct net_device *ndev, const struct sk_buff *skb);
void qtnf_update_tx_stats(struct net_device *ndev, const struct sk_buff *skb);
=======
struct net_device *qtnf_classify_skb_no_mbss(struct qtnf_bus *bus,
					     struct sk_buff *skb);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

void qtnf_virtual_intf_cleanup(struct net_device *ndev);

void qtnf_netdev_updown(struct net_device *ndev, bool up);
<<<<<<< HEAD
void qtnf_scan_done(struct qtnf_wmac *mac, bool aborted);
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

static inline struct qtnf_vif *qtnf_netdev_get_priv(struct net_device *dev)
{
	return *((void **)netdev_priv(dev));
}

#endif /* _QTN_FMAC_CORE_H_ */
