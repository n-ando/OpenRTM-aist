// -*- C++ -*-
/*!
 * @file  PublisherPeriodic.cpp
 * @brief PublisherPeriodic class
 * @date  $Date: 2007-02-04 17:03:04 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006
 *     Noriaki Ando
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: PublisherPeriodic.cpp,v 1.4 2007-02-04 17:03:04 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.3  2007/01/21 13:04:32  n-ando
 * Data push interval property accepts float.
 *
 * Revision 1.2  2007/01/06 18:01:00  n-ando
 * Some trivial fixes.
 *
 * Revision 1.1  2006/11/27 09:44:50  n-ando
 * The first commitment.
 *
 */

#include <rtm/PublisherPeriodic.h>
#include <rtm/InPortConsumer.h>
#include <rtm/Properties.h>
#include <stdlib.h>

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
				       const Properties& property)
    : m_consumer(consumer), m_running(true)
  {
    std::string rate(property.getProperty("dataport.push_interval"));
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
    m_usec = static_cast<double>(1000000.0/hz);
    open(0);
  }


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
	usleep(m_usec);
#endif //ARTLinux
      }
    return 0;
  }


  /*!
   * @if jp
   * @brief タスク開始
   * @else
   * @brief Task start function
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
