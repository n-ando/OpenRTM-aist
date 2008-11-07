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

#ifdef WIN32
#pragma warning( push )
#pragma warning( disable : 4267 )
#pragma warning( disable : 4290 )
#pragma warning( disable : 4311 )
#pragma warning( disable : 4312 )
#endif // WIN32

#include <coil/Properties.h>
#include <coil/Time.h>
#include <rtm/PublisherPeriodic.h>
#include <rtm/InPortConsumer.h>
#include <rtm/RTC.h>
#include <stdlib.h>

#ifdef WIN32
#pragma warning( pop )
#endif // WIN32

namespace RTC
{
  /*!
   * @if jp
   * @brief コンストラクタ
   * @else
   * @brief Constructor
   * @endif
   */
  PublisherPeriodic::PublisherPeriodic(InPortConsumer* consumer,
				       const coil::Properties& property)
    : m_consumer(consumer), m_running(true)
  {
    std::string rate(property.getProperty("dataport.push_rate"));
    double hz;
    
    if (rate != "")
      {
	hz = atof(rate.c_str());
	if (hz == 0) hz = 1000.0;
      }
    else
      {
	hz = 1000.0;
      }
    m_usec = static_cast<unsigned int>(1000000.0/hz);
    open(0);
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
    m_running = 0;
    wait();
    delete m_consumer;
  }
  
  
  /*!
   * @if jp
   * @brief Observer関数
   * @else
   * @brief Observer function
   * @endif
   */
  void PublisherPeriodic::update()
  {
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
    
#ifdef ARTLinux
    art_enter( ART_PRIO_MAX, ART_TASK_PERIODIC, m_usec );
#endif // ARTLinux
    while (m_running)
      {
	m_consumer->push();
#ifdef ARTLinux
	art_wait();
#else
    coil::usleep(m_usec);
#endif //ARTLinux
      }
    return 0;
  }
  
  
  /*!
   * @if jp
   * @brief タスク開始
   * @else
   * @brief Start task
   * @endif
   */
  int PublisherPeriodic::open(void *args)
  {
    m_running = true;
    this->activate();
    return 0;
  }
  
  
  /*!
   * @if jp
   * @brief タスク終了関数
   * @else
   * @brief Task terminate function
   * @endif
   */
  void PublisherPeriodic::release()
  {
    m_running = false;
  }

}; // namespace RTC
