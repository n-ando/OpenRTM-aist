// -*- C++ -*-
/*!
 * @file RtcComponentAction.h
 * @brief Component Action Callback Interface
 * @date $Date: 2006-09-11 19:04:56 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: RtcComponentAction.h,v 1.1 2006-09-11 19:04:56 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 *
 */

#ifndef RtcComponentAction_h
#define RtcComponentAction_h

// CORBA header include
#include "rtm/RTC.h"
#include "rtm/Util.h"

// local includes
#include "rtm/idl/RTCSkel.h"

namespace RTC
{
  class ComponentAction_impl
    : public virtual POA_RTC::ComponentAction,
      public virtual PortableServer::RefCountServantBase
  {
  public:
    ComponentAction_impl(CORBA::ORB_ptr orb, PortableServer::POA_ptr poa);
    virtual ~ComponentAction_impl(){};
    virtual ReturnCode_t on_initialize();
    virtual ReturnCode_t on_finalize();
    virtual ReturnCode_t on_startup(RTC::ExecutionContext exec_context);
    virtual ReturnCode_t on_shutdown(RTC::ExecutionContext exec_context);
    virtual ReturnCode_t on_activated(RTC::ExecutionContext exec_context);
    virtual ReturnCode_t on_deactivated(RTC::ExecutionContext exec_context);
    virtual ReturnCode_t on_aborting(RTC::ExecutionContext exec_context);
    virtual ReturnCode_t on_error(RTC::ExecutionContext exec_context);
    virtual ReturnCode_t on_reset(RTC::ExecutionContext exec_context);
  protected:
    CORBA::ORB_var m_varORB;
    PortableServer::POA_var m_varPOA;

  };
};

#endif // RtcComponentAction_h

