## -*- Makefile -*-
##------------------------------------------------------------
## Makefile.am for deb package
##
## $Id$
##------------------------------------------------------------

#
# Debian package control files
#
# the following files are constant
# - README.Debian
# - changelog
# - compat
# - control
# - copyright
# - dirs
# - docs
# - rules         
#
# the following files shoud be generated at make-dist
# - files
#
# Package build process
#
# 1. edit "changelog" file with appropriate package version number
#    like "1.1.0-2." This version number will be used for actual 
#    deb package files.
#
# 2. Check permissions of the parent directory of distribution sourcecode
#    extracted directory. (ex. parent of OpenRTM-aist-1.0.0)
#    Package build script create deb packages there.
#
# 3. Run package build script debpkg_build.sh
#    This script do everithings.
#

AUTOMAKE_OPTIONS = 1.4

PKGVER=`head -n 1 changelog | sed 's/.*(\([0-9\.\-]*\).*/\1/'`

all-local: ${EXTRA_DIST} files
	sh dpkg_build.sh

files: changelog
	echo "openrtm-aist_"${PKGVER}"_amd64.deb main extra" > files
	echo "openrtm-aist-dev_"${PKGVER}"_amd64.deb main extra" >> files
	echo "openrtm-aist-example_"${PKGVER}"_amd64.deb main extra" >> files
	echo "openrtm-aist-doc_"${PKGVER}"_all.deb main extra" >> files

clean-local:
	rm -f *~
	rm -f files

EXTRA_DIST = \
	README.Debian \
	changelog     \
	compat        \
	control       \
	copyright     \
	dirs          \
	docs          \
	rules         \
	dpkg_build.sh
