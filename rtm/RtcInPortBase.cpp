/* -*- C++ -*-
 *
 * @file RtcInPortBase.cpp
 * @brief Input channel base class
 * @date $Date: 2005-05-27 07:31:40 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2003-2005
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: RtcInPortBase.cpp,v 1.2 2005-05-27 07:31:40 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.1.1.1  2005/05/12 09:06:18  n-ando
 * Public release.
 *
 *
 */
#include <ace/ACE.h>
#include <ace/UUID.h> 
#include "rtm/RtcBase.h"
#include "rtm/RtcOutPortBase.h"
#include "rtm/RtcSubscriber.h"
#include "rtm/RtcInPortBase.h"

namespace RTM
{

  //============================================================
  // CORBA interface
  //============================================================
  PortProfile* InPortBase::profile()
	throw (CORBA::SystemException)
  {
	PortProfile_var profile = new PortProfile(m_Profile);
	
	return profile._retn();
  }
  
  
  RtmRes InPortBase::subscribe(SubscriptionProfile& subs_prof)
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
		// Notify subscription peer OutPort		
		subs_prof.out_port->notify_subscribe(subs_prof);
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
		std::cerr << "unknown exception in InPort::subscribe" << std::endl;
		throw;
	  }

	return RTM_OK;
  }


  RtmRes InPortBase::notify_subscribe(SubscriptionProfile& subs_prof)
	throw (CORBA::SystemException, RTM::PortBase::InvalidSubscription)
  {
	if (!m_thisObjRef->_is_equivalent(subs_prof.in_port))
	  {
		throw RTM::PortBase::InvalidSubscription();
	  }
	SubsProfileBase* subsb;
	subsb = new SubsProfileBase(subs_prof);
	ACE_Guard<ACE_Thread_Mutex> guard(m_Subscribers.m_Mutex);
	m_Subscribers.m_List.push_back(subsb);
	return RTM_OK;
  }


  RtmRes InPortBase::unsubscribe(const char* id)
	throw (CORBA::SystemException, RTM::PortBase::NoSubscription)
  {
	try
	  {
		ACE_Guard<ACE_Thread_Mutex> guard(m_Subscribers.m_Mutex);
		SubsProfileBase* subsb(*(m_Subscribers.findById(id)));
		m_Subscribers.eraseById(id);
		delete subsb;
		subsb->getOutPort()->notify_unsubscribe(id);
	  }
	catch (RTM::PortBase::NoSubscription& nse)
	  {
		throw nse;
	  }
	return RTM_OK;
  }


  RtmRes InPortBase::notify_unsubscribe(const char* id)
	throw (CORBA::SystemException, RTM::PortBase::NoSubscription)
  {
	try
	  {
		ACE_Guard<ACE_Thread_Mutex> guard(m_Subscribers.m_Mutex);
		SubsProfileBase* subsb(*(m_Subscribers.findById(id)));
		m_Subscribers.eraseById(id);
		delete subsb;
	  }
	catch (RTM::PortBase::NoSubscription& nse)
	  {
		throw nse;
	  }
	return RTM_OK;
  }


  SubscriptionList* InPortBase::subscriptions()
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

  //------------------------------------------------------------
  // << Local interfaces >>
  //------------------------------------------------------------
  InPort_ptr InPortBase::getObjRef()
  {
	return m_thisObjRef;
  }

  void InPortBase::setObjRef(InPort_ptr objref)
  {
	m_thisObjRef = RTM::InPort::_duplicate(objref);

	return;
  }


  bool InPortBase::Subscribers::eq_id::operator()(SubsProfileBase* subs)
  {
	std::string id(subs->getId());
	return m_id == id;
  }
  
  InPortBase::Subs_it InPortBase::Subscribers::findById(const char* id)
  {
	Subs_it it;
	it = find_if(m_List.begin(),
				 m_List.end(),
				 eq_id(id));
	return it;
  }

  InPortBase::Subs_it InPortBase::Subscribers::eraseById(const char* id)
  {
	return m_List.erase(findById(id));
  }
  
};

