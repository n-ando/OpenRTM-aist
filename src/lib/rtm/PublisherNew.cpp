// -*- C++ -*-
/*!
 * @file  PublisherNew.cpp
 * @brief PublisherNew class
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

#include <iostream>
#include <assert.h>

#include <coil/Properties.h>
#include <coil/stringutil.h>

#include <rtm/RTC.h>
#include <rtm/PublisherNew.h>
#include <rtm/InPortConsumer.h>
#include <rtm/PeriodicTaskFactory.h>
#include <rtm/idl/DataPortSkel.h>

namespace RTC
{
  /*!
   * @if jp
   * @brief コンストラクタ
   * @else
   * @brief Constructor
   * @endif
   */
  PublisherNew::PublisherNew()
    : m_consumer(0), m_buffer(0), m_task(0),
      m_retcode(PORT_OK), m_pushPolicy(NEW),
      m_skipn(10), m_active(false)
  {
  }

  /*!
   * @if jp
   * @brief デストラクタ
   * @else
   * @brief Destructor
   * @endif
   */
  PublisherNew::~PublisherNew()
  {
    if (m_task != 0)
      {
        m_task->resume();
        m_task->finalize();
        //        m_task->wait();
        RTC::PeriodicTaskFactory::instance().deleteObject(m_task);
      }

    // "consumer" should be deleted in the Connector
    m_consumer = 0;
    // "buffer"   should be deleted in the Connector
    m_buffer = 0;
  }

  /*!
   * @if jp
   * @brief 初期化
   * @else
   * @brief initialization
   * @endif
   */
  PublisherBase::ReturnCode PublisherNew::init(coil::Properties& prop)
  {
    RTC::PeriodicTaskFactory& factory(RTC::PeriodicTaskFactory::instance());
    coil::vstring th = factory.getIdentifiers();
    std::cout << "vstring.size: " << th.size() << std::endl;
    for (int i(0); i < th.size(); ++i)
      {
        std::cout << "thread type: " << th[i] << std::endl;
      }
    m_task = factory.createObject(prop.getProperty("thread_type", "default"));
    if (m_task == 0)
      {
        std::cout << "PeriodicTask creation failed" << std::endl;
        return INVALID_ARGS;
      }

    coil::Properties& mprop(prop.getNode("measurement"));

    m_task->setTask(this, &PublisherNew::svc);
    m_task->setPeriod(0.0);
    m_task->executionMeasure(coil::toBool(mprop["exec_time"],
                                    "enable", "disable", true));
    
    int ecount;
    if (coil::stringTo(ecount, mprop["exec_count"].c_str()))
      {
        m_task->executionMeasureCount(ecount);
      }

    m_task->periodicMeasure(coil::toBool(mprop["period_time"],
                                   "enable", "disable", true));
    int pcount;
    if (coil::stringTo(pcount, mprop["period_count"].c_str()))
      {
        m_task->periodicMeasureCount(pcount);
      }

    m_task->suspend();
    m_task->activate();
    m_task->suspend();
    return PORT_OK;
  }

  /*!
   * @if jp
   * @brief InPortコンシューマのセット
   * @else
   * @brief Store InPort consumer
   * @endif
   */
  PublisherBase::ReturnCode PublisherNew::setConsumer(InPortConsumer* consumer)
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
  PublisherBase::ReturnCode PublisherNew::setBuffer(CdrBufferBase* buffer)
  {
    if (buffer == 0) { return INVALID_ARGS; }
    if (m_buffer != 0) { delete m_buffer; }
    m_buffer = buffer;
    return PORT_OK;
  }

  PublisherBase::ReturnCode PublisherNew::write(const cdrMemoryStream& data,
                                                unsigned long sec,
                                                unsigned long usec)
  {
    std::cout << 0 << std::endl;
    if (m_retcode == CONNECTION_LOST) { return m_retcode; }
    std::cout << 1 << std::endl;
    // why?
    //    if (m_retcode == BUFFER_FULL) { return BUFFER_FULL; }
    assert(m_buffer != 0);
    std::cout << 2 << std::endl;
    CdrBufferBase::ReturnCode ret(m_buffer->write(data, sec, usec));
    std::cout << 3 << std::endl;
    m_task->signal();
    std::cout << 4 << std::endl;
    return (RTC::PublisherBase::ReturnCode)ret;
  }

  bool PublisherNew::isActive()
  {
    return m_active;
  }

  PublisherBase::ReturnCode PublisherNew::activate()
  {
    m_active = true;
    return PORT_OK;
  }

  PublisherBase::ReturnCode PublisherNew::deactivate()
  {
    m_active = false;
    return PORT_OK;
  }
  
  /*!
   * @if jp
   * @brief PublisherNew::スレッド実行関数
   * @else
   * @brief Thread execution function
   * @endif
   */
  int PublisherNew::svc(void)
  {
    
    Guard guard(m_retmutex);
    switch (m_pushPolicy)
      {
      case ALL:
        m_retcode = pushAll();
        break;
      case FIFO:
        m_retcode = pushFifo();
        break;
      case SKIP:
        m_retcode = pushSkip();
        break;
      case NEW:
        m_retcode = pushNew();
        break;
      default:
        m_retcode = pushNew();
        break;
      }
    return 0;
  }

  /*!
   * @brief push all policy
   */
  PublisherNew::ReturnCode PublisherNew::pushAll()
  {
    try
      {
        while (m_buffer->readable() > 0)
          {
            cdrMemoryStream& cdr(m_buffer->get());
            ReturnCode ret(m_consumer->put(cdr));
            
            if (ret == SEND_FULL)
              {
                return SEND_FULL;
              }
            
            m_buffer->advanceRptr();
          }
      }
    catch (...)
      {
        return CONNECTION_LOST;
      }
    return PORT_ERROR;
  }

  /*!
   * @brief push "fifo" policy
   */
  PublisherNew::ReturnCode PublisherNew::pushFifo()
  {
    try
      {
        cdrMemoryStream& cdr(m_buffer->get());
        ReturnCode ret(m_consumer->put(cdr));
        
        if (ret == SEND_FULL)
          {
            return SEND_FULL;
          }
        
        m_buffer->advanceRptr();
        
        return ret;
      }
    catch (...)
      {
        return CONNECTION_LOST;
      }
    return PORT_ERROR;
  }

  /*!
   * @brief push "skip" policy
   */
  PublisherNew::ReturnCode PublisherNew::pushSkip()
  {
    try
      {
        cdrMemoryStream& cdr(m_buffer->get());
        m_buffer->advanceRptr(m_skipn);
        return m_consumer->put(cdr);
      }
    catch (...)
      {
        return CONNECTION_LOST;
      }
    return PORT_ERROR;
  }

   /*!
    * @brief push "new" policy
    */
  PublisherNew::ReturnCode PublisherNew::pushNew()
  {
    std::cout << "pushNew()" << std::endl;
    try
      {
        std::cout << "00" << std::endl;
        m_buffer->advanceRptr(m_buffer->readable() - 1);
        std::cout << "01" << std::endl;
        
        cdrMemoryStream& cdr(m_buffer->get());
        std::cout << "02" << std::endl;
        ReturnCode ret(m_consumer->put(cdr));
        std::cout << "03" << std::endl;
        if (ret == SEND_FULL)
          {
        std::cout << "04" << std::endl;
            return SEND_FULL;
          }
        std::cout << "05" << std::endl;
        m_buffer->advanceRptr();
        std::cout << "06" << std::endl;
        return ret;
      }
    catch (...)
      {
        std::cout << "07" << std::endl;
        return CONNECTION_LOST;
      }
        std::cout << "08" << std::endl;
    return PORT_ERROR;
  }

}; // namespace RTC

extern "C"
{
  void PublisherNewInit()
  {
    ::RTC::PublisherFactory::
      instance().addFactory("new",
                            ::coil::Creator< ::RTC::PublisherBase,
                                             ::RTC::PublisherNew>,
                            ::coil::Destructor< ::RTC::PublisherBase,
                                                ::RTC::PublisherNew>);
  }
};
