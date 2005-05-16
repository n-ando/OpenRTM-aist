// -*- C++ -*-
/*!
 * @file RtcBase.cpp
 * @brief RT component base class
 * @date $Date: 2005-05-16 05:50:33 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2003-2005
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: RtcBase.cpp,v 1.2 2005-05-16 05:50:33 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.1.1.1  2005/05/12 09:06:18  n-ando
 * Public release.
 *
 *
 */

#include "rtm/RtcBase.h"
#include "rtm/RtcInPortBase.h"
#include "rtm/RtcOutPortBase.h"
#include "rtm/RtcManager.h"
#include "rtm/RtcConfig.h"
#include <ace/OS.h>

namespace RTM {

  RtcBase::RtcBase()
  	: m_StatePort("status", m_TimedState),
	  m_NamingPolicy((NamingPolicy)(LONGNAME_ENABLE | ALIAS_ENABLE)),
	  m_MedLogbuf(), rtcout(m_MedLogbuf)
  {
	RTC_TRACE(("RtcBase::RtcBase()"));

	init_state_func_table();
  }


  RtcBase::RtcBase(CORBA::ORB_ptr orb, PortableServer::POA_ptr poa)
  	: m_StatePort("status", m_TimedState),
	  m_NamingPolicy((NamingPolicy)(LONGNAME_ENABLE | ALIAS_ENABLE)),
	  m_pORB(orb), m_pPOA(poa),
	  m_pManager(NULL),
	  m_MedLogbuf(), rtcout(m_MedLogbuf)
  {
	RTC_TRACE(("RtcBase::RtcBase(CORBA::ORB_var, PortableServer::POA_var)"));

	init_state_func_table();
	m_pPOA->activate_object(&m_StatePort);
  }


  RtcBase::RtcBase(RtcManager* manager)
	: m_StatePort("status", m_TimedState),
	  m_NamingPolicy((NamingPolicy)(LONGNAME_ENABLE | ALIAS_ENABLE)),
	  m_pORB(manager->getORB()), m_pPOA(manager->getPOA()),
	  m_pManager(manager),
	  m_MedLogbuf(manager->getLogbuf()), rtcout(m_MedLogbuf)
  {
	m_MedLogbuf.setDateFmt(manager->getConfig().getLogTimeFormat());
	rtcout.setLogLevel(manager->getConfig().getLogLevel());
	rtcout.setLogLock(manager->getConfig().getLogLock());

	RTC_TRACE(("RtcBase::RtcBase(RtcManager* manager)"));
	init_state_func_table();
	m_pPOA->activate_object(&m_StatePort);
  }


  RtcBase::~RtcBase()
  {
	RTC_TRACE(("RtcBase::~RtcBase()"));
	//	finalizeOutPorts();
	//	finalizeInPorts();
	/*
	try
	  {
		PortableServer::ObjectId_var id;
		id = m_pPOA->servant_to_id(this);
		m_pPOA->deactivate_object(id);
	  }	
	catch (PortableServer::POA::ObjectNotActive e)
	  {
		RTC_ERROR(("exception : ~RtcBase(): Not Active"));
	  }
	catch (PortableServer::POA::WrongPolicy e)
	  {
		RTC_ERROR(("exception: ~RtcBase(): Wrong Policy"));
	  }
	catch (CORBA::OBJECT_NOT_EXIST e)
	  {
		RTC_ERROR(("exception: ~RtcBase(): OBJECT_NOT_EXIST"));
	  }
	catch (...)
	  {
		RTC_ERROR(("exception: ~RtcBase(): unknown exception"));
	  }
	*/
  }


  //============================================================
  //
  // <<< CORBA interfaces >>>
  //
  //============================================================
  

  //------------------------------------------------------------
  // RTC_READY -> RTC_STARTING -> RTC_ACTIVE
  //
  // Activate this components' activity.
  // Other components or managers call this method to activate
  // the component. Component should be in Ready state, when
  // this method is called.
  //------------------------------------------------------------
  RtmRes RtcBase::rtc_start()
	throw (CORBA::SystemException, RTM::RTComponent::IllegalTransition)
  {
	RTC_TRACE(("RtcBase::rtc_start()"));

	ACE_Guard<ACE_Thread_Mutex> guard_curr(m_CurrentState._mutex);

	if (m_CurrentState._state == RTC_READY)
	  {
		ACE_Guard<ACE_Thread_Mutex> guard_next(m_NextState._mutex);
		m_NextState._state = RTC_STARTING;
		return RTM_OK;
	  }
	else
	  {
		throw RTM::RTComponent::IllegalTransition();
		return RTM_OK;
	  }
	return RTM_ERR;
  }


  //------------------------------------------------------------
  // RTC_ACTIVE -> RTC_STOPPING -> RTC_ABORTING
  //
  // Stop this component's activity.
  // Other components or managers call this method to stop the
  // component. Component should be in Active state when this
  // method is called.
  //------------------------------------------------------------
  RtmRes RtcBase::rtc_stop()
	  throw (CORBA::SystemException, RTM::RTComponent::IllegalTransition)
  {
	RTC_TRACE(("RtcBase::rtc_stop()"));

	ACE_Guard<ACE_Thread_Mutex> guard_curr(m_CurrentState._mutex);

	if (m_CurrentState._state == RTC_ACTIVE)
	  {
		ACE_Guard<ACE_Thread_Mutex> guard_next(m_NextState._mutex);
		m_NextState._state = RTC_STOPPING;
		return RTM_OK;
	  }
	else
	  {
		throw RTM::RTComponent::IllegalTransition();
		return RTM_OK;
	  }
	return RTM_ERR;
  }


  //------------------------------------------------------------
  // RTC_ERROR -> RTC_INITIALIZING -> RTC_READY
  // RTC_READY -> RTC_INITIALIZING -> RTC_READY
  //
  // Reset this component to recover from error state.
  // Other component or managers call this method to recover
  // the component from error. After transit initializing state
  // component's state will go to Ready state.
  //------------------------------------------------------------
  RtmRes RtcBase::rtc_reset()
	  throw (CORBA::SystemException, RTM::RTComponent::IllegalTransition)
  {
	RTC_TRACE(("RtcBase::rtc_reset()"));

	ACE_Guard<ACE_Thread_Mutex> guard_curr(m_CurrentState._mutex);

	if (m_CurrentState._state == RTC_READY ||
		m_CurrentState._state == RTC_ERROR)
	  {
		ACE_Guard<ACE_Thread_Mutex> guard_next(m_NextState._mutex);
		m_NextState._state = RTC_INITIALIZING;
		return RTM_OK;
	  }
	else
	  {
		throw RTM::RTComponent::IllegalTransition();
		return RTM_OK;
	  }
	return RTM_ERR;
  }
  
  
  //------------------------------------------------------------
  // RTC_READY -> RTC_EXITING -> END
  // RTC_ERROR -> RTC_EXITING -> END
  //
  // Terminate this component to delete this component.
  // Other components or managers can call this method when 
  // the component is in Error state or Ready state to terminate
  // the component.
  //------------------------------------------------------------
  RtmRes RtcBase::rtc_exit()
	  throw (CORBA::SystemException, RTM::RTComponent::IllegalTransition)
  {
	RTC_TRACE(("RtcBase::rtc_exit()"));

	ACE_Guard<ACE_Thread_Mutex> guard_curr(m_CurrentState._mutex);
	
	if (m_CurrentState._state == RTC_READY ||
		m_CurrentState._state == RTC_ERROR)
	  {
		ACE_Guard<ACE_Thread_Mutex> guard_next(m_NextState._mutex);
		m_NextState._state = RTC_EXITING;
		return RTM_OK;
	  }
	else
	  {
		throw RTM::RTComponent::IllegalTransition();
		return RTM_OK;
	  }
	return RTM_ERR;
  }
  

  //------------------------------------------------------------
  // -> RTC_FATAL_ERROR -> END
  // resume: Go to error() state from anywhere
  //------------------------------------------------------------
  RtmRes RtcBase::rtc_kill()
  {
	RTC_TRACE(("RtcBase::rtc_kill()"));

	ACE_Guard<ACE_Thread_Mutex> guard_curr(m_CurrentState._mutex);
	
	if (m_CurrentState._state == RTC_FATAL_ERROR)
	  {
		ACE_Guard<ACE_Thread_Mutex> guard_next(m_NextState._mutex);
		m_NextState._state = RTC_EXITING;
		return RTM_OK;
	  }
	else
	  {
		rtc_stop_thread();
		//		throw RTM::RTComponent::IllegalTransition();
		return RTM_OK;
	  }
	return RTM_ERR;
  }
  


  //------------------------------------------------------------
  // rtc_main: Main activity function. Called from activity thread periodically.
  //------------------------------------------------------------
  RtmRes RtcBase::rtc_worker()
  {
	//	RTC_PARANOID(("RtcBase::rtc_worker()"));

	ComponentState cur_state;
	ComponentState nxt_state;
	{
	  {
		ACE_Guard<ACE_Thread_Mutex> guard_curr(m_CurrentState._mutex);
		ACE_Guard<ACE_Thread_Mutex> guard_next(m_NextState._mutex);
		cur_state = m_CurrentState._state;
		nxt_state = m_NextState._state;
		m_CurrentState._state = nxt_state;
	  }
	  m_TimedState.data = nxt_state;
	}
	// Change state
	//	ACE_DEBUG((LM_DEBUG,"Current stat: %s, Next stat: %s\n",
	//			   StateString[m_CurrentState._state],
	//			   StateString[m_NextState._state]));
	// Status was changed
	if (cur_state != nxt_state)
	  {
		// exit from the current state.
		RtmRes result_exit = (this->*_exit_func[cur_state])();
		_check_error(result_exit);
		
		// Update component state for StatePort
		m_StatePort.write();

		// Enter to the next state.
		// If next state is transient state, execute transient state function.
		RtmRes result_entry = (this->*_entry_func[nxt_state])();
		return _check_error(result_entry);
	  }
	else 
	  {
		// 状態はそのままなのでdo を実行
		RtmRes result_do = (this->*_do_func[cur_state])();
		return _check_error(result_do);
	  }
	
	return RTM_ERR;
  }


  //------------------------------------------------------------
  // _check_error: Error check help function
  //------------------------------------------------------------
  RtmRes RtcBase::_check_error(RtmRes result)
  {
	// If current function returns error, goto RTC_ERROR status.
	if (result == RTM_ERR && m_CurrentState._state
		!= RTC_ACTIVE) 
	  {
		m_NextState._state = RTC_ERROR;

		return RTM_ERR;
	  }
	//
	// Active state have to transit RTC_ABORTING status.
	//
	else if (result == RTM_ERR
			 && m_CurrentState._state == RTC_ACTIVE) 
	  {
		m_NextState._state = RTC_ABORTING;

		return RTM_ERR;
	  }
	//
	// If function returns RTM_FATAL_ERR, status is directly changed
	//  RTC_FATAL_ERRROR
	else if (result == RTM_FATAL_ERR)
	  {
		m_NextState._state = RTC_FATAL_ERROR;

		return RTM_FATAL_ERR;
	  }

	return RTM_ERR;
  }


  //------------------------------------------------------------
  // Status action functions
  //
  // This functions should be only called rtc_worker.
  // m_CurrentState and m_NextState are already locked.
  // So these variables need not lock once again.
  //------------------------------------------------------------  
  // entry methods
  RtmRes RtcBase::_rtc_initializing()
  {
	RTC_TRACE(("RtcBase::_rtc_initializing()"));

	m_NextState._state = RTC_READY;

	return this->rtc_init_entry();
  }

  RtmRes RtcBase::_rtc_ready_entry()
  {
	RTC_TRACE(("RtcBase::_rtc_ready_entry()"));

	return this->rtc_ready_entry();
  }
  
  RtmRes RtcBase::_rtc_starting()
  {
	RTC_TRACE(("RtcBase::_rtc_starting()"));

	m_NextState._state = RTC_ACTIVE;

	return this->rtc_starting_entry();
  }

  RtmRes RtcBase::_rtc_active_entry()
  {
	RTC_TRACE(("RtcBase::_rtc_active_entry()"));

	return this->rtc_active_entry();
  }

  RtmRes RtcBase::_rtc_stopping()
  {
	RTC_TRACE(("RtcBase::_rtc_stopping()"));

	m_NextState._state = RTC_READY;

	return this->rtc_stopping_entry();
  }

  RtmRes RtcBase::_rtc_aborting()
  {
	RTC_TRACE(("RtcBase::_rtc_aborting()"));

	m_NextState._state = RTC_ERROR;

	return this->rtc_aborting_entry();
  }

  RtmRes RtcBase::_rtc_error_entry()
  {
	RTC_TRACE(("RtcBase::_rtc_error_entry()"));

	return this->rtc_error_entry();
  }

  RtmRes RtcBase::_rtc_fatal_entry()
  {
	RTC_TRACE(("RtcBase::_rtc_fatal_entry()"));

	return this->rtc_fatal_entry();
  }

  RtmRes RtcBase::_rtc_exiting()
  {
	RTC_TRACE(("RtcBase::_rtc_exiting()"));
	RtmRes result;
	result = this->rtc_exiting_entry();

	// Finalize this component.
	rtc_stop_thread();

	return result;
  }

  // do methods
  RtmRes RtcBase::_rtc_ready()
  {
	return this->rtc_ready_do();
  }

  RtmRes RtcBase::_rtc_active()
  {
	return this->rtc_active_do();
  }

  RtmRes RtcBase::_rtc_error()
  {
	return this->rtc_error_do();
  }

  RtmRes RtcBase::_rtc_fatal()
  {
	return this->rtc_fatal_do();
  }


  // exit methods
  RtmRes RtcBase::_rtc_ready_exit()
  {
	RTC_TRACE(("RtcBase::_rtc_ready_exit()"));

	return this->rtc_ready_exit();
  }
  
  RtmRes RtcBase::_rtc_active_exit()
  {
	RTC_TRACE(("RtcBase::_rtc_active_exit()"));

	return this->rtc_active_exit();
  }
  
  RtmRes RtcBase::_rtc_error_exit()
  {
	RTC_TRACE(("RtcBase::_rtc_error_exit()"));

	m_NextState._state = RTC_EXITING;
	return this->rtc_error_exit();
  }
  
  RtmRes RtcBase::_rtc_fatal_exit()
  {
	RTC_TRACE(("RtcBase::_rtc_fatal_exit()"));

	m_NextState._state = RTC_EXITING;
	return this->rtc_fatal_exit();
  }
  // End of status fanctions.
  //------------------------------------------------------------





  //------------------------------------------------------------
  // rtc_state()
  //------------------------------------------------------------
  OutPort_ptr RtcBase::rtc_state()
  {
	RTC_TRACE(("RtcBase::rtc_state()"));

	return OutPort::_narrow(m_pPOA->servant_to_reference(&m_StatePort));
  }
  
  
  InPortList* RtcBase::inports()
  {
	RTC_TRACE(("RtcBase::inports()"));

	ACE_Guard<ACE_Thread_Mutex> guard(m_InPorts.m_Mutex);
	
	InPortList_var inport_list = new InPortList();
	inport_list->length(m_InPorts.m_List.size());
	
	InPorts_it it = m_InPorts.m_List.begin();
	InPorts_it it_end = m_InPorts.m_List.end();
	int i(0);
	
	while (it != it_end)
	  {
		//
		// POA should have policies RETAIN & UNIQUE_ID. 
		// If POA have MULTIPLE_ID policy, InPort newly activate on the POA.
		// 
		inport_list[i] = InPort::_narrow(m_pPOA->servant_to_reference(*it));
		it++;
		i++;
	}
	
	return inport_list._retn();
  }
  
  
  InPort_ptr RtcBase::get_inport(const char* name)
	throw (CORBA::SystemException, RTM::RTComponent::NoSuchName)
  {
	RTC_TRACE(("RtcBase::get_inport()"));
	
	ACE_Guard<ACE_Thread_Mutex> guard(m_InPorts.m_Mutex);
	
	InPorts_it it;
	it = find_if(m_InPorts.m_List.begin(),
				 m_InPorts.m_List.end(),
				 eq_name(name));
	InPort_var inp = InPort::_narrow(m_pPOA->servant_to_reference(*it));
	if (it == m_InPorts.m_List.end())
	  {
		throw RTM::RTComponent::NoSuchName(name);
	  }
	return inp._retn();
  }
  
  
  OutPortList* RtcBase::outports()
  {
	RTC_TRACE(("RtcBase::outports()"));

	ACE_Guard<ACE_Thread_Mutex> guard(m_OutPorts.m_Mutex);
	
	OutPortList_var outport_list = new OutPortList();
	outport_list->length(m_OutPorts.m_List.size());

	OutPorts_it it = m_OutPorts.m_List.begin();
	OutPorts_it it_end = m_OutPorts.m_List.end();
	int i(0);

	while (it != it_end)
	  {	
		//
		// POA should have policies RETAIN & UNIQUE_ID. 
		// If POA have MULTIPLE_ID policy, InPort newly activate on the POA.
		//
		outport_list[i] = OutPort::_narrow(m_pPOA->servant_to_reference(*it));
		it++;
		i++;
	  }
	
	return outport_list._retn();
  }
  
  
  OutPort_ptr RtcBase::get_outport(const char* name)
	throw (CORBA::SystemException, RTM::RTComponent::NoSuchName)
	
  {
	RTC_TRACE(("RtcBase::get_outport()"));

	ACE_Guard<ACE_Thread_Mutex> guard(m_OutPorts.m_Mutex);
	
	OutPorts_it it;
	it = find_if(m_OutPorts.m_List.begin(),
				 m_OutPorts.m_List.end(),
				 eq_name(name));
	
	OutPort_var outp = OutPort::_narrow(m_pPOA->servant_to_reference(*it));
	if (it == m_OutPorts.m_List.end())
	  {
		throw RTM::RTComponent::NoSuchName(name);
	  }
	return outp._retn();
  }
  
  
  char* RtcBase::instance_id()
  {
	RTC_TRACE(("RtcBase::instance_id() -> %s", m_Profile.getInstanceId()));

	return CORBA::string_dup(m_Profile.getInstanceId());
  }


  char* RtcBase::implementation_id()
  {
	RTC_TRACE(("RtcBase::implementation_id() -> %s",
			   m_Profile.getImplementationId()));

	return CORBA::string_dup(m_Profile.getImplementationId());
  }


  char* RtcBase::description()
  {
	RTC_TRACE(("RtcBase::description() -> %s", m_Profile.getDescription()));

	return CORBA::string_dup(m_Profile.getDescription());
  }


  char* RtcBase::version()
  {
	RTC_TRACE(("RtcBase::version() -> %s", m_Profile.getVersion()));
	
	return CORBA::string_dup(m_Profile.getVersion());
  }

  
  char* RtcBase::maker()
  {
	RTC_TRACE(("RtcBase::profile() -> %s", m_Profile.getAuthorName()));

	return CORBA::string_dup(m_Profile.getAuthorName());
  }


  char* RtcBase::category()
  {
	RTC_TRACE(("RtcBase::profile() -> %s", m_Profile.getCategory()));

	return CORBA::string_dup(m_Profile.getCategory());
  }

  
  RTCProfile* RtcBase::profile()
  {
	RTC_TRACE(("RtcBase::profile()"));

	RTCProfile_var profile = new RTCProfile(m_Profile.getProfile());
	return profile._retn();
  }


  RtmRes RtcBase::rtc_start_thread()
  {
	RTC_TRACE(("RtcBase::rtc_start_thread()"));

	m_ThreadState.m_Flag = RUNNING;
	open(0);
	return RTM_OK;
  }


  RtmRes RtcBase::rtc_suspend_thread()
  {
	RTC_TRACE(("RtcBase::rtc_suspend_thread()"));

	m_ThreadState.m_Flag = SUSPEND;

	return RTM_OK;
  }

  RtmRes RtcBase::rtc_stop_thread()
  {
	RTC_TRACE(("RtcBase::rtc_stop_thread()"));
	
	m_ThreadState.m_Flag = STOP;

	return RTM_OK;
  }

  
  RtmRes RtcBase::rtc_set_parent(RTCBase_ptr comp)
  {
	RTC_TRACE(("RtcBase::rtc_set_parent(%s)", comp->instance_id()));

	if (CORBA::is_nil(comp))
	  {
		return RTM_ERR;
	  }
	m_Parent = RTM::RTCBase::_duplicate(comp);
	
	return RTM_OK;
  }
  
  
  
  
  //============================================================
  // Local interfaces
  //============================================================
  void RtcBase::init_orb(CORBA::ORB_ptr orb, PortableServer::POA_ptr poa)
  {
	RTC_TRACE(("RtcBase::init_orb()"));

	m_pORB = orb;
	m_pPOA = poa;
  }
  
  /*------------------------------------------------------------
   * Start activity
   * ACE_Task class method over ride.
   *------------------------------------------------------------*/
  int RtcBase::open(void *args)
  {
	RTC_TRACE(("RtcBase::open()"));

	ACE_Guard<ACE_Thread_Mutex> guard_next(m_NextState._mutex);
	m_NextState._state = RTC_INITIALIZING;
	activate();
	return 0;
  }
  
  
  /*------------------------------------------------------------
   * Run by a daemon thread to handle deferred processing
   * ACE_Task class method over ride.
   *------------------------------------------------------------*/
  int RtcBase::svc(void)
  {
	RTC_TRACE(("RtcBase::svc()"));
	ACE_Time_Value tv(0, 1000); // (s, us)
	while (m_ThreadState.m_Flag == RUNNING ||
		   m_ThreadState.m_Flag == SUSPEND)
	  {
		rtc_worker();
		while (m_ThreadState.m_Flag == SUSPEND) ACE_OS::sleep(tv);
	  }
	forceExit();
	finalize();
	return 0;
  }


  int RtcBase::close(unsigned long flags)
  {
	RTC_TRACE(("RtcBase::close()"));

	// At this point, this component have to be finished.
	// Current state and Next state should be RTC_EXITING.
	delete this;
	return 0;
  }
  

  RTM::RTComponent::ComponentState RtcBase::getState()
  {
	RTC_TRACE(("RtcBase::getState()"));

	ACE_Guard<ACE_Thread_Mutex> guard(m_CurrentState._mutex);

	return m_CurrentState._state;
  }


  void RtcBase::initModuleProfile(RtcModuleProfile prof)
  {
	RTC_TRACE(("RtcBase::initModuleProfile()"));

	m_Profile.setInstanceId      (prof.getInstanceId());
	m_Profile.setImplementationId(prof.getImplementationId());
	m_Profile.setDescription     (prof.getDescription());
	m_Profile.setVersion         (prof.getVersion());
	m_Profile.setAuthorName      (prof.getAuthorName());
	m_Profile.setCategory        (prof.getCategory());
	m_Profile.setComponentType   (prof.getComponentType());
	m_Profile.setActivityType    (prof.getActivityType());
	m_Profile.setMaxInstance     (prof.getMaxInstance());
	m_Profile.setLanguage        (prof.getLanguage());
	m_Profile.setLanguageType    (prof.getLanguageType());
	m_Profile.setIconImage       (prof.getIconImage());
	
	// Initialize log suffix string
	m_MedLogbuf.setSuffix(m_Profile.getImplementationId());
  }

  
  /*------------------------------------------------------------
   * Set component name
   *------------------------------------------------------------*/  
  string RtcBase::setComponentName(int num)
  {
	RTC_TRACE(("RtcBase::setComponentName()"));

	string module_name(m_Profile.getImplementationId());
	string comp_name;
	char n[1000];
	
	ACE_OS::itoa(num, n, 10);
	string nn(n);
	
	comp_name = module_name + nn;

	m_Profile.setInstanceId(comp_name.c_str());

	// Initialize log suffix string
	m_MedLogbuf.setSuffix(m_Profile.getInstanceId());

	return comp_name;
  }


 
  /*------------------------------------------------------------
   * Protcted member function for Component Creator
   *------------------------------------------------------------*/
  bool RtcBase::registerInPort(InPortBase& inport)
  {
	RTC_TRACE(("RtcBase::registerInPort( %s )", inport.name()));

	ACE_Guard<ACE_Thread_Mutex> guard(m_InPorts.m_Mutex);
	
	// すでに同じ名前のチャンネルがないかどうかチェック
	InPorts_it it;
	it = find_if(m_InPorts.m_List.begin(),
				 m_InPorts.m_List.end(),
				 eq_name(inport.name()));
	
	if (it != m_InPorts.m_List.end())
	  {
		RTC_ERROR(("Already registered port: %s.", inport.name()));
		return false;
	  }
	
	// Store input channel reference and flag.
	m_InPorts.m_List.push_back(&inport);
	
	// append port profile to component profile
	m_Profile.appendInPortProfile(*(inport.profile()));

	// Activate Input Port servant
	m_pPOA->activate_object(&inport);
	
	return true;
  }
  
  
  bool RtcBase::deleteInPort(InPortBase& inport)
  {
	RTC_TRACE(("RtcBase::deleteInPort( %s )", inport.name()));

	ACE_Guard<ACE_Thread_Mutex> guard(m_InPorts.m_Mutex);
	
	return deleteInPortByName(inport.name());
  }
  
  
  bool RtcBase::deleteInPortByName(const char* name)
  {
	RTC_TRACE(("RtcBase::deleteInPortByName( %s )", name));

	ACE_Guard<ACE_Thread_Mutex> guard(m_InPorts.m_Mutex);
	
	InPorts_it it;
	
	it = find_if(m_InPorts.m_List.begin(),
				 m_InPorts.m_List.end(),
				 eq_name(name));
	
	if (it == m_InPorts.m_List.end()) // Not found
	  {
		RTC_ERROR(("No such InPort: %s.", name));
		return false;
	  }
	else
	  {
		m_pPOA->deactivate_object(*m_pPOA->servant_to_id(*it));
		m_InPorts.m_List.erase(it);
	  }

	return true;
  }
  

  void RtcBase::readAllInPorts()
  {
	RTC_PARANOID(("RtcBase::readAllInPorts()"));

	ACE_Guard<ACE_Thread_Mutex> guard(m_InPorts.m_Mutex);
	InPorts_it it;
	InPorts_it it_end;
	it     = m_InPorts.m_List.begin();
	it_end = m_InPorts.m_List.end();

	while (it != it_end)
	  {
		(*it)->read_pm();
		++it;
	  }

	return;
  }
	


  void RtcBase::finalizeInPorts()
  {
	RTC_TRACE(("RtcBase::finalizeInPorts()"));

	ACE_Guard<ACE_Thread_Mutex> guard(m_InPorts.m_Mutex);
	InPorts_it it;
	InPorts_it it_end;
	it     = m_InPorts.m_List.begin();
	it_end = m_InPorts.m_List.end();
	
	while (it != it_end)
	  {
		try
		  {
			m_pPOA->deactivate_object(*(m_pPOA->servant_to_id(*it)));
		  }
		catch (PortableServer::POA::ObjectNotActive e)
		  {
			RTC_ERROR(("exception: RtcBase::finalizeInPorts(): Not Active"));
		  }
		catch (PortableServer::POA::WrongPolicy e)
		  {
			RTC_ERROR(("exception: RtcBase::finalizeInPorts(): Wrong Policy"));
		  }
		catch (CORBA::OBJECT_NOT_EXIST e)
		  {
			RTC_ERROR(("exception: RtcBase::finalizeInPorts(): OBJECT_NOT_EXIST"));
		  }
		catch (...)
		  {
			RTC_ERROR(("exception: RtcBase::finalizeInPorts(): unknown"));
		  }
		it = m_InPorts.m_List.erase(it);
	  }
	
	return;
  }

  
  bool RtcBase::registerOutPort(OutPortBase& outport)
  {
	RTC_TRACE(("RtcBase::registerOutPort( %s )", outport.name()));

	ACE_Guard<ACE_Thread_Mutex> guard(m_OutPorts.m_Mutex);
	
	// すでに同じ名前のチャンネルがないかどうかチェック
	OutPorts_it it;
	it = find_if(m_OutPorts.m_List.begin(),
				 m_OutPorts.m_List.end(),
				 eq_name(outport.name()));
	
	if (it != m_OutPorts.m_List.end())
	  {
		RTC_ERROR(("Already registered port: %s.", outport.name()));
		return false;
	  }

	// Store output channel reference and flag.
	m_OutPorts.m_List.push_back(&outport);

	// append port profile to component profile
	m_Profile.appendOutPortProfile(*(outport.profile()));

	// Activate Output Port servant
	m_pPOA->activate_object(&outport);

	return true;
  }
  
  
  bool RtcBase::deleteOutPort(OutPortBase& outport)
  {
	RTC_TRACE(("RtcBase::deleteOutPort(%s)", outport.name()));

	ACE_Guard<ACE_Thread_Mutex> guard(m_OutPorts.m_Mutex);

	return deleteOutPortByName(outport.name());
  }
  
  
  bool RtcBase::deleteOutPortByName(const char* name)
  {
	RTC_TRACE(("RtcBase::deleteOutPortByName(%s)", name));

	ACE_Guard<ACE_Thread_Mutex> guard(m_OutPorts.m_Mutex);
	
	OutPorts_it it;
	
	it = find_if(m_OutPorts.m_List.begin(),
				 m_OutPorts.m_List.end(),
				 eq_name(name));
	
	if (it == m_OutPorts.m_List.end())
	  {
		RTC_ERROR(("No such OutPort: %s.", name));
		return false;
	  }
	else
	  {
		m_pPOA->deactivate_object(*m_pPOA->servant_to_id(*it));
		m_OutPorts.m_List.erase(it);
	  }
	
	return true;
  }
  

  void RtcBase::writeAllOutPorts()
  {
	RTC_PARANOID(("RtcBase::writeAllOutPorts()"));

	ACE_Guard<ACE_Thread_Mutex> guard(m_OutPorts.m_Mutex);
	OutPorts_it it;
	OutPorts_it it_end;
	it     = m_OutPorts.m_List.begin();
	it_end = m_OutPorts.m_List.end();

	while (it != it_end)
	  {
		(*it)->write_pm();
		++it;
	  }

	return;
  }

  
  void RtcBase::finalizeOutPorts()
  {
	RTC_TRACE(("RtcBase::finalizeOutPorts()"));

	ACE_Guard<ACE_Thread_Mutex> guard(m_OutPorts.m_Mutex);
	OutPorts_it it;
	OutPorts_it it_end;
	it     = m_OutPorts.m_List.begin();
	it_end = m_OutPorts.m_List.end();

	// Deactivate state OutPort
	m_StatePort.disconnect_all();
	m_pPOA->deactivate_object(*(m_pPOA->servant_to_id(&m_StatePort)));

	// Deactivate all registered OutPorts
	while (it != it_end)
	  {
		try
		  {
			(*it)->disconnect_all();
			m_pPOA->deactivate_object(*(m_pPOA->servant_to_id(*it)));
		  }
		catch (PortableServer::POA::ObjectNotActive e)
		  {
			RTC_ERROR(("exception: RtcBase::finalizeOutPorts(): Not Active"));
		  }
		catch (PortableServer::POA::WrongPolicy e)
		  {
			RTC_ERROR(("exception: RtcBase::finalizeOutPorts(): Wrong Policy"));
		  }
		catch (CORBA::OBJECT_NOT_EXIST e)
		  {
			RTC_ERROR(("exception: RtcBase::finalizeOutPorts(): OBJECT_NOT_EXIST"));
		  }
		catch (...)
		  {
			RTC_ERROR(("exception: RtcBase::finalizeOutPorts(): unknown"));
		  }
		it = m_OutPorts.m_List.erase(it);
	  }

	return;
  }

  void RtcBase::appendAlias(const char* alias)
  {
	RTC_TRACE(("RtcBase::appendAlias(%s)", alias));
	appendAlias(std::string(alias));
	return;
  }


  void RtcBase::appendAlias(std::string alias)
  {
	RTC_TRACE(("RtcBase::appendAlias(%s)", alias.c_str()));
	m_Alias.push_back(alias);
	return;
  }


  std::list<string> RtcBase::getAliases()
  {
	RTC_TRACE(("RtcBase::getAliases()"));
	return m_Alias;
  }


  void RtcBase::setNamingPolicy(NamingPolicy policy)
  {
	RTC_TRACE(("RtcBase::setNamingPolicy()"));
	m_NamingPolicy = policy;
  }


  NamingPolicy RtcBase::getNamingPolicy()
  {
	RTC_TRACE(("RtcBase::getNamingPolicy()"));
	return m_NamingPolicy;
  }


  bool RtcBase::isLongNameEnable()
  {
	RTC_TRACE(("RtcBase::isLongNameEnable()"));
	if ((m_NamingPolicy & LONGNAME_ENABLE) != 0)
	  {
		return true;
	  }
	return false;
  }


  bool RtcBase::isAliasEnable()
  {
	RTC_TRACE(("RtcBase::isAliasEnable()"));
	if ((m_NamingPolicy & ALIAS_ENABLE) != 0)
	  {
		return true;
	  }
	return false;
  }


  void RtcBase::finalize()
  {
	RTC_TRACE(("RtcBase::finalize()"));

	if (isThreadRunning())
	  {
		rtc_stop_thread();
	  }

	finalizeOutPorts();
	finalizeInPorts();

	try
	  {
		PortableServer::ObjectId_var id;
		id = m_pPOA->servant_to_id(this);
		m_pPOA->deactivate_object(id.in());
		RTC_DEBUG(("The servant RTCBase() was deactivated."));
	  }	
	catch (PortableServer::POA::ObjectNotActive e)
	  {
		RTC_ERROR(("exception: RtcBase::finalize(): Not Active"));
	  }
	catch (PortableServer::POA::WrongPolicy e)
	  {
		RTC_ERROR(("exception: RtcBase::finalize(): Wrong Policy"));
	  }
	catch (CORBA::OBJECT_NOT_EXIST e)
	  {
		RTC_ERROR(("exception: RtcBase::finalize(): OBJECT_NOT_EXIST"));
	  }
	catch (...)
	  {
		RTC_ERROR(("exception: RtcBase::finalize(): unknown exception"));
	  }

	m_pManager->cleanupComponent(m_Profile.getInstanceId(),
								 m_Profile.getCategory());

	return;
  }


  void RtcBase::forceExit()
  {
	RTC_TRACE(("RtcBase::forceExit()"));
	static int reenter(0);

	if (reenter != 0) return;
	++reenter;

	if (isThreadRunning())
	  {
		rtc_stop_thread();
	  }

	int count(0);

	while (m_CurrentState._state != RTC_EXITING)
	  {
		switch (m_CurrentState._state)
		  {
		  case RTC_UNKNOWN:
			m_CurrentState._state = RTC_EXITING;
			break;
		  case RTC_READY:
			m_NextState._state = RTC_EXITING;
			break;
		  case RTC_ACTIVE:
			m_NextState._state = RTC_STOPPING;
			break;
		  case RTC_ERROR:
			m_NextState._state = RTC_EXITING;
			break;
		  case RTC_FATAL_ERROR:
			m_NextState._state = RTC_EXITING;
			break;
		  case RTC_EXITING:
			return;
			break;
		  case RTC_BORN:
		  case RTC_INITIALIZING:
		  case RTC_STARTING:
		  case RTC_STOPPING:
		  case RTC_ABORTING:
		  default:
			break;
		  }
		this->rtc_worker();
		++count;
		if (count > 1000)
		  {
			RTC_ERROR(("The activity cannot be finished. Giving up."));
			m_CurrentState._state = RTC_EXITING;
			break;
		  }
	  }
	--reenter;
	return;
  }


  bool RtcBase::isThreadRunning()
  {
	RTC_TRACE(("RtcBase::isThreadRunning()"));

	return m_ThreadState.m_Flag == RUNNING ? true : false;
  }

  
  void RtcBase::init_state_func_table()
  {
	RTC_TRACE(("RtcBase::init_state_func_table()"));

	m_NextState._state = RTC_BORN;
	m_CurrentState._state = RTC_BORN;
	
	_entry_func[RTC_UNKNOWN]      = &RtcBase::_nop;
	_entry_func[RTC_BORN]         = &RtcBase::_nop;
	_entry_func[RTC_INITIALIZING] = &RtcBase::_rtc_initializing;
	_entry_func[RTC_READY]        = &RtcBase::_rtc_ready_entry;
	_entry_func[RTC_STARTING]     = &RtcBase::_rtc_starting;
	_entry_func[RTC_ACTIVE]       = &RtcBase::_rtc_active_entry;
	_entry_func[RTC_STOPPING]     = &RtcBase::_rtc_stopping;
	_entry_func[RTC_ABORTING]     = &RtcBase::_rtc_aborting;
	_entry_func[RTC_ERROR]        = &RtcBase::_rtc_error_entry;
	_entry_func[RTC_FATAL_ERROR]  = &RtcBase::_rtc_fatal_entry;
	_entry_func[RTC_EXITING]      = &RtcBase::_rtc_exiting;
	
	_do_func[RTC_UNKNOWN]         = &RtcBase::_nop;
	_do_func[RTC_BORN]            = &RtcBase::_nop;
	_do_func[RTC_INITIALIZING]    = &RtcBase::_nop;
	_do_func[RTC_READY]           = &RtcBase::_rtc_ready;
	_do_func[RTC_STARTING]        = &RtcBase::_nop;
	_do_func[RTC_ACTIVE]          = &RtcBase::_rtc_active;
	_do_func[RTC_STOPPING]        = &RtcBase::_nop;
	_do_func[RTC_ABORTING]        = &RtcBase::_nop;
	_do_func[RTC_ERROR]           = &RtcBase::_rtc_error;
	_do_func[RTC_FATAL_ERROR]     = &RtcBase::_rtc_fatal;
	_do_func[RTC_EXITING]         = &RtcBase::_nop;
	
	_exit_func[RTC_UNKNOWN]       = &RtcBase::_nop;
	_exit_func[RTC_BORN]          = &RtcBase::_nop;
	_exit_func[RTC_INITIALIZING]  = &RtcBase::_nop;
	_exit_func[RTC_READY]         = &RtcBase::_rtc_ready_exit;
	_exit_func[RTC_STARTING]      = &RtcBase::_nop;
	_exit_func[RTC_ACTIVE]        = &RtcBase::_rtc_active_exit;
	_exit_func[RTC_STOPPING]      = &RtcBase::_nop;
	_exit_func[RTC_ABORTING]      = &RtcBase::_nop;
	_exit_func[RTC_ERROR]         = &RtcBase::_rtc_error_exit;
	_exit_func[RTC_FATAL_ERROR]   = &RtcBase::_rtc_fatal_exit;
	_exit_func[RTC_EXITING]       = &RtcBase::_nop;

	m_NextState._state = RTC_INITIALIZING;
  }

  
}; // end of namespace RTM

#ifdef WIN32
BOOL WINAPI DllMain (HINSTANCE hinstDll, DWORD fdwReason, LPVOID lpvReserved)
{
	return TRUE;
}
#endif //WIN32
