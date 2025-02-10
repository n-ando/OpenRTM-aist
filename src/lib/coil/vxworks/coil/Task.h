// -*- C++ -*-
/*!
 * @file Task_vxworks.h
 * @brief Task class
 * @date $Date$
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

#ifndef COIL_TASK_H
#define COIL_TASK_H

#include <vxWorks.h>
#include <taskLib.h>
#include <coil/Mutex.h>
#include <mutex>

namespace coil
{
  /*!
   * @if jp
   *
   * @class Task
   * @brief Task クラス
   *
   * @else
   *
   * @class Task
   * @brief Task class
   *
   * @endif
   */
  class Task
  {
  public:
    /*!
     * @if jp
     *
     * @brief コンストラクタ
     *
     * コンストラクタ
     *
     * @else
     *
     * @brief Constructor
     *
     * Constructor
     *
     * @endif
     */
    Task();

    /*!
     * @if jp
     *
     * @brief デストラクタ
     *
     * デストラクタ
     *
     * @else
     *
     * @brief Destructor
     *
     * Destructor
     *
     * @endif
     */
    virtual ~Task();

    /*!
     * @if jp
     *
     * @brief タスクオープン
     *
     * タスクオープン
     *
     * @param args 引数
     *
     * @else
     *
     * @brief Task open
     *
     * Task open
     *
     * @param args Arguments
     *
     * @endif
     */
    virtual int open(void* args = 0);

    /*!
     * @if jp
     *
     * @brief タスククローズ
     *
     * タスククローズ
     *
     * @param flags フラグ
     *
     * @else
     *
     * @brief Task close
     *
     * Task close
     *
     * @param flags Flags
     *
     * @endif
     */
    virtual int close(unsigned long flags = 0);

    /*!
     * @if jp
     *
     * @brief スレッドを実行する
     *
     * スレッドを実行する
     *
     * @else
     *
     * @brief Execute thread
     *
     * Execute thread
     *
     * @endif
     */
    virtual int svc();

    /*!
     * @if jp
     *
     * @brief スレッドを生成する
     *
     * スレッドを生成する
     *
     * @else
     *
     * @brief Create a thread
     *
     * Create a thread
     *
     * @endif
     */
    virtual void activate();

    /*!
     * @if jp
     *
     * @brief スレッド終了を待つ
     *
     * スレッド終了を待つ
     *
     * @else
     *
     * @brief Waiting for the thread terminate
     *
     * Waiting for the thread terminate
     *
     * @endif
     */
    virtual int wait(void);

    /*!
     * @if jp
     *
     * @brief タスク実行を中断する
     *
     * タスク実行を中断する
     *
     * @else
     *
     * @brief Suspending the task
     *
     * Suspending the task
     *
     * @endif
     */
    virtual int suspend(void);

    /*!
     * @if jp
     *
     * @brief 中断されているタスクを再開する
     *
     * 中断されているタスクを再開する
     *
     * @else
     *
     * @brief Resuming the suspended task
     *
     * Resuming the suspended task
     *
     * @endif
     */
    virtual int resume(void);

    /*!
     * @if jp
     *
     * @brief タスク数リセット
     *
     * タスク数リセット
     *
     * @else
     *
     * @brief Reset of task count
     *
     * Reset of task count
     *
     * @endif
     */
    virtual void reset();

    /*!
     * @if jp
     *
     * @brief タスク実行を終了する
     *
     * タスク実行を終了する
     *
     * @else
     *
     * @brief Finalizing the task
     *
     * Finalizing the task.
     *
     * @endif
     */
    virtual void finalize();

    /*!
     * @if jp
     *
     * @brief スレッド実行を開始する
     *
     * スレッド実行を開始する
     *
     * @param args スレッド引数
     *
     * @else
     *
     * @brief Start thread Execution
     *
     * Start thread Execution
     *
     * @param args Thread arguments
     *
     * @endif
     */
    static void* svc_run(void* args = 0);
/*
#ifdef __RTP__
*/
    /*!
     * @if jp
     *
     * @brief タスクの優先度を設定
     *
     *
     * @param priority 優先度
     *
     * @else
     *
     * @brief 
     *
     *
     * @param priority 
     *
     * @endif
     */
    STATUS set_priority(int priority);
    /*!
     * @if jp
     *
     * @brief タスクの優先度を所得
     *
     *
     * @return priority 優先度
     *
     * @else
     *
     * @brief 
     *
     *
     * @return priority 
     *
     * @endif
     */
     int get_priority();
    /*!
     * @if jp
     *
     * @brief スタックサイズの設定
     *
     *
     * @param stacksize スタックサイズ
     *
     * @else
     *
     * @brief 
     *
     *
     * @param stacksize 
     *
     * @endif
     */
    void set_stacksize(int stacksize);
    coil::Mutex m_waitmutex;
  private:
    int m_count;
    int m_tid;
    int m_priority;
    int m_stacksize;
    void* m_args;
  };

};

#endif // COIL_TASK_H
