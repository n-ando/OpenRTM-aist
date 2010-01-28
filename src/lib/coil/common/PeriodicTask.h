// -*- C++ -*-
/*!
 * @file Factory.h
 * @brief generic Factory template class
 * @date $Date$
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2009
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

#ifndef COIL_PERIODICTASK_H
#define COIL_PERIODICTASK_H

#include <map>
#include <string>
#include <vector>
#include <algorithm>

#include <coil/Mutex.h>
#include <coil/Guard.h>
#include <coil/Condition.h>
#include <coil/TimeValue.h>
#include <coil/TimeMeasure.h>
#include <coil/PeriodicTaskBase.h>

namespace coil
{
  /*!
   * @if jp
   * @class 周期タスクスレッド実行クラス
   *
   * 特定の関数を周期実行するためのスレッドオブジェクトを実現する。
   * 使用手順は以下の通り。
   *
   * task; // インスタンス生成
   * task.setTask(TaskFuncBase(obj, mem_func)); // 実行する関数を与える
   * task.activate(); // スレッドをスタートさせる
   *
   * task.suspend(); // 周期実行を止める
   * task.signal(); // 1周期だけ実行
   * task.resume(); // 周期実行を再開
   *
   * task.finalize(); // タスクを終了させる
   * 
   * @else
   * @brief
   *
   * @endif
   */
  class PeriodicTask
    : public coil::PeriodicTaskBase
  {
  public:
    typedef coil::Guard<coil::Mutex> Guard;

    /*!
     * @if jp
     * @brief ctor
     * @else
     * @brief ctor
     * @endif
     */
    PeriodicTask();
    
    /*!
     * @if jp
     * @brief dtor
     * @else
     * @brief dtor
     * @endif
     */
    virtual ~PeriodicTask();
    
    /*!
     * @if jp
     * @brief タスク実行を開始する
     *
     * タスクの実行を開始するためにスレッドをスタートさせる。  タスクが
     * 正常に開始された場合は true が返り、すでにタスクが開始済み、また
     * は実行するタスクが設定されていなければ false を返す。
     *
     * @return true: 正常開始、false: スレッド済みかタスクが未設定である。
     *
     * @else
     * @brief Starting the task
     *
     * Starting a thread to execute a task.  If the task/thread is
     * started properly, it will return 'TRUE'.  if the task/thread
     * are already started or task function object is not set, 'FALSE'
     * will be returned.
     *
     * @return true: normal start, false: already started  or task is not set
     *
     * @endif
     */
    virtual void activate();

    /*!
     * @if jp
     * @brief タスク実行を終了する
     *
     * 実行中のタスクを終了する。
     *
     * @else
     * @brief Finalizing the task
     *
     * Finalizing the task running.
     *
     * @endif
     */
    virtual void finalize();

    /*!
     * @if jp
     * @brief タスク実行を中断する
     *
     * 実行中のタスクを中断する。
     *
     * @else
     * @brief Suspending the task
     *
     * Suspending the task running.
     *
     * @endif
     */
    virtual int suspend(void);

    /*!
     * @if jp
     * @brief 中断されているタスクを再開する
     *
     * 中断されているタスクを再開する
     *
     * @else
     * @brief Resuming the suspended task
     *
     * Resuming the suspended task
     *
     * @endif
     */
    virtual int resume(void);

    /*!
     * @if jp
     * @brief 中断されているタスクを1周期だけ実行する
     *
     * 中断されているタスクを1周期だけ実行する
     *
     * @else
     * @brief Executing the suspended task one tick
     *
     * Executing the suspended task one tick
     *
     * @endif
     */
    virtual void signal();

    /*!
     * @if jp
     * @brief タスク実行関数をセットする
     *
     * @param func int (*)() 型の関数ポインタ
     *
     * @else
     * @brief Setting task execution function
     *
     * @param func Set int (*)() type function pointer
     *
     * @endif
     */
    virtual bool setTask(TaskFuncBase* func, bool delete_in_dtor = true);

    template <class O, class F>
    bool setTask(O* obj, F fun)
    {
      return this->setTask(new TaskFunc<O, F>(obj, fun));
    }

    /*!
     * @if jp
     * @brief タスク実行周期をセットする
     *
     * @param period 実行周期 [sec]
     *
     * @else
     * @brief Setting task execution period
     *
     * @param period Execution period [sec]
     *
     * @endif
     */
    virtual void setPeriod(double period);

    /*!
     * @if jp
     * @brief タスク実行周期をセットする
     *
     * @param period 実行周期
     *
     * @else
     * @brief Setting task execution period
     *
     * @param period Execution period
     *
     * @endif
     */
    virtual void setPeriod(TimeValue& period);

    /*!
     * @if jp
     * @brief タスク関数実行時間計測を有効にするか
     * @else
     * @brief 
     * @endif
     */
    virtual void executionMeasure(bool value);
    
    /*!
     * @if jp
     * @brief タスク関数実行時間計測周期
     * @else
     * @brief 
     * @endif
     */
    virtual void executionMeasureCount(int n);
    
    /*!
     * @if jp
     * @brief タスク周期時間計測を有効にするか
     * @else
     * @brief 
     * @endif
     */
    virtual void periodicMeasure(bool value);
    
    /*!
     * @if jp
     * @brief タスク周期時間計測周期
     * @else
     * @brief 
     * @endif
     */
    virtual void periodicMeasureCount(int n);
    
    /*!
     * @if jp
     * @brief タスク関数実行時間計測結果を取得
     * @else
     * @brief 
     * @endif
     */
    virtual TimeMeasure::Statistics getExecStat();
    
    /*!
     * @if jp
     * @brief タスク周期時間計測結果を取得
     * @else
     * @brief 
     * @endif
     */
    virtual TimeMeasure::Statistics getPeriodStat();
    
  protected:
    virtual int svc();
    virtual void sleep();
    virtual void updateExecStat();
    virtual void updatePeriodStat();

  protected:
    // execution period
    coil::TimeValue m_period;
    bool m_nowait;
    TaskFuncBase* m_func;
    bool m_deleteInDtor;

    // alive flag
    class alive_t
    {
    public:
      alive_t(bool val) : value(val) {}
      bool value;
      coil::Mutex mutex;
    };
    alive_t m_alive;

    // suspend flag
    struct suspend_t
    {
      suspend_t(bool sus) : suspend(sus), mutex(), cond(mutex) {}
      bool suspend;
      coil::Mutex mutex;
      coil::Condition<coil::Mutex> cond;
    };
    suspend_t m_suspend;
      
    // time measurement statistics struct
    struct statistics_t
    {
      coil::TimeMeasure::Statistics stat;
      coil::Mutex mutex;
    };

    // variables for execution time measurement
    bool              m_execMeasure;
    unsigned int      m_execCount;
    unsigned int      m_execCountMax;
    statistics_t      m_execStat;
    coil::TimeMeasure m_execTime;

    // variables for period time measurement
    bool              m_periodMeasure;
    unsigned int      m_periodCount;
    unsigned int      m_periodCountMax;
    statistics_t      m_periodStat;
    coil::TimeMeasure m_periodTime;

  };

}; // namespace coil

#endif // COIL_PERIODICTASK_H
