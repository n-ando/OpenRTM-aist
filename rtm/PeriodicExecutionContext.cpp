// -*- C++ -*-
/*!
 * @file PeriodicExecutionContext.cpp
 * @brief PeriodicExecutionContext class
 * @date $Date: 2007-01-14 19:44:26 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: PeriodicExecutionContext.cpp,v 1.2 2007-01-14 19:44:26 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.1  2007/01/09 15:29:25  n-ando
 * PeriodicExecutionContext class
 *
 */

#include <rtm/PeriodicExecutionContext.h>
#include <algorithm>
#include <iostream>

namespace RTC
{
  PeriodicExecutionContext::
  PeriodicExecutionContext(DataFlowComponent_ptr owner,
			   double rate)
    : m_running(false)
  {
    m_profile.kind = PERIODIC;
    m_profile.rate = rate;
    m_usec = (long int)(1000000/rate);
    m_ref = this->_this();
  }

  PeriodicExecutionContext::~PeriodicExecutionContext()
  {
    ;
  }


  

  /*------------------------------------------------------------
   * Start activity
   * ACE_Task class method over ride.
   *------------------------------------------------------------*/
  int PeriodicExecutionContext::open(void *args)
  {
    //    RTC_TRACE(("RtcBase::open()"));
    //    ACE_Guard<ACE_Thread_Mutex> guard_next(m_NextState._mutex);
    //    m_NextState._state = RTC_INITIALIZING;
    activate();
    return 0;
  }
  
  
  /*------------------------------------------------------------
   * Run by a daemon thread to handle deferred processing
   * ACE_Task class method over ride.
   *------------------------------------------------------------*/
  int PeriodicExecutionContext::svc(void)
  {
    //    RTC_TRACE(("RtcBase::svc()"));
    //    std::cout << (m_running ? "RUNNING" : "STOPPING") << std::endl;
    do
      {
	ACE_Time_Value tv(0, m_usec); // (s, us)
	std::for_each(m_comps.begin(), m_comps.end(), invoke_worker());
	while (!m_running) {ACE_OS::sleep(tv);}
	ACE_OS::sleep(tv);
      } while (m_running);
    //    forceExit();
    //    finalize();
    return 0;
  }
  
  
  int PeriodicExecutionContext::close(unsigned long flags)
  {
    //    RTC_TRACE(("RtcBase::close()"));
    
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
   * @brief ExecutionContext が実行中かどうかのテスト
   * @else
   * @brief Test for ExecutionContext running state
   * @endif
   */
  CORBA::Boolean PeriodicExecutionContext::is_running()
  {
    return m_running;
  }


  /*!
   * @if jp
   * @brief ExecutionContext をスタートさせる
   * @else
   * @brief Start the ExecutionContext
   * @endif
   */
  ReturnCode_t PeriodicExecutionContext::start()
  {
    if (m_running) return RTC::PRECONDITION_NOT_MET;

    // invoke ComponentAction::on_startup for each comps.
    std::for_each(m_comps.begin(), m_comps.end(), invoke_on_startup());

    // change EC thread state
    m_running = true;
    this->open(0);

    return RTC::OK;
  }
  

  /*!
   * @if jp
   * @brief ExecutionContext をストップさせる
   * @else
   * @brief Stop the ExecutionContext
   * @endif
   */
  ReturnCode_t PeriodicExecutionContext::stop()
  {
    if (!m_running) return RTC::PRECONDITION_NOT_MET;

    // invoke on_shutdown for each comps.
    std::for_each(m_comps.begin(), m_comps.end(), invoke_on_shutdown());

    // change EC thread state
    m_running = false;

    return RTC::OK;
  }

  /*!
   * @if jp
   * @brief 実行周期(Hz)を取得する
   * @else
   * @brief Get executionrate(Hz)
   * @endif
   */
  CORBA::Double PeriodicExecutionContext::get_rate()
  {
    return m_profile.rate;
  }


  /*!
   * @if jp
   * @brief 実行周期(Hz)を与える 
   * @else
   * @brief Set rate (Hz)
   * @endif
   */
  ReturnCode_t PeriodicExecutionContext::set_rate(CORBA::Double rate)
  {
    if (rate > 0.0)
      {
	m_profile.rate = rate;
	m_usec = (long int)(1000000/rate);
	std::for_each(m_comps.begin(), m_comps.end(), invoke_on_rate_changed());
	return RTC::OK;
      }
    return RTC::BAD_PARAMETER;
  }


  /*!
   * @if jp
   * @brief コンポーネントをアクティブ化する
   * @else
   * @brief Activate a component
   * @endif
   */ 
  ReturnCode_t
  PeriodicExecutionContext::activate_component(LightweightRTObject_ptr comp)
  {
    // コンポーネントが参加者リストに無ければ BAD_PARAMETER を返す
    CompItr it;
    it = std::find_if(m_comps.begin(), m_comps.end(), find_comp(comp));
    if (it == m_comps.end())
      return RTC::BAD_PARAMETER;

    if (!(it->_sm.m_sm.isIn(INACTIVE_STATE)))
      return RTC::PRECONDITION_NOT_MET;

    it->_sm.m_sm.goTo(ACTIVE_STATE);
    
    return RTC::OK;
  }
  

  /*!
   * @if jp
   * @brief コンポーネントを非アクティブ化する
   * @else
   * @brief Deactivate a component
   * @endif
   */  
  ReturnCode_t
  PeriodicExecutionContext::deactivate_component(LightweightRTObject_ptr comp)
  {
    CompItr it;
    it = std::find_if(m_comps.begin(), m_comps.end(), find_comp(comp));
    if (it == m_comps.end())
      return RTC::BAD_PARAMETER;

    if (!(it->_sm.m_sm.isIn(ACTIVE_STATE)))
      return RTC::PRECONDITION_NOT_MET;
    
    it->_sm.m_sm.goTo(INACTIVE_STATE);
    return RTC::OK;
  }
  
  
  /*!
   * @if jp
   * @brief コンポーネントを非アクティブ化する
   * @else
   * @brief Deactivate a component
   * @endif
   */  
  ReturnCode_t
  PeriodicExecutionContext::reset_component(LightweightRTObject_ptr comp)
  {
    CompItr it;
    it = std::find_if(m_comps.begin(), m_comps.end(), find_comp(comp));
    if (it == m_comps.end())
      return RTC::BAD_PARAMETER;

    if (!(it->_sm.m_sm.isIn(ERROR_STATE)))
      return RTC::PRECONDITION_NOT_MET;
    
    it->_sm.m_sm.goTo(INACTIVE_STATE);
    return RTC::OK;
  }
  

  /*!
   * @if jp
   * @brief コンポーネントの状態を取得する
   * @else
   * @brief Get component's state
   * @endif
   */
  LifeCycleState
  PeriodicExecutionContext::get_component_state(LightweightRTObject_ptr comp)
  {
    CompItr it;
    it = std::find_if(m_comps.begin(), m_comps.end(), find_comp(comp));
    if (it == m_comps.end())
      return RTC::UNKNOWN_STATE;

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
  {
    return m_profile.kind;
  }
  
  /*!
   * @if jp
   * @brief コンポーネントを追加する
   * @else
   * @brief Add a component
   * @endif
   */
  ReturnCode_t PeriodicExecutionContext::add(LightweightRTObject_ptr comp)
  {
    if (CORBA::is_nil(comp)) return RTC::BAD_PARAMETER;

    try
      {
	DataFlowComponent_ptr dfp;
	dfp = DataFlowComponent::_narrow(comp);

	UniqueId id;
	id = dfp->set_execution_context_service(m_ref);

	m_comps.push_back(Comp(comp, dfp, id));
	return RTC::OK;
      }
    catch (CORBA::Exception& e)
      {
	return RTC::BAD_PARAMETER;
      }
    return RTC::OK;
  }
  
  
  /*!
   * @if jp
   * @brief コンポーネントをコンポーネントリストから削除する
   * @else
   * @brief Remove the component from component list
   * @endif
   */	
  ReturnCode_t
  PeriodicExecutionContext::remove(LightweightRTObject_ptr comp)
  {
    CompItr it;
    it = std::find_if(m_comps.begin(), m_comps.end(), find_comp(comp));
    if (it == m_comps.end())
      return RTC::BAD_PARAMETER;

    m_comps.erase(it);

    return RTC::OK;
  }



  //============================================================
  // ExecutionContextAdmin interfaces
  //============================================================
  /*!
   * @if jp
   * @brief ExecutionContextProfile を取得する
   * @else
   * @brief Get the ExecutionContextProfile
   * @endif
   */
  ExecutionContextProfile* PeriodicExecutionContext::get_profile()
  {
    ExecutionContextProfile_var p;
    p = new ExecutionContextProfile(m_profile);
    return p._retn();
  }
  


}; // namespace RTC
