/*! -*- C++ -*-
 *
 * @file OutPortPushConnector.cpp
 * @brief OutPortPush type connector class
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

#include <rtm/OutPortPushConnector.h>

namespace RTC
{
  /*!
   * @if jp
   * @brief コンストラクタ
   * @else
   * @brief Constructor
   * @endif
   */
  OutPortPushConnector::OutPortPushConnector(Profile profile, 
                                             InPortConsumer* consumer,
                                             CdrBufferBase* buffer)
    : OutPortConnector(profile),
      m_consumer(consumer), m_publisher(0), m_buffer(buffer)
  {
    rtclog.setLevel("PARANOID");

    // publisher/buffer creation. This may throw std::bad_alloc;
    m_publisher = createPublisher(profile);
    if (m_buffer == 0)
      {
        m_buffer = createBuffer(profile);
      }
    if (m_publisher == 0 || m_buffer == 0) { throw std::bad_alloc(); }

    if (m_publisher->init(profile.properties) != PORT_OK)
      {
        throw std::bad_alloc();
      }
    m_consumer->init(profile.properties);

    m_publisher->setConsumer(m_consumer);
    m_publisher->setBuffer(m_buffer);
  }

  /*!
   * @if jp
   * @brief デストラクタ
   * @else
   * @brief Destructor
   * @endif
   */
  OutPortPushConnector::~OutPortPushConnector()
  {
    disconnect();
  }

  /*!
   * @if jp
   * @brief データの書き込み
   * @else
   * @brief Writing data
   * @endif
   */
  ConnectorBase::ReturnCode
  OutPortPushConnector::write(const cdrMemoryStream& data)
  {
    RTC_TRACE(("write()"));
    RTC_PARANOID(("data size = %d bytes", data.bufSize()));

    return m_publisher->write(data, 0, 0);
  }

  /*!
   * @if jp
   * @brief 接続解除
   * @else
   * @brief disconnect
   * @endif
   */
  ConnectorBase::ReturnCode OutPortPushConnector::disconnect()
  {
    RTC_TRACE(("disconnect()"));
    // delete publisher
    if (m_publisher != 0)
      {
        RTC_DEBUG(("delete publisher"));
        PublisherFactory& pfactory(PublisherFactory::instance());
        pfactory.deleteObject(m_publisher);
      }
    m_publisher = 0;
    
    // delete consumer
    if (m_consumer != 0)
      {
        RTC_DEBUG(("delete consumer"));
        InPortConsumerFactory& cfactory(InPortConsumerFactory::instance());
        cfactory.deleteObject(m_consumer);
      }
    m_consumer = 0;

    // delete buffer
    if (m_buffer != 0)
      {
        RTC_DEBUG(("delete buffer"));
        CdrBufferFactory& bfactory(CdrBufferFactory::instance());
        bfactory.deleteObject(m_buffer);
      }
    m_buffer = 0;
    RTC_TRACE(("disconnect() done"));
    return PORT_OK;
  }

    void OutPortPushConnector::activate()
    {
      m_publisher->activate();
    }

    void OutPortPushConnector::deactivate()
    {
      m_publisher->deactivate();
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
    CdrBufferBase* OutPortPushConnector::getBuffer()
    {
      return m_buffer;
    }

  /*!
   * @if jp
   * @brief Publisherの生成
   * @else
   * @brief create publisher
   * @endif
   */
  PublisherBase* OutPortPushConnector::createPublisher(Profile& profile)
  {
    std::string pub_type;
    pub_type = profile.properties.getProperty("subscription_type",
                                              "flush");
    return PublisherFactory::instance().createObject(pub_type);
  }
  
  /*!
   * @if jp
   * @brief Bufferの生成
   * @else
   * @brief create buffer
   * @endif
   */
  CdrBufferBase* OutPortPushConnector::createBuffer(Profile& profile)
  {
    std::string buf_type;
    buf_type = profile.properties.getProperty("buffer_type",
                                              "ring_buffer");
    return CdrBufferFactory::instance().createObject(buf_type);
  }

};

