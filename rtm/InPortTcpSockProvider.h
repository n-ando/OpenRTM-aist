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
 * $Id: InPortTcpSockProvider.h,v 1.1.2.2 2007-12-31 03:08:04 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.1.2.1  2007/10/06 12:29:17  n-ando
 * InPort provider for TCP socket data port.
 *
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
     * 　インターフェースタイプ : TCP_Any
     * 　データフロータイプ : Push
     * 　サブスクリプションタイプ : Any
     *
     * @param buffer 当該プロバイダに割り当てるバッファオブジェクト
     * @param prop TCP 通信設定用プロパティ
     *
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
    
    /*!
     * @if jp
     * @brief デストラクタ
     *
     * デストラクタ
     *
     * @else
     * @brief Destructor
     * @endif
     */
    virtual ~InPortTcpSockProvider()
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
#endif // InPortTcpSockProvider_h
