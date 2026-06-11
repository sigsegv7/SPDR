
#
# Copyright (c) 2026, Chloe M.
# Provided under the BSD-3 clause.
#
# Description: String runtime library build script
# Author:      Chloe M.
#

CFILES = $(shell find . -name "*.c")
OFILES = $(CFILES:.c=.o)

CC = clang
CFLAGS = 			\
	$(SYS_CFLAGS) 	\
	-I../../head       \
	-I../../../../../public/sdk/head

.PHONY: all
all: $(OFILES)

%.o: %.c
	$(CC) -c $< $(CFLAGS) -o $@
