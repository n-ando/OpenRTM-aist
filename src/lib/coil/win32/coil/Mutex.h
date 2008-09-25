// -*- C++ -*-
/*!
 * @file  MutexPosix.h
 * @brief RT-Middleware Service interface
 * @date  $Date$
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2008
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

#ifndef COIL_MUTEX_H
#define COIL_MUTEX_H

#include <windows.h>

namespace coil
{
  typedef HANDLE pthread_mutex_t;
  
  class Mutex
  {
  public:
    Mutex()
    {
      ::InitializeCriticalSection(&mutex_);
    }

    ~Mutex()
    {
      ::DeleteCriticalSection(&mutex_);
    }

    inline void lock()
    {
      ::EnterCriticalSection(&mutex_);
    }

    inline bool trylock()
    {
		return ::TryEnterCriticalSection(&mutex_) ? true : false;
    }

    inline void unlock()
    {
      ::LeaveCriticalSection(&mutex_);
    }
    CRITICAL_SECTION mutex_;
    
  private:
    Mutex(const Mutex&);
    Mutex& operator=(const Mutex &);
  };
};
#endif // COIL_MUTEX_H
