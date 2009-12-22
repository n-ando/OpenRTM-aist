// -*- C++ -*-
/*!
 * @file InPortBase.h
 * @brief RTC::Port implementation for InPort
 * @date $Date: 2008-01-13 15:06:40 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006-2009
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

#ifndef RTC_INPORTBASE_H
#define RTC_INPORTBASE_H

#include <rtm/PortBase.h>
#include <rtm/DataPortStatus.h>
#include <rtm/CdrBufferBase.h>
#include <rtm/ConnectorListener.h>

/*!
 * @if jp
 * @namespace RTC
 *
 * @brief RTコンポーネント
 *
 * @else
 *
 * @namespace RTC
 *
 * @brief RT-Component
 *
 * @endif
 */
namespace RTC
{
  class InPortProvider;
  class OutPortConsumer;
  class InPortConnector;

  /*!
   * @if jp
   * @class InPortBase
   * @brief InPort 用 Port
   *
   * データ入力ポートの実装クラス。
   *
   * @since 0.4.0
   *
   * @else
   * @class InPortBase
   * @brief Port for InPort
   *
   * This is an implementation class for the data input port.
   *
   * @since 0.4.0
   *
   * @endif
   */
  class InPortBase
    : public PortBase, public DataPortStatus
  {
  public:
    DATAPORTSTATUS_ENUM

    typedef std::vector<InPortConnector*> ConnectorList;

    /*!
     * @if jp
     * @brief コンストラクタ
     *
     * コンストラクタ
     *
     * @param name ポート名称
     * @param inport 当該データ入力ポートに関連付けるInPortオブジェクト
     *               InPortオブジェクトで扱うデータ型、バッファタイプも指定する
     * @param prop ポート設定用プロパティ
     *
     * @else
     * @brief Constructor
     *
     * Constructor
     *
     * @param name Port name
     * @param inport InPort object that is associated with this data input port.
     *               Specify also the data type and the buffer type used in 
     *               the InPort object.
     * @param prop Property for setting ports
     *
     * @endif
     */
    InPortBase(const char* name, const char* data_type);
    
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
    virtual ~InPortBase(void);
    
    coil::Properties& properties();

    void init();

    /*!
     * @if jp
     *
     * @brief InPortを activates する
     *
     * InPortを activate する。
     *
     * @else
     *
     * @brief Activate all Port interfaces
     *
     * This operation activate all interfaces that is registered in the
     * ports.
     *
     * @endif
     */
    virtual void activateInterfaces();

    /*!
     * @if jp
     *
     * @brief 全ての Port のインターフェースを deactivates する
     *
     * Port に登録されている全てのインターフェースを deactivate する。
     *
     * @else
     *
     * @brief Deactivate all Port interfaces
     *
     * This operation deactivate all interfaces that is registered in the
     * ports.
     *
     * @endif
     */
    virtual void deactivateInterfaces();

    /*!
     * @if jp
     * @brief ConnectorDataListener リスナを追加する
     *
     * バッファ書き込みまたは読み出しイベントに関連する各種リスナを設定する。
     *
     * 設定できるリスナのタイプとコールバックイベントは以下の通り
     *
     * - ON_BUFFER_WRITE:          バッファ書き込み時
     * - ON_BUFFER_FULL:           バッファフル時
     * - ON_BUFFER_WRITE_TIMEOUT:  バッファ書き込みタイムアウト時
     * - ON_BUFFER_OVERWRITE:      バッファ上書き時
     * - ON_BUFFER_READ:           バッファ読み出し時
     * - ON_SEND:                  InProtへの送信時
     * - ON_RECEIVED:              InProtへの送信完了時
     * - ON_SEND_ERTIMEOUT:        OutPort側タイムアウト時
     * - ON_SEND_ERERROR:          OutPort側エラー時
     * - ON_RECEIVER_FULL:         InProt側バッファフル時
     * - ON_RECEIVER_TIMEOUT:      InProt側バッファタイムアウト時
     * - ON_RECEIVER_ERROR:        InProt側エラー時
     *
     * リスナは ConnectorDataListener を継承し、以下のシグニチャを持つ
     * operator() を実装している必要がある。
     *
     * ConnectorDataListener::
     *         operator()(const ConnectorProfile&, const cdrStream&)
     *
     * デフォルトでは、この関数に与えたリスナオブジェクトの所有権は
     * OutPortに移り、OutPort解体時もしくは、
     * removeConnectorDataListener() により削除時に自動的に解体される。
     * リスナオブジェクトの所有権を呼び出し側で維持したい場合は、第3引
     * 数に false を指定し、自動的な解体を抑制することができる。
     *
     * @param listener_type リスナタイプ
     * @param listener リスナオブジェクトへのポインタ
     * @param autoclean リスナオブジェクトの自動的解体を行うかどうかのフラグ
     *
     * @else
     * @brief Adding BufferDataListener type listener
     *
     * This operation adds certain listeners related to buffer writing and
     * reading events.
     * The following listener types are available.
     *
     * - ON_BUFFER_WRITE:          At the time of buffer write
     * - ON_BUFFER_FULL:           At the time of buffer full
     * - ON_BUFFER_WRITE_TIMEOUT:  At the time of buffer write timeout
     * - ON_BUFFER_OVERWRITE:      At the time of buffer overwrite
     * - ON_BUFFER_READ:           At the time of buffer read
     * - ON_SEND:                  At the time of sending to InPort
     * - ON_RECEIVED:              At the time of finishing sending to InPort
     * - ON_SENDER_TIMEOUT:        At the time of timeout of OutPort
     * - ON_SENDER_ERROR:          At the time of error of OutPort
     * - ON_RECEIVER_FULL:         At the time of bufferfull of InPort
     * - ON_RECEIVER_TIMEOUT:      At the time of timeout of InPort
     * - ON_RECEIVER_ERROR:        At the time of error of InPort
     *
     * Listeners should have the following function operator().
     *
     * ConnectorDataListener::
     *         operator()(const ConnectorProfile&, const cdrStream&)
     *
     * The ownership of the given listener object is transferred to
     * this OutPort object in default.  The given listener object will
     * be destroied automatically in the OutPort's dtor or if the
     * listener is deleted by removeConnectorDataListener() function.
     * If you want to keep ownership of the listener object, give
     * "false" value to 3rd argument to inhibit automatic destruction.
     *
     * @param listener_type A listener type
     * @param listener A pointer to a listener object
     * @param autoclean A flag for automatic listener destruction
     *
     * @endif
     */
    void addConnectorDataListener(ConnectorDataListenerType listener_type,
                                  ConnectorDataListener* listener,
                                  bool autoclean = true);


    /*!
     * @if jp
     * @brief ConnectorDataListener リスナを削除する
     *
     * 設定した各種リスナを削除する。
     * 
     * @param listener_type リスナタイプ
     * @param listener リスナオブジェクトへのポインタ
     *
     * @else
     * @brief Removing BufferDataListener type listener
     *
     * This operation removes a specified listener.
     *     
     * @param listener_type A listener type
     * @param listener A pointer to a listener object
     *
     * @endif
     */
    void removeConnectorDataListener(ConnectorDataListenerType listener_type,
                                     ConnectorDataListener* listener);
    

    /*!
     * @if jp
     * @brief ConnectorListener リスナを追加する
     *
     * バッファ書き込みまたは読み出しイベントに関連する各種リスナを設定する。
     *
     * 設定できるリスナのタイプは
     *
     * - ON_BUFFER_EMPTY:       バッファが空の場合
     * - ON_BUFFER_READTIMEOUT: バッファが空でタイムアウトした場合
     *
     * リスナは以下のシグニチャを持つ operator() を実装している必要がある。
     *
     * ConnectorListener::operator()(const ConnectorProfile&)
     *
     * デフォルトでは、この関数に与えたリスナオブジェクトの所有権は
     * OutPortに移り、OutPort解体時もしくは、
     * removeConnectorListener() により削除時に自動的に解体される。
     * リスナオブジェクトの所有権を呼び出し側で維持したい場合は、第3引
     * 数に false を指定し、自動的な解体を抑制することができる。
     *
     * @param listener_type リスナタイプ
     * @param listener リスナオブジェクトへのポインタ
     * @param autoclean リスナオブジェクトの自動的解体を行うかどうかのフラグ
     *
     * @else
     * @brief Adding ConnectorListener type listener
     *
     * This operation adds certain listeners related to buffer writing and
     * reading events.
     * The following listener types are available.
     *
     * - ON_BUFFER_EMPTY:       At the time of buffer empty
     * - ON_BUFFER_READTIMEOUT: At the time of buffer read timeout
     *
     * Listeners should have the following function operator().
     *
     * ConnectorListener::operator()(const ConnectorProfile&)
     *  
     * The ownership of the given listener object is transferred to
     * this OutPort object in default.  The given listener object will
     * be destroied automatically in the OutPort's dtor or if the
     * listener is deleted by removeConnectorListener() function.
     * If you want to keep ownership of the listener object, give
     * "false" value to 3rd argument to inhibit automatic destruction.
     *
     * @param listener_type A listener type
     * @param listener A pointer to a listener object
     * @param autoclean A flag for automatic listener destruction
     *
     * @endif
     */
    void addConnectorListener(ConnectorListenerType callback_type,
                              ConnectorListener* listener,
                              bool autoclean = true);

    /*!
     * @if jp
     * @brief ConnectorDataListener リスナを削除する
     *
     * 設定した各種リスナを削除する。
     * 
     * @param listener_type リスナタイプ
     * @param listener リスナオブジェクトへのポインタ
     *
     * @else
     * @brief Removing BufferDataListener type listener
     *
     * This operation removes a specified listener.
     *     
     * @param listener_type A listener type
     * @param listener A pointer to a listener object
     *
     * @endif
     */
    void removeConnectorListener(ConnectorListenerType callback_type,
                                 ConnectorListener* listener);

    /*!
     * @if jp
     * @brief endian 設定を返す
     *
     * endian 設定のbool値を返す。
     *
     * @return m_littleEndian がlittleの場合true、bigの場合false を返す。
     *
     * @else
     * @brief
     *
     * return it whether endian setting.
     *
     *@return Return true in the case of "little", false in "big" than it.
     *
     * @endif
     */
    bool isLittleEndian();

    /*!
     * @if jp
     *
     * @brief [CORBA interface] Port の接続を行う
     *
     * 与えられた ConnectoionProfile の情報に基づき、Port間の接続を確立
     * する。この関数は主にアプリケーションプログラムやツールから呼び出
     * すことを前提としている。
     * 
     * @param connector_profile ConnectorProfile
     * @return ReturnCode_t 型のリターンコード
     *
     * @else
     *
     * @brief [CORBA interface] Connect the Port
     *
     * This operation establishes connection according to the given
     * ConnectionProfile inforamtion. This function is premised on
     * calling from mainly application program or tools.
     *
     * @param connector_profile The ConnectorProfile.
     * @return ReturnCode_t The return code of ReturnCode_t type.
     *
     * @endif
     */
    virtual ReturnCode_t
    connect(ConnectorProfile& connector_profile)
      throw (CORBA::SystemException);

  protected:

    /*!
     * @if jp
     * @brief Interface情報を公開する
     *
     * Interface情報を公開する。
     * 引数の ConnectorProfile に格納されている dataflow_type が push 型
     * の場合は、指定された interface_type の InPortProvider に関する情報
     * を ConnectorProfile::properties に書込み呼び出し側に戻す。
     *
     *  dataport.dataflow_type
     *
     * @param connector_profile コネクタプロファイル
     *
     * @return ReturnCode_t 型のリターンコード
     *
     * @else
     * @brief Publish interface information
     *
     * Publish interface information.
     * Assign the Provider information that owned by this port
     * to ConnectorProfile#properties
     *
     * @param connector_profile The connector profile
     *
     * @return The return code of ReturnCode_t type
     *
     * @endif
     */
    virtual ReturnCode_t
    publishInterfaces(ConnectorProfile& connector_profile);
    
    /*!
     * @if jp
     * @brief Interfaceに接続する
     *
     * Interfaceに接続する。
     * Portが所有するConsumerに適合するProviderに関する情報を 
     * ConnectorProfile#properties から抽出し、
     * ConsumerにCORBAオブジェクト参照を設定する。
     *
     * @param connector_profile コネクタ・プロファイル
     *
     * @return ReturnCode_t 型のリターンコード
     *
     * @else
     * @brief Subscribe to the interface
     *
     * Subscribe to interface.
     * Derive Provider information that matches Consumer owned by the Port 
     * from ConnectorProfile#properties and 
     * set the Consumer to the reference of the CORBA object.
     *
     * @param connector_profile The connector profile
     *
     * @return ReturnCode_t The return code of ReturnCode_t type
     *
     * @endif
     */
    virtual ReturnCode_t
    subscribeInterfaces(const ConnectorProfile& connector_profile);
    
    /*!
     * @if jp
     * @brief Interfaceへの接続を解除する
     *
     * Interfaceへの接続を解除する。
     * 与えられたConnectorProfileに関連するConsumerに設定された全てのObjectを
     * 解放し接続を解除する。
     *
     * @param connector_profile コネクタ・プロファイル
     *
     * @else
     * @brief Disconnect the interface connection
     *
     * Disconnect the interface connection.
     * Release all objects set in Consumer associated with 
     * given ConnectorProfile and unscribe the interface.
     *
     * @param connector_profile The connector profile
     *
     * @endif
     */
    virtual void
    unsubscribeInterfaces(const ConnectorProfile& connector_profile);


    /*!
     * @if jp
     * @brief InPort provider の初期化
     * @else
     * @brief InPort provider initialization
     * @endif
     */
    void initProviders();

    /*!
     * @if jp
     * @brief OutPort consumer の初期化
     * @else
     * @brief OutPort consumer initialization
     * @endif
     */
    void initConsumers();

    /*!
     * @if jp
     * @brief InPort provider の生成
     *
     * InPortProvider を生成し、情報を ConnectorProfile に公開する。
     * 生成に失敗した場合 0 を返す。
     *
     * @else
     * @brief InPort provider creation
     * @endif
     */
    InPortProvider*
    createProvider(ConnectorProfile& cprof, coil::Properties& prop);

    /*!
     * @if jp
     * @brief OutPort consumer の生成
     *
     * OutPortConsumer を生成する。
     * 生成に失敗した場合 0 を返す。
     *
     * @else
     * @brief InPort provider creation
     * @endif
     */
    OutPortConsumer*
    createConsumer(const ConnectorProfile& cprof, coil::Properties& prop);

    /*!
     * @if jp
     * @brief InPortPushConnector の生成
     *
     * Connector を生成し、生成が成功すれば m_connectors に保存する。
     * 生成に失敗した場合 0 を返す。
     *
     * @else
     * @brief InPortPushConnector creation
     * @endif
     */
    InPortConnector*
    createConnector(ConnectorProfile& cprof, coil::Properties& prop,
                    InPortProvider* provider);
    /*!
     * @if jp
     * @brief InPortPullConnector の生成
     *
     * Connector を生成し、生成が成功すれば m_connectors に保存する。
     * 生成に失敗した場合 0 を返す。
     *
     * @else
     * @brief InPortPullConnector creation
     * @endif
     */
    InPortConnector*
    createConnector(const ConnectorProfile& cprof, coil::Properties& prop,
                    OutPortConsumer* consumer);

  protected:
    bool m_singlebuffer;
    CdrBufferBase* m_thebuffer;
    coil::Properties m_properties;
    coil::vstring m_providerTypes;
    coil::vstring m_consumerTypes;
    ConnectorList m_connectors;
    bool m_littleEndian;

    ConnectorListeners m_listeners;
  };
}; // namespace RTC

#endif // RTC_INPORTBASE_H
