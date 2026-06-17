#
# Copyright (c) 2026, Chloe M.
# Provided under the BSD-3 clause.
#
# Description: Sex service manager build script
# Author:      Chloe M.
#

include ../mk/user.mk

CFLAGS += -I$(PROJECT_ROOT)/public/sdk/head

SERVER_CFILES = $(shell find server/ -name "*.c")
SERVER_OFILES = $(SERVER_CFILES:.c=.o)
CRT_OFILES = $(shell find ../crt/ -name "*.o")

.PHONY: all
all: server

.PHONY: server
server: $(SERVER_OFILES)
	$(LD) $(CRT_OFILES) $(SERVER_OFILES) -o $(BASE_DIR)/system64/ssm.sys

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@
