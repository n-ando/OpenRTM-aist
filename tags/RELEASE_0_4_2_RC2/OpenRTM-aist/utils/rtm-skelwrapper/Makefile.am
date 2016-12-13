## -*- Makefile -*-
##---------------------------------------------------------------------------
## Makefile.am for rtm-skelwrapper: rtm skeleton/stub wrapper generator
##
## $Id$
##---------------------------------------------------------------------------

AUTOMAKE_OPTIONS = 1.4

bin_SCRIPTS = rtm-skelwrapper

all:
	chmod 755 rtm-skelwrapper

pyhelperdir = $(pkglibdir)/py_helper

pyhelper_SCRIPTS = skel_wrapper.py


EXTRA_DIST = \
	rtm-skelwrapper \
	skel_wrapper.py \
	ezt.py


clean-local:
	rm -rf *~ *core *.pyc
