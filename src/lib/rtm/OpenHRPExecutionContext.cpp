// -*- C++ -*-
/*!
 * @file OpenHRPExecutionContext.cpp
 * @brief OpenHRPExecutionContext class
 * @date $Date$
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006-2008,2012
 *     Noriaki Ando
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id$
 *
 */

#include <rtm/OpenHRPExecutionContext.h>
#include <rtm/ECFactory.h>

namespace RTC
{
  /*!
   * @if jp
   * @brief コンストラクタ
   * @else
   * @brief Constructor
   * @endif
   */
  OpenHRPExecutionContext::OpenHRPExecutionContext()
    :  ExecutionContextBase("exttrig_sync_ec"),
       rtclog("exttrig_sync_ec"), m_count(0)
  {
    RTC_TRACE(("OpenHRPExecutionContext()"));

    // getting my reference
    setObjRef(this->_this());

    // profile initialization
    setKind(RTC::PERIODIC);
    setRate(DEFAULT_EXECUTION_RATE);

    RTC_DEBUG(("Actual period: %d [sec], %d [usec]",
               m_profile.getPeriod().sec(), m_profile.getPeriod().usec()));

  }

  /*!
   * @if jp
   * @brief デストラクタ
   * @else
   * @brief Destructor 
   * @endif
   */
  OpenHRPExecutionContext::~OpenHRPExecutionContext()
  {
    RTC_TRACE(("~OpenHRPExecutionContext()"));
    Guard guard(m_tickmutex);
  }

  //============================================================
  // OpenHRPExecutionContextService
  //============================================================
  /*!
   * @if jp
   * @brief 処理を1ステップ進める
   * @else
   * @brief Move forward one step of ExecutionContext
   * @endif
   */
  void OpenHRPExecutionContext::tick()
    throw (CORBA::SystemException)
  {
    RTC_TRACE(("tick()"));
    if (!isRunning()) { return; }
    Guard guard(m_tickmutex);

    ExecutionContextBase::invokeWorkerPreDo(); // update state
    coil::TimeValue t0(coil::gettimeofday());
    ExecutionContextBase::invokeWorkerDo();
    coil::TimeValue t1(coil::gettimeofday());
    ExecutionContextBase::invokeWorkerPostDo();
    coil::TimeValue t2(coil::gettimeofday());

    coil::TimeValue period(getPeriod());
    if (m_count > 1000)
      {
        RTC_PARANOID(("Period:      %f [s]", (double)period));
        RTC_PARANOID(("Exec-Do:     %f [s]", (double)(t1 - t0)));
        RTC_PARANOID(("Exec-PostDo: %f [s]", (double)(t2 - t1)));
        RTC_PARANOID(("Sleep:       %f [s]", (double)(period - (t2 - t0))));
      }
    coil::TimeValue t3(coil::gettimeofday());
    if (period > (t2 - t0))
      {
        if (m_count > 1000) { RTC_PARANOID(("sleeping...")); }
        coil::sleep((coil::TimeValue)(period - (t2 - t0)));
      }
    if (m_count > 1000)
      {
        coil::TimeValue t4(coil::gettimeofday());
        RTC_PARANOID(("Slept:       %f [s]", (double)(t4 - t3)));
        m_count = 0;
      }
    ++m_count;
    return;
  }

  //============================================================
  // ExecutionContextService
  //============================================================
  /*!
   * @if jp
   * @brief ExecutionContext 実行状態確認関数
   * @else
   * @brief Check for ExecutionContext running state
   * @endif
   */
  CORBA::Boolean OpenHRPExecutionContext::is_running()
    throw (CORBA::SystemException)
  {
    return ExecutionContextBase::isRunning();
  }

  /*!
   * @if jp
   * @brief ExecutionContext の実行を開始
   * @else
   * @brief Start the ExecutionContext
   * @endif
   */
  RTC::ReturnCode_t OpenHRPExecutionContext::start()
    throw (CORBA::SystemException)
  {
    return ExecutionContextBase::start();
  }

  /*!
   * @if jp
   * @brief ExecutionContext の実行を停止
   * @else
   * @brief Stop the ExecutionContext
   * @endif
   */
  RTC::ReturnCode_t OpenHRPExecutionContext::stop()
    throw (CORBA::SystemException)
  {
    return ExecutionContextBase::stop();
  }



  /*!
   * @if jp
   * @brief ExecutionContext の実行周期(Hz)を取得する
   * @else
   * @brief Get execution rate(Hz) of ExecutionContext
   * @endif
   */
  CORBA::Double OpenHRPExecutionContext::get_rate()
    throw (CORBA::SystemException)
  {
    return ExecutionContextBase::getRate();
  }

  /*!
   * @if jp
   * @brief ExecutionContext の実行周期(Hz)を設定する
   * @else
   * @brief Set execution rate(Hz) of ExecutionContext
   * @endif
   */
  RTC::ReturnCode_t OpenHRPExecutionContext::set_rate(CORBA::Double rate)
    throw (CORBA::SystemException)
  {
    return ExecutionContextBase::setRate(rate);
  }

  /*!
   * @if jp
   * @brief RTコンポーネントを追加する
   * @else
   * @brief Add an RT-Component
   * @endif
   */
  RTC::ReturnCode_t
  OpenHRPExecutionContext::add_component(RTC::LightweightRTObject_ptr comp)
    throw (CORBA::SystemException)
  {
    return ExecutionContextBase::addComponent(comp);
  }

  /*!
   * @if jp
   * @brief コンポーネントをコンポーネントリストから削除する
   * @else
   * @brief Remove the RT-Component from participant list
   * @endif
   */
  RTC::ReturnCode_t OpenHRPExecutionContext::
  remove_component(RTC::LightweightRTObject_ptr comp)
    throw (CORBA::SystemException)
  {
    return ExecutionContextBase::removeComponent(comp);
  }

  /*!
   * @if jp
   * @brief RTコンポーネントをアクティブ化する
   * @else
   * @brief Activate an RT-Component
   * @endif
   */
  RTC::ReturnCode_t OpenHRPExecutionContext::
  activate_component(RTC::LightweightRTObject_ptr comp)
    throw (CORBA::SystemException)
  {
    return ExecutionContextBase::activateComponent(comp);
  }

  /*!
   * @if jp
   * @brief RTコンポーネントを非アクティブ化する
   * @else
   * @brief Deactivate an RT-Component
   * @endif
   */
  RTC::ReturnCode_t OpenHRPExecutionContext::
  deactivate_component(RTC::LightweightRTObject_ptr comp)
    throw (CORBA::SystemException)
  {
    return ExecutionContextBase::deactivateComponent(comp);
  }

  /*!
   * @if jp
   * @brief RTコンポーネントをリセットする
   * @else
   * @brief Reset the RT-Component
   * @endif
   */
  RTC::ReturnCode_t OpenHRPExecutionContext::
  reset_component(RTC::LightweightRTObject_ptr comp)
    throw (CORBA::SystemException)
  {
    return ExecutionContextBase::resetComponent(comp);
  }

  /*!
   * @if jp
   * @brief RTコンポーネントの状態を取得する
   * @else
   * @brief Get RT-Component's state
   * @endif
   */
  RTC::LifeCycleState OpenHRPExecutionContext::
  get_component_state(RTC::LightweightRTObject_ptr comp)
    throw (CORBA::SystemException)
  {
    return ExecutionContextBase::getComponentState(comp);
  }

  /*!
   * @if jp
   * @brief ExecutionKind を取得する
   * @else
   * @brief Get the ExecutionKind
   * @endif
   */
  RTC::ExecutionKind OpenHRPExecutionContext::get_kind()
    throw (CORBA::SystemException)
  {
    return ExecutionContextBase::getKind();
  }

  //------------------------------------------------------------
  // ExecutionContextService interfaces
  //------------------------------------------------------------
  /*!
   * @if jp
   * @brief ExecutionContextProfile を取得する
   * @else
   * @brief Get the ExecutionContextProfile
   * @endif
   */
  RTC::ExecutionContextProfile* OpenHRPExecutionContext::get_profile()
    throw (CORBA::SystemException)
  {
    return ExecutionContextBase::getProfile();
  }
};


extern "C"
{
  /*!
   * @if jp
   * @brief ECFactoryへの登録のための初期化関数
   * @else
   * @brief Initialization function to register to ECFactory
   * @endif
   */
  void OpenHRPExecutionContextInit(RTC::Manager* manager)
  {
    RTC::ExecutionContextFactory::
      instance().addFactory("SynchExtTriggerEC",
                            ::coil::Creator< ::RTC::ExecutionContextBase,
                            ::RTC::OpenHRPExecutionContext>,
                            ::coil::Destructor< ::RTC::ExecutionContextBase,
                            ::RTC::OpenHRPExecutionContext>);
  }
};
