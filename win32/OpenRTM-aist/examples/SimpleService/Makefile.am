## -*- Makefile -*-
##---------------------------------------------------------------------------
## Makefile.am for win32/OpenRTM-aist/examples/SimpleService
##
## $Id$
##---------------------------------------------------------------------------
clean-local:
	rm -rf Debug Release
	rm -rf *~ *.cpp *.h *.idl rtc.conf
	rm -rf *.vcproj *.user *.ncb *.suo

src:
	cp -p $(top_srcdir)/examples/SimpleService/*.cpp .
	cp -p $(top_srcdir)/examples/SimpleService/*.h .
	cp -p $(top_srcdir)/examples/SimpleService/*.idl .
	cp -p $(top_srcdir)/examples/SimpleService/rtc.conf .
	qkc -ms *.cpp
	qkc -ms *.h
	qkc -ms *.idl

dist-hook: src
