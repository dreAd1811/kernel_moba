#!/bin/bash
# SPDX-License-Identifier: GPL-2.0

set -e
set -o pipefail

# To debug, uncomment the following line
# set -x

<<<<<<< HEAD
# -mprofile-kernel is only supported on 64le, so this should not be invoked
# for other targets. Therefore we can pass in -m64 and -mlittle-endian
# explicitly, to take care of toolchains defaulting to other targets.

# Test whether the compile option -mprofile-kernel exists and generates
# profiling code (ie. a call to _mcount()).
echo "int func() { return 0; }" | \
    $* -m64 -mlittle-endian -S -x c -O2 -p -mprofile-kernel - -o - \
    2> /dev/null | grep -q "_mcount"
=======
# Test whether the compile option -mprofile-kernel exists and generates
# profiling code (ie. a call to _mcount()).
echo "int func() { return 0; }" | \
    $* -S -x c -O2 -p -mprofile-kernel - -o - 2> /dev/null | \
    grep -q "_mcount"
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

# Test whether the notrace attribute correctly suppresses calls to _mcount().

echo -e "#include <linux/compiler.h>\nnotrace int func() { return 0; }" | \
<<<<<<< HEAD
    $* -m64 -mlittle-endian -S -x c -O2 -p -mprofile-kernel - -o - \
    2> /dev/null | grep -q "_mcount" && \
    exit 1

=======
    $* -S -x c -O2 -p -mprofile-kernel - -o - 2> /dev/null | \
    grep -q "_mcount" && \
    exit 1

echo "OK"
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
exit 0
