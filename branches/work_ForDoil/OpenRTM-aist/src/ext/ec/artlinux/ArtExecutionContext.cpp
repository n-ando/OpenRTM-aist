// -*- C++ -*-
/*!
 * @file ArtExecutionContext.cpp
 * @brief ArtExecutionContext class
 * @date $Date: 2008-01-14 07:53:01 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006-2008,2012
 *     Noriaki Ando
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: ArtExecutionContext.cpp 2307 2012-02-05 21:29:15Z n-ando $
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sched.h>
#include <sys/mman.h>
#include <linux/art_task.h>

#include <algorithm>
#include <iostream>

#include <coil/Time.h>
#include <coil/TimeValue.h>

#include <rtm/RTObjectStateMachine.h>
#include <ArtExecutionContext.h>

#define MAX_SAFE_STACK (8*1024)
#define NSEC_PER_SEC 1000000000
#define DEEFAULT_PERIOD 0.000001

namespace RTC_exp
{
  /*!
   * @if jp
   * @brief デフォルトコンストラクタ
   * @else
   * @brief Default constructor
   * @endif
   */
  ArtExecutionContext::
  ArtExecutionContext()
    : ExecutionContextBase("artlinux_ec"),
      rtclog("artlinux_ec"),
      m_svc(false), m_nowait(false)
  {
    RTC_TRACE(("ArtExecutionContext()"));

    // getting my reference
    setObjRef(this->_this());

    // profile initialization
    setKind(RTC::PERIODIC);
    setRate(1.0 / (double)DEEFAULT_PERIOD);

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
  ArtExecutionContext::~ArtExecutionContext()
  {
    RTC_TRACE(("~ArtExecutionContext()"));
    {
      Guard guard(m_svcmutex);
      m_svc = false;
    }
    {
      Guard guard(m_workerthread.mutex_);
      m_workerthread.running_ = true;
      m_workerthread.cond_.signal();
    }
    wait();
  }

  void ArtExecutionContext::init(coil::Properties& props)
  {
    RTC_TRACE(("init()"));
    ExecutionContextBase::init(props);

    setPriority(props);
    m_currPeriod = getPeriod();
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
  int ArtExecutionContext::open(void *args)
  {
    RTC_TRACE(("open()"));
    activate();
    return 0;
  }

  /*!
   * @if jp
   * @brief ExecutionContext 用のスレッド実行関数
   * @else
   * @brief Thread execution function for ExecutionContext
   * @endif
   */
  int ArtExecutionContext::svc(void)
  {
    RTC_TRACE(("svc()"));
    if (!prepareThread()) { return -1; }
    m_currPeriod = getPeriod();

    int count(0);
    coil::TimeValue t0, t1, t2, t3;
    do
      {
        ExecutionContextBase::invokeWorkerPreDo();
        {
          Guard guard(m_workerthread.mutex_);
          while (!m_workerthread.running_)
            {
              m_workerthread.cond_.wait();
            }
        }
        if (count > 1000) { t0 = coil::gettimeofday(); }
        ExecutionContextBase::invokeWorkerDo();
        ExecutionContextBase::invokeWorkerPostDo();
        if (count > 1000) { t1 = coil::gettimeofday(); }

        changeRate(); // if period changed: art_exit() -> art_enter()
        if (count > 1000)
          {
            RTC_PARANOID(("Period:    %f [s]", (double)m_currPeriod));
            RTC_PARANOID(("Execution: %f [s]", (double)(t1 - t0)));
            RTC_PARANOID(("Sleep:     %f [s]",
                          (double)(m_currPeriod - (t1 - t0))));
          }
        if (count > 1000) { t2 = coil::gettimeofday(); }
        if (m_nowait)
          {
            if (count > 1000) { count = 0; }
            ++count; continue;
          }
        if (art_wait() == -1)
          {
            RTC_ERROR(("fatal error: art_wait"));
            std::cerr << "fatal error: art_wait" << std::endl;
          }
        if (count > 1000)
          {
            t3 = coil::gettimeofday();
            RTC_PARANOID(("Slept:     %f [s]", (double)(t3 - t2)));
            count = 0;
          }
        ++count;
      } while (threadRunning());
    if (art_exit() == -1)
      {
        RTC_ERROR(("Fatal error: art_exit()"));
        std::cerr << "fatal error: art_exit" << std::endl;
      }
    RTC_DEBUG(("Thread terminated."));
    return 0;
  }

  /*!
   * @if jp
   * @brief ExecutionContext 用のスレッド実行関数
   * @else
   * @brief Thread execution function for ExecutionContext
   * @endif
   */
  int ArtExecutionContext::close(unsigned long flags)
  {
    RTC_TRACE(("close()"));
    // At this point, this component have to be finished.
    // Current state and Next state should be RTC_EXITING.
    return 0;
  }


  //============================================================
  // ExecutionContext CORBA operations
  //============================================================
  /*!
   * @if jp
   * @brief ExecutionContext 実行状態確認関数
   * @else
   * @brief Check for ExecutionContext running state
   * @endif
   */
  CORBA::Boolean ArtExecutionContext::is_running()
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
  RTC::ReturnCode_t ArtExecutionContext::start()
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
  RTC::ReturnCode_t ArtExecutionContext::stop()
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
  CORBA::Double ArtExecutionContext::get_rate()
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
  RTC::ReturnCode_t ArtExecutionContext::set_rate(CORBA::Double rate)
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
  ArtExecutionContext::add_component(RTC::LightweightRTObject_ptr comp)
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
  RTC::ReturnCode_t ArtExecutionContext::
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
  RTC::ReturnCode_t ArtExecutionContext::
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
  RTC::ReturnCode_t ArtExecutionContext::
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
  RTC::ReturnCode_t ArtExecutionContext::
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
  RTC::LifeCycleState ArtExecutionContext::
  get_component_state(RTC::LightweightRTObject_ptr comp)
    throw (CORBA::SystemException)
  {
    RTC::LifeCycleState ret = ExecutionContextBase::getComponentState(comp);
    return ret;
  }

  /*!
   * @if jp
   * @brief ExecutionKind を取得する
   * @else
   * @brief Get the ExecutionKind
   * @endif
   */
  RTC::ExecutionKind ArtExecutionContext::get_kind()
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
  RTC::ExecutionContextProfile* ArtExecutionContext::get_profile()
    throw (CORBA::SystemException)
  {
    return ExecutionContextBase::getProfile();
  }


  //============================================================
  // protected functions
  //============================================================
  /*!
   * @brief onStarted() template function
   */
  RTC::ReturnCode_t ArtExecutionContext::onStarted()
  {
    // change EC thread state
    {
      Guard guard(m_svcmutex);
      if (!m_svc)
        {
          m_svc = true;
          this->open(0);
        }
    }
    if (isAllNextState(RTC::INACTIVE_STATE))
      {
        Guard guard(m_workerthread.mutex_);
        m_workerthread.running_ = false;
      }
    else
      {
        Guard guard(m_workerthread.mutex_);
        m_workerthread.running_ = true;
        m_workerthread.cond_.signal();
      }
    return RTC::RTC_OK;
  }

  /*!
   * @brief onStopping() template function
   */
  RTC::ReturnCode_t ArtExecutionContext::onStopping()
  {
    // stop thread
    Guard guard(m_workerthread.mutex_);
    m_workerthread.running_ = false;
    return RTC::RTC_OK;
  }

  /*!
   * @brief onWaitingActivated() template function
   */
  RTC::ReturnCode_t ArtExecutionContext::
  onWaitingActivated(RTC_impl::RTObjectStateMachine* comp, long int count)
  {
    RTC_TRACE(("onWaitingActivated(count = %d)", count));
    RTC_PARANOID(("curr: %s, next: %s",
                  getStateString(comp->getStates().curr),
                  getStateString(comp->getStates().next)));
    // Now comp's next state must be ACTIVE state
    // If worker thread is stopped, restart worker thread.
    Guard guard(m_workerthread.mutex_);
    if (m_workerthread.running_ == false)
      {
        m_workerthread.running_ = true;
        m_workerthread.cond_.signal();
      }
    return RTC::RTC_OK;
  }

  /*!
   * @brief onActivated() template function
   */
  RTC::ReturnCode_t ArtExecutionContext::
  onActivated(RTC_impl::RTObjectStateMachine* comp, long int count)
  {
    RTC_TRACE(("onActivated(count = %d)", count));
    RTC_PARANOID(("curr: %s, next: %s",
                  getStateString(comp->getStates().curr),
                  getStateString(comp->getStates().next)));
    // count = -1; Asynch mode. Since onWaitingActivated is not
    // called, onActivated() have to send restart singnal to worker
    // thread.
    // count > 0: Synch mode.

    // Now comp's next state must be ACTIVE state
    // If worker thread is stopped, restart worker thread.
    Guard guard(m_workerthread.mutex_);
    if (m_workerthread.running_ == false)
      {
        m_workerthread.running_ = true;
        m_workerthread.cond_.signal();
      }
    return RTC::RTC_OK;
  }

  /*!
   * @brief onWaitingDeactivated() template function
   */
  RTC::ReturnCode_t ArtExecutionContext::
  onWaitingDeactivated(RTC_impl::RTObjectStateMachine* comp, long int count)
  {
    RTC_TRACE(("onWaitingDeactivated(count = %d)", count));
    RTC_PARANOID(("curr: %s, next: %s",
                  getStateString(comp->getStates().curr),
                  getStateString(comp->getStates().next)));
    if (isAllNextState(RTC::INACTIVE_STATE))
      {
        Guard guard(m_workerthread.mutex_);
        if (m_workerthread.running_ == true)
          {
            m_workerthread.running_ = false;
            RTC_TRACE(("All RTCs are INACTIVE. Stopping worker thread."));
          }
      }
    return RTC::RTC_OK;
  }

  /*!
   * @brief onDeactivated() template function
   */
  RTC::ReturnCode_t ArtExecutionContext::
  onDeactivated(RTC_impl::RTObjectStateMachine* comp, long int count)
  {
    RTC_TRACE(("onDeactivated(count = %d)", count));
    RTC_PARANOID(("curr: %s, next: %s",
                  getStateString(comp->getStates().curr),
                  getStateString(comp->getStates().next)));
    if (isAllNextState(RTC::INACTIVE_STATE))
      {
        Guard guard(m_workerthread.mutex_);
        if (m_workerthread.running_ == true)
          {
            m_workerthread.running_ = false;
            RTC_TRACE(("All RTCs are INACTIVE. Stopping worker thread."));
          }
      }
    return RTC::RTC_OK;
  }

  /*!
   * @brief onWaitingReset() template function
   */
  RTC::ReturnCode_t ArtExecutionContext::
  onWaitingReset(RTC_impl::RTObjectStateMachine* comp, long int count)
  {
    RTC_TRACE(("onWaitingReset(count = %d)", count));
    RTC_PARANOID(("curr: %s, next: %s",
                  getStateString(comp->getStates().curr),
                  getStateString(comp->getStates().next)));
    if (isAllNextState(RTC::INACTIVE_STATE))
      {
        Guard guard(m_workerthread.mutex_);
        if (m_workerthread.running_ == true)
          {
            m_workerthread.running_ = false;
            RTC_TRACE(("All RTCs are INACTIVE. Stopping worker thread."));
          }
      }
    return RTC::RTC_OK;
  }

  /*!
   * @brief onReset() template function
   */
  RTC::ReturnCode_t ArtExecutionContext::
  onReset(RTC_impl::RTObjectStateMachine* comp, long int count)
  {
    RTC_TRACE(("onReset(count = %d)", count));
    RTC_PARANOID(("curr: %s, next: %s",
                  getStateString(comp->getStates().curr),
                  getStateString(comp->getStates().next)));
    if (isAllNextState(RTC::INACTIVE_STATE))
      {
        Guard guard(m_workerthread.mutex_);
        if (m_workerthread.running_ == true)
          {
            m_workerthread.running_ = false;
            RTC_TRACE(("All RTCs are INACTIVE. Stopping worker thread."));
          }
      }
    return RTC::RTC_OK;
  }

  //============================================================
  // private functions
  //============================================================
  /*!
   * @if jp
   * @brief スレッドの準備
   * @else
   * @brief Preparing thread
   * @endif
   */
  bool ArtExecutionContext::prepareThread()
  {
    assert(m_priority <= ART_PRIO_MAX);
    coil::TimeValue period(getPeriod());
    int usec_period(period.sec() * 1000000 + period.usec());
    if (art_enter(m_priority, ART_TASK_PERIODIC, usec_period) == -1)
      {
        return false;
        std::cerr << "fatal error: art_enter" << std::endl;
      }
    return true;
  }

  /*!
   * @if jp
   * @brief 優先度の設定
   * @else
   * @brief Setting a priority
   * @endif
   */
  void ArtExecutionContext::
  setPriority(coil::Properties& prop)
  {
    RTC_TRACE(("setPriority()"));
    getProperty(prop, "priority", m_priority);
    RTC_DEBUG(("setPriority(): priority: %d", m_priority));
  }

  /*!
   * @if jp
   * @brief 実行周期の変更
   * @else
   * @brief Changing execution rate
   * @endif
   */
  bool ArtExecutionContext::changeRate()
  {
    coil::TimeValue next_period(getPeriod());
    if (m_currPeriod.sec() == next_period.sec() &&
        m_currPeriod.usec() == next_period.usec()) { return true; }

    RTC_PARANOID(("Period changed."));
    if (art_exit() == -1)
      {
        RTC_PARANOID(("art_exit() failed."));
        std::cerr << "error: art_exit" << std::endl;
        return false;
      }
    int new_period(next_period.sec() * 1000000 + next_period.usec());
    if (art_enter(m_priority, ART_TASK_PERIODIC, new_period) == -1)
      {
        RTC_PARANOID(("art_enter() failed."));
        std::cerr << "error: art_enter" << std::endl;
        return false;
      }
    m_currPeriod = next_period;
    return true;
  }

}; // namespace RTC

extern "C"
{
  /*!
   * @if jp
   * @brief ECFactoryへの登録のための初期化関数
   * @else
   * @brief Initialization function to register to ECFactory
   * @endif
   */

 void ArtExecutionContextInit(RTC::Manager* manager)
  {
    RTC::ExecutionContextFactory::
      instance().addFactory("ArtExecutionContext",
                            ::coil::Creator< ::RTC::ExecutionContextBase,
                            ::RTC_exp::ArtExecutionContext>,
                            ::coil::Destructor< ::RTC::ExecutionContextBase,
                            ::RTC_exp::ArtExecutionContext>);
    RTC::ExecutionContextFactory::
      instance().addFactory("artlinux_ec",
                            ::coil::Creator< ::RTC::ExecutionContextBase,
                            ::RTC_exp::ArtExecutionContext>,
                            ::coil::Destructor< ::RTC::ExecutionContextBase,
                            ::RTC_exp::ArtExecutionContext>);
  }
};

