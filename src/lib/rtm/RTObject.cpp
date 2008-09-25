// -*- C++ -*-
/*!
 * @file RTObject.cpp
 * @brief RT component base class
 * @date $Date: 2008-01-14 07:57:15 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id$
 *
 */

#include <assert.h>
#include <rtm/RTObject.h>
#include <rtm/SdoConfiguration.h>
#include <rtm/CORBA_SeqUtil.h>
#include <rtm/Manager.h>
#include <coil/stringutil.h>
#include <iostream>

namespace RTC
{
  /*!
   * @if jp
   * @brief RTコンポーネントのデフォルトプロファイル
   * @else
   * @brief RT-Component default profile
   * @endif
   */
  static const char* default_conf[] =
    {
      "implementation_id", "",
      "type_name",         "",
      "description",       "",
      "version",           "",
      "vendor",            "",
      "category",          "",
      "activity_type",     "",
      "max_instance",      "",
      "language",          "",
      "lang_type",         "",
      "conf",              "",
      ""
    };
  
  /*!
   * @if jp
   * @brief コンストラクタ
   * @else
   * @brief Constructor
   * @endif
   */
  RTObject_impl::RTObject_impl(Manager* manager)
    : m_pManager(manager),
      m_pORB(CORBA::ORB::_duplicate(manager->getORB())),
      m_pPOA(PortableServer::POA::_duplicate(manager->getPOA())),
      m_portAdmin(manager->getORB(), manager->getPOA()),
      m_created(true), m_alive(false),
      m_properties(default_conf), m_configsets(*(m_properties.getNode("conf")))
  {
    m_pSdoConfigImpl = new SDOPackage::Configuration_impl(m_configsets);
    m_pSdoConfig = m_pSdoConfigImpl->getObjRef();
  }
  
  /*!
   * @if jp
   * @brief コンストラクタ
   * @else
   * @brief Constructor
   * @endif
   */
  RTObject_impl::RTObject_impl(CORBA::ORB_ptr orb,
			       PortableServer::POA_ptr poa)
    : m_pManager(NULL),
      m_pORB(CORBA::ORB::_duplicate(orb)),
      m_pPOA(PortableServer::POA::_duplicate(poa)),
      m_portAdmin(orb, poa),
      m_created(true), m_alive(false),
      m_properties(default_conf), m_configsets(*(m_properties.getNode("conf")))
  {
    m_pSdoConfigImpl = new SDOPackage::Configuration_impl(m_configsets);
    m_pSdoConfig = m_pSdoConfigImpl->getObjRef();
  }
  
  /*!
   * @if jp
   * @brief 仮想デストラクタ
   * @else
   * @brief Virtual destructor
   * @endif
   */
  RTObject_impl::~RTObject_impl()
  {
  }
  
  //============================================================
  // Overridden functions
  //============================================================
  /*!
   * @if jp
   * @brief 初期化処理用コールバック関数
   * @else
   * @brief Callback function to initialize
   * @endif
   */
  // The initialize action (on CREATED->ALIVE transition)
  // former rtc_init_entry() 
  ReturnCode_t RTObject_impl::onInitialize()
  {
    return RTC::RTC_OK;
  }
  
  /*!
   * @if jp
   * @brief 終了処理用コールバック関数
   * @else
   * @brief Callback function to finalize
   * @endif
   */
  // The finalize action (on ALIVE->END transition)
  // former rtc_exiting_entry()
  ReturnCode_t RTObject_impl::onFinalize()
  {
    return RTC::RTC_OK;
  }
  
  /*!
   * @if jp
   * @brief 開始処理用コールバック関数
   * @else
   * @brief Callback function for startup action
   * @endif
   */
  // The startup action when ExecutionContext startup
  // former rtc_starting_entry()
  ReturnCode_t RTObject_impl::onStartup(RTC::UniqueId ec_id)
  {
    return RTC::RTC_OK;
  }
  
  /*!
   * @if jp
   * @brief 停止処理用コールバック関数
   * @else
   * @brief Callback function for shutdown action
   * @endif
   */
  // The shutdown action when ExecutionContext stop
  // former rtc_stopping_entry()
  ReturnCode_t RTObject_impl::onShutdown(RTC::UniqueId ec_id)
  {
    return RTC::RTC_OK;
  }
  
  /*!
   * @if jp
   * @brief 活性化処理用コールバック関数
   * @else
   * @brief Callback function to activate
   * @endif
   */
  // The activated action (Active state entry action)
  // former rtc_active_entry()
  ReturnCode_t RTObject_impl::onActivated(RTC::UniqueId ec_id)
  {
    return RTC::RTC_OK;
  }
  
  /*!
   * @if jp
   * @brief 非活性化処理用コールバック関数
   * @else
   * @brief Callback function to deactivate
   * @endif
   */
  // The deactivated action (Active state exit action)
  // former rtc_active_exit()
  ReturnCode_t RTObject_impl::onDeactivated(RTC::UniqueId ec_id)
  {
    return RTC::RTC_OK;
  }
  
  /*!
   * @if jp
   * @brief 周期処理用コールバック関数
   * @else
   * @brief Callback function to execute periodically
   * @endif
   */
  // The execution action that is invoked periodically
  // former rtc_active_do()
  ReturnCode_t RTObject_impl::onExecute(RTC::UniqueId ec_id)
  {
    return RTC::RTC_OK;
  }
  
  /*!
   * @if jp
   * @brief 中断処理用コールバック関数
   * @else
   * @brief Callback function to abort
   * @endif
   */
  // The aborting action when main logic error occurred.
  // former rtc_aborting_entry()
  ReturnCode_t RTObject_impl::onAborting(RTC::UniqueId ec_id)
  {
    return RTC::RTC_OK;
  }
  
  /*!
   * @if jp
   * @brief エラー処理用コールバック関数
   * @else
   * @brief Callback function for error handling
   * @endif
   */
  // The error action in ERROR state
  // former rtc_error_do()
  ReturnCode_t RTObject_impl::onError(RTC::UniqueId ec_id)
  {
    return RTC::RTC_OK;
  }
  
  /*!
   * @if jp
   * @brief リセット処理用コールバック関数
   * @else
   * @brief Callback function to reset
   * @endif
   */
  // The reset action that is invoked resetting
  // This is same but different the former rtc_init_entry()
  ReturnCode_t RTObject_impl::onReset(RTC::UniqueId ec_id)
  {
    return RTC::RTC_OK;
  }
  
  /*!
   * @if jp
   * @brief 状態変更処理用コールバック関数
   * @else
   * @brief Callback function to update the state
   * @endif
   */
  // The state update action that is invoked after onExecute() action
  // no corresponding operation exists in OpenRTm-aist-0.2.0
  ReturnCode_t RTObject_impl::onStateUpdate(RTC::UniqueId ec_id)
  {
    return RTC::RTC_OK;
  }
  
  /*!
   * @if jp
   * @brief 動作周期変更通知用コールバック関数
   * @else
   * @brief Callback function to change execution cycle
   * @endif
   */
  // The action that is invoked when execution context's rate is changed
  // no corresponding operation exists in OpenRTm-aist-0.2.0
  ReturnCode_t RTObject_impl::onRateChanged(RTC::UniqueId ec_id)
  {
    return RTC::RTC_OK;
  }
  
  //============================================================
  // RTC::LightweightRTObject
  //============================================================
  /*!
   * @if jp
   * @brief [CORBA interface] RTCを初期化する
   * @else
   * @brief [CORBA interface] IInitialize the RTC that realizes this interface.
   * @endif
   */
  ReturnCode_t RTObject_impl::initialize()
    throw (CORBA::SystemException)
  {
    ReturnCode_t ret;
    ret = on_initialize();
    m_created = false;
    
    if (ret == RTC::RTC_OK)
      {
	if (m_execContexts.length() > 0)
	  {
	    m_execContexts[0]->start();
	  }
	m_alive = true;
      }
    return ret;
  }
  
  /*!
   * @if jp
   * @brief [CORBA interface] RTC を終了する
   * @else
   * @brief [CORBA interface] Finalize the RTC for preparing it for destruction
   * @endif
   */
  ReturnCode_t RTObject_impl::finalize()
    throw (CORBA::SystemException)
  {
    if (m_created) return RTC::PRECONDITION_NOT_MET;
    
    for (CORBA::ULong i(0), n(m_execContexts.length()); i < n; ++i)
      {
	if (m_execContexts[i]->is_running())
	  return RTC::PRECONDITION_NOT_MET;
      }
    
    ReturnCode_t ret(on_finalize());
    shutdown();
    return ret;
  }
  
  /*!
   * @if jp
   * @brief [CORBA interface] RTC がオーナーである ExecutionContext を
   *        停止させ、そのコンテンツと共に終了させる
   * @else
   * @brief [CORBA interface] RTC stops ExecutionContext of RTC's owner
   *        and finalize it with its contents
   * @endif
   */
  ReturnCode_t RTObject_impl::exit()
    throw (CORBA::SystemException)
  {
    CORBA_SeqUtil::for_each(m_execContexts,
	    deactivate_comps(RTC::LightweightRTObject::_duplicate(m_objref)));
    if (m_execContexts.length() > 0)
      {
	m_execContexts[0]->stop();
	m_alive = false;
      }
    ReturnCode_t ret(finalize());
    
    return ret;
  }
  
  /*!
   * @if jp
   * @brief [CORBA interface] RTC が Alive 状態であるかどうか確認する。
   * @else
   * @brief [CORBA interface] Confirm whether RTC is the alive state
   * @endif
   */
  CORBA::Boolean RTObject_impl::is_alive(ExecutionContext_ptr exec_context)
    throw (CORBA::SystemException)
  {
    // ### not implemented ###
    return m_alive;
  }
  
  /*!
   * @if jp
   * @brief [CORBA interface] ExecutionContextを取得する
   * @else
   * @brief [CORBA interface] Get ExecutionContext
   * @endif
   */
  ExecutionContext_ptr RTObject_impl::get_context(UniqueId ec_id)
    throw (CORBA::SystemException)
  {
    if (((CORBA::Long)ec_id) > ((CORBA::Long)m_execContexts.length() - 1))
      {
	return ExecutionContext::_nil();
      }
    return ExecutionContext::_duplicate(m_execContexts[ec_id]);
  }
    
  /*!
   * @if jp
   * @brief [CORBA interface] ExecutionContextListを取得する
   * @else
   * @brief [CORBA interface] Get ExecutionContextList
   * @endif
   */
  ExecutionContextList* RTObject_impl::get_owned_contexts()
    throw (CORBA::SystemException)
  {
    ExecutionContextList_var execlist;
    execlist = new ExecutionContextList();
    
    CORBA_SeqUtil::for_each(m_execContexts, ec_copy(execlist));
    
    return execlist._retn();
  }

  /*!
   * @if jp
   * @brief [CORBA interface] 参加している ExecutionContextList を取得する
   * @else
   * @brief [CORBA interface] Get participating ExecutionContextList.
   * @endif
   */
  ExecutionContextList* RTObject_impl::get_participating_contexts()
    throw (CORBA::SystemException)
  {
    ExecutionContextList_var execlist;
    execlist = new ExecutionContextList();
    
    // ### not implemented ###
    //    CORBA_SeqUtil::for_each(m_execContexts, ec_copy(execlist));
    
    return execlist._retn();
  }


  /*!
   * @if jp
   * @brief [CORBA interface] ExecutionContext のハンドルを返す
   * @else
   * @brief [CORBA interface] Return a handle of a ExecutionContext
   * @endif
   */
  ExecutionContextHandle_t
  RTObject_impl::get_context_handle(ExecutionContext_ptr cxt)
    throw (CORBA::SystemException)
  {
    CORBA::Long num;
    num = CORBA_SeqUtil::find(m_execContexts, ec_find(cxt));
    return (ExecutionContextHandle_t)num;
  }


  /*!
   * @if jp
   * @brief [CORBA interface] ExecutionContextをattachする
   * @else
   * @brief [CORBA interface] Attach ExecutionContext
   * @endif
   */
  UniqueId RTObject_impl::attach_context(ExecutionContext_ptr exec_context)
    throw (CORBA::SystemException)
  {
    ExecutionContextService_var ecs;
    ecs = ExecutionContextService::_narrow(exec_context);
    if (CORBA::is_nil(ecs))
      {
	return -1;
      }
    
    CORBA_SeqUtil::
      push_back(m_execContexts, ExecutionContextService::_duplicate(ecs));
    
    return m_execContexts.length() - 1;
  }
  
  /*!
   * @if jp
   * @brief [CORBA interface] ExecutionContextをdetachする
   * @else
   * @brief [CORBA interface] Detach ExecutionContext
   * @endif
   */
  ReturnCode_t RTObject_impl::detach_context(UniqueId ec_id)
    throw (CORBA::SystemException)
  {
    if (((CORBA::Long)ec_id) > ((CORBA::Long)m_execContexts.length() - 1))
      {
	return RTC::BAD_PARAMETER;
      }
    
    if (CORBA::is_nil(m_execContexts[ec_id]))
      {
	return RTC::BAD_PARAMETER;
      }
    
    CORBA::release(m_execContexts[ec_id]);
    m_execContexts[ec_id] = ExecutionContextService::_nil();
    return RTC::RTC_OK;
  }
  
  //============================================================
  // RTC::RTObject
  //============================================================
  
  /*!
   * @if jp
   * @brief [RTObject CORBA interface] コンポーネントプロファイルを取得する
   * @else
   * @brief [RTCObject CORBA interface] Get RTC's profile
   * @endif
   */
  ComponentProfile* RTObject_impl::get_component_profile()
    throw (CORBA::SystemException)
  {
    try
      {
	ComponentProfile_var profile
	  = new ComponentProfile(m_profile);
	profile->port_profiles = m_portAdmin.getPortProfileList();
	return profile._retn();
      }
    catch (...)
      {
	; // This operation throws no exception.
      }
    assert(false);
    return 0;
  }
  
  /*!
   * @if jp
   * @brief [RTObject CORBA interface] ポートを取得する
   * @else
   * @brief [RTCObject CORBA interface] Get Ports
   * @endif
   */
  PortServiceList* RTObject_impl::get_ports()
    throw (CORBA::SystemException)
  {
    try
      {
	return m_portAdmin.getPortServiceList();
      }
    catch (...)
      {
	; // This operation throws no exception.
      }
    assert(false);
    return 0;
  }
  
  /*!
   * @if jp
   * @brief [RTObject CORBA interface] ExecutionContextAdmin を取得する
   * @else
   * @brief [RTCObject CORBA interface] Get ExecutionContextAdmin
   * @endif
   */
//  ExecutionContextServiceList* RTObject_impl::get_execution_context_services()
//    throw (CORBA::SystemException)
//  {
//    try
//      {
//	ExecutionContextServiceList_var exec_context;
//	exec_context = new ExecutionContextServiceList(m_execContexts);
//	return exec_context._retn();
//      }
//    catch (...)
//      {
//	; // This operation throws no exception.
//      }
//    assert(false);
//    return 0;
//  }
  
  //============================================================
  // RTC::ComponentAction
  //============================================================
  /*!
   * @if jp
   * @brief [ComponentAction CORBA interface] RTC の初期化
   * @else
   * @brief [ComponentAction CORBA interface] Initialize RTC
   * @endif
   */
  ReturnCode_t RTObject_impl::on_initialize()
    throw (CORBA::SystemException)
  {
    ReturnCode_t ret(RTC::RTC_ERROR);
    try
      {
	ret = onInitialize();
      }
    catch (...)
      {
	return RTC::RTC_ERROR;
      }
    return ret;
  }
  
  /*!
   * @if jp
   * @brief [ComponentAction CORBA interface] RTC の終了
   * @else
   * @brief [ComponentAction CORBA interface] Finalize RTC
   * @endif
   */
  ReturnCode_t RTObject_impl::on_finalize()
    throw (CORBA::SystemException)
  {
    ReturnCode_t ret(RTC::RTC_ERROR);
    try
      {
	ret = onFinalize();
      }
    catch (...)
      {
	return RTC::RTC_ERROR;
      }
    return ret;
  }
  
  /*!
   * @if jp
   * @brief [ComponentAction CORBA interface] RTC の開始
   * @else
   * @brief [ComponentAction CORBA interface] Startup RTC
   * @endif
   */
  ReturnCode_t RTObject_impl::on_startup(UniqueId ec_id)
    throw (CORBA::SystemException)
  {
    ReturnCode_t ret(RTC::RTC_ERROR);
    try
      {
	ret = onStartup(ec_id);
      }
    catch (...)
      {
	return RTC::RTC_ERROR;
      }
    return ret;
  }
  
  /*!
   * @if jp
   * @brief [ComponentAction CORBA interface] RTC の停止
   * @else
   * @brief [ComponentAction CORBA interface] Shutdown RTC
   * @endif
   */
  ReturnCode_t RTObject_impl::on_shutdown(UniqueId ec_id)
    throw (CORBA::SystemException)
  {
    ReturnCode_t ret(RTC::RTC_ERROR);
    try
      {
	ret = onShutdown(ec_id);
      }
    catch (...)
      {
	return RTC::RTC_ERROR;
      }
    return ret;
  }
  
  /*!
   * @if jp
   * @brief [ComponentAction CORBA interface] RTC の活性化
   * @else
   * @brief [ComponentAction CORBA interface] Activate RTC
   * @endif
   */
  ReturnCode_t RTObject_impl::on_activated(UniqueId ec_id)
    throw (CORBA::SystemException)
  {
    ReturnCode_t ret(RTC::RTC_ERROR);
    try
      {
	m_configsets.update();
	ret = onActivated(ec_id);
      }
    catch (...)
      {
	return RTC::RTC_ERROR;
      }
    return ret;
  }
  
  /*!
   * @if jp
   * @brief [ComponentAction CORBA interface] RTC の非活性化
   * @else
   * @brief [ComponentAction CORBA interface] Deactivate RTC
   * @endif
   */
  ReturnCode_t RTObject_impl::on_deactivated(UniqueId ec_id)
    throw (CORBA::SystemException)
  {
    ReturnCode_t ret(RTC::RTC_ERROR);
    try
      {
	ret = onDeactivated(ec_id);
      }
    catch (...)
      {
	return RTC::RTC_ERROR;
      }
    return ret;
  }
  
  /*!
   * @if jp
   * @brief [ComponentAction CORBA interface] RTC のエラー状態への遷移
   * @else
   * @brief [ComponentAction interface] Transition to the error state
   * @endif
   */
  ReturnCode_t RTObject_impl::on_aborting(UniqueId ec_id)
    throw (CORBA::SystemException)
  {
    ReturnCode_t ret(RTC::RTC_ERROR);
    try
      {
	ret = onAborting(ec_id);
      }
    catch (...)
      {
	return RTC::RTC_ERROR;
      }
    return ret;
  }
  
  /*!
   * @if jp
   * @brief [ComponentAction CORBA interface] RTC のエラー処理
   * @else
   * @brief [ComponentAction CORBA interface] Error Processing of RTC
   * @endif
   */
  ReturnCode_t RTObject_impl::on_error(UniqueId ec_id)
    throw (CORBA::SystemException)
  {
    ReturnCode_t ret(RTC::RTC_ERROR);
    try
      {
	ret = onError(ec_id);
	m_configsets.update();
      }
    catch (...)
      {
	return RTC::RTC_ERROR;
      }
    return ret;
  }
  
  /*!
   * @if jp
   * @brief [ComponentAction CORBA interface] RTC のリセット
   * @else
   * @brief [ComponentAction CORBA interface] Resetting RTC
   * @endif
   */
  ReturnCode_t RTObject_impl::on_reset(UniqueId ec_id)
    throw (CORBA::SystemException)
  {
    ReturnCode_t ret(RTC::RTC_ERROR);
    try
      {
	ret = onReset(ec_id);
      }
    catch (...)
      {
	return RTC::RTC_ERROR;
      }
    return ret;
  }
  
  /*!
   * @if jp
   * @brief [DataFlowComponentAction CORBA interface] RTC の定常処理(第一周期)
   * @else
   * @brief [DataFlowComponentAction CORBA interface] Primary Periodic 
   *        Operation of RTC
   * @endif
   */
  ReturnCode_t RTObject_impl::on_execute(UniqueId ec_id)
    throw (CORBA::SystemException)
  {
    ReturnCode_t ret(RTC::RTC_ERROR);
    try
      {
	ret = onExecute(ec_id);
      }
    catch (...)
      {
	return RTC::RTC_ERROR;
      }
    return ret;
  }
  
  /*!
   * @if jp
   * @brief [DataFlowComponentAction CORBA interface] RTC の定常処理(第二周期)
   * @else
   * @brief [DataFlowComponentAction CORBA interface] Secondary Periodic 
   *        Operation of RTC
   * @endif
   */
  ReturnCode_t RTObject_impl::on_state_update(UniqueId ec_id)
    throw (CORBA::SystemException)
  {
    ReturnCode_t ret(RTC::RTC_ERROR);
    try
      {
	ret = onStateUpdate(ec_id);
	m_configsets.update();
      }
    catch (...)
      {
	return RTC::RTC_ERROR;
      }
    return ret;
  }
  
  /*!
   * @if jp
   * @brief [DataFlowComponentAction CORBA interface] 実行周期変更通知
   * @else
   * @brief [DataFlowComponentAction CORBA interface] Notify rate changed
   * @endif
   */
  ReturnCode_t RTObject_impl::on_rate_changed(UniqueId ec_id)
    throw (CORBA::SystemException)
  {
    ReturnCode_t ret(RTC::RTC_ERROR);
    try
      {
	ret = onRateChanged(ec_id);
      }
    catch (...)
      {
	return RTC::RTC_ERROR;
      }
    return ret;
  }
  
  //============================================================
  // SDO interfaces
  //============================================================
  /*!
   * @if jp
   * @brief [SDO interface] Organization リストの取得 
   * @else
   * @brief [SDO interface] Get Organization list
   * @endif
   */
  SDOPackage::OrganizationList* RTObject_impl::get_owned_organizations()
    throw (CORBA::SystemException, SDOPackage::NotAvailable)
  {
    try
      {
	SDOPackage::OrganizationList_var org_list;
	org_list = new SDOPackage::OrganizationList(m_sdoOwnedOrganizations);
	return org_list._retn();
      }
    catch (...)
      {
	throw SDOPackage::NotAvailable();
      }
    return new SDOPackage::OrganizationList();
  }
  
  // SDOPackage::SDO
  /*!
   * @if jp
   * @brief [SDO interface] SDO ID の取得
   * @else
   * @brief [SDO interface] Get the SDO ID
   * @endif
   */
  char* RTObject_impl::get_sdo_id()
    throw (CORBA::SystemException, 
	   SDOPackage::NotAvailable, SDOPackage::InternalError)
  {
    try
      {
	CORBA::String_var sdo_id;
	sdo_id = CORBA::string_dup(m_profile.instance_name);
	return sdo_id._retn();
      }
    catch (...)
      {
	throw SDOPackage::InternalError("get_sdo_id()");
      }
  }
  
  /*!
   * @if jp
   * @brief [SDO interface] SDO タイプの取得
   * @else
   * @brief [SDO interface] Get SDO type
   * @endif
   */
  char* RTObject_impl::get_sdo_type()
    throw (CORBA::SystemException, 
	   SDOPackage::NotAvailable, SDOPackage::InternalError)
  {
    try
      {
	CORBA::String_var sdo_type;
	sdo_type = CORBA::string_dup(m_profile.description);
	return sdo_type._retn();
      }
    catch (...)
      {
	throw SDOPackage::InternalError("get_sdo_type()");
      }
    return "";
  }
  
  /*!
   * @if jp
   * @brief [SDO interface] SDO DeviceProfile リストの取得 
   * @else
   * @brief [SDO interface] Get SDO DeviceProfile list
   * @endif
   */
  SDOPackage::DeviceProfile* RTObject_impl::get_device_profile()
    throw (CORBA::SystemException, 
	   SDOPackage::NotAvailable, SDOPackage::InternalError)
  {
    try
      {
	SDOPackage::DeviceProfile_var dprofile;
	dprofile = new SDOPackage::DeviceProfile();
	dprofile->device_type  = CORBA::string_dup(m_profile.category);
	dprofile->manufacturer = CORBA::string_dup(m_profile.vendor);
	dprofile->model        = CORBA::string_dup(m_profile.type_name);
	dprofile->version      = CORBA::string_dup(m_profile.version);
	dprofile->properties   = m_profile.properties;
	return dprofile._retn();
      }
    catch (...)
      {
	throw SDOPackage::InternalError("get_device_profile()");
      }
    return new SDOPackage::DeviceProfile();
  }
  
  /*!
   * @if jp
   * @brief [SDO interface] SDO ServiceProfile の取得 
   * @else
   * @brief [SDO interface] Get SDO ServiceProfile
   * @endif
   */
  SDOPackage::ServiceProfileList* RTObject_impl::get_service_profiles()
    throw (CORBA::SystemException, 
	   SDOPackage::NotAvailable, SDOPackage::InternalError)
  {
    try
      {
	SDOPackage::ServiceProfileList_var sprofiles;
	sprofiles = new SDOPackage::ServiceProfileList(m_sdoSvcProfiles);
	return sprofiles._retn();
      }
    catch (...)
      {
	throw SDOPackage::InternalError("get_service_profiles()");
      }
    return new SDOPackage::ServiceProfileList();
  }
  
  /*!
   * @if jp
   * @brief [SDO interface] 特定のServiceProfileの取得 
   * @else
   * @brief [SDO interface] Get specified ServiceProfile
   * @endif
   */
  SDOPackage::ServiceProfile*
  RTObject_impl::get_service_profile(const char* id)
    throw (CORBA::SystemException, 
	   SDOPackage::InvalidParameter, SDOPackage::NotAvailable,
	   SDOPackage::InternalError)
  {
    if (!id)
      throw SDOPackage::InvalidParameter("get_service_profile(): Empty name.");
    
    try
      {
	CORBA::Long index;
	index = CORBA_SeqUtil::find(m_sdoSvcProfiles, svc_name(id));
	
	SDOPackage::ServiceProfile_var sprofile;
	sprofile = new SDOPackage::ServiceProfile(m_sdoSvcProfiles[index]);
	return sprofile._retn();
      }
    catch (...)
      {
	throw SDOPackage::InternalError("get_service_profile()");
      }
    return new SDOPackage::ServiceProfile();
  }
  
  /*!
   * @if jp
   * @brief [SDO interface] 指定された SDO Service の取得
   * @else
   * @brief [SDO interface] Get specified SDO Service's reference
   * @endif
   */
  SDOPackage::SDOService_ptr RTObject_impl::get_sdo_service(const char* id)
    throw (CORBA::SystemException, 
	   SDOPackage::InvalidParameter, SDOPackage::NotAvailable,
	   SDOPackage::InternalError)
  {
    if (!id)
      throw SDOPackage::InvalidParameter("get_service(): Empty name.");
    
    try
      {
	CORBA::Long index;
	index = CORBA_SeqUtil::find(m_sdoSvcProfiles, svc_name(id));
	
	SDOPackage::SDOService_var service;
	service = m_sdoSvcProfiles[index].service;
	return service._retn();
      }
    catch (...)
      {
	throw SDOPackage::InternalError("get_service()");
      }
    return SDOPackage::SDOService::_nil();
  }
  
  /*!
   * @if jp
   * @brief [SDO interface] Configuration オブジェクトの取得 
   * @else
   * @brief [SDO interface] Get Configuration object
   * @endif
   */
  SDOPackage::Configuration_ptr RTObject_impl::get_configuration()
    throw (CORBA::SystemException, 
	   SDOPackage::InterfaceNotImplemented, SDOPackage::NotAvailable,
	   SDOPackage::InternalError)
  {
    if (m_pSdoConfig == NULL)
      throw SDOPackage::InterfaceNotImplemented();
    try
      {
	SDOPackage::Configuration_var config;
	config = m_pSdoConfig;
	return config._retn();
      }
    catch (...)
      {
	SDOPackage::InternalError("get_configuration()");
      }
    return SDOPackage::Configuration::_nil();
  }
  
  /*!
   * @if jp
   * @brief [SDO interface] Monitoring オブジェクトの取得 
   * @else
   * @brief [SDO interface] Get Monitoring object
   * @endif
   */
  SDOPackage::Monitoring_ptr RTObject_impl::get_monitoring()
    throw (CORBA::SystemException, 
	   SDOPackage::InterfaceNotImplemented, SDOPackage::NotAvailable,
	   SDOPackage::InternalError)
  {
    throw SDOPackage::InterfaceNotImplemented();
    return SDOPackage::Monitoring::_nil();
  }
  
  /*!
   * @if jp
   * @brief [SDO interface] Organization リストの取得 
   * @else
   * @brief [SDO interface] Get Organization list
   * @endif
   */
  SDOPackage::OrganizationList* RTObject_impl::get_organizations()
    throw (CORBA::SystemException, 
	   SDOPackage::NotAvailable, SDOPackage::InternalError)
  {
    try
      {
	SDOPackage::OrganizationList_var org;
	org = new SDOPackage::OrganizationList(m_sdoOrganizations);
	return org._retn();
      }
    catch (...)
      {
	throw SDOPackage::InternalError("get_organizations()");
      }
    return new SDOPackage::OrganizationList(0);
  }
  
  /*!
   * @if jp
   * @brief [SDO interface] SDO Status リストの取得 
   * @else
   * @brief [SDO interface] Get SDO Status list
   * @endif
   */
  SDOPackage::NVList* RTObject_impl::get_status_list()
    throw (CORBA::SystemException, 
	   SDOPackage::NotAvailable, SDOPackage::InternalError)
  {
    try
      {
	NVList_var status;
	status = new NVList(m_sdoStatus);
	return status._retn();
      }
    catch (...)
      {
	SDOPackage::InternalError("get_status_list()");
      }
    return new SDOPackage::NVList(0);
  }
  
  /*!
   * @if jp
   * @brief [SDO interface] SDO Status の取得 
   * @else
   * @brief [SDO interface] Get SDO Status
   * @endif
   */
  CORBA::Any* RTObject_impl::get_status(const char* name)
    throw (CORBA::SystemException, 
	   SDOPackage::InvalidParameter, SDOPackage::NotAvailable,
	   SDOPackage::InternalError)
  {
    CORBA::Long index;
    index = CORBA_SeqUtil::find(m_sdoStatus, nv_name(name));
    if (index < 0)
      throw SDOPackage::InvalidParameter("get_status(): Not found");
    try
      {
	CORBA::Any_var status;
	status = new CORBA::Any(m_sdoStatus[index].value);
	return status._retn();
      }
    catch (...)
      {
	throw SDOPackage::InternalError("get_status()");
      }
    return new CORBA::Any();
  }
  
  //============================================================
  // Local methods
  //============================================================
  /*!
   * @if jp
   * @brief [local interface] インスタンス名の設定
   * @else
   * @brief [local interface] Set instance name
   * @endif
   */
  void RTObject_impl::setInstanceName(const char* instance_name)
  {
    m_properties["instance_name"] = instance_name;
    m_profile.instance_name = m_properties["instance_name"].c_str();
  }
  
  /*!
   * @if jp
   * @brief [local interface] Naming Server 情報の取得
   * @else
   * @brief [local interface] Get Naming Server information
   * @endif
   */
  std::vector<std::string> RTObject_impl::getNamingNames()
  {
    return coil::split(m_properties["naming.names"], ",");
  }
  
  /*!
   * @if jp
   * @brief [local interface] オブジェクトリファレンスの設定
   * @else
   * @brief [local interface] Set the object reference
   * @endif
   */
  void RTObject_impl::setObjRef(const RTObject_ptr rtobj)
  {
    m_objref = rtobj;
  }
  
  /*!
   * @if jp
   * @brief [local interface] オブジェクトリファレンスの取得
   * @else
   * @brief [local interface] Get the object reference
   * @endif
   */
  RTObject_ptr RTObject_impl::getObjRef() const
  {
    return RTC::RTObject::_duplicate(m_objref);
  }
  
  /*!
   * @if jp
   * @brief [local interface] RTC のプロパティを設定する
   * @else
   * @brief [local interface] Set RTC property
   * @endif
   */
  void RTObject_impl::setProperties(const Properties& prop)
  {
    m_properties << prop;
    m_profile.instance_name = m_properties["instance_name"].c_str();
    m_profile.type_name     = m_properties["type_name"].c_str();
    m_profile.description   = m_properties["description"].c_str();
    m_profile.version       = m_properties["version"].c_str();
    m_profile.vendor        = m_properties["vendor"].c_str();
    m_profile.category      = m_properties["category"].c_str();
  }
  
  /*!
   * @if jp
   * @brief [local interface] RTC のプロパティを取得する
   * @else
   * @brief [local interface] Get RTC property
   * @endif
   */
  Properties& RTObject_impl::getProperties()
  {
    return m_properties;
  }
  
  /*!
   * @if jp
   * @brief コンフィギュレーションパラメータの更新(ID指定)
   * @else
   * @brief Update configuration parameters (by ID)
   * @endif
   */
  void RTObject_impl::updateParameters(const char* config_set)
  {
    m_configsets.update(config_set);
    return;
  }
  
  /*!
   * @if jp
   * @brief [local interface] Port を登録する
   * @else
   * @brief [local interface] Register Port
   * @endif
   */
  void RTObject_impl::registerPort(PortBase& port)
  {
    m_portAdmin.registerPort(port);
    port.setOwner(this->getObjRef());
    return;
  }
  
  /*!
   * @if jp
   * @brief [local interface] Port の登録を削除する
   * @else
   * @brief [local interface] Unregister Port
   * @endif
   */
  void RTObject_impl::deletePort(PortBase& port)
  {
    m_portAdmin.deletePort(port);
    return;
  }
  
  /*!
   * @if jp
   * @brief [local interface] 名前指定により Port の登録を削除する
   * @else
   * @brief [local interface] Delete Port by specifying its name
   * @endif
   */
  void RTObject_impl::deletePortByName(const char* port_name)
  {
    m_portAdmin.deletePortByName(port_name);
    return;
  }
  
  /*!
   * @if jp
   * @brief 全 Port の登録を削除する
   * @else
   * @brief Unregister All Ports
   * @endif
   */
  void RTObject_impl::finalizePorts()
  {
    m_portAdmin.finalizePorts();
  }
  
  /*!
   * @if jp
   * @brief RTC を終了する
   * @else
   * @brief Shutdown RTC
   * @endif
   */
  void RTObject_impl::shutdown()
  {
    try
      {
	finalizePorts();
	m_pPOA->deactivate_object(*m_pPOA->servant_to_id(m_pSdoConfigImpl));
	m_pPOA->deactivate_object(*m_pPOA->servant_to_id(this));
      }
    catch (...)
      {
	;
      }
    
    if (m_pManager != NULL)
      {
	m_pManager->cleanupComponent(this);
      }
  }
};
