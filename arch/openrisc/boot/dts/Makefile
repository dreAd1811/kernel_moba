# SPDX-License-Identifier: GPL-2.0
ifneq '$(CONFIG_OPENRISC_BUILTIN_DTB)' '""'
BUILTIN_DTB := $(patsubst "%",%,$(CONFIG_OPENRISC_BUILTIN_DTB)).dtb.o
else
BUILTIN_DTB :=
endif
obj-y += $(BUILTIN_DTB)

<<<<<<< HEAD
=======
clean-files := *.dtb.S

>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
#DTC_FLAGS ?= -p 1024
