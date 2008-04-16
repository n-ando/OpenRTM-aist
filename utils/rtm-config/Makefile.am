## -*- Makefile -*-
##---------------------------------------------------------------------------
## Makefile for rtm-config: rtm configuration information viewer
##
## $Id$
##
## $Log: not supported by cvs2svn $
## Revision 1.1.1.1  2005/05/12 09:06:18  n-ando
## Public release.
##
##---------------------------------------------------------------------------

##
##  Process this file with automake to create Makefile.in
##

AUTOMAKE_OPTIONS = 1.4

ORB = @ORB@
IDLC = @IDLC@
IDLFLAGS = @IDL_FLAGS@

bin_SCRIPTS = rtm-config

rtm-config: rtm-config.in
	echo '#!/bin/sh' > $@
	echo '' >> $@
	echo 'rtm_prefix="'${prefix}'"' >> $@
	echo 'rtm_exec_prefix="'${exec_prefix}'"' >> $@
	echo 'rtm_cflags="'${CXXFLAGS}' -I'${prefix}'/include/rtm/idl"' >> $@
	echo 'rtm_libs="'${LDFLAGS}' -L'${prefix}'/lib '${LIBS}' -lRTC"' >> $@
	echo 'rtm_libdir="'${pkglibdir}'"' >> $@
	echo 'rtm_version="'${VERSION}'"' >> $@
	echo 'rtm_orb="'${ORB}'"' >> $@
	echo 'rtm_idlc="'${IDLC}'"' >> $@
	echo 'rtm_idlflags="'${IDLFLAGS}'"' >> $@
	cat rtm-config.in >> $@
	chmod 755 $@

EXTRA_DIST = rtm-config.in

clean-local:
	rm -rf rtm-config *~ *core
