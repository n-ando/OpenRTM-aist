// -*- C++ -*-
/*!
 * @file PortAdmin.cpp
 * @brief RTC's Port administration class
 * @date $Date: 2008-01-14 07:56:11 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: PortAdmin.cpp,v 1.7.2.3 2008-01-14 07:56:11 n-ando Exp $
 *
 */

#include <functional>
#include <rtm/PortAdmin.h>
#include <rtm/CORBA_SeqUtil.h>

namespace RTC
{
  /*!
   * @if jp
   * @brief Port検索用ファンクタ
   * @else
   * @brief Functor to fing a Port
   * @endif
   */
  struct PortAdmin::find_port_name
  {
    find_port_name(const char* name) : m_name(name) {};
    bool operator()(const Port_ptr& p)
    {
      std::string name(p->get_port_profile()->name);
      return m_name == name;
    }
    const std::string m_name;
  };
  
  /*!
   * @if jp
   * @brief Port削除用ファンクタ
   * @else
   * @brief Functor to delete the Port
   * @endif
   */
  struct PortAdmin::del_port
  {
    PortAdmin* m_pa;
    del_port(PortAdmin* pa) : m_pa(pa) {};
    void operator()(PortBase* p)
    {
      m_pa->deletePort(*p);
    }
  };
  
  /*!
   * @if jp
   * @brief コンストラクタ
   * @else
   * @brief Constructor
   * @endif
   */
  PortAdmin::PortAdmin(CORBA::ORB_ptr orb, PortableServer::POA_ptr poa)
    : m_pORB(orb), m_pPOA(poa)
  {
  }
  
  /*!
   * @if jp
   * @brief PortList の取得
   * @else
   * @brief Get PortList
   * @endif
   */
  PortList* PortAdmin::getPortList() const
  {
    PortList_var ports;
    ports = new PortList(m_portRefs);
    return ports._retn();
  }
  
  /*!
   * @if jp
   * @brief PortProfileList の取得
   * @else
   * @brief Get PortProfileList
   * @endif
   */
  PortProfileList PortAdmin::getPortProfileList() const
  {
    PortProfileList port_profs;
    port_prof_collect p(port_profs);
    m_portServants.for_each(p);
    return port_profs;
  }
  
  /*!
   * @if jp
   * @brief Port のオブジェクト参照の取得
   * @else
   * @brief Get the reference to the Port's object
   * @endif
   */
  Port_ptr PortAdmin::getPortRef(const char* port_name) const
  {
    CORBA::Long index;
    index = CORBA_SeqUtil::find(m_portRefs, find_port_name(port_name));
    if (index >= 0) 
      {//throw NotFound(port_name);
	return RTC::Port::_duplicate(m_portRefs[index]);
      }
    return RTC::Port::_nil();
  }
  
  /*!
   * @if jp
   * @brief Port のサーバントのポインタの取得
   * @else
   * @brief Get pointer to the Port's servant
   * @endif
   */
  PortBase* PortAdmin::getPort(const char* port_name) const
  {
    return m_portServants.find(port_name);
  }
  
  /*!
   * @if jp
   * @brief Port を登録する
   * @else
   * @brief Regsiter the Port
   * @endif
   */
  void PortAdmin::registerPort(PortBase& port)
  {
    //CORBA Object activation
    //m_pPOA->activate_object(&port);
    
    //Setting Port's object reference to its profile
    //Port_ptr port_ref = Port::_narrow(m_pPOA->servant_to_reference(&port));
    //port.setPortRef(port.getRef());
    
    // Store Port's ref to PortList
    CORBA_SeqUtil::push_back(m_portRefs, port.getPortRef());
    
    // Store Port servant
    m_portServants.registerObject(&port);
  }
  
  /*!
   * @if jp
   * @brief Port の登録を解除する
   * @else
   * @brief Unregister the Port's registration
   * @endif
   */
  void PortAdmin::deletePort(PortBase& port)
  {
    try
      {
	port.disconnect_all();
	// port.shutdown();
	
	const char* tmp(port.getProfile().name);
	CORBA_SeqUtil::erase_if(m_portRefs, find_port_name(tmp));
	
	m_pPOA->deactivate_object(*m_pPOA->servant_to_id(&port));
	port.setPortRef(RTC::Port::_nil());
	
	m_portServants.unregisterObject(tmp);
      }
    catch (...)
      {
	;
      }
  }
  
  /*!
   * @if jp
   * @brief 名称指定によりPort の登録を解除する
   * @else
   * @brief Unregister the Port's registration by its name
   * @endif
   */
  void PortAdmin::deletePortByName(const char* port_name)
  {
    if (!port_name) return;
    PortBase& p(*m_portServants.find(port_name));
    deletePort(p);
  }
  
  /*!
   * @if jp
   * @brief 全ての Port をdeactivateし登録を削除する
   * @else
   * @brief Deactivate all Ports and unregister them
   * @endif
   */
  void PortAdmin::finalizePorts()
  {
    std::vector<PortBase*> ports;
    ports = m_portServants.getObjects();
    for_each(ports.begin(), ports.end(), del_port(this));
  }
};
