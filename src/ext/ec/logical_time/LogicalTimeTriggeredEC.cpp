// -*- C++ -*-
/*!
 * @file LogicalTimeTriggeredEC.cpp
 * @brief LogicalTimeTriggeredEC class
 * @date $Date: 2008-01-14 07:49:14 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2007-2008
 *     Noriaki Ando
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: LogicalTimeTriggeredEC.cpp 2307 2012-02-05 21:29:15Z n-ando $
 *
 */

#include <coil/TimeValue.h>
#include <coil/Guard.h>
#include <coil/ClockManager.h>

#include <rtm/ECFactory.h>
#include <rtm/RTObjectStateMachine.h>
#include "LogicalTimeTriggeredEC.h"

namespace RTC
{
  /*!
   * @if jp
   * @brief コンストラクタ
   * @else
   * @brief Constructor
   * @endif
   */
  LogicalTimeTriggeredEC::LogicalTimeTriggeredEC()
    : ExecutionContextBase("exttrig_async_ec"),
      rtclog("exttrig_async_ec"),
      m_clock(coil::ClockManager::instance().getClock("logical")),
      m_syncTick(true), m_count(0),
      m_svc(false)
  {
    RTC_TRACE(("LogicalTimeTriggeredEC()"));

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
  LogicalTimeTriggeredEC::~LogicalTimeTriggeredEC()
  {
    RTC_TRACE(("~LogicalTimeTriggeredEC()"));
    {
      {
        Guard guard(m_svcmutex);
        m_svc = false;
      }
      {
        Guard guard(m_worker.mutex_);
        m_worker.ticked_ = true;
        m_worker.cond_.signal();
      }
    }
    wait();
  }

  void LogicalTimeTriggeredEC::init(coil::Properties& props)
  {
    RTC_TRACE(("init()"));
    ExecutionContextBase::init(props);
    if (props.findNode("sync_tick") != NULL)
      {
        m_syncTick = coil::toBool(props["sync_tick"], "YES", "NO", true);
        RTC_DEBUG(("Tick mode: %s",
                   m_syncTick ? "Synchronous" : "Asynchronous"));
      }
    RTC_DEBUG(("init() done"));
    
  }
  
  /*------------------------------------------------------------
   * Start activity
   * ACE_Task class method over ride.
   *------------------------------------------------------------*/
  /*!
   * @if jp
   * @brief ExecutionContext用アクティビティスレッドを生成する
   * @else
   * @brief Generate internal activity thread for ExecutionContext
   * @endif
   */
  int LogicalTimeTriggeredEC::open(void *args)
  {
    RTC_TRACE(("open()"));
    activate();
    return 0;
  }

  /*!
   * @if jp
   * @brief 各 Component の処理を呼び出す。
   * @else
   * @brief Invoke each component's operation
   * @endif
   */
  int LogicalTimeTriggeredEC::svc(void)
  {
    RTC_TRACE(("svc()"));
    unsigned int count(0);
    do
      {
        {
          Guard gurad(m_worker.mutex_);
          RTC_DEBUG(("Start of worker invocation. ticked = %s",
                     m_worker.ticked_ ? "true" : "false"));
          while (!m_worker.ticked_)
            {
              m_worker.cond_.wait(); // wait for tick
              RTC_DEBUG(("Thread was woken up."));
            }
          if (!m_worker.ticked_) { continue; }
        }
        coil::TimeValue t0(coil::gettimeofday());
        ExecutionContextBase::invokeWorkerPreDo();
        ExecutionContextBase::invokeWorkerDo();
        ExecutionContextBase::invokeWorkerPostDo();
        coil::TimeValue t1(coil::gettimeofday());
        {
          Guard gurad(m_worker.mutex_);
          m_worker.ticked_ = false;
        }
        coil::TimeValue period(getPeriod());
        if (1) //count > 1000)
          {
            RTC_PARANOID(("Period:    %f [s]", (double)period));
            RTC_PARANOID(("Execution: %f [s]", (double)(t1 - t0)));
            RTC_PARANOID(("Sleep:     %f [s]", (double)(period - (t1 - t0))));
          }
        coil::TimeValue t2(coil::gettimeofday());
        if (period > (t1 - t0))
          {
            if (1 /*count > 1000*/) { RTC_PARANOID(("sleeping...")); }
            coil::sleep((coil::TimeValue)(period - (t1 - t0)));
          }
        if (1) //count > 1000)
          {
            coil::TimeValue t3(coil::gettimeofday());
            RTC_PARANOID(("Slept:       %f [s]", (double)(t3 - t2)));
            count = 0;
          }
        ++count;
      } while (threadRunning());

    return 0;
  }

  /*!
   * @if jp
   * @brief ExecutionContext 用のスレッド実行関数
   * @else
   * @brief Thread execution function for ExecutionContext
   * @endif
   */
  int LogicalTimeTriggeredEC::close(unsigned long flags)
  {
    RTC_TRACE(("close()"));
    // At this point, this component have to be finished.
    // Current state and Next state should be RTC_EXITING.
    return 0;
  }

  //============================================================
  // LogicalTimeTriggeredECService
  //============================================================
  /*!
   * @if jp
   * @brief 処理を1ステップ進める
   * @else
   * @brief Move forward one step of ExecutionContext
   * @endif
   */
  void LogicalTimeTriggeredEC::
  tick(::CORBA::ULong sec, ::CORBA::ULong usec)
    throw (CORBA::SystemException)
  {
    RTC_TRACE(("tick(sec = %d, usec = %d)", sec, usec));
    coil::TimeValue time(sec, usec);
    m_clock.settime(time);

    if (!isRunning())
      {
        RTC_DEBUG(("EC is not running. do nothing."))
        return;
      }

    if (m_syncTick) // Synchronous tick mode
      {
        invokeWorker();
      }
    else            // Asynchronous tick mode
      {
        Guard guard(m_worker.mutex_);
        m_worker.ticked_ = true;
        m_worker.cond_.signal();
        RTC_PARANOID(("EC was ticked. Signal was sent to worker thread."));
      }
    return;
  }


  
  void LogicalTimeTriggeredEC::
  get_time(::CORBA::ULong& sec, ::CORBA::ULong& usec)
    throw (CORBA::SystemException)
  {
    coil::TimeValue time(m_clock.gettime());
    sec  = time.sec();
    usec = time.usec();
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
  CORBA::Boolean LogicalTimeTriggeredEC::is_running()
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
  RTC::ReturnCode_t LogicalTimeTriggeredEC::start()
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
  RTC::ReturnCode_t LogicalTimeTriggeredEC::stop()
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
  CORBA::Double LogicalTimeTriggeredEC::get_rate()
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
  RTC::ReturnCode_t LogicalTimeTriggeredEC::set_rate(CORBA::Double rate)
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
  LogicalTimeTriggeredEC::add_component(RTC::LightweightRTObject_ptr comp)
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
  RTC::ReturnCode_t LogicalTimeTriggeredEC::
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
  RTC::ReturnCode_t LogicalTimeTriggeredEC::
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
  RTC::ReturnCode_t LogicalTimeTriggeredEC::
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
  RTC::ReturnCode_t LogicalTimeTriggeredEC::
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
  RTC::LifeCycleState LogicalTimeTriggeredEC::
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
  RTC::ExecutionKind LogicalTimeTriggeredEC::get_kind()
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
  RTC::ExecutionContextProfile* LogicalTimeTriggeredEC::get_profile()
    throw (CORBA::SystemException)
  {
    return ExecutionContextBase::getProfile();
  }

  //============================================================
  // protected functions
  //============================================================
  /*!
   * @brief calling worker
   */
  void LogicalTimeTriggeredEC::invokeWorker()
  {
    RTC_TRACE(("invokeWorker()"));
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
  /*!
   * @brief onStarted() template function
   */
  RTC::ReturnCode_t LogicalTimeTriggeredEC::onStarted()
  {
    // change EC thread state
    Guard gurad(m_svcmutex);
    if (m_syncTick) { return RTC::RTC_OK; }
    if (!m_svc)
      { // If start() is called first time, start the worker thread.
        m_svc = true;
        this->open(0);
      }
    return RTC::RTC_OK;
  }

  /*!
   * @brief onWaitingActivated() template function
   */
  RTC::ReturnCode_t LogicalTimeTriggeredEC::
  onWaitingActivated(RTC_impl::RTObjectStateMachine* comp, long int count)
  {
    RTC_TRACE(("onWaitingActivated(count = %d)", count));
    RTC_PARANOID(("curr: %s, next: %s",
                  getStateString(comp->getStates().curr),
                  getStateString(comp->getStates().next)));
    // Now comp's next state must be ACTIVE state
    // If worker thread is stopped, restart worker thread.

    if (m_syncTick) // Synchronous tick mode
      {
      }
    else            // Asynchronous tick mode
      {
        Guard guard(m_worker.mutex_);
        m_worker.ticked_ = true;
        m_worker.cond_.signal();
      }
    return RTC::RTC_OK;
  }


  /*!
   * @brief onWaitingDeactivated() template function
   */
  RTC::ReturnCode_t LogicalTimeTriggeredEC::
  onWaitingDeactivated(RTC_impl::RTObjectStateMachine* comp, long int count)
  {
    RTC_TRACE(("onWaitingDeactivated(count = %d)", count));
    RTC_PARANOID(("curr: %s, next: %s",
                  getStateString(comp->getStates().curr),
                  getStateString(comp->getStates().next)));
    if (m_syncTick) // Synchronous tick mode
      {
      }
    else            // Asynchronous tick mode
      {
        Guard guard(m_worker.mutex_);
        m_worker.ticked_ = true;
        m_worker.cond_.signal();
      }
    return RTC::RTC_OK;
  }

  /*!
   * @brief onWaitingReset() template function
   */
  RTC::ReturnCode_t LogicalTimeTriggeredEC::
  onWaitingReset(RTC_impl::RTObjectStateMachine* comp, long int count)
  {
    RTC_TRACE(("onWaitingReset(count = %d)", count));
    RTC_PARANOID(("curr: %s, next: %s",
                  getStateString(comp->getStates().curr),
                  getStateString(comp->getStates().next)));
    if (m_syncTick) // Synchronous tick mode
      {
      }
    else            // Asynchronous tick mode
      {
        Guard guard(m_worker.mutex_);
        m_worker.ticked_ = true;
        m_worker.cond_.signal();
      }
    return RTC::RTC_OK;
  }
};


extern "C"
{
  /*!
   * @if jp
   * @brief 当該 ExecutionContext 用Factoryクラスの登録。
   * @else
   * @brief Register Factory class for this ExecutionContext
   * @endif
   */
  void LogicalTimeTriggeredECInit(RTC::Manager* manager)
  {
    RTC::ExecutionContextFactory::
      instance().addFactory("ltt_ec",
                            ::coil::Creator< ::RTC::ExecutionContextBase,
                            ::RTC::LogicalTimeTriggeredEC>,
                            ::coil::Destructor< ::RTC::ExecutionContextBase,
                            ::RTC::LogicalTimeTriggeredEC>);
  }
};
