## -*- Makefile -*-
##------------------------------------------------------------
## @file   Makefile.am
## @brief  Makefile.am for build tools
## @author Noriaki Ando <n-ando@aist.go.jp>
##
## $Id: Makefile.am,v 1.5 2007-04-24 01:23:57 n-ando Exp $
##
## $Log: not supported by cvs2svn $
## Revision 1.4  2007/01/21 14:02:21  n-ando
## Scripts' permission is explicitly controled now.
##
## Revision 1.3  2006/11/28 00:54:43  n-ando
## clean-local target was added to remove *.pyc, *~
##
## Revision 1.2  2006/11/04 16:20:42  n-ando
## The following file entries were added to EXTRA_DIST.
## - ezt.py
## - pkg_install_fc4.sh, pkg_install_fc5.sh
## - pkg_install_freebsd52, pkg_install_freebsd6.sh
##
## Revision 1.1.1.1  2005/05/12 09:06:18  n-ando
## Public release.
##
##------------------------------------------------------------

AUTOMAKE_OPTIONS = 1.9

all:
	chmod 755                \
	autogen		         \
	makewrapper.py	         \
	makewrapper.pl	         \
	pkg_install_fc4.sh       \
	pkg_install_fc5.sh       \
	pkg_install_fc6.sh       \
	pkg_install_freebsd52.sh \
	pkg_install_freebsd6.sh  \
	codegen.py               \
	setuptest.py

EXTRA_DIST =                     \
	autogen		         \
	makewrapper.py	         \
	makewrapper.pl	         \
	ezt.py		         \
	pkg_install_fc4.sh       \
	pkg_install_fc5.sh       \
	pkg_install_fc6.sh       \
	pkg_install_freebsd52.sh \
	pkg_install_freebsd6.sh  \
	codegen.py               \
	setuptest.py

clean-local:
	rm -f *.pyc *~