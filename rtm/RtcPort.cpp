// -*- C++ -*-
/*!
 * @file RTObject.cpp
 * @brief RT component base class
 * @date $Date: 2006-09-11 19:05:21 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: RtcPort.cpp,v 1.1 2006-09-11 19:05:21 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 *
 */

#include "rtm/RtcPort.h"

namespace RTC
{

  Port_impl::Port_impl(CORBA::ORB_ptr orb, PortableServer::POA_ptr poa)
    : m_varORB(orb), m_varPOA(poa)
  {

  }

  PortProfile* Port_impl::get_port_profile()
  {
    PortProfile_var prof(&m_portProfile);
    return prof._retn();
  }


  ConnectorProfileList* Port_impl::get_connector_profiles()
  {
    ConnectorProfileList_var conn_prof(&m_connectorProfiles);
    return conn_prof._retn();
  }


  ConnectorProfile* Port_impl::get_connector_profile(const char* connector_id)
  {
    try
      {
	ConnectorProfile conn;
	conn = m_connectorProfiles.find(connector_name(connector_id));
	ConnectorProfile_var conn_prof(&conn);
	return conn_prof._retn();
      }
    catch (...)
      {
	//	throw InternalError("Port_impl::get_connector_profile()");
      }
    return new ConnectorProfile();
  }


  ReturnCode_t Port_impl::connect(const ConnectorProfile& connector_profile)
  {
    try
      {
	m_connectorProfiles.push_back(connector_profile);
      }
    catch (...)
      {
	return RTC::ERROR;
      }
    return RTC::OK;
  }


  ReturnCode_t Port_impl::disconnect(const char* connector_id)
  {
    return RTC::OK;
  }


  ReturnCode_t Port_impl::disconnect_all()
  {
    return RTC::OK;
  }

};
