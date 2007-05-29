// -*- C++ -*-
/*!
 * @file NamingManager.h
 * @brief naming Service helper class
 * @date $Date: 2007-04-26 15:37:43 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: NamingManager.cpp,v 1.4 2007-04-26 15:37:43 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.3  2007/04/13 18:08:38  n-ando
 * Some changes for NameServers rebinding and objects rebinding.
 *
 * Revision 1.2  2007/01/14 19:43:28  n-ando
 * Debugging messages to stdout were deleted.
 *
 * Revision 1.1  2006/11/04 21:11:36  n-ando
 * NamingManager was introduced to support multiple name server.
 *
 */

#include <rtm/NamingManager.h>
#include <rtm/Manager.h>
#include <rtm/StringUtil.h>
#include <functional>
#include <algorithm>
#include <iostream>

namespace RTC
{
  void NamingOnCorba::bindObject(const char* name,
				 const RTObject_impl* rtobj)
  {
    try
      {
	m_cosnaming.rebindByString(name, rtobj->getObjRef(), true);
      }
    catch (...)
      {
	;
      }
  }

  void NamingOnCorba::unbindObject(const char* name)
  {
    try
      {
	m_cosnaming.unbind(name);
      }
    catch (...)
      {
	;
      }
  }

  //============================================================
  // NamingManager
  //============================================================
  NamingManager::NamingManager(Manager* manager)
    :m_manager(manager), 
     m_MedLogbuf(manager->getLogbuf()), rtcout(m_MedLogbuf)
  {
    m_MedLogbuf.setSuffix("naming_svc");
    m_MedLogbuf.setDateFmt(manager->getConfig()["logger.date_format"]);
    rtcout.setLogLevel(manager->getConfig()["logger.log_level"]);
    rtcout.setLogLock(toBool(manager->getConfig()["logger.stream_lock"],
			     "enable", "disable", false));
  }


  NamingManager::~NamingManager()
  {
    
  }


  void NamingManager::registerNameServer(const char* method,
					 const char* name_server)
  {
    RTC_TRACE(("NamingManager::registerNameServer(%s, %s)", \
	       method, name_server));
    NamingBase* name;
    name = createNamingObj(method, name_server);
    m_names.push_back(new Names(method, name_server, name));
  }
  

  void NamingManager::bindObject(const char* name, 
			       const RTObject_impl* rtobj)
  {
    RTC_TRACE(("NamingManager::bindObject(%s)", name));

    ACE_Guard<ACE_Thread_Mutex> guard(m_namesMutex);
    for (int i(0), len(m_names.size()); i < len; ++i)
      {
	if (m_names[i]->ns != NULL)
	  m_names[i]->ns->bindObject(name, rtobj);
      }
    registerCompName(name, rtobj);
  }

  
  void NamingManager::update()
  {
    RTC_TRACE(("NamingManager::update()"));

    ACE_Guard<ACE_Thread_Mutex> guard(m_namesMutex);
    
    for (int i(0), len(m_names.size()); i < len; ++i)
      {
	if (m_names[i]->ns == NULL) // if ns==NULL
	  { // recreate NamingObj
	    NamingBase* nsobj;
	    nsobj = createNamingObj(m_names[i]->method.c_str(),
				    m_names[i]->nsname.c_str());
	    if (nsobj != NULL) // if succeed
	      {
		RTC_INFO(("New name server found: %s/%s", \
			  m_names[i]->method.c_str(), \
			  m_names[i]->nsname.c_str()));
		m_names[i]->ns = nsobj;
		bindCompsTo(nsobj); // rebind all comps to new NS
	      }
	  }
      }
  }


  void NamingManager::unbindObject(const char* name)
  {
    RTC_TRACE(("NamingManager::unbindObject(%s)", name));

    ACE_Guard<ACE_Thread_Mutex> guard(m_namesMutex);
    for (int i(0), len(m_names.size()); i < len; ++i)
      {
	if (m_names[i]->ns != NULL)
	  m_names[i]->ns->unbindObject(name);
      }
    unregisterCompName(name);
  }


  void NamingManager::unbindAll()
  {
    RTC_TRACE(("NamingManager::unbindAll(): %d names.", m_compNames.size()));
    ACE_Guard<ACE_Thread_Mutex> guard(m_compNamesMutex);
    for (int i(0), len(m_compNames.size()); i < len; ++i)
      {
	unbindObject(m_compNames[i]->name.c_str());
      }
  }


  std::vector<RTObject_impl*> NamingManager::getObjects()
  {
    std::vector<RTObject_impl*> comps;
    ACE_Guard<ACE_Thread_Mutex> guard(m_compNamesMutex);

    for (int i(0), len(m_compNames.size()); i < len; ++i)
      {
	comps.push_back(const_cast<RTObject_impl*>(m_compNames[i]->rtobj));
      }
    return comps;
  }
    


  //============================================================
  // Protected
  //============================================================
  NamingBase* NamingManager::createNamingObj(const char* method,
					     const char* name_server)
  {
    std::string m(method);
    if (m == "corba")
      {
	try
	  {
	    NamingBase* name;
	    name = new NamingOnCorba(m_manager->getORB(), name_server);
	    if (name == NULL) return NULL;
	    RTC_INFO(("NameServer connection succeeded: %s/%s", \
		       method, name_server));
	    return name;
	  }
	catch (...)
	  {
	    RTC_INFO(("NameServer connection failed: %s/%s", \
		      method, name_server));
	    return NULL;
	  }
      }
    return NULL;
  }
  
  
  void NamingManager::bindCompsTo(NamingBase* ns)
  {
    for (int i(0), len(m_compNames.size()); i < len; ++i)
      {
	ns->bindObject(m_compNames[i]->name.c_str(), m_compNames[i]->rtobj);
      }
  }


  void NamingManager::registerCompName(const char* name,
				       const RTObject_impl* rtobj)
  {
    for (int i(0), len(m_compNames.size()); i < len; ++i)
      {
	if (m_compNames[i]->name == name)
	  {
	    m_compNames[i]->rtobj = rtobj;
	    return;
	  }
      }
    m_compNames.push_back(new Comps(name, rtobj));
    return;
  }
  

  void NamingManager::unregisterCompName(const char* name)
  {
    std::vector<Comps*>::iterator it(m_compNames.begin());
    for (int i(0), len(m_compNames.size()); i < len; ++i, ++it)
      {
	if (m_compNames[i]->name == name)
	  {
	    m_compNames.erase(it);
	    return;
	  }
      }
    return;
  }

}; // namespace RTC
