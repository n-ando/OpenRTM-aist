## -*- Makefile -*-
##---------------------------------------------------------------------------
## Makefile.am for win32/OpenRTM-aist/ext/ec/artlinux
##
## $Id$
##---------------------------------------------------------------------------
clean-local:
	rm -rf *~ *.cpp *.h rtc.conf.sample Makefile.in

src:
	cp -p $(top_srcdir)/src/ext/ec/artlinux/rtc.conf.sample .
	cp -p $(top_srcdir)/src/ext/ec/artlinux/*.cpp .
	cp -p $(top_srcdir)/src/ext/ec/artlinux/*.h .
	qkc -O- -ms *.cpp
	qkc -O- -ms *.h

dist-hook: src
