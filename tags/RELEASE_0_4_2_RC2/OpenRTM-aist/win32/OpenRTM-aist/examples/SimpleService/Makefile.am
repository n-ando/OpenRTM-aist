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
	cp $(top_srcdir)/examples/SimpleService/*.cpp .
	cp $(top_srcdir)/examples/SimpleService/*.h .
	cp $(top_srcdir)/examples/SimpleService/*.idl .
	cp $(top_srcdir)/examples/SimpleService/rtc.conf .
	qkc -ms *.cpp
	qkc -ms *.h
	qkc -ms *.idl

dist-hook: src
