// -*- C++ -*-
/*!
 * @file DataInPort.h
 * @brief RTC::Port implementation for Data InPort
 * @date $Date: 2006-12-02 18:27:49 $
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
 * $Id: DataInPort.h,v 1.1 2006-12-02 18:27:49 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
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
    DataInPort(CORBA::ORB_ptr orb, PortableServer::POA_ptr poa,
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

      addProperty("port.port_type",             "DataInPort");
      addProperty("dataport.data_type",         any_var.type().name());
      addProperty("dataport.interface_type",    "CORBA_Any, RawTCP");
      addProperty("dataport.dataflow_type",     "Push, Pull");
      addProperty("dataport.subscription_type", "Any");

      InPortCorbaProvider<DataType>* inport;
      inport = new InPortCorbaProvider<DataType>(buffer);
      addProvider(name, "InPortAny", inport);

      OutPortConsumer* outport;
      outport = new OutPortCorbaConsumer<DataType>();
      addConsumer(name, "OutPortAny", outport);
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
    virtual ReturnCode_t connect(ConnectorProfile& connector_profile);
    virtual ReturnCode_t disconnect(const char* connector_id);

  protected:
    bool setInPortRef(ConnectorProfile& cprof);
    bool getOutPortRef(ConnectorProfile& cprof);
  private:
    struct find_conn_id;
  };
}; // namespace RTC

#endif // DataInPort_h
