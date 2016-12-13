#!/bin/sh
#
# @file pkg_install_freebsd52.sh
# @brief OpenRTM-aist dependent packages install script for FreeBSD-5.2
# @author Noriaki Ando <n-ando@aist.go.jp>
#
# $Id: pkg_install_freebsd52.sh,v 1.1 2006-07-18 08:36:22 n-ando Exp $
#
# $Log: not supported by cvs2svn $
#

PACKAGEROOT='ftp://ftp.jp.freebsd.org'
export PACKAGEROOT

ace="ace+tao-5.4.1+1.4.1"
ace_pkg="ace+tao"

boost="boost-1.30.2"
boost_pkg="boost"

boost_python="boost-python-1.32.2"
boost_python_pkg="boost-python"

omniorb="omniORB-4.0.2"
omniorb_pkg="omniORB"

omniorbpy="py23-omniorb-2.2"
omniorbpy_pkg="py23-omniorb"

tkinter="py23-tkinter-2.3.2_1"
tkinter_pkg="py23-tkinter"


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
}

if test "x$1" = "x-u" ; then
	pkg_uninstall_all
else
	pkg_install_all
fi

