#
# Copyright (c) 2026, Chloe M.
# Provided under the BSD-3 clause.
#
# Description: C runtime build script
# Author:      Chloe M.
#

include ../mk/user.mk

.PHONY: all
all: machdep

.PHONY: machdep
machdep:
	cd $(ARCH_TARGET)/; $(MAKE) $(PASSDOWN_ARGS)
