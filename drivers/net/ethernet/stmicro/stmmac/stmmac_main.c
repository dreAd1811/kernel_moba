/*******************************************************************************
  This is the driver for the ST MAC 10/100/1000 on-chip Ethernet controllers.
  ST Ethernet IPs are built around a Synopsys IP Core.

	Copyright(C) 2007-2011 STMicroelectronics Ltd

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

  Documentation available at:
	http://www.stlinux.com
  Support available at:
	https://bugzilla.stlinux.com/
*******************************************************************************/

#include <linux/clk.h>
#include <linux/kernel.h>
#include <linux/interrupt.h>
#include <linux/ip.h>
#include <linux/tcp.h>
#include <linux/skbuff.h>
#include <linux/ethtool.h>
#include <linux/if_ether.h>
#include <linux/crc32.h>
#include <linux/mii.h>
#include <linux/if.h>
#include <linux/if_vlan.h>
#include <linux/dma-mapping.h>
#include <linux/slab.h>
#include <linux/prefetch.h>
#include <linux/pinctrl/consumer.h>
#ifdef CONFIG_DEBUG_FS
#include <linux/debugfs.h>
#include <linux/seq_file.h>
#endif /* CONFIG_DEBUG_FS */
#include <linux/net_tstamp.h>
<<<<<<< HEAD
#include <net/pkt_cls.h>
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
#include "stmmac_ptp.h"
#include "stmmac.h"
#include <linux/reset.h>
#include <linux/of_mdio.h>
#include "dwmac1000.h"
<<<<<<< HEAD
#include "dwxgmac2.h"
#include "hwif.h"

#define	STMMAC_ALIGN(x)		__ALIGN_KERNEL(x, SMP_CACHE_BYTES)
=======

#define	STMMAC_ALIGN(x)		ALIGN(ALIGN(x, SMP_CACHE_BYTES), 16)
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
#define	TSO_MAX_BUFF_SIZE	(SZ_16K - 1)

/* Module parameters */
#define TX_TIMEO	5000
static int watchdog = TX_TIMEO;
<<<<<<< HEAD
module_param(watchdog, int, 0644);
MODULE_PARM_DESC(watchdog, "Transmit timeout in milliseconds (default 5s)");

static int debug = -1;
module_param(debug, int, 0644);
MODULE_PARM_DESC(debug, "Message Level (-1: default, 0: no output, 16: all)");

static int phyaddr = -1;
module_param(phyaddr, int, 0444);
=======
module_param(watchdog, int, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(watchdog, "Transmit timeout in milliseconds (default 5s)");

static int debug = -1;
module_param(debug, int, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(debug, "Message Level (-1: default, 0: no output, 16: all)");

static int phyaddr = -1;
module_param(phyaddr, int, S_IRUGO);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
MODULE_PARM_DESC(phyaddr, "Physical device address");

#define STMMAC_TX_THRESH	(DMA_TX_SIZE / 4)
#define STMMAC_RX_THRESH	(DMA_RX_SIZE / 4)

static int flow_ctrl = FLOW_OFF;
<<<<<<< HEAD
module_param(flow_ctrl, int, 0644);
MODULE_PARM_DESC(flow_ctrl, "Flow control ability [on/off]");

static int pause = PAUSE_TIME;
module_param(pause, int, 0644);
=======
module_param(flow_ctrl, int, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(flow_ctrl, "Flow control ability [on/off]");

static int pause = PAUSE_TIME;
module_param(pause, int, S_IRUGO | S_IWUSR);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
MODULE_PARM_DESC(pause, "Flow Control Pause Time");

#define TC_DEFAULT 64
static int tc = TC_DEFAULT;
<<<<<<< HEAD
module_param(tc, int, 0644);
=======
module_param(tc, int, S_IRUGO | S_IWUSR);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
MODULE_PARM_DESC(tc, "DMA threshold control value");

#define	DEFAULT_BUFSIZE	1536
static int buf_sz = DEFAULT_BUFSIZE;
<<<<<<< HEAD
module_param(buf_sz, int, 0644);
=======
module_param(buf_sz, int, S_IRUGO | S_IWUSR);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
MODULE_PARM_DESC(buf_sz, "DMA buffer size");

#define	STMMAC_RX_COPYBREAK	256

static const u32 default_msg_level = (NETIF_MSG_DRV | NETIF_MSG_PROBE |
				      NETIF_MSG_LINK | NETIF_MSG_IFUP |
				      NETIF_MSG_IFDOWN | NETIF_MSG_TIMER);

#define STMMAC_DEFAULT_LPI_TIMER	1000
static int eee_timer = STMMAC_DEFAULT_LPI_TIMER;
<<<<<<< HEAD
module_param(eee_timer, int, 0644);
=======
module_param(eee_timer, int, S_IRUGO | S_IWUSR);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
MODULE_PARM_DESC(eee_timer, "LPI tx expiration time in msec");
#define STMMAC_LPI_T(x) (jiffies + msecs_to_jiffies(x))

/* By default the driver will use the ring mode to manage tx and rx descriptors,
 * but allow user to force to use the chain instead of the ring
 */
static unsigned int chain_mode;
<<<<<<< HEAD
module_param(chain_mode, int, 0444);
=======
module_param(chain_mode, int, S_IRUGO);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
MODULE_PARM_DESC(chain_mode, "To use chain instead of ring mode");

static irqreturn_t stmmac_interrupt(int irq, void *dev_id);

#ifdef CONFIG_DEBUG_FS
static int stmmac_init_fs(struct net_device *dev);
static void stmmac_exit_fs(struct net_device *dev);
#endif

#define STMMAC_COAL_TIMER(x) (jiffies + usecs_to_jiffies(x))

/**
 * stmmac_verify_args - verify the driver parameters.
 * Description: it checks the driver parameters and set a default in case of
 * errors.
 */
static void stmmac_verify_args(void)
{
	if (unlikely(watchdog < 0))
		watchdog = TX_TIMEO;
	if (unlikely((buf_sz < DEFAULT_BUFSIZE) || (buf_sz > BUF_SIZE_16KiB)))
		buf_sz = DEFAULT_BUFSIZE;
	if (unlikely(flow_ctrl > 1))
		flow_ctrl = FLOW_AUTO;
	else if (likely(flow_ctrl < 0))
		flow_ctrl = FLOW_OFF;
	if (unlikely((pause < 0) || (pause > 0xffff)))
		pause = PAUSE_TIME;
	if (eee_timer < 0)
		eee_timer = STMMAC_DEFAULT_LPI_TIMER;
}

/**
 * stmmac_disable_all_queues - Disable all queues
 * @priv: driver private structure
 */
static void stmmac_disable_all_queues(struct stmmac_priv *priv)
{
	u32 rx_queues_cnt = priv->plat->rx_queues_to_use;
<<<<<<< HEAD
	u32 tx_queues_cnt = priv->plat->tx_queues_to_use;
	u32 maxq = max(rx_queues_cnt, tx_queues_cnt);
	u32 queue;

	for (queue = 0; queue < maxq; queue++) {
		struct stmmac_channel *ch = &priv->channel[queue];

		napi_disable(&ch->napi);
=======
	u32 queue;

	for (queue = 0; queue < rx_queues_cnt; queue++) {
		struct stmmac_rx_queue *rx_q = &priv->rx_queue[queue];
		if (rx_q->skip_sw)
			continue;
		napi_disable(&rx_q->napi);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	}
}

/**
 * stmmac_enable_all_queues - Enable all queues
 * @priv: driver private structure
 */
static void stmmac_enable_all_queues(struct stmmac_priv *priv)
{
	u32 rx_queues_cnt = priv->plat->rx_queues_to_use;
<<<<<<< HEAD
	u32 tx_queues_cnt = priv->plat->tx_queues_to_use;
	u32 maxq = max(rx_queues_cnt, tx_queues_cnt);
	u32 queue;

	for (queue = 0; queue < maxq; queue++) {
		struct stmmac_channel *ch = &priv->channel[queue];

		napi_enable(&ch->napi);
=======
	u32 queue;

	for (queue = 0; queue < rx_queues_cnt; queue++) {
		struct stmmac_rx_queue *rx_q = &priv->rx_queue[queue];
		if (rx_q->skip_sw)
			continue;
		napi_enable(&rx_q->napi);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	}
}

/**
 * stmmac_stop_all_queues - Stop all queues
 * @priv: driver private structure
 */
static void stmmac_stop_all_queues(struct stmmac_priv *priv)
{
	u32 tx_queues_cnt = priv->plat->tx_queues_to_use;
	u32 queue;

	for (queue = 0; queue < tx_queues_cnt; queue++)
		netif_tx_stop_queue(netdev_get_tx_queue(priv->dev, queue));
}

/**
 * stmmac_start_all_queues - Start all queues
 * @priv: driver private structure
 */
static void stmmac_start_all_queues(struct stmmac_priv *priv)
{
	u32 tx_queues_cnt = priv->plat->tx_queues_to_use;
	u32 queue;

	for (queue = 0; queue < tx_queues_cnt; queue++)
		netif_tx_start_queue(netdev_get_tx_queue(priv->dev, queue));
}

<<<<<<< HEAD
static void stmmac_service_event_schedule(struct stmmac_priv *priv)
{
	if (!test_bit(STMMAC_DOWN, &priv->state) &&
	    !test_and_set_bit(STMMAC_SERVICE_SCHED, &priv->state))
		queue_work(priv->wq, &priv->service_task);
}

static void stmmac_global_err(struct stmmac_priv *priv)
{
	netif_carrier_off(priv->dev);
	set_bit(STMMAC_RESET_REQUESTED, &priv->state);
	stmmac_service_event_schedule(priv);
}

=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
/**
 * stmmac_clk_csr_set - dynamically set the MDC clock
 * @priv: driver private structure
 * Description: this is to dynamically set the MDC clock according to the csr
 * clock input.
 * Note:
 *	If a specific clk_csr value is passed from the platform
 *	this means that the CSR Clock Range selection cannot be
 *	changed at run-time and it is fixed (as reported in the driver
 *	documentation). Viceversa the driver will try to set the MDC
 *	clock dynamically according to the actual clock input.
 */
static void stmmac_clk_csr_set(struct stmmac_priv *priv)
{
	u32 clk_rate;

	clk_rate = clk_get_rate(priv->plat->stmmac_clk);

	/* Platform provided default clk_csr would be assumed valid
	 * for all other cases except for the below mentioned ones.
	 * For values higher than the IEEE 802.3 specified frequency
	 * we can not estimate the proper divider as it is not known
	 * the frequency of clk_csr_i. So we do not change the default
	 * divider.
	 */
	if (!(priv->clk_csr & MAC_CSR_H_FRQ_MASK)) {
		if (clk_rate < CSR_F_35M)
			priv->clk_csr = STMMAC_CSR_20_35M;
		else if ((clk_rate >= CSR_F_35M) && (clk_rate < CSR_F_60M))
			priv->clk_csr = STMMAC_CSR_35_60M;
		else if ((clk_rate >= CSR_F_60M) && (clk_rate < CSR_F_100M))
			priv->clk_csr = STMMAC_CSR_60_100M;
		else if ((clk_rate >= CSR_F_100M) && (clk_rate < CSR_F_150M))
			priv->clk_csr = STMMAC_CSR_100_150M;
		else if ((clk_rate >= CSR_F_150M) && (clk_rate < CSR_F_250M))
			priv->clk_csr = STMMAC_CSR_150_250M;
		else if ((clk_rate >= CSR_F_250M) && (clk_rate < CSR_F_300M))
			priv->clk_csr = STMMAC_CSR_250_300M;
	}

	if (priv->plat->has_sun8i) {
		if (clk_rate > 160000000)
			priv->clk_csr = 0x03;
		else if (clk_rate > 80000000)
			priv->clk_csr = 0x02;
		else if (clk_rate > 40000000)
			priv->clk_csr = 0x01;
		else
			priv->clk_csr = 0;
	}
<<<<<<< HEAD

	if (priv->plat->has_xgmac) {
		if (clk_rate > 400000000)
			priv->clk_csr = 0x5;
		else if (clk_rate > 350000000)
			priv->clk_csr = 0x4;
		else if (clk_rate > 300000000)
			priv->clk_csr = 0x3;
		else if (clk_rate > 250000000)
			priv->clk_csr = 0x2;
		else if (clk_rate > 150000000)
			priv->clk_csr = 0x1;
		else
			priv->clk_csr = 0x0;
	}
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
}

static void print_pkt(unsigned char *buf, int len)
{
	pr_debug("len = %d byte, buf addr: 0x%p\n", len, buf);
	print_hex_dump_bytes("", DUMP_PREFIX_OFFSET, buf, len);
}

static inline u32 stmmac_tx_avail(struct stmmac_priv *priv, u32 queue)
{
	struct stmmac_tx_queue *tx_q = &priv->tx_queue[queue];
	u32 avail;

	if (tx_q->dirty_tx > tx_q->cur_tx)
		avail = tx_q->dirty_tx - tx_q->cur_tx - 1;
	else
		avail = DMA_TX_SIZE - tx_q->cur_tx + tx_q->dirty_tx - 1;

	return avail;
}

/**
 * stmmac_rx_dirty - Get RX queue dirty
 * @priv: driver private structure
 * @queue: RX queue index
 */
static inline u32 stmmac_rx_dirty(struct stmmac_priv *priv, u32 queue)
{
	struct stmmac_rx_queue *rx_q = &priv->rx_queue[queue];
	u32 dirty;

	if (rx_q->dirty_rx <= rx_q->cur_rx)
		dirty = rx_q->cur_rx - rx_q->dirty_rx;
	else
		dirty = DMA_RX_SIZE - rx_q->dirty_rx + rx_q->cur_rx;

	return dirty;
}

/**
 * stmmac_hw_fix_mac_speed - callback for speed selection
 * @priv: driver private structure
 * Description: on some platforms (e.g. ST), some HW system configuration
 * registers have to be set according to the link speed negotiated.
 */
static inline void stmmac_hw_fix_mac_speed(struct stmmac_priv *priv)
{
<<<<<<< HEAD
	struct net_device *ndev = priv->dev;
	struct phy_device *phydev = ndev->phydev;

	if (likely(priv->plat->fix_mac_speed))
		priv->plat->fix_mac_speed(priv->plat->bsp_priv, phydev->speed);
=======
	if (likely(priv->plat->fix_mac_speed)) {
		if (priv->plat->mac2mac_en) {
			priv->plat->fix_mac_speed(priv->plat->bsp_priv,
					priv->speed);
			return;
		}

		if (priv->phydev->link)
			priv->plat->fix_mac_speed(priv->plat->bsp_priv,
						  priv->speed);
		else
			priv->plat->fix_mac_speed(priv->plat->bsp_priv,
						  SPEED_10);
	}
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
}

/**
 * stmmac_enable_eee_mode - check and enter in LPI mode
 * @priv: driver private structure
 * Description: this function is to verify and enter in LPI mode in case of
 * EEE.
 */
static void stmmac_enable_eee_mode(struct stmmac_priv *priv)
{
	u32 tx_cnt = priv->plat->tx_queues_to_use;
	u32 queue;

	/* check if all TX queues have the work finished */
	for (queue = 0; queue < tx_cnt; queue++) {
		struct stmmac_tx_queue *tx_q = &priv->tx_queue[queue];

		if (tx_q->dirty_tx != tx_q->cur_tx)
			return; /* still unfinished work */
	}

	/* Check and enter in LPI mode */
	if (!priv->tx_path_in_lpi_mode)
<<<<<<< HEAD
		stmmac_set_eee_mode(priv, priv->hw,
				priv->plat->en_tx_lpi_clockgating);
=======
		priv->hw->mac->set_eee_mode(priv->hw,
					    priv->plat->en_tx_lpi_clockgating);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
}

/**
 * stmmac_disable_eee_mode - disable and exit from LPI mode
 * @priv: driver private structure
 * Description: this function is to exit and disable EEE in case of
 * LPI state is true. This is called by the xmit.
 */
void stmmac_disable_eee_mode(struct stmmac_priv *priv)
{
<<<<<<< HEAD
	stmmac_reset_eee_mode(priv, priv->hw);
=======
	priv->hw->mac->reset_eee_mode(priv->hw);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	del_timer_sync(&priv->eee_ctrl_timer);
	priv->tx_path_in_lpi_mode = false;
}

/**
 * stmmac_eee_ctrl_timer - EEE TX SW timer.
 * @arg : data hook
 * Description:
 *  if there is no data transfer and if we are not in LPI state,
 *  then MAC Transmitter can be moved to LPI state.
 */
<<<<<<< HEAD
static void stmmac_eee_ctrl_timer(struct timer_list *t)
{
	struct stmmac_priv *priv = from_timer(priv, t, eee_ctrl_timer);
=======
static void stmmac_eee_ctrl_timer(unsigned long arg)
{
	struct stmmac_priv *priv = (struct stmmac_priv *)arg;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	stmmac_enable_eee_mode(priv);
	mod_timer(&priv->eee_ctrl_timer, STMMAC_LPI_T(eee_timer));
}

/**
 * stmmac_eee_init - init EEE
 * @priv: driver private structure
 * Description:
 *  if the GMAC supports the EEE (from the HW cap reg) and the phy device
 *  can also manage EEE, this function enable the LPI state and start related
 *  timer.
 */
bool stmmac_eee_init(struct stmmac_priv *priv)
{
	struct net_device *ndev = priv->dev;
	int interface = priv->plat->interface;
	bool ret = false;

	if ((interface != PHY_INTERFACE_MODE_MII) &&
	    (interface != PHY_INTERFACE_MODE_GMII) &&
	    !phy_interface_mode_is_rgmii(interface))
		goto out;

	/* Using PCS we cannot dial with the phy registers at this stage
	 * so we do not support extra feature like EEE.
	 */
	if ((priv->hw->pcs == STMMAC_PCS_RGMII) ||
	    (priv->hw->pcs == STMMAC_PCS_TBI) ||
	    (priv->hw->pcs == STMMAC_PCS_RTBI))
		goto out;

	/* MAC core supports the EEE feature. */
	if (priv->dma_cap.eee) {
		int tx_lpi_timer = priv->tx_lpi_timer;

		/* Check if the PHY supports EEE */
		if (phy_init_eee(ndev->phydev, 1)) {
			/* To manage at run-time if the EEE cannot be supported
			 * anymore (for example because the lp caps have been
			 * changed).
			 * In that case the driver disable own timers.
			 */
			mutex_lock(&priv->lock);
			if (priv->eee_active) {
				netdev_dbg(priv->dev, "disable EEE\n");
				del_timer_sync(&priv->eee_ctrl_timer);
<<<<<<< HEAD
				stmmac_set_eee_timer(priv, priv->hw, 0,
						tx_lpi_timer);
=======
				priv->hw->mac->set_eee_timer(priv->hw, 0,
							     tx_lpi_timer);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
			}
			priv->eee_active = 0;
			mutex_unlock(&priv->lock);
			goto out;
		}
		/* Activate the EEE and start timers */
		mutex_lock(&priv->lock);
		if (!priv->eee_active) {
			priv->eee_active = 1;
<<<<<<< HEAD
			timer_setup(&priv->eee_ctrl_timer,
				    stmmac_eee_ctrl_timer, 0);
			mod_timer(&priv->eee_ctrl_timer,
				  STMMAC_LPI_T(eee_timer));

			stmmac_set_eee_timer(priv, priv->hw,
					STMMAC_DEFAULT_LIT_LS, tx_lpi_timer);
		}
		/* Set HW EEE according to the speed */
		stmmac_set_eee_pls(priv, priv->hw, ndev->phydev->link);
=======
			setup_timer(&priv->eee_ctrl_timer,
				    stmmac_eee_ctrl_timer,
				    (unsigned long)priv);
			mod_timer(&priv->eee_ctrl_timer,
				  STMMAC_LPI_T(eee_timer));

			priv->hw->mac->set_eee_timer(priv->hw,
						     STMMAC_DEFAULT_LIT_LS,
						     tx_lpi_timer);
		}
		/* Set HW EEE according to the speed */
		priv->hw->mac->set_eee_pls(priv->hw, ndev->phydev->link);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

		ret = true;
		mutex_unlock(&priv->lock);

		netdev_dbg(priv->dev, "Energy-Efficient Ethernet initialized\n");
	}
out:
	return ret;
}

/* stmmac_get_tx_hwtstamp - get HW TX timestamps
 * @priv: driver private structure
 * @p : descriptor pointer
 * @skb : the socket buffer
 * Description :
 * This function will read timestamp from the descriptor & pass it to stack.
 * and also perform some sanity checks.
 */
static void stmmac_get_tx_hwtstamp(struct stmmac_priv *priv,
				   struct dma_desc *p, struct sk_buff *skb)
{
	struct skb_shared_hwtstamps shhwtstamp;
<<<<<<< HEAD
	u64 ns = 0;
=======
	u64 ns;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	if (!priv->hwts_tx_en)
		return;

	/* exit if skb doesn't support hw tstamp */
	if (likely(!skb || !(skb_shinfo(skb)->tx_flags & SKBTX_IN_PROGRESS)))
		return;

	/* check tx tstamp status */
<<<<<<< HEAD
	if (stmmac_get_tx_timestamp_status(priv, p)) {
		/* get the valid tstamp */
		stmmac_get_timestamp(priv, p, priv->adv_ts, &ns);
=======
	if (priv->hw->desc->get_tx_timestamp_status(p)) {
		/* get the valid tstamp */
		ns = priv->hw->desc->get_timestamp(p, priv->adv_ts);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

		memset(&shhwtstamp, 0, sizeof(struct skb_shared_hwtstamps));
		shhwtstamp.hwtstamp = ns_to_ktime(ns);

		netdev_dbg(priv->dev, "get valid TX hw timestamp %llu\n", ns);
		/* pass tstamp to stack */
		skb_tstamp_tx(skb, &shhwtstamp);
	}

	return;
}

/* stmmac_get_rx_hwtstamp - get HW RX timestamps
 * @priv: driver private structure
 * @p : descriptor pointer
 * @np : next descriptor pointer
 * @skb : the socket buffer
 * Description :
 * This function will read received packet's timestamp from the descriptor
 * and pass it to stack. It also perform some sanity checks.
 */
static void stmmac_get_rx_hwtstamp(struct stmmac_priv *priv, struct dma_desc *p,
				   struct dma_desc *np, struct sk_buff *skb)
{
	struct skb_shared_hwtstamps *shhwtstamp = NULL;
	struct dma_desc *desc = p;
<<<<<<< HEAD
	u64 ns = 0;
=======
	u64 ns;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	if (!priv->hwts_rx_en)
		return;
	/* For GMAC4, the valid timestamp is from CTX next desc. */
<<<<<<< HEAD
	if (priv->plat->has_gmac4 || priv->plat->has_xgmac)
		desc = np;

	/* Check if timestamp is available */
	if (stmmac_get_rx_timestamp_status(priv, p, np, priv->adv_ts)) {
		stmmac_get_timestamp(priv, desc, priv->adv_ts, &ns);
=======
	if (priv->plat->has_gmac4)
		desc = np;

	/* Check if timestamp is available */
	if (priv->hw->desc->get_rx_timestamp_status(p, np, priv->adv_ts)) {
		ns = priv->hw->desc->get_timestamp(desc, priv->adv_ts);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
		netdev_dbg(priv->dev, "get valid RX hw timestamp %llu\n", ns);
		shhwtstamp = skb_hwtstamps(skb);
		memset(shhwtstamp, 0, sizeof(struct skb_shared_hwtstamps));
		shhwtstamp->hwtstamp = ns_to_ktime(ns);
	} else  {
		netdev_dbg(priv->dev, "cannot get RX hw timestamp\n");
	}
}

/**
 *  stmmac_hwtstamp_ioctl - control hardware timestamping.
 *  @dev: device pointer.
 *  @ifr: An IOCTL specific structure, that can contain a pointer to
 *  a proprietary structure used to pass information to the driver.
 *  Description:
 *  This function configures the MAC to enable/disable both outgoing(TX)
 *  and incoming(RX) packets time stamping based on user input.
 *  Return Value:
 *  0 on success and an appropriate -ve integer on failure.
 */
static int stmmac_hwtstamp_ioctl(struct net_device *dev, struct ifreq *ifr)
{
	struct stmmac_priv *priv = netdev_priv(dev);
	struct hwtstamp_config config;
	struct timespec64 now;
	u64 temp = 0;
	u32 ptp_v2 = 0;
	u32 tstamp_all = 0;
	u32 ptp_over_ipv4_udp = 0;
	u32 ptp_over_ipv6_udp = 0;
	u32 ptp_over_ethernet = 0;
	u32 snap_type_sel = 0;
	u32 ts_master_en = 0;
	u32 ts_event_en = 0;
<<<<<<< HEAD
	u32 sec_inc = 0;
	u32 value = 0;
	bool xmac;

	xmac = priv->plat->has_gmac4 || priv->plat->has_xgmac;
=======
	u32 av_8021asm_en = 0;
	u32 value = 0;
	u32 sec_inc;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	if (!(priv->dma_cap.time_stamp || priv->adv_ts)) {
		netdev_alert(priv->dev, "No support for HW time stamping\n");
		priv->hwts_tx_en = 0;
		priv->hwts_rx_en = 0;

		return -EOPNOTSUPP;
	}

	if (copy_from_user(&config, ifr->ifr_data,
			   sizeof(struct hwtstamp_config)))
		return -EFAULT;

<<<<<<< HEAD
=======
	if (qcom_ethqos_ipa_enabled() &&
	    config.rx_filter == HWTSTAMP_FILTER_ALL) {
		netdev_alert(priv->dev,
			     "No hw timestamping since ipa is enabled\n");
		return -EOPNOTSUPP;
	}

>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	netdev_dbg(priv->dev, "%s config flags:0x%x, tx_type:0x%x, rx_filter:0x%x\n",
		   __func__, config.flags, config.tx_type, config.rx_filter);

	/* reserved for future extensions */
	if (config.flags)
		return -EINVAL;

	if (config.tx_type != HWTSTAMP_TX_OFF &&
	    config.tx_type != HWTSTAMP_TX_ON)
		return -ERANGE;

	if (priv->adv_ts) {
		switch (config.rx_filter) {
		case HWTSTAMP_FILTER_NONE:
			/* time stamp no incoming packet at all */
			config.rx_filter = HWTSTAMP_FILTER_NONE;
			break;

		case HWTSTAMP_FILTER_PTP_V1_L4_EVENT:
			/* PTP v1, UDP, any kind of event packet */
			config.rx_filter = HWTSTAMP_FILTER_PTP_V1_L4_EVENT;
			/* take time stamp for all event messages */
<<<<<<< HEAD
			if (xmac)
				snap_type_sel = PTP_GMAC4_TCR_SNAPTYPSEL_1;
			else
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
				snap_type_sel = PTP_TCR_SNAPTYPSEL_1;

			ptp_over_ipv4_udp = PTP_TCR_TSIPV4ENA;
			ptp_over_ipv6_udp = PTP_TCR_TSIPV6ENA;
			break;

		case HWTSTAMP_FILTER_PTP_V1_L4_SYNC:
			/* PTP v1, UDP, Sync packet */
			config.rx_filter = HWTSTAMP_FILTER_PTP_V1_L4_SYNC;
			/* take time stamp for SYNC messages only */
			ts_event_en = PTP_TCR_TSEVNTENA;

			ptp_over_ipv4_udp = PTP_TCR_TSIPV4ENA;
			ptp_over_ipv6_udp = PTP_TCR_TSIPV6ENA;
			break;

		case HWTSTAMP_FILTER_PTP_V1_L4_DELAY_REQ:
			/* PTP v1, UDP, Delay_req packet */
			config.rx_filter = HWTSTAMP_FILTER_PTP_V1_L4_DELAY_REQ;
			/* take time stamp for Delay_Req messages only */
			ts_master_en = PTP_TCR_TSMSTRENA;
			ts_event_en = PTP_TCR_TSEVNTENA;

			ptp_over_ipv4_udp = PTP_TCR_TSIPV4ENA;
			ptp_over_ipv6_udp = PTP_TCR_TSIPV6ENA;
			break;

		case HWTSTAMP_FILTER_PTP_V2_L4_EVENT:
			/* PTP v2, UDP, any kind of event packet */
			config.rx_filter = HWTSTAMP_FILTER_PTP_V2_L4_EVENT;
			ptp_v2 = PTP_TCR_TSVER2ENA;
			/* take time stamp for all event messages */
<<<<<<< HEAD
			if (xmac)
				snap_type_sel = PTP_GMAC4_TCR_SNAPTYPSEL_1;
			else
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
				snap_type_sel = PTP_TCR_SNAPTYPSEL_1;

			ptp_over_ipv4_udp = PTP_TCR_TSIPV4ENA;
			ptp_over_ipv6_udp = PTP_TCR_TSIPV6ENA;
			break;

		case HWTSTAMP_FILTER_PTP_V2_L4_SYNC:
			/* PTP v2, UDP, Sync packet */
			config.rx_filter = HWTSTAMP_FILTER_PTP_V2_L4_SYNC;
			ptp_v2 = PTP_TCR_TSVER2ENA;
			/* take time stamp for SYNC messages only */
			ts_event_en = PTP_TCR_TSEVNTENA;

			ptp_over_ipv4_udp = PTP_TCR_TSIPV4ENA;
			ptp_over_ipv6_udp = PTP_TCR_TSIPV6ENA;
			break;

		case HWTSTAMP_FILTER_PTP_V2_L4_DELAY_REQ:
			/* PTP v2, UDP, Delay_req packet */
			config.rx_filter = HWTSTAMP_FILTER_PTP_V2_L4_DELAY_REQ;
			ptp_v2 = PTP_TCR_TSVER2ENA;
			/* take time stamp for Delay_Req messages only */
			ts_master_en = PTP_TCR_TSMSTRENA;
			ts_event_en = PTP_TCR_TSEVNTENA;

			ptp_over_ipv4_udp = PTP_TCR_TSIPV4ENA;
			ptp_over_ipv6_udp = PTP_TCR_TSIPV6ENA;
			break;

		case HWTSTAMP_FILTER_PTP_V2_EVENT:
			/* PTP v2/802.AS1 any layer, any kind of event packet */
			config.rx_filter = HWTSTAMP_FILTER_PTP_V2_EVENT;
			ptp_v2 = PTP_TCR_TSVER2ENA;
			/* take time stamp for all event messages */
<<<<<<< HEAD
			if (xmac)
				snap_type_sel = PTP_GMAC4_TCR_SNAPTYPSEL_1;
			else
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
				snap_type_sel = PTP_TCR_SNAPTYPSEL_1;

			ptp_over_ipv4_udp = PTP_TCR_TSIPV4ENA;
			ptp_over_ipv6_udp = PTP_TCR_TSIPV6ENA;
			ptp_over_ethernet = PTP_TCR_TSIPENA;
<<<<<<< HEAD
=======
			av_8021asm_en = PTP_TCR_AV8021ASMEN;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
			break;

		case HWTSTAMP_FILTER_PTP_V2_SYNC:
			/* PTP v2/802.AS1, any layer, Sync packet */
			config.rx_filter = HWTSTAMP_FILTER_PTP_V2_SYNC;
			ptp_v2 = PTP_TCR_TSVER2ENA;
			/* take time stamp for SYNC messages only */
			ts_event_en = PTP_TCR_TSEVNTENA;

			ptp_over_ipv4_udp = PTP_TCR_TSIPV4ENA;
			ptp_over_ipv6_udp = PTP_TCR_TSIPV6ENA;
			ptp_over_ethernet = PTP_TCR_TSIPENA;
<<<<<<< HEAD
=======
			av_8021asm_en = PTP_TCR_AV8021ASMEN;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
			break;

		case HWTSTAMP_FILTER_PTP_V2_DELAY_REQ:
			/* PTP v2/802.AS1, any layer, Delay_req packet */
			config.rx_filter = HWTSTAMP_FILTER_PTP_V2_DELAY_REQ;
			ptp_v2 = PTP_TCR_TSVER2ENA;
			/* take time stamp for Delay_Req messages only */
			ts_master_en = PTP_TCR_TSMSTRENA;
			ts_event_en = PTP_TCR_TSEVNTENA;

			ptp_over_ipv4_udp = PTP_TCR_TSIPV4ENA;
			ptp_over_ipv6_udp = PTP_TCR_TSIPV6ENA;
			ptp_over_ethernet = PTP_TCR_TSIPENA;
<<<<<<< HEAD
=======
			av_8021asm_en = PTP_TCR_AV8021ASMEN;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
			break;

		case HWTSTAMP_FILTER_NTP_ALL:
		case HWTSTAMP_FILTER_ALL:
			/* time stamp any incoming packet */
			config.rx_filter = HWTSTAMP_FILTER_ALL;
			tstamp_all = PTP_TCR_TSENALL;
			break;

		default:
			return -ERANGE;
		}
	} else {
		switch (config.rx_filter) {
		case HWTSTAMP_FILTER_NONE:
			config.rx_filter = HWTSTAMP_FILTER_NONE;
			break;
		default:
			/* PTP v1, UDP, any kind of event packet */
			config.rx_filter = HWTSTAMP_FILTER_PTP_V1_L4_EVENT;
			break;
		}
	}
	priv->hwts_rx_en = ((config.rx_filter == HWTSTAMP_FILTER_NONE) ? 0 : 1);
	priv->hwts_tx_en = config.tx_type == HWTSTAMP_TX_ON;

	if (!priv->hwts_tx_en && !priv->hwts_rx_en)
<<<<<<< HEAD
		stmmac_config_hw_tstamping(priv, priv->ptpaddr, 0);
=======
		priv->hw->ptp->config_hw_tstamping(priv->ptpaddr, 0);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	else {
		value = (PTP_TCR_TSENA | PTP_TCR_TSCFUPDT | PTP_TCR_TSCTRLSSR |
			 tstamp_all | ptp_v2 | ptp_over_ethernet |
			 ptp_over_ipv6_udp | ptp_over_ipv4_udp | ts_event_en |
<<<<<<< HEAD
			 ts_master_en | snap_type_sel);
		stmmac_config_hw_tstamping(priv, priv->ptpaddr, value);

		/* program Sub Second Increment reg */
		stmmac_config_sub_second_increment(priv,
				priv->ptpaddr, priv->plat->clk_ptp_rate,
				xmac, &sec_inc);
		temp = div_u64(1000000000ULL, sec_inc);

		/* Store sub second increment and flags for later use */
		priv->sub_second_inc = sec_inc;
		priv->systime_flags = value;
=======
			 ts_master_en | snap_type_sel | av_8021asm_en);
		priv->hw->ptp->config_hw_tstamping(priv->ptpaddr, value);

		/* program Sub Second Increment reg */
		sec_inc = priv->hw->ptp->config_sub_second_increment(
			priv->ptpaddr, priv->plat->clk_ptp_req_rate,
			priv->plat->has_gmac4);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

		/* calculate default added value:
		 * formula is :
		 * addend = (2^32)/freq_div_ratio;
		 * where, freq_div_ratio = 1e9ns/sec_inc
		 */
<<<<<<< HEAD
		temp = (u64)(temp << 32);
		priv->default_addend = div_u64(temp, priv->plat->clk_ptp_rate);
		stmmac_config_addend(priv, priv->ptpaddr, priv->default_addend);
=======
		temp = (u64)((u64)priv->plat->clk_ptp_req_rate << 32);
		priv->default_addend = div_u64(temp, priv->plat->clk_ptp_rate);
		priv->hw->ptp->config_addend(priv->ptpaddr,
					     priv->default_addend);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

		/* initialize system time */
		ktime_get_real_ts64(&now);

		/* lower 32 bits of tv_sec are safe until y2106 */
<<<<<<< HEAD
		stmmac_init_systime(priv, priv->ptpaddr,
				(u32)now.tv_sec, now.tv_nsec);
=======
		priv->hw->ptp->init_systime(priv->ptpaddr, (u32)now.tv_sec,
					    now.tv_nsec);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	}

	return copy_to_user(ifr->ifr_data, &config,
			    sizeof(struct hwtstamp_config)) ? -EFAULT : 0;
}

/**
 * stmmac_init_ptp - init PTP
 * @priv: driver private structure
 * Description: this is to verify if the HW supports the PTPv1 or PTPv2.
 * This is done by looking at the HW cap. register.
 * This function also registers the ptp driver.
 */
static int stmmac_init_ptp(struct stmmac_priv *priv)
{
<<<<<<< HEAD
	bool xmac = priv->plat->has_gmac4 || priv->plat->has_xgmac;

=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	if (!(priv->dma_cap.time_stamp || priv->dma_cap.atime_stamp))
		return -EOPNOTSUPP;

	priv->adv_ts = 0;
<<<<<<< HEAD
	/* Check if adv_ts can be enabled for dwmac 4.x / xgmac core */
	if (xmac && priv->dma_cap.atime_stamp)
=======
	/* Check if adv_ts can be enabled for dwmac 4.x core */
	if (priv->plat->has_gmac4 && priv->dma_cap.atime_stamp)
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
		priv->adv_ts = 1;
	/* Dwmac 3.x core with extend_desc can support adv_ts */
	else if (priv->extend_desc && priv->dma_cap.atime_stamp)
		priv->adv_ts = 1;

	if (priv->dma_cap.time_stamp)
		netdev_info(priv->dev, "IEEE 1588-2002 Timestamp supported\n");

	if (priv->adv_ts)
		netdev_info(priv->dev,
			    "IEEE 1588-2008 Advanced Timestamp supported\n");

<<<<<<< HEAD
=======
	priv->hw->ptp = &stmmac_ptp;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	priv->hwts_tx_en = 0;
	priv->hwts_rx_en = 0;

	stmmac_ptp_register(priv);

	return 0;
}

static void stmmac_release_ptp(struct stmmac_priv *priv)
{
	if (priv->plat->clk_ptp_ref)
		clk_disable_unprepare(priv->plat->clk_ptp_ref);
	stmmac_ptp_unregister(priv);
}

/**
 *  stmmac_mac_flow_ctrl - Configure flow control in all queues
 *  @priv: driver private structure
 *  Description: It is used for configuring the flow control in all queues
 */
static void stmmac_mac_flow_ctrl(struct stmmac_priv *priv, u32 duplex)
{
	u32 tx_cnt = priv->plat->tx_queues_to_use;

<<<<<<< HEAD
	stmmac_flow_ctrl(priv, priv->hw, duplex, priv->flow_ctrl,
			priv->pause, tx_cnt);
=======
	priv->hw->mac->flow_ctrl(priv->hw, duplex, priv->flow_ctrl,
				 priv->pause, tx_cnt);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
}

/**
 * stmmac_adjust_link - adjusts the link parameters
 * @dev: net device structure
 * Description: this is the helper called by the physical abstraction layer
 * drivers to communicate the phy link status. According the speed and duplex
 * this driver can invoke registered glue-logic as well.
 * It also invoke the eee initialization because it could happen when switch
 * on different networks (that are eee capable).
 */
static void stmmac_adjust_link(struct net_device *dev)
{
	struct stmmac_priv *priv = netdev_priv(dev);
	struct phy_device *phydev = dev->phydev;
	bool new_state = false;

	if (!phydev)
		return;

	mutex_lock(&priv->lock);

	if (phydev->link) {
		u32 ctrl = readl(priv->ioaddr + MAC_CTRL_REG);

		/* Now we make sure that we can be in full duplex mode.
		 * If not, we operate in half-duplex mode. */
		if (phydev->duplex != priv->oldduplex) {
			new_state = true;
			if (!phydev->duplex)
				ctrl &= ~priv->hw->link.duplex;
			else
				ctrl |= priv->hw->link.duplex;
			priv->oldduplex = phydev->duplex;
		}
		/* Flow Control operation */
		if (phydev->pause)
			stmmac_mac_flow_ctrl(priv, phydev->duplex);

		if (phydev->speed != priv->speed) {
			new_state = true;
			ctrl &= ~priv->hw->link.speed_mask;
			switch (phydev->speed) {
			case SPEED_1000:
				ctrl |= priv->hw->link.speed1000;
				break;
			case SPEED_100:
				ctrl |= priv->hw->link.speed100;
				break;
			case SPEED_10:
				ctrl |= priv->hw->link.speed10;
				break;
			default:
				netif_warn(priv, link, priv->dev,
					   "broken speed: %d\n", phydev->speed);
				phydev->speed = SPEED_UNKNOWN;
				break;
			}
<<<<<<< HEAD
			if (phydev->speed != SPEED_UNKNOWN)
				stmmac_hw_fix_mac_speed(priv);
			priv->speed = phydev->speed;
=======
			priv->speed = phydev->speed;
			if (phydev->speed != SPEED_UNKNOWN)
				stmmac_hw_fix_mac_speed(priv);

>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
		}

		writel(ctrl, priv->ioaddr + MAC_CTRL_REG);

<<<<<<< HEAD
		if (!priv->oldlink) {
=======
		if (!priv->oldlink || (priv->oldlink == -1)) {
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
			new_state = true;
			priv->oldlink = true;
		}
	} else if (priv->oldlink) {
<<<<<<< HEAD
=======
		stmmac_hw_fix_mac_speed(priv);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
		new_state = true;
		priv->oldlink = false;
		priv->speed = SPEED_UNKNOWN;
		priv->oldduplex = DUPLEX_UNKNOWN;
	}

	if (new_state && netif_msg_link(priv))
		phy_print_status(phydev);

	mutex_unlock(&priv->lock);

<<<<<<< HEAD
=======
	if (new_state) {
		if (phydev->link == 1 && priv->hw_offload_enabled)
			ethqos_ipa_offload_event_handler(priv,
							 EV_PHY_LINK_UP);
		else if (phydev->link == 0 &&
			 priv->hw_offload_enabled)
			ethqos_ipa_offload_event_handler(priv,
							 EV_PHY_LINK_DOWN);
	}
#ifdef CONFIG_MSM_BOOT_TIME_MARKER
if (phydev->link == 1 && !priv->boot_kpi) {
	place_marker("M - Ethernet is Ready.Link is UP");
	priv->boot_kpi = true;
}
#endif

>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	if (phydev->is_pseudo_fixed_link)
		/* Stop PHY layer to call the hook to adjust the link in case
		 * of a switch is attached to the stmmac driver.
		 */
		phydev->irq = PHY_IGNORE_INTERRUPT;
	else
		/* At this stage, init the EEE if supported.
		 * Never called in case of fixed_link.
		 */
		priv->eee_enabled = stmmac_eee_init(priv);
}

/**
 * stmmac_check_pcs_mode - verify if RGMII/SGMII is supported
 * @priv: driver private structure
 * Description: this is to verify if the HW supports the PCS.
 * Physical Coding Sublayer (PCS) interface that can be used when the MAC is
 * configured for the TBI, RTBI, or SGMII PHY interface.
 */
static void stmmac_check_pcs_mode(struct stmmac_priv *priv)
{
	int interface = priv->plat->interface;

	if (priv->dma_cap.pcs) {
		if ((interface == PHY_INTERFACE_MODE_RGMII) ||
		    (interface == PHY_INTERFACE_MODE_RGMII_ID) ||
		    (interface == PHY_INTERFACE_MODE_RGMII_RXID) ||
		    (interface == PHY_INTERFACE_MODE_RGMII_TXID)) {
			netdev_dbg(priv->dev, "PCS RGMII support enabled\n");
			priv->hw->pcs = STMMAC_PCS_RGMII;
		} else if (interface == PHY_INTERFACE_MODE_SGMII) {
			netdev_dbg(priv->dev, "PCS SGMII support enabled\n");
			priv->hw->pcs = STMMAC_PCS_SGMII;
		}
	}
}

<<<<<<< HEAD
=======
static void stmmac_set_speed100(struct phy_device *phydev)
{
	u16 bmcr_val, ctrl1000_val, adv_val;

	/* Disable 1000M mode */
	ctrl1000_val = phy_read(phydev, MII_CTRL1000);
	ctrl1000_val &= ~(ADVERTISE_1000HALF | ADVERTISE_1000FULL);
	phy_write(phydev, MII_CTRL1000, ctrl1000_val);

	/* Disable 100M mode */
	adv_val = phy_read(phydev, MII_ADVERTISE);
	adv_val &= ~(ADVERTISE_100HALF);
	phy_write(phydev, MII_ADVERTISE, adv_val);

	/* Disable autoneg */
	bmcr_val = phy_read(phydev, MII_BMCR);
	bmcr_val &= ~(BMCR_ANENABLE);
	phy_write(phydev, MII_BMCR, bmcr_val);

	bmcr_val = phy_read(phydev, MII_BMCR);
	bmcr_val |= BMCR_ANRESTART;
	phy_write(phydev, MII_BMCR, bmcr_val);
}

>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
/**
 * stmmac_init_phy - PHY initialization
 * @dev: net device structure
 * Description: it initializes the driver's PHY state, and attaches the PHY
 * to the mac driver.
 *  Return value:
 *  0 on success
 */
static int stmmac_init_phy(struct net_device *dev)
{
	struct stmmac_priv *priv = netdev_priv(dev);
	u32 tx_cnt = priv->plat->tx_queues_to_use;
	struct phy_device *phydev;
	char phy_id_fmt[MII_BUS_ID_SIZE + 3];
	char bus_id[MII_BUS_ID_SIZE];
	int interface = priv->plat->interface;
	int max_speed = priv->plat->max_speed;
<<<<<<< HEAD
	priv->oldlink = false;
	priv->speed = SPEED_UNKNOWN;
	priv->oldduplex = DUPLEX_UNKNOWN;

	if (priv->plat->phy_node) {
		phydev = of_phy_connect(dev, priv->plat->phy_node,
					&stmmac_adjust_link, 0, interface);
	} else {
		snprintf(bus_id, MII_BUS_ID_SIZE, "stmmac-%x",
			 priv->plat->bus_id);

		snprintf(phy_id_fmt, MII_BUS_ID_SIZE + 3, PHY_ID_FMT, bus_id,
			 priv->plat->phy_addr);
		netdev_dbg(priv->dev, "%s: trying to attach to %s\n", __func__,
			   phy_id_fmt);

		phydev = phy_connect(dev, phy_id_fmt, &stmmac_adjust_link,
				     interface);
	}

	if (IS_ERR_OR_NULL(phydev)) {
		netdev_err(priv->dev, "Could not attach to PHY\n");
		if (!phydev)
			return -ENODEV;

		return PTR_ERR(phydev);
=======
	int ret = 0;
	priv->oldlink = -1;
	priv->boot_kpi = false;
	priv->speed = SPEED_UNKNOWN;
	priv->oldduplex = DUPLEX_UNKNOWN;

	if (priv->plat->early_eth && priv->phydev) {
		phydev = priv->phydev;
		phydev->skip_sw_reset = true;
		ret = phy_connect_direct(dev, phydev,
					 &stmmac_adjust_link, interface);
		if (ret) {
			pr_info("phy_connect_direct failed\n");
			return ret;
		}
	} else {
		if (priv->plat->phy_node) {
			phydev = of_phy_connect(dev,
						priv->plat->phy_node,
						&stmmac_adjust_link,
						0, interface);
		} else {
			snprintf(bus_id, MII_BUS_ID_SIZE, "stmmac-%x",
				 priv->plat->bus_id);

			snprintf(phy_id_fmt,
				 MII_BUS_ID_SIZE + 3, PHY_ID_FMT, bus_id,
				 priv->plat->phy_addr);

			netdev_dbg(priv->dev,
				   "%s: trying to attach to %s\n", __func__,
				   phy_id_fmt);

			phydev = phy_connect(dev,
					     phy_id_fmt,
					     &stmmac_adjust_link,
					     interface);
		}

		if (IS_ERR_OR_NULL(phydev)) {
			netdev_err(priv->dev, "Could not attach to PHY\n");
			if (!phydev)
				return -ENODEV;

			return PTR_ERR(phydev);
		}
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	}

	/* Stop Advertising 1000BASE Capability if interface is not GMII */
	if ((interface == PHY_INTERFACE_MODE_MII) ||
	    (interface == PHY_INTERFACE_MODE_RMII) ||
		(max_speed < 1000 && max_speed > 0))
		phydev->advertising &= ~(SUPPORTED_1000baseT_Half |
					 SUPPORTED_1000baseT_Full);

	/*
	 * Half-duplex mode not supported with multiqueue
	 * half-duplex can only works with single queue
	 */
	if (tx_cnt > 1)
		phydev->supported &= ~(SUPPORTED_1000baseT_Half |
				       SUPPORTED_100baseT_Half |
				       SUPPORTED_10baseT_Half);

<<<<<<< HEAD
=======
	/* Early ethernet settings to bring up link in 100M,
	 * Auto neg Off with full duplex link.
	 */
	if (max_speed == SPEED_100 && priv->plat->early_eth) {
		phydev->autoneg = AUTONEG_DISABLE;
		phydev->speed = SPEED_100;
		phydev->duplex = DUPLEX_FULL;

		phydev->advertising = phydev->supported;
		phydev->advertising &= ~(SUPPORTED_1000baseT_Full);

		pr_info(" qcom-ethqos: %s early eth setting successful\n",
			__func__);

		stmmac_set_speed100(phydev);
	}

>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	/*
	 * Broken HW is sometimes missing the pull-up resistor on the
	 * MDIO line, which results in reads to non-existent devices returning
	 * 0 rather than 0xffff. Catch this here and treat 0 as a non-existent
	 * device as well.
	 * Note: phydev->phy_id is the result of reading the UID PHY registers.
	 */
	if (!priv->plat->phy_node && phydev->phy_id == 0) {
		phy_disconnect(phydev);
		return -ENODEV;
	}

	/* stmmac_adjust_link will change this to PHY_IGNORE_INTERRUPT to avoid
	 * subsequent PHY polling, make sure we force a link transition if
	 * we have a UP/DOWN/UP transition
	 */
	if (phydev->is_pseudo_fixed_link)
		phydev->irq = PHY_POLL;

<<<<<<< HEAD
=======
	if (((phydev->phy_id & phydev->drv->phy_id_mask) == MICREL_PHY_ID) &&
	    !priv->plat->phy_intr_en) {
		ret = ethqos_phy_intr_enable(priv);
		if (ret)
			pr_alert("qcom-ethqos: Unable to enable PHY interrupt\n");
		else
			priv->plat->phy_intr_en = true;
	}

	if (phy_intr_en) {
		phydev->irq = PHY_IGNORE_INTERRUPT;
		phydev->interrupts =  PHY_INTERRUPT_ENABLED;
		if (phydev->drv->config_intr &&
		    !phydev->drv->config_intr(phydev)) {
			pr_debug(" qcom-ethqos: %s config_phy_intr successful\n",
				 __func__);
			qcom_ethqos_request_phy_wol(priv->plat);
		} else {
			pr_alert("Unable to register PHY IRQ\n");
			phydev->irq = PHY_POLL;
		}
	}
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	phy_attached_info(phydev);
	return 0;
}

static void stmmac_display_rx_rings(struct stmmac_priv *priv)
{
	u32 rx_cnt = priv->plat->rx_queues_to_use;
	void *head_rx;
	u32 queue;

	/* Display RX rings */
	for (queue = 0; queue < rx_cnt; queue++) {
		struct stmmac_rx_queue *rx_q = &priv->rx_queue[queue];

		pr_info("\tRX Queue %u rings\n", queue);

		if (priv->extend_desc)
			head_rx = (void *)rx_q->dma_erx;
		else
			head_rx = (void *)rx_q->dma_rx;

		/* Display RX ring */
<<<<<<< HEAD
		stmmac_display_ring(priv, head_rx, DMA_RX_SIZE, true);
=======
		priv->hw->desc->display_ring(head_rx, DMA_RX_SIZE, true);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	}
}

static void stmmac_display_tx_rings(struct stmmac_priv *priv)
{
	u32 tx_cnt = priv->plat->tx_queues_to_use;
	void *head_tx;
	u32 queue;

	/* Display TX rings */
	for (queue = 0; queue < tx_cnt; queue++) {
		struct stmmac_tx_queue *tx_q = &priv->tx_queue[queue];

		pr_info("\tTX Queue %d rings\n", queue);

		if (priv->extend_desc)
			head_tx = (void *)tx_q->dma_etx;
		else
			head_tx = (void *)tx_q->dma_tx;

<<<<<<< HEAD
		stmmac_display_ring(priv, head_tx, DMA_TX_SIZE, false);
=======
		priv->hw->desc->display_ring(head_tx, DMA_TX_SIZE, false);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	}
}

static void stmmac_display_rings(struct stmmac_priv *priv)
{
	/* Display RX ring */
	stmmac_display_rx_rings(priv);

	/* Display TX ring */
	stmmac_display_tx_rings(priv);
}

static int stmmac_set_bfsize(int mtu, int bufsize)
{
	int ret = bufsize;

<<<<<<< HEAD
	if (mtu >= BUF_SIZE_4KiB)
=======
	if (mtu >= BUF_SIZE_8KiB)
		ret = BUF_SIZE_16KiB;
	else if (mtu >= BUF_SIZE_4KiB)
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
		ret = BUF_SIZE_8KiB;
	else if (mtu >= BUF_SIZE_2KiB)
		ret = BUF_SIZE_4KiB;
	else if (mtu > DEFAULT_BUFSIZE)
		ret = BUF_SIZE_2KiB;
	else
		ret = DEFAULT_BUFSIZE;

	return ret;
}

/**
 * stmmac_clear_rx_descriptors - clear RX descriptors
 * @priv: driver private structure
 * @queue: RX queue index
 * Description: this function is called to clear the RX descriptors
 * in case of both basic and extended descriptors are used.
 */
static void stmmac_clear_rx_descriptors(struct stmmac_priv *priv, u32 queue)
{
	struct stmmac_rx_queue *rx_q = &priv->rx_queue[queue];
	int i;

	/* Clear the RX descriptors */
	for (i = 0; i < DMA_RX_SIZE; i++)
		if (priv->extend_desc)
<<<<<<< HEAD
			stmmac_init_rx_desc(priv, &rx_q->dma_erx[i].basic,
					priv->use_riwt, priv->mode,
					(i == DMA_RX_SIZE - 1),
					priv->dma_buf_sz);
		else
			stmmac_init_rx_desc(priv, &rx_q->dma_rx[i],
					priv->use_riwt, priv->mode,
					(i == DMA_RX_SIZE - 1),
					priv->dma_buf_sz);
=======
			priv->hw->desc->init_rx_desc(&rx_q->dma_erx[i].basic,
						     priv->use_riwt, priv->mode,
						     (i == DMA_RX_SIZE - 1),
						     priv->dma_buf_sz);
		else
			priv->hw->desc->init_rx_desc(&rx_q->dma_rx[i],
						     priv->use_riwt, priv->mode,
						     (i == DMA_RX_SIZE - 1),
						     priv->dma_buf_sz);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
}

/**
 * stmmac_clear_tx_descriptors - clear tx descriptors
 * @priv: driver private structure
 * @queue: TX queue index.
 * Description: this function is called to clear the TX descriptors
 * in case of both basic and extended descriptors are used.
 */
static void stmmac_clear_tx_descriptors(struct stmmac_priv *priv, u32 queue)
{
	struct stmmac_tx_queue *tx_q = &priv->tx_queue[queue];
	int i;

	/* Clear the TX descriptors */
	for (i = 0; i < DMA_TX_SIZE; i++)
		if (priv->extend_desc)
<<<<<<< HEAD
			stmmac_init_tx_desc(priv, &tx_q->dma_etx[i].basic,
					priv->mode, (i == DMA_TX_SIZE - 1));
		else
			stmmac_init_tx_desc(priv, &tx_q->dma_tx[i],
					priv->mode, (i == DMA_TX_SIZE - 1));
=======
			priv->hw->desc->init_tx_desc(&tx_q->dma_etx[i].basic,
						     priv->mode,
						     (i == DMA_TX_SIZE - 1));
		else
			priv->hw->desc->init_tx_desc(&tx_q->dma_tx[i],
						     priv->mode,
						     (i == DMA_TX_SIZE - 1));
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
}

/**
 * stmmac_clear_descriptors - clear descriptors
 * @priv: driver private structure
 * Description: this function is called to clear the TX and RX descriptors
 * in case of both basic and extended descriptors are used.
 */
static void stmmac_clear_descriptors(struct stmmac_priv *priv)
{
	u32 rx_queue_cnt = priv->plat->rx_queues_to_use;
	u32 tx_queue_cnt = priv->plat->tx_queues_to_use;
	u32 queue;

	/* Clear the RX descriptors */
	for (queue = 0; queue < rx_queue_cnt; queue++)
		stmmac_clear_rx_descriptors(priv, queue);

	/* Clear the TX descriptors */
	for (queue = 0; queue < tx_queue_cnt; queue++)
		stmmac_clear_tx_descriptors(priv, queue);
}

/**
 * stmmac_init_rx_buffers - init the RX descriptor buffer.
 * @priv: driver private structure
 * @p: descriptor pointer
 * @i: descriptor index
 * @flags: gfp flag
 * @queue: RX queue index
 * Description: this function is called to allocate a receive buffer, perform
 * the DMA mapping and init the descriptor.
 */
static int stmmac_init_rx_buffers(struct stmmac_priv *priv, struct dma_desc *p,
				  int i, gfp_t flags, u32 queue)
{
	struct stmmac_rx_queue *rx_q = &priv->rx_queue[queue];
	struct sk_buff *skb;

	skb = __netdev_alloc_skb_ip_align(priv->dev, priv->dma_buf_sz, flags);
	if (!skb) {
		netdev_err(priv->dev,
			   "%s: Rx init fails; skb is NULL\n", __func__);
		return -ENOMEM;
	}
	rx_q->rx_skbuff[i] = skb;
<<<<<<< HEAD
	rx_q->rx_skbuff_dma[i] = dma_map_single(priv->device, skb->data,
						priv->dma_buf_sz,
						DMA_FROM_DEVICE);
	if (dma_mapping_error(priv->device, rx_q->rx_skbuff_dma[i])) {
=======
	rx_q->rx_skbuff_dma[i] = dma_map_single(GET_MEM_PDEV_DEV, skb->data,
						priv->dma_buf_sz,
						DMA_FROM_DEVICE);
	if (dma_mapping_error(GET_MEM_PDEV_DEV, rx_q->rx_skbuff_dma[i])) {
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
		netdev_err(priv->dev, "%s: DMA mapping error\n", __func__);
		dev_kfree_skb_any(skb);
		return -EINVAL;
	}

<<<<<<< HEAD
	stmmac_set_desc_addr(priv, p, rx_q->rx_skbuff_dma[i]);

	if (priv->dma_buf_sz == BUF_SIZE_16KiB)
		stmmac_init_desc3(priv, p);
=======
	if (priv->synopsys_id >= DWMAC_CORE_4_00)
		p->des0 = cpu_to_le32(rx_q->rx_skbuff_dma[i]);
	else
		p->des2 = cpu_to_le32(rx_q->rx_skbuff_dma[i]);

	if ((priv->hw->mode->init_desc3) &&
	    (priv->dma_buf_sz == BUF_SIZE_16KiB))
		priv->hw->mode->init_desc3(p);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	return 0;
}

/**
 * stmmac_free_rx_buffer - free RX dma buffers
 * @priv: private structure
 * @queue: RX queue index
 * @i: buffer index.
 */
static void stmmac_free_rx_buffer(struct stmmac_priv *priv, u32 queue, int i)
{
	struct stmmac_rx_queue *rx_q = &priv->rx_queue[queue];

	if (rx_q->rx_skbuff[i]) {
<<<<<<< HEAD
		dma_unmap_single(priv->device, rx_q->rx_skbuff_dma[i],
=======
		dma_unmap_single(GET_MEM_PDEV_DEV, rx_q->rx_skbuff_dma[i],
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
				 priv->dma_buf_sz, DMA_FROM_DEVICE);
		dev_kfree_skb_any(rx_q->rx_skbuff[i]);
	}
	rx_q->rx_skbuff[i] = NULL;
}

/**
 * stmmac_free_tx_buffer - free RX dma buffers
 * @priv: private structure
 * @queue: RX queue index
 * @i: buffer index.
 */
static void stmmac_free_tx_buffer(struct stmmac_priv *priv, u32 queue, int i)
{
	struct stmmac_tx_queue *tx_q = &priv->tx_queue[queue];

	if (tx_q->tx_skbuff_dma[i].buf) {
		if (tx_q->tx_skbuff_dma[i].map_as_page)
<<<<<<< HEAD
			dma_unmap_page(priv->device,
=======
			dma_unmap_page(GET_MEM_PDEV_DEV,
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
				       tx_q->tx_skbuff_dma[i].buf,
				       tx_q->tx_skbuff_dma[i].len,
				       DMA_TO_DEVICE);
		else
<<<<<<< HEAD
			dma_unmap_single(priv->device,
=======
			dma_unmap_single(GET_MEM_PDEV_DEV,
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
					 tx_q->tx_skbuff_dma[i].buf,
					 tx_q->tx_skbuff_dma[i].len,
					 DMA_TO_DEVICE);
	}

	if (tx_q->tx_skbuff[i]) {
		dev_kfree_skb_any(tx_q->tx_skbuff[i]);
		tx_q->tx_skbuff[i] = NULL;
		tx_q->tx_skbuff_dma[i].buf = 0;
		tx_q->tx_skbuff_dma[i].map_as_page = false;
	}
}

/**
 * init_dma_rx_desc_rings - init the RX descriptor rings
 * @dev: net device structure
 * @flags: gfp flag.
 * Description: this function initializes the DMA RX descriptors
 * and allocates the socket buffers. It supports the chained and ring
 * modes.
 */
static int init_dma_rx_desc_rings(struct net_device *dev, gfp_t flags)
{
	struct stmmac_priv *priv = netdev_priv(dev);
	u32 rx_count = priv->plat->rx_queues_to_use;
<<<<<<< HEAD
	int ret = -ENOMEM;
	int bfsize = 0;
	int queue;
	int i;

	bfsize = stmmac_set_16kib_bfsize(priv, dev->mtu);
	if (bfsize < 0)
		bfsize = 0;
=======
	unsigned int bfsize = 0;
	int ret = -ENOMEM;
	int queue;
	int i;

	if (priv->hw->mode->set_16kib_bfsize)
		bfsize = priv->hw->mode->set_16kib_bfsize(dev->mtu);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	if (bfsize < BUF_SIZE_16KiB)
		bfsize = stmmac_set_bfsize(dev->mtu, priv->dma_buf_sz);

	priv->dma_buf_sz = bfsize;

	/* RX INITIALIZATION */
	netif_dbg(priv, probe, priv->dev,
		  "SKB addresses:\nskb\t\tskb data\tdma data\n");

	for (queue = 0; queue < rx_count; queue++) {
		struct stmmac_rx_queue *rx_q = &priv->rx_queue[queue];

		netif_dbg(priv, probe, priv->dev,
			  "(%s) dma_rx_phy=0x%08x\n", __func__,
			  (u32)rx_q->dma_rx_phy);

		for (i = 0; i < DMA_RX_SIZE; i++) {
			struct dma_desc *p;

			if (priv->extend_desc)
				p = &((rx_q->dma_erx + i)->basic);
			else
				p = rx_q->dma_rx + i;

			ret = stmmac_init_rx_buffers(priv, p, i, flags,
						     queue);
			if (ret)
				goto err_init_rx_buffers;

			netif_dbg(priv, probe, priv->dev, "[%p]\t[%p]\t[%x]\n",
				  rx_q->rx_skbuff[i], rx_q->rx_skbuff[i]->data,
				  (unsigned int)rx_q->rx_skbuff_dma[i]);
		}

		rx_q->cur_rx = 0;
		rx_q->dirty_rx = (unsigned int)(i - DMA_RX_SIZE);

		stmmac_clear_rx_descriptors(priv, queue);

		/* Setup the chained descriptor addresses */
		if (priv->mode == STMMAC_CHAIN_MODE) {
			if (priv->extend_desc)
<<<<<<< HEAD
				stmmac_mode_init(priv, rx_q->dma_erx,
						rx_q->dma_rx_phy, DMA_RX_SIZE, 1);
			else
				stmmac_mode_init(priv, rx_q->dma_rx,
						rx_q->dma_rx_phy, DMA_RX_SIZE, 0);
=======
				priv->hw->mode->init(rx_q->dma_erx,
						     rx_q->dma_rx_phy,
						     DMA_RX_SIZE, 1);
			else
				priv->hw->mode->init(rx_q->dma_rx,
						     rx_q->dma_rx_phy,
						     DMA_RX_SIZE, 0);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
		}
	}

	buf_sz = bfsize;

	return 0;

err_init_rx_buffers:
	while (queue >= 0) {
		while (--i >= 0)
			stmmac_free_rx_buffer(priv, queue, i);

		if (queue == 0)
			break;

		i = DMA_RX_SIZE;
		queue--;
	}

	return ret;
}

/**
 * init_dma_tx_desc_rings - init the TX descriptor rings
 * @dev: net device structure.
 * Description: this function initializes the DMA TX descriptors
 * and allocates the socket buffers. It supports the chained and ring
 * modes.
 */
static int init_dma_tx_desc_rings(struct net_device *dev)
{
	struct stmmac_priv *priv = netdev_priv(dev);
	u32 tx_queue_cnt = priv->plat->tx_queues_to_use;
	u32 queue;
	int i;

	for (queue = 0; queue < tx_queue_cnt; queue++) {
		struct stmmac_tx_queue *tx_q = &priv->tx_queue[queue];

		netif_dbg(priv, probe, priv->dev,
			  "(%s) dma_tx_phy=0x%08x\n", __func__,
			 (u32)tx_q->dma_tx_phy);

		/* Setup the chained descriptor addresses */
		if (priv->mode == STMMAC_CHAIN_MODE) {
			if (priv->extend_desc)
<<<<<<< HEAD
				stmmac_mode_init(priv, tx_q->dma_etx,
						tx_q->dma_tx_phy, DMA_TX_SIZE, 1);
			else
				stmmac_mode_init(priv, tx_q->dma_tx,
						tx_q->dma_tx_phy, DMA_TX_SIZE, 0);
=======
				priv->hw->mode->init(tx_q->dma_etx,
						     tx_q->dma_tx_phy,
						     DMA_TX_SIZE, 1);
			else
				priv->hw->mode->init(tx_q->dma_tx,
						     tx_q->dma_tx_phy,
						     DMA_TX_SIZE, 0);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
		}

		for (i = 0; i < DMA_TX_SIZE; i++) {
			struct dma_desc *p;
			if (priv->extend_desc)
				p = &((tx_q->dma_etx + i)->basic);
			else
				p = tx_q->dma_tx + i;

<<<<<<< HEAD
			stmmac_clear_desc(priv, p);
=======
			if (priv->synopsys_id >= DWMAC_CORE_4_00) {
				p->des0 = 0;
				p->des1 = 0;
				p->des2 = 0;
				p->des3 = 0;
			} else {
				p->des2 = 0;
			}
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

			tx_q->tx_skbuff_dma[i].buf = 0;
			tx_q->tx_skbuff_dma[i].map_as_page = false;
			tx_q->tx_skbuff_dma[i].len = 0;
			tx_q->tx_skbuff_dma[i].last_segment = false;
			tx_q->tx_skbuff[i] = NULL;
		}

		tx_q->dirty_tx = 0;
		tx_q->cur_tx = 0;
<<<<<<< HEAD
		tx_q->mss = 0;
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

		netdev_tx_reset_queue(netdev_get_tx_queue(priv->dev, queue));
	}

	return 0;
}

/**
 * init_dma_desc_rings - init the RX/TX descriptor rings
 * @dev: net device structure
 * @flags: gfp flag.
 * Description: this function initializes the DMA RX/TX descriptors
 * and allocates the socket buffers. It supports the chained and ring
 * modes.
 */
static int init_dma_desc_rings(struct net_device *dev, gfp_t flags)
{
	struct stmmac_priv *priv = netdev_priv(dev);
	int ret;

	ret = init_dma_rx_desc_rings(dev, flags);
	if (ret)
		return ret;

	ret = init_dma_tx_desc_rings(dev);

	stmmac_clear_descriptors(priv);

	if (netif_msg_hw(priv))
		stmmac_display_rings(priv);

	return ret;
}

/**
 * dma_free_rx_skbufs - free RX dma buffers
 * @priv: private structure
 * @queue: RX queue index
 */
static void dma_free_rx_skbufs(struct stmmac_priv *priv, u32 queue)
{
	int i;

	for (i = 0; i < DMA_RX_SIZE; i++)
		stmmac_free_rx_buffer(priv, queue, i);
}

/**
 * dma_free_tx_skbufs - free TX dma buffers
 * @priv: private structure
 * @queue: TX queue index
 */
static void dma_free_tx_skbufs(struct stmmac_priv *priv, u32 queue)
{
	int i;

	for (i = 0; i < DMA_TX_SIZE; i++)
		stmmac_free_tx_buffer(priv, queue, i);
}

/**
 * free_dma_rx_desc_resources - free RX dma desc resources
 * @priv: private structure
 */
static void free_dma_rx_desc_resources(struct stmmac_priv *priv)
{
	u32 rx_count = priv->plat->rx_queues_to_use;
	u32 queue;

	/* Free RX queue resources */
	for (queue = 0; queue < rx_count; queue++) {
		struct stmmac_rx_queue *rx_q = &priv->rx_queue[queue];

		/* Release the DMA RX socket buffers */
		dma_free_rx_skbufs(priv, queue);

		/* Free DMA regions of consistent memory previously allocated */
		if (!priv->extend_desc)
<<<<<<< HEAD
			dma_free_coherent(priv->device,
					  DMA_RX_SIZE * sizeof(struct dma_desc),
					  rx_q->dma_rx, rx_q->dma_rx_phy);
		else
			dma_free_coherent(priv->device, DMA_RX_SIZE *
=======
			dma_free_coherent(GET_MEM_PDEV_DEV,
					  DMA_RX_SIZE * sizeof(struct dma_desc),
					  rx_q->dma_rx, rx_q->dma_rx_phy);
		else
			dma_free_coherent(GET_MEM_PDEV_DEV, DMA_RX_SIZE *
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
					  sizeof(struct dma_extended_desc),
					  rx_q->dma_erx, rx_q->dma_rx_phy);

		kfree(rx_q->rx_skbuff_dma);
		kfree(rx_q->rx_skbuff);
	}
}

/**
 * free_dma_tx_desc_resources - free TX dma desc resources
 * @priv: private structure
 */
static void free_dma_tx_desc_resources(struct stmmac_priv *priv)
{
	u32 tx_count = priv->plat->tx_queues_to_use;
	u32 queue;

	/* Free TX queue resources */
	for (queue = 0; queue < tx_count; queue++) {
		struct stmmac_tx_queue *tx_q = &priv->tx_queue[queue];

		/* Release the DMA TX socket buffers */
		dma_free_tx_skbufs(priv, queue);

		/* Free DMA regions of consistent memory previously allocated */
		if (!priv->extend_desc)
<<<<<<< HEAD
			dma_free_coherent(priv->device,
					  DMA_TX_SIZE * sizeof(struct dma_desc),
					  tx_q->dma_tx, tx_q->dma_tx_phy);
		else
			dma_free_coherent(priv->device, DMA_TX_SIZE *
=======
			dma_free_coherent(GET_MEM_PDEV_DEV,
					  DMA_TX_SIZE * sizeof(struct dma_desc),
					  tx_q->dma_tx, tx_q->dma_tx_phy);
		else
			dma_free_coherent(GET_MEM_PDEV_DEV, DMA_TX_SIZE *
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
					  sizeof(struct dma_extended_desc),
					  tx_q->dma_etx, tx_q->dma_tx_phy);

		kfree(tx_q->tx_skbuff_dma);
		kfree(tx_q->tx_skbuff);
	}
}

/**
 * alloc_dma_rx_desc_resources - alloc RX resources.
 * @priv: private structure
 * Description: according to which descriptor can be used (extend or basic)
 * this function allocates the resources for TX and RX paths. In case of
 * reception, for example, it pre-allocated the RX socket buffer in order to
 * allow zero-copy mechanism.
 */
static int alloc_dma_rx_desc_resources(struct stmmac_priv *priv)
{
	u32 rx_count = priv->plat->rx_queues_to_use;
	int ret = -ENOMEM;
	u32 queue;

	/* RX queues buffers and DMA */
	for (queue = 0; queue < rx_count; queue++) {
		struct stmmac_rx_queue *rx_q = &priv->rx_queue[queue];

		rx_q->queue_index = queue;
		rx_q->priv_data = priv;

		rx_q->rx_skbuff_dma = kmalloc_array(DMA_RX_SIZE,
						    sizeof(dma_addr_t),
						    GFP_KERNEL);
		if (!rx_q->rx_skbuff_dma)
			goto err_dma;

		rx_q->rx_skbuff = kmalloc_array(DMA_RX_SIZE,
						sizeof(struct sk_buff *),
						GFP_KERNEL);
		if (!rx_q->rx_skbuff)
			goto err_dma;

		if (priv->extend_desc) {
<<<<<<< HEAD
			rx_q->dma_erx = dma_zalloc_coherent(priv->device,
=======
			rx_q->dma_erx = dma_zalloc_coherent(GET_MEM_PDEV_DEV,
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
							    DMA_RX_SIZE *
							    sizeof(struct
							    dma_extended_desc),
							    &rx_q->dma_rx_phy,
							    GFP_KERNEL);
			if (!rx_q->dma_erx)
				goto err_dma;

		} else {
<<<<<<< HEAD
			rx_q->dma_rx = dma_zalloc_coherent(priv->device,
=======
			rx_q->dma_rx = dma_zalloc_coherent(GET_MEM_PDEV_DEV,
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
							   DMA_RX_SIZE *
							   sizeof(struct
							   dma_desc),
							   &rx_q->dma_rx_phy,
							   GFP_KERNEL);
			if (!rx_q->dma_rx)
				goto err_dma;
		}
	}

	return 0;

err_dma:
	free_dma_rx_desc_resources(priv);

	return ret;
}

/**
 * alloc_dma_tx_desc_resources - alloc TX resources.
 * @priv: private structure
 * Description: according to which descriptor can be used (extend or basic)
 * this function allocates the resources for TX and RX paths. In case of
 * reception, for example, it pre-allocated the RX socket buffer in order to
 * allow zero-copy mechanism.
 */
static int alloc_dma_tx_desc_resources(struct stmmac_priv *priv)
{
	u32 tx_count = priv->plat->tx_queues_to_use;
	int ret = -ENOMEM;
	u32 queue;

	/* TX queues buffers and DMA */
	for (queue = 0; queue < tx_count; queue++) {
		struct stmmac_tx_queue *tx_q = &priv->tx_queue[queue];

		tx_q->queue_index = queue;
		tx_q->priv_data = priv;

		tx_q->tx_skbuff_dma = kmalloc_array(DMA_TX_SIZE,
						    sizeof(*tx_q->tx_skbuff_dma),
						    GFP_KERNEL);
		if (!tx_q->tx_skbuff_dma)
			goto err_dma;

		tx_q->tx_skbuff = kmalloc_array(DMA_TX_SIZE,
						sizeof(struct sk_buff *),
						GFP_KERNEL);
		if (!tx_q->tx_skbuff)
			goto err_dma;

		if (priv->extend_desc) {
<<<<<<< HEAD
			tx_q->dma_etx = dma_zalloc_coherent(priv->device,
=======
			tx_q->dma_etx = dma_zalloc_coherent(GET_MEM_PDEV_DEV,
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
							    DMA_TX_SIZE *
							    sizeof(struct
							    dma_extended_desc),
							    &tx_q->dma_tx_phy,
							    GFP_KERNEL);
			if (!tx_q->dma_etx)
				goto err_dma;
		} else {
<<<<<<< HEAD
			tx_q->dma_tx = dma_zalloc_coherent(priv->device,
=======
			tx_q->dma_tx = dma_zalloc_coherent(GET_MEM_PDEV_DEV,
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
							   DMA_TX_SIZE *
							   sizeof(struct
								  dma_desc),
							   &tx_q->dma_tx_phy,
							   GFP_KERNEL);
			if (!tx_q->dma_tx)
				goto err_dma;
		}
	}

	return 0;

err_dma:
	free_dma_tx_desc_resources(priv);

	return ret;
}

/**
 * alloc_dma_desc_resources - alloc TX/RX resources.
 * @priv: private structure
 * Description: according to which descriptor can be used (extend or basic)
 * this function allocates the resources for TX and RX paths. In case of
 * reception, for example, it pre-allocated the RX socket buffer in order to
 * allow zero-copy mechanism.
 */
static int alloc_dma_desc_resources(struct stmmac_priv *priv)
{
	/* RX Allocation */
	int ret = alloc_dma_rx_desc_resources(priv);

	if (ret)
		return ret;

	ret = alloc_dma_tx_desc_resources(priv);

	return ret;
}

/**
 * free_dma_desc_resources - free dma desc resources
 * @priv: private structure
 */
static void free_dma_desc_resources(struct stmmac_priv *priv)
{
	/* Release the DMA RX socket buffers */
	free_dma_rx_desc_resources(priv);

	/* Release the DMA TX socket buffers */
	free_dma_tx_desc_resources(priv);
}

/**
 *  stmmac_mac_enable_rx_queues - Enable MAC rx queues
 *  @priv: driver private structure
 *  Description: It is used for enabling the rx queues in the MAC
 */
static void stmmac_mac_enable_rx_queues(struct stmmac_priv *priv)
{
	u32 rx_queues_count = priv->plat->rx_queues_to_use;
	int queue;
	u8 mode;

	for (queue = 0; queue < rx_queues_count; queue++) {
		mode = priv->plat->rx_queues_cfg[queue].mode_to_use;
<<<<<<< HEAD
		stmmac_rx_queue_enable(priv, priv->hw, mode, queue);
=======
		priv->hw->mac->rx_queue_enable(priv->hw, mode, queue);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	}
}

/**
 * stmmac_start_rx_dma - start RX DMA channel
 * @priv: driver private structure
 * @chan: RX channel index
 * Description:
 * This starts a RX DMA channel
 */
static void stmmac_start_rx_dma(struct stmmac_priv *priv, u32 chan)
{
	netdev_dbg(priv->dev, "DMA RX processes started in channel %d\n", chan);
<<<<<<< HEAD
	stmmac_start_rx(priv, priv->ioaddr, chan);
=======
	priv->hw->dma->start_rx(priv->ioaddr, chan);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
}

/**
 * stmmac_start_tx_dma - start TX DMA channel
 * @priv: driver private structure
 * @chan: TX channel index
 * Description:
 * This starts a TX DMA channel
 */
static void stmmac_start_tx_dma(struct stmmac_priv *priv, u32 chan)
{
	netdev_dbg(priv->dev, "DMA TX processes started in channel %d\n", chan);
<<<<<<< HEAD
	stmmac_start_tx(priv, priv->ioaddr, chan);
=======
	priv->hw->dma->start_tx(priv->ioaddr, chan);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
}

/**
 * stmmac_stop_rx_dma - stop RX DMA channel
 * @priv: driver private structure
 * @chan: RX channel index
 * Description:
 * This stops a RX DMA channel
 */
static void stmmac_stop_rx_dma(struct stmmac_priv *priv, u32 chan)
{
	netdev_dbg(priv->dev, "DMA RX processes stopped in channel %d\n", chan);
<<<<<<< HEAD
	stmmac_stop_rx(priv, priv->ioaddr, chan);
=======
	priv->hw->dma->stop_rx(priv->ioaddr, chan);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
}

/**
 * stmmac_stop_tx_dma - stop TX DMA channel
 * @priv: driver private structure
 * @chan: TX channel index
 * Description:
 * This stops a TX DMA channel
 */
static void stmmac_stop_tx_dma(struct stmmac_priv *priv, u32 chan)
{
	netdev_dbg(priv->dev, "DMA TX processes stopped in channel %d\n", chan);
<<<<<<< HEAD
	stmmac_stop_tx(priv, priv->ioaddr, chan);
=======
	priv->hw->dma->stop_tx(priv->ioaddr, chan);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
}

/**
 * stmmac_start_all_dma - start all RX and TX DMA channels
 * @priv: driver private structure
 * Description:
 * This starts all the RX and TX DMA channels
 */
static void stmmac_start_all_dma(struct stmmac_priv *priv)
{
	u32 rx_channels_count = priv->plat->rx_queues_to_use;
	u32 tx_channels_count = priv->plat->tx_queues_to_use;
	u32 chan = 0;

<<<<<<< HEAD
	for (chan = 0; chan < rx_channels_count; chan++)
		stmmac_start_rx_dma(priv, chan);

	for (chan = 0; chan < tx_channels_count; chan++)
		stmmac_start_tx_dma(priv, chan);
=======
	for (chan = 0; chan < rx_channels_count; chan++) {
		if (priv->rx_queue[chan].skip_sw)
			continue;
		stmmac_start_rx_dma(priv, chan);
	}

	for (chan = 0; chan < tx_channels_count; chan++) {
		if (priv->tx_queue[chan].skip_sw)
			continue;
		stmmac_start_tx_dma(priv, chan);
	}
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
}

/**
 * stmmac_stop_all_dma - stop all RX and TX DMA channels
 * @priv: driver private structure
 * Description:
 * This stops the RX and TX DMA channels
 */
static void stmmac_stop_all_dma(struct stmmac_priv *priv)
{
	u32 rx_channels_count = priv->plat->rx_queues_to_use;
	u32 tx_channels_count = priv->plat->tx_queues_to_use;
	u32 chan = 0;

<<<<<<< HEAD
	for (chan = 0; chan < rx_channels_count; chan++)
		stmmac_stop_rx_dma(priv, chan);

	for (chan = 0; chan < tx_channels_count; chan++)
		stmmac_stop_tx_dma(priv, chan);
=======
	for (chan = 0; chan < rx_channels_count; chan++) {
		if (priv->rx_queue[chan].skip_sw)
			continue;
		stmmac_stop_rx_dma(priv, chan);
	}
	for (chan = 0; chan < tx_channels_count; chan++) {
		if (priv->tx_queue[chan].skip_sw)
			continue;
		stmmac_stop_tx_dma(priv, chan);
	}
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
}

/**
 *  stmmac_dma_operation_mode - HW DMA operation mode
 *  @priv: driver private structure
 *  Description: it is used for configuring the DMA operation mode register in
 *  order to program the tx/rx DMA thresholds or Store-And-Forward mode.
 */
static void stmmac_dma_operation_mode(struct stmmac_priv *priv)
{
	u32 rx_channels_count = priv->plat->rx_queues_to_use;
	u32 tx_channels_count = priv->plat->tx_queues_to_use;
	int rxfifosz = priv->plat->rx_fifo_size;
	int txfifosz = priv->plat->tx_fifo_size;
	u32 txmode = 0;
	u32 rxmode = 0;
	u32 chan = 0;
<<<<<<< HEAD
=======
	u32 mtl_rx_int;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	u8 qmode = 0;

	if (rxfifosz == 0)
		rxfifosz = priv->dma_cap.rx_fifo_size;
	if (txfifosz == 0)
		txfifosz = priv->dma_cap.tx_fifo_size;

	/* Adjust for real per queue fifo size */
	rxfifosz /= rx_channels_count;
	txfifosz /= tx_channels_count;

	if (priv->plat->force_thresh_dma_mode) {
		txmode = tc;
		rxmode = tc;
	} else if (priv->plat->force_sf_dma_mode || priv->plat->tx_coe) {
		/*
		 * In case of GMAC, SF mode can be enabled
		 * to perform the TX COE in HW. This depends on:
		 * 1) TX COE if actually supported
		 * 2) There is no bugged Jumbo frame support
		 *    that needs to not insert csum in the TDES.
		 */
		txmode = SF_DMA_MODE;
		rxmode = SF_DMA_MODE;
		priv->xstats.threshold = SF_DMA_MODE;
	} else {
		txmode = tc;
		rxmode = SF_DMA_MODE;
	}

	/* configure all channels */
<<<<<<< HEAD
	for (chan = 0; chan < rx_channels_count; chan++) {
		qmode = priv->plat->rx_queues_cfg[chan].mode_to_use;

		stmmac_dma_rx_mode(priv, priv->ioaddr, rxmode, chan,
				rxfifosz, qmode);
		stmmac_set_dma_bfsize(priv, priv->ioaddr, priv->dma_buf_sz,
				chan);
	}

	for (chan = 0; chan < tx_channels_count; chan++) {
		qmode = priv->plat->tx_queues_cfg[chan].mode_to_use;

		stmmac_dma_tx_mode(priv, priv->ioaddr, txmode, chan,
				txfifosz, qmode);
=======
	if (priv->synopsys_id >= DWMAC_CORE_4_00) {
		for (chan = 0; chan < rx_channels_count; chan++) {
			qmode = priv->plat->rx_queues_cfg[chan].mode_to_use;

			priv->hw->dma->dma_rx_mode(priv->ioaddr, rxmode, chan,
						   rxfifosz, qmode);
			if (priv->rx_queue[chan].skip_sw) {
				mtl_rx_int = readl_relaxed(priv->ioaddr +
							   (0x00000d00 + 0x2c));
				writel_relaxed(mtl_rx_int & ~(BIT(24)),
					       priv->ioaddr +
					       (0x00000d00 + 0x2c));
			}

			if (priv->rx_queue[chan].en_fep)
				priv->hw->dma->enable_rx_fep(priv->ioaddr,
							     true, chan);
		}

		for (chan = 0; chan < tx_channels_count; chan++) {
			qmode = priv->plat->tx_queues_cfg[chan].mode_to_use;

			priv->hw->dma->dma_tx_mode(priv->ioaddr, txmode, chan,
						   txfifosz, qmode);
		}
	} else {
		priv->hw->dma->dma_mode(priv->ioaddr, txmode, rxmode,
					rxfifosz);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	}
}

/**
 * stmmac_tx_clean - to manage the transmission completion
 * @priv: driver private structure
 * @queue: TX queue index
 * Description: it reclaims the transmit resources after transmission completes.
 */
<<<<<<< HEAD
static int stmmac_tx_clean(struct stmmac_priv *priv, int budget, u32 queue)
{
	struct stmmac_tx_queue *tx_q = &priv->tx_queue[queue];
	unsigned int bytes_compl = 0, pkts_compl = 0;
	unsigned int entry, count = 0;

	__netif_tx_lock_bh(netdev_get_tx_queue(priv->dev, queue));
=======
static void stmmac_tx_clean(struct stmmac_priv *priv, u32 queue)
{
	struct stmmac_tx_queue *tx_q = &priv->tx_queue[queue];
	unsigned int bytes_compl = 0, pkts_compl = 0;
	unsigned int entry;

	netif_tx_lock(priv->dev);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	priv->xstats.tx_clean++;

	entry = tx_q->dirty_tx;
<<<<<<< HEAD
	while ((entry != tx_q->cur_tx) && (count < budget)) {
=======
	while (entry != tx_q->cur_tx) {
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
		struct sk_buff *skb = tx_q->tx_skbuff[entry];
		struct dma_desc *p;
		int status;

		if (priv->extend_desc)
			p = (struct dma_desc *)(tx_q->dma_etx + entry);
		else
			p = tx_q->dma_tx + entry;

<<<<<<< HEAD
		status = stmmac_tx_status(priv, &priv->dev->stats,
				&priv->xstats, p, priv->ioaddr);
=======
		status = priv->hw->desc->tx_status(&priv->dev->stats,
						      &priv->xstats, p,
						      priv->ioaddr);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
		/* Check if the descriptor is owned by the DMA */
		if (unlikely(status & tx_dma_own))
			break;

<<<<<<< HEAD
		count++;

=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
		/* Make sure descriptor fields are read after reading
		 * the own bit.
		 */
		dma_rmb();

		/* Just consider the last segment and ...*/
		if (likely(!(status & tx_not_ls))) {
			/* ... verify the status error condition */
			if (unlikely(status & tx_err)) {
				priv->dev->stats.tx_errors++;
			} else {
				priv->dev->stats.tx_packets++;
				priv->xstats.tx_pkt_n++;
<<<<<<< HEAD
=======
				priv->xstats.q_tx_pkt_n[queue]++;
#ifdef CONFIG_MSM_BOOT_TIME_MARKER
if (priv->dev->stats.tx_packets == 1)
	place_marker("M - Ethernet first packet transmitted");
#endif
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
			}
			stmmac_get_tx_hwtstamp(priv, p, skb);
		}

		if (likely(tx_q->tx_skbuff_dma[entry].buf)) {
			if (tx_q->tx_skbuff_dma[entry].map_as_page)
<<<<<<< HEAD
				dma_unmap_page(priv->device,
=======
				dma_unmap_page(GET_MEM_PDEV_DEV,
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
					       tx_q->tx_skbuff_dma[entry].buf,
					       tx_q->tx_skbuff_dma[entry].len,
					       DMA_TO_DEVICE);
			else
<<<<<<< HEAD
				dma_unmap_single(priv->device,
=======
				dma_unmap_single(GET_MEM_PDEV_DEV,
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
						 tx_q->tx_skbuff_dma[entry].buf,
						 tx_q->tx_skbuff_dma[entry].len,
						 DMA_TO_DEVICE);
			tx_q->tx_skbuff_dma[entry].buf = 0;
			tx_q->tx_skbuff_dma[entry].len = 0;
			tx_q->tx_skbuff_dma[entry].map_as_page = false;
		}

<<<<<<< HEAD
		stmmac_clean_desc3(priv, tx_q, p);
=======
		if (priv->hw->mode->clean_desc3)
			priv->hw->mode->clean_desc3(tx_q, p);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

		tx_q->tx_skbuff_dma[entry].last_segment = false;
		tx_q->tx_skbuff_dma[entry].is_jumbo = false;

		if (likely(skb != NULL)) {
			pkts_compl++;
			bytes_compl += skb->len;
			dev_consume_skb_any(skb);
			tx_q->tx_skbuff[entry] = NULL;
		}

<<<<<<< HEAD
		stmmac_release_tx_desc(priv, p, priv->mode);
=======
		priv->hw->desc->release_tx_desc(p, priv->mode);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

		entry = STMMAC_GET_ENTRY(entry, DMA_TX_SIZE);
	}
	tx_q->dirty_tx = entry;

<<<<<<< HEAD
	netdev_tx_completed_queue(netdev_get_tx_queue(priv->dev, queue),
				  pkts_compl, bytes_compl);
=======
	if (!priv->tx_coal_timer_disable)
		netdev_tx_completed_queue(
			netdev_get_tx_queue(priv->dev, queue),
			pkts_compl, bytes_compl);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	if (unlikely(netif_tx_queue_stopped(netdev_get_tx_queue(priv->dev,
								queue))) &&
	    stmmac_tx_avail(priv, queue) > STMMAC_TX_THRESH) {

		netif_dbg(priv, tx_done, priv->dev,
			  "%s: restart transmit\n", __func__);
		netif_tx_wake_queue(netdev_get_tx_queue(priv->dev, queue));
	}

	if ((priv->eee_enabled) && (!priv->tx_path_in_lpi_mode)) {
		stmmac_enable_eee_mode(priv);
		mod_timer(&priv->eee_ctrl_timer, STMMAC_LPI_T(eee_timer));
	}
<<<<<<< HEAD

	__netif_tx_unlock_bh(netdev_get_tx_queue(priv->dev, queue));

	return count;
=======
	netif_tx_unlock(priv->dev);
}

static inline void stmmac_enable_dma_irq(struct stmmac_priv *priv, u32 chan)
{
	priv->hw->dma->enable_dma_irq(priv->ioaddr, chan);
}

static inline void stmmac_disable_dma_irq(struct stmmac_priv *priv, u32 chan)
{
	priv->hw->dma->disable_dma_irq(priv->ioaddr, chan);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
}

/**
 * stmmac_tx_err - to manage the tx error
 * @priv: driver private structure
 * @chan: channel index
 * Description: it cleans the descriptors and restarts the transmission
 * in case of transmission errors.
 */
static void stmmac_tx_err(struct stmmac_priv *priv, u32 chan)
{
	struct stmmac_tx_queue *tx_q = &priv->tx_queue[chan];
	int i;

<<<<<<< HEAD
=======
	if (tx_q->skip_sw) {
		ethqos_ipa_offload_event_handler(priv, EV_DEV_CLOSE);
		ethqos_ipa_offload_event_handler(priv, EV_DEV_OPEN);
		priv->dev->stats.tx_errors++;
		return;
	}

>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	netif_tx_stop_queue(netdev_get_tx_queue(priv->dev, chan));

	stmmac_stop_tx_dma(priv, chan);
	dma_free_tx_skbufs(priv, chan);
	for (i = 0; i < DMA_TX_SIZE; i++)
		if (priv->extend_desc)
<<<<<<< HEAD
			stmmac_init_tx_desc(priv, &tx_q->dma_etx[i].basic,
					priv->mode, (i == DMA_TX_SIZE - 1));
		else
			stmmac_init_tx_desc(priv, &tx_q->dma_tx[i],
					priv->mode, (i == DMA_TX_SIZE - 1));
	tx_q->dirty_tx = 0;
	tx_q->cur_tx = 0;
	tx_q->mss = 0;
=======
			priv->hw->desc->init_tx_desc(&tx_q->dma_etx[i].basic,
						     priv->mode,
						     (i == DMA_TX_SIZE - 1));
		else
			priv->hw->desc->init_tx_desc(&tx_q->dma_tx[i],
						     priv->mode,
						     (i == DMA_TX_SIZE - 1));
	tx_q->dirty_tx = 0;
	tx_q->cur_tx = 0;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	netdev_tx_reset_queue(netdev_get_tx_queue(priv->dev, chan));
	stmmac_start_tx_dma(priv, chan);

	priv->dev->stats.tx_errors++;
	netif_tx_wake_queue(netdev_get_tx_queue(priv->dev, chan));
}

/**
 *  stmmac_set_dma_operation_mode - Set DMA operation mode by channel
 *  @priv: driver private structure
 *  @txmode: TX operating mode
 *  @rxmode: RX operating mode
 *  @chan: channel index
 *  Description: it is used for configuring of the DMA operation mode in
 *  runtime in order to program the tx/rx DMA thresholds or Store-And-Forward
 *  mode.
 */
static void stmmac_set_dma_operation_mode(struct stmmac_priv *priv, u32 txmode,
					  u32 rxmode, u32 chan)
{
	u8 rxqmode = priv->plat->rx_queues_cfg[chan].mode_to_use;
	u8 txqmode = priv->plat->tx_queues_cfg[chan].mode_to_use;
	u32 rx_channels_count = priv->plat->rx_queues_to_use;
	u32 tx_channels_count = priv->plat->tx_queues_to_use;
	int rxfifosz = priv->plat->rx_fifo_size;
	int txfifosz = priv->plat->tx_fifo_size;

	if (rxfifosz == 0)
		rxfifosz = priv->dma_cap.rx_fifo_size;
	if (txfifosz == 0)
		txfifosz = priv->dma_cap.tx_fifo_size;

	/* Adjust for real per queue fifo size */
	rxfifosz /= rx_channels_count;
	txfifosz /= tx_channels_count;

<<<<<<< HEAD
	stmmac_dma_rx_mode(priv, priv->ioaddr, rxmode, chan, rxfifosz, rxqmode);
	stmmac_dma_tx_mode(priv, priv->ioaddr, txmode, chan, txfifosz, txqmode);
}

static bool stmmac_safety_feat_interrupt(struct stmmac_priv *priv)
{
	int ret;

	ret = stmmac_safety_feat_irq_status(priv, priv->dev,
			priv->ioaddr, priv->dma_cap.asp, &priv->sstats);
	if (ret && (ret != -EINVAL)) {
		stmmac_global_err(priv);
		return true;
	}

	return false;
}

static int stmmac_napi_check(struct stmmac_priv *priv, u32 chan)
{
	int status = stmmac_dma_interrupt_status(priv, priv->ioaddr,
						 &priv->xstats, chan);
	struct stmmac_channel *ch = &priv->channel[chan];
	bool needs_work = false;

	if ((status & handle_rx) && ch->has_rx) {
		needs_work = true;
	} else {
		status &= ~handle_rx;
	}

	if ((status & handle_tx) && ch->has_tx) {
		needs_work = true;
	} else {
		status &= ~handle_tx;
	}

	if (needs_work && napi_schedule_prep(&ch->napi)) {
		stmmac_disable_dma_irq(priv, priv->ioaddr, chan);
		__napi_schedule(&ch->napi);
	}

	return status;
=======
	if (priv->synopsys_id >= DWMAC_CORE_4_00) {
		priv->hw->dma->dma_rx_mode(priv->ioaddr, rxmode, chan,
					   rxfifosz, rxqmode);
		priv->hw->dma->dma_tx_mode(priv->ioaddr, txmode, chan,
					   txfifosz, txqmode);
	} else {
		priv->hw->dma->dma_mode(priv->ioaddr, txmode, rxmode,
					rxfifosz);
	}
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
}

/**
 * stmmac_dma_interrupt - DMA ISR
 * @priv: driver private structure
 * Description: this is the DMA ISR. It is called by the main ISR.
 * It calls the dwmac dma routine and schedule poll method in case of some
 * work can be done.
 */
static void stmmac_dma_interrupt(struct stmmac_priv *priv)
{
	u32 tx_channel_count = priv->plat->tx_queues_to_use;
<<<<<<< HEAD
	u32 rx_channel_count = priv->plat->rx_queues_to_use;
	u32 channels_to_check = tx_channel_count > rx_channel_count ?
				tx_channel_count : rx_channel_count;
	u32 chan;
	int status[max_t(u32, MTL_MAX_TX_QUEUES, MTL_MAX_RX_QUEUES)];

	/* Make sure we never check beyond our status buffer. */
	if (WARN_ON_ONCE(channels_to_check > ARRAY_SIZE(status)))
		channels_to_check = ARRAY_SIZE(status);

	for (chan = 0; chan < channels_to_check; chan++)
		status[chan] = stmmac_napi_check(priv, chan);

	for (chan = 0; chan < tx_channel_count; chan++) {
		if (unlikely(status[chan] & tx_hard_error_bump_tc)) {
=======
	int status;
	u32 chan;
	struct stmmac_rx_queue *rx_q;

	for (chan = 0; chan < tx_channel_count; chan++) {
		rx_q = &priv->rx_queue[chan];

		status = priv->hw->dma->dma_interrupt(priv->ioaddr,
						      &priv->xstats, chan);
		if (priv->rx_queue[chan].skip_sw && (status & handle_rx))
			ethqos_ipa_offload_event_handler(
				&chan, EV_IPA_HANDLE_RX_INTR);
		if (priv->tx_queue[chan].skip_sw && (status & handle_tx))
			ethqos_ipa_offload_event_handler(
				&chan, EV_IPA_HANDLE_TX_INTR);

		if ((likely((status & handle_rx)) || (status & handle_tx)) &&
		    !rx_q->skip_sw) {
			if (likely(napi_schedule_prep(&rx_q->napi))) {
				stmmac_disable_dma_irq(priv, chan);
				__napi_schedule(&rx_q->napi);
			}
		}

		if (unlikely(status & tx_hard_error_bump_tc)) {
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
			/* Try to bump up the dma threshold on this failure */
			if (unlikely(priv->xstats.threshold != SF_DMA_MODE) &&
			    (tc <= 256)) {
				tc += 64;
				if (priv->plat->force_thresh_dma_mode)
					stmmac_set_dma_operation_mode(priv,
								      tc,
								      tc,
								      chan);
				else
					stmmac_set_dma_operation_mode(priv,
								    tc,
								    SF_DMA_MODE,
								    chan);
				priv->xstats.threshold = tc;
			}
<<<<<<< HEAD
		} else if (unlikely(status[chan] == tx_hard_error)) {
=======
		} else if (unlikely(status == tx_hard_error)) {
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
			stmmac_tx_err(priv, chan);
		}
	}
}

/**
 * stmmac_mmc_setup: setup the Mac Management Counters (MMC)
 * @priv: driver private structure
 * Description: this masks the MMC irq, in fact, the counters are managed in SW.
 */
static void stmmac_mmc_setup(struct stmmac_priv *priv)
{
	unsigned int mode = MMC_CNTRL_RESET_ON_READ | MMC_CNTRL_COUNTER_RESET |
			    MMC_CNTRL_PRESET | MMC_CNTRL_FULL_HALF_PRESET;

<<<<<<< HEAD
=======
	if (priv->synopsys_id >= DWMAC_CORE_4_00) {
		priv->ptpaddr = priv->ioaddr + PTP_GMAC4_OFFSET;
		priv->mmcaddr = priv->ioaddr + MMC_GMAC4_OFFSET;
	} else {
		priv->ptpaddr = priv->ioaddr + PTP_GMAC3_X_OFFSET;
		priv->mmcaddr = priv->ioaddr + MMC_GMAC3_X_OFFSET;
	}

>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	dwmac_mmc_intr_all_mask(priv->mmcaddr);

	if (priv->dma_cap.rmon) {
		dwmac_mmc_ctrl(priv->mmcaddr, mode);
		memset(&priv->mmc, 0, sizeof(struct stmmac_counters));
	} else
		netdev_info(priv->dev, "No MAC Management Counters available\n");
}

/**
<<<<<<< HEAD
=======
 * stmmac_selec_desc_mode - to select among: normal/alternate/extend descriptors
 * @priv: driver private structure
 * Description: select the Enhanced/Alternate or Normal descriptors.
 * In case of Enhanced/Alternate, it checks if the extended descriptors are
 * supported by the HW capability register.
 */
static void stmmac_selec_desc_mode(struct stmmac_priv *priv)
{
	if (priv->plat->enh_desc) {
		dev_info(priv->device, "Enhanced/Alternate descriptors\n");

		/* GMAC older than 3.50 has no extended descriptors */
		if (priv->synopsys_id >= DWMAC_CORE_3_50) {
			dev_info(priv->device, "Enabled extended descriptors\n");
			priv->extend_desc = 1;
		} else
			dev_warn(priv->device, "Extended descriptors not supported\n");

		priv->hw->desc = &enh_desc_ops;
	} else {
		dev_info(priv->device, "Normal descriptors\n");
		priv->hw->desc = &ndesc_ops;
	}
}

/**
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
 * stmmac_get_hw_features - get MAC capabilities from the HW cap. register.
 * @priv: driver private structure
 * Description:
 *  new GMAC chip generations have a new register to indicate the
 *  presence of the optional feature/functions.
 *  This can be also used to override the value passed through the
 *  platform and necessary for old MAC10/100 and GMAC chips.
 */
static int stmmac_get_hw_features(struct stmmac_priv *priv)
{
<<<<<<< HEAD
	return stmmac_get_hw_feature(priv, priv->ioaddr, &priv->dma_cap) == 0;
=======
	u32 ret = 0;

	if (priv->hw->dma->get_hw_feature) {
		priv->hw->dma->get_hw_feature(priv->ioaddr,
					      &priv->dma_cap);
		ret = 1;
	}

	return ret;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
}

/**
 * stmmac_check_ether_addr - check if the MAC addr is valid
 * @priv: driver private structure
 * Description:
 * it is to verify if the MAC address is valid, in case of failures it
 * generates a random MAC address
 */
static void stmmac_check_ether_addr(struct stmmac_priv *priv)
{
	if (!is_valid_ether_addr(priv->dev->dev_addr)) {
<<<<<<< HEAD
		stmmac_get_umac_addr(priv, priv->hw, priv->dev->dev_addr, 0);
=======
		priv->hw->mac->get_umac_addr(priv->hw,
					     priv->dev->dev_addr, 0);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
		if (!is_valid_ether_addr(priv->dev->dev_addr))
			eth_hw_addr_random(priv->dev);
		netdev_info(priv->dev, "device MAC address %pM\n",
			    priv->dev->dev_addr);
	}
}

/**
 * stmmac_init_dma_engine - DMA init.
 * @priv: driver private structure
 * Description:
 * It inits the DMA invoking the specific MAC/GMAC callback.
 * Some DMA parameters can be passed from the platform;
 * in case of these are not passed a default is kept for the MAC or GMAC.
 */
static int stmmac_init_dma_engine(struct stmmac_priv *priv)
{
	u32 rx_channels_count = priv->plat->rx_queues_to_use;
	u32 tx_channels_count = priv->plat->tx_queues_to_use;
<<<<<<< HEAD
	u32 dma_csr_ch = max(rx_channels_count, tx_channels_count);
	struct stmmac_rx_queue *rx_q;
	struct stmmac_tx_queue *tx_q;
=======
	struct stmmac_rx_queue *rx_q;
	struct stmmac_tx_queue *tx_q;
	u32 dummy_dma_rx_phy = 0;
	u32 dummy_dma_tx_phy = 0;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	u32 chan = 0;
	int atds = 0;
	int ret = 0;

	if (!priv->plat->dma_cfg || !priv->plat->dma_cfg->pbl) {
		dev_err(priv->device, "Invalid DMA configuration\n");
		return -EINVAL;
	}

	if (priv->extend_desc && (priv->mode == STMMAC_RING_MODE))
		atds = 1;

<<<<<<< HEAD
	ret = stmmac_reset(priv, priv->ioaddr);
=======
	ret = priv->hw->dma->reset(priv->ioaddr);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	if (ret) {
		dev_err(priv->device, "Failed to reset the dma\n");
		return ret;
	}

<<<<<<< HEAD
	/* DMA Configuration */
	stmmac_dma_init(priv, priv->ioaddr, priv->plat->dma_cfg, atds);

	if (priv->plat->axi)
		stmmac_axi(priv, priv->ioaddr, priv->plat->axi);

	/* DMA CSR Channel configuration */
	for (chan = 0; chan < dma_csr_ch; chan++)
		stmmac_init_chan(priv, priv->ioaddr, priv->plat->dma_cfg, chan);

	/* DMA RX Channel Configuration */
	for (chan = 0; chan < rx_channels_count; chan++) {
		rx_q = &priv->rx_queue[chan];

		stmmac_init_rx_chan(priv, priv->ioaddr, priv->plat->dma_cfg,
				    rx_q->dma_rx_phy, chan);

		rx_q->rx_tail_addr = rx_q->dma_rx_phy +
			    (DMA_RX_SIZE * sizeof(struct dma_desc));
		stmmac_set_rx_tail_ptr(priv, priv->ioaddr,
				       rx_q->rx_tail_addr, chan);
	}

	/* DMA TX Channel Configuration */
	for (chan = 0; chan < tx_channels_count; chan++) {
		tx_q = &priv->tx_queue[chan];

		stmmac_init_tx_chan(priv, priv->ioaddr, priv->plat->dma_cfg,
				    tx_q->dma_tx_phy, chan);

		tx_q->tx_tail_addr = tx_q->dma_tx_phy;
		stmmac_set_tx_tail_ptr(priv, priv->ioaddr,
				       tx_q->tx_tail_addr, chan);
	}

	return ret;
}

static void stmmac_tx_timer_arm(struct stmmac_priv *priv, u32 queue)
{
	struct stmmac_tx_queue *tx_q = &priv->tx_queue[queue];

	mod_timer(&tx_q->txtimer, STMMAC_COAL_TIMER(priv->tx_coal_timer));
}

=======
	if (priv->synopsys_id >= DWMAC_CORE_4_00) {
		/* DMA Configuration */
		priv->hw->dma->init(priv->ioaddr, priv->plat->dma_cfg,
				    dummy_dma_tx_phy, dummy_dma_rx_phy, atds);

		/* DMA RX Channel Configuration */
		for (chan = 0; chan < rx_channels_count; chan++) {
			rx_q = &priv->rx_queue[chan];

			priv->hw->dma->init_rx_chan(priv->ioaddr,
						    priv->plat->dma_cfg,
						    rx_q->dma_rx_phy, chan);

			rx_q->rx_tail_addr = rx_q->dma_rx_phy +
				    (DMA_RX_SIZE * sizeof(struct dma_desc));
			priv->hw->dma->set_rx_tail_ptr(priv->ioaddr,
						       rx_q->rx_tail_addr,
						       chan);
		}

		/* DMA TX Channel Configuration */
		for (chan = 0; chan < tx_channels_count; chan++) {
			tx_q = &priv->tx_queue[chan];

			priv->hw->dma->init_chan(priv->ioaddr,
						 priv->plat->dma_cfg,
						 chan);

			priv->hw->dma->init_tx_chan(priv->ioaddr,
						    priv->plat->dma_cfg,
						    tx_q->dma_tx_phy, chan);
			if (priv->tx_queue[chan].skip_sw)
				continue;
			tx_q->tx_tail_addr = tx_q->dma_tx_phy;
			priv->hw->dma->set_tx_tail_ptr(priv->ioaddr,
					       tx_q->tx_tail_addr,
					       chan);
		}
	} else {
		rx_q = &priv->rx_queue[chan];
		tx_q = &priv->tx_queue[chan];
		priv->hw->dma->init(priv->ioaddr, priv->plat->dma_cfg,
				    tx_q->dma_tx_phy, rx_q->dma_rx_phy, atds);
	}

	if (priv->plat->axi && priv->hw->dma->axi)
		priv->hw->dma->axi(priv->ioaddr, priv->plat->axi);

	return ret;
}

>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
/**
 * stmmac_tx_timer - mitigation sw timer for tx.
 * @data: data pointer
 * Description:
 * This is the timer handler to directly invoke the stmmac_tx_clean.
 */
<<<<<<< HEAD
static void stmmac_tx_timer(struct timer_list *t)
{
	struct stmmac_tx_queue *tx_q = from_timer(tx_q, t, txtimer);
	struct stmmac_priv *priv = tx_q->priv_data;
	struct stmmac_channel *ch;

	ch = &priv->channel[tx_q->queue_index];

	if (likely(napi_schedule_prep(&ch->napi)))
		__napi_schedule(&ch->napi);
=======
static void stmmac_tx_timer(unsigned long data)
{
	struct stmmac_priv *priv = (struct stmmac_priv *)data;
	u32 tx_queues_count = priv->plat->tx_queues_to_use;
	u32 queue;

	/* let's scan all the tx queues */
	for (queue = 0; queue < tx_queues_count; queue++) {
		if (priv->tx_queue[queue].skip_sw)
			continue;
		stmmac_tx_clean(priv, queue);
	}
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
}

/**
 * stmmac_init_tx_coalesce - init tx mitigation options.
 * @priv: driver private structure
 * Description:
 * This inits the transmit coalesce parameters: i.e. timer rate,
 * timer handler and default threshold used for enabling the
 * interrupt on completion bit.
 */
static void stmmac_init_tx_coalesce(struct stmmac_priv *priv)
{
<<<<<<< HEAD
	u32 tx_channel_count = priv->plat->tx_queues_to_use;
	u32 chan;

	priv->tx_coal_frames = STMMAC_TX_FRAMES;
	priv->tx_coal_timer = STMMAC_COAL_TX_TIMER;

	for (chan = 0; chan < tx_channel_count; chan++) {
		struct stmmac_tx_queue *tx_q = &priv->tx_queue[chan];

		timer_setup(&tx_q->txtimer, stmmac_tx_timer, 0);
	}
=======
	priv->tx_coal_frames = STMMAC_TX_FRAMES;
	priv->tx_coal_timer = STMMAC_COAL_TX_TIMER;
	init_timer(&priv->txtimer);
	priv->txtimer.expires = STMMAC_COAL_TIMER(priv->tx_coal_timer);
	priv->txtimer.data = (unsigned long)priv;
	priv->txtimer.function = stmmac_tx_timer;
	add_timer(&priv->txtimer);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
}

static void stmmac_set_rings_length(struct stmmac_priv *priv)
{
	u32 rx_channels_count = priv->plat->rx_queues_to_use;
	u32 tx_channels_count = priv->plat->tx_queues_to_use;
	u32 chan;

	/* set TX ring length */
<<<<<<< HEAD
	for (chan = 0; chan < tx_channels_count; chan++)
		stmmac_set_tx_ring_len(priv, priv->ioaddr,
				(DMA_TX_SIZE - 1), chan);

	/* set RX ring length */
	for (chan = 0; chan < rx_channels_count; chan++)
		stmmac_set_rx_ring_len(priv, priv->ioaddr,
				(DMA_RX_SIZE - 1), chan);
=======
	if (priv->hw->dma->set_tx_ring_len) {
		for (chan = 0; chan < tx_channels_count; chan++)
			priv->hw->dma->set_tx_ring_len(priv->ioaddr,
						       (DMA_TX_SIZE - 1), chan);
	}

	/* set RX ring length */
	if (priv->hw->dma->set_rx_ring_len) {
		for (chan = 0; chan < rx_channels_count; chan++)
			priv->hw->dma->set_rx_ring_len(priv->ioaddr,
						       (DMA_RX_SIZE - 1), chan);
	}
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
}

/**
 *  stmmac_set_tx_queue_weight - Set TX queue weight
 *  @priv: driver private structure
 *  Description: It is used for setting TX queues weight
 */
static void stmmac_set_tx_queue_weight(struct stmmac_priv *priv)
{
	u32 tx_queues_count = priv->plat->tx_queues_to_use;
	u32 weight;
	u32 queue;

	for (queue = 0; queue < tx_queues_count; queue++) {
		weight = priv->plat->tx_queues_cfg[queue].weight;
<<<<<<< HEAD
		stmmac_set_mtl_tx_queue_weight(priv, priv->hw, weight, queue);
=======
		priv->hw->mac->set_mtl_tx_queue_weight(priv->hw, weight, queue);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	}
}

/**
 *  stmmac_configure_cbs - Configure CBS in TX queue
 *  @priv: driver private structure
 *  Description: It is used for configuring CBS in AVB TX queues
 */
static void stmmac_configure_cbs(struct stmmac_priv *priv)
{
	u32 tx_queues_count = priv->plat->tx_queues_to_use;
	u32 mode_to_use;
	u32 queue;

	/* queue 0 is reserved for legacy traffic */
	for (queue = 1; queue < tx_queues_count; queue++) {
		mode_to_use = priv->plat->tx_queues_cfg[queue].mode_to_use;
		if (mode_to_use == MTL_QUEUE_DCB)
			continue;

<<<<<<< HEAD
		stmmac_config_cbs(priv, priv->hw,
=======
		priv->hw->mac->config_cbs(priv->hw,
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
				priv->plat->tx_queues_cfg[queue].send_slope,
				priv->plat->tx_queues_cfg[queue].idle_slope,
				priv->plat->tx_queues_cfg[queue].high_credit,
				priv->plat->tx_queues_cfg[queue].low_credit,
				queue);
	}
}

/**
 *  stmmac_rx_queue_dma_chan_map - Map RX queue to RX dma channel
 *  @priv: driver private structure
 *  Description: It is used for mapping RX queues to RX dma channels
 */
static void stmmac_rx_queue_dma_chan_map(struct stmmac_priv *priv)
{
	u32 rx_queues_count = priv->plat->rx_queues_to_use;
	u32 queue;
	u32 chan;

	for (queue = 0; queue < rx_queues_count; queue++) {
<<<<<<< HEAD
		chan = priv->plat->rx_queues_cfg[queue].chan;
		stmmac_map_mtl_to_dma(priv, priv->hw, queue, chan);
=======
		if (priv->rx_queue[queue].skip_sw)
			continue;
		chan = priv->plat->rx_queues_cfg[queue].chan;
		priv->hw->mac->map_mtl_to_dma(priv->hw, queue, chan);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	}
}

/**
 *  stmmac_mac_config_rx_queues_prio - Configure RX Queue priority
 *  @priv: driver private structure
 *  Description: It is used for configuring the RX Queue Priority
 */
static void stmmac_mac_config_rx_queues_prio(struct stmmac_priv *priv)
{
	u32 rx_queues_count = priv->plat->rx_queues_to_use;
	u32 queue;
	u32 prio;

	for (queue = 0; queue < rx_queues_count; queue++) {
		if (!priv->plat->rx_queues_cfg[queue].use_prio)
			continue;

		prio = priv->plat->rx_queues_cfg[queue].prio;
<<<<<<< HEAD
		stmmac_rx_queue_prio(priv, priv->hw, prio, queue);
=======
		priv->hw->mac->rx_queue_prio(priv->hw, prio, queue);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	}
}

/**
 *  stmmac_mac_config_tx_queues_prio - Configure TX Queue priority
 *  @priv: driver private structure
 *  Description: It is used for configuring the TX Queue Priority
 */
static void stmmac_mac_config_tx_queues_prio(struct stmmac_priv *priv)
{
	u32 tx_queues_count = priv->plat->tx_queues_to_use;
	u32 queue;
	u32 prio;

	for (queue = 0; queue < tx_queues_count; queue++) {
		if (!priv->plat->tx_queues_cfg[queue].use_prio)
			continue;

		prio = priv->plat->tx_queues_cfg[queue].prio;
<<<<<<< HEAD
		stmmac_tx_queue_prio(priv, priv->hw, prio, queue);
=======
		priv->hw->mac->tx_queue_prio(priv->hw, prio, queue);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	}
}

/**
 *  stmmac_mac_config_rx_queues_routing - Configure RX Queue Routing
 *  @priv: driver private structure
 *  Description: It is used for configuring the RX queue routing
 */
static void stmmac_mac_config_rx_queues_routing(struct stmmac_priv *priv)
{
	u32 rx_queues_count = priv->plat->rx_queues_to_use;
	u32 queue;
	u8 packet;

	for (queue = 0; queue < rx_queues_count; queue++) {
		/* no specific packet type routing specified for the queue */
		if (priv->plat->rx_queues_cfg[queue].pkt_route == 0x0)
			continue;

		packet = priv->plat->rx_queues_cfg[queue].pkt_route;
<<<<<<< HEAD
		stmmac_rx_queue_routing(priv, priv->hw, packet, queue);
=======
		priv->hw->mac->rx_queue_routing(priv->hw, packet, queue);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	}
}

/**
 *  stmmac_mtl_configuration - Configure MTL
 *  @priv: driver private structure
 *  Description: It is used for configurring MTL
 */
static void stmmac_mtl_configuration(struct stmmac_priv *priv)
{
	u32 rx_queues_count = priv->plat->rx_queues_to_use;
	u32 tx_queues_count = priv->plat->tx_queues_to_use;

<<<<<<< HEAD
	if (tx_queues_count > 1)
		stmmac_set_tx_queue_weight(priv);

	/* Configure MTL RX algorithms */
	if (rx_queues_count > 1)
		stmmac_prog_mtl_rx_algorithms(priv, priv->hw,
				priv->plat->rx_sched_algorithm);

	/* Configure MTL TX algorithms */
	if (tx_queues_count > 1)
		stmmac_prog_mtl_tx_algorithms(priv, priv->hw,
				priv->plat->tx_sched_algorithm);

	/* Configure CBS in AVB TX queues */
	if (tx_queues_count > 1)
		stmmac_configure_cbs(priv);

	/* Map RX MTL to DMA channels */
	stmmac_rx_queue_dma_chan_map(priv);

	/* Enable MAC RX Queues */
	stmmac_mac_enable_rx_queues(priv);

	/* Set RX priorities */
	if (rx_queues_count > 1)
		stmmac_mac_config_rx_queues_prio(priv);

	/* Set TX priorities */
	if (tx_queues_count > 1)
		stmmac_mac_config_tx_queues_prio(priv);

	/* Set RX routing */
	if (rx_queues_count > 1)
		stmmac_mac_config_rx_queues_routing(priv);
}

static void stmmac_safety_feat_configuration(struct stmmac_priv *priv)
{
	if (priv->dma_cap.asp) {
		netdev_info(priv->dev, "Enabling Safety Features\n");
		stmmac_safety_feat_config(priv, priv->ioaddr, priv->dma_cap.asp);
	} else {
		netdev_info(priv->dev, "No Safety Features support found\n");
	}
}

=======
	if (tx_queues_count > 1 && priv->hw->mac->set_mtl_tx_queue_weight)
		stmmac_set_tx_queue_weight(priv);

	/* Configure MTL RX algorithms */
	if (rx_queues_count > 1 && priv->hw->mac->prog_mtl_rx_algorithms)
		priv->hw->mac->prog_mtl_rx_algorithms(priv->hw,
						priv->plat->rx_sched_algorithm);

	/* Configure MTL TX algorithms */
	if (tx_queues_count > 1 && priv->hw->mac->prog_mtl_tx_algorithms)
		priv->hw->mac->prog_mtl_tx_algorithms(priv->hw,
						priv->plat->tx_sched_algorithm);

	/* Configure CBS in AVB TX queues */
	if (tx_queues_count > 1 && priv->hw->mac->config_cbs)
		stmmac_configure_cbs(priv);

	/* Map RX MTL to DMA channels */
	if (priv->hw->mac->map_mtl_to_dma)
		stmmac_rx_queue_dma_chan_map(priv);

	/* Enable MAC RX Queues */
	if (priv->hw->mac->rx_queue_enable)
		stmmac_mac_enable_rx_queues(priv);

	/* Set RX priorities */
	if (rx_queues_count > 1 && priv->hw->mac->rx_queue_prio)
		stmmac_mac_config_rx_queues_prio(priv);

	/* Set TX priorities */
	if (tx_queues_count > 1 && priv->hw->mac->tx_queue_prio)
		stmmac_mac_config_tx_queues_prio(priv);

	/* Set RX routing */
	if (rx_queues_count > 1 && priv->hw->mac->rx_queue_routing)
		stmmac_mac_config_rx_queues_routing(priv);
}

>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
/**
 * stmmac_hw_setup - setup mac in a usable state.
 *  @dev : pointer to the device structure.
 *  Description:
 *  this is the main function to setup the HW in a usable state because the
 *  dma engine is reset, the core registers are configured (e.g. AXI,
 *  Checksum features, timers). The DMA is ready to start receiving and
 *  transmitting.
 *  Return value:
 *  0 on success and an appropriate (-)ve integer as defined in errno.h
 *  file on failure.
 */
static int stmmac_hw_setup(struct net_device *dev, bool init_ptp)
{
	struct stmmac_priv *priv = netdev_priv(dev);
	u32 rx_cnt = priv->plat->rx_queues_to_use;
	u32 tx_cnt = priv->plat->tx_queues_to_use;
	u32 chan;
	int ret;

	/* DMA initialization and SW reset */
	ret = stmmac_init_dma_engine(priv);
	if (ret < 0) {
		netdev_err(priv->dev, "%s: DMA engine initialization failed\n",
			   __func__);
		return ret;
	}

	/* Copy the MAC addr into the HW  */
<<<<<<< HEAD
	stmmac_set_umac_addr(priv, priv->hw, dev->dev_addr, 0);
=======
	priv->hw->mac->set_umac_addr(priv->hw, dev->dev_addr, 0);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	/* PS and related bits will be programmed according to the speed */
	if (priv->hw->pcs) {
		int speed = priv->plat->mac_port_sel_speed;

		if ((speed == SPEED_10) || (speed == SPEED_100) ||
		    (speed == SPEED_1000)) {
			priv->hw->ps = speed;
		} else {
			dev_warn(priv->device, "invalid port speed\n");
			priv->hw->ps = 0;
		}
	}
<<<<<<< HEAD

	/* Initialize the MAC Core */
	stmmac_core_init(priv, priv->hw, dev);

	/* Initialize MTL*/
	stmmac_mtl_configuration(priv);

	/* Initialize Safety Features */
	stmmac_safety_feat_configuration(priv);

	ret = stmmac_rx_ipc(priv, priv->hw);
=======
	priv->hw->crc_strip_en = priv->plat->crc_strip_en;
	priv->hw->acs_strip_en = 0;

	/* Initialize the MAC Core */
	priv->hw->mac->core_init(priv->hw, dev);

	/* Initialize MTL*/
	if (priv->synopsys_id >= DWMAC_CORE_4_00)
		stmmac_mtl_configuration(priv);

	ret = priv->hw->mac->rx_ipc(priv->hw);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	if (!ret) {
		netdev_warn(priv->dev, "RX IPC Checksum Offload disabled\n");
		priv->plat->rx_coe = STMMAC_RX_COE_NONE;
		priv->hw->rx_csum = 0;
	}

	/* Enable the MAC Rx/Tx */
<<<<<<< HEAD
	stmmac_mac_set(priv, priv->ioaddr, true);
=======
	priv->hw->mac->set_mac(priv->ioaddr, true);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	/* Set the HW DMA mode and the COE */
	stmmac_dma_operation_mode(priv);

	stmmac_mmc_setup(priv);

	if (init_ptp) {
		ret = clk_prepare_enable(priv->plat->clk_ptp_ref);
		if (ret < 0)
			netdev_warn(priv->dev, "failed to enable PTP reference clock: %d\n", ret);

		ret = stmmac_init_ptp(priv);
		if (ret == -EOPNOTSUPP)
			netdev_warn(priv->dev, "PTP not supported by HW\n");
		else if (ret)
			netdev_warn(priv->dev, "PTP init failed\n");
<<<<<<< HEAD
=======
		else
			clk_set_rate(
				priv->plat->clk_ptp_ref,
				priv->plat->clk_ptp_rate);

		ret = ethqos_init_pps(priv);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	}

	priv->tx_lpi_timer = STMMAC_DEFAULT_TWT_LS;

<<<<<<< HEAD
	if (priv->use_riwt) {
		ret = stmmac_rx_watchdog(priv, priv->ioaddr, MAX_DMA_RIWT, rx_cnt);
		if (!ret)
			priv->rx_riwt = MAX_DMA_RIWT;
	}

	if (priv->hw->pcs)
		stmmac_pcs_ctrl_ane(priv, priv->hw, 1, priv->hw->ps, 0);
=======
	if ((priv->use_riwt) && (priv->hw->dma->rx_watchdog)) {
		priv->rx_riwt = MAX_DMA_RIWT;
		priv->hw->dma->rx_watchdog(priv->ioaddr, MAX_DMA_RIWT, rx_cnt);
	}

	if (priv->hw->pcs && priv->hw->mac->pcs_ctrl_ane)
		priv->hw->mac->pcs_ctrl_ane(priv->hw, 1, priv->hw->ps, 0);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	/* set TX and RX rings length */
	stmmac_set_rings_length(priv);

	/* Enable TSO */
	if (priv->tso) {
		for (chan = 0; chan < tx_cnt; chan++)
<<<<<<< HEAD
			stmmac_enable_tso(priv, priv->ioaddr, 1, chan);
=======
			priv->hw->dma->enable_tso(priv->ioaddr, 1, chan);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	}

	/* Start the ball rolling... */
	stmmac_start_all_dma(priv);

	return 0;
}

static void stmmac_hw_teardown(struct net_device *dev)
{
	struct stmmac_priv *priv = netdev_priv(dev);

	clk_disable_unprepare(priv->plat->clk_ptp_ref);
}

/**
 *  stmmac_open - open entry point of the driver
 *  @dev : pointer to the device structure.
 *  Description:
 *  This function is the open entry point of the driver.
 *  Return value:
 *  0 on success and an appropriate (-)ve integer as defined in errno.h
 *  file on failure.
 */
static int stmmac_open(struct net_device *dev)
{
	struct stmmac_priv *priv = netdev_priv(dev);
<<<<<<< HEAD
	u32 chan;
	int ret;

	if (priv->hw->pcs != STMMAC_PCS_RGMII &&
	    priv->hw->pcs != STMMAC_PCS_TBI &&
	    priv->hw->pcs != STMMAC_PCS_RTBI) {
=======
	int ret;

	if (!priv->plat->mac2mac_en &&
	    (priv->hw->pcs != STMMAC_PCS_RGMII &&
	     priv->hw->pcs != STMMAC_PCS_TBI &&
	     priv->hw->pcs != STMMAC_PCS_RTBI)) {
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
		ret = stmmac_init_phy(dev);
		if (ret) {
			netdev_err(priv->dev,
				   "%s: Cannot attach to PHY (error: %d)\n",
				   __func__, ret);
			return ret;
		}
	}

	/* Extra statistics */
	memset(&priv->xstats, 0, sizeof(struct stmmac_extra_stats));
	priv->xstats.threshold = tc;

	priv->dma_buf_sz = STMMAC_ALIGN(buf_sz);
	priv->rx_copybreak = STMMAC_RX_COPYBREAK;
<<<<<<< HEAD
=======
	priv->mss = 0;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	ret = alloc_dma_desc_resources(priv);
	if (ret < 0) {
		netdev_err(priv->dev, "%s: DMA descriptors allocation failed\n",
			   __func__);
		goto dma_desc_error;
	}

	ret = init_dma_desc_rings(dev, GFP_KERNEL);
	if (ret < 0) {
		netdev_err(priv->dev, "%s: DMA descriptors initialization failed\n",
			   __func__);
		goto init_error;
	}

<<<<<<< HEAD
	ret = stmmac_hw_setup(dev, true);
=======
#ifdef CONFIG_PTPSUPPORT_OBJ
	ret = stmmac_hw_setup(dev, true);
#else
	ret = stmmac_hw_setup(dev, false);
#endif

>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	if (ret < 0) {
		netdev_err(priv->dev, "%s: Hw setup failed\n", __func__);
		goto init_error;
	}

<<<<<<< HEAD
	stmmac_init_tx_coalesce(priv);
=======
	if (!priv->tx_coal_timer_disable)
		stmmac_init_tx_coalesce(priv);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	if (dev->phydev)
		phy_start(dev->phydev);

	/* Request the IRQ lines */
	ret = request_irq(dev->irq, stmmac_interrupt,
			  IRQF_SHARED, dev->name, dev);
	if (unlikely(ret < 0)) {
		netdev_err(priv->dev,
			   "%s: ERROR: allocating the IRQ %d (error: %d)\n",
			   __func__, dev->irq, ret);
		goto irq_error;
	}

	/* Request the Wake IRQ in case of another line is used for WoL */
	if (priv->wol_irq != dev->irq) {
		ret = request_irq(priv->wol_irq, stmmac_interrupt,
				  IRQF_SHARED, dev->name, dev);
		if (unlikely(ret < 0)) {
			netdev_err(priv->dev,
				   "%s: ERROR: allocating the WoL IRQ %d (%d)\n",
				   __func__, priv->wol_irq, ret);
			goto wolirq_error;
		}
	}

	/* Request the IRQ lines */
	if (priv->lpi_irq > 0) {
		ret = request_irq(priv->lpi_irq, stmmac_interrupt, IRQF_SHARED,
				  dev->name, dev);
		if (unlikely(ret < 0)) {
			netdev_err(priv->dev,
				   "%s: ERROR: allocating the LPI IRQ %d (%d)\n",
				   __func__, priv->lpi_irq, ret);
			goto lpiirq_error;
		}
	}

	stmmac_enable_all_queues(priv);
	stmmac_start_all_queues(priv);
<<<<<<< HEAD
=======
	if (priv->hw_offload_enabled)
		ethqos_ipa_offload_event_handler(priv, EV_DEV_OPEN);

	if (priv->plat->mac2mac_en) {
		u32 ctrl = readl_relaxed(priv->ioaddr + MAC_CTRL_REG);

		ctrl &= ~priv->hw->link.speed_mask;

		if (priv->plat->mac2mac_rgmii_speed == SPEED_1000) {
			ctrl |= priv->hw->link.speed1000;
			priv->speed = SPEED_1000;
		} else if (priv->plat->mac2mac_rgmii_speed == SPEED_100) {
			ctrl |= priv->hw->link.speed100;
			priv->speed = SPEED_100;
		} else {
			ctrl |= priv->hw->link.speed10;
			priv->speed = SPEED_10;
		}

		stmmac_hw_fix_mac_speed(priv);
		writel_relaxed(ctrl, priv->ioaddr + MAC_CTRL_REG);
	}
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	return 0;

lpiirq_error:
	if (priv->wol_irq != dev->irq)
		free_irq(priv->wol_irq, dev);
wolirq_error:
	free_irq(dev->irq, dev);
irq_error:
	if (dev->phydev)
		phy_stop(dev->phydev);
<<<<<<< HEAD

	for (chan = 0; chan < priv->plat->tx_queues_to_use; chan++)
		del_timer_sync(&priv->tx_queue[chan].txtimer);

=======
	if (!priv->tx_coal_timer_disable)
		del_timer_sync(&priv->txtimer);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	stmmac_hw_teardown(dev);
init_error:
	free_dma_desc_resources(priv);
dma_desc_error:
	if (dev->phydev)
		phy_disconnect(dev->phydev);

	return ret;
}

/**
 *  stmmac_release - close entry point of the driver
 *  @dev : device pointer.
 *  Description:
 *  This is the stop entry point of the driver.
 */
static int stmmac_release(struct net_device *dev)
{
	struct stmmac_priv *priv = netdev_priv(dev);
<<<<<<< HEAD
	u32 chan;
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	if (priv->eee_enabled)
		del_timer_sync(&priv->eee_ctrl_timer);

	/* Stop and disconnect the PHY */
	if (dev->phydev) {
		phy_stop(dev->phydev);
		phy_disconnect(dev->phydev);
	}

	stmmac_stop_all_queues(priv);

	stmmac_disable_all_queues(priv);

<<<<<<< HEAD
	for (chan = 0; chan < priv->plat->tx_queues_to_use; chan++)
		del_timer_sync(&priv->tx_queue[chan].txtimer);
=======
	if (!priv->tx_coal_timer_disable)
		del_timer_sync(&priv->txtimer);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	/* Free the IRQ lines */
	free_irq(dev->irq, dev);
	if (priv->wol_irq != dev->irq)
		free_irq(priv->wol_irq, dev);
	if (priv->lpi_irq > 0)
		free_irq(priv->lpi_irq, dev);

	/* Stop TX/RX DMA and clear the descriptors */
	stmmac_stop_all_dma(priv);

	/* Release and free the Rx/Tx resources */
	free_dma_desc_resources(priv);
<<<<<<< HEAD

	/* Disable the MAC Rx/Tx */
	stmmac_mac_set(priv, priv->ioaddr, false);
=======
	if (priv->hw_offload_enabled)
		ethqos_ipa_offload_event_handler(priv, EV_DEV_CLOSE);

	/* Disable the MAC Rx/Tx */
	priv->hw->mac->set_mac(priv->ioaddr, false);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	netif_carrier_off(dev);

	stmmac_release_ptp(priv);

	return 0;
}

/**
 *  stmmac_tso_allocator - close entry point of the driver
 *  @priv: driver private structure
 *  @des: buffer start address
 *  @total_len: total length to fill in descriptors
 *  @last_segmant: condition for the last descriptor
 *  @queue: TX queue index
 *  Description:
 *  This function fills descriptor and request new descriptors according to
 *  buffer length to fill
 */
static void stmmac_tso_allocator(struct stmmac_priv *priv, unsigned int des,
				 int total_len, bool last_segment, u32 queue)
{
	struct stmmac_tx_queue *tx_q = &priv->tx_queue[queue];
	struct dma_desc *desc;
	u32 buff_size;
	int tmp_len;

	tmp_len = total_len;

	while (tmp_len > 0) {
		tx_q->cur_tx = STMMAC_GET_ENTRY(tx_q->cur_tx, DMA_TX_SIZE);
<<<<<<< HEAD
		WARN_ON(tx_q->tx_skbuff[tx_q->cur_tx]);
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
		desc = tx_q->dma_tx + tx_q->cur_tx;

		desc->des0 = cpu_to_le32(des + (total_len - tmp_len));
		buff_size = tmp_len >= TSO_MAX_BUFF_SIZE ?
			    TSO_MAX_BUFF_SIZE : tmp_len;

<<<<<<< HEAD
		stmmac_prepare_tso_tx_desc(priv, desc, 0, buff_size,
				0, 1,
				(last_segment) && (tmp_len <= TSO_MAX_BUFF_SIZE),
				0, 0);
=======
		priv->hw->desc->prepare_tso_tx_desc(desc, 0, buff_size,
			0, 1,
			(last_segment) && (tmp_len <= TSO_MAX_BUFF_SIZE),
			0, 0);

		if (last_segment && tmp_len <= TSO_MAX_BUFF_SIZE) {
			priv->tx_count_frames = 0;
			priv->hw->desc->set_tx_ic(desc);
			priv->xstats.tx_set_ic_bit++;
		}
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

		tmp_len -= TSO_MAX_BUFF_SIZE;
	}
}

/**
 *  stmmac_tso_xmit - Tx entry point of the driver for oversized frames (TSO)
 *  @skb : the socket buffer
 *  @dev : device pointer
 *  Description: this is the transmit function that is called on TSO frames
 *  (support available on GMAC4 and newer chips).
 *  Diagram below show the ring programming in case of TSO frames:
 *
 *  First Descriptor
 *   --------
 *   | DES0 |---> buffer1 = L2/L3/L4 header
 *   | DES1 |---> TCP Payload (can continue on next descr...)
 *   | DES2 |---> buffer 1 and 2 len
 *   | DES3 |---> must set TSE, TCP hdr len-> [22:19]. TCP payload len [17:0]
 *   --------
 *	|
 *     ...
 *	|
 *   --------
 *   | DES0 | --| Split TCP Payload on Buffers 1 and 2
 *   | DES1 | --|
 *   | DES2 | --> buffer 1 and 2 len
 *   | DES3 |
 *   --------
 *
 * mss is fixed when enable tso, so w/o programming the TDES3 ctx field.
 */
static netdev_tx_t stmmac_tso_xmit(struct sk_buff *skb, struct net_device *dev)
{
	struct dma_desc *desc, *first, *mss_desc = NULL;
	struct stmmac_priv *priv = netdev_priv(dev);
	int nfrags = skb_shinfo(skb)->nr_frags;
	u32 queue = skb_get_queue_mapping(skb);
	unsigned int first_entry, des;
	struct stmmac_tx_queue *tx_q;
	int tmp_pay_len = 0;
	u32 pay_len, mss;
	u8 proto_hdr_len;
	int i;

	tx_q = &priv->tx_queue[queue];

	/* Compute header lengths */
	proto_hdr_len = skb_transport_offset(skb) + tcp_hdrlen(skb);

	/* Desc availability based on threshold should be enough safe */
	if (unlikely(stmmac_tx_avail(priv, queue) <
		(((skb->len - proto_hdr_len) / TSO_MAX_BUFF_SIZE + 1)))) {
		if (!netif_tx_queue_stopped(netdev_get_tx_queue(dev, queue))) {
			netif_tx_stop_queue(netdev_get_tx_queue(priv->dev,
								queue));
			/* This is a hard error, log it. */
			netdev_err(priv->dev,
				   "%s: Tx Ring full when queue awake\n",
				   __func__);
		}
		return NETDEV_TX_BUSY;
	}

	pay_len = skb_headlen(skb) - proto_hdr_len; /* no frags */

	mss = skb_shinfo(skb)->gso_size;

	/* set new MSS value if needed */
<<<<<<< HEAD
	if (mss != tx_q->mss) {
		mss_desc = tx_q->dma_tx + tx_q->cur_tx;
		stmmac_set_mss(priv, mss_desc, mss);
		tx_q->mss = mss;
		tx_q->cur_tx = STMMAC_GET_ENTRY(tx_q->cur_tx, DMA_TX_SIZE);
		WARN_ON(tx_q->tx_skbuff[tx_q->cur_tx]);
=======
	if (mss != priv->mss) {
		mss_desc = tx_q->dma_tx + tx_q->cur_tx;
		priv->hw->desc->set_mss(mss_desc, mss);
		priv->mss = mss;
		tx_q->cur_tx = STMMAC_GET_ENTRY(tx_q->cur_tx, DMA_TX_SIZE);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	}

	if (netif_msg_tx_queued(priv)) {
		pr_info("%s: tcphdrlen %d, hdr_len %d, pay_len %d, mss %d\n",
			__func__, tcp_hdrlen(skb), proto_hdr_len, pay_len, mss);
		pr_info("\tskb->len %d, skb->data_len %d\n", skb->len,
			skb->data_len);
	}

	first_entry = tx_q->cur_tx;
<<<<<<< HEAD
	WARN_ON(tx_q->tx_skbuff[first_entry]);
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	desc = tx_q->dma_tx + first_entry;
	first = desc;

	/* first descriptor: fill Headers on Buf1 */
<<<<<<< HEAD
	des = dma_map_single(priv->device, skb->data, skb_headlen(skb),
			     DMA_TO_DEVICE);
	if (dma_mapping_error(priv->device, des))
=======
	des = dma_map_single(GET_MEM_PDEV_DEV, skb->data, skb_headlen(skb),
			     DMA_TO_DEVICE);
	if (dma_mapping_error(GET_MEM_PDEV_DEV, des))
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
		goto dma_map_err;

	tx_q->tx_skbuff_dma[first_entry].buf = des;
	tx_q->tx_skbuff_dma[first_entry].len = skb_headlen(skb);

	first->des0 = cpu_to_le32(des);

	/* Fill start of payload in buff2 of first descriptor */
	if (pay_len)
		first->des1 = cpu_to_le32(des + proto_hdr_len);

	/* If needed take extra descriptors to fill the remaining payload */
	tmp_pay_len = pay_len - TSO_MAX_BUFF_SIZE;

	stmmac_tso_allocator(priv, des, tmp_pay_len, (nfrags == 0), queue);

	/* Prepare fragments */
	for (i = 0; i < nfrags; i++) {
		const skb_frag_t *frag = &skb_shinfo(skb)->frags[i];

<<<<<<< HEAD
		des = skb_frag_dma_map(priv->device, frag, 0,
				       skb_frag_size(frag),
				       DMA_TO_DEVICE);
		if (dma_mapping_error(priv->device, des))
=======
		des = skb_frag_dma_map(GET_MEM_PDEV_DEV, frag, 0,
				       skb_frag_size(frag),
				       DMA_TO_DEVICE);
		if (dma_mapping_error(GET_MEM_PDEV_DEV, des))
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
			goto dma_map_err;

		stmmac_tso_allocator(priv, des, skb_frag_size(frag),
				     (i == nfrags - 1), queue);

		tx_q->tx_skbuff_dma[tx_q->cur_tx].buf = des;
		tx_q->tx_skbuff_dma[tx_q->cur_tx].len = skb_frag_size(frag);
<<<<<<< HEAD
=======
		tx_q->tx_skbuff[tx_q->cur_tx] = NULL;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
		tx_q->tx_skbuff_dma[tx_q->cur_tx].map_as_page = true;
	}

	tx_q->tx_skbuff_dma[tx_q->cur_tx].last_segment = true;

	/* Only the last descriptor gets to point to the skb. */
	tx_q->tx_skbuff[tx_q->cur_tx] = skb;

	/* We've used all descriptors we need for this skb, however,
	 * advance cur_tx so that it references a fresh descriptor.
	 * ndo_start_xmit will fill this descriptor the next time it's
	 * called and stmmac_tx_clean may clean up to this descriptor.
	 */
	tx_q->cur_tx = STMMAC_GET_ENTRY(tx_q->cur_tx, DMA_TX_SIZE);

	if (unlikely(stmmac_tx_avail(priv, queue) <= (MAX_SKB_FRAGS + 1))) {
		netif_dbg(priv, hw, priv->dev, "%s: stop transmitted packets\n",
			  __func__);
		netif_tx_stop_queue(netdev_get_tx_queue(priv->dev, queue));
	}

	dev->stats.tx_bytes += skb->len;
	priv->xstats.tx_tso_frames++;
	priv->xstats.tx_tso_nfrags += nfrags;

	/* Manage tx mitigation */
<<<<<<< HEAD
	tx_q->tx_count_frames += nfrags + 1;
	if (likely(priv->tx_coal_frames > tx_q->tx_count_frames) &&
	    !(priv->synopsys_id >= DWMAC_CORE_4_00 &&
	    (skb_shinfo(skb)->tx_flags & SKBTX_HW_TSTAMP) &&
	    priv->hwts_tx_en)) {
		stmmac_tx_timer_arm(priv, queue);
	} else {
		tx_q->tx_count_frames = 0;
		stmmac_set_tx_ic(priv, desc);
		priv->xstats.tx_set_ic_bit++;
=======
	priv->tx_count_frames += nfrags + 1;

	if (likely(priv->tx_coal_timer_disable)) {
		priv->tx_count_frames = 0;
		priv->hw->desc->set_tx_ic(desc);
		priv->xstats.tx_set_ic_bit++;
	} else {
		if (likely(priv->tx_coal_frames > priv->tx_count_frames)) {
			mod_timer(
				&priv->txtimer,
				STMMAC_COAL_TIMER(priv->tx_coal_timer));
		} else {
			priv->tx_count_frames = 0;
			priv->hw->desc->set_tx_ic(desc);
			priv->xstats.tx_set_ic_bit++;
		}
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	}

	skb_tx_timestamp(skb);

	if (unlikely((skb_shinfo(skb)->tx_flags & SKBTX_HW_TSTAMP) &&
		     priv->hwts_tx_en)) {
		/* declare that device is doing timestamping */
		skb_shinfo(skb)->tx_flags |= SKBTX_IN_PROGRESS;
<<<<<<< HEAD
		stmmac_enable_tx_timestamp(priv, first);
	}

	/* Complete the first descriptor before granting the DMA */
	stmmac_prepare_tso_tx_desc(priv, first, 1,
=======
		priv->hw->desc->enable_tx_timestamp(first);
	}

	/* Complete the first descriptor before granting the DMA */
	priv->hw->desc->prepare_tso_tx_desc(first, 1,
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
			proto_hdr_len,
			pay_len,
			1, tx_q->tx_skbuff_dma[first_entry].last_segment,
			tcp_hdrlen(skb) / 4, (skb->len - proto_hdr_len));

	/* If context desc is used to change MSS */
	if (mss_desc) {
		/* Make sure that first descriptor has been completely
		 * written, including its own bit. This is because MSS is
		 * actually before first descriptor, so we need to make
		 * sure that MSS's own bit is the last thing written.
		 */
		dma_wmb();
<<<<<<< HEAD
		stmmac_set_tx_owner(priv, mss_desc);
=======
		priv->hw->desc->set_tx_owner(mss_desc);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	}

	/* The own bit must be the latest setting done when prepare the
	 * descriptor and then barrier is needed to make sure that
	 * all is coherent before granting the DMA engine.
	 */
<<<<<<< HEAD
	wmb();
=======
	dma_wmb();
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	if (netif_msg_pktdata(priv)) {
		pr_info("%s: curr=%d dirty=%d f=%d, e=%d, f_p=%p, nfrags %d\n",
			__func__, tx_q->cur_tx, tx_q->dirty_tx, first_entry,
			tx_q->cur_tx, first, nfrags);

<<<<<<< HEAD
		stmmac_display_ring(priv, (void *)tx_q->dma_tx, DMA_TX_SIZE, 0);
=======
		priv->hw->desc->display_ring((void *)tx_q->dma_tx, DMA_TX_SIZE,
					     0);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

		pr_info(">>> frame to be transmitted: ");
		print_pkt(skb->data, skb_headlen(skb));
	}

<<<<<<< HEAD
	netdev_tx_sent_queue(netdev_get_tx_queue(dev, queue), skb->len);

	tx_q->tx_tail_addr = tx_q->dma_tx_phy + (tx_q->cur_tx * sizeof(*desc));
	stmmac_set_tx_tail_ptr(priv, priv->ioaddr, tx_q->tx_tail_addr, queue);
=======
	if (!priv->tx_coal_timer_disable)
		netdev_tx_sent_queue(netdev_get_tx_queue(dev, queue), skb->len);

	tx_q->tx_tail_addr = tx_q->dma_tx_phy + (tx_q->cur_tx * sizeof(*desc));
	priv->hw->dma->set_tx_tail_ptr(priv->ioaddr, tx_q->tx_tail_addr,
				       queue);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	return NETDEV_TX_OK;

dma_map_err:
	dev_err(priv->device, "Tx dma map failed\n");
	dev_kfree_skb(skb);
	priv->dev->stats.tx_dropped++;
	return NETDEV_TX_OK;
}

/**
 *  stmmac_xmit - Tx entry point of the driver
 *  @skb : the socket buffer
 *  @dev : device pointer
 *  Description : this is the tx entry point of the driver.
 *  It programs the chain or the ring and supports oversized frames
 *  and SG feature.
 */
static netdev_tx_t stmmac_xmit(struct sk_buff *skb, struct net_device *dev)
{
	struct stmmac_priv *priv = netdev_priv(dev);
	unsigned int nopaged_len = skb_headlen(skb);
	int i, csum_insertion = 0, is_jumbo = 0;
	u32 queue = skb_get_queue_mapping(skb);
	int nfrags = skb_shinfo(skb)->nr_frags;
	int entry;
	unsigned int first_entry;
	struct dma_desc *desc, *first;
	struct stmmac_tx_queue *tx_q;
	unsigned int enh_desc;
<<<<<<< HEAD
	unsigned int des;
=======
	unsigned int des, int_mod;
	unsigned int eth_type;

	GET_ETH_TYPE(skb->data, eth_type);

	if (eth_type == ETH_P_IP || eth_type == ETH_P_IPV6)
		skb_orphan(skb);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	tx_q = &priv->tx_queue[queue];

	if (priv->tx_path_in_lpi_mode)
		stmmac_disable_eee_mode(priv);

	/* Manage oversized TCP frames for GMAC4 device */
	if (skb_is_gso(skb) && priv->tso) {
<<<<<<< HEAD
		if (skb_shinfo(skb)->gso_type & (SKB_GSO_TCPV4 | SKB_GSO_TCPV6))
			return stmmac_tso_xmit(skb, dev);
=======
		if (skb_shinfo(skb)->gso_type & (SKB_GSO_TCPV4 | SKB_GSO_TCPV6)) {
			/*
			 * There is no way to determine the number of TSO
			 * capable Queues. Let's use always the Queue 0
			 * because if TSO is supported then at least this
			 * one will be capable.
			 */
			if (!priv->tx_queue[0].skip_sw)
				skb_set_queue_mapping(skb, 0);
			else
				skb_set_queue_mapping
				(skb, ALL_OTHER_TRAFFIC_TX_CHANNEL);

			return stmmac_tso_xmit(skb, dev);
		}
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	}

	if (unlikely(stmmac_tx_avail(priv, queue) < nfrags + 1)) {
		if (!netif_tx_queue_stopped(netdev_get_tx_queue(dev, queue))) {
			netif_tx_stop_queue(netdev_get_tx_queue(priv->dev,
								queue));
			/* This is a hard error, log it. */
			netdev_err(priv->dev,
				   "%s: Tx Ring full when queue awake\n",
				   __func__);
		}
		return NETDEV_TX_BUSY;
	}

	entry = tx_q->cur_tx;
	first_entry = entry;
<<<<<<< HEAD
	WARN_ON(tx_q->tx_skbuff[first_entry]);
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	csum_insertion = (skb->ip_summed == CHECKSUM_PARTIAL);

	if (likely(priv->extend_desc))
		desc = (struct dma_desc *)(tx_q->dma_etx + entry);
	else
		desc = tx_q->dma_tx + entry;

	first = desc;

	enh_desc = priv->plat->enh_desc;
	/* To program the descriptors according to the size of the frame */
	if (enh_desc)
<<<<<<< HEAD
		is_jumbo = stmmac_is_jumbo_frm(priv, skb->len, enh_desc);

	if (unlikely(is_jumbo)) {
		entry = stmmac_jumbo_frm(priv, tx_q, skb, csum_insertion);
		if (unlikely(entry < 0) && (entry != -EINVAL))
=======
		is_jumbo = priv->hw->mode->is_jumbo_frm(skb->len, enh_desc);

	if (unlikely(is_jumbo) && likely(priv->synopsys_id <
					 DWMAC_CORE_4_00)) {
		entry = priv->hw->mode->jumbo_frm(tx_q, skb, csum_insertion);
		if (unlikely(entry < 0))
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
			goto dma_map_err;
	}

	for (i = 0; i < nfrags; i++) {
		const skb_frag_t *frag = &skb_shinfo(skb)->frags[i];
		int len = skb_frag_size(frag);
		bool last_segment = (i == (nfrags - 1));

		entry = STMMAC_GET_ENTRY(entry, DMA_TX_SIZE);
<<<<<<< HEAD
		WARN_ON(tx_q->tx_skbuff[entry]);
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

		if (likely(priv->extend_desc))
			desc = (struct dma_desc *)(tx_q->dma_etx + entry);
		else
			desc = tx_q->dma_tx + entry;

<<<<<<< HEAD
		des = skb_frag_dma_map(priv->device, frag, 0, len,
				       DMA_TO_DEVICE);
		if (dma_mapping_error(priv->device, des))
			goto dma_map_err; /* should reuse desc w/o issues */

		tx_q->tx_skbuff_dma[entry].buf = des;

		stmmac_set_desc_addr(priv, desc, des);
=======
		des = skb_frag_dma_map(GET_MEM_PDEV_DEV, frag, 0, len,
				       DMA_TO_DEVICE);
		if (dma_mapping_error(GET_MEM_PDEV_DEV, des))
			goto dma_map_err; /* should reuse desc w/o issues */

		tx_q->tx_skbuff[entry] = NULL;

		tx_q->tx_skbuff_dma[entry].buf = des;
		if (unlikely(priv->synopsys_id >= DWMAC_CORE_4_00))
			desc->des0 = cpu_to_le32(des);
		else
			desc->des2 = cpu_to_le32(des);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

		tx_q->tx_skbuff_dma[entry].map_as_page = true;
		tx_q->tx_skbuff_dma[entry].len = len;
		tx_q->tx_skbuff_dma[entry].last_segment = last_segment;

		/* Prepare the descriptor and set the own bit too */
<<<<<<< HEAD
		stmmac_prepare_tx_desc(priv, desc, 0, len, csum_insertion,
				priv->mode, 1, last_segment, skb->len);
=======
		priv->hw->desc->prepare_tx_desc(desc, 0, len, csum_insertion,
						priv->mode, 1, last_segment,
						skb->len);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	}

	/* Only the last descriptor gets to point to the skb. */
	tx_q->tx_skbuff[entry] = skb;

	/* We've used all descriptors we need for this skb, however,
	 * advance cur_tx so that it references a fresh descriptor.
	 * ndo_start_xmit will fill this descriptor the next time it's
	 * called and stmmac_tx_clean may clean up to this descriptor.
	 */
	entry = STMMAC_GET_ENTRY(entry, DMA_TX_SIZE);
	tx_q->cur_tx = entry;

	if (netif_msg_pktdata(priv)) {
		void *tx_head;

		netdev_dbg(priv->dev,
			   "%s: curr=%d dirty=%d f=%d, e=%d, first=%p, nfrags=%d",
			   __func__, tx_q->cur_tx, tx_q->dirty_tx, first_entry,
			   entry, first, nfrags);

		if (priv->extend_desc)
			tx_head = (void *)tx_q->dma_etx;
		else
			tx_head = (void *)tx_q->dma_tx;

<<<<<<< HEAD
		stmmac_display_ring(priv, tx_head, DMA_TX_SIZE, false);
=======
		priv->hw->desc->display_ring(tx_head, DMA_TX_SIZE, false);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

		netdev_dbg(priv->dev, ">>> frame to be transmitted: ");
		print_pkt(skb->data, skb->len);
	}

	if (unlikely(stmmac_tx_avail(priv, queue) <= (MAX_SKB_FRAGS + 1))) {
		netif_dbg(priv, hw, priv->dev, "%s: stop transmitted packets\n",
			  __func__);
		netif_tx_stop_queue(netdev_get_tx_queue(priv->dev, queue));
	}

	dev->stats.tx_bytes += skb->len;

<<<<<<< HEAD
=======
	priv->tx_count_frames += nfrags + 1;

>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	/* According to the coalesce parameter the IC bit for the latest
	 * segment is reset and the timer re-started to clean the tx status.
	 * This approach takes care about the fragments: desc is the first
	 * element in case of no SG.
	 */
<<<<<<< HEAD
	tx_q->tx_count_frames += nfrags + 1;
	if (likely(priv->tx_coal_frames > tx_q->tx_count_frames) &&
	    !(priv->synopsys_id >= DWMAC_CORE_4_00 &&
	    (skb_shinfo(skb)->tx_flags & SKBTX_HW_TSTAMP) &&
	    priv->hwts_tx_en)) {
		stmmac_tx_timer_arm(priv, queue);
	} else {
		tx_q->tx_count_frames = 0;
		stmmac_set_tx_ic(priv, desc);
		priv->xstats.tx_set_ic_bit++;
	}

	skb_tx_timestamp(skb);
=======
	if (likely(priv->tx_coal_timer_disable)) {
		if (priv->plat->get_plat_tx_coal_frames) {
			int_mod = priv->plat->get_plat_tx_coal_frames(skb);

			if (!(tx_q->cur_tx % int_mod)) {
				priv->tx_count_frames = 0;
				priv->hw->desc->set_tx_ic(desc);
				priv->xstats.tx_set_ic_bit++;
			}
		}
	} else {
		if (likely(priv->tx_coal_frames > priv->tx_count_frames)) {
			mod_timer(
				&priv->txtimer,
				STMMAC_COAL_TIMER(priv->tx_coal_timer));
		} else {
			priv->tx_count_frames = 0;
			priv->hw->desc->set_tx_ic(desc);
			priv->xstats.tx_set_ic_bit++;
		}
	}

	if (!priv->hwts_tx_en)
		skb_tx_timestamp(skb);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	/* Ready to fill the first descriptor and set the OWN bit w/o any
	 * problems because all the descriptors are actually ready to be
	 * passed to the DMA engine.
	 */
	if (likely(!is_jumbo)) {
		bool last_segment = (nfrags == 0);

<<<<<<< HEAD
		des = dma_map_single(priv->device, skb->data,
				     nopaged_len, DMA_TO_DEVICE);
		if (dma_mapping_error(priv->device, des))
			goto dma_map_err;

		tx_q->tx_skbuff_dma[first_entry].buf = des;

		stmmac_set_desc_addr(priv, first, des);
=======
		des = dma_map_single(GET_MEM_PDEV_DEV, skb->data,
				     nopaged_len, DMA_TO_DEVICE);
		if (dma_mapping_error(GET_MEM_PDEV_DEV, des))
			goto dma_map_err;

		tx_q->tx_skbuff_dma[first_entry].buf = des;
		if (unlikely(priv->synopsys_id >= DWMAC_CORE_4_00))
			first->des0 = cpu_to_le32(des);
		else
			first->des2 = cpu_to_le32(des);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

		tx_q->tx_skbuff_dma[first_entry].len = nopaged_len;
		tx_q->tx_skbuff_dma[first_entry].last_segment = last_segment;

		if (unlikely((skb_shinfo(skb)->tx_flags & SKBTX_HW_TSTAMP) &&
			     priv->hwts_tx_en)) {
			/* declare that device is doing timestamping */
			skb_shinfo(skb)->tx_flags |= SKBTX_IN_PROGRESS;
<<<<<<< HEAD
			stmmac_enable_tx_timestamp(priv, first);
		}

		/* Prepare the first descriptor setting the OWN bit too */
		stmmac_prepare_tx_desc(priv, first, 1, nopaged_len,
				csum_insertion, priv->mode, 1, last_segment,
				skb->len);
	} else {
		stmmac_set_tx_owner(priv, first);
	}

	/* The own bit must be the latest setting done when prepare the
	 * descriptor and then barrier is needed to make sure that
	 * all is coherent before granting the DMA engine.
	 */
	wmb();

	netdev_tx_sent_queue(netdev_get_tx_queue(dev, queue), skb->len);

	stmmac_enable_dma_transmission(priv, priv->ioaddr);

	tx_q->tx_tail_addr = tx_q->dma_tx_phy + (tx_q->cur_tx * sizeof(*desc));
	stmmac_set_tx_tail_ptr(priv, priv->ioaddr, tx_q->tx_tail_addr, queue);
=======
			priv->hw->desc->enable_tx_timestamp(first);
		}

		/* Prepare the first descriptor setting the OWN bit too */
		priv->hw->desc->prepare_tx_desc(first, 1, nopaged_len,
						csum_insertion, priv->mode, 1,
						last_segment, skb->len);

		/* The own bit must be the latest setting done when prepare the
		 * descriptor and then barrier is needed to make sure that
		 * all is coherent before granting the DMA engine.
		 */
		dma_wmb();
	}

	if (!priv->tx_coal_timer_disable)
		netdev_tx_sent_queue(netdev_get_tx_queue(dev, queue), skb->len);
	if (priv->synopsys_id < DWMAC_CORE_4_00)
		priv->hw->dma->enable_dma_transmission(priv->ioaddr);
	else {
		tx_q->tx_tail_addr = tx_q->dma_tx_phy + (tx_q->cur_tx * sizeof(*desc));
		priv->hw->dma->set_tx_tail_ptr(priv->ioaddr, tx_q->tx_tail_addr,
					       queue);
	}
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	return NETDEV_TX_OK;

dma_map_err:
	netdev_err(priv->dev, "Tx DMA map failed\n");
	dev_kfree_skb(skb);
	priv->dev->stats.tx_dropped++;
	return NETDEV_TX_OK;
}

static void stmmac_rx_vlan(struct net_device *dev, struct sk_buff *skb)
{
<<<<<<< HEAD
	struct vlan_ethhdr *veth;
	__be16 vlan_proto;
	u16 vlanid;

	veth = (struct vlan_ethhdr *)skb->data;
	vlan_proto = veth->h_vlan_proto;

	if ((vlan_proto == htons(ETH_P_8021Q) &&
	     dev->features & NETIF_F_HW_VLAN_CTAG_RX) ||
	    (vlan_proto == htons(ETH_P_8021AD) &&
	     dev->features & NETIF_F_HW_VLAN_STAG_RX)) {
		/* pop the vlan tag */
		vlanid = ntohs(veth->h_vlan_TCI);
		memmove(skb->data + VLAN_HLEN, veth, ETH_ALEN * 2);
		skb_pull(skb, VLAN_HLEN);
		__vlan_hwaccel_put_tag(skb, vlan_proto, vlanid);
=======
	struct ethhdr *ehdr;
	u16 vlanid;

	if ((dev->features & NETIF_F_HW_VLAN_CTAG_RX) ==
	    NETIF_F_HW_VLAN_CTAG_RX &&
	    !__vlan_get_tag(skb, &vlanid)) {
		/* pop the vlan tag */
		ehdr = (struct ethhdr *)skb->data;
		memmove(skb->data + VLAN_HLEN, ehdr, ETH_ALEN * 2);
		skb_pull(skb, VLAN_HLEN);
		__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q), vlanid);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	}
}


static inline int stmmac_rx_threshold_count(struct stmmac_rx_queue *rx_q)
{
	if (rx_q->rx_zeroc_thresh < STMMAC_RX_THRESH)
		return 0;

	return 1;
}

/**
 * stmmac_rx_refill - refill used skb preallocated buffers
 * @priv: driver private structure
 * @queue: RX queue index
 * Description : this is to reallocate the skb for the reception process
 * that is based on zero-copy.
 */
static inline void stmmac_rx_refill(struct stmmac_priv *priv, u32 queue)
{
	struct stmmac_rx_queue *rx_q = &priv->rx_queue[queue];
	int dirty = stmmac_rx_dirty(priv, queue);
	unsigned int entry = rx_q->dirty_rx;

	int bfsize = priv->dma_buf_sz;

	while (dirty-- > 0) {
		struct dma_desc *p;

		if (priv->extend_desc)
			p = (struct dma_desc *)(rx_q->dma_erx + entry);
		else
			p = rx_q->dma_rx + entry;

		if (likely(!rx_q->rx_skbuff[entry])) {
			struct sk_buff *skb;

			skb = netdev_alloc_skb_ip_align(priv->dev, bfsize);
			if (unlikely(!skb)) {
				/* so for a while no zero-copy! */
				rx_q->rx_zeroc_thresh = STMMAC_RX_THRESH;
				if (unlikely(net_ratelimit()))
					dev_err(priv->device,
						"fail to alloc skb entry %d\n",
						entry);
				break;
			}

			rx_q->rx_skbuff[entry] = skb;
			rx_q->rx_skbuff_dma[entry] =
<<<<<<< HEAD
			    dma_map_single(priv->device, skb->data, bfsize,
					   DMA_FROM_DEVICE);
			if (dma_mapping_error(priv->device,
=======
			    dma_map_single(GET_MEM_PDEV_DEV, skb->data, bfsize,
					   DMA_FROM_DEVICE);
			if (dma_mapping_error(GET_MEM_PDEV_DEV,
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
					      rx_q->rx_skbuff_dma[entry])) {
				netdev_err(priv->dev, "Rx DMA map failed\n");
				dev_kfree_skb(skb);
				break;
			}

<<<<<<< HEAD
			stmmac_set_desc_addr(priv, p, rx_q->rx_skbuff_dma[entry]);
			stmmac_refill_desc3(priv, rx_q, p);
=======
			if (unlikely(priv->synopsys_id >= DWMAC_CORE_4_00)) {
				p->des0 = cpu_to_le32(rx_q->rx_skbuff_dma[entry]);
				p->des1 = 0;
			} else {
				p->des2 = cpu_to_le32(rx_q->rx_skbuff_dma[entry]);
			}
			if (priv->hw->mode->refill_desc3)
				priv->hw->mode->refill_desc3(rx_q, p);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

			if (rx_q->rx_zeroc_thresh > 0)
				rx_q->rx_zeroc_thresh--;

			netif_dbg(priv, rx_status, priv->dev,
				  "refill entry #%d\n", entry);
		}
		dma_wmb();

<<<<<<< HEAD
		stmmac_set_rx_owner(priv, p, priv->use_riwt);
=======
		if (unlikely(priv->synopsys_id >= DWMAC_CORE_4_00))
			priv->hw->desc->init_rx_desc(p, priv->use_riwt, 0, 0, priv->dma_buf_sz);
		else
			priv->hw->desc->set_rx_owner(p);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

		dma_wmb();

		entry = STMMAC_GET_ENTRY(entry, DMA_RX_SIZE);
	}
	rx_q->dirty_rx = entry;
<<<<<<< HEAD
	stmmac_set_rx_tail_ptr(priv, priv->ioaddr, rx_q->rx_tail_addr, queue);
=======
}

static u16 csum(u16 old_csum)
{
	u16 new_checksum = 0;

	new_checksum = ~(~old_csum + (-8) + 0);
	return new_checksum;
}

void swap_ip_port(struct sk_buff *skb, unsigned int eth_type)
{
	__be32 temp_addr;
	unsigned char *buf = skb->data;
	struct icmphdr *icmp_hdr;
	unsigned char eth_temp[ETH_ALEN] = {};
	struct ethhdr *eth = (struct ethhdr *)(buf);
	struct iphdr *ip_header;

	if (eth_type == ETH_P_IP) {
		ip_header = (struct iphdr *)(buf + sizeof(struct ethhdr));
		if (ip_header->protocol == IPPROTO_UDP ||
		    ip_header->protocol ==  IPPROTO_ICMP) {
			//swap mac address
			memcpy(eth_temp, eth->h_dest, ETH_ALEN);
			memcpy(eth->h_dest, eth->h_source, ETH_ALEN);
			memcpy(eth->h_source, eth_temp, ETH_ALEN);
			//swap ip address
			temp_addr = ip_header->daddr;
			ip_header->daddr = ip_header->saddr;
			ip_header->saddr = temp_addr;

			icmp_hdr = (struct icmphdr *)(buf
					+ sizeof(struct ethhdr)
					+ sizeof(struct iphdr));
			if (icmp_hdr->type == ICMP_ECHO) {
				icmp_hdr->type = ICMP_ECHOREPLY;
				icmp_hdr->checksum = csum(icmp_hdr->checksum);
			}
		}
	}
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
}

/**
 * stmmac_rx - manage the receive process
 * @priv: driver private structure
 * @limit: napi bugget
 * @queue: RX queue index.
 * Description :  this the function called by the napi poll method.
 * It gets all the frames inside the ring.
 */
static int stmmac_rx(struct stmmac_priv *priv, int limit, u32 queue)
{
	struct stmmac_rx_queue *rx_q = &priv->rx_queue[queue];
<<<<<<< HEAD
	struct stmmac_channel *ch = &priv->channel[queue];
	unsigned int next_entry = rx_q->cur_rx;
	int coe = priv->hw->rx_csum;
	unsigned int count = 0;
	bool xmac;

	xmac = priv->plat->has_gmac4 || priv->plat->has_xgmac;
=======
	int coe = priv->hw->rx_csum;
	unsigned int next_entry = rx_q->cur_rx;
	unsigned int count = 0;
#ifndef CONFIG_ETH_IPA_OFFLOAD
	unsigned int eth_type;
#endif
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	if (netif_msg_rx_status(priv)) {
		void *rx_head;

		netdev_dbg(priv->dev, "%s: descriptor ring:\n", __func__);
		if (priv->extend_desc)
			rx_head = (void *)rx_q->dma_erx;
		else
			rx_head = (void *)rx_q->dma_rx;

<<<<<<< HEAD
		stmmac_display_ring(priv, rx_head, DMA_RX_SIZE, true);
=======
		priv->hw->desc->display_ring(rx_head, DMA_RX_SIZE, true);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	}
	while (count < limit) {
		int entry, status;
		struct dma_desc *p;
		struct dma_desc *np;

		entry = next_entry;

		if (priv->extend_desc)
			p = (struct dma_desc *)(rx_q->dma_erx + entry);
		else
			p = rx_q->dma_rx + entry;

		/* read the status of the incoming frame */
<<<<<<< HEAD
		status = stmmac_rx_status(priv, &priv->dev->stats,
				&priv->xstats, p);
=======
		status = priv->hw->desc->rx_status(&priv->dev->stats,
						   &priv->xstats, p);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
		/* check if managed by the DMA otherwise go ahead */
		if (unlikely(status & dma_own))
			break;

		count++;

		rx_q->cur_rx = STMMAC_GET_ENTRY(rx_q->cur_rx, DMA_RX_SIZE);
		next_entry = rx_q->cur_rx;

		if (priv->extend_desc)
			np = (struct dma_desc *)(rx_q->dma_erx + next_entry);
		else
			np = rx_q->dma_rx + next_entry;

		prefetch(np);

<<<<<<< HEAD
		if (priv->extend_desc)
			stmmac_rx_extended_status(priv, &priv->dev->stats,
					&priv->xstats, rx_q->dma_erx + entry);
		if (unlikely(status == discard_frame)) {
			priv->dev->stats.rx_errors++;
=======
		if ((priv->extend_desc) && (priv->hw->desc->rx_extended_status))
			priv->hw->desc->rx_extended_status(&priv->dev->stats,
							   &priv->xstats,
							   rx_q->dma_erx +
							   entry);
		if (unlikely(status & discard_frame)) {
			if (!(status & ctxt_desc))
				priv->dev->stats.rx_errors++;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
			if (priv->hwts_rx_en && !priv->extend_desc) {
				/* DESC2 & DESC3 will be overwritten by device
				 * with timestamp value, hence reinitialize
				 * them in stmmac_rx_refill() function so that
				 * device can reuse it.
				 */
				dev_kfree_skb_any(rx_q->rx_skbuff[entry]);
				rx_q->rx_skbuff[entry] = NULL;
<<<<<<< HEAD
				dma_unmap_single(priv->device,
=======
				dma_unmap_single(GET_MEM_PDEV_DEV,
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
						 rx_q->rx_skbuff_dma[entry],
						 priv->dma_buf_sz,
						 DMA_FROM_DEVICE);
			}
		} else {
			struct sk_buff *skb;
			int frame_len;
			unsigned int des;

<<<<<<< HEAD
			stmmac_get_desc_addr(priv, p, &des);
			frame_len = stmmac_get_rx_frame_len(priv, p, coe);
=======
			if (unlikely(priv->synopsys_id >= DWMAC_CORE_4_00))
				des = le32_to_cpu(p->des0);
			else
				des = le32_to_cpu(p->des2);

			frame_len = priv->hw->desc->get_rx_frame_len(p, coe);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

			/*  If frame length is greater than skb buffer size
			 *  (preallocated during init) then the packet is
			 *  ignored
			 */
			if (frame_len > priv->dma_buf_sz) {
				if (net_ratelimit())
					netdev_err(priv->dev,
						   "len %d larger than size (%d)\n",
						   frame_len, priv->dma_buf_sz);
				priv->dev->stats.rx_length_errors++;
				continue;
			}

			/* ACS is set; GMAC core strips PAD/FCS for IEEE 802.3
			 * Type frames (LLC/LLC-SNAP)
			 *
			 * llc_snap is never checked in GMAC >= 4, so this ACS
			 * feature is always disabled and packets need to be
			 * stripped manually.
			 */
<<<<<<< HEAD
			if (unlikely(priv->synopsys_id >= DWMAC_CORE_4_00) ||
			    unlikely(status != llc_snap))
=======
			if ((likely(priv->synopsys_id >= DWMAC_CORE_4_00) &&
			     ((unlikely(!priv->hw->crc_strip_en) &&
			       status != llc_snap) ||
			      (unlikely(!priv->hw->acs_strip_en) &&
			       status == llc_snap))) ||
			    (unlikely(priv->synopsys_id < DWMAC_CORE_4_00) &&
			     unlikely(status != llc_snap)))
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
				frame_len -= ETH_FCS_LEN;

			if (netif_msg_rx_status(priv)) {
				netdev_dbg(priv->dev, "\tdesc: %p [entry %d] buff=0x%x\n",
					   p, entry, des);
<<<<<<< HEAD
				netdev_dbg(priv->dev, "frame size %d, COE: %d\n",
					   frame_len, status);
=======
				if (frame_len > ETH_FRAME_LEN)
					netdev_dbg(priv->dev, "frame size %d, COE: %d\n",
						   frame_len, status);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
			}

			/* The zero-copy is always used for all the sizes
			 * in case of GMAC4 because it needs
			 * to refill the used descriptors, always.
			 */
<<<<<<< HEAD
			if (unlikely(!xmac &&
=======
			if (unlikely(!priv->plat->has_gmac4 &&
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
				     ((frame_len < priv->rx_copybreak) ||
				     stmmac_rx_threshold_count(rx_q)))) {
				skb = netdev_alloc_skb_ip_align(priv->dev,
								frame_len);
				if (unlikely(!skb)) {
					if (net_ratelimit())
						dev_warn(priv->device,
							 "packet dropped\n");
					priv->dev->stats.rx_dropped++;
					continue;
				}

<<<<<<< HEAD
				dma_sync_single_for_cpu(priv->device,
=======
				dma_sync_single_for_cpu(GET_MEM_PDEV_DEV,
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
							rx_q->rx_skbuff_dma
							[entry], frame_len,
							DMA_FROM_DEVICE);
				skb_copy_to_linear_data(skb,
							rx_q->
							rx_skbuff[entry]->data,
							frame_len);

				skb_put(skb, frame_len);
<<<<<<< HEAD
				dma_sync_single_for_device(priv->device,
=======
				dma_sync_single_for_device(GET_MEM_PDEV_DEV,
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
							   rx_q->rx_skbuff_dma
							   [entry], frame_len,
							   DMA_FROM_DEVICE);
			} else {
				skb = rx_q->rx_skbuff[entry];
				if (unlikely(!skb)) {
					if (net_ratelimit())
						netdev_err(priv->dev,
							   "%s: Inconsistent Rx chain\n",
							   priv->dev->name);
					priv->dev->stats.rx_dropped++;
					continue;
				}
				prefetch(skb->data - NET_IP_ALIGN);
				rx_q->rx_skbuff[entry] = NULL;
				rx_q->rx_zeroc_thresh++;

				skb_put(skb, frame_len);
<<<<<<< HEAD
				dma_unmap_single(priv->device,
=======
				dma_unmap_single(GET_MEM_PDEV_DEV,
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
						 rx_q->rx_skbuff_dma[entry],
						 priv->dma_buf_sz,
						 DMA_FROM_DEVICE);
			}

			if (netif_msg_pktdata(priv)) {
				netdev_dbg(priv->dev, "frame received (%dbytes)",
					   frame_len);
				print_pkt(skb->data, frame_len);
			}

			stmmac_get_rx_hwtstamp(priv, p, np, skb);

			stmmac_rx_vlan(priv->dev, skb);
<<<<<<< HEAD

=======
#ifndef CONFIG_ETH_IPA_OFFLOAD
			eth_type = dwmac_qcom_get_eth_type(skb->data);

			if (priv->current_loopback > 0 &&
			    eth_type == ETH_P_IP)
				swap_ip_port(skb, eth_type);
#endif
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
			skb->protocol = eth_type_trans(skb, priv->dev);

			if (unlikely(!coe))
				skb_checksum_none_assert(skb);
			else
				skb->ip_summed = CHECKSUM_UNNECESSARY;

<<<<<<< HEAD
			napi_gro_receive(&ch->napi, skb);

			priv->dev->stats.rx_packets++;
=======
			napi_gro_receive(&rx_q->napi, skb);

			priv->dev->stats.rx_packets++;

#ifdef CONFIG_MSM_BOOT_TIME_MARKER
	if (priv->dev->stats.rx_packets == 1)
		place_marker("M - Ethernet first packet received");
#endif
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
			priv->dev->stats.rx_bytes += frame_len;
		}
	}

	stmmac_rx_refill(priv, queue);

	priv->xstats.rx_pkt_n += count;
<<<<<<< HEAD
=======
	priv->xstats.q_rx_pkt_n[queue] += count;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	return count;
}

/**
 *  stmmac_poll - stmmac poll method (NAPI)
 *  @napi : pointer to the napi structure.
 *  @budget : maximum number of packets that the current CPU can receive from
 *	      all interfaces.
 *  Description :
 *  To look at the incoming frames and clear the tx resources.
 */
<<<<<<< HEAD
static int stmmac_napi_poll(struct napi_struct *napi, int budget)
{
	struct stmmac_channel *ch =
		container_of(napi, struct stmmac_channel, napi);
	struct stmmac_priv *priv = ch->priv_data;
	int work_done, rx_done = 0, tx_done = 0;
	u32 chan = ch->index;

	priv->xstats.napi_poll++;

	if (ch->has_tx)
		tx_done = stmmac_tx_clean(priv, budget, chan);
	if (ch->has_rx)
		rx_done = stmmac_rx(priv, budget, chan);

	work_done = max(rx_done, tx_done);
	work_done = min(work_done, budget);

	if (work_done < budget && napi_complete_done(napi, work_done)) {
		int stat;

		stmmac_enable_dma_irq(priv, priv->ioaddr, chan);
		stat = stmmac_dma_interrupt_status(priv, priv->ioaddr,
						   &priv->xstats, chan);
		if (stat && napi_reschedule(napi))
			stmmac_disable_dma_irq(priv, priv->ioaddr, chan);
	}

=======
static int stmmac_poll(struct napi_struct *napi, int budget)
{
	struct stmmac_rx_queue *rx_q =
		container_of(napi, struct stmmac_rx_queue, napi);
	struct stmmac_priv *priv = rx_q->priv_data;
	u32 tx_count = priv->plat->tx_queues_to_use;
	u32 chan = rx_q->queue_index;
	int work_done = 0;
	u32 queue;

	priv->xstats.napi_poll++;

	/* check all the queues */
	for (queue = 0; queue < tx_count; queue++) {
		if (priv->tx_queue[queue].skip_sw)
			continue;
		stmmac_tx_clean(priv, queue);
	}

	work_done = stmmac_rx(priv, budget, rx_q->queue_index);
	if (work_done < budget) {
		napi_complete_done(napi, work_done);
		stmmac_enable_dma_irq(priv, chan);
	}
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	return work_done;
}

/**
 *  stmmac_tx_timeout
 *  @dev : Pointer to net device structure
 *  Description: this function is called when a packet transmission fails to
 *   complete within a reasonable time. The driver will mark the error in the
 *   netdev structure and arrange for the device to be reset to a sane state
 *   in order to transmit a new packet.
 */
static void stmmac_tx_timeout(struct net_device *dev)
{
	struct stmmac_priv *priv = netdev_priv(dev);
<<<<<<< HEAD

	stmmac_global_err(priv);
=======
	u32 tx_count = priv->plat->tx_queues_to_use;
	u32 chan;

	/* Clear Tx resources and restart transmitting again */
	for (chan = 0; chan < tx_count; chan++) {
		if (priv->tx_queue[chan].skip_sw)
			continue;
		stmmac_tx_err(priv, chan);
	}
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
}

/**
 *  stmmac_set_rx_mode - entry point for multicast addressing
 *  @dev : pointer to the device structure
 *  Description:
 *  This function is a driver entry point which gets called by the kernel
 *  whenever multicast addresses must be enabled/disabled.
 *  Return value:
 *  void.
 */
static void stmmac_set_rx_mode(struct net_device *dev)
{
	struct stmmac_priv *priv = netdev_priv(dev);

<<<<<<< HEAD
	stmmac_set_filter(priv, priv->hw, dev);
=======
	priv->hw->mac->set_filter(priv->hw, dev);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
}

/**
 *  stmmac_change_mtu - entry point to change MTU size for the device.
 *  @dev : device pointer.
 *  @new_mtu : the new MTU size for the device.
 *  Description: the Maximum Transfer Unit (MTU) is used by the network layer
 *  to drive packet transmission. Ethernet has an MTU of 1500 octets
 *  (ETH_DATA_LEN). This value can be changed with ifconfig.
 *  Return value:
 *  0 on success and an appropriate (-)ve integer as defined in errno.h
 *  file on failure.
 */
static int stmmac_change_mtu(struct net_device *dev, int new_mtu)
{
	struct stmmac_priv *priv = netdev_priv(dev);
<<<<<<< HEAD
=======
	int txfifosz = priv->plat->tx_fifo_size;

	if (txfifosz == 0)
		txfifosz = priv->dma_cap.tx_fifo_size;

	txfifosz /= priv->plat->tx_queues_to_use;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	if (netif_running(dev)) {
		netdev_err(priv->dev, "must be stopped to change its MTU\n");
		return -EBUSY;
	}

<<<<<<< HEAD
=======
	new_mtu = STMMAC_ALIGN(new_mtu);

	/* If condition true, FIFO is too small or MTU too large */
	if ((txfifosz < new_mtu) || (new_mtu > BUF_SIZE_16KiB))
		return -EINVAL;

>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	dev->mtu = new_mtu;

	netdev_update_features(dev);

	return 0;
}

static netdev_features_t stmmac_fix_features(struct net_device *dev,
					     netdev_features_t features)
{
	struct stmmac_priv *priv = netdev_priv(dev);

	if (priv->plat->rx_coe == STMMAC_RX_COE_NONE)
		features &= ~NETIF_F_RXCSUM;

	if (!priv->plat->tx_coe)
		features &= ~NETIF_F_CSUM_MASK;

	/* Some GMAC devices have a bugged Jumbo frame support that
	 * needs to have the Tx COE disabled for oversized frames
	 * (due to limited buffer sizes). In this case we disable
	 * the TX csum insertion in the TDES and not use SF.
	 */
	if (priv->plat->bugged_jumbo && (dev->mtu > ETH_DATA_LEN))
		features &= ~NETIF_F_CSUM_MASK;

	/* Disable tso if asked by ethtool */
	if ((priv->plat->tso_en) && (priv->dma_cap.tsoen)) {
		if (features & NETIF_F_TSO)
			priv->tso = true;
		else
			priv->tso = false;
	}

	return features;
}

static int stmmac_set_features(struct net_device *netdev,
			       netdev_features_t features)
{
	struct stmmac_priv *priv = netdev_priv(netdev);

	/* Keep the COE Type in case of csum is supporting */
	if (features & NETIF_F_RXCSUM)
		priv->hw->rx_csum = priv->plat->rx_coe;
	else
		priv->hw->rx_csum = 0;
	/* No check needed because rx_coe has been set before and it will be
	 * fixed in case of issue.
	 */
<<<<<<< HEAD
	stmmac_rx_ipc(priv, priv->hw);
=======
	priv->hw->mac->rx_ipc(priv->hw);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	return 0;
}

/**
 *  stmmac_interrupt - main ISR
 *  @irq: interrupt number.
 *  @dev_id: to pass the net device pointer.
 *  Description: this is the main driver interrupt service routine.
 *  It can call:
 *  o DMA service routine (to manage incoming frame reception and transmission
 *    status)
 *  o Core interrupts to manage: remote wake-up, management counter, LPI
 *    interrupts.
 */
static irqreturn_t stmmac_interrupt(int irq, void *dev_id)
{
	struct net_device *dev = (struct net_device *)dev_id;
	struct stmmac_priv *priv = netdev_priv(dev);
	u32 rx_cnt = priv->plat->rx_queues_to_use;
	u32 tx_cnt = priv->plat->tx_queues_to_use;
	u32 queues_count;
	u32 queue;
<<<<<<< HEAD
	bool xmac;

	xmac = priv->plat->has_gmac4 || priv->plat->has_xgmac;
=======
	struct stmmac_rx_queue *rx_q;

>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	queues_count = (rx_cnt > tx_cnt) ? rx_cnt : tx_cnt;

	if (priv->irq_wake)
		pm_wakeup_event(priv->device, 0);

	if (unlikely(!dev)) {
		netdev_err(priv->dev, "%s: invalid dev pointer\n", __func__);
		return IRQ_NONE;
	}

<<<<<<< HEAD
	/* Check if adapter is up */
	if (test_bit(STMMAC_DOWN, &priv->state))
		return IRQ_HANDLED;
	/* Check if a fatal error happened */
	if (stmmac_safety_feat_interrupt(priv))
		return IRQ_HANDLED;

	/* To handle GMAC own interrupts */
	if ((priv->plat->has_gmac) || xmac) {
		int status = stmmac_host_irq_status(priv, priv->hw, &priv->xstats);
		int mtl_status;
=======
	/* To handle GMAC own interrupts */
	if ((priv->plat->has_gmac) || (priv->plat->has_gmac4)) {
		int status = priv->hw->mac->host_irq_status(priv->hw,
							    &priv->xstats);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

		if (unlikely(status)) {
			/* For LPI we need to save the tx status */
			if (status & CORE_IRQ_TX_PATH_IN_LPI_MODE)
				priv->tx_path_in_lpi_mode = true;
			if (status & CORE_IRQ_TX_PATH_EXIT_LPI_MODE)
				priv->tx_path_in_lpi_mode = false;
		}

<<<<<<< HEAD
		for (queue = 0; queue < queues_count; queue++) {
			struct stmmac_rx_queue *rx_q = &priv->rx_queue[queue];

			mtl_status = stmmac_host_mtl_irq_status(priv, priv->hw,
								queue);
			if (mtl_status != -EINVAL)
				status |= mtl_status;

			if (status & CORE_IRQ_MTL_RX_OVERFLOW)
				stmmac_set_rx_tail_ptr(priv, priv->ioaddr,
						       rx_q->rx_tail_addr,
						       queue);
=======
		if (priv->synopsys_id >= DWMAC_CORE_4_00) {
			for (queue = 0; queue < queues_count; queue++) {
				if (priv->rx_queue[queue].skip_sw)
					continue;
				rx_q = &priv->rx_queue[queue];

				status |=
				priv->hw->mac->host_mtl_irq_status(priv->hw,
								   queue);

				if (status & CORE_IRQ_MTL_RX_OVERFLOW &&
				    priv->hw->dma->set_rx_tail_ptr)
					priv->hw->dma->set_rx_tail_ptr(priv->ioaddr,
								rx_q->rx_tail_addr,
								queue);
			}
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
		}

		/* PCS link status */
		if (priv->hw->pcs) {
			if (priv->xstats.pcs_link)
				netif_carrier_on(dev);
			else
				netif_carrier_off(dev);
		}
	}

	/* To handle DMA interrupts */
	stmmac_dma_interrupt(priv);

	return IRQ_HANDLED;
}

#ifdef CONFIG_NET_POLL_CONTROLLER
/* Polling receive - used by NETCONSOLE and other diagnostic tools
 * to allow network I/O with interrupts disabled.
 */
static void stmmac_poll_controller(struct net_device *dev)
{
	disable_irq(dev->irq);
	stmmac_interrupt(dev->irq, dev);
	enable_irq(dev->irq);
}
#endif

/**
 *  stmmac_ioctl - Entry point for the Ioctl
 *  @dev: Device pointer.
 *  @rq: An IOCTL specefic structure, that can contain a pointer to
 *  a proprietary structure used to pass information to the driver.
 *  @cmd: IOCTL command
 *  Description:
 *  Currently it supports the phy_mii_ioctl(...) and HW time stamping.
 */
static int stmmac_ioctl(struct net_device *dev, struct ifreq *rq, int cmd)
{
	int ret = -EOPNOTSUPP;

	if (!netif_running(dev))
		return -EINVAL;

	switch (cmd) {
	case SIOCGMIIPHY:
	case SIOCGMIIREG:
	case SIOCSMIIREG:
		if (!dev->phydev)
			return -EINVAL;
		ret = phy_mii_ioctl(dev->phydev, rq, cmd);
		break;
	case SIOCSHWTSTAMP:
		ret = stmmac_hwtstamp_ioctl(dev, rq);
		break;
<<<<<<< HEAD
=======
	case SIOCDEVPRIVATE:
		ret = ethqos_handle_prv_ioctl(dev, rq, cmd);
		break;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	default:
		break;
	}

	return ret;
}

<<<<<<< HEAD
static int stmmac_setup_tc_block_cb(enum tc_setup_type type, void *type_data,
				    void *cb_priv)
{
	struct stmmac_priv *priv = cb_priv;
	int ret = -EOPNOTSUPP;

	stmmac_disable_all_queues(priv);

	switch (type) {
	case TC_SETUP_CLSU32:
		if (tc_cls_can_offload_and_chain0(priv->dev, type_data))
			ret = stmmac_tc_setup_cls_u32(priv, priv, type_data);
		break;
	default:
		break;
	}

	stmmac_enable_all_queues(priv);
	return ret;
}

static int stmmac_setup_tc_block(struct stmmac_priv *priv,
				 struct tc_block_offload *f)
{
	if (f->binder_type != TCF_BLOCK_BINDER_TYPE_CLSACT_INGRESS)
		return -EOPNOTSUPP;

	switch (f->command) {
	case TC_BLOCK_BIND:
		return tcf_block_cb_register(f->block, stmmac_setup_tc_block_cb,
				priv, priv, f->extack);
	case TC_BLOCK_UNBIND:
		tcf_block_cb_unregister(f->block, stmmac_setup_tc_block_cb, priv);
		return 0;
	default:
		return -EOPNOTSUPP;
	}
}

static int stmmac_setup_tc(struct net_device *ndev, enum tc_setup_type type,
			   void *type_data)
{
	struct stmmac_priv *priv = netdev_priv(ndev);

	switch (type) {
	case TC_SETUP_BLOCK:
		return stmmac_setup_tc_block(priv, type_data);
	case TC_SETUP_QDISC_CBS:
		return stmmac_tc_setup_cbs(priv, priv, type_data);
	default:
		return -EOPNOTSUPP;
	}
}

static u16 stmmac_select_queue(struct net_device *dev, struct sk_buff *skb,
			       struct net_device *sb_dev,
			       select_queue_fallback_t fallback)
{
	if (skb_shinfo(skb)->gso_type & (SKB_GSO_TCPV4 | SKB_GSO_TCPV6)) {
		/*
		 * There is no way to determine the number of TSO
		 * capable Queues. Let's use always the Queue 0
		 * because if TSO is supported then at least this
		 * one will be capable.
		 */
		return 0;
	}

	return fallback(dev, skb, NULL) % dev->real_num_tx_queues;
}

=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
static int stmmac_set_mac_address(struct net_device *ndev, void *addr)
{
	struct stmmac_priv *priv = netdev_priv(ndev);
	int ret = 0;

	ret = eth_mac_addr(ndev, addr);
	if (ret)
		return ret;

<<<<<<< HEAD
	stmmac_set_umac_addr(priv, priv->hw, ndev->dev_addr, 0);
=======
	priv->hw->mac->set_umac_addr(priv->hw, ndev->dev_addr, 0);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	return ret;
}

<<<<<<< HEAD
=======
static u16 stmmac_tx_select_queue(
		struct net_device *dev,
		struct sk_buff *skb,
		void *accel_priv,
		select_queue_fallback_t fallback)
{
	struct stmmac_priv *priv = netdev_priv(dev);

	if (likely(priv->plat->tx_select_queue))
		return priv->plat->tx_select_queue(
			dev, skb, accel_priv, fallback);

	return fallback(dev, skb);
}

>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
#ifdef CONFIG_DEBUG_FS
static struct dentry *stmmac_fs_dir;

static void sysfs_display_ring(void *head, int size, int extend_desc,
			       struct seq_file *seq)
{
	int i;
	struct dma_extended_desc *ep = (struct dma_extended_desc *)head;
	struct dma_desc *p = (struct dma_desc *)head;

	for (i = 0; i < size; i++) {
		if (extend_desc) {
			seq_printf(seq, "%d [0x%x]: 0x%x 0x%x 0x%x 0x%x\n",
				   i, (unsigned int)virt_to_phys(ep),
				   le32_to_cpu(ep->basic.des0),
				   le32_to_cpu(ep->basic.des1),
				   le32_to_cpu(ep->basic.des2),
				   le32_to_cpu(ep->basic.des3));
			ep++;
		} else {
			seq_printf(seq, "%d [0x%x]: 0x%x 0x%x 0x%x 0x%x\n",
				   i, (unsigned int)virt_to_phys(p),
				   le32_to_cpu(p->des0), le32_to_cpu(p->des1),
				   le32_to_cpu(p->des2), le32_to_cpu(p->des3));
			p++;
		}
		seq_printf(seq, "\n");
	}
}

static int stmmac_sysfs_ring_read(struct seq_file *seq, void *v)
{
	struct net_device *dev = seq->private;
	struct stmmac_priv *priv = netdev_priv(dev);
	u32 rx_count = priv->plat->rx_queues_to_use;
	u32 tx_count = priv->plat->tx_queues_to_use;
	u32 queue;

	if ((dev->flags & IFF_UP) == 0)
		return 0;

	for (queue = 0; queue < rx_count; queue++) {
		struct stmmac_rx_queue *rx_q = &priv->rx_queue[queue];

		seq_printf(seq, "RX Queue %d:\n", queue);

		if (priv->extend_desc) {
			seq_printf(seq, "Extended descriptor ring:\n");
			sysfs_display_ring((void *)rx_q->dma_erx,
					   DMA_RX_SIZE, 1, seq);
		} else {
			seq_printf(seq, "Descriptor ring:\n");
			sysfs_display_ring((void *)rx_q->dma_rx,
					   DMA_RX_SIZE, 0, seq);
		}
	}

	for (queue = 0; queue < tx_count; queue++) {
		struct stmmac_tx_queue *tx_q = &priv->tx_queue[queue];

		seq_printf(seq, "TX Queue %d:\n", queue);

		if (priv->extend_desc) {
			seq_printf(seq, "Extended descriptor ring:\n");
			sysfs_display_ring((void *)tx_q->dma_etx,
					   DMA_TX_SIZE, 1, seq);
		} else {
			seq_printf(seq, "Descriptor ring:\n");
			sysfs_display_ring((void *)tx_q->dma_tx,
					   DMA_TX_SIZE, 0, seq);
		}
	}

	return 0;
}

static int stmmac_sysfs_ring_open(struct inode *inode, struct file *file)
{
	return single_open(file, stmmac_sysfs_ring_read, inode->i_private);
}

/* Debugfs files, should appear in /sys/kernel/debug/stmmaceth/eth0 */

static const struct file_operations stmmac_rings_status_fops = {
	.owner = THIS_MODULE,
	.open = stmmac_sysfs_ring_open,
	.read = seq_read,
	.llseek = seq_lseek,
	.release = single_release,
};

static int stmmac_sysfs_dma_cap_read(struct seq_file *seq, void *v)
{
	struct net_device *dev = seq->private;
	struct stmmac_priv *priv = netdev_priv(dev);

	if (!priv->hw_cap_support) {
		seq_printf(seq, "DMA HW features not supported\n");
		return 0;
	}

	seq_printf(seq, "==============================\n");
	seq_printf(seq, "\tDMA HW features\n");
	seq_printf(seq, "==============================\n");

	seq_printf(seq, "\t10/100 Mbps: %s\n",
		   (priv->dma_cap.mbps_10_100) ? "Y" : "N");
	seq_printf(seq, "\t1000 Mbps: %s\n",
		   (priv->dma_cap.mbps_1000) ? "Y" : "N");
	seq_printf(seq, "\tHalf duplex: %s\n",
		   (priv->dma_cap.half_duplex) ? "Y" : "N");
	seq_printf(seq, "\tHash Filter: %s\n",
		   (priv->dma_cap.hash_filter) ? "Y" : "N");
	seq_printf(seq, "\tMultiple MAC address registers: %s\n",
		   (priv->dma_cap.multi_addr) ? "Y" : "N");
	seq_printf(seq, "\tPCS (TBI/SGMII/RTBI PHY interfaces): %s\n",
		   (priv->dma_cap.pcs) ? "Y" : "N");
	seq_printf(seq, "\tSMA (MDIO) Interface: %s\n",
		   (priv->dma_cap.sma_mdio) ? "Y" : "N");
	seq_printf(seq, "\tPMT Remote wake up: %s\n",
		   (priv->dma_cap.pmt_remote_wake_up) ? "Y" : "N");
	seq_printf(seq, "\tPMT Magic Frame: %s\n",
		   (priv->dma_cap.pmt_magic_frame) ? "Y" : "N");
	seq_printf(seq, "\tRMON module: %s\n",
		   (priv->dma_cap.rmon) ? "Y" : "N");
	seq_printf(seq, "\tIEEE 1588-2002 Time Stamp: %s\n",
		   (priv->dma_cap.time_stamp) ? "Y" : "N");
	seq_printf(seq, "\tIEEE 1588-2008 Advanced Time Stamp: %s\n",
		   (priv->dma_cap.atime_stamp) ? "Y" : "N");
	seq_printf(seq, "\t802.3az - Energy-Efficient Ethernet (EEE): %s\n",
		   (priv->dma_cap.eee) ? "Y" : "N");
	seq_printf(seq, "\tAV features: %s\n", (priv->dma_cap.av) ? "Y" : "N");
	seq_printf(seq, "\tChecksum Offload in TX: %s\n",
		   (priv->dma_cap.tx_coe) ? "Y" : "N");
	if (priv->synopsys_id >= DWMAC_CORE_4_00) {
		seq_printf(seq, "\tIP Checksum Offload in RX: %s\n",
			   (priv->dma_cap.rx_coe) ? "Y" : "N");
	} else {
		seq_printf(seq, "\tIP Checksum Offload (type1) in RX: %s\n",
			   (priv->dma_cap.rx_coe_type1) ? "Y" : "N");
		seq_printf(seq, "\tIP Checksum Offload (type2) in RX: %s\n",
			   (priv->dma_cap.rx_coe_type2) ? "Y" : "N");
	}
	seq_printf(seq, "\tRXFIFO > 2048bytes: %s\n",
		   (priv->dma_cap.rxfifo_over_2048) ? "Y" : "N");
	seq_printf(seq, "\tNumber of Additional RX channel: %d\n",
		   priv->dma_cap.number_rx_channel);
	seq_printf(seq, "\tNumber of Additional TX channel: %d\n",
		   priv->dma_cap.number_tx_channel);
	seq_printf(seq, "\tEnhanced descriptors: %s\n",
		   (priv->dma_cap.enh_desc) ? "Y" : "N");

	return 0;
}

static int stmmac_sysfs_dma_cap_open(struct inode *inode, struct file *file)
{
	return single_open(file, stmmac_sysfs_dma_cap_read, inode->i_private);
}

static const struct file_operations stmmac_dma_cap_fops = {
	.owner = THIS_MODULE,
	.open = stmmac_sysfs_dma_cap_open,
	.read = seq_read,
	.llseek = seq_lseek,
	.release = single_release,
};

static int stmmac_init_fs(struct net_device *dev)
{
	struct stmmac_priv *priv = netdev_priv(dev);

	/* Create per netdev entries */
	priv->dbgfs_dir = debugfs_create_dir(dev->name, stmmac_fs_dir);

	if (!priv->dbgfs_dir || IS_ERR(priv->dbgfs_dir)) {
		netdev_err(priv->dev, "ERROR failed to create debugfs directory\n");

		return -ENOMEM;
	}

	/* Entry to report DMA RX/TX rings */
	priv->dbgfs_rings_status =
<<<<<<< HEAD
		debugfs_create_file("descriptors_status", 0444,
=======
		debugfs_create_file("descriptors_status", S_IRUGO,
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
				    priv->dbgfs_dir, dev,
				    &stmmac_rings_status_fops);

	if (!priv->dbgfs_rings_status || IS_ERR(priv->dbgfs_rings_status)) {
		netdev_err(priv->dev, "ERROR creating stmmac ring debugfs file\n");
		debugfs_remove_recursive(priv->dbgfs_dir);

		return -ENOMEM;
	}

	/* Entry to report the DMA HW features */
<<<<<<< HEAD
	priv->dbgfs_dma_cap = debugfs_create_file("dma_cap", 0444,
						  priv->dbgfs_dir,
						  dev, &stmmac_dma_cap_fops);
=======
	priv->dbgfs_dma_cap = debugfs_create_file("dma_cap", S_IRUGO,
					    priv->dbgfs_dir,
					    dev, &stmmac_dma_cap_fops);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	if (!priv->dbgfs_dma_cap || IS_ERR(priv->dbgfs_dma_cap)) {
		netdev_err(priv->dev, "ERROR creating stmmac MMC debugfs file\n");
		debugfs_remove_recursive(priv->dbgfs_dir);

		return -ENOMEM;
	}

	return 0;
}

static void stmmac_exit_fs(struct net_device *dev)
{
	struct stmmac_priv *priv = netdev_priv(dev);

	debugfs_remove_recursive(priv->dbgfs_dir);
}
#endif /* CONFIG_DEBUG_FS */

static const struct net_device_ops stmmac_netdev_ops = {
	.ndo_open = stmmac_open,
	.ndo_start_xmit = stmmac_xmit,
	.ndo_stop = stmmac_release,
	.ndo_change_mtu = stmmac_change_mtu,
	.ndo_fix_features = stmmac_fix_features,
	.ndo_set_features = stmmac_set_features,
	.ndo_set_rx_mode = stmmac_set_rx_mode,
	.ndo_tx_timeout = stmmac_tx_timeout,
	.ndo_do_ioctl = stmmac_ioctl,
<<<<<<< HEAD
	.ndo_setup_tc = stmmac_setup_tc,
	.ndo_select_queue = stmmac_select_queue,
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
#ifdef CONFIG_NET_POLL_CONTROLLER
	.ndo_poll_controller = stmmac_poll_controller,
#endif
	.ndo_set_mac_address = stmmac_set_mac_address,
<<<<<<< HEAD
};

static void stmmac_reset_subtask(struct stmmac_priv *priv)
{
	if (!test_and_clear_bit(STMMAC_RESET_REQUESTED, &priv->state))
		return;
	if (test_bit(STMMAC_DOWN, &priv->state))
		return;

	netdev_err(priv->dev, "Reset adapter.\n");

	rtnl_lock();
	netif_trans_update(priv->dev);
	while (test_and_set_bit(STMMAC_RESETING, &priv->state))
		usleep_range(1000, 2000);

	set_bit(STMMAC_DOWN, &priv->state);
	dev_close(priv->dev);
	dev_open(priv->dev);
	clear_bit(STMMAC_DOWN, &priv->state);
	clear_bit(STMMAC_RESETING, &priv->state);
	rtnl_unlock();
}

static void stmmac_service_task(struct work_struct *work)
{
	struct stmmac_priv *priv = container_of(work, struct stmmac_priv,
			service_task);

	stmmac_reset_subtask(priv);
	clear_bit(STMMAC_SERVICE_SCHED, &priv->state);
}

=======
	.ndo_select_queue = stmmac_tx_select_queue,
};

>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
/**
 *  stmmac_hw_init - Init the MAC device
 *  @priv: driver private structure
 *  Description: this function is to configure the MAC device according to
 *  some platform parameters or the HW capability register. It prepares the
 *  driver to use either ring or chain modes and to setup either enhanced or
 *  normal descriptors.
 */
static int stmmac_hw_init(struct stmmac_priv *priv)
{
<<<<<<< HEAD
	int ret;
=======
	struct mac_device_info *mac;

	/* Identify the MAC HW device */
	if (priv->plat->setup) {
		mac = priv->plat->setup(priv);
	} else if (priv->plat->has_gmac) {
		priv->dev->priv_flags |= IFF_UNICAST_FLT;
		mac = dwmac1000_setup(priv->ioaddr,
				      priv->plat->multicast_filter_bins,
				      priv->plat->unicast_filter_entries,
				      &priv->synopsys_id);
	} else if (priv->plat->has_gmac4) {
		priv->dev->priv_flags |= IFF_UNICAST_FLT;
		mac = dwmac4_setup(priv->ioaddr,
				   priv->plat->multicast_filter_bins,
				   priv->plat->unicast_filter_entries,
				   &priv->synopsys_id);
	} else {
		mac = dwmac100_setup(priv->ioaddr, &priv->synopsys_id);
	}
	if (!mac)
		return -ENOMEM;

	priv->hw = mac;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	/* dwmac-sun8i only work in chain mode */
	if (priv->plat->has_sun8i)
		chain_mode = 1;
<<<<<<< HEAD
	priv->chain_mode = chain_mode;

	/* Initialize HW Interface */
	ret = stmmac_hwif_init(priv);
	if (ret)
		return ret;
=======

	/* To use the chained or ring mode */
	if (priv->synopsys_id >= DWMAC_CORE_4_00) {
		priv->hw->mode = &dwmac4_ring_mode_ops;
	} else {
		if (chain_mode) {
			priv->hw->mode = &chain_mode_ops;
			dev_info(priv->device, "Chain mode enabled\n");
			priv->mode = STMMAC_CHAIN_MODE;
		} else {
			priv->hw->mode = &ring_mode_ops;
			dev_info(priv->device, "Ring mode enabled\n");
			priv->mode = STMMAC_RING_MODE;
		}
	}
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	/* Get the HW capability (new GMAC newer than 3.50a) */
	priv->hw_cap_support = stmmac_get_hw_features(priv);
	if (priv->hw_cap_support) {
		dev_info(priv->device, "DMA HW capability register supported\n");

		/* We can override some gmac/dma configuration fields: e.g.
		 * enh_desc, tx_coe (e.g. that are passed through the
		 * platform) with the values from the HW capability
		 * register (if supported).
		 */
		priv->plat->enh_desc = priv->dma_cap.enh_desc;
		priv->plat->pmt = priv->dma_cap.pmt_remote_wake_up;
		priv->hw->pmt = priv->plat->pmt;

		/* TXCOE doesn't work in thresh DMA mode */
		if (priv->plat->force_thresh_dma_mode)
			priv->plat->tx_coe = 0;
		else
			priv->plat->tx_coe = priv->dma_cap.tx_coe;

		/* In case of GMAC4 rx_coe is from HW cap register. */
		priv->plat->rx_coe = priv->dma_cap.rx_coe;

		if (priv->dma_cap.rx_coe_type2)
			priv->plat->rx_coe = STMMAC_RX_COE_TYPE2;
		else if (priv->dma_cap.rx_coe_type1)
			priv->plat->rx_coe = STMMAC_RX_COE_TYPE1;

	} else {
		dev_info(priv->device, "No HW DMA feature register supported\n");
	}

<<<<<<< HEAD
=======
	/* To use alternate (extended), normal or GMAC4 descriptor structures */
	if (priv->synopsys_id >= DWMAC_CORE_4_00)
		priv->hw->desc = &dwmac4_desc_ops;
	else
		stmmac_selec_desc_mode(priv);

>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	if (priv->plat->rx_coe) {
		priv->hw->rx_csum = priv->plat->rx_coe;
		dev_info(priv->device, "RX Checksum Offload Engine supported\n");
		if (priv->synopsys_id < DWMAC_CORE_4_00)
			dev_info(priv->device, "COE Type %d\n", priv->hw->rx_csum);
	}
	if (priv->plat->tx_coe)
		dev_info(priv->device, "TX Checksum insertion supported\n");

	if (priv->plat->pmt) {
		dev_info(priv->device, "Wake-Up On Lan supported\n");
		device_set_wakeup_capable(priv->device, 1);
	}

	if (priv->dma_cap.tsoen)
		dev_info(priv->device, "TSO supported\n");

<<<<<<< HEAD
	/* Run HW quirks, if any */
	if (priv->hwif_quirks) {
		ret = priv->hwif_quirks(priv);
		if (ret)
			return ret;
	}

	/* Rx Watchdog is available in the COREs newer than the 3.40.
	 * In some case, for example on bugged HW this feature
	 * has to be disable and this can be done by passing the
	 * riwt_off field from the platform.
	 */
	if (((priv->synopsys_id >= DWMAC_CORE_3_50) ||
	    (priv->plat->has_xgmac)) && (!priv->plat->riwt_off)) {
		priv->use_riwt = 1;
		dev_info(priv->device,
			 "Enable RX Mitigation via HW Watchdog Timer\n");
	}

=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	return 0;
}

/**
 * stmmac_dvr_probe
 * @device: device pointer
 * @plat_dat: platform data pointer
 * @res: stmmac resource pointer
 * Description: this is the main probe function used to
 * call the alloc_etherdev, allocate the priv structure.
 * Return:
 * returns 0 on success, otherwise errno.
 */
int stmmac_dvr_probe(struct device *device,
		     struct plat_stmmacenet_data *plat_dat,
		     struct stmmac_resources *res)
{
	struct net_device *ndev = NULL;
	struct stmmac_priv *priv;
<<<<<<< HEAD
	u32 queue, maxq;
	int ret = 0;
=======
	int ret = 0;
	u32 queue;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	ndev = alloc_etherdev_mqs(sizeof(struct stmmac_priv),
				  MTL_MAX_TX_QUEUES,
				  MTL_MAX_RX_QUEUES);
	if (!ndev)
		return -ENOMEM;

	SET_NETDEV_DEV(ndev, device);

	priv = netdev_priv(ndev);
	priv->device = device;
	priv->dev = ndev;

	stmmac_set_ethtool_ops(ndev);
	priv->pause = pause;
	priv->plat = plat_dat;
	priv->ioaddr = res->addr;
	priv->dev->base_addr = (unsigned long)res->addr;

	priv->dev->irq = res->irq;
	priv->wol_irq = res->wol_irq;
	priv->lpi_irq = res->lpi_irq;

	if (res->mac)
		memcpy(priv->dev->dev_addr, res->mac, ETH_ALEN);

	dev_set_drvdata(device, priv->dev);

	/* Verify driver arguments */
	stmmac_verify_args();

<<<<<<< HEAD
	/* Allocate workqueue */
	priv->wq = create_singlethread_workqueue("stmmac_wq");
	if (!priv->wq) {
		dev_err(priv->device, "failed to create workqueue\n");
		ret = -ENOMEM;
		goto error_wq;
	}

	INIT_WORK(&priv->service_task, stmmac_service_task);

=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	/* Override with kernel parameters if supplied XXX CRS XXX
	 * this needs to have multiple instances
	 */
	if ((phyaddr >= 0) && (phyaddr <= 31))
		priv->plat->phy_addr = phyaddr;

	if (priv->plat->stmmac_rst) {
		ret = reset_control_assert(priv->plat->stmmac_rst);
		reset_control_deassert(priv->plat->stmmac_rst);
		/* Some reset controllers have only reset callback instead of
		 * assert + deassert callbacks pair.
		 */
		if (ret == -ENOTSUPP)
			reset_control_reset(priv->plat->stmmac_rst);
	}

	/* Init MAC and get the capabilities */
	ret = stmmac_hw_init(priv);
	if (ret)
		goto error_hw_init;

	stmmac_check_ether_addr(priv);

	/* Configure real RX and TX queues */
	netif_set_real_num_rx_queues(ndev, priv->plat->rx_queues_to_use);
	netif_set_real_num_tx_queues(ndev, priv->plat->tx_queues_to_use);

	ndev->netdev_ops = &stmmac_netdev_ops;

	ndev->hw_features = NETIF_F_SG | NETIF_F_IP_CSUM | NETIF_F_IPV6_CSUM |
			    NETIF_F_RXCSUM;

<<<<<<< HEAD
	ret = stmmac_tc_init(priv, priv);
	if (!ret) {
		ndev->hw_features |= NETIF_F_HW_TC;
	}

=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	if ((priv->plat->tso_en) && (priv->dma_cap.tsoen)) {
		ndev->hw_features |= NETIF_F_TSO | NETIF_F_TSO6;
		priv->tso = true;
		dev_info(priv->device, "TSO feature enabled\n");
	}
	ndev->features |= ndev->hw_features | NETIF_F_HIGHDMA;
	ndev->watchdog_timeo = msecs_to_jiffies(watchdog);
#ifdef STMMAC_VLAN_TAG_USED
	/* Both mac100 and gmac support receive VLAN tag detection */
<<<<<<< HEAD
	ndev->features |= NETIF_F_HW_VLAN_CTAG_RX | NETIF_F_HW_VLAN_STAG_RX;
=======
	ndev->features |= NETIF_F_HW_VLAN_CTAG_RX;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
#endif
	priv->msg_enable = netif_msg_init(debug, default_msg_level);

	/* MTU range: 46 - hw-specific max */
	ndev->min_mtu = ETH_ZLEN - ETH_HLEN;
	if ((priv->plat->enh_desc) || (priv->synopsys_id >= DWMAC_CORE_4_00))
		ndev->max_mtu = JUMBO_LEN;
<<<<<<< HEAD
	else if (priv->plat->has_xgmac)
		ndev->max_mtu = XGMAC_JUMBO_LEN;
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	else
		ndev->max_mtu = SKB_MAX_HEAD(NET_SKB_PAD + NET_IP_ALIGN);
	/* Will not overwrite ndev->max_mtu if plat->maxmtu > ndev->max_mtu
	 * as well as plat->maxmtu < ndev->min_mtu which is a invalid range.
	 */
	if ((priv->plat->maxmtu < ndev->max_mtu) &&
	    (priv->plat->maxmtu >= ndev->min_mtu))
		ndev->max_mtu = priv->plat->maxmtu;
	else if (priv->plat->maxmtu < ndev->min_mtu)
		dev_warn(priv->device,
			 "%s: warning: maxmtu having invalid value (%d)\n",
			 __func__, priv->plat->maxmtu);

	if (flow_ctrl)
		priv->flow_ctrl = FLOW_AUTO;	/* RX/TX pause on */

<<<<<<< HEAD
	/* Setup channels NAPI */
	maxq = max(priv->plat->rx_queues_to_use, priv->plat->tx_queues_to_use);

	for (queue = 0; queue < maxq; queue++) {
		struct stmmac_channel *ch = &priv->channel[queue];

		ch->priv_data = priv;
		ch->index = queue;

		if (queue < priv->plat->rx_queues_to_use)
			ch->has_rx = true;
		if (queue < priv->plat->tx_queues_to_use)
			ch->has_tx = true;

		netif_napi_add(ndev, &ch->napi, stmmac_napi_poll,
			       NAPI_POLL_WEIGHT);
=======
	/* Rx Watchdog is available in the COREs newer than the 3.40.
	 * In some case, for example on bugged HW this feature
	 * has to be disable and this can be done by passing the
	 * riwt_off field from the platform.
	 */
	if ((priv->synopsys_id >= DWMAC_CORE_3_50) && (!priv->plat->riwt_off)) {
		priv->use_riwt = 1;
		dev_info(priv->device,
			 "Enable RX Mitigation via HW Watchdog Timer\n");
	}

	for (queue = 0; queue < priv->plat->rx_queues_to_use; queue++) {
		struct stmmac_rx_queue *rx_q = &priv->rx_queue[queue];

		netif_napi_add(ndev, &rx_q->napi, stmmac_poll,
			       (8 * priv->plat->rx_queues_to_use));
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	}

	mutex_init(&priv->lock);

	/* If a specific clk_csr value is passed from the platform
	 * this means that the CSR Clock Range selection cannot be
	 * changed at run-time and it is fixed. Viceversa the driver'll try to
	 * set the MDC clock dynamically according to the csr actual
	 * clock input.
	 */
	if (!priv->plat->clk_csr)
		stmmac_clk_csr_set(priv);
	else
		priv->clk_csr = priv->plat->clk_csr;

	stmmac_check_pcs_mode(priv);

<<<<<<< HEAD
	if (priv->hw->pcs != STMMAC_PCS_RGMII  &&
	    priv->hw->pcs != STMMAC_PCS_TBI &&
	    priv->hw->pcs != STMMAC_PCS_RTBI) {
=======
	if (!priv->plat->mac2mac_en &&
	    (priv->hw->pcs != STMMAC_PCS_RGMII &&
	     priv->hw->pcs != STMMAC_PCS_TBI &&
	     priv->hw->pcs != STMMAC_PCS_RTBI)) {
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
		/* MDIO bus Registration */
		ret = stmmac_mdio_register(ndev);
		if (ret < 0) {
			dev_err(priv->device,
				"%s: MDIO bus (id: %d) registration failed",
				__func__, priv->plat->bus_id);
			goto error_mdio_register;
		}
	}

	ret = register_netdev(ndev);
	if (ret) {
		dev_err(priv->device, "%s: ERROR %i registering the device\n",
			__func__, ret);
		goto error_netdev_register;
	}

<<<<<<< HEAD
=======
	/* Disable tx_coal_timer if plat provides callback */
	priv->tx_coal_timer_disable =
		plat_dat->get_plat_tx_coal_frames ? true : false;

>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
#ifdef CONFIG_DEBUG_FS
	ret = stmmac_init_fs(ndev);
	if (ret < 0)
		netdev_warn(priv->dev, "%s: failed debugFS registration\n",
			    __func__);
#endif

	return ret;

error_netdev_register:
	if (priv->hw->pcs != STMMAC_PCS_RGMII &&
	    priv->hw->pcs != STMMAC_PCS_TBI &&
	    priv->hw->pcs != STMMAC_PCS_RTBI)
		stmmac_mdio_unregister(ndev);
error_mdio_register:
<<<<<<< HEAD
	for (queue = 0; queue < maxq; queue++) {
		struct stmmac_channel *ch = &priv->channel[queue];

		netif_napi_del(&ch->napi);
	}
error_hw_init:
	destroy_workqueue(priv->wq);
error_wq:
=======
	for (queue = 0; queue < priv->plat->rx_queues_to_use; queue++) {
		struct stmmac_rx_queue *rx_q = &priv->rx_queue[queue];

		netif_napi_del(&rx_q->napi);
	}
error_hw_init:
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	free_netdev(ndev);

	return ret;
}
EXPORT_SYMBOL_GPL(stmmac_dvr_probe);

/**
 * stmmac_dvr_remove
 * @dev: device pointer
 * Description: this function resets the TX/RX processes, disables the MAC RX/TX
 * changes the link status, releases the DMA descriptor rings.
 */
int stmmac_dvr_remove(struct device *dev)
{
	struct net_device *ndev = dev_get_drvdata(dev);
	struct stmmac_priv *priv = netdev_priv(ndev);

	netdev_info(priv->dev, "%s: removing driver", __func__);

#ifdef CONFIG_DEBUG_FS
	stmmac_exit_fs(ndev);
#endif
	stmmac_stop_all_dma(priv);

<<<<<<< HEAD
	stmmac_mac_set(priv, priv->ioaddr, false);
=======
	priv->hw->mac->set_mac(priv->ioaddr, false);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	netif_carrier_off(ndev);
	unregister_netdev(ndev);
	if (priv->plat->stmmac_rst)
		reset_control_assert(priv->plat->stmmac_rst);
	clk_disable_unprepare(priv->plat->pclk);
	clk_disable_unprepare(priv->plat->stmmac_clk);
	if (priv->hw->pcs != STMMAC_PCS_RGMII &&
	    priv->hw->pcs != STMMAC_PCS_TBI &&
	    priv->hw->pcs != STMMAC_PCS_RTBI)
		stmmac_mdio_unregister(ndev);
<<<<<<< HEAD
	destroy_workqueue(priv->wq);
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	mutex_destroy(&priv->lock);
	free_netdev(ndev);

	return 0;
}
EXPORT_SYMBOL_GPL(stmmac_dvr_remove);

/**
 * stmmac_suspend - suspend callback
 * @dev: device pointer
 * Description: this is the function to suspend the device and it is called
 * by the platform driver to stop the network queue, release the resources,
 * program the PMT register (for WoL), clean and release driver resources.
 */
int stmmac_suspend(struct device *dev)
{
	struct net_device *ndev = dev_get_drvdata(dev);
	struct stmmac_priv *priv = netdev_priv(ndev);

	if (!ndev || !netif_running(ndev))
		return 0;

	if (ndev->phydev)
		phy_stop(ndev->phydev);

	mutex_lock(&priv->lock);

	netif_device_detach(ndev);
	stmmac_stop_all_queues(priv);

	stmmac_disable_all_queues(priv);

	/* Stop TX/RX DMA */
	stmmac_stop_all_dma(priv);

	/* Enable Power down mode by programming the PMT regs */
	if (device_may_wakeup(priv->device)) {
<<<<<<< HEAD
		stmmac_pmt(priv, priv->hw, priv->wolopts);
		priv->irq_wake = 1;
	} else {
		stmmac_mac_set(priv, priv->ioaddr, false);
=======
		priv->hw->mac->pmt(priv->hw, priv->wolopts);
		priv->irq_wake = 1;
	} else {
		priv->hw->mac->set_mac(priv->ioaddr, false);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
		pinctrl_pm_select_sleep_state(priv->device);
		/* Disable clock in case of PWM is off */
		if (priv->plat->clk_ptp_ref)
			clk_disable_unprepare(priv->plat->clk_ptp_ref);
		clk_disable_unprepare(priv->plat->pclk);
		clk_disable_unprepare(priv->plat->stmmac_clk);
	}
	mutex_unlock(&priv->lock);

<<<<<<< HEAD
	priv->oldlink = false;
=======
	priv->oldlink = -1;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	priv->speed = SPEED_UNKNOWN;
	priv->oldduplex = DUPLEX_UNKNOWN;
	return 0;
}
EXPORT_SYMBOL_GPL(stmmac_suspend);

/**
 * stmmac_reset_queues_param - reset queue parameters
 * @dev: device pointer
 */
static void stmmac_reset_queues_param(struct stmmac_priv *priv)
{
	u32 rx_cnt = priv->plat->rx_queues_to_use;
	u32 tx_cnt = priv->plat->tx_queues_to_use;
	u32 queue;

	for (queue = 0; queue < rx_cnt; queue++) {
		struct stmmac_rx_queue *rx_q = &priv->rx_queue[queue];

		rx_q->cur_rx = 0;
		rx_q->dirty_rx = 0;
	}

	for (queue = 0; queue < tx_cnt; queue++) {
		struct stmmac_tx_queue *tx_q = &priv->tx_queue[queue];

		tx_q->cur_tx = 0;
		tx_q->dirty_tx = 0;
<<<<<<< HEAD
		tx_q->mss = 0;
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	}
}

/**
 * stmmac_resume - resume callback
 * @dev: device pointer
 * Description: when resume this function is invoked to setup the DMA and CORE
 * in a usable state.
 */
int stmmac_resume(struct device *dev)
{
	struct net_device *ndev = dev_get_drvdata(dev);
	struct stmmac_priv *priv = netdev_priv(ndev);

	if (!netif_running(ndev))
		return 0;

	/* Power Down bit, into the PM register, is cleared
	 * automatically as soon as a magic packet or a Wake-up frame
	 * is received. Anyway, it's better to manually clear
	 * this bit because it can generate problems while resuming
	 * from another devices (e.g. serial console).
	 */
	if (device_may_wakeup(priv->device)) {
		mutex_lock(&priv->lock);
<<<<<<< HEAD
		stmmac_pmt(priv, priv->hw, 0);
=======
		priv->hw->mac->pmt(priv->hw, 0);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
		mutex_unlock(&priv->lock);
		priv->irq_wake = 0;
	} else {
		pinctrl_pm_select_default_state(priv->device);
		/* enable the clk previously disabled */
		clk_prepare_enable(priv->plat->stmmac_clk);
		clk_prepare_enable(priv->plat->pclk);
		if (priv->plat->clk_ptp_ref)
			clk_prepare_enable(priv->plat->clk_ptp_ref);
		/* reset the phy so that it's ready */
		if (priv->mii)
			stmmac_mdio_reset(priv->mii);
	}

	netif_device_attach(ndev);

	mutex_lock(&priv->lock);

	stmmac_reset_queues_param(priv);

<<<<<<< HEAD
	stmmac_clear_descriptors(priv);

	stmmac_hw_setup(ndev, false);
	stmmac_init_tx_coalesce(priv);
=======
	/* reset private mss value to force mss context settings at
	 * next tso xmit (only used for gmac4).
	 */
	priv->mss = 0;

	stmmac_clear_descriptors(priv);

	stmmac_hw_setup(ndev, false);

	if (!priv->tx_coal_timer_disable)
		stmmac_init_tx_coalesce(priv);

>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	stmmac_set_rx_mode(ndev);

	stmmac_enable_all_queues(priv);

	stmmac_start_all_queues(priv);

	mutex_unlock(&priv->lock);

	if (ndev->phydev)
		phy_start(ndev->phydev);

	return 0;
}
EXPORT_SYMBOL_GPL(stmmac_resume);

#ifndef MODULE
static int __init stmmac_cmdline_opt(char *str)
{
	char *opt;

	if (!str || !*str)
		return -EINVAL;
	while ((opt = strsep(&str, ",")) != NULL) {
		if (!strncmp(opt, "debug:", 6)) {
			if (kstrtoint(opt + 6, 0, &debug))
				goto err;
		} else if (!strncmp(opt, "phyaddr:", 8)) {
			if (kstrtoint(opt + 8, 0, &phyaddr))
				goto err;
		} else if (!strncmp(opt, "buf_sz:", 7)) {
			if (kstrtoint(opt + 7, 0, &buf_sz))
				goto err;
		} else if (!strncmp(opt, "tc:", 3)) {
			if (kstrtoint(opt + 3, 0, &tc))
				goto err;
		} else if (!strncmp(opt, "watchdog:", 9)) {
			if (kstrtoint(opt + 9, 0, &watchdog))
				goto err;
		} else if (!strncmp(opt, "flow_ctrl:", 10)) {
			if (kstrtoint(opt + 10, 0, &flow_ctrl))
				goto err;
		} else if (!strncmp(opt, "pause:", 6)) {
			if (kstrtoint(opt + 6, 0, &pause))
				goto err;
		} else if (!strncmp(opt, "eee_timer:", 10)) {
			if (kstrtoint(opt + 10, 0, &eee_timer))
				goto err;
		} else if (!strncmp(opt, "chain_mode:", 11)) {
			if (kstrtoint(opt + 11, 0, &chain_mode))
				goto err;
		}
	}
	return 0;

err:
	pr_err("%s: ERROR broken module parameter conversion", __func__);
	return -EINVAL;
}

__setup("stmmaceth=", stmmac_cmdline_opt);
#endif /* MODULE */

static int __init stmmac_init(void)
{
#ifdef CONFIG_DEBUG_FS
	/* Create debugfs main directory if it doesn't exist yet */
	if (!stmmac_fs_dir) {
		stmmac_fs_dir = debugfs_create_dir(STMMAC_RESOURCE_NAME, NULL);

		if (!stmmac_fs_dir || IS_ERR(stmmac_fs_dir)) {
			pr_err("ERROR %s, debugfs create directory failed\n",
			       STMMAC_RESOURCE_NAME);

			return -ENOMEM;
		}
	}
#endif

	return 0;
}

static void __exit stmmac_exit(void)
{
#ifdef CONFIG_DEBUG_FS
	debugfs_remove_recursive(stmmac_fs_dir);
#endif
}

module_init(stmmac_init)
module_exit(stmmac_exit)

MODULE_DESCRIPTION("STMMAC 10/100/1000 Ethernet device driver");
MODULE_AUTHOR("Giuseppe Cavallaro <peppe.cavallaro@st.com>");
MODULE_LICENSE("GPL");
