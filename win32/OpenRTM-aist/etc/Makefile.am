## -*- Makefile -*-
##---------------------------------------------------------------------------
## Makefile.am for win32/OpenRTM-aist
##
## $Id$
##---------------------------------------------------------------------------

clean-local:
	rm -f *.vsprops *.conf.*

copy_etc:
	cp $(top_srcdir)/win32/OpenRTM-aist/*.vsprops .
	cp $(top_srcdir)/etc/rtc.conf.sample .

wxs:
	$(top_srcdir)/build/makewxs.py flist \
		-c Etc \
		-o ../installer/etc.yaml \
		-p ..\\etc \
		*.vsprops rtc.conf.sample

dist-hook: clean-local copy_etc wxs


