// -*- C++ -*-
/*!
 * @file  RtmServiceInterface.h
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

#ifndef COIL_GUARD_H
#define COIL_GUARD_H

#include <coil/Mutex.h>

namespace coil
{
  template <class M>
  class Guard
  {
  public:
    Guard(M& mutex) : m_mutex(mutex)
    {
      m_mutex.lock();
    }
    ~Guard()
    {
      m_mutex.unlock();
    }
  private:
    Guard(const Guard&);
    Guard& operator=(const Guard&);
    M& m_mutex;
  };
};
#endif // COIL_GUARD_H
