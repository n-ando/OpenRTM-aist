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

#ifdef WIN32
#pragma warning( push )
#pragma warning( disable : 4267 )
#pragma warning( disable : 4290 )
#pragma warning( disable : 4311 )
#pragma warning( disable : 4312 )
#endif // WIN32

#include <coil/Properties.h>
#include <rtm/PublisherNew.h>
#include <rtm/InPortConsumer.h>
#include <rtm/RTC.h>
#include <iostream>

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
  PublisherNew::PublisherNew(InPortConsumer* consumer,
			     const coil::Properties& property)
    : m_consumer(consumer), m_running(true), m_data()
  {
    open(0);
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
    if (m_data._mutex.trylock() != 0)
      {
	return;
      }
    m_data._updated = true;
    m_data._cond.signal();
    m_data._mutex.unlock();
#ifdef WIN32
    ::Sleep(0);
#else
    pthread_yield();
#endif
    return;
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
    while (m_running)
      {
	m_data._mutex.lock();
	
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
	
	m_data._mutex.unlock();	
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
    if (m_data._mutex.trylock() != 0)
      {
	return;
      }
    m_running = false;
    m_data._cond.signal(); //broadcast();
    m_data._mutex.unlock();
    wait();
  }
  
}; // namespace RTC
