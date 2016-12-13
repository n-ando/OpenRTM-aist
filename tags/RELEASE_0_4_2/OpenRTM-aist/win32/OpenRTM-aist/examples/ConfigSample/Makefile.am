## -*- Makefile -*-
##---------------------------------------------------------------------------
## Makefile.am for win32/OpenRTM-aist/examples/ConfigSample
##
## $Id$
##---------------------------------------------------------------------------
clean-local:
	rm -rf Debug Release
	rm -rf *~ *.cpp *.h *.idl *.conf
	rm -rf *.vcproj *.user *.ncb *.suo

src:
	cp $(top_srcdir)/examples/ConfigSample/*.cpp .
	cp $(top_srcdir)/examples/ConfigSample/*.h .
	cp $(top_srcdir)/examples/ConfigSample/*.conf .
	qkc -ms *.cpp
	qkc -ms *.h
	qkc -ms *.conf

dist-hook: src
