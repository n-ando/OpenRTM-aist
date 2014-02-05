## -*- Makefile -*-
##---------------------------------------------------------------------------
## Makefile.am for external libraries
##
## $Id$
##---------------------------------------------------------------------------

AUTOMAKE_OPTIONS = 1.4

SUBDIRS = nameservice_file

wxs:
	cp -p nameservice_file.yaml ../../installer/

clean-local:
	rm -f *~

dist-hook: clean-local wxs

EXTRA_DIST = nameservice_file.yaml