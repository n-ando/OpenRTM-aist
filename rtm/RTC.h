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
 * $Id: RTC.h,v 1.5.2.3 2008-02-29 04:57:44 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.5.2.2  2008/01/13 07:52:44  n-ando
 * In case of using MICO, two RTC.h exists as rtm/RTC.h and rtm/idl/RTC.h.
 * Since the "#include <RTC.h>" only includes rtm/RTC.h, this file should
 * include rtm/idl/RTC.h in case of MICO.
 *
 * Revision 1.5.2.1  2007/07/20 16:05:14  n-ando
 * usleep definition for win32 porting.
 * Useless __declspec definitions were deleted.
 *
 * Revision 1.5  2007/04/13 18:14:41  n-ando
 * Now OpenRTMSkel.h is included.
 *
 * Revision 1.4  2007/01/21 10:38:54  n-ando
 * Some tirivial fixex.
 *
 * Revision 1.3  2006/10/17 19:12:01  n-ando
 * Modified to include omniORB4 CORBA/h header file.
 *
 * Revision 1.2  2005/05/16 05:49:10  n-ando
 * Some definitions (__declspec(dllexport), __declspec(dllimport) etc..)
 * were added for Windows ports.
 *
 * Revision 1.1.1.1  2005/05/12 09:06:18  n-ando
 * Public release.
 *
 *
 */

#ifndef RTC_h
#define RTC_h

#include "rtm/config_rtc.h"

#ifdef ORB_IS_MICO
#include <CORBA.h>
#include <coss/CosNaming.h>
#include <rtm/idl/RTC.h>
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
#include <omniORB4/CORBA.h>
#include <omnithread.h>
#endif

#ifdef RTC_CORBA_CXXMAPPING11
#define RefCountServantBase ServantBase
#endif

// for Windows DLL export 
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#   define DLL_EXPORT __declspec(dllexport)
#   define usleep(x) Sleep(x/1000);
#   define LINE_MAX 256
BOOL WINAPI DllMain (HINSTANCE hinstDll, DWORD fdwReason, LPVOID lpvReserved);
#else 
#   define DLL_EXPORT 
#   define WINAPI
#endif /* Windows */


#include "rtm/idl/OpenRTMSkel.h"


#endif // RTC_h
