## -*- Makefile -*-
##---------------------------------------------------------------------------
## Makefile.am for rtc-template: rtm template code generator script
##
## $Id: Makefile.am,v 1.3.4.1 2007-07-20 16:16:13 n-ando Exp $
##
## $Log: not supported by cvs2svn $
## Revision 1.3  2005/09/08 09:21:57  n-ando
## - Little bug fix.
##
## Revision 1.2  2005/08/26 11:59:17  n-ando
## Now rtc-template uses ezt (Easy Template).
##
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
	vcproject_gen.py \
	uuid.py \
	cxx_svc_impl.py \
	python_gen.py \
	gen_base.py \
	ezt.py


EXTRA_DIST = \
	rtc-template \
	README_src.py \
	cxx_gen.py \
	vcproject_gen.py \
	uuid.py \
	cxx_svc_impl.py \
	python_gen.py \
	gen_base.py \
	ezt.py

clean-local:
	rm -rf *~ *core *.pyc
