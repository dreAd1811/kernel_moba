# SPDX-License-Identifier: GPL-2.0
<<<<<<< HEAD
ccflags-y := -Idrivers/gpu/drm/msm
ccflags-y += -Idrivers/gpu/drm/msm/disp/dpu1
ccflags-$(CONFIG_DRM_MSM_DSI) += -Idrivers/gpu/drm/msm/dsi

msm-y := \
	hdmi/hdmi.o \
=======
ccflags-y := -Iinclude/drm -Idrivers/gpu/drm/msm -Idrivers/gpu/drm/msm/dsi-staging -Idrivers/gpu/drm/msm/dp
ccflags-y += -Idrivers/gpu/drm/msm/display-manager
ccflags-$(CONFIG_DRM_MSM_DSI) += -Idrivers/gpu/drm/msm/dsi
ccflags-$(CONFIG_DRM_MSM_DSI_PLL) += -Idrivers/gpu/drm/msm/dsi
ccflags-y += -Idrivers/gpu/drm/msm/sde
ccflags-y += -Idrivers/media/platform/msm/sde/rotator
ccflags-y += -Idrivers/gpu/drm/msm/hdmi
ccflags-$(CONFIG_DRM_SDE_SHD) += -Idrivers/gpu/drm/msm/shd
ccflags-$(CONFIG_DRM_SDE_SHP) += -Idrivers/gpu/drm/msm/shp

msm_drm-y := \
	dp/dp_usbpd.o \
	dp/dp_parser.o \
	dp/dp_power.o \
	dp/dp_catalog.o \
	dp/dp_catalog_v420.o \
	dp/dp_catalog_v200.o \
	dp/dp_aux.o \
	dp/dp_panel.o \
	dp/dp_link.o \
	dp/dp_ctrl.o \
	dp/dp_audio.o \
	dp/dp_debug.o \
	dp/dp_mst_sim_helper.o \
	dp/dp_mst_sim.o \
	dp/dp_hpd.o \
	dp/dp_aux_bridge.o \
	dp/dp_bridge_hpd.o \
	dp/dp_gpio_hpd.o \
	dp/dp_lphw_hpd.o \
	dp/dp_display.o \
	dp/dp_drm.o \
	dp/dp_hdcp2p2.o \
	dp/dp_mst_drm.o \
	sde/sde_crtc.o \
	sde/sde_encoder.o \
	sde/sde_encoder_phys_vid.o \
	sde/sde_encoder_phys_cmd.o \
	sde/sde_irq.o \
	sde/sde_core_irq.o \
	sde/sde_core_perf.o \
	sde/sde_rm.o \
	sde/sde_kms_utils.o \
	sde/sde_kms.o \
	sde/sde_plane.o \
	sde/sde_connector.o \
	sde/sde_color_processing.o \
	sde/sde_vbif.o \
	sde_io_util.o \
	sde/sde_hw_reg_dma_v1_color_proc.o \
	sde/sde_hw_color_proc_v4.o \
	sde/sde_hw_ad4.o \
	sde_edid_parser.o \
	sde_hdcp_1x.o \
	sde_hdcp_2x.o \
	sde_dbg.o \
	sde_dbg_evtlog.o \

msm_drm-$(CONFIG_DRM_MSM_HDMI) += hdmi/hdmi.o \
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	hdmi/hdmi_audio.o \
	hdmi/hdmi_bridge.o \
	hdmi/hdmi_connector.o \
	hdmi/hdmi_i2c.o \
	hdmi/hdmi_phy.o \
	hdmi/hdmi_phy_8960.o \
	hdmi/hdmi_phy_8x60.o \
	hdmi/hdmi_phy_8x74.o \
<<<<<<< HEAD
	edp/edp.o \
=======

msm_drm-$(CONFIG_DRM_MSM_EDP) += edp/edp.o \
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	edp/edp_aux.o \
	edp/edp_bridge.o \
	edp/edp_connector.o \
	edp/edp_ctrl.o \
	edp/edp_phy.o \
<<<<<<< HEAD
	disp/mdp_format.o \
	disp/mdp_kms.o \
	disp/mdp4/mdp4_crtc.o \
	disp/mdp4/mdp4_dtv_encoder.o \
	disp/mdp4/mdp4_lcdc_encoder.o \
	disp/mdp4/mdp4_lvds_connector.o \
	disp/mdp4/mdp4_irq.o \
	disp/mdp4/mdp4_kms.o \
	disp/mdp4/mdp4_plane.o \
	disp/mdp5/mdp5_cfg.o \
	disp/mdp5/mdp5_ctl.o \
	disp/mdp5/mdp5_crtc.o \
	disp/mdp5/mdp5_encoder.o \
	disp/mdp5/mdp5_irq.o \
	disp/mdp5/mdp5_mdss.o \
	disp/mdp5/mdp5_kms.o \
	disp/mdp5/mdp5_pipe.o \
	disp/mdp5/mdp5_mixer.o \
	disp/mdp5/mdp5_plane.o \
	disp/mdp5/mdp5_smp.o \
	disp/dpu1/dpu_core_irq.o \
	disp/dpu1/dpu_core_perf.o \
	disp/dpu1/dpu_crtc.o \
	disp/dpu1/dpu_encoder.o \
	disp/dpu1/dpu_encoder_phys_cmd.o \
	disp/dpu1/dpu_encoder_phys_vid.o \
	disp/dpu1/dpu_formats.o \
	disp/dpu1/dpu_hw_blk.o \
	disp/dpu1/dpu_hw_catalog.o \
	disp/dpu1/dpu_hw_cdm.o \
	disp/dpu1/dpu_hw_ctl.o \
	disp/dpu1/dpu_hw_interrupts.o \
	disp/dpu1/dpu_hw_intf.o \
	disp/dpu1/dpu_hw_lm.o \
	disp/dpu1/dpu_hw_pingpong.o \
	disp/dpu1/dpu_hw_sspp.o \
	disp/dpu1/dpu_hw_top.o \
	disp/dpu1/dpu_hw_util.o \
	disp/dpu1/dpu_hw_vbif.o \
	disp/dpu1/dpu_io_util.o \
	disp/dpu1/dpu_irq.o \
	disp/dpu1/dpu_kms.o \
	disp/dpu1/dpu_mdss.o \
	disp/dpu1/dpu_plane.o \
	disp/dpu1/dpu_power_handle.o \
	disp/dpu1/dpu_rm.o \
	disp/dpu1/dpu_vbif.o \
	msm_atomic.o \
	msm_debugfs.o \
	msm_drv.o \
	msm_fb.o \
	msm_fence.o \
	msm_gem.o \
	msm_gem_prime.o \
	msm_gem_shrinker.o \
	msm_gem_submit.o \
	msm_gem_vma.o \
	msm_gpu.o \
	msm_iommu.o \
	msm_perf.o \
	msm_rd.o \
	msm_ringbuffer.o \
	msm_submitqueue.o

# use drm gpu driver only if qcom_kgsl driver not available
#ifneq ($(CONFIG_QCOM_KGSL),y)
msm_drm-y += adreno/adreno_device.o \
     	adreno/adreno_gpu.o \
	adreno/a3xx_gpu.o \
	adreno/a4xx_gpu.o \
	adreno/a5xx_gpu.o \
	adreno/a5xx_power.o \
	adreno/a5xx_preempt.o\
	adreno/a6xx_gpu.o\
	adreno/a6xx_gmu.o\
 	adreno/a6xx_hfi.o
#endif

msm-$(CONFIG_DEBUG_FS) += adreno/a5xx_debugfs.o \
			  disp/dpu1/dpu_dbg.o

msm-$(CONFIG_DRM_FBDEV_EMULATION) += msm_fbdev.o
msm-$(CONFIG_COMMON_CLK) += disp/mdp4/mdp4_lvds_pll.o
msm-$(CONFIG_COMMON_CLK) += hdmi/hdmi_pll_8960.o
msm-$(CONFIG_COMMON_CLK) += hdmi/hdmi_phy_8996.o

msm-$(CONFIG_DRM_MSM_HDMI_HDCP) += hdmi/hdmi_hdcp.o

msm-$(CONFIG_DRM_MSM_DSI) += dsi/dsi.o \
			disp/mdp4/mdp4_dsi_encoder.o \
=======

msm_drm-$(CONFIG_DRM_MSM_MDP5) += mdp/mdp_format.o \
	mdp/mdp_kms.o \
	mdp/mdp5/mdp5_cfg.o \
	mdp/mdp5/mdp5_ctl.o \
	mdp/mdp5/mdp5_crtc.o \
	mdp/mdp5/mdp5_encoder.o \
	mdp/mdp5/mdp5_irq.o \
	mdp/mdp5/mdp5_mdss.o \
	mdp/mdp5/mdp5_kms.o \
	mdp/mdp5/mdp5_pipe.o \
	mdp/mdp5/mdp5_mixer.o \
	mdp/mdp5/mdp5_plane.o \
	mdp/mdp5/mdp5_smp.o \

msm_drm-$(CONFIG_DRM_SDE_RSC) += sde_rsc.o \
	sde_rsc_hw.o \
	sde_rsc_hw_v3.o \

# use drm gpu driver only if qcom_kgsl driver not available
ifneq ($(CONFIG_QCOM_KGSL),y)
msm_drm-y += adreno/adreno_device.o \
	adreno/adreno_gpu.o \
	adreno/a3xx_gpu.o \
	adreno/a4xx_gpu.o \
	adreno/a5xx_gpu.o \
	adreno/a5xx_power.o
endif

msm_drm-$(CONFIG_DRM_MSM_MDP4) += mdp/mdp4/mdp4_crtc.o \
	mdp/mdp4/mdp4_dtv_encoder.o \
	mdp/mdp4/mdp4_lcdc_encoder.o \
	mdp/mdp4/mdp4_lvds_connector.o \
	mdp/mdp4/mdp4_irq.o \
	mdp/mdp4/mdp4_kms.o \
	mdp/mdp4/mdp4_dsi_encoder.o \
	mdp/mdp4/mdp4_plane.o

msm_drm-$(CONFIG_DRM_FBDEV_EMULATION) += msm_fbdev.o
msm_drm-$(CONFIG_SYNC_FILE) += sde/sde_fence.o
msm_drm-$(CONFIG_DRM_MSM_MDP4) += mdp/mdp4/mdp4_lvds_pll.o
msm_drm-$(CONFIG_DRM_MSM_HDMI) += hdmi/hdmi_pll_8960.o
msm_drm-$(CONFIG_DRM_MSM_HDMI) += hdmi/hdmi_phy_8996.o

msm_drm-$(CONFIG_DRM_MSM_HDMI_HDCP) += hdmi/hdmi_hdcp.o

msm_drm-$(CONFIG_DRM_MSM_DSI) += dsi/dsi.o \
			mdp/mdp4/mdp4_dsi_encoder.o \
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
			dsi/dsi_cfg.o \
			dsi/dsi_host.o \
			dsi/dsi_manager.o \
			dsi/phy/dsi_phy.o \
<<<<<<< HEAD
			disp/mdp5/mdp5_cmd_encoder.o

msm-$(CONFIG_DRM_MSM_DSI_28NM_PHY) += dsi/phy/dsi_phy_28nm.o
msm-$(CONFIG_DRM_MSM_DSI_20NM_PHY) += dsi/phy/dsi_phy_20nm.o
msm-$(CONFIG_DRM_MSM_DSI_28NM_8960_PHY) += dsi/phy/dsi_phy_28nm_8960.o
msm-$(CONFIG_DRM_MSM_DSI_14NM_PHY) += dsi/phy/dsi_phy_14nm.o
msm-$(CONFIG_DRM_MSM_DSI_10NM_PHY) += dsi/phy/dsi_phy_10nm.o

ifeq ($(CONFIG_DRM_MSM_DSI_PLL),y)
msm-y += dsi/pll/dsi_pll.o
msm-$(CONFIG_DRM_MSM_DSI_28NM_PHY) += dsi/pll/dsi_pll_28nm.o
msm-$(CONFIG_DRM_MSM_DSI_28NM_8960_PHY) += dsi/pll/dsi_pll_28nm_8960.o
msm-$(CONFIG_DRM_MSM_DSI_14NM_PHY) += dsi/pll/dsi_pll_14nm.o
msm-$(CONFIG_DRM_MSM_DSI_10NM_PHY) += dsi/pll/dsi_pll_10nm.o
endif

obj-$(CONFIG_DRM_MSM)	+= msm.o
=======
			dsi/dsi_manager.o \
			mdp/mdp5/mdp5_cmd_encoder.o

msm_drm-$(CONFIG_DRM_MSM_DSI_28NM_PHY) += dsi/phy/dsi_phy_28nm.o
msm_drm-$(CONFIG_DRM_MSM_DSI_20NM_PHY) += dsi/phy/dsi_phy_20nm.o
msm_drm-$(CONFIG_DRM_MSM_DSI_28NM_8960_PHY) += dsi/phy/dsi_phy_28nm_8960.o
msm_drm-$(CONFIG_DRM_MSM_DSI_14NM_PHY) += dsi/phy/dsi_phy_14nm.o

ifeq ($(CONFIG_DRM_MSM_DSI_PLL),y)
msm_drm-y += dsi/pll/dsi_pll.o
msm_drm-$(CONFIG_DRM_MSM_DSI_28NM_PHY) += dsi/pll/dsi_pll_28nm.o
msm_drm-$(CONFIG_DRM_MSM_DSI_28NM_8960_PHY) += dsi/pll/dsi_pll_28nm_8960.o
msm_drm-$(CONFIG_DRM_MSM_DSI_14NM_PHY) += dsi/pll/dsi_pll_14nm.o
endif
msm_drm-$(CONFIG_DRM_MSM_DSI_STAGING) += dsi-staging/dsi_phy.o \
				dsi-staging/dsi_pwr.o \
				dsi-staging/dsi_phy.o \
				dsi-staging/dsi_phy_hw_v2_0.o \
				dsi-staging/dsi_phy_hw_v3_0.o \
				dsi-staging/dsi_phy_hw_v4_0.o \
				dsi-staging/dsi_phy_timing_calc.o \
				dsi-staging/dsi_phy_timing_v2_0.o \
				dsi-staging/dsi_phy_timing_v3_0.o \
				dsi-staging/dsi_phy_timing_v4_0.o \
				dsi-staging/dsi_ctrl_hw_cmn.o \
				dsi-staging/dsi_ctrl_hw_1_4.o \
				dsi-staging/dsi_ctrl_hw_2_0.o \
				dsi-staging/dsi_ctrl_hw_2_2.o \
				dsi-staging/dsi_ctrl.o \
				dsi-staging/dsi_catalog.o \
				dsi-staging/dsi_drm.o \
				dsi-staging/dsi_display.o \
				dsi-staging/dsi_panel.o \
				dsi-staging/dsi_clk_manager.o \
				dsi-staging/dsi_display_test.o

msm_drm-$(CONFIG_DSI_PARSER) += dsi-staging/dsi_parser.o

msm_drm-$(CONFIG_DRM_MSM_DSI_PLL) += dsi/pll/dsi_pll.o \
				dsi/pll/dsi_pll_28nm.o

msm_drm-$(CONFIG_DRM_MSM) += \
	sde/sde_hw_catalog.o \
	sde/sde_hw_cdm.o \
	sde/sde_hw_dspp.o \
	sde/sde_hw_intf.o \
	sde/sde_hw_lm.o \
	sde/sde_hw_ctl.o \
	sde/sde_hw_util.o \
	sde/sde_hw_sspp.o \
	sde/sde_hw_wb.o \
	sde/sde_hw_rot.o \
	sde/sde_hw_pingpong.o \
	sde/sde_hw_top.o \
	sde/sde_hw_interrupts.o \
	sde/sde_hw_vbif.o \
	sde/sde_hw_blk.o \
	sde/sde_formats.o \
	sde_power_handle.o \
	sde/sde_hw_color_processing_v1_7.o \
	sde/sde_reg_dma.o \
	sde/sde_hw_reg_dma_v1.o \
	sde/sde_hw_dsc.o \
	sde/sde_hw_ds.o \
	sde/sde_hw_qdss.o

msm_drm-$(CONFIG_DRM_SDE_WB) += sde/sde_wb.o \
	sde/sde_encoder_phys_wb.o

msm_drm-$(CONFIG_DRM_SDE_SHD) += shd/shd_drm.o \
	shd/shd_hw.o \
	shd/sde_encoder_phys_shd.o

msm_drm-$(CONFIG_DRM_SDE_SHP) += shp/shp_drm.o

msm_drm-$(CONFIG_DRM_MSM) += \
	msm_atomic.o \
	msm_drv.o \
	msm_fb.o \
	msm_gem.o \
	msm_gem_prime.o \
	msm_gem_submit.o \
	msm_gem_shrinker.o \
	msm_gem_vma.o\
	msm_gpu.o \
	msm_iommu.o \
	msm_smmu.o \
	msm_perf.o \
	msm_rd.o \
	msm_ringbuffer.o \
	msm_prop.o \
	msm_fence.o \
	msm_debugfs.o

obj-$(CONFIG_DRM_MSM)	+= msm_drm.o
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
