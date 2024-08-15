LibADX (c) 2011-2013 Josh PH3NOM Pearson


decoder algorithm based on adx2wav (c) BERO 2001

LibADX is a library for decoding ADX audio files using the
KallistiOS development environment, intended for use only
on the Sega Dreamcast game console.

LibADX features full implementation of the ADX looping function.
The functions available include play, pause, stop, restart.

This library is completely free to modify and or redistribute.

LibADX is a static library, build the library with the makefile:
LibADX/LibADX/Makefile

Then build the example player:
LibADX/Makefile

The example player uses a hard-coded file name, so make sure
to include a "sample.adx" on the root of the /cd/, or modify
the source libADXplay.c to load a different file.

** This File is a part of Dreamcast Media Center
** (C) Josh "PH3NOM" Pearson 2011


