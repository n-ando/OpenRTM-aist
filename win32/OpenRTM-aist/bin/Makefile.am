## -*- Makefile -*-
##------------------------------------------------------------
## Makefile.am for win32/OpenRTM-aist/bin
##
## $Id$
##---------------------------------------------------------------------------

VER = $(RTM_SHORT_VERSION)

clean-local:
	rm -f *~ *.dll *.lib *.exe
	rm -rf *~ *.py

copy_scripts:
	cp -p $(top_srcdir)/build/*.py .
	cp -p $(top_srcdir)/utils/rtm-skelwrapper/*.py .
	cp -p $(top_srcdir)/utils/rtm-skelwrapper/rtm-skelwrapper rtm-skelwrapper.py

dist-hook: clean-local copy_scripts

EXTRA_DIST = \
	rtm-naming.bat \
	rtc.conf
