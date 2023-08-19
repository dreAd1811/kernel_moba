cmd_arch/arm64/crypto/sha256-core.o := clang -Wp,-MD,arch/arm64/crypto/.sha256-core.o.d -nostdinc -isystem /home/dread/toolchains/proton-clang/lib/clang/13.0.0/include -I./arch/arm64/include -I./arch/arm64/include/generated  -I./include -I./arch/arm64/include/uapi -I./arch/arm64/include/generated/uapi -I./include/uapi -I./include/generated/uapi -include ./include/linux/kconfig.h -D__KERNEL__ -mlittle-endian -Qunused-arguments -D__ASSEMBLY__ --target=aarch64-linux-gnu --prefix=/home/dread/toolchains/proton-clang/bin/aarch64-linux-gnu- --gcc-toolchain=/home/dread/toolchains/proton-clang -no-integrated-as -Werror=unknown-warning-option -fno-PIE -DCONFIG_AS_LSE=1 --target=aarch64-linux-gnu --gcc-toolchain=/home/dread/toolchains/proton-clang -Wa,-gdwarf-2   -c -o arch/arm64/crypto/sha256-core.o arch/arm64/crypto/sha256-core.S

source_arch/arm64/crypto/sha256-core.o := arch/arm64/crypto/sha256-core.S

deps_arch/arm64/crypto/sha256-core.o := \
  include/linux/kconfig.h \
    $(wildcard include/config/cpu/big/endian.h) \
    $(wildcard include/config/booger.h) \
    $(wildcard include/config/foo.h) \

arch/arm64/crypto/sha256-core.o: $(deps_arch/arm64/crypto/sha256-core.o)

$(deps_arch/arm64/crypto/sha256-core.o):
