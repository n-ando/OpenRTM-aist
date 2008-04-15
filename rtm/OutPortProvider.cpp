// -*- C++ -*-
/*!
 * @file  OutPortProvider.cpp
 * @brief OutPortProvider class
 * @date  $Date: 2007-12-31 03:08:05 $
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
 * $Id: OutPortProvider.cpp,v 1.2.4.1 2007-12-31 03:08:05 n-ando Exp $
 *
 */

#include <rtm/OutPortProvider.h>

namespace RTC
{
  /*!
   * @if jp
   * @brief InterfaceProfile情報を公開する
   * @else
   * @brief Publish InterfaceProfile information
   * @endif
   */
  void OutPortProvider::publishInterfaceProfile(SDOPackage::NVList& prop)
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
  
  /*!
   * @if jp
   * @brief Interface情報を公開する
   * @else
   * @brief Publish interface information
   * @endif
   */
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
  
  /*!
   * @if jp
   * @brief ポートタイプを設定する
   * @else
   * @brief Set the port type
   * @endif
   */
  void OutPortProvider::setPortType(const char* port_type)
  {
    m_portType = port_type;
  }
  
  /*!
   * @if jp
   * @brief データタイプを設定する
   * @else
   * @brief Set the data type
   * @endif
   */
  void OutPortProvider::setDataType(const char* data_type)
  {
    m_dataType = data_type;
  }
  
  /*!
   * @if jp
   * @brief インターフェースタイプを設定する
   * @else
   * @brief Set the interface type
   * @endif
   */
  void OutPortProvider::setInterfaceType(const char* interface_type)
  {
    m_interfaceType = interface_type;
  }
  
  /*!
   * @if jp
   * @brief データフロータイプを設定する
   * @else
   * @brief Set the data flow type
   * @endif
   */
  void OutPortProvider::setDataFlowType(const char* dataflow_type)
  {
    m_dataflowType = dataflow_type;
  }
  
  /*!
   * @if jp
   * @brief サブスクリプションタイプを設定する
   * @else
   * @brief Set the subscription type
   * @endif
   */
  void OutPortProvider::setSubscriptionType(const char* subs_type)
  {
    m_subscriptionType = subs_type;
  }
}; // namespace RTC
