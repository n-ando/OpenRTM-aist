// -*- C++ -*-
/*!
 * @file InPortPullConnector.cpp
 * @brief InPortPull type connector class
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

#include <rtm/InPortPullConnector.h>
#include <rtm/OutPortConsumer.h>

namespace RTC
{
  /*!
   * @if jp
   * @brief コンストラクタ
   * @else
   * @brief Constructor
   * @endif
   */
  InPortPullConnector::InPortPullConnector(Profile profile,
                                           OutPortConsumer* consumer,
                                           CdrBufferBase* buffer)
    : InPortConnector(profile, buffer), m_consumer(consumer)
  {
    if (buffer == 0)
      {
        m_buffer = createBuffer(m_profile);
      }
    if (m_buffer == 0 || m_consumer==0)
      {
        throw std::bad_alloc();
        return;
      }
    m_consumer->setBuffer(m_buffer);
  }
  
  /*!
   * @if jp
   * @brief デストラクタ
   * @else
   * @brief Destructor
   * @endif
   */
  InPortPullConnector::~InPortPullConnector()
  {
    disconnect();
  }
  
  /*!
   * @if jp
   * @brief read 関数
   *
   * Buffer からデータを InPort へ read する関数
   *
   * @else
   * @brief Destructor
   *
   * The read function to read data from buffer to InPort
   *
   * @endif
   */
  ConnectorBase::ReturnCode
  InPortPullConnector::read(cdrMemoryStream& data)
  {
    if (m_buffer == 0)
      {
        return PORT_ERROR;
      }
    m_buffer->write(data);
    return PORT_OK;
  }
  
  /*!
   * @if jp
   * @brief 接続解除関数
   *
   * Connector が保持している接続を解除する
   *
   * @else
   * @brief Disconnect connection
   *
   * This operation disconnect this connection
   *
   * @endif
   */
  ConnectorBase::ReturnCode InPortPullConnector::disconnect()
  {
    // delete provider
    //    InPortProviderFactory& factory(InPortProviderFactory::instance());
    //    factory.deleteObject(m_buffer);
    
    return PORT_OK;
  }
  
  /*!
   * @if jp
   * @brief Bufferの生成
   * @else
   * @brief create buffer
   * @endif
   */
  CdrBufferBase* InPortPullConnector::createBuffer(Profile& profile)
  {
    std::string buf_type;
    buf_type = profile.properties.getProperty("buffer_type",
                                              "ring_buffer");
    return CdrBufferFactory::instance().createObject(buf_type);
  }
};

