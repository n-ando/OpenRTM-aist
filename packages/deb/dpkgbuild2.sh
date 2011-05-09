#!/bin/sh 

openrtm_deb_readme () {
cat <<'EOF'
openrtm-aist for Debian
-----------------------
Debian package of OpenRTM-aist

 -- Noriaki Ando <n-ando@aist.go.jp>  Mon, 23 Jun 2008 16:18:55 +0900
EOF
} 

openrtm_deb_changelog () {
cat <<'EOF'
openrtm-aist (1.1.0-0) unstable; urgency=low

  * 1.0.0-2 (1.0.0-RELEASE). A bug (rtcprof not included) has been fixed.
 -- Noriaki Ando <n-ando@aist.go.jp>  Thu, 28 May 2010 16:58:44 +0900

  * 1.0.0-1 (1.0.0-RELEASE).
 -- Noriaki Ando <n-ando@aist.go.jp>  Thu, 28 May 2010 16:58:44 +0900

  * 1.0.0-0 (1.0.0-RC1).
 -- Noriaki Ando <n-ando@aist.go.jp>  Thu, 28 May 2009 11:58:55 +0900

  * Initial release.
 -- Noriaki Ando <n-ando@aist.go.jp>  Mon, 23 Jun 2008 16:18:55 +0900
EOF
}

openrtm_deb_compat () {
cat <<EOF
4
EOF
}

openrtm_deb_control () {
cat<<'EOF'
Source: openrtm-aist
Section: main
Priority: extra
Maintainer: Noriaki Ando <n-ando@aist.go.jp>
Build-Depends: debhelper, omniidl4, python
Standards-Version: 3.7.2

Package: openrtm-aist
Architecture: any
Depends: ${shlibs:Depends}, ${misc:Depends}
Description: OpenRTM-aist, RT-Middleware distributed by AIST
 OpenRTM-aist is a reference implementation of RTC (Robotic Technology 
 Component) specification which is OMG standard. OpenRTM-aist includes
 RT-Middleware runtime environment and RTC framework. The OMG standard
 defines a component model and certain important infrastructure services
 applicable to the domain of robotics software development.
 OpenRTM-aist is being developed and distributed by 
 Task Intelligence Research Group, Intelligent Systems Research Institute, 
 National Institute of Advanced Industrial Science and Technology (AIST), Japan. 
 Please see http://www.openrtm.org/ for more detail. 

Package: openrtm-aist-dev
Architecture: any
Depends: openrtm-aist
Description: OpenRTM-aist headers for development
 The header files and libraries needed for developing programs using
 OpenRTM-aist.

Package: openrtm-aist-example
Architecture: any
Depends: openrtm-aist
Description: OpenRTM-aist examples
 Example components and sources

Package: openrtm-aist-doc
Architecture: all
Description: Documentation for openrtm-aist
 Developer documentation.
EOF
}

openrtm_deb_copyright () {
cat <<'EOF'
This package was debianized by Noriaki Ando <n-ando@aist.go.jp> on
Mon, 23 Jun 2008 16:18:55 +0900.

It was downloaded from <http://www.openrtm.org>

Upstream Author(s): 

    Noriaki Ando <n-ando@aist.go.jp>

Copyright: 

    Copyright (C) 2003-2010
    Noriaki Ando and the OpenRTM-aist Project team
    Intelligent Systems Research Institute,
    National Institute of Advanced Industrial Science and Technology (AIST),
    Tsukuba, Japan, All rights reserved.

License:

    The OpenRTM-aist is the dual-licensed open source software. You can
    use, copy, distribute and/or modify this library under the terms and
    conditions of either of the licenses below.
    
    1) EPL (Eclipse Public License - v 1.0)
    See
    http://www.eclipse.org/legal/epl-v10.html
    http://www.eclipse.org/org/documents/epl-v10.php
    or
    COPYING.LIB.
    
    2) Individual Licnese
    You can purchase license from AIST and/or AIST's TLO to copy,
    distribute, modify and/or sublicense the library without any
    limitation in the terms of LGPL. The individual license should be
    concluded with a negotiated agreement between you and AIST and/or AIST
    TLO. To conclude individual license, contact the person responsible of
    AIST.

# Please also look if there are files or directories which have a
# different copyright/license attached and list them here.
EOF
}

openrtm_deb_dirs () {
cat <<EOF
usr/bin
usr/sbin
EOF
}

openrtm_deb_docs () {
cat <<EOF
NEWS
README
README.jp
EOF
}

openrtm_deb_files () {
cat <<EOF
openrtm-aist_1.1.0-0_amd64.deb main extra
openrtm-aist-dev_1.1.0-0_amd64.deb main extra
openrtm-aist-example_1.1.0-0_amd64.deb main extra
openrtm-aist-doc_1.1.0-0_all.deb main extra
EOF
}

openrtm_deb_rules () {
cat <<'EOF'
#!/usr/bin/make -f
# -*- makefile -*-
# Sample debian/rules that uses debhelper.
#
# This file was originally written by Joey Hess and Craig Small.
# As a special exception, when this file is copied by dh-make into a
# dh-make output file, you may use that output file without restriction.
# This special exception was added by Craig Small in version 0.37 of dh-make.
#
# Modified to make a template file for a multi-binary package with separated
# build-arch and build-indep targets  by Bill Allombert 2001

# Uncomment this to turn on verbose mode.
#export DH_VERBOSE=1

# This has to be exported to make some magic below work.
export DH_OPTIONS

# These are used for cross-compiling and for saving the configure script
# from having to guess our platform (since we know it already)
DEB_HOST_GNU_TYPE   ?= $(shell dpkg-architecture -qDEB_HOST_GNU_TYPE)
DEB_BUILD_GNU_TYPE  ?= $(shell dpkg-architecture -qDEB_BUILD_GNU_TYPE)


CFLAGS = -Wall -g

ifneq (,$(findstring noopt,$(DEB_BUILD_OPTIONS)))
	CFLAGS += -O0
else
	CFLAGS += -O2
endif

config.status: configure
	dh_testdir
	# Add here commands to configure the package.
ifneq "$(wildcard /usr/share/misc/config.sub)" ""
	cp -f /usr/share/misc/config.sub config.sub
endif
ifneq "$(wildcard /usr/share/misc/config.guess)" ""
	cp -f /usr/share/misc/config.guess config.guess
endif
	./configure --host=$(DEB_HOST_GNU_TYPE) --build=$(DEB_BUILD_GNU_TYPE) --prefix=/usr --mandir=\$${prefix}/share/man --infodir=\$${prefix}/share/info CFLAGS="$(CFLAGS)" LDFLAGS="-Wl,-z,defs"


#Architecture 
build: build-arch build-indep

build-arch: build-arch-stamp
build-arch-stamp:  config.status

	# Add here commands to compile the arch part of the package.
	#$(MAKE) 
	touch $@

build-indep: build-indep-stamp
build-indep-stamp:  config.status

	# Add here commands to compile the indep part of the package.
	#$(MAKE) doc
	touch $@

clean:
	dh_testdir
	dh_testroot
	rm -f build-arch-stamp build-indep-stamp #CONFIGURE-STAMP#

	# Add here commands to clean up after the build process.
	# -$(MAKE) distclean
	#rm -f config.sub config.guess

	dh_clean 

install: install-indep install-arch
install-indep:
	dh_testdir
	dh_testroot
	dh_clean -k -i 
	dh_installdirs -i

	# Add here commands to install the indep part of the package into
	# debian/<package>-doc.
	#INSTALLDOC#
	# for openrtm-aist-doc package
	(cd $(CURDIR)/docs ; $(MAKE) DESTDIR=$(CURDIR)/debian/openrtm-aist-doc install)

	dh_install -i

install-arch:
	dh_testdir
	dh_testroot
	dh_clean -k -s 
	dh_installdirs -s

	# Add here commands to install the arch part of the package into 
	# debian/tmp.
	$(MAKE)

	# for openrtm-aist package
	(cd $(CURDIR)/src/lib/coil/posix     ; $(MAKE) DESTDIR=$(CURDIR)/debian/openrtm-aist install-exec)
	(cd $(CURDIR)/src/lib/rtm      ; $(MAKE) DESTDIR=$(CURDIR)/debian/openrtm-aist install-exec)
	(cd $(CURDIR)/etc              ; $(MAKE) DESTDIR=$(CURDIR)/debian/openrtm-aist install-exec)
	(cd $(CURDIR)/utils/rtcd       ; $(MAKE) DESTDIR=$(CURDIR)/debian/openrtm-aist install)
	(cd $(CURDIR)/utils/rtcprof    ; $(MAKE) DESTDIR=$(CURDIR)/debian/openrtm-aist install)
	(cd $(CURDIR)/utils/rtm-naming ; $(MAKE) DESTDIR=$(CURDIR)/debian/openrtm-aist install)

	# for openrtm-dev package
	#$(MAKE)
	(cd $(CURDIR)/src/lib/rtm           ; $(MAKE) DESTDIR=$(CURDIR)/debian/openrtm-aist-dev install-data-recursive)
	(cd $(CURDIR)/src/lib/coil          ; $(MAKE) DESTDIR=$(CURDIR)/debian/openrtm-aist-dev install-data)
	(cd $(CURDIR)/utils/rtc-template    ; $(MAKE) DESTDIR=$(CURDIR)/debian/openrtm-aist-dev install)
	(cd $(CURDIR)/utils/rtm-skelwrapper ; $(MAKE) DESTDIR=$(CURDIR)/debian/openrtm-aist-dev install)
	(cd $(CURDIR)/utils/rtm-config      ; $(MAKE) DESTDIR=$(CURDIR)/debian/openrtm-aist-dev install)
	(cd $(CURDIR)/src/lib/coil/utils/coil-config      ; $(MAKE) DESTDIR=$(CURDIR)/debian/openrtm-aist-dev install)

	# for openrtm-aist-example package
	#$(MAKE)
	(cd $(CURDIR)/src/lib/coil     ; $(MAKE) DESTDIR=$(CURDIR)/debian/openrtm-aist-example install-exec)
	(cd $(CURDIR)/src/lib/rtm      ; $(MAKE) DESTDIR=$(CURDIR)/debian/openrtm-aist-example install-exec)
	(cd $(CURDIR)/examples         ; $(MAKE) DESTDIR=$(CURDIR)/debian/openrtm-aist-example install)
	(cd $(CURDIR)/src/lib/rtm      ; $(MAKE) DESTDIR=$(CURDIR)/debian/openrtm-aist-example uninstall)
	(cd $(CURDIR)/src/lib/coil     ; $(MAKE) DESTDIR=$(CURDIR)/debian/openrtm-aist-example uninstall)

	dh_install -s
# Must not depend on anything. This is to be called by
# binary-arch/binary-indep
# in another 'make' thread.
binary-common:
	dh_testdir
	dh_testroot
	dh_installchangelogs ChangeLog
	dh_installdocs
	dh_installexamples
#	dh_installmenu
#	dh_installdebconf	
#	dh_installlogrotate	
#	dh_installemacsen
#	dh_installpam
#	dh_installmime
#	dh_python
#	dh_installinit
#	dh_installcron
#	dh_installinfo
	dh_installman
	dh_link
	dh_strip
	dh_compress 
	dh_fixperms
#	dh_perl
	dh_makeshlibs
	dh_installdeb
	dh_shlibdeps
	dh_gencontrol
	dh_md5sums
	dh_builddeb
# Build architecture independant packages using the common target.
binary-indep: build-indep install-indep
	$(MAKE) -f debian/rules DH_OPTIONS=-i binary-common

# Build architecture dependant packages using the common target.
binary-arch: build-arch install-arch
	$(MAKE) -f debian/rules DH_OPTIONS=-s binary-common

binary: binary-arch binary-indep
.PHONY: build clean binary-indep binary-arch binary install install-indep install-arch 

EOF
}


export PATH=/usr/local/bin:/usr/bin:/bin:/usr/X11R6/bin:/usr/local/X11R6/bin:/usr/local/sbin:/usr/sbin:/sbin
export LANG=C
export LC_ALL=C

# date
date=`date "+%y%m%d%H%M"`
time=/usr/bin/time
# package location and build directory
package=/usr/users/builder/PackageBuild/src/OpenRTM-aist-1.1.0-RELEASE.tar.gz
packagedir=OpenRTM-aist-1.1.0
package_date=`ls -al $package | awk '{printf("%s/%s %s\n",$6,$7,$8);}'`
package_date=`diff -ac $package /dev/null | head -1 |awk '{print $3,$4,$5,$6,$7,$8;}'`
package_name=`basename $package`
buildroot=/usr/users/builder/PackageBuild

logheader="<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 3.2 Final//EN\"><html><body><pre>"
logfooter="</pre></body></html>"

# system information
hostname=`hostname`
os=`uname -s`
release=`uname -r`-`uname -p`

dist_name=""
dist_key=""
# Check the lsb distribution name
if test -f /etc/lsb-release ; then
    . /etc/lsb-release
    if test "x$DISTRIB_DESCRIPTION" != "x" ; then
	dist_name=$DISTRIB_DESCRIPTION-`uname -m`
	dist_key=$DISTRIB_ID
    fi
fi
# Check the Fedora version
if test "x$dist_name" = "x" && test -f /etc/fedora-release ; then
    dist_name=`cat /etc/fedora-release`-`uname -m`
    dist_key=`sed -e 's/.[^0-9]*\([0-9]\).*/fc\1/' /etc/fedora-release`
fi
#Check the Debian version
if test "x$dist_name" = "x" && test -f /etc/debian_version ; then
    dist_name="Debian"`cat /etc/debian_version`-`uname -m`
    dist_key="Debian"
fi
# Check the Vine version
if test "x$dist_name" = "x" && test -f /etc/vine-release ; then
    dist_name=`cat /etc/vine-release`-`uname -m`
    dist_key=`sed -e 's/.*\([0-9]\)\.\([0-9]\).*/vl\1\2/' /etc/vine-release`
fi
# Check the TuboLinux version
if test "x$dist_name" = "x" && test -f /etc/turbolinux-release ; then
    dist_name=`cat /etc/tubolinux-release`-`uname -m`
    dist_key=""
fi

if test "x$dist_name" = "x" ; then
    dist_name=$os$release
fi
# Check the RedHat/Fedora version
if test "x$dist_name" = "x" && test -f /etc/redhat-release ; then
    dist_name=`cat /etc/redhat-release`-`uname -m`
fi

# only fedora and vine
if test ! "x$dist_key" = "xDebian" -a ! "x$dist_key" = "xUbuntu" ; then
    echo $dist_key
    echo "This is not debian/ubuntu"
    exit 0
fi

echo $dist_key

distname=`echo $dist_name | sed 's/[ |\(|\)]//g'`
# system dependent build directory and log file name
builddir=$buildroot/$distname
timestamp=$buildroot/.$distname
logfile=$distname-$date.log

build=""
echo $dist_key
# check package
if test -f $package ; then
    echo "Package found: " $package
else
    echo "Package not found: " $pacakge
    exit 1
fi
cd $buildroot

# check if package is new
if test -f $timestamp ; then
    if test $package -nt $timestamp ; then
	build=yes
	echo "New source file was found."
        touch $timestamp
    fi
else
    echo "Timestamp not found."
    touch $timestamp
    build=yes
fi

if test "x$build" = "x" ; then
    echo "No new package."
    exit 1
fi

# cleanup 
echo "cleanup " $builddir/$packagedir
rm -rf $builddir

mkdir -p $builddir
cd $builddir

echo "distribution: " $dist_name >> $buildroot/$logfile
echo "package: $package_date " >> $buildroot/$logfile


#------------------------------------------------------------
# package build process
#------------------------------------------------------------
echo $logheader > $buildroot/make-$logfile

tar xvzf $package
mkdir $packagedir/debian
openrtm_deb_readme    > $packagedir/debian/README.Debian
openrtm_deb_changelog > $packagedir/debian/changelog
openrtm_deb_compat    > $packagedir/debian/compat
openrtm_deb_control   > $packagedir/debian/control
openrtm_deb_copyright > $packagedir/debian/copyright
openrtm_deb_dirs      > $packagedir/debian/dirs
openrtm_deb_docs      > $packagedir/debian/docs
openrtm_deb_files     > $packagedir/debian/files
chmod 444 $packagedir/debian/files
openrtm_deb_rules     > $packagedir/debian/rules
chmod 755 $packagedir/debian/rules

cd $packagedir

if $time -p -o make_time-$logfile dpkg-buildpackage -W -us -uc -rfakeroot >> $buildroot/make-$logfile 2>&1 ; then
    echo $logfooter >> $buildroot/make-$logfile
    make_time=`awk '/real/{printf("%s[s] ", $0);}' make_time-$logfile`
    echo "make: OK" >> $buildroot/$logfile
    echo "make_time: $make_time" >> $buildroot/$logfile
    rm -f make_time-$logfile
else
    echo "make: NG" >> $buildroot/$logfile
    rm -f make_time-$logfile
    exit 1
fi

