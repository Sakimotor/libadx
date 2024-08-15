# LibADX for KallistiOS ##version##
# Copyright (C) 2011-2013 Josh 'PH3NOM' Pearson
# Copyright (C) 2024 The KOS Team and contributors
# Licensed under the BSD 2-Clause License

TARGET = libADX.a
OBJS = libadx.o snddrv.o

defaultall: create_kos_link $(OBJS) subdirs linklib
defaultclean: clean_kos_link clean_subdirs

ROOT_DIR := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

include $(KOS_BASE)/addons/Makefile.prefab

# Handle the headers
HDR_INSTDIR = adx

create_kos_link: clean_kos_link
	mkdir -p $(KOS_BASE)/addons/include/$(HDR_INSTDIR)
	ln -s $(ROOT_DIR)*.h $(KOS_BASE)/addons/include/$(HDR_INSTDIR)

clean_kos_link:
	-rm -rf $(KOS_BASE)/addons/include/$(HDR_INSTDIR)
