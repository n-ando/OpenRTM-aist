// -*- C++ -*-
/*!
 * @file RTObject.h
 * @brief RT component base class
 * @date $Date: 2007-01-09 15:21:47 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: RTObject.h,v 1.2 2007-01-09 15:21:47 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.1  2006/09/11 19:04:38  n-ando
 * The first commit.
 *
 *
 */

#ifndef RTObject_h
#define RTObject_h

// CORBA header include
#include "rtm/RTC.h"
#include "rtm/Properties.h"
#include "rtm/idl/RTCSkel.h"
#include "rtm/PortBase.h"
//#include "rtm/ObjectManager.h"
#include "rtm/PortAdmin.h"

// ACE
#include <ace/Task.h>


namespace SDOPackage
{
  class Configuration_impl;
};

namespace RTC
{
  class Manager;

  class RTObject_impl
    : public virtual POA_RTC::DataFlowComponent, 
      public virtual PortableServer::RefCountServantBase
  {
  public:
    RTObject_impl(Manager* manager);
    RTObject_impl(CORBA::ORB_ptr orb, PortableServer::POA_ptr poa);
    virtual ~RTObject_impl();



    //============================================================
    // RTC::LightweightRTObject
    //============================================================
    /*!
     * @if jp
     *
     * @breif RTCを初期化する
     *
     * このオペレーション呼び出しの結果として、ComponentAction::on_initialize
     * コールバック関数が呼ばれる。
     * 制約
     * Created状態にいるときにのみ、初期化が行われる。他の状態にいる場合には
     * ReturnCode_t::PRECONDITION_NOT_MET が返され呼び出しは失敗する。
     * このオペレーションはRTCのミドルウエアから呼ばれることを想定しており、
     * アプリケーション開発者は直接このオペレーションを呼ぶことは想定
     * されていない。
     * 
     * @else
     *
     * @breif Initialize the RTC that realizes this interface.
     *
     * The invocation of this operation shall result in the invocation of the
     * callback ComponentAction::on_initialize.
     *
     * Constraints
     * - An RTC may be initialized only while it is in the Created state. Any
     *   attempt to invoke this operation while in another state shall fail
     *   with ReturnCode_t::PRECONDITION_NOT_MET.
     * - Application developers are not expected to call this operation
     *   directly; it exists for use by the RTC infrastructure.
     *
     * @endif
     */
    virtual ReturnCode_t initialize();


    /*!
     * @if jp
     *
     * @brief 
     *
     * @else
     *
     * @brief Finalize the RTC for preparing it for destruction
     * 
     * This invocation of this operation shall result in the invocation of the
     * callback ComponentAction::on_finalize.
     *
     * Constraints
     * - An RTC may not be finalized while it is Active in any Running
     *   execution context. Any attempt to invoke this operation at such a time
     *   shall fail with ReturnCode_t::PRECONDITION_NOT_MET.
     * - An RTC may not be finalized while it is in the Created state.
     *   Any attempt to invoke this operation while in that state shall fail
     *   with ReturnCode_t::PRECONDITION_NOT_MET.
     * - Application developers are not expected to call this operation
     *   directly; it exists for use by the RTC infrastructure.
     *
     * @endif
     */
    virtual ReturnCode_t finalize();


    /*!
     * @if jp
     *
     * @brief
     *
     * @else
     *
     * @brief Stop the RTC's and finalize it along with its contents.
     * 
     * Any execution contexts for which the RTC is the owner shall be stopped. 
     * If the RTC participates in any execution contexts belonging to another
     * RTC that contains it, directly or indirectly (i.e. the containing RTC
     * is the owner of the ExecutionContext), it shall be deactivated in those
     * contexts.
     * After the RTC is no longer Active in any Running execution context, it
     * and any RTCs contained transitively within it shall be finalized.
     *
     * Constraints
     * - An RTC cannot be exited if it has not yet been initialized. Any
     *   attempt to exit an RTC that is in the Created state shall fail with
     *   ReturnCode_t::PRECONDITION_NOT_MET.
     *
     * @endif
     */
    virtual ReturnCode_t exit(); 

    /*!
     * @if jp
     *
     * @brief
     *
     * @else
     *
     * @brief
     *
     * A component is alive or not regardless of the execution context from
     * which it is observed. However, whether or not it is Active, Inactive,
     * or in Error is dependent on the execution context(s) in which it is
     * running. That is, it may be Active in one context but Inactive in
     * another. Therefore, this operation shall report whether this RTC is
     * either Active, Inactive or in Error; which of those states a component
     * is in with respect to a particular context may be queried from the
     * context itself.
     *
     * @endif
     */
    virtual CORBA::Boolean is_alive();


    /*!
     * @if jp
     * @brief [CORBA interface] ExecutionContextListを取得する
     * @else
     * @brief [CORBA interface] Get ExecutionContextList.
     * @endif
     */
    virtual ExecutionContextList* get_contexts();

    virtual UniqueId 
    set_execution_context_service(const ExecutionContextService_ptr ec);

    //============================================================
    // RTC::RTObject
    //============================================================
    /*!
     * @if jp
     *
     * @brief [RTObject CORBA interface] コンポーネントプロファイルの取得
     *
     * 当該コンポーネントのプロファイル情報を返す。 
     *
     * @else
     *
     * @brief [RTObject CORBA interface] Get RTC's profile
     *
     * This operation returns the ComponentProfile of the RTC
     *
     * @endif
     */
    virtual ComponentProfile* get_component_profile();


    /*!
     * @if jp
     *
     * @brief [RTObject CORBA interface] ポートの取得
     *
     * 当該コンポーネントが保有するポートの参照を返す。
     *
     * @else
     *
     * @brief [RTObject CORBA interface] Get Ports
     *
     * This operation returns a list of the RTCs ports.
     *
     * @endif
     */
    virtual PortList* get_ports();


    /*!
     * @if jp
     *
     * @brief [RTObject CORBA interface] ExecutionContextAdmin の取得
     *
     * このオペレーションは当該　RTC が所属する ExecutionContextに関連した
     * ExecutionContextAdmin のリストを返す。
     *
     * @else
     *
     * @brief [RTObject CORBA interface] Get ExecutionContextAdmin
     *
     * This operation returns a list containing an ExecutionContextAdmin for
     * every ExecutionContext owned by the RTC.	
     *
     * @endif
     */
    virtual ExecutionContextServiceList* get_execution_context_services();



    // RTC::ComponentAction
    virtual ReturnCode_t on_initialize();
    virtual ReturnCode_t on_finalize();
    virtual ReturnCode_t on_startup(UniqueId ec_id);
    virtual ReturnCode_t on_shutdown(UniqueId ec_id);
    virtual ReturnCode_t on_activated(UniqueId ec_id);
    virtual ReturnCode_t on_deactivated(UniqueId ec_id);
    virtual ReturnCode_t on_aborting(UniqueId ec_id);
    virtual ReturnCode_t on_error(UniqueId ec_id);
    virtual ReturnCode_t on_reset(UniqueId ec_id);

    virtual ReturnCode_t on_execute(UniqueId ec_id);
    virtual ReturnCode_t on_state_update(UniqueId ec_id);
    virtual ReturnCode_t on_rate_changed(UniqueId ec_id);



    //============================================================
    // SDOPackage::SdoSystemElement
    //============================================================
    /*!
     * @if jp
     * 
     * @brief [CORBA interface] Organization リストの取得 
     *
     * SDOSystemElement は0個もしくはそれ以上の Organization を所有することが
     * 出来る。 SDOSystemElement が1つ以上の Organization を所有している場合
     * には、このオペレーションは所有する Organization のリストを返す。
     * もしOrganizationを一つも所有していないければ空のリストを返す。
     *
     * @else
     *
     * @brief [CORBA interface] Getting Organizations
     *
     * SDOSystemElement can be the owner of zero or more organizations.
     * If the SDOSystemElement owns one or more Organizations, this operation
     * returns the list of Organizations that the SDOSystemElement owns.
     * If it does not own any Organization, it returns empty list.
     *
     * @endif
     */
    virtual SDOPackage::OrganizationList* get_owned_organizations()
      throw (SDOPackage::NotAvailable);


    //============================================================
    // SDOPackage::SDO
    //============================================================
    /*!
     * @if jp
     * 
     * @brief [CORBA interface] SDO ID の取得
     *
     * SDO ID を返すオペレーション。
     * このオペレーションは以下の型の例外を発生させる。
     * 
     * @exception SDONotExists ターゲットのSDOが存在しない。
     * @exception NotAvailable SDOは存在するが応答がない。
     * @exception InternalError 内部的エラーが発生した。
     * @return    リソースデータモデルで定義されている SDO の ID
     *
     * @else
     *
     * @brief [CORBA interface] Getting SDO ID
     *
     * This operation returns id of the SDO.
     * This operation throws SDOException with one of the following types.
     *
     * @exception SDONotExists if the target SDO does not exist.
     * @exception NotAvailable if the target SDO is reachable but cannot
     *                         respond.
     * @exception InternalError if the target SDO cannot execute the operation
     *                          completely due to some internal error.
     * @return    id of the SDO defined in the resource data model.
     *
     * @endif
     */
    virtual char* get_sdo_id()
      throw (SDOPackage::NotAvailable, SDOPackage::InternalError);
    
    /*!
     * @if jp
     * 
     * @brief [CORBA interface] SDO タイプの取得
     * 
     * SDO Type を返すオペレーション。
     * このオペレーションは以下の型の例外を発生させる。
     *
     * @exception SDONotExists ターゲットのSDOが存在しない。
     * @exception NotAvailable SDOは存在するが応答がない。
     * @exception InternalError 内部的エラーが発生した。
     * @return    リソースデータモデルで定義されている SDO の Type
     *
     * @else
     *
     * @brief [CORBA interface] Getting SDO type
     *
     * This operation returns sdoType of the SDO.
     * This operation throws SDOException with one of the following types.
     *
     * @exception SDONotExists if the target SDO does not exist.
     * @exception NotAvailable if the target SDO is reachable but cannot
     *                         respond.
     * @exception InternalError if the target SDO cannot execute the operation
     *                          completely due to some internal error.
     * @return    Type of the SDO defined in the resource data model.
     *
     * @endif
     */
    virtual char* get_sdo_type()
      throw (SDOPackage::NotAvailable, SDOPackage::InternalError);

    /*!
     * @if jp
     * 
     * @brief [CORBA interface] SDO DeviceProfile リストの取得 
     *
     * SDO の DeviceProfile を返すオペレーション。 SDO がハードウエアデバイス
     * に関連付けられていない場合には、空の DeviceProfile が返される。
     * このオペレーションは以下の型の例外を発生させる。
     *
     * @exception NotAvailable SDOは存在するが応答がない。
     * @exception InternalError 内部的エラーが発生した。
     * @return    SDO DeviceProfile
     *
     * @else
     *
     * @brief [CORBA interface] Getting SDO DeviceProfile
     *
     * This operation returns the DeviceProfile of the SDO. If the SDO does not
     * represent any hardware device, then a DeviceProfile with empty values
     * are returned.
     * This operation throws SDOException with one of the following types.
     *
     * @exception NotAvailable if the target SDO is reachable but cannot
     *                         respond.
     * @exception InternalError if the target SDO cannot execute the operation
     *                          completely due to some internal error.
     * @return    The DeviceProfile of the SDO.
     *
     * @endif
     */
    virtual SDOPackage::DeviceProfile* get_device_profile()
      throw (SDOPackage::NotAvailable, SDOPackage::InternalError);
    
    /*!
     * @if jp
     * 
     * @brief [CORBA interface] SDO ServiceProfile の取得 
     *
     * SDO が所有している Service の ServiceProfile を返すオペレーション。
     * SDO がサービスを一つも所有していない場合には、空のリストを返す。
     * このオペレーションは以下の型の例外を発生させる。
     * 
     * @exception SDONotExists ターゲットのSDOが存在しない。
     * @exception NotAvailable SDOは存在するが応答がない。
     * @exception InternalError 内部的エラーが発生した。
     * @return    SDO が提供する全ての Service の ServiceProfile。
     *
     * @else
     *
     * @brief [CORBA interface] Getting SDO ServiceProfile
     * 
     * This operation returns a list of ServiceProfiles that the SDO has.
     * If the SDO does not provide any service, then an empty list is returned.
     * This operation throws SDOException with one of the following types.
     * 
     * @exception NotAvailable if the target SDO is reachable but cannot
     *                         respond.
     * @exception InternalError if the target SDO cannot execute the operation
     *                          completely due to some internal error.
     * @return    List of ServiceProfiles of all the services the SDO is
     *            providing.
     *
     * @endif
     */
    virtual SDOPackage::ServiceProfileList* get_service_profiles()
      throw (SDOPackage::InvalidParameter, SDOPackage::NotAvailable,
	     SDOPackage::InternalError);
    
    /*!
     * @if jp
     * 
     * @brief [CORBA interface] 特定のServiceProfileの取得 
     *
     * 引数 "id" で指定された名前のサービスの ServiceProfile を返す。
     * 
     * @param     id SDO Service の ServiceProfile に関連付けられた識別子。
     * @return    指定された SDO Service の ServiceProfile。
     * @exception NotAvailable SDOは存在するが応答がない。
     * @exception InternalError 内部的エラーが発生した。
     *
     * @else
     *
     * @brief [CORBA interface] Getting Organizations
     *
     * This operation returns the ServiceProfile that is specified by the
     * argument "id."
     * 
     * @param     id The identifier referring to one of the ServiceProfiles.
     * @return    The profile of the specified service.
     * @exception NotAvailable If the target SDO is reachable but cannot
     *                         respond.
     * @exception InternalError If the target SDO cannot execute the operation
     *                          completely due to some internal error.
     *
     * @endif
     */
    virtual SDOPackage::ServiceProfile* get_service_profile(const char* id)
      throw (SDOPackage::InvalidParameter, SDOPackage::NotAvailable,
	     SDOPackage::InternalError);
    
    /*!
     * @if jp
     * 
     * @brief [CORBA interface] 指定された SDO Service の取得
     *
     * このオペレーションは引数 "id" で指定された名前によって区別される
     * SDO の Service へのオブジェクト参照を返す。 SDO により提供される
     * Service はそれぞれ一意の識別子により区別される。
     *
     * @param id SDO Service に関連付けられた識別子。
     * @return 要求された SDO Service への参照。
     *
     * @else
     *
     * @brief [CORBA interface] Getting specified SDO Service's reference
     *
     * This operation returns an object implementing an SDO's service that
     * is identified by the identifier specified as an argument. Different
     * services provided by an SDO are distinguished with different
     * identifiers. See OMG SDO specification Section 2.2.8, "ServiceProfile,"
     * on page 2-12 for more details.
     *
     * @param id The identifier referring to one of the SDO Service
     * @return The object implementing the requested service.
     *
     * @endif
     */
    virtual SDOPackage::SDOService_ptr get_sdo_service(const char* id)
      throw (SDOPackage::InvalidParameter, SDOPackage::NotAvailable,
	     SDOPackage::InternalError);
    
    /*!
     * @if jp
     * 
     * @brief [CORBA interface] Configuration オブジェクトの取得 
     *
     * このオペレーションは Configuration interface への参照を返す。
     * Configuration interface は各 SDO を管理するためのインターフェースの
     * ひとつである。このインターフェースは DeviceProfile, ServiceProfile,
     * Organization で定義された SDO の属性値を設定するために使用される。
     * Configuration インターフェースの詳細については、OMG SDO specification
     * の 2.3.5節, p.2-24 を参照のこと。
     *
     * @return SDO の Configuration インターフェースへの参照
     * @exception InterfaceNotImplemented SDOはConfigurationインターフェースを
     *                                    持たない。
     * @exception SDONotExists ターゲットのSDOが存在しない。
     * @exception NotAvailable SDOは存在するが応答がない。
     * @exception InternalError 内部的エラーが発生した。
     *
     * @else
     *
     * @brief [CORBA interface] Getting Configuration object
     *
     * This operation returns an object implementing the Configuration
     * interface. The Configuration interface is one of the interfaces that
     * each SDO maintains. The interface is used to configure the attributes
     * defined in DeviceProfile, ServiceProfile, and Organization.
     * See OMG SDO specification Section 2.3.5, "Configuration Interface,"
     * on page 2-24 for more details about the Configuration interface.
     *
     * @return The Configuration interface of an SDO.
     * @exception InterfaceNotImplemented The target SDO has no Configuration
     *                                    interface.
     * @exception SDONotExists The target SDO does not exist.
     * @exception NotAvailable The target SDO is reachable but cannot respond.
     * @exception InternalError The target SDO cannot execute the operation
     *                          completely due to some internal error.
     * @endif
     */
    virtual SDOPackage::Configuration_ptr get_configuration()
      throw (SDOPackage::InterfaceNotImplemented, SDOPackage::NotAvailable,
	     SDOPackage::InternalError);
    
    /*!
     * @if jp
     * 
     * @brief [CORBA interface] Monitoring オブジェクトの取得 
     *
     * このオペレーションは Monitoring interface への参照を返す。
     * Monitoring interface は SDO が管理するインターフェースの一つである。
     * このインターフェースは SDO のプロパティをモニタリングするために
     * 使用される。
     * Monitoring interface の詳細については OMG SDO specification の
     * 2.3.7節 "Monitoring Interface" p.2-35 を参照のこと。
     *
     * @return SDO の Monitoring interface への参照
     * @exception InterfaceNotImplemented SDOはConfigurationインターフェースを
     *                                    持たない。
     * @exception SDONotExists ターゲットのSDOが存在しない。
     * @exception NotAvailable SDOは存在するが応答がない。
     * @exception InternalError 内部的エラーが発生した。
     *
     * @else
     *
     * @brief [CORBA interface] Get Monitoring object
     *
     * This operation returns an object implementing the Monitoring interface.
     * The Monitoring interface is one of the interfaces that each SDO
     * maintains. The interface is used to monitor the properties of an SDO.
     * See OMG SDO specification Section 2.3.7, "Monitoring Interface," on
     * page 2-35 for more details about the Monitoring interface.
     *
     * @return The Monitoring interface of an SDO.
     * @exception InterfaceNotImplemented The target SDO has no Configuration
     *                                    interface.
     * @exception SDONotExists The target SDO does not exist.
     * @exception NotAvailable The target SDO is reachable but cannot respond.
     * @exception InternalError The target SDO cannot execute the operation
     *                          completely due to some internal error.
     * @endif
     */
    virtual SDOPackage::Monitoring_ptr get_monitoring()
      throw (SDOPackage::InterfaceNotImplemented, SDOPackage::NotAvailable,
	     SDOPackage::InternalError);

    /*!
     * @if jp
     * 
     * @brief [CORBA interface] Organization リストの取得 
     *
     * SDO は0個以上の Organization (組織)に所属することができる。 もし SDO が
     * 1個以上の Organization に所属している場合、このオペレーションは所属する
     * Organization のリストを返す。SDO が どの Organization にも所属していない
     * 場合には、空のリストが返される。
     *
     * @return SDO が所属する Organization のリスト。
     * @exception SDONotExists ターゲットのSDOが存在しない。
     * @exception NotAvailable SDOは存在するが応答がない。
     * @exception InternalError 内部的エラーが発生した。
     * @else
     *
     * @brief [CORBA interface] Getting Organizations
     *
     * An SDO belongs to zero or more organizations. If the SDO belongs to one
     * or more organizations, this operation returns the list of organizations
     * that the SDO belongs to. An empty list is returned if the SDO does not
     * belong to any Organizations.
     *
     * @return The list of Organizations that the SDO belong to.
     * @exception SDONotExists The target SDO does not exist.
     * @exception NotAvailable The target SDO is reachable but cannot respond.
     * @exception InternalError The target SDO cannot execute the operation
     *                          completely due to some internal error.
     * @endif
     */
    virtual SDOPackage::OrganizationList* get_organizations()
      throw (SDOPackage::NotAvailable, SDOPackage::InternalError);
    
    /*!
     * @if jp
     * 
     * @brief [CORBA interface] SDO Status リストの取得 
     *
     * このオペレーションは SDO のステータスを表す NVList を返す。
     *
     * @return SDO のステータス。
     * @exception SDONotExists ターゲットのSDOが存在しない。
     * @exception NotAvailable SDOは存在するが応答がない。
     * @exception InternalError 内部的エラーが発生した。
     *
     * @else
     *
     * @brief [CORBA interface] Get SDO Status
     *
     * This operation returns an NVlist describing the status of an SDO.
     *
     * @return The actual status of an SDO.
     * @exception SDONotExists The target SDO does not exist.
     * @exception NotAvailable The target SDO is reachable but cannot respond.
     * @exception InternalError The target SDO cannot execute the operation
     *                          completely due to some internal error.
     *
     * @endif
     */
    virtual SDOPackage::NVList* get_status_list()
      throw (SDOPackage::NotAvailable, SDOPackage::InternalError);
    
    /*!
     * @if jp
     * 
     * @brief [CORBA interface] SDO Status の取得 
     *
     * This operation returns the value of the specified status parameter.
     * 
     * @param name SDO のステータスを定義するパラメータ。
     * @return 指定されたパラメータのステータス値。
     * @exception SDONotExists ターゲットのSDOが存在しない。
     * @exception NotAvailable SDOは存在するが応答がない。
     * @exception InvalidParameter 引数 "name" が null あるいは存在しない。
     * @exception InternalError 内部的エラーが発生した。
     * @else
     *
     * @brief [CORBA interface] Get SDO Status
     *
     * @param name One of the parameters defining the "status" of an SDO.
     * @return The value of the specified status parameter.
     * @exception SDONotExists The target SDO does not exist.
     * @exception NotAvailable The target SDO is reachable but cannot respond.
     * @exception InvalidParameter The parameter defined by "name" is null or
     *                             does not exist.
     * @exception InternalError The target SDO cannot execute the operation
     *                          completely due to some internal error.
     *
     *
     * @endif
     */
    virtual CORBA::Any* get_status(const char* name)
      throw (SDOPackage::InvalidParameter, SDOPackage::NotAvailable,
	     SDOPackage::InternalError);



    //============================================================
    // Local interfaces
    //============================================================
    const char* getInstanceName() {return m_profile.instance_name;}
    void setInstanceName(const char* instance_name);
    const char* getTypeName() {return m_profile.type_name;}
    const char* getDescription() { return m_profile.description;}
    const char* getVersion() {return m_profile.version;}
    const char* getVendor() {return m_profile.vendor;}
    const char* getCategory() {return m_profile.category;}

    std::vector<std::string> getNamingNames();

    void setObjRef(const RTObject_ptr rtobj);
    RTObject_ptr getObjRef() const;



    /*!
     * @if jp
     * 
     * @brief [local interface] RTC のプロパティを設定する
     *
     * RTC が保持すべきプロパティを設定する。与えられるプロパティは、
     * ComponentProfile 等に設定されるべき情報を持たなければならない。
     * このオペレーションは通常 RTC が初期化される際に Manager から
     * 呼ばれることを意図している。
     * 
     * @param prop RTC のプロパティ
     *
     * @else
     *
     * @brief [local interface] Set RTC property
     *
     * This operation sets the properties to the RTC. The given property
     * values should include information for ComponentProfile.
     * Generally, this operation is designed to be called from Manager, when
     * RTC is initialized
     *
     * @param prop Property for RTC.
     *
     * @endif
     */
    void setProperties(const Properties& prop);

    /*!
     * @if jp
     * 
     * @brief [local interface] RTC のプロパティを取得する
     *
     * RTC が保持しているプロパティを返す。与えられるプロパティは、
     * RTCがプロパティを持たない場合は空のプロパティが返される。
     * 
     * @return RTC のプロパティ
     *
     * @else
     *
     * @brief [local interface] Get RTC property
     *
     * This operation returns the properties of the RTC.
     * Empty property would be returned, if RTC has no property.
     *
     * @return Property for RTC.
     *
     * @endif
     */
    Properties& getProperties();


    /*!
     * @if jp
     * 
     * @brief [local interface] Port を登録する
     *
     * RTC が保持するPortを登録する。
     * Port を外部からアクセス可能にするためには、このオペレーションにより
     * 登録されていなければならない。登録される Port はこの RTC 内部において
     * PortProfile.name により区別される。したがって、Port は RTC 内において、
     * ユニークな PortProfile.name を持たなければならない。
     * 登録された Port は内部で適切にアクティブ化された後、その参照と
     * オブジェクト参照がリスト内に保存される。
     * 
     * @param port RTC に登録する Port
     *
     * @else
     *
     * @brief [local interface] Register Port
     *
     * This operation registers a Port to be held by this RTC.
     * In order to enable access to the Port from outside of RTC, the Port
     * must be registered by this operation. The Port that is registered by
     * this operation would be identified by PortProfile.name in the inside of
     * RTC. Therefore, the Port should have unique PortProfile.name in the RTC.
     * The registering Port would be activated properly, and the reference
     * and the object reference would be stored in lists in RTC.
     *
     * @param port Port which is registered in the RTC
     *
     * @endif
     */
    void registerPort(PortBase& port);

    /*!
     * @if jp
     * 
     * @brief [local interface] Port の登録を削除する
     *
     * RTC が保持するPortの登録を削除する。
     * 
     * @param port RTC に登録する Port
     *
     * @else
     *
     * @brief [local interface] Register Port
     *
     * This operation registers a Port to be held by this RTC.
     * In order to enable access to the Port from outside of RTC, the Port
     * must be registered by this operation. The Port that is registered by
     * this operation would be identified by PortProfile.name in the inside of
     * RTC. Therefore, the Port should have unique PortProfile.name in the RTC.
     * The registering Port would be activated properly, and the reference
     * and the object reference would be stored in lists in RTC.
     *
     * @param port Port which is registered in the RTC
     *
     * @endif
     */
    void deletePort(PortBase& port);
    void deletePortByName(const char* port_name);
    void finalizePorts();



    /*
    template <class DataType>
    void registerInPort(BufferBase<DataType>& buffer)
    {
      CorbaInPort<DataType>* port;
      p = new CorbaInPort<DataType>(buffer);
      Port_var inport;
      inport = new PortInPort();
      inport->setInPortRef(p->_this());
    }
    */





  protected:
    //============================================================
    // SDO 関係の変数
    //============================================================
    /*!
     * SDO owned organization list
     */
    SDOPackage::OrganizationList m_sdoOwnedOrganizations;

    /*!
     * SDOService のプロファイルリスト
     */
    SDOPackage::ServiceProfileList m_sdoSvcProfiles;

    /*!
     * SDOService のプロファイルリストからidでサーチするためのファンクタ
     */
    struct svc_name
    {
      svc_name (const char* id) : m_id(id) {};
      bool operator()(const SDOPackage::ServiceProfile& prof)
      {
	return m_id == std::string(prof.id);
      }
      std::string m_id;
    };

    /*!
     * SDO Configuratio Interface へのポインタ
     */
    SDOPackage::Configuration_impl* m_pSdoConfigImpl;
    SDOPackage::Configuration_var  m_pSdoConfig;

    /*!
     * SDO organization
     */
    SDOPackage::OrganizationList m_sdoOrganizations;

    /*!
     * SDO Status
     */
    SDOPackage::NVList m_sdoStatus;

    
    //============================================================
    // RTC 関係の変数
    //============================================================
    /*!
     * RTC::ComponentProfile
     */
    ComponentProfile m_profile;

    RTObject_ptr m_objref;
    /*!
     * Port のオブジェクトリファレンスのリスト
     */
    PortAdmin m_portAdmin;

    ExecutionContextServiceList m_execContexts;

    bool m_alive;

    /*!
     * RTC のプロパティ
     */
    Properties m_properties;

    struct nv_name
    {
      nv_name(const char* name) : m_name(name) {};
      bool operator()(const SDOPackage::NameValue& nv)
      {
        return m_name == std::string(nv.name);
      }
      std::string m_name;
    };


    struct ec_copy
    {
      ec_copy(ExecutionContextList& eclist)
	: m_eclist(eclist)
      {
      }
      void operator()(ExecutionContextService_ptr ecs)
      {
	CORBA_SeqUtil::push_back(m_eclist, ExecutionContext::_duplicate(ecs));
      }
      ExecutionContextList& m_eclist;
    };
    //    ExecutionContextAdminList m_execContextList;



  };
};
#endif // RTObject
