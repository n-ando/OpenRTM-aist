// -*- C++ -*-
/*!
 * @file PortBase.h
 * @brief RTC's Port base class
 * @date $Date: 2006-10-17 19:06:37 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: PortBase.cpp,v 1.2 2006-10-17 19:06:37 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.1  2006/10/17 10:22:07  n-ando
 * The first commitment.
 *
 */

#include <rtm/PortBase.h>
#include <rtm/Util.h>
#include <rtm/UUID.h>

namespace RTC
{
  /*!
   * @if jp
   * @brief [CORBA interface] PortProfileを取得する
   * @else
   * @brief [CORBA interface] Get the PortProfile of the Port
   * @endif
   */
  PortProfile* PortBase::get_port_profile()
  {
    return m_profile.getPortProfile();
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
    ConnectorProfileList tmp;
    tmp = m_profile.getConnectorProfiles();
    ConnectorProfileList_var conn_prof(&tmp);
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
    ConnectorProfile tmp;
    tmp = m_profile.getConnectorProfileById(connector_id);
    ConnectorProfile_var conn_prof(&tmp);
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
	connect_func f;
	f = SeqHelper::for_each(connector_profile.ports,
				connect_func(getProfileHelper().getPortRef(),
					     connector_profile));
	retval = f.return_code;
	
      }
    else
      {
	// This Port is mid-flow of connection process
	
      }
    m_profile.appendConnectorProfile(connector_profile);
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
    // The Port of which the reference is stored in the beginning of
    // ConnectorProfile's PortList is master Port.
    // The master Port has the responsibility of disconnecting all Ports.
    // The slave Ports have only responsibility of deleting its own
    // ConnectorProfile.
    ConnectorProfile connector_profile;
    connector_profile = m_profile.getConnectorProfileById(connector_id);
    Port_var ref = getProfileHelper().getPortRef();

    if (ref->_is_equivalent(connector_profile.ports[0]))
      {
	// This Port is master
	// invoke disconnect() for all Ports
	disconnect_func f;
	f = SeqHelper::for_each(connector_profile.ports,
				disconnect_func(ref, connector_profile));
      }
    m_profile.eraseConnectorProfileById(connector_id);
    
    return RTC::OK;
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
    // disconnect all connections
    ConnectorProfileList conn_profs;
    conn_profs = m_profile.getConnectorProfiles();
    disconnect_all_func f;

    // Call disconnect() for each ConnectorProfile.
    f = SeqHelper::for_each(conn_profs, disconnect_all_func(this));

    return f.return_code;
  }
  
  /*!
   * @if jp
   *
   * @brief PortProfileを取得する
   *
   * Portが保持するPortProfileを返す。
   *
   * @return この Port の PortProfile
   *
   * @else
   *
   * @brief Get the PortProfile of the Port
   *
   * This operation returns the PortProfile of the Port.
   *
   * @return the PortProfile of the Port
   *
   * @endif
   */
  /*
  const PortProfile& PortBase::getProfile() const
  {
    return *(m_profile.getPortProfile());
  }
  */  
  PortProfileHelper& PortBase::getProfileHelper()
  {
    return m_profile;
  }
  /*!
   * @if jp
   *
   * @brief Port に PortProfile を設定する
   *
   * PortProfileを設定する。
   *
   * @param profile Port に与える PortProfile
   *
   * @else
   *
   * @brief Set the PortProfile of the Port
   *
   * This operation sets the PortProfile of the Port.
   *
   * @param profile The PortProfile to be set to the Port
   *
   * @endif
   */
  void PortBase::setProfile(const PortProfile& profile)
  {
    m_profile.setPortProfile(profile);
  }

  const std::string PortBase::getUUID() const
  {
    RTC_Utils::UUID_Generator uugen;
    uugen.init();
    RTC_Utils::UUID* uuid = uugen.generateUUID(2,0x01);

    return std::string(uuid->to_string()->c_str());
  }

}; // namespace RTC
