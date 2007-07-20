## -*- Makefile -*-
##---------------------------------------------------------------------------
## Makefile.am for rtc-template
##
## $Log: not supported by cvs2svn $
## Revision 1.1.2.1  2007/07/20 16:27:16  n-ando
## Makefile for Win32 source tree management.
##
##
##---------------------------------------------------------------------------

clean-local:
	rm -rf *~ *core *.pyc

src:
	cp $(top_srcdir)/utils/rtc-template/rtc-template rtc-template.py
	cp $(top_srcdir)/utils/rtc-template/*.py .


dist-hook: clean-local src
