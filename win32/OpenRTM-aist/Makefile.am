## -*- Makefile -*-
##---------------------------------------------------------------------------
## Makefile.am for win32/OpenRTM-aist
##
## $Id: Makefile.am,v 1.1.2.2 2007-07-22 10:59:44 n-ando Exp $
##
## $Log: not supported by cvs2svn $
## Revision 1.1.2.1  2007/07/20 16:26:19  n-ando
## Makefile for Win32 source tree management.
##
##
##---------------------------------------------------------------------------
SUBDIRS = bin build docs examples utils rtm .


clean-local:
	rm -f *~ *.sln *.yaml *.ncb *.suo *.user


OpenRTM-aist.sln.yaml:
	rm -f OpenRTM-aist.sln.yaml
	find ./ -name '*.vcproj' \
		-exec $(top_srcdir)/build/pickupprojs.py {} \
		>> OpenRTM-aist.sln.yaml \;


OpenRTM-aist.sln:
	$(top_srcdir)/build/makevcproj.py \
		-i OpenRTM-aist.sln.in   \
		-d OpenRTM-aist.sln.yaml \
		-o OpenRTM-aist.sln
	qkc -ms OpenRTM-aist.sln

dist-hook: clean-local OpenRTM-aist.sln.yaml OpenRTM-aist.sln

EXTRA_DIST =                  \
	OpenRTM-aist.vsprops  \
	OpenRTM-aist.sln.in   \
	RunAtFirst.py
