## Makefile.am for win32/OpenRTM-aist/examples/ConfigSample
##
## $Id: Makefile.am,v 1.1.2.2 2007-07-20 16:54:56 n-ando Exp $
##
## $Log: not supported by cvs2svn $
## Revision 1.1.2.1  2007/07/20 16:26:46  n-ando
## Makefile for Win32 source tree management.
##
##
##---------------------------------------------------------------------------
clean-local:
	rm -rf Debug Release
	rm -rf *~ *.cpp *.h *.user *.conf

vcprojs: ConfigSamplevc8.vcproj


src:
	cp $(top_srcdir)/examples/ConfigSample/*.cpp .
	cp $(top_srcdir)/examples/ConfigSample/*.h .
	cp $(top_srcdir)/examples/ConfigSample/*.conf .
	qkc -ms *.cpp
	qkc -ms *.h
	qkc -ms *.conf


ConfigSamplevc8.vcproj:
	$(top_srcdir)/build/makevcproj.py      \
		-i ConfigSamplevc8.vcproj.in   \
		-d ConfigSamplevc8.vcproj.yaml \
		-o ConfigSamplevc8.vcproj
	qkc -ms ConfigSamplevc8.vcproj


dist-hook: clean-local src vcprojs

EXTRA_DIST =                         \
	ConfigSamplevc8.vcproj.in    \
	ConfigSamplevc8.vcproj.yaml


