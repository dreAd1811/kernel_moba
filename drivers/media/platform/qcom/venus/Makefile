# SPDX-License-Identifier: GPL-2.0
# Makefile for Qualcomm Venus driver

venus-core-objs += core.o helpers.o firmware.o \
<<<<<<< HEAD
		   hfi_venus.o hfi_msgs.o hfi_cmds.o hfi.o \
		   hfi_parser.o
=======
		   hfi_venus.o hfi_msgs.o hfi_cmds.o hfi.o
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

venus-dec-objs += vdec.o vdec_ctrls.o
venus-enc-objs += venc.o venc_ctrls.o

obj-$(CONFIG_VIDEO_QCOM_VENUS) += venus-core.o
obj-$(CONFIG_VIDEO_QCOM_VENUS) += venus-dec.o
obj-$(CONFIG_VIDEO_QCOM_VENUS) += venus-enc.o
