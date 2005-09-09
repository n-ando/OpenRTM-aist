## -*- Makefile -*-
##---------------------------------------------------------------------------
## Makefile.am for rtm-skelwrapper: rtm skeleton/stub wrapper generator
##
## $Id: Makefile.am,v 1.2 2005-09-09 09:31:13 n-ando Exp $
##
## $Log: not supported by cvs2svn $
## Revision 1.1  2005/09/06 14:47:32  n-ando
## The first version of rtm-skelwrapper.
##
##
##---------------------------------------------------------------------------

AUTOMAKE_OPTIONS = 1.4

bin_SCRIPTS = rtm-skelwrapper

rtm-skelwrapper: 

pyhelperdir = $(pkglibdir)/py_helper

pyhelper_SCRIPTS = skel_wrapper.py


EXTRA_DIST = \
	rtm-skelwrapper \
	skel_wrapper.py \
	ezt.py


clean-local:
	rm -rf *~ *core *.pyc
