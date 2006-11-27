// -*- C++ -*-
/*!
 * @file PortBase.h
 * @brief RTC's Port base class
 * @date $Date: 2006-11-27 09:57:04 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: PortBase.cpp,v 1.5 2006-11-27 09:57:04 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.4  2006/11/06 01:46:42  n-ando
 * #include <assert.h> was added.
 *
 * Revision 1.3  2006/11/06 01:16:31  n-ando
 * Now PortBase doesn't depend on PortProfileHelper.
 * Class refference manual has been updated.
 *
 * Revision 1.2  2006/10/17 19:06:37  n-ando
 * connect(), disconnect() and disconnect_all() was implemented.
 *
 * Revision 1.1  2006/10/17 10:22:07  n-ando
 * The first commitment.
 *
 */
// PortBase.o 74584, PortProfileHelper.o 82624
// (+ 74584 82624) 157208
// PortBase.o 87500 without PortProfileHelper
// PortBase.o 92292 with ACE_Guard
// PortBase.o 105340 impl local interfaces
#include <assert.h>
#include <rtm/PortBase.h>
#include <rtm/UUID.h>

namespace RTC
{
  //============================================================
  // class PortBase 
  //============================================================
  PortBase::PortBase(CORBA::ORB_ptr orb, PortableServer::POA_ptr poa)
    : m_pORB(orb), m_pPOA(poa)
  {
    // activate object and set port_ref
    PortableServer::ObjectId_var oid;
    oid = m_pPOA->activate_object(this);
    m_profile.port_ref = RTC::Port::_narrow(m_pPOA->id_to_reference(oid));
  }
  /*!
   * @if jp
   * @brief [CORBA interface] PortProfileを取得する
   * @else
   * @brief [CORBA interface] Get the PortProfile of the Port
   * @endif
   */
  PortProfile* PortBase::get_port_profile()
  {
    Guard gaurd(m_profile_mutex);
    PortProfile_var prof;
    prof = new PortProfile(m_profile);
    return prof._retn();
  }


  /*!
   * @if jp
   * @brief [CORBA interface] ConnectorProfileListを取得する
   * @else
   * @brief [CORBA interface] Get the ConnectorProfileList of the Port
   * @endif
   */
  ConnectorProfileList* PortBase::get_connector_profiles()
  {
    Guard gaurd(m_profile_mutex);
    ConnectorProfileList_var conn_prof;
    conn_prof = new ConnectorProfileList(m_profile.connector_profiles);
    return conn_prof._retn();
  }


  /*!
   * @if jp
   * @brief [CORBA interface] ConnectorProfile を取得する
   * @else
   * @brief [CORBA interface] Get the ConnectorProfile
   * @endif
   */
  ConnectorProfile* PortBase::get_connector_profile(const char* connector_id)
  {
    Guard gaurd(m_profile_mutex);
    CORBA::Long index;
    index = CORBA_SeqUtil::find(m_profile.connector_profiles,
				PortBase::find_conn_id(connector_id));
    if (index < 0)
      {
	ConnectorProfile_var conn_prof;
	conn_prof = new ConnectorProfile();
	return conn_prof._retn();
      }
    ConnectorProfile_var conn_prof;
    conn_prof = new ConnectorProfile(m_profile.connector_profiles[index]);
    return conn_prof._retn();
  }


  /*!
   * @if jp
   * @brief [CORBA interface] Port の接続を行う
   * @else
   * @brief [CORBA interface] Connect the Port
   * @endif
   */
  ReturnCode_t PortBase::connect(ConnectorProfile& connector_profile)
  {
    ReturnCode_t retval(RTC::OK);
    if (connector_profile.connector_id[(CORBA::ULong)0] != 0)
      {
	// this Port is the entry point of connection process.

	// "connector_id" stores UUID which is generated at the initial Port
	// in connection process.
	connector_profile.connector_id = CORBA::string_dup(getUUID().c_str());
	assert(connector_profile.connector_id[(CORBA::ULong)0] != 0);

	// The initial Port has the responsibility of connecting all
	//  the Ports stored in given ConnectionProfile.
	Guard gaurd(m_profile_mutex);
	connect_func f;
	f = CORBA_SeqUtil::for_each(connector_profile.ports,
				     connect_func(m_profile.port_ref,
						  connector_profile));
	retval = f.return_code;
      }
    else
      {
	// This Port is mid-flow of connection process
	
      }
    CORBA_SeqUtil::push_back(m_profile.connector_profiles, connector_profile);
    return retval;
  }


  /*!
   * @if jp
   * @brief [CORBA interface] Port の接続を解除する
   * @else
   * @brief [CORBA interface] Connect the Port
   * @endif
   */
  ReturnCode_t PortBase::disconnect(const char* connector_id)
  {
    Guard gaurd(m_profile_mutex);

    // The Port of which the reference is stored in the beginning of
    // ConnectorProfile's PortList is master Port.
    // The master Port has the responsibility of disconnecting all Ports.
    // The slave Ports have only responsibility of deleting its own
    // ConnectorProfile.

    // find connector_profile
    CORBA::Long index;
    index = CORBA_SeqUtil::find(m_profile.connector_profiles,
				find_conn_id(connector_id));
    if (index < 0) 
      {
	return RTC::BAD_PARAMETER;
      }
    ConnectorProfile connector_profile(m_profile.connector_profiles[index]);
    Port_var port_ref = m_profile.port_ref;
    disconnect_func f;
    if (port_ref->_is_equivalent(connector_profile.ports[0]))
      {
	// This Port is master
	// invoke disconnect() for all Ports

	f = CORBA_SeqUtil::for_each(connector_profile.ports,
				    disconnect_func(port_ref,
						    connector_profile));
      }
    CORBA_SeqUtil::erase(m_profile.connector_profiles, index);
    
    return f.return_code;
  }


  /*!
   * @if jp
   * @brief [CORBA interface] Port の全接続を解除する
   * @else
   * @brief [CORBA interface] Connect the Port
   * @endif
   */
  ReturnCode_t PortBase::disconnect_all()
  {
    Guard gaurd(m_profile_mutex);
    // disconnect all connections
    disconnect_all_func f;

    // Call disconnect() for each ConnectorProfile.
    f = CORBA_SeqUtil::for_each(m_profile.connector_profiles,
				disconnect_all_func(this));

    return f.return_code;
  }
  

  
  

  //============================================================
  // Local operations
  //============================================================
  void PortBase::addProvidor(const char* name, const char* type_name,
			     PortableServer::RefCountServantBase* provider)
  {
    // setup PortInterfaceProfile
    PortInterfaceProfile prof;
    prof.instance_name = CORBA::string_dup(name);
    prof.type_name     = CORBA::string_dup(type_name);
    prof.polarity      = PROVIDED;
    CORBA_SeqUtil::push_back(m_profile.interfaces, prof);

    // setup Provider List
    PortableServer::ObjectId_var oid;
    oid = m_pPOA->activate_object(provider);
    Provider prov;
    prov.name      = name;
    prov.type_name = type_name;
    prov.provider  = m_pPOA->id_to_reference(oid);
    m_providers.push_back(prov);
  }
  
  void PortBase::addConsumer(const char* name, const char* type_name,
			     ConsumerBase* consumer)
  {
    // setup PortInterfaceProfile
    PortInterfaceProfile prof;
    prof.instance_name = CORBA::string_dup(name);
    prof.type_name     = CORBA::string_dup(type_name);
    prof.polarity      = REQUIRED;
    CORBA_SeqUtil::push_back(m_profile.interfaces, prof);

    // setup Consumer List
    Consumer cons;
    cons.name      = name;
    cons.type_name = type_name;
    cons.consumer  = consumer;
    m_consumers.push_back(cons);
  }


  /*!
   * @if jp
   * @brief PortProfileを設定する
   * @else
   * @brief Set a PortProfile to the Port
   * @endif
   */
//  void PortBase::setProfile(const PortProfile& profile)
//  {
//    Guard gaurd(m_profile_mutex);
//    m_profile = profile;
//  }

  /*!
   * @if jp
   * @brief PortProfileを取得する
   * @else
   * @brief Get the PortProfile of the Port
   * @endif
   */
//  const PortProfile& PortBase::getProfile()
//  {
//    Guard guard(m_profile_mutex);
//    return m_profile;
//  }


  /*!
   * @if jp
   * @brief Port の名前を設定する
   * @else
   * @brief Set the name of this Port
   * @endif
   */
//  void PortBase::setName(const char* name)
//  {
//    Guard guard(m_profile_mutex);
//    m_profile.name = CORBA::string_dup(name);
//  }

  /*!
   * @if jp
   * @brief Port の名前を取得する
   * @else
   * @brief Get the name of this Port
   * @endif
   */
//  const char* PortBase::getName()
//  {
//    Guard gurad(m_profile_mutex);
//    return m_profile.name;
//  }


  /*!
   * @if jp
   * @brief Port の PortInterfaceProfileList を設定する
   * @else
   * @brief Set the PortInterfaceProfileList of this Port
   * @endif
   */
//  void PortBase::setInterfaceProfiles(PortInterfaceProfileList& if_profiles)
//  {
//    Guard gurad(m_profile_mutex);
//    CORBA_SeqUtil::clear(m_profile.interfaces);
//    m_profile.interfaces = if_profiles;
//  }


  /*!
   * @if jp
   * @brief Port の PortInterfaceProfile を追加する
   * @else
   * @brief Add the PortInterfaceProfile of this Port
   * @endif
   */
//  void PortBase::addInterfaceProfile(PortInterfaceProfile& if_profile)
//  {
//    Guard gurad(m_profile_mutex);
//    CORBA_SeqUtil::push_back(m_profile.interfaces, if_profile);
//  }


  /*!
   * @if jp
   * @brief Port の PortInterfaceProfileList を取得する
   * @else
   * @brief get the InterfaceprofileList of this Port
   * @endif
   */
//  PortInterfaceProfileList PortBase::getInterfaceProfiles()
//  {
//    Guard gurad(m_profile_mutex);
//    return m_profile.interfaces;
//  }


  /*!
   * @if jp
   * @brief Port の PortInterfaceProfile を取得する
   * @else
   * @brief Get the Interfaceprofile of this Port
   * @endif
   */
//  PortInterfaceProfile PortBase::getInterfaceProfile(const char* name)
//  {
//    Guard gurad(m_profile_mutex);
//    CORBA::Long index;
//    index = CORBA_SeqUtil::find(m_profile.interfaces,
//				PortBase::if_name(name));
//
//    //    if (index < 0) throw;
//    return m_profile.interfaces[index];
//  }


  /*!
   * @if jp
   * @brief Port のオブジェクト参照を設定する
   * @else
   * @brief Set the object reference of this Port
   * @endif
   */
  void PortBase::setPortRef(Port_ptr port_ref)
  {
    Guard gurad(m_profile_mutex);
    m_profile.port_ref = port_ref;
  }


   /*!
    * @if jp
    * @brief Port のオブジェクト参照を取得する
    * @else
    * @brief Get the object reference of this Port
    * @endif
    */
  Port_ptr PortBase::getPortRef()
  {
    Guard gurad(m_profile_mutex);
    return m_profile.port_ref;
  }


  /*!
   * @if jp
   * @brief ConnectorProfile を追加する
   * @else
   * @brief Set the ConnectorProfile to PortProfile
   * @endif
   */
//  void PortBase::addConnectorProfile(ConnectorProfile conn_prof)
//  {
//    Guard gurad(m_profile_mutex);
//    CORBA_SeqUtil::push_back(m_profile.connector_profiles, conn_prof);
//  }


  /*!
   * @if jp
   * @brief ConnectorProfile を削除する
   * @else
   * @brief Delete the ConnectorProfile
   * @endif
   */
//  void PortBase::eraseConnectorProfile(const char* id)
//  {
//    if (id == "") throw;
//
//    Guard gruad(m_profile_mutex);
//
//    CORBA::Long index;
//    index = CORBA_SeqUtil::find(m_profile.connector_profiles,
//				find_conn_id(id));
//    if (index < 0) throw;
//
//    CORBA_SeqUtil::erase(m_profile.connector_profiles, index);
//
//  }


  /*!
   * @if jp
   * @brief ConnectorProfileList を取得する
   * @else
   * @brief Get ConnectorProfileList
   * @endif
   */
//  const ConnectorProfileList& PortBase::getConnectorProfileList()
//  {
//    Guard gurad(m_profile_mutex);
//    return m_profile.connector_profiles;
//  }


  /*!
   * @if jp
   * @brief ConnectorProfile を取得する
   * @else
   * @brief Get ConnectorProfile
   * @endif
   */
//  const ConnectorProfile& PortBase::getConnectorProfile(const char* id)
//  {
//    if (id == "") throw;
//
//    Guard gurad(m_profile_mutex);
//    CORBA::Long index;
//    index = CORBA_SeqUtil::find(m_profile.connector_profiles,
//				find_conn_id(id));
//
//    if (index < 0) throw;
//    
//    return m_profile.connector_profiles[index];
//  }


  /*!
   * @if jp
   * @brief Port の owner の RTObject を指定する
   * @else
   * @brief Set the owner RTObject of the Port
   * @endif
   */
  void PortBase::setOwner(RTObject_ptr owner)
  {
    Guard gurad(m_profile_mutex); 

    m_profile.owner = owner;
  }


  /*!
   * @if jp
   * @brief Port の owner の RTObject を取得する
   * @else
   * @brief Get the owner RTObject of the Port
   * @endif
   */
//  RTObject_ptr PortBase::getOwner()
//  {
//    Guard gurad(m_profile_mutex);
//    return m_profile.owner;
//  }

  /*!
   * @if jp
   * @brief PortProfile の property を設定する
   * @else
   * @brief Set the properties of the PortProfile
   * @endif
   */
//  void PortBase::setProperties(const NVList& properties)
//  {
//    Guard gurad(m_profile_mutex);
//    m_profile.properties = properties;
//  }


  /*!
   * @if jp
   * @brief PortProfile の property を取得する
   * @else
   * @brief Get the properties of the PortProfile
   * @endif
   */
//  const NVList& PortBase::getProperties()
//  {
//    Guard gurad(m_profile_mutex);
//    return m_profile.properties;
//  }


  //============================================================
  // Protected functions
  //============================================================
  /*!
   * @if jp
   * @brief UUIDを生成する
   * @else
   * @brief Get the UUID
   * @endif
   */
  const std::string PortBase::getUUID() const
  {
    RTC_Utils::UUID_Generator uugen;
    uugen.init();
    RTC_Utils::UUID* uuid = uugen.generateUUID(2,0x01);
    
    return std::string(uuid->to_string()->c_str());
  }


}; // namespace RTC
