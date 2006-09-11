// -*- C++ -*-
/*!
 * @file RtcLifeCycle.cpp
 * @brief RTC Life Cycle management interface
 * @date $Date: 2006-09-11 19:05:04 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: RtcLifeCycle.cpp,v 1.1 2006-09-11 19:05:04 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 *
 */

#include "rtm/RtcLifeCycle.h"

namespace RTC
{
  LifeCycle_impl::LifeCycle_impl(CORBA::ORB_ptr orb,
					 PortableServer::POA_ptr poa)
    : m_varORB(orb), m_varPOA(poa),
      m_preState(RTC::CREATED_STATE),
      m_curState(RTC::CREATED_STATE),
      m_nxtState(RTC::CREATED_STATE)
  {
  }


  ReturnCode_t LifeCycle_impl::initialize()
  {
    if (m_curState != RTC::CREATED_STATE)
      {
	return RTC::PRECONDITION_NOT_MET;
      }
    else
      {
	m_nxtState = RTC::INACTIVE_STATE;
      }

    return RTC::OK;
  }


  ReturnCode_t LifeCycle_impl::finalize()
  {
    return RTC::OK;
  }


  ReturnCode_t LifeCycle_impl::reset()
  {
    return RTC::OK;
  }


  ReturnCode_t LifeCycle_impl::exit()
  {
    return RTC::OK;
  }


  CORBA::Boolean LifeCycle_impl::is_alive()
  {
    return true;
  }
};
