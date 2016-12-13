// -*- C++ -*-
/*!
 * @file  CorbaPort.h
 * @brief CorbaPort class
 * @date  $Date: 2007-04-13 15:37:33 $
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
 * $Id: CorbaPort.cpp,v 1.3 2007-04-13 15:37:33 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.2  2007/01/21 17:16:34  n-ando
 * PortProfile.properties = {"port.port_type": "CorbaPort"}
 *
 * Revision 1.1  2007/01/04 00:45:13  n-ando
 * CORBA serivce provider/consumer Port implementation.
 *
 *
 */

#include <rtm/CorbaPort.h>
#include <rtm/CORBA_SeqUtil.h>
#include <rtm/NVUtil.h>
#include <string.h>
#include <iostream>

namespace RTC
{
  /*!
   * @if jp
   * @brief コンストラクタ
   * @else
   * @brief Constructor
   * @endif
   */
  CorbaPort::CorbaPort(const char* name)
    : PortBase(name)
  {
    addProperty("port.port_type", "CorbaPort");
  }


  /*!
   * @if jp
   * @brief デストラクタ
   * @else
   * @brief Destructor
   * @endif
   */
  CorbaPort::~CorbaPort()
  {
  }


  /*!
   * @if jp
   * @brief Provider を登録する
   * @else
   * @brief Register provider
   * @endif
   */
  bool
  CorbaPort::registerProvider(const char* instance_name,
			      const char* type_name,
			      PortableServer::RefCountServantBase& provider)
  {
    if (!appendInterface(instance_name, type_name, RTC::PROVIDED))
      {
	return false;
      }
    
    PortableServer::ObjectId_var oid;
    oid = _default_POA()->activate_object(&provider);
    CORBA::Object_ptr obj;
    obj = _default_POA()->id_to_reference(oid);
    
    //Provider prov(instance_name, type_name, m_pPOA->id_to_reference(oid));
    //m_providers.push_back(prov);
    
    std::string key("port");
    key.append(".");key.append(type_name);
    key.append(".");key.append(instance_name);

    CORBA_SeqUtil::
      push_back(m_providers, NVUtil::newNV(key.c_str(), obj));

    return true;
  };
  
  
  /*!
   * @if jp
   * @brief Consumer を登録する
   * @else
   * @brief Register consumer
   * @endif
   */
  bool
  CorbaPort::registerConsumer(const char* instance_name,
			      const char* type_name,
			      CorbaConsumerBase& consumer)
  {
    if (!appendInterface(instance_name, type_name, RTC::REQUIRED))
      {
	return false;
      }
    
    Consumer cons(instance_name, type_name, consumer);
    m_consumers.push_back(cons);

    return true;
  }
  


  //============================================================
  // protected functions
  //============================================================
  /*!
   * @if jp
   * @brief Interface 情報を公開する
   * @else
   * @brief Publish interface information
   * @endif
   */
  ReturnCode_t
  CorbaPort::publishInterfaces(ConnectorProfile& connector_profile)
  {
    CORBA_SeqUtil::push_back_list(connector_profile.properties,
				  m_providers);
    return RTC::RTC_OK;
  }


  /*!
   * @if jp
   * @brief Interface に接続する
   * @else
   * @brief Subscribe interfaces
   * @endif
   */
  ReturnCode_t
  CorbaPort::subscribeInterfaces(const ConnectorProfile& connector_profile)
  {
    const NVList& nv(connector_profile.properties);

    CORBA_SeqUtil::for_each(nv, subscribe(m_consumers));
    return RTC::RTC_OK;
  }


  /*!
   * @if jp
   * @brief Interface への接続を解除する
   * @else
   * @brief Unsubscribe interfaces
   * @endif
   */
  void
  CorbaPort::unsubscribeInterfaces(const ConnectorProfile& connector_profile)
  {
    const NVList& nv(connector_profile.properties);
    
    CORBA_SeqUtil::for_each(nv, unsubscribe(m_consumers));
  }

};
