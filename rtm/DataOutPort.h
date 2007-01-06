// -*- C++ -*-
/*!
 * @file DataOutPort.h
 * @brief Base class of OutPort
 * @date $Date: 2007-01-06 17:44:11 $
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
 * $Id: DataOutPort.h,v 1.3 2007-01-06 17:44:11 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.2  2006/12/02 18:29:15  n-ando
 * Now OutPortCorbaProvider and InPortCorbaConsumer are used.
 *
 * Revision 1.1  2006/11/27 09:44:37  n-ando
 * The first commitment.
 *
 *
 */

#ifndef DataOutPort_h
#define DataOutPort_h

#include <rtm/RTObject.h>
#include <rtm/PortBase.h>
#include <rtm/BufferBase.h>
#include <rtm/OutPortCorbaProvider.h>
#include <rtm/InPortCorbaConsumer.h>
#include <rtm/OutPort.h>
#include <rtm/NVUtil.h>
#include <rtm/PublisherFactory.h>

namespace RTC
{
  /*!
   * @if jp
   * @class DataOutPort
   * @brief InPort 用 Port
   * @else
   * @class DataOutPort
   * @brief InPort abstruct class
   * @endif
   */
  class DataOutPort
    : public PortBase
  {
  public:
    /*!
     * @if jp
     * @brief コンストラクタ
     * @else
     * @brief Constructor
     * @endif
     */
    template <class DataType>
    DataOutPort(const char* name, OutPort<DataType>& outport)
      : PortBase(name), m_outport(outport)
    {
      // PortProfile::properties を設定
      addProperty("port.port_type",             "DataOutPort");
      
      m_providers.push_back(new OutPortCorbaProvider<DataType>(outport));

      m_consumers.push_back(new InPortCorbaConsumer<DataType>(outport));
    }


    /*!
     * @if jp
     * @brief デストラクタ
     * @else
     * @brief Destructor
     * @endif
     */
    virtual ~DataOutPort();

    
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
    
  protected:
    /*!
     * @if jp
     *
     * @brief Interface 情報を公開する
     *
     * このオペレーションは、notify_connect() 処理シーケンスの始めにコール
     * される純粋仮想関数である。
     * notify_connect() では、
     *
     * - publishInterfaces()
     * - connectNext()
     * - subscribeInterfaces()
     * - updateConnectorProfile()
     *
     * の順に protected 関数がコールされ接続処理が行われる。
     * <br>
     * このオペレーションは、新規の connector_id に対しては接続の生成、
     * 既存の connector_id に対しては更新が適切に行われる必要がある。
     *
     * @param connector_profile 接続に関するプロファイル情報
     * @return ReturnCode_t 型のリターンコード
     *
     * @else
     *
     * @brief Publish interface information
     *
     * This operation is pure virutal method that would be called at the
     * beginning of the notify_connect() process sequence.
     * In the notify_connect(), the following methods would be called in order.
     *
     * - publishInterfaces()
     * - connectNext()
     * - subscribeInterfaces()
     * - updateConnectorProfile() 
     *
     * This operation should create the new connection for the new
     * connector_id, and should update the connection for the existing
     * connection_id.
     *
     * @param connector_profile The connection profile information
     * @return The return code of ReturnCode_t type.
     *
     * @endif
     */
    virtual ReturnCode_t
    publishInterfaces(ConnectorProfile& connector_profile);
    

    /*! @if jp
     *
     * @brief Interface 情報を取得する
     *
     * このオペレーションは、notify_connect() 処理シーケンスの中間にコール
     * される純粋仮想関数である。
     * notify_connect() では、
     *
     * - publishInterfaces()
     * - connectNext()
     * - subscribeInterfaces()
     * - updateConnectorProfile()
     *
     * の順に protected 関数がコールされ接続処理が行われる。
     *
     * @param connector_profile 接続に関するプロファイル情報
     * @return ReturnCode_t 型のリターンコード
     *
     * @else
     *
     * @brief Publish interface information
     *
     * This operation is pure virutal method that would be called at the
     * mid-flow of the notify_connect() process sequence.
     * In the notify_connect(), the following methods would be called in order.
     *
     * - publishInterfaces()
     * - connectNext()
     * - subscribeInterfaces()
     * - updateConnectorProfile()
     *
     * @param connector_profile The connection profile information
     * @return The return code of ReturnCode_t type.
     *
     * @endif
     */
    virtual ReturnCode_t
    subscribeInterfaces(const ConnectorProfile& connector_profile);
    

    /*!
     * @if jp
     *
     * @brief Interface の接続を解除する
     *
     * このオペレーションは、notify_disconnect() 処理シーケンスの終わりにコール
     * される純粋仮想関数である。
     * notify_disconnect() では、
     * - disconnectNext()
     * - unsubscribeInterfaces()
     * - eraseConnectorProfile()
     * の順に protected 関数がコールされ接続解除処理が行われる。
     *
     * @param connector_profile 接続に関するプロファイル情報
     *
     * @else
     *
     * @brief Disconnect interface connection
     *
     * This operation is pure virutal method that would be called at the
     * end of the notify_disconnect() process sequence.
     * In the notify_disconnect(), the following methods would be called.
     * - disconnectNext()
     * - unsubscribeInterfaces()
     * - eraseConnectorProfile() 
     *
     * @param connector_profile The connection profile information
     *
     * @endif
     */
    virtual void
    unsubscribeInterfaces(const ConnectorProfile& connector_profile);


    
    struct publish
    {
      publish(SDOPackage::NVList& prop) : m_prop(prop) {}
      void operator()(OutPortProvider* provider)
      {
	provider->publishInterface(m_prop);
      }
      SDOPackage::NVList& m_prop;
    };

    struct unsubscribe
    {
      unsubscribe(const SDOPackage::NVList& prop) : m_prop(prop) {}
      void operator()(InPortConsumer* consumer)
      {
	consumer->unsubscribeInterface(m_prop);
      }
      const SDOPackage::NVList& m_prop;
    };

  private:
    struct find_conn_id;
    std::vector<OutPortProvider*> m_providers;
    std::vector<InPortConsumer*> m_consumers;
    OutPortBase& m_outport;

    PublisherFactory m_pf;

    struct subscribe
    {
      subscribe(const ConnectorProfile& prof)
	: m_prof(&prof), _consumer(NULL) 
      {
      }

      subscribe(const subscribe& subs)
	: m_prof(subs.m_prof),
	  _consumer(subs._consumer)
      {
      }

      subscribe& operator=(const subscribe& subs)
      {
	if (this == &subs) return *this;
	m_prof = subs.m_prof;
	_consumer = subs._consumer;
	return *this;
      }

      void operator()(InPortConsumer* cons)
      {
	if (cons->subscribeInterface(m_prof->properties))
	  {
	    _consumer = cons;
	  }
      }
      const ConnectorProfile* m_prof;
      InPortConsumer* _consumer;
    };


  };
}; // namespace RTC

#endif // DataOutPort_h
