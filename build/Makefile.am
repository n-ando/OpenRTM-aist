## -*- Makefile -*-
##------------------------------------------------------------
## @file   Makefile.am
## @brief  Makefile.am for build tools
## @author Noriaki Ando <n-ando@aist.go.jp>
##
## $Id$
##
## $Log: not supported by cvs2svn $
## Revision 1.6.2.1  2007/07/20 15:29:04  n-ando
## Modified for win32 porting.
##
## Revision 1.6  2007/04/27 03:28:29  n-ando
## Some package installer script was added.
##
## Revision 1.5  2007/04/24 01:23:57  n-ando
## pkg_install_fc6.sh was added.
##
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
	chmod 755                  \
	autogen                    \
	codegen.py                 \
	distbuild.sh               \
	yat.py                     \
	makedeffile.py             \
	makevcproj.py              \
	makewrapper.pl             \
	makewrapper.py             \
	pickupprojs.py             \
	pkg_install_debianSarge.sh \
	pkg_install_fc4.sh         \
	pkg_install_fc5.sh         \
	pkg_install_fc6.sh         \
	pkg_install_freebsd52.sh   \
	pkg_install_freebsd6.sh    \
	pkg_install_vl32.sh        \
	pkg_install_vl4.sh         \
	setuptest.py               \
	uuid.py

dist-hook: all

EXTRA_DIST =                       \
	README.Debian              \
	autogen                    \
	codegen.py                 \
	distbuild.sh               \
	yat.py                     \
	makedeffile.py             \
	makevcproj.py              \
	makewrapper.pl             \
	makewrapper.py             \
	pickupprojs.py             \
	pkg_install_debianSarge.sh \
	pkg_install_fc4.sh         \
	pkg_install_fc5.sh         \
	pkg_install_fc6.sh         \
	pkg_install_freebsd52.sh   \
	pkg_install_freebsd6.sh    \
	pkg_install_vl32.sh        \
	pkg_install_vl4.sh         \
	setuptest.py               \
	uuid.py


clean-local:
	rm -f *.pyc *~