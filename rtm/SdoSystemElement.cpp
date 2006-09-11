// -*- C++ -*-
/*!
 * @file SdoSystemElement.h
 * @brief SDOSystemElement and SDO implementation classes
 * @date $Date: 2006-09-11 18:14:31 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: SdoSystemElement.cpp,v 1.1 2006-09-11 18:14:31 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 *
 */

#include "rtm/SdoSystemElement.h"
#include "rtm/SdoConfiguration.h"

namespace SDOPackage
{
  //============================================================
  // SDOSystemElement_impl
  //============================================================

  //============================================================
  //
  // <<< CORBA interfaces >>>
  //
  //============================================================
  /*!
   * @if jp
   * @brief [CORBA interface] Organization リストの取得 
   * @else
   * @brief [CORBA interface] Getting Organizations
   * @endif
   */
  SDOSystemElement_impl::SDOSystemElement_impl()
  {
    m_ownedOrganizations.length(0);
  }
  SDOSystemElement_impl::SDOSystemElement_impl(CORBA::ORB_ptr orb,
					       PortableServer::POA_ptr poa)
    : m_pORB(orb), m_pPOA(poa)
  {
    m_ownedOrganizations.length(0);
  }


  /*!
   * @if jp
   * @brief [CORBA interface] Organization リストの取得 
   * @else
   * @brief [CORBA interface] Getting Organizations
   * @endif
   */
  OrganizationList*  SDOSystemElement_impl::get_owned_organizations()
    throw (NotAvailable)
  {
    OrganizationList_var org_list(&m_ownedOrganizations);
    return org_list._retn();
  }

  

  //============================================================
  // SDO_impl
  //============================================================
  SDO_impl::SDO_impl(CORBA::ORB_ptr orb, PortableServer::POA_ptr poa)
    : SDOSystemElement_impl(orb, poa)
  {
    m_SdoId._id = CORBA::string_dup("");
    m_SdoType._type = CORBA::string_dup("");
    m_pConfig = new SDOPackage::Configuration_impl(orb, poa);


    m_varConfigId = m_pPOA->activate_object(m_pConfig);
    m_varConfigObj = Configuration::_narrow(m_pPOA->id_to_reference(m_varConfigId));
    m_pConfig->_remove_ref();
    
  }
  

  //============================================================
  //
  // <<< CORBA interfaces >>>
  //
  //============================================================
  
  /*!
   * @if jp
   * @brief [CORBA interface] SDO ID の取得
   * @else
   * @brief [CORBA interface] Getting SDO ID
   * @endif
   */
  char* SDO_impl::get_sdo_id()
    throw (NotAvailable, InternalError)
  {
    try
      {
	ACE_Guard<ACE_Thread_Mutex> guard(m_SdoId._mutex);
	return CORBA::string_dup(m_SdoId._id);
      }
    catch (...)
      {
	throw InternalError("Unknown Error: SDO::get_sdo_id()");
      }
  }
  
  /*!
   * @if jp
   * @brief [CORBA interface] SDO タイプの取得
   * @else
   * @brief [CORBA interface] Getting SDO type
   * @endif
   */
  char* SDO_impl::get_sdo_type()
    throw (NotAvailable, InternalError)
  { 
    try
      {
	ACE_Guard<ACE_Thread_Mutex> guard(m_SdoType._mutex);
	return CORBA::string_dup(m_SdoType._type);
      }
    catch (...)
      {
	throw InternalError("Unknown Error: SDO::get_sdo_type()");
      }
  }
  
  /*!
   * @if jp
   * @brief [CORBA interface] SDO DeviceProfile リストの取得 
   * @else
   * @brief [CORBA interface] Getting SDO DeviceProfile
   * @endif
   */
  DeviceProfile* SDO_impl::get_device_profile()
    throw (NotAvailable, InternalError)
  {
    try
      {
	// return copied struct data while data is locked
	return new DeviceProfile(m_pConfig->getDeviceProfile());
      }
    catch (...)
      {
	throw InternalError("Unknown Error: SDO::get_device_profile()");
      }
  }
  
  /*!
   * @if jp
   * @brief [CORBA interface] SDO ServiceProfile の取得 
   * @else
   * @brief [CORBA interface] Getting SDO ServiceProfile
   * @endif
   */
  ServiceProfileList* SDO_impl::get_service_profiles()
    throw (InvalidParameter, NotAvailable, InternalError)
  {
    try
      {
	return new ServiceProfileList(m_pConfig->getServiceProfiles());
      }
    catch (...)
      {
	throw InternalError("Unknown Error: SDO::get_service_profiles()");
      }
  }
  
  /*!
   * @if jp
   * @brief [CORBA interface] 特定のServiceProfileの取得 
   * @else
   * @brief [CORBA interface] Getting Organizations
   * @endif
   */
  ServiceProfile* SDO_impl::get_service_profile(const char* id)
    throw (InvalidParameter, NotAvailable, InternalError)
  {
    try
      {
	return new ServiceProfile(m_pConfig->getServiceProfile(id));
      }
    catch (...)
      {
	throw InternalError("Unknown Error: SDO::get_service_profile()");
      }
  }
  
  /*!
   * @if jp
   * @brief [CORBA interface] 指定された SDO Service の取得
   * @else
   * @brief [CORBA interface] Getting specified SDO Service's reference
   * @endif
   */
  SDOService_ptr SDO_impl::get_sdo_service(const char* id)
    throw (InvalidParameter, NotAvailable, InternalError)
  {
    try
      {
	//	SDOService_var service(m_Configuration.getService(id));
	return SDOService::_nil();
      }
    catch (...)
      {
	throw InternalError("Unknown Error: SDO::get_sdo_service()");
      }
    return SDOService::_nil();
  }
  
  /*!
   * @if jp
   * @brief [CORBA interface] Configuration オブジェクトの取得 
   * @else
   * @brief [CORBA interface] Getting Configuration object
   * @endif
   */
  Configuration_ptr SDO_impl::get_configuration()
    throw (InterfaceNotImplemented, NotAvailable, InternalError)
  {
    try
      {
	return Configuration::_duplicate(m_varConfigObj);
      }
    catch (...)
      {
	throw InternalError("Unknown Error: SDO::get_configuration()");
      }
    return Configuration::_nil();
  }
  
  /*!
   * @if jp
   * @brief [CORBA interface] Organization リストの取得 
   * @else
   * @brief [CORBA interface] Getting Organizations
   * @endif
   */
  Monitoring_ptr SDO_impl::get_monitoring()
    throw (InterfaceNotImplemented, NotAvailable, InternalError)
  {
    throw InterfaceNotImplemented();
    return SDOPackage::Monitoring::_nil();
  }
  
  /*!
   * @if jp
   * @brief [CORBA interface] Organization リストの取得 
   * @else
   * @endif
   */
  OrganizationList* SDO_impl::get_organizations()
    throw (NotAvailable, InternalError)
  {
    try
      {
	return new OrganizationList(m_pConfig->getOrganizations());
      }
    catch (...)
      {
	throw InternalError("Unknown Error: SDO::get_organization()");
      }
    return new OrganizationList(0);
  }
  
  /*!
   * @if jp
   * @brief [CORBA interface] Status リストの取得
   * @else
   * @brief [CORBA interface] Getting list of SDO's status
   * @endif
   */
  NVList* SDO_impl::get_status_list()
    throw (NotAvailable, InternalError)
  {
    try
      {
	return new NVList(m_Status);
      }
    catch (...)
      {
	throw InternalError("Unknown Error: SDO::get_status_list()");
      }
  }
  
  /*!
   * @if jp
   * 
   * @brief [CORBA interface] Organization リストの取得 
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
   * @brief [CORBA interface] Getting Organizations
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
  CORBA::Any* SDO_impl::get_status(const char* name)
    throw (InvalidParameter, NotAvailable, InternalError)
  {
    if (name == NULL)
      throw InvalidParameter("name is NULL: SDO::get_status()");
    
    try
      {
	return new CORBA::Any(m_Status.find(nv_name(name)).value);
      }
    //    catch ()
    //      {
    //	throw InvalidParameter("invalid name: SDO::get_status()");
    //      }
    catch (...)
      {
	throw InternalError("Unknown Error: SDO::get_status()");
      }
  }
  
  // end of CORBA interface definition
  //============================================================
  
  
  void SDO_impl::setSdoId(const char* sdo_id)
  {
    ACE_Guard<ACE_Thread_Mutex> guard(m_SdoId._mutex);
    m_SdoId._id = CORBA::string_dup(sdo_id);
    return;
  }
  
  void SDO_impl::setSdoType(const char* sdo_type)
  {
    ACE_Guard<ACE_Thread_Mutex> guard(m_SdoType._mutex);
    m_SdoType._type = CORBA::string_dup(sdo_type);
    return;
  }
  
  void SDO_impl::setDeviceProfile(const DeviceProfile& dProfile)
  {
    m_pConfig->set_device_profile(dProfile);
  }
  
  void SDO_impl::addServiceProfile(const ServiceProfile& sProfile)
  {
    m_pConfig->set_service_profile(sProfile);
  }
  
};
