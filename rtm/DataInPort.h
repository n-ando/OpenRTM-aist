// -*- C++ -*-
/*!
 * @file DataInPort.h
 * @brief RTC::Port implementation for Data InPort
 * @date $Date: 2007-01-06 17:43:39 $
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
 * $Id: DataInPort.h,v 1.2 2007-01-06 17:43:39 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.1  2006/12/02 18:27:49  n-ando
 * The first commitment.
 *
 *
 */

#ifndef DataInPort_h
#define DataInPort_h

#include <rtm/RTObject.h>
#include <rtm/PortBase.h>
#include <rtm/BufferBase.h>
#include <rtm/InPortCorbaProvider.h>
#include <rtm/OutPortCorbaConsumer.h>
#include <rtm/NVUtil.h>
#include <rtm/InPort.h>
namespace RTC
{
  /*!
   * @if jp
   *
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
    template <class DataType>
    DataInPort(const char* name, InPort<DataType>& inport)
      : PortBase(name)
    {
      // PortProfile::properties を設定
      addProperty("port.port_type", "DataInPort");

      m_providers.push_back(new InPortCorbaProvider<DataType>(inport));

      m_consumers.push_back(new OutPortCorbaConsumer<DataType>(inport));

    }

    virtual ~DataInPort(){};

    /*!
     * @if jp
     * @brief [CORBA interface] Port の接続を行う
     *
     * InPort と OutPort との接続を行う。
     *
     * InPort 側の connect() では以下のシーケンスで処理が行われる。
     *
     * 1. InPort に関連する connector 情報の生成およびセット
     *  - ConnectorProfile::properties["dataport.interface_type"] = CORBA_Any
     *    の場合、InPortAny を通して、RawTCP の場合 Raw TCP socket を通して
     *    データ交換される。
     *  - ConnectorProfile::properties["dataport.corba_any.inport_ref"]に
     *    InPortAny のオブジェクトリファレンスをセットする。(CORBA_Anyの場合)
     *  - ConnectorProfile::properties["dataport.raw_tcp.server_addr"]
     *    にInPort側のサーバアドレスをセットする。(RawTCP の場合)
     * 2. OutPortに関連する connector 情報の取得
     *  - ConnectorProfile::properties["dataport.corba_any.outport_ref"]に
     *    OutPortAny のオブジェクトリファレンスが設定されている場合、
     *    リファレンスを取得してConsumerオブジェクトにセットする。
     *    リファレンスがセットされていなければ無視して継続。
     *    (InPortがconnect() 呼び出しのエントリポイントの場合は、
     *    OutPortのオブジェクトリファレンスはセットされていないはずである。)
     * 3. PortBase::connect() をコール
     *    Portの接続の基本処理が行われる。
     * 4. 上記2.でOutPortのリファレンスが取得できなければ、再度OutPortに
     *    関連する connector 情報を取得する。
     * 5. 上記の処理のうち一つでもエラーであれば、エラーリターンする。
     *    正常に処理が行われた場合はRTC::OKでリターンする。
     *  
     * @else
     * @brief [CORBA interface] Connect the Port
     * @endif
     */
 

  protected:
    virtual ReturnCode_t
    publishInterfaces(ConnectorProfile& connector_profile);

    virtual ReturnCode_t
    subscribeInterfaces(const ConnectorProfile& connector_profile);

    virtual void
    unsubscribeInterfaces(const ConnectorProfile& connector_profile);
    
    struct publish
    {
      publish(SDOPackage::NVList& prop) : m_prop(prop) {}
      void operator()(InPortProvider* provider)
      {
	provider->publishInterface(m_prop);
      }
      SDOPackage::NVList& m_prop;
    };

    struct subscribe
    {
      subscribe(const SDOPackage::NVList& prop) : m_prop(prop) {}
      void operator()(OutPortConsumer* consumer)
      {
	consumer->subscribeInterface(m_prop);
      }
      const SDOPackage::NVList& m_prop;
    };

    struct unsubscribe
    {
      unsubscribe(const SDOPackage::NVList& prop) : m_prop(prop) {}
      void operator()(OutPortConsumer* consumer)
      {
	consumer->unsubscribeInterface(m_prop);
      }
      const SDOPackage::NVList& m_prop;
    };

  private:
    struct find_conn_id;
    std::vector<InPortProvider*> m_providers;
    std::vector<OutPortConsumer*> m_consumers;
  };
}; // namespace RTC

#endif // DataInPort_h
