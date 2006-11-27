// -*- C++ -*-
/*!
 * @file DataOutPort.h
 * @brief Base class of OutPort
 * @date $Date: 2006-11-27 09:44:37 $
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
 * $Id: DataOutPort.h,v 1.1 2006-11-27 09:44:37 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 *
 */

#ifndef DataOutPort_h
#define DataOutPort_h

#include <rtm/RTObject.h>
#include <rtm/PortBase.h>
#include <rtm/BufferBase.h>
#include <rtm/DataPort.h>
#include <rtm/NVUtil.h>
#include <rtm/PublisherFactory.h>

namespace RTC
{
  /*!
   * @if jp
   *
   * @class DataOutPort
   * @brief InPort 用 Port
   * @else
   * @class DataOutPort
   * @brief InPort abstruct class
   * @endif
   */
  
  class DataOutPort
    : public virtual PortBase
  {
    
  public:
    template <class DataType>
    DataOutPort(CORBA::ORB_ptr orb, PortableServer::POA_ptr poa,
		const char* name, BufferBase<DataType>* buffer,
		RTObject_ptr owner)
      : PortBase(orb, poa)
    {
      m_profile.name = CORBA::string_dup(name);
      m_profile.connector_profiles.length(0);
      m_profile.owner = owner;
      
      CORBA::Any any_var;
      DataType   tmp_var;
      any_var <<= tmp_var;
      
      addProperty("port.port_type",             "DataOutPort");
      addProperty("dataport.data_type",         any_var.type().name());
      addProperty("dataport.interface_type",    "CORBA_Any, RawTCP");
      addProperty("dataport.dataflow_type",     "Push, Pull");
      addProperty("dataport.subscription_type", "Once, New, Periodic");
      
      OutPortProvider<DataType> outport;
      outport = new OutPortProvider<DataType>(buffer);
      addProvider(name, "OutPortAny", outport);
      
      InPortConsumer<DataType> inport;
      inport = new InPortConsumer<DataType>();
      addConsumer(name, "InPortAny", inport);
    }
    
    virtual ~DataOutPort(){};

    /*!
     * @if jp
     * @brief [CORBA interface] Port の接続を行う
     *
     * OutPort と InPort との接続を行う。
     *
     * OutPort 側の connect() では以下のシーケンスで処理が行われる。
     *
     * 1. OutPort に関連する connector 情報の生成およびセット
     *
     * 2. InPortに関連する connector 情報の取得
     *  - ConnectorProfile::properties["dataport.corba_any.inport_ref"]に
     *    OutPortAny のオブジェクトリファレンスが設定されている場合、
     *    リファレンスを取得してConsumerオブジェクトにセットする。
     *    リファレンスがセットされていなければ無視して継続。
     *    (OutPortがconnect() 呼び出しのエントリポイントの場合は、
     *    InPortのオブジェクトリファレンスはセットされていないはずである。)
     * 3. PortBase::connect() をコール
     *    Portの接続の基本処理が行われる。
     * 4. 上記2.でInPortのリファレンスが取得できなければ、再度InPortに
     *    関連する connector 情報を取得する。
     *
     * 5. ConnectorProfile::properties で与えられた情報から、
     *    OutPort側の初期化処理を行う。
     *
     * - [dataport.interface_type]
     * -- CORBA_Any の場合: 
     *    InPortAny を通してデータ交換される。
     *    ConnectorProfile::properties["dataport.corba_any.inport_ref"]に
     *    InPortAny のオブジェクトリファレンスをセットする。
     * -- RawTCP の場合: Raw TCP socket を通してデータ交換される。
     *    ConnectorProfile::properties["dataport.raw_tcp.server_addr"]
     *    にInPort側のサーバアドレスをセットする。
     *
     * - [dataport.dataflow_type]
     * -- Pushの場合: Subscriberを生成する。Subscriberのタイプは、
     *    dataport.subscription_type に設定されている。
     * -- Pullの場合: InPort側がデータをPull型で取得するため、
     *    特に何もする必要が無い。
     *
     * - [dataport.subscription_type]
     * -- Onceの場合: SubscriberOnceを生成する。
     * -- Newの場合: SubscriberNewを生成する。
     * -- Periodicの場合: SubscriberPeriodicを生成する。
     *
     * - [dataport.push_interval]
     * -- dataport.subscription_type=Periodicの場合周期を設定する。
     *
     * 6. 上記の処理のうち一つでもエラーであれば、エラーリターンする。
     *    正常に処理が行われた場合はRTC::OKでリターンする。
     *  
     * @else
     * @brief [CORBA interface] Connect the Port
     * @endif
     */
    virtual ReturnCode_t connect(ConnectorProfile& connector_profile);
    virtual ReturnCode_t disconnect(const char* connector_id);
    
  protected:
    bool setOutPortRef(ConnectorProfile& cprof);
    bool getInPortRef(const ConnectorProfile& cprof);
    PublisherFactory m_pf;

  };
}; // namespace RTC

#endif // DataOutPort_h
