## -*- Makefile -*-
##---------------------------------------------------------------------------
## Makefile.am for win32/OpenRTM-aist/examples
##
## $Id$
##---------------------------------------------------------------------------
SUBDIRS = Composite ConfigSample LTTSample SimpleIO SeqIO SimpleService USBCamera Fsm .

wxs:
	cp -p *.yaml ../installer/

clean-local:
	rm -f *~

dist-hook: clean-local wxs

EXTRA_DIST = example.yaml lttsample.yaml
