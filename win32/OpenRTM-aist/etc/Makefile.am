## -*- Makefile -*-
##---------------------------------------------------------------------------
## Makefile.am for win32/OpenRTM-aist
##
## $Id$
##---------------------------------------------------------------------------

clean-local:
	rm -f *.conf.*

rtc.conf.sample:
	cp -p $(top_srcdir)/etc/rtc.conf.sample .

wxs:
	cp -p etc.yaml ../installer/etc.yaml

dist-hook: clean-local rtc.conf.sample wxs

EXTRA_DIST =                       \
	rtc.conf.sample            \
	etc.yaml                   \
	rtm_config_omni407.vsprops \
	rtm_config_omni412.vsprops \
	rtm_config_omni414.vsprops \
	rtm_config_omni414.props
