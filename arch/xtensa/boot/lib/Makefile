# SPDX-License-Identifier: GPL-2.0
#
# Makefile for some libs needed by zImage.
#

zlib	:= inffast.c inflate.c inftrees.c

lib-y	+= $(zlib:.c=.o) zmem.o

ccflags-y	:= -Ilib/zlib_inflate
ifdef CONFIG_FUNCTION_TRACER
CFLAGS_REMOVE_inflate.o = -pg
CFLAGS_REMOVE_zmem.o = -pg
CFLAGS_REMOVE_inftrees.o = -pg
CFLAGS_REMOVE_inffast.o = -pg
endif

<<<<<<< HEAD
KASAN_SANITIZE := n

CFLAGS_REMOVE_inflate.o += -fstack-protector -fstack-protector-strong
CFLAGS_REMOVE_zmem.o += -fstack-protector -fstack-protector-strong
CFLAGS_REMOVE_inftrees.o += -fstack-protector -fstack-protector-strong
CFLAGS_REMOVE_inffast.o += -fstack-protector -fstack-protector-strong
=======
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

quiet_cmd_copy_zlib = COPY    $@
      cmd_copy_zlib = cat $< > $@

$(addprefix $(obj)/,$(zlib)): $(obj)/%: $(srctree)/lib/zlib_inflate/%
	$(call cmd,copy_zlib)

clean-files	:= $(zlib)
