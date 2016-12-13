## -*- Makefile -*-
##---------------------------------------------------------------------------
## Makefile.am for rtcprof
##
## $Id$
##---------------------------------------------------------------------------

clean-local:
	rm -rf *~ *core *.cpp *.vcproj *.user *.exe
	rm -rf rtc.conf
	rm -rf rtcprof

src:
	cp -p $(top_srcdir)/utils/rtcd/*.cpp .
	qkc -ms *.cpp

dist-hook: src
