// -*- C++ -*-
/*!
 * @file  PublisherFlush.cpp
 * @brief PublisherFlush class
 * @date  $Date: 2007-12-31 03:08:06 $
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
 * $Id$
 *
 */

#include <coil/Properties.h>
#include <rtm/RTC.h>
#include <rtm/PublisherBase.h>
#include <rtm/PublisherFlush.h>
#include <rtm/InPortConsumer.h>

namespace RTC
{
  /*!
   * @if jp
   * @brief コンストラクタ
   * @else
   * @brief Constructor
   * @endif
   */
  PublisherFlush::PublisherFlush()
    : m_consumer(0), m_active(false)
  {
  }

  /*!
   * @if jp
   * @brief デストラクタ
   * @else
   * @brief Destructor
   * @endif
   */
  PublisherFlush::~PublisherFlush()
  {
    // "consumer" should be deleted in the Connector
    m_consumer = 0;
  }
  
  /*!
   * @if jp
   * @brief 初期化
   * @else
   * @brief initialization
   * @endif
   */
  PublisherBase::ReturnCode PublisherFlush::init(coil::Properties& prop)
  {
    return PORT_OK;
  }

  /*!
   * @if jp
   * @brief InPortコンシューマのセット
   * @else
   * @brief Store InPort consumer
   * @endif
   */
  PublisherBase::ReturnCode PublisherFlush::setConsumer(InPortConsumer* consumer)
  {
    if (consumer == 0) { return INVALID_ARGS; }
    if (m_consumer != 0) { delete m_consumer; }
    m_consumer = consumer;
    return PORT_OK;
  }

  /*!
   * @if jp
   * @brief バッファのセット
   * @else
   * @brief Setting buffer pointer
   * @endif
   */
  PublisherBase::ReturnCode PublisherFlush::setBuffer(CdrBufferBase* buffer)
  {
    return PORT_ERROR;
  }

  PublisherBase::ReturnCode PublisherFlush::write(const cdrMemoryStream& data,
                                                  unsigned long sec,
                                                  unsigned long usec)
  {
    //    if (!m_active) { return PRECONDITION_NOT_MET; }

    m_consumer->put(data);

    return PORT_OK;
  }

  bool PublisherFlush::isActive()
  {
    return m_active;
  }

  PublisherBase::ReturnCode PublisherFlush::activate()
  {
    if ( m_active) { return PRECONDITION_NOT_MET; }

    m_active = true;

    return PORT_OK;
  }

  PublisherBase::ReturnCode PublisherFlush::deactivate()
  {
    if (!m_active) { return PRECONDITION_NOT_MET; }

    m_active = false;

    return PORT_OK;
  }
 


}; // namespace RTC


extern "C"
{
  void PublisherFlushInit()
  {
    ::RTC::PublisherFactory::
      instance().addFactory("flush",
                            ::coil::Creator< ::RTC::PublisherBase,
                                             ::RTC::PublisherFlush>,
                            ::coil::Destructor< ::RTC::PublisherBase,
                                                ::RTC::PublisherFlush>);
  }
};

