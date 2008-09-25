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

all:
	cp $(top_srcdir)/$(PLATFORM)/coil/.libs/*.so.* .
	cp $(top_srcdir)/$(PLATFORM)/coil/.libs/*.a .

clean-local:
	rm -f *~
	rm -f libcoil*