// -*- C++ -*-
/*!
 * @file Timer.h
 * @brief Timer class
 * @date $Date: 2007-04-26 15:34:05 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2007-2008
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: Timer.h 826 2008-08-26 08:13:39Z n-ando $
 *
 */

#ifndef Timer_h
#define Timer_h

#include <chrono>
#include <functional>
#include <list>
#include <memory>
#include <mutex>
#include <utility>

namespace coil
{
  /*!
   * @if jp
   * @class DelayedFunction
   * @brief 実行遅延関数呼び出し
   * @since 2.0.0
   * @else
   * @class DelayedFunction
   * @brief Delayed function call
   * @since 2.0.0
   * @endif
   */
  class DelayedFunction
  {
  public:
    /*!
     * @if jp
     * @brief コンストラクタ
     * @param fn: 実行する関数または関数オブジェクト
     * @param delay: 実行までの遅延時間
     *
     * @else
     * @brief Constructor
     * @param fn Function or functional object
     * @param delay the delay until function call
     *
     * @endif
     */
    DelayedFunction(std::function<void(void)> fn,
                    std::chrono::nanoseconds delay) noexcept
      : m_fn(std::move(fn)), m_remains(delay) {}

    /*!
     * @if jp
     * @brief 1回の時間経過
     * @param interval 経過した時間
     * @return bool true:  期限が来た
     *              false: 期限が来ていない
     *
     * interval 分だけ期限を減算し、期限切れの場合に関数を実行する。
     *
     * @else
     * @brief Tick
     * @param interval Tick interval
     * @return bool true:  The function is expired and executed.
     *              false: The function is unexpired.
     * @endif
     */
    bool tick(std::chrono::nanoseconds interval);

  private:
    std::function<void(void)> const m_fn;
    std::chrono::nanoseconds m_remains;
  };

  /*!
   * @if jp
   * @class PeriodicFunction
   * @brief 周期関数呼び出し
   * @since 2.0.0
   * @else
   * @class PeriodicFunction
   * @brief Periodic function call
   * @since 2.0.0
   * @endif
   */
  class PeriodicFunction
  {
  public:
    /*!
     * @if jp
     * @brief コンストラクタ
     * @param fn 実行する関数または関数オブジェクト
     * @param period 実行間隔
     *
     * @else
     * @brief Constructor
     * @param fn Function or functional object
     * @param period the period of function exectuion
     *
     * @endif
     */
    PeriodicFunction(std::function<void(void)> fn,
                     std::chrono::nanoseconds period) noexcept
      : m_fn(std::move(fn)), m_remains(period), m_period(period) {}

    /*!
     * @if jp
     * @brief 1回の時間経過
     * @param interval 経過した時間
     * @return bool true 固定
     *
     * interval 分だけ期限を減算し、期限切れの場合に関数を実行する。
     * 関数が実行されると周期が再設定される。
     *
     * @else
     * @brief Tick
     * @param interval Tick interval
     * @return bool true only
     * @endif
     */
    bool tick(std::chrono::nanoseconds interval);

    /*!
     * @if jp
     * @brief 周期実行を停止する
     * @else
     * @brief Stop to execute function
     * @endif
     */
    void stop();

  private:
    std::function<void(void)> const m_fn;
    std::chrono::nanoseconds m_remains;
    std::chrono::nanoseconds const m_period;
    bool m_isRemoved = false;
    // This lock ensures that tick() is not running when stop() completes.
    std::mutex m_lock;
  };

  /*!
   * @if jp
   * @class Timer
   * @brief Manager のスレッド上で遅延実行される関数群の管理
   *
   * emplace() にて指定される関数や関数オブジェクトをtick()の中で
   * テンプレートパラメター Function を通して呼び出す。Function は、
   * "bool tick(nanoseconds)" をメンバーに持たなければならない。emplace()
   * された関数を実際に呼び出すべきかは Function が時間管理とともに判断する。
   * 本クラスは Function をリスト管理する。リストの各要素毎に tick() が
   * true を返すとき、本クラスはリストから消去する。Function にポインター
   * を指定する場合は資源開放漏れを避けるために、unique_ptr や shared_ptr
   * を用いること。(For ex. Timer(std::unique_ptr<F>>)
   *
   * @since 2.0.0
   * @else
   * @class Timer
   * @brief Management of Delayed functions on the Manager thread.
   * @since 2.0.0
   * @endif
   */
  template <class Function>
  class Timer {
  public:
    using TaskId = Function*;
    Timer() = default;
    Timer(Timer const&) = delete;
    Timer& operator=(Timer const&) = delete;
    // If you need to  move, implement it.
    Timer(Timer&&) = delete;
    Timer& operator=(Timer&&) = delete;

    /*!
     * @if jp
     * @brief 非同期処理を登録する
     * @else
     * @brief Add an async function into list.
     * @endif
     */
    template <class... Args>
    TaskId emplace(Args&&... args)
    {
      std::lock_guard<std::mutex> guard(m_lock);
      m_tasks.emplace_back(std::forward<Args>(args)...);
      return &(m_tasks.back());
    }

    /*!
     * @if jp
     * @brief 1回の時間経過
     * @param interval 経過した時間
     *
     * 時間経過により、リスト上の期限切れとなった関数を実行する。
     * 実行した関数が true を返すとき、リストから削除する。
     *
     * @else
     * @brief One tick passes
     * @param interval One tick interval
     *
     * This operation execute expired functions and remove it from the list
     * if tick() returns true.
     *
     * @endif
     */
    void tick(std::chrono::nanoseconds interval)
    {
      // Move m_tasks to tasks.
      decltype(m_tasks) tasks;
      {
        std::lock_guard<std::mutex> guard(m_lock);
        tasks.swap(m_tasks);
      }

      // Tick each task and remove from the list what returned true.
      for (auto&& x = tasks.begin(); x != tasks.end();
           x = toRef(*x).tick(interval) ? tasks.erase(x) : std::next(x));

      // Feed back remain tasks to m_tasks.
      if (!tasks.empty())
      {
        std::lock_guard<std::mutex> guard(m_lock);
        m_tasks.splice(m_tasks.end(), std::move(tasks));
      }
    }
  private:
    std::list<Function> m_tasks;
    std::mutex m_lock;
    template <class Fn> Fn& toRef(Fn& x){ return x; }
    template <class Fn> Fn& toRef(Fn* x){ return *x; }
    template <class Fn> Fn& toRef(std::unique_ptr<Fn>& x){ return *x; }
    template <class Fn> Fn& toRef(std::shared_ptr<Fn>& x){ return *x; }
  };
} // namespace coil
#endif  // Timer_h
