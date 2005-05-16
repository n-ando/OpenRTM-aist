/*! -*- C++ -*-
 *
 * @file RtcOutPortBase.cpp
 * @brief Output porty base class
 * @date $Date: 2005-05-16 06:35:11 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2003-2005
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: RtcOutPortBase.cpp,v 1.2 2005-05-16 06:35:11 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.1.1.1  2005/05/12 09:06:18  n-ando
 * Public release.
 *
 *
 */

#include <iostream>
#include <ace/ACE.h>
#include <ace/UUID.h> 

#include "rtm/RtcOutPortBase.h"
#include "rtm/RtcSubscriber.h"

namespace RTM
{
 
  //============================================================
  // CORBA interface
  //============================================================
  

  //------------------------------------------------------------
  // [CORBA interface] subscribe()
  //
  // Subscribe this port
  //------------------------------------------------------------
  RtmRes OutPortBase::subscribe(InPort_ptr in_port, SubscriptionID_out id, 
								const SubscriberProfile &profile)
	throw (CORBA::SystemException)
  {
	ACE_TRACE("OutPortBase::subscribe()");

	// Generate UUID for this subscription
	ACE_Utils::UUID_Generator uugen;
	uugen.init();
	ACE_Utils::UUID* uuid = uugen.generateUUID(2,0x01);
	id = CORBA::string_dup((uuid->to_string())->c_str());
	//	CORBA::String_var subid = CORBA::string_dup(id);
#ifdef WIN32
	uuid->~UUID();
#else
	delete uuid;
#endif

	SubscriberBase* subs;
	try
	  {
		switch(profile.subscription_type)
		  {
		  case OPS_ONCE:
			subs = new SubscriberOnce(this, in_port, id, profile);
			break;
		  case OPS_PERIODIC:
			subs = new SubscriberPeriodic(this, in_port, id, profile);
			break;
		  case OPS_NEW:
			subs = new SubscriberNew(this, in_port, id, profile);
			break;
		  case OSP_PERIODIC_NEW:
			subs = new SubscriberPeriodicNew(this, in_port, id, profile);
			break;
		  case OPS_NEW_PERIODIC:
			subs = new SubscriberNewPeriodic(this, in_port, id, profile);
			break;
		  case OPS_PERIODIC_TRIGGERED:
			subs = new SubscriberTriggerd(this, in_port, id, profile);
			break;
		  case OPS_TRIGGERRED_PERIODIC:
			subs = new SubscriberTriggerdPeriodic(this, in_port, id, profile);
			break;
		  default:
			return RTM_ERR;
		  }
		ACE_Guard<ACE_Thread_Mutex> guard(m_Subscribers.m_Mutex);
		m_Subscribers.m_List.push_back(subs);
	  }
	catch (...)
	  {
		return RTM_OK;
	  }
	return RTM_OK;
  }

  
  //------------------------------------------------------------
  // [CORBA interface] unsubscribe(SubscriptionID id)
  //
  // Unsubscribe this subscription by subscription ID
  //------------------------------------------------------------
  RtmRes OutPortBase::unsubscribe(const char* id)
	throw (CORBA::SystemException)
  {
	ACE_TRACE("OutPortBase::unsubscribe()");
	
	ACE_Guard<ACE_Thread_Mutex> guard(m_Subscribers.m_Mutex);
	RtmRes res = unsubscribeNoLocked(id);
	
	return res;
  }
  

  //------------------------------------------------------------
  // [CORBA interface] inports()
  //
  // Return inports who subscribe this outport
  //------------------------------------------------------------
  InPortList* OutPortBase::inports()
	throw (CORBA::SystemException)
  {
	ACE_TRACE("OutPortBase::inports()");

	InPortList_var inport_list;
	inport_list = new InPortList();
	ACE_Guard<ACE_Thread_Mutex> guard(m_Subscribers.m_Mutex);
	inport_list->length(m_Subscribers.m_List.size());

	list<SubscriberBase*>::iterator it;
	it = m_Subscribers.m_List.begin();
	CORBA::ULong i(0);

	while (it != m_Subscribers.m_List.end())
	  {
		inport_list[i] = InPort::_duplicate((*it)->get_inport());
		++i;
		++it;
	  }
	
	return inport_list._retn();
  }
  

  //------------------------------------------------------------
  // [CORBA interface] profile()
  //
  // Return this port profile
  //------------------------------------------------------------
  PortProfile* OutPortBase::profile()
	throw (CORBA::SystemException)
  {
	ACE_TRACE("OutPortBase::profile()");

	PortProfile_var profile = new PortProfile(m_Profile);
	return profile._retn();
  }
 


  //============================================================
  // Local interfaces
  //============================================================
  //------------------------------------------------------------
  // disconnect_all()
  //
  // Disconnect all subscribers.
  //------------------------------------------------------------
  void OutPortBase::disconnect_all()
  {
	ACE_TRACE("OutPortBase::disconnect_all()");

	ACE_Guard<ACE_Thread_Mutex> guard(m_Subscribers.m_Mutex);
	list<SubscriberBase*>::iterator it;

	it = m_Subscribers.m_List.begin();
	while (it != m_Subscribers.m_List.end()) // Release correspondent port
	  {
		(*it)->release();
		it = m_Subscribers.m_List.erase(it);
	  }
	
	return;
  }


  //------------------------------------------------------------
  // update_all()
  //
  // Notify current data update to subscriber objects.
  // This is called from derived class of this OutPort.
  //------------------------------------------------------------
  void OutPortBase::updateall()
  {
	ACE_TRACE("OutPortBase::updateall()");
	//	ACE_GUARD_RETURN(ACE_Thread_Mutex, guard, m_Subscribers.m_Mutex,);
	//	ACE_Guard<ACE_Thread_Mutex> guard(m_Subscribers.m_Mutex);
	if (m_Subscribers.m_Mutex.tryacquire_write() != 0)
	  {
		return;
	  }
	list<SubscriberBase*>::iterator it;
	list<SubscriberBase*>::iterator it_end;

	it = m_Subscribers.m_List.begin();
	it_end = m_Subscribers.m_List.end();
	while (it != it_end)
	  {
		if (*it != NULL)
		  {
			(*it)->update();
		  }
		++it;
	  }
	m_Subscribers.m_Mutex.release();
  }

  RtmRes OutPortBase::unsubscribeNoLocked(const char* id)
  {
	list<SubscriberBase*>::iterator it;
	list<SubscriberBase*>::iterator it_end;

	it     = m_Subscribers.m_List.begin();
	it_end = m_Subscribers.m_List.end();
	while (it != it_end) // Release correspondent port
	  {
		string _id(id);
		if (_id == (*it)->get_id()) // subscription ID is matched
		  { // subscription ID must have been unique
			{
			  (*it)->release();
			  //			  delete (*it);
			  it = m_Subscribers.m_List.erase(it);
			}
			return RTM_OK;
		  }
		else
		  {
			++it;
		  }
	  }
	return RTM_ERR;
  }
  
}; // end of namespace RTM
