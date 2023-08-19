/*
 *  Bluetooth support for Realtek devices
 *
 *  Copyright (C) 2015 Endless Mobile, Inc.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 */

#include <linux/module.h>
#include <linux/firmware.h>
#include <asm/unaligned.h>
#include <linux/usb.h>

#include <net/bluetooth/bluetooth.h>
#include <net/bluetooth/hci_core.h>

#include "btrtl.h"

#define VERSION "0.1"

#define RTL_EPATCH_SIGNATURE	"Realtech"
#define RTL_ROM_LMP_3499	0x3499
#define RTL_ROM_LMP_8723A	0x1200
#define RTL_ROM_LMP_8723B	0x8723
#define RTL_ROM_LMP_8821A	0x8821
#define RTL_ROM_LMP_8761A	0x8761
#define RTL_ROM_LMP_8822B	0x8822
<<<<<<< HEAD
#define RTL_CONFIG_MAGIC	0x8723ab55

#define IC_MATCH_FL_LMPSUBV	(1 << 0)
#define IC_MATCH_FL_HCIREV	(1 << 1)
#define IC_MATCH_FL_HCIVER	(1 << 2)
#define IC_MATCH_FL_HCIBUS	(1 << 3)
#define IC_INFO(lmps, hcir) \
	.match_flags = IC_MATCH_FL_LMPSUBV | IC_MATCH_FL_HCIREV, \
	.lmp_subver = (lmps), \
	.hci_rev = (hcir)

struct id_table {
	__u16 match_flags;
	__u16 lmp_subver;
	__u16 hci_rev;
	__u8 hci_ver;
	__u8 hci_bus;
	bool config_needed;
	bool has_rom_version;
	char *fw_name;
	char *cfg_name;
};

struct btrtl_device_info {
	const struct id_table *ic_info;
	u8 rom_version;
	u8 *fw_data;
	int fw_len;
	u8 *cfg_data;
	int cfg_len;
};

static const struct id_table ic_id_table[] = {
	{ IC_MATCH_FL_LMPSUBV, RTL_ROM_LMP_8723A, 0x0,
	  .config_needed = false,
	  .has_rom_version = false,
	  .fw_name = "rtl_bt/rtl8723a_fw.bin",
	  .cfg_name = NULL },

	{ IC_MATCH_FL_LMPSUBV, RTL_ROM_LMP_3499, 0x0,
	  .config_needed = false,
	  .has_rom_version = false,
	  .fw_name = "rtl_bt/rtl8723a_fw.bin",
	  .cfg_name = NULL },

	/* 8723BS */
	{ .match_flags = IC_MATCH_FL_LMPSUBV | IC_MATCH_FL_HCIREV |
			 IC_MATCH_FL_HCIVER | IC_MATCH_FL_HCIBUS,
	  .lmp_subver = RTL_ROM_LMP_8723B,
	  .hci_rev = 0xb,
	  .hci_ver = 6,
	  .hci_bus = HCI_UART,
	  .config_needed = true,
	  .has_rom_version = true,
	  .fw_name  = "rtl_bt/rtl8723bs_fw.bin",
	  .cfg_name = "rtl_bt/rtl8723bs_config" },

	/* 8723B */
	{ IC_INFO(RTL_ROM_LMP_8723B, 0xb),
	  .config_needed = false,
	  .has_rom_version = true,
	  .fw_name  = "rtl_bt/rtl8723b_fw.bin",
	  .cfg_name = "rtl_bt/rtl8723b_config" },

	/* 8723D */
	{ IC_INFO(RTL_ROM_LMP_8723B, 0xd),
	  .config_needed = true,
	  .has_rom_version = true,
	  .fw_name  = "rtl_bt/rtl8723d_fw.bin",
	  .cfg_name = "rtl_bt/rtl8723d_config" },

	/* 8723DS */
	{ .match_flags = IC_MATCH_FL_LMPSUBV | IC_MATCH_FL_HCIREV |
			 IC_MATCH_FL_HCIVER | IC_MATCH_FL_HCIBUS,
	  .lmp_subver = RTL_ROM_LMP_8723B,
	  .hci_rev = 0xd,
	  .hci_ver = 8,
	  .hci_bus = HCI_UART,
	  .config_needed = true,
	  .has_rom_version = true,
	  .fw_name  = "rtl_bt/rtl8723ds_fw.bin",
	  .cfg_name = "rtl_bt/rtl8723ds_config" },

	/* 8821A */
	{ IC_INFO(RTL_ROM_LMP_8821A, 0xa),
	  .config_needed = false,
	  .has_rom_version = true,
	  .fw_name  = "rtl_bt/rtl8821a_fw.bin",
	  .cfg_name = "rtl_bt/rtl8821a_config" },

	/* 8821C */
	{ IC_INFO(RTL_ROM_LMP_8821A, 0xc),
	  .config_needed = false,
	  .has_rom_version = true,
	  .fw_name  = "rtl_bt/rtl8821c_fw.bin",
	  .cfg_name = "rtl_bt/rtl8821c_config" },

	/* 8761A */
	{ IC_MATCH_FL_LMPSUBV, RTL_ROM_LMP_8761A, 0x0,
	  .config_needed = false,
	  .has_rom_version = true,
	  .fw_name  = "rtl_bt/rtl8761a_fw.bin",
	  .cfg_name = "rtl_bt/rtl8761a_config" },

	/* 8822B */
	{ IC_INFO(RTL_ROM_LMP_8822B, 0xb),
	  .config_needed = true,
	  .has_rom_version = true,
	  .fw_name  = "rtl_bt/rtl8822b_fw.bin",
	  .cfg_name = "rtl_bt/rtl8822b_config" },
	};

static const struct id_table *btrtl_match_ic(u16 lmp_subver, u16 hci_rev,
					     u8 hci_ver, u8 hci_bus)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(ic_id_table); i++) {
		if ((ic_id_table[i].match_flags & IC_MATCH_FL_LMPSUBV) &&
		    (ic_id_table[i].lmp_subver != lmp_subver))
			continue;
		if ((ic_id_table[i].match_flags & IC_MATCH_FL_HCIREV) &&
		    (ic_id_table[i].hci_rev != hci_rev))
			continue;
		if ((ic_id_table[i].match_flags & IC_MATCH_FL_HCIVER) &&
		    (ic_id_table[i].hci_ver != hci_ver))
			continue;
		if ((ic_id_table[i].match_flags & IC_MATCH_FL_HCIBUS) &&
		    (ic_id_table[i].hci_bus != hci_bus))
			continue;

		break;
	}
	if (i >= ARRAY_SIZE(ic_id_table))
		return NULL;

	return &ic_id_table[i];
}
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

static int rtl_read_rom_version(struct hci_dev *hdev, u8 *version)
{
	struct rtl_rom_version_evt *rom_version;
	struct sk_buff *skb;

	/* Read RTL ROM version command */
	skb = __hci_cmd_sync(hdev, 0xfc6d, 0, NULL, HCI_INIT_TIMEOUT);
	if (IS_ERR(skb)) {
<<<<<<< HEAD
		rtl_dev_err(hdev, "Read ROM version failed (%ld)\n",
			    PTR_ERR(skb));
=======
		BT_ERR("%s: Read ROM version failed (%ld)",
		       hdev->name, PTR_ERR(skb));
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
		return PTR_ERR(skb);
	}

	if (skb->len != sizeof(*rom_version)) {
<<<<<<< HEAD
		rtl_dev_err(hdev, "RTL version event length mismatch\n");
=======
		BT_ERR("%s: RTL version event length mismatch", hdev->name);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
		kfree_skb(skb);
		return -EIO;
	}

	rom_version = (struct rtl_rom_version_evt *)skb->data;
<<<<<<< HEAD
	rtl_dev_info(hdev, "rom_version status=%x version=%x\n",
		     rom_version->status, rom_version->version);
=======
	BT_INFO("%s: rom_version status=%x version=%x",
		hdev->name, rom_version->status, rom_version->version);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	*version = rom_version->version;

	kfree_skb(skb);
	return 0;
}

<<<<<<< HEAD
static int rtlbt_parse_firmware(struct hci_dev *hdev,
				struct btrtl_device_info *btrtl_dev,
				unsigned char **_buf)
=======
static int rtl8723b_parse_firmware(struct hci_dev *hdev, u16 lmp_subver,
				   const struct firmware *fw,
				   unsigned char **_buf)
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
{
	const u8 extension_sig[] = { 0x51, 0x04, 0xfd, 0x77 };
	struct rtl_epatch_header *epatch_info;
	unsigned char *buf;
<<<<<<< HEAD
	int i, len;
	size_t min_size;
	u8 opcode, length, data;
=======
	int i, ret, len;
	size_t min_size;
	u8 opcode, length, data, rom_version = 0;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	int project_id = -1;
	const unsigned char *fwptr, *chip_id_base;
	const unsigned char *patch_length_base, *patch_offset_base;
	u32 patch_offset = 0;
	u16 patch_length, num_patches;
	static const struct {
		__u16 lmp_subver;
		__u8 id;
	} project_id_to_lmp_subver[] = {
		{ RTL_ROM_LMP_8723A, 0 },
		{ RTL_ROM_LMP_8723B, 1 },
		{ RTL_ROM_LMP_8821A, 2 },
		{ RTL_ROM_LMP_8761A, 3 },
		{ RTL_ROM_LMP_8822B, 8 },
<<<<<<< HEAD
		{ RTL_ROM_LMP_8723B, 9 },	/* 8723D */
		{ RTL_ROM_LMP_8821A, 10 },	/* 8821C */
	};

	min_size = sizeof(struct rtl_epatch_header) + sizeof(extension_sig) + 3;
	if (btrtl_dev->fw_len < min_size)
		return -EINVAL;

	fwptr = btrtl_dev->fw_data + btrtl_dev->fw_len - sizeof(extension_sig);
	if (memcmp(fwptr, extension_sig, sizeof(extension_sig)) != 0) {
		rtl_dev_err(hdev, "extension section signature mismatch\n");
=======
	};

	ret = rtl_read_rom_version(hdev, &rom_version);
	if (ret)
		return ret;

	min_size = sizeof(struct rtl_epatch_header) + sizeof(extension_sig) + 3;
	if (fw->size < min_size)
		return -EINVAL;

	fwptr = fw->data + fw->size - sizeof(extension_sig);
	if (memcmp(fwptr, extension_sig, sizeof(extension_sig)) != 0) {
		BT_ERR("%s: extension section signature mismatch", hdev->name);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
		return -EINVAL;
	}

	/* Loop from the end of the firmware parsing instructions, until
	 * we find an instruction that identifies the "project ID" for the
	 * hardware supported by this firwmare file.
	 * Once we have that, we double-check that that project_id is suitable
	 * for the hardware we are working with.
	 */
<<<<<<< HEAD
	while (fwptr >= btrtl_dev->fw_data + (sizeof(*epatch_info) + 3)) {
=======
	while (fwptr >= fw->data + (sizeof(struct rtl_epatch_header) + 3)) {
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
		opcode = *--fwptr;
		length = *--fwptr;
		data = *--fwptr;

		BT_DBG("check op=%x len=%x data=%x", opcode, length, data);

		if (opcode == 0xff) /* EOF */
			break;

		if (length == 0) {
<<<<<<< HEAD
			rtl_dev_err(hdev, "found instruction with length 0\n");
=======
			BT_ERR("%s: found instruction with length 0",
			       hdev->name);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
			return -EINVAL;
		}

		if (opcode == 0 && length == 1) {
			project_id = data;
			break;
		}

		fwptr -= length;
	}

	if (project_id < 0) {
<<<<<<< HEAD
		rtl_dev_err(hdev, "failed to find version instruction\n");
=======
		BT_ERR("%s: failed to find version instruction", hdev->name);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
		return -EINVAL;
	}

	/* Find project_id in table */
	for (i = 0; i < ARRAY_SIZE(project_id_to_lmp_subver); i++) {
		if (project_id == project_id_to_lmp_subver[i].id)
			break;
	}

	if (i >= ARRAY_SIZE(project_id_to_lmp_subver)) {
<<<<<<< HEAD
		rtl_dev_err(hdev, "unknown project id %d\n", project_id);
		return -EINVAL;
	}

	if (btrtl_dev->ic_info->lmp_subver !=
				project_id_to_lmp_subver[i].lmp_subver) {
		rtl_dev_err(hdev, "firmware is for %x but this is a %x\n",
			    project_id_to_lmp_subver[i].lmp_subver,
			    btrtl_dev->ic_info->lmp_subver);
		return -EINVAL;
	}

	epatch_info = (struct rtl_epatch_header *)btrtl_dev->fw_data;
	if (memcmp(epatch_info->signature, RTL_EPATCH_SIGNATURE, 8) != 0) {
		rtl_dev_err(hdev, "bad EPATCH signature\n");
=======
		BT_ERR("%s: unknown project id %d", hdev->name, project_id);
		return -EINVAL;
	}

	if (lmp_subver != project_id_to_lmp_subver[i].lmp_subver) {
		BT_ERR("%s: firmware is for %x but this is a %x", hdev->name,
		       project_id_to_lmp_subver[i].lmp_subver, lmp_subver);
		return -EINVAL;
	}

	epatch_info = (struct rtl_epatch_header *)fw->data;
	if (memcmp(epatch_info->signature, RTL_EPATCH_SIGNATURE, 8) != 0) {
		BT_ERR("%s: bad EPATCH signature", hdev->name);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
		return -EINVAL;
	}

	num_patches = le16_to_cpu(epatch_info->num_patches);
	BT_DBG("fw_version=%x, num_patches=%d",
	       le32_to_cpu(epatch_info->fw_version), num_patches);

	/* After the rtl_epatch_header there is a funky patch metadata section.
	 * Assuming 2 patches, the layout is:
	 * ChipID1 ChipID2 PatchLength1 PatchLength2 PatchOffset1 PatchOffset2
	 *
	 * Find the right patch for this chip.
	 */
	min_size += 8 * num_patches;
<<<<<<< HEAD
	if (btrtl_dev->fw_len < min_size)
		return -EINVAL;

	chip_id_base = btrtl_dev->fw_data + sizeof(struct rtl_epatch_header);
=======
	if (fw->size < min_size)
		return -EINVAL;

	chip_id_base = fw->data + sizeof(struct rtl_epatch_header);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	patch_length_base = chip_id_base + (sizeof(u16) * num_patches);
	patch_offset_base = patch_length_base + (sizeof(u16) * num_patches);
	for (i = 0; i < num_patches; i++) {
		u16 chip_id = get_unaligned_le16(chip_id_base +
						 (i * sizeof(u16)));
<<<<<<< HEAD
		if (chip_id == btrtl_dev->rom_version + 1) {
=======
		if (chip_id == rom_version + 1) {
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
			patch_length = get_unaligned_le16(patch_length_base +
							  (i * sizeof(u16)));
			patch_offset = get_unaligned_le32(patch_offset_base +
							  (i * sizeof(u32)));
			break;
		}
	}

	if (!patch_offset) {
<<<<<<< HEAD
		rtl_dev_err(hdev, "didn't find patch for chip id %d",
			    btrtl_dev->rom_version);
=======
		BT_ERR("%s: didn't find patch for chip id %d",
		       hdev->name, rom_version);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
		return -EINVAL;
	}

	BT_DBG("length=%x offset=%x index %d", patch_length, patch_offset, i);
	min_size = patch_offset + patch_length;
<<<<<<< HEAD
	if (btrtl_dev->fw_len < min_size)
=======
	if (fw->size < min_size)
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
		return -EINVAL;

	/* Copy the firmware into a new buffer and write the version at
	 * the end.
	 */
	len = patch_length;
<<<<<<< HEAD
	buf = kmemdup(btrtl_dev->fw_data + patch_offset, patch_length,
		      GFP_KERNEL);
=======
	buf = kmemdup(fw->data + patch_offset, patch_length, GFP_KERNEL);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	if (!buf)
		return -ENOMEM;

	memcpy(buf + patch_length - 4, &epatch_info->fw_version, 4);

	*_buf = buf;
	return len;
}

static int rtl_download_firmware(struct hci_dev *hdev,
				 const unsigned char *data, int fw_len)
{
	struct rtl_download_cmd *dl_cmd;
	int frag_num = fw_len / RTL_FRAG_LEN + 1;
	int frag_len = RTL_FRAG_LEN;
	int ret = 0;
	int i;

	dl_cmd = kmalloc(sizeof(struct rtl_download_cmd), GFP_KERNEL);
	if (!dl_cmd)
		return -ENOMEM;

	for (i = 0; i < frag_num; i++) {
		struct sk_buff *skb;

		BT_DBG("download fw (%d/%d)", i, frag_num);

		dl_cmd->index = i;
		if (i == (frag_num - 1)) {
			dl_cmd->index |= 0x80; /* data end */
			frag_len = fw_len % RTL_FRAG_LEN;
		}
		memcpy(dl_cmd->data, data, frag_len);

		/* Send download command */
		skb = __hci_cmd_sync(hdev, 0xfc20, frag_len + 1, dl_cmd,
				     HCI_INIT_TIMEOUT);
		if (IS_ERR(skb)) {
<<<<<<< HEAD
			rtl_dev_err(hdev, "download fw command failed (%ld)\n",
				    PTR_ERR(skb));
=======
			BT_ERR("%s: download fw command failed (%ld)",
			       hdev->name, PTR_ERR(skb));
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
			ret = -PTR_ERR(skb);
			goto out;
		}

		if (skb->len != sizeof(struct rtl_download_response)) {
<<<<<<< HEAD
			rtl_dev_err(hdev, "download fw event length mismatch\n");
=======
			BT_ERR("%s: download fw event length mismatch",
			       hdev->name);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
			kfree_skb(skb);
			ret = -EIO;
			goto out;
		}

		kfree_skb(skb);
		data += RTL_FRAG_LEN;
	}

out:
	kfree(dl_cmd);
	return ret;
}

<<<<<<< HEAD
static int rtl_load_file(struct hci_dev *hdev, const char *name, u8 **buff)
=======
static int rtl_load_config(struct hci_dev *hdev, const char *name, u8 **buff)
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
{
	const struct firmware *fw;
	int ret;

<<<<<<< HEAD
	rtl_dev_info(hdev, "rtl: loading %s\n", name);
=======
	BT_INFO("%s: rtl: loading %s", hdev->name, name);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	ret = request_firmware(&fw, name, &hdev->dev);
	if (ret < 0)
		return ret;
	ret = fw->size;
	*buff = kmemdup(fw->data, ret, GFP_KERNEL);
	if (!*buff)
		ret = -ENOMEM;

	release_firmware(fw);

	return ret;
}

<<<<<<< HEAD
static int btrtl_setup_rtl8723a(struct hci_dev *hdev,
				struct btrtl_device_info *btrtl_dev)
{
	if (btrtl_dev->fw_len < 8)
		return -EINVAL;
=======
static int btrtl_setup_rtl8723a(struct hci_dev *hdev)
{
	const struct firmware *fw;
	int ret;

	BT_INFO("%s: rtl: loading rtl_bt/rtl8723a_fw.bin", hdev->name);
	ret = request_firmware(&fw, "rtl_bt/rtl8723a_fw.bin", &hdev->dev);
	if (ret < 0) {
		BT_ERR("%s: Failed to load rtl_bt/rtl8723a_fw.bin", hdev->name);
		return ret;
	}

	if (fw->size < 8) {
		ret = -EINVAL;
		goto out;
	}
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	/* Check that the firmware doesn't have the epatch signature
	 * (which is only for RTL8723B and newer).
	 */
<<<<<<< HEAD
	if (!memcmp(btrtl_dev->fw_data, RTL_EPATCH_SIGNATURE, 8)) {
		rtl_dev_err(hdev, "unexpected EPATCH signature!\n");
		return -EINVAL;
	}

	return rtl_download_firmware(hdev, btrtl_dev->fw_data,
				     btrtl_dev->fw_len);
}

static int btrtl_setup_rtl8723b(struct hci_dev *hdev,
				struct btrtl_device_info *btrtl_dev)
{
	unsigned char *fw_data = NULL;
	int ret;
	u8 *tbuff;

	ret = rtlbt_parse_firmware(hdev, btrtl_dev, &fw_data);
	if (ret < 0)
		goto out;

	if (btrtl_dev->cfg_len > 0) {
		tbuff = kzalloc(ret + btrtl_dev->cfg_len, GFP_KERNEL);
=======
	if (!memcmp(fw->data, RTL_EPATCH_SIGNATURE, 8)) {
		BT_ERR("%s: unexpected EPATCH signature!", hdev->name);
		ret = -EINVAL;
		goto out;
	}

	ret = rtl_download_firmware(hdev, fw->data, fw->size);

out:
	release_firmware(fw);
	return ret;
}

static int btrtl_setup_rtl8723b(struct hci_dev *hdev, u16 lmp_subver,
				const char *fw_name)
{
	unsigned char *fw_data = NULL;
	const struct firmware *fw;
	int ret;
	int cfg_sz;
	u8 *cfg_buff = NULL;
	u8 *tbuff;
	char *cfg_name = NULL;
	bool config_needed = false;

	switch (lmp_subver) {
	case RTL_ROM_LMP_8723B:
		cfg_name = "rtl_bt/rtl8723b_config.bin";
		break;
	case RTL_ROM_LMP_8821A:
		cfg_name = "rtl_bt/rtl8821a_config.bin";
		break;
	case RTL_ROM_LMP_8761A:
		cfg_name = "rtl_bt/rtl8761a_config.bin";
		break;
	case RTL_ROM_LMP_8822B:
		cfg_name = "rtl_bt/rtl8822b_config.bin";
		config_needed = true;
		break;
	default:
		BT_ERR("%s: rtl: no config according to lmp_subver %04x",
		       hdev->name, lmp_subver);
		break;
	}

	if (cfg_name) {
		cfg_sz = rtl_load_config(hdev, cfg_name, &cfg_buff);
		if (cfg_sz < 0) {
			cfg_sz = 0;
			if (config_needed)
				BT_ERR("Necessary config file %s not found\n",
				       cfg_name);
		}
	} else
		cfg_sz = 0;

	BT_INFO("%s: rtl: loading %s", hdev->name, fw_name);
	ret = request_firmware(&fw, fw_name, &hdev->dev);
	if (ret < 0) {
		BT_ERR("%s: Failed to load %s", hdev->name, fw_name);
		goto err_req_fw;
	}

	ret = rtl8723b_parse_firmware(hdev, lmp_subver, fw, &fw_data);
	if (ret < 0)
		goto out;

	if (cfg_sz) {
		tbuff = kzalloc(ret + cfg_sz, GFP_KERNEL);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
		if (!tbuff) {
			ret = -ENOMEM;
			goto out;
		}

		memcpy(tbuff, fw_data, ret);
		kfree(fw_data);

<<<<<<< HEAD
		memcpy(tbuff + ret, btrtl_dev->cfg_data, btrtl_dev->cfg_len);
		ret += btrtl_dev->cfg_len;
=======
		memcpy(tbuff + ret, cfg_buff, cfg_sz);
		ret += cfg_sz;
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

		fw_data = tbuff;
	}

<<<<<<< HEAD
	rtl_dev_info(hdev, "cfg_sz %d, total sz %d\n", btrtl_dev->cfg_len, ret);
=======
	BT_INFO("cfg_sz %d, total size %d", cfg_sz, ret);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	ret = rtl_download_firmware(hdev, fw_data, ret);

out:
<<<<<<< HEAD
	kfree(fw_data);
=======
	release_firmware(fw);
	kfree(fw_data);
err_req_fw:
	if (cfg_sz)
		kfree(cfg_buff);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	return ret;
}

static struct sk_buff *btrtl_read_local_version(struct hci_dev *hdev)
{
	struct sk_buff *skb;

	skb = __hci_cmd_sync(hdev, HCI_OP_READ_LOCAL_VERSION, 0, NULL,
			     HCI_INIT_TIMEOUT);
	if (IS_ERR(skb)) {
<<<<<<< HEAD
		rtl_dev_err(hdev, "HCI_OP_READ_LOCAL_VERSION failed (%ld)\n",
			    PTR_ERR(skb));
=======
		BT_ERR("%s: HCI_OP_READ_LOCAL_VERSION failed (%ld)",
		       hdev->name, PTR_ERR(skb));
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
		return skb;
	}

	if (skb->len != sizeof(struct hci_rp_read_local_version)) {
<<<<<<< HEAD
		rtl_dev_err(hdev, "HCI_OP_READ_LOCAL_VERSION event length mismatch\n");
=======
		BT_ERR("%s: HCI_OP_READ_LOCAL_VERSION event length mismatch",
		       hdev->name);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
		kfree_skb(skb);
		return ERR_PTR(-EIO);
	}

	return skb;
}

<<<<<<< HEAD
void btrtl_free(struct btrtl_device_info *btrtl_dev)
{
	kfree(btrtl_dev->fw_data);
	kfree(btrtl_dev->cfg_data);
	kfree(btrtl_dev);
}
EXPORT_SYMBOL_GPL(btrtl_free);

struct btrtl_device_info *btrtl_initialize(struct hci_dev *hdev,
					   const char *postfix)
{
	struct btrtl_device_info *btrtl_dev;
	struct sk_buff *skb;
	struct hci_rp_read_local_version *resp;
	char cfg_name[40];
	u16 hci_rev, lmp_subver;
	u8 hci_ver;
	int ret;

	btrtl_dev = kzalloc(sizeof(*btrtl_dev), GFP_KERNEL);
	if (!btrtl_dev) {
		ret = -ENOMEM;
		goto err_alloc;
	}

	skb = btrtl_read_local_version(hdev);
	if (IS_ERR(skb)) {
		ret = PTR_ERR(skb);
		goto err_free;
	}

	resp = (struct hci_rp_read_local_version *)skb->data;
	rtl_dev_info(hdev, "rtl: examining hci_ver=%02x hci_rev=%04x lmp_ver=%02x lmp_subver=%04x\n",
		     resp->hci_ver, resp->hci_rev,
		     resp->lmp_ver, resp->lmp_subver);

	hci_ver = resp->hci_ver;
	hci_rev = le16_to_cpu(resp->hci_rev);
	lmp_subver = le16_to_cpu(resp->lmp_subver);
	kfree_skb(skb);

	btrtl_dev->ic_info = btrtl_match_ic(lmp_subver, hci_rev, hci_ver,
					    hdev->bus);

	if (!btrtl_dev->ic_info) {
		rtl_dev_info(hdev, "rtl: unknown IC info, lmp subver %04x, hci rev %04x, hci ver %04x",
			    lmp_subver, hci_rev, hci_ver);
		return btrtl_dev;
	}

	if (btrtl_dev->ic_info->has_rom_version) {
		ret = rtl_read_rom_version(hdev, &btrtl_dev->rom_version);
		if (ret)
			goto err_free;
	}

	btrtl_dev->fw_len = rtl_load_file(hdev, btrtl_dev->ic_info->fw_name,
					  &btrtl_dev->fw_data);
	if (btrtl_dev->fw_len < 0) {
		rtl_dev_err(hdev, "firmware file %s not found\n",
			    btrtl_dev->ic_info->fw_name);
		ret = btrtl_dev->fw_len;
		goto err_free;
	}

	if (btrtl_dev->ic_info->cfg_name) {
		if (postfix) {
			snprintf(cfg_name, sizeof(cfg_name), "%s-%s.bin",
				 btrtl_dev->ic_info->cfg_name, postfix);
		} else {
			snprintf(cfg_name, sizeof(cfg_name), "%s.bin",
				 btrtl_dev->ic_info->cfg_name);
		}
		btrtl_dev->cfg_len = rtl_load_file(hdev, cfg_name,
						   &btrtl_dev->cfg_data);
		if (btrtl_dev->ic_info->config_needed &&
		    btrtl_dev->cfg_len <= 0) {
			rtl_dev_err(hdev, "mandatory config file %s not found\n",
				    btrtl_dev->ic_info->cfg_name);
			ret = btrtl_dev->cfg_len;
			goto err_free;
		}
	}

	return btrtl_dev;

err_free:
	btrtl_free(btrtl_dev);
err_alloc:
	return ERR_PTR(ret);
}
EXPORT_SYMBOL_GPL(btrtl_initialize);

int btrtl_download_firmware(struct hci_dev *hdev,
			    struct btrtl_device_info *btrtl_dev)
{
=======
int btrtl_setup_realtek(struct hci_dev *hdev)
{
	struct sk_buff *skb;
	struct hci_rp_read_local_version *resp;
	u16 lmp_subver;

	skb = btrtl_read_local_version(hdev);
	if (IS_ERR(skb))
		return -PTR_ERR(skb);

	resp = (struct hci_rp_read_local_version *)skb->data;
	BT_INFO("%s: rtl: examining hci_ver=%02x hci_rev=%04x lmp_ver=%02x "
		"lmp_subver=%04x", hdev->name, resp->hci_ver, resp->hci_rev,
		resp->lmp_ver, resp->lmp_subver);

	lmp_subver = le16_to_cpu(resp->lmp_subver);
	kfree_skb(skb);

>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	/* Match a set of subver values that correspond to stock firmware,
	 * which is not compatible with standard btusb.
	 * If matched, upload an alternative firmware that does conform to
	 * standard btusb. Once that firmware is uploaded, the subver changes
	 * to a different value.
	 */
<<<<<<< HEAD
	if (!btrtl_dev->ic_info) {
		rtl_dev_info(hdev, "rtl: assuming no firmware upload needed\n");
		return 0;
	}

	switch (btrtl_dev->ic_info->lmp_subver) {
	case RTL_ROM_LMP_8723A:
	case RTL_ROM_LMP_3499:
		return btrtl_setup_rtl8723a(hdev, btrtl_dev);
	case RTL_ROM_LMP_8723B:
	case RTL_ROM_LMP_8821A:
	case RTL_ROM_LMP_8761A:
	case RTL_ROM_LMP_8822B:
		return btrtl_setup_rtl8723b(hdev, btrtl_dev);
	default:
		rtl_dev_info(hdev, "rtl: assuming no firmware upload needed\n");
		return 0;
	}
}
EXPORT_SYMBOL_GPL(btrtl_download_firmware);

int btrtl_setup_realtek(struct hci_dev *hdev)
{
	struct btrtl_device_info *btrtl_dev;
	int ret;

	btrtl_dev = btrtl_initialize(hdev, NULL);
	if (IS_ERR(btrtl_dev))
		return PTR_ERR(btrtl_dev);

	ret = btrtl_download_firmware(hdev, btrtl_dev);

	btrtl_free(btrtl_dev);

	return ret;
}
EXPORT_SYMBOL_GPL(btrtl_setup_realtek);

int btrtl_shutdown_realtek(struct hci_dev *hdev)
{
	struct sk_buff *skb;
	int ret;

	/* According to the vendor driver, BT must be reset on close to avoid
	 * firmware crash.
	 */
	skb = __hci_cmd_sync(hdev, HCI_OP_RESET, 0, NULL, HCI_INIT_TIMEOUT);
	if (IS_ERR(skb)) {
		ret = PTR_ERR(skb);
		bt_dev_err(hdev, "HCI reset during shutdown failed");
		return ret;
	}
	kfree_skb(skb);

	return 0;
}
EXPORT_SYMBOL_GPL(btrtl_shutdown_realtek);

static unsigned int btrtl_convert_baudrate(u32 device_baudrate)
{
	switch (device_baudrate) {
	case 0x0252a00a:
		return 230400;

	case 0x05f75004:
		return 921600;

	case 0x00005004:
		return 1000000;

	case 0x04928002:
	case 0x01128002:
		return 1500000;

	case 0x00005002:
		return 2000000;

	case 0x0000b001:
		return 2500000;

	case 0x04928001:
		return 3000000;

	case 0x052a6001:
		return 3500000;

	case 0x00005001:
		return 4000000;

	case 0x0252c014:
	default:
		return 115200;
	}
}

int btrtl_get_uart_settings(struct hci_dev *hdev,
			    struct btrtl_device_info *btrtl_dev,
			    unsigned int *controller_baudrate,
			    u32 *device_baudrate, bool *flow_control)
{
	struct rtl_vendor_config *config;
	struct rtl_vendor_config_entry *entry;
	int i, total_data_len;
	bool found = false;

	total_data_len = btrtl_dev->cfg_len - sizeof(*config);
	if (total_data_len <= 0) {
		rtl_dev_warn(hdev, "no config loaded\n");
		return -EINVAL;
	}

	config = (struct rtl_vendor_config *)btrtl_dev->cfg_data;
	if (le32_to_cpu(config->signature) != RTL_CONFIG_MAGIC) {
		rtl_dev_err(hdev, "invalid config magic\n");
		return -EINVAL;
	}

	if (total_data_len < le16_to_cpu(config->total_len)) {
		rtl_dev_err(hdev, "config is too short\n");
		return -EINVAL;
	}

	for (i = 0; i < total_data_len; ) {
		entry = ((void *)config->entry) + i;

		switch (le16_to_cpu(entry->offset)) {
		case 0xc:
			if (entry->len < sizeof(*device_baudrate)) {
				rtl_dev_err(hdev, "invalid UART config entry\n");
				return -EINVAL;
			}

			*device_baudrate = get_unaligned_le32(entry->data);
			*controller_baudrate = btrtl_convert_baudrate(
							*device_baudrate);

			if (entry->len >= 13)
				*flow_control = !!(entry->data[12] & BIT(2));
			else
				*flow_control = false;

			found = true;
			break;

		default:
			rtl_dev_dbg(hdev, "skipping config entry 0x%x (len %u)\n",
				   le16_to_cpu(entry->offset), entry->len);
			break;
		};

		i += sizeof(*entry) + entry->len;
	}

	if (!found) {
		rtl_dev_err(hdev, "no UART config entry found\n");
		return -ENOENT;
	}

	rtl_dev_dbg(hdev, "device baudrate = 0x%08x\n", *device_baudrate);
	rtl_dev_dbg(hdev, "controller baudrate = %u\n", *controller_baudrate);
	rtl_dev_dbg(hdev, "flow control %d\n", *flow_control);

	return 0;
}
EXPORT_SYMBOL_GPL(btrtl_get_uart_settings);

=======
	switch (lmp_subver) {
	case RTL_ROM_LMP_8723A:
	case RTL_ROM_LMP_3499:
		return btrtl_setup_rtl8723a(hdev);
	case RTL_ROM_LMP_8723B:
		return btrtl_setup_rtl8723b(hdev, lmp_subver,
					    "rtl_bt/rtl8723b_fw.bin");
	case RTL_ROM_LMP_8821A:
		return btrtl_setup_rtl8723b(hdev, lmp_subver,
					    "rtl_bt/rtl8821a_fw.bin");
	case RTL_ROM_LMP_8761A:
		return btrtl_setup_rtl8723b(hdev, lmp_subver,
					    "rtl_bt/rtl8761a_fw.bin");
	case RTL_ROM_LMP_8822B:
		return btrtl_setup_rtl8723b(hdev, lmp_subver,
					    "rtl_bt/rtl8822b_fw.bin");
	default:
		BT_INFO("rtl: assuming no firmware upload needed.");
		return 0;
	}
}
EXPORT_SYMBOL_GPL(btrtl_setup_realtek);

>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
MODULE_AUTHOR("Daniel Drake <drake@endlessm.com>");
MODULE_DESCRIPTION("Bluetooth support for Realtek devices ver " VERSION);
MODULE_VERSION(VERSION);
MODULE_LICENSE("GPL");
<<<<<<< HEAD
MODULE_FIRMWARE("rtl_bt/rtl8723a_fw.bin");
MODULE_FIRMWARE("rtl_bt/rtl8723b_fw.bin");
MODULE_FIRMWARE("rtl_bt/rtl8723b_config.bin");
MODULE_FIRMWARE("rtl_bt/rtl8723bs_fw.bin");
MODULE_FIRMWARE("rtl_bt/rtl8723bs_config.bin");
MODULE_FIRMWARE("rtl_bt/rtl8723ds_fw.bin");
MODULE_FIRMWARE("rtl_bt/rtl8723ds_config.bin");
MODULE_FIRMWARE("rtl_bt/rtl8761a_fw.bin");
MODULE_FIRMWARE("rtl_bt/rtl8761a_config.bin");
MODULE_FIRMWARE("rtl_bt/rtl8821a_fw.bin");
MODULE_FIRMWARE("rtl_bt/rtl8821a_config.bin");
MODULE_FIRMWARE("rtl_bt/rtl8822b_fw.bin");
MODULE_FIRMWARE("rtl_bt/rtl8822b_config.bin");
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
