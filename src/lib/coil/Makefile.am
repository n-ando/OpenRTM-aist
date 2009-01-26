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

SUBDIRS = $(PLATFORM) include lib build common utils win32 @UNITTEST@
DIST_SUBDIRS = $(SUBDIRS) tests

clean-local:
	rm -f config_coil.h
	rm -f *~
