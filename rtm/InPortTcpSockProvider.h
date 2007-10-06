// -*- C++ -*-
/*!
 * @file  InPortTcpSockProvider.h
 * @brief InPortTcpSockProvider class
 * @date  $Date: 2007-10-06 12:29:17 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2007
 *     Noriaki Ando
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: InPortTcpSockProvider.h,v 1.1.2.1 2007-10-06 12:29:17 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 */

#ifndef InPortTcpSockProvider_h
#define InPortTcpSockProvider_h

#include <rtm/BufferBase.h>
#include <rtm/InPortProvider.h>
#include <rtm/TcpSockServer.h>
#include <rtm/StringUtil.h>

namespace RTC
{
  /*!
   * @if jp
   * @class InPortTcpSockProvider
   * @brief InPortTcpSockProvider クラス
   * @else
   * @class InPortTcpSockProvider
   * @brief InPortTcpSockProvider class
   * @endif
   */
  template <class DataType>
  class InPortTcpSockProvider
    : public InPortProvider
  {
  public:
    /*!
     * @if jp
     * @brief コンストラクタ
     * @else
     * @brief Constructor
     * @endif
     */
    InPortTcpSockProvider(BufferBase<DataType>& buffer, Properties& prop)
      : m_server(buffer, prop), m_buffer(buffer), m_prop(prop)
    {
      CORBA::Any any_var;
      DataType   tmp_var;
      any_var <<= tmp_var;
      
      // PortProfile setting
      setDataType(any_var.type()->name());
      setInterfaceType("TCP_Any");
      setDataFlowType("Push");
      setSubscriptionType("Any");

      // setup TCP server
      m_server.open(0);

      // set the TCP server address to properties
      std::string addr;
      addr  = m_server.getHostName();
      addr += ":";
      addr += otos(m_server.getPortNumber());
      CORBA_SeqUtil::push_back(m_properties,
	       NVUtil::newNV("dataport.tcp_any.inport_addr", addr.c_str()));
    }


    virtual ~InPortTcpSockProvider()
    {
    }


    void publishInterface(SDOPackage::NVList& prop)
    {
      if (!NVUtil::isStringValue(prop,
				 "dataport.interface_type",
				 "TCP_Any"))
	{
	  return;
	}
      SDOPackage::NVList nv(m_properties);
      NVUtil::append(prop, nv);
    }

  private:
    TcpServer<DataType> m_server;
    BufferBase<DataType>& m_buffer;
    Properties& m_prop;
  };
};     // namespace RTC
#endif // InPortTcpSockProvider_h

