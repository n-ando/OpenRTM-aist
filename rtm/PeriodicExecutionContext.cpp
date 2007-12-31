// -*- C++ -*-
/*!
 * @file PeriodicExecutionContext.cpp
 * @brief PeriodicExecutionContext class
 * @date $Date: 2007-12-31 03:08:05 $
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
 * $Id: PeriodicExecutionContext.cpp,v 1.5.2.4 2007-12-31 03:08:05 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.5.2.3  2007/09/20 11:22:45  n-ando
 * A trivial fix.
 *
 * Revision 1.5.2.2  2007/09/19 07:44:37  n-ando
 * The usleep() in the execution loop will be skipped, if wait-time is 0.
 *
 * Revision 1.5.2.1  2007/07/20 15:58:50  n-ando
 * Some ineffective expressions were added to suppress compiler's warning.
 *
 * Revision 1.5  2007/04/13 15:52:15  n-ando
 * RTC::OK was changed to RTC::RTC_OK.
 * Initialization function was added to make it an external module.
 *
 * Revision 1.4  2007/02/04 16:56:52  n-ando
 * The bugs around object references count were fixed.
 *
 * Revision 1.3  2007/01/21 10:26:55  n-ando
 * Object reference count related bugs were fixed.
 *
 * Revision 1.2  2007/01/14 19:44:26  n-ando
 * The logic of main activity loop was changed.
 *
 * Revision 1.1  2007/01/09 15:29:25  n-ando
 * PeriodicExecutionContext class
 *
 */

#include <rtm/PeriodicExecutionContext.h>
#include <algorithm>
#include <iostream>

namespace RTC
{
  /*!
   * @if jp
   * @brief デフォルトコンストラクタ
   * @else
   * 
   * @endif
   */
  PeriodicExecutionContext::
  PeriodicExecutionContext()
    : m_running(false), m_nowait(false)
  {
    m_profile.kind = PERIODIC;
    m_profile.rate = 0.0;
    m_usec = (long int)0;
    m_ref = this->_this();
  }
  
  /*!
   * @if jp
   * @brief コンストラクタ
   * @else
   * 
   * @endif
   */
  PeriodicExecutionContext::
  PeriodicExecutionContext(DataFlowComponent_ptr owner,
			   double rate)
    : m_running(false), m_nowait(false)
  {
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
   * 
   * @endif
   */
  PeriodicExecutionContext::~PeriodicExecutionContext()
  {
    ;
  }
  
  /*------------------------------------------------------------
   * Start activity
   * ACE_Task class method over ride.
   *------------------------------------------------------------*/
  /*!
   * @if jp
   * @brief ExecutionContext用アクティビティスレッドを生成する
   * @else
   * 
   * @endif
   */
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
  /*!
   * @if jp
   * @brief ExecutionContext 用のスレッド実行関数
   * @else
   * 
   * @endif
   */
  int PeriodicExecutionContext::svc(void)
  {
    //    RTC_TRACE(("RtcBase::svc()"));
    do
      {
	ACE_Time_Value tv(0, m_usec); // (s, us)
	std::for_each(m_comps.begin(), m_comps.end(), invoke_worker());
	while (!m_running) {ACE_OS::sleep(tv);}
	if (!m_nowait) ACE_OS::sleep(tv);
      } while (m_running);
    //    forceExit();
    //    finalize();
    return 0;
  }
  
  /*!
   * @if jp
   * @brief ExecutionContext 用のスレッド実行関数
   * @else
   * 
   * @endif
   */
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
   * @brief ExecutionContext 実行状態確認関数
   * @else
   * @brief Check for ExecutionContext running state
   * @endif
   */
  CORBA::Boolean PeriodicExecutionContext::is_running()
  {
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
  {
    if (m_running) return RTC::PRECONDITION_NOT_MET;
    
    // invoke ComponentAction::on_startup for each comps.
    std::for_each(m_comps.begin(), m_comps.end(), invoke_on_startup());
    
    // change EC thread state
    m_running = true;
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
  {
    if (!m_running) return RTC::PRECONDITION_NOT_MET;
    
    // invoke on_shutdown for each comps.
    std::for_each(m_comps.begin(), m_comps.end(), invoke_on_shutdown());
    
    // change EC thread state
    m_running = false;
    
    return RTC::RTC_OK;
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
   * @brief 実行周期(Hz)を設定する 
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
   * @brief Activate a RT-component
   * @endif
   */ 
  ReturnCode_t
  PeriodicExecutionContext::activate_component(LightweightRTObject_ptr comp)
  {
    // コンポーネントが参加者リストに無ければ BAD_PARAMETER を返す
    CompItr it;
    it = std::find_if(m_comps.begin(), m_comps.end(),
		      find_comp(LightweightRTObject::_duplicate(comp)));
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
   * @brief Deactivate a RT-component
   * @endif
   */  
  ReturnCode_t
  PeriodicExecutionContext::deactivate_component(LightweightRTObject_ptr comp)
  {
    CompItr it;
    it = std::find_if(m_comps.begin(), m_comps.end(),
		      find_comp(RTC::LightweightRTObject::_duplicate(comp)));
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
   * @brief Reset a RT-component
   * @endif
   */  
  ReturnCode_t
  PeriodicExecutionContext::reset_component(LightweightRTObject_ptr comp)
  {
    CompItr it;
    it = std::find_if(m_comps.begin(), m_comps.end(),
		      find_comp(RTC::LightweightRTObject::_duplicate(comp)));
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
   * @brief Get RT-component's state
   * @endif
   */
  LifeCycleState
  PeriodicExecutionContext::get_component_state(LightweightRTObject_ptr comp)
  {
    CompItr it;
    it = std::find_if(m_comps.begin(), m_comps.end(),
		      find_comp(RTC::LightweightRTObject::_duplicate(comp)));
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
   * @brief RTコンポーネントを追加する
   * @else
   * @brief Add a RT-component
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
	id = dfp->attach_executioncontext(m_ref);
	
	m_comps.push_back(Comp(LightweightRTObject::_duplicate(comp),
			       DataFlowComponent::_duplicate(dfp), id));
	return RTC::RTC_OK;
      }
    catch (CORBA::Exception& e)
      {
	e;
	return RTC::BAD_PARAMETER;
      }
    return RTC::RTC_OK;
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
    it = std::find_if(m_comps.begin(), m_comps.end(),
		      find_comp(RTC::LightweightRTObject::_duplicate(comp)));
    if (it == m_comps.end())
      return RTC::BAD_PARAMETER;
    
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
  {
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

