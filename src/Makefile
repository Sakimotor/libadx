# LibADX for KallistiOS ##version##
# Copyright (C) 2011-2013 Josh 'PH3NOM' Pearson
# Copyright (C) 2024 The KOS Team and contributors
# Licensed under the BSD 2-Clause License

TARGET = libADX.a
OBJS = libadx.o snddrv.o

HDR_INSTDIR = adx

ROOT_PATH := $(realpath $(dir $(abspath $(lastword $(MAKEFILE_LIST))))..)
HDR_INSTPATH := $(KOS_BASE)/addons/include/$(HDR_INSTDIR)
LIB_INSTPATH := $(KOS_BASE)/addons/lib/$(KOS_ARCH)/$(TARGET)
LIB_BUILDPATH := $(ROOT_PATH)/$(TARGET)

KOS_CFLAGS += -I$(ROOT_PATH)/include

defaultall: $(OBJS) subdirs linklib movelib
defaultclean: cleanlib clean_kos_link clean_subdirs

include $(KOS_BASE)/addons/Makefile.prefab

# By default, KallistiOS installs the library in the "addons" directory,
# which indeed is expected in most cases. But since this library can be
# installed using the 'addons' dir (using this Makefile) or via kos-ports,
# we move the $(TARGET) from the 'addons' directory to the current location.
# Then, we will decide where the library file will be moved, depending of
# the installation method.
movelib:
	mv $(LIB_INSTPATH) $(ROOT_PATH)

# Remove the $(TARGET) binary if installed in the current location
cleanlib:
	-rm -f $(LIB_BUILDPATH)

# Install the library in the "addons" location; which is the standard
# behaviour if we are using this Makefile.
install: defaultall create_kos_link
	mv $(LIB_BUILDPATH) $(LIB_INSTPATH)

# Handle headers installation
create_kos_link: clean_kos_link
	ln -s $(ROOT_PATH)/include $(HDR_INSTPATH)

# Handle headers removal
clean_kos_link:
	-rm -rf $(HDR_INSTPATH)
