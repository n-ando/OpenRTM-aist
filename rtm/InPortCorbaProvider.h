// -*- C++ -*-
/*!
 * @file  InPortCorbaProvider.h
 * @brief InPortCorbaProvider class
 * @date  $Date: 2006-12-02 18:41:02 $
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
 * $Id: InPortCorbaProvider.h,v 1.1 2006-12-02 18:41:02 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
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
    InPortCorbaProvider(BufferBase<DataType>* buffer)
      : m_buffer(buffer)
    {
    }

    virtual ~InPortCorbaProvider()
    {
    }

    virtual void put(const CORBA::Any& data)
    {
      DataType* tmp;
      if (data >>= tmp)
	{
	  m_buffer->write(tmp);
	}
      return;
    }
  private:
    BufferBase<DataType>* m_buffer;
  };


};     // namespace RTC
#endif // InPortCorbaProvider_h

