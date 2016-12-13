## -*- Makefile -*-
##---------------------------------------------------------------------------
## Makefile.am for coil (Component Object Infrastructure Layer)
##
## $Id$
##---------------------------------------------------------------------------

DIST_SUBDIRS = coil bin build .

clean-local:
	rm -f *~
	rm -f *.sln *.ncb *.suo

EXTRA_DIST =                   \
	coil                   \
	coil.sln.dep           \
	coil_config.vsprops    \
	coil_distbuild.vsprops \
	coil_vc8.sln           \
	coil_vc9.sln

#------------------------------------------------------------
# sln file build rules
#------------------------------------------------------------
win32_builddir = .

sln: coil_vc8.sln coil_vc9.sln

vcproj:
	(cd coil ; make vcproj)


coil_vc8.sln: coil.sln.dep vcproj
	$(top_srcdir)/build/slntool.py     \
		--vcversion VC8            \
		--dep coil.sln.dep \
		--out coil_vc8.sln \
		`find ./ -name '*_vc8.vcproj'`
	qkc -ms coil_vc8.sln

coil_vc9.sln: coil.sln.dep vcproj
	$(top_srcdir)/build/slntool.py     \
		--vcversion VC9            \
		--dep coil.sln.dep \
		--out coil_vc9.sln \
		`find ./ -name '*_vc9.vcproj'`
	qkc -ms coil_vc9.sln

