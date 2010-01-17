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
	cp -p $(top_srcdir)/examples/ConfigSample/*.cpp .
	cp -p $(top_srcdir)/examples/ConfigSample/*.h .
	cp -p $(top_srcdir)/examples/ConfigSample/*.conf .
	qkc -ms *.cpp
	qkc -ms *.h
	qkc -ms *.conf

dist-hook: src
