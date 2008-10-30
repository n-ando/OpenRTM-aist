## -*- Makefile -*-
##---------------------------------------------------------------------------
## Makefile.am for win32/OpenRTM-aist/rtm_corba/idl
##
## $Id: Makefile.am 725 2008-10-27 16:49:04Z h-Kojima $
##---------------------------------------------------------------------------
clean-local:
	rm -rf Debug Release
	rm -f *~ *.idl *.cpp *.h *.cc *.hh *.sln *.suo *.ncb *.user *.vcproj

src:
	cp $(top_srcdir)/src/lib/rtm_corba/idl/*.idl .
	cp $(top_srcdir)/src/lib/rtm_corba/idl/*.h .
	qkc -ms *.idl
	qkc -ms *.h


dist-hook: src
