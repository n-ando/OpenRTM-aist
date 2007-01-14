// -*- C++ -*-
/*!
 * @file  OutPortCorbaProvider.h
 * @brief OutPortCorbaProvider class
 * @date  $Date: 2007-01-14 23:01:53 $
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
 * $Id: OutPortCorbaProvider.h,v 1.3 2007-01-14 23:01:53 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
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
      setSubscriptionType("Any");

      // ConnectorProfile setting
      m_objref = this->_this();
      CORBA_SeqUtil::push_back(m_properties,
			       NVUtil::newNV("dataport.corba_any.outport_ref",
					     RTC::OutPortAny::_duplicate(m_objref)));
    }
    
    /*!
     * @if jp
     * @brief デストラクタ
     * @else
     * @brief Destructor
     * @endif
     */
    virtual ~OutPortCorbaProvider()
    {}

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

