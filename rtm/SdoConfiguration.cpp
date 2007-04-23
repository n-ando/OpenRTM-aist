// -*- C++ -*-
/*!
 * @file SdoConfiguration.cpp
 * @brief SDO's Configuration implementation class
 * @date $Date: 2007-04-23 04:58:16 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: SdoConfiguration.cpp,v 1.7 2007-04-23 04:58:16 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.6  2007/01/24 16:03:52  n-ando
 * The ctor. was changed.
 *
 * Revision 1.5  2006/11/09 10:20:40  n-ando
 * set_service_profile never throws InvalidParameter exception.
 *
 * Revision 1.4  2006/11/08 20:00:12  n-ando
 * ConfigurationSet related interfaces are fixed.
 *
 * Revision 1.3  2006/10/30 08:05:38  n-ando
 * CORBA sequence operations were replaced by CORBA_SeqUtil functions.
 *
 * Revision 1.2  2006/10/17 10:13:23  n-ando
 * Small fixes.
 *
 * Revision 1.1  2006/09/11 18:13:49  n-ando
 * The first commit.
 *
 *
 */

#include "rtm/SdoConfiguration.h"
#include <rtm/CORBA_SeqUtil.h>
#include <rtm/UUID.h>
#include <rtm/NVUtil.h>
#include <iostream>
// ACE

namespace SDOPackage
{
  void 
  toProperties(RTC::Properties& prop, const SDOPackage::ConfigurationSet& conf)
  {
    NVUtil::copyToProperties(prop, conf.configuration_data);
    //    prop["description"] = conf.description;
  }

  void
  toConfigurationSet(SDOPackage::ConfigurationSet& conf,
		     const RTC::Properties& prop)
  {
    conf.description = CORBA::string_dup(prop["description"].c_str());
    conf.id = CORBA::string_dup(prop.getName());
    NVUtil::copyFromProperties(conf.configuration_data, prop);
  }

  //============================================================
  // Ctor and Dtor
  //============================================================

  Configuration_impl::Configuration_impl(RTC::ConfigAdmin& configsets)
    : m_configsets(configsets)
  {
    m_objref = this->_this();
  }

  Configuration_impl::~Configuration_impl()
  {
  }


  //============================================================
  // Basic Configuration 
  //============================================================
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
	Guard gurad(m_dprofile_mutex);
        m_deviceProfile = dProfile;
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
    // SDO specification defines that InvalidParameter() exception
    // is thrown when sProfile is null.
    // But sProfile is reference and it becomes never null.
    // So this operation does not throw InvalidParameter exception.
    //    if (CORBA::is_nil(sProfile.service)) throw InvalidParameter();
    try
      {

	if (sProfile.id == "")
	  {
	    ServiceProfile prof(sProfile);
	    prof.id = CORBA::string_dup(getUUID().c_str());
	    CORBA_SeqUtil::push_back(m_serviceProfiles, prof);
	    return true;
	  }

	CORBA::Long index;
	index = CORBA_SeqUtil::find(m_serviceProfiles,
				    service_id(sProfile.id));
	if (index >= 0)
	  {
	    CORBA_SeqUtil::erase(m_serviceProfiles, index);
	  }
	CORBA_SeqUtil::push_back(m_serviceProfiles, sProfile);
	return true;
      }
    catch (...)
      {
        throw InternalError("Configuration::set_service_profile");

        return false;
      }
    // never reach here
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
        CORBA_SeqUtil::push_back(m_organizations, org);
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
	CORBA_SeqUtil::erase_if(m_serviceProfiles, service_id(id));
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
	Guard gurad(m_org_mutex);
        CORBA_SeqUtil::erase_if(m_organizations, org_id(organization_id));
      }
    catch (...)
      {
        throw InternalError("Configuration::remove_organization");
        // never reach here
        return false;
      }
    return true;
  }


  //============================================================
  // Configuration Parameter manipulation
  //============================================================
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
	Guard gaurd(m_params_mutex);
	ParameterList_var param;
	param = new ParameterList(m_parameters);
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
    Guard guard(m_config_mutex);
    NVList_var nvlist;
    nvlist = new NVList((CORBA::ULong)0);

    /*
    CORBA::Long index;
    index = getActiveConfigIndex();
    if (index >= 0)
      {
	nvlist = new NVList(m_configurations[index].configuration_data);
      }
    */
    return nvlist._retn();
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
    if (name == "") throw InvalidParameter("Name is empty.");

    //    CORBA::Long index;
    CORBA::Any_var value;
    value = new CORBA::Any();
    /*
    index = getActiveConfigIndex();
    if (index < 0) throw InternalError("No active configuration.");

    CORBA::Long item;
    item = CORBA_SeqUtil::find(m_configurations[index].configuration_data,
			       nv_name(name));
    if (item < 0) throw InvalidParameter("No such name."); 
    
    value = new CORBA::Any(m_configurations[index].configuration_data[item].value);
    */
    return value._retn();
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
    /*
    if (name == "") throw InvalidParameter("Name is empty.");
    
    CORBA::Long index(getActiveConfigIndex());
    if (index < 0) throw InternalError("No active config.");

    CORBA::Long item;
    item = CORBA_SeqUtil::find(m_configurations[index].configuration_data,
			       nv_name(name));
    if (item < 0) throw InvalidParameter("No such name.");
    
    m_configurations[index].configuration_data[item].value = value;
    */
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
	Guard guard(m_config_mutex);

	ConfigurationSetList_var config_sets;
	config_sets = new ConfigurationSetList((CORBA::ULong)0);
	
	std::vector<RTC::Properties*> cf(m_configsets.getConfigurationSets());
	config_sets->length(cf.size());
	for (CORBA::ULong i(0), len(cf.size()); i < len; ++i)
	  {
	    toConfigurationSet(config_sets[i], *(cf[i]));
	  }

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
    if (id == "") throw InvalidParameter("ID is empty");

    Guard guard(m_config_mutex);

    if (!m_configsets.haveConfig(id))
      throw InvalidParameter("No such ConfigurationSet");

    const RTC::Properties& configset(m_configsets.getConfigurationSet(id));

    try
      {
	ConfigurationSet_var config;
	config = new ConfigurationSet();
	toConfigurationSet(config, configset);
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
    if (id == "") throw InvalidParameter("ID is empty.");
    
    try
      {
	RTC::Properties conf(id);
	toProperties(conf, configuration_set);
	return m_configsets.setConfigurationSetValues(id, conf);
      }
    catch (...)
      {
	throw InternalError("Configuration::set_configuration_set_values()");
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
    // activeなConfigurationSetは無い
    if (!m_configsets.isActive()) throw NotAvailable();    
    
    try
      {
	Guard gurad(m_config_mutex);
	// activeなConfigurationSetを返す
	ConfigurationSet_var config;
	config = new ConfigurationSet();
	toConfigurationSet(config, m_configsets.getActiveConfigurationSet());
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
	Guard gurad(m_config_mutex);
	const char* config_id(configuration_set.id);
	RTC::Properties config(config_id);
	toProperties(config, configuration_set);
	return m_configsets.addConfigurationSet(config);
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
    if (id == "")
      throw InvalidParameter("ID is empty.");

    try
      {
	Guard guard(m_config_mutex);
	return m_configsets.removeConfigurationSet(id);
      }
    catch (...)
      {
	throw InternalError("Configuration::remove_configuration_set()");
	return false;
      }
    return false;
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
    if (id == "")
      throw InvalidParameter("ID is empty.");

    try
      {
	return m_configsets.activateConfigurationSet(id);
      }
    catch (...)
      {
	throw InternalError("Configuration::activate_configuration_set()");
	return false;
      }
    return false;
  }



  //============================================================
  // Local interfaces
  //============================================================
  
  Configuration_ptr Configuration_impl::getObjRef()
  {
    return m_objref;
  }

  const DeviceProfile Configuration_impl::getDeviceProfile()
  {
    return m_deviceProfile;
  }

  const ServiceProfileList Configuration_impl::getServiceProfiles()
  {
    return m_serviceProfiles;
  }
  const ServiceProfile Configuration_impl::getServiceProfile(const char* id)
  {
    CORBA::Long index;
    index =  CORBA_SeqUtil::find(m_serviceProfiles,
				 service_id(id));
    if (index < 0) return ServiceProfile();
    return m_serviceProfiles[index];
  }
  
  const OrganizationList Configuration_impl::getOrganizations()
  {
    return m_organizations;
  }
  
  /*!
   * @if jp
   * @brief UUIDを生成する
   * @else
   * @brief Get the UUID
   * @endif
   */
  const std::string Configuration_impl::getUUID() const
  {
    RTC_Utils::UUID_Generator uugen;
    uugen.init();
    RTC_Utils::UUID* uuid = uugen.generateUUID(2,0x01);
    
    return std::string(uuid->to_string()->c_str());
  }

};
