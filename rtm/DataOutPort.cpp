// -*- C++ -*-
/*!
 * @file DataOutPort.cpp
 * @brief Base class of OutPort
 * @date $Date: 2006-12-02 18:29:08 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006
 *     Noriaki Ando
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: DataOutPort.cpp,v 1.2 2006-12-02 18:29:08 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.1  2006/11/27 09:44:36  n-ando
 * The first commitment.
 *
 *
 */

#include <rtm/DataOutPort.h>
#include <rtm/CORBA_SeqUtil.h>
#include <rtm/NVUtil.h>


namespace RTC
{
  /*!
   * @if jp
   * @brief [CORBA interface] Port の接続を行う
   * @else
   * @brief [CORBA interface] Connect the Port
   * @endif
   */
  ReturnCode_t DataOutPort::connect(ConnectorProfile& connector_profile)
  {
    setOutPortRef(connector_profile);

    bool inref;
    inref = getInPortRef(connector_profile);

    ReturnCode_t retval;
    retval = PortBase::connect(connector_profile);
    if (retval != RTC::OK)
      return retval;

    if (!inref)
      inref = getInPortRef(connector_profile);

    if (!inref)
      return RTC::ERROR;

    // Subscriberを生成する。
    if (NVUtil::isString(connector_profile.properties,
			 "dataport.interface_type"))
      {
	std::string subs_type;
	subs_type = NVUtil::toString(connector_profile.properties,
				   "dataport.subscription_type");
	
	
	m_pubFactory.create(subs_type.c_str(),
			    m_inports["CORBA_Any"],
			    NVUtil::toProperties(connector_profile.properties));
	
      }
    return retval;
  }


  bool DataOutPort::setOutPortRef(ConnectorProfile& cprof)
  {
    // ConnectorProfile::properties
    //
    // connector.type: CORBA, rawTCP, etc...
    //
    // CORBA の場合
    // connector.corba.iif_ref: OutPortConnector の参照
    // connector.corba.oif_ref: OutPortConnector の参照
    // Raw TCP の場合
    // connector.rawtcp.inport_addr: サーバアドレス：ポート

    // 今のところCORBAしかないので無視
    //    std::string type;
    //    type = NVUtil::toString(prop, "connector.type");
    //    if (type == "") return false;

    CORBA_SeqUtil::push_back(cprof.properties,
			     NVUtil::newNV("dataport.corba_any.outportany_ref",
					   m_providers[0].provider));
    return true;
  }


  bool DataOutPort::getInPortRef(const ConnectorProfile& cprof)
  {
    try
      {
	CORBA::Any tmp;
	tmp = NVUtil::find(cprof.properties,
			   "dataport.corba_any.inportany_ref");
	InPortAny_ptr inport;
	if (tmp >>= inport)
	  m_consumers[0].consumer->setObject(inport);
	return true;
      }
    catch (...)
      {
	return false;
      }
    return false;
  }

  /*!
   * @if jp
   * @brief [CORBA interface] Port の接続を解除する
   * @else
   * @brief [CORBA interface] Connect the Port
   * @endif
   */
  ReturnCode_t DataOutPort::disconnect(const char* connector_id)
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
				PortBase::find_conn_id(connector_id));
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
				    PortBase::disconnect_func(port_ref,
						       connector_profile));
      }
    CORBA_SeqUtil::erase(m_profile.connector_profiles, index);
    
    return f.return_code;
  }

};
