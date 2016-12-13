## -*- Makefile -*-
##---------------------------------------------------------------------------
## Makefile.am for win32/OpenRTM-aist/examples/SimpleIO
##
## $Id$
##---------------------------------------------------------------------------
clean-local:
	rm -rf Debug Release
	rm -rf *~ *.cpp *.h *.idl rtc.conf
	rm -rf *.vcproj *.user *.ncb *.suo
	rm -rf ConsoleIn ConsoleInComp ConsoleOut ConsoleOutComp

src:
	cp -p $(top_srcdir)/examples/SimpleIO/*.cpp .
	cp -p $(top_srcdir)/examples/SimpleIO/*.h .
	cp -p $(top_srcdir)/examples/SimpleIO/rtc.conf .
	qkc -ms *.cpp
	qkc -ms *.h

dist-hook: src
