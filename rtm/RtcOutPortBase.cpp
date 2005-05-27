/*! -*- C++ -*-
 *
 * @file RtcOutPortBase.cpp
 * @brief Output porty base class
 * @date $Date: 2005-05-27 07:34:21 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2003-2005
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: RtcOutPortBase.cpp,v 1.3 2005-05-27 07:34:21 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.2  2005/05/16 06:35:11  n-ando
 * - In windows "delete uuid;" in constructor of OutPortBase does not work.
 *   To avoid this bug, "delete uuid" was replaced with "uuid->~UUID()".
 *
 * Revision 1.1.1.1  2005/05/12 09:06:18  n-ando
 * Public release.
 *
 *
 */

#include <iostream>
#include <ace/ACE.h>
#include <ace/UUID.h> 
#include <ace/Task.h>

#include "rtm/RtcBase.h"
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
  RtmRes OutPortBase::subscribe(SubscriptionProfile& subs_prof)
	throw (CORBA::SystemException, RTM::PortBase::InvalidSubscription)
  {
	// Generate UUID for this subscription
	ACE_Utils::UUID_Generator uugen;
	uugen.init();
	ACE_Utils::UUID* uuid = uugen.generateUUID(2,0x01);
	subs_prof.id = CORBA::string_dup((uuid->to_string())->c_str());
#ifdef WIN32
	uuid->~UUID();
#else
	delete uuid;
#endif

	try
	  {
		// Notify local
		notify_subscribe(subs_prof);
		// Notify subscription peer InPort		
		subs_prof.in_port->notify_subscribe(subs_prof);
	  }
	catch (RTM::PortBase::InvalidSubscription& ise)
	  {
		ACE_Guard<ACE_Thread_Mutex> guard(m_Subscribers.m_Mutex);
		Subs_it it = m_Subscribers.findById(subs_prof.id);
		m_Subscribers.eraseById(subs_prof.id);
		delete (*it);
		throw ise;
	  }
	catch (...)
	  {
		ACE_Guard<ACE_Thread_Mutex> guard(m_Subscribers.m_Mutex);
		Subs_it it = m_Subscribers.findById(subs_prof.id);
		m_Subscribers.eraseById(subs_prof.id);
		delete *it;
		std::cerr << "unknown exception in OutPort::subscribe" << std::endl;
		throw;
	  }

	// start Subscriber task
	(*m_Subscribers.findById(subs_prof.id))->open(0);
	return RTM_OK;
  }

  //------------------------------------------------------------
  // [CORBA interface] notify_subscribe()
  //
  // Subscribe this port
  //------------------------------------------------------------
  RtmRes OutPortBase::notify_subscribe(SubscriptionProfile& subs_prof)
	throw (CORBA::SystemException, RTM::PortBase::InvalidSubscription)
  {
	ACE_TRACE("OutPortBase::notify_subscribe()");
	
	// is subscription valid?
	if (!m_thisObjRef->_is_equivalent(subs_prof.out_port))
	  {
		throw RTM::PortBase::InvalidSubscription();
	  }
	SubscriberBase* subsb;
	switch(subs_prof.subscription_type)
	  {
	  case OPS_ONCE:
		subsb = new SubscriberOnce(this, subs_prof);
		break;
	  case OPS_PERIODIC:
		subsb = new SubscriberPeriodic(this, subs_prof);
		break;
	  case OPS_NEW:
		subsb = new SubscriberNew(this, subs_prof);
		break;
	  case OSP_PERIODIC_NEW:
		subsb = new SubscriberPeriodicNew(this, subs_prof);
		break;
	  case OPS_NEW_PERIODIC:
		subsb = new SubscriberNewPeriodic(this, subs_prof);
		break;
	  case OPS_PERIODIC_TRIGGERED:
		subsb = new SubscriberTriggerd(this, subs_prof);
		break;
	  case OPS_TRIGGERRED_PERIODIC:
		subsb = new SubscriberTriggerdPeriodic(this, subs_prof);
		break;
	  default:
		return RTM_ERR;
	  }

	ACE_Guard<ACE_Thread_Mutex> guard(m_Subscribers.m_Mutex);
	m_Subscribers.m_List.push_back(subsb);
	return RTM_OK;
  }

  
  //------------------------------------------------------------
  // [CORBA interface] unsubscribe(SubscriptionID id)
  //
  // Unsubscribe this subscription by subscription ID
  //------------------------------------------------------------
  RtmRes OutPortBase::unsubscribe(const char* id)
	throw (CORBA::SystemException, RTM::PortBase::NoSubscription)
  {
	try
	  {
		ACE_Guard<ACE_Thread_Mutex> guard(m_Subscribers.m_Mutex);
		SubscriberBase* subsb(*(m_Subscribers.findById(id)));
		m_Subscribers.eraseById(id);
		subsb->getInPort()->notify_unsubscribe(id);
		subsb->release(); // Subscriber delete itself
	  }
	catch (RTM::PortBase::NoSubscription& nse)
	  {
		throw nse;
	  }
	return RTM_OK;
  }
  

  RtmRes OutPortBase::notify_unsubscribe(const char* id)
	throw (CORBA::SystemException, RTM::PortBase::NoSubscription)
  {
	ACE_TRACE("OutPortBase::unsubscribe()");
	
	try
	  {
		ACE_Guard<ACE_Thread_Mutex> guard(m_Subscribers.m_Mutex);
		SubscriberBase* subsb(*(m_Subscribers.findById(id)));
		subsb->release();
		m_Subscribers.eraseById(id);
		delete subsb;
	  }
	catch (RTM::PortBase::NoSubscription& nse)
	  {
		throw nse;
	  }
	return RTM_OK;
  }
  //------------------------------------------------------------
  // [CORBA interface] inports()
  //
  // Return inports who subscribe this outport
  //------------------------------------------------------------
  /*
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
		inport_list[i] = InPort::_duplicate((*it)->getInPort());
		++i;
		++it;
	  }
	
	return inport_list._retn();
  }
  */

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
 
  SubscriptionList* OutPortBase::subscriptions()
  {


	ACE_Guard<ACE_Thread_Mutex> guard(m_Subscribers.m_Mutex);
	
	SubscriptionList_var subs_list = new SubscriptionList();
	subs_list->length(m_Subscribers.m_List.size());

	Subs_it it, it_end;
	it = m_Subscribers.m_List.begin();
	it_end = m_Subscribers.m_List.end();

	for (CORBA::ULong i = 0; it != it_end; ++i, ++it)
	  {
		subs_list[i] = (*it)->getSubsProfile();
	  }
	return subs_list._retn();
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
	Subs_it it, it_end;

	it     = m_Subscribers.m_List.begin();
	it_end = m_Subscribers.m_List.end();
	// Release correspondent port
	while (it != it_end)
	  {
		SubscriberBase* subsb(*it);
		char* id;
		id = CORBA::string_dup(subsb->getId());
		subsb->release();
		it = m_Subscribers.m_List.erase(it);
		delete subsb;
		subsb->getInPort()->notify_unsubscribe(id);
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
	Subs_it it, it_end;

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
	throw (CORBA::SystemException, RTM::PortBase::NoSubscription)
  {
	try
	  {
		SubscriberBase* subsb(*(m_Subscribers.findById(id)));
		subsb->release();
		m_Subscribers.eraseById(id);
		delete subsb;
		subsb->getInPort()->notify_unsubscribe(id);
	  }
	catch (RTM::PortBase::NoSubscription nse)
	  {
		throw nse;
	  }
	return RTM_OK;
  }

  OutPort_ptr OutPortBase::getObjRef()
  {
	return m_thisObjRef;
  }

  void OutPortBase::setObjRef(OutPort_ptr objref)
  {
	m_thisObjRef = RTM::OutPort::_duplicate(objref);

	return;
  }

  bool OutPortBase::Subscribers::eq_id::operator()(SubscriberBase* subs)
  {
	std::string id(subs->getId());
	return m_id == id;
  }
  
  OutPortBase::Subs_it OutPortBase::Subscribers::findById(const char* id)
  {
	Subs_it it;
	it = find_if(m_List.begin(),
				 m_List.end(),
				 eq_id(id));
	return it;
  }

  OutPortBase::Subs_it OutPortBase::Subscribers::eraseById(const char* id)
  {
	return m_List.erase(findById(id));
  }
  
}; // end of namespace RTM
