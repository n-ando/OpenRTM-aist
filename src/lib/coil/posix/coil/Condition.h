// -*- C++ -*-
/*!
 * @file  Condition_posix.h
 * @brief Condition variable for POSIX
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

#ifndef COIL_CONDITION_H
#define COIL_CONDITION_H

#include <pthread.h>
#include <algorithm>

namespace coil
{
  template <class M>
  class Condition
  {
  public:
    Condition(M& mutex)
      : m_mutex(mutex)
    {
      ::pthread_cond_init(&m_cond, 0);
    }
    ~Condition()
    {
      ::pthread_cond_destroy(&m_cond);
    }

    inline void signal()
    {
      ::pthread_cond_signal(&m_cond);
    }

    inline void broadcast()
    {
      ::pthread_cond_broadcast(&m_cond);
    }

    bool wait()
    {
      return 0 == ::pthread_cond_wait(&m_cond, &m_mutex.mutex_);
    }

    bool wait(long second, long nano_second = 0)
    {
      timespec abstime;
      abstime.tv_sec = std::time(0) + second;
      abstime.tv_nsec = nano_second;
      return 0 == ::pthread_cond_timedwait(&m_cond, &m_mutex.mutex_, &abstime);
    }

  private:
    Condition(const M&);
    Condition& operator=(const M &);
    pthread_cond_t m_cond;
    M& m_mutex;
  };
};
#endif // COIL_CONDITION_H
