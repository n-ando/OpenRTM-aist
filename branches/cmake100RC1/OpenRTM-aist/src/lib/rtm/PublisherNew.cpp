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
    : rtclog("PublisherNew"),
      m_consumer(0), m_buffer(0), m_task(0),
      m_retcode(PORT_OK), m_pushPolicy(NEW),
      m_skipn(0), m_active(false), m_leftskip(0)
  {
    rtclog.setLevel("PARANOID");
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
    RTC_TRACE(("~PublisherNew()"));
    if (m_task != 0)
      {
        m_task->resume();
        m_task->finalize();

        RTC::PeriodicTaskFactory::instance().deleteObject(m_task);
        RTC_PARANOID(("task deleted."));
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
    RTC_TRACE(("init()"));
    rtclog.lock();
    rtclog.level(::RTC::Logger::RTL_PARANOID) << prop;
    rtclog.unlock();
    
    // push_policy default: NEW
    std::string push_policy = prop.getProperty("publisher.push_policy", "new");
    RTC_DEBUG(("push_policy: %s", push_policy.c_str()));

    // skip_count default: 0
    std::string skip_count = prop.getProperty("publisher.skip_count", "0");
    RTC_DEBUG(("skip_count: %s", skip_count.c_str()));

    coil::normalize(push_policy);
    if (push_policy == "all") 
      {
        m_pushPolicy = ALL;
      }
    else if (push_policy == "fifo")
      {
        m_pushPolicy = FIFO;
      }
    else if (push_policy == "skip")
      {
        m_pushPolicy = SKIP;
      }
    else if (push_policy == "new")
      {
        m_pushPolicy = NEW;
      }
    else
      {
        RTC_ERROR(("invalid push_policy value: %s", push_policy.c_str()));
        m_pushPolicy = NEW;     // default push policy
      }

    if (!coil::stringTo(m_skipn, skip_count.c_str()))
      {
        RTC_ERROR(("invalid skip_count value: %s", skip_count.c_str()));
        m_skipn = 0;           // default skip count
      }
    if (m_skipn < 0)
      {
        RTC_ERROR(("invalid skip_count value: %d", m_skipn));
        m_skipn = 0;           // default skip count
      }

    RTC::PeriodicTaskFactory& factory(RTC::PeriodicTaskFactory::instance());

    coil::vstring th = factory.getIdentifiers();
    RTC_DEBUG(("available task types: %s", coil::flatten(th).c_str()));

    m_task = factory.createObject(prop.getProperty("thread_type", "default"));
    if (m_task == 0)
      {
        RTC_ERROR(("Task creation failed: %s",
                   prop.getProperty("thread_type", "default").c_str()));
        return INVALID_ARGS;
      }
    RTC_PARANOID(("Task creation succeeded."));

    coil::Properties& mprop(prop.getNode("measurement"));

    // setting task function
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
    RTC_TRACE(("setConsumer()"));
    
    if (consumer == 0)
      {
        RTC_ERROR(("setConsumer(consumer = 0): invalid argument."));
        return INVALID_ARGS;
      }
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
    RTC_TRACE(("setBuffer()"));

    if (buffer == 0)
      {
        RTC_ERROR(("setBuffer(buffer == 0): invalid argument"));
        return INVALID_ARGS;
      }
    m_buffer = buffer;
    return PORT_OK;
  }

  PublisherBase::ReturnCode PublisherNew::write(const cdrMemoryStream& data,
                                                unsigned long sec,
                                                unsigned long usec)
  {
    RTC_PARANOID(("write()"));
    if (m_consumer == 0) { return PRECONDITION_NOT_MET; }
    if (m_buffer == 0) { return PRECONDITION_NOT_MET; }
    if (m_retcode == CONNECTION_LOST)
      {
        RTC_DEBUG(("write(): connection lost."));
        return m_retcode;
      }

    if (m_retcode == BUFFER_FULL)
      {
        RTC_DEBUG(("write(): InPort buffer is full."));
        CdrBufferBase::ReturnCode ret(m_buffer->write(data, sec, usec));
        m_task->signal();
        return BUFFER_FULL;
      }

    assert(m_buffer != 0);

    CdrBufferBase::ReturnCode ret(m_buffer->write(data, sec, usec));

    m_task->signal();
    RTC_DEBUG(("%s = write()", CdrBufferBase::toString(ret)));

    return convertReturn(ret);
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
    RTC_TRACE(("pushAll()"));
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
            else if (ret != PORT_OK)
              {
                return ret;
              }
            
            m_buffer->advanceRptr();
          }
        return PORT_OK;
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
    RTC_TRACE(("pushFifo()"));
    try
      {
        cdrMemoryStream& cdr(m_buffer->get());
        ReturnCode ret(m_consumer->put(cdr));
        
        if (ret == SEND_FULL)
          {
            return SEND_FULL;
          }
        else if (ret != PORT_OK)
          {
            return ret;
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
    RTC_TRACE(("pushSkip()"));
    try
      {
        ReturnCode ret(PORT_OK);
        int preskip(m_buffer->readable() + m_leftskip);
        int loopcnt(preskip/(m_skipn +1));
        int postskip(m_skipn - m_leftskip);
        for (int i(0); i < loopcnt; ++i)
          {
            m_buffer->advanceRptr(postskip);

            const cdrMemoryStream& cdr(m_buffer->get());
            ret = m_consumer->put(cdr);
            if (ret != PORT_OK)
              {
                m_buffer->advanceRptr(-postskip);
                return ret;
              }
            postskip = m_skipn +1;
          }
        m_buffer->advanceRptr(m_buffer->readable());
        if (loopcnt == 0)
          {  // Not put
            m_leftskip = preskip % (m_skipn +1);
          }
        else
          {
          if ( m_retcode != PORT_OK )
            {  // put Error after 
              m_leftskip = 0;
            }
          else
            {  // put OK after
              m_leftskip = preskip % (m_skipn +1);
            }
          }
        return ret;
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
    RTC_TRACE(("pushNew()"));
    try
      {
        m_buffer->advanceRptr(m_buffer->readable() - 1);
        
        cdrMemoryStream& cdr(m_buffer->get());
        ReturnCode ret(m_consumer->put(cdr));

        if (ret == PORT_OK)
          {
            m_buffer->advanceRptr();
          }
        return ret;
      }
    catch (...)
      {
        return CONNECTION_LOST;
      }
    return PORT_ERROR;
  }

  PublisherBase::ReturnCode
  PublisherNew::convertReturn(BufferStatus::Enum status)
  {
    switch (status)
      {
      case BufferStatus::BUFFER_OK:
        return PORT_OK;
        break;
      case BufferStatus::BUFFER_EMPTY:
        return BUFFER_EMPTY;
        break;
      case BufferStatus::TIMEOUT:
        return BUFFER_TIMEOUT;
        break;
      case BufferStatus::PRECONDITION_NOT_MET:
        return PRECONDITION_NOT_MET;
        break;
      default:
        return PORT_ERROR;
      }
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
