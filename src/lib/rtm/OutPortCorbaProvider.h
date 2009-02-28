// -*- C++ -*-
/*!
 * @file  OutPortCorbaProvider.h
 * @brief OutPortCorbaProvider class
 * @date  $Date: 2008-01-14 07:52:40 $
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
 * $Id$
 *
 */

#ifndef OutPortCorbaProvider_h
#define OutPortCorbaProvider_h

#include <rtm/idl/DataPortSkel.h>
#include <rtm/BufferBase.h>
#include <rtm/OutPortProvider.h>
#include <rtm/CORBA_SeqUtil.h>

namespace RTC
{
  /*!
   * @if jp
   * @class OutPortCorbaProvider
   * @brief OutPortCorbaProvider クラス
   *
   * 通信手段に CORBA を利用した出力ポートプロバイダーの実装クラス。
   *
   * @param DataType 当該プロバイダに割り当てたバッファが保持するデータ型
   *
   * @since 0.4.0
   *
   * @else
   * @class OutPortCorbaProvider
   * @brief OutPortCorbaProvider class
   *
   * This is an implementation class of OutPort Provider that uses 
   * CORBA for mean of communication.
   *
   * @param DataType Data type held by the buffer that is assigned to this 
   *        provider
   *
   * @since 0.4.0
   *
   * @endif
   */
  template <class DataType>
  class OutPortCorbaProvider
    : public OutPortProvider,
      public virtual POA_RTC::OutPortAny,
      public virtual PortableServer::RefCountServantBase
  {
  public:
    /*!
     * @if jp
     * @brief コンストラクタ
     *
     * コンストラクタ
     *
     * @param buffer 当該プロバイダに割り当てるバッファオブジェクト
     *
     * @else
     * @brief Constructor
     *
     * Constructor
     *
     * @param buffer Buffer object that is assigned to this provider
     *
     * @endif
     */
    OutPortCorbaProvider(BufferBase<DataType>& buffer)
      : m_buffer(buffer)
    {
      CORBA::Any any_var;
      DataType   tmp_var;
      any_var <<= tmp_var;
      
      // PortProfile setting
      setDataType(any_var.type()->name());
      setInterfaceType("CORBA_Any");
      setDataFlowType("Push, Pull");
      setSubscriptionType("Flush, New, Periodic");
      
      // ConnectorProfile setting
      m_objref = this->_this();
      CORBA_SeqUtil::push_back(m_properties,
			       NVUtil::newNV("dataport.corba_any.outport_ref",
					     m_objref));
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
    virtual ~OutPortCorbaProvider(void)
    {}
    
    /*!
     * @if jp
     * @brief バッファからデータを取得する
     *
     * 設定された内部バッファからデータを取得する。
     *
     * @return 取得データ
     *
     * @else
     * @brief Get data from the buffer
     *
     * Get data from the internal buffer.
     *
     * @return Data got from the buffer.
     *
     * @endif
     */
    CORBA::Any* get()
      throw (CORBA::SystemException)
    {
      DataType data;
      m_buffer.read(data);
      m_tmp <<= data;
      return new CORBA::Any(m_tmp);
    }
    
  private:
    BufferBase<DataType>& m_buffer;
    OutPortAny_var m_objref;
    CORBA::Any m_tmp;
  };
};     // namespace RTC
#endif // OutPortCorbaProvider_h
