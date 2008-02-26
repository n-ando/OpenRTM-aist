## Makefile.am for win32/OpenRTM-aist/bin
##
## $Id: Makefile.am,v 1.1.2.4 2008-02-26 15:15:57 n-ando Exp $
##
## $Log: not supported by cvs2svn $
## Revision 1.1.2.3  2008/02/09 20:01:08  n-ando
## For wix's wxs file generation.
##
## Revision 1.1.2.2  2007/07/20 20:31:24  n-ando
## rtm-naming.bat was added.
##
## Revision 1.1.2.1  2007/07/20 16:26:26  n-ando
## Makefile for Win32 source tree management.
##
##
##---------------------------------------------------------------------------

VER = $(RTM_SHORT_VERSION)
WINLIBS = libRTCSkel.lib \
	libRTCSkeld.lib \
	RTC$(VER).lib \
	RTC$(VER)d.lib \
	RTC$(VER).dll \
	RTC$(VER)d.dll

clean-local:
	rm -f *~ *.dll *.lib
	rm -rf *~ *.py

copy_scripts:
	cp $(top_srcdir)/build/*.py .
	cp $(top_srcdir)/utils/rtm-skelwrapper/*.py .
	cp $(top_srcdir)/utils/rtm-skelwrapper/rtm-skelwrapper rtm-skelwrapper.py
wxs:
	$(top_srcdir)/build/makewxs.py flist \
		-c Libs \
		-o ../installer/libs.yaml \
		-p ..\\bin \
		$(WINLIBS)
	$(top_srcdir)/build/makewxs.py flist \
		-c Bin \
		-o ../installer/bin.yaml \
		-p ..\\bin \
		*.py *.bat $(WINLIBS)

dist-hook: clean-local copy_scripts wxs

EXTRA_DIST = rtm-naming.bat
