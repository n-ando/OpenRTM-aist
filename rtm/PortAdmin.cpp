// -*- C++ -*-
/*!
 * @file PortAdmin.cpp
 * @brief RTC's Port administration class
 * @date $Date: 2007-09-20 11:25:16 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: PortAdmin.cpp,v 1.7.2.1 2007-09-20 11:25:16 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.7  2007/04/23 04:55:40  n-ando
 * Port finalization process was modified.
 *
 * Revision 1.6  2007/01/12 14:37:57  n-ando
 * Since Port activates itself now, PortAdmin does not need to activate Port.
 *
 * Revision 1.5  2007/01/09 15:13:04  n-ando
 * Now Port does not have getName().
 * The name of Port is obtained from getProfile().
 *
 * Revision 1.4  2006/11/08 09:57:11  n-ando
 * A PortAdmin::getPortRef()'s bug was fixed.
 *
 * Revision 1.3  2006/11/06 01:18:59  n-ando
 * CORBA sequence manipulation has been rewritten by using CORBA_SeqUtil.
 *
 * Revision 1.2  2006/10/17 19:16:34  n-ando
 * registerPort() was modified to store Port's object reference in PortProfile.
 *
 * Revision 1.1  2006/10/17 10:21:56  n-ando
 * The first commitment.
 *
 */

#include <functional>
#include <rtm/PortAdmin.h>
#include <rtm/CORBA_SeqUtil.h>

namespace RTC
{
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
  
  struct PortAdmin::del_port
  {
    PortAdmin* m_pa;
    del_port(PortAdmin* pa) : m_pa(pa) {};
    void operator()(PortBase* p)
    {
      m_pa->deletePort(*p);
    }
  };


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
   * @brief Get PortList
   * @endif
   */
  Port_ptr PortAdmin::getPortRef(const char* port_name) const
  {
    Port_var port;
    CORBA::Long index;
    index = CORBA_SeqUtil::find(m_portRefs, find_port_name(port_name));
    if (index >= 0) 
      {//throw NotFound(port_name);
	port = m_portRefs[index];
      }
    return port._retn();
  }

  
  /*!
   * @if jp
   * @brief Port のサーバントのポインタの取得
   * @else
   * @brief Getpointer to the Port's servant
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
   * @brief Regsiter Port
   * @endif
   */
  void PortAdmin::registerPort(PortBase& port)
  {
    // CORBA Object activation
    //    m_pPOA->activate_object(&port);

    // Setting Port's object reference to its profile
    //    Port_ptr port_ref = Port::_narrow(m_pPOA->servant_to_reference(&port));
    //    port.setPortRef(port.getRef());

    // Store Port's ref to PortList
    CORBA_SeqUtil::push_back(m_portRefs, port.getPortRef());

    // Store Port servant
    m_portServants.registerObject(&port);
  }


  /*!
   * @if jp
   * @brief Port の登録を削除する
   * @else
   * @brief Delete the Port's registration
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
   * @brief Port の登録を削除する
   * @else
   * @brief Delete the Port' registration
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
   * @brief Unregister the Port
   * @endif
   */
  void PortAdmin::finalizePorts()
  {
    std::vector<PortBase*> ports;
    ports = m_portServants.getObjects();
    for_each(ports.begin(), ports.end(), del_port(this));
  }
  

};
