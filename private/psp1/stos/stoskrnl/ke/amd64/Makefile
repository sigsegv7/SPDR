
#
# Copyright (c) 2026, Chloe M.
# Provided under the BSD-3 clause.
#
# Description: Kernel-side machine specific build script
# Author:      Chloe M.
#

ASMFILES = $(shell find . -name "*.S")
CFILES = $(shell find . -name "*.c")
CFILES += $(shell find ../init -name "*.c")

ASMOFILES = $(ASMFILES:.S=.S.o)
OFILES = $(CFILES:.c=.o)

MISC_OFILES = $(shell find ../../ -name "*.o")
PROJECT_ROOT = ../../../../../..

CC = 				\
	$(SYS_CC)

LD =				\
	$(SYS_LD)

CFLAGS = 								\
	$(SYS_CFLAGS)   					\
	-I$(PROJECT_ROOT)/public/sdk/head/	\
	-D_KERNEL

.PHONY: all
all: $(OFILES) $(ASMOFILES)
	$(LD) 			   \
		-Tdevel/link.ld \
		$(MISC_OFILES) \
		-o $(PROJECT_ROOT)/artifacts/stoskrnl.sys

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

%.S.o: %.S
	$(CC) -c $(CFLAGS) $< -o $@
