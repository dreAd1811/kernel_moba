/*
 * aQuantia Corporation Network Driver
 * Copyright (C) 2014-2017 aQuantia Corporation. All rights reserved
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 */

/* File hw_atl_llh_internal.h: Preprocessor definitions
 * for Atlantic registers.
 */

#ifndef HW_ATL_LLH_INTERNAL_H
#define HW_ATL_LLH_INTERNAL_H

/* global microprocessor semaphore  definitions
 * base address: 0x000003a0
 * parameter: semaphore {s} | stride size 0x4 | range [0, 15]
 */
<<<<<<< HEAD
#define HW_ATL_GLB_CPU_SEM_ADR(semaphore)  (0x000003a0u + (semaphore) * 0x4)
/* register address for bitfield rx dma good octet counter lsw [1f:0] */
#define HW_ATL_STATS_RX_DMA_GOOD_OCTET_COUNTERLSW 0x00006808
/* register address for bitfield rx dma good packet counter lsw [1f:0] */
#define HW_ATL_STATS_RX_DMA_GOOD_PKT_COUNTERLSW 0x00006800
/* register address for bitfield tx dma good octet counter lsw [1f:0] */
#define HW_ATL_STATS_TX_DMA_GOOD_OCTET_COUNTERLSW 0x00008808
/* register address for bitfield tx dma good packet counter lsw [1f:0] */
#define HW_ATL_STATS_TX_DMA_GOOD_PKT_COUNTERLSW 0x00008800

/* register address for bitfield rx dma good octet counter msw [3f:20] */
#define HW_ATL_STATS_RX_DMA_GOOD_OCTET_COUNTERMSW 0x0000680c
/* register address for bitfield rx dma good packet counter msw [3f:20] */
#define HW_ATL_STATS_RX_DMA_GOOD_PKT_COUNTERMSW 0x00006804
/* register address for bitfield tx dma good octet counter msw [3f:20] */
#define HW_ATL_STATS_TX_DMA_GOOD_OCTET_COUNTERMSW 0x0000880c
/* register address for bitfield tx dma good packet counter msw [3f:20] */
#define HW_ATL_STATS_TX_DMA_GOOD_PKT_COUNTERMSW 0x00008804

/* preprocessor definitions for msm rx errors counter register */
#define HW_ATL_MAC_MSM_RX_ERRS_CNT_ADR 0x00000120u

/* preprocessor definitions for msm rx unicast frames counter register */
#define HW_ATL_MAC_MSM_RX_UCST_FRM_CNT_ADR 0x000000e0u

/* preprocessor definitions for msm rx multicast frames counter register */
#define HW_ATL_MAC_MSM_RX_MCST_FRM_CNT_ADR 0x000000e8u

/* preprocessor definitions for msm rx broadcast frames counter register */
#define HW_ATL_MAC_MSM_RX_BCST_FRM_CNT_ADR 0x000000f0u

/* preprocessor definitions for msm rx broadcast octets counter register 1 */
#define HW_ATL_MAC_MSM_RX_BCST_OCTETS_COUNTER1_ADR 0x000001b0u

/* preprocessor definitions for msm rx broadcast octets counter register 2 */
#define HW_ATL_MAC_MSM_RX_BCST_OCTETS_COUNTER2_ADR 0x000001b4u

/* preprocessor definitions for msm rx unicast octets counter register 0 */
#define HW_ATL_MAC_MSM_RX_UCST_OCTETS_COUNTER0_ADR 0x000001b8u

/* preprocessor definitions for rx dma statistics counter 7 */
#define HW_ATL_RX_DMA_STAT_COUNTER7_ADR 0x00006818u

/* preprocessor definitions for msm tx unicast frames counter register */
#define HW_ATL_MAC_MSM_TX_UCST_FRM_CNT_ADR 0x00000108u

/* preprocessor definitions for msm tx multicast frames counter register */
#define HW_ATL_MAC_MSM_TX_MCST_FRM_CNT_ADR 0x00000110u

/* preprocessor definitions for global mif identification */
#define HW_ATL_GLB_MIF_ID_ADR 0x0000001cu

/* register address for bitfield iamr_lsw[1f:0] */
#define HW_ATL_ITR_IAMRLSW_ADR 0x00002090
/* register address for bitfield rx dma drop packet counter [1f:0] */
#define HW_ATL_RPB_RX_DMA_DROP_PKT_CNT_ADR 0x00006818

/* register address for bitfield imcr_lsw[1f:0] */
#define HW_ATL_ITR_IMCRLSW_ADR 0x00002070
/* register address for bitfield imsr_lsw[1f:0] */
#define HW_ATL_ITR_IMSRLSW_ADR 0x00002060
/* register address for bitfield itr_reg_res_dsbl */
#define HW_ATL_ITR_REG_RES_DSBL_ADR 0x00002300
/* bitmask for bitfield itr_reg_res_dsbl */
#define HW_ATL_ITR_REG_RES_DSBL_MSK 0x20000000
/* lower bit position of bitfield itr_reg_res_dsbl */
#define HW_ATL_ITR_REG_RES_DSBL_SHIFT 29
/* register address for bitfield iscr_lsw[1f:0] */
#define HW_ATL_ITR_ISCRLSW_ADR 0x00002050
/* register address for bitfield isr_lsw[1f:0] */
#define HW_ATL_ITR_ISRLSW_ADR 0x00002000
/* register address for bitfield itr_reset */
#define HW_ATL_ITR_RES_ADR 0x00002300
/* bitmask for bitfield itr_reset */
#define HW_ATL_ITR_RES_MSK 0x80000000
/* lower bit position of bitfield itr_reset */
#define HW_ATL_ITR_RES_SHIFT 31
/* register address for bitfield dca{d}_cpuid[7:0] */
#define HW_ATL_RDM_DCADCPUID_ADR(dca) (0x00006100 + (dca) * 0x4)
/* bitmask for bitfield dca{d}_cpuid[7:0] */
#define HW_ATL_RDM_DCADCPUID_MSK 0x000000ff
/* lower bit position of bitfield dca{d}_cpuid[7:0] */
#define HW_ATL_RDM_DCADCPUID_SHIFT 0
/* register address for bitfield dca_en */
#define HW_ATL_RDM_DCA_EN_ADR 0x00006180
=======
#define glb_cpu_sem_adr(semaphore)  (0x000003a0u + (semaphore) * 0x4)
/* register address for bitfield rx dma good octet counter lsw [1f:0] */
#define stats_rx_dma_good_octet_counterlsw__adr 0x00006808
/* register address for bitfield rx dma good packet counter lsw [1f:0] */
#define stats_rx_dma_good_pkt_counterlsw__adr 0x00006800
/* register address for bitfield tx dma good octet counter lsw [1f:0] */
#define stats_tx_dma_good_octet_counterlsw__adr 0x00008808
/* register address for bitfield tx dma good packet counter lsw [1f:0] */
#define stats_tx_dma_good_pkt_counterlsw__adr 0x00008800

/* register address for bitfield rx dma good octet counter msw [3f:20] */
#define stats_rx_dma_good_octet_countermsw__adr 0x0000680c
/* register address for bitfield rx dma good packet counter msw [3f:20] */
#define stats_rx_dma_good_pkt_countermsw__adr 0x00006804
/* register address for bitfield tx dma good octet counter msw [3f:20] */
#define stats_tx_dma_good_octet_countermsw__adr 0x0000880c
/* register address for bitfield tx dma good packet counter msw [3f:20] */
#define stats_tx_dma_good_pkt_countermsw__adr 0x00008804

/* preprocessor definitions for msm rx errors counter register */
#define mac_msm_rx_errs_cnt_adr 0x00000120u

/* preprocessor definitions for msm rx unicast frames counter register */
#define mac_msm_rx_ucst_frm_cnt_adr 0x000000e0u

/* preprocessor definitions for msm rx multicast frames counter register */
#define mac_msm_rx_mcst_frm_cnt_adr 0x000000e8u

/* preprocessor definitions for msm rx broadcast frames counter register */
#define mac_msm_rx_bcst_frm_cnt_adr 0x000000f0u

/* preprocessor definitions for msm rx broadcast octets counter register 1 */
#define mac_msm_rx_bcst_octets_counter1_adr 0x000001b0u

/* preprocessor definitions for msm rx broadcast octets counter register 2 */
#define mac_msm_rx_bcst_octets_counter2_adr 0x000001b4u

/* preprocessor definitions for msm rx unicast octets counter register 0 */
#define mac_msm_rx_ucst_octets_counter0_adr 0x000001b8u

/* preprocessor definitions for rx dma statistics counter 7 */
#define rx_dma_stat_counter7_adr 0x00006818u

/* preprocessor definitions for msm tx unicast frames counter register */
#define mac_msm_tx_ucst_frm_cnt_adr 0x00000108u

/* preprocessor definitions for msm tx multicast frames counter register */
#define mac_msm_tx_mcst_frm_cnt_adr 0x00000110u

/* preprocessor definitions for global mif identification */
#define glb_mif_id_adr 0x0000001cu

/* register address for bitfield iamr_lsw[1f:0] */
#define itr_iamrlsw_adr 0x00002090
/* register address for bitfield rx dma drop packet counter [1f:0] */
#define rpb_rx_dma_drop_pkt_cnt_adr 0x00006818

/* register address for bitfield imcr_lsw[1f:0] */
#define itr_imcrlsw_adr 0x00002070
/* register address for bitfield imsr_lsw[1f:0] */
#define itr_imsrlsw_adr 0x00002060
/* register address for bitfield itr_reg_res_dsbl */
#define itr_reg_res_dsbl_adr 0x00002300
/* bitmask for bitfield itr_reg_res_dsbl */
#define itr_reg_res_dsbl_msk 0x20000000
/* lower bit position of bitfield itr_reg_res_dsbl */
#define itr_reg_res_dsbl_shift 29
/* register address for bitfield iscr_lsw[1f:0] */
#define itr_iscrlsw_adr 0x00002050
/* register address for bitfield isr_lsw[1f:0] */
#define itr_isrlsw_adr 0x00002000
/* register address for bitfield itr_reset */
#define itr_res_adr 0x00002300
/* bitmask for bitfield itr_reset */
#define itr_res_msk 0x80000000
/* lower bit position of bitfield itr_reset */
#define itr_res_shift 31
/* register address for bitfield dca{d}_cpuid[7:0] */
#define rdm_dcadcpuid_adr(dca) (0x00006100 + (dca) * 0x4)
/* bitmask for bitfield dca{d}_cpuid[7:0] */
#define rdm_dcadcpuid_msk 0x000000ff
/* lower bit position of bitfield dca{d}_cpuid[7:0] */
#define rdm_dcadcpuid_shift 0
/* register address for bitfield dca_en */
#define rdm_dca_en_adr 0x00006180
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* rx dca_en bitfield definitions
 * preprocessor definitions for the bitfield "dca_en".
 * port="pif_rdm_dca_en_i"
 */

/* register address for bitfield dca_en */
<<<<<<< HEAD
#define HW_ATL_RDM_DCA_EN_ADR 0x00006180
/* bitmask for bitfield dca_en */
#define HW_ATL_RDM_DCA_EN_MSK 0x80000000
/* inverted bitmask for bitfield dca_en */
#define HW_ATL_RDM_DCA_EN_MSKN 0x7fffffff
/* lower bit position of bitfield dca_en */
#define HW_ATL_RDM_DCA_EN_SHIFT 31
/* width of bitfield dca_en */
#define HW_ATL_RDM_DCA_EN_WIDTH 1
/* default value of bitfield dca_en */
#define HW_ATL_RDM_DCA_EN_DEFAULT 0x1
=======
#define rdm_dca_en_adr 0x00006180
/* bitmask for bitfield dca_en */
#define rdm_dca_en_msk 0x80000000
/* inverted bitmask for bitfield dca_en */
#define rdm_dca_en_mskn 0x7fffffff
/* lower bit position of bitfield dca_en */
#define rdm_dca_en_shift 31
/* width of bitfield dca_en */
#define rdm_dca_en_width 1
/* default value of bitfield dca_en */
#define rdm_dca_en_default 0x1
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* rx dca_mode[3:0] bitfield definitions
 * preprocessor definitions for the bitfield "dca_mode[3:0]".
 * port="pif_rdm_dca_mode_i[3:0]"
 */

/* register address for bitfield dca_mode[3:0] */
<<<<<<< HEAD
#define HW_ATL_RDM_DCA_MODE_ADR 0x00006180
/* bitmask for bitfield dca_mode[3:0] */
#define HW_ATL_RDM_DCA_MODE_MSK 0x0000000f
/* inverted bitmask for bitfield dca_mode[3:0] */
#define HW_ATL_RDM_DCA_MODE_MSKN 0xfffffff0
/* lower bit position of bitfield dca_mode[3:0] */
#define HW_ATL_RDM_DCA_MODE_SHIFT 0
/* width of bitfield dca_mode[3:0] */
#define HW_ATL_RDM_DCA_MODE_WIDTH 4
/* default value of bitfield dca_mode[3:0] */
#define HW_ATL_RDM_DCA_MODE_DEFAULT 0x0
=======
#define rdm_dca_mode_adr 0x00006180
/* bitmask for bitfield dca_mode[3:0] */
#define rdm_dca_mode_msk 0x0000000f
/* inverted bitmask for bitfield dca_mode[3:0] */
#define rdm_dca_mode_mskn 0xfffffff0
/* lower bit position of bitfield dca_mode[3:0] */
#define rdm_dca_mode_shift 0
/* width of bitfield dca_mode[3:0] */
#define rdm_dca_mode_width 4
/* default value of bitfield dca_mode[3:0] */
#define rdm_dca_mode_default 0x0
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* rx desc{d}_data_size[4:0] bitfield definitions
 * preprocessor definitions for the bitfield "desc{d}_data_size[4:0]".
 * parameter: descriptor {d} | stride size 0x20 | range [0, 31]
 * port="pif_rdm_desc0_data_size_i[4:0]"
 */

/* register address for bitfield desc{d}_data_size[4:0] */
<<<<<<< HEAD
#define HW_ATL_RDM_DESCDDATA_SIZE_ADR(descriptor) \
	(0x00005b18 + (descriptor) * 0x20)
/* bitmask for bitfield desc{d}_data_size[4:0] */
#define HW_ATL_RDM_DESCDDATA_SIZE_MSK 0x0000001f
/* inverted bitmask for bitfield desc{d}_data_size[4:0] */
#define HW_ATL_RDM_DESCDDATA_SIZE_MSKN 0xffffffe0
/* lower bit position of bitfield desc{d}_data_size[4:0] */
#define HW_ATL_RDM_DESCDDATA_SIZE_SHIFT 0
/* width of bitfield desc{d}_data_size[4:0] */
#define HW_ATL_RDM_DESCDDATA_SIZE_WIDTH 5
/* default value of bitfield desc{d}_data_size[4:0] */
#define HW_ATL_RDM_DESCDDATA_SIZE_DEFAULT 0x0
=======
#define rdm_descddata_size_adr(descriptor) (0x00005b18 + (descriptor) * 0x20)
/* bitmask for bitfield desc{d}_data_size[4:0] */
#define rdm_descddata_size_msk 0x0000001f
/* inverted bitmask for bitfield desc{d}_data_size[4:0] */
#define rdm_descddata_size_mskn 0xffffffe0
/* lower bit position of bitfield desc{d}_data_size[4:0] */
#define rdm_descddata_size_shift 0
/* width of bitfield desc{d}_data_size[4:0] */
#define rdm_descddata_size_width 5
/* default value of bitfield desc{d}_data_size[4:0] */
#define rdm_descddata_size_default 0x0
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* rx dca{d}_desc_en bitfield definitions
 * preprocessor definitions for the bitfield "dca{d}_desc_en".
 * parameter: dca {d} | stride size 0x4 | range [0, 31]
 * port="pif_rdm_dca_desc_en_i[0]"
 */

/* register address for bitfield dca{d}_desc_en */
<<<<<<< HEAD
#define HW_ATL_RDM_DCADDESC_EN_ADR(dca) (0x00006100 + (dca) * 0x4)
/* bitmask for bitfield dca{d}_desc_en */
#define HW_ATL_RDM_DCADDESC_EN_MSK 0x80000000
/* inverted bitmask for bitfield dca{d}_desc_en */
#define HW_ATL_RDM_DCADDESC_EN_MSKN 0x7fffffff
/* lower bit position of bitfield dca{d}_desc_en */
#define HW_ATL_RDM_DCADDESC_EN_SHIFT 31
/* width of bitfield dca{d}_desc_en */
#define HW_ATL_RDM_DCADDESC_EN_WIDTH 1
/* default value of bitfield dca{d}_desc_en */
#define HW_ATL_RDM_DCADDESC_EN_DEFAULT 0x0
=======
#define rdm_dcaddesc_en_adr(dca) (0x00006100 + (dca) * 0x4)
/* bitmask for bitfield dca{d}_desc_en */
#define rdm_dcaddesc_en_msk 0x80000000
/* inverted bitmask for bitfield dca{d}_desc_en */
#define rdm_dcaddesc_en_mskn 0x7fffffff
/* lower bit position of bitfield dca{d}_desc_en */
#define rdm_dcaddesc_en_shift 31
/* width of bitfield dca{d}_desc_en */
#define rdm_dcaddesc_en_width 1
/* default value of bitfield dca{d}_desc_en */
#define rdm_dcaddesc_en_default 0x0
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* rx desc{d}_en bitfield definitions
 * preprocessor definitions for the bitfield "desc{d}_en".
 * parameter: descriptor {d} | stride size 0x20 | range [0, 31]
 * port="pif_rdm_desc_en_i[0]"
 */

/* register address for bitfield desc{d}_en */
<<<<<<< HEAD
#define HW_ATL_RDM_DESCDEN_ADR(descriptor) (0x00005b08 + (descriptor) * 0x20)
/* bitmask for bitfield desc{d}_en */
#define HW_ATL_RDM_DESCDEN_MSK 0x80000000
/* inverted bitmask for bitfield desc{d}_en */
#define HW_ATL_RDM_DESCDEN_MSKN 0x7fffffff
/* lower bit position of bitfield desc{d}_en */
#define HW_ATL_RDM_DESCDEN_SHIFT 31
/* width of bitfield desc{d}_en */
#define HW_ATL_RDM_DESCDEN_WIDTH 1
/* default value of bitfield desc{d}_en */
#define HW_ATL_RDM_DESCDEN_DEFAULT 0x0
=======
#define rdm_descden_adr(descriptor) (0x00005b08 + (descriptor) * 0x20)
/* bitmask for bitfield desc{d}_en */
#define rdm_descden_msk 0x80000000
/* inverted bitmask for bitfield desc{d}_en */
#define rdm_descden_mskn 0x7fffffff
/* lower bit position of bitfield desc{d}_en */
#define rdm_descden_shift 31
/* width of bitfield desc{d}_en */
#define rdm_descden_width 1
/* default value of bitfield desc{d}_en */
#define rdm_descden_default 0x0
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* rx desc{d}_hdr_size[4:0] bitfield definitions
 * preprocessor definitions for the bitfield "desc{d}_hdr_size[4:0]".
 * parameter: descriptor {d} | stride size 0x20 | range [0, 31]
 * port="pif_rdm_desc0_hdr_size_i[4:0]"
 */

/* register address for bitfield desc{d}_hdr_size[4:0] */
<<<<<<< HEAD
#define HW_ATL_RDM_DESCDHDR_SIZE_ADR(descriptor) \
	(0x00005b18 + (descriptor) * 0x20)
/* bitmask for bitfield desc{d}_hdr_size[4:0] */
#define HW_ATL_RDM_DESCDHDR_SIZE_MSK 0x00001f00
/* inverted bitmask for bitfield desc{d}_hdr_size[4:0] */
#define HW_ATL_RDM_DESCDHDR_SIZE_MSKN 0xffffe0ff
/* lower bit position of bitfield desc{d}_hdr_size[4:0] */
#define HW_ATL_RDM_DESCDHDR_SIZE_SHIFT 8
/* width of bitfield desc{d}_hdr_size[4:0] */
#define HW_ATL_RDM_DESCDHDR_SIZE_WIDTH 5
/* default value of bitfield desc{d}_hdr_size[4:0] */
#define HW_ATL_RDM_DESCDHDR_SIZE_DEFAULT 0x0
=======
#define rdm_descdhdr_size_adr(descriptor) (0x00005b18 + (descriptor) * 0x20)
/* bitmask for bitfield desc{d}_hdr_size[4:0] */
#define rdm_descdhdr_size_msk 0x00001f00
/* inverted bitmask for bitfield desc{d}_hdr_size[4:0] */
#define rdm_descdhdr_size_mskn 0xffffe0ff
/* lower bit position of bitfield desc{d}_hdr_size[4:0] */
#define rdm_descdhdr_size_shift 8
/* width of bitfield desc{d}_hdr_size[4:0] */
#define rdm_descdhdr_size_width 5
/* default value of bitfield desc{d}_hdr_size[4:0] */
#define rdm_descdhdr_size_default 0x0
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* rx desc{d}_hdr_split bitfield definitions
 * preprocessor definitions for the bitfield "desc{d}_hdr_split".
 * parameter: descriptor {d} | stride size 0x20 | range [0, 31]
 * port="pif_rdm_desc_hdr_split_i[0]"
 */

/* register address for bitfield desc{d}_hdr_split */
<<<<<<< HEAD
#define HW_ATL_RDM_DESCDHDR_SPLIT_ADR(descriptor) \
	(0x00005b08 + (descriptor) * 0x20)
/* bitmask for bitfield desc{d}_hdr_split */
#define HW_ATL_RDM_DESCDHDR_SPLIT_MSK 0x10000000
/* inverted bitmask for bitfield desc{d}_hdr_split */
#define HW_ATL_RDM_DESCDHDR_SPLIT_MSKN 0xefffffff
/* lower bit position of bitfield desc{d}_hdr_split */
#define HW_ATL_RDM_DESCDHDR_SPLIT_SHIFT 28
/* width of bitfield desc{d}_hdr_split */
#define HW_ATL_RDM_DESCDHDR_SPLIT_WIDTH 1
/* default value of bitfield desc{d}_hdr_split */
#define HW_ATL_RDM_DESCDHDR_SPLIT_DEFAULT 0x0
=======
#define rdm_descdhdr_split_adr(descriptor) (0x00005b08 + (descriptor) * 0x20)
/* bitmask for bitfield desc{d}_hdr_split */
#define rdm_descdhdr_split_msk 0x10000000
/* inverted bitmask for bitfield desc{d}_hdr_split */
#define rdm_descdhdr_split_mskn 0xefffffff
/* lower bit position of bitfield desc{d}_hdr_split */
#define rdm_descdhdr_split_shift 28
/* width of bitfield desc{d}_hdr_split */
#define rdm_descdhdr_split_width 1
/* default value of bitfield desc{d}_hdr_split */
#define rdm_descdhdr_split_default 0x0
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* rx desc{d}_hd[c:0] bitfield definitions
 * preprocessor definitions for the bitfield "desc{d}_hd[c:0]".
 * parameter: descriptor {d} | stride size 0x20 | range [0, 31]
 * port="rdm_pif_desc0_hd_o[12:0]"
 */

/* register address for bitfield desc{d}_hd[c:0] */
<<<<<<< HEAD
#define HW_ATL_RDM_DESCDHD_ADR(descriptor) (0x00005b0c + (descriptor) * 0x20)
/* bitmask for bitfield desc{d}_hd[c:0] */
#define HW_ATL_RDM_DESCDHD_MSK 0x00001fff
/* inverted bitmask for bitfield desc{d}_hd[c:0] */
#define HW_ATL_RDM_DESCDHD_MSKN 0xffffe000
/* lower bit position of bitfield desc{d}_hd[c:0] */
#define HW_ATL_RDM_DESCDHD_SHIFT 0
/* width of bitfield desc{d}_hd[c:0] */
#define HW_ATL_RDM_DESCDHD_WIDTH 13
=======
#define rdm_descdhd_adr(descriptor) (0x00005b0c + (descriptor) * 0x20)
/* bitmask for bitfield desc{d}_hd[c:0] */
#define rdm_descdhd_msk 0x00001fff
/* inverted bitmask for bitfield desc{d}_hd[c:0] */
#define rdm_descdhd_mskn 0xffffe000
/* lower bit position of bitfield desc{d}_hd[c:0] */
#define rdm_descdhd_shift 0
/* width of bitfield desc{d}_hd[c:0] */
#define rdm_descdhd_width 13
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* rx desc{d}_len[9:0] bitfield definitions
 * preprocessor definitions for the bitfield "desc{d}_len[9:0]".
 * parameter: descriptor {d} | stride size 0x20 | range [0, 31]
 * port="pif_rdm_desc0_len_i[9:0]"
 */

/* register address for bitfield desc{d}_len[9:0] */
<<<<<<< HEAD
#define HW_ATL_RDM_DESCDLEN_ADR(descriptor) (0x00005b08 + (descriptor) * 0x20)
/* bitmask for bitfield desc{d}_len[9:0] */
#define HW_ATL_RDM_DESCDLEN_MSK 0x00001ff8
/* inverted bitmask for bitfield desc{d}_len[9:0] */
#define HW_ATL_RDM_DESCDLEN_MSKN 0xffffe007
/* lower bit position of bitfield desc{d}_len[9:0] */
#define HW_ATL_RDM_DESCDLEN_SHIFT 3
/* width of bitfield desc{d}_len[9:0] */
#define HW_ATL_RDM_DESCDLEN_WIDTH 10
/* default value of bitfield desc{d}_len[9:0] */
#define HW_ATL_RDM_DESCDLEN_DEFAULT 0x0
=======
#define rdm_descdlen_adr(descriptor) (0x00005b08 + (descriptor) * 0x20)
/* bitmask for bitfield desc{d}_len[9:0] */
#define rdm_descdlen_msk 0x00001ff8
/* inverted bitmask for bitfield desc{d}_len[9:0] */
#define rdm_descdlen_mskn 0xffffe007
/* lower bit position of bitfield desc{d}_len[9:0] */
#define rdm_descdlen_shift 3
/* width of bitfield desc{d}_len[9:0] */
#define rdm_descdlen_width 10
/* default value of bitfield desc{d}_len[9:0] */
#define rdm_descdlen_default 0x0
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* rx desc{d}_reset bitfield definitions
 * preprocessor definitions for the bitfield "desc{d}_reset".
 * parameter: descriptor {d} | stride size 0x20 | range [0, 31]
 * port="pif_rdm_q_pf_res_i[0]"
 */

/* register address for bitfield desc{d}_reset */
<<<<<<< HEAD
#define HW_ATL_RDM_DESCDRESET_ADR(descriptor) (0x00005b08 + (descriptor) * 0x20)
/* bitmask for bitfield desc{d}_reset */
#define HW_ATL_RDM_DESCDRESET_MSK 0x02000000
/* inverted bitmask for bitfield desc{d}_reset */
#define HW_ATL_RDM_DESCDRESET_MSKN 0xfdffffff
/* lower bit position of bitfield desc{d}_reset */
#define HW_ATL_RDM_DESCDRESET_SHIFT 25
/* width of bitfield desc{d}_reset */
#define HW_ATL_RDM_DESCDRESET_WIDTH 1
/* default value of bitfield desc{d}_reset */
#define HW_ATL_RDM_DESCDRESET_DEFAULT 0x0

/* rdm_desc_init_i bitfield definitions
 * preprocessor definitions for the bitfield rdm_desc_init_i.
 * port="pif_rdm_desc_init_i"
 */

/* register address for bitfield rdm_desc_init_i */
#define HW_ATL_RDM_RX_DMA_DESC_CACHE_INIT_ADR 0x00005a00
/* bitmask for bitfield rdm_desc_init_i */
#define HW_ATL_RDM_RX_DMA_DESC_CACHE_INIT_MSK 0xffffffff
/* inverted bitmask for bitfield rdm_desc_init_i */
#define HW_ATL_RDM_RX_DMA_DESC_CACHE_INIT_MSKN 0x00000000
/* lower bit position of bitfield  rdm_desc_init_i */
#define HW_ATL_RDM_RX_DMA_DESC_CACHE_INIT_SHIFT 0
/* width of bitfield rdm_desc_init_i */
#define HW_ATL_RDM_RX_DMA_DESC_CACHE_INIT_WIDTH 32
/* default value of bitfield rdm_desc_init_i */
#define HW_ATL_RDM_RX_DMA_DESC_CACHE_INIT_DEFAULT 0x0
=======
#define rdm_descdreset_adr(descriptor) (0x00005b08 + (descriptor) * 0x20)
/* bitmask for bitfield desc{d}_reset */
#define rdm_descdreset_msk 0x02000000
/* inverted bitmask for bitfield desc{d}_reset */
#define rdm_descdreset_mskn 0xfdffffff
/* lower bit position of bitfield desc{d}_reset */
#define rdm_descdreset_shift 25
/* width of bitfield desc{d}_reset */
#define rdm_descdreset_width 1
/* default value of bitfield desc{d}_reset */
#define rdm_descdreset_default 0x0
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* rx int_desc_wrb_en bitfield definitions
 * preprocessor definitions for the bitfield "int_desc_wrb_en".
 * port="pif_rdm_int_desc_wrb_en_i"
 */

/* register address for bitfield int_desc_wrb_en */
<<<<<<< HEAD
#define HW_ATL_RDM_INT_DESC_WRB_EN_ADR 0x00005a30
/* bitmask for bitfield int_desc_wrb_en */
#define HW_ATL_RDM_INT_DESC_WRB_EN_MSK 0x00000004
/* inverted bitmask for bitfield int_desc_wrb_en */
#define HW_ATL_RDM_INT_DESC_WRB_EN_MSKN 0xfffffffb
/* lower bit position of bitfield int_desc_wrb_en */
#define HW_ATL_RDM_INT_DESC_WRB_EN_SHIFT 2
/* width of bitfield int_desc_wrb_en */
#define HW_ATL_RDM_INT_DESC_WRB_EN_WIDTH 1
/* default value of bitfield int_desc_wrb_en */
#define HW_ATL_RDM_INT_DESC_WRB_EN_DEFAULT 0x0
=======
#define rdm_int_desc_wrb_en_adr 0x00005a30
/* bitmask for bitfield int_desc_wrb_en */
#define rdm_int_desc_wrb_en_msk 0x00000004
/* inverted bitmask for bitfield int_desc_wrb_en */
#define rdm_int_desc_wrb_en_mskn 0xfffffffb
/* lower bit position of bitfield int_desc_wrb_en */
#define rdm_int_desc_wrb_en_shift 2
/* width of bitfield int_desc_wrb_en */
#define rdm_int_desc_wrb_en_width 1
/* default value of bitfield int_desc_wrb_en */
#define rdm_int_desc_wrb_en_default 0x0
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* rx dca{d}_hdr_en bitfield definitions
 * preprocessor definitions for the bitfield "dca{d}_hdr_en".
 * parameter: dca {d} | stride size 0x4 | range [0, 31]
 * port="pif_rdm_dca_hdr_en_i[0]"
 */

/* register address for bitfield dca{d}_hdr_en */
<<<<<<< HEAD
#define HW_ATL_RDM_DCADHDR_EN_ADR(dca) (0x00006100 + (dca) * 0x4)
/* bitmask for bitfield dca{d}_hdr_en */
#define HW_ATL_RDM_DCADHDR_EN_MSK 0x40000000
/* inverted bitmask for bitfield dca{d}_hdr_en */
#define HW_ATL_RDM_DCADHDR_EN_MSKN 0xbfffffff
/* lower bit position of bitfield dca{d}_hdr_en */
#define HW_ATL_RDM_DCADHDR_EN_SHIFT 30
/* width of bitfield dca{d}_hdr_en */
#define HW_ATL_RDM_DCADHDR_EN_WIDTH 1
/* default value of bitfield dca{d}_hdr_en */
#define HW_ATL_RDM_DCADHDR_EN_DEFAULT 0x0
=======
#define rdm_dcadhdr_en_adr(dca) (0x00006100 + (dca) * 0x4)
/* bitmask for bitfield dca{d}_hdr_en */
#define rdm_dcadhdr_en_msk 0x40000000
/* inverted bitmask for bitfield dca{d}_hdr_en */
#define rdm_dcadhdr_en_mskn 0xbfffffff
/* lower bit position of bitfield dca{d}_hdr_en */
#define rdm_dcadhdr_en_shift 30
/* width of bitfield dca{d}_hdr_en */
#define rdm_dcadhdr_en_width 1
/* default value of bitfield dca{d}_hdr_en */
#define rdm_dcadhdr_en_default 0x0
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* rx dca{d}_pay_en bitfield definitions
 * preprocessor definitions for the bitfield "dca{d}_pay_en".
 * parameter: dca {d} | stride size 0x4 | range [0, 31]
 * port="pif_rdm_dca_pay_en_i[0]"
 */

/* register address for bitfield dca{d}_pay_en */
<<<<<<< HEAD
#define HW_ATL_RDM_DCADPAY_EN_ADR(dca) (0x00006100 + (dca) * 0x4)
/* bitmask for bitfield dca{d}_pay_en */
#define HW_ATL_RDM_DCADPAY_EN_MSK 0x20000000
/* inverted bitmask for bitfield dca{d}_pay_en */
#define HW_ATL_RDM_DCADPAY_EN_MSKN 0xdfffffff
/* lower bit position of bitfield dca{d}_pay_en */
#define HW_ATL_RDM_DCADPAY_EN_SHIFT 29
/* width of bitfield dca{d}_pay_en */
#define HW_ATL_RDM_DCADPAY_EN_WIDTH 1
/* default value of bitfield dca{d}_pay_en */
#define HW_ATL_RDM_DCADPAY_EN_DEFAULT 0x0
=======
#define rdm_dcadpay_en_adr(dca) (0x00006100 + (dca) * 0x4)
/* bitmask for bitfield dca{d}_pay_en */
#define rdm_dcadpay_en_msk 0x20000000
/* inverted bitmask for bitfield dca{d}_pay_en */
#define rdm_dcadpay_en_mskn 0xdfffffff
/* lower bit position of bitfield dca{d}_pay_en */
#define rdm_dcadpay_en_shift 29
/* width of bitfield dca{d}_pay_en */
#define rdm_dcadpay_en_width 1
/* default value of bitfield dca{d}_pay_en */
#define rdm_dcadpay_en_default 0x0
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* RX rdm_int_rim_en Bitfield Definitions
 * Preprocessor definitions for the bitfield "rdm_int_rim_en".
 * PORT="pif_rdm_int_rim_en_i"
 */

/* Register address for bitfield rdm_int_rim_en */
<<<<<<< HEAD
#define HW_ATL_RDM_INT_RIM_EN_ADR 0x00005A30
/* Bitmask for bitfield rdm_int_rim_en */
#define HW_ATL_RDM_INT_RIM_EN_MSK 0x00000008
/* Inverted bitmask for bitfield rdm_int_rim_en */
#define HW_ATL_RDM_INT_RIM_EN_MSKN 0xFFFFFFF7
/* Lower bit position of bitfield rdm_int_rim_en */
#define HW_ATL_RDM_INT_RIM_EN_SHIFT 3
/* Width of bitfield rdm_int_rim_en */
#define HW_ATL_RDM_INT_RIM_EN_WIDTH 1
/* Default value of bitfield rdm_int_rim_en */
#define HW_ATL_RDM_INT_RIM_EN_DEFAULT 0x0
=======
#define rdm_int_rim_en_adr 0x00005A30
/* Bitmask for bitfield rdm_int_rim_en */
#define rdm_int_rim_en_msk 0x00000008
/* Inverted bitmask for bitfield rdm_int_rim_en */
#define rdm_int_rim_en_mskn 0xFFFFFFF7
/* Lower bit position of bitfield rdm_int_rim_en */
#define rdm_int_rim_en_shift 3
/* Width of bitfield rdm_int_rim_en */
#define rdm_int_rim_en_width 1
/* Default value of bitfield rdm_int_rim_en */
#define rdm_int_rim_en_default 0x0
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* general interrupt mapping register definitions
 * preprocessor definitions for general interrupt mapping register
 * base address: 0x00002180
 * parameter: regidx {f} | stride size 0x4 | range [0, 3]
 */
<<<<<<< HEAD
#define HW_ATL_GEN_INTR_MAP_ADR(regidx) (0x00002180u + (regidx) * 0x4)
=======
#define gen_intr_map_adr(regidx) (0x00002180u + (regidx) * 0x4)
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* general interrupt status register definitions
 * preprocessor definitions for general interrupt status register
 * address: 0x000021A0
 */

<<<<<<< HEAD
#define HW_ATL_GEN_INTR_STAT_ADR 0x000021A4U
=======
#define gen_intr_stat_adr 0x000021A4U
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* interrupt global control register  definitions
 * preprocessor definitions for interrupt global control register
 * address: 0x00002300
 */
<<<<<<< HEAD
#define HW_ATL_INTR_GLB_CTL_ADR 0x00002300u
=======
#define intr_glb_ctl_adr 0x00002300u
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* interrupt throttle register definitions
 * preprocessor definitions for interrupt throttle register
 * base address: 0x00002800
 * parameter: throttle {t} | stride size 0x4 | range [0, 31]
 */
<<<<<<< HEAD
#define HW_ATL_INTR_THR_ADR(throttle) (0x00002800u + (throttle) * 0x4)
=======
#define intr_thr_adr(throttle) (0x00002800u + (throttle) * 0x4)
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* rx dma descriptor base address lsw definitions
 * preprocessor definitions for rx dma descriptor base address lsw
 * base address: 0x00005b00
 * parameter: descriptor {d} | stride size 0x20 | range [0, 31]
 */
<<<<<<< HEAD
#define HW_ATL_RX_DMA_DESC_BASE_ADDRLSW_ADR(descriptor) \
=======
#define rx_dma_desc_base_addrlsw_adr(descriptor) \
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
(0x00005b00u + (descriptor) * 0x20)

/* rx dma descriptor base address msw definitions
 * preprocessor definitions for rx dma descriptor base address msw
 * base address: 0x00005b04
 * parameter: descriptor {d} | stride size 0x20 | range [0, 31]
 */
<<<<<<< HEAD
#define HW_ATL_RX_DMA_DESC_BASE_ADDRMSW_ADR(descriptor) \
=======
#define rx_dma_desc_base_addrmsw_adr(descriptor) \
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
(0x00005b04u + (descriptor) * 0x20)

/* rx dma descriptor status register definitions
 * preprocessor definitions for rx dma descriptor status register
 * base address: 0x00005b14
 * parameter: descriptor {d} | stride size 0x20 | range [0, 31]
 */
<<<<<<< HEAD
#define HW_ATL_RX_DMA_DESC_STAT_ADR(descriptor) \
	(0x00005b14u + (descriptor) * 0x20)
=======
#define rx_dma_desc_stat_adr(descriptor) (0x00005b14u + (descriptor) * 0x20)
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* rx dma descriptor tail pointer register definitions
 * preprocessor definitions for rx dma descriptor tail pointer register
 * base address: 0x00005b10
 * parameter: descriptor {d} | stride size 0x20 | range [0, 31]
 */
<<<<<<< HEAD
#define HW_ATL_RX_DMA_DESC_TAIL_PTR_ADR(descriptor) \
	(0x00005b10u + (descriptor) * 0x20)
=======
#define rx_dma_desc_tail_ptr_adr(descriptor) (0x00005b10u + (descriptor) * 0x20)
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* rx interrupt moderation control register definitions
 * Preprocessor definitions for RX Interrupt Moderation Control Register
 * Base Address: 0x00005A40
 * Parameter: RIM {R} | stride size 0x4 | range [0, 31]
 */
<<<<<<< HEAD
#define HW_ATL_RX_INTR_MODERATION_CTL_ADR(rim) (0x00005A40u + (rim) * 0x4)
=======
#define rx_intr_moderation_ctl_adr(rim) (0x00005A40u + (rim) * 0x4)
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* rx filter multicast filter mask register definitions
 * preprocessor definitions for rx filter multicast filter mask register
 * address: 0x00005270
 */
<<<<<<< HEAD
#define HW_ATL_RX_FLR_MCST_FLR_MSK_ADR 0x00005270u
=======
#define rx_flr_mcst_flr_msk_adr 0x00005270u
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* rx filter multicast filter register definitions
 * preprocessor definitions for rx filter multicast filter register
 * base address: 0x00005250
 * parameter: filter {f} | stride size 0x4 | range [0, 7]
 */
<<<<<<< HEAD
#define HW_ATL_RX_FLR_MCST_FLR_ADR(filter) (0x00005250u + (filter) * 0x4)
=======
#define rx_flr_mcst_flr_adr(filter) (0x00005250u + (filter) * 0x4)
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* RX Filter RSS Control Register 1 Definitions
 * Preprocessor definitions for RX Filter RSS Control Register 1
 * Address: 0x000054C0
 */
<<<<<<< HEAD
#define HW_ATL_RX_FLR_RSS_CONTROL1_ADR 0x000054C0u
=======
#define rx_flr_rss_control1_adr 0x000054C0u
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* RX Filter Control Register 2 Definitions
 * Preprocessor definitions for RX Filter Control Register 2
 * Address: 0x00005104
 */
<<<<<<< HEAD
#define HW_ATL_RX_FLR_CONTROL2_ADR 0x00005104u
=======
#define rx_flr_control2_adr 0x00005104u
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* tx tx dma debug control [1f:0] bitfield definitions
 * preprocessor definitions for the bitfield "tx dma debug control [1f:0]".
 * port="pif_tdm_debug_cntl_i[31:0]"
 */

/* register address for bitfield tx dma debug control [1f:0] */
<<<<<<< HEAD
#define HW_ATL_TDM_TX_DMA_DEBUG_CTL_ADR 0x00008920
/* bitmask for bitfield tx dma debug control [1f:0] */
#define HW_ATL_TDM_TX_DMA_DEBUG_CTL_MSK 0xffffffff
/* inverted bitmask for bitfield tx dma debug control [1f:0] */
#define HW_ATL_TDM_TX_DMA_DEBUG_CTL_MSKN 0x00000000
/* lower bit position of bitfield tx dma debug control [1f:0] */
#define HW_ATL_TDM_TX_DMA_DEBUG_CTL_SHIFT 0
/* width of bitfield tx dma debug control [1f:0] */
#define HW_ATL_TDM_TX_DMA_DEBUG_CTL_WIDTH 32
/* default value of bitfield tx dma debug control [1f:0] */
#define HW_ATL_TDM_TX_DMA_DEBUG_CTL_DEFAULT 0x0
=======
#define tdm_tx_dma_debug_ctl_adr 0x00008920
/* bitmask for bitfield tx dma debug control [1f:0] */
#define tdm_tx_dma_debug_ctl_msk 0xffffffff
/* inverted bitmask for bitfield tx dma debug control [1f:0] */
#define tdm_tx_dma_debug_ctl_mskn 0x00000000
/* lower bit position of bitfield tx dma debug control [1f:0] */
#define tdm_tx_dma_debug_ctl_shift 0
/* width of bitfield tx dma debug control [1f:0] */
#define tdm_tx_dma_debug_ctl_width 32
/* default value of bitfield tx dma debug control [1f:0] */
#define tdm_tx_dma_debug_ctl_default 0x0
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* tx dma descriptor base address lsw definitions
 * preprocessor definitions for tx dma descriptor base address lsw
 * base address: 0x00007c00
 * parameter: descriptor {d} | stride size 0x40 | range [0, 31]
 */
<<<<<<< HEAD
#define HW_ATL_TX_DMA_DESC_BASE_ADDRLSW_ADR(descriptor) \
=======
#define tx_dma_desc_base_addrlsw_adr(descriptor) \
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	(0x00007c00u + (descriptor) * 0x40)

/* tx dma descriptor tail pointer register definitions
 * preprocessor definitions for tx dma descriptor tail pointer register
 * base address: 0x00007c10
 *  parameter: descriptor {d} | stride size 0x40 | range [0, 31]
 */
<<<<<<< HEAD
#define HW_ATL_TX_DMA_DESC_TAIL_PTR_ADR(descriptor) \
	(0x00007c10u + (descriptor) * 0x40)
=======
#define tx_dma_desc_tail_ptr_adr(descriptor) (0x00007c10u + (descriptor) * 0x40)
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* rx dma_sys_loopback bitfield definitions
 * preprocessor definitions for the bitfield "dma_sys_loopback".
 * port="pif_rpb_dma_sys_lbk_i"
 */

/* register address for bitfield dma_sys_loopback */
<<<<<<< HEAD
#define HW_ATL_RPB_DMA_SYS_LBK_ADR 0x00005000
/* bitmask for bitfield dma_sys_loopback */
#define HW_ATL_RPB_DMA_SYS_LBK_MSK 0x00000040
/* inverted bitmask for bitfield dma_sys_loopback */
#define HW_ATL_RPB_DMA_SYS_LBK_MSKN 0xffffffbf
/* lower bit position of bitfield dma_sys_loopback */
#define HW_ATL_RPB_DMA_SYS_LBK_SHIFT 6
/* width of bitfield dma_sys_loopback */
#define HW_ATL_RPB_DMA_SYS_LBK_WIDTH 1
/* default value of bitfield dma_sys_loopback */
#define HW_ATL_RPB_DMA_SYS_LBK_DEFAULT 0x0
=======
#define rpb_dma_sys_lbk_adr 0x00005000
/* bitmask for bitfield dma_sys_loopback */
#define rpb_dma_sys_lbk_msk 0x00000040
/* inverted bitmask for bitfield dma_sys_loopback */
#define rpb_dma_sys_lbk_mskn 0xffffffbf
/* lower bit position of bitfield dma_sys_loopback */
#define rpb_dma_sys_lbk_shift 6
/* width of bitfield dma_sys_loopback */
#define rpb_dma_sys_lbk_width 1
/* default value of bitfield dma_sys_loopback */
#define rpb_dma_sys_lbk_default 0x0
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* rx rx_tc_mode bitfield definitions
 * preprocessor definitions for the bitfield "rx_tc_mode".
 * port="pif_rpb_rx_tc_mode_i,pif_rpf_rx_tc_mode_i"
 */

/* register address for bitfield rx_tc_mode */
<<<<<<< HEAD
#define HW_ATL_RPB_RPF_RX_TC_MODE_ADR 0x00005700
/* bitmask for bitfield rx_tc_mode */
#define HW_ATL_RPB_RPF_RX_TC_MODE_MSK 0x00000100
/* inverted bitmask for bitfield rx_tc_mode */
#define HW_ATL_RPB_RPF_RX_TC_MODE_MSKN 0xfffffeff
/* lower bit position of bitfield rx_tc_mode */
#define HW_ATL_RPB_RPF_RX_TC_MODE_SHIFT 8
/* width of bitfield rx_tc_mode */
#define HW_ATL_RPB_RPF_RX_TC_MODE_WIDTH 1
/* default value of bitfield rx_tc_mode */
#define HW_ATL_RPB_RPF_RX_TC_MODE_DEFAULT 0x0
=======
#define rpb_rpf_rx_tc_mode_adr 0x00005700
/* bitmask for bitfield rx_tc_mode */
#define rpb_rpf_rx_tc_mode_msk 0x00000100
/* inverted bitmask for bitfield rx_tc_mode */
#define rpb_rpf_rx_tc_mode_mskn 0xfffffeff
/* lower bit position of bitfield rx_tc_mode */
#define rpb_rpf_rx_tc_mode_shift 8
/* width of bitfield rx_tc_mode */
#define rpb_rpf_rx_tc_mode_width 1
/* default value of bitfield rx_tc_mode */
#define rpb_rpf_rx_tc_mode_default 0x0
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* rx rx_buf_en bitfield definitions
 * preprocessor definitions for the bitfield "rx_buf_en".
 * port="pif_rpb_rx_buf_en_i"
 */

/* register address for bitfield rx_buf_en */
<<<<<<< HEAD
#define HW_ATL_RPB_RX_BUF_EN_ADR 0x00005700
/* bitmask for bitfield rx_buf_en */
#define HW_ATL_RPB_RX_BUF_EN_MSK 0x00000001
/* inverted bitmask for bitfield rx_buf_en */
#define HW_ATL_RPB_RX_BUF_EN_MSKN 0xfffffffe
/* lower bit position of bitfield rx_buf_en */
#define HW_ATL_RPB_RX_BUF_EN_SHIFT 0
/* width of bitfield rx_buf_en */
#define HW_ATL_RPB_RX_BUF_EN_WIDTH 1
/* default value of bitfield rx_buf_en */
#define HW_ATL_RPB_RX_BUF_EN_DEFAULT 0x0
=======
#define rpb_rx_buf_en_adr 0x00005700
/* bitmask for bitfield rx_buf_en */
#define rpb_rx_buf_en_msk 0x00000001
/* inverted bitmask for bitfield rx_buf_en */
#define rpb_rx_buf_en_mskn 0xfffffffe
/* lower bit position of bitfield rx_buf_en */
#define rpb_rx_buf_en_shift 0
/* width of bitfield rx_buf_en */
#define rpb_rx_buf_en_width 1
/* default value of bitfield rx_buf_en */
#define rpb_rx_buf_en_default 0x0
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* rx rx{b}_hi_thresh[d:0] bitfield definitions
 * preprocessor definitions for the bitfield "rx{b}_hi_thresh[d:0]".
 * parameter: buffer {b} | stride size 0x10 | range [0, 7]
 * port="pif_rpb_rx0_hi_thresh_i[13:0]"
 */

/* register address for bitfield rx{b}_hi_thresh[d:0] */
<<<<<<< HEAD
#define HW_ATL_RPB_RXBHI_THRESH_ADR(buffer) (0x00005714 + (buffer) * 0x10)
/* bitmask for bitfield rx{b}_hi_thresh[d:0] */
#define HW_ATL_RPB_RXBHI_THRESH_MSK 0x3fff0000
/* inverted bitmask for bitfield rx{b}_hi_thresh[d:0] */
#define HW_ATL_RPB_RXBHI_THRESH_MSKN 0xc000ffff
/* lower bit position of bitfield rx{b}_hi_thresh[d:0] */
#define HW_ATL_RPB_RXBHI_THRESH_SHIFT 16
/* width of bitfield rx{b}_hi_thresh[d:0] */
#define HW_ATL_RPB_RXBHI_THRESH_WIDTH 14
/* default value of bitfield rx{b}_hi_thresh[d:0] */
#define HW_ATL_RPB_RXBHI_THRESH_DEFAULT 0x0
=======
#define rpb_rxbhi_thresh_adr(buffer) (0x00005714 + (buffer) * 0x10)
/* bitmask for bitfield rx{b}_hi_thresh[d:0] */
#define rpb_rxbhi_thresh_msk 0x3fff0000
/* inverted bitmask for bitfield rx{b}_hi_thresh[d:0] */
#define rpb_rxbhi_thresh_mskn 0xc000ffff
/* lower bit position of bitfield rx{b}_hi_thresh[d:0] */
#define rpb_rxbhi_thresh_shift 16
/* width of bitfield rx{b}_hi_thresh[d:0] */
#define rpb_rxbhi_thresh_width 14
/* default value of bitfield rx{b}_hi_thresh[d:0] */
#define rpb_rxbhi_thresh_default 0x0
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* rx rx{b}_lo_thresh[d:0] bitfield definitions
 * preprocessor definitions for the bitfield "rx{b}_lo_thresh[d:0]".
 * parameter: buffer {b} | stride size 0x10 | range [0, 7]
 * port="pif_rpb_rx0_lo_thresh_i[13:0]"
 */

/* register address for bitfield rx{b}_lo_thresh[d:0] */
<<<<<<< HEAD
#define HW_ATL_RPB_RXBLO_THRESH_ADR(buffer) (0x00005714 + (buffer) * 0x10)
/* bitmask for bitfield rx{b}_lo_thresh[d:0] */
#define HW_ATL_RPB_RXBLO_THRESH_MSK 0x00003fff
/* inverted bitmask for bitfield rx{b}_lo_thresh[d:0] */
#define HW_ATL_RPB_RXBLO_THRESH_MSKN 0xffffc000
/* lower bit position of bitfield rx{b}_lo_thresh[d:0] */
#define HW_ATL_RPB_RXBLO_THRESH_SHIFT 0
/* width of bitfield rx{b}_lo_thresh[d:0] */
#define HW_ATL_RPB_RXBLO_THRESH_WIDTH 14
/* default value of bitfield rx{b}_lo_thresh[d:0] */
#define HW_ATL_RPB_RXBLO_THRESH_DEFAULT 0x0
=======
#define rpb_rxblo_thresh_adr(buffer) (0x00005714 + (buffer) * 0x10)
/* bitmask for bitfield rx{b}_lo_thresh[d:0] */
#define rpb_rxblo_thresh_msk 0x00003fff
/* inverted bitmask for bitfield rx{b}_lo_thresh[d:0] */
#define rpb_rxblo_thresh_mskn 0xffffc000
/* lower bit position of bitfield rx{b}_lo_thresh[d:0] */
#define rpb_rxblo_thresh_shift 0
/* width of bitfield rx{b}_lo_thresh[d:0] */
#define rpb_rxblo_thresh_width 14
/* default value of bitfield rx{b}_lo_thresh[d:0] */
#define rpb_rxblo_thresh_default 0x0
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* rx rx_fc_mode[1:0] bitfield definitions
 * preprocessor definitions for the bitfield "rx_fc_mode[1:0]".
 * port="pif_rpb_rx_fc_mode_i[1:0]"
 */

/* register address for bitfield rx_fc_mode[1:0] */
<<<<<<< HEAD
#define HW_ATL_RPB_RX_FC_MODE_ADR 0x00005700
/* bitmask for bitfield rx_fc_mode[1:0] */
#define HW_ATL_RPB_RX_FC_MODE_MSK 0x00000030
/* inverted bitmask for bitfield rx_fc_mode[1:0] */
#define HW_ATL_RPB_RX_FC_MODE_MSKN 0xffffffcf
/* lower bit position of bitfield rx_fc_mode[1:0] */
#define HW_ATL_RPB_RX_FC_MODE_SHIFT 4
/* width of bitfield rx_fc_mode[1:0] */
#define HW_ATL_RPB_RX_FC_MODE_WIDTH 2
/* default value of bitfield rx_fc_mode[1:0] */
#define HW_ATL_RPB_RX_FC_MODE_DEFAULT 0x0
=======
#define rpb_rx_fc_mode_adr 0x00005700
/* bitmask for bitfield rx_fc_mode[1:0] */
#define rpb_rx_fc_mode_msk 0x00000030
/* inverted bitmask for bitfield rx_fc_mode[1:0] */
#define rpb_rx_fc_mode_mskn 0xffffffcf
/* lower bit position of bitfield rx_fc_mode[1:0] */
#define rpb_rx_fc_mode_shift 4
/* width of bitfield rx_fc_mode[1:0] */
#define rpb_rx_fc_mode_width 2
/* default value of bitfield rx_fc_mode[1:0] */
#define rpb_rx_fc_mode_default 0x0
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* rx rx{b}_buf_size[8:0] bitfield definitions
 * preprocessor definitions for the bitfield "rx{b}_buf_size[8:0]".
 * parameter: buffer {b} | stride size 0x10 | range [0, 7]
 * port="pif_rpb_rx0_buf_size_i[8:0]"
 */

/* register address for bitfield rx{b}_buf_size[8:0] */
<<<<<<< HEAD
#define HW_ATL_RPB_RXBBUF_SIZE_ADR(buffer) (0x00005710 + (buffer) * 0x10)
/* bitmask for bitfield rx{b}_buf_size[8:0] */
#define HW_ATL_RPB_RXBBUF_SIZE_MSK 0x000001ff
/* inverted bitmask for bitfield rx{b}_buf_size[8:0] */
#define HW_ATL_RPB_RXBBUF_SIZE_MSKN 0xfffffe00
/* lower bit position of bitfield rx{b}_buf_size[8:0] */
#define HW_ATL_RPB_RXBBUF_SIZE_SHIFT 0
/* width of bitfield rx{b}_buf_size[8:0] */
#define HW_ATL_RPB_RXBBUF_SIZE_WIDTH 9
/* default value of bitfield rx{b}_buf_size[8:0] */
#define HW_ATL_RPB_RXBBUF_SIZE_DEFAULT 0x0
=======
#define rpb_rxbbuf_size_adr(buffer) (0x00005710 + (buffer) * 0x10)
/* bitmask for bitfield rx{b}_buf_size[8:0] */
#define rpb_rxbbuf_size_msk 0x000001ff
/* inverted bitmask for bitfield rx{b}_buf_size[8:0] */
#define rpb_rxbbuf_size_mskn 0xfffffe00
/* lower bit position of bitfield rx{b}_buf_size[8:0] */
#define rpb_rxbbuf_size_shift 0
/* width of bitfield rx{b}_buf_size[8:0] */
#define rpb_rxbbuf_size_width 9
/* default value of bitfield rx{b}_buf_size[8:0] */
#define rpb_rxbbuf_size_default 0x0
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* rx rx{b}_xoff_en bitfield definitions
 * preprocessor definitions for the bitfield "rx{b}_xoff_en".
 * parameter: buffer {b} | stride size 0x10 | range [0, 7]
 * port="pif_rpb_rx_xoff_en_i[0]"
 */

/* register address for bitfield rx{b}_xoff_en */
<<<<<<< HEAD
#define HW_ATL_RPB_RXBXOFF_EN_ADR(buffer) (0x00005714 + (buffer) * 0x10)
/* bitmask for bitfield rx{b}_xoff_en */
#define HW_ATL_RPB_RXBXOFF_EN_MSK 0x80000000
/* inverted bitmask for bitfield rx{b}_xoff_en */
#define HW_ATL_RPB_RXBXOFF_EN_MSKN 0x7fffffff
/* lower bit position of bitfield rx{b}_xoff_en */
#define HW_ATL_RPB_RXBXOFF_EN_SHIFT 31
/* width of bitfield rx{b}_xoff_en */
#define HW_ATL_RPB_RXBXOFF_EN_WIDTH 1
/* default value of bitfield rx{b}_xoff_en */
#define HW_ATL_RPB_RXBXOFF_EN_DEFAULT 0x0
=======
#define rpb_rxbxoff_en_adr(buffer) (0x00005714 + (buffer) * 0x10)
/* bitmask for bitfield rx{b}_xoff_en */
#define rpb_rxbxoff_en_msk 0x80000000
/* inverted bitmask for bitfield rx{b}_xoff_en */
#define rpb_rxbxoff_en_mskn 0x7fffffff
/* lower bit position of bitfield rx{b}_xoff_en */
#define rpb_rxbxoff_en_shift 31
/* width of bitfield rx{b}_xoff_en */
#define rpb_rxbxoff_en_width 1
/* default value of bitfield rx{b}_xoff_en */
#define rpb_rxbxoff_en_default 0x0
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* rx l2_bc_thresh[f:0] bitfield definitions
 * preprocessor definitions for the bitfield "l2_bc_thresh[f:0]".
 * port="pif_rpf_l2_bc_thresh_i[15:0]"
 */

/* register address for bitfield l2_bc_thresh[f:0] */
<<<<<<< HEAD
#define HW_ATL_RPFL2BC_THRESH_ADR 0x00005100
/* bitmask for bitfield l2_bc_thresh[f:0] */
#define HW_ATL_RPFL2BC_THRESH_MSK 0xffff0000
/* inverted bitmask for bitfield l2_bc_thresh[f:0] */
#define HW_ATL_RPFL2BC_THRESH_MSKN 0x0000ffff
/* lower bit position of bitfield l2_bc_thresh[f:0] */
#define HW_ATL_RPFL2BC_THRESH_SHIFT 16
/* width of bitfield l2_bc_thresh[f:0] */
#define HW_ATL_RPFL2BC_THRESH_WIDTH 16
/* default value of bitfield l2_bc_thresh[f:0] */
#define HW_ATL_RPFL2BC_THRESH_DEFAULT 0x0
=======
#define rpfl2bc_thresh_adr 0x00005100
/* bitmask for bitfield l2_bc_thresh[f:0] */
#define rpfl2bc_thresh_msk 0xffff0000
/* inverted bitmask for bitfield l2_bc_thresh[f:0] */
#define rpfl2bc_thresh_mskn 0x0000ffff
/* lower bit position of bitfield l2_bc_thresh[f:0] */
#define rpfl2bc_thresh_shift 16
/* width of bitfield l2_bc_thresh[f:0] */
#define rpfl2bc_thresh_width 16
/* default value of bitfield l2_bc_thresh[f:0] */
#define rpfl2bc_thresh_default 0x0
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* rx l2_bc_en bitfield definitions
 * preprocessor definitions for the bitfield "l2_bc_en".
 * port="pif_rpf_l2_bc_en_i"
 */

/* register address for bitfield l2_bc_en */
<<<<<<< HEAD
#define HW_ATL_RPFL2BC_EN_ADR 0x00005100
/* bitmask for bitfield l2_bc_en */
#define HW_ATL_RPFL2BC_EN_MSK 0x00000001
/* inverted bitmask for bitfield l2_bc_en */
#define HW_ATL_RPFL2BC_EN_MSKN 0xfffffffe
/* lower bit position of bitfield l2_bc_en */
#define HW_ATL_RPFL2BC_EN_SHIFT 0
/* width of bitfield l2_bc_en */
#define HW_ATL_RPFL2BC_EN_WIDTH 1
/* default value of bitfield l2_bc_en */
#define HW_ATL_RPFL2BC_EN_DEFAULT 0x0
=======
#define rpfl2bc_en_adr 0x00005100
/* bitmask for bitfield l2_bc_en */
#define rpfl2bc_en_msk 0x00000001
/* inverted bitmask for bitfield l2_bc_en */
#define rpfl2bc_en_mskn 0xfffffffe
/* lower bit position of bitfield l2_bc_en */
#define rpfl2bc_en_shift 0
/* width of bitfield l2_bc_en */
#define rpfl2bc_en_width 1
/* default value of bitfield l2_bc_en */
#define rpfl2bc_en_default 0x0
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* rx l2_bc_act[2:0] bitfield definitions
 * preprocessor definitions for the bitfield "l2_bc_act[2:0]".
 * port="pif_rpf_l2_bc_act_i[2:0]"
 */

/* register address for bitfield l2_bc_act[2:0] */
<<<<<<< HEAD
#define HW_ATL_RPFL2BC_ACT_ADR 0x00005100
/* bitmask for bitfield l2_bc_act[2:0] */
#define HW_ATL_RPFL2BC_ACT_MSK 0x00007000
/* inverted bitmask for bitfield l2_bc_act[2:0] */
#define HW_ATL_RPFL2BC_ACT_MSKN 0xffff8fff
/* lower bit position of bitfield l2_bc_act[2:0] */
#define HW_ATL_RPFL2BC_ACT_SHIFT 12
/* width of bitfield l2_bc_act[2:0] */
#define HW_ATL_RPFL2BC_ACT_WIDTH 3
/* default value of bitfield l2_bc_act[2:0] */
#define HW_ATL_RPFL2BC_ACT_DEFAULT 0x0
=======
#define rpfl2bc_act_adr 0x00005100
/* bitmask for bitfield l2_bc_act[2:0] */
#define rpfl2bc_act_msk 0x00007000
/* inverted bitmask for bitfield l2_bc_act[2:0] */
#define rpfl2bc_act_mskn 0xffff8fff
/* lower bit position of bitfield l2_bc_act[2:0] */
#define rpfl2bc_act_shift 12
/* width of bitfield l2_bc_act[2:0] */
#define rpfl2bc_act_width 3
/* default value of bitfield l2_bc_act[2:0] */
#define rpfl2bc_act_default 0x0
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* rx l2_mc_en{f} bitfield definitions
 * preprocessor definitions for the bitfield "l2_mc_en{f}".
 * parameter: filter {f} | stride size 0x4 | range [0, 7]
 * port="pif_rpf_l2_mc_en_i[0]"
 */

/* register address for bitfield l2_mc_en{f} */
<<<<<<< HEAD
#define HW_ATL_RPFL2MC_ENF_ADR(filter) (0x00005250 + (filter) * 0x4)
/* bitmask for bitfield l2_mc_en{f} */
#define HW_ATL_RPFL2MC_ENF_MSK 0x80000000
/* inverted bitmask for bitfield l2_mc_en{f} */
#define HW_ATL_RPFL2MC_ENF_MSKN 0x7fffffff
/* lower bit position of bitfield l2_mc_en{f} */
#define HW_ATL_RPFL2MC_ENF_SHIFT 31
/* width of bitfield l2_mc_en{f} */
#define HW_ATL_RPFL2MC_ENF_WIDTH 1
/* default value of bitfield l2_mc_en{f} */
#define HW_ATL_RPFL2MC_ENF_DEFAULT 0x0
=======
#define rpfl2mc_enf_adr(filter) (0x00005250 + (filter) * 0x4)
/* bitmask for bitfield l2_mc_en{f} */
#define rpfl2mc_enf_msk 0x80000000
/* inverted bitmask for bitfield l2_mc_en{f} */
#define rpfl2mc_enf_mskn 0x7fffffff
/* lower bit position of bitfield l2_mc_en{f} */
#define rpfl2mc_enf_shift 31
/* width of bitfield l2_mc_en{f} */
#define rpfl2mc_enf_width 1
/* default value of bitfield l2_mc_en{f} */
#define rpfl2mc_enf_default 0x0
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* rx l2_promis_mode bitfield definitions
 * preprocessor definitions for the bitfield "l2_promis_mode".
 * port="pif_rpf_l2_promis_mode_i"
 */

/* register address for bitfield l2_promis_mode */
<<<<<<< HEAD
#define HW_ATL_RPFL2PROMIS_MODE_ADR 0x00005100
/* bitmask for bitfield l2_promis_mode */
#define HW_ATL_RPFL2PROMIS_MODE_MSK 0x00000008
/* inverted bitmask for bitfield l2_promis_mode */
#define HW_ATL_RPFL2PROMIS_MODE_MSKN 0xfffffff7
/* lower bit position of bitfield l2_promis_mode */
#define HW_ATL_RPFL2PROMIS_MODE_SHIFT 3
/* width of bitfield l2_promis_mode */
#define HW_ATL_RPFL2PROMIS_MODE_WIDTH 1
/* default value of bitfield l2_promis_mode */
#define HW_ATL_RPFL2PROMIS_MODE_DEFAULT 0x0
=======
#define rpfl2promis_mode_adr 0x00005100
/* bitmask for bitfield l2_promis_mode */
#define rpfl2promis_mode_msk 0x00000008
/* inverted bitmask for bitfield l2_promis_mode */
#define rpfl2promis_mode_mskn 0xfffffff7
/* lower bit position of bitfield l2_promis_mode */
#define rpfl2promis_mode_shift 3
/* width of bitfield l2_promis_mode */
#define rpfl2promis_mode_width 1
/* default value of bitfield l2_promis_mode */
#define rpfl2promis_mode_default 0x0
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* rx l2_uc_act{f}[2:0] bitfield definitions
 * preprocessor definitions for the bitfield "l2_uc_act{f}[2:0]".
 * parameter: filter {f} | stride size 0x8 | range [0, 37]
 * port="pif_rpf_l2_uc_act0_i[2:0]"
 */

/* register address for bitfield l2_uc_act{f}[2:0] */
<<<<<<< HEAD
#define HW_ATL_RPFL2UC_ACTF_ADR(filter) (0x00005114 + (filter) * 0x8)
/* bitmask for bitfield l2_uc_act{f}[2:0] */
#define HW_ATL_RPFL2UC_ACTF_MSK 0x00070000
/* inverted bitmask for bitfield l2_uc_act{f}[2:0] */
#define HW_ATL_RPFL2UC_ACTF_MSKN 0xfff8ffff
/* lower bit position of bitfield l2_uc_act{f}[2:0] */
#define HW_ATL_RPFL2UC_ACTF_SHIFT 16
/* width of bitfield l2_uc_act{f}[2:0] */
#define HW_ATL_RPFL2UC_ACTF_WIDTH 3
/* default value of bitfield l2_uc_act{f}[2:0] */
#define HW_ATL_RPFL2UC_ACTF_DEFAULT 0x0
=======
#define rpfl2uc_actf_adr(filter) (0x00005114 + (filter) * 0x8)
/* bitmask for bitfield l2_uc_act{f}[2:0] */
#define rpfl2uc_actf_msk 0x00070000
/* inverted bitmask for bitfield l2_uc_act{f}[2:0] */
#define rpfl2uc_actf_mskn 0xfff8ffff
/* lower bit position of bitfield l2_uc_act{f}[2:0] */
#define rpfl2uc_actf_shift 16
/* width of bitfield l2_uc_act{f}[2:0] */
#define rpfl2uc_actf_width 3
/* default value of bitfield l2_uc_act{f}[2:0] */
#define rpfl2uc_actf_default 0x0
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* rx l2_uc_en{f} bitfield definitions
 * preprocessor definitions for the bitfield "l2_uc_en{f}".
 * parameter: filter {f} | stride size 0x8 | range [0, 37]
 * port="pif_rpf_l2_uc_en_i[0]"
 */

/* register address for bitfield l2_uc_en{f} */
<<<<<<< HEAD
#define HW_ATL_RPFL2UC_ENF_ADR(filter) (0x00005114 + (filter) * 0x8)
/* bitmask for bitfield l2_uc_en{f} */
#define HW_ATL_RPFL2UC_ENF_MSK 0x80000000
/* inverted bitmask for bitfield l2_uc_en{f} */
#define HW_ATL_RPFL2UC_ENF_MSKN 0x7fffffff
/* lower bit position of bitfield l2_uc_en{f} */
#define HW_ATL_RPFL2UC_ENF_SHIFT 31
/* width of bitfield l2_uc_en{f} */
#define HW_ATL_RPFL2UC_ENF_WIDTH 1
/* default value of bitfield l2_uc_en{f} */
#define HW_ATL_RPFL2UC_ENF_DEFAULT 0x0

/* register address for bitfield l2_uc_da{f}_lsw[1f:0] */
#define HW_ATL_RPFL2UC_DAFLSW_ADR(filter) (0x00005110 + (filter) * 0x8)
/* register address for bitfield l2_uc_da{f}_msw[f:0] */
#define HW_ATL_RPFL2UC_DAFMSW_ADR(filter) (0x00005114 + (filter) * 0x8)
/* bitmask for bitfield l2_uc_da{f}_msw[f:0] */
#define HW_ATL_RPFL2UC_DAFMSW_MSK 0x0000ffff
/* lower bit position of bitfield l2_uc_da{f}_msw[f:0] */
#define HW_ATL_RPFL2UC_DAFMSW_SHIFT 0
=======
#define rpfl2uc_enf_adr(filter) (0x00005114 + (filter) * 0x8)
/* bitmask for bitfield l2_uc_en{f} */
#define rpfl2uc_enf_msk 0x80000000
/* inverted bitmask for bitfield l2_uc_en{f} */
#define rpfl2uc_enf_mskn 0x7fffffff
/* lower bit position of bitfield l2_uc_en{f} */
#define rpfl2uc_enf_shift 31
/* width of bitfield l2_uc_en{f} */
#define rpfl2uc_enf_width 1
/* default value of bitfield l2_uc_en{f} */
#define rpfl2uc_enf_default 0x0

/* register address for bitfield l2_uc_da{f}_lsw[1f:0] */
#define rpfl2uc_daflsw_adr(filter) (0x00005110 + (filter) * 0x8)
/* register address for bitfield l2_uc_da{f}_msw[f:0] */
#define rpfl2uc_dafmsw_adr(filter) (0x00005114 + (filter) * 0x8)
/* bitmask for bitfield l2_uc_da{f}_msw[f:0] */
#define rpfl2uc_dafmsw_msk 0x0000ffff
/* lower bit position of bitfield l2_uc_da{f}_msw[f:0] */
#define rpfl2uc_dafmsw_shift 0
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* rx l2_mc_accept_all bitfield definitions
 * Preprocessor definitions for the bitfield "l2_mc_accept_all".
 * PORT="pif_rpf_l2_mc_all_accept_i"
 */

/* Register address for bitfield l2_mc_accept_all */
<<<<<<< HEAD
#define HW_ATL_RPFL2MC_ACCEPT_ALL_ADR 0x00005270
/* Bitmask for bitfield l2_mc_accept_all */
#define HW_ATL_RPFL2MC_ACCEPT_ALL_MSK 0x00004000
/* Inverted bitmask for bitfield l2_mc_accept_all */
#define HW_ATL_RPFL2MC_ACCEPT_ALL_MSKN 0xFFFFBFFF
/* Lower bit position of bitfield l2_mc_accept_all */
#define HW_ATL_RPFL2MC_ACCEPT_ALL_SHIFT 14
/* Width of bitfield l2_mc_accept_all */
#define HW_ATL_RPFL2MC_ACCEPT_ALL_WIDTH 1
/* Default value of bitfield l2_mc_accept_all */
#define HW_ATL_RPFL2MC_ACCEPT_ALL_DEFAULT 0x0

/* width of bitfield rx_tc_up{t}[2:0] */
#define HW_ATL_RPF_RPB_RX_TC_UPT_WIDTH 3
/* default value of bitfield rx_tc_up{t}[2:0] */
#define HW_ATL_RPF_RPB_RX_TC_UPT_DEFAULT 0x0
=======
#define rpfl2mc_accept_all_adr 0x00005270
/* Bitmask for bitfield l2_mc_accept_all */
#define rpfl2mc_accept_all_msk 0x00004000
/* Inverted bitmask for bitfield l2_mc_accept_all */
#define rpfl2mc_accept_all_mskn 0xFFFFBFFF
/* Lower bit position of bitfield l2_mc_accept_all */
#define rpfl2mc_accept_all_shift 14
/* Width of bitfield l2_mc_accept_all */
#define rpfl2mc_accept_all_width 1
/* Default value of bitfield l2_mc_accept_all */
#define rpfl2mc_accept_all_default 0x0

/* width of bitfield rx_tc_up{t}[2:0] */
#define rpf_rpb_rx_tc_upt_width 3
/* default value of bitfield rx_tc_up{t}[2:0] */
#define rpf_rpb_rx_tc_upt_default 0x0
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* rx rss_key_addr[4:0] bitfield definitions
 * preprocessor definitions for the bitfield "rss_key_addr[4:0]".
 * port="pif_rpf_rss_key_addr_i[4:0]"
 */

/* register address for bitfield rss_key_addr[4:0] */
<<<<<<< HEAD
#define HW_ATL_RPF_RSS_KEY_ADDR_ADR 0x000054d0
/* bitmask for bitfield rss_key_addr[4:0] */
#define HW_ATL_RPF_RSS_KEY_ADDR_MSK 0x0000001f
/* inverted bitmask for bitfield rss_key_addr[4:0] */
#define HW_ATL_RPF_RSS_KEY_ADDR_MSKN 0xffffffe0
/* lower bit position of bitfield rss_key_addr[4:0] */
#define HW_ATL_RPF_RSS_KEY_ADDR_SHIFT 0
/* width of bitfield rss_key_addr[4:0] */
#define HW_ATL_RPF_RSS_KEY_ADDR_WIDTH 5
/* default value of bitfield rss_key_addr[4:0] */
#define HW_ATL_RPF_RSS_KEY_ADDR_DEFAULT 0x0
=======
#define rpf_rss_key_addr_adr 0x000054d0
/* bitmask for bitfield rss_key_addr[4:0] */
#define rpf_rss_key_addr_msk 0x0000001f
/* inverted bitmask for bitfield rss_key_addr[4:0] */
#define rpf_rss_key_addr_mskn 0xffffffe0
/* lower bit position of bitfield rss_key_addr[4:0] */
#define rpf_rss_key_addr_shift 0
/* width of bitfield rss_key_addr[4:0] */
#define rpf_rss_key_addr_width 5
/* default value of bitfield rss_key_addr[4:0] */
#define rpf_rss_key_addr_default 0x0
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* rx rss_key_wr_data[1f:0] bitfield definitions
 * preprocessor definitions for the bitfield "rss_key_wr_data[1f:0]".
 * port="pif_rpf_rss_key_wr_data_i[31:0]"
 */

/* register address for bitfield rss_key_wr_data[1f:0] */
<<<<<<< HEAD
#define HW_ATL_RPF_RSS_KEY_WR_DATA_ADR 0x000054d4
/* bitmask for bitfield rss_key_wr_data[1f:0] */
#define HW_ATL_RPF_RSS_KEY_WR_DATA_MSK 0xffffffff
/* inverted bitmask for bitfield rss_key_wr_data[1f:0] */
#define HW_ATL_RPF_RSS_KEY_WR_DATA_MSKN 0x00000000
/* lower bit position of bitfield rss_key_wr_data[1f:0] */
#define HW_ATL_RPF_RSS_KEY_WR_DATA_SHIFT 0
/* width of bitfield rss_key_wr_data[1f:0] */
#define HW_ATL_RPF_RSS_KEY_WR_DATA_WIDTH 32
/* default value of bitfield rss_key_wr_data[1f:0] */
#define HW_ATL_RPF_RSS_KEY_WR_DATA_DEFAULT 0x0
=======
#define rpf_rss_key_wr_data_adr 0x000054d4
/* bitmask for bitfield rss_key_wr_data[1f:0] */
#define rpf_rss_key_wr_data_msk 0xffffffff
/* inverted bitmask for bitfield rss_key_wr_data[1f:0] */
#define rpf_rss_key_wr_data_mskn 0x00000000
/* lower bit position of bitfield rss_key_wr_data[1f:0] */
#define rpf_rss_key_wr_data_shift 0
/* width of bitfield rss_key_wr_data[1f:0] */
#define rpf_rss_key_wr_data_width 32
/* default value of bitfield rss_key_wr_data[1f:0] */
#define rpf_rss_key_wr_data_default 0x0
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* rx rss_key_wr_en_i bitfield definitions
 * preprocessor definitions for the bitfield "rss_key_wr_en_i".
 * port="pif_rpf_rss_key_wr_en_i"
 */

/* register address for bitfield rss_key_wr_en_i */
<<<<<<< HEAD
#define HW_ATL_RPF_RSS_KEY_WR_ENI_ADR 0x000054d0
/* bitmask for bitfield rss_key_wr_en_i */
#define HW_ATL_RPF_RSS_KEY_WR_ENI_MSK 0x00000020
/* inverted bitmask for bitfield rss_key_wr_en_i */
#define HW_ATL_RPF_RSS_KEY_WR_ENI_MSKN 0xffffffdf
/* lower bit position of bitfield rss_key_wr_en_i */
#define HW_ATL_RPF_RSS_KEY_WR_ENI_SHIFT 5
/* width of bitfield rss_key_wr_en_i */
#define HW_ATL_RPF_RSS_KEY_WR_ENI_WIDTH 1
/* default value of bitfield rss_key_wr_en_i */
#define HW_ATL_RPF_RSS_KEY_WR_ENI_DEFAULT 0x0
=======
#define rpf_rss_key_wr_eni_adr 0x000054d0
/* bitmask for bitfield rss_key_wr_en_i */
#define rpf_rss_key_wr_eni_msk 0x00000020
/* inverted bitmask for bitfield rss_key_wr_en_i */
#define rpf_rss_key_wr_eni_mskn 0xffffffdf
/* lower bit position of bitfield rss_key_wr_en_i */
#define rpf_rss_key_wr_eni_shift 5
/* width of bitfield rss_key_wr_en_i */
#define rpf_rss_key_wr_eni_width 1
/* default value of bitfield rss_key_wr_en_i */
#define rpf_rss_key_wr_eni_default 0x0
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* rx rss_redir_addr[3:0] bitfield definitions
 * preprocessor definitions for the bitfield "rss_redir_addr[3:0]".
 * port="pif_rpf_rss_redir_addr_i[3:0]"
 */

/* register address for bitfield rss_redir_addr[3:0] */
<<<<<<< HEAD
#define HW_ATL_RPF_RSS_REDIR_ADDR_ADR 0x000054e0
/* bitmask for bitfield rss_redir_addr[3:0] */
#define HW_ATL_RPF_RSS_REDIR_ADDR_MSK 0x0000000f
/* inverted bitmask for bitfield rss_redir_addr[3:0] */
#define HW_ATL_RPF_RSS_REDIR_ADDR_MSKN 0xfffffff0
/* lower bit position of bitfield rss_redir_addr[3:0] */
#define HW_ATL_RPF_RSS_REDIR_ADDR_SHIFT 0
/* width of bitfield rss_redir_addr[3:0] */
#define HW_ATL_RPF_RSS_REDIR_ADDR_WIDTH 4
/* default value of bitfield rss_redir_addr[3:0] */
#define HW_ATL_RPF_RSS_REDIR_ADDR_DEFAULT 0x0
=======
#define rpf_rss_redir_addr_adr 0x000054e0
/* bitmask for bitfield rss_redir_addr[3:0] */
#define rpf_rss_redir_addr_msk 0x0000000f
/* inverted bitmask for bitfield rss_redir_addr[3:0] */
#define rpf_rss_redir_addr_mskn 0xfffffff0
/* lower bit position of bitfield rss_redir_addr[3:0] */
#define rpf_rss_redir_addr_shift 0
/* width of bitfield rss_redir_addr[3:0] */
#define rpf_rss_redir_addr_width 4
/* default value of bitfield rss_redir_addr[3:0] */
#define rpf_rss_redir_addr_default 0x0
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* rx rss_redir_wr_data[f:0] bitfield definitions
 * preprocessor definitions for the bitfield "rss_redir_wr_data[f:0]".
 * port="pif_rpf_rss_redir_wr_data_i[15:0]"
 */

/* register address for bitfield rss_redir_wr_data[f:0] */
<<<<<<< HEAD
#define HW_ATL_RPF_RSS_REDIR_WR_DATA_ADR 0x000054e4
/* bitmask for bitfield rss_redir_wr_data[f:0] */
#define HW_ATL_RPF_RSS_REDIR_WR_DATA_MSK 0x0000ffff
/* inverted bitmask for bitfield rss_redir_wr_data[f:0] */
#define HW_ATL_RPF_RSS_REDIR_WR_DATA_MSKN 0xffff0000
/* lower bit position of bitfield rss_redir_wr_data[f:0] */
#define HW_ATL_RPF_RSS_REDIR_WR_DATA_SHIFT 0
/* width of bitfield rss_redir_wr_data[f:0] */
#define HW_ATL_RPF_RSS_REDIR_WR_DATA_WIDTH 16
/* default value of bitfield rss_redir_wr_data[f:0] */
#define HW_ATL_RPF_RSS_REDIR_WR_DATA_DEFAULT 0x0
=======
#define rpf_rss_redir_wr_data_adr 0x000054e4
/* bitmask for bitfield rss_redir_wr_data[f:0] */
#define rpf_rss_redir_wr_data_msk 0x0000ffff
/* inverted bitmask for bitfield rss_redir_wr_data[f:0] */
#define rpf_rss_redir_wr_data_mskn 0xffff0000
/* lower bit position of bitfield rss_redir_wr_data[f:0] */
#define rpf_rss_redir_wr_data_shift 0
/* width of bitfield rss_redir_wr_data[f:0] */
#define rpf_rss_redir_wr_data_width 16
/* default value of bitfield rss_redir_wr_data[f:0] */
#define rpf_rss_redir_wr_data_default 0x0
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* rx rss_redir_wr_en_i bitfield definitions
 * preprocessor definitions for the bitfield "rss_redir_wr_en_i".
 * port="pif_rpf_rss_redir_wr_en_i"
 */

/* register address for bitfield rss_redir_wr_en_i */
<<<<<<< HEAD
#define HW_ATL_RPF_RSS_REDIR_WR_ENI_ADR 0x000054e0
/* bitmask for bitfield rss_redir_wr_en_i */
#define HW_ATL_RPF_RSS_REDIR_WR_ENI_MSK 0x00000010
/* inverted bitmask for bitfield rss_redir_wr_en_i */
#define HW_ATL_RPF_RSS_REDIR_WR_ENI_MSKN 0xffffffef
/* lower bit position of bitfield rss_redir_wr_en_i */
#define HW_ATL_RPF_RSS_REDIR_WR_ENI_SHIFT 4
/* width of bitfield rss_redir_wr_en_i */
#define HW_ATL_RPF_RSS_REDIR_WR_ENI_WIDTH 1
/* default value of bitfield rss_redir_wr_en_i */
#define HW_ATL_RPF_RSS_REDIR_WR_ENI_DEFAULT 0x0
=======
#define rpf_rss_redir_wr_eni_adr 0x000054e0
/* bitmask for bitfield rss_redir_wr_en_i */
#define rpf_rss_redir_wr_eni_msk 0x00000010
/* inverted bitmask for bitfield rss_redir_wr_en_i */
#define rpf_rss_redir_wr_eni_mskn 0xffffffef
/* lower bit position of bitfield rss_redir_wr_en_i */
#define rpf_rss_redir_wr_eni_shift 4
/* width of bitfield rss_redir_wr_en_i */
#define rpf_rss_redir_wr_eni_width 1
/* default value of bitfield rss_redir_wr_en_i */
#define rpf_rss_redir_wr_eni_default 0x0
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* rx tpo_rpf_sys_loopback bitfield definitions
 * preprocessor definitions for the bitfield "tpo_rpf_sys_loopback".
 * port="pif_rpf_tpo_pkt_sys_lbk_i"
 */

/* register address for bitfield tpo_rpf_sys_loopback */
<<<<<<< HEAD
#define HW_ATL_RPF_TPO_RPF_SYS_LBK_ADR 0x00005000
/* bitmask for bitfield tpo_rpf_sys_loopback */
#define HW_ATL_RPF_TPO_RPF_SYS_LBK_MSK 0x00000100
/* inverted bitmask for bitfield tpo_rpf_sys_loopback */
#define HW_ATL_RPF_TPO_RPF_SYS_LBK_MSKN 0xfffffeff
/* lower bit position of bitfield tpo_rpf_sys_loopback */
#define HW_ATL_RPF_TPO_RPF_SYS_LBK_SHIFT 8
/* width of bitfield tpo_rpf_sys_loopback */
#define HW_ATL_RPF_TPO_RPF_SYS_LBK_WIDTH 1
/* default value of bitfield tpo_rpf_sys_loopback */
#define HW_ATL_RPF_TPO_RPF_SYS_LBK_DEFAULT 0x0
=======
#define rpf_tpo_rpf_sys_lbk_adr 0x00005000
/* bitmask for bitfield tpo_rpf_sys_loopback */
#define rpf_tpo_rpf_sys_lbk_msk 0x00000100
/* inverted bitmask for bitfield tpo_rpf_sys_loopback */
#define rpf_tpo_rpf_sys_lbk_mskn 0xfffffeff
/* lower bit position of bitfield tpo_rpf_sys_loopback */
#define rpf_tpo_rpf_sys_lbk_shift 8
/* width of bitfield tpo_rpf_sys_loopback */
#define rpf_tpo_rpf_sys_lbk_width 1
/* default value of bitfield tpo_rpf_sys_loopback */
#define rpf_tpo_rpf_sys_lbk_default 0x0
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* rx vl_inner_tpid[f:0] bitfield definitions
 * preprocessor definitions for the bitfield "vl_inner_tpid[f:0]".
 * port="pif_rpf_vl_inner_tpid_i[15:0]"
 */

/* register address for bitfield vl_inner_tpid[f:0] */
<<<<<<< HEAD
#define HW_ATL_RPF_VL_INNER_TPID_ADR 0x00005284
/* bitmask for bitfield vl_inner_tpid[f:0] */
#define HW_ATL_RPF_VL_INNER_TPID_MSK 0x0000ffff
/* inverted bitmask for bitfield vl_inner_tpid[f:0] */
#define HW_ATL_RPF_VL_INNER_TPID_MSKN 0xffff0000
/* lower bit position of bitfield vl_inner_tpid[f:0] */
#define HW_ATL_RPF_VL_INNER_TPID_SHIFT 0
/* width of bitfield vl_inner_tpid[f:0] */
#define HW_ATL_RPF_VL_INNER_TPID_WIDTH 16
/* default value of bitfield vl_inner_tpid[f:0] */
#define HW_ATL_RPF_VL_INNER_TPID_DEFAULT 0x8100
=======
#define rpf_vl_inner_tpid_adr 0x00005284
/* bitmask for bitfield vl_inner_tpid[f:0] */
#define rpf_vl_inner_tpid_msk 0x0000ffff
/* inverted bitmask for bitfield vl_inner_tpid[f:0] */
#define rpf_vl_inner_tpid_mskn 0xffff0000
/* lower bit position of bitfield vl_inner_tpid[f:0] */
#define rpf_vl_inner_tpid_shift 0
/* width of bitfield vl_inner_tpid[f:0] */
#define rpf_vl_inner_tpid_width 16
/* default value of bitfield vl_inner_tpid[f:0] */
#define rpf_vl_inner_tpid_default 0x8100
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* rx vl_outer_tpid[f:0] bitfield definitions
 * preprocessor definitions for the bitfield "vl_outer_tpid[f:0]".
 * port="pif_rpf_vl_outer_tpid_i[15:0]"
 */

/* register address for bitfield vl_outer_tpid[f:0] */
<<<<<<< HEAD
#define HW_ATL_RPF_VL_OUTER_TPID_ADR 0x00005284
/* bitmask for bitfield vl_outer_tpid[f:0] */
#define HW_ATL_RPF_VL_OUTER_TPID_MSK 0xffff0000
/* inverted bitmask for bitfield vl_outer_tpid[f:0] */
#define HW_ATL_RPF_VL_OUTER_TPID_MSKN 0x0000ffff
/* lower bit position of bitfield vl_outer_tpid[f:0] */
#define HW_ATL_RPF_VL_OUTER_TPID_SHIFT 16
/* width of bitfield vl_outer_tpid[f:0] */
#define HW_ATL_RPF_VL_OUTER_TPID_WIDTH 16
/* default value of bitfield vl_outer_tpid[f:0] */
#define HW_ATL_RPF_VL_OUTER_TPID_DEFAULT 0x88a8
=======
#define rpf_vl_outer_tpid_adr 0x00005284
/* bitmask for bitfield vl_outer_tpid[f:0] */
#define rpf_vl_outer_tpid_msk 0xffff0000
/* inverted bitmask for bitfield vl_outer_tpid[f:0] */
#define rpf_vl_outer_tpid_mskn 0x0000ffff
/* lower bit position of bitfield vl_outer_tpid[f:0] */
#define rpf_vl_outer_tpid_shift 16
/* width of bitfield vl_outer_tpid[f:0] */
#define rpf_vl_outer_tpid_width 16
/* default value of bitfield vl_outer_tpid[f:0] */
#define rpf_vl_outer_tpid_default 0x88a8
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* rx vl_promis_mode bitfield definitions
 * preprocessor definitions for the bitfield "vl_promis_mode".
 * port="pif_rpf_vl_promis_mode_i"
 */

/* register address for bitfield vl_promis_mode */
<<<<<<< HEAD
#define HW_ATL_RPF_VL_PROMIS_MODE_ADR 0x00005280
/* bitmask for bitfield vl_promis_mode */
#define HW_ATL_RPF_VL_PROMIS_MODE_MSK 0x00000002
/* inverted bitmask for bitfield vl_promis_mode */
#define HW_ATL_RPF_VL_PROMIS_MODE_MSKN 0xfffffffd
/* lower bit position of bitfield vl_promis_mode */
#define HW_ATL_RPF_VL_PROMIS_MODE_SHIFT 1
/* width of bitfield vl_promis_mode */
#define HW_ATL_RPF_VL_PROMIS_MODE_WIDTH 1
/* default value of bitfield vl_promis_mode */
#define HW_ATL_RPF_VL_PROMIS_MODE_DEFAULT 0x0
=======
#define rpf_vl_promis_mode_adr 0x00005280
/* bitmask for bitfield vl_promis_mode */
#define rpf_vl_promis_mode_msk 0x00000002
/* inverted bitmask for bitfield vl_promis_mode */
#define rpf_vl_promis_mode_mskn 0xfffffffd
/* lower bit position of bitfield vl_promis_mode */
#define rpf_vl_promis_mode_shift 1
/* width of bitfield vl_promis_mode */
#define rpf_vl_promis_mode_width 1
/* default value of bitfield vl_promis_mode */
#define rpf_vl_promis_mode_default 0x0
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* RX vl_accept_untagged_mode Bitfield Definitions
 * Preprocessor definitions for the bitfield "vl_accept_untagged_mode".
 * PORT="pif_rpf_vl_accept_untagged_i"
 */

/* Register address for bitfield vl_accept_untagged_mode */
<<<<<<< HEAD
#define HW_ATL_RPF_VL_ACCEPT_UNTAGGED_MODE_ADR 0x00005280
/* Bitmask for bitfield vl_accept_untagged_mode */
#define HW_ATL_RPF_VL_ACCEPT_UNTAGGED_MODE_MSK 0x00000004
/* Inverted bitmask for bitfield vl_accept_untagged_mode */
#define HW_ATL_RPF_VL_ACCEPT_UNTAGGED_MODE_MSKN 0xFFFFFFFB
/* Lower bit position of bitfield vl_accept_untagged_mode */
#define HW_ATL_RPF_VL_ACCEPT_UNTAGGED_MODE_SHIFT 2
/* Width of bitfield vl_accept_untagged_mode */
#define HW_ATL_RPF_VL_ACCEPT_UNTAGGED_MODE_WIDTH 1
/* Default value of bitfield vl_accept_untagged_mode */
#define HW_ATL_RPF_VL_ACCEPT_UNTAGGED_MODE_DEFAULT 0x0
=======
#define rpf_vl_accept_untagged_mode_adr 0x00005280
/* Bitmask for bitfield vl_accept_untagged_mode */
#define rpf_vl_accept_untagged_mode_msk 0x00000004
/* Inverted bitmask for bitfield vl_accept_untagged_mode */
#define rpf_vl_accept_untagged_mode_mskn 0xFFFFFFFB
/* Lower bit position of bitfield vl_accept_untagged_mode */
#define rpf_vl_accept_untagged_mode_shift 2
/* Width of bitfield vl_accept_untagged_mode */
#define rpf_vl_accept_untagged_mode_width 1
/* Default value of bitfield vl_accept_untagged_mode */
#define rpf_vl_accept_untagged_mode_default 0x0
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* rX vl_untagged_act[2:0] Bitfield Definitions
 * Preprocessor definitions for the bitfield "vl_untagged_act[2:0]".
 * PORT="pif_rpf_vl_untagged_act_i[2:0]"
 */

/* Register address for bitfield vl_untagged_act[2:0] */
<<<<<<< HEAD
#define HW_ATL_RPF_VL_UNTAGGED_ACT_ADR 0x00005280
/* Bitmask for bitfield vl_untagged_act[2:0] */
#define HW_ATL_RPF_VL_UNTAGGED_ACT_MSK 0x00000038
/* Inverted bitmask for bitfield vl_untagged_act[2:0] */
#define HW_ATL_RPF_VL_UNTAGGED_ACT_MSKN 0xFFFFFFC7
/* Lower bit position of bitfield vl_untagged_act[2:0] */
#define HW_ATL_RPF_VL_UNTAGGED_ACT_SHIFT 3
/* Width of bitfield vl_untagged_act[2:0] */
#define HW_ATL_RPF_VL_UNTAGGED_ACT_WIDTH 3
/* Default value of bitfield vl_untagged_act[2:0] */
#define HW_ATL_RPF_VL_UNTAGGED_ACT_DEFAULT 0x0
=======
#define rpf_vl_untagged_act_adr 0x00005280
/* Bitmask for bitfield vl_untagged_act[2:0] */
#define rpf_vl_untagged_act_msk 0x00000038
/* Inverted bitmask for bitfield vl_untagged_act[2:0] */
#define rpf_vl_untagged_act_mskn 0xFFFFFFC7
/* Lower bit position of bitfield vl_untagged_act[2:0] */
#define rpf_vl_untagged_act_shift 3
/* Width of bitfield vl_untagged_act[2:0] */
#define rpf_vl_untagged_act_width 3
/* Default value of bitfield vl_untagged_act[2:0] */
#define rpf_vl_untagged_act_default 0x0
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* RX vl_en{F} Bitfield Definitions
 * Preprocessor definitions for the bitfield "vl_en{F}".
 * Parameter: filter {F} | stride size 0x4 | range [0, 15]
 * PORT="pif_rpf_vl_en_i[0]"
 */

/* Register address for bitfield vl_en{F} */
<<<<<<< HEAD
#define HW_ATL_RPF_VL_EN_F_ADR(filter) (0x00005290 + (filter) * 0x4)
/* Bitmask for bitfield vl_en{F} */
#define HW_ATL_RPF_VL_EN_F_MSK 0x80000000
/* Inverted bitmask for bitfield vl_en{F} */
#define HW_ATL_RPF_VL_EN_F_MSKN 0x7FFFFFFF
/* Lower bit position of bitfield vl_en{F} */
#define HW_ATL_RPF_VL_EN_F_SHIFT 31
/* Width of bitfield vl_en{F} */
#define HW_ATL_RPF_VL_EN_F_WIDTH 1
/* Default value of bitfield vl_en{F} */
#define HW_ATL_RPF_VL_EN_F_DEFAULT 0x0
=======
#define rpf_vl_en_f_adr(filter) (0x00005290 + (filter) * 0x4)
/* Bitmask for bitfield vl_en{F} */
#define rpf_vl_en_f_msk 0x80000000
/* Inverted bitmask for bitfield vl_en{F} */
#define rpf_vl_en_f_mskn 0x7FFFFFFF
/* Lower bit position of bitfield vl_en{F} */
#define rpf_vl_en_f_shift 31
/* Width of bitfield vl_en{F} */
#define rpf_vl_en_f_width 1
/* Default value of bitfield vl_en{F} */
#define rpf_vl_en_f_default 0x0
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* RX vl_act{F}[2:0] Bitfield Definitions
 * Preprocessor definitions for the bitfield "vl_act{F}[2:0]".
 * Parameter: filter {F} | stride size 0x4 | range [0, 15]
 * PORT="pif_rpf_vl_act0_i[2:0]"
 */

/* Register address for bitfield vl_act{F}[2:0] */
<<<<<<< HEAD
#define HW_ATL_RPF_VL_ACT_F_ADR(filter) (0x00005290 + (filter) * 0x4)
/* Bitmask for bitfield vl_act{F}[2:0] */
#define HW_ATL_RPF_VL_ACT_F_MSK 0x00070000
/* Inverted bitmask for bitfield vl_act{F}[2:0] */
#define HW_ATL_RPF_VL_ACT_F_MSKN 0xFFF8FFFF
/* Lower bit position of bitfield vl_act{F}[2:0] */
#define HW_ATL_RPF_VL_ACT_F_SHIFT 16
/* Width of bitfield vl_act{F}[2:0] */
#define HW_ATL_RPF_VL_ACT_F_WIDTH 3
/* Default value of bitfield vl_act{F}[2:0] */
#define HW_ATL_RPF_VL_ACT_F_DEFAULT 0x0
=======
#define rpf_vl_act_f_adr(filter) (0x00005290 + (filter) * 0x4)
/* Bitmask for bitfield vl_act{F}[2:0] */
#define rpf_vl_act_f_msk 0x00070000
/* Inverted bitmask for bitfield vl_act{F}[2:0] */
#define rpf_vl_act_f_mskn 0xFFF8FFFF
/* Lower bit position of bitfield vl_act{F}[2:0] */
#define rpf_vl_act_f_shift 16
/* Width of bitfield vl_act{F}[2:0] */
#define rpf_vl_act_f_width 3
/* Default value of bitfield vl_act{F}[2:0] */
#define rpf_vl_act_f_default 0x0
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* RX vl_id{F}[B:0] Bitfield Definitions
 * Preprocessor definitions for the bitfield "vl_id{F}[B:0]".
 * Parameter: filter {F} | stride size 0x4 | range [0, 15]
 * PORT="pif_rpf_vl_id0_i[11:0]"
 */

/* Register address for bitfield vl_id{F}[B:0] */
<<<<<<< HEAD
#define HW_ATL_RPF_VL_ID_F_ADR(filter) (0x00005290 + (filter) * 0x4)
/* Bitmask for bitfield vl_id{F}[B:0] */
#define HW_ATL_RPF_VL_ID_F_MSK 0x00000FFF
/* Inverted bitmask for bitfield vl_id{F}[B:0] */
#define HW_ATL_RPF_VL_ID_F_MSKN 0xFFFFF000
/* Lower bit position of bitfield vl_id{F}[B:0] */
#define HW_ATL_RPF_VL_ID_F_SHIFT 0
/* Width of bitfield vl_id{F}[B:0] */
#define HW_ATL_RPF_VL_ID_F_WIDTH 12
/* Default value of bitfield vl_id{F}[B:0] */
#define HW_ATL_RPF_VL_ID_F_DEFAULT 0x0
=======
#define rpf_vl_id_f_adr(filter) (0x00005290 + (filter) * 0x4)
/* Bitmask for bitfield vl_id{F}[B:0] */
#define rpf_vl_id_f_msk 0x00000FFF
/* Inverted bitmask for bitfield vl_id{F}[B:0] */
#define rpf_vl_id_f_mskn 0xFFFFF000
/* Lower bit position of bitfield vl_id{F}[B:0] */
#define rpf_vl_id_f_shift 0
/* Width of bitfield vl_id{F}[B:0] */
#define rpf_vl_id_f_width 12
/* Default value of bitfield vl_id{F}[B:0] */
#define rpf_vl_id_f_default 0x0
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* RX et_en{F} Bitfield Definitions
 * Preprocessor definitions for the bitfield "et_en{F}".
 * Parameter: filter {F} | stride size 0x4 | range [0, 15]
 * PORT="pif_rpf_et_en_i[0]"
 */

/* Register address for bitfield et_en{F} */
<<<<<<< HEAD
#define HW_ATL_RPF_ET_EN_F_ADR(filter) (0x00005300 + (filter) * 0x4)
/* Bitmask for bitfield et_en{F} */
#define HW_ATL_RPF_ET_EN_F_MSK 0x80000000
/* Inverted bitmask for bitfield et_en{F} */
#define HW_ATL_RPF_ET_EN_F_MSKN 0x7FFFFFFF
/* Lower bit position of bitfield et_en{F} */
#define HW_ATL_RPF_ET_EN_F_SHIFT 31
/* Width of bitfield et_en{F} */
#define HW_ATL_RPF_ET_EN_F_WIDTH 1
/* Default value of bitfield et_en{F} */
#define HW_ATL_RPF_ET_EN_F_DEFAULT 0x0
=======
#define rpf_et_en_f_adr(filter) (0x00005300 + (filter) * 0x4)
/* Bitmask for bitfield et_en{F} */
#define rpf_et_en_f_msk 0x80000000
/* Inverted bitmask for bitfield et_en{F} */
#define rpf_et_en_f_mskn 0x7FFFFFFF
/* Lower bit position of bitfield et_en{F} */
#define rpf_et_en_f_shift 31
/* Width of bitfield et_en{F} */
#define rpf_et_en_f_width 1
/* Default value of bitfield et_en{F} */
#define rpf_et_en_f_default 0x0
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* rx et_en{f} bitfield definitions
 * preprocessor definitions for the bitfield "et_en{f}".
 * parameter: filter {f} | stride size 0x4 | range [0, 15]
 * port="pif_rpf_et_en_i[0]"
 */

/* register address for bitfield et_en{f} */
<<<<<<< HEAD
#define HW_ATL_RPF_ET_ENF_ADR(filter) (0x00005300 + (filter) * 0x4)
/* bitmask for bitfield et_en{f} */
#define HW_ATL_RPF_ET_ENF_MSK 0x80000000
/* inverted bitmask for bitfield et_en{f} */
#define HW_ATL_RPF_ET_ENF_MSKN 0x7fffffff
/* lower bit position of bitfield et_en{f} */
#define HW_ATL_RPF_ET_ENF_SHIFT 31
/* width of bitfield et_en{f} */
#define HW_ATL_RPF_ET_ENF_WIDTH 1
/* default value of bitfield et_en{f} */
#define HW_ATL_RPF_ET_ENF_DEFAULT 0x0
=======
#define rpf_et_enf_adr(filter) (0x00005300 + (filter) * 0x4)
/* bitmask for bitfield et_en{f} */
#define rpf_et_enf_msk 0x80000000
/* inverted bitmask for bitfield et_en{f} */
#define rpf_et_enf_mskn 0x7fffffff
/* lower bit position of bitfield et_en{f} */
#define rpf_et_enf_shift 31
/* width of bitfield et_en{f} */
#define rpf_et_enf_width 1
/* default value of bitfield et_en{f} */
#define rpf_et_enf_default 0x0
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* rx et_up{f}_en bitfield definitions
 * preprocessor definitions for the bitfield "et_up{f}_en".
 * parameter: filter {f} | stride size 0x4 | range [0, 15]
 * port="pif_rpf_et_up_en_i[0]"
 */

/* register address for bitfield et_up{f}_en */
<<<<<<< HEAD
#define HW_ATL_RPF_ET_UPFEN_ADR(filter) (0x00005300 + (filter) * 0x4)
/* bitmask for bitfield et_up{f}_en */
#define HW_ATL_RPF_ET_UPFEN_MSK 0x40000000
/* inverted bitmask for bitfield et_up{f}_en */
#define HW_ATL_RPF_ET_UPFEN_MSKN 0xbfffffff
/* lower bit position of bitfield et_up{f}_en */
#define HW_ATL_RPF_ET_UPFEN_SHIFT 30
/* width of bitfield et_up{f}_en */
#define HW_ATL_RPF_ET_UPFEN_WIDTH 1
/* default value of bitfield et_up{f}_en */
#define HW_ATL_RPF_ET_UPFEN_DEFAULT 0x0
=======
#define rpf_et_upfen_adr(filter) (0x00005300 + (filter) * 0x4)
/* bitmask for bitfield et_up{f}_en */
#define rpf_et_upfen_msk 0x40000000
/* inverted bitmask for bitfield et_up{f}_en */
#define rpf_et_upfen_mskn 0xbfffffff
/* lower bit position of bitfield et_up{f}_en */
#define rpf_et_upfen_shift 30
/* width of bitfield et_up{f}_en */
#define rpf_et_upfen_width 1
/* default value of bitfield et_up{f}_en */
#define rpf_et_upfen_default 0x0
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* rx et_rxq{f}_en bitfield definitions
 * preprocessor definitions for the bitfield "et_rxq{f}_en".
 * parameter: filter {f} | stride size 0x4 | range [0, 15]
 * port="pif_rpf_et_rxq_en_i[0]"
 */

/* register address for bitfield et_rxq{f}_en */
<<<<<<< HEAD
#define HW_ATL_RPF_ET_RXQFEN_ADR(filter) (0x00005300 + (filter) * 0x4)
/* bitmask for bitfield et_rxq{f}_en */
#define HW_ATL_RPF_ET_RXQFEN_MSK 0x20000000
/* inverted bitmask for bitfield et_rxq{f}_en */
#define HW_ATL_RPF_ET_RXQFEN_MSKN 0xdfffffff
/* lower bit position of bitfield et_rxq{f}_en */
#define HW_ATL_RPF_ET_RXQFEN_SHIFT 29
/* width of bitfield et_rxq{f}_en */
#define HW_ATL_RPF_ET_RXQFEN_WIDTH 1
/* default value of bitfield et_rxq{f}_en */
#define HW_ATL_RPF_ET_RXQFEN_DEFAULT 0x0
=======
#define rpf_et_rxqfen_adr(filter) (0x00005300 + (filter) * 0x4)
/* bitmask for bitfield et_rxq{f}_en */
#define rpf_et_rxqfen_msk 0x20000000
/* inverted bitmask for bitfield et_rxq{f}_en */
#define rpf_et_rxqfen_mskn 0xdfffffff
/* lower bit position of bitfield et_rxq{f}_en */
#define rpf_et_rxqfen_shift 29
/* width of bitfield et_rxq{f}_en */
#define rpf_et_rxqfen_width 1
/* default value of bitfield et_rxq{f}_en */
#define rpf_et_rxqfen_default 0x0
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* rx et_up{f}[2:0] bitfield definitions
 * preprocessor definitions for the bitfield "et_up{f}[2:0]".
 * parameter: filter {f} | stride size 0x4 | range [0, 15]
 * port="pif_rpf_et_up0_i[2:0]"
 */

/* register address for bitfield et_up{f}[2:0] */
<<<<<<< HEAD
#define HW_ATL_RPF_ET_UPF_ADR(filter) (0x00005300 + (filter) * 0x4)
/* bitmask for bitfield et_up{f}[2:0] */
#define HW_ATL_RPF_ET_UPF_MSK 0x1c000000
/* inverted bitmask for bitfield et_up{f}[2:0] */
#define HW_ATL_RPF_ET_UPF_MSKN 0xe3ffffff
/* lower bit position of bitfield et_up{f}[2:0] */
#define HW_ATL_RPF_ET_UPF_SHIFT 26
/* width of bitfield et_up{f}[2:0] */
#define HW_ATL_RPF_ET_UPF_WIDTH 3
/* default value of bitfield et_up{f}[2:0] */
#define HW_ATL_RPF_ET_UPF_DEFAULT 0x0
=======
#define rpf_et_upf_adr(filter) (0x00005300 + (filter) * 0x4)
/* bitmask for bitfield et_up{f}[2:0] */
#define rpf_et_upf_msk 0x1c000000
/* inverted bitmask for bitfield et_up{f}[2:0] */
#define rpf_et_upf_mskn 0xe3ffffff
/* lower bit position of bitfield et_up{f}[2:0] */
#define rpf_et_upf_shift 26
/* width of bitfield et_up{f}[2:0] */
#define rpf_et_upf_width 3
/* default value of bitfield et_up{f}[2:0] */
#define rpf_et_upf_default 0x0
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* rx et_rxq{f}[4:0] bitfield definitions
 * preprocessor definitions for the bitfield "et_rxq{f}[4:0]".
 * parameter: filter {f} | stride size 0x4 | range [0, 15]
 * port="pif_rpf_et_rxq0_i[4:0]"
 */

/* register address for bitfield et_rxq{f}[4:0] */
<<<<<<< HEAD
#define HW_ATL_RPF_ET_RXQF_ADR(filter) (0x00005300 + (filter) * 0x4)
/* bitmask for bitfield et_rxq{f}[4:0] */
#define HW_ATL_RPF_ET_RXQF_MSK 0x01f00000
/* inverted bitmask for bitfield et_rxq{f}[4:0] */
#define HW_ATL_RPF_ET_RXQF_MSKN 0xfe0fffff
/* lower bit position of bitfield et_rxq{f}[4:0] */
#define HW_ATL_RPF_ET_RXQF_SHIFT 20
/* width of bitfield et_rxq{f}[4:0] */
#define HW_ATL_RPF_ET_RXQF_WIDTH 5
/* default value of bitfield et_rxq{f}[4:0] */
#define HW_ATL_RPF_ET_RXQF_DEFAULT 0x0
=======
#define rpf_et_rxqf_adr(filter) (0x00005300 + (filter) * 0x4)
/* bitmask for bitfield et_rxq{f}[4:0] */
#define rpf_et_rxqf_msk 0x01f00000
/* inverted bitmask for bitfield et_rxq{f}[4:0] */
#define rpf_et_rxqf_mskn 0xfe0fffff
/* lower bit position of bitfield et_rxq{f}[4:0] */
#define rpf_et_rxqf_shift 20
/* width of bitfield et_rxq{f}[4:0] */
#define rpf_et_rxqf_width 5
/* default value of bitfield et_rxq{f}[4:0] */
#define rpf_et_rxqf_default 0x0
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* rx et_mng_rxq{f} bitfield definitions
 * preprocessor definitions for the bitfield "et_mng_rxq{f}".
 * parameter: filter {f} | stride size 0x4 | range [0, 15]
 * port="pif_rpf_et_mng_rxq_i[0]"
 */

/* register address for bitfield et_mng_rxq{f} */
<<<<<<< HEAD
#define HW_ATL_RPF_ET_MNG_RXQF_ADR(filter) (0x00005300 + (filter) * 0x4)
/* bitmask for bitfield et_mng_rxq{f} */
#define HW_ATL_RPF_ET_MNG_RXQF_MSK 0x00080000
/* inverted bitmask for bitfield et_mng_rxq{f} */
#define HW_ATL_RPF_ET_MNG_RXQF_MSKN 0xfff7ffff
/* lower bit position of bitfield et_mng_rxq{f} */
#define HW_ATL_RPF_ET_MNG_RXQF_SHIFT 19
/* width of bitfield et_mng_rxq{f} */
#define HW_ATL_RPF_ET_MNG_RXQF_WIDTH 1
/* default value of bitfield et_mng_rxq{f} */
#define HW_ATL_RPF_ET_MNG_RXQF_DEFAULT 0x0
=======
#define rpf_et_mng_rxqf_adr(filter) (0x00005300 + (filter) * 0x4)
/* bitmask for bitfield et_mng_rxq{f} */
#define rpf_et_mng_rxqf_msk 0x00080000
/* inverted bitmask for bitfield et_mng_rxq{f} */
#define rpf_et_mng_rxqf_mskn 0xfff7ffff
/* lower bit position of bitfield et_mng_rxq{f} */
#define rpf_et_mng_rxqf_shift 19
/* width of bitfield et_mng_rxq{f} */
#define rpf_et_mng_rxqf_width 1
/* default value of bitfield et_mng_rxq{f} */
#define rpf_et_mng_rxqf_default 0x0
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* rx et_act{f}[2:0] bitfield definitions
 * preprocessor definitions for the bitfield "et_act{f}[2:0]".
 * parameter: filter {f} | stride size 0x4 | range [0, 15]
 * port="pif_rpf_et_act0_i[2:0]"
 */

/* register address for bitfield et_act{f}[2:0] */
<<<<<<< HEAD
#define HW_ATL_RPF_ET_ACTF_ADR(filter) (0x00005300 + (filter) * 0x4)
/* bitmask for bitfield et_act{f}[2:0] */
#define HW_ATL_RPF_ET_ACTF_MSK 0x00070000
/* inverted bitmask for bitfield et_act{f}[2:0] */
#define HW_ATL_RPF_ET_ACTF_MSKN 0xfff8ffff
/* lower bit position of bitfield et_act{f}[2:0] */
#define HW_ATL_RPF_ET_ACTF_SHIFT 16
/* width of bitfield et_act{f}[2:0] */
#define HW_ATL_RPF_ET_ACTF_WIDTH 3
/* default value of bitfield et_act{f}[2:0] */
#define HW_ATL_RPF_ET_ACTF_DEFAULT 0x0
=======
#define rpf_et_actf_adr(filter) (0x00005300 + (filter) * 0x4)
/* bitmask for bitfield et_act{f}[2:0] */
#define rpf_et_actf_msk 0x00070000
/* inverted bitmask for bitfield et_act{f}[2:0] */
#define rpf_et_actf_mskn 0xfff8ffff
/* lower bit position of bitfield et_act{f}[2:0] */
#define rpf_et_actf_shift 16
/* width of bitfield et_act{f}[2:0] */
#define rpf_et_actf_width 3
/* default value of bitfield et_act{f}[2:0] */
#define rpf_et_actf_default 0x0
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* rx et_val{f}[f:0] bitfield definitions
 * preprocessor definitions for the bitfield "et_val{f}[f:0]".
 * parameter: filter {f} | stride size 0x4 | range [0, 15]
 * port="pif_rpf_et_val0_i[15:0]"
 */

/* register address for bitfield et_val{f}[f:0] */
<<<<<<< HEAD
#define HW_ATL_RPF_ET_VALF_ADR(filter) (0x00005300 + (filter) * 0x4)
/* bitmask for bitfield et_val{f}[f:0] */
#define HW_ATL_RPF_ET_VALF_MSK 0x0000ffff
/* inverted bitmask for bitfield et_val{f}[f:0] */
#define HW_ATL_RPF_ET_VALF_MSKN 0xffff0000
/* lower bit position of bitfield et_val{f}[f:0] */
#define HW_ATL_RPF_ET_VALF_SHIFT 0
/* width of bitfield et_val{f}[f:0] */
#define HW_ATL_RPF_ET_VALF_WIDTH 16
/* default value of bitfield et_val{f}[f:0] */
#define HW_ATL_RPF_ET_VALF_DEFAULT 0x0
=======
#define rpf_et_valf_adr(filter) (0x00005300 + (filter) * 0x4)
/* bitmask for bitfield et_val{f}[f:0] */
#define rpf_et_valf_msk 0x0000ffff
/* inverted bitmask for bitfield et_val{f}[f:0] */
#define rpf_et_valf_mskn 0xffff0000
/* lower bit position of bitfield et_val{f}[f:0] */
#define rpf_et_valf_shift 0
/* width of bitfield et_val{f}[f:0] */
#define rpf_et_valf_width 16
/* default value of bitfield et_val{f}[f:0] */
#define rpf_et_valf_default 0x0
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* rx ipv4_chk_en bitfield definitions
 * preprocessor definitions for the bitfield "ipv4_chk_en".
 * port="pif_rpo_ipv4_chk_en_i"
 */

/* register address for bitfield ipv4_chk_en */
<<<<<<< HEAD
#define HW_ATL_RPO_IPV4CHK_EN_ADR 0x00005580
/* bitmask for bitfield ipv4_chk_en */
#define HW_ATL_RPO_IPV4CHK_EN_MSK 0x00000002
/* inverted bitmask for bitfield ipv4_chk_en */
#define HW_ATL_RPO_IPV4CHK_EN_MSKN 0xfffffffd
/* lower bit position of bitfield ipv4_chk_en */
#define HW_ATL_RPO_IPV4CHK_EN_SHIFT 1
/* width of bitfield ipv4_chk_en */
#define HW_ATL_RPO_IPV4CHK_EN_WIDTH 1
/* default value of bitfield ipv4_chk_en */
#define HW_ATL_RPO_IPV4CHK_EN_DEFAULT 0x0
=======
#define rpo_ipv4chk_en_adr 0x00005580
/* bitmask for bitfield ipv4_chk_en */
#define rpo_ipv4chk_en_msk 0x00000002
/* inverted bitmask for bitfield ipv4_chk_en */
#define rpo_ipv4chk_en_mskn 0xfffffffd
/* lower bit position of bitfield ipv4_chk_en */
#define rpo_ipv4chk_en_shift 1
/* width of bitfield ipv4_chk_en */
#define rpo_ipv4chk_en_width 1
/* default value of bitfield ipv4_chk_en */
#define rpo_ipv4chk_en_default 0x0
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* rx desc{d}_vl_strip bitfield definitions
 * preprocessor definitions for the bitfield "desc{d}_vl_strip".
 * parameter: descriptor {d} | stride size 0x20 | range [0, 31]
 * port="pif_rpo_desc_vl_strip_i[0]"
 */

/* register address for bitfield desc{d}_vl_strip */
<<<<<<< HEAD
#define HW_ATL_RPO_DESCDVL_STRIP_ADR(descriptor) \
	(0x00005b08 + (descriptor) * 0x20)
/* bitmask for bitfield desc{d}_vl_strip */
#define HW_ATL_RPO_DESCDVL_STRIP_MSK 0x20000000
/* inverted bitmask for bitfield desc{d}_vl_strip */
#define HW_ATL_RPO_DESCDVL_STRIP_MSKN 0xdfffffff
/* lower bit position of bitfield desc{d}_vl_strip */
#define HW_ATL_RPO_DESCDVL_STRIP_SHIFT 29
/* width of bitfield desc{d}_vl_strip */
#define HW_ATL_RPO_DESCDVL_STRIP_WIDTH 1
/* default value of bitfield desc{d}_vl_strip */
#define HW_ATL_RPO_DESCDVL_STRIP_DEFAULT 0x0
=======
#define rpo_descdvl_strip_adr(descriptor) (0x00005b08 + (descriptor) * 0x20)
/* bitmask for bitfield desc{d}_vl_strip */
#define rpo_descdvl_strip_msk 0x20000000
/* inverted bitmask for bitfield desc{d}_vl_strip */
#define rpo_descdvl_strip_mskn 0xdfffffff
/* lower bit position of bitfield desc{d}_vl_strip */
#define rpo_descdvl_strip_shift 29
/* width of bitfield desc{d}_vl_strip */
#define rpo_descdvl_strip_width 1
/* default value of bitfield desc{d}_vl_strip */
#define rpo_descdvl_strip_default 0x0
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* rx l4_chk_en bitfield definitions
 * preprocessor definitions for the bitfield "l4_chk_en".
 * port="pif_rpo_l4_chk_en_i"
 */

/* register address for bitfield l4_chk_en */
<<<<<<< HEAD
#define HW_ATL_RPOL4CHK_EN_ADR 0x00005580
/* bitmask for bitfield l4_chk_en */
#define HW_ATL_RPOL4CHK_EN_MSK 0x00000001
/* inverted bitmask for bitfield l4_chk_en */
#define HW_ATL_RPOL4CHK_EN_MSKN 0xfffffffe
/* lower bit position of bitfield l4_chk_en */
#define HW_ATL_RPOL4CHK_EN_SHIFT 0
/* width of bitfield l4_chk_en */
#define HW_ATL_RPOL4CHK_EN_WIDTH 1
/* default value of bitfield l4_chk_en */
#define HW_ATL_RPOL4CHK_EN_DEFAULT 0x0
=======
#define rpol4chk_en_adr 0x00005580
/* bitmask for bitfield l4_chk_en */
#define rpol4chk_en_msk 0x00000001
/* inverted bitmask for bitfield l4_chk_en */
#define rpol4chk_en_mskn 0xfffffffe
/* lower bit position of bitfield l4_chk_en */
#define rpol4chk_en_shift 0
/* width of bitfield l4_chk_en */
#define rpol4chk_en_width 1
/* default value of bitfield l4_chk_en */
#define rpol4chk_en_default 0x0
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* rx reg_res_dsbl bitfield definitions
 * preprocessor definitions for the bitfield "reg_res_dsbl".
 * port="pif_rx_reg_res_dsbl_i"
 */

/* register address for bitfield reg_res_dsbl */
<<<<<<< HEAD
#define HW_ATL_RX_REG_RES_DSBL_ADR 0x00005000
/* bitmask for bitfield reg_res_dsbl */
#define HW_ATL_RX_REG_RES_DSBL_MSK 0x20000000
/* inverted bitmask for bitfield reg_res_dsbl */
#define HW_ATL_RX_REG_RES_DSBL_MSKN 0xdfffffff
/* lower bit position of bitfield reg_res_dsbl */
#define HW_ATL_RX_REG_RES_DSBL_SHIFT 29
/* width of bitfield reg_res_dsbl */
#define HW_ATL_RX_REG_RES_DSBL_WIDTH 1
/* default value of bitfield reg_res_dsbl */
#define HW_ATL_RX_REG_RES_DSBL_DEFAULT 0x1
=======
#define rx_reg_res_dsbl_adr 0x00005000
/* bitmask for bitfield reg_res_dsbl */
#define rx_reg_res_dsbl_msk 0x20000000
/* inverted bitmask for bitfield reg_res_dsbl */
#define rx_reg_res_dsbl_mskn 0xdfffffff
/* lower bit position of bitfield reg_res_dsbl */
#define rx_reg_res_dsbl_shift 29
/* width of bitfield reg_res_dsbl */
#define rx_reg_res_dsbl_width 1
/* default value of bitfield reg_res_dsbl */
#define rx_reg_res_dsbl_default 0x1
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* tx dca{d}_cpuid[7:0] bitfield definitions
 * preprocessor definitions for the bitfield "dca{d}_cpuid[7:0]".
 * parameter: dca {d} | stride size 0x4 | range [0, 31]
 * port="pif_tdm_dca0_cpuid_i[7:0]"
 */

/* register address for bitfield dca{d}_cpuid[7:0] */
<<<<<<< HEAD
#define HW_ATL_TDM_DCADCPUID_ADR(dca) (0x00008400 + (dca) * 0x4)
/* bitmask for bitfield dca{d}_cpuid[7:0] */
#define HW_ATL_TDM_DCADCPUID_MSK 0x000000ff
/* inverted bitmask for bitfield dca{d}_cpuid[7:0] */
#define HW_ATL_TDM_DCADCPUID_MSKN 0xffffff00
/* lower bit position of bitfield dca{d}_cpuid[7:0] */
#define HW_ATL_TDM_DCADCPUID_SHIFT 0
/* width of bitfield dca{d}_cpuid[7:0] */
#define HW_ATL_TDM_DCADCPUID_WIDTH 8
/* default value of bitfield dca{d}_cpuid[7:0] */
#define HW_ATL_TDM_DCADCPUID_DEFAULT 0x0
=======
#define tdm_dcadcpuid_adr(dca) (0x00008400 + (dca) * 0x4)
/* bitmask for bitfield dca{d}_cpuid[7:0] */
#define tdm_dcadcpuid_msk 0x000000ff
/* inverted bitmask for bitfield dca{d}_cpuid[7:0] */
#define tdm_dcadcpuid_mskn 0xffffff00
/* lower bit position of bitfield dca{d}_cpuid[7:0] */
#define tdm_dcadcpuid_shift 0
/* width of bitfield dca{d}_cpuid[7:0] */
#define tdm_dcadcpuid_width 8
/* default value of bitfield dca{d}_cpuid[7:0] */
#define tdm_dcadcpuid_default 0x0
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* tx lso_en[1f:0] bitfield definitions
 * preprocessor definitions for the bitfield "lso_en[1f:0]".
 * port="pif_tdm_lso_en_i[31:0]"
 */

/* register address for bitfield lso_en[1f:0] */
<<<<<<< HEAD
#define HW_ATL_TDM_LSO_EN_ADR 0x00007810
/* bitmask for bitfield lso_en[1f:0] */
#define HW_ATL_TDM_LSO_EN_MSK 0xffffffff
/* inverted bitmask for bitfield lso_en[1f:0] */
#define HW_ATL_TDM_LSO_EN_MSKN 0x00000000
/* lower bit position of bitfield lso_en[1f:0] */
#define HW_ATL_TDM_LSO_EN_SHIFT 0
/* width of bitfield lso_en[1f:0] */
#define HW_ATL_TDM_LSO_EN_WIDTH 32
/* default value of bitfield lso_en[1f:0] */
#define HW_ATL_TDM_LSO_EN_DEFAULT 0x0
=======
#define tdm_lso_en_adr 0x00007810
/* bitmask for bitfield lso_en[1f:0] */
#define tdm_lso_en_msk 0xffffffff
/* inverted bitmask for bitfield lso_en[1f:0] */
#define tdm_lso_en_mskn 0x00000000
/* lower bit position of bitfield lso_en[1f:0] */
#define tdm_lso_en_shift 0
/* width of bitfield lso_en[1f:0] */
#define tdm_lso_en_width 32
/* default value of bitfield lso_en[1f:0] */
#define tdm_lso_en_default 0x0
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* tx dca_en bitfield definitions
 * preprocessor definitions for the bitfield "dca_en".
 * port="pif_tdm_dca_en_i"
 */

/* register address for bitfield dca_en */
<<<<<<< HEAD
#define HW_ATL_TDM_DCA_EN_ADR 0x00008480
/* bitmask for bitfield dca_en */
#define HW_ATL_TDM_DCA_EN_MSK 0x80000000
/* inverted bitmask for bitfield dca_en */
#define HW_ATL_TDM_DCA_EN_MSKN 0x7fffffff
/* lower bit position of bitfield dca_en */
#define HW_ATL_TDM_DCA_EN_SHIFT 31
/* width of bitfield dca_en */
#define HW_ATL_TDM_DCA_EN_WIDTH 1
/* default value of bitfield dca_en */
#define HW_ATL_TDM_DCA_EN_DEFAULT 0x1
=======
#define tdm_dca_en_adr 0x00008480
/* bitmask for bitfield dca_en */
#define tdm_dca_en_msk 0x80000000
/* inverted bitmask for bitfield dca_en */
#define tdm_dca_en_mskn 0x7fffffff
/* lower bit position of bitfield dca_en */
#define tdm_dca_en_shift 31
/* width of bitfield dca_en */
#define tdm_dca_en_width 1
/* default value of bitfield dca_en */
#define tdm_dca_en_default 0x1
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* tx dca_mode[3:0] bitfield definitions
 * preprocessor definitions for the bitfield "dca_mode[3:0]".
 * port="pif_tdm_dca_mode_i[3:0]"
 */

/* register address for bitfield dca_mode[3:0] */
<<<<<<< HEAD
#define HW_ATL_TDM_DCA_MODE_ADR 0x00008480
/* bitmask for bitfield dca_mode[3:0] */
#define HW_ATL_TDM_DCA_MODE_MSK 0x0000000f
/* inverted bitmask for bitfield dca_mode[3:0] */
#define HW_ATL_TDM_DCA_MODE_MSKN 0xfffffff0
/* lower bit position of bitfield dca_mode[3:0] */
#define HW_ATL_TDM_DCA_MODE_SHIFT 0
/* width of bitfield dca_mode[3:0] */
#define HW_ATL_TDM_DCA_MODE_WIDTH 4
/* default value of bitfield dca_mode[3:0] */
#define HW_ATL_TDM_DCA_MODE_DEFAULT 0x0
=======
#define tdm_dca_mode_adr 0x00008480
/* bitmask for bitfield dca_mode[3:0] */
#define tdm_dca_mode_msk 0x0000000f
/* inverted bitmask for bitfield dca_mode[3:0] */
#define tdm_dca_mode_mskn 0xfffffff0
/* lower bit position of bitfield dca_mode[3:0] */
#define tdm_dca_mode_shift 0
/* width of bitfield dca_mode[3:0] */
#define tdm_dca_mode_width 4
/* default value of bitfield dca_mode[3:0] */
#define tdm_dca_mode_default 0x0
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* tx dca{d}_desc_en bitfield definitions
 * preprocessor definitions for the bitfield "dca{d}_desc_en".
 * parameter: dca {d} | stride size 0x4 | range [0, 31]
 * port="pif_tdm_dca_desc_en_i[0]"
 */

/* register address for bitfield dca{d}_desc_en */
<<<<<<< HEAD
#define HW_ATL_TDM_DCADDESC_EN_ADR(dca) (0x00008400 + (dca) * 0x4)
/* bitmask for bitfield dca{d}_desc_en */
#define HW_ATL_TDM_DCADDESC_EN_MSK 0x80000000
/* inverted bitmask for bitfield dca{d}_desc_en */
#define HW_ATL_TDM_DCADDESC_EN_MSKN 0x7fffffff
/* lower bit position of bitfield dca{d}_desc_en */
#define HW_ATL_TDM_DCADDESC_EN_SHIFT 31
/* width of bitfield dca{d}_desc_en */
#define HW_ATL_TDM_DCADDESC_EN_WIDTH 1
/* default value of bitfield dca{d}_desc_en */
#define HW_ATL_TDM_DCADDESC_EN_DEFAULT 0x0
=======
#define tdm_dcaddesc_en_adr(dca) (0x00008400 + (dca) * 0x4)
/* bitmask for bitfield dca{d}_desc_en */
#define tdm_dcaddesc_en_msk 0x80000000
/* inverted bitmask for bitfield dca{d}_desc_en */
#define tdm_dcaddesc_en_mskn 0x7fffffff
/* lower bit position of bitfield dca{d}_desc_en */
#define tdm_dcaddesc_en_shift 31
/* width of bitfield dca{d}_desc_en */
#define tdm_dcaddesc_en_width 1
/* default value of bitfield dca{d}_desc_en */
#define tdm_dcaddesc_en_default 0x0
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* tx desc{d}_en bitfield definitions
 * preprocessor definitions for the bitfield "desc{d}_en".
 * parameter: descriptor {d} | stride size 0x40 | range [0, 31]
 * port="pif_tdm_desc_en_i[0]"
 */

/* register address for bitfield desc{d}_en */
<<<<<<< HEAD
#define HW_ATL_TDM_DESCDEN_ADR(descriptor) (0x00007c08 + (descriptor) * 0x40)
/* bitmask for bitfield desc{d}_en */
#define HW_ATL_TDM_DESCDEN_MSK 0x80000000
/* inverted bitmask for bitfield desc{d}_en */
#define HW_ATL_TDM_DESCDEN_MSKN 0x7fffffff
/* lower bit position of bitfield desc{d}_en */
#define HW_ATL_TDM_DESCDEN_SHIFT 31
/* width of bitfield desc{d}_en */
#define HW_ATL_TDM_DESCDEN_WIDTH 1
/* default value of bitfield desc{d}_en */
#define HW_ATL_TDM_DESCDEN_DEFAULT 0x0
=======
#define tdm_descden_adr(descriptor) (0x00007c08 + (descriptor) * 0x40)
/* bitmask for bitfield desc{d}_en */
#define tdm_descden_msk 0x80000000
/* inverted bitmask for bitfield desc{d}_en */
#define tdm_descden_mskn 0x7fffffff
/* lower bit position of bitfield desc{d}_en */
#define tdm_descden_shift 31
/* width of bitfield desc{d}_en */
#define tdm_descden_width 1
/* default value of bitfield desc{d}_en */
#define tdm_descden_default 0x0
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* tx desc{d}_hd[c:0] bitfield definitions
 * preprocessor definitions for the bitfield "desc{d}_hd[c:0]".
 * parameter: descriptor {d} | stride size 0x40 | range [0, 31]
 * port="tdm_pif_desc0_hd_o[12:0]"
 */

/* register address for bitfield desc{d}_hd[c:0] */
<<<<<<< HEAD
#define HW_ATL_TDM_DESCDHD_ADR(descriptor) (0x00007c0c + (descriptor) * 0x40)
/* bitmask for bitfield desc{d}_hd[c:0] */
#define HW_ATL_TDM_DESCDHD_MSK 0x00001fff
/* inverted bitmask for bitfield desc{d}_hd[c:0] */
#define HW_ATL_TDM_DESCDHD_MSKN 0xffffe000
/* lower bit position of bitfield desc{d}_hd[c:0] */
#define HW_ATL_TDM_DESCDHD_SHIFT 0
/* width of bitfield desc{d}_hd[c:0] */
#define HW_ATL_TDM_DESCDHD_WIDTH 13
=======
#define tdm_descdhd_adr(descriptor) (0x00007c0c + (descriptor) * 0x40)
/* bitmask for bitfield desc{d}_hd[c:0] */
#define tdm_descdhd_msk 0x00001fff
/* inverted bitmask for bitfield desc{d}_hd[c:0] */
#define tdm_descdhd_mskn 0xffffe000
/* lower bit position of bitfield desc{d}_hd[c:0] */
#define tdm_descdhd_shift 0
/* width of bitfield desc{d}_hd[c:0] */
#define tdm_descdhd_width 13
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* tx desc{d}_len[9:0] bitfield definitions
 * preprocessor definitions for the bitfield "desc{d}_len[9:0]".
 * parameter: descriptor {d} | stride size 0x40 | range [0, 31]
 * port="pif_tdm_desc0_len_i[9:0]"
 */

/* register address for bitfield desc{d}_len[9:0] */
<<<<<<< HEAD
#define HW_ATL_TDM_DESCDLEN_ADR(descriptor) (0x00007c08 + (descriptor) * 0x40)
/* bitmask for bitfield desc{d}_len[9:0] */
#define HW_ATL_TDM_DESCDLEN_MSK 0x00001ff8
/* inverted bitmask for bitfield desc{d}_len[9:0] */
#define HW_ATL_TDM_DESCDLEN_MSKN 0xffffe007
/* lower bit position of bitfield desc{d}_len[9:0] */
#define HW_ATL_TDM_DESCDLEN_SHIFT 3
/* width of bitfield desc{d}_len[9:0] */
#define HW_ATL_TDM_DESCDLEN_WIDTH 10
/* default value of bitfield desc{d}_len[9:0] */
#define HW_ATL_TDM_DESCDLEN_DEFAULT 0x0
=======
#define tdm_descdlen_adr(descriptor) (0x00007c08 + (descriptor) * 0x40)
/* bitmask for bitfield desc{d}_len[9:0] */
#define tdm_descdlen_msk 0x00001ff8
/* inverted bitmask for bitfield desc{d}_len[9:0] */
#define tdm_descdlen_mskn 0xffffe007
/* lower bit position of bitfield desc{d}_len[9:0] */
#define tdm_descdlen_shift 3
/* width of bitfield desc{d}_len[9:0] */
#define tdm_descdlen_width 10
/* default value of bitfield desc{d}_len[9:0] */
#define tdm_descdlen_default 0x0
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* tx int_desc_wrb_en bitfield definitions
 * preprocessor definitions for the bitfield "int_desc_wrb_en".
 * port="pif_tdm_int_desc_wrb_en_i"
 */

/* register address for bitfield int_desc_wrb_en */
<<<<<<< HEAD
#define HW_ATL_TDM_INT_DESC_WRB_EN_ADR 0x00007b40
/* bitmask for bitfield int_desc_wrb_en */
#define HW_ATL_TDM_INT_DESC_WRB_EN_MSK 0x00000002
/* inverted bitmask for bitfield int_desc_wrb_en */
#define HW_ATL_TDM_INT_DESC_WRB_EN_MSKN 0xfffffffd
/* lower bit position of bitfield int_desc_wrb_en */
#define HW_ATL_TDM_INT_DESC_WRB_EN_SHIFT 1
/* width of bitfield int_desc_wrb_en */
#define HW_ATL_TDM_INT_DESC_WRB_EN_WIDTH 1
/* default value of bitfield int_desc_wrb_en */
#define HW_ATL_TDM_INT_DESC_WRB_EN_DEFAULT 0x0
=======
#define tdm_int_desc_wrb_en_adr 0x00007b40
/* bitmask for bitfield int_desc_wrb_en */
#define tdm_int_desc_wrb_en_msk 0x00000002
/* inverted bitmask for bitfield int_desc_wrb_en */
#define tdm_int_desc_wrb_en_mskn 0xfffffffd
/* lower bit position of bitfield int_desc_wrb_en */
#define tdm_int_desc_wrb_en_shift 1
/* width of bitfield int_desc_wrb_en */
#define tdm_int_desc_wrb_en_width 1
/* default value of bitfield int_desc_wrb_en */
#define tdm_int_desc_wrb_en_default 0x0
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* tx desc{d}_wrb_thresh[6:0] bitfield definitions
 * preprocessor definitions for the bitfield "desc{d}_wrb_thresh[6:0]".
 * parameter: descriptor {d} | stride size 0x40 | range [0, 31]
 * port="pif_tdm_desc0_wrb_thresh_i[6:0]"
 */

/* register address for bitfield desc{d}_wrb_thresh[6:0] */
<<<<<<< HEAD
#define HW_ATL_TDM_DESCDWRB_THRESH_ADR(descriptor) \
	(0x00007c18 + (descriptor) * 0x40)
/* bitmask for bitfield desc{d}_wrb_thresh[6:0] */
#define HW_ATL_TDM_DESCDWRB_THRESH_MSK 0x00007f00
/* inverted bitmask for bitfield desc{d}_wrb_thresh[6:0] */
#define HW_ATL_TDM_DESCDWRB_THRESH_MSKN 0xffff80ff
/* lower bit position of bitfield desc{d}_wrb_thresh[6:0] */
#define HW_ATL_TDM_DESCDWRB_THRESH_SHIFT 8
/* width of bitfield desc{d}_wrb_thresh[6:0] */
#define HW_ATL_TDM_DESCDWRB_THRESH_WIDTH 7
/* default value of bitfield desc{d}_wrb_thresh[6:0] */
#define HW_ATL_TDM_DESCDWRB_THRESH_DEFAULT 0x0
=======
#define tdm_descdwrb_thresh_adr(descriptor) (0x00007c18 + (descriptor) * 0x40)
/* bitmask for bitfield desc{d}_wrb_thresh[6:0] */
#define tdm_descdwrb_thresh_msk 0x00007f00
/* inverted bitmask for bitfield desc{d}_wrb_thresh[6:0] */
#define tdm_descdwrb_thresh_mskn 0xffff80ff
/* lower bit position of bitfield desc{d}_wrb_thresh[6:0] */
#define tdm_descdwrb_thresh_shift 8
/* width of bitfield desc{d}_wrb_thresh[6:0] */
#define tdm_descdwrb_thresh_width 7
/* default value of bitfield desc{d}_wrb_thresh[6:0] */
#define tdm_descdwrb_thresh_default 0x0
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* tx lso_tcp_flag_first[b:0] bitfield definitions
 * preprocessor definitions for the bitfield "lso_tcp_flag_first[b:0]".
 * port="pif_thm_lso_tcp_flag_first_i[11:0]"
 */

/* register address for bitfield lso_tcp_flag_first[b:0] */
<<<<<<< HEAD
#define HW_ATL_THM_LSO_TCP_FLAG_FIRST_ADR 0x00007820
/* bitmask for bitfield lso_tcp_flag_first[b:0] */
#define HW_ATL_THM_LSO_TCP_FLAG_FIRST_MSK 0x00000fff
/* inverted bitmask for bitfield lso_tcp_flag_first[b:0] */
#define HW_ATL_THM_LSO_TCP_FLAG_FIRST_MSKN 0xfffff000
/* lower bit position of bitfield lso_tcp_flag_first[b:0] */
#define HW_ATL_THM_LSO_TCP_FLAG_FIRST_SHIFT 0
/* width of bitfield lso_tcp_flag_first[b:0] */
#define HW_ATL_THM_LSO_TCP_FLAG_FIRST_WIDTH 12
/* default value of bitfield lso_tcp_flag_first[b:0] */
#define HW_ATL_THM_LSO_TCP_FLAG_FIRST_DEFAULT 0x0
=======
#define thm_lso_tcp_flag_first_adr 0x00007820
/* bitmask for bitfield lso_tcp_flag_first[b:0] */
#define thm_lso_tcp_flag_first_msk 0x00000fff
/* inverted bitmask for bitfield lso_tcp_flag_first[b:0] */
#define thm_lso_tcp_flag_first_mskn 0xfffff000
/* lower bit position of bitfield lso_tcp_flag_first[b:0] */
#define thm_lso_tcp_flag_first_shift 0
/* width of bitfield lso_tcp_flag_first[b:0] */
#define thm_lso_tcp_flag_first_width 12
/* default value of bitfield lso_tcp_flag_first[b:0] */
#define thm_lso_tcp_flag_first_default 0x0
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* tx lso_tcp_flag_last[b:0] bitfield definitions
 * preprocessor definitions for the bitfield "lso_tcp_flag_last[b:0]".
 * port="pif_thm_lso_tcp_flag_last_i[11:0]"
 */

/* register address for bitfield lso_tcp_flag_last[b:0] */
<<<<<<< HEAD
#define HW_ATL_THM_LSO_TCP_FLAG_LAST_ADR 0x00007824
/* bitmask for bitfield lso_tcp_flag_last[b:0] */
#define HW_ATL_THM_LSO_TCP_FLAG_LAST_MSK 0x00000fff
/* inverted bitmask for bitfield lso_tcp_flag_last[b:0] */
#define HW_ATL_THM_LSO_TCP_FLAG_LAST_MSKN 0xfffff000
/* lower bit position of bitfield lso_tcp_flag_last[b:0] */
#define HW_ATL_THM_LSO_TCP_FLAG_LAST_SHIFT 0
/* width of bitfield lso_tcp_flag_last[b:0] */
#define HW_ATL_THM_LSO_TCP_FLAG_LAST_WIDTH 12
/* default value of bitfield lso_tcp_flag_last[b:0] */
#define HW_ATL_THM_LSO_TCP_FLAG_LAST_DEFAULT 0x0
=======
#define thm_lso_tcp_flag_last_adr 0x00007824
/* bitmask for bitfield lso_tcp_flag_last[b:0] */
#define thm_lso_tcp_flag_last_msk 0x00000fff
/* inverted bitmask for bitfield lso_tcp_flag_last[b:0] */
#define thm_lso_tcp_flag_last_mskn 0xfffff000
/* lower bit position of bitfield lso_tcp_flag_last[b:0] */
#define thm_lso_tcp_flag_last_shift 0
/* width of bitfield lso_tcp_flag_last[b:0] */
#define thm_lso_tcp_flag_last_width 12
/* default value of bitfield lso_tcp_flag_last[b:0] */
#define thm_lso_tcp_flag_last_default 0x0
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* tx lso_tcp_flag_mid[b:0] bitfield definitions
 * preprocessor definitions for the bitfield "lso_tcp_flag_mid[b:0]".
 * port="pif_thm_lso_tcp_flag_mid_i[11:0]"
 */

/* Register address for bitfield lro_rsc_max[1F:0] */
<<<<<<< HEAD
#define HW_ATL_RPO_LRO_RSC_MAX_ADR 0x00005598
/* Bitmask for bitfield lro_rsc_max[1F:0] */
#define HW_ATL_RPO_LRO_RSC_MAX_MSK 0xFFFFFFFF
/* Inverted bitmask for bitfield lro_rsc_max[1F:0] */
#define HW_ATL_RPO_LRO_RSC_MAX_MSKN 0x00000000
/* Lower bit position of bitfield lro_rsc_max[1F:0] */
#define HW_ATL_RPO_LRO_RSC_MAX_SHIFT 0
/* Width of bitfield lro_rsc_max[1F:0] */
#define HW_ATL_RPO_LRO_RSC_MAX_WIDTH 32
/* Default value of bitfield lro_rsc_max[1F:0] */
#define HW_ATL_RPO_LRO_RSC_MAX_DEFAULT 0x0
=======
#define rpo_lro_rsc_max_adr 0x00005598
/* Bitmask for bitfield lro_rsc_max[1F:0] */
#define rpo_lro_rsc_max_msk 0xFFFFFFFF
/* Inverted bitmask for bitfield lro_rsc_max[1F:0] */
#define rpo_lro_rsc_max_mskn 0x00000000
/* Lower bit position of bitfield lro_rsc_max[1F:0] */
#define rpo_lro_rsc_max_shift 0
/* Width of bitfield lro_rsc_max[1F:0] */
#define rpo_lro_rsc_max_width 32
/* Default value of bitfield lro_rsc_max[1F:0] */
#define rpo_lro_rsc_max_default 0x0
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* RX lro_en[1F:0] Bitfield Definitions
 * Preprocessor definitions for the bitfield "lro_en[1F:0]".
 * PORT="pif_rpo_lro_en_i[31:0]"
 */

/* Register address for bitfield lro_en[1F:0] */
<<<<<<< HEAD
#define HW_ATL_RPO_LRO_EN_ADR 0x00005590
/* Bitmask for bitfield lro_en[1F:0] */
#define HW_ATL_RPO_LRO_EN_MSK 0xFFFFFFFF
/* Inverted bitmask for bitfield lro_en[1F:0] */
#define HW_ATL_RPO_LRO_EN_MSKN 0x00000000
/* Lower bit position of bitfield lro_en[1F:0] */
#define HW_ATL_RPO_LRO_EN_SHIFT 0
/* Width of bitfield lro_en[1F:0] */
#define HW_ATL_RPO_LRO_EN_WIDTH 32
/* Default value of bitfield lro_en[1F:0] */
#define HW_ATL_RPO_LRO_EN_DEFAULT 0x0
=======
#define rpo_lro_en_adr 0x00005590
/* Bitmask for bitfield lro_en[1F:0] */
#define rpo_lro_en_msk 0xFFFFFFFF
/* Inverted bitmask for bitfield lro_en[1F:0] */
#define rpo_lro_en_mskn 0x00000000
/* Lower bit position of bitfield lro_en[1F:0] */
#define rpo_lro_en_shift 0
/* Width of bitfield lro_en[1F:0] */
#define rpo_lro_en_width 32
/* Default value of bitfield lro_en[1F:0] */
#define rpo_lro_en_default 0x0
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* RX lro_ptopt_en Bitfield Definitions
 * Preprocessor definitions for the bitfield "lro_ptopt_en".
 * PORT="pif_rpo_lro_ptopt_en_i"
 */

/* Register address for bitfield lro_ptopt_en */
<<<<<<< HEAD
#define HW_ATL_RPO_LRO_PTOPT_EN_ADR 0x00005594
/* Bitmask for bitfield lro_ptopt_en */
#define HW_ATL_RPO_LRO_PTOPT_EN_MSK 0x00008000
/* Inverted bitmask for bitfield lro_ptopt_en */
#define HW_ATL_RPO_LRO_PTOPT_EN_MSKN 0xFFFF7FFF
/* Lower bit position of bitfield lro_ptopt_en */
#define HW_ATL_RPO_LRO_PTOPT_EN_SHIFT 15
/* Width of bitfield lro_ptopt_en */
#define HW_ATL_RPO_LRO_PTOPT_EN_WIDTH 1
/* Default value of bitfield lro_ptopt_en */
#define HW_ATL_RPO_LRO_PTOPT_EN_DEFALT 0x1
=======
#define rpo_lro_ptopt_en_adr 0x00005594
/* Bitmask for bitfield lro_ptopt_en */
#define rpo_lro_ptopt_en_msk 0x00008000
/* Inverted bitmask for bitfield lro_ptopt_en */
#define rpo_lro_ptopt_en_mskn 0xFFFF7FFF
/* Lower bit position of bitfield lro_ptopt_en */
#define rpo_lro_ptopt_en_shift 15
/* Width of bitfield lro_ptopt_en */
#define rpo_lro_ptopt_en_width 1
/* Default value of bitfield lro_ptopt_en */
#define rpo_lro_ptopt_en_defalt 0x1
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* RX lro_q_ses_lmt Bitfield Definitions
 * Preprocessor definitions for the bitfield "lro_q_ses_lmt".
 * PORT="pif_rpo_lro_q_ses_lmt_i[1:0]"
 */

/* Register address for bitfield lro_q_ses_lmt */
<<<<<<< HEAD
#define HW_ATL_RPO_LRO_QSES_LMT_ADR 0x00005594
/* Bitmask for bitfield lro_q_ses_lmt */
#define HW_ATL_RPO_LRO_QSES_LMT_MSK 0x00003000
/* Inverted bitmask for bitfield lro_q_ses_lmt */
#define HW_ATL_RPO_LRO_QSES_LMT_MSKN 0xFFFFCFFF
/* Lower bit position of bitfield lro_q_ses_lmt */
#define HW_ATL_RPO_LRO_QSES_LMT_SHIFT 12
/* Width of bitfield lro_q_ses_lmt */
#define HW_ATL_RPO_LRO_QSES_LMT_WIDTH 2
/* Default value of bitfield lro_q_ses_lmt */
#define HW_ATL_RPO_LRO_QSES_LMT_DEFAULT 0x1
=======
#define rpo_lro_qses_lmt_adr 0x00005594
/* Bitmask for bitfield lro_q_ses_lmt */
#define rpo_lro_qses_lmt_msk 0x00003000
/* Inverted bitmask for bitfield lro_q_ses_lmt */
#define rpo_lro_qses_lmt_mskn 0xFFFFCFFF
/* Lower bit position of bitfield lro_q_ses_lmt */
#define rpo_lro_qses_lmt_shift 12
/* Width of bitfield lro_q_ses_lmt */
#define rpo_lro_qses_lmt_width 2
/* Default value of bitfield lro_q_ses_lmt */
#define rpo_lro_qses_lmt_default 0x1
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* RX lro_tot_dsc_lmt[1:0] Bitfield Definitions
 * Preprocessor definitions for the bitfield "lro_tot_dsc_lmt[1:0]".
 * PORT="pif_rpo_lro_tot_dsc_lmt_i[1:0]"
 */

/* Register address for bitfield lro_tot_dsc_lmt[1:0] */
<<<<<<< HEAD
#define HW_ATL_RPO_LRO_TOT_DSC_LMT_ADR 0x00005594
/* Bitmask for bitfield lro_tot_dsc_lmt[1:0] */
#define HW_ATL_RPO_LRO_TOT_DSC_LMT_MSK 0x00000060
/* Inverted bitmask for bitfield lro_tot_dsc_lmt[1:0] */
#define HW_ATL_RPO_LRO_TOT_DSC_LMT_MSKN 0xFFFFFF9F
/* Lower bit position of bitfield lro_tot_dsc_lmt[1:0] */
#define HW_ATL_RPO_LRO_TOT_DSC_LMT_SHIFT 5
/* Width of bitfield lro_tot_dsc_lmt[1:0] */
#define HW_ATL_RPO_LRO_TOT_DSC_LMT_WIDTH 2
/* Default value of bitfield lro_tot_dsc_lmt[1:0] */
#define HW_ATL_RPO_LRO_TOT_DSC_LMT_DEFALT 0x1
=======
#define rpo_lro_tot_dsc_lmt_adr 0x00005594
/* Bitmask for bitfield lro_tot_dsc_lmt[1:0] */
#define rpo_lro_tot_dsc_lmt_msk 0x00000060
/* Inverted bitmask for bitfield lro_tot_dsc_lmt[1:0] */
#define rpo_lro_tot_dsc_lmt_mskn 0xFFFFFF9F
/* Lower bit position of bitfield lro_tot_dsc_lmt[1:0] */
#define rpo_lro_tot_dsc_lmt_shift 5
/* Width of bitfield lro_tot_dsc_lmt[1:0] */
#define rpo_lro_tot_dsc_lmt_width 2
/* Default value of bitfield lro_tot_dsc_lmt[1:0] */
#define rpo_lro_tot_dsc_lmt_defalt 0x1
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* RX lro_pkt_min[4:0] Bitfield Definitions
 * Preprocessor definitions for the bitfield "lro_pkt_min[4:0]".
 * PORT="pif_rpo_lro_pkt_min_i[4:0]"
 */

/* Register address for bitfield lro_pkt_min[4:0] */
<<<<<<< HEAD
#define HW_ATL_RPO_LRO_PKT_MIN_ADR 0x00005594
/* Bitmask for bitfield lro_pkt_min[4:0] */
#define HW_ATL_RPO_LRO_PKT_MIN_MSK 0x0000001F
/* Inverted bitmask for bitfield lro_pkt_min[4:0] */
#define HW_ATL_RPO_LRO_PKT_MIN_MSKN 0xFFFFFFE0
/* Lower bit position of bitfield lro_pkt_min[4:0] */
#define HW_ATL_RPO_LRO_PKT_MIN_SHIFT 0
/* Width of bitfield lro_pkt_min[4:0] */
#define HW_ATL_RPO_LRO_PKT_MIN_WIDTH 5
/* Default value of bitfield lro_pkt_min[4:0] */
#define HW_ATL_RPO_LRO_PKT_MIN_DEFAULT 0x8

/* Width of bitfield lro{L}_des_max[1:0] */
#define HW_ATL_RPO_LRO_LDES_MAX_WIDTH 2
/* Default value of bitfield lro{L}_des_max[1:0] */
#define HW_ATL_RPO_LRO_LDES_MAX_DEFAULT 0x0
=======
#define rpo_lro_pkt_min_adr 0x00005594
/* Bitmask for bitfield lro_pkt_min[4:0] */
#define rpo_lro_pkt_min_msk 0x0000001F
/* Inverted bitmask for bitfield lro_pkt_min[4:0] */
#define rpo_lro_pkt_min_mskn 0xFFFFFFE0
/* Lower bit position of bitfield lro_pkt_min[4:0] */
#define rpo_lro_pkt_min_shift 0
/* Width of bitfield lro_pkt_min[4:0] */
#define rpo_lro_pkt_min_width 5
/* Default value of bitfield lro_pkt_min[4:0] */
#define rpo_lro_pkt_min_default 0x8

/* Width of bitfield lro{L}_des_max[1:0] */
#define rpo_lro_ldes_max_width 2
/* Default value of bitfield lro{L}_des_max[1:0] */
#define rpo_lro_ldes_max_default 0x0
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* RX lro_tb_div[11:0] Bitfield Definitions
 * Preprocessor definitions for the bitfield "lro_tb_div[11:0]".
 * PORT="pif_rpo_lro_tb_div_i[11:0]"
 */

/* Register address for bitfield lro_tb_div[11:0] */
<<<<<<< HEAD
#define HW_ATL_RPO_LRO_TB_DIV_ADR 0x00005620
/* Bitmask for bitfield lro_tb_div[11:0] */
#define HW_ATL_RPO_LRO_TB_DIV_MSK 0xFFF00000
/* Inverted bitmask for bitfield lro_tb_div[11:0] */
#define HW_ATL_RPO_LRO_TB_DIV_MSKN 0x000FFFFF
/* Lower bit position of bitfield lro_tb_div[11:0] */
#define HW_ATL_RPO_LRO_TB_DIV_SHIFT 20
/* Width of bitfield lro_tb_div[11:0] */
#define HW_ATL_RPO_LRO_TB_DIV_WIDTH 12
/* Default value of bitfield lro_tb_div[11:0] */
#define HW_ATL_RPO_LRO_TB_DIV_DEFAULT 0xC35
=======
#define rpo_lro_tb_div_adr 0x00005620
/* Bitmask for bitfield lro_tb_div[11:0] */
#define rpo_lro_tb_div_msk 0xFFF00000
/* Inverted bitmask for bitfield lro_tb_div[11:0] */
#define rpo_lro_tb_div_mskn 0x000FFFFF
/* Lower bit position of bitfield lro_tb_div[11:0] */
#define rpo_lro_tb_div_shift 20
/* Width of bitfield lro_tb_div[11:0] */
#define rpo_lro_tb_div_width 12
/* Default value of bitfield lro_tb_div[11:0] */
#define rpo_lro_tb_div_default 0xC35
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* RX lro_ina_ival[9:0] Bitfield Definitions
 *   Preprocessor definitions for the bitfield "lro_ina_ival[9:0]".
 *   PORT="pif_rpo_lro_ina_ival_i[9:0]"
 */

/* Register address for bitfield lro_ina_ival[9:0] */
<<<<<<< HEAD
#define HW_ATL_RPO_LRO_INA_IVAL_ADR 0x00005620
/* Bitmask for bitfield lro_ina_ival[9:0] */
#define HW_ATL_RPO_LRO_INA_IVAL_MSK 0x000FFC00
/* Inverted bitmask for bitfield lro_ina_ival[9:0] */
#define HW_ATL_RPO_LRO_INA_IVAL_MSKN 0xFFF003FF
/* Lower bit position of bitfield lro_ina_ival[9:0] */
#define HW_ATL_RPO_LRO_INA_IVAL_SHIFT 10
/* Width of bitfield lro_ina_ival[9:0] */
#define HW_ATL_RPO_LRO_INA_IVAL_WIDTH 10
/* Default value of bitfield lro_ina_ival[9:0] */
#define HW_ATL_RPO_LRO_INA_IVAL_DEFAULT 0xA
=======
#define rpo_lro_ina_ival_adr 0x00005620
/* Bitmask for bitfield lro_ina_ival[9:0] */
#define rpo_lro_ina_ival_msk 0x000FFC00
/* Inverted bitmask for bitfield lro_ina_ival[9:0] */
#define rpo_lro_ina_ival_mskn 0xFFF003FF
/* Lower bit position of bitfield lro_ina_ival[9:0] */
#define rpo_lro_ina_ival_shift 10
/* Width of bitfield lro_ina_ival[9:0] */
#define rpo_lro_ina_ival_width 10
/* Default value of bitfield lro_ina_ival[9:0] */
#define rpo_lro_ina_ival_default 0xA
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* RX lro_max_ival[9:0] Bitfield Definitions
 * Preprocessor definitions for the bitfield "lro_max_ival[9:0]".
 * PORT="pif_rpo_lro_max_ival_i[9:0]"
 */

/* Register address for bitfield lro_max_ival[9:0] */
<<<<<<< HEAD
#define HW_ATL_RPO_LRO_MAX_IVAL_ADR 0x00005620
/* Bitmask for bitfield lro_max_ival[9:0] */
#define HW_ATL_RPO_LRO_MAX_IVAL_MSK 0x000003FF
/* Inverted bitmask for bitfield lro_max_ival[9:0] */
#define HW_ATL_RPO_LRO_MAX_IVAL_MSKN 0xFFFFFC00
/* Lower bit position of bitfield lro_max_ival[9:0] */
#define HW_ATL_RPO_LRO_MAX_IVAL_SHIFT 0
/* Width of bitfield lro_max_ival[9:0] */
#define HW_ATL_RPO_LRO_MAX_IVAL_WIDTH 10
/* Default value of bitfield lro_max_ival[9:0] */
#define HW_ATL_RPO_LRO_MAX_IVAL_DEFAULT 0x19
=======
#define rpo_lro_max_ival_adr 0x00005620
/* Bitmask for bitfield lro_max_ival[9:0] */
#define rpo_lro_max_ival_msk 0x000003FF
/* Inverted bitmask for bitfield lro_max_ival[9:0] */
#define rpo_lro_max_ival_mskn 0xFFFFFC00
/* Lower bit position of bitfield lro_max_ival[9:0] */
#define rpo_lro_max_ival_shift 0
/* Width of bitfield lro_max_ival[9:0] */
#define rpo_lro_max_ival_width 10
/* Default value of bitfield lro_max_ival[9:0] */
#define rpo_lro_max_ival_default 0x19
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* TX dca{D}_cpuid[7:0] Bitfield Definitions
 * Preprocessor definitions for the bitfield "dca{D}_cpuid[7:0]".
 * Parameter: DCA {D} | stride size 0x4 | range [0, 31]
 * PORT="pif_tdm_dca0_cpuid_i[7:0]"
 */

/* Register address for bitfield dca{D}_cpuid[7:0] */
<<<<<<< HEAD
#define HW_ATL_TDM_DCA_DCPUID_ADR(dca) (0x00008400 + (dca) * 0x4)
/* Bitmask for bitfield dca{D}_cpuid[7:0] */
#define HW_ATL_TDM_DCA_DCPUID_MSK 0x000000FF
/* Inverted bitmask for bitfield dca{D}_cpuid[7:0] */
#define HW_ATL_TDM_DCA_DCPUID_MSKN 0xFFFFFF00
/* Lower bit position of bitfield dca{D}_cpuid[7:0] */
#define HW_ATL_TDM_DCA_DCPUID_SHIFT 0
/* Width of bitfield dca{D}_cpuid[7:0] */
#define HW_ATL_TDM_DCA_DCPUID_WIDTH 8
/* Default value of bitfield dca{D}_cpuid[7:0] */
#define HW_ATL_TDM_DCA_DCPUID_DEFAULT 0x0
=======
#define tdm_dca_dcpuid_adr(dca) (0x00008400 + (dca) * 0x4)
/* Bitmask for bitfield dca{D}_cpuid[7:0] */
#define tdm_dca_dcpuid_msk 0x000000FF
/* Inverted bitmask for bitfield dca{D}_cpuid[7:0] */
#define tdm_dca_dcpuid_mskn 0xFFFFFF00
/* Lower bit position of bitfield dca{D}_cpuid[7:0] */
#define tdm_dca_dcpuid_shift 0
/* Width of bitfield dca{D}_cpuid[7:0] */
#define tdm_dca_dcpuid_width 8
/* Default value of bitfield dca{D}_cpuid[7:0] */
#define tdm_dca_dcpuid_default 0x0
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* TX dca{D}_desc_en Bitfield Definitions
 * Preprocessor definitions for the bitfield "dca{D}_desc_en".
 * Parameter: DCA {D} | stride size 0x4 | range [0, 31]
 * PORT="pif_tdm_dca_desc_en_i[0]"
 */

/* Register address for bitfield dca{D}_desc_en */
<<<<<<< HEAD
#define HW_ATL_TDM_DCA_DDESC_EN_ADR(dca) (0x00008400 + (dca) * 0x4)
/* Bitmask for bitfield dca{D}_desc_en */
#define HW_ATL_TDM_DCA_DDESC_EN_MSK 0x80000000
/* Inverted bitmask for bitfield dca{D}_desc_en */
#define HW_ATL_TDM_DCA_DDESC_EN_MSKN 0x7FFFFFFF
/* Lower bit position of bitfield dca{D}_desc_en */
#define HW_ATL_TDM_DCA_DDESC_EN_SHIFT 31
/* Width of bitfield dca{D}_desc_en */
#define HW_ATL_TDM_DCA_DDESC_EN_WIDTH 1
/* Default value of bitfield dca{D}_desc_en */
#define HW_ATL_TDM_DCA_DDESC_EN_DEFAULT 0x0
=======
#define tdm_dca_ddesc_en_adr(dca) (0x00008400 + (dca) * 0x4)
/* Bitmask for bitfield dca{D}_desc_en */
#define tdm_dca_ddesc_en_msk 0x80000000
/* Inverted bitmask for bitfield dca{D}_desc_en */
#define tdm_dca_ddesc_en_mskn 0x7FFFFFFF
/* Lower bit position of bitfield dca{D}_desc_en */
#define tdm_dca_ddesc_en_shift 31
/* Width of bitfield dca{D}_desc_en */
#define tdm_dca_ddesc_en_width 1
/* Default value of bitfield dca{D}_desc_en */
#define tdm_dca_ddesc_en_default 0x0
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* TX desc{D}_en Bitfield Definitions
 * Preprocessor definitions for the bitfield "desc{D}_en".
 * Parameter: descriptor {D} | stride size 0x40 | range [0, 31]
 * PORT="pif_tdm_desc_en_i[0]"
 */

/* Register address for bitfield desc{D}_en */
<<<<<<< HEAD
#define HW_ATL_TDM_DESC_DEN_ADR(descriptor) (0x00007C08 + (descriptor) * 0x40)
/* Bitmask for bitfield desc{D}_en */
#define HW_ATL_TDM_DESC_DEN_MSK 0x80000000
/* Inverted bitmask for bitfield desc{D}_en */
#define HW_ATL_TDM_DESC_DEN_MSKN 0x7FFFFFFF
/* Lower bit position of bitfield desc{D}_en */
#define HW_ATL_TDM_DESC_DEN_SHIFT 31
/* Width of bitfield desc{D}_en */
#define HW_ATL_TDM_DESC_DEN_WIDTH 1
/* Default value of bitfield desc{D}_en */
#define HW_ATL_TDM_DESC_DEN_DEFAULT 0x0
=======
#define tdm_desc_den_adr(descriptor) (0x00007C08 + (descriptor) * 0x40)
/* Bitmask for bitfield desc{D}_en */
#define tdm_desc_den_msk 0x80000000
/* Inverted bitmask for bitfield desc{D}_en */
#define tdm_desc_den_mskn 0x7FFFFFFF
/* Lower bit position of bitfield desc{D}_en */
#define tdm_desc_den_shift 31
/* Width of bitfield desc{D}_en */
#define tdm_desc_den_width 1
/* Default value of bitfield desc{D}_en */
#define tdm_desc_den_default 0x0
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* TX desc{D}_hd[C:0] Bitfield Definitions
 * Preprocessor definitions for the bitfield "desc{D}_hd[C:0]".
 * Parameter: descriptor {D} | stride size 0x40 | range [0, 31]
 * PORT="tdm_pif_desc0_hd_o[12:0]"
 */

/* Register address for bitfield desc{D}_hd[C:0] */
<<<<<<< HEAD
#define HW_ATL_TDM_DESC_DHD_ADR(descriptor) (0x00007C0C + (descriptor) * 0x40)
/* Bitmask for bitfield desc{D}_hd[C:0] */
#define HW_ATL_TDM_DESC_DHD_MSK 0x00001FFF
/* Inverted bitmask for bitfield desc{D}_hd[C:0] */
#define HW_ATL_TDM_DESC_DHD_MSKN 0xFFFFE000
/* Lower bit position of bitfield desc{D}_hd[C:0] */
#define HW_ATL_TDM_DESC_DHD_SHIFT 0
/* Width of bitfield desc{D}_hd[C:0] */
#define HW_ATL_TDM_DESC_DHD_WIDTH 13
=======
#define tdm_desc_dhd_adr(descriptor) (0x00007C0C + (descriptor) * 0x40)
/* Bitmask for bitfield desc{D}_hd[C:0] */
#define tdm_desc_dhd_msk 0x00001FFF
/* Inverted bitmask for bitfield desc{D}_hd[C:0] */
#define tdm_desc_dhd_mskn 0xFFFFE000
/* Lower bit position of bitfield desc{D}_hd[C:0] */
#define tdm_desc_dhd_shift 0
/* Width of bitfield desc{D}_hd[C:0] */
#define tdm_desc_dhd_width 13
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* TX desc{D}_len[9:0] Bitfield Definitions
 * Preprocessor definitions for the bitfield "desc{D}_len[9:0]".
 * Parameter: descriptor {D} | stride size 0x40 | range [0, 31]
 * PORT="pif_tdm_desc0_len_i[9:0]"
 */

/* Register address for bitfield desc{D}_len[9:0] */
<<<<<<< HEAD
#define HW_ATL_TDM_DESC_DLEN_ADR(descriptor) (0x00007C08 + (descriptor) * 0x40)
/* Bitmask for bitfield desc{D}_len[9:0] */
#define HW_ATL_TDM_DESC_DLEN_MSK 0x00001FF8
/* Inverted bitmask for bitfield desc{D}_len[9:0] */
#define HW_ATL_TDM_DESC_DLEN_MSKN 0xFFFFE007
/* Lower bit position of bitfield desc{D}_len[9:0] */
#define HW_ATL_TDM_DESC_DLEN_SHIFT 3
/* Width of bitfield desc{D}_len[9:0] */
#define HW_ATL_TDM_DESC_DLEN_WIDTH 10
/* Default value of bitfield desc{D}_len[9:0] */
#define HW_ATL_TDM_DESC_DLEN_DEFAULT 0x0
=======
#define tdm_desc_dlen_adr(descriptor) (0x00007C08 + (descriptor) * 0x40)
/* Bitmask for bitfield desc{D}_len[9:0] */
#define tdm_desc_dlen_msk 0x00001FF8
/* Inverted bitmask for bitfield desc{D}_len[9:0] */
#define tdm_desc_dlen_mskn 0xFFFFE007
/* Lower bit position of bitfield desc{D}_len[9:0] */
#define tdm_desc_dlen_shift 3
/* Width of bitfield desc{D}_len[9:0] */
#define tdm_desc_dlen_width 10
/* Default value of bitfield desc{D}_len[9:0] */
#define tdm_desc_dlen_default 0x0
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* TX desc{D}_wrb_thresh[6:0] Bitfield Definitions
 * Preprocessor definitions for the bitfield "desc{D}_wrb_thresh[6:0]".
 * Parameter: descriptor {D} | stride size 0x40 | range [0, 31]
 * PORT="pif_tdm_desc0_wrb_thresh_i[6:0]"
 */

/* Register address for bitfield desc{D}_wrb_thresh[6:0] */
<<<<<<< HEAD
#define HW_ATL_TDM_DESC_DWRB_THRESH_ADR(descriptor) \
	(0x00007C18 + (descriptor) * 0x40)
/* Bitmask for bitfield desc{D}_wrb_thresh[6:0] */
#define HW_ATL_TDM_DESC_DWRB_THRESH_MSK 0x00007F00
/* Inverted bitmask for bitfield desc{D}_wrb_thresh[6:0] */
#define HW_ATL_TDM_DESC_DWRB_THRESH_MSKN 0xFFFF80FF
/* Lower bit position of bitfield desc{D}_wrb_thresh[6:0] */
#define HW_ATL_TDM_DESC_DWRB_THRESH_SHIFT 8
/* Width of bitfield desc{D}_wrb_thresh[6:0] */
#define HW_ATL_TDM_DESC_DWRB_THRESH_WIDTH 7
/* Default value of bitfield desc{D}_wrb_thresh[6:0] */
#define HW_ATL_TDM_DESC_DWRB_THRESH_DEFAULT 0x0
=======
#define tdm_desc_dwrb_thresh_adr(descriptor) \
	(0x00007C18 + (descriptor) * 0x40)
/* Bitmask for bitfield desc{D}_wrb_thresh[6:0] */
#define tdm_desc_dwrb_thresh_msk 0x00007F00
/* Inverted bitmask for bitfield desc{D}_wrb_thresh[6:0] */
#define tdm_desc_dwrb_thresh_mskn 0xFFFF80FF
/* Lower bit position of bitfield desc{D}_wrb_thresh[6:0] */
#define tdm_desc_dwrb_thresh_shift 8
/* Width of bitfield desc{D}_wrb_thresh[6:0] */
#define tdm_desc_dwrb_thresh_width 7
/* Default value of bitfield desc{D}_wrb_thresh[6:0] */
#define tdm_desc_dwrb_thresh_default 0x0
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* TX tdm_int_mod_en Bitfield Definitions
 * Preprocessor definitions for the bitfield "tdm_int_mod_en".
 * PORT="pif_tdm_int_mod_en_i"
 */

/* Register address for bitfield tdm_int_mod_en */
<<<<<<< HEAD
#define HW_ATL_TDM_INT_MOD_EN_ADR 0x00007B40
/* Bitmask for bitfield tdm_int_mod_en */
#define HW_ATL_TDM_INT_MOD_EN_MSK 0x00000010
/* Inverted bitmask for bitfield tdm_int_mod_en */
#define HW_ATL_TDM_INT_MOD_EN_MSKN 0xFFFFFFEF
/* Lower bit position of bitfield tdm_int_mod_en */
#define HW_ATL_TDM_INT_MOD_EN_SHIFT 4
/* Width of bitfield tdm_int_mod_en */
#define HW_ATL_TDM_INT_MOD_EN_WIDTH 1
/* Default value of bitfield tdm_int_mod_en */
#define HW_ATL_TDM_INT_MOD_EN_DEFAULT 0x0
=======
#define tdm_int_mod_en_adr 0x00007B40
/* Bitmask for bitfield tdm_int_mod_en */
#define tdm_int_mod_en_msk 0x00000010
/* Inverted bitmask for bitfield tdm_int_mod_en */
#define tdm_int_mod_en_mskn 0xFFFFFFEF
/* Lower bit position of bitfield tdm_int_mod_en */
#define tdm_int_mod_en_shift 4
/* Width of bitfield tdm_int_mod_en */
#define tdm_int_mod_en_width 1
/* Default value of bitfield tdm_int_mod_en */
#define tdm_int_mod_en_default 0x0
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* TX lso_tcp_flag_mid[B:0] Bitfield Definitions
 * Preprocessor definitions for the bitfield "lso_tcp_flag_mid[B:0]".
 * PORT="pif_thm_lso_tcp_flag_mid_i[11:0]"
 */
/* register address for bitfield lso_tcp_flag_mid[b:0] */
<<<<<<< HEAD
#define HW_ATL_THM_LSO_TCP_FLAG_MID_ADR 0x00007820
/* bitmask for bitfield lso_tcp_flag_mid[b:0] */
#define HW_ATL_THM_LSO_TCP_FLAG_MID_MSK 0x0fff0000
/* inverted bitmask for bitfield lso_tcp_flag_mid[b:0] */
#define HW_ATL_THM_LSO_TCP_FLAG_MID_MSKN 0xf000ffff
/* lower bit position of bitfield lso_tcp_flag_mid[b:0] */
#define HW_ATL_THM_LSO_TCP_FLAG_MID_SHIFT 16
/* width of bitfield lso_tcp_flag_mid[b:0] */
#define HW_ATL_THM_LSO_TCP_FLAG_MID_WIDTH 12
/* default value of bitfield lso_tcp_flag_mid[b:0] */
#define HW_ATL_THM_LSO_TCP_FLAG_MID_DEFAULT 0x0
=======
#define thm_lso_tcp_flag_mid_adr 0x00007820
/* bitmask for bitfield lso_tcp_flag_mid[b:0] */
#define thm_lso_tcp_flag_mid_msk 0x0fff0000
/* inverted bitmask for bitfield lso_tcp_flag_mid[b:0] */
#define thm_lso_tcp_flag_mid_mskn 0xf000ffff
/* lower bit position of bitfield lso_tcp_flag_mid[b:0] */
#define thm_lso_tcp_flag_mid_shift 16
/* width of bitfield lso_tcp_flag_mid[b:0] */
#define thm_lso_tcp_flag_mid_width 12
/* default value of bitfield lso_tcp_flag_mid[b:0] */
#define thm_lso_tcp_flag_mid_default 0x0
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* tx tx_buf_en bitfield definitions
 * preprocessor definitions for the bitfield "tx_buf_en".
 * port="pif_tpb_tx_buf_en_i"
 */

/* register address for bitfield tx_buf_en */
<<<<<<< HEAD
#define HW_ATL_TPB_TX_BUF_EN_ADR 0x00007900
/* bitmask for bitfield tx_buf_en */
#define HW_ATL_TPB_TX_BUF_EN_MSK 0x00000001
/* inverted bitmask for bitfield tx_buf_en */
#define HW_ATL_TPB_TX_BUF_EN_MSKN 0xfffffffe
/* lower bit position of bitfield tx_buf_en */
#define HW_ATL_TPB_TX_BUF_EN_SHIFT 0
/* width of bitfield tx_buf_en */
#define HW_ATL_TPB_TX_BUF_EN_WIDTH 1
/* default value of bitfield tx_buf_en */
#define HW_ATL_TPB_TX_BUF_EN_DEFAULT 0x0
=======
#define tpb_tx_buf_en_adr 0x00007900
/* bitmask for bitfield tx_buf_en */
#define tpb_tx_buf_en_msk 0x00000001
/* inverted bitmask for bitfield tx_buf_en */
#define tpb_tx_buf_en_mskn 0xfffffffe
/* lower bit position of bitfield tx_buf_en */
#define tpb_tx_buf_en_shift 0
/* width of bitfield tx_buf_en */
#define tpb_tx_buf_en_width 1
/* default value of bitfield tx_buf_en */
#define tpb_tx_buf_en_default 0x0
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* tx tx{b}_hi_thresh[c:0] bitfield definitions
 * preprocessor definitions for the bitfield "tx{b}_hi_thresh[c:0]".
 * parameter: buffer {b} | stride size 0x10 | range [0, 7]
 * port="pif_tpb_tx0_hi_thresh_i[12:0]"
 */

/* register address for bitfield tx{b}_hi_thresh[c:0] */
<<<<<<< HEAD
#define HW_ATL_TPB_TXBHI_THRESH_ADR(buffer) (0x00007914 + (buffer) * 0x10)
/* bitmask for bitfield tx{b}_hi_thresh[c:0] */
#define HW_ATL_TPB_TXBHI_THRESH_MSK 0x1fff0000
/* inverted bitmask for bitfield tx{b}_hi_thresh[c:0] */
#define HW_ATL_TPB_TXBHI_THRESH_MSKN 0xe000ffff
/* lower bit position of bitfield tx{b}_hi_thresh[c:0] */
#define HW_ATL_TPB_TXBHI_THRESH_SHIFT 16
/* width of bitfield tx{b}_hi_thresh[c:0] */
#define HW_ATL_TPB_TXBHI_THRESH_WIDTH 13
/* default value of bitfield tx{b}_hi_thresh[c:0] */
#define HW_ATL_TPB_TXBHI_THRESH_DEFAULT 0x0
=======
#define tpb_txbhi_thresh_adr(buffer) (0x00007914 + (buffer) * 0x10)
/* bitmask for bitfield tx{b}_hi_thresh[c:0] */
#define tpb_txbhi_thresh_msk 0x1fff0000
/* inverted bitmask for bitfield tx{b}_hi_thresh[c:0] */
#define tpb_txbhi_thresh_mskn 0xe000ffff
/* lower bit position of bitfield tx{b}_hi_thresh[c:0] */
#define tpb_txbhi_thresh_shift 16
/* width of bitfield tx{b}_hi_thresh[c:0] */
#define tpb_txbhi_thresh_width 13
/* default value of bitfield tx{b}_hi_thresh[c:0] */
#define tpb_txbhi_thresh_default 0x0
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* tx tx{b}_lo_thresh[c:0] bitfield definitions
 * preprocessor definitions for the bitfield "tx{b}_lo_thresh[c:0]".
 * parameter: buffer {b} | stride size 0x10 | range [0, 7]
 * port="pif_tpb_tx0_lo_thresh_i[12:0]"
 */

/* register address for bitfield tx{b}_lo_thresh[c:0] */
<<<<<<< HEAD
#define HW_ATL_TPB_TXBLO_THRESH_ADR(buffer) (0x00007914 + (buffer) * 0x10)
/* bitmask for bitfield tx{b}_lo_thresh[c:0] */
#define HW_ATL_TPB_TXBLO_THRESH_MSK 0x00001fff
/* inverted bitmask for bitfield tx{b}_lo_thresh[c:0] */
#define HW_ATL_TPB_TXBLO_THRESH_MSKN 0xffffe000
/* lower bit position of bitfield tx{b}_lo_thresh[c:0] */
#define HW_ATL_TPB_TXBLO_THRESH_SHIFT 0
/* width of bitfield tx{b}_lo_thresh[c:0] */
#define HW_ATL_TPB_TXBLO_THRESH_WIDTH 13
/* default value of bitfield tx{b}_lo_thresh[c:0] */
#define HW_ATL_TPB_TXBLO_THRESH_DEFAULT 0x0
=======
#define tpb_txblo_thresh_adr(buffer) (0x00007914 + (buffer) * 0x10)
/* bitmask for bitfield tx{b}_lo_thresh[c:0] */
#define tpb_txblo_thresh_msk 0x00001fff
/* inverted bitmask for bitfield tx{b}_lo_thresh[c:0] */
#define tpb_txblo_thresh_mskn 0xffffe000
/* lower bit position of bitfield tx{b}_lo_thresh[c:0] */
#define tpb_txblo_thresh_shift 0
/* width of bitfield tx{b}_lo_thresh[c:0] */
#define tpb_txblo_thresh_width 13
/* default value of bitfield tx{b}_lo_thresh[c:0] */
#define tpb_txblo_thresh_default 0x0
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* tx dma_sys_loopback bitfield definitions
 * preprocessor definitions for the bitfield "dma_sys_loopback".
 * port="pif_tpb_dma_sys_lbk_i"
 */

/* register address for bitfield dma_sys_loopback */
<<<<<<< HEAD
#define HW_ATL_TPB_DMA_SYS_LBK_ADR 0x00007000
/* bitmask for bitfield dma_sys_loopback */
#define HW_ATL_TPB_DMA_SYS_LBK_MSK 0x00000040
/* inverted bitmask for bitfield dma_sys_loopback */
#define HW_ATL_TPB_DMA_SYS_LBK_MSKN 0xffffffbf
/* lower bit position of bitfield dma_sys_loopback */
#define HW_ATL_TPB_DMA_SYS_LBK_SHIFT 6
/* width of bitfield dma_sys_loopback */
#define HW_ATL_TPB_DMA_SYS_LBK_WIDTH 1
/* default value of bitfield dma_sys_loopback */
#define HW_ATL_TPB_DMA_SYS_LBK_DEFAULT 0x0
=======
#define tpb_dma_sys_lbk_adr 0x00007000
/* bitmask for bitfield dma_sys_loopback */
#define tpb_dma_sys_lbk_msk 0x00000040
/* inverted bitmask for bitfield dma_sys_loopback */
#define tpb_dma_sys_lbk_mskn 0xffffffbf
/* lower bit position of bitfield dma_sys_loopback */
#define tpb_dma_sys_lbk_shift 6
/* width of bitfield dma_sys_loopback */
#define tpb_dma_sys_lbk_width 1
/* default value of bitfield dma_sys_loopback */
#define tpb_dma_sys_lbk_default 0x0
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* tx tx{b}_buf_size[7:0] bitfield definitions
 * preprocessor definitions for the bitfield "tx{b}_buf_size[7:0]".
 * parameter: buffer {b} | stride size 0x10 | range [0, 7]
 * port="pif_tpb_tx0_buf_size_i[7:0]"
 */

/* register address for bitfield tx{b}_buf_size[7:0] */
<<<<<<< HEAD
#define HW_ATL_TPB_TXBBUF_SIZE_ADR(buffer) (0x00007910 + (buffer) * 0x10)
/* bitmask for bitfield tx{b}_buf_size[7:0] */
#define HW_ATL_TPB_TXBBUF_SIZE_MSK 0x000000ff
/* inverted bitmask for bitfield tx{b}_buf_size[7:0] */
#define HW_ATL_TPB_TXBBUF_SIZE_MSKN 0xffffff00
/* lower bit position of bitfield tx{b}_buf_size[7:0] */
#define HW_ATL_TPB_TXBBUF_SIZE_SHIFT 0
/* width of bitfield tx{b}_buf_size[7:0] */
#define HW_ATL_TPB_TXBBUF_SIZE_WIDTH 8
/* default value of bitfield tx{b}_buf_size[7:0] */
#define HW_ATL_TPB_TXBBUF_SIZE_DEFAULT 0x0
=======
#define tpb_txbbuf_size_adr(buffer) (0x00007910 + (buffer) * 0x10)
/* bitmask for bitfield tx{b}_buf_size[7:0] */
#define tpb_txbbuf_size_msk 0x000000ff
/* inverted bitmask for bitfield tx{b}_buf_size[7:0] */
#define tpb_txbbuf_size_mskn 0xffffff00
/* lower bit position of bitfield tx{b}_buf_size[7:0] */
#define tpb_txbbuf_size_shift 0
/* width of bitfield tx{b}_buf_size[7:0] */
#define tpb_txbbuf_size_width 8
/* default value of bitfield tx{b}_buf_size[7:0] */
#define tpb_txbbuf_size_default 0x0
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* tx tx_scp_ins_en bitfield definitions
 * preprocessor definitions for the bitfield "tx_scp_ins_en".
 * port="pif_tpb_scp_ins_en_i"
 */

/* register address for bitfield tx_scp_ins_en */
<<<<<<< HEAD
#define HW_ATL_TPB_TX_SCP_INS_EN_ADR 0x00007900
/* bitmask for bitfield tx_scp_ins_en */
#define HW_ATL_TPB_TX_SCP_INS_EN_MSK 0x00000004
/* inverted bitmask for bitfield tx_scp_ins_en */
#define HW_ATL_TPB_TX_SCP_INS_EN_MSKN 0xfffffffb
/* lower bit position of bitfield tx_scp_ins_en */
#define HW_ATL_TPB_TX_SCP_INS_EN_SHIFT 2
/* width of bitfield tx_scp_ins_en */
#define HW_ATL_TPB_TX_SCP_INS_EN_WIDTH 1
/* default value of bitfield tx_scp_ins_en */
#define HW_ATL_TPB_TX_SCP_INS_EN_DEFAULT 0x0
=======
#define tpb_tx_scp_ins_en_adr 0x00007900
/* bitmask for bitfield tx_scp_ins_en */
#define tpb_tx_scp_ins_en_msk 0x00000004
/* inverted bitmask for bitfield tx_scp_ins_en */
#define tpb_tx_scp_ins_en_mskn 0xfffffffb
/* lower bit position of bitfield tx_scp_ins_en */
#define tpb_tx_scp_ins_en_shift 2
/* width of bitfield tx_scp_ins_en */
#define tpb_tx_scp_ins_en_width 1
/* default value of bitfield tx_scp_ins_en */
#define tpb_tx_scp_ins_en_default 0x0
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* tx ipv4_chk_en bitfield definitions
 * preprocessor definitions for the bitfield "ipv4_chk_en".
 * port="pif_tpo_ipv4_chk_en_i"
 */

/* register address for bitfield ipv4_chk_en */
<<<<<<< HEAD
#define HW_ATL_TPO_IPV4CHK_EN_ADR 0x00007800
/* bitmask for bitfield ipv4_chk_en */
#define HW_ATL_TPO_IPV4CHK_EN_MSK 0x00000002
/* inverted bitmask for bitfield ipv4_chk_en */
#define HW_ATL_TPO_IPV4CHK_EN_MSKN 0xfffffffd
/* lower bit position of bitfield ipv4_chk_en */
#define HW_ATL_TPO_IPV4CHK_EN_SHIFT 1
/* width of bitfield ipv4_chk_en */
#define HW_ATL_TPO_IPV4CHK_EN_WIDTH 1
/* default value of bitfield ipv4_chk_en */
#define HW_ATL_TPO_IPV4CHK_EN_DEFAULT 0x0
=======
#define tpo_ipv4chk_en_adr 0x00007800
/* bitmask for bitfield ipv4_chk_en */
#define tpo_ipv4chk_en_msk 0x00000002
/* inverted bitmask for bitfield ipv4_chk_en */
#define tpo_ipv4chk_en_mskn 0xfffffffd
/* lower bit position of bitfield ipv4_chk_en */
#define tpo_ipv4chk_en_shift 1
/* width of bitfield ipv4_chk_en */
#define tpo_ipv4chk_en_width 1
/* default value of bitfield ipv4_chk_en */
#define tpo_ipv4chk_en_default 0x0
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* tx l4_chk_en bitfield definitions
 * preprocessor definitions for the bitfield "l4_chk_en".
 * port="pif_tpo_l4_chk_en_i"
 */

/* register address for bitfield l4_chk_en */
<<<<<<< HEAD
#define HW_ATL_TPOL4CHK_EN_ADR 0x00007800
/* bitmask for bitfield l4_chk_en */
#define HW_ATL_TPOL4CHK_EN_MSK 0x00000001
/* inverted bitmask for bitfield l4_chk_en */
#define HW_ATL_TPOL4CHK_EN_MSKN 0xfffffffe
/* lower bit position of bitfield l4_chk_en */
#define HW_ATL_TPOL4CHK_EN_SHIFT 0
/* width of bitfield l4_chk_en */
#define HW_ATL_TPOL4CHK_EN_WIDTH 1
/* default value of bitfield l4_chk_en */
#define HW_ATL_TPOL4CHK_EN_DEFAULT 0x0
=======
#define tpol4chk_en_adr 0x00007800
/* bitmask for bitfield l4_chk_en */
#define tpol4chk_en_msk 0x00000001
/* inverted bitmask for bitfield l4_chk_en */
#define tpol4chk_en_mskn 0xfffffffe
/* lower bit position of bitfield l4_chk_en */
#define tpol4chk_en_shift 0
/* width of bitfield l4_chk_en */
#define tpol4chk_en_width 1
/* default value of bitfield l4_chk_en */
#define tpol4chk_en_default 0x0
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* tx pkt_sys_loopback bitfield definitions
 * preprocessor definitions for the bitfield "pkt_sys_loopback".
 * port="pif_tpo_pkt_sys_lbk_i"
 */

/* register address for bitfield pkt_sys_loopback */
<<<<<<< HEAD
#define HW_ATL_TPO_PKT_SYS_LBK_ADR 0x00007000
/* bitmask for bitfield pkt_sys_loopback */
#define HW_ATL_TPO_PKT_SYS_LBK_MSK 0x00000080
/* inverted bitmask for bitfield pkt_sys_loopback */
#define HW_ATL_TPO_PKT_SYS_LBK_MSKN 0xffffff7f
/* lower bit position of bitfield pkt_sys_loopback */
#define HW_ATL_TPO_PKT_SYS_LBK_SHIFT 7
/* width of bitfield pkt_sys_loopback */
#define HW_ATL_TPO_PKT_SYS_LBK_WIDTH 1
/* default value of bitfield pkt_sys_loopback */
#define HW_ATL_TPO_PKT_SYS_LBK_DEFAULT 0x0
=======
#define tpo_pkt_sys_lbk_adr 0x00007000
/* bitmask for bitfield pkt_sys_loopback */
#define tpo_pkt_sys_lbk_msk 0x00000080
/* inverted bitmask for bitfield pkt_sys_loopback */
#define tpo_pkt_sys_lbk_mskn 0xffffff7f
/* lower bit position of bitfield pkt_sys_loopback */
#define tpo_pkt_sys_lbk_shift 7
/* width of bitfield pkt_sys_loopback */
#define tpo_pkt_sys_lbk_width 1
/* default value of bitfield pkt_sys_loopback */
#define tpo_pkt_sys_lbk_default 0x0
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* tx data_tc_arb_mode bitfield definitions
 * preprocessor definitions for the bitfield "data_tc_arb_mode".
 * port="pif_tps_data_tc_arb_mode_i"
 */

/* register address for bitfield data_tc_arb_mode */
<<<<<<< HEAD
#define HW_ATL_TPS_DATA_TC_ARB_MODE_ADR 0x00007100
/* bitmask for bitfield data_tc_arb_mode */
#define HW_ATL_TPS_DATA_TC_ARB_MODE_MSK 0x00000001
/* inverted bitmask for bitfield data_tc_arb_mode */
#define HW_ATL_TPS_DATA_TC_ARB_MODE_MSKN 0xfffffffe
/* lower bit position of bitfield data_tc_arb_mode */
#define HW_ATL_TPS_DATA_TC_ARB_MODE_SHIFT 0
/* width of bitfield data_tc_arb_mode */
#define HW_ATL_TPS_DATA_TC_ARB_MODE_WIDTH 1
/* default value of bitfield data_tc_arb_mode */
#define HW_ATL_TPS_DATA_TC_ARB_MODE_DEFAULT 0x0
=======
#define tps_data_tc_arb_mode_adr 0x00007100
/* bitmask for bitfield data_tc_arb_mode */
#define tps_data_tc_arb_mode_msk 0x00000001
/* inverted bitmask for bitfield data_tc_arb_mode */
#define tps_data_tc_arb_mode_mskn 0xfffffffe
/* lower bit position of bitfield data_tc_arb_mode */
#define tps_data_tc_arb_mode_shift 0
/* width of bitfield data_tc_arb_mode */
#define tps_data_tc_arb_mode_width 1
/* default value of bitfield data_tc_arb_mode */
#define tps_data_tc_arb_mode_default 0x0
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* tx desc_rate_ta_rst bitfield definitions
 * preprocessor definitions for the bitfield "desc_rate_ta_rst".
 * port="pif_tps_desc_rate_ta_rst_i"
 */

/* register address for bitfield desc_rate_ta_rst */
<<<<<<< HEAD
#define HW_ATL_TPS_DESC_RATE_TA_RST_ADR 0x00007310
/* bitmask for bitfield desc_rate_ta_rst */
#define HW_ATL_TPS_DESC_RATE_TA_RST_MSK 0x80000000
/* inverted bitmask for bitfield desc_rate_ta_rst */
#define HW_ATL_TPS_DESC_RATE_TA_RST_MSKN 0x7fffffff
/* lower bit position of bitfield desc_rate_ta_rst */
#define HW_ATL_TPS_DESC_RATE_TA_RST_SHIFT 31
/* width of bitfield desc_rate_ta_rst */
#define HW_ATL_TPS_DESC_RATE_TA_RST_WIDTH 1
/* default value of bitfield desc_rate_ta_rst */
#define HW_ATL_TPS_DESC_RATE_TA_RST_DEFAULT 0x0
=======
#define tps_desc_rate_ta_rst_adr 0x00007310
/* bitmask for bitfield desc_rate_ta_rst */
#define tps_desc_rate_ta_rst_msk 0x80000000
/* inverted bitmask for bitfield desc_rate_ta_rst */
#define tps_desc_rate_ta_rst_mskn 0x7fffffff
/* lower bit position of bitfield desc_rate_ta_rst */
#define tps_desc_rate_ta_rst_shift 31
/* width of bitfield desc_rate_ta_rst */
#define tps_desc_rate_ta_rst_width 1
/* default value of bitfield desc_rate_ta_rst */
#define tps_desc_rate_ta_rst_default 0x0
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* tx desc_rate_limit[a:0] bitfield definitions
 * preprocessor definitions for the bitfield "desc_rate_limit[a:0]".
 * port="pif_tps_desc_rate_lim_i[10:0]"
 */

/* register address for bitfield desc_rate_limit[a:0] */
<<<<<<< HEAD
#define HW_ATL_TPS_DESC_RATE_LIM_ADR 0x00007310
/* bitmask for bitfield desc_rate_limit[a:0] */
#define HW_ATL_TPS_DESC_RATE_LIM_MSK 0x000007ff
/* inverted bitmask for bitfield desc_rate_limit[a:0] */
#define HW_ATL_TPS_DESC_RATE_LIM_MSKN 0xfffff800
/* lower bit position of bitfield desc_rate_limit[a:0] */
#define HW_ATL_TPS_DESC_RATE_LIM_SHIFT 0
/* width of bitfield desc_rate_limit[a:0] */
#define HW_ATL_TPS_DESC_RATE_LIM_WIDTH 11
/* default value of bitfield desc_rate_limit[a:0] */
#define HW_ATL_TPS_DESC_RATE_LIM_DEFAULT 0x0
=======
#define tps_desc_rate_lim_adr 0x00007310
/* bitmask for bitfield desc_rate_limit[a:0] */
#define tps_desc_rate_lim_msk 0x000007ff
/* inverted bitmask for bitfield desc_rate_limit[a:0] */
#define tps_desc_rate_lim_mskn 0xfffff800
/* lower bit position of bitfield desc_rate_limit[a:0] */
#define tps_desc_rate_lim_shift 0
/* width of bitfield desc_rate_limit[a:0] */
#define tps_desc_rate_lim_width 11
/* default value of bitfield desc_rate_limit[a:0] */
#define tps_desc_rate_lim_default 0x0
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* tx desc_tc_arb_mode[1:0] bitfield definitions
 * preprocessor definitions for the bitfield "desc_tc_arb_mode[1:0]".
 * port="pif_tps_desc_tc_arb_mode_i[1:0]"
 */

/* register address for bitfield desc_tc_arb_mode[1:0] */
<<<<<<< HEAD
#define HW_ATL_TPS_DESC_TC_ARB_MODE_ADR 0x00007200
/* bitmask for bitfield desc_tc_arb_mode[1:0] */
#define HW_ATL_TPS_DESC_TC_ARB_MODE_MSK 0x00000003
/* inverted bitmask for bitfield desc_tc_arb_mode[1:0] */
#define HW_ATL_TPS_DESC_TC_ARB_MODE_MSKN 0xfffffffc
/* lower bit position of bitfield desc_tc_arb_mode[1:0] */
#define HW_ATL_TPS_DESC_TC_ARB_MODE_SHIFT 0
/* width of bitfield desc_tc_arb_mode[1:0] */
#define HW_ATL_TPS_DESC_TC_ARB_MODE_WIDTH 2
/* default value of bitfield desc_tc_arb_mode[1:0] */
#define HW_ATL_TPS_DESC_TC_ARB_MODE_DEFAULT 0x0
=======
#define tps_desc_tc_arb_mode_adr 0x00007200
/* bitmask for bitfield desc_tc_arb_mode[1:0] */
#define tps_desc_tc_arb_mode_msk 0x00000003
/* inverted bitmask for bitfield desc_tc_arb_mode[1:0] */
#define tps_desc_tc_arb_mode_mskn 0xfffffffc
/* lower bit position of bitfield desc_tc_arb_mode[1:0] */
#define tps_desc_tc_arb_mode_shift 0
/* width of bitfield desc_tc_arb_mode[1:0] */
#define tps_desc_tc_arb_mode_width 2
/* default value of bitfield desc_tc_arb_mode[1:0] */
#define tps_desc_tc_arb_mode_default 0x0
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* tx desc_tc{t}_credit_max[b:0] bitfield definitions
 * preprocessor definitions for the bitfield "desc_tc{t}_credit_max[b:0]".
 * parameter: tc {t} | stride size 0x4 | range [0, 7]
 * port="pif_tps_desc_tc0_credit_max_i[11:0]"
 */

/* register address for bitfield desc_tc{t}_credit_max[b:0] */
<<<<<<< HEAD
#define HW_ATL_TPS_DESC_TCTCREDIT_MAX_ADR(tc) (0x00007210 + (tc) * 0x4)
/* bitmask for bitfield desc_tc{t}_credit_max[b:0] */
#define HW_ATL_TPS_DESC_TCTCREDIT_MAX_MSK 0x0fff0000
/* inverted bitmask for bitfield desc_tc{t}_credit_max[b:0] */
#define HW_ATL_TPS_DESC_TCTCREDIT_MAX_MSKN 0xf000ffff
/* lower bit position of bitfield desc_tc{t}_credit_max[b:0] */
#define HW_ATL_TPS_DESC_TCTCREDIT_MAX_SHIFT 16
/* width of bitfield desc_tc{t}_credit_max[b:0] */
#define HW_ATL_TPS_DESC_TCTCREDIT_MAX_WIDTH 12
/* default value of bitfield desc_tc{t}_credit_max[b:0] */
#define HW_ATL_TPS_DESC_TCTCREDIT_MAX_DEFAULT 0x0
=======
#define tps_desc_tctcredit_max_adr(tc) (0x00007210 + (tc) * 0x4)
/* bitmask for bitfield desc_tc{t}_credit_max[b:0] */
#define tps_desc_tctcredit_max_msk 0x0fff0000
/* inverted bitmask for bitfield desc_tc{t}_credit_max[b:0] */
#define tps_desc_tctcredit_max_mskn 0xf000ffff
/* lower bit position of bitfield desc_tc{t}_credit_max[b:0] */
#define tps_desc_tctcredit_max_shift 16
/* width of bitfield desc_tc{t}_credit_max[b:0] */
#define tps_desc_tctcredit_max_width 12
/* default value of bitfield desc_tc{t}_credit_max[b:0] */
#define tps_desc_tctcredit_max_default 0x0
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* tx desc_tc{t}_weight[8:0] bitfield definitions
 * preprocessor definitions for the bitfield "desc_tc{t}_weight[8:0]".
 * parameter: tc {t} | stride size 0x4 | range [0, 7]
 * port="pif_tps_desc_tc0_weight_i[8:0]"
 */

/* register address for bitfield desc_tc{t}_weight[8:0] */
<<<<<<< HEAD
#define HW_ATL_TPS_DESC_TCTWEIGHT_ADR(tc) (0x00007210 + (tc) * 0x4)
/* bitmask for bitfield desc_tc{t}_weight[8:0] */
#define HW_ATL_TPS_DESC_TCTWEIGHT_MSK 0x000001ff
/* inverted bitmask for bitfield desc_tc{t}_weight[8:0] */
#define HW_ATL_TPS_DESC_TCTWEIGHT_MSKN 0xfffffe00
/* lower bit position of bitfield desc_tc{t}_weight[8:0] */
#define HW_ATL_TPS_DESC_TCTWEIGHT_SHIFT 0
/* width of bitfield desc_tc{t}_weight[8:0] */
#define HW_ATL_TPS_DESC_TCTWEIGHT_WIDTH 9
/* default value of bitfield desc_tc{t}_weight[8:0] */
#define HW_ATL_TPS_DESC_TCTWEIGHT_DEFAULT 0x0
=======
#define tps_desc_tctweight_adr(tc) (0x00007210 + (tc) * 0x4)
/* bitmask for bitfield desc_tc{t}_weight[8:0] */
#define tps_desc_tctweight_msk 0x000001ff
/* inverted bitmask for bitfield desc_tc{t}_weight[8:0] */
#define tps_desc_tctweight_mskn 0xfffffe00
/* lower bit position of bitfield desc_tc{t}_weight[8:0] */
#define tps_desc_tctweight_shift 0
/* width of bitfield desc_tc{t}_weight[8:0] */
#define tps_desc_tctweight_width 9
/* default value of bitfield desc_tc{t}_weight[8:0] */
#define tps_desc_tctweight_default 0x0
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* tx desc_vm_arb_mode bitfield definitions
 * preprocessor definitions for the bitfield "desc_vm_arb_mode".
 * port="pif_tps_desc_vm_arb_mode_i"
 */

/* register address for bitfield desc_vm_arb_mode */
<<<<<<< HEAD
#define HW_ATL_TPS_DESC_VM_ARB_MODE_ADR 0x00007300
/* bitmask for bitfield desc_vm_arb_mode */
#define HW_ATL_TPS_DESC_VM_ARB_MODE_MSK 0x00000001
/* inverted bitmask for bitfield desc_vm_arb_mode */
#define HW_ATL_TPS_DESC_VM_ARB_MODE_MSKN 0xfffffffe
/* lower bit position of bitfield desc_vm_arb_mode */
#define HW_ATL_TPS_DESC_VM_ARB_MODE_SHIFT 0
/* width of bitfield desc_vm_arb_mode */
#define HW_ATL_TPS_DESC_VM_ARB_MODE_WIDTH 1
/* default value of bitfield desc_vm_arb_mode */
#define HW_ATL_TPS_DESC_VM_ARB_MODE_DEFAULT 0x0
=======
#define tps_desc_vm_arb_mode_adr 0x00007300
/* bitmask for bitfield desc_vm_arb_mode */
#define tps_desc_vm_arb_mode_msk 0x00000001
/* inverted bitmask for bitfield desc_vm_arb_mode */
#define tps_desc_vm_arb_mode_mskn 0xfffffffe
/* lower bit position of bitfield desc_vm_arb_mode */
#define tps_desc_vm_arb_mode_shift 0
/* width of bitfield desc_vm_arb_mode */
#define tps_desc_vm_arb_mode_width 1
/* default value of bitfield desc_vm_arb_mode */
#define tps_desc_vm_arb_mode_default 0x0
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* tx data_tc{t}_credit_max[b:0] bitfield definitions
 * preprocessor definitions for the bitfield "data_tc{t}_credit_max[b:0]".
 * parameter: tc {t} | stride size 0x4 | range [0, 7]
 * port="pif_tps_data_tc0_credit_max_i[11:0]"
 */

/* register address for bitfield data_tc{t}_credit_max[b:0] */
<<<<<<< HEAD
#define HW_ATL_TPS_DATA_TCTCREDIT_MAX_ADR(tc) (0x00007110 + (tc) * 0x4)
/* bitmask for bitfield data_tc{t}_credit_max[b:0] */
#define HW_ATL_TPS_DATA_TCTCREDIT_MAX_MSK 0x0fff0000
/* inverted bitmask for bitfield data_tc{t}_credit_max[b:0] */
#define HW_ATL_TPS_DATA_TCTCREDIT_MAX_MSKN 0xf000ffff
/* lower bit position of bitfield data_tc{t}_credit_max[b:0] */
#define HW_ATL_TPS_DATA_TCTCREDIT_MAX_SHIFT 16
/* width of bitfield data_tc{t}_credit_max[b:0] */
#define HW_ATL_TPS_DATA_TCTCREDIT_MAX_WIDTH 12
/* default value of bitfield data_tc{t}_credit_max[b:0] */
#define HW_ATL_TPS_DATA_TCTCREDIT_MAX_DEFAULT 0x0
=======
#define tps_data_tctcredit_max_adr(tc) (0x00007110 + (tc) * 0x4)
/* bitmask for bitfield data_tc{t}_credit_max[b:0] */
#define tps_data_tctcredit_max_msk 0x0fff0000
/* inverted bitmask for bitfield data_tc{t}_credit_max[b:0] */
#define tps_data_tctcredit_max_mskn 0xf000ffff
/* lower bit position of bitfield data_tc{t}_credit_max[b:0] */
#define tps_data_tctcredit_max_shift 16
/* width of bitfield data_tc{t}_credit_max[b:0] */
#define tps_data_tctcredit_max_width 12
/* default value of bitfield data_tc{t}_credit_max[b:0] */
#define tps_data_tctcredit_max_default 0x0
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* tx data_tc{t}_weight[8:0] bitfield definitions
 * preprocessor definitions for the bitfield "data_tc{t}_weight[8:0]".
 * parameter: tc {t} | stride size 0x4 | range [0, 7]
 * port="pif_tps_data_tc0_weight_i[8:0]"
 */

/* register address for bitfield data_tc{t}_weight[8:0] */
<<<<<<< HEAD
#define HW_ATL_TPS_DATA_TCTWEIGHT_ADR(tc) (0x00007110 + (tc) * 0x4)
/* bitmask for bitfield data_tc{t}_weight[8:0] */
#define HW_ATL_TPS_DATA_TCTWEIGHT_MSK 0x000001ff
/* inverted bitmask for bitfield data_tc{t}_weight[8:0] */
#define HW_ATL_TPS_DATA_TCTWEIGHT_MSKN 0xfffffe00
/* lower bit position of bitfield data_tc{t}_weight[8:0] */
#define HW_ATL_TPS_DATA_TCTWEIGHT_SHIFT 0
/* width of bitfield data_tc{t}_weight[8:0] */
#define HW_ATL_TPS_DATA_TCTWEIGHT_WIDTH 9
/* default value of bitfield data_tc{t}_weight[8:0] */
#define HW_ATL_TPS_DATA_TCTWEIGHT_DEFAULT 0x0
=======
#define tps_data_tctweight_adr(tc) (0x00007110 + (tc) * 0x4)
/* bitmask for bitfield data_tc{t}_weight[8:0] */
#define tps_data_tctweight_msk 0x000001ff
/* inverted bitmask for bitfield data_tc{t}_weight[8:0] */
#define tps_data_tctweight_mskn 0xfffffe00
/* lower bit position of bitfield data_tc{t}_weight[8:0] */
#define tps_data_tctweight_shift 0
/* width of bitfield data_tc{t}_weight[8:0] */
#define tps_data_tctweight_width 9
/* default value of bitfield data_tc{t}_weight[8:0] */
#define tps_data_tctweight_default 0x0
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* tx reg_res_dsbl bitfield definitions
 * preprocessor definitions for the bitfield "reg_res_dsbl".
 * port="pif_tx_reg_res_dsbl_i"
 */

/* register address for bitfield reg_res_dsbl */
<<<<<<< HEAD
#define HW_ATL_TX_REG_RES_DSBL_ADR 0x00007000
/* bitmask for bitfield reg_res_dsbl */
#define HW_ATL_TX_REG_RES_DSBL_MSK 0x20000000
/* inverted bitmask for bitfield reg_res_dsbl */
#define HW_ATL_TX_REG_RES_DSBL_MSKN 0xdfffffff
/* lower bit position of bitfield reg_res_dsbl */
#define HW_ATL_TX_REG_RES_DSBL_SHIFT 29
/* width of bitfield reg_res_dsbl */
#define HW_ATL_TX_REG_RES_DSBL_WIDTH 1
/* default value of bitfield reg_res_dsbl */
#define HW_ATL_TX_REG_RES_DSBL_DEFAULT 0x1
=======
#define tx_reg_res_dsbl_adr 0x00007000
/* bitmask for bitfield reg_res_dsbl */
#define tx_reg_res_dsbl_msk 0x20000000
/* inverted bitmask for bitfield reg_res_dsbl */
#define tx_reg_res_dsbl_mskn 0xdfffffff
/* lower bit position of bitfield reg_res_dsbl */
#define tx_reg_res_dsbl_shift 29
/* width of bitfield reg_res_dsbl */
#define tx_reg_res_dsbl_width 1
/* default value of bitfield reg_res_dsbl */
#define tx_reg_res_dsbl_default 0x1
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* mac_phy register access busy bitfield definitions
 * preprocessor definitions for the bitfield "register access busy".
 * port="msm_pif_reg_busy_o"
 */

/* register address for bitfield register access busy */
<<<<<<< HEAD
#define HW_ATL_MSM_REG_ACCESS_BUSY_ADR 0x00004400
/* bitmask for bitfield register access busy */
#define HW_ATL_MSM_REG_ACCESS_BUSY_MSK 0x00001000
/* inverted bitmask for bitfield register access busy */
#define HW_ATL_MSM_REG_ACCESS_BUSY_MSKN 0xffffefff
/* lower bit position of bitfield register access busy */
#define HW_ATL_MSM_REG_ACCESS_BUSY_SHIFT 12
/* width of bitfield register access busy */
#define HW_ATL_MSM_REG_ACCESS_BUSY_WIDTH 1
=======
#define msm_reg_access_busy_adr 0x00004400
/* bitmask for bitfield register access busy */
#define msm_reg_access_busy_msk 0x00001000
/* inverted bitmask for bitfield register access busy */
#define msm_reg_access_busy_mskn 0xffffefff
/* lower bit position of bitfield register access busy */
#define msm_reg_access_busy_shift 12
/* width of bitfield register access busy */
#define msm_reg_access_busy_width 1
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* mac_phy msm register address[7:0] bitfield definitions
 * preprocessor definitions for the bitfield "msm register address[7:0]".
 * port="pif_msm_reg_addr_i[7:0]"
 */

/* register address for bitfield msm register address[7:0] */
<<<<<<< HEAD
#define HW_ATL_MSM_REG_ADDR_ADR 0x00004400
/* bitmask for bitfield msm register address[7:0] */
#define HW_ATL_MSM_REG_ADDR_MSK 0x000000ff
/* inverted bitmask for bitfield msm register address[7:0] */
#define HW_ATL_MSM_REG_ADDR_MSKN 0xffffff00
/* lower bit position of bitfield msm register address[7:0] */
#define HW_ATL_MSM_REG_ADDR_SHIFT 0
/* width of bitfield msm register address[7:0] */
#define HW_ATL_MSM_REG_ADDR_WIDTH 8
/* default value of bitfield msm register address[7:0] */
#define HW_ATL_MSM_REG_ADDR_DEFAULT 0x0
=======
#define msm_reg_addr_adr 0x00004400
/* bitmask for bitfield msm register address[7:0] */
#define msm_reg_addr_msk 0x000000ff
/* inverted bitmask for bitfield msm register address[7:0] */
#define msm_reg_addr_mskn 0xffffff00
/* lower bit position of bitfield msm register address[7:0] */
#define msm_reg_addr_shift 0
/* width of bitfield msm register address[7:0] */
#define msm_reg_addr_width 8
/* default value of bitfield msm register address[7:0] */
#define msm_reg_addr_default 0x0
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* mac_phy register read strobe bitfield definitions
 * preprocessor definitions for the bitfield "register read strobe".
 * port="pif_msm_reg_rden_i"
 */

/* register address for bitfield register read strobe */
<<<<<<< HEAD
#define HW_ATL_MSM_REG_RD_STROBE_ADR 0x00004400
/* bitmask for bitfield register read strobe */
#define HW_ATL_MSM_REG_RD_STROBE_MSK 0x00000200
/* inverted bitmask for bitfield register read strobe */
#define HW_ATL_MSM_REG_RD_STROBE_MSKN 0xfffffdff
/* lower bit position of bitfield register read strobe */
#define HW_ATL_MSM_REG_RD_STROBE_SHIFT 9
/* width of bitfield register read strobe */
#define HW_ATL_MSM_REG_RD_STROBE_WIDTH 1
/* default value of bitfield register read strobe */
#define HW_ATL_MSM_REG_RD_STROBE_DEFAULT 0x0
=======
#define msm_reg_rd_strobe_adr 0x00004400
/* bitmask for bitfield register read strobe */
#define msm_reg_rd_strobe_msk 0x00000200
/* inverted bitmask for bitfield register read strobe */
#define msm_reg_rd_strobe_mskn 0xfffffdff
/* lower bit position of bitfield register read strobe */
#define msm_reg_rd_strobe_shift 9
/* width of bitfield register read strobe */
#define msm_reg_rd_strobe_width 1
/* default value of bitfield register read strobe */
#define msm_reg_rd_strobe_default 0x0
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* mac_phy msm register read data[31:0] bitfield definitions
 * preprocessor definitions for the bitfield "msm register read data[31:0]".
 * port="msm_pif_reg_rd_data_o[31:0]"
 */

/* register address for bitfield msm register read data[31:0] */
<<<<<<< HEAD
#define HW_ATL_MSM_REG_RD_DATA_ADR 0x00004408
/* bitmask for bitfield msm register read data[31:0] */
#define HW_ATL_MSM_REG_RD_DATA_MSK 0xffffffff
/* inverted bitmask for bitfield msm register read data[31:0] */
#define HW_ATL_MSM_REG_RD_DATA_MSKN 0x00000000
/* lower bit position of bitfield msm register read data[31:0] */
#define HW_ATL_MSM_REG_RD_DATA_SHIFT 0
/* width of bitfield msm register read data[31:0] */
#define HW_ATL_MSM_REG_RD_DATA_WIDTH 32
=======
#define msm_reg_rd_data_adr 0x00004408
/* bitmask for bitfield msm register read data[31:0] */
#define msm_reg_rd_data_msk 0xffffffff
/* inverted bitmask for bitfield msm register read data[31:0] */
#define msm_reg_rd_data_mskn 0x00000000
/* lower bit position of bitfield msm register read data[31:0] */
#define msm_reg_rd_data_shift 0
/* width of bitfield msm register read data[31:0] */
#define msm_reg_rd_data_width 32
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* mac_phy msm register write data[31:0] bitfield definitions
 * preprocessor definitions for the bitfield "msm register write data[31:0]".
 * port="pif_msm_reg_wr_data_i[31:0]"
 */

/* register address for bitfield msm register write data[31:0] */
<<<<<<< HEAD
#define HW_ATL_MSM_REG_WR_DATA_ADR 0x00004404
/* bitmask for bitfield msm register write data[31:0] */
#define HW_ATL_MSM_REG_WR_DATA_MSK 0xffffffff
/* inverted bitmask for bitfield msm register write data[31:0] */
#define HW_ATL_MSM_REG_WR_DATA_MSKN 0x00000000
/* lower bit position of bitfield msm register write data[31:0] */
#define HW_ATL_MSM_REG_WR_DATA_SHIFT 0
/* width of bitfield msm register write data[31:0] */
#define HW_ATL_MSM_REG_WR_DATA_WIDTH 32
/* default value of bitfield msm register write data[31:0] */
#define HW_ATL_MSM_REG_WR_DATA_DEFAULT 0x0
=======
#define msm_reg_wr_data_adr 0x00004404
/* bitmask for bitfield msm register write data[31:0] */
#define msm_reg_wr_data_msk 0xffffffff
/* inverted bitmask for bitfield msm register write data[31:0] */
#define msm_reg_wr_data_mskn 0x00000000
/* lower bit position of bitfield msm register write data[31:0] */
#define msm_reg_wr_data_shift 0
/* width of bitfield msm register write data[31:0] */
#define msm_reg_wr_data_width 32
/* default value of bitfield msm register write data[31:0] */
#define msm_reg_wr_data_default 0x0
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* mac_phy register write strobe bitfield definitions
 * preprocessor definitions for the bitfield "register write strobe".
 * port="pif_msm_reg_wren_i"
 */

/* register address for bitfield register write strobe */
<<<<<<< HEAD
#define HW_ATL_MSM_REG_WR_STROBE_ADR 0x00004400
/* bitmask for bitfield register write strobe */
#define HW_ATL_MSM_REG_WR_STROBE_MSK 0x00000100
/* inverted bitmask for bitfield register write strobe */
#define HW_ATL_MSM_REG_WR_STROBE_MSKN 0xfffffeff
/* lower bit position of bitfield register write strobe */
#define HW_ATL_MSM_REG_WR_STROBE_SHIFT 8
/* width of bitfield register write strobe */
#define HW_ATL_MSM_REG_WR_STROBE_WIDTH 1
/* default value of bitfield register write strobe */
#define HW_ATL_MSM_REG_WR_STROBE_DEFAULT 0x0
=======
#define msm_reg_wr_strobe_adr 0x00004400
/* bitmask for bitfield register write strobe */
#define msm_reg_wr_strobe_msk 0x00000100
/* inverted bitmask for bitfield register write strobe */
#define msm_reg_wr_strobe_mskn 0xfffffeff
/* lower bit position of bitfield register write strobe */
#define msm_reg_wr_strobe_shift 8
/* width of bitfield register write strobe */
#define msm_reg_wr_strobe_width 1
/* default value of bitfield register write strobe */
#define msm_reg_wr_strobe_default 0x0
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* mif soft reset bitfield definitions
 * preprocessor definitions for the bitfield "soft reset".
 * port="pif_glb_res_i"
 */

/* register address for bitfield soft reset */
<<<<<<< HEAD
#define HW_ATL_GLB_SOFT_RES_ADR 0x00000000
/* bitmask for bitfield soft reset */
#define HW_ATL_GLB_SOFT_RES_MSK 0x00008000
/* inverted bitmask for bitfield soft reset */
#define HW_ATL_GLB_SOFT_RES_MSKN 0xffff7fff
/* lower bit position of bitfield soft reset */
#define HW_ATL_GLB_SOFT_RES_SHIFT 15
/* width of bitfield soft reset */
#define HW_ATL_GLB_SOFT_RES_WIDTH 1
/* default value of bitfield soft reset */
#define HW_ATL_GLB_SOFT_RES_DEFAULT 0x0
=======
#define glb_soft_res_adr 0x00000000
/* bitmask for bitfield soft reset */
#define glb_soft_res_msk 0x00008000
/* inverted bitmask for bitfield soft reset */
#define glb_soft_res_mskn 0xffff7fff
/* lower bit position of bitfield soft reset */
#define glb_soft_res_shift 15
/* width of bitfield soft reset */
#define glb_soft_res_width 1
/* default value of bitfield soft reset */
#define glb_soft_res_default 0x0
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* mif register reset disable bitfield definitions
 * preprocessor definitions for the bitfield "register reset disable".
 * port="pif_glb_reg_res_dsbl_i"
 */

/* register address for bitfield register reset disable */
<<<<<<< HEAD
#define HW_ATL_GLB_REG_RES_DIS_ADR 0x00000000
/* bitmask for bitfield register reset disable */
#define HW_ATL_GLB_REG_RES_DIS_MSK 0x00004000
/* inverted bitmask for bitfield register reset disable */
#define HW_ATL_GLB_REG_RES_DIS_MSKN 0xffffbfff
/* lower bit position of bitfield register reset disable */
#define HW_ATL_GLB_REG_RES_DIS_SHIFT 14
/* width of bitfield register reset disable */
#define HW_ATL_GLB_REG_RES_DIS_WIDTH 1
/* default value of bitfield register reset disable */
#define HW_ATL_GLB_REG_RES_DIS_DEFAULT 0x1

/* tx dma debug control definitions */
#define HW_ATL_TX_DMA_DEBUG_CTL_ADR 0x00008920u

/* tx dma descriptor base address msw definitions */
#define HW_ATL_TX_DMA_DESC_BASE_ADDRMSW_ADR(descriptor) \
			(0x00007c04u + (descriptor) * 0x40)

/* tx dma total request limit */
#define HW_ATL_TX_DMA_TOTAL_REQ_LIMIT_ADR 0x00007b20u
=======
#define glb_reg_res_dis_adr 0x00000000
/* bitmask for bitfield register reset disable */
#define glb_reg_res_dis_msk 0x00004000
/* inverted bitmask for bitfield register reset disable */
#define glb_reg_res_dis_mskn 0xffffbfff
/* lower bit position of bitfield register reset disable */
#define glb_reg_res_dis_shift 14
/* width of bitfield register reset disable */
#define glb_reg_res_dis_width 1
/* default value of bitfield register reset disable */
#define glb_reg_res_dis_default 0x1

/* tx dma debug control definitions */
#define tx_dma_debug_ctl_adr 0x00008920u

/* tx dma descriptor base address msw definitions */
#define tx_dma_desc_base_addrmsw_adr(descriptor) \
			(0x00007c04u + (descriptor) * 0x40)

/* tx dma total request limit */
#define tx_dma_total_req_limit_adr 0x00007b20u
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* tx interrupt moderation control register definitions
 * Preprocessor definitions for TX Interrupt Moderation Control Register
 * Base Address: 0x00008980
 * Parameter: queue {Q} | stride size 0x4 | range [0, 31]
 */

<<<<<<< HEAD
#define HW_ATL_TX_INTR_MODERATION_CTL_ADR(queue) (0x00008980u + (queue) * 0x4)
=======
#define tx_intr_moderation_ctl_adr(queue) (0x00008980u + (queue) * 0x4)
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

/* pcie reg_res_dsbl bitfield definitions
 * preprocessor definitions for the bitfield "reg_res_dsbl".
 * port="pif_pci_reg_res_dsbl_i"
 */

/* register address for bitfield reg_res_dsbl */
<<<<<<< HEAD
#define HW_ATL_PCI_REG_RES_DSBL_ADR 0x00001000
/* bitmask for bitfield reg_res_dsbl */
#define HW_ATL_PCI_REG_RES_DSBL_MSK 0x20000000
/* inverted bitmask for bitfield reg_res_dsbl */
#define HW_ATL_PCI_REG_RES_DSBL_MSKN 0xdfffffff
/* lower bit position of bitfield reg_res_dsbl */
#define HW_ATL_PCI_REG_RES_DSBL_SHIFT 29
/* width of bitfield reg_res_dsbl */
#define HW_ATL_PCI_REG_RES_DSBL_WIDTH 1
/* default value of bitfield reg_res_dsbl */
#define HW_ATL_PCI_REG_RES_DSBL_DEFAULT 0x1

/* PCI core control register */
#define HW_ATL_PCI_REG_CONTROL6_ADR 0x1014u

/* global microprocessor scratch pad definitions */
#define HW_ATL_GLB_CPU_SCRATCH_SCP_ADR(scratch_scp) \
	(0x00000300u + (scratch_scp) * 0x4)
=======
#define pci_reg_res_dsbl_adr 0x00001000
/* bitmask for bitfield reg_res_dsbl */
#define pci_reg_res_dsbl_msk 0x20000000
/* inverted bitmask for bitfield reg_res_dsbl */
#define pci_reg_res_dsbl_mskn 0xdfffffff
/* lower bit position of bitfield reg_res_dsbl */
#define pci_reg_res_dsbl_shift 29
/* width of bitfield reg_res_dsbl */
#define pci_reg_res_dsbl_width 1
/* default value of bitfield reg_res_dsbl */
#define pci_reg_res_dsbl_default 0x1

/* PCI core control register */
#define pci_reg_control6_adr 0x1014u

/* global microprocessor scratch pad definitions */
#define glb_cpu_scratch_scp_adr(scratch_scp) (0x00000300u + (scratch_scp) * 0x4)
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

#endif /* HW_ATL_LLH_INTERNAL_H */
