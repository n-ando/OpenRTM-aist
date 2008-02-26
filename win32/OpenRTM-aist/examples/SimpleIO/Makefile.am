## -*- Makefile -*-
##---------------------------------------------------------------------------
## Makefile.am for win32/OpenRTM-aist/examples/SimpleIO
##
## $Id: Makefile.am,v 1.1.2.4 2008-02-26 15:11:41 n-ando Exp $
##
## $Log: not supported by cvs2svn $
## Revision 1.1.2.3  2007/09/21 10:30:49  n-ando
## Now vcproj is not deleted in clean target.
##
## Revision 1.1.2.2  2007/07/22 10:34:18  n-ando
## *** empty log message ***
##
## Revision 1.1.2.1  2007/07/20 16:26:56  n-ando
## Makefile for Win32 source tree management.
##
##
##---------------------------------------------------------------------------
clean-local:
	rm -rf Debug Release
	rm -rf *~ *.cpp *.h rtc.conf *.user *.vcproj

src:
	cp $(top_srcdir)/examples/SimpleIO/*.cpp .
	cp $(top_srcdir)/examples/SimpleIO/*.h .
	cp $(top_srcdir)/examples/SimpleIO/rtc.conf .
	qkc -ms *.cpp
	qkc -ms *.h

dist-hook: src
