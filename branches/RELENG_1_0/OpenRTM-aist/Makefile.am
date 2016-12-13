## -*- Makefile -*-
##---------------------------------------------------------------------------
## Makefile.am for the top directory
##
## $Id$
##---------------------------------------------------------------------------

AUTOMAKE_OPTIONS = 1.4

SUBDIRS = build src utils examples etc docs win32
DIST_SUBDIRS = build src utils examples etc docs win32 packages

EXTRA_DIST =        \
	README      \
	README.jp   \
	COPYRIGHT   \
	COPYING.LIB \
	INSTALL     \
	INSTALL.jp

clean-local:
	rm -f *~ *.core
	rm -rf build-arch-stamp build-indep-stamp
	rm -f OpenRTM-aist*.tar.gz OpenRT-aist*.tar.bz OpenRTM-aist*.zip
