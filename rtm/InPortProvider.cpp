// -*- C++ -*-
/*!
 * @file  InPortProvider.h
 * @brief InPortProvider class
 * @date  $Date: 2007-01-06 17:53:37 $
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
 * $Id: InPortProvider.cpp,v 1.1 2007-01-06 17:53:37 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 */

#include <rtm/InPortProvider.h>
#include <iostream>

namespace RTC
{
  
  void InPortProvider::publishInterfaceProfile(SDOPackage::NVList& prop)
  {
    NVUtil::appendStringValue(prop, "dataport.data_type",
			      m_dataType.c_str());
    NVUtil::appendStringValue(prop, "dataport.interface_type",
			      m_interfaceType.c_str());
    NVUtil::appendStringValue(prop, "dataport.dataflow_type",
			      m_dataflowType.c_str());
    NVUtil::appendStringValue(prop, "dataport.subscription_type",
			      m_subscriptionType.c_str());
  }


  void InPortProvider::publishInterface(SDOPackage::NVList& prop)
  {
    if (!NVUtil::isStringValue(prop,
			       "dataport.interface_type",
			       m_interfaceType.c_str()))
      {
	return;
      }

    NVUtil::append(prop, m_properties);
  }


  void InPortProvider::setDataType(const char* data_type)
  {
    m_dataType = data_type;
  }


  void InPortProvider::setInterfaceType(const char* interface_type)
  {
    m_interfaceType = interface_type;
  }


  void InPortProvider::setDataFlowType(const char* dataflow_type)
  {
    m_dataflowType = dataflow_type;
  }


  void InPortProvider::setSubscriptionType(const char* subs_type)
  {
    m_subscriptionType = subs_type;
  }

}; // namespace RTC
