// -*- C++ -*-
/*!
 * @file  OutPortProvider.h
 * @brief OutPortProvider class
 * @date  $Date: 2006-11-27 09:44:42 $
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
 * $Id: OutPortProvider.h,v 1.1 2006-11-27 09:44:42 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 */

#ifndef OutPortProvider_h
#define OutPortProvider_h

#include <rtm/idl/DataPortSkel.h>
#include <rtm/BufferBase.h>

namespace RTC
{
  /*!
   * @if jp
   * @class OutPortProvider
   * @brief OutPortProvider クラス
   * @else
   * @class OutPortProvider
   * @brief OutPortProvider class
   * @endif
   */
  template <class DataType>
  class OutPortProvider
    : public virtual POA_RTC::OutPortAny,
      public virtual PortableServer::RefCountServantBase
  {
    /*!
     * @if jp
     * @brief コンストラクタ
     * @else
     * @brief Constructor
     * @endif
     */
    OutPortProvider(BufferBase<DataType>* buffer)
      : m_buffer(buffer)
    {}
    
    /*!
     * @if jp
     * @brief デストラクタ
     * @else
     * @brief Destructor
     * @endif
     */
    virtual ~OutPortProvider()
    {}

    CORBA::Any* get()
    {
      CORBA::Any_var tmp = new CORBA::Any();
      tmp <<= m_buffer->read();
      return tmp._retn();
    }
    
  private:
    BufferBase<DataType>* m_buffer;
  };
};     // namespace RTC
#endif // OutPortProvider_h

