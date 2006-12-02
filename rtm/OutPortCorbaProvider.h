// -*- C++ -*-
/*!
 * @file  OutPortCorbaProvider.h
 * @brief OutPortCorbaProvider class
 * @date  $Date: 2006-12-02 18:48:21 $
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
 * $Id: OutPortCorbaProvider.h,v 1.1 2006-12-02 18:48:21 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.1  2006/11/27 09:44:42  n-ando
 * The first commitment.
 *
 */

#ifndef OutPortCorbaProvider_h
#define OutPortCorbaProvider_h

#include <rtm/idl/DataPortSkel.h>
#include <rtm/BufferBase.h>

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
    OutPortCorbaProvider(BufferBase<DataType>* buffer)
      : m_buffer(buffer)
    {}
    
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
      CORBA::Any_var tmp = new CORBA::Any();
      tmp <<= m_buffer->read();
      return tmp._retn();
    }
    
  private:
    BufferBase<DataType>* m_buffer;
  };
};     // namespace RTC
#endif // OutPortCorbaProvider_h

