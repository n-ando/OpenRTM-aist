// -*- C++ -*-
/*!
 * @file RtcSubscriber.cpp
 * @brief Subscriber active object class runs on Output port
 * @date $Date: 2005-05-27 07:36:44 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2003-2005
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: RtcSubscriber.cpp,v 1.3 2005-05-27 07:36:44 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.2  2005/05/16 06:38:00  n-ando
 * - Some bugs were fixed.
 *
 * Revision 1.1.1.1  2005/05/12 09:06:18  n-ando
 * Public release.
 *
 *
 */

#include <ace/ACE.h>
#include "rtm/RtcSubscriber.h"
#include "rtm/RtcOutPortBase.h"

namespace RTM
{

  using namespace std;


  //============================================================
  // SubsProfileBase
  //============================================================
  SubsProfileBase::SubsProfileBase(SubscriptionProfile& subs)
	: m_Profile(subs)
  {
  }
  
  SubscriptionProfile SubsProfileBase::getSubsProfile()
  {
	return m_Profile;
  }
  
  void SubsProfileBase::setSubsProfile(SubscriptionProfile& subs)
  {
	m_Profile = subs;
  }
  
  SubscriptionType SubsProfileBase::getType()
  {
	return m_Profile.subscription_type;
  }

  bool SubsProfileBase::setType(SubscriptionType type)
  {
	if (type < OPS_ONCE || type > OPS_TRIGGERRED_PERIODIC)
	  {
		return false;
	  }
	m_Profile.subscription_type = type;
	return true;
  }
  
  SubscriptionID SubsProfileBase::getId()
  {
	return m_Profile.id;
  }

  bool SubsProfileBase::setId(const char* id)
  {
	m_Profile.id = CORBA::string_dup(id);
	return true;
  }

  bool SubsProfileBase::setId(std::string id)
  {
	m_Profile.id = CORBA::string_dup(id.c_str());
	return true;
  }
  
  InPort_ptr SubsProfileBase::getInPort()
  {
	return m_Profile.in_port;
  }

  bool SubsProfileBase::setInPort(InPort_ptr in_port)
  {
	if (CORBA::is_nil(in_port))
	  {
		return false;
	  }
	m_Profile.in_port = InPort::_duplicate(in_port);
	return true;
  }
  
  OutPort_ptr SubsProfileBase::getOutPort()
  {
	return m_Profile.out_port;
  }

  bool SubsProfileBase::setOutPort(OutPort_ptr out_port)
  {
	if (CORBA::is_nil(out_port))
	  {
		return false;
	  }
	m_Profile.out_port = OutPort::_duplicate(out_port);
	return true;
  }
  
  bool SubsProfileBase::getEventBase()
  {
	return m_Profile.event_base;
  }

  bool SubsProfileBase::setEventBase(bool event_base)
  {
	m_Profile.event_base = event_base;
	return true;
  }
  



  //============================================================
  // SubscriberBase
  //============================================================
  SubscriberBase::SubscriberBase(OutPortBase* parent, 
								 SubscriptionProfile& profile)
	: m_pParent(parent), SubsProfileBase(profile) 
  {
	ACE_TRACE("SubscriberBase::SubscriberBase()");
	//	open(0);
  };
  
  SubscriberBase::~SubscriberBase()
  {
	ACE_TRACE("SubscriberBase::~SubscriberBase()");
	if (is_running())
	  {
		this->stop_thread();
	  }
  }

  int SubscriberBase::open(void *args)
  {
	ACE_TRACE("SubscriberBase::open(void *args)");
	
	m_Running = true;
	activate();
	return 0;
  }

  int SubscriberBase::close(unsigned long flags)
  {
	delete this;
	return 0;
  }

  void SubscriberBase::release()
  {
	ACE_TRACE("SubscriberBase::release()");

	if (is_running())
	  {
		// The thread will be restarted by cond signal and completely stoped.
		this->stop_thread();
	  }
  }
  /*
  SubscriberProfile SubscriberBase::get_profile()
  {
	ACE_TRACE("SubscriberBase::get_profile()");
	return m_Profile;
  }


  InPort_ptr SubscriberBase::get_inport()
  {
	ACE_TRACE("SubscriberBase::get_inport()");
	return m_pInPort;
  }

  std::string SubscriberBase::get_id()
  {
	ACE_TRACE("SubscriberBase::get_id()");
	return m_Id;
  }
  */
  bool SubscriberBase::is_running()
  {
	ACE_TRACE("SubscriberBase::is_running()");

	return m_Running;
  }

  void SubscriberBase::stop_thread()
  {
	ACE_TRACE("SubscriberBase::stop_thread()");
	m_Running = false;
	update(); // through cond. var. wait. is svc().
	wait();   // wait finished svc() thread.
  }

  //------------------------------------------------------------
  // SubscriberOnce
  //------------------------------------------------------------
  SubscriberOnce::SubscriberOnce(RTM::OutPortBase* parent,
								 SubscriptionProfile& profile)
	: SubscriberBase(parent, profile)
  {
	ACE_TRACE("SubscriberOnce::SubscriberOnce()");
  }

  // Notify data update to subscriber
  bool SubscriberOnce::update()
  {
	ACE_TRACE("SubscriberOnce::update()");
	if (m_NewData.m_Mutex.tryacquire_write() != 0)
	  {
		return false;
	  }

	m_NewData.m_Updated = true;
	m_NewData.m_Cond.signal();

	m_NewData.m_Mutex.release();
	return true;
  }

  // Subscriber active object main routine
  int SubscriberOnce::svc(void)
  {
	ACE_TRACE("SubscribetrOnce::svc()");

	m_NewData.m_Mutex.acquire();
	
	// Waiting for new data updated
	while (!m_NewData.m_Updated)
	  m_NewData.m_Cond.wait();
	
	if (m_NewData.m_Updated)
	  {
		//		m_pParent->push(m_InPort);
		//		m_pParent->unsubscribe(m_InPort, m_Id);
		m_NewData.m_Updated = false;
	  }
	
	m_NewData.m_Mutex.release();

	return 0;
  }
  


  //------------------------------------------------------------
  // SubscriberPeriodic
  //------------------------------------------------------------
  SubscriberPeriodic::SubscriberPeriodic(RTM::OutPortBase* parent,
										 SubscriptionProfile& profile)
	: SubscriberBase(parent, profile)
  {
	ACE_TRACE("SubscriberPeriodic::SubscriberPeriodic()");
  }


  // Notify data update to subscriber
  bool SubscriberPeriodic::update()
  {
	ACE_TRACE("SubscriberPeriodic::update()");

	// Do nothing: Periodic subscriber object push data asynchronously to InPort
	return true;
  }


  // Subscriber active object main routine
  int SubscriberPeriodic::svc(void)
  {
	ACE_TRACE("SubscriberPeriodic::svc()");
#ifdef ARTLinux
	//	art_enter();
#endif // ARTLinux
	while (m_Running)
	  {
		// sleep(1);
		//		m_pParent->push(m_InPort, m_Id);
		
		// sleep() is needed
#ifdef ARTLinux
		//art_wait();
#else
		//		ACE_OS::sleep(m_WaitTime);
#endif //ARTLinux
		
	  }
	return 0;
  }


  //------------------------------------------------------------
  // SubscriberNew
  //------------------------------------------------------------
  SubscriberNew::SubscriberNew(RTM::OutPortBase* parent,
							   SubscriptionProfile& profile)
	: SubscriberBase(parent, profile)
  {
	ACE_TRACE("SubscriberNew::SubscriberNew()");
  }


  // Notify data update to subscriber
  bool SubscriberNew::update()
  {
	ACE_TRACE("SubscriberNew::update()");
	if (m_NewData.m_Mutex.tryacquire() != 0)
	  {
		return false;
	  }

	m_NewData.m_Updated = true;
	m_NewData.m_Cond.signal();

	m_NewData.m_Mutex.release();

	return true;
  }


  int SubscriberNew::svc(void)
  {
	ACE_TRACE("SubscriberNew::svc()");
	
	while (m_Running)
	  {
		//		ACE_Guard<ACE_Thread_Mutex> guard(m_NewData.m_Mutex);
		m_NewData.m_Mutex.acquire();
		
		// Waiting for new data updated
		while (!m_NewData.m_Updated && m_Running)
		  {
			m_NewData.m_Cond.wait();
		  }
		
		if (m_NewData.m_Updated)
		  {
			if (m_pParent->push(getInPort(),
								std::string(getId())) != RTM_OK) 
			  {
				;
			  }
			m_NewData.m_Updated = false;
		  }
		
		m_NewData.m_Mutex.release();	
	  }

	// If subscriber comes here, subscriber will be finished and
	// be destructed immediately.

	return 0;
  }


  //------------------------------------------------------------
  // SubscriberTriggerd
  //------------------------------------------------------------
  SubscriberTriggerd::SubscriberTriggerd(RTM::OutPortBase* parent,
										 SubscriptionProfile& profile)
	: SubscriberBase(parent, profile)
  {
	ACE_TRACE("SubscriberTriggerd::SubscriberTriggerd()");

  }


  //------------------------------------------------------------
  // SubscriberNewPeriodic
  //------------------------------------------------------------
  SubscriberNewPeriodic::SubscriberNewPeriodic(RTM::OutPortBase* parent,
											   SubscriptionProfile& profile)
	: SubscriberBase(parent, profile)
  {
	ACE_TRACE("SubscriberNewPeriodic::SubscriberNewPeriodic()");
  }


  //------------------------------------------------------------
  // SubscriberPeriodicNew
  //------------------------------------------------------------
  SubscriberPeriodicNew::SubscriberPeriodicNew(RTM::OutPortBase* parent,
											   SubscriptionProfile& profile)
	: SubscriberBase(parent, profile)
  {
	ACE_TRACE("SubscriberPeriodicNew::SubscriberPeriodicNew()");

  }



  //------------------------------------------------------------
  // SubscriberPeriodicTriggerd
  //------------------------------------------------------------
  SubscriberPeriodicTriggerd::
  SubscriberPeriodicTriggerd(RTM::OutPortBase* parent,
							 SubscriptionProfile& profile)
	: SubscriberBase(parent, profile)
  {
	ACE_TRACE("SubscriberPeriodicTriggerd::SubscriberPeriodicTriggerd()");

  }



  //------------------------------------------------------------
  // SubscriberTriggerdPeriodic
  //------------------------------------------------------------

  SubscriberTriggerdPeriodic::
  SubscriberTriggerdPeriodic(RTM::OutPortBase* parent,
							 SubscriptionProfile& profile)
	: SubscriberBase(parent, profile)
  {
	ACE_TRACE("SubscriberTriggerdPeriodic::SubscriberTriggerdPeriodic()");
  }

}; //end of namespace RTM






