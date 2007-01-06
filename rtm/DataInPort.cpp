// -*- C++ -*-
/*!
 * @file DataInPort.cpp
 * @brief Base class of InPort
 * @date $Date: 2007-01-06 17:43:32 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006
 *     Noriaki Ando
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: DataInPort.cpp,v 1.3 2007-01-06 17:43:32 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.2  2006/12/02 18:25:30  n-ando
 * A trivial fix.
 *
 * Revision 1.1  2006/11/27 09:44:35  n-ando
 * The first commitment.
 *
 *
 */

#include <rtm/DataInPort.h>
#include <rtm/CORBA_SeqUtil.h>
#include <rtm/NVUtil.h>
#include <iostream>

namespace RTC
{
  //============================================================
  // protected interfaces
  //============================================================
  ReturnCode_t
  DataInPort::publishInterfaces(ConnectorProfile& connector_profile)
  {    
    std::for_each(m_providers.begin(), m_providers.end(),
		  publish(connector_profile.properties));

    return RTC::OK;
  }
  
  ReturnCode_t
  DataInPort::subscribeInterfaces(const ConnectorProfile& connector_profile)
  {
    std::for_each(m_consumers.begin(), m_consumers.end(),
		  subscribe(connector_profile.properties));
    return RTC::OK;
  }

  void
  DataInPort::unsubscribeInterfaces(const ConnectorProfile& connector_profile)
  {
    std::for_each(m_consumers.begin(), m_consumers.end(),
		  unsubscribe(connector_profile.properties));
  }

};
