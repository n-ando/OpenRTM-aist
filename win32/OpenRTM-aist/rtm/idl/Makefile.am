## -*- Makefile -*-
##---------------------------------------------------------------------------
## Makefile.am for win32/OpenRTM-aist/rtm/idl
##
## $Id$
##---------------------------------------------------------------------------
clean-local:
	rm -rf Debug Release
	rm -f *~ *.idl *.cpp *.h *.cc *.hh
	rm -f *.sln *.suo *.ncb *.user *.vcproj *.vcxproj

src:
	cp -p $(top_srcdir)/src/lib/rtm/idl/*.idl .
	qkc -ms *.idl


dist-hook: src
