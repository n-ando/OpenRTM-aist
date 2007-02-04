// -*- C++ -*-
/*!
 * @file DataOutPort.cpp
 * @brief Base class of OutPort
 * @date $Date: 2007-02-04 16:54:12 $
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
 * $Id: DataOutPort.cpp,v 1.4 2007-02-04 16:54:12 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.3  2007/01/06 17:44:00  n-ando
 * The behavior on notify_connect() and notify_disconnect() are now
 * implemented in protected functions(ex. publisherInterfaces()).
 *
 * Revision 1.2  2006/12/02 18:29:08  n-ando
 * Now OutPortCorbaProvider and InPortCorbaConsumer are used.
 *
 * Revision 1.1  2006/11/27 09:44:36  n-ando
 * The first commitment.
 *
 *
 */

#include <rtm/DataOutPort.h>
#include <rtm/CORBA_SeqUtil.h>
#include <rtm/NVUtil.h>
#include <rtm/PublisherBase.h>
#include <iostream>

namespace RTC
{
  DataOutPort::~DataOutPort()
  {
  };

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
  DataOutPort::publishInterfaces(ConnectorProfile& connector_profile)
  {
    std::for_each(m_providers.begin(), m_providers.end(),
		  publish(connector_profile.properties));
    return RTC::OK;
  }
  
  ReturnCode_t
  DataOutPort::subscribeInterfaces(const ConnectorProfile& connector_profile)
  {
    subscribe s(connector_profile);
    s = std::for_each(m_consumers.begin(), m_consumers.end(), s);
    if (s._consumer == NULL) return RTC::OK;
    
    // Pubslihser を生成
    PublisherBase* publisher;
    Properties prop(NVUtil::toProperties(connector_profile.properties));

    publisher = m_pf.create(s._consumer->clone(), prop);

    // Publisher を OutPort にアタッチ
    m_outport.attach(connector_profile.connector_id, publisher);

    return RTC::OK;
  }
  
  void
  DataOutPort::unsubscribeInterfaces(const ConnectorProfile& connector_profile)
  {
    PublisherBase* publisher;
    publisher = m_outport.detach(connector_profile.connector_id);
    delete publisher;
    return;
  }
  


};
