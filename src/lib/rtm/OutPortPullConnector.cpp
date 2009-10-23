// -*- C++ -*-
/*!
 * @file OutPortPullConnector.cpp
 * @brief OutPortPull type connector class
 * @date $Date$
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2009
 *     Noriaki Ando
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id$
 *
 */

#include <rtm/OutPortPullConnector.h>
#include <rtm/OutPortProvider.h>

namespace RTC
{
  OutPortPullConnector::OutPortPullConnector(ConnectorInfo info,
                                             OutPortProvider* provider,
                                             CdrBufferBase* buffer)
    : OutPortConnector(info),
      m_provider(provider), m_buffer(buffer)
  {
  }

  OutPortPullConnector::~OutPortPullConnector()
  {
    disconnect();
  }
  
  ConnectorBase::ReturnCode
  OutPortPullConnector::write(const cdrMemoryStream& data)
  {
    m_buffer->write(data);
    return PORT_OK;
  }
  
  ConnectorBase::ReturnCode OutPortPullConnector::disconnect()
  {
    // delete provider
    //    OutPortProviderFactory& factory(OutPortProviderFactory::instance());
    //    factory.deleteObject(m_buffer);
    
    return PORT_OK;
  }

  /*!
   * @if jp
   * @brief Buffer を所得する
   *
   * Connector が保持している Buffer を返す
   *
   * @else
   * @brief Getting Buffer
   *
   * This operation returns this connector's buffer
   *
   * @endif
   */
  CdrBufferBase* OutPortPullConnector::getBuffer()
  {
    return m_buffer;
  }

};

