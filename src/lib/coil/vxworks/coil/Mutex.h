// -*- C++ -*-
/*!
 * @file  Mutex_vxworks.h
 * @brief coil VxWorks mutex class
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


#ifndef COIL_MUTEX_H
#define COIL_MUTEX_H


#include <pthread.h>
#include <semLib.h>

namespace coil
{
  /*!
   * @if jp
   *
   * @class Mutex
   * @brief Mutex クラス
   *
   * @else
   *
   * @class Mutex
   * @brief Mutex class
   *
   * @endif
   */
  class Mutex
  {
  public:
    /*!
     * @if jp
     *
     * @brief コンストラクタ
     *
     * コンストラクタ。
     *
     * @param name オブジェクト名
     *
     * @else
     *
     * @brief Constructor
     *
     * Constructor
     *
     * @param name Object name
     *
     * @endif
     */
    Mutex(const char * const name = 0)
    {
      mutex_ = semMCreate(SEM_Q_PRIORITY | SEM_INVERSION_SAFE);
    }

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
    ~Mutex()
    {
      semDelete(mutex_);
    }

    /*!
     * @if jp
     *
     * @brief 排他制御のロック
     *
     * 排他制御のロックを行う。
     *
     * @else
     *
     * @brief Mutual exclusion lock
     *
     * Lock the Mutual exclusion.
     *
     * @endif
     */
    inline void lock()
    {
      semTake(mutex_, WAIT_FOREVER);
    }

    /*!
     * @if jp
     *
     * @brief 排他制御のノンブロッキングロック
     *
     * 排他制御のロックをノンブロッキングで行う。
     *
     * @else
     *
     * @brief Mutual exclusion non-blocking lock
     *
     * Lock the Mutual exclusion by non-blocking.
     *
     * @endif
     */
    inline bool trylock()
    {
      STATUS status = semTake(mutex_, NO_WAIT);
      return (status == OK);
    }

    /*!
     * @if jp
     *
     * @brief 排他制御のロック解除
     *
     * 排他制御のロック解除を行う。
     *
     * @else
     *
     * @brief Mutual exclusion unlock
     *
     * Unlock the Mutual exclusion.
     *
     * @endif
     */
    inline void unlock()
    {
      semGive(mutex_);
    }

    /*!
     * @if jp
     *
     * @brief 排他制御オブジェクト
     *
     * @else
     *
     * @brief Mutual exclusion object
     *
     * @endif
     */
    SEM_ID mutex_;

  private:
    Mutex(const Mutex&);
    Mutex& operator=(const Mutex &);
  };
};
#endif // COIL_MUTEX_H
