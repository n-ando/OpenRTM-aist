## -*- Makefile -*-
##---------------------------------------------------------------------------
## Makefile.am for win32/OpenRTM-aist
##
## $Id$
##---------------------------------------------------------------------------

clean-local:
	rm -f *.conf.*

copy_etc:
	cp $(top_srcdir)/etc/rtc.conf.sample .

wxs:
	cp etc.yaml ../installer/etc.yaml

dist-hook: clean-local copy_etc wxs

EXTRA_DIST =                       \
	rtc.conf.sample            \
	etc.yaml                   \
	rtm_config_omni407.vsprops \
	rtm_config_omni412.vsprops
