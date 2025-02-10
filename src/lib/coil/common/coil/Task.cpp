// -*- C++ -*-
/*!
 * @file Task_posix.cpp
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

#include <coil/Task.h>

namespace coil
{

  /*!
   * @if jp
   * @brief コンストラクタ
   * @else
   * @brief Constructor
   * @endif
   */
  Task::Task() = default;

  /*!
   * @if jp
   * @brief デストラクタ
   * @else
   * @brief Destructor
   * @endif
   */
  Task::~Task() = default;

  /*!
   * @if jp
   * @brief タスクオープン
   * @else
   * @brief Task open
   * @endif
   */
  int Task::open(void*  /*args*/)
  {
    return 0;
  }

  /*!
   * @if jp
   * @brief タスククローズ
   * @else
   * @brief Task close
   * @endif
   */
  int Task::close(unsigned long  /*flags*/)
  {
    return 0;
  }

  /*!
   * @if jp
   * @brief スレッドを生成する
   * @else
   * @brief Create a thread
   * @endif
   */
  void Task::activate()
  {
    if (!m_thread.joinable())
      {
        m_thread = std::thread([this] {
                                   svc();
                                   finalize();
                               });
      }
  }

  /*!
   * @if jp
   * @brief スレッド終了を待つ
   * @else
   * @brief Waiting for the thread terminate
   * @endif
   */
  int Task::wait()
  {
      if (m_thread.joinable())
      {
        m_thread.join();
      }
    return 0;
  }

  /*!
   * @if jp
   * @brief タスク実行を中断する
   * @else
   * @brief Suspending the task
   * @endif
   */
  int Task::suspend()
  {
    return 0;
  }

  /*!
   * @if jp
   * @brief 中断されているタスクを再開する
   * @else
   * @brief Resuming the suspended task
   * @endif
   */
  int Task::resume()
  {
    return 0;
  }

  /*!
   * @if jp
   * @brief タスク実行を終了する
   * @else
   * @brief Finalizing the task
   * @endif
   */
  void Task::finalize()
  {
  }

} // namespace coil
