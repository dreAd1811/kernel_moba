# SPDX-License-Identifier: GPL-2.0
#
# Makefile for s390 specific build tools
#

<<<<<<< HEAD
kapi := arch/$(ARCH)/include/generated/asm
kapi-hdrs-y := $(kapi)/facility-defs.h $(kapi)/dis-defs.h

targets += $(addprefix ../../../,$(kapi-hdrs-y))
PHONY += kapi

kapi:	$(kapi-hdrs-y)

hostprogs-y		    += gen_facilities
hostprogs-y		    += gen_opcode_table

HOSTCFLAGS_gen_facilities.o += -Wall $(LINUXINCLUDE)
HOSTCFLAGS_gen_opcode_table.o += -Wall $(LINUXINCLUDE)

# Ensure output directory exists
_dummy := $(shell [ -d '$(kapi)' ] || mkdir -p '$(kapi)')

define filechk_facility-defs.h
	$(obj)/gen_facilities
endef

define filechk_dis-defs.h
	( $(obj)/gen_opcode_table < $(srctree)/arch/$(ARCH)/tools/opcodes.txt )
endef

$(kapi)/facility-defs.h: $(obj)/gen_facilities FORCE
	$(call filechk,facility-defs.h)

$(kapi)/dis-defs.h: $(obj)/gen_opcode_table FORCE
	$(call filechk,dis-defs.h)
=======
hostprogs-y		    += gen_facilities
HOSTCFLAGS_gen_facilities.o += -Wall $(LINUXINCLUDE)

define filechk_facilities.h
	$(obj)/gen_facilities
endef

include/generated/facilities.h: $(obj)/gen_facilities FORCE
	$(call filechk,facilities.h)
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
