// -*- C++ -*-
/*!
 * @file SdoConfiguration.cpp
 * @brief SDO's Configuration implementation class
 * @date $Date: 2006-11-08 20:00:12 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: SdoConfiguration.cpp,v 1.4 2006-11-08 20:00:12 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
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
    try
      {
	if (CORBA::is_nil(sProfile.service)) throw InvalidParameter();

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

    CORBA::Long index;
    index = getActiveConfigIndex();
    if (index >= 0)
      {
	nvlist = new NVList(m_configurations[index].configuration_data);
      }

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
    if (m_activeConfId == "") return new CORBA::Any();

    CORBA::Long index;
    CORBA::Any_var value;
    index = getActiveConfigIndex();
    if (index < 0) throw InternalError("No active configuration.");

    CORBA::Long item;
    item = CORBA_SeqUtil::find(m_configurations[index].configuration_data,
			       nv_name(name));
    if (item < 0) throw InvalidParameter("No such name."); 
    
    value = new CORBA::Any(m_configurations[index].configuration_data[item].value);
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
    if (name == "") throw InvalidParameter("Name is empty.");
    
    CORBA::Long index(getActiveConfigIndex());
    if (index < 0) throw InternalError("No active config.");

    CORBA::Long item;
    item = CORBA_SeqUtil::find(m_configurations[index].configuration_data,
			       nv_name(name));
    if (item < 0) throw InvalidParameter("No such name.");
    
    m_configurations[index].configuration_data[item].value = value;
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
	config_sets = new ConfigurationSetList(m_configurations);
	
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
    CORBA::Long index;
    index = CORBA_SeqUtil::find(m_configurations,
				config_id(id));
    
    if (index < 0) throw InvalidParameter("No such ConfigurationSet");
    try
      {
	ConfigurationSet_var config;
	config = new ConfigurationSet(m_configurations[index]);
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
	CORBA::Long index;
	index = CORBA_SeqUtil::find(m_configurations, config_id(id));
	if (index < 0)
	  { // idに同一なものは無いのでリストの後ろに追加
	    CORBA_SeqUtil::push_back(m_configurations, configuration_set);
	  }
	else
	  { // 同一なIDがある場合上書き
	    m_configurations[index] = configuration_set;
	  }
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
    try
      {
	Guard gurad(m_config_mutex);
	CORBA::Long index(getActiveConfigIndex());
	// activeなConfigurationSetは無い
	if (index < 0) return new ConfigurationSet();

	// activeなConfigurationSetを返す
	ConfigurationSet_var config;
	config = new ConfigurationSet(m_configurations[index]);
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
	// 同じIDのConfigurationSetがあるか？
	CORBA::Long index;
	index = CORBA_SeqUtil::find(m_configurations,
				    config_id(configuration_set.id));
	if (index < 0)
	  { // 新規IDなので後ろに追加
	    CORBA_SeqUtil::push_back(m_configurations, configuration_set);
	  }
	else // 同一IDのConfigurationSetが存在：上書き
	  { // 
	    m_configurations[index] = configuration_set;
	  }
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

	// id は存在するか？
	CORBA::Long index;
	index = CORBA_SeqUtil::find(m_configurations, config_id(id));
	if (index < 0) throw InvalidParameter("No such id");

	// active な ID と同じなら active ID を消去
	if (m_activeConfId == id)
	  {
	    m_activeConfId == "";
	  }
	CORBA_SeqUtil::erase(m_configurations, index);

	// configsetlist が変更された
	m_activeConfIndex = -1;
	return true;
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
    if (id == "")
      throw InvalidParameter("ID is empty.");

    CORBA::Long index;
    index = CORBA_SeqUtil::find(m_configurations,
				config_id(id));
    if (index < 0)
      throw InvalidParameter("No ID found.");
    
    try
      {
	m_activeConfId = id;
	m_activeConfIndex = index;
      }
    catch (...)
      {
	throw InternalError("Configuration::activate_configuration_set()");
	return false;
      }
    return true;
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


  CORBA::Long Configuration_impl::getActiveConfigIndex()
  {
    // index が変わっていないならキャッシュしている番号を返す
    if (m_activeConfIndex != -1) return m_activeConfIndex;

    // IDがからなら、active な ConfigurationSet が無いことになる
    if (m_activeConfId == "")
      {
	return -1;
      }
    CORBA::Long index;
    index = CORBA_SeqUtil::find(m_configurations,
				config_id(m_activeConfId.c_str()));

    return index;
  }

};
