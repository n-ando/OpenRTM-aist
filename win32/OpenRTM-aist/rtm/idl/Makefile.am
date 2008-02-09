## Makefile.am for win32/OpenRTM-aist/rtm/idl
##
## $Id: Makefile.am,v 1.1.2.2 2008-02-09 20:00:24 n-ando Exp $
##
## $Log: not supported by cvs2svn $
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


libRTCSkelvc8.vcproj:
	$(top_srcdir)/build/makevcproj.py    \
		-i libRTCSkelvc8.vcproj.in   \
		-d libRTCSkelvc8.vcproj.yaml \
		-o libRTCSkelvc8.vcproj
	qkc -ms libRTCSkelvc8.vcproj

idls.yaml: src
	$(top_srcdir)/build/makewxs.py flist \
		-c IDLs \
		-o ../../installer/idls.yaml \
		-p ..\\rtm\\idl \
		*.idl

dist-hook: clean-local src libRTCSkelvc8.vcproj idls.yaml

EXTRA_DIST =                      \
	libRTCSkelvc8.vcproj.in   \
	libRTCSkelvc8.vcproj.yaml