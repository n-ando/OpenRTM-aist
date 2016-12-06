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

dist-hook: clean-local rtc.conf.sample

EXTRA_DIST =                   \
	rtc.conf.sample            \
	etc.yaml
