// -*- C++ -*-
/*!
 * @file  SimulatorExecutionContext.h
 * @brief Execution context for Choreonoid
 * @date  $Date: 2017-06-12 07:49:59 $
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


#ifndef TEST_EC_H
#define TEST_EC_H



#include <coil/Mutex.h>
#include <coil/Guard.h>
#include <rtm/RTC.h>
#include <rtm/ExecutionContextBase.h>
#include <rtm/OpenHRPExecutionContext.h>


namespace RTC
{
  /*!
   * @if jp
   * @class SimulatorExecutionContext
   * @brief SimulatorExecutionContext クラス
   *
   * Choreonoidのための実行コンテキスト。外部からの tick() 呼び出しにより、1周期
   * 分だけ処理を進めることができる。
   *
   * @else
   * @class SimulatorExecutionContext
   * @brief SimulatorExecutionContext class
   *
   * 
   *
   *
   * @endif
   */
  class SimulatorExecutionContext
	  : public virtual RTC::OpenHRPExecutionContext
  {
	  typedef coil::Mutex Mutex;
	  typedef coil::Guard<coil::Mutex> Guard;
  public:
    /*!
     * @if jp
     * @brief コンストラクタ
     * @else
     * @brief Constructor
     * @endif
     */
    SimulatorExecutionContext();
    /*!
     * @if jp
     * @brief デストラクタ
     * @else
     * @brief Destructor 
     * @endif
     */
    virtual ~SimulatorExecutionContext(void);

    /*!
     * @if jp
     * @brief RTコンポーネントをアクティブ化する
     *
     * 内部でinvokeWorkerPreDo関数を呼ぶため、即座に
     * 状態を遷移させることができる。
     * 現在tick実行中の場合は実行終了まで待つ
     *
     * @param comp アクティブ化対象RTコンポーネント
     *
     * @return ReturnCode_t 型のリターンコード
     *
     * @else
     *
     * @brief Activate an RT-component
     *
     * @param comp The target RT-Component for activation
     *
     * @return The return code of ReturnCode_t type
     *
     * @endif
     */
    virtual RTC::ReturnCode_t
    activate_component(RTC::LightweightRTObject_ptr comp)
      throw (CORBA::SystemException);
    /*!
     * @if jp
     * @brief RTコンポーネントを非アクティブ化する
     *
     * 内部でinvokeWorkerPreDo関数を呼ぶため、即座に
     * 状態を遷移させることができる。
     * 現在tick実行中の場合は実行終了まで待つ
     *
     * @param comp 非アクティブ化対象RTコンポーネント
     *
     * @return ReturnCode_t 型のリターンコード
     *
     * @else
     *
     * @brief Activate an RT-component
     *
     * @param comp The target RT-Component for deactivate
     *
     * @return The return code of ReturnCode_t type
     *
     * @endif
     */
    virtual RTC::ReturnCode_t
    deactivate_component(RTC::LightweightRTObject_ptr comp)
      throw (CORBA::SystemException);
    /*!
     * @if jp
     * @brief RTコンポーネントをリセットする
     *
     * 内部でinvokeWorkerPreDo関数を呼ぶため、即座に
     * 状態を遷移させることができる。
     * 現在tick実行中の場合は実行終了まで待つ
     *
     * @param comp リセット対象RTコンポーネント
     *
     * @return ReturnCode_t 型のリターンコード
     *
     * @else
     *
     * @brief Activate an RT-component
     *
     * @param comp The target RT-Component for reset
     *
     * @return The return code of ReturnCode_t type
     *
     * @endif
     */
    virtual RTC::ReturnCode_t
    reset_component(RTC::LightweightRTObject_ptr comp)
      throw (CORBA::SystemException);

  private:

  };
};



#ifdef WIN32
#pragma warning( default : 4290 )
#endif

extern "C"
{
  /*!
   * @if jp
   * @brief ECFactoryへの登録のための初期化関数
   * @else
   * @brief Initialization function to register to ECFactory
   * @endif
   */
  DLL_EXPORT void SimulatorExecutionContextInit(RTC::Manager* manager);
};

#endif