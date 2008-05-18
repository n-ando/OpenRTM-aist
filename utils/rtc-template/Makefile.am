## -*- Makefile -*-
##---------------------------------------------------------------------------
## Makefile.am for rtc-template: rtm template code generator script
##
## $Id$
##---------------------------------------------------------------------------

AUTOMAKE_OPTIONS = 1.4

bin_SCRIPTS = rtc-template

yat.py:
	cp $(top_srcdir)/build/yat.py .
vcprojtool.py:
	cp $(top_srcdir)/build/vcprojtool.py .
slntool.py:
	cp $(top_srcdir)/build/slntool.py .

rtc-template: 

pyhelperdir = $(pkglibdir)/py_helper

pyhelper_SCRIPTS =       \
	README_src.py    \
	cxx_gen.py       \
	vcproject_gen.py \
	uuid.py          \
	cxx_svc_impl.py  \
	python_gen.py    \
	gen_base.py      \
	yat.py           \
	slntool.py       \
	vcprojtool.py


EXTRA_DIST =             \
	rtc-template     \
	README_src.py    \
	cxx_gen.py       \
	vcproject_gen.py \
	uuid.py          \
	cxx_svc_impl.py  \
	python_gen.py    \
	gen_base.py      \
	yat.py           \
	slntool.py       \
	vsprojtool.py

clean-local:
	rm -rf *~ *core *.pyc
	rm -rf yat.py