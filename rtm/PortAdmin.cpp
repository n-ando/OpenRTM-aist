// -*- C++ -*-
/*!
 * @file PortAdmin.cpp
 * @brief RTC's Port administration class
 * @date $Date: 2006-10-17 19:16:34 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: PortAdmin.cpp,v 1.2 2006-10-17 19:16:34 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.1  2006/10/17 10:21:56  n-ando
 * The first commitment.
 *
 */

#include <rtm/PortAdmin.h>

namespace RTC
{
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
  const PortList* PortAdmin::getPorts() const
  {
    PortList_var ports = new PortList(m_portRefs);
    return ports._retn();
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
    Port_var port(m_portRefs.find(p_name(port_name)));
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
    m_pPOA->activate_object(&port);
    Port_ptr port_ref = Port::_narrow(m_pPOA->servant_to_reference(&port));
    port.getProfileHelper().setPortRef(port_ref);
    m_portRefs.push_back(port_ref);
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
    m_pPOA->deactivate_object(*m_pPOA->servant_to_id(&port));
    m_portRefs.erase_if(p_name(port.getProfile().name));
    port.getProfileHelper().setPortRef(RTC::Port::_nil());
    m_portServants.unregisterObject(std::string(port.getProfile().name));
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
    deletePort(*(m_portServants.find(port_name)));
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
    m_portServants.for_each(del_port(this));
  }
  

};
