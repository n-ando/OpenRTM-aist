// -*- C++ -*-
/*!
 * @file NamingManager.h
 * @brief naming Service helper class
 * @date $Date: 2007-12-31 03:08:04 $
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
 * $Id: NamingManager.cpp,v 1.4.2.1 2007-12-31 03:08:04 n-ando Exp $
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
  /*!
   * @if jp
   * @brief 指定した CORBA オブジェクトのNamingServiceへバインド
   * @else
   * @brief Bind the specified CORBA objects to NamingService
   * @endif
   */
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
  
  /*!
   * @if jp
   * @brief 指定した CORBA オブジェクトをNamingServiceからアンバインド
   * @else
   * @brief Unbind the specified CORBA object from NamingService
   * @endif
   */
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
  /*!
   * @if jp
   * @brief コンストラクタ
   * @else
   * @brief Constructor
   * @endif
   */
  NamingManager::NamingManager(Manager* manager)
    :m_manager(manager), 
     m_MedLogbuf(manager->getMedLogbuf()), rtcout(m_MedLogbuf)
  {
    m_MedLogbuf.setSuffix("naming_svc");
    rtcout.setLogLevel(manager->getConfig()["logger.log_level"]);
    rtcout.setLogLock(toBool(manager->getConfig()["logger.stream_lock"],
			     "enable", "disable", false));
  }
  
  /*!
   * @if jp
   * @brief デストラクタ
   * @else
   * @brief Destructor
   * @endif
   */
  NamingManager::~NamingManager()
  {
  }
  
  /*!
   * @if jp
   * @brief NameServer の登録
   * @else
   * @brief Register the NameServer
   * @endif
   */
  void NamingManager::registerNameServer(const char* method,
					 const char* name_server)
  {
    RTC_TRACE(("NamingManager::registerNameServer(%s, %s)",		\
	       method, name_server));
    NamingBase* name;
    name = createNamingObj(method, name_server);
    m_names.push_back(new Names(method, name_server, name));
  }
  
  /*!
   * @if jp
   * @brief 指定したオブジェクトのNamingServiceへバインド
   * @else
   * @brief Bind the specified objects to NamingService
   * @endif
   */
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
  
  /*!
   * @if jp
   * @brief NamingServer の情報の更新
   * @else
   * @brief Update information of NamingServer
   * @endif
   */
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
		RTC_INFO(("New name server found: %s/%s",		\
			  m_names[i]->method.c_str(),			\
			  m_names[i]->nsname.c_str()));
		m_names[i]->ns = nsobj;
		bindCompsTo(nsobj); // rebind all comps to new NS
	      }
	  }
      }
  }
  
  /*!
   * @if jp
   * @brief 指定したオブジェクトをNamingServiceからアンバインド
   * @else
   * @brief Unbind the specified object from NamingService
   * @endif
   */
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
  
  /*!
   * @if jp
   * @brief 全てのオブジェクトをNamingServiceからアンバインド
   * @else
   * @brief Unbind all objects from NamingService
   * @endif
   */
  void NamingManager::unbindAll()
  {
    RTC_TRACE(("NamingManager::unbindAll(): %d names.", m_compNames.size()));
    ACE_Guard<ACE_Thread_Mutex> guard(m_compNamesMutex);
    for (int i(0), len(m_compNames.size()); i < len; ++i)
      {
	unbindObject(m_compNames[i]->name.c_str());
      }
  }
  
  /*!
   * @if jp
   * @brief バインドされている全てのオブジェクトを取得
   * @else
   * @brief Get all bound objects
   * @endif
   */
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
  /*!
   * @if jp
   * @brief NameServer 管理用オブジェクトの生成
   * @else
   * @brief Create objects for NameServer management
   * @endif
   */
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
	    RTC_INFO(("NameServer connection succeeded: %s/%s",		\
		      method, name_server));
	    return name;
	  }
	catch (...)
	  {
	    RTC_INFO(("NameServer connection failed: %s/%s",		\
		      method, name_server));
	    return NULL;
	  }
      }
    return NULL;
  }
  
  /*!
   * @if jp
   * @brief 設定済みコンポーネントを NameServer に登録
   * @else
   * @brief Register the configured component to NameServer
   * @endif
   */
  void NamingManager::bindCompsTo(NamingBase* ns)
  {
    for (int i(0), len(m_compNames.size()); i < len; ++i)
      {
	ns->bindObject(m_compNames[i]->name.c_str(), m_compNames[i]->rtobj);
      }
  }
  
  /*!
   * @if jp
   * @brief NameServer に登録するコンポーネントの設定
   * @else
   * @brief Configure the components that will be registered to NameServer
   * @endif
   */
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
  
  /*!
   * @if jp
   * @brief NameServer に登録するコンポーネントの設定解除
   * @else
   * @brief Unregister the components that will be registered to NameServer
   * @endif
   */
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
