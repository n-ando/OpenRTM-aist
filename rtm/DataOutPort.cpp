// -*- C++ -*-
/*!
 * @file DataOutPort.cpp
 * @brief Base class of OutPort
 * @date $Date: 2007-12-31 03:08:02 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006-2008
 *     Noriaki Ando
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: DataOutPort.cpp,v 1.5.2.2 2007-12-31 03:08:02 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.5.2.1  2007/06/22 10:54:56  n-ando
 * The bug of OutPort's disconnect operation was fixed.
 *
 * Revision 1.5  2007/04/13 15:44:56  n-ando
 * RTC::OK was changed to RTC::RTC_OK.
 *
 * Revision 1.4  2007/02/04 16:54:12  n-ando
 * The disconnection process was implemented.
 *
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
  /*!
   * @if jp
   * @brief デストラクタ
   * @else
   * @brief Destructor
   * @endif
   */
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
    return RTC::RTC_OK;
  }
  
  /*!
   * @if jp
   * @brief Interface に接続する
   * @else
   * @endif
   */
  ReturnCode_t
  DataOutPort::subscribeInterfaces(const ConnectorProfile& connector_profile)
  {
    subscribe s(connector_profile);
    s = std::for_each(m_consumers.begin(), m_consumers.end(), s);
    if (s._consumer == NULL) return RTC::RTC_OK;
    
    // Pubslihser を生成
    PublisherBase* publisher;
    Properties prop(NVUtil::toProperties(connector_profile.properties));
    
    publisher = m_pf.create(s._consumer->clone(), prop);
    
    // Publisher を OutPort にアタッチ
    m_outport.attach(connector_profile.connector_id, publisher);
    
    return RTC::RTC_OK;
  }
  
  /*!
   * @if jp
   * @brief Interface の接続を解除する
   * @else
   * @endif
   */
  void
  DataOutPort::unsubscribeInterfaces(const ConnectorProfile& connector_profile)
  {
    PublisherBase* publisher;
    publisher = m_outport.detach(connector_profile.connector_id);
    m_pf.destroy(publisher);
    return;
  }
};
