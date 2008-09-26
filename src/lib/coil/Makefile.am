## -*- Makefile -*-
##---------------------------------------------------------------------------
## Makefile.am for coil (Component Object Infrastructure Layer)
##
## $Id$
##---------------------------------------------------------------------------

if COIL_PLATFORM_ACE
PLATFORM = ace
endif
if COIL_PLATFORM_POSIX
PLATFORM = posix
endif

SUBDIRS = $(PLATFORM) @UNITTEST@ include lib build common win32
DIST_SUBDIR = posix ace

clean-local:
	rm -f config_coil.h
	rm -f *~