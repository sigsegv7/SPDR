#
# Copyright (c) 2026, Chloe M.
# Provided under the BSD-3 clause
#

CC_PREFIX =
ARCH_TARGET = amd64

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
	-mcmodel=kernel		\
	-Wno-attributes		\
	-Wno-multichar		\
	-fno-stack-protector\
	-D_ST_MULTICORE     \

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
