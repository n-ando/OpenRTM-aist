// -*- C++ -*-
/*!
 * @file  OpenHRPExecutionContext.h
 * @brief Execution context for OpenHRP3
 * @date  $Date: 2008-01-14 07:49:59 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006-2008
 *     Noriaki Ando
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id$
 *
 */

#ifndef RTC_OPENHRPEXECUTIONCONTEXT_H
#define RTC_OPENHRPEXECUTIONCONTEXT_H

#include <rtm/RTC.h>

#include <coil/Task.h>

#include <rtm/Manager.h>
#include <rtm/PeriodicExecutionContext.h>

// for Windows DLL export 
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#   define DLL_EXPORT __declspec(dllexport)
#else 
#	define DLL_EXPORT 
#endif /* Windows */

#ifdef WIN32
#pragma warning( disable : 4290 )
#endif

namespace RTC
{
  /*!
   * @if jp
   * @class OpenHRPExecutionContext
   * @brief OpenHRPExecutionContext епеще╣
   *
   *
   * @else
   * @class OpenHRPExecutionContext
   * @brief OpenHRPExecutionContext class
   *
   *
   * @endif
   */
  class OpenHRPExecutionContext
    : public virtual PeriodicExecutionContext
  {
  public:
    OpenHRPExecutionContext();
    virtual ~OpenHRPExecutionContext(void);
    virtual void tick(void)
      throw (CORBA::SystemException);
    virtual int svc(void);

  private:
  };  // class OpenHRPExecutionContext
};  // namespace RTC

#ifdef WIN32
#pragma warning( default : 4290 )
#endif


extern "C"
{
  DLL_EXPORT void OpenHRPExecutionContextInit(RTC::Manager* manager);
};

#endif // RTC_OPENHRPEXECUTIONCONTEXT_H

