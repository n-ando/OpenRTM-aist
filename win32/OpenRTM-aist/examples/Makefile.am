## -*- Makefile -*-
##---------------------------------------------------------------------------
## Makefile.am for win32/OpenRTM-aist/examples
##
## $Id$
##---------------------------------------------------------------------------
SUBDIRS = ConfigSample SimpleIO SeqIO SimpleService USBCamera .

wxs:
	cp example.yaml	../installer/

clean-local:
	rm -f *~

dist-hook: clean-local wxs

EXTRA_DIST = example.yaml
