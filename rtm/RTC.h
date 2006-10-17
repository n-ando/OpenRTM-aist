// -*- C++ -*-
/*!
 * @file RTC.h
 * @brief RTComponent header
 * @date $Date: 2006-10-17 19:12:01 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2003-2005
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: RTC.h,v 1.3 2006-10-17 19:12:01 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
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


#include <ace/Thread_Manager.h>
#include <boost/lexical_cast.hpp>


// for windows DLL
#ifdef WIN32

#ifdef DLLEXT
#define EXPORTS __declspec(dllexport)
#else  // DLLEXT
#define EXPORTS __declspec(dllimport)
#endif // DLLEXT

#define LINE_MAX 256
BOOL WINAPI DllMain (HINSTANCE hinstDll, DWORD fdwReason, LPVOID lpvReserved);

#else  // WIN32

#define EXPORTS
#define WINAPI

#endif // WIN32


#endif // RTC_h
