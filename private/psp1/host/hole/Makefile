#
# Copyright (c) 2026, Chloe M.
# Provided under the BSD-3 clause
#
# Description: CUMHOLE build script
# Author: 	   Chloe M.
#

CC = gcc
CFILES = $(shell find . -name "*.c")
OFILES = $(CFILES:.c=.o)

CFLAGS =		\
	-Wall		\
	-pedantic

.PHONY: all
all: ../bin/hole

.PHONY: hole
../bin/hole: $(OFILES)
	$(CC) $^ -o $@

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@
