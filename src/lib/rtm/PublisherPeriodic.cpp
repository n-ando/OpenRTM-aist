// -*- C++ -*-
/*!
 * @file  PublisherPeriodic.cpp
 * @brief PublisherPeriodic class
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
#include <rtm/RTC.h>
#include <coil/Properties.h>
#include <coil/Time.h>
#include <coil/stringutil.h>
#include <rtm/PublisherPeriodic.h>
#include <rtm/InPortConsumer.h>
#include <rtm/RTC.h>
#include <stdlib.h>
#include <rtm/idl/DataPortSkel.h>
#include <rtm/PeriodicTaskFactory.h>
#include <rtm/SystemLogger.h>

namespace RTC
{
  /*!
   * @if jp
   * @brief コンストラクタ
   * @else
   * @brief Constructor
   * @endif
   */
  PublisherPeriodic::PublisherPeriodic()
    : rtclog("PublisherPeriodic"),
      m_consumer(0), m_buffer(0), m_task(0),
      m_retcode(PORT_OK), m_pushPolicy(NEW),
      m_skipn(10), m_active(false), m_readback(false)
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
  PublisherPeriodic::~PublisherPeriodic()
  {
    RTC_TRACE(("~PublisherPeriodic()"));
    if (m_task != 0)
      {
        m_task->resume();
        m_task->finalize();
        RTC_PARANOID(("task finalized."));

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
  PublisherBase::ReturnCode PublisherPeriodic::init(coil::Properties& prop)
  {
    RTC_TRACE(("init()"));
    rtclog.lock();
    rtclog.level(::RTC::Logger::RTL_PARANOID) << prop;
    rtclog.unlock();

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

    // setting task function
    m_task->setTask(this, &PublisherPeriodic::svc);

    // Task execution rate
    std::string rate(prop["push_rate"]);
    double hz;
    if (rate != "")
      {
	hz = atof(rate.c_str());
	if (hz == 0) hz = 1000.0;
        RTC_DEBUG(("Task period %f [Hz]", hz));
      }
    else
      {
	hz = 1000.0;
      }
    m_task->setPeriod(1.0/hz);
    
    // Measurement setting
    coil::Properties& mprop(prop.getNode("measurement"));

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


    // Start task in suspended mode
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
  PublisherBase::ReturnCode
  PublisherPeriodic::setConsumer(InPortConsumer* consumer)
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
  PublisherBase::ReturnCode PublisherPeriodic::setBuffer(CdrBufferBase* buffer)
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

  PublisherBase::ReturnCode
  PublisherPeriodic::write(const cdrMemoryStream& data,
                           unsigned long sec,
                           unsigned long usec)
  {
    RTC_PARANOID(("write()"));

    if (m_retcode == CONNECTION_LOST)
      {
        RTC_DEBUG(("write(): connection lost."));
        return m_retcode;
      }

    if (m_retcode == BUFFER_FULL)
      {
        RTC_DEBUG(("write(): InPort buffer is full."));
        return BUFFER_FULL;
      }

    CdrBufferBase::ReturnCode ret(m_buffer->write(data, sec, usec));
    RTC_DEBUG(("%s = write()", CdrBufferBase::toString(ret)));
    m_task->resume();
    return convertReturn(ret);
  }

  bool PublisherPeriodic::isActive()
  {
    return m_active;
  }

  PublisherBase::ReturnCode PublisherPeriodic::activate()
  {
    m_active = true;
    m_task->resume();
    return PORT_OK;
  }

  PublisherBase::ReturnCode PublisherPeriodic::deactivate()
  {
    m_active = false;
    m_task->suspend();
    return PORT_OK;
  }
  /*!
   * @if jp
   * @brief スレッド実行関数
   * @else
   * @brief Thread execution function
   * @endif
   */
  int PublisherPeriodic::svc(void)
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
  PublisherBase::ReturnCode PublisherPeriodic::pushAll()
  {
    RTC_TRACE(("pushAll()"));

    while (m_buffer->readable() > 0)
      {
        const cdrMemoryStream& cdr(m_buffer->get());
        ReturnCode ret(m_consumer->put(cdr));

        if (ret != PORT_OK)
          {
            return ret;
          }
        m_buffer->advanceRptr();
      }
    return PORT_OK;
   }

  /*!
   * @brief push "fifo" policy
   */
  PublisherBase::ReturnCode PublisherPeriodic::pushFifo()
  {
    RTC_TRACE(("pushFifo()"));
    const cdrMemoryStream& cdr(m_buffer->get());
    ReturnCode ret(m_consumer->put(cdr));
    m_buffer->advanceRptr();
    
    return ret;
  }

  /*!
   * @brief push "skip" policy
   */
  PublisherBase::ReturnCode PublisherPeriodic::pushSkip()
  {
    static int leftskip; // 残りのスキップ数

    RTC_TRACE(("pushSkip()"));
    int preskip(m_buffer->readable() - leftskip);

    if (preskip < 0)
      {
        m_buffer->advanceRptr(m_buffer->readable());
        leftskip = -preskip;
        // this causes empty() == true
      }
    else
      {
        m_buffer->advanceRptr(preskip);
      }

    if (m_buffer->empty())
      {
        RTC_DEBUG(("buffer empty"));
        return BUFFER_EMPTY;
      }
    
    const cdrMemoryStream& cdr(m_buffer->get());
    ReturnCode ret(m_consumer->put(cdr));
    
    int postskip(m_skipn - m_buffer->readable());

    if (postskip < 0)
      {
        leftskip = -postskip;
        m_buffer->advanceRptr(m_buffer->readable());
      }
    else
      {
        m_buffer->advanceRptr(m_skipn);
      }
    
    return ret;
  }

   /*!
    * @brief push "new" policy
    */
  PublisherBase::ReturnCode PublisherPeriodic::pushNew()
  {
    RTC_TRACE(("pushNew()"));

    if (m_buffer->empty() && !m_readback)
      {
        RTC_DEBUG(("buffer empty"));
        return BUFFER_EMPTY;
      }
    
    m_buffer->advanceRptr(m_buffer->readable() - 1);
    
    const cdrMemoryStream& cdr(m_buffer->get());
    ReturnCode ret(m_consumer->put(cdr));
    RTC_DEBUG(("%s = consumer.put()", DataPortStatus::toString(ret)));

    m_buffer->advanceRptr();
    return ret;
  }

  PublisherBase::ReturnCode
  PublisherPeriodic::convertReturn(BufferStatus::Enum status)
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
  void PublisherPeriodicInit()
  {
    ::RTC::PublisherFactory::
      instance().addFactory("periodic",
                            ::coil::Creator< ::RTC::PublisherBase,
                                             ::RTC::PublisherPeriodic>,
                            ::coil::Destructor< ::RTC::PublisherBase,
                                                ::RTC::PublisherPeriodic>);
  }
};
