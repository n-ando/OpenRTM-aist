// -*- C++ -*-
/*!
 * @file  OutPortTcpSockProvider.h
 * @brief OutPortTcpSockProvider class
 * @date  $Date: 2007-12-31 03:08:05 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2007-2008
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

#ifndef OutPortTcpSockProvider_h
#define OutPortTcpSockProvider_h

#include <rtm/BufferBase.h>
#include <rtm/OutPortProvider.h>

namespace RTC
{
  /*!
   * @if jp
   * @class OutPortTcpSockProvider
   * @brief OutPortTcpSockProvider クラス
   *
   * 通信手段に TCP ソケットを利用した出力ポートプロバイダーの実装クラス
   *
   * @param DataType 当該プロバイダに割り当てたバッファが保持するデータ型
   *
   * @else
   * @class OutPortTcpSockProvider
   * @brief OutPortTcpSockProvider class
   *
   * This is an implementation class of OutPort Provider 
   * that uses TCP socket for means of communication.
   *
   * @param DataType Data type held by the buffer that attached to this provider
   *
   * @endif
   */
  template <class DataType>
  class OutPortTcpSockProvider
    : public OutPortProvider
  {
  public:
    /*!
     * @if jp
     * @brief コンストラクタ
     *
     * コンストラクタ
     * ポートプロパティに以下の項目を設定する。
     *  - インターフェースタイプ : TCP_Any
     *  - データフロータイプ : Push, Pull
     *  - サブスクリプションタイプ : Flush, New, Periodic
     *
     * @param buffer 当該プロバイダに割り当てるバッファオブジェクト
     *
     * @else
     * @brief Constructor
     *
     * Constructor.
     * Set the following items to port properties.
     *  - Interface type : TCP_Any
     *  - Data flow type : Push, Pull
     *  - Subscription type : Flush, New, Periodic
     *
     * @param buffer Buffer object that is attached to this provider
     *
     * @endif
     */
    OutPortTcpSockProvider(BufferBase<DataType>& buffer)
      : m_buffer(buffer)
    {
      CORBA::Any any_var;
      DataType   tmp_var;
      any_var <<= tmp_var;
      
      // PortProfile setting
      setDataType(any_var.type()->name());
      setInterfaceType("TCP_Any");
      setDataFlowType("Push, Pull");
      setSubscriptionType("Flush, New, Periodic");
      
      // ConnectorProfile setting
      //      m_objref = this->_this();
      //      CORBA_SeqUtil::push_back(m_properties,
      //	       NVUtil::newNV("dataport.corba_any.outport_ref",
      //		     m_objref));
    }
    
    /*!
     * @if jp
     * @brief デストラクタ
     * @else
     * @brief Destructor
     * @endif
     */
    virtual ~OutPortTcpSockProvider(void)
    {}
    
    /*
      CORBA::Any* get()
      {
      DataType data;
      CORBA::Any_var tmp = new CORBA::Any();
      m_buffer.read(data);
      tmp <<= data;
      return tmp._retn();
      }
    */
    
  private:
    BufferBase<DataType>& m_buffer;
    //    OutPortAny_var m_objref;
  };
};     // namespace RTC
#endif // OutPortTcpSockProvider_h
