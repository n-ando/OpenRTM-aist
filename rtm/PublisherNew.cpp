// -*- C++ -*-
/*!
 * @file  PublisherNew.cpp
 * @brief PublisherNew class
 * @date  $Date: 2007-07-20 16:03:50 $
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
 * $Id: PublisherNew.cpp,v 1.2.4.1 2007-07-20 16:03:50 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.2  2007/01/06 18:00:49  n-ando
 * Some trivial fixes.
 *
 * Revision 1.1  2006/11/27 09:44:48  n-ando
 * The first commitment.
 *
 */

#include <rtm/PublisherNew.h>
#include <rtm/InPortConsumer.h>
#include <rtm/Properties.h>
#include <rtm/RTC.h>
#include <iostream>


namespace RTC
{
  /*!
   * @if jp
   * @brief コンストラクタ
   * @else
   * @brief Constructor
   * @endif
   */
  PublisherNew::PublisherNew(InPortConsumer* consumer,
			     const Properties& property)
    : m_consumer(consumer), m_running(true), m_data()
  {
    open(0);
  }

  PublisherNew::~PublisherNew()
  {
    delete m_consumer;
  }

  /*!
   * @if jp
   * @brief Observer関数
   * @else
   * @brief Observer function
   * @endif
   */
  void PublisherNew::update()
  {
    if (m_data._mutex.tryacquire() != 0)
      {
	return;
      }
    m_data._updated = true;
    m_data._cond.signal();
    m_data._mutex.release();
#ifdef WIN32
    ACE_OS::thr_yield();
#else
    pthread_yield();
#endif
    usleep(100);
    return;
  }
  
  /*!
   * @if jp
   * @brief スレッPublisherNew::ド実行関数
   * @else
   * @brief Thread execution function
   * @endif
   */
  int PublisherNew::svc(void)
  {
    while (m_running)
      {
	m_data._mutex.acquire();
	
	// Waiting for new data updated
	while (!m_data._updated && m_running)
	  {
	    m_data._cond.wait();
	  }
	
	if (m_data._updated)
	  {
	    m_consumer->push(); 
	    m_data._updated = false;
	  }
	
	m_data._mutex.release();	
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
  int PublisherNew::open(void *args)
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
  void PublisherNew::release()
  {
    m_running = false;
  }

}; // namespace RTC
