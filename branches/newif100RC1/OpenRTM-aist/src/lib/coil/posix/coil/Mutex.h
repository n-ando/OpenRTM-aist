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

#include <pthread.h>

namespace coil
{
  class Mutex
  {
  public:
    Mutex(const char * const name = 0)
    {
      if(name != 0 )
      {
        pthread_mutexattr_t mattr;
        int ret;
        ret = pthread_mutexattr_init(&mattr);
        ret = pthread_mutexattr_setpshared(&mattr, PTHREAD_PROCESS_SHARED);
        ::pthread_mutex_init(&mutex_, &mattr);
      }
      else
      {
        ::pthread_mutex_init(&mutex_, 0);
      }
    }

    ~Mutex()
    {
      ::pthread_mutex_destroy(&mutex_);
    }

    inline void lock()
    {
      ::pthread_mutex_lock(&mutex_);
    }

    inline bool trylock()
    {
      return ::pthread_mutex_trylock(&mutex_);
    }

    inline void unlock()
    {
      ::pthread_mutex_unlock(&mutex_);
    }
    pthread_mutex_t mutex_;

  private:
    Mutex(const Mutex&);
    Mutex& operator=(const Mutex &);
  };
};
#endif // COIL_MUTEX_H
