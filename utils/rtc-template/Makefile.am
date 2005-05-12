## -*- Makefile -*-
##---------------------------------------------------------------------------
## Makefile.am for rtc-template: rtm template code generator script
##
## $Id: Makefile.am,v 1.1.1.1 2005-05-12 09:06:18 n-ando Exp $
##
## $Log: not supported by cvs2svn $
##---------------------------------------------------------------------------

AUTOMAKE_OPTIONS = 1.4

bin_SCRIPTS = rtc-template

rtc-template: 

pyhelperdir = $(pkglibdir)/py_helper

pyhelper_SCRIPTS = \
	README_src.py \
	CXX_src.py \
	Py_src.py


EXTRA_DIST = \
	rtc-template \
	README_src.py \
	CXX_src.py \
	Py_src.py

clean-local:
	rm -rf *~ *core
