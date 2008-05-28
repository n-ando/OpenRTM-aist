#!/bin/sh
#
# @file pkg_install_debianSarge.sh
# @brief OpenRTM-aist dependent packages install script for Debian-sarge
# @author Noriaki Ando <n-ando@aist.go.jp> and Shinji Kurihara
#

#---------------------------------------
# パッケージリスト
#---------------------------------------
omni="libomniorb4 libomniorb4-de omniidl4 omniorb4-nameserver"
ace="libace libace-dev"
openrtm="python-yaml"
devel="gcc g++ make"
packages="$devel $omni $ace $openrtm"

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
	echo "Now installing: " $p
	apt-get install $p
	echo "done."
	echo ""
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
	aptitude remove $p
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
    install_packages $packages
fi

