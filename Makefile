# LibADX for KallistiOS ##version##
# Copyright (C) 2011-2013 Josh 'PH3NOM' Pearson
# Copyright (C) 2024 The KOS Team and contributors
# Licensed under the BSD 2-Clause License

MAKE ?= make

all:
	@cd ./src; \
	$(MAKE)

clean:
	@cd ./src; \
	$(MAKE) clean

install:
	@cd ./src; \
	$(MAKE) install
