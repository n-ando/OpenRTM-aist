// -*- C++ -*-
/*!
 * @file  Signal_win32.cpp
 * @brief SignalAction class
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
#include <csignal>

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
    : m_handle(nullptr), m_signum(0), m_mask(nullptr), m_flags(0)
  {
  }

  /*!
   * @if jp
   * @brief コンストラクタ
   * @param handle シグナルハンドラ
   * @param signum シグナル番号
   * @param mask シグナルマスク
   * @param flags フラグ
   * @else
   * @brief Constructor
   * @param handle Signal handler.
   * @param signum Signal number.
   * @param mask Signal mask.
   * @param flags Flag.
   * @endif
   */
  SignalAction::SignalAction(SignalHandler handle, int signum,
                             sigset_t *mask, int flags)
    : m_handle(handle), m_signum(signum), m_mask(mask), m_flags(flags)
  {
    ::signal(m_signum, m_handle);
  }

  /*!
   * @if jp
   * @brief 代入演算子
   * @else
   * @brief 
   * @endif
   */
  SignalAction& SignalAction::operator=(const SignalAction &signal)
  {
      m_handle = signal.m_handle;
      m_signum = signal.m_signum;
      m_mask = signal.m_mask;
      m_flags = signal.m_flags;
      return *this;
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
  }

} // namespace coil
