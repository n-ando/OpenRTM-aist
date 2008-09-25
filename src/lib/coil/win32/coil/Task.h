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

#ifndef COIL_TASK_H
#define COIL_TASK_H

#include <windows.h>
#include <process.h>


namespace coil
{
  class Task
  {
  public:
    Task();
    virtual ~Task();
    virtual int open(void* args = 0);
    virtual int close(unsigned long flags = 0);
    virtual int svc();
    virtual void activate();
    virtual int wait(void);
    virtual int suspend(void);
    virtual int resume(void);
    static unsigned int WINAPI svc_run(void* args = 0);
  private:
    int m_count;
    HANDLE m_thread;
  };
};

#endif // COIL_TASK_H
