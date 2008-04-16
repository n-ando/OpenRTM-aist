#!/bin/sh
#
# @file pkg_install_freebsd6.sh
# @brief OpenRTM-aist dependent packages install script for FreeBSD-6
# @author Noriaki Ando <n-ando@aist.go.jp>
#
# $Id$
#
# $Log: not supported by cvs2svn $
# Revision 1.2  2006/11/04 16:35:47  n-ando
# Autotools installation was added.
#
# Revision 1.1  2006/07/18 08:36:32  n-ando
# OpenRTM-aist dependent packages install script for FreeBSD 6.0.
#
#

PACKAGEROOT='ftp://ftp.jp.freebsd.org'
export PACKAGEROOT

ace="ace+tao-5.4.2+1.4.2"
ace_pkg="ace+tao"

boost="boost-1.32.0_2"
boost_pkg="boost"

boost_python="boost-python-1.32.0_2"
boost_python_pkg="boost-python"

omniorb="omniORB-4.0.6"
omniorb_pkg="omniORB"

omniorbpy="py24-omniorb-2.6"
omniorbpy_pkg="py24-omniorb"

tkinter="py24-tkinter-2.4.1_1"
tkinter_pkg="py24-tkinter"

autoconf="autoconf-2.59_2"
autoconf_pkg="autoconf259"

automake="automake-1.9.6"
automake_pkg="automake19"

libtool="libtool-1.5.22_2"
libtool_pkg="libtool"


pkg_install () {
    echo '------------------------------------------------------------'
    echo 'Checking OpenRTM-aist dependent package:' $1
    if ! pkg_info -e $1 ; then
	echo $1 'is not installed.'
	echo 'Downloading' $2'.tgz from' $PACKAGEROOT', and installing'
	echo ''
	pkg_add -r $2
    else
	echo $1 'is already installed.'
    fi
}

pkg_uninstall () {
    echo '------------------------------------------------------------'
    if ! pkg_info -e $1 ; then
	echo $1 'is not installed.'
    else
	echo 'Uninstalling ' $1
	pkg_delete $1
    fi
}

pkg_install_all () {
    pkg_install $autoconf $autoconf_pkg
    pkg_install $automake $automake_pkg
    pkg_install $libtool  $libtool_pkg
    pkg_install $ace $ace_pkg
    pkg_install $boost $boost_pkg
    pkg_install $omniorb $omniorb_pkg
    pkg_install $omniorbpy $omniorbpy_pkg
    pkg_install $tkinter $tkinter_pkg
}


pkg_uninstall_all () {
    pkg_uninstall $ace $ace_pkg
    pkg_uninstall $boost $boost_pkg
    pkg_uninstall $omniorbpy $omniorbpy_pkg
    pkg_uninstall $omniorb $omniorb_pkg
    pkg_uninstall $tkinter $tkinter_pkg
    pkg_uninstall $libtool  $libtool_pkg
    pkg_uninstall $automake $automake_pkg
    pkg_uninstall $autoconf $autoconf_pkg
}

if test "x$1" = "x-u" ; then
    pkg_uninstall_all
else
    pkg_install_all
fi

