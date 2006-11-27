// -*- C++ -*-
/*!
 * @file  InPortProvider.h
 * @brief InPortProvider class
 * @date  $Date: 2006-11-27 09:44:40 $
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
 * $Id: InPortProvider.h,v 1.1 2006-11-27 09:44:40 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 */

#ifndef InPortProvider_h
#define InPortProvider_h

#include <rtm/idl/DataPortSkel.h>
#include <rtm/BufferBase.h>

namespace RTC
{
  /*!
   * @if jp
   * @class InPortProvider
   * @brief InPortProvider クラス
   * @else
   * @class InPortProvider
   * @brief InPortProvider class
   * @endif
   */
  template <class DataType>
  class InPortProvider
    : public virtual POA_RTC::InPortAny,
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
    InPortProvider(BufferBase<DataType>* buffer)
      : m_buffer(buffer)
    {
    }

    virtual ~InPortProvider()
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
#endif // InPortProvider_h

