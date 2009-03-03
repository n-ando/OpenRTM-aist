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
	rm -rf .libs
	mkdir .libs
	cp $(top_srcdir)/$(PLATFORM)/coil/.libs/*.so* ./.libs/
	cp $(top_srcdir)/$(PLATFORM)/coil/.libs/*.a ./.libs/
	cp $(top_srcdir)/$(PLATFORM)/coil/*.la .

clean-local:
	rm -f *~
	rm -rf .libs
	rm -f libcoil*
