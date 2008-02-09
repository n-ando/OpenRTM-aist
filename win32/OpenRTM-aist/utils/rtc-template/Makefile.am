## -*- Makefile -*-
##---------------------------------------------------------------------------
## Makefile.am for rtc-template
##
## $Log: not supported by cvs2svn $
## Revision 1.1.2.3  2007/09/21 10:30:56  n-ando
## Now vcproj is not deleted in clean target.
##
## Revision 1.1.2.2  2007/07/20 17:29:13  n-ando
## A fix for win32 porting.
##
## Revision 1.1.2.1  2007/07/20 16:27:16  n-ando
## Makefile for Win32 source tree management.
##
##
##---------------------------------------------------------------------------

clean-local:
	rm -rf *~ *core *.pyc *.py

src:
	cp $(top_srcdir)/utils/rtc-template/rtc-template rtc-template.py
	cp $(top_srcdir)/utils/rtc-template/*.py .

wxs: src
	$(top_srcdir)/build/makewxs.py flist \
		-c RtcTemplate \
		-o ../../installer/rtctemplate.yaml \
		-p ..\\utils\\rtc-template \
		*.py

dist-hook: clean-local src wxs
