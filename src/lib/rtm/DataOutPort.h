// -*- C++ -*-
/*!
 * @file DataOutPort.h
 * @brief Base class of OutPort
 * @date $Date: 2008-01-13 15:06:58 $
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
 * $Id$
 *
 */

#ifndef DataOutPort_h
#define DataOutPort_h


#include <rtm/PortBase.h>
#include <rtm/BufferBase.h>
#include <rtm/OutPortCorbaProvider.h>
#include <rtm/InPortCorbaConsumer.h>
#include <rtm/OutPort.h>
#include <rtm/NVUtil.h>
#include <rtm/PublisherFactory.h>
#include <coil/Properties.h>

#ifdef RTC_SOCK_DATAPORT
#include <rtm/OutPortTcpSockProvider.h>
#include <rtm/InPortTcpSockConsumer.h>
#endif

namespace RTC
{
  /*!
   * @if jp
   * @class DataOutPort
   * @brief Outort 用 Port
   *
   * データ出力ポートの実装クラス。
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
   *    正常に処理が行われた場合はRTC::RTC_OKでリターンする。
   *  
   * @since 0.4.0
   *
   * @else
   * @class DataOutPort
   * @brief OutPort abstruct class
   * @endif
   */
  class DataOutPort
    : public PortBase
  {
  public:
    /*!
     * @if jp
     * @brief コンストラクタ
     *
     * コンストラクタ
     *
     * @param name ポート名称
     * @param outport 当該データ出力ポートに関連付けるOutPortオブジェクト
     *                OutPortオブジェクトで扱うデータ型、バッファタイプも指定する
     * @param prop ポート設定用プロパティ
     *
     * @else
     * @brief Constructor
     *
     * Constructor
     *
     * @param name Port name
     * @param outport OutPort object associated with this data output port.
     *                Specify also the data type and the buffer type used in
     *                the OutPort object.
     * @param prop Property for setting ports
     *
     * @endif
     */
    template <class DataType, template <class DataType> class Buffer>
    DataOutPort(const char* name, OutPort<DataType, Buffer>& outport,
		coil::Properties& prop)
      : PortBase(name), m_outport(outport)
    {
      // PortProfile::properties を設定
      addProperty("port.port_type", "DataOutPort");
      
      m_providers.push_back(new OutPortCorbaProvider<DataType>(outport));
      m_providers.back()->publishInterfaceProfile(m_profile.properties);
      
#ifdef RTC_SOCK_DATAPORT
      m_providers.push_back(new OutPortTcpSockProvider<DataType>(outport));
      m_providers.back()->publishInterfaceProfile(m_profile.properties);
#endif      
      m_consumers.push_back(new InPortCorbaConsumer<DataType>(outport));
#ifdef RTC_SOCK_DATAPORT
      m_consumers.push_back(new InPortTcpSockConsumer<DataType>(outport, prop));
#endif
    }
    
    /*!
     * @if jp
     * @brief デストラクタ
     *
     * デストラクタ
     *
     * @else
     * @brief Destructor
     *
     * Destructor
     *
     * @endif
     */
    virtual ~DataOutPort();
    
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
     *
     * @return ReturnCode_t 型のリターンコード
     *
     * @else
     *
     * @brief Publish interface information
     *
     * This operation is pure virutal function that would be called at the
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
     *
     * @return The return code of ReturnCode_t type.
     *
     * @endif
     */
    virtual ReturnCode_t
    publishInterfaces(ConnectorProfile& connector_profile);
    
    /*! @if jp
     *
     * @brief Interface に接続する
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
     *
     * @return ReturnCode_t 型のリターンコード
     *
     * @else
     *
     * @brief Subscribe to the interface
     *
     * This operation is pure virutal function that would be called at the
     * middle of the notify_connect() process sequence.
     * In the notify_connect(), the following methods would be called in order.
     *
     * - publishInterfaces()
     * - connectNext()
     * - subscribeInterfaces()
     * - updateConnectorProfile()
     *
     * @param connector_profile The connection profile information
     *
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
     * @brief Disconnect the interface connection
     *
     * This operation is pure virutal function that would be called at the
     * end of the notify_disconnect() process sequence.
     * In the notify_disconnect(), the following methods would be called.
     * - disconnectNext()
     * - unsubscribeInterfaces()
     * - eraseConnectorProfile() 
     *
     * @param connector_profile The profile information associated with 
     *                          the connection
     *
     * @endif
     */
    virtual void
    unsubscribeInterfaces(const ConnectorProfile& connector_profile);
    
    /*!
     * @if jp
     * @brief Interface公開用Functor
     * @else
     * @brief Functor to publish the interface
     * @endif
     */
    struct publish
    {
      publish(SDOPackage::NVList& prop) : m_prop(prop) {}
      void operator()(OutPortProvider* provider)
      {
	provider->publishInterface(m_prop);
      }
      SDOPackage::NVList& m_prop;
    };
    
    /*!
     * @if jp
     * @brief Interface接続解除用Functor
     * @else
     * @brief Functor to unsubscribe the interface
     * @endif
     */
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
