## -*- Makefile -*-
##---------------------------------------------------------------------------
## Makefile.am for win32/OpenRTM-aist/examples
##
## $Id: Makefile.am,v 1.1.2.3 2008-02-09 20:00:59 n-ando Exp $
##
## $Log: not supported by cvs2svn $
## Revision 1.1.2.2  2007/07/22 13:48:10  n-ando
## *** empty log message ***
##
## Revision 1.1.2.1  2007/07/20 16:26:39  n-ando
## Makefile for Win32 source tree management.
##
##
##---------------------------------------------------------------------------
SUBDIRS = ConfigSample SimpleIO SeqIO SimpleService USBCamera .

wxs:
	cp example.yaml	../installer/

clean-local:
	rm -f *~

dist-hook: clean-local wxs

EXTRA_DIST = example.yaml