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
#define COIL_ATOMIC_H

#ifdef COIL_HAS_ATOMIC_ADD
#include <Windows.h>
#define atomic_add(x, y) ::InterlockedExchangeAdd(x, y)
#define atomic_incr(x)   ::InterlockedIncrement(x)
#define atomic_decr(x)   ::InterlockedDecrement(x)
#define atomic_exchange_add(x, y) ::InterlockedExchangeAdd(x, y)
#else

#include <mutex>

#define atomic_add(x, y)                        \
  {                                             \
    std::lock_guard<std::mutex> guard(__mutex);    \
    x = x + y;                                  \
  }

#define atomic_incr(x)                          \
  {                                             \
    std::lock_guard<std::mutex> guard(__mutex);    \
    ++x;                                        \
  }

#define atomic_decr(x)                          \
  {                                             \
    std::lock_guard<std::mutex> guard(__mutex);    \
    --x;                                        \
  }

int exchange_add(int* x, int y, std::mutex* mutex)
{
  std::lock_guard<std::mutex> guard(*mutex);
  int tmp(*x);
  *x = *x + y;
  return tmp;
}

#define atomic_exchange_add(x, y)               \
  exchange_add(x, y, &__mutex)

#endif  // COIL_HAS_ATOMIC_ADD
#endif  // COIL_ATOMIC_H
