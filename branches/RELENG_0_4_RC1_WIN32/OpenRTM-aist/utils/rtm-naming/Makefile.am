## -*- Makefile -*-
##---------------------------------------------------------------------------
## Makefile.am for rtm-naming: name service wrapper script
##
## $Id: Makefile.am,v 1.1.1.1 2005-05-12 09:06:19 n-ando Exp $
##
## $Log: not supported by cvs2svn $
##---------------------------------------------------------------------------

AUTOMAKE_OPTIONS = 1.4

COSNAMES = @COSNAMES@
ORB = @ORB@

bin_SCRIPTS = rtm-naming

rtm-naming: rtm-naming.in
	echo '#!/bin/sh' > $@
	echo '' >> $@
	echo 'cosnames="'${COSNAMES}'"' >> $@
	echo 'orb="'${ORB}'"' >> $@
	cat rtm-naming.in >> $@
	chmod 755 $@

EXTRA_DIST = rtm-naming.in

clean-local:
	rm -rf rtm-naming *~ *core
