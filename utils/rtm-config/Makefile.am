## -*- Makefile -*-
##---------------------------------------------------------------------------
## Makefile for rtm-config: rtm configuration information viewer
##
## $Id$
##---------------------------------------------------------------------------

AUTOMAKE_OPTIONS = 1.4

ORB = @ORB@
IDLC = @IDLC@
IDLFLAGS = @IDL_FLAGS@

pkgconfigdir = @pkgconfigdir@
pkgconfig_DATA = libRTM.pc

bin_SCRIPTS = rtm-config

rtm-config: rtm-config.in
	echo '#!/bin/sh' > $@
	echo '' >> $@
	echo 'rtm_prefix="'${prefix}'"' >> $@
	echo 'rtm_exec_prefix="'${exec_prefix}'"' >> $@
	echo 'rtm_cxx="'${CXX}'"' >> $@
	echo 'rtm_cflags="'${CXXFLAGS}' -I'${prefix}'/include -I'${prefix}'/include/rtm/idl"' >> $@
	echo 'rtm_libs="'${LDFLAGS}' -L'${prefix}'/lib '${LIBS}' -lRTC"' >> $@
	echo 'rtm_libdir="'${pkglibdir}'"' >> $@
	echo 'rtm_version="'${RTM_VERSION}'"' >> $@
	echo 'rtm_orb="'${ORB}'"' >> $@
	echo 'rtm_idlc="'${IDLC}'"' >> $@
	echo 'rtm_idlflags="'${IDLFLAGS}'"' >> $@
	cat rtm-config.in >> $@
	chmod 755 $@

EXTRA_DIST = rtm-config.in

clean-local:
	rm -f libRTM.pc
	rm -f rtm-config
	rm -rf *~ *core
