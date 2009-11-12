// -*- C++ -*-
/*!
 * @file  InPortTcpSockProvider.h
 * @brief InPortTcpSockProvider class
 * @date  $Date: 2007-12-31 03:08:04 $
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
 * $Id$
 *
 */

#ifndef RTC_INPORTTCPSOCKPROVIDER_H
#define RTC_INPORTTCPSOCKPROVIDER_H

#include <rtm/BufferBase.h>
#include <rtm/InPortProvider.h>
#include <rtm/TcpSockServer.h>
#include <rtm/StringUtil.h>
#include <rtm/Properties.h>
#include <rtm/CORBA_SeqUtil.h>

namespace RTC
{
  /*!
   * @if jp
   * @class InPortTcpSockProvider
   * @brief InPortTcpSockProvider クラス
   *
   * 通信手段に TCP ソケットを利用した入力ポートプロバイダの実装クラス。
   *
   * @param DataType 当該プロバイダに割り当てたバッファが保持するデータ型
   *
   * @since 0.4.1
   *
   * @else
   * @class InPortTcpSockProvider
   * @brief InPortTcpSockProvider class
   *
   * This is an implementation class of OutPort Provider 
   * that uses TCP socket for means of communication.
   *
   * @param DataType Data type held by the buffer that attached to this provider
   *
   * @since 0.4.1
   *
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
     *
     * コンストラクタ
     * ポートプロパティに以下の項目を設定する。
     *  - インターフェースタイプ : TCP_Any
     *  - データフロータイプ : Push
     *  - サブスクリプションタイプ : Any
     *
     * @param buffer 当該プロバイダに割り当てるバッファオブジェクト
     * @param prop TCP 通信設定用プロパティ
     *
     * @else
     * @brief Constructor
     *
     * Constructor
     * Set the following items to port properties
     *  - Interface type : TCP_Any
     *  - Data flow type : Push
     *  - Subscription type : Any
     *
     * @param buffer Buffer object that is attached to this provider
     * @param prop Property for setup TCP communication.
     *
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
    
    /*!
     * @if jp
     * @brief デストラクタ
     *
     * デストラクタ
     *
     * @else
     * @brief Destructor
     *
     * Destructor
     *
     * @endif
     */
    virtual ~InPortTcpSockProvider(void)
    {
    }
    
    /*!
     * @if jp
     * @brief Interface情報を公開する
     *
     * Interface情報を公開する。
     *
     * @param prop Interface情報を受け取るプロパティ
     *
     * @else
     * @brief Publish interface information
     *
     * Publish interface information
     *
     * @param prop Property for receiving interface information
     *
     * @endif
     */
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
#endif // RTC_INPORTTCPSOCKPROVIDER_H
