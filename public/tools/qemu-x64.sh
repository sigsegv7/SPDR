#!/bin/sh
#
# Copyright (c) 2026, Chloe M.
# Provided under the BSD-3 clause
#
# Description: QEMU x86_64 run wrapper
# Author: 	   Chloe M.
#

qemu-system-x86_64            \
    -cdrom artifacts/spdr.iso \
    --enable-kvm              \
    -m 2G                     \
    -serial stdio             \
    -cpu host
