## -*- Makefile -*-
##---------------------------------------------------------------------------
## Makefile.am for external libraries
##
## $Id$
##---------------------------------------------------------------------------
SUBDIRS = logical_time .

wxs:
	cp -p logical_time.yaml ../../installer

clean-local:
	rm -f *~

dist-hook: clean-local wxs

EXTRA_DIST = logical_time.yaml

