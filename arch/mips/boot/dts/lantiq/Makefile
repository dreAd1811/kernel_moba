# SPDX-License-Identifier: GPL-2.0
dtb-$(CONFIG_DT_EASY50712)	+= easy50712.dtb

<<<<<<< HEAD
obj-$(CONFIG_BUILTIN_DTB)	+= $(addsuffix .o, $(dtb-y))
=======
obj-y				+= $(patsubst %.dtb, %.dtb.o, $(dtb-y))

# Force kbuild to make empty built-in.o if necessary
obj-				+= dummy.o

always				:= $(dtb-y)
clean-files			:= *.dtb *.dtb.S
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
