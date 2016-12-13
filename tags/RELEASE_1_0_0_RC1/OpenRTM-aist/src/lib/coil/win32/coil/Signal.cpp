// -*- C++ -*-
/*!
 * @file  Signal_posix.h
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

#include <coil/config_coil.h>
#include <coil/Signal.h>
#include <signal.h>

namespace coil
{
  SignalAction::SignalAction()
    : m_handle(0), m_signum(0), m_mask(0), m_flags(0)
  {
  }

  SignalAction::SignalAction(SignalHandler handle, int signum,
                             sigset_t *mask, int flags)
    : m_handle(handle), m_signum(signum), m_mask(mask), m_flags(flags)
  {
	  ::signal(m_signum, m_handle);
  }

  SignalAction::~SignalAction()
  {
  }

};
