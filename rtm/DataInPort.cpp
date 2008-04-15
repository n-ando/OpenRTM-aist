// -*- C++ -*-
/*!
 * @file DataInPort.cpp
 * @brief Base class of InPort
 * @date $Date: 2007-12-31 03:08:02 $
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
 * $Id: DataInPort.cpp,v 1.6.2.2 2007-12-31 03:08:02 n-ando Exp $
 *
 */

#include <rtm/DataInPort.h>
#include <rtm/CORBA_SeqUtil.h>
#include <rtm/NVUtil.h>
#include <iostream>
#include <algorithm>

namespace RTC
{
  /*!
   * @if jp
   * @brief Interface公開用Functor
   * @else
   * @brief Functor to publish the interface
   * @endif
   */
  struct DataInPort::publish
  {
    publish(SDOPackage::NVList& prop) : m_prop(prop) {}
    void operator()(InPortProvider* provider)
    {
      provider->publishInterface(m_prop);
    }
    SDOPackage::NVList& m_prop;
  };
  
  /*!
   * @if jp
   * @brief Interface接続用Functor
   * @else
   * @brief Functor to subscribe the interface
   * @endif
   */
  struct DataInPort::subscribe
  {
    subscribe(const SDOPackage::NVList& prop) : m_prop(prop) {}
    void operator()(OutPortConsumer* consumer)
    {
      consumer->subscribeInterface(m_prop);
    }
    const SDOPackage::NVList& m_prop;
  };
  
  /*!
   * @if jp
   * @brief Interface接続解除用Functor
   * @else
   * @brief Functor to unsubscribe the interface
   * @endif
   */
  struct DataInPort::unsubscribe
  {
    unsubscribe(const SDOPackage::NVList& prop) : m_prop(prop) {}
    void operator()(OutPortConsumer* consumer)
    {
      consumer->unsubscribeInterface(m_prop);
    }
    const SDOPackage::NVList& m_prop;
  };
  
  /*!
   * @if jp
   * @brief デストラクタ
   * @else
   * @brief Destructor
   * @endif
   */
  DataInPort::~DataInPort()
  {
  }
  
  //============================================================
  // protected interfaces
  //============================================================
  
  /*!
   * @if jp
   * @brief Interface情報を公開する
   * @else
   * @brief Publish interface information
   * @endif
   */
  ReturnCode_t
  DataInPort::publishInterfaces(ConnectorProfile& connector_profile)
  {    
    if (m_dummy.size() != 1)
      {
	std::cerr << "Memory access violation was detected." << std::endl;
	std::cerr << "dummy.size(): " << m_dummy.size() << std::endl;
	std::cerr << "size() should be 1." << std::endl;
      }
    std::for_each(m_providers.begin(), m_providers.end(),
		  publish(connector_profile.properties));
    
    return RTC::RTC_OK;
  }
  
  /*!
   * @if jp
   * @brief Interfaceに接続する
   * @else
   * @brief Subscribe to the interface
   * @endif
   */
  ReturnCode_t
  DataInPort::subscribeInterfaces(const ConnectorProfile& connector_profile)
  {
    std::for_each(m_consumers.begin(), m_consumers.end(),
		  subscribe(connector_profile.properties));
    return RTC::RTC_OK;
  }
  
  /*!
   * @if jp
   * @brief Interfaceへの接続を解除する
   * @else
   * @brief Disconnect the interface connection
   * @endif
   */
  void
  DataInPort::unsubscribeInterfaces(const ConnectorProfile& connector_profile)
  {
    std::for_each(m_consumers.begin(), m_consumers.end(),
		  unsubscribe(connector_profile.properties));
  }
  
};
