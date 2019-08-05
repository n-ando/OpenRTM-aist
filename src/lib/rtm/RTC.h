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

#ifndef RTC_H
#define RTC_H

#include <rtm/config_rtc.h>

#ifdef ORB_IS_MICO
#include <CORBA.h>
#include <coss/CosNaming.h>
#include <rtm/idl/RTC.h>
#endif

#ifdef ORB_IS_TAO
#include <tao/corba.h>
#include <orbsvcs/CosNamingC.h>
#include <rtm/idl/DataPortSkel.h>
#include <rtm/idl/DataPort_OpenRTMSkel.h>
#endif

#ifdef ORB_IS_RTORB
#include <RtORB/cdrStream.h>
#endif  // ORB_IS_RTORB

#ifdef ORB_IS_OMNIORB

#include <omniORB4/CORBA.h>
#include <omnithread.h>

#endif  // ORB_IS_OMNIORB

#include <rtm/idl/OpenRTMSkel.h>

#ifdef RTC_CORBA_CXXMAPPING11
#define RefCountServantBase ServantBase
#endif

// for Windows DLL export
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#   define DLL_EXPORT __declspec(dllexport)
BOOL WINAPI DllMain (HINSTANCE hinstDll, DWORD fdwReason, LPVOID lpvReserved);
#else
#   define DLL_EXPORT
#   define WINAPI
#endif /* Windows */

#ifdef ORB_IS_ORBEXPRESS
#include <CosNaming.h>
#endif


#include <coil/Properties.h>

namespace RTC
{
  using Properties = coil::Properties;

} // namespace RTC


#endif  // RTC_H
