// -*- C++ -*-
/*!
 * @file PortBase.h
 * @brief RTC's Port base class
 * @date $Date: 2007-04-13 15:52:57 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: PortBase.cpp,v 1.8 2007-04-13 15:52:57 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.7  2007/02/04 17:00:22  n-ando
 * The ubsubscribeInterfaces is calle for disconnection.
 *
 * Revision 1.6  2007/01/04 00:43:42  n-ando
 * Now, notify_connect() and notify_disconnect() behavior can be customized
 * publishInterfaces(), subscribeInterfaces() and unsubscribeInterfaces().
 *
 * Revision 1.5  2006/11/27 09:57:04  n-ando
 * addProvider() function was added for registration of provider.
 * addConsumer() function was added for registration of consumer.
 *
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
#include <iostream>
namespace RTC
{
  //============================================================
  // class PortBase 
  //============================================================
  /*!
   * @if jp
   * @brief コンストラクタ
   * @else
   * @brief Constructor
   * @endif
   */
  PortBase::PortBase(const char* name)
  {
    m_profile.name = CORBA::string_dup(name);
    m_objref = RTC::Port::_duplicate(this->_this());
    m_profile.port_ref = m_objref;
    m_profile.owner = RTC::RTObject::_nil();
  }
  

  /*!
   * @if jp
   * @brief デストラクタ
   * @else
   * @brief Destructor
   * @endif
   */
  PortBase::~PortBase()
  {
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
    if (isEmptyId(connector_profile))
      {
	// "connector_id" stores UUID which is generated at the initial Port
	// in connection process.
	setUUID(connector_profile);
	assert(!isExistingConnId(connector_profile.connector_id));
      }
    return connector_profile.ports[0]->notify_connect(connector_profile);
  }


  /*!
   * @if jp
   * @brief [CORBA interface] Port の接続を行う
   * @else
   * @brief [CORBA interface] Connect the Port
   * @endif
   */
  ReturnCode_t PortBase::notify_connect(ConnectorProfile& connector_profile)
  {
    // publish owned interface information to the ConnectorProfile
    ReturnCode_t retval;
    retval = publishInterfaces(connector_profile);
    if (retval != RTC::RTC_OK) return retval;

    // call notify_connect() of the next Port
    retval = connectNext(connector_profile);
    if (retval != RTC::RTC_OK) return retval;

    // subscribe interface from the ConnectorProfile's information
    retval = subscribeInterfaces(connector_profile);
    if (retval != RTC::RTC_OK)
      {
	// cleanup this connection for downstream ports
	notify_disconnect(connector_profile.connector_id);
	return retval;
      }

    // update ConnectorProfile
    CORBA::Long index;
    index = findConnProfileIndex(connector_profile.connector_id);
    if (index < 0)
      {
	CORBA_SeqUtil::push_back(m_profile.connector_profiles,
				 connector_profile);
      }
    else
      {
	m_profile.connector_profiles[index] = connector_profile;
      }
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
    // find connector_profile
    if (!isExistingConnId(connector_id)) 
      {
	return RTC::BAD_PARAMETER;
      }
    CORBA::Long index;
    index = findConnProfileIndex(connector_id);
    ConnectorProfile prof(m_profile.connector_profiles[index]);

    return prof.ports[0]->notify_disconnect(connector_id);
  }


  /*!
   * @if jp
   * @brief [CORBA interface] Port の接続解除通知を行う
   * @else
   * @brief [CORBA interface] Notify the Ports disconnection
   * @endif
   */
  ReturnCode_t PortBase::notify_disconnect(const char* connector_id)
  {
    // The Port of which the reference is stored in the beginning of
    // ConnectorProfile's PortList is master Port.
    // The master Port has the responsibility of disconnecting all Ports.
    // The slave Ports have only responsibility of deleting its own
    // ConnectorProfile.

    // find connector_profile
    if (!isExistingConnId(connector_id)) 
      {
	
	return RTC::BAD_PARAMETER;
      }
    CORBA::Long index;
    index = findConnProfileIndex(connector_id);
    ConnectorProfile prof(m_profile.connector_profiles[index]);

    ReturnCode_t retval;
    retval = disconnectNext(prof);

    CORBA_SeqUtil::erase(m_profile.connector_profiles, index);
    
    return retval;
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
  /*!
   * @if jp
   * @brief Port の名前を設定する
   * @else
   * @brief Set the name of this Port
   * @endif
   */
  void PortBase::setName(const char* name)
  {
    Guard guard(m_profile_mutex);
    m_profile.name = CORBA::string_dup(name);
  }


  /*!
   * @if jp
   * @brief PortProfileを取得する
   * @else
   * @brief Get the PortProfile of the Port
   * @endif
   */
  const PortProfile& PortBase::getProfile() const
  {
    Guard guard(m_profile_mutex);
    return m_profile;
  }


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


  //============================================================
  // protected operations
  //============================================================
  /*!
   * @if jp
   * @brief 次の Port に対して notify_connect() をコールする
   * @else
   * @brief Call notify_connect() of the next Port
   * @endif
   */
  ReturnCode_t PortBase::connectNext(ConnectorProfile& connector_profile)
  {
    CORBA::Long index;
    index = CORBA_SeqUtil::find(connector_profile.ports,
				find_port_ref(m_profile.port_ref));
    
    if (index < 0) return RTC::BAD_PARAMETER;
    
    if (++index < static_cast<CORBA::Long>(connector_profile.ports.length()))
      {
	RTC::Port_var p;
	p = connector_profile.ports[index];
	return p->notify_connect(connector_profile);
      }
    return RTC::RTC_OK;
  }				  
  

  /*!
   * @if jp
   * @brief 次の Port に対して notify_disconnect() をコールする
   * @else
   * @brief Call notify_disconnect() of the next Port
   * @endif
   */
  ReturnCode_t PortBase::disconnectNext(ConnectorProfile& connector_profile)
  {
    CORBA::Long index;
    index = CORBA_SeqUtil::find(connector_profile.ports,
				find_port_ref(m_profile.port_ref));
    if (index < 0) return RTC::BAD_PARAMETER;
    
    if (++index < static_cast<CORBA::Long>(connector_profile.ports.length()))
      {
	RTC::Port_var p;
	p = connector_profile.ports[index];
	return p->notify_disconnect(connector_profile.connector_id);
      }
    unsubscribeInterfaces(connector_profile);
    return RTC::RTC_OK;
  }				  


  //============================================================
  // protected utility functions
  //============================================================
  /*!
   * @if jp
   * @brief ConnectorProfile の connector_id フィールドが空かどうか判定
   * @else
   * @brief Whether connector_id of ConnectorProfile is empty
   * @endif
   */
  bool PortBase::isEmptyId(const ConnectorProfile& connector_profile) const
  {
    return connector_profile.connector_id[(CORBA::ULong)0] == 0;
  }
  

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
  

  /*!
   * @if jp
   * @brief UUIDを生成し ConnectorProfile にセットする
   * @else
   * @brief Create and set the UUID to the ConnectorProfile
   * @endif
   */
  void PortBase::setUUID(ConnectorProfile& connector_profile) const
  {
    connector_profile.connector_id = CORBA::string_dup(getUUID().c_str());
    assert(connector_profile.connector_id[(CORBA::ULong)0] != 0);
  }
  

  /*!
   * @if jp
   * @brief id が既存の ConnectorProfile のものかどうか判定する
   * @else
   * @brief Whether the given id exists in stored ConnectorProfiles
   * @endif
   */
  bool PortBase::isExistingConnId(const char* id)
  {
    return CORBA_SeqUtil::find(m_profile.connector_profiles,
			       find_conn_id(id)) >= 0;
  }


  /*!
   * @if jp
   * @brief id を持つ ConnectorProfile を探す
   * @else
   * @brief Find ConnectorProfile with id
   * @endif
   */
  ConnectorProfile PortBase::findConnProfile(const char* id)
  {
    CORBA::Long index;
    index = CORBA_SeqUtil::find(m_profile.connector_profiles,
				find_conn_id(id));
    return m_profile.connector_profiles[index];
  }
  

  /*!
   * @if jp
   * @brief id を持つ ConnectorProfile を探す
   * @else
   * @brief Find ConnectorProfile with id
   * @endif
   */
  CORBA::Long PortBase::findConnProfileIndex(const char* id)
  {
    return CORBA_SeqUtil::find(m_profile.connector_profiles,
			       find_conn_id(id));
  }
  

  /*!
   * @if jp
   * @brief ConnectorProfile の追加もしくは更新
   * @else
   * @brief Append or update the ConnectorProfile list
   * @endif
   */
  void
  PortBase::updateConnectorProfile(const ConnectorProfile& connector_profile)
  {
    CORBA::Long index;
    index = CORBA_SeqUtil::find(m_profile.connector_profiles,
				find_conn_id(connector_profile.connector_id));
    
    if (index < 0)
      {
	CORBA_SeqUtil::push_back(m_profile.connector_profiles,
				 connector_profile);
      }
    else
      {
	m_profile.connector_profiles[index] = connector_profile;
      }
  }
  

  /*!
   * @if jp
   * @brief ConnectorProfile を削除する
   * @else
   * @brief Delete the ConnectorProfile
   * @endif
   */
  bool PortBase::eraseConnectorProfile(const char* id)
  {
    Guard gruad(m_profile_mutex);
    
    CORBA::Long index;
    index = CORBA_SeqUtil::find(m_profile.connector_profiles,
				find_conn_id(id));
    if (index < 0) return false;

    CORBA_SeqUtil::erase(m_profile.connector_profiles, index);
    return true;
  }


  /*!
   * @if jp
   * @brief PortInterfaceProfile に インターフェースを登録する
   * @else
   * @brief Append an interface to the PortInterfaceProfile
   * @endif
   */
  bool PortBase::appendInterface(const char* instance_name,
				 const char* type_name,
				 PortInterfacePolarity pol)
  {
    CORBA::Long index;
    index = CORBA_SeqUtil::find(m_profile.interfaces,
				find_interface(instance_name, pol));
    
    if (index >= 0) return false;
    // setup PortInterfaceProfile
    PortInterfaceProfile prof;
    prof.instance_name = CORBA::string_dup(instance_name);
    prof.type_name     = CORBA::string_dup(type_name);
    prof.polarity      = pol;
    CORBA_SeqUtil::push_back(m_profile.interfaces, prof);
    
    return true;
  }

  
  /*!
   * @if jp
   * @brief PortInterfaceProfile からインターフェース登録を削除する
   * @else
   * @brief Delete an interface from the PortInterfaceProfile
   * @endif
   */
  bool PortBase::deleteInterface(const char* name, PortInterfacePolarity pol)
  {
    CORBA::Long index;
    index = CORBA_SeqUtil::find(m_profile.interfaces,
				find_interface(name, pol));
    
    if (index < 0) return false;
    
    CORBA_SeqUtil::erase(m_profile.interfaces, index);
    return true;
  }

}; // namespace RTC
