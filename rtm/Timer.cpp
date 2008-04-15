// -*- C++ -*-
/*!
 * @file Timer.cpp
 * @brief Timer class
 * @date $Date: 2007-07-20 16:12:58 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2007-2008
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: Timer.cpp,v 1.1.2.1 2007-07-20 16:12:58 n-ando Exp $
 *
 */

#include <rtm/Listener.h>
#include <rtm/Timer.h>

namespace RTC
{
  /*!
   * @if jp
   * @brief コンストラクタ
   * @else
   * @brief Constructor
   * @endif
   */
  Timer::Timer(TimeValue& interval)
    : m_interval(interval), m_running(false)
  {
  }
  
  /*!
   * @if jp
   * @brief デストラクタ
   * @else
   * @brief Destructor
   * @endif
   */
  Timer::~Timer()
  {
    stop();
    wait();
  }
  
  /*!
   * @if jp
   * @brief Timer 用スレッド生成
   * @else
   * @brief Generate thread for Timer
   * @endif
   */
  int Timer::open(void *args)
  {
    activate();
    return 0;
  }
  
  /*!
   * @if jp
   * @brief Timer 用スレッド実行関数
   * @else
   * @brief Thread execution function for Timer
   * @endif
   */
  int Timer::svc(void)
  {
    TimeValue t_curr, t_pre, tm;;
    while (m_running)
      {
	invoke();
	if (m_interval.tv_sec != 0)
	  {
#ifdef WIN32
	    Sleep(m_interval.tv_sec * 1000);
#else
	    sleep(m_interval.tv_sec);
#endif
	  }
	usleep(m_interval.tv_usec);
      }
    return 0;
  }
  
  //============================================================
  // public functions
  //============================================================
  /*!
   * @if jp
   * @brief Timer タスク開始
   * @else
   * @brief Start Timer task
   * @endif
   */
  void Timer::start()
  {
    ACE_Guard<ACE_Thread_Mutex> guard(m_runningMutex);
    if (!m_running) 
      {
	m_running = true;
	open(0);
      }
  }
  
  /*!
   * @if jp
   * @brief Timer タスク停止
   * @else
   * @brief Stop Timer tast
   * @endif
   */
  void Timer::stop()
  {
    ACE_Guard<ACE_Thread_Mutex> guard(m_runningMutex);
    m_running = false;
  }
  
  /*!
   * @if jp
   * @brief Timer タスク実行
   * @else
   * @brief Invoke Timer task
   * @endif
   */
  void Timer::invoke()
  {
    for (int i(0), len(m_tasks.size()); i < len; ++i)
      {
	m_tasks[i].remains = m_tasks[i].remains - m_interval;
	if (m_tasks[i].remains.sign() <= 0)
	  {
	    m_tasks[i].listener->invoke();
	    m_tasks[i].remains = m_tasks[i].period;
	  }
      }
  }
  
  /*!
   * @if jp
   * @brief リスナー登録
   * @else
   * @brief Register listener
   * @endif
   */
  ListenerId Timer::registerListener(ListenerBase* listener, TimeValue tm)
  {
    ACE_Guard<ACE_Thread_Mutex> guard(m_taskMutex);
    
    for (int i(0), len(m_tasks.size()); i < len; ++i)
      {
	if (m_tasks[i].listener == listener)
	  {
	    m_tasks[i].period = tm;
	    m_tasks[i].remains = tm;
	    return listener;
	  }
      }
    m_tasks.push_back(Task(listener, tm));
    return listener;
  }
  
  /*!
   * @if jp
   * @brief リスナー登録解除
   * @else
   * @brief Unregister listener
   * @endif
   */
  bool Timer::unregisterListener(ListenerId id)
  {
    ACE_Guard<ACE_Thread_Mutex> guard(m_taskMutex);
    std::vector<Task>::iterator it;
    it = m_tasks.begin();
    
    for (int i(0), len(m_tasks.size()); i < len; ++i, ++it)
      {
	if (m_tasks[i].listener == id)
	  {
	    m_tasks.erase(it);
	    return true;
	  }
      }
    return false;
  }
}; // namespace RTC
