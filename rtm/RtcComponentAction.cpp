// -*- C++ -*-
/*!
 * @file RtcComponentAction.h
 * @brief Component Action Callback Interface
 * @date $Date: 2006-09-11 19:04:47 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: RtcComponentAction.cpp,v 1.1 2006-09-11 19:04:47 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 *
 */

#include "rtm/RtcComponentAction.h"

namespace RTC
{
  ComponentAction_impl::ComponentAction_impl(CORBA::ORB_ptr orb,
					     PortableServer::POA_ptr poa)
    : m_varORB(orb), m_varPOA(poa)
  {
  }
  ReturnCode_t ComponentAction_impl::on_initialize()
  {
    return RTC::OK;
  }

  ReturnCode_t ComponentAction_impl::on_finalize()
  {
    return RTC::OK;
  }


  ReturnCode_t ComponentAction_impl::on_startup(RTC::ExecutionContext exec_context)
  {
    return RTC::OK;
  }


  ReturnCode_t ComponentAction_impl::on_shutdown(RTC::ExecutionContext exec_context)
  {
    return RTC::OK;
  }


  ReturnCode_t ComponentAction_impl::on_activated(RTC::ExecutionContext exec_context)
  {
    return RTC::OK;
  }


  ReturnCode_t ComponentAction_impl::on_deactivated(RTC::ExecutionContext exec_context)
  {
    return RTC::OK;
  }


  ReturnCode_t ComponentAction_impl::on_aborting(RTC::ExecutionContext exec_context)
  {
    return RTC::OK;
  }


  ReturnCode_t ComponentAction_impl::on_error(RTC::ExecutionContext exec_context)
  {
    return RTC::OK;
  }


  ReturnCode_t ComponentAction_impl::on_reset(RTC::ExecutionContext exec_context)
  {
    return RTC::OK;
  }
};
