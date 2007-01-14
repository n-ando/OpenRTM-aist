// -*- C++ -*-
/*!
 * @file  InPortCorbaProvider.h
 * @brief InPortCorbaProvider class
 * @date  $Date: 2007-01-14 23:01:47 $
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
 * $Id: InPortCorbaProvider.h,v 1.3 2007-01-14 23:01:47 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.2  2007/01/06 17:52:54  n-ando
 * Interface and its profile publish functions (publishInterfaceProfile()
 * and publishInterface()) are added.
 *
 * Revision 1.1  2006/12/02 18:41:02  n-ando
 * InPortCorbaProvider class is an implementation of InPortAny.
 *
 */

#ifndef InPortCorbaProvider_h
#define InPortCorbaProvider_h

#include <rtm/idl/DataPortSkel.h>
#include <rtm/BufferBase.h>
#include <rtm/InPortProvider.h>

namespace RTC
{
  /*!
   * @if jp
   * @class InPortCorbaProvider
   * @brief InPortCorbaProvider クラス
   * @else
   * @class InPortCorbaProvider
   * @brief InPortCorbaProvider class
   * @endif
   */
  template <class DataType>
  class InPortCorbaProvider
    : public InPortProvider,
      public virtual POA_RTC::InPortAny,
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
    InPortCorbaProvider(BufferBase<DataType>& buffer)
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
			       NVUtil::newNV("dataport.corba_any.inport_ref",
					     RTC::InPortAny::_duplicate(m_objref)));
    }

    virtual ~InPortCorbaProvider()
    {
    }

    virtual void put(const CORBA::Any& data)
    {
      DataType* tmp;
      if (data >>= tmp)
	{
	  m_buffer.write(*tmp);
	}
      return;
    }
  private:
    BufferBase<DataType>& m_buffer;
    RTC::InPortAny_var m_objref;
  };


};     // namespace RTC
#endif // InPortCorbaProvider_h

