#!/bin/sh
#
# @brief Preparing OpenRTM-aist build environment on Windows
# @author Noriaki Ando <n-ando@aist.go.jp>
#         Copyright 2014 (C) All Right Reserved
#
# This is part of build.bat omniORB build batch file
# for building omniORB for Windows binaries.
#
# The following environment variables should be set.
#
# OMNI_VERSION (= 4.1.7, ...)
# OMNITH_VER (= 3.4, ...)
# PYTHON_DIR (= /cygdrive/c/Python27)
# VC_VERSION  (= 9, 10, ...)
# ARCH (= x86 or x64)
#
export PATH=/cygdrive/c/cygwin64/bin:$PATH
echo `pwd`

check_env()
{

    if test "x$ARCH" = "xx86" ;then
        WIN_ARCH="win32"
    elif test "x$ARCH" = "xx86_64" ;then
        WIN_ARCH="win64"
    else
        echo "ARCH not defined"
        exit -1
    fi
    if test "x$VC_VERSION" = "x" ; then
        echo "VC_VERSION not defined."
        exit -1
    fi
    if test "x$OMNI_VERSION" = "x" ; then
        echo "OMNI_VERSION not defined."
        exit -1
    else
        OMNI_SHORT_VER=`echo $OMNI_VERSION | sed 's/\.//g'`
    fi
    if test "x$OMNITH_VER" = "x" ; then
        echo "OMNITH_VER not defined."
        exit -1
    else
        OMNITH_SHORT_VER=`echo $OMNITH_VER | sed 's/\.//g'`
    fi
    if test "xPYTHON_DIR" = "x" ; then
        echo "PYTHON_DIR not defined."
        exit -1
    else
        PY_VERSION=`echo ${PYTHON_DIR} | sed 's/.*ython\([0-9][0-9]\).*/\1/'`
    fi
    base_url="http://openrtm.org/pub/omniORB/win32/omniORB-${OMNI_VERSION}/"

    OMNIORB_ZIP=omniORB-${OMNI_VERSION}-${WIN_ARCH}-vc${VC_VERSION}-py${PY_VERSION}.zip
    OMNIORB_URL=${base_url}/${OMNIORB_ZIP}
}

unpack_omnibin()
{
    # getting omniORB-4.1.7.tar.bz2
    if test ! -f $OMNIORB_ZIP ; then
        wget $OMNIORB_URL
    fi
    unzip $OMNIORB_ZIP
}

unpack_openrtm()
{
    OPENRTM_ZIP=`ls OpenRTM-aist*.zip`
    if test "x$OPENRTM_ZIP" = "x" ; then
        echo "OpenRTM-aist ZIP file not found."
        exit 1
    fi
    unzip $OPENRTM_ZIP
}

copy_props()
{
    OpenRTM-aist/etc/rtm_config_omniorb415.vcprops OpenRTM-aist/rtm_config.vcprops
    OpenRTM-aist/etc/rtm_config_omniorb415.props   OpenRTM-aist/rtm_config.props

    sed -i "s/415/$OMNI_SHORT_VER/g" OpenRTM-aist/rtm_config.vcprops
    sed -i "s/34/$OMNITH_SHORT_VER/g" OpenRTM-aist/rtm_config.vcprops
    sed -i "s/415/$OMNI_SHORT_VER/g" OpenRTM-aist/rtm_config.props
    sed -i "s/34/$OMNITH_SHORT_VER/g" OpenRTM-aist/rtm_config.props
}
check_env
unpack_omnibin
unpack_openrtm


# end of ecript
#==============================
