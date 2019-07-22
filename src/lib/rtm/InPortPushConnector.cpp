// -*- C++ -*-
/*!
 * @file InPortPushConnector.cpp
 * @brief InPortPush type connector class
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

#include <rtm/InPortPushConnector.h>
#include <rtm/InPortProvider.h>
#include <rtm/ConnectorListener.h>

#include <string>

namespace RTC
{
  /*!
   * @if jp
   * @brief コンストラクタ
   * @else
   * @brief Constructor
   * @endif
   */
  InPortPushConnector::InPortPushConnector(ConnectorInfo info,
                                           InPortProvider* provider,
                                           ConnectorListeners& listeners,
                                           CdrBufferBase* buffer)
    : InPortConnector(info, listeners, buffer),
      m_provider(provider),
      m_listeners(listeners),
      m_deleteBuffer(buffer == nullptr),
      m_sync_readwrite(false)
  {
    if (m_buffer == nullptr)
      {
        m_buffer = createBuffer(info);
      }
    if (m_buffer == nullptr || m_provider == nullptr) { throw std::bad_alloc(); }

    m_buffer->init(info.properties.getNode("buffer"));
    m_provider->init(info.properties);
    m_provider->setBuffer(m_buffer);
    m_provider->setListener(info, &m_listeners);

    if (coil::toBool(info.properties["sync_readwrite"], "YES", "NO", false))
    {
        m_sync_readwrite = true;
    }

    m_marshaling_type = info.properties.getProperty("marshaling_type", "corba");
    m_marshaling_type = info.properties.getProperty("in.marshaling_type", m_marshaling_type);
    coil::eraseBothEndsBlank(m_marshaling_type);
    

    onConnect();
  }

  /*!
   * @if jp
   * @brief デストラクタ
   * @else
   * @brief Destructor
   * @endif
   */
  InPortPushConnector::~InPortPushConnector()
  {
    onDisconnect();
    disconnect();
  }

  /*!
   * @if jp
   * @brief データの読み出し
   * @else
   * @brief Reading data
   * @endif
   */
  ConnectorBase::ReturnCode
  InPortPushConnector::read(ByteDataStreamBase* data)
  {
    RTC_TRACE(("read()"));
    /*
     * buffer returns
     *   BUFFER_OK
     *   BUFFER_EMPTY
     *   TIMEOUT
     *   PRECONDITION_NOT_MET
     */
    if (m_buffer == nullptr)
      {
        return PRECONDITION_NOT_MET;
      }
    if (m_sync_readwrite)
    {
    
        {
            std::lock_guard<std::mutex> guard(m_readcompleted_worker.mutex_);
            m_readcompleted_worker.completed_ = false;
        }

        {
            std::lock_guard<std::mutex> guard(m_readready_worker.mutex_);
            m_readready_worker.completed_ = true;
            m_readready_worker.cond_.notify_one();
        }
        {
            std::unique_lock<std::mutex> guard(m_writecompleted_worker.mutex_);
            while (!m_writecompleted_worker.completed_)
            {
                m_writecompleted_worker.cond_.wait(guard);
            }
        }
    }
    ByteData tmp;
    BufferStatus ret = m_buffer->read(tmp);
    data->writeData(tmp.getBuffer(), tmp.getDataLength());

    if (m_sync_readwrite)
    {
        {
            std::lock_guard<std::mutex> guard(m_readcompleted_worker.mutex_);
            m_readcompleted_worker.completed_ = true;
            m_readcompleted_worker.cond_.notify_one();
        }

        {
            std::lock_guard<std::mutex> guard(m_readready_worker.mutex_);
            m_readready_worker.completed_ = false;
        }
    }

    switch (ret)
      {
      case BufferStatus::OK:
        onBufferRead(tmp);
        return PORT_OK;
        break;
      case BufferStatus::EMPTY:
        onBufferEmpty(tmp);
        return BUFFER_EMPTY;
        break;
      case BufferStatus::TIMEOUT:
        onBufferReadTimeout(tmp);
        return BUFFER_TIMEOUT;
        break;
      case BufferStatus::PRECONDITION_NOT_MET:
        return PRECONDITION_NOT_MET;
        break;
      default:
        return PORT_ERROR;
      }
  }

  /*!
   * @if jp
   * @brief 接続解除
   * @else
   * @brief disconnect
   * @endif
   */
  ConnectorBase::ReturnCode InPortPushConnector::disconnect()
  {
    RTC_TRACE(("disconnect()"));
    // delete provider
    if (m_provider != nullptr)
      {
        InPortProviderFactory& cfactory(InPortProviderFactory::instance());
        cfactory.deleteObject(m_provider);
      }
    m_provider = nullptr;

    // delete buffer
    if (m_buffer != nullptr && m_deleteBuffer)
      {
        CdrBufferFactory& bfactory(CdrBufferFactory::instance());
        bfactory.deleteObject(m_buffer);
      }
    m_buffer = nullptr;

    return PORT_OK;
  }

  /*!
   * @if jp
   * @brief Bufferの生成
   * @else
   * @brief create buffer
   * @endif
   */
  CdrBufferBase* InPortPushConnector::createBuffer(ConnectorInfo& info)
  {
    std::string buf_type;
    buf_type = info.properties.getProperty("buffer_type",
                                              "ring_buffer");
    return CdrBufferFactory::instance().createObject(buf_type);
  }

  /*!
   * @if jp
   * @brief 接続確立時にコールバックを呼ぶ
   * @else
   * @brief Invoke callback when connection is established
   * @endif
   */
  void InPortPushConnector::onConnect()
  {
    m_listeners.connector_[ON_CONNECT].notify(m_profile);
  }

  /*!
   * @if jp
   * @brief 接続切断時にコールバックを呼ぶ
   * @else
   * @brief Invoke callback when connection is destroied
   * @endif
   */
  void InPortPushConnector::onDisconnect()
  {
    m_listeners.connector_[ON_DISCONNECT].notify(m_profile);
  }

  BufferStatus InPortPushConnector::write(ByteData &cdr)
  {
      if (m_sync_readwrite)
      {
          {
              std::unique_lock<std::mutex> guard(m_readready_worker.mutex_);
              while (!m_readready_worker.completed_)
              {
                  m_readready_worker.cond_.wait(guard);
              }
          }
      }

      

      BufferStatus ret = m_buffer->write(cdr);

      if (m_sync_readwrite)
      {
          {
              std::lock_guard<std::mutex> guard(m_writecompleted_worker.mutex_);
              m_writecompleted_worker.completed_ = true;
              m_writecompleted_worker.cond_.notify_one();
          }


          {
              std::unique_lock<std::mutex> guard(m_readcompleted_worker.mutex_);
              while (!m_readcompleted_worker.completed_)
              {
                  m_readcompleted_worker.cond_.wait(guard);
              }
          }
          {
              std::lock_guard<std::mutex> guard(m_writecompleted_worker.mutex_);
              m_writecompleted_worker.completed_ = false;
          }
      }


      return ret;
  }

} // namespace RTC

