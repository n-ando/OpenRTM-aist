## -*- Makefile -*-
##---------------------------------------------------------------------------
## Makefile.am for rtc-template: rtm template code generator script
##
## $Id: Makefile.am,v 1.2 2005-08-26 11:59:17 n-ando Exp $
##
## $Log: not supported by cvs2svn $
## Revision 1.1.1.1  2005/05/12 09:06:18  n-ando
## Public release.
##
##---------------------------------------------------------------------------

AUTOMAKE_OPTIONS = 1.4

bin_SCRIPTS = rtc-template

rtc-template: 

pyhelperdir = $(pkglibdir)/py_helper

pyhelper_SCRIPTS = \
	README_src.py \
	cxx_gen.py \
	python_gen.py \
	gen_base.py \
	ezt.py


EXTRA_DIST = \
	rtc-template \
	README_src.py \
	cxx_gen.py \
	python_gen.py \
	gen_base.py \
	ezt.py

clean-local:
	rm -rf *~ *core *.pyc
