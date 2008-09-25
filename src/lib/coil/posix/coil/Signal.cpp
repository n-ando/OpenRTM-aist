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

#ifdef COIL_OS_FREEBSD
#define _SIGSET_NWORDS _SIG_WORDS
#endif

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
    struct sigaction action;
    action.sa_handler = m_handle;
    if (m_mask)
      {
        action.sa_mask = *m_mask;
      }
    else
      {
        for (unsigned int i(0); i < _SIGSET_NWORDS; ++i)
          {
#ifdef COIL_OS_FREEBSD
            action.sa_mask.__bits[i] = 0;
#else
            action.sa_mask.__val[i] = 0;
#endif

          }
      }
    action.sa_flags = m_flags;

    signal(m_signum, SIG_IGN);
    if (sigaction(m_signum, &action, 0) < 0)
      {
        signal(m_signum, SIG_DFL);
        m_handle = 0;
        m_signum = 0;
        m_mask   = 0;
        m_flags  = 0;
      }
  }

  SignalAction::~SignalAction()
  {
    signal(m_signum, SIG_DFL);
    m_handle = 0;
    m_signum = 0;
    m_mask   = 0;
    m_flags  = 0;
  }

};
