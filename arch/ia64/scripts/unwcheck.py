#!/usr/bin/python
# SPDX-License-Identifier: GPL-2.0
#
# Usage: unwcheck.py FILE
#
# This script checks the unwind info of each function in file FILE
# and verifies that the sum of the region-lengths matches the total
# length of the function.
#
# Based on a shell/awk script originally written by Harish Patil,
# which was converted to Perl by Matthew Chapman, which was converted
# to Python by David Mosberger.
#
import os
import re
import sys

if len(sys.argv) != 2:
<<<<<<< HEAD
    print("Usage: %s FILE" % sys.argv[0])
=======
    print "Usage: %s FILE" % sys.argv[0]
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
    sys.exit(2)

readelf = os.getenv("READELF", "readelf")

start_pattern = re.compile("<([^>]*)>: \[0x([0-9a-f]+)-0x([0-9a-f]+)\]")
rlen_pattern  = re.compile(".*rlen=([0-9]+)")

def check_func (func, slots, rlen_sum):
    if slots != rlen_sum:
        global num_errors
        num_errors += 1
        if not func: func = "[%#x-%#x]" % (start, end)
<<<<<<< HEAD
        print("ERROR: %s: %lu slots, total region length = %lu" % (func, slots, rlen_sum))
=======
        print "ERROR: %s: %lu slots, total region length = %lu" % (func, slots, rlen_sum)
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
    return

num_funcs = 0
num_errors = 0
func = False
slots = 0
rlen_sum = 0
for line in os.popen("%s -u %s" % (readelf, sys.argv[1])):
    m = start_pattern.match(line)
    if m:
        check_func(func, slots, rlen_sum)

        func  = m.group(1)
<<<<<<< HEAD
        start = int(m.group(2), 16)
        end   = int(m.group(3), 16)
        slots = 3 * (end - start) / 16
        rlen_sum = 0
=======
        start = long(m.group(2), 16)
        end   = long(m.group(3), 16)
        slots = 3 * (end - start) / 16
        rlen_sum = 0L
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
        num_funcs += 1
    else:
        m = rlen_pattern.match(line)
        if m:
<<<<<<< HEAD
            rlen_sum += int(m.group(1))
check_func(func, slots, rlen_sum)

if num_errors == 0:
    print("No errors detected in %u functions." % num_funcs)
=======
            rlen_sum += long(m.group(1))
check_func(func, slots, rlen_sum)

if num_errors == 0:
    print "No errors detected in %u functions." % num_funcs
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
else:
    if num_errors > 1:
        err="errors"
    else:
        err="error"
<<<<<<< HEAD
    print("%u %s detected in %u functions." % (num_errors, err, num_funcs))
=======
    print "%u %s detected in %u functions." % (num_errors, err, num_funcs)
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
    sys.exit(1)
