// -*- C++ -*-
/*!
 * @file PortBase.h
 * @brief RTC's Port base class
 * @date $Date: 2008-01-14 07:56:44 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006-2008
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

#ifndef PortBase_h
#define PortBase_h

#include <rtm/RTC.h>

#include <string>
#include <vector>
#include <coil/Guard.h>
#include <coil/Mutex.h>
#include <rtm/idl/RTCSkel.h>
#include <rtm/CORBA_SeqUtil.h>
#include <rtm/NVUtil.h>

#include <iostream>
namespace RTC
{
  /*!
   * @if jp
   * @class PortBase
   * @brief Port の基底クラス
   *
   * RTC::Port の基底となるクラス。
   * RTC::Port はほぼ UML Port の概念を継承しており、ほぼ同等のものとみなす
   * ことができる。RT コンポーネントのコンセプトにおいては、
   * Port はコンポーネントに付属し、コンポーネントが他のコンポーネントと相互作用
   * を行う接点であり、通常幾つかのインターフェースと関連付けられる。
   * コンポーネントは Port を通して外部に対しインターフェースを提供または要求
   * することができ、Portはその接続を管理する役割を担う。
   * <p>
   * Port の具象クラスは、通常 RT コンポーネントインスタンス生成時に同時に
   * 生成され、提供・要求インターフェースを登録した後、RT コンポーネントに
   * 登録され、外部からアクセス可能な Port として機能することを想定している。
   * <p>
   * RTC::Port は CORBA インターフェースとして以下のオペレーションを提供する。
   *
   * - get_port_profile()
   * - get_connector_profiles()
   * - get_connector_profile()
   * - connect()
   * - notify_connect()
   * - disconnect()
   * - notify_disconnect()
   * - disconnect_all()
   *
   * このクラスでは、これらのオペレーションの実装を提供する。
   * <p>
   * これらのオペレーションのうち、get_port_profile(), get_connector_profiles(),
   * get_connector_profile(), connect(), disconnect(), disconnect_all() は、
   * サブクラスにおいて特に振る舞いを変更する必要がないため、オーバーライド
   * することは推奨されない。
   * <p>
   * notify_connect(), notify_disconnect() については、サブクラスが提供・要求
   * するインターフェースの種類に応じて、振る舞いを変更する必要が生ずる
   * かもしれないが、これらを直接オーバーライドすることは推奨されず、
   * 後述の notify_connect(), notify_disconnect() の項においても述べられる通り
   * これらの関数に関連した protected 関数をオーバーライドすることにより
   * 振る舞いを変更することが推奨される。
   *
   * @since 0.4.0
   *
   * @else
   * @class PortBase
   * @brief Port base class
   *
   * This class is a base class of RTC::Port.
   * RTC::Port inherits a concept of RT-Component, and can be regarded as almost
   * the same as it. In the concept of RT-Component, Port is attached to the
   * component, can mediate interaction between other components and usually is
   * associated with some interfaces.
   * Component can provide or require interface for outside via Port, and the
   * Port plays a role to manage the connection.
   * <p>
   * Concrete class of Port assumes to be usually created at the same time that
   * RT-Component's instance is created, be registerd to RT-Component after
   * provided and required interfaces are registerd, and function as accessible
   * Port from outside.
   * <p>
   * RTC::Port provides the following operations as CORBA interface:
   *
   * - get_port_profile()
   * - get_connector_profiles()
   * - get_connector_profile()
   * - connect()
   * - notify_connect()
   * - disconnect()
   * - notify_disconnect()
   * - disconnect_all()
   *
   * This class provides implementations of these operations.
   * <p>
   * In these operations, as for get_port_profile(), get_connector_profiles(),
   * get_connector_profile(), connect(), disconnect() and disconnect_all(),
   * since their behaviors especially need not to be change in subclass, 
   * overriding is not recommended.
   * <p>
   * As for notify_connect() and notify_disconnect(), you may have to modify
   * behavior according to the kind of interfaces that subclass provides and
   * requires, however it is not recommended these are overriden directly.
   * In the section of notify_connect() and notify_disconnect() as described
   * below, it is recommended that you modify behavior by overriding the
   * protected function related to these functions.
   *
   * @since 0.4.0
   *
   * @endif
   */  
  class PortBase
    : public virtual POA_RTC::PortService,
      public virtual PortableServer::RefCountServantBase
  {
  public:
    /*!
     * @if jp
     * @brief コンストラクタ
     *
     * PortBase のコンストラクタは Port 名 name を引数に取り初期化を行う
     * と同時に、自分自身を CORBA Object として活性化し、自身の PortProfile
     * の port_ref に自身のオブジェクトリファレンスを格納する。
     *
     * @param name Port の名前(デフォルト値:"")
     *
     * @else
     *
     * @brief Constructor
     *
     * The constructor of the ProtBase class is given the name of this Port
     * and initialized. At the same time, the PortBase activates itself
     * as CORBA object and stores its object reference to the PortProfile's 
     * port_ref member.
     *
     * @param name The name of Port (The default value:"")
     *
     * @endif
     */
    PortBase(const char* name = "");
    
    /*!
     * @if jp
     *
     * @brief デストラクタ
     *
     * デストラクタ
     *
     * @else
     *
     * @brief Destructor
     *
     * Destructor
     *
     * @endif
     */
    virtual ~PortBase();
    
    /*!
     * @if jp
     *
     * @brief [CORBA interface] PortProfileを取得する
     *
     * Portが保持するPortProfileを返す。
     * PortProfile 構造体は以下のメンバーを持つ。
     *
     * - name              [string 型] Port の名前。
     * - interfaces        [PortInterfaceProfileList 型] Port が保持する
     *                     PortInterfaceProfile のシーケンス
     * - port_ref          [Port Object 型] Port 自身のオブジェクトリファレンス
     * - connector_profile [ConnectorProfileList 型] Port が現在保持する
     *                     ConnectorProfile のシーケンス
     * - owner             [RTObject Object 型] この Port を所有する
     *                     RTObjectのリファレンス
     * - properties        [NVList 型] その他のプロパティ。
     *
     * @return PortProfile
     *
     * @else
     *
     * @brief [CORBA interface] Get the PortProfile of the Port
     *
     * This operation returns the PortProfile of the Port.
     * PortProfile struct has the following members:
     *
     * - name              [string type] The name of the Port.
     * - interfaces        [PortInterfaceProfileList type] The sequence of 
     *                     PortInterfaceProfile owned by the Port
     * - port_ref          [Port Object type] The object reference of the Port.
     * - connector_profile [ConnectorProfileList type] The sequence of 
     *                     ConnectorProfile owned by the Port.
     * - owner             [RTObject Object type] The object reference of 
     *                     RTObject that is owner of the Port.
     * - properties        [NVList type] The other properties.
     *
     * @return PortProfile of the Port
     *
     * @endif
     */
    virtual PortProfile* get_port_profile()
      throw (CORBA::SystemException);
    
    /*!
     * @if jp
     *
     * @brief PortProfile を取得する。
     *
     * 本ポートの PortProfile を取得する。
     *
     * @return PortProfile
     *
     * @else
     *
     * @brief Get the PortProfile of the Port
     *
     * Get the PortProfile of this Port.
     *
     * @return PortProfile
     *
     * @endif
     */
    const PortProfile& getPortProfile() const;
    
    /*!
     * @if jp
     *
     * @brief [CORBA interface] ConnectorProfileListを取得する
     *
     * Portが保持する ConnectorProfile の sequence を返す。
     * ConnectorProfile は Port 間の接続プロファイル情報を保持する構造体であり、
     * 接続時にPort間で情報交換を行い、関連するすべての Port で同一の値が
     * 保持される。
     * ConnectorProfile は以下のメンバーを保持している。
     *
     * - name         [string 型] このコネクタの名前。
     * - connector_id [string 型] ユニークなID
     * - ports        [Port sequnce] このコネクタに関連する Port のオブジェクト
     *                リファレンスのシーケンス。
     * - properties   [NVList 型] その他のプロパティ。
     *
     * @return この Port が保持する ConnectorProfile
     *
     * @else
     *
     * @brief [CORBA interface] Get the ConnectorProfileList of the Port
     *
     * This operation returns a list of the ConnectorProfiles of the Port.
     * ConnectorProfile includes the connection information that describes 
     * relation between (among) Ports, and Ports exchange the ConnectionProfile
     * on connection process and hold the same information in every Port.
     * ConnectionProfile has the following members:
     *
     * - name         [string type] The name of the connection.
     * - connector_id [string type] Unique identifier.
     * - ports        [Port sequnce] The sequence of Port's object reference
     *                that are related the connection.
     * - properties   [NVList type] The other properties.
     *
     * @return ConnectorProfileList of the Port
     *
     * @endif
     */
    virtual ConnectorProfileList* get_connector_profiles()
      throw (CORBA::SystemException);
    
    /*!
     * @if jp
     *
     * @brief [CORBA interface] ConnectorProfile を取得する
     *
     * connector_id で指定された ConnectorProfile を返す。
     * 指定した connector_id を持つ ConnectorProfile を保持していない場合は、
     * 空の ConnectorProfile を返す。
     *
     * @param connector_id ConnectorProfile の ID
     *
     * @return connector_id で指定された ConnectorProfile
     *
     * @else
     *
     * @brief [CORBA interface] Get the ConnectorProfile
     *
     * This operation returns the ConnectorProfiles specified connector_id.
     * If ConnectorProfile with specified connector_id is not included,
     * empty ConnectorProfile is returned.
     *
     * @param connector_id ID of the ConnectorProfile
     *
     * @return the ConnectorProfile identified by the connector_id
     *
     * @endif
     */
    virtual ConnectorProfile* get_connector_profile(const char* connector_id)
      throw (CORBA::SystemException);
    
    /*!
     * @if jp
     *
     * @brief [CORBA interface] Port の接続を行う
     *
     * 与えられた ConnectoionProfile の情報を基に、Port間の接続を確立する。
     * アプリケーションプログラム側は、幾つかのコンポーネントが持つ複数の
     * Port を接続したい場合、適切な値をセットした ConnectorProfile を
     * connect() の引数として与えてコールすることにより、関連する Port の
     * 接続を確立する。
     *
     * connect() に与える ConnectorProfile のメンバーのうち、name, ports, 
     * properties メンバーに対してデータをセットしなければならない。
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
     *
     * 3. PortBase::connect() をコール
     *    Portの接続の基本処理が行われる。
     *
     * 4. 上記2.でInPortのリファレンスが取得できなければ、再度InPortに
     *    関連する connector 情報を取得する。
     *
     * 5. ConnectorProfile::properties で与えられた情報から、
     *    OutPort側の初期化処理を行う。
     *
     * - [dataport.interface_type]<BR>
     * -- CORBA_Any の場合: 
     *    InPortAny を通してデータ交換される。
     *    ConnectorProfile::properties["dataport.corba_any.inport_ref"]に
     *    InPortAny のオブジェクトリファレンスをセットする。<BR>
     * -- RawTCP の場合: Raw TCP socket を通してデータ交換される。
     *    ConnectorProfile::properties["dataport.raw_tcp.server_addr"]
     *    にInPort側のサーバアドレスをセットする。
     *
     * - [dataport.dataflow_type]<BR>
     * -- Pushの場合: Subscriberを生成する。Subscriberのタイプは、
     *    dataport.subscription_type に設定されている。<BR>
     * -- Pullの場合: InPort側がデータをPull型で取得するため、
     *    特に何もする必要が無い。
     *
     * - [dataport.subscription_type]<BR>
     * -- Onceの場合: SubscriberOnceを生成する。<BR>
     * -- Newの場合: SubscriberNewを生成する。<BR>
     * -- Periodicの場合: SubscriberPeriodicを生成する。
     *
     * - [dataport.push_interval]<BR>
     * -- dataport.subscription_type=Periodicの場合周期を設定する。
     *
     * 6. 上記の処理のうち一つでもエラーであれば、エラーリターンする。
     *    正常に処理が行われた場合は RTC::RTC_OK でリターンする。
     *  
     * @param connector_profile ConnectorProfile
     *
     * @return ReturnCode_t 型のリターンコード
     *
     * @else
     *
     * @brief [CORBA interface] Connect the Port
     *
     * This operation establishes connection according to the given 
     * ConnectionProfile inforamtion. 
     * Application programs, which is going to establish the connection 
     * among Ports owned by RT-Components, have to set valid values to the 
     * ConnectorProfile and give it to the argument of connect() operation.
     * 
     * name, ports and properties which are members of ConnectorProfile,
     * should be set valid values before giving to the argument of connect()
     * operation.
     *
     * The following sequences are executed in connect() of OutPort side.
     *
     * 1. Create and set connector information associated with OutPort.
     *
     * 2. Get connector information associated with InPort.
     *  - If the object reference of OutPortAny is set in 
     *    ConnectorProfile::properties["dataport.corba_any.inport_ref"],
     *    get its reference and set to Consumer object.
     *    If the object reference of OutPortAny is not set, 
     *    it ignores and continues.
     *    (If OutPort is an entry point of connect call, the object reference
     *    of InPort sure not to be set.)
     *
     * 3. Invoke PortBase::connect().
     *    Execute the basic processing of Port's connection.
     *
     * 4. If the reference of InPort cannot be got (by step2), get connector
     *    information associated with InPort again.
     *
     * 5. Initialize on OutPort side from information given by
     *    ConnectorProfile::properties.
     *
     * - [dataport.interface_type]<BR>
     * -- For CORBA_Any: 
     *    Exchange data via InPortAny.
     *    Set the object reference of InPortAny to
     *    ConnectorProfile::properties["dataport.corba_any.inport_ref"].
     * -- For RawTCP:
     *    Exechange data via Raw TCP socket.
     *    Set server address of InPort to
     *    ConnectorProfile::properties["dataport.raw_tcp.server_addr"].
     *
     * - [dataport.dataflow_type]<BR>
     * -- For Push: Create Subscriber. Type of Subscriber is set to
     *    dataport.subscription_type.<BR>
     * -- For Pull: Operate nothing since InPort side gets data in Pull type.
     *
     * - [dataport.subscription_type]<BR>
     * -- For Once: Create SubscriberOnce.<BR>
     * -- For New: Create SubscriberNew.<BR>
     * -- For Periodic: Create SubscriberPeriodic.
     *
     * - [dataport.push_interval]<BR>
     * -- For dataport.subscription_type=Periodic, the cycle is set.
     *
     * 6. If error occurs in one of the above processings, return error.
     *    If processing has completed successfully, return RTC::RTC_OK.
     *  
     * @param connector_profile The ConnectorProfile.
     *
     * @return ReturnCode_t The return code of ReturnCode_t type.
     *
     * @endif
     */
    virtual ReturnCode_t connect(ConnectorProfile& connector_profile)
      throw (CORBA::SystemException);
    
    /*!
     * @if jp
     *
     * @brief [CORBA interface] Port の接続通知を行う
     *
     * このオペレーションは、Port間の接続が行われる際に、Port間で内部的に
     * 呼ばれるオペレーションである。
     * ConnectorProfile には接続対象 Port のリスト情報が保持されている。Port は
     * ConnectorProfile を保持するとともに、リスト中の次 Port の notify_connect 
     * を呼び出す。そして、ポートをコネクタに追加した後、ConnectorProfile に
     * 呼びだし先の Port を設定し、呼びだし元に返す。このように ConnectorProfile
     * を使用して接続通知が伝達されていく。
     *
     * @param connector_profile ConnectorProfile
     *
     * @return ReturnCode_t 型のリターンコード
     *
     * @else
     *
     * @brief [CORBA interface] Notify the Ports connection
     *
     * This operation is invoked between Ports internally when the connection
     * is established.
     * A ConnectorProfile has a sequence of port references. This Port 
     * stores the ConnectorProfile and invokes the notify_connect operation of 
     * the next Port in the sequence. As ports are added to the connector, 
     * Port references are added to the ConnectorProfile and provided to 
     * the caller. In this way, notification of connection is propagated with
     * the ConnectorProfile.
     *
     * @param connector_profile The ConnectorProfile.
     *
     * @return ReturnCode_t The return code of ReturnCode_t type.
     *
     * @endif
     */
    virtual ReturnCode_t notify_connect(ConnectorProfile& connector_profile)
      throw (CORBA::SystemException);
    
    /*!
     * @if jp
     *
     * @brief [CORBA interface] Port の接続を解除する
     *
     * このオペレーションは接続確立時に接続に対して与えられる connector_id に
     * 対応するピア Port との接続を解除する。
     * Port は ConnectorProfile 中のポートリストに含まれる１つのポートの
     * notify_disconnect を呼びだす。接続解除の通知は notify_disconnect によって
     * 実行される。
     *
     * @param connector_id ConnectorProfile の ID
     *
     * @return ReturnCode_t 型のリターンコード
     *
     * @else
     *
     * @brief [CORBA interface] Disconnect the Port
     *
     * This operation destroys connection between this port and the peer port
     * according to given connector_id when the connection established.
     * This port invokes the notify_disconnect of one of the ports included
     * a port list in ConnectorProfile stored when the connection was
     * established. The notification of disconnection is executed by
     * the notify_disconnect.
     *
     * @param connector_id The ID of the ConnectorProfile.
     *
     * @return ReturnCode_t The return code of ReturnCode_t type.
     *
     * @endif
     */
    virtual ReturnCode_t disconnect(const char* connector_id)
      throw (CORBA::SystemException);
    
    /*!
     * @if jp
     *
     * @brief [CORBA interface] Port の接続解除通知を行う
     *
     * このオペレーションは、Port間の接続解除が行われる際に、Port間で内部的に
     * 呼ばれるオペレーションである。
     * このオペレーションは、該当する Port と接続されている他の Port に接続解除
     * を通知する。接続解除対象の Port はIDによって指定される。Port は
     * ConnectorProfile 中のポートリスト内の次 Port の notify_disconnect を呼び
     * 出す。ポートの接続が解除されると ConnectorProfile から該当する Port の
     * 情報が削除される。このように notify_disconnect を使用して接続解除通知が
     * 伝達されていく。
     *
     * @param connector_id ConnectorProfile の ID
     *
     * @return ReturnCode_t 型のリターンコード
     *
     * @else
     *
     * @brief [CORBA interface] Notify the Ports disconnection
     *
     * This operation is invoked between Ports internally when the connection
     * is destroied.
     * This operation notifies a disconnection between corresponding port and
     * the other ports. The disconnected Port is identified by the given ID.
     * This port invokes the notify_disconnect operation of the next Port
     * in the sequence of the ConnectorProfile that was stored when the 
     * connection was established. As ports are disconnected, corresponding port
     * information are removed from the ConnectorProfile. In this way, the
     * notification of disconnection is propagated by the notify_disconnect
     * operation.
     *
     * @param connector_id The ID of the ConnectorProfile.
     *
     * @return ReturnCode_t The return code of ReturnCode_t type.
     *
     * @endif
     */
    virtual ReturnCode_t notify_disconnect(const char* connector_id)
      throw (CORBA::SystemException);
    
    /*!
     * @if jp
     *
     * @brief [CORBA interface] Port の全接続を解除する
     *
     * このオペレーションはこの Port に関連した全ての接続を解除する。
     *
     * @return ReturnCode_t 型のリターンコード
     *
     * @else
     *
     * @brief [CORBA interface] Disconnect the All Ports
     *
     * This operation destroys all connections associated with this Port.
     *
     * @return ReturnCode_t The return code of ReturnCode_t type.
     *
     * @endif
     */
    virtual ReturnCode_t disconnect_all()
      throw (CORBA::SystemException);
    
    //============================================================
    // Local operations
    //============================================================
    /*!
     * @if jp
     * @brief Port の名前を設定する
     *
     * Port の名前を設定する。この名前は Port が保持する PortProfile.name
     * に反映される。
     *
     * @param name Port の名前
     *
     * @else
     * @brief Set the name of this Port
     *
     * This operation sets the name of this Port. The given Port's name is
     * applied to Port's PortProfile.name.
     *
     * @param name The name of this Port.
     *
     * @endif
     */
    void setName(const char* name);
    
    /*!
     * @if jp
     * @brief PortProfileを取得する
     *
     * Portが保持する PortProfile の const 参照を返す。
     *
     * @return この Port の PortProfile
     *
     * @else
     * @brief Get the PortProfile of the Port
     *
     * This operation returns const reference of the PortProfile.
     *
     * @return PortProfile of the Port
     *
     * @endif
     */
    const PortProfile& getProfile() const;
    
    /*!
     * @if jp
     *
     * @brief Port のオブジェクト参照を設定する
     *
     * このオペレーションは Port の PortProfile にこの Port 自身の
     * オブジェクト参照を設定する。
     *
     * @param port_ref この Port のオブジェクト参照
     *
     * @else
     *
     * @brief Set the object reference of this Port
     *
     * This operation sets the object reference itself
     * to the Port's PortProfile.
     *
     * @param port_ref The object reference of this Port.
     *
     * @endif
     */
    void setPortRef(PortService_ptr port_ref);
    
    /*!
     * @if jp
     *
     * @brief Port のオブジェクト参照を取得する
     *
     * このオペレーションは Port の PortProfile が保持している
     * この Port 自身のオブジェクト参照を取得する。
     *
     * @return この Port のオブジェクト参照
     *
     * @else
     *
     * @brief Get the object reference of this Port
     *
     * This operation returns the object reference
     * that is stored in the Port's PortProfile.
     *
     * @return The object reference of this Port.
     *
     * @endif
     */
    PortService_ptr getPortRef();
    
    /*!
     * @if jp
     *
     * @brief Port の owner の RTObject を指定する
     *
     * このオペレーションは Port の PortProfile.owner を設定する。
     *
     * @param owner この Port を所有する RTObject の参照
     *
     * @else
     *
     * @brief Set the owner RTObject of the Port
     *
     * This operation sets the owner RTObject of this Port.
     *
     * @param owner The owner RTObject's reference of this Port
     *
     * @endif
     */
    void setOwner(RTObject_ptr owner);
    
    //============================================================
    // protected operations
    //============================================================
  protected:
    /*! @if jp
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
     * 具象 Port ではこのオペレーションをオーバーライドし、引数として
     * 与えられた ConnectorProfile に従い処理を行い、パラメータが不適切
     * であれば、RteurnCode_t 型のエラーコードを返す。
     * 通常 publishInterafaces() 内においては、この Port に属する
     * インターフェースに関する情報を ConnectorProfile に対して適切に設定し
     * 他の Port に通知しなければならない。
     * <br>
     * また、この関数がコールされる段階では、他の Port の Interface に関する
     * 情報はすべて含まれていないので、他の Port の Interface を取得する処理
     * は subscribeInterfaces() 内で行われるべきである。
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
     * In the concrete Port, this method should be overridden. This method
     * processes the given ConnectorProfile argument and if the given parameter
     * is invalid, it would return error code of ReturnCode_t.
     * Usually, publishInterfaces() method should set interfaces information
     * owned by this Port, and publish it to the other Ports.
     * <br>
     * When this method is called, other Ports' interfaces information may not
     * be completed. Therefore, the process to obtain other Port's interfaces
     * information should be done in the subscribeInterfaces() method.
     * <br>
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
    publishInterfaces(ConnectorProfile& connector_profile) = 0;
    
    /*!
     * @if jp
     *
     * @brief 次の Port に対して notify_connect() をコールする
     *
     * ConnectorProfile の port_ref 内に格納されている Port のオブジェクト
     * リファレンスのシーケンスの中から、自身の Port の次の Port に対して
     * notify_connect() をコールする。
     *
     * @param connector_profile 接続に関するプロファイル情報
     *
     * @return ReturnCode_t 型のリターンコード
     *
     * @else
     *
     * @brief Call notify_connect() of the next Port
     *
     * This operation calls the notify_connect() of the next Port's 
     * that stored in ConnectorProfile's port_ref sequence.
     *
     * @param connector_profile The connection profile information
     *
     * @return The return code of ReturnCode_t type.
     *
     * @endif
     */
    virtual ReturnCode_t connectNext(ConnectorProfile& connector_profile);
    
    /*!
     * @if jp
     *
     * @brief 次の Port に対して notify_disconnect() をコールする
     *
     * ConnectorProfile の port_ref 内に格納されている Port のオブジェクト
     * リファレンスのシーケンスの中から、自身の Port の次の Port に対して
     * notify_disconnect() をコールする。
     *
     * @param connector_profile 接続に関するプロファイル情報
     *
     * @return ReturnCode_t 型のリターンコード
     *
     * @else
     *
     * @brief Call notify_disconnect() of the next Port
     *
     * This operation calls the notify_disconnect() of the next Port's 
     * that stored in ConnectorProfile's port_ref sequence.
     *
     * @param connector_profile The connection profile information
     *
     * @return The return code of ReturnCode_t type.
     *
     * @endif
     */
    virtual ReturnCode_t disconnectNext(ConnectorProfile& connector_profile);
    
    /*! @if jp
     *
     * @brief Interface 情報を公開する
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
     * <br>
     * 具象 Port ではこのオペレーションをオーバーライドし、引数として
     * 与えられた ConnectorProfile に従い処理を行い、パラメータが不適切
     * であれば、RteurnCode_t 型のエラーコードを返す。
     * 引数 ConnectorProfile には他の Port の Interface に関する情報が
     * 全て含まれている。
     * 通常 subscribeInterafaces() 内においては、この Port が使用する
     * Interface に関する情報を取得し、要求側のインターフェースに対して
     * 情報を設定しなければならない。
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
     * mid-flow of the notify_connect() process sequence.
     * In the notify_connect(), the following methods would be called in order.
     *
     * - publishInterfaces()
     * - connectNext()
     * - subscribeInterfaces()
     * - updateConnectorProfile()
     *
     * In the concrete Port, this method should be overridden. This method
     * processes the given ConnectorProfile argument and if the given parameter
     * is invalid, it would return error code of ReturnCode_t.
     * The given argument ConnectorProfile includes all the interfaces
     * information in it.
     * Usually, subscribeInterafaces() method obtains information of interfaces
     * from ConnectorProfile, and should set it to the interfaces that require
     * them.
     * <br>
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
    subscribeInterfaces(const ConnectorProfile& connector_profile) = 0;
    
    /*! @if jp
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
     * <br>
     * 具象 Port ではこのオペレーションをオーバーライドし、引数として
     * 与えられた ConnectorProfile に従い接続解除処理を行う。
     *
     * @param connector_profile 接続に関するプロファイル情報
     *
     * @else
     *
     * @brief Disconnect interface connection
     *
     * This operation is pure virutal function that would be called at the
     * end of the notify_disconnect() process sequence.
     * In the notify_disconnect(), the following methods would be called
     * in order to disconnect.
     * - disconnectNext()
     * - unsubscribeInterfaces()
     * - eraseConnectorProfile() 
     *  <br>
     * In the concrete Port, this method should be overridden. This method
     * processes the given ConnectorProfile argument and disconnect interface
     * connection.
     *
     * @param connector_profile The connection profile information
     *
     * @endif
     */
    virtual void
    unsubscribeInterfaces(const ConnectorProfile& connector_profile) = 0;
    
    //============================================================
    // protected utility functions
    //============================================================
    /*!
     * @if jp
     *
     * @brief ConnectorProfile の connector_id フィールドが空かどうか判定
     *
     * 指定された ConnectorProfile の connector_id が空であるかどうかの判定を
     * 行う。
     *
     * @param connector_profile 判定対象コネクタプロファイル
     *
     * @return 引数で与えられた ConnectorProfile の connector_id が空であれば、
     *         true、そうでなければ false を返す。
     *
     * @else
     *
     * @brief Check whether connector_id of ConnectorProfile is empty
     *
     * Check whether connector_id of specified ConnectorProfile is empty.
     * 
     * @param connector_profile Target ConnectorProfile for the check
     *
     * @return If the given ConnectorProfile's connector_id is empty string,
     *         it returns true.
     *
     * @endif
     */
    bool isEmptyId(const ConnectorProfile& connector_profile) const;
    
    /*!
     * @if jp
     *
     * @brief UUIDを生成する
     *
     * このオペレーションは UUID を生成する。
     *
     * @return uuid
     *
     * @else
     *
     * @brief Generate the UUID
     *
     * This operation generates UUID.
     *
     * @return uuid
     *
     * @endif
     */
    const std::string getUUID() const;
    
    /*!
     * @if jp
     *
     * @brief UUIDを生成し ConnectorProfile にセットする
     *
     * このオペレーションは UUID を生成し、ConnectorProfile にセットする。
     *
     * @param connector_profile connector_id をセットする ConnectorProfile
     *
     * @else
     *
     * @brief Generate and set the UUID to the ConnectorProfile
     *
     * This operation generates and set UUID to the ConnectorProfile.
     *
     * @param connector_profile ConnectorProfile to be set connector_id
     *
     * @endif
     */
    void setUUID(ConnectorProfile& connector_profile) const;
    
    /*!
     * @if jp
     *
     * @brief id が既存の ConnectorProfile のものかどうか判定する
     *
     * このオペレーションは与えられた ID が既存の ConnectorProfile のリスト中に
     * 存在するかどうか判定する。
     *
     * @param id 判定する connector_id
     *
     * @return id の存在判定結果
     *
     * @else
     *
     * @brief Check whether the given id exists in stored ConnectorProfiles
     *
     * This operation returns boolean whether the given id exists in 
     * the Port's ConnectorProfiles.
     *
     * @param id connector_id to be find in Port's ConnectorProfiles
     *
     * @return id exestance resutl
     *
     * @endif
     */
    bool isExistingConnId(const char* id);
    
    /*!
     * @if jp
     *
     * @brief id を持つ ConnectorProfile を探す
     *
     * このオペレーションは与えられた ID を持つ ConnectorProfile を Port が
     * もつ ConnectorProfile のリスト中から探す。
     * もし、同一の id を持つ ConnectorProfile がなければ、空の ConnectorProfile
     * が返される。
     *
     * @param id 検索する connector_id
     *
     * @return connector_id を持つ ConnectorProfile
     *
     * @else
     *
     * @brief Find ConnectorProfile with id
     *
     * This operation returns ConnectorProfile with the given id from Port's
     * ConnectorProfiles' list.
     * If the ConnectorProfile with connector id that is identical with the
     * given id does not exist, empty ConnectorProfile is returned.
     *
     * @param id the connector_id to be searched in Port's ConnectorProfiles
     *
     * @return CoonectorProfile with connector_id
     *
     * @endif
     */
    ConnectorProfile findConnProfile(const char* id);
    
    /*!
     * @if jp
     *
     * @brief id を持つ ConnectorProfile を探す
     *
     * このオペレーションは与えられた ID を持つ ConnectorProfile を Port が
     * もつ ConnectorProfile のリスト中から探しインデックスを返す。
     * もし、同一の id を持つ ConnectorProfile がなければ、-1 を返す。
     *
     * @param id 検索する connector_id
     *
     * @return Port の ConnectorProfile リストのインデックス
     *
     * @else
     *
     * @brief Find ConnectorProfile with id
     *
     * This operation returns ConnectorProfile with the given id from Port's
     * ConnectorProfiles' list.
     * If the ConnectorProfile with connector id that is identical with the
     * given id does not exist, -1 is returned.
     *
     * @param id the connector_id to be searched
     *
     * @return The index of ConnectorProfile of the Port
     *
     * @endif
     */
    CORBA::Long findConnProfileIndex(const char* id);
    
    /*!
     * @if jp
     *
     * @brief ConnectorProfile の追加もしくは更新
     *
     * このオペレーションは与えられた ConnectorProfile を Port に追加もしくは
     * 更新保存する。
     * 与えられた ConnectorProfile の connector_id と同じ ID を持つ
     * ConnectorProfile がリストになければ、リストに追加し、
     * 同じ ID が存在すれば ConnectorProfile を上書き保存する。
     *
     * @param connector_profile 追加もしくは更新する ConnectorProfile
     *
     * @else
     *
     * @brief Append or update the ConnectorProfile list
     *
     * This operation appends or updates ConnectorProfile of the Port
     * by the given ConnectorProfile.
     * If the connector_id of the given ConnectorProfile does not exist
     * in the Port's ConnectorProfile list, the given ConnectorProfile would be
     * append to the list. If the same id exists, the list would be updated.
     *
     * @param connector_profile the ConnectorProfile to be appended or updated
     *
     * @endif
     */
    void updateConnectorProfile(const ConnectorProfile& connector_profile);
    
    /*!
     * @if jp
     *
     * @brief ConnectorProfile を削除する
     *
     * このオペレーションは Port の PortProfile が保持している
     * ConnectorProfileList のうち与えられた id を持つ ConnectorProfile
     * を削除する。
     *
     * @param id 削除する ConnectorProfile の id
     *
     * @return 正常に削除できた場合は true、
     *         指定した ConnectorProfile が見つからない場合は false を返す
     *
     * @else
     *
     * @brief Delete the ConnectorProfile
     *
     * This operation deletes a ConnectorProfile specified by id from
     * ConnectorProfileList owned by PortProfile of this Port.
     *
     * @param id The id of the ConnectorProfile to be deleted.
     *
     * @return true would be returned if it deleted correctly.
     *         false woluld be returned if specified ConnectorProfile
     *         cannot be found.
     *
     * @endif
     */
    bool eraseConnectorProfile(const char* id);
    
    /*!
     * @if jp
     *
     * @brief PortInterfaceProfile に インターフェースを登録する
     *
     * このオペレーションは Port が持つ PortProfile の、PortInterfaceProfile
     * にインターフェースの情報を追加する。
     * この情報は、get_port_profile() によって得られる PortProfile のうち
     * PortInterfaceProfile の値を変更するのみであり、実際にインターフェースを
     * 提供したり要求したりする場合には、サブクラスで、 publishInterface() ,
     *  subscribeInterface() 等の関数を適切にオーバーライドしインターフェースの
     * 提供、要求処理を行わなければならない。
     *
     * インターフェース(のインスタンス)名は Port 内で一意でなければならない。
     * 同名のインターフェースがすでに登録されている場合、この関数は false を
     * 返す。
     *
     * @param name インターフェースのインスタンスの名前
     * @param type_name インターフェースの型の名前
     * @param pol インターフェースの属性 (RTC::PROVIDED もしくは RTC:REQUIRED)
     *
     * @return インターフェース登録処理結果。
     *         同名のインターフェースが既に登録されていれば false を返す。
     *
     * @else
     *
     * @brief Append an interface to the PortInterfaceProfile
     *
     * This operation appends interface information to the PortInterfaceProfile
     * that is owned by the Port.
     * The given interfaces information only updates PortInterfaceProfile of
     * PortProfile that is obtained through get_port_profile().
     * In order to provide and require interfaces, proper functions (for
     * example publishInterface(), subscribeInterface() and so on) should be
     * overridden in subclasses, and these functions provide concrete interface
     * connection and disconnection functionality.
     *
     * The interface (instance) name have to be unique in the Port.
     * If the given interface name is identical with stored interface name,
     * this function returns false.
     *
     * @param name The instance name of the interface.
     * @param type_name The type name of the interface.
     * @param pol The interface's polarity (RTC::PROVIDED or RTC:REQUIRED)
     *
     * @return false would be returned if the same name is already registered.
     *
     * @endif
     */
    bool appendInterface(const char* name, const char* type_name,
			 PortInterfacePolarity pol);
    
    /*!
     * @if jp
     *
     * @brief PortInterfaceProfile からインターフェース登録を削除する
     *
     * このオペレーションは Port が持つ PortProfile の、PortInterfaceProfile
     * からインターフェースの情報を削除する。
     *
     * @param name インターフェースのインスタンスの名前
     * @param pol インターフェースの属性 (RTC::PROVIDED もしくは RTC:REQUIRED)
     *
     * @return インターフェース削除処理結果。
     *         インターフェースが登録されていなければ false を返す。
     *
     * @else
     *
     * @brief Delete the interface registration from the PortInterfaceProfile
     *
     * This operation deletes interface information from the
     * PortInterfaceProfile that is owned by the Port.
     *
     * @param name The instance name of the interface.
     * @param pol The interface's polarity (RTC::PROVIDED or RTC:REQUIRED)
     *
     * @return Delete processing result of interface.
     *         false would be returned if the given name is not registered.
     *
     * @endif
     */
    bool deleteInterface(const char* name, PortInterfacePolarity pol);
    
    /*!
     * @if jp
     *
     * @brief PortProfile の properties に NameValue 値を追加する
     *
     * PortProfile の properties に NameValue 値を追加する。
     * 追加するデータの型をValueTypeで指定する。
     *
     * @param key properties の name
     * @param value properties の value
     *
     * @else
     *
     * @brief Add NameValue data to PortProfile's properties
     *
     * Add NameValue data to PortProfile's properties.
     * Type of additional data is specified by ValueType.
     *
     * @param key The name of properties
     * @param value The value of properties
     *
     * @endif
     */
    template <class ValueType>
    void addProperty(const char* key, ValueType value)
    {
      CORBA_SeqUtil::push_back(m_profile.properties,
			       NVUtil::newNV(key, value));
    }
    
  protected:
    /*!
     * @if jp
     * @brief Port の PortProfile
     * @else
     * @brief PortProfile of the Port
     * @endif
     */
    PortProfile m_profile;
    
    /*!
     * @if jp
     * @brief Port の オブジェクト参照
     * @else
     * @brief Object Reference of the Port
     * @endif
     */
    RTC::PortService_var m_objref;
    mutable coil::Mutex m_profile_mutex;
    typedef coil::Guard<coil::Mutex> Guard;
    
    //============================================================
    // Functor
    //============================================================
    /*!
     * @if jp
     * @brief instance_name を持つ PortInterfaceProfile を探す Functor
     * @else
     * @brief Functor to find a PortInterfaceProfile named instance_name
     * @endif
     */
    struct if_name
    {
      if_name(const char* name) : m_name(name) {};
      bool operator()(const PortInterfaceProfile& prof)
      {
	return m_name == std::string(prof.instance_name);
      }
      std::string m_name;
    };
    
    /*!
     * @if jp
     * @brief id を持つ ConnectorProfile を探す Functor
     * @else
     * @brief Functor to find a ConnectorProfile named id
     * @endif
     */
    struct find_conn_id
    {
      find_conn_id(const char* id) : m_id(id) {};
      bool operator()(const ConnectorProfile& cprof)
      {
	return m_id == std::string(cprof.connector_id);
      }
      std::string m_id;
    };
    
    /*!
     * @if jp
     * @brief コンストラクタ引数 port_ref と同じオブジェクト参照を探す Functor
     * @else
     * @brief Functor to find the object reference that is identical port_ref
     * @endif
     */
    struct find_port_ref
    {
      find_port_ref(PortService_ptr port_ref) : m_port(port_ref) {};
      bool operator()(PortService_ptr port_ref)
      {
	return m_port->_is_equivalent(port_ref);
      }
      PortService_ptr m_port;
    };
    
    /*!
     * @if jp
     * @brief Port の接続を行う Functor
     * @else
     * @brief Functor to connect Ports
     * @endif
     */
    struct connect_func
    {
      PortService_var port_ref;
      ConnectorProfile connector_profile;
      ReturnCode_t return_code;
      
      connect_func() {};
      connect_func(PortService_ptr p, ConnectorProfile& prof)
	: port_ref(p), connector_profile(prof), return_code(RTC::RTC_OK) {};
      void operator()(PortService_ptr p)
      {
	if (!port_ref->_is_equivalent(p))
	  {
	    ReturnCode_t retval;
	    retval = p->notify_connect(connector_profile);
	    if (retval != RTC::RTC_OK)
	      {
		return_code = retval;
	      }
	  }
      }
    };
    
    /*!
     * @if jp
     * @brief Port の接続解除を行う Functor
     * @else
     * @brief Functor to disconnect Ports
     * @endif
     */
    struct disconnect_func
    {
      PortService_var port_ref;
      ConnectorProfile connector_profile;
      ReturnCode_t return_code;
      
      disconnect_func() : return_code(RTC::RTC_OK) {};
      disconnect_func(PortService_ptr p, ConnectorProfile& prof)
	: port_ref(p), connector_profile(prof), return_code(RTC::RTC_OK) {};
      void operator()(PortService_ptr p)
      {
	if (!port_ref->_is_equivalent(p))
	  {
	    ReturnCode_t retval;
	    retval = p->disconnect(connector_profile.connector_id);
	    if (retval != RTC::RTC_OK)
	      {
		return_code = retval;
	      }
	  }
      }
    };
    
    /*!
     * @if jp
     * @brief Port の全接続解除を行う Functor
     * @else
     * @brief Functor to disconnect all Ports
     * @endif
     */
    struct disconnect_all_func
    {
      ReturnCode_t return_code;
      PortBase* port;
      
      disconnect_all_func() {};
      disconnect_all_func(PortBase* p) 
	: return_code(RTC::RTC_OK), port(p) {};
      void operator()(ConnectorProfile& p)
      {
	ReturnCode_t retval;
	retval = port->disconnect(p.connector_id);
	if (retval != RTC::RTC_OK)
	  {
	    return_code = retval;
	  }
      }
    };
    
    /*!
     * @if jp
     * @brief name と polarity から interface を探す Functor
     * @else
     * @brief Functor to find interface from name and polarity
     * @endif
     */
    struct find_interface
    {
      find_interface(const char* name, PortInterfacePolarity pol)
	: m_name(name), m_pol(pol)
      {}
      
      bool operator()(const PortInterfaceProfile& prof)
      {
	std::string name(CORBA::string_dup(prof.instance_name));
	return ((m_name == name) && (m_pol == prof.polarity));
      }
      std::string m_name;
      PortInterfacePolarity m_pol;
    };
  };
};
#endif // PortBase_h
