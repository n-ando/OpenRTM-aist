## Makefile.am for win32/OpenRTM-aist/rtm/idl
##
## $Id: Makefile.am,v 1.1.2.3 2008-02-26 15:12:32 n-ando Exp $
##
## $Log: not supported by cvs2svn $
## Revision 1.1.2.2  2008/02/09 20:00:24  n-ando
## For wix's wxs file generation.
##
## Revision 1.1.2.1  2007/07/20 16:27:07  n-ando
## Makefile for Win32 source tree management.
##
##
##---------------------------------------------------------------------------
clean-local:
	rm -rf Debug Release
	rm -f *~ *.idl *.cpp *.h *.cc *.hh *.sln *.suo *.ncb *.user *.vcproj

src:
	cp $(top_srcdir)/rtm/idl/*.idl .
	qkc -ms *.idl


dist-hook: clean-local src
