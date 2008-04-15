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
 * $Id: CorbaPort.h,v 1.1.4.1 2007-12-31 03:08:02 n-ando Exp $
 *
 */

#ifndef CorbaPort_h
#define CorbaPort_h

#include <rtm/PortBase.h>
#include <rtm/CorbaConsumer.h>
#include <rtm/NVUtil.h>

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
   * CorbaPort は RT コンポーネントにおいて、ユーザ定義の CORBA オブジェクト
   * サービスおよびコンシューマを提供する Port 実装である。
   * <p>
   * RT コンポーネントは、Port を介してユーザが定義した CORBA サービスを提供
   * することができ、これを RT Service (Provider) と呼ぶ。
   * また、他の RT コンポーネントのサービスを利用するための CORBA オブジェクト
   * のプレースホルダを提供することができ、これを RT Service Consumer と呼ぶ。
   * <p>
   * CorbaPort は任意の数の Provider および Consumer を管理することができ、
   * Port 同士を接続する際に対応する Provider と Consumer を適切に関連付ける
   * ことができる。
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
   * このように、提供したい Service Provider を registerProvider() で登録
   * することにより、他のコンポーネントから利用可能にし、他方、
   * 利用したい Service Consumer を registerConsumer() で登録することにより
   * 他のコンポーネントの Service をコンポーネント内で利用可能にすることが
   * できる。
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
    virtual ~CorbaPort();
    
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
    
  private:
    /*!
     * @if jp
     * @brief Provider の情報を格納する NVList
     * @else
     * @brief NVList to be stored Providers' information
     * @endif
     */
    NVList m_providers;
    
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
     * @brief ConnectorProfile と Consuemr の比較をしオブジェクト参照を
     *        セットするための Functor
     * @else
     * @brief Functor to compare ConnectorProfile and Consuemr, to set object 
     *        reference
     * @endif
     */
    struct subscribe
    {
      subscribe(std::vector<Consumer>& cons)
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
		CORBA::Object_ptr obj;
		if (nv.value >>= CORBA::Any::to_object(obj))
		  {
		    m_cons[i].consumer.setObject(obj);
		  }
	      }
	  }
      }
      std::vector<Consumer> m_cons;
      CORBA::ULong m_len;
    };
    
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
#endif // CorbaPort_h
