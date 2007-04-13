// -*- C++ -*-
/*!
 * @file Timer.h
 * @brief Timer class
 * @date $Date: 2007-04-13 16:04:06 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2007
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: Timer.h,v 1.1 2007-04-13 16:04:06 n-ando Exp $
 *
 */

#ifndef Timer_h
#define Timer_h

#include <rtm/TimeValue.h>
#include <rtm/Listener.h>
#include <ace/Synch.h>
#include <ace/Task.h>
#include <vector>


typedef ListenerBase* ListenerId;

class Timer
  : public ACE_Task<ACE_MT_SYNCH>
{
public:
  Timer(TimeValue& interval);


  virtual ~Timer();


  //============================================================
  // ACE_Task 
  //============================================================
  virtual int open(void *args);
  

  virtual int svc(void);

  
  //============================================================
  // public functions
  //============================================================
  void start();


  void stop();


  void invoke();


  ListenerId registerListener(ListenerBase* listener, TimeValue tm);

  template <class ListenerClass>
  ListenerId registerListenerObj(ListenerClass* obj,
				 void (ListenerClass::*cbf)(),
				 TimeValue tm)
  {
    return registerListener(new ListenerObject<ListenerClass>(obj, cbf), tm);
  }

  
  ListenerId registerListenerFunc(void (*cbf)(), TimeValue tm)
  {
    return registerListener(new ListenerFunc(cbf), tm);
  }

  bool unregisterListener(ListenerId id);


private:
  TimeValue m_interval;

  ACE_Thread_Mutex m_runningMutex;
  bool m_running;

  struct Task
  {
    Task(ListenerBase* l, TimeValue p)
      : listener(l), period(p), remains(p)
    {
    }
    ListenerBase* listener;
    TimeValue period;
    TimeValue remains;
  };

  std::vector<Task> m_tasks;
  ACE_Thread_Mutex  m_taskMutex;

};
#endif // Timer_h
