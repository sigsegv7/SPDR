
#
# Copyright (c) 2026, Chloe M.
# Provided under the BSD-3 clause.
#
# Description: Kernel-side machine specific build script
# Author:      Chloe M.
#

ASMFILES = $(shell find . -name "*.S")
CFILES = $(shell find . -name "*.c")

ASMOFILES = $(ASMFILES:.S=.S.o)
OFILES = $(CFILES:.c=.o)

PROJECT_ROOT = ../../../../../..
KERNEL_ROOT = $(PROJECT_ROOT)/private/$(SERVICE_PACK)/stos
SPKG_LOC = $(PROJECT_ROOT)/private/$(SERVICE_PACK)/spkg/

MISC_OFILES = $(shell find $(SPKG_LOC) -name "*.o")
MISC_OFILES += $(shell find $(KERNEL_ROOT) -name "*.o")

CC = 				\
	$(SYS_CC)

LD =				\
	$(SYS_LD)

CFLAGS = 								\
	$(SYS_CFLAGS)   					\
	-I$(PROJECT_ROOT)/public/sdk/head/	\
	-I../../head/						\
	-D_KERNEL

.PHONY: all
all: $(OFILES) $(ASMOFILES)
	$(LD) 			   \
		-Tdevel/link.ld \
		$(MISC_OFILES) \
		$(OFILES)		\
		-o $(PROJECT_ROOT)/artifacts/stoskrnl.sys

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

%.S.o: %.S
	$(CC) -c $(CFLAGS) $< -o $@
