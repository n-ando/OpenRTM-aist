// -*- C++ -*-
/*!
 * @file SdoConfiguration.cpp
 * @brief SDO's Configuration implementation class
 * @date $Date: 2006-10-17 10:13:23 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: SdoConfiguration.cpp,v 1.2 2006-10-17 10:13:23 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.1  2006/09/11 18:13:49  n-ando
 * The first commit.
 *
 *
 */

#include "rtm/SdoConfiguration.h"

// ACE

namespace SDOPackage
{
  Configuration_impl::Configuration_impl(CORBA::ORB_ptr orb,
					 PortableServer::POA_ptr poa)
    : m_varORB(orb), m_varPOA(poa)
  {
  }

  
  /* @if jp
   * @brief [CORBA interface] SDO の DeviceProfile をセットする
   * @else
   * @brief [CORBA interface] Set DeviceProfile of SDO
   * @endif
   */
  CORBA::Boolean
  Configuration_impl::set_device_profile(const DeviceProfile& dProfile)
    throw (InvalidParameter, NotAvailable, InternalError)
  {
    try
      {
        Write_Guard guard(m_deviceProfile.lock);
        m_deviceProfile.data = dProfile;
      }
    catch (...)
      {
        throw InternalError("Unknown Error");
        // never reach here
        return false;
      }
    return true;
  }

  
  /*!
   * @if jp
   * @brief [CORBA interface] SDO の ServiceProfile のセット
   * @else
   * @brief [CORBA interface] Set SDO's ServiceProfile
   * @endif
   */
  CORBA::Boolean
  Configuration_impl::set_service_profile(const ServiceProfile& sProfile)
    throw (InvalidParameter, NotAvailable, InternalError)
  {
    try
      {
        m_serviceProfiles.push_back(sProfile);
      }
    catch (...)
      {
        throw InternalError("Configuration::set_service_profile");
        // never reach here
        return false;
      }
    return true;
  }
  

  /*!
   * @if jp
   * @brief [CORBA interface] Organization の追加
   * @else
   * @brief [CORBA interface] Add Organization
   * @endif
   */ 
  CORBA::Boolean
  Configuration_impl::add_organization(Organization_ptr org)
    throw (InvalidParameter, NotAvailable, InternalError)
  {
    try
      {
	//        Write_Guard guard(m_organizations.lock);
        m_organizations.push_back(org);
      }
    catch (...)
      {
        throw InternalError("Configuration::set_service_profile");
        // never reach here
        return false;
      }
    return true;
  }
  

  /*!
   * @if jp
   * @brief [CORBA interface] ServiceProfile の削除
   * @else
   * @brief [CORBA interface] Getting Organizations
   * @endif
   */  
  CORBA::Boolean
  Configuration_impl::remove_service_profile(const char* id)
    throw (InvalidParameter, NotAvailable, InternalError)
  {
    try
      {
        m_serviceProfiles.erase_if(service_id(id));
      }
    catch (...)
      {
        throw InternalError("Configuration::remove_service_profile");
        // never reach here
        return false;
      }
    return true;
  }
  

  /*!
   * @if jp
   * @brief [CORBA interface] Organization の参照の削除
   * @else
   * @brief [CORBA interface] Remove the reference of Organization 
   * @endif
   */
  CORBA::Boolean
  Configuration_impl::remove_organization(const char* organization_id)
    throw (InvalidParameter, NotAvailable, InternalError)
  {
    try
      {
        m_organizations.erase_if(org_id(organization_id));
      }
    catch (...)
      {
        throw InternalError("Configuration::remove_organization");
        // never reach here
        return false;
      }
    return true;
  }

  
  /*!
   * @if jp
   * @brief [CORBA interface] 設定パラメータのリストの取得
   * @else
   * @brief [CORBA interface] Getting a list of configuration parameter
   * @endif
   */ 
  ParameterList*
  Configuration_impl::get_configuration_parameters()
    throw (NotAvailable, InternalError)
  {
    try
      {
	Read_Guard gaurd(m_parameters.lock);
	ParameterList_var param(&m_parameters);
	return param._retn();
      }
    catch (...)
      {
	throw InternalError("Configuration::get_configuration_parameters()");
	//never reach here
      }
    // never reach here
    return new ParameterList(0);
  }

  
  /*!
   * @if jp
   * @brief [CORBA interface] Configuration parameter の値のリストの取得
   * @else
   * @brief [CORBA interface] Getting value list of configuration parameter
   * @endif
   */
  NVList*
  Configuration_impl::get_configuration_parameter_values()
    throw (NotAvailable, InternalError)
  {
    return new NVList(0);
  }

  
  /*!
   * @if jp
   * @brief [CORBA interface] Configuration parameter の値の取得
   * @else
   * @brief [CORBA interface] Getting value of configuration parameter
   * @endif
   */
  CORBA::Any*
  Configuration_impl::get_configuration_parameter_value(const char* name)
    throw (InvalidParameter, NotAvailable, InternalError)
  {
    return new CORBA::Any();
  }
  

  /*!
   * @if jp
   * @brief [CORBA interface] Configuration パラメータの変更
   * @else
   * @brief [CORBA interface] Modify the parameter value
   * @endif
   */
  CORBA::Boolean
  Configuration_impl::set_configuration_parameter(const char* name,
						  const CORBA::Any& value)
    throw (InvalidParameter, NotAvailable, InternalError)
  {
    return true;
  }
  

  /*!
   * @if jp
   * @brief [CORBA interface] ConfigurationSet リストの取得 
   * @else
   * @brief [CORBA interface] Getting list of ConfigurationSet
   * @endif
   */
  ConfigurationSetList*
  Configuration_impl::get_configuration_sets()
    throw (NotAvailable, InternalError)
  {
    try
      {
	Read_Guard guard(m_configurations.lock);
	ConfigurationSetList_var config_sets(&m_configurations);
	return config_sets._retn();
      }
    catch (...)
      {
	throw InternalError("Configuration::get_configuration_sets()");
      }
    // never reach here
    return new ConfigurationSetList(0);
  }
  

  /*!
   * @if jp
   * @brief [CORBA interface] ConfigurationSet の取得
   * @else
   * @brief [CORBA interface] Getting a ConfigurationSet
   * @endif
   */
  ConfigurationSet*
  Configuration_impl::get_configuration_set(const char* id)
    throw (InvalidParameter, NotAvailable, InternalError)
  {
    try
      {
	ConfigurationSet config_set;
	config_set = m_configurations.find(config_id(id));
	ConfigurationSet_var config(&config_set);
	return config._retn();
      }
    catch (...)
      {
	throw InternalError("Configuration::get_configuration_set()");
      }
    // never reach here
    return new ConfigurationSet();
  }
  

  /*!
   * @if jp
   * @brief [CORBA interface] ConfigurationSet をセットする
   * @else
   * @brief [CORBA interface] Set ConfigurationSet
   * @endif
   */
  CORBA::Boolean
  Configuration_impl::
    set_configuration_set_values(const char* id,
				 const ConfigurationSet& configuration_set)
    throw (InvalidParameter, NotAvailable, InternalError)
  {
    try
      {
	// validation check of given "configuration_set"
	// not implemented

	// find and store the configuration_set
	m_configurations.find(config_id(id)) = configuration_set;
      }
    catch (...)
      {
	throw InvalidParameter("Configuration::set_configuration_set_values()");
      }
    return true;
  }
  

  /*!
   * @if jp
   * @brief [CORBA interface] アクティブな ConfigurationSet を取得する
   * @else
   * @brief [CORBA interface] Get active ConfigurationSet
   * @endif
   */ 
  ConfigurationSet*
  Configuration_impl::get_active_configuration_set()
    throw (NotAvailable, InternalError)
  {
    try
      {
	//	std::string id(m_activeConfigurationSet.id());
	std::string id("default");
	ConfigurationSet config_set;
	config_set = m_configurations.find(config_id(id.c_str()));
	ConfigurationSet_var config(&config_set);
	return config._retn();
      }
    catch (...)
      {
	throw InternalError("Configuration::get_active_configuration_set()");
      }
    // never reach here
    return new ConfigurationSet();
  }
  

  /*!
   * @if jp
   * @brief [CORBA interface] ConfigurationSet を追加する
   * @else
   * @brief [CORBA interface] Add ConfigurationSet
   * @endif
   */
  CORBA::Boolean
  Configuration_impl::
  add_configuration_set(const ConfigurationSet& configuration_set)
    throw (InvalidParameter, NotAvailable, InternalError)
  {
    try
      {
	m_configurations.push_back(configuration_set);
      }
    catch (...)
      {
	throw InternalError("Configuration::add_configuration_set()");
	return false;
      }
    return true;
  }
  
  
  /*!
   * @if jp
   * @brief [CORBA interface] ConfigurationSet を削除する
   * @else
   * @brief [CORBA interface] Remove ConfigurationSet
   * @endif
   */
  CORBA::Boolean
  Configuration_impl::remove_configuration_set(const char* id)
    throw (InvalidParameter, NotAvailable, InternalError)
  {
    try
      {
	m_configurations.erase_if(config_id(id));
      }
    catch (...)
      {
	throw InternalError("Configuration::remove_configuration_set()");
	return false;
      }
    return true;
  }
  

  /*!
   * @if jp
   * @brief [CORBA interface] ConfigurationSet のアクティブ化
   * @else
   * @brief [CORBA interface] Activate ConfigurationSet
   * @endif
   */ 
  CORBA::Boolean
  Configuration_impl::activate_configuration_set(const char* id)
    throw (InvalidParameter, NotAvailable, InternalError)
  {
    try
      {
	m_configurations.find(config_id(id));
	m_activeConfigurationSet = std::string(id);
      }
    catch (...)
      {
	throw InternalError("Configuration::activate_configuration_set()");
	return false;
      }
    return true;
  }
  
  
};
