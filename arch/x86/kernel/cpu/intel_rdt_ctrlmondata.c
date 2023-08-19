/*
 * Resource Director Technology(RDT)
 * - Cache Allocation code.
 *
 * Copyright (C) 2016 Intel Corporation
 *
 * Authors:
 *    Fenghua Yu <fenghua.yu@intel.com>
 *    Tony Luck <tony.luck@intel.com>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * More information about RDT be found in the Intel (R) x86 Architecture
 * Software Developer Manual June 2016, volume 3, section 17.17.
 */

#define pr_fmt(fmt)	KBUILD_MODNAME ": " fmt

<<<<<<< HEAD
#include <linux/cpu.h>
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
#include <linux/kernfs.h>
#include <linux/seq_file.h>
#include <linux/slab.h>
#include "intel_rdt.h"

/*
 * Check whether MBA bandwidth percentage value is correct. The value is
 * checked against the minimum and max bandwidth values specified by the
 * hardware. The allocated bandwidth percentage is rounded to the next
 * control step available on the hardware.
 */
static bool bw_validate(char *buf, unsigned long *data, struct rdt_resource *r)
{
	unsigned long bw;
	int ret;

	/*
	 * Only linear delay values is supported for current Intel SKUs.
	 */
<<<<<<< HEAD
	if (!r->membw.delay_linear) {
		rdt_last_cmd_puts("No support for non-linear MB domains\n");
		return false;
	}

	ret = kstrtoul(buf, 10, &bw);
	if (ret) {
		rdt_last_cmd_printf("Non-decimal digit in MB value %s\n", buf);
		return false;
	}

	if ((bw < r->membw.min_bw || bw > r->default_ctrl) &&
	    !is_mba_sc(r)) {
		rdt_last_cmd_printf("MB value %ld out of range [%d,%d]\n", bw,
				    r->membw.min_bw, r->default_ctrl);
		return false;
	}
=======
	if (!r->membw.delay_linear)
		return false;

	ret = kstrtoul(buf, 10, &bw);
	if (ret)
		return false;

	if (bw < r->membw.min_bw || bw > r->default_ctrl)
		return false;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	*data = roundup(bw, (unsigned long)r->membw.bw_gran);
	return true;
}

<<<<<<< HEAD
int parse_bw(struct rdt_parse_data *data, struct rdt_resource *r,
	     struct rdt_domain *d)
{
	unsigned long bw_val;

	if (d->have_new_ctrl) {
		rdt_last_cmd_printf("duplicate domain %d\n", d->id);
		return -EINVAL;
	}

	if (!bw_validate(data->buf, &bw_val, r))
		return -EINVAL;
	d->new_ctrl = bw_val;
=======
int parse_bw(char *buf, struct rdt_resource *r, struct rdt_domain *d)
{
	unsigned long data;

	if (d->have_new_ctrl)
		return -EINVAL;

	if (!bw_validate(buf, &data, r))
		return -EINVAL;
	d->new_ctrl = data;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	d->have_new_ctrl = true;

	return 0;
}

/*
 * Check whether a cache bit mask is valid. The SDM says:
 *	Please note that all (and only) contiguous '1' combinations
 *	are allowed (e.g. FFFFH, 0FF0H, 003CH, etc.).
 * Additionally Haswell requires at least two bits set.
 */
<<<<<<< HEAD
static bool cbm_validate(char *buf, u32 *data, struct rdt_resource *r)
=======
static bool cbm_validate(char *buf, unsigned long *data, struct rdt_resource *r)
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
{
	unsigned long first_bit, zero_bit, val;
	unsigned int cbm_len = r->cache.cbm_len;
	int ret;

	ret = kstrtoul(buf, 16, &val);
<<<<<<< HEAD
	if (ret) {
		rdt_last_cmd_printf("non-hex character in mask %s\n", buf);
		return false;
	}

	if (val == 0 || val > r->default_ctrl) {
		rdt_last_cmd_puts("mask out of range\n");
		return false;
	}
=======
	if (ret)
		return false;

	if (val == 0 || val > r->default_ctrl)
		return false;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	first_bit = find_first_bit(&val, cbm_len);
	zero_bit = find_next_zero_bit(&val, cbm_len, first_bit);

<<<<<<< HEAD
	if (find_next_bit(&val, cbm_len, zero_bit) < cbm_len) {
		rdt_last_cmd_printf("mask %lx has non-consecutive 1-bits\n", val);
		return false;
	}

	if ((zero_bit - first_bit) < r->cache.min_cbm_bits) {
		rdt_last_cmd_printf("Need at least %d bits in mask\n",
				    r->cache.min_cbm_bits);
		return false;
	}
=======
	if (find_next_bit(&val, cbm_len, zero_bit) < cbm_len)
		return false;

	if ((zero_bit - first_bit) < r->cache.min_cbm_bits)
		return false;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	*data = val;
	return true;
}

/*
 * Read one cache bit mask (hex). Check that it is valid for the current
 * resource type.
 */
<<<<<<< HEAD
int parse_cbm(struct rdt_parse_data *data, struct rdt_resource *r,
	      struct rdt_domain *d)
{
	struct rdtgroup *rdtgrp = data->rdtgrp;
	u32 cbm_val;

	if (d->have_new_ctrl) {
		rdt_last_cmd_printf("duplicate domain %d\n", d->id);
		return -EINVAL;
	}

	/*
	 * Cannot set up more than one pseudo-locked region in a cache
	 * hierarchy.
	 */
	if (rdtgrp->mode == RDT_MODE_PSEUDO_LOCKSETUP &&
	    rdtgroup_pseudo_locked_in_hierarchy(d)) {
		rdt_last_cmd_printf("pseudo-locked region in hierarchy\n");
		return -EINVAL;
	}

	if (!cbm_validate(data->buf, &cbm_val, r))
		return -EINVAL;

	if ((rdtgrp->mode == RDT_MODE_EXCLUSIVE ||
	     rdtgrp->mode == RDT_MODE_SHAREABLE) &&
	    rdtgroup_cbm_overlaps_pseudo_locked(d, cbm_val)) {
		rdt_last_cmd_printf("CBM overlaps with pseudo-locked region\n");
		return -EINVAL;
	}

	/*
	 * The CBM may not overlap with the CBM of another closid if
	 * either is exclusive.
	 */
	if (rdtgroup_cbm_overlaps(r, d, cbm_val, rdtgrp->closid, true)) {
		rdt_last_cmd_printf("overlaps with exclusive group\n");
		return -EINVAL;
	}

	if (rdtgroup_cbm_overlaps(r, d, cbm_val, rdtgrp->closid, false)) {
		if (rdtgrp->mode == RDT_MODE_EXCLUSIVE ||
		    rdtgrp->mode == RDT_MODE_PSEUDO_LOCKSETUP) {
			rdt_last_cmd_printf("overlaps with other group\n");
			return -EINVAL;
		}
	}

	d->new_ctrl = cbm_val;
=======
int parse_cbm(char *buf, struct rdt_resource *r, struct rdt_domain *d)
{
	unsigned long data;

	if (d->have_new_ctrl)
		return -EINVAL;

	if(!cbm_validate(buf, &data, r))
		return -EINVAL;
	d->new_ctrl = data;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	d->have_new_ctrl = true;

	return 0;
}

/*
 * For each domain in this resource we expect to find a series of:
 *	id=mask
 * separated by ";". The "id" is in decimal, and must match one of
 * the "id"s for this resource.
 */
<<<<<<< HEAD
static int parse_line(char *line, struct rdt_resource *r,
		      struct rdtgroup *rdtgrp)
{
	struct rdt_parse_data data;
=======
static int parse_line(char *line, struct rdt_resource *r)
{
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	char *dom = NULL, *id;
	struct rdt_domain *d;
	unsigned long dom_id;

<<<<<<< HEAD
	if (rdtgrp->mode == RDT_MODE_PSEUDO_LOCKSETUP &&
	    r->rid == RDT_RESOURCE_MBA) {
		rdt_last_cmd_puts("Cannot pseudo-lock MBA resource\n");
		return -EINVAL;
	}

=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
next:
	if (!line || line[0] == '\0')
		return 0;
	dom = strsep(&line, ";");
	id = strsep(&dom, "=");
<<<<<<< HEAD
	if (!dom || kstrtoul(id, 10, &dom_id)) {
		rdt_last_cmd_puts("Missing '=' or non-numeric domain\n");
		return -EINVAL;
	}
	dom = strim(dom);
	list_for_each_entry(d, &r->domains, list) {
		if (d->id == dom_id) {
			data.buf = dom;
			data.rdtgrp = rdtgrp;
			if (r->parse_ctrlval(&data, r, d))
				return -EINVAL;
			if (rdtgrp->mode ==  RDT_MODE_PSEUDO_LOCKSETUP) {
				/*
				 * In pseudo-locking setup mode and just
				 * parsed a valid CBM that should be
				 * pseudo-locked. Only one locked region per
				 * resource group and domain so just do
				 * the required initialization for single
				 * region and return.
				 */
				rdtgrp->plr->r = r;
				rdtgrp->plr->d = d;
				rdtgrp->plr->cbm = d->new_ctrl;
				d->plr = rdtgrp->plr;
				return 0;
			}
=======
	if (!dom || kstrtoul(id, 10, &dom_id))
		return -EINVAL;
	dom = strim(dom);
	list_for_each_entry(d, &r->domains, list) {
		if (d->id == dom_id) {
			if (r->parse_ctrlval(dom, r, d))
				return -EINVAL;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
			goto next;
		}
	}
	return -EINVAL;
}

<<<<<<< HEAD
int update_domains(struct rdt_resource *r, int closid)
=======
static int update_domains(struct rdt_resource *r, int closid)
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
{
	struct msr_param msr_param;
	cpumask_var_t cpu_mask;
	struct rdt_domain *d;
<<<<<<< HEAD
	bool mba_sc;
	u32 *dc;
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	int cpu;

	if (!zalloc_cpumask_var(&cpu_mask, GFP_KERNEL))
		return -ENOMEM;

	msr_param.low = closid;
	msr_param.high = msr_param.low + 1;
	msr_param.res = r;

<<<<<<< HEAD
	mba_sc = is_mba_sc(r);
	list_for_each_entry(d, &r->domains, list) {
		dc = !mba_sc ? d->ctrl_val : d->mbps_val;
		if (d->have_new_ctrl && d->new_ctrl != dc[closid]) {
			cpumask_set_cpu(cpumask_any(&d->cpu_mask), cpu_mask);
			dc[closid] = d->new_ctrl;
		}
	}

	/*
	 * Avoid writing the control msr with control values when
	 * MBA software controller is enabled
	 */
	if (cpumask_empty(cpu_mask) || mba_sc)
=======
	list_for_each_entry(d, &r->domains, list) {
		if (d->have_new_ctrl && d->new_ctrl != d->ctrl_val[closid]) {
			cpumask_set_cpu(cpumask_any(&d->cpu_mask), cpu_mask);
			d->ctrl_val[closid] = d->new_ctrl;
		}
	}
	if (cpumask_empty(cpu_mask))
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
		goto done;
	cpu = get_cpu();
	/* Update CBM on this cpu if it's in cpu_mask. */
	if (cpumask_test_cpu(cpu, cpu_mask))
		rdt_ctrl_update(&msr_param);
	/* Update CBM on other cpus. */
	smp_call_function_many(cpu_mask, rdt_ctrl_update, &msr_param, 1);
	put_cpu();

done:
	free_cpumask_var(cpu_mask);

	return 0;
}

<<<<<<< HEAD
static int rdtgroup_parse_resource(char *resname, char *tok,
				   struct rdtgroup *rdtgrp)
=======
static int rdtgroup_parse_resource(char *resname, char *tok, int closid)
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
{
	struct rdt_resource *r;

	for_each_alloc_enabled_rdt_resource(r) {
<<<<<<< HEAD
		if (!strcmp(resname, r->name) && rdtgrp->closid < r->num_closid)
			return parse_line(tok, r, rdtgrp);
	}
	rdt_last_cmd_printf("unknown/unsupported resource name '%s'\n", resname);
=======
		if (!strcmp(resname, r->name) && closid < r->num_closid)
			return parse_line(tok, r);
	}
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	return -EINVAL;
}

ssize_t rdtgroup_schemata_write(struct kernfs_open_file *of,
				char *buf, size_t nbytes, loff_t off)
{
	struct rdtgroup *rdtgrp;
	struct rdt_domain *dom;
	struct rdt_resource *r;
	char *tok, *resname;
<<<<<<< HEAD
	int ret = 0;
=======
	int closid, ret = 0;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	/* Valid input requires a trailing newline */
	if (nbytes == 0 || buf[nbytes - 1] != '\n')
		return -EINVAL;
	buf[nbytes - 1] = '\0';

<<<<<<< HEAD
	cpus_read_lock();
	rdtgrp = rdtgroup_kn_lock_live(of->kn);
	if (!rdtgrp) {
		rdtgroup_kn_unlock(of->kn);
		cpus_read_unlock();
		return -ENOENT;
	}
	rdt_last_cmd_clear();

	/*
	 * No changes to pseudo-locked region allowed. It has to be removed
	 * and re-created instead.
	 */
	if (rdtgrp->mode == RDT_MODE_PSEUDO_LOCKED) {
		ret = -EINVAL;
		rdt_last_cmd_puts("resource group is pseudo-locked\n");
		goto out;
	}
=======
	rdtgrp = rdtgroup_kn_lock_live(of->kn);
	if (!rdtgrp) {
		rdtgroup_kn_unlock(of->kn);
		return -ENOENT;
	}

	closid = rdtgrp->closid;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	for_each_alloc_enabled_rdt_resource(r) {
		list_for_each_entry(dom, &r->domains, list)
			dom->have_new_ctrl = false;
	}

	while ((tok = strsep(&buf, "\n")) != NULL) {
		resname = strim(strsep(&tok, ":"));
		if (!tok) {
<<<<<<< HEAD
			rdt_last_cmd_puts("Missing ':'\n");
			ret = -EINVAL;
			goto out;
		}
		if (tok[0] == '\0') {
			rdt_last_cmd_printf("Missing '%s' value\n", resname);
			ret = -EINVAL;
			goto out;
		}
		ret = rdtgroup_parse_resource(resname, tok, rdtgrp);
=======
			ret = -EINVAL;
			goto out;
		}
		ret = rdtgroup_parse_resource(resname, tok, closid);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
		if (ret)
			goto out;
	}

	for_each_alloc_enabled_rdt_resource(r) {
<<<<<<< HEAD
		ret = update_domains(r, rdtgrp->closid);
=======
		ret = update_domains(r, closid);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
		if (ret)
			goto out;
	}

<<<<<<< HEAD
	if (rdtgrp->mode == RDT_MODE_PSEUDO_LOCKSETUP) {
		/*
		 * If pseudo-locking fails we keep the resource group in
		 * mode RDT_MODE_PSEUDO_LOCKSETUP with its class of service
		 * active and updated for just the domain the pseudo-locked
		 * region was requested for.
		 */
		ret = rdtgroup_pseudo_lock_create(rdtgrp);
	}

out:
	rdtgroup_kn_unlock(of->kn);
	cpus_read_unlock();
=======
out:
	rdtgroup_kn_unlock(of->kn);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	return ret ?: nbytes;
}

static void show_doms(struct seq_file *s, struct rdt_resource *r, int closid)
{
	struct rdt_domain *dom;
	bool sep = false;
<<<<<<< HEAD
	u32 ctrl_val;
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	seq_printf(s, "%*s:", max_name_width, r->name);
	list_for_each_entry(dom, &r->domains, list) {
		if (sep)
			seq_puts(s, ";");
<<<<<<< HEAD

		ctrl_val = (!is_mba_sc(r) ? dom->ctrl_val[closid] :
			    dom->mbps_val[closid]);
		seq_printf(s, r->format_str, dom->id, max_data_width,
			   ctrl_val);
=======
		seq_printf(s, r->format_str, dom->id, max_data_width,
			   dom->ctrl_val[closid]);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
		sep = true;
	}
	seq_puts(s, "\n");
}

int rdtgroup_schemata_show(struct kernfs_open_file *of,
			   struct seq_file *s, void *v)
{
	struct rdtgroup *rdtgrp;
	struct rdt_resource *r;
	int ret = 0;
	u32 closid;

	rdtgrp = rdtgroup_kn_lock_live(of->kn);
	if (rdtgrp) {
<<<<<<< HEAD
		if (rdtgrp->mode == RDT_MODE_PSEUDO_LOCKSETUP) {
			for_each_alloc_enabled_rdt_resource(r)
				seq_printf(s, "%s:uninitialized\n", r->name);
		} else if (rdtgrp->mode == RDT_MODE_PSEUDO_LOCKED) {
			seq_printf(s, "%s:%d=%x\n", rdtgrp->plr->r->name,
				   rdtgrp->plr->d->id, rdtgrp->plr->cbm);
		} else {
			closid = rdtgrp->closid;
			for_each_alloc_enabled_rdt_resource(r) {
				if (closid < r->num_closid)
					show_doms(s, r, closid);
			}
=======
		closid = rdtgrp->closid;
		for_each_alloc_enabled_rdt_resource(r) {
			if (closid < r->num_closid)
				show_doms(s, r, closid);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
		}
	} else {
		ret = -ENOENT;
	}
	rdtgroup_kn_unlock(of->kn);
	return ret;
}

void mon_event_read(struct rmid_read *rr, struct rdt_domain *d,
		    struct rdtgroup *rdtgrp, int evtid, int first)
{
	/*
	 * setup the parameters to send to the IPI to read the data.
	 */
	rr->rgrp = rdtgrp;
	rr->evtid = evtid;
	rr->d = d;
	rr->val = 0;
	rr->first = first;

	smp_call_function_any(&d->cpu_mask, mon_event_count, rr, 1);
}

int rdtgroup_mondata_show(struct seq_file *m, void *arg)
{
	struct kernfs_open_file *of = m->private;
	u32 resid, evtid, domid;
	struct rdtgroup *rdtgrp;
	struct rdt_resource *r;
	union mon_data_bits md;
	struct rdt_domain *d;
	struct rmid_read rr;
	int ret = 0;

	rdtgrp = rdtgroup_kn_lock_live(of->kn);
<<<<<<< HEAD
=======
	if (!rdtgrp) {
		ret = -ENOENT;
		goto out;
	}
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	md.priv = of->kn->priv;
	resid = md.u.rid;
	domid = md.u.domid;
	evtid = md.u.evtid;

	r = &rdt_resources_all[resid];
	d = rdt_find_domain(r, domid, NULL);
	if (!d) {
		ret = -ENOENT;
		goto out;
	}

	mon_event_read(&rr, d, rdtgrp, evtid, false);

	if (rr.val & RMID_VAL_ERROR)
		seq_puts(m, "Error\n");
	else if (rr.val & RMID_VAL_UNAVAIL)
		seq_puts(m, "Unavailable\n");
	else
		seq_printf(m, "%llu\n", rr.val * r->mon_scale);

out:
	rdtgroup_kn_unlock(of->kn);
	return ret;
}
