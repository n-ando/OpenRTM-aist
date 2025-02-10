// -*- C++ -*-
/*!
 * @file Task_posix.h
 * @brief Task class
 * @date $Date$
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2008
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id$
 *
 */

#ifndef COIL_TASK_H
#define COIL_TASK_H

#include <thread>

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
    virtual int open(void* args = nullptr);

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
    virtual int svc() = 0;

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
    virtual int wait();

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
    virtual int suspend();

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
    virtual int resume();

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

  private:
    std::thread m_thread;
  };
} // namespace coil

#endif  // COIL_TASK_H
