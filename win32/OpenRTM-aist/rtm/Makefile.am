## Makefile.am for win32/OpenRTM-aist/rtm
##
## $Id: Makefile.am,v 1.1.2.1 2007-07-20 16:27:03 n-ando Exp $
##
## $Log: not supported by cvs2svn $
##
##---------------------------------------------------------------------------
SUBDIRS = idl .

clean-local:
	rm -rf Debug Release
	rm -f *~ *.cpp *.h *.cc *.hh *.sln *.suo *.ncb *.user *.vcproj

vcprojs: libRTCvc8.vcproj


src:
	cp $(top_srcdir)/rtm/*.cpp .
	cp $(top_srcdir)/rtm/*.h .
	qkc -ms *.cpp
	qkc -ms *.h


libRTCvc8.vcproj:
	$(top_srcdir)/build/makevcproj.py \
		-i libRTCvc8.vcproj.in    \
		-d libRTCvc8.vcproj.yaml  \
		-o libRTCvc8.vcproj
	qkc -ms libRTCvc8.vcproj



dist-hook: clean-local src libRTCvc8.vcproj


EXTRA_DIST =                  \
	libRTCvc8.vcproj.in   \
	libRTCvc8.vcproj.yaml