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

all-local:
	cp $(top_srcdir)/$(PLATFORM)/coil/*.h .
	cp $(top_srcdir)/common/*.h .

clean-local:
	rm -f *.h
	rm -f *~
