/*
<<<<<<< HEAD
 * Copyright (C) 2016-2018 Netronome Systems, Inc.
=======
 * Copyright (C) 2016 Netronome Systems, Inc.
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
 *
 * This software is dual licensed under the GNU General License Version 2,
 * June 1991 as shown in the file COPYING in the top-level directory of this
 * source tree or the BSD 2-Clause License provided below.  You have the
 * option to license this software under the complete terms of either license.
 *
 * The BSD 2-Clause License:
 *
 *     Redistribution and use in source and binary forms, with or
 *     without modification, are permitted provided that the following
 *     conditions are met:
 *
 *      1. Redistributions of source code must retain the above
 *         copyright notice, this list of conditions and the following
 *         disclaimer.
 *
 *      2. Redistributions in binary form must reproduce the above
 *         copyright notice, this list of conditions and the following
 *         disclaimer in the documentation and/or other materials
 *         provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/*
 * nfp_net_offload.c
 * Netronome network device driver: TC offload functions for PF and VF
 */

<<<<<<< HEAD
#define pr_fmt(fmt)	"NFP net bpf: " fmt

#include <linux/bpf.h>
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
#include <linux/kernel.h>
#include <linux/netdevice.h>
#include <linux/pci.h>
#include <linux/jiffies.h>
#include <linux/timer.h>
#include <linux/list.h>
<<<<<<< HEAD
#include <linux/mm.h>
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

#include <net/pkt_cls.h>
#include <net/tc_act/tc_gact.h>
#include <net/tc_act/tc_mirred.h>

#include "main.h"
<<<<<<< HEAD
#include "../nfp_app.h"
#include "../nfp_net_ctrl.h"
#include "../nfp_net.h"

static int
nfp_map_ptr_record(struct nfp_app_bpf *bpf, struct nfp_prog *nfp_prog,
		   struct bpf_map *map)
{
	struct nfp_bpf_neutral_map *record;
	int err;

	/* Map record paths are entered via ndo, update side is protected. */
	ASSERT_RTNL();

	/* Reuse path - other offloaded program is already tracking this map. */
	record = rhashtable_lookup_fast(&bpf->maps_neutral, &map->id,
					nfp_bpf_maps_neutral_params);
	if (record) {
		nfp_prog->map_records[nfp_prog->map_records_cnt++] = record;
		record->count++;
		return 0;
	}

	/* Grab a single ref to the map for our record.  The prog destroy ndo
	 * happens after free_used_maps().
	 */
	map = bpf_map_inc(map, false);
	if (IS_ERR(map))
		return PTR_ERR(map);

	record = kmalloc(sizeof(*record), GFP_KERNEL);
	if (!record) {
		err = -ENOMEM;
		goto err_map_put;
	}

	record->ptr = map;
	record->map_id = map->id;
	record->count = 1;

	err = rhashtable_insert_fast(&bpf->maps_neutral, &record->l,
				     nfp_bpf_maps_neutral_params);
	if (err)
		goto err_free_rec;

	nfp_prog->map_records[nfp_prog->map_records_cnt++] = record;

	return 0;

err_free_rec:
	kfree(record);
err_map_put:
	bpf_map_put(map);
	return err;
}

static void
nfp_map_ptrs_forget(struct nfp_app_bpf *bpf, struct nfp_prog *nfp_prog)
{
	bool freed = false;
	int i;

	ASSERT_RTNL();

	for (i = 0; i < nfp_prog->map_records_cnt; i++) {
		if (--nfp_prog->map_records[i]->count) {
			nfp_prog->map_records[i] = NULL;
			continue;
		}

		WARN_ON(rhashtable_remove_fast(&bpf->maps_neutral,
					       &nfp_prog->map_records[i]->l,
					       nfp_bpf_maps_neutral_params));
		freed = true;
	}

	if (freed) {
		synchronize_rcu();

		for (i = 0; i < nfp_prog->map_records_cnt; i++)
			if (nfp_prog->map_records[i]) {
				bpf_map_put(nfp_prog->map_records[i]->ptr);
				kfree(nfp_prog->map_records[i]);
			}
	}

	kfree(nfp_prog->map_records);
	nfp_prog->map_records = NULL;
	nfp_prog->map_records_cnt = 0;
}

static int
nfp_map_ptrs_record(struct nfp_app_bpf *bpf, struct nfp_prog *nfp_prog,
		    struct bpf_prog *prog)
{
	int i, cnt, err;

	/* Quickly count the maps we will have to remember */
	cnt = 0;
	for (i = 0; i < prog->aux->used_map_cnt; i++)
		if (bpf_map_offload_neutral(prog->aux->used_maps[i]))
			cnt++;
	if (!cnt)
		return 0;

	nfp_prog->map_records = kmalloc_array(cnt,
					      sizeof(nfp_prog->map_records[0]),
					      GFP_KERNEL);
	if (!nfp_prog->map_records)
		return -ENOMEM;

	for (i = 0; i < prog->aux->used_map_cnt; i++)
		if (bpf_map_offload_neutral(prog->aux->used_maps[i])) {
			err = nfp_map_ptr_record(bpf, nfp_prog,
						 prog->aux->used_maps[i]);
			if (err) {
				nfp_map_ptrs_forget(bpf, nfp_prog);
				return err;
			}
		}
	WARN_ON(cnt != nfp_prog->map_records_cnt);
=======
#include "../nfp_net_ctrl.h"
#include "../nfp_net.h"

void nfp_net_filter_stats_timer(unsigned long data)
{
	struct nfp_net *nn = (void *)data;
	struct nfp_net_bpf_priv *priv;
	struct nfp_stat_pair latest;

	priv = nn->app_priv;

	spin_lock_bh(&priv->rx_filter_lock);

	if (nn->dp.ctrl & NFP_NET_CFG_CTRL_BPF)
		mod_timer(&priv->rx_filter_stats_timer,
			  jiffies + NFP_NET_STAT_POLL_IVL);

	spin_unlock_bh(&priv->rx_filter_lock);

	latest.pkts = nn_readq(nn, NFP_NET_CFG_STATS_APP1_FRAMES);
	latest.bytes = nn_readq(nn, NFP_NET_CFG_STATS_APP1_BYTES);

	if (latest.pkts != priv->rx_filter.pkts)
		priv->rx_filter_change = jiffies;

	priv->rx_filter = latest;
}

static void nfp_net_bpf_stats_reset(struct nfp_net *nn)
{
	struct nfp_net_bpf_priv *priv = nn->app_priv;

	priv->rx_filter.pkts = nn_readq(nn, NFP_NET_CFG_STATS_APP1_FRAMES);
	priv->rx_filter.bytes = nn_readq(nn, NFP_NET_CFG_STATS_APP1_BYTES);
	priv->rx_filter_prev = priv->rx_filter;
	priv->rx_filter_change = jiffies;
}

static int
nfp_net_bpf_stats_update(struct nfp_net *nn, struct tc_cls_bpf_offload *cls_bpf)
{
	struct nfp_net_bpf_priv *priv = nn->app_priv;
	u64 bytes, pkts;

	pkts = priv->rx_filter.pkts - priv->rx_filter_prev.pkts;
	bytes = priv->rx_filter.bytes - priv->rx_filter_prev.bytes;
	bytes -= pkts * ETH_HLEN;

	priv->rx_filter_prev = priv->rx_filter;

	tcf_exts_stats_update(cls_bpf->exts,
			      bytes, pkts, priv->rx_filter_change);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	return 0;
}

static int
<<<<<<< HEAD
nfp_prog_prepare(struct nfp_prog *nfp_prog, const struct bpf_insn *prog,
		 unsigned int cnt)
{
	struct nfp_insn_meta *meta;
	unsigned int i;

	for (i = 0; i < cnt; i++) {
		meta = kzalloc(sizeof(*meta), GFP_KERNEL);
		if (!meta)
			return -ENOMEM;

		meta->insn = prog[i];
		meta->n = i;
		if (is_mbpf_alu(meta)) {
			meta->umin_src = U64_MAX;
			meta->umin_dst = U64_MAX;
		}

		list_add_tail(&meta->l, &nfp_prog->insns);
	}

	nfp_bpf_jit_prepare(nfp_prog, cnt);

	return 0;
}

static void nfp_prog_free(struct nfp_prog *nfp_prog)
{
	struct nfp_insn_meta *meta, *tmp;

	list_for_each_entry_safe(meta, tmp, &nfp_prog->insns, l) {
		list_del(&meta->l);
		kfree(meta);
	}
	kfree(nfp_prog);
}

static int
nfp_bpf_verifier_prep(struct nfp_app *app, struct nfp_net *nn,
		      struct netdev_bpf *bpf)
{
	struct bpf_prog *prog = bpf->verifier.prog;
	struct nfp_prog *nfp_prog;
	int ret;

	nfp_prog = kzalloc(sizeof(*nfp_prog), GFP_KERNEL);
	if (!nfp_prog)
		return -ENOMEM;
	prog->aux->offload->dev_priv = nfp_prog;

	INIT_LIST_HEAD(&nfp_prog->insns);
	nfp_prog->type = prog->type;
	nfp_prog->bpf = app->priv;

	ret = nfp_prog_prepare(nfp_prog, prog->insnsi, prog->len);
	if (ret)
		goto err_free;

	nfp_prog->verifier_meta = nfp_prog_first_meta(nfp_prog);
	bpf->verifier.ops = &nfp_bpf_analyzer_ops;

	return 0;

err_free:
	nfp_prog_free(nfp_prog);

	return ret;
}

static int nfp_bpf_translate(struct nfp_net *nn, struct bpf_prog *prog)
{
	struct nfp_prog *nfp_prog = prog->aux->offload->dev_priv;
	unsigned int stack_size;
	unsigned int max_instr;
	int err;

	stack_size = nn_readb(nn, NFP_NET_CFG_BPF_STACK_SZ) * 64;
	if (prog->aux->stack_depth > stack_size) {
		nn_info(nn, "stack too large: program %dB > FW stack %dB\n",
			prog->aux->stack_depth, stack_size);
		return -EOPNOTSUPP;
	}
	nfp_prog->stack_depth = round_up(prog->aux->stack_depth, 4);

	max_instr = nn_readw(nn, NFP_NET_CFG_BPF_MAX_LEN);
	nfp_prog->__prog_alloc_len = max_instr * sizeof(u64);

	nfp_prog->prog = kvmalloc(nfp_prog->__prog_alloc_len, GFP_KERNEL);
	if (!nfp_prog->prog)
		return -ENOMEM;

	err = nfp_bpf_jit(nfp_prog);
	if (err)
		return err;

	prog->aux->offload->jited_len = nfp_prog->prog_len * sizeof(u64);
	prog->aux->offload->jited_image = nfp_prog->prog;

	return nfp_map_ptrs_record(nfp_prog->bpf, nfp_prog, prog);
}

static int nfp_bpf_destroy(struct nfp_net *nn, struct bpf_prog *prog)
{
	struct nfp_prog *nfp_prog = prog->aux->offload->dev_priv;

	kvfree(nfp_prog->prog);
	nfp_map_ptrs_forget(nfp_prog->bpf, nfp_prog);
	nfp_prog_free(nfp_prog);

	return 0;
}

/* Atomic engine requires values to be in big endian, we need to byte swap
 * the value words used with xadd.
 */
static void nfp_map_bpf_byte_swap(struct nfp_bpf_map *nfp_map, void *value)
{
	u32 *word = value;
	unsigned int i;

	for (i = 0; i < DIV_ROUND_UP(nfp_map->offmap->map.value_size, 4); i++)
		if (nfp_map->use_map[i] == NFP_MAP_USE_ATOMIC_CNT)
			word[i] = (__force u32)cpu_to_be32(word[i]);
}

static int
nfp_bpf_map_lookup_entry(struct bpf_offloaded_map *offmap,
			 void *key, void *value)
{
	int err;

	err = nfp_bpf_ctrl_lookup_entry(offmap, key, value);
	if (err)
		return err;

	nfp_map_bpf_byte_swap(offmap->dev_priv, value);
	return 0;
}

static int
nfp_bpf_map_update_entry(struct bpf_offloaded_map *offmap,
			 void *key, void *value, u64 flags)
{
	nfp_map_bpf_byte_swap(offmap->dev_priv, value);
	return nfp_bpf_ctrl_update_entry(offmap, key, value, flags);
}

static int
nfp_bpf_map_get_next_key(struct bpf_offloaded_map *offmap,
			 void *key, void *next_key)
{
	if (!key)
		return nfp_bpf_ctrl_getfirst_entry(offmap, next_key);
	return nfp_bpf_ctrl_getnext_entry(offmap, key, next_key);
}

static int
nfp_bpf_map_delete_elem(struct bpf_offloaded_map *offmap, void *key)
{
	if (offmap->map.map_type == BPF_MAP_TYPE_ARRAY)
		return -EINVAL;
	return nfp_bpf_ctrl_del_entry(offmap, key);
}

static const struct bpf_map_dev_ops nfp_bpf_map_ops = {
	.map_get_next_key	= nfp_bpf_map_get_next_key,
	.map_lookup_elem	= nfp_bpf_map_lookup_entry,
	.map_update_elem	= nfp_bpf_map_update_entry,
	.map_delete_elem	= nfp_bpf_map_delete_elem,
};

static int
nfp_bpf_map_alloc(struct nfp_app_bpf *bpf, struct bpf_offloaded_map *offmap)
{
	struct nfp_bpf_map *nfp_map;
	unsigned int use_map_size;
	long long int res;

	if (!bpf->maps.types)
		return -EOPNOTSUPP;

	if (offmap->map.map_flags ||
	    offmap->map.numa_node != NUMA_NO_NODE) {
		pr_info("map flags are not supported\n");
		return -EINVAL;
	}

	if (!(bpf->maps.types & 1 << offmap->map.map_type)) {
		pr_info("map type not supported\n");
		return -EOPNOTSUPP;
	}
	if (bpf->maps.max_maps == bpf->maps_in_use) {
		pr_info("too many maps for a device\n");
		return -ENOMEM;
	}
	if (bpf->maps.max_elems - bpf->map_elems_in_use <
	    offmap->map.max_entries) {
		pr_info("map with too many elements: %u, left: %u\n",
			offmap->map.max_entries,
			bpf->maps.max_elems - bpf->map_elems_in_use);
		return -ENOMEM;
	}

	if (round_up(offmap->map.key_size, 8) +
	    round_up(offmap->map.value_size, 8) > bpf->maps.max_elem_sz) {
		pr_info("map elements too large: %u, FW max element size (key+value): %u\n",
			round_up(offmap->map.key_size, 8) +
			round_up(offmap->map.value_size, 8),
			bpf->maps.max_elem_sz);
		return -ENOMEM;
	}
	if (offmap->map.key_size > bpf->maps.max_key_sz) {
		pr_info("map key size %u, FW max is %u\n",
			offmap->map.key_size, bpf->maps.max_key_sz);
		return -ENOMEM;
	}
	if (offmap->map.value_size > bpf->maps.max_val_sz) {
		pr_info("map value size %u, FW max is %u\n",
			offmap->map.value_size, bpf->maps.max_val_sz);
		return -ENOMEM;
	}

	use_map_size = DIV_ROUND_UP(offmap->map.value_size, 4) *
		       FIELD_SIZEOF(struct nfp_bpf_map, use_map[0]);

	nfp_map = kzalloc(sizeof(*nfp_map) + use_map_size, GFP_USER);
	if (!nfp_map)
		return -ENOMEM;

	offmap->dev_priv = nfp_map;
	nfp_map->offmap = offmap;
	nfp_map->bpf = bpf;

	res = nfp_bpf_ctrl_alloc_map(bpf, &offmap->map);
	if (res < 0) {
		kfree(nfp_map);
		return res;
	}

	nfp_map->tid = res;
	offmap->dev_ops = &nfp_bpf_map_ops;
	bpf->maps_in_use++;
	bpf->map_elems_in_use += offmap->map.max_entries;
	list_add_tail(&nfp_map->l, &bpf->map_list);

	return 0;
}

static int
nfp_bpf_map_free(struct nfp_app_bpf *bpf, struct bpf_offloaded_map *offmap)
{
	struct nfp_bpf_map *nfp_map = offmap->dev_priv;

	nfp_bpf_ctrl_free_map(bpf, nfp_map);
	list_del_init(&nfp_map->l);
	bpf->map_elems_in_use -= offmap->map.max_entries;
	bpf->maps_in_use--;
	kfree(nfp_map);

	return 0;
}

int nfp_ndo_bpf(struct nfp_app *app, struct nfp_net *nn, struct netdev_bpf *bpf)
{
	switch (bpf->command) {
	case BPF_OFFLOAD_VERIFIER_PREP:
		return nfp_bpf_verifier_prep(app, nn, bpf);
	case BPF_OFFLOAD_TRANSLATE:
		return nfp_bpf_translate(nn, bpf->offload.prog);
	case BPF_OFFLOAD_DESTROY:
		return nfp_bpf_destroy(nn, bpf->offload.prog);
	case BPF_OFFLOAD_MAP_ALLOC:
		return nfp_bpf_map_alloc(app->priv, bpf->offmap);
	case BPF_OFFLOAD_MAP_FREE:
		return nfp_bpf_map_free(app->priv, bpf->offmap);
	default:
		return -EINVAL;
	}
}

static unsigned long
nfp_bpf_perf_event_copy(void *dst, const void *src,
			unsigned long off, unsigned long len)
{
	memcpy(dst, src + off, len);
	return 0;
}

int nfp_bpf_event_output(struct nfp_app_bpf *bpf, const void *data,
			 unsigned int len)
{
	struct cmsg_bpf_event *cbe = (void *)data;
	struct nfp_bpf_neutral_map *record;
	u32 pkt_size, data_size, map_id;
	u64 map_id_full;

	if (len < sizeof(struct cmsg_bpf_event))
		return -EINVAL;

	pkt_size = be32_to_cpu(cbe->pkt_size);
	data_size = be32_to_cpu(cbe->data_size);
	map_id_full = be64_to_cpu(cbe->map_ptr);
	map_id = map_id_full;

	if (len < sizeof(struct cmsg_bpf_event) + pkt_size + data_size)
		return -EINVAL;
	if (cbe->hdr.ver != CMSG_MAP_ABI_VERSION)
		return -EINVAL;

	rcu_read_lock();
	record = rhashtable_lookup_fast(&bpf->maps_neutral, &map_id,
					nfp_bpf_maps_neutral_params);
	if (!record || map_id_full > U32_MAX) {
		rcu_read_unlock();
		cmsg_warn(bpf, "perf event: map id %lld (0x%llx) not recognized, dropping event\n",
			  map_id_full, map_id_full);
		return -EINVAL;
	}

	bpf_event_output(record->ptr, be32_to_cpu(cbe->cpu_id),
			 &cbe->data[round_up(pkt_size, 4)], data_size,
			 cbe->data, pkt_size, nfp_bpf_perf_event_copy);
	rcu_read_unlock();

	return 0;
}

static int
nfp_net_bpf_load(struct nfp_net *nn, struct bpf_prog *prog,
		 struct netlink_ext_ack *extack)
{
	struct nfp_prog *nfp_prog = prog->aux->offload->dev_priv;
	unsigned int max_mtu;
	dma_addr_t dma_addr;
	void *img;
	int err;

	max_mtu = nn_readb(nn, NFP_NET_CFG_BPF_INL_MTU) * 64 - 32;
	if (max_mtu < nn->dp.netdev->mtu) {
		NL_SET_ERR_MSG_MOD(extack, "BPF offload not supported with MTU larger than HW packet split boundary");
		return -EOPNOTSUPP;
	}

	img = nfp_bpf_relo_for_vnic(nfp_prog, nn->app_priv);
	if (IS_ERR(img))
		return PTR_ERR(img);

	dma_addr = dma_map_single(nn->dp.dev, img,
				  nfp_prog->prog_len * sizeof(u64),
				  DMA_TO_DEVICE);
	if (dma_mapping_error(nn->dp.dev, dma_addr)) {
		kfree(img);
		return -ENOMEM;
	}

	nn_writew(nn, NFP_NET_CFG_BPF_SIZE, nfp_prog->prog_len);
	nn_writeq(nn, NFP_NET_CFG_BPF_ADDR, dma_addr);
=======
nfp_net_bpf_get_act(struct nfp_net *nn, struct tc_cls_bpf_offload *cls_bpf)
{
	const struct tc_action *a;
	LIST_HEAD(actions);

	if (!cls_bpf->exts)
		return NN_ACT_XDP;

	/* TC direct action */
	if (cls_bpf->exts_integrated) {
		if (!tcf_exts_has_actions(cls_bpf->exts))
			return NN_ACT_DIRECT;

		return -EOPNOTSUPP;
	}

	/* TC legacy mode */
	if (!tcf_exts_has_one_action(cls_bpf->exts))
		return -EOPNOTSUPP;

	tcf_exts_to_list(cls_bpf->exts, &actions);
	list_for_each_entry(a, &actions, list) {
		if (is_tcf_gact_shot(a))
			return NN_ACT_TC_DROP;

		if (is_tcf_mirred_egress_redirect(a) &&
		    tcf_mirred_ifindex(a) == nn->dp.netdev->ifindex)
			return NN_ACT_TC_REDIR;
	}

	return -EOPNOTSUPP;
}

static int
nfp_net_bpf_offload_prepare(struct nfp_net *nn,
			    struct tc_cls_bpf_offload *cls_bpf,
			    struct nfp_bpf_result *res,
			    void **code, dma_addr_t *dma_addr, u16 max_instr)
{
	unsigned int code_sz = max_instr * sizeof(u64);
	enum nfp_bpf_action_type act;
	u16 start_off, done_off;
	unsigned int max_mtu;
	int ret;

	if (!IS_ENABLED(CONFIG_BPF_SYSCALL))
		return -EOPNOTSUPP;

	ret = nfp_net_bpf_get_act(nn, cls_bpf);
	if (ret < 0)
		return ret;
	act = ret;

	max_mtu = nn_readb(nn, NFP_NET_CFG_BPF_INL_MTU) * 64 - 32;
	if (max_mtu < nn->dp.netdev->mtu) {
		nn_info(nn, "BPF offload not supported with MTU larger than HW packet split boundary\n");
		return -EOPNOTSUPP;
	}

	start_off = nn_readw(nn, NFP_NET_CFG_BPF_START);
	done_off = nn_readw(nn, NFP_NET_CFG_BPF_DONE);

	*code = dma_zalloc_coherent(nn->dp.dev, code_sz, dma_addr, GFP_KERNEL);
	if (!*code)
		return -ENOMEM;

	ret = nfp_bpf_jit(cls_bpf->prog, *code, act, start_off, done_off,
			  max_instr, res);
	if (ret)
		goto out;

	return 0;

out:
	dma_free_coherent(nn->dp.dev, code_sz, *code, *dma_addr);
	return ret;
}

static void
nfp_net_bpf_load_and_start(struct nfp_net *nn, u32 tc_flags,
			   void *code, dma_addr_t dma_addr,
			   unsigned int code_sz, unsigned int n_instr,
			   bool dense_mode)
{
	struct nfp_net_bpf_priv *priv = nn->app_priv;
	u64 bpf_addr = dma_addr;
	int err;

	nn->dp.bpf_offload_skip_sw = !!(tc_flags & TCA_CLS_FLAGS_SKIP_SW);

	if (dense_mode)
		bpf_addr |= NFP_NET_CFG_BPF_CFG_8CTX;

	nn_writew(nn, NFP_NET_CFG_BPF_SIZE, n_instr);
	nn_writeq(nn, NFP_NET_CFG_BPF_ADDR, bpf_addr);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	/* Load up the JITed code */
	err = nfp_net_reconfig(nn, NFP_NET_CFG_UPDATE_BPF);
	if (err)
<<<<<<< HEAD
		NL_SET_ERR_MSG_MOD(extack,
				   "FW command error while loading BPF");

	dma_unmap_single(nn->dp.dev, dma_addr, nfp_prog->prog_len * sizeof(u64),
			 DMA_TO_DEVICE);
	kfree(img);

	return err;
}

static void
nfp_net_bpf_start(struct nfp_net *nn, struct netlink_ext_ack *extack)
{
	int err;
=======
		nn_err(nn, "FW command error while loading BPF: %d\n", err);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	/* Enable passing packets through BPF function */
	nn->dp.ctrl |= NFP_NET_CFG_CTRL_BPF;
	nn_writel(nn, NFP_NET_CFG_CTRL, nn->dp.ctrl);
	err = nfp_net_reconfig(nn, NFP_NET_CFG_UPDATE_GEN);
	if (err)
<<<<<<< HEAD
		NL_SET_ERR_MSG_MOD(extack,
				   "FW command error while enabling BPF");
=======
		nn_err(nn, "FW command error while enabling BPF: %d\n", err);

	dma_free_coherent(nn->dp.dev, code_sz, code, dma_addr);

	nfp_net_bpf_stats_reset(nn);
	mod_timer(&priv->rx_filter_stats_timer,
		  jiffies + NFP_NET_STAT_POLL_IVL);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
}

static int nfp_net_bpf_stop(struct nfp_net *nn)
{
<<<<<<< HEAD
	if (!(nn->dp.ctrl & NFP_NET_CFG_CTRL_BPF))
		return 0;

	nn->dp.ctrl &= ~NFP_NET_CFG_CTRL_BPF;
	nn_writel(nn, NFP_NET_CFG_CTRL, nn->dp.ctrl);

	return nfp_net_reconfig(nn, NFP_NET_CFG_UPDATE_GEN);
}

int nfp_net_bpf_offload(struct nfp_net *nn, struct bpf_prog *prog,
			bool old_prog, struct netlink_ext_ack *extack)
{
	int err;

	if (prog && !bpf_offload_dev_match(prog, nn->dp.netdev))
		return -EINVAL;

	if (prog && old_prog) {
		u8 cap;

		cap = nn_readb(nn, NFP_NET_CFG_BPF_CAP);
		if (!(cap & NFP_NET_BPF_CAP_RELO)) {
			NL_SET_ERR_MSG_MOD(extack,
					   "FW does not support live reload");
			return -EBUSY;
		}
	}

	/* Something else is loaded, different program type? */
	if (!old_prog && nn->dp.ctrl & NFP_NET_CFG_CTRL_BPF)
		return -EBUSY;

	if (old_prog && !prog)
		return nfp_net_bpf_stop(nn);

	err = nfp_net_bpf_load(nn, prog, extack);
	if (err)
		return err;

	if (!old_prog)
		nfp_net_bpf_start(nn, extack);

	return 0;
=======
	struct nfp_net_bpf_priv *priv = nn->app_priv;

	if (!(nn->dp.ctrl & NFP_NET_CFG_CTRL_BPF))
		return 0;

	spin_lock_bh(&priv->rx_filter_lock);
	nn->dp.ctrl &= ~NFP_NET_CFG_CTRL_BPF;
	spin_unlock_bh(&priv->rx_filter_lock);
	nn_writel(nn, NFP_NET_CFG_CTRL, nn->dp.ctrl);

	del_timer_sync(&priv->rx_filter_stats_timer);
	nn->dp.bpf_offload_skip_sw = 0;

	return nfp_net_reconfig(nn, NFP_NET_CFG_UPDATE_GEN);
}

int nfp_net_bpf_offload(struct nfp_net *nn, struct tc_cls_bpf_offload *cls_bpf)
{
	struct nfp_bpf_result res;
	dma_addr_t dma_addr;
	u16 max_instr;
	void *code;
	int err;

	max_instr = nn_readw(nn, NFP_NET_CFG_BPF_MAX_LEN);

	switch (cls_bpf->command) {
	case TC_CLSBPF_REPLACE:
		/* There is nothing stopping us from implementing seamless
		 * replace but the simple method of loading I adopted in
		 * the firmware does not handle atomic replace (i.e. we have to
		 * stop the BPF offload and re-enable it).  Leaking-in a few
		 * frames which didn't have BPF applied in the hardware should
		 * be fine if software fallback is available, though.
		 */
		if (nn->dp.bpf_offload_skip_sw)
			return -EBUSY;

		err = nfp_net_bpf_offload_prepare(nn, cls_bpf, &res, &code,
						  &dma_addr, max_instr);
		if (err)
			return err;

		nfp_net_bpf_stop(nn);
		nfp_net_bpf_load_and_start(nn, cls_bpf->gen_flags, code,
					   dma_addr, max_instr * sizeof(u64),
					   res.n_instr, res.dense_mode);
		return 0;

	case TC_CLSBPF_ADD:
		if (nn->dp.ctrl & NFP_NET_CFG_CTRL_BPF)
			return -EBUSY;

		err = nfp_net_bpf_offload_prepare(nn, cls_bpf, &res, &code,
						  &dma_addr, max_instr);
		if (err)
			return err;

		nfp_net_bpf_load_and_start(nn, cls_bpf->gen_flags, code,
					   dma_addr, max_instr * sizeof(u64),
					   res.n_instr, res.dense_mode);
		return 0;

	case TC_CLSBPF_DESTROY:
		return nfp_net_bpf_stop(nn);

	case TC_CLSBPF_STATS:
		return nfp_net_bpf_stats_update(nn, cls_bpf);

	default:
		return -EOPNOTSUPP;
	}
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
}
