## -*- Makefile -*-
##---------------------------------------------------------------------------
## Makefile.am for win32/OpenRTM-aist/examples/SeqIO
##
## $Id: Makefile.am,v 1.1.2.2 2007-07-22 10:34:15 n-ando Exp $
##
## $Log: not supported by cvs2svn $
## Revision 1.1.2.1  2007/07/20 16:26:51  n-ando
## Makefile for Win32 source tree management.
##
##
##---------------------------------------------------------------------------
clean-local:
	rm -rf Debug Release
	rm -rf *~ *.cpp *.h rtc.conf *.user


vcprojs: SeqInvc8.vcproj SeqOutvc8.vcproj


src:
	cp $(top_srcdir)/examples/SeqIO/*.cpp .
	cp $(top_srcdir)/examples/SeqIO/*.h .
	cp $(top_srcdir)/examples/SeqIO/rtc.conf .
	qkc -ms *.cpp
	qkc -ms *.h


SeqInvc8.vcproj:
	$(top_srcdir)/build/makevcproj.py \
		-i SeqInvc8.vcproj.in     \
		-d SeqInvc8.vcproj.yaml   \
		-o SeqInvc8.vcproj
	qkc -ms SeqInvc8.vcproj


SeqOutvc8.vcproj:
	$(top_srcdir)/build/makevcproj.py \
		-i SeqOutvc8.vcproj.in    \
		-d SeqOutvc8.vcproj.yaml  \
		-o SeqOutvc8.vcproj
	qkc -ms SeqOutvc8.vcproj


dist-hook: clean-local src vcprojs

EXTRA_DIST =                  \
	SeqInvc8.vcproj.in    \
	SeqOutvc8.vcproj.in   \
	SeqInvc8.vcproj.yaml  \
	SeqOutvc8.vcproj.yaml
