// -*- C++ -*-
/*!
 * @file  Signal_vxworks.h
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

#ifndef COIL_SIGNAL_H
#define COIL_SIGNAL_H

#ifndef __RTP__
#include <vxWorks.h>
#endif
#include <signal.h>

namespace coil
{
  typedef void (*SignalHandler)(int);

  /*!
   * @if jp
   *
   * @class SignalAction
   * @brief SignalAction クラス
   *
   * @else
   *
   * @class SignalAction
   * @brief SignalAction class
   *
   * @endif
   */
  class SignalAction
  {
  public:
    /*!
     * @if jp
     *
     * @brief コンストラクタ
     *
     * コンストラクタ。
     *
     * @else
     *
     * @brief Constructor
     *
     * Constructor
     *
     * @endif
     */
    SignalAction();

    /*!
     * @if jp
     *
     * @brief コンストラクタ
     *
     * コンストラクタ。
     *
     * @param handle シグナルハンドラ
     * @param signum シグナル番号
     *
     * @else
     *
     * @brief Constructor
     *
     * Constructor
     *
     * @param handle Signal handler.
     * @param signum Signal number.
     *
     * @endif
     */
    SignalAction(SignalHandler handle, int signum);

    /*!
     * @if jp
     *
     * @brief デストラクタ
     *
     * デストラクタ。
     *
     * @else
     *
     * @brief Destructor
     *
     * Destructor
     *
     * @endif
     */
    ~SignalAction();

  private:
    SignalAction(const SignalAction&);
    SignalAction& operator=(const SignalAction &);
    SignalHandler m_handle;
    int m_signum;
    sigset_t* m_mask;
    int m_vxflags;

  };
};

#endif // COIL_SIGNAL_H
