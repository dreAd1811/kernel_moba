/*
 * Copyright (C) 2013 Red Hat
 * Author: Rob Clark <robdclark@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 as published by
 * the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "hdmi.h"

static void hdmi_phy_8960_powerup(struct hdmi_phy *phy,
				  unsigned long int pixclock)
{
	DBG("pixclock: %lu", pixclock);

	hdmi_phy_write(phy, REG_HDMI_8960_PHY_REG2, 0x00);
	hdmi_phy_write(phy, REG_HDMI_8960_PHY_REG0, 0x1b);
	hdmi_phy_write(phy, REG_HDMI_8960_PHY_REG1, 0xf2);
	hdmi_phy_write(phy, REG_HDMI_8960_PHY_REG4, 0x00);
	hdmi_phy_write(phy, REG_HDMI_8960_PHY_REG5, 0x00);
	hdmi_phy_write(phy, REG_HDMI_8960_PHY_REG6, 0x00);
	hdmi_phy_write(phy, REG_HDMI_8960_PHY_REG7, 0x00);
	hdmi_phy_write(phy, REG_HDMI_8960_PHY_REG8, 0x00);
	hdmi_phy_write(phy, REG_HDMI_8960_PHY_REG9, 0x00);
	hdmi_phy_write(phy, REG_HDMI_8960_PHY_REG10, 0x00);
	hdmi_phy_write(phy, REG_HDMI_8960_PHY_REG11, 0x00);
	hdmi_phy_write(phy, REG_HDMI_8960_PHY_REG3, 0x20);
}

static void hdmi_phy_8960_powerdown(struct hdmi_phy *phy)
{
	DBG("");

	hdmi_phy_write(phy, REG_HDMI_8960_PHY_REG2, 0x7f);
}

static const char * const hdmi_phy_8960_reg_names[] = {
	"core-vdda",
};

static const char * const hdmi_phy_8960_clk_names[] = {
<<<<<<< HEAD
	"slave_iface",
=======
	"slave_iface_clk",
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
};

const struct hdmi_phy_cfg msm_hdmi_phy_8960_cfg = {
	.type = MSM_HDMI_PHY_8960,
	.powerup = hdmi_phy_8960_powerup,
	.powerdown = hdmi_phy_8960_powerdown,
	.reg_names = hdmi_phy_8960_reg_names,
	.num_regs = ARRAY_SIZE(hdmi_phy_8960_reg_names),
	.clk_names = hdmi_phy_8960_clk_names,
	.num_clks = ARRAY_SIZE(hdmi_phy_8960_clk_names),
};
