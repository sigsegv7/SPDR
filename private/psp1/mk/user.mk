#
# Copyright (c) 2026, Chloe M.
# Provided under the BSD-3 clause
#

CC_PREFIX =

ifeq ($(ARCH_TARGET), amd64)
	CC_TARGET = x86_64-unknown-elf
else
	CC_TARGET =
endif

CC = \
	clang
LD = \
	 ld

SYS_CFLAGS =			\
	-nostdlib			\
	-nostdinc			\
	-ffreestanding		\
	-fexceptions		\
	-target $(CC_TARGET)\
	-Wno-attributes		\
	-Wno-multichar		\
	-fno-stack-protector

ifeq ($(ARCH_TARGET),amd64)
	SYS_CFLAGS += 		\
		-mno-sse		\
		-mno-sse2		\
		-mno-sse3		\
		-mno-avx		\
		-mno-avx2		\
		-mno-80387		\
		-mno-3dnow		\
		-mno-mmx
endif

PASSDOWN_ARGS = \
	ARCH=$(ARCH_TARGET)		\
	SYS_CC=$(CC)			\
	SYS_LD=$(LD)			\
	SYS_CFLAGS="$(SYS_CFLAGS)"\
	ARCH_TARGET=$(ARCH_TARGET)
