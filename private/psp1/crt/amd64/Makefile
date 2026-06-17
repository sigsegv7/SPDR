#
# Copyright (c) 2026, Chloe M.
# Provided under the BSD-3 clause.
#
# Description: C runtime build script
# Author:      Chloe M.
#

ASMFILES = $(shell find . -name "*.S")
ASM_OFILES = $(ASMFILES:.S=.S.o)

.PHONY: all
all: $(ASM_OFILES)

%.S.o: %.S
	$(SYS_CC) -c $(SYS_CFLAGS) $< -o $@
