// -*- C++ -*-
/*!
 * @file  InPortProvider.h
 * @brief InPortProvider class
 * @date  $Date: 2007-12-31 03:08:03 $
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
 * $Id: InPortProvider.cpp,v 1.2.4.1 2007-12-31 03:08:03 n-ando Exp $
 *
 */

#include <rtm/InPortProvider.h>
#include <iostream>

namespace RTC
{
  /*!
   * @if jp
   * @brief デストラクタ
   * @else
   * @brief Destructor
   * @endif
   */
  InPortProvider::~InPortProvider()
  {
  }
  
  /*!
   * @if jp
   * @brief InterfaceProfile情報を公開する
   * @else
   * @brief Publish InterfaceProfile information
   * @endif
   */
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
  
  /*!
   * @if jp
   * @brief Interface情報を公開する
   * @else
   * @brief Publish Interface information
   * @endif
   */
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
  
  /*!
   * @if jp
   * @brief データタイプを設定する
   * @else
   * @brief Set the data tape
   * @endif
   */
  void InPortProvider::setDataType(const char* data_type)
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
  void InPortProvider::setInterfaceType(const char* interface_type)
  {
    m_interfaceType = interface_type;
  }
  
  /*!
   * @if jp
   * @brief データフロータイプを設定する
   * @else
   * @brief Set the dataflow type
   * @endif
   */
  void InPortProvider::setDataFlowType(const char* dataflow_type)
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
  void InPortProvider::setSubscriptionType(const char* subs_type)
  {
    m_subscriptionType = subs_type;
  }
}; // namespace RTC
