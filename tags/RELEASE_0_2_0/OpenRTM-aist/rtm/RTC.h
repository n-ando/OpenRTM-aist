// -*- C++ -*-
/*!
 * @file RTC.h
 * @brief RTComponent header
 * @date $Date: 2005-05-12 09:06:18 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2003-2005
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: RTC.h,v 1.1.1.1 2005-05-12 09:06:18 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
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
//#include <omniORB4/CORBA.h>
//#include <omnithread.h>
#endif


#include <ace/Thread_Manager.h>
#include <boost/lexical_cast.hpp>

#endif // RTC_h
