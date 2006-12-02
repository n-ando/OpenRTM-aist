// -*- C++ -*-
/*!
 * @file DataInPort.cpp
 * @brief Base class of InPort
 * @date $Date: 2006-12-02 18:25:30 $
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
 * $Id: DataInPort.cpp,v 1.2 2006-12-02 18:25:30 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.1  2006/11/27 09:44:35  n-ando
 * The first commitment.
 *
 *
 */

#include <rtm/DataInPort.h>
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
  ReturnCode_t DataInPort::connect(ConnectorProfile& connector_profile)
  {

    setInPortRef(connector_profile);


    bool outref;
    outref = getOutPortRef(connector_profile);


    ReturnCode_t retval;
    retval = PortBase::connect(connector_profile);
    if (retval != RTC::OK)
      return retval;


    if (!outref)
      outref = getOutPortRef(connector_profile);

    if (!outref)
      return RTC::ERROR;
    
    // 接続完了
    return retval;
  }


  bool DataInPort::setInPortRef(ConnectorProfile& cprof)
  {
    // ConnectorProfile::properties
    //
    // connector.type: CORBA, rawTCP, etc...
    //
    // CORBA の場合
    // connector.corba.iif_ref: InPortConnector の参照
    // connector.corba.oif_ref: OutPortConnector の参照
    // Raw TCP の場合
    // connector.rawtcp.inport_addr: サーバアドレス：ポート

    // 今のところCORBAしかないので無視
    //    std::string type;
    //    type = NVUtil::toString(prop, "connector.type");
    //    if (type == "") return false;

    CORBA_SeqUtil::push_back(cprof.properties,
			     NVUtil::newNV("dataport.corba_any.inport_ref",
					   m_providers[0].provider));
    return true;
  }


  bool DataInPort::getOutPortRef(ConnectorProfile& cprof)
  {
    try
      {
	CORBA::Any tmp;
	tmp = NVUtil::find(cprof.properties, "dataport.corba_any.outport_ref");
	OutPortAny_ptr outport;
	if (tmp >>= outport)
	  m_consumers[0].consumer->setObject(outport);
	else
	  return false;
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
  ReturnCode_t DataInPort::disconnect(const char* connector_id)
  {
    ReturnCode_t retcode;
    retcode = PortBase::disconnect(connector_id);

    // InPort の disconnect 処理を行う
    
    return retcode;
  }

};
