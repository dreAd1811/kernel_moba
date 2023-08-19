<<<<<<< HEAD
# SPDX-License-Identifier: GPL-2.0
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
#
# s390/Makefile
#
# This file is included by the global makefile so that you can add your own
# architecture-specific flags and dependencies. Remember to do have actions
# for "archclean" and "archdep" for cleaning up and making dependencies for
# this architecture
#
<<<<<<< HEAD
=======
# This file is subject to the terms and conditions of the GNU General Public
# License.  See the file "COPYING" in the main directory of this archive
# for more details.
#
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
# Copyright (C) 1994 by Linus Torvalds
#

LD_BFD		:= elf64-s390
<<<<<<< HEAD
KBUILD_LDFLAGS	:= -m elf64_s390
KBUILD_AFLAGS_MODULE += -fPIC
KBUILD_CFLAGS_MODULE += -fPIC
KBUILD_AFLAGS	+= -m64
KBUILD_CFLAGS	+= -m64
aflags_dwarf	:= -Wa,-gdwarf-2
KBUILD_AFLAGS_DECOMPRESSOR := -m64 -D__ASSEMBLY__
KBUILD_AFLAGS_DECOMPRESSOR += $(if $(CONFIG_DEBUG_INFO),$(aflags_dwarf))
KBUILD_CFLAGS_DECOMPRESSOR := -m64 -O2
KBUILD_CFLAGS_DECOMPRESSOR += -DDISABLE_BRANCH_PROFILING -D__NO_FORTIFY
KBUILD_CFLAGS_DECOMPRESSOR += -fno-delete-null-pointer-checks -msoft-float
KBUILD_CFLAGS_DECOMPRESSOR += -fno-asynchronous-unwind-tables
KBUILD_CFLAGS_DECOMPRESSOR += $(call cc-option,-ffreestanding)
KBUILD_CFLAGS_DECOMPRESSOR += $(call cc-disable-warning, address-of-packed-member)
KBUILD_CFLAGS_DECOMPRESSOR += $(if $(CONFIG_DEBUG_INFO),-g)
KBUILD_CFLAGS_DECOMPRESSOR += $(if $(CONFIG_DEBUG_INFO_DWARF4), $(call cc-option, -gdwarf-4,))
=======
LDFLAGS		:= -m elf64_s390
KBUILD_AFLAGS_MODULE += -fPIC
KBUILD_CFLAGS_MODULE += -fPIC
KBUILD_CFLAGS	+= -m64
KBUILD_AFLAGS	+= -m64
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
UTS_MACHINE	:= s390x
STACK_SIZE	:= 16384
CHECKFLAGS	+= -D__s390__ -D__s390x__

export LD_BFD

mflags-$(CONFIG_MARCH_Z900)   := -march=z900
mflags-$(CONFIG_MARCH_Z990)   := -march=z990
mflags-$(CONFIG_MARCH_Z9_109) := -march=z9-109
mflags-$(CONFIG_MARCH_Z10)    := -march=z10
mflags-$(CONFIG_MARCH_Z196)   := -march=z196
mflags-$(CONFIG_MARCH_ZEC12)  := -march=zEC12
mflags-$(CONFIG_MARCH_Z13)    := -march=z13
mflags-$(CONFIG_MARCH_Z14)    := -march=z14

export CC_FLAGS_MARCH := $(mflags-y)

aflags-y += $(mflags-y)
cflags-y += $(mflags-y)

cflags-$(CONFIG_MARCH_Z900_TUNE)	+= -mtune=z900
cflags-$(CONFIG_MARCH_Z990_TUNE)	+= -mtune=z990
cflags-$(CONFIG_MARCH_Z9_109_TUNE)	+= -mtune=z9-109
cflags-$(CONFIG_MARCH_Z10_TUNE)		+= -mtune=z10
cflags-$(CONFIG_MARCH_Z196_TUNE)	+= -mtune=z196
cflags-$(CONFIG_MARCH_ZEC12_TUNE)	+= -mtune=zEC12
cflags-$(CONFIG_MARCH_Z13_TUNE)		+= -mtune=z13
cflags-$(CONFIG_MARCH_Z14_TUNE)		+= -mtune=z14

cflags-y += -Wa,-I$(srctree)/arch/$(ARCH)/include

<<<<<<< HEAD
=======
#KBUILD_IMAGE is necessary for make rpm
KBUILD_IMAGE	:=arch/s390/boot/image

>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
#
# Prevent tail-call optimizations, to get clearer backtraces:
#
cflags-$(CONFIG_FRAME_POINTER) += -fno-optimize-sibling-calls

<<<<<<< HEAD
=======
# old style option for packed stacks
ifeq ($(call cc-option-yn,-mkernel-backchain),y)
cflags-$(CONFIG_PACK_STACK)  += -mkernel-backchain -D__PACK_STACK
aflags-$(CONFIG_PACK_STACK)  += -D__PACK_STACK
endif

# new style option for packed stacks
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
ifeq ($(call cc-option-yn,-mpacked-stack),y)
cflags-$(CONFIG_PACK_STACK)  += -mpacked-stack -D__PACK_STACK
aflags-$(CONFIG_PACK_STACK)  += -D__PACK_STACK
endif

<<<<<<< HEAD
KBUILD_AFLAGS_DECOMPRESSOR += $(aflags-y)
KBUILD_CFLAGS_DECOMPRESSOR += $(cflags-y)

=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
ifeq ($(call cc-option-yn,-mstack-size=8192 -mstack-guard=128),y)
cflags-$(CONFIG_CHECK_STACK) += -mstack-size=$(STACK_SIZE)
ifneq ($(call cc-option-yn,-mstack-size=8192),y)
cflags-$(CONFIG_CHECK_STACK) += -mstack-guard=$(CONFIG_STACK_GUARD)
endif
endif

<<<<<<< HEAD
ifdef CONFIG_WARN_DYNAMIC_STACK
  ifeq ($(call cc-option-yn,-mwarn-dynamicstack),y)
    KBUILD_CFLAGS += -mwarn-dynamicstack
    KBUILD_CFLAGS_DECOMPRESSOR += -mwarn-dynamicstack
  endif
=======
ifeq ($(call cc-option-yn,-mwarn-dynamicstack),y)
cflags-$(CONFIG_WARN_DYNAMIC_STACK) += -mwarn-dynamicstack
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
endif

ifdef CONFIG_EXPOLINE
  ifeq ($(call cc-option-yn,$(CC_FLAGS_MARCH) -mindirect-branch=thunk),y)
    CC_FLAGS_EXPOLINE := -mindirect-branch=thunk
    CC_FLAGS_EXPOLINE += -mfunction-return=thunk
    CC_FLAGS_EXPOLINE += -mindirect-branch-table
    export CC_FLAGS_EXPOLINE
    cflags-y += $(CC_FLAGS_EXPOLINE) -DCC_USING_EXPOLINE
<<<<<<< HEAD
    aflags-y += -DCC_USING_EXPOLINE
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
  endif
endif

ifdef CONFIG_FUNCTION_TRACER
<<<<<<< HEAD
  ifeq ($(call cc-option-yn,-mfentry -mnop-mcount),n)
    # make use of hotpatch feature if the compiler supports it
    cc_hotpatch	:= -mhotpatch=0,3
    ifeq ($(call cc-option-yn,$(cc_hotpatch)),y)
      CC_FLAGS_FTRACE := $(cc_hotpatch)
      KBUILD_AFLAGS	+= -DCC_USING_HOTPATCH
      KBUILD_CFLAGS	+= -DCC_USING_HOTPATCH
    endif
  endif
endif

# Test CFI features of binutils
cfi := $(call as-instr,.cfi_startproc\n.cfi_val_offset 15$(comma)-160\n.cfi_endproc,-DCONFIG_AS_CFI_VAL_OFFSET=1)

KBUILD_CFLAGS	+= -mbackchain -msoft-float $(cflags-y)
KBUILD_CFLAGS	+= -pipe -fno-strength-reduce -Wno-sign-compare
KBUILD_CFLAGS	+= -fno-asynchronous-unwind-tables $(cfi)
KBUILD_AFLAGS	+= $(aflags-y) $(cfi)
export KBUILD_AFLAGS_DECOMPRESSOR
export KBUILD_CFLAGS_DECOMPRESSOR

OBJCOPYFLAGS	:= -O binary

head-y		:= arch/s390/kernel/head64.o
=======
# make use of hotpatch feature if the compiler supports it
cc_hotpatch	:= -mhotpatch=0,3
ifeq ($(call cc-option-yn,$(cc_hotpatch)),y)
CC_FLAGS_FTRACE := $(cc_hotpatch)
KBUILD_AFLAGS	+= -DCC_USING_HOTPATCH
KBUILD_CFLAGS	+= -DCC_USING_HOTPATCH
endif
endif

KBUILD_CFLAGS	+= -mbackchain -msoft-float $(cflags-y)
KBUILD_CFLAGS	+= -pipe -fno-strength-reduce -Wno-sign-compare
KBUILD_AFLAGS	+= $(aflags-y)

OBJCOPYFLAGS	:= -O binary

head-y		:= arch/s390/kernel/head.o
head-y		+= arch/s390/kernel/head64.o
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

# See arch/s390/Kbuild for content of core part of the kernel
core-y		+= arch/s390/

libs-y		+= arch/s390/lib/
drivers-y	+= drivers/s390/

# must be linked after kernel
drivers-$(CONFIG_OPROFILE)	+= arch/s390/oprofile/

boot		:= arch/s390/boot
<<<<<<< HEAD
syscalls	:= arch/s390/kernel/syscalls
tools		:= arch/s390/tools

all: bzImage

#KBUILD_IMAGE is necessary for packaging targets like rpm-pkg, deb-pkg...
KBUILD_IMAGE	:= $(boot)/bzImage
=======
tools		:= arch/s390/tools

all: image bzImage
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

install: vmlinux
	$(Q)$(MAKE) $(build)=$(boot) $@

<<<<<<< HEAD
bzImage: vmlinux
=======
image bzImage: vmlinux
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	$(Q)$(MAKE) $(build)=$(boot) $(boot)/$@

zfcpdump:
	$(Q)$(MAKE) $(build)=$(boot) $(boot)/$@

vdso_install:
	$(Q)$(MAKE) $(build)=arch/$(ARCH)/kernel/vdso64 $@
	$(Q)$(MAKE) $(build)=arch/$(ARCH)/kernel/vdso32 $@

archclean:
	$(Q)$(MAKE) $(clean)=$(boot)
	$(Q)$(MAKE) $(clean)=$(tools)

<<<<<<< HEAD
archheaders:
	$(Q)$(MAKE) $(build)=$(syscalls) uapi

archprepare:
	$(Q)$(MAKE) $(build)=$(syscalls) kapi
	$(Q)$(MAKE) $(build)=$(tools) kapi

# Don't use tabs in echo arguments
define archhelp
  echo	'* bzImage         - Kernel image for IPL ($(boot)/bzImage)'
=======
archprepare:
	$(Q)$(MAKE) $(build)=$(tools) include/generated/facilities.h

# Don't use tabs in echo arguments
define archhelp
  echo  '* image           - Kernel image for IPL ($(boot)/image)'
  echo	'* bzImage         - Compressed kernel image for IPL ($(boot)/bzImage)'
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
  echo	'  install         - Install kernel using'
  echo	'                    (your) ~/bin/$(INSTALLKERNEL) or'
  echo	'                    (distribution) /sbin/$(INSTALLKERNEL) or'
  echo	'                    install to $$(INSTALL_PATH)'
endef
