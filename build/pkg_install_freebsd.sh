#!/bin/sh
#
# @file pkg_install_freebsd6.sh
# @brief OpenRTM-aist dependent packages install script for FreeBSD-6
# @author Noriaki Ando <n-ando@aist.go.jp>
#
# $Id: pkg_install_freebsd6.sh 726 2008-05-14 03:05:42Z n-ando $
#

PACKAGEROOT='ftp://ftp.jp.freebsd.org'
export PACKAGEROOT

omni="omniORB"
omniorbpy="py24-omniorb py24-tkinter"
ace="ace+tao"
autotools="autoconf259 automake19 libtool"
packages="$omni $ace"

#----------------------------------------
# root かどうかをチェック
#----------------------------------------
check_root () {
    if test ! `id -u` = 0 ; then
	echo ""
	echo "This script should be run by root user."
	echo "Abort."
	echo ""
	exit 1
    fi
}

#----------------------------------------
# パッケージインストール関数
#----------------------------------------
install_packages () {
    for p in $*; do
	ins=`rpm -qa $p`
	if test "x$ins" = "x"; then
	    echo "Now installing: " $p
	    pkg_add -r install $p
	    echo "done."
	    echo ""
	else
	    echo $p "is already installed."
	    echo ""
	fi
    done
}

#------------------------------------------------------------
# リストを逆順にする
#------------------------------------------------------------
reverse () {
    for i in $*; do
	echo $i
    done | sed '1!G;h;$!d'
}

#----------------------------------------
# パッケージをアンインストールする
#----------------------------------------
uninstall_packages () {
    for p in $*; do
	echo "Now uninstalling: " $p
	pkg_delete $p
	echo "done."
	echo ""
    done
}

#---------------------------------------
# メイン
#---------------------------------------
check_root
if test "x$1" = "x-u" ; then
    uninstall_packages `reverse $packages`
else
    create_repo
    install_packages $packages
fi
