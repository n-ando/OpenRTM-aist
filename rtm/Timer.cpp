// -*- C++ -*-
/*!
 * @file Timer.cpp
 * @brief Timer class
 * @date $Date: 2007-04-13 16:04:00 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2007
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: Timer.cpp,v 1.1 2007-04-13 16:04:00 n-ando Exp $
 *
 */

#include <rtm/Listener.h>
#include <rtm/Timer.h>

namespace RTC
{

  Timer::Timer(TimeValue& interval)
    : m_interval(interval), m_running(false)
  {
  }


  Timer::~Timer()
  {
  }


  int Timer::open(void *args)
  {
    activate();
    return 0;
  }


  int Timer::svc(void)
  {
    TimeValue t_curr, t_pre, tm;;
    while (m_running)
      {
	invoke();
	if (m_interval.tv_sec != 0) sleep(m_interval.tv_sec);
	usleep(m_interval.tv_usec);
      }
    return 0;
  }
  

  //============================================================
  // public functions
  //============================================================
  void Timer::start()
  {
    ACE_Guard<ACE_Thread_Mutex> guard(m_runningMutex);
    if (!m_running) 
      {
	m_running = true;
	open(0);
      }
  }
  

  void Timer::stop()
  {
    ACE_Guard<ACE_Thread_Mutex> guard(m_runningMutex);
    m_running = false;
  }


  void Timer::invoke()
  {
    for (int i(0), len(m_tasks.size()); i < len; ++i)
      {
	m_tasks[i].remains = m_tasks[i].remains - m_interval;
	if (m_tasks[i].remains.tv_usec < 0)
	  {
	    m_tasks[i].listener->invoke();
	    m_tasks[i].remains = m_tasks[i].period;
	  }
      }
  }


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
