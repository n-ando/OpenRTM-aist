// -*- C++ -*-
/*!
 * @file PeriodicExecutionContext.cpp
 * @brief PeriodicExecutionContext class
 * @date $Date: 2008-01-14 07:53:01 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006-2008
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

#include <coil/Time.h>
#include <coil/TimeValue.h>
#include <rtm/PeriodicExecutionContext.h>
#include <rtm/RTObject.h>
#include <algorithm>
#include <iostream>

namespace RTC
{
  /*!
   * @if jp
   * @brief デフォルトコンストラクタ
   * @else
   * @brief Default constructor
   * @endif
   */
  PeriodicExecutionContext::
  PeriodicExecutionContext()
    : rtclog("periodic_ec"), m_running(false), m_svc(true), m_nowait(false)
  {
    RTC_TRACE(("PeriodicExecutionContext()"));
    m_profile.kind = PERIODIC;
    m_profile.rate = 0.0;
    m_usec = (long int)0;
    m_ref = this->_this();
  }
  
  /*!
   * @if jp
   * @brief コンストラクタ
   * @else
   * @brief Construnctor
   * @endif
   */
  PeriodicExecutionContext::
  PeriodicExecutionContext(OpenRTM::DataFlowComponent_ptr owner,
			   double rate)
    : rtclog("periodic_ec"), m_running(false), m_svc(true), m_nowait(false)
  {
    RTC_TRACE(("PeriodicExecutionContext(owner, rate)"));
    m_profile.kind = PERIODIC;
    m_profile.rate = rate;
    if (rate == 0) rate = 0.0000001;
    m_usec = (long int)(1000000/rate);
    if (m_usec == 0) m_nowait = true;
    m_ref = this->_this();
  }
  
  /*!
   * @if jp
   * @brief デストラクタ
   * @else
   * @brief Destructor
   * @endif
   */
  PeriodicExecutionContext::~PeriodicExecutionContext()
  {
    RTC_TRACE(("~PeriodicExecutionContext()"));
    m_worker.mutex_.lock();
    m_worker.running_ = true;
    m_worker.cond_.signal();
    m_worker.mutex_.unlock();
    m_svc = false;
    wait();
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
  int PeriodicExecutionContext::open(void *args)
  {
    RTC_TRACE(("open()"));
    activate();
    return 0;
  }
  
  /*------------------------------------------------------------
   * Run by a daemon thread to handle deferred processing
   * ACE_Task class method over ride.
   *------------------------------------------------------------*/
  /*!
   * @if jp
   * @brief ExecutionContext 用のスレッド実行関数
   * @else
   * @brief Thread execution function for ExecutionContext
   * @endif
   */
  int PeriodicExecutionContext::svc(void)
  {
    RTC_TRACE(("svc()"));
    do 
      {
        m_worker.mutex_.lock();
	while (!m_worker.running_)
	  {
	    m_worker.cond_.wait();
	  }
	if (m_worker.running_)
	  {
	    std::for_each(m_comps.begin(), m_comps.end(), invoke_worker());
	  }
	m_worker.mutex_.unlock();
        coil::TimeValue tv(0, m_usec);
        if (!m_nowait) coil::sleep(tv);
      } while (m_svc);

    return 0;
  }
  
  /*!
   * @if jp
   * @brief ExecutionContext 用のスレッド実行関数
   * @else
   * @brief Thread execution function for ExecutionContext
   * @endif
   */
  int PeriodicExecutionContext::close(unsigned long flags)
  {
    RTC_TRACE(("close()"));
    
    // At this point, this component have to be finished.
    // Current state and Next state should be RTC_EXITING.
    //    delete this;
    return 0;
  }
  
  
  //============================================================
  // ExecutionContext
  //============================================================
  /*!
   * @if jp
   * @brief ExecutionContext 実行状態確認関数
   * @else
   * @brief Check for ExecutionContext running state
   * @endif
   */
  CORBA::Boolean PeriodicExecutionContext::is_running()
    throw (CORBA::SystemException)
  {
    RTC_TRACE(("is_running()"));
    return m_running;
  }
  
  /*!
   * @if jp
   * @brief ExecutionContext の実行を開始
   * @else
   * @brief Start the ExecutionContext
   * @endif
   */
  ReturnCode_t PeriodicExecutionContext::start()
    throw (CORBA::SystemException)
  {
    RTC_TRACE(("start()"));
    if (m_running) return RTC::PRECONDITION_NOT_MET;
    
    // invoke ComponentAction::on_startup for each comps.
    std::for_each(m_comps.begin(), m_comps.end(), invoke_on_startup());
    
    // change EC thread state
    m_running = true;
    {
      m_worker.mutex_.lock();
      m_worker.running_ = true;
      m_worker.cond_.signal();
      m_worker.mutex_.unlock();
    }
    
    this->open(0);
    
    return RTC::RTC_OK;
  }
  
  /*!
   * @if jp
   * @brief ExecutionContext の実行を停止
   * @else
   * @brief Stop the ExecutionContext
   * @endif
   */
  ReturnCode_t PeriodicExecutionContext::stop()
    throw (CORBA::SystemException)
  {
    RTC_TRACE(("stop()"));
    if (!m_running) return RTC::PRECONDITION_NOT_MET;
    
    // stop thread
    m_running = false;
    {
      m_worker.mutex_.lock();
      m_worker.running_ = false;
      m_worker.mutex_.unlock();
    }
    // invoke on_shutdown for each comps.
    std::for_each(m_comps.begin(), m_comps.end(), invoke_on_shutdown());
   
    return RTC::RTC_OK;
  }
  
  /*!
   * @if jp
   * @brief ExecutionContext の実行周期(Hz)を取得する
   * @else
   * @brief Get execution rate(Hz) of ExecutionContext
   * @endif
   */
  CORBA::Double PeriodicExecutionContext::get_rate()
    throw (CORBA::SystemException)
  {
    RTC_TRACE(("get_rate()"));
    return m_profile.rate;
  }
  
  /*!
   * @if jp
   * @brief ExecutionContext の実行周期(Hz)を設定する
   * @else
   * @brief Set execution rate(Hz) of ExecutionContext
   * @endif
   */
  ReturnCode_t PeriodicExecutionContext::set_rate(CORBA::Double rate)
    throw (CORBA::SystemException)
  {
    RTC_TRACE(("set_rate(%f)", rate));
    if (rate > 0.0)
      {
	m_profile.rate = rate;
	m_usec = (long int)(1000000/rate);
	if (m_usec == 0) m_nowait = true;
	std::for_each(m_comps.begin(), m_comps.end(), invoke_on_rate_changed());
	return RTC::RTC_OK;
      }
    return RTC::BAD_PARAMETER;
  }
  
  /*!
   * @if jp
   * @brief RTコンポーネントをアクティブ化する
   * @else
   * @brief Activate an RT-Component
   * @endif
   */ 
  ReturnCode_t
  PeriodicExecutionContext::activate_component(LightweightRTObject_ptr comp)
    throw (CORBA::SystemException)
  {
    RTC_TRACE(("activate_component()"));
    CompItr it;
    it = std::find_if(m_comps.begin(), m_comps.end(),
		      find_comp(comp));

    if (it == m_comps.end())
      return RTC::BAD_PARAMETER;

    if (!(it->_sm.m_sm.isIn(INACTIVE_STATE)))
        return RTC::PRECONDITION_NOT_MET;

    it->_sm.m_sm.goTo(ACTIVE_STATE);
    return RTC::RTC_OK;
  }
  
  /*!
   * @if jp
   * @brief RTコンポーネントを非アクティブ化する
   * @else
   * @brief Deactivate an RT-Component
   * @endif
   */  
  ReturnCode_t
  PeriodicExecutionContext::deactivate_component(LightweightRTObject_ptr comp)
    throw (CORBA::SystemException)
  {
    RTC_TRACE(("deactivate_component()"));
    CompItr it;
    it = std::find_if(m_comps.begin(), m_comps.end(),
		      find_comp(comp));
    if (it == m_comps.end())
      return RTC::BAD_PARAMETER;
    
    if (!(it->_sm.m_sm.isIn(ACTIVE_STATE)))
      return RTC::PRECONDITION_NOT_MET;
    
    it->_sm.m_sm.goTo(INACTIVE_STATE);
    return RTC::RTC_OK;
  }
  
  /*!
   * @if jp
   * @brief RTコンポーネントをリセットする
   * @else
   * @brief Reset the RT-Component
   * @endif
   */  
  ReturnCode_t
  PeriodicExecutionContext::reset_component(LightweightRTObject_ptr comp)
    throw (CORBA::SystemException)
  {
    RTC_TRACE(("reset_component()"));
    CompItr it;
    it = std::find_if(m_comps.begin(), m_comps.end(),
		      find_comp(comp));
    if (it == m_comps.end())
      return RTC::BAD_PARAMETER;
    
    if (!(it->_sm.m_sm.isIn(ERROR_STATE)))
      return RTC::PRECONDITION_NOT_MET;
    
    it->_sm.m_sm.goTo(INACTIVE_STATE);
    return RTC::RTC_OK;
  }
  
  /*!
   * @if jp
   * @brief RTコンポーネントの状態を取得する
   * @else
   * @brief Get RT-Component's state
   * @endif
   */
  LifeCycleState
  PeriodicExecutionContext::get_component_state(LightweightRTObject_ptr comp)
    throw (CORBA::SystemException)
  {
    RTC_TRACE(("get_component_state()"));
    CompItr it;
    it = std::find_if(m_comps.begin(), m_comps.end(), find_comp(comp));

    if (it == m_comps.end())
      {
	return RTC::CREATED_STATE;
      }
    
    return it->_sm.m_sm.getState();
  }
  
  /*!
   * @if jp
   * @brief ExecutionKind を取得する
   * @else
   * @brief Get the ExecutionKind
   * @endif
   */
  ExecutionKind PeriodicExecutionContext::get_kind()
    throw (CORBA::SystemException)
  {
    RTC_TRACE(("get_kind()"));
    return m_profile.kind;
  }
  
  /*!
   * @if jp
   * @brief RTコンポーネントを追加する
   * @else
   * @brief Add an RT-Component
   * @endif
   */
  ReturnCode_t
  PeriodicExecutionContext::add_component(LightweightRTObject_ptr comp)
    throw (CORBA::SystemException)
  {
    RTC_TRACE(("add_component()"));
    if (CORBA::is_nil(comp)) return RTC::BAD_PARAMETER;
    
    try
      {
	OpenRTM::DataFlowComponent_var dfp;
	dfp = OpenRTM::DataFlowComponent::_narrow(comp);
        //Check the pointer.
        if(CORBA::is_nil(dfp))
          {
	    return RTC::BAD_PARAMETER;
          }
	ExecutionContextHandle_t id;
	id = dfp->attach_context(m_ref);
	m_comps.push_back(Comp(comp,dfp,id));
	return RTC::RTC_OK;
      }
    catch (CORBA::Exception& e)
      {
	(void)(e);
	return RTC::BAD_PARAMETER;
      }
    return RTC::RTC_OK;
  }

  RTC::ReturnCode_t PeriodicExecutionContext::bindComponent(RTObject_impl* rtc)
  {
    RTC_TRACE(("bindComponent()"));
    if (rtc == NULL) return RTC::BAD_PARAMETER;

    LightweightRTObject_var comp = RTC::RTObject::_duplicate(rtc->getObjRef());
    OpenRTM::DataFlowComponent_var dfp;
    dfp = OpenRTM::DataFlowComponent::_narrow(comp);

    ExecutionContextHandle_t id = rtc->bindContext(m_ref);
    if (id < 0 || id > ECOTHER_OFFSET) 
      {
        // id should be owned context id < ECOTHER_OFFSET
        RTC_ERROR(("bindContext returns invalid id: %d", id));
        return RTC::RTC_ERROR;
      }
    RTC_DEBUG(("bindContext returns id = %d", id));
    m_comps.push_back(Comp(comp,dfp,id));
    return RTC::RTC_OK;
  }
  
  /*!
   * @if jp
   * @brief コンポーネントをコンポーネントリストから削除する
   * @else
   * @brief Remove the RT-Component from participant list
   * @endif
   */	
  ReturnCode_t
  PeriodicExecutionContext::remove_component(LightweightRTObject_ptr comp)
    throw (CORBA::SystemException)
  {
    RTC_TRACE(("remove_component()"));
    CompItr it;
    it = std::find_if(m_comps.begin(), m_comps.end(),
		      find_comp(comp));
    if (it == m_comps.end())
      return RTC::BAD_PARAMETER;
    
    Comp& c(*it);
    c._ref->detach_context(c._sm.ec_id);
    c._ref = RTC::LightweightRTObject::_nil();
    m_comps.erase(it);
    
    return RTC::RTC_OK;
  }
  
  //============================================================
  // ExecutionContextService interfaces
  //============================================================
  /*!
   * @if jp
   * @brief ExecutionContextProfile を取得する
   * @else
   * @brief Get the ExecutionContextProfile
   * @endif
   */
  ExecutionContextProfile* PeriodicExecutionContext::get_profile()
    throw (CORBA::SystemException)
  {
    RTC_TRACE(("get_profile()"));
    ExecutionContextProfile_var p;
    p = new ExecutionContextProfile(m_profile);
    return p._retn();
  }
}; // namespace RTC  

extern "C"
{
  void PeriodicExecutionContextInit(RTC::Manager* manager)
  {
    manager->registerECFactory("PeriodicExecutionContext",
			       RTC::ECCreate<RTC::PeriodicExecutionContext>,
			       RTC::ECDelete<RTC::PeriodicExecutionContext>);
  }
};

