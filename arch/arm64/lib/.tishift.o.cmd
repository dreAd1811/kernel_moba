cmd_arch/arm64/lib/tishift.o := clang -Wp,-MD,arch/arm64/lib/.tishift.o.d -nostdinc -isystem /home/dread/toolchains/proton-clang/lib/clang/13.0.0/include -I./arch/arm64/include -I./arch/arm64/include/generated  -I./include -I./arch/arm64/include/uapi -I./arch/arm64/include/generated/uapi -I./include/uapi -I./include/generated/uapi -include ./include/linux/kconfig.h -D__KERNEL__ -mlittle-endian -Qunused-arguments -D__ASSEMBLY__ --target=aarch64-linux-gnu --prefix=/home/dread/toolchains/proton-clang/bin/aarch64-linux-gnu- --gcc-toolchain=/home/dread/toolchains/proton-clang -no-integrated-as -Werror=unknown-warning-option -fno-PIE -DCONFIG_AS_LSE=1 --target=aarch64-linux-gnu --gcc-toolchain=/home/dread/toolchains/proton-clang -Wa,-gdwarf-2   -c -o arch/arm64/lib/tishift.o arch/arm64/lib/tishift.S

source_arch/arm64/lib/tishift.o := arch/arm64/lib/tishift.S

deps_arch/arm64/lib/tishift.o := \
  include/linux/kconfig.h \
    $(wildcard include/config/cpu/big/endian.h) \
    $(wildcard include/config/booger.h) \
    $(wildcard include/config/foo.h) \
  include/linux/linkage.h \
  include/linux/compiler_types.h \
    $(wildcard include/config/have/arch/compiler/h.h) \
    $(wildcard include/config/enable/must/check.h) \
    $(wildcard include/config/arch/supports/optimized/inlining.h) \
    $(wildcard include/config/optimize/inlining.h) \
  include/linux/stringify.h \
  include/linux/export.h \
    $(wildcard include/config/modules.h) \
    $(wildcard include/config/modversions.h) \
    $(wildcard include/config/module/rel/crcs.h) \
    $(wildcard include/config/have/arch/prel32/relocations.h) \
    $(wildcard include/config/trim/unused/ksyms.h) \
    $(wildcard include/config/unused/symbols.h) \
  arch/arm64/include/asm/linkage.h \

arch/arm64/lib/tishift.o: $(deps_arch/arm64/lib/tishift.o)

$(deps_arch/arm64/lib/tishift.o):
