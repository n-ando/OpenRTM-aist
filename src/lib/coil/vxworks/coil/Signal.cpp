// -*- C++ -*-
/*!
 * @file  Signal_posix.cpp
 * @brief SignalAction class
 * @date  $Date$
 * @author Nobuhiko Miyamoto <n-miyamoto@aist.go.jp>
 *
 * Copyright (C) 2017
 *     Nobuhiko Miyamoto
 *     Robot Innovation Research Center
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id$
 *
 */

#include <coil/config_coil.h>
#include <coil/Signal.h>
#include <string.h>



namespace coil
{
  /*!
   * @if jp
   * @brief コンストラクタ
   * @else
   * @brief Constructor
   * @endif
   */
  SignalAction::SignalAction()
    : m_handle(0), m_signum(0), m_mask(0), m_vxflags(0)
  {
  }

  /*!
   * @if jp
   * @brief コンストラクタ
   * @param handle シグナルハンドラ
   * @param signum シグナル番号
   * @else
   * @brief Constructor
   * @param handle Signal handler.
   * @param signum Signal number.
   * @endif
   */
  SignalAction::SignalAction(SignalHandler handle, int signum)
    : m_handle(handle), m_signum(signum), m_mask(0), m_vxflags(0)
  {
    struct sigaction action;
    memset(&action, 0, sizeof(action));  // clear.
    action.sa_handler = m_handle;

    signal(m_signum, SIG_IGN);
    if (sigaction(m_signum, &action, 0) < 0)
      {
        signal(m_signum, SIG_DFL);
        m_handle = 0;
        m_signum = 0;
        m_mask   = 0;
        m_vxflags  = 0;
      }
  }

  /*!
   * @if jp
   * @brief デストラクタ
   * @else
   * @brief Destructor
   * @endif
   */
  SignalAction::~SignalAction()
  {
    signal(m_signum, SIG_DFL);
    m_handle = 0;
    m_signum = 0;
    m_mask   = 0;
    m_vxflags  = 0;
  }

};


