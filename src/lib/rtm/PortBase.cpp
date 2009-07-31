// -*- C++ -*-
/*!
 * @file PortBase.cpp
 * @brief RTC's Port base class
 * @date $Date: 2008-01-14 10:19:42 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006-2009
 *     Noriaki Ando
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id$
 *
 */

#include <assert.h>
#include <memory>
#include <coil/UUID.h>
#include <rtm/PortBase.h>

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
    : rtclog(name)
  {
    m_objref = this->_this();
    m_profile.name = CORBA::string_dup(name);
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
    RTC_TRACE(("~PortBase()"));
    try
      {
        PortableServer::ObjectId_var oid = _default_POA()->servant_to_id(this);
        _default_POA()->deactivate_object(oid);
      }
    catch (...)
      {
        RTC_WARN(("Unknown exception caught."));
      }
  }
  
  /*!
   * @if jp
   * @brief [CORBA interface] PortProfileを取得する
   * @else
   * @brief [CORBA interface] Get the PortProfile of the Port
   * @endif
   */
  PortProfile* PortBase::get_port_profile()
    throw (CORBA::SystemException)
  {
    RTC_TRACE(("get_port_profile()"));
    Guard gaurd(m_profile_mutex);
    PortProfile_var prof;
    prof = new PortProfile(m_profile);
    return prof._retn();
  }
  
  /*!
   * @if jp
   * @brief PortProfile を取得する。
   * @else
   * @brief Get the PortProfile of the Port
   * @endif
   */
  const PortProfile& PortBase::getPortProfile() const
  {
    RTC_TRACE(("getPortProfile()"));
    return m_profile;
  }
  
  /*!
   * @if jp
   * @brief [CORBA interface] ConnectorProfileListを取得する
   * @else
   * @brief [CORBA interface] Get the ConnectorProfileList of the Port
   * @endif
   */
  ConnectorProfileList* PortBase::get_connector_profiles()
    throw (CORBA::SystemException)
  {
    RTC_TRACE(("get_connector_profiles()"));
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
    throw (CORBA::SystemException)
  {
    RTC_TRACE(("get_connector_profile(%s)", connector_id));
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
    throw (CORBA::SystemException)
  {
    RTC_TRACE(("connect()"));
    if (isEmptyId(connector_profile))
      {
        Guard gurad(m_profile_mutex);
	// "connector_id" stores UUID which is generated at the initial Port
	// in connection process.
	setUUID(connector_profile);
	assert(!isExistingConnId(connector_profile.connector_id));
      }
    else
      {
        Guard gurad(m_profile_mutex);
	if (isExistingConnId(connector_profile.connector_id))
	  {
            RTC_ERROR(("Connection already exists."));
	    return RTC::PRECONDITION_NOT_MET;
	  }
      }

    try
      {
	RTC::PortService_ptr p;
	p = connector_profile.ports[(CORBA::ULong)0];
	ReturnCode_t ret = p->notify_connect(connector_profile);
        if (ret != RTC::RTC_OK)
          {
            RTC_ERROR(("Connection failed. cleanup."));
            disconnect(connector_profile.connector_id);
          }
        return ret;
      }
    catch (...)
      {
	return RTC::BAD_PARAMETER;
      }
    return RTC::RTC_ERROR;
  }
  
  /*!
   * @if jp
   * @brief [CORBA interface] Port の接続通知を行う
   * @else
   * @brief [CORBA interface] Notify the Ports connection
   * @endif
   */
  ReturnCode_t PortBase::notify_connect(ConnectorProfile& connector_profile)
    throw (CORBA::SystemException)
  {
    RTC_TRACE(("notify_connect()"));

    ReturnCode_t retval[] = {RTC::RTC_OK, RTC::RTC_OK, RTC::RTC_OK};

    // publish owned interface information to the ConnectorProfile
    retval[0] = publishInterfaces(connector_profile);
    if (retval[0] != RTC::RTC_OK)
      {
        RTC_ERROR(("publishInterfaces() in notify_connect() failed."));
      }

    // call notify_connect() of the next Port
    retval[1] = connectNext(connector_profile);
    if (retval[1] != RTC::RTC_OK)
      {
        RTC_ERROR(("connectNext() in notify_connect() failed."));
      }

    // subscribe interface from the ConnectorProfile's information
    retval[2] = subscribeInterfaces(connector_profile);
    if (retval[2] != RTC::RTC_OK) 
      {
        RTC_ERROR(("subscribeInterfaces() in notify_connect() failed."));
      }

    RTC_PARANOID(("%d connectors are existing",
                  m_profile.connector_profiles.length()));

    Guard gurad(m_profile_mutex);
    CORBA::Long index(findConnProfileIndex(connector_profile.connector_id));
    if (index < 0)
      {
        CORBA_SeqUtil::push_back(m_profile.connector_profiles,
                                 connector_profile);
        RTC_PARANOID(("New connector_id. Push backed."));
      }
    else
      {
	m_profile.connector_profiles[index] = connector_profile;
        RTC_PARANOID(("Existing connector_id. Updated."));
      }

    for (int i(0), len(sizeof(retval)/sizeof(ReturnCode_t)); i < len; ++i)
      {
        if (retval[i] != RTC::RTC_OK)
          {
            return retval[i];
          }
      }
    return RTC::RTC_OK;
  }
  
  /*!
   * @if jp
   * @brief [CORBA interface] Port の接続を解除する
   * @else
   * @brief [CORBA interface] Disconnect the Port
   * @endif
   */
  ReturnCode_t PortBase::disconnect(const char* connector_id)
    throw (CORBA::SystemException)
  {
    RTC_TRACE(("disconnect(%s)", connector_id));

    CORBA::Long index(findConnProfileIndex(connector_id));
    if (index < 0)
      {
        RTC_ERROR(("Invalid connector id: %s", connector_id));
	return RTC::BAD_PARAMETER;
      }

    ConnectorProfile prof;
    { // lock and copy profile
      Guard guard(m_profile_mutex);
      prof = m_profile.connector_profiles[index];
    }

    if (prof.ports.length() < 1)
      {
        RTC_FATAL(("ConnectorProfile has empty port list."));
        return RTC::PRECONDITION_NOT_MET;
      }

    for (CORBA::ULong i(0), len(prof.ports.length()); i < len; ++i)
      {
        RTC::PortService_var p(prof.ports[i]);
        try
          {
            return p->notify_disconnect(connector_id);
          }
        catch (CORBA::SystemException &e)
          {
            RTC_WARN(("Exception caught: minor code(%d).", e.minor()));;
            continue;
          }
        catch (...)
          {
            RTC_WARN(("Unknown exception caught."));;
            continue;
          }
      }
    RTC_ERROR(("notify_disconnect() for all ports failed."));
    return RTC::RTC_ERROR;
  }
  
  /*!
   * @if jp
   * @brief [CORBA interface] Port の接続解除通知を行う
   * @else
   * @brief [CORBA interface] Notify the Ports disconnection
   * @endif
   */
  ReturnCode_t PortBase::notify_disconnect(const char* connector_id)
    throw (CORBA::SystemException)
  {
    RTC_TRACE(("notify_disconnect(%s)", connector_id));
    Guard gaurd(m_profile_mutex);

    // find connector_profile
    CORBA::Long index(findConnProfileIndex(connector_id));
    if (index < 0) 
      {
        RTC_ERROR(("Invalid connector id: %s", connector_id));
	return RTC::BAD_PARAMETER;
      }
    
    ConnectorProfile& prof(m_profile.connector_profiles[(CORBA::ULong)index]);
    ReturnCode_t retval(disconnectNext(prof));

    unsubscribeInterfaces(prof);
    
    CORBA_SeqUtil::erase(m_profile.connector_profiles, index);
    
    return retval;
  }
  
  /*!
   * @if jp
   * @brief [CORBA interface] Port の全接続を解除する
   * @else
   * @brief [CORBA interface] Disconnect the All Ports
   * @endif
   */
  ReturnCode_t PortBase::disconnect_all()
    throw (CORBA::SystemException)
  {
    RTC_TRACE(("disconnect_all()"));

    ::RTC::ConnectorProfileList plist;
    {
      Guard gaurd(m_profile_mutex);
      plist = m_profile.connector_profiles;
    }

    RTC::ReturnCode_t retcode(::RTC::RTC_OK);
    CORBA::ULong len(plist.length());
    RTC_DEBUG(("disconnecting %d connections.", len));
    for (CORBA::ULong i(0); i < len; ++i)
      {
        ReturnCode_t tmpret;
        tmpret =this->disconnect(plist[i].connector_id);
        if (tmpret != RTC::RTC_OK) retcode = tmpret;
      }
    
    return retcode;
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
    RTC_TRACE(("setName(%s)", name));
    Guard guard(m_profile_mutex);
    m_profile.name = CORBA::string_dup(name);
    rtclog.setName(name);
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
    RTC_TRACE(("getProfile()"));
    Guard guard(m_profile_mutex);
    return m_profile;
  }
  
  /*!
   * @if jp
   * @brief Port のオブジェクト参照を設定する
   * @else
   * @brief Set the object reference of the Port
   * @endif
   */
  void PortBase::setPortRef(PortService_ptr port_ref)
  {
    RTC_TRACE(("setPortRef()"));
    Guard gurad(m_profile_mutex);
    m_profile.port_ref = port_ref;
  }
  
  /*!
   * @if jp
   * @brief Port のオブジェクト参照を取得する
   * @else
   * @brief Get the object reference of the Port
   * @endif
   */
  PortService_ptr PortBase::getPortRef()
  {
    RTC_TRACE(("getPortRef()"));
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
    RTC_TRACE(("setOwner()"));
    Guard gurad(m_profile_mutex); 
    m_profile.owner = RTC::RTObject::_duplicate(owner);
  }
  
  //============================================================
  // protected operations
  //============================================================
  /*!
   * @if jp
   * @brief 次の Port に対して notify_connect() をコールする
   * @else
   * @brief Call notify_connect() for the next Port
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
	RTC::PortService_ptr p;
	p = connector_profile.ports[index];
	return p->notify_connect(connector_profile);
      }
    return RTC::RTC_OK;
  }
  
  /*!
   * @if jp
   * @brief 次の Port に対して notify_disconnect() をコールする
   * @else
   * @brief Call notify_disconnect() for the next Port
   * @endif
   */
  ReturnCode_t PortBase::disconnectNext(ConnectorProfile& cprof)
  {
    CORBA::ULong index;
    index = CORBA_SeqUtil::find(cprof.ports,
				find_port_ref(m_profile.port_ref));
    if (index < 0)
      {
        return RTC::BAD_PARAMETER;
      }
    
    CORBA::ULong len = cprof.ports.length();
    
    ++index;
    for (CORBA::ULong i(index); i < len; ++i)
      {
        RTC::PortService_var p;
        p = cprof.ports[i];
        try
          {
            return p->notify_disconnect(cprof.connector_id);
          }
        catch (CORBA::SystemException& e)
          {
            RTC_WARN(("Exception caught: minor code.", e.minor()));
            continue;
          } 
        catch (...)
          {
            RTC_WARN(("Unknown exception caught."));
            continue;
          }
      }
        
    return RTC::RTC_OK;
  }
  
  //============================================================
  // protected utility functions
  //============================================================
  /*!
   * @if jp
   * @brief ConnectorProfile の connector_id フィールドが空かどうか判定
   * @else
   * @brief Check whether connector_id of ConnectorProfile is empty
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
   * @brief Generate the UUID
   * @endif
   */
  const std::string PortBase::getUUID() const
  {
    coil::UUID_Generator uugen;
    uugen.init();
    std::auto_ptr<coil::UUID> uuid(uugen.generateUUID(2,0x01));
    
    return std::string((const char*)uuid->to_string());
  }
  
  /*!
   * @if jp
   * @brief UUIDを生成し ConnectorProfile にセットする
   * @else
   * @brief Generate the UUID and set it to the ConnectorProfile
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
   * @brief Check whether the given id exists in stored ConnectorProfiles
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
   * @brief Delete the interface registration from the PortInterfaceProfile
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
