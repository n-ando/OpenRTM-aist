// -*- C++ -*-
/*!
 * @file DataInPort.h
 * @brief RTC::Port implementation for Data InPort
 * @date $Date: 2007-01-21 17:16:58 $
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
 * $Id: DataInPort.h,v 1.6 2007-01-21 17:16:58 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.5  2007/01/21 09:43:22  n-ando
 * - A bug about memory access violation to m_providers still exists.
 *   This bug arises on Fedora5/gcc4 environment.
 *   To escape the bug temporarily dummy variable (m_dummy) is defined.
 * - Some functors were moved to cpp file.
 *
 * Revision 1.4  2007/01/14 22:57:48  n-ando
 * A bug fix about template argument for buffer-type in constructor.
 *
 * Revision 1.3  2007/01/12 14:29:48  n-ando
 * A trivial bug fix.
 *
 * Revision 1.2  2007/01/06 17:43:39  n-ando
 * The behavior on notify_connect() and notify_disconnect() are now
 * implemented in protected functions(ex. publisherInterfaces()).
 *
 * Revision 1.1  2006/12/02 18:27:49  n-ando
 * The first commitment.
 *
 *
 */

#ifndef DataInPort_h
#define DataInPort_h

#include <rtm/PortBase.h>
#include <rtm/BufferBase.h>
#include <rtm/InPortCorbaProvider.h>
#include <rtm/OutPortCorbaConsumer.h>
#include <rtm/NVUtil.h>
#include <rtm/InPort.h>
#include <stdio.h>

namespace RTC
{
  /*!
   * @if jp
   * @class DataInPort
   * @brief InPort 用 Port
   * @else
   * @class DataInPort
   * @brief InPort abstruct class
   * @endif
   */

  class DataInPort
    : public virtual PortBase
  {

  public:
    template <class DataType, template <class DataType> class Buffer>
    DataInPort(const char* name, InPort<DataType, Buffer>& inport)
      : PortBase(name)
    {
      // PortProfile::properties を設定
      addProperty("port.port_type", "DataInPort");

      m_providers.push_back(new InPortCorbaProvider<DataType>(inport));
      m_providers.back()->publishInterfaceProfile(m_profile.properties);
      m_consumers.push_back(new OutPortCorbaConsumer<DataType>(inport));
      m_dummy.push_back(1);
    }

    virtual ~DataInPort();

  protected:
    virtual ReturnCode_t
    publishInterfaces(ConnectorProfile& connector_profile);

    virtual ReturnCode_t
    subscribeInterfaces(const ConnectorProfile& connector_profile);

    virtual void
    unsubscribeInterfaces(const ConnectorProfile& connector_profile);
    
    struct publish;
    struct subscribe;
    struct unsubscribe;

  private:
    /*
     * Bug
     *
     * Fedora5/gcc4.1.1. にて DataInPort の先頭領域のメモリ破壊が
     * 起こっている模様。
     * (gdbでかなり粘って追ってみたが断念)
     * もともともは std::vector<InPortProvider*> m_providers が先頭
     * このままだと、
     * $vec->_M_impl._M_start:  begin() に相当？
     * $vec->_M_impl._M_finish: end() に相当？
     * においてい _M_start が不可解な位置を指すため、
     * m_providers に対して for_each を適用するとSegvで落ちる。
     *
     * FreeBSD6.0/gcc3.4.4ではこの現象は発生せず。
     */
    std::vector<int> m_dummy;
    std::vector<InPortProvider*> m_providers;
    std::vector<OutPortConsumer*> m_consumers;
  };
}; // namespace RTC

#endif // DataInPort_h
