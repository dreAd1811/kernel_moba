<<<<<<< HEAD
#
# Copyright 2017 Advanced Micro Devices, Inc.
#
# Permission is hereby granted, free of charge, to any person obtaining a
# copy of this software and associated documentation files (the "Software"),
# to deal in the Software without restriction, including without limitation
# the rights to use, copy, modify, merge, publish, distribute, sublicense,
# and/or sell copies of the Software, and to permit persons to whom the
# Software is furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
# THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
# OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
# ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
# OTHER DEALINGS IN THE SOFTWARE.
#
=======
# SPDX-License-Identifier: GPL-2.0
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
#
# Makefile for the 'smu manager' sub-component of powerplay.
# It provides the smu management services for the driver.

<<<<<<< HEAD
SMU_MGR = smumgr.o smu8_smumgr.o tonga_smumgr.o fiji_smumgr.o \
	  polaris10_smumgr.o iceland_smumgr.o \
	  smu7_smumgr.o vega10_smumgr.o smu10_smumgr.o ci_smumgr.o \
	  vega12_smumgr.o vegam_smumgr.o smu9_smumgr.o
=======
SMU_MGR = smumgr.o cz_smumgr.o tonga_smumgr.o fiji_smumgr.o fiji_smc.o \
	  polaris10_smumgr.o iceland_smumgr.o polaris10_smc.o tonga_smc.o \
	  smu7_smumgr.o iceland_smc.o vega10_smumgr.o rv_smumgr.o
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

AMD_PP_SMUMGR = $(addprefix $(AMD_PP_PATH)/smumgr/,$(SMU_MGR))

AMD_POWERPLAY_FILES += $(AMD_PP_SMUMGR)
