// -*- C++ -*-
/*!
 * @file ExtTrigExecutionContext.h
 * @brief ExtTrigExecutionContext class
 * @date $Date: 2007-04-26 15:29:39 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2007
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: ExtTrigExecutionContext.h,v 1.2 2007-04-26 15:29:39 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.1  2007/04/13 16:08:24  n-ando
 * External Triggered ExecutionContext class.
 *
 */

#ifndef ExtTrigExecutionContext_h
#define ExtTrigExecutionContext_h

#include <rtm/RTC.h>

#include <ace/Task.h>
#include <ace/Synch.h>

#include <rtm/Manager.h>
#include <rtm/PeriodicExecutionContext.h>

namespace RTC
{
  class ExtTrigExecutionContext
    : public virtual PeriodicExecutionContext
  {
  public:
    ExtTrigExecutionContext();
    virtual ~ExtTrigExecutionContext();
    virtual void tick();
    virtual int svc(void);

  private:
    struct Worker
    {
      Worker() : _cond(_mutex), _called(false) {};
      ACE_Thread_Mutex _mutex;
      ACE_Condition<ACE_Thread_Mutex> _cond;
      bool _called;
    };
    // A condition variable for external triggered worker
    Worker m_worker;

  };
};

extern "C"
{
  void ExtTrigExecutionContextInit(RTC::Manager* manager);
};

#endif // ExtTrigExecutionContext_h

