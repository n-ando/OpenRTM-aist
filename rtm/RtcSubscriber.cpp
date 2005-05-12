// -*- C++ -*-
/*!
 * @file RtcSubscriber.cpp
 * @brief Subscriber active object class runs on Output port
 * @date $Date: 2005-05-12 09:06:18 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2003-2005
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: RtcSubscriber.cpp,v 1.1.1.1 2005-05-12 09:06:18 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 *
 */

#include <ace/ACE.h>
#include "RtcSubscriber.h"

namespace RTM
{

  using namespace std;

  //------------------------------------------------------------
  // SubscriberBase
  //------------------------------------------------------------
  SubscriberBase::SubscriberBase(OutPortBase* parent, InPort_ptr inport,
				   const SubscriptionID id, SubscriberProfile profile)
	: m_pParent(parent), m_pInPort(InPort::_duplicate(inport)),
	  m_Id(id), m_Profile(profile)
	  {
		ACE_TRACE("SubscriberBase::SubscriberBase()");
		open(0);
	  };

  SubscriberBase::~SubscriberBase()
  {
	ACE_TRACE("SubscriberBase::~SubscriberBase()");

	this->release();
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
	CORBA::release(m_pInPort);
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
  SubscriberOnce::SubscriberOnce(OutPortBase* parent, InPort_ptr inport,
								 const SubscriptionID id,
								 SubscriberProfile profile)
	: SubscriberBase(parent, inport, id, profile)
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
  }
  


  //------------------------------------------------------------
  // SubscriberPeriodic
  //------------------------------------------------------------
  SubscriberPeriodic::SubscriberPeriodic(OutPortBase* parent,
										 InPort_ptr inport,
										 const SubscriptionID id,
										 SubscriberProfile profile)
	: SubscriberBase(parent, inport, id, profile)
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
		sleep(1);
		//		m_pParent->push(m_InPort, m_Id);
		
		// sleep() is needed
#ifdef ARTLinux
		//art_wait();
#else
		//		ACE_OS::sleep(m_WaitTime);
#endif //ARTLinux
		
	  }
  }


  //------------------------------------------------------------
  // SubscriberNew
  //------------------------------------------------------------
  SubscriberNew::SubscriberNew(OutPortBase* parent, InPort_ptr inport,
								const SubscriptionID id,
							   SubscriberProfile profile)
	: SubscriberBase(parent, inport, id, profile)
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
			if (m_pParent->push(m_pInPort, m_Id) != RTM_OK) 
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
  SubscriberTriggerd::SubscriberTriggerd(OutPortBase* parent,
										 InPort_ptr inport,
										 const SubscriptionID id,
										 SubscriberProfile profile)
	: SubscriberBase(parent, inport, id, profile)
  {
	ACE_TRACE("SubscriberTriggerd::SubscriberTriggerd()");

  }


  //------------------------------------------------------------
  // SubscriberNewPeriodic
  //------------------------------------------------------------
  SubscriberNewPeriodic::SubscriberNewPeriodic(OutPortBase* parent,
											   InPort_ptr inport,
											   const SubscriptionID id,
											   SubscriberProfile profile)
	: SubscriberBase(parent, inport, id, profile)
  {
	ACE_TRACE("SubscriberNewPeriodic::SubscriberNewPeriodic()");
  }


  //------------------------------------------------------------
  // SubscriberPeriodicNew
  //------------------------------------------------------------
  SubscriberPeriodicNew::SubscriberPeriodicNew(OutPortBase* parent,
											   InPort_ptr inport,
											   const SubscriptionID id,
											   SubscriberProfile profile)
	: SubscriberBase(parent, inport, id, profile)
  {
	ACE_TRACE("SubscriberPeriodicNew::SubscriberPeriodicNew()");

  }



  //------------------------------------------------------------
  // SubscriberPeriodicTriggerd
  //------------------------------------------------------------
  SubscriberPeriodicTriggerd::
  SubscriberPeriodicTriggerd(OutPortBase* parent,
							 InPort_ptr inport,
							 const SubscriptionID id,
							 SubscriberProfile profile)
	: SubscriberBase(parent, inport, id, profile)
  {
	ACE_TRACE("SubscriberPeriodicTriggerd::SubscriberPeriodicTriggerd()");

  }



  //------------------------------------------------------------
  // SubscriberTriggerdPeriodic
  //------------------------------------------------------------

  SubscriberTriggerdPeriodic::
  SubscriberTriggerdPeriodic(OutPortBase* parent,
							 InPort_ptr inport,
							 const SubscriptionID id,
							 SubscriberProfile profile)
	:SubscriberBase(parent, inport, id, profile)
  {
	ACE_TRACE("SubscriberTriggerdPeriodic::SubscriberTriggerdPeriodic()");
  }

}; //end of namespace RTM






