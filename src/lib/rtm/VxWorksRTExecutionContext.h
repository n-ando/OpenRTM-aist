// -*- C++ -*-
/*!
 * @file VxWorksRTExecutionContext.h
 * @brief VxWorksRTExecutionContext class
 * @date $Date: 2017-07-11 10:53:05 $
 * @author Nobuhiko Miyamoto <n-miyamoto@aist.go.jp>
 *
 * Copyright (C) 2017
 *     Nobuhiko Miyamoto
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 *
 */

#ifndef RTC_VXWORKSRTEXECUTIONCONTEXT_H
#define RTC_VXWORKSRTEXECUTIONCONTEXT_H

#include <vector>
#include <iostream>

#include <coil/Task.h>
#include <coil/Mutex.h>
#include <coil/Condition.h>

#include <rtm/PeriodicExecutionContext.h>



namespace RTC_exp
{
  class TimeValue_nano;
  /*!
   * @if jp
   * @class VxWorksRTExecutionContext
   * @brief VxWorksRTExecutionContext クラス
   *
   * Periodic Sampled Data Processing(周期実行用)ExecutionContextクラス。
   *
   * @since 0.4.0
   *
   * @else
   * @class VxWorksRTExecutionContext
   * @brief VxWorksRTExecutionContext class
   *
   * Periodic Sampled Data Processing (for the execution cycles)
   * ExecutionContext class
   *
   * @since 0.4.0
   *
   * @endif
   */
  class VxWorksRTExecutionContext
      : public RTC_exp::PeriodicExecutionContext
  {
  public:
    /*!
     * @if jp
     * @brief デフォルトコンストラクタ
     *
     * デフォルトコンストラクタ
     * プロファイルに以下の項目を設定する。
     *  - kind : PERIODIC
     *  - rate : 0.0
     *
     * @else
     * @brief Default Constructor
     *
     * Default Constructor
     * Set the following items to profile.
     *  - kind : PERIODIC
     *  - rate : 0.0
     *
     * @endif
     */
    VxWorksRTExecutionContext();

    /*!
     * @if jp
     * @brief デストラクタ
     *
     * デストラクタ
     *
     * @else
     * @brief Destructor
     *
     * Destructor
     *
     * @endif
     */
    virtual ~VxWorksRTExecutionContext(void);

    /*!
     * @if jp
     * @brief ExecutionContextの初期化を行う
     *
     * ExecutionContextの初期化処理
     *
     * @else
     * @brief Initialize the ExecutionContext
     *
     * This operation initialize the ExecutionContext
     *
     * @endif
     */
    virtual  void init(coil::Properties& props);

    /*!
     * @if jp
     * @brief ExecutionContext 用のスレッド実行関数
     *
     * ExecutionContext 用のスレッド実行関数。登録されたコンポーネント
     * の処理を呼び出す。
     *
     * @return 実行結果
     *
     * @else
     * @brief Thread execution function for ExecutionContext
     *
     * Thread execution function for ExecutionContext.  Invoke the
     * registered components operation.
     *
     * @return The execution result
     *
     * @endif
     */
    virtual int svc(void);



  protected:
  private:
    /*!
     * @if jp
     * @brief 優先度の設定
     *
     * @param prop
     *
     * @return 
     *
     * @else
     * @brief set priority
     * 
     * @param prop
     *
     * @return 
     *
     * @endif
     */
   void setPriority(coil::Properties& props);
    /*!
     * @if jp
     * @brief スタックサイズの設定
     *
     * @param prop
     *
     * @return 
     *
     * @else
     * @brief set stack size
     * 
     * @param prop
     *
     * @return 
     *
     * @endif
     */
   void setStackSize(coil::Properties& props);
    /*!
     * @if jp
     * @brief ナノ秒単位のsleep
     *
     * @param interval
     *
     * @return 
     *
     * @else
     * @brief 
     * 
     * @param interval
     *
     * @return 
     *
     * @endif
     */
   int sleep_nano(TimeValue_nano interval);
  }; // class VxWorksRTExecutionContext
  class TimeValue_nano
  {
  public:
    TimeValue_nano(long sec=0, long usec=0);
    TimeValue_nano(double timeval);
    ~TimeValue_nano();
    TimeValue_nano operator-(TimeValue_nano& tm);
    TimeValue_nano operator+(TimeValue_nano& tm);
    TimeValue_nano operator=(double time);
    operator double() const;
    int sign() const;
    void normalize();
    inline long int sec() const {return m_sec;}
    inline long int nsec() const {return m_nsec;}
  private:
    long int m_sec;
    long int m_nsec;
  };
} // namespace RTC


extern "C"
{
  /*!
   * @if jp
   * @brief ECFactoryへの登録のための初期化関数
   * @else
   * @brief Initialization function to register to ECFactory
   * @endif
   */
  void VxWorksRTExecutionContextInit(RTC::Manager* manager);
};

#endif // RTC_VXWORKSRTEXECUTIONCONTEXT_H

