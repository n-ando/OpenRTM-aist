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

SUBDIRS = $(PLATFORM) @UNITTEST@ include lib
DIST_SUBDIRS = build common posix win32 ace


clean-local:
	rm -f *~