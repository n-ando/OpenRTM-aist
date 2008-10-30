// -*- C++ -*-
/*!
 * @file RTC.h
 * @brief RTComponent header
 * @date $Date: 2008-02-29 04:57:44 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2003-2005
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id$
 *
 */

#ifndef RTC_h
#define RTC_h

#include "rtm/config_rtc.h"

#ifdef ORB_IS_MICO
#include <CORBA.h>
#include <coss/CosNaming.h>
#include <rtm_corba/idl/RTC.h>
#endif

#ifdef ORB_IS_TAO
#include <tao/corba.h>
#include <orbsvcs/CosNamingC.h>
#endif

#ifdef ORB_IS_OMNIORB
#undef PACKAGE_BUGREPORT
#undef PACKAGE_NAME
#undef PACKAGE_STRING
#undef PACKAGE_TARNAME
#undef PACKAGE_VERSION
#undef PACKAGE_TARNAME
#include <omniORB4/CORBA.h>
#include <omnithread.h>
#endif

#include "rtm_corba/idl/OpenRTMSkel.h"

#ifdef RTC_CORBA_CXXMAPPING11
#define RefCountServantBase ServantBase
#endif

// for Windows DLL export 
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#   define DLL_EXPORT __declspec(dllexport)
// #   define usleep(x) Sleep(x/1000);
#   define LINE_MAX 256
BOOL WINAPI DllMain (HINSTANCE hinstDll, DWORD fdwReason, LPVOID lpvReserved);
#else 
#   define DLL_EXPORT 
#   define WINAPI
#endif /* Windows */





#endif // RTC_h
