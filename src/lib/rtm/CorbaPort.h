// -*- C++ -*-
/*!
 * @file  CorbaPort.h
 * @brief CorbaPort class
 * @date  $Date: 2007-12-31 03:08:02 $
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

#ifndef RTC_CORBAPORT_H
#define RTC_CORBAPORT_H

#include <rtm/PortBase.h>
#include <rtm/CorbaConsumer.h>
#include <rtm/NVUtil.h>
#include <list>

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
  /*!
   * @if jp
   * @class CorbaPort
   * @brief RT コンポーネント CORBA provider/consumer 用 Port
   *
   * CorbaPort は RT コンポーネントにおいて、ユーザ定義の CORBA オブジェ
   * クトサービスおよびコンシューマを提供する Port 実装である。
   *
   * <p>
   * RT コンポーネントは、Port を介してユーザが定義した CORBA サービス
   * を提供することができ、これを RT Service (Provider) と呼ぶ。また、
   * 他の RT コンポーネントのサービスを利用するための CORBA オブジェク
   * トのプレースホルダを提供することができ、これを RT Service
   * Consumer と呼ぶ。
   * <p>
   * CorbaPort は任意の数の Provider および Consumer を管理することがで
   * き、Port 同士を接続する際に対応する Provider と Consumer を適切に
   * 関連付けることができる。
   * <p>
   * CorbaPort は通常以下のように利用される。
   *
   * <pre>
   * RTC::CorbaPort m_port0; // Port の宣言
   *
   * MyService_impl m_mysvc0; // この Port が提供する Serivce Provider
   * RTC::CorbaConsumer<YourService> m_cons0; // この Port の Consumer
   *
   * // Service Provider を Port に登録
   * m_port0.registerProvider("MyService0", "Generic", m_mysvc0);
   * // Service Consumer を Port に登録
   * m_port0.registerConsumer("YourService0", "Generic", m_cons0 );
   *
   * // connect が行われた後
   *
   * m_cons0->your_service_function(); // YourService の関数をコール
   *
   * // connect された 別のコンポーネントにおいて
   * m_cons1->my_service_function(); // MyService の関数をコール
   * </pre>
   *
   * このように、提供したい Service Provider を registerProvider() で登
   * 録することにより、他のコンポーネントから利用可能にし、他方、利用し
   * たい Service Consumer を registerConsumer() で登録することにより他
   * のコンポーネントの Service をコンポーネント内で利用可能にすること
   * ができる。
   *
   * PortInterfaceProfile は Port に所属するプロバイダもしくはコンシュー
   * マインターフェースについての情報を記述するためのプロファイルである。
   * 接続を行うツール等は、これらの情報に基づき ConnectorProfile を適切
   * に生成し、接続を構成する Port のうち任意の一つに対して引数に
   * ConnectorProfile を与えて Port::connect() を呼び出す必要がある。
   *
   * なお、PortInterfaceProfile のインスタンス名 "*" は特殊なインスタン
   * スを表す。
   *
   * PROVIDEDすなわちプロバイダのインスタンス名が "*" の場合は、接続開
   * 始時点ではインスタンスが存在せず、コンシューマの要求に応じて動的に
   * インスタンスを生成するタイプのプロバイダであることを表す。したがっ
   * て、接続開始時点ではインスタンス名は存在しないが、接続シーケンス中
   * のインターフェースを公開するプロセスにおいて、プロバイダは生成した
   * インスタンスに対応した記述子を COnnectorProfile に適正に設定するも
   * のとする。
   *
   * REQUIREDすなわちコンシューマのインスタンス名が "*" の場合は、一つ
   * のコンシューマが複数のプロバイダと接続可能なタイプのコンシューマで
   * あることを示す。(未実装)
   *
   * 以下は、Port間のインターフェースを接続するために ConnectorProfile に
   * マッピングを記述するためのルールを示す。
   *
   * Portに付属するインターフェースの指定子のフォーマットを以下のように
   * 定める。インターフェースに関するプロパティが以下の場合
   *
   * - RTCインスタンス名:              rtc_iname
   * - ポート名:                       port_name
   * - インターフェース極性:           if_polarity
   * - インターフェース型名:           if_tname
   * - インターフェースインスタンス名: if_iname
   * 
   * インターフェースの指定子を以下の文字列名称で指定するものとする。
   *
   * <rtc_iname>.port.<port_name>.<if_polarity>.<if_tname>.<if_iname>
   *
   * PROVIDED(提供)型すなわちプロバイダのインタフェースのプロパティが以
   * 下の場合、
   *
   * - rtc_iname   = MyComp0
   * - port_name   = myservice
   * - if_polarity = provided
   * - if_tname    = echo_interface
   * - if_iname    = echo_interface2
   *
   * インターフェース指定子は
   *
   * MyComp0.port.myservice.provided.echo_interface.echo_interface2
   *
   * のように記述される。また、同様にREQUIRED(要求)型すなわちコンシュー
   * マのインターフェースのプロパティが以下の場合、
   *
   * - rtc_iname   = YourComp0
   * - port_name   = yourservice
   * - if_polarity = required
   * - if_tname    = hoge_interface
   * - if_iname    = hoge_interface1
   *
   * インターフェース指定子は、
   * 
   * YourComp0.port.myservice.required.hoge_interface.hoge_inteface1
   *
   * のように記述することができる。
   * 
   * なお、ここで動的生成インターフェースのインスタンスのための特殊なタ
   * イプのインスタンス名記述子
   *
   * - <type_name>*: 動的生成型インスタンス名記述子
   * - <type_name>+: インクリメンタル生成型インスタンス名記述子
   *
   * を定義する。動的生成インターフェースとは、接続時にインスタンスが生
   * 成されるタイプのインターフェースである。(未実装)
   *
   * 動的生成型インスタンス名記述子 "<type_name>*" では、インターフェー
   * スのインスタンスは、コンシューマからの要求が1つ以上存在する場合、
   * インスタンスを1つ新規に生成して、各コンシューマに接続される。すな
   * わち、<type_name>* の記述子を持ってプロバイダを要求する n 個のコン
   * シューマが存在する場合、これらからの要求(オペレーションコール)を1
   * つのプロバイダにより処理する関係を構築する(下図)。
   *
   * consumer0 ]---<
   * consumer1 ]---<  O----[ provider0
   * consumer2 ]---<
   *  
   * これに対し、インクリメンタル生成型インスタンス名記述子
   * "<type_name>+" では、インターフェースのインスタンスは、コンシュー
   * マからの要求が n 個存在する場合、n 個のインスタンスを動的に生成し
   * て、各コンシューマに静つ属する。すなわち、<type_name>* の記述子を
   * 持ってプロバイダを要求する n 個のコンシューマが存在する場合、これ
   * らからの要求(オペレーションコール)を、対応するそれぞれのプロバイダ
   * により処理する関係を構築する(下図)。
   *
   * consumer0 ]---<  O----[ provider0
   * consumer1 ]---<  O----[ provider1
   * consumer2 ]---<  O----[ provider2
   *
   *
   * 接続に際して、ツール等から ConnectorProfile::properties に適切なイ
   * ンターフェースマッピング指定を記述することで、相互の提供/要求イン
   * ターフェースを自由に接続することができる。ただし、接続に関わるRTC
   * の中に、異なるインスタンスでありながら、同一のインスタンス名が存在
   * する場合、インターフェース記述子の一意性が保証できないので、この方
   * 法による接続性は保証されない。
   *
   * ここでインターフェース記述子を簡単のために <if_desc0>,
   * <if_desc1>, ...  とする。また、ConnectorProfile::properties の
   * NVListの key と value を key: value のように記述するものとする。
   *
   * いま、2つのコンポーネントのサービスポートを接続する場合を考える。
   * それぞれのコンポーネントのサービスポートが以下の場合、
   *
   * - rtc_iname: MyComp0
   *   port_name: mycomp_service
   *   interfaces:
   *   - if_polarity: provided
   *     if_iname: echo0
   *     if_tname: Echo
   *   - if_polarity: required
   *     if_iname: add0
   *     if_tname: add
   *
   * - rtc_iname: YourComp0
   *   port_name: yourcomp_service
   *   interfaces:
   *   - if_polarity: required
   *     if_iname: echo9
   *     if_tname: Echo
   *   - if_polarity: provided
   *     if_iname: add9
   *     if_tname: add
   *
   *      MyComp0                                 YourComp0
   *     _______ mycomp_service   yourcomp_service ______
   *            |                                 |
   *          |~~~|---O echo0         echo9 >---|~~~|
   *          |   |---< add0          add9  O---|   |
   *           ~T~                               ~T~
   *            |                                 |
   *
   * MyComp0 の echo0 (プロバイダ) と YourComp0 の echo9 (コンシューマ)、
   * MyComp0 の add0 (コンシューマ) と YourComp0 の echo9 (プロバイダ)
   * をそれぞれ対にして接続させるものと仮定する。この場合、
   * ConnectorProfile は以下のように設定する。
   * 
   * ConnectorProfile:
   *   name: 任意のコネクタ名
   *   connector_id: 空文字
   *   ports[]: mycomp_service の参照, yourcomp_service の参照
   *   properties:
   *     <add0>: <add9>
   *     <echo9>: <echo0>
   *
   * ただし、それぞれ
   * 
   * <add0> は MyComp0.port.mycomp_service.required.add.add0
   * <add9> は YourComp0.port.yourcomp_service.provided.add.add9
   * <echo0> は MyComp0.port.mycomp_service.provided.echo.echo0
   * <echo9> は YourComp0.port.yourcomp_service.required.echo.echo9
   *
   * である。接続プロセスにおいて、各ポートのプロバイダおよびコンシュー
   * マは、それぞれ以下の作業を、CorbaPort::publishInterfaces(),
   * Corba::PortsubscribeInterfaces() 仮想関数において行う。
   *
   * プロバイダは、publishInterfaces() 関数において、自分のインターフェー
   * ス記述子をキーとし、値にIORの文字列表記したものを
   * ConnectorProfile::properties に設定する。前提として、このインター
   * フェース記述子は今行おうとしているコネクタにおいては一意であるため、
   * 同じキーは1つしか存在してはいけない。
   *
   * [この部分の記述は未実装の機能] なお、動的生成インターフェースにつ
   * いては、以下の手続きに従い処理することとなる。publishInterface()
   * 関数において、動的生成インスタンス名記述子 "<type_name>*" または、
   * インクリメンタル生成型インスタンス名記述子 "<type_name>+" が存在す
   * るかどうかを走査する。動的生成インスタンス名記述子 "<type_name>*"
   * が存在する場合、プロバイダのインスタンスを1つ生成し、そのインター
   * フェース指定子を key に、IOR文字列を value に設定するとともに、動
   * 的生成インスタンス名記述子 "<type_name>*" を value に含むすべての
   * value 上のインターフェース指定子を、ここで生成したインターフェース
   * 指定子に置き換える。インクリメンタル生成型インスタンス名記述子
   * "<type_name>+" が存在する場合、インスタンス名記述子の数だけプロバ
   * イダのインスタンスを生成し、それぞれのインターフェース指定子を
   * key に、IOR文字列を value に設定するとともに、インクリメンタル生成
   * 型インスタンス名記述子 "<type_name>+" を value 含むすべての value
   * 上のインターフェース指定子に対して順に、ここで生成したそれぞれのイ
   * ンターフェース指定子に置き換える。
   *
   * プロバイダは subscribeInterfaces() では特に操作は行わない。
   *
   * コンシューマは、publishInterfaces() においては特に操作を行わない。
   *
   * 一方、subscribeInterfaces() では、自分の記述子を key とする
   * key-value ペア が存在するかどうか調べ、もし存在すれば、その value
   * に設定されたプロバイダのインターフェース指定子で指定される参照を、
   * さらに ConnectorProfile::properties から探し、それをコンシューマの
   * 接続先として設定する。なお、意図的にコンシューマにプロバイダの参照
   * を設定しない場合は、予約文字列 "nil" を設定するものとする。
   *
   * コンシューマは、もし自分の記述子が存在しない場合、またはプロバイダ
   * の参照が Connector::properties に存在しない場合、コンシューマは、
   * 自分のインスタンス名および型名と同一のプロバイダを探し、その参照を
   * 自分自身に設定する。これは、OpenRTM-aist-0.4 との互換性を保持する
   * ためのルールであり、1.0以降では推奨されない。
   *
   * プロバイダ対コンシューマの対応は一対一である必要はなく、プロバイダ
   * 1 に対して、コンシューマ n、またはコンシューマ 1 に対してプロバイ
   * ダ n のケースも許される。プロバイダ 1 に対して、コンシューマ n の
   * ケースでは、あるプロバイダの指定子が、複数のコンシューマに対して、
   * 上記の方法で指定されることにより、実現される。一方、コンシューマ
   * 1 に対してプロバイダ n のケースでは、コンシューマ指定子の key に対
   * して、複数のプロバイダの指定子がカンマ区切りで列挙される形式となる
   * ものとする。
   *
   * @since 0.4.0
   *
   * @else
   * @class CorbaPort
   * @brief RT Conponent CORBA service/consumer Port
   *
   * CorbaPort is an implementation of the Port of RT-Component's that provides
   * user-defined CORBA Object Service and Consumer.
   * <p>
   * RT-Component can provide user-defined CORBA serivces, which is called
   * RT-Serivce (Provider), through the Ports.
   * RT-Component can also provide place-holder, which is called RT-Serivce
   * Consumer, to use other RT-Component's service.
   * <p>
   * The CorbaPort can manage any number of Providers and Consumers, can
   * associate Consumers with correspondent Providers when establishing
   * connection among Ports.
   * <p>
   * Usually, CorbaPort is used like the following.
   *
   * <pre>
   * RTC::CorbaPort m_port0; // declaration of Port
   *
   * MyService_impl m_mysvc0; // Serivce Provider that is provided by the Port
   * RTC::CorbaConsumer<YourService> m_cons0; // Consumer of the Port
   *
   * // register Service Provider to the Port
   * m_port0.registerProvider("MyService0", "Generic", m_mysvc0);
   * // register Service Consumer to the Port
   * m_port0.registerConsumer("YourService0", "Generic", m_cons0 );
   *
   * // after connect established
   *
   * m_cons0->your_service_function(); // call a YourService's function
   *
   * // in another component that is connected with the Port
   * m_cons1->my_service_function(); // call a MyService's function
   * </pre>
   *
   * Registering Service Provider by registerProvider(), it can be used from
   * other RT-Components.
   * Registering Service Consumer by registerConsumer(), other RT-Component's
   * services can be used through the consumer object.
   *
   * @since 0.4.0
   *
   * @endif
   */
  class CorbaPort
    : public PortBase
  {
  public:
    /*!
     * @if jp
     * @brief コンストラクタ
     *
     * @param name Port の名前
     *
     * @else
     *
     * @brief Constructor
     *
     * @param name The name of Port 
     *
     * @endif
     */
    CorbaPort(const char* name);
    
    /*!
     * @if jp
     *
     * @brief 仮想デストラクタ
     *
     * @else
     *
     * @brief Virtual destructor
     *
     * @endif
     */
    virtual ~CorbaPort(void);
    
    /*!
     * @if jp
     *
     * @brief Provider を登録する
     *
     * この Port において提供したいサーバントをこの Port に対して登録する。
     * サーバントは、引数で与えられる instance_name, type_name を、
     * サーバント自身のインスタンス名およびタイプ名として、サーバントに
     * 関連付けられる。
     *
     * @param instance_name サーバントのインスタンス名
     * @param type_name サーバントのタイプ名
     * @param provider CORBA サーバント
     *
     * @return 既に同名の instance_name が登録されていれば false を返す。
     *
     * @else
     *
     * @brief Register the provider
     *
     * This operation registers a servant, which is provided in this Port,
     * to the Port. The servant is associated with "instance_name" and
     * "type_name" as the instance name of the servant and as the type name
     * of the servant.
     *
     * @param instance_name Instance name of servant
     * @param type_name Type name of the servant
     * @param provider CORBA servant
     *
     * @return Return false if the same name of instance_name is already 
     *         registered.
     *
     * @endif
     */
    bool registerProvider(const char* instance_name, const char* type_name,
                          PortableServer::RefCountServantBase& provider);
    
    /*!
     * @if jp
     *
     * @brief Consumer を登録する
     *
     * この Port が要求するサービスのプレースホルダであるコンシューマ
     * (Consumer) を登録する。
     * Consumer が関連付けられるサービスのインスタンス名およびタイプ名として、
     * 引数に instance_name, type_name および Consumer 自身を与えることにより、
     * 内部でこれらが関連付けられる。
     * Port 間の接続 (connect) 時 には、同一の instance_name, type_name を持つ
     * サービスが他の Port から提供 (Provide) されている場合、そのサービスの
     * オブジェクト参照が自動的に Consumer にセットされる。
     *
     * @param instance_name Consumer が要求するサービスのインスタンス名
     * @param type_name Consumer が要求するサービスのタイプ名
     * @param consumer CORBA サービスコンシューマ
     *
     * @return 既に同名の instance_name が登録されていれば false を返す。
     *
     * @else
     *
     * @brief Register the consumer
     *
     * This operation registers a consumer, which is a service placeholder
     * this port requires. These are associated internally by specified 
     * instance_name, type_name and Consumer itself to the argument as
     * service's instance name and its type name associated with Consumer.
     * If the service with the same instance_name and type_name is provided
     * by the other port when connecting between ports, its service object
     * reference will be set automatically.
     *
     * @param instance_name Instance name of the service Consumer requires
     * @param type_name Type name of the service Consumer requires
     * @param consumer CORBA service consumer
     *
     * @return False would be returned if the same instance_name was registered
     *
     * @endif
     */
    bool registerConsumer(const char* instance_name, const char* type_name,
                          CorbaConsumerBase& consumer);
    
  protected:
    /*!
     * @if jp
     *
     * @brief Interface 情報を公開する
     *
     * この Portが所有する Provider に関する情報を ConnectorProfile::properties
     * に代入する。
     * 代入する情報は、NVListの name と value として以下のものが格納される。
     *
     * - port.<type_name>.<instance_name>: <CORBA::Object_ptr>
     *
     * ここで、
     * - <type_name>: PortInterfaceProfile::type_name
     * - <instance_name>: PortInterfaceProfile::instance_name
     *
     * である。
     * ConnectorProfile::properties では、これらを .(ドット)表記で、
     * NameValue のキーとしている。したがって、
     *
     * <pre>
     *  PortInterfaceProfile
     *  {
     *    instance_name = "PA10_0";
     *    type_name     = "Manipulator";
     *    polarity      = PROVIDED;
     *  }
     *</pre>
     *
     * ならば、
     *
     * <pre>
     * NameValue = { "port.Manipulator.PA10_0": <Object reference> }
     * </pre>
     *
     * といった値が ConnectorProfile::properties に格納され、他のポートに対して
     * 伝達される。他の Port でこのインターフェースを使用する Consumer が
     * 存在すれば、ConnectorProfile からこのキーからオブジェクトリファレンスを
     * 取得し何らかの形で使用される。
     *
     * @param connector_profile コネクタプロファイル
     *
     * @return ReturnCode_t 型のリターンコード
     *
     * @else
     *
     * @brief Publish interface information
     *
     * Assign information associated with Provider owned by this Port
     * to ConnectorProfile::properties.
     * In assignment information, the following is stored as NVList name and 
     * its value.
     *
     * - port.<type_name>.<instance_name>: <CORBA::Object_ptr>
     *
     * Here,
     * - <type_name>: PortInterfaceProfile::type_name
     * - <instance_name>: PortInterfaceProfile::instance_name<br>
     * <br>
     * In ConnectorProfile::properties, these are keys of NameValue written 
     * with .(dot) notation. Therefore,
     *
     * <pre>
     *  PortInterfaceProfile
     *  {
     *    instance_name = "PA10_0";
     *    type_name     = "Manipulator";
     *    polarity      = PROVIDED;
     *  }
     *</pre>
     *
     * so,
     *
     * <pre>
     * NameValue = { "port.Manipulator.PA10_0": <Object reference> }
     * </pre>
     *
     * The above value is set to ConnectorProfile::properties and sent to other
     * ports. If Consumer that uses this interface in other Port exists,
     * the object references will be got and use from the key of 
     * ConnectorProfile.
     *
     * @param connector_profile Connector profile
     *
     * @return The return code of ReturnCode_t type
     *
     * @endif
     */
    virtual ReturnCode_t
    publishInterfaces(ConnectorProfile& connector_profile);
    
    /*!
     * @if jp
     *
     * @brief Interface に接続する
     *
     * この Portが所有する Consumer に適合する Provider に関する情報を
     * ConnectorProfile::properties から抽出し Consumer にオブジェクト参照
     * をセットする。
     *
     * 今、Consumer が
     * <pre>
     *  PortInterfaceProfile
     *  {
     *    instance_name = "PA10_0";
     *    type_name     = "Manipulator";
     *    polarity      = REQUIRED;
     *  }
     *</pre>
     * として登録されていれば、他の Port の
     * <pre>
     *  PortInterfaceProfile
     *  {
     *    instance_name = "PA10_0";
     *    type_name     = "Manipulator";
     *    polarity      = PROVIDED;
     *  }
     * </pre> 
     * として登録されている Serivce Provider のオブジェクト参照を探し、
     * Consumer にセットする。
     * 実際には、ConnectorProfile::properties に
     * <pre>
     * NameValue = { "port.Manipulator.PA10_0": <Object reference> }
     * </pre>
     * として登録されている NameValue を探し、そのオブジェクト参照を
     * Consumer にセットする。
     *
     * @param connector_profile コネクタプロファイル
     *
     * @return ReturnCode_t 型のリターンコード
     *
     * @else
     *
     * @brief Subscribe to interface
     *
     * Retrieve information associated with Provider matches Consumer
     * owned by this port and set the object reference to Consumer.
     *
     * Now, Consumer is registered as the following:
     * <pre>
     *  PortInterfaceProfile
     *  {
     *    instance_name = "PA10_0";
     *    type_name     = "Manipulator";
     *    polarity      = REQUIRED;
     *  }
     *</pre>
     * Find the object reference of Serivce Provider that is registered as
     * the following of other ports:
     * <pre>
     *  PortInterfaceProfile
     *  {
     *    instance_name = "PA10_0";
     *    type_name     = "Manipulator";
     *    polarity      = PROVIDED;
     *  }
     * </pre> 
     * and set to Consumer.
     * In fact, find NameValue that is registered as the following to 
     * ConnectorProfile::properties:
     * <pre>
     * NameValue = { "port.Manipulator.PA10_0": <Object reference> }
     * </pre>
     * and set the object reference to Consumer.
     *
     * @param connector_profile Connector profile
     *
     * @return The return code of ReturnCode_t type
     *
     * @endif
     */
    virtual ReturnCode_t
    subscribeInterfaces(const ConnectorProfile& connector_profile);
    
    /*!
     * @if jp
     *
     * @brief Interface への接続を解除する
     *
     * 与えられた ConnectorProfile に関連する Consumer にセットされた
     * すべての Object を解放し接続を解除する。
     *
     * @param connector_profile コネクタプロファイル
     *
     * @else
     *
     * @brief Unsubscribe interfaces
     *
     * Release all Objects that was set in Consumer associated with the given 
     * ConnectorProfile.
     *
     * @param connector_profile Connector profile
     *
     * @endif
     */
    virtual void
    unsubscribeInterfaces(const ConnectorProfile& connector_profile);

    //============================================================
    // Local operations
    //============================================================
    /*!
     * @if jp
     *
     * @brief Port の全てのインターフェースを activates する
     *
     * Port に登録されている全てのインターフェースを activate する。
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

  private:
    /*!
     * @if jp
     * @class CorbaProviderHolder
     * CORBA Provider のホルダクラス
     * @else
     * @class CorbaProviderHolder
     * CORBA Provider holder class
     * @endif
     */
    class CorbaProviderHolder
    {
    public:
      CorbaProviderHolder(const char* type_name,
                          const char* instance_name,
                          PortableServer::RefCountServantBase* servant)
        : m_typeName(type_name),
          m_instanceName(instance_name),
          m_servant(servant),
          m_ior()
      {  
        m_oid = Manager::instance().getPOA()->servant_to_id(m_servant);
        try
          {
            Manager::instance().
              getPOA()->activate_object_with_id(m_oid, m_servant);
          }
        catch(const ::PortableServer::POA::ServantAlreadyActive &)
          {
            ;
          }
        catch(const ::PortableServer::POA::ObjectAlreadyActive &)
          {
            ;
          }
        CORBA::Object_var obj;
        obj = Manager::instance().getPOA()->id_to_reference(m_oid);
        CORBA::ORB_ptr orb = Manager::instance().getORB();
        CORBA::String_var ior_var = orb->object_to_string(obj);
        m_ior = ior_var;
        deactivate();
      }

      std::string instanceName() { return m_instanceName; }
      std::string typeName() { return m_typeName; }
      std::string ior() { return m_ior; }
      std::string descriptor() { return m_typeName + "." + m_instanceName; }

      void activate()
      {
        try
          {
            Manager::instance().
              getPOA()->activate_object_with_id(m_oid, m_servant);
          }
        catch(const ::PortableServer::POA::ServantAlreadyActive &)
          {
            ; // do nothing
          }
        catch(const ::PortableServer::POA::ObjectAlreadyActive &)
          {
            ; // do nothing
          }
      }
      void deactivate()
      {
        try
          {
            Manager::instance().getPOA()->deactivate_object(m_oid);
          }
        catch(const ::PortableServer::POA::ObjectNotActive&)
          {
            ; // do nothing
          }
      }
    private:
      std::string m_typeName;
      std::string m_instanceName;
      PortableServer::RefCountServantBase* m_servant;
      PortableServer::ObjectId_var m_oid;
      std::string m_ior;
    };

    /*!
     * @if jp
     * @brief Provider の情報を格納する vector
     * @else
     * @brief vector to stored Providers' information
     * @endif
     */
    typedef std::vector<CorbaProvider> CorbaProviderList;
    CorbaProviderList m_providers;

    /*!
     * @if jp
     * @brief Consumer の情報を格納する構造体
     * @else
     * @brief The structure to be stored Consumer information.
     * @endif
     */
    struct Consumer
    {
      Consumer(const char* _instance_name, const char* _type_name,
               CorbaConsumerBase& _cons)
        : name(std::string("port.")
               + _type_name
               + std::string(".")
               + _instance_name),
          consumer(_cons)
      {}
      Consumer(const Consumer& cons)
        : name(cons.name), consumer(cons.consumer)
      {        
      }
      Consumer operator=(const Consumer& _cons)
      {
        Consumer cons(_cons);
        return cons;
      }
      std::string name;
      CorbaConsumerBase& consumer;
    };
    std::vector<Consumer> m_consumers;
    
    // functors
    /*!
     * @if jp
     * @brief Consumer のオブジェクトを解放するための Functor
     * @else
     * @brief Functor to release Consumer's object
     * @endif
     */
    struct unsubscribe
    {
      unsubscribe(std::vector<Consumer>& cons)
        : m_cons(cons), m_len(cons.size())
      {
      }
      
      void operator()(const SDOPackage::NameValue& nv)
      {
        for (CORBA::ULong i = 0; i < m_len; ++i)
          {
            std::string name(nv.name);
            if (m_cons[i].name == name)
              {
                m_cons[i].consumer.releaseObject();
              }
          }
      }
      std::vector<Consumer> m_cons;
      CORBA::ULong m_len;
    };
  };
};
#endif // RTC_CORBAPORT_H
