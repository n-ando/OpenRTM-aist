// -*- C++ -*-
/*!
 * @file  OutPortProvider.h
 * @brief OutPortProvider class
 * @date  $Date: 2007-01-06 17:58:47 $
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
 * $Id: OutPortProvider.cpp,v 1.1 2007-01-06 17:58:47 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 *
 */


#include <rtm/OutPortProvider.h>

namespace RTC
{
  
  void OutPortProvider::publishInterfaceProfile(SDOPackage::NVList& prop)
  {
    NVUtil::appendStringValue(prop, "port.port_type",
			      m_portType.c_str());
    NVUtil::appendStringValue(prop, "dataport.data_type",
			      m_dataType.c_str());
    NVUtil::appendStringValue(prop, "dataport.interface_type",
			      m_interfaceType.c_str());
    NVUtil::appendStringValue(prop, "dataport.dataflow_type",
			      m_dataflowType.c_str());
    NVUtil::appendStringValue(prop, "dataport.subscription_type",
			      m_subscriptionType.c_str());
  }


  void OutPortProvider::publishInterface(SDOPackage::NVList& prop)
  {
    if (!NVUtil::isStringValue(prop,
			       "dataport.interface_type",
			       m_interfaceType.c_str()))
      {
	return;
      }

    NVUtil::append(prop, m_properties);
  }


  void OutPortProvider::setPortType(const char* port_type)
  {
    m_portType = port_type;
  }


  void OutPortProvider::setDataType(const char* data_type)
  {
    m_dataType = data_type;
  }


  void OutPortProvider::setInterfaceType(const char* interface_type)
  {
    m_interfaceType = interface_type;
  }


  void OutPortProvider::setDataFlowType(const char* dataflow_type)
  {
    m_dataflowType = dataflow_type;
  }


  void OutPortProvider::setSubscriptionType(const char* subs_type)
  {
    m_subscriptionType = subs_type;
  }

}; // namespace RTC
