// -*- C++ -*-
/*!
 * @file ExtTrigExecutionContext.h
 * @brief ExtTrigExecutionContext class
 * @date $Date: 2007-12-31 03:08:03 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2007
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: ExtTrigExecutionContext.h,v 1.2.2.1 2007-12-31 03:08:03 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.2  2007/04/26 15:29:39  n-ando
 * The header include order was modified to define _REENTRANT before
 * including ace/config-lite.h in Linux systems.
 * In ace 5.4.7 or later, _REENTRANT flag should be defined explicitly.
 *
 * Revision 1.1  2007/04/13 16:08:24  n-ando
 * External Triggered ExecutionContext class.
 *
 */

#ifndef ExtTrigExecutionContext_h
#define ExtTrigExecutionContext_h

#include <rtm/RTC.h>

#include <ace/Task.h>
#include <ace/Synch.h>

#include <rtm/Manager.h>
#include <rtm/PeriodicExecutionContext.h>

namespace RTC
{
  /*!
   * @if jp
   * @class ExtTrigExecutionContext
   * @brief ステップ実行が可能な ExecutionContext クラス
   *
   * 1周期毎の実行が可能なPeriodic Sampled Data Processing(周期実行用)
   * ExecutionContextクラス。
   * 外部からのメソッド呼びだしによって時間が１周期づつ進む。
   *
   * @since 0.4.0
   *
   * @else
   *
   * @endif
   */
  class ExtTrigExecutionContext
    : public virtual PeriodicExecutionContext
  {
  public:
    /*!
     * @if jp
     * @brief コンストラクタ
     *
     * コンストラクタ
     *
     * @else
     * @brief Constructor
     * @endif
     */
    ExtTrigExecutionContext();
    
    /*!
     * @if jp
     * @brief デストラクタ
     *
     * デストラクタ
     *
     * @else
     * @brief Destructor
     * @endif
     */
    virtual ~ExtTrigExecutionContext();
    
    /*!
     * @if jp
     * @brief 処理を1ステップ進める
     *
     * ExecutionContextの処理を１周期分進める。
     *
     * @else
     *
     * @endif
     */
    virtual void tick();
    
    /*!
     * @if jp
     * @brief 各 Component の処理を呼び出す。
     *
     * ExecutionContext に attach されている各 Component の処理を呼び出す。
     * 全 Component の処理を呼び出した後、次の呼出が発生するまで休止する。
     *
     * @return 処理結果
     *
     * @else
     *
     * @endif
     */
    virtual int svc(void);
    
  private:
    struct Worker
    {
      Worker() : _cond(_mutex), _called(false) {};
      ACE_Thread_Mutex _mutex;
      ACE_Condition<ACE_Thread_Mutex> _cond;
      bool _called;
    };
    // A condition variable for external triggered worker
    Worker m_worker;
  };
};

extern "C"
{
  /*!
   * @if jp
   * @brief 当該 ExecutionContext 用Factoryクラスの登録。
   *
   * このExecutionContextを生成するFactoryクラスを
   * ExecutionContext管理用ObjectManagerに登録する。
   *
   * @else
   *
   * @endif
   */
  void ExtTrigExecutionContextInit(RTC::Manager* manager);
};

#endif // ExtTrigExecutionContext_h
