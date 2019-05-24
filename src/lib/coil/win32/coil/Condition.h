// -*- C++ -*-
/*!
 * @file  Condition_win32.h
 * @brief Condition variable class for Win32
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


#include <Windows.h>
#include <algorithm>
#include <iostream>
#include <mutex>

namespace coil
{
  typedef struct
  {
    // Number of waiting threads.
    int waiters_count_;

    // Serialize access to <waiters_count_>.
    std::mutex waiters_count_lock_;

    // Semaphore used to queue up threads waiting for the condition to
    // become signaled.
    HANDLE sema_;

    // An auto-reset event used by the broadcast/signal thread to wait
    // for all the waiting thread(s) to wake up and be released from the
    // semaphore.
    HANDLE waiters_done_;

    // Keeps track of whether we were broadcasting or signaling.  This
    // allows us to optimize the code if we're just signaling.
    size_t was_broadcast_;

  } pthread_cond_t;


  int pthread_cond_init(pthread_cond_t *cv);


  /*!
   * @if jp
   *
   * @brief スレッド実行の待機
   *
   * シグナル状態になるまでスレッドの実行を停止する。
   *
   * @return 実行結果(成功:0、失敗:0以外)
   *
   * @else
   *
   * @brief Wait of the thread practice
   *
   * Stop the practice of the thread till become the signal state.
   *
   * @return If it is 0 succeed, other is fail.
   *
   * @endif
   */
  DWORD pthread_cond_wait(coil::pthread_cond_t *cv,
      std::mutex *external_mutex, DWORD aMilliSecond);

  /*!
   * @if jp
   *
   * @brief スレッド実行の再開
   *
   * 待機しているスレッド実行を再開させる。
   *
   * @return 実行結果(成功:0)
   *
   * @else
   *
   * @brief Resume of the thread practice
   *
   * Let the practice of a waiting thread resume.
   *
   * @return If it is 0 succeed.
   *
   * @endif
   */
  int pthread_cond_signal(pthread_cond_t *cv);

  /*!
   * @if jp
   *
   * @brief 全スレッド実行の再開
   *
   * 待機している全てのスレッド実行を再開させる。
   *
   * @return 実行結果(成功:0)
   *
   * @else
   *
   * @brief Resume of all the thread practice
   *
   * Let all waiting thread practice resume.
   *
   * @return If it is 0 succeed.
   *
   * @endif
   */
  int pthread_cond_broadcast(pthread_cond_t *cv);

  /*!
   * @if jp
   *
   * @class Condition
   * @brief Condition テンプレートクラス
   *
   * @else
   *
   * @class Condition
   * @brief Condition template class
   *
   * @endif
   */
  template <class M>
  class Condition
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
    explicit Condition(M& mutex)
      : m_mutex(mutex)
    {
      pthread_cond_init(&m_cond);
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
    ~Condition()
    {
    }

    /*!
     * @if jp
     *
     * @brief スレッド実行の再開
     *
     * 待機しているスレッド実行を再開させる。
     *
     * @else
     *
     * @brief Resume of the thread practice
     *
     * Let the practice of a waiting thread resume.
     *
     * @endif
     */
    inline void signal()
    {
      pthread_cond_signal(&m_cond);
    }

    /*!
     * @if jp
     *
     * @brief 全スレッド実行の再開
     *
     * 待機している全てのスレッド実行を再開させる。
     *
     * @else
     *
     * @brief Resume of all the thread practice
     *
     * Let all waiting thread practice resume.
     *
     * @endif
     */
    inline void broadcast()
    {
      pthread_cond_broadcast(&m_cond);
    }

    /*!
     * @if jp
     *
     * @brief スレッド実行の待機
     *
     * 条件変数が送信されるまでスレッドの実行を停止する。
     *
     * @return true: 成功, false: 失敗
     *
     * @else
     *
     * @brief Wait of the thread practice
     *
     * Stop the practice of the thread till a condition variable is transmitted.
     *
     * @return true: successful, false: failed
     *
     * @endif
     */
    bool wait()
    {
      return 0 == pthread_cond_wait(&m_cond, &m_mutex, INFINITE);
    }

    /*!
     * @if jp
     *
     * @brief 設定時間のスレッド実行待機
     *
     * 設定された時間、スレッドの実行を停止する。
     *
     * @param second 秒単位の時間
     * @param nano_second ナノ秒単位の時間
     *
     * @return true: 成功, false: 失敗
     *
     * @else
     *
     * @brief Thread practice wait of set time
     *
     * In set time, stop the practice of the thread.
     *
     * @param second Time of the seconds.
     * @param nano_second time of the nanoseconds.
     *
     * @return true: successful, false: failed
     *
     * @endif
     */
    bool wait(long second, long nano_second = 0)
    {
      DWORD milli_second = second * 1000 + nano_second / 1000000;
      return 0 == pthread_cond_wait(&m_cond, &m_mutex, milli_second);
    }

  private:
    explicit Condition(const std::mutex&);
    Condition& operator=(const std::mutex &);
    coil::pthread_cond_t m_cond;
    M& m_mutex;
  };  // class Condition

} // namespace coil
#endif  // COIL_CONDITION_H
