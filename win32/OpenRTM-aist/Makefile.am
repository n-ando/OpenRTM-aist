## -*- Makefile -*-
##---------------------------------------------------------------------------
## Makefile.am for win32/OpenRTM-aist
##
## $Id: Makefile.am,v 1.1.2.5 2008-03-06 06:53:39 n-ando Exp $
##
## $Log: not supported by cvs2svn $
## Revision 1.1.2.4  2008/02/29 05:07:17  n-ando
## Changes for new solution tool.
##
## Revision 1.1.2.3  2008/02/09 20:01:37  n-ando
## For wix's wxs file generation.
##
## Revision 1.1.2.2  2007/07/22 10:59:44  n-ando
## *** empty log message ***
##
## Revision 1.1.2.1  2007/07/20 16:26:19  n-ando
## Makefile for Win32 source tree management.
##
##
##---------------------------------------------------------------------------
SUBDIRS = bin build docs examples utils rtm installer .


clean-local:
	rm -f *~ *.sln *.yaml *.ncb *.suo *.user


sln: OpenRTM-aist_vc8.sln OpenRTM-aist_vc9.sln

OpenRTM-aist_vc8.sln: OpenRTM-aist.sln.dep
	$(top_srcdir)/build/slntool.py     \
		--vcversion VC8            \
		--dep OpenRTM-aist.sln.dep \
		--out OpenRTM-aist_vc8.sln \
		`find ./ -name '*_vc8.vcproj' \! -name 'USB*.vcproj'`
	qkc -ms OpenRTM-aist_vc8.sln

OpenRTM-aist_vc9.sln:
	$(top_srcdir)/build/slntool.py     \
		--vcversion VC9            \
		--dep OpenRTM-aist.sln.dep \
		--out OpenRTM-aist_vc9.sln \
		`find ./ -name '*_vc9.vcproj' \! -name 'USB*.vcproj'`
	qkc -ms OpenRTM-aist_vc9.sln

dist-hook: clean-local sln

EXTRA_DIST =                 \
	OpenRTM-aist.sln.dep \
	RunAtFirst.py
