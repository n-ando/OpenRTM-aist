// -*- C++ -*-
/*!
 * @file  atomic.h
 * @brief atomic add func
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
#ifndef COIL_ATOMIC_H

#ifdef COIL_HAS_ATOMIC_OP

#include <bits/atomicity.h>

#define COIL_USES_ATOMIC_OP
#define atomic_add(x, y) __gnu_cxx::__atomic_add(x, y)
#define atomic_incr(x)   __gnu_cxx::__atomic_add(x, 1)
#define atomic_decr(x)   __gnu_cxx::__atomic_add(x, -1)
#define atomic_exchange_add(x, y) __gnu_cxx::__exchange_and_add(x, y)
#else

#include <coil/Mutex.h>
#include <mutex>
#define COIL_USES_ATOMIC_OP coil::Mutex mutex_;

#define atomic_add(x, y)                        \
  {                                             \
    std::lock_guard<coil::Mutex> guard(mutex_);    \
    *x = *x + y;                                \
  }

#define atomic_incr(x)                          \
  {                                             \
    std::lock_guard<coil::Mutex> guard(mutex_);    \
    ++(*x);                                     \
  }

#define atomic_decr(x)                          \
  {                                             \
    std::lock_guard<coil::Mutex> guard(mutex_);    \
    --(*x);                                     \
  }

int exchange_add(int* x, int y, coil::Mutex* mutex)
{
  std::lock_guard<coil::Mutex> guard(*mutex);
  int tmp(*x);
  *x = *x + y;
  return tmp;
}

#define atomic_exchange_add(x, y)               \
  exchange_add(x, y, &mutex_)
    
#endif // COIL_HAS_ATOMIC_ADD
#endif // COIL_ATOMIC_H
