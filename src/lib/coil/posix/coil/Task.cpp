// -*- C++ -*-
/*!
 * @file Task.cpp
 * @brief Task class
 * @date $Date$
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2008
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id$
 *
 */

#include <coil/Task.h>

namespace coil
{

  Task::Task()
    : m_count(0)
  {
    ::pthread_attr_init(&m_attr);
  }

  Task::~Task()
  {
    m_count = 0;
  }

  int Task::open(void* args)
  {
    return 0;
  }

  int Task::close(unsigned long flags)
  {
    return 0;
  }

  int Task::svc()
  {
    return 0;
  }

  void Task::activate()
  {
    if (m_count == 0)
      {
        ::pthread_create(&m_thread,
                         &m_attr,
                         (void* (*)(void*))Task::svc_run,
                         this);
        ++m_count;
      };
  }

  int Task::wait(void)
  {
    void* retval;
    ::pthread_join(m_thread, &retval);
    return 0;
  }

  int Task::suspend(void)
  {
    return 0;
  }

  int Task::resume(void)
  {
    return 0;
  }

  void Task::reset()
  {
    m_count = 0;
  }

  void* Task::svc_run(void* args)
  {
    Task* t = (coil::Task*)args;
    int status;
    status = t->svc();
    t->reset();
    return 0;
  }
};


