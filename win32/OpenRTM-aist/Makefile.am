## -*- Makefile -*-
##---------------------------------------------------------------------------
## Makefile.am for win32/OpenRTM-aist
##
## $Id$
##---------------------------------------------------------------------------
SUBDIRS = bin etc cmake build docs examples ext utils coil rtm installer .


clean-local:
	rm -f *~ *.sln *.yaml *.ncb *.suo *.user
	rm -rf components
	rm -f coil_distbuild.vsprops
	rm -f coil_config.vsprops
	rm -f coil_distbuild.props
	rm -f coil_config.props


sln: OpenRTM-aist_vc8.sln OpenRTM-aist_vc9.sln OpenRTM-aist_vc10.sln

OpenRTM-aist_vc8.sln: OpenRTM-aist.sln.dep
	$(top_srcdir)/build/slntool.py     \
		--vcversion VC8            \
		--dep OpenRTM-aist.sln.dep \
		--out OpenRTM-aist_vc8.sln \
		`find ./ -name '*_vc8.vcproj' \! -name 'USB*.vcproj'`
	qkc -O- -ms OpenRTM-aist_vc8.sln

OpenRTM-aist_vc9.sln:
	$(top_srcdir)/build/slntool.py     \
		--vcversion VC9            \
		--dep OpenRTM-aist.sln.dep \
		--out OpenRTM-aist_vc9.sln \
		`find ./ -name '*_vc9.vcproj' \! -name 'USB*.vcproj'`
	qkc -O- -ms OpenRTM-aist_vc9.sln

OpenRTM-aist_vc10.sln:
	$(top_srcdir)/build/slntool.py      \
		--vcversion VC10            \
		--dep OpenRTM-aist.sln.dep  \
		--out OpenRTM-aist_vc10.sln \
		`find ./ -name '*_vc10.vcxproj' \! -name 'USB*.vcxproj'`
	qkc -O- -ms OpenRTM-aist_vc10.sln

vsprops:  coil_distbuild.vsprops coil_config.vsprops coil_distbuild.props coil_config.props


coil_distbuild.vsprops:
	cp -p $(top_srcdir)/src/lib/coil/win32/coil_distbuild.vsprops .

coil_config.vsprops:
	cp -p $(top_srcdir)/src/lib/coil/win32/coil_config.vsprops .

coil_distbuild.props:
	cp -p $(top_srcdir)/src/lib/coil/win32/coil_distbuild.props .

coil_config.props:
	cp -p $(top_srcdir)/src/lib/coil/win32/coil_config.props .

dist-hook: clean-local sln vsprops

EXTRA_DIST =                          \
	OpenRTM-aist.sln.dep          \
	RunAtFirst.py                 \
	autobuild_vc8.bat             \
	autobuild_vc9.bat             \
	autobuild_vc10.bat            \
	rtm_distbuild.vsprops         \
	coil_distbuild.vsprops        \
	coil_config.vsprops


