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
		  m_thread =
			  (HANDLE)::_beginthreadex(NULL, // security
			  0, //stuck size
			  Task::svc_run, // func
			  (void*)this, // argument
			  0, // flag (0 or CREATE_SUSPEND)
			  NULL); //thread descripter
		  ++m_count;
      };
  }

  int Task::wait(void)
  {
    if (m_count > 0)
      {
        DWORD retval;
	retval = ::WaitForSingleObject(m_thread, INFINITE);
      }
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

  void Task::finalize()
  {
    reset();
  }
 
  unsigned int WINAPI Task::svc_run(void* args)
  {
    Task* t = (coil::Task*)args;
    int status;
    status = t->svc();
    return 0;
  }
};


