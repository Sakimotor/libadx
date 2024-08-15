# LibADX for KallistiOS ##version##
# Copyright (C) 2011-2013 Josh 'PH3NOM' Pearson
# Copyright (C) 2024 The KOS Team and contributors
# Licensed under the BSD 2-Clause License

TARGET = libADX.a
OBJS = libadx.o snddrv.o

HDR_INSTDIR = adx

ROOT_PATH := $(realpath $(dir $(abspath $(lastword $(MAKEFILE_LIST))))..)
HDR_INSTPATH := $(KOS_BASE)/addons/include/$(HDR_INSTDIR)

KOS_CFLAGS += -I$(ROOT_PATH)/include

defaultall: create_kos_link $(OBJS) subdirs linklib
defaultclean: clean_kos_link clean_subdirs

include $(KOS_BASE)/addons/Makefile.prefab

# Handle headers installation
create_kos_link: clean_kos_link
	ln -s $(ROOT_PATH)/include $(KOS_BASE)/addons/include/$(HDR_INSTDIR)

# Handle headers removal
clean_kos_link:
	-rm -rf $(HDR_INSTPATH)

# KallistiOS Port management
# Prepare the library for installing it using the corresponding kos-port
# This target is executed from the kos-ports trunk
prepareport: defaultall clean_kos_link
	mv $(KOS_BASE)/addons/lib/$(KOS_ARCH)/$(TARGET) $(ROOT_PATH)
	-rm -rf $(HDR_INSTPATH)
