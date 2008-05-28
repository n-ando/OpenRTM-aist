## -*- Makefile -*-
##---------------------------------------------------------------------------
## Makefile.am for win32/OpenRTM-aist
##
## $Id$
##---------------------------------------------------------------------------
SUBDIRS = bin etc build docs examples utils rtm installer .


clean-local:
	rm -f *~ *.sln *.yaml *.ncb *.suo *.user


sln: OpenRTM-aist_vc8.sln OpenRTM-aist_vc9.sln

OpenRTM-aist_vc8.sln: OpenRTM-aist.sln.dep
	$(top_srcdir)/build/slntool.py     \
		--vcversion VC8            \
		--dep OpenRTM-aist.sln.dep \
		--out OpenRTM-aist_vc8.sln \
		`find ./ -name '*_vc8.vcproj' \! -name 'USB*.vcproj'`
	qkc -ms OpenRTM-aist_vc8.sln

OpenRTM-aist_vc9.sln:
	$(top_srcdir)/build/slntool.py     \
		--vcversion VC9            \
		--dep OpenRTM-aist.sln.dep \
		--out OpenRTM-aist_vc9.sln \
		`find ./ -name '*_vc9.vcproj' \! -name 'USB*.vcproj'`
	qkc -ms OpenRTM-aist_vc9.sln

dist-hook: clean-local sln

EXTRA_DIST =                          \
	OpenRTM-aist_vc8.sln          \
	OpenRTM-aist_vc9.sln          \
	OpenRTM-aist.sln.dep          \
	RunAtFirst.py                 \
	autobuild_vc8.bat             \
	autobuild_vc9.bat             \
	rtm_distbuild.vsprops


