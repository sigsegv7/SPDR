#
# Copyright (c) 2026, Chloe M.
# Provided under the BSD-3 clause.
#
# Description: Kernel-side build script
# Author:      Chloe M.
#

CFILES = $(shell find ../init -name "*.c")
CFILES += $(shell ls *.c)
CFILES += $(shell find ../bpal/ -name "*.c")
CFILES += $(shell find ../drivers/ -name "*.c")
CFILES += $(shell find ../xt/ -name "*.c")
CFILES += $(shell find ../ex/ -name "*.c")
CFILES += $(shell find ../lib/ -name "*.c")
CFILES += $(shell find ../mm/ -name "*.c")
CFILES += $(shell find ../ob/ -name "*.c")
CFILES += $(shell find ../ps/ -name "*.c")
OFILES = $(CFILES:.c=.o)
DFILES = $(CFILES:.c=.d)

CC = clang
PROJECT_ROOT = ../../../../..
SPKG_LOC = $(PROJECT_ROOT)/private/$(SERVICE_PACK)/spkg/

CFLAGS = 			\
	$(SYS_CFLAGS)   \
	-I$(PROJECT_ROOT)/public/sdk/head \
	-I$(SPKG_LOC)/head/ 			  \
	-I../xt/flanterm/src				\
	-I../head/target/					\
	-I../head							\
	-D_KERNEL		\
	-MMD			\
	-DPRINTF_DISABLE_SUPPORT_PTRDIFF_T \
	-DPRINTF_DISABLE_SUPPORT_FLOAT

.PHONY: all
all: target $(OFILES) machine

.PHONY: target
target:
	mkdir -p ../head/target/machine/
	rsync -avr ../head/amd64/*.h ../head/target/machine/

.PHONY: machine
machine:
	cd $(ARCH_TARGET)/; 		\
		$(MAKE) 				\
		SYS_CC=$(SYS_CC) 		\
		SYS_LD=$(SYS_LD)		\
		SYS_CFLAGS="$(SYS_CFLAGS)"

-include $(DFILES)
%.o: %.c
	$(CC) -c $< $(CFLAGS) -o $@
