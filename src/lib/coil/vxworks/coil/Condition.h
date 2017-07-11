// -*- C++ -*-
/*!
 * @file  Condition_vxworks.h
 * @brief Condition variable for VxWorks
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

#ifndef COIL_CONDITION_H
#define COIL_CONDITION_H

#include <pthread.h>
#include <algorithm>
#include <ctime>

#include <semLib.h>
#include <sysLib.h>
#include <taskLib.h>
/*
#ifdef __RTP__
#include <semLib.h>
#include <sysLib.h>
#include <taskLib.h>
#else
#ifdef VXWORKS_66
#include <timers.h>
#else
#include <sys/time.h>
#endif
#endif
*/



namespace coil
{
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
    Condition(M& mutex)
      : m_mutex(mutex)
    {
      m_cond = semCCreate(SEM_Q_PRIORITY, 0);
/*
#ifdef __RTP__
      m_cond = semCCreate(SEM_Q_PRIORITY, 0);
#else
      ::pthread_cond_init(&m_cond, 0);
#endif
*/
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
      semDelete(m_cond);
/*
#ifdef __RTP__
      semDelete(m_cond);
#else
      ::pthread_cond_destroy(&m_cond);
#endif
*/
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
      semGive(m_cond);
/*
#ifdef __RTP__
      semGive(m_cond);
#else
      ::pthread_cond_signal(&m_cond);
#endif
*/
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
      semFlush(m_cond);
/*
#ifdef __RTP__
      semFlush(m_cond);
#else
      ::pthread_cond_broadcast(&m_cond);
#endif
*/
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
#ifndef __RTP__
      taskLock();
#endif
      m_mutex.unlock();
      STATUS status = semTake(m_cond, WAIT_FOREVER);
#ifndef __RTP__
      taskUnlock();
#endif
      if(status != OK)
      {
            return -1;
      }
      m_mutex.lock();
      return 0;
/*
#ifdef __RTP__
      //taskLock();
      m_mutex.unlock();
      STATUS status = semTake(m_cond, WAIT_FOREVER);
      //taskUnlock();
      if(status != OK)
      {
            return -1;
      }
      m_mutex.lock();
      return 0;
#else
      return 0 == ::pthread_cond_wait(&m_cond, &m_mutex.mutex_);
#endif
*/
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
#ifndef __RTP__
      taskLock();
#endif
      m_mutex.unlock();
      long timeout = (second*1000 + nano_second/1000000l);
      int ticks = (timeout*sysClkRateGet()) / 1000l;
      STATUS status = semTake(m_cond, ticks);
#ifndef __RTP__
      taskUnlock();
#endif

      m_mutex.lock();
      if(status != OK)
      {
            return -1;
      }
      else
      {
            return 0;
      }
/*
#ifdef __RTP__
      //taskLock();
      m_mutex.unlock();
      long timeout = (second*1000 + nano_second/1000000l);
      int ticks = (timeout*sysClkRateGet()) / 1000l;
      STATUS status = semTake(m_cond, ticks);
      //taskUnlock();

      m_mutex.lock();
      if(status != OK)
      {
            return -1;
      }
      else
      {
            return 0;
      }
#else
#ifdef VXWORKS_66
      timespec abstime;
      ::clock_gettime(CLOCK_REALTIME, &abstime);
      abstime.tv_sec  += second;
      abstime.tv_nsec += nano_second;
#else
      struct timeval tv;
      timespec abstime;

      ::gettimeofday(&tv, NULL);
      abstime.tv_sec  = tv.tv_sec + second;
      abstime.tv_nsec = tv.tv_usec * 1000 + nano_second;
#endif
      if (abstime.tv_nsec >= 1000000000) {
        abstime.tv_nsec -= 1000000000;
        abstime.tv_sec ++;
      }
      return 0 == ::pthread_cond_timedwait(&m_cond, &m_mutex.mutex_, &abstime);
#endif
*/
    }

  private:
    Condition(const M&);
    Condition& operator=(const M &);
    SEM_ID m_cond;
/*
#ifdef __RTP__
    SEM_ID m_cond;
#else
    pthread_cond_t m_cond;
#endif
*/
    M& m_mutex;
  };
};
#endif // COIL_CONDITION_H
