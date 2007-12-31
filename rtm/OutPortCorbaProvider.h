// -*- C++ -*-
/*!
 * @file  OutPortCorbaProvider.h
 * @brief OutPortCorbaProvider class
 * @date  $Date: 2007-12-31 03:08:05 $
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
 * $Id: OutPortCorbaProvider.h,v 1.5.2.1 2007-12-31 03:08:05 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.5  2007/02/04 16:56:00  n-ando
 * The subscription types were updated.
 *
 * Revision 1.4  2007/01/21 10:25:24  n-ando
 * A trivial fix.
 *
 * Revision 1.3  2007/01/14 23:01:53  n-ando
 * Now object reference is duplicate to set property.
 *
 * Revision 1.2  2007/01/06 17:57:35  n-ando
 * Interface subscription/unsubscription functions (subscribeInterface()
 * and unsubscribeInterface()) are added.
 *
 * Revision 1.1  2006/12/02 18:48:21  n-ando
 * The first commitment.
 *
 * Revision 1.1  2006/11/27 09:44:42  n-ando
 * The first commitment.
 *
 */

#ifndef OutPortCorbaProvider_h
#define OutPortCorbaProvider_h

#include <rtm/idl/DataPortSkel.h>
#include <rtm/BufferBase.h>
#include <rtm/OutPortProvider.h>

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
     * @endif
     */
    virtual ~OutPortCorbaProvider()
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
     *
     * @endif
     */
    CORBA::Any* get()
    {
      DataType data;
      CORBA::Any_var tmp = new CORBA::Any();
      m_buffer.read(data);
      tmp <<= data;
      return tmp._retn();
    }
    
  private:
    BufferBase<DataType>& m_buffer;
    OutPortAny_var m_objref;
  };
};     // namespace RTC
#endif // OutPortCorbaProvider_h
