// -*- C++ -*-
/*!
 * @file ConfigurationProxy.cpp 
 * @brief IConfiguration CORBA proxy for doil
 * @date $Date$
 * @author This file was automatically generated form SDOPackage.idl 
 *         by omniidl/doil backend
 *
 * $Id$
 */

#include <doil/corba/CORBAManager.h>
#include <IConfiguration.h>
#include <ConfigurationProxy.h>
#include <SDOPackageTypeConversion.h>
#include <doil/corba/BasicTypeConversion.h>

namespace SDOPackage 
{
  /*!
   * @brief ctor
   */ 
  ConfigurationProxy::ConfigurationProxy(::CORBA::Object_ptr obj)
   : m_obj(::SDOPackage::Configuration::_nil()),
     m_refcount(1)//   : m_obj(::SDOPackage::Configuration::_nil())
  {
    m_obj = ::SDOPackage::Configuration::_narrow(obj);
    if (::CORBA::is_nil(m_obj)) throw std::bad_alloc();
    m_obj = ::SDOPackage::Configuration::_duplicate(m_obj);
  }

  /*!
   * @brief dtor
   */ 
  ConfigurationProxy::~ConfigurationProxy()
  {
    ::CORBA::release(m_obj);
  }

  
  /*!
   * @brief set_device_profile 
   */ 
  bool ConfigurationProxy::set_device_profile(const ::SDOPackage::DeviceProfile& dProfile)
      throw (::SDOPackage::InvalidParameter,
             ::SDOPackage::NotAvailable,
             ::SDOPackage::InternalError)
  {
    // Convert Local to CORBA.
    // (The direction of the argument is 'in' or 'inout'.)
    ::SDOPackage::DeviceProfile _dProfile;
    local_to_corba(dProfile, _dProfile);

    // Execute the method. 
    ::CORBA::Boolean corba_ret;
    bool local_ret;
    corba_ret = m_obj->set_device_profile(_dProfile);

    // Convert CORBA to Local.
    // (The direction of the argument is 'out' or 'inout'.)

    // Generate the return value.
//    local_ret = corba_ret;
    corba_to_local(corba_ret, local_ret);
    return local_ret;
  }

  /*!
   * @brief set_service_profile 
   */ 
  bool ConfigurationProxy::set_service_profile(const ::SDOPackage::ServiceProfile& sProfile)
      throw (::SDOPackage::InvalidParameter,
             ::SDOPackage::NotAvailable,
             ::SDOPackage::InternalError)
  {
    // Convert Local to CORBA.
    // (The direction of the argument is 'in' or 'inout'.)
    ::SDOPackage::ServiceProfile _sProfile;
    local_to_corba(sProfile, _sProfile);

    // Execute the method. 
    ::CORBA::Boolean corba_ret;
    bool local_ret;
    corba_ret = m_obj->set_service_profile(_sProfile);

    // Convert CORBA to Local.
    // (The direction of the argument is 'out' or 'inout'.)

    // Generate the return value.
//    local_ret = corba_ret;
    corba_to_local(corba_ret, local_ret);
    return local_ret;
  }

  /*!
   * @brief add_organization 
   */ 
  bool ConfigurationProxy::add_organization(const ::SDOPackage::IOrganization* org)
      throw (::SDOPackage::InvalidParameter,
             ::SDOPackage::NotAvailable,
             ::SDOPackage::InternalError)
  {
    // Convert Local to CORBA.
    // (The direction of the argument is 'in' or 'inout'.)
    ::SDOPackage::Organization_ptr _org;
    local_to_corba(const_cast< ::SDOPackage::IOrganization* >(org), _org);

    // Execute the method. 
    ::CORBA::Boolean corba_ret;
    bool local_ret;
    corba_ret = m_obj->add_organization(_org);

    // Convert CORBA to Local.
    // (The direction of the argument is 'out' or 'inout'.)

    // Generate the return value.
//    local_ret = corba_ret;
    corba_to_local(corba_ret, local_ret);
    return local_ret;
  }

  /*!
   * @brief remove_service_profile 
   */ 
  bool ConfigurationProxy::remove_service_profile(const ::std::string& id)
      throw (::SDOPackage::InvalidParameter,
             ::SDOPackage::NotAvailable,
             ::SDOPackage::InternalError)
  {
    // Convert Local to CORBA.
    // (The direction of the argument is 'in' or 'inout'.)
    char* _id;
    local_to_corba(id, _id);

    // Execute the method. 
    ::CORBA::Boolean corba_ret;
    bool local_ret;
    corba_ret = m_obj->remove_service_profile(_id);

    // Convert CORBA to Local.
    // (The direction of the argument is 'out' or 'inout'.)

    // Generate the return value.
//    local_ret = corba_ret;
    corba_to_local(corba_ret, local_ret);
    return local_ret;
  }

  /*!
   * @brief remove_organization 
   */ 
  bool ConfigurationProxy::remove_organization(const ::std::string& organization_id)
      throw (::SDOPackage::InvalidParameter,
             ::SDOPackage::NotAvailable,
             ::SDOPackage::InternalError)
  {
    // Convert Local to CORBA.
    // (The direction of the argument is 'in' or 'inout'.)
    char* _organization_id;
    local_to_corba(organization_id, _organization_id);

    // Execute the method. 
    ::CORBA::Boolean corba_ret;
    bool local_ret;
    corba_ret = m_obj->remove_organization(_organization_id);

    // Convert CORBA to Local.
    // (The direction of the argument is 'out' or 'inout'.)

    // Generate the return value.
//    local_ret = corba_ret;
    corba_to_local(corba_ret, local_ret);
    return local_ret;
  }

  /*!
   * @brief get_configuration_parameters 
   */ 
  ::SDOPackage::ParameterList ConfigurationProxy::get_configuration_parameters()
      throw (::SDOPackage::NotAvailable,
             ::SDOPackage::InternalError)
  {
    // Convert Local to CORBA.
    // (The direction of the argument is 'in' or 'inout'.)

    // Execute the method. 
    ::SDOPackage::ParameterList* corba_ret;
    ::SDOPackage::ParameterList local_ret;
    corba_ret = m_obj->get_configuration_parameters();

    // Convert CORBA to Local.
    // (The direction of the argument is 'out' or 'inout'.)

    // Generate the return value.
    corba_to_local(*corba_ret, local_ret);
    delete corba_ret; 
    return local_ret;
  }

  /*!
   * @brief get_configuration_parameter_values 
   */ 
  ::SDOPackage::NVList ConfigurationProxy::get_configuration_parameter_values()
      throw (::SDOPackage::NotAvailable,
             ::SDOPackage::InternalError)
  {
    // Convert Local to CORBA.
    // (The direction of the argument is 'in' or 'inout'.)

    // Execute the method. 
    ::SDOPackage::NVList* corba_ret;
    ::SDOPackage::NVList local_ret;
    corba_ret = m_obj->get_configuration_parameter_values();

    // Convert CORBA to Local.
    // (The direction of the argument is 'out' or 'inout'.)

    // Generate the return value.
    corba_to_local(*corba_ret, local_ret);
    delete corba_ret; 
    return local_ret;
  }

  /*!
   * @brief get_configuration_parameter_value 
   */ 
  ::std::string ConfigurationProxy::get_configuration_parameter_value(const ::std::string& name)
      throw (::SDOPackage::InvalidParameter,
             ::SDOPackage::NotAvailable,
             ::SDOPackage::InternalError)
  {
    // Convert Local to CORBA.
    // (The direction of the argument is 'in' or 'inout'.)
    char* _name;
    local_to_corba(name, _name);

    // Execute the method. 
    ::CORBA::Any* corba_ret;
    ::std::string local_ret;
    corba_ret = m_obj->get_configuration_parameter_value(_name);

    // Convert CORBA to Local.
    // (The direction of the argument is 'out' or 'inout'.)

    // Generate the return value.
    corba_to_local(*corba_ret, local_ret);
    delete corba_ret; 
    return local_ret;
  }

  /*!
   * @brief set_configuration_parameter 
   */ 
  bool ConfigurationProxy::set_configuration_parameter(const ::std::string& name, const ::std::string& value)
      throw (::SDOPackage::InvalidParameter,
             ::SDOPackage::NotAvailable,
             ::SDOPackage::InternalError)
  {
    // Convert Local to CORBA.
    // (The direction of the argument is 'in' or 'inout'.)
    char* _name;
    ::CORBA::Any _value;
    local_to_corba(name, _name);
    local_to_corba(value, _value);

    // Execute the method. 
    ::CORBA::Boolean corba_ret;
    bool local_ret;
    corba_ret = m_obj->set_configuration_parameter(_name, _value);

    // Convert CORBA to Local.
    // (The direction of the argument is 'out' or 'inout'.)

    // Generate the return value.
//    local_ret = corba_ret;
    corba_to_local(corba_ret, local_ret);
    return local_ret;
  }

  /*!
   * @brief get_configuration_sets 
   */ 
  ::SDOPackage::ConfigurationSetList ConfigurationProxy::get_configuration_sets()
      throw (::SDOPackage::NotAvailable,
             ::SDOPackage::InternalError)
  {
    // Convert Local to CORBA.
    // (The direction of the argument is 'in' or 'inout'.)

    // Execute the method. 
    ::SDOPackage::ConfigurationSetList* corba_ret;
    ::SDOPackage::ConfigurationSetList local_ret;
    corba_ret = m_obj->get_configuration_sets();

    // Convert CORBA to Local.
    // (The direction of the argument is 'out' or 'inout'.)

    // Generate the return value.
    corba_to_local(*corba_ret, local_ret);
    delete corba_ret; 
    return local_ret;
  }

  /*!
   * @brief get_configuration_set 
   */ 
  ::SDOPackage::ConfigurationSet ConfigurationProxy::get_configuration_set(const ::std::string& config_id)
      throw (::SDOPackage::NotAvailable,
             ::SDOPackage::InternalError)
  {
    // Convert Local to CORBA.
    // (The direction of the argument is 'in' or 'inout'.)
    char* _config_id;
    local_to_corba(config_id, _config_id);

    // Execute the method. 
    ::SDOPackage::ConfigurationSet* corba_ret;
    ::SDOPackage::ConfigurationSet local_ret;
    corba_ret = m_obj->get_configuration_set(_config_id);

    // Convert CORBA to Local.
    // (The direction of the argument is 'out' or 'inout'.)

    // Generate the return value.
    corba_to_local(*corba_ret, local_ret);
    delete corba_ret; 
    return local_ret;
  }

  /*!
   * @brief set_configuration_set_values 
   */ 
  bool ConfigurationProxy::set_configuration_set_values(const ::std::string& config_id, const ::SDOPackage::ConfigurationSet& configuration_set)
      throw (::SDOPackage::InvalidParameter,
             ::SDOPackage::NotAvailable,
             ::SDOPackage::InternalError)
  {
    // Convert Local to CORBA.
    // (The direction of the argument is 'in' or 'inout'.)
    char* _config_id;
    ::SDOPackage::ConfigurationSet _configuration_set;
    local_to_corba(config_id, _config_id);
    local_to_corba(configuration_set, _configuration_set);

    // Execute the method. 
    ::CORBA::Boolean corba_ret;
    bool local_ret;
    corba_ret = m_obj->set_configuration_set_values(_config_id, _configuration_set);

    // Convert CORBA to Local.
    // (The direction of the argument is 'out' or 'inout'.)

    // Generate the return value.
//    local_ret = corba_ret;
    corba_to_local(corba_ret, local_ret);
    return local_ret;
  }

  /*!
   * @brief get_active_configuration_set 
   */ 
  ::SDOPackage::ConfigurationSet ConfigurationProxy::get_active_configuration_set()
      throw (::SDOPackage::NotAvailable,
             ::SDOPackage::InternalError)
  {
    // Convert Local to CORBA.
    // (The direction of the argument is 'in' or 'inout'.)

    // Execute the method. 
    ::SDOPackage::ConfigurationSet* corba_ret;
    ::SDOPackage::ConfigurationSet local_ret;
    corba_ret = m_obj->get_active_configuration_set();

    // Convert CORBA to Local.
    // (The direction of the argument is 'out' or 'inout'.)

    // Generate the return value.
    corba_to_local(*corba_ret, local_ret);
    delete corba_ret; 
    return local_ret;
  }

  /*!
   * @brief add_configuration_set 
   */ 
  bool ConfigurationProxy::add_configuration_set(const ::SDOPackage::ConfigurationSet& configuration_set)
      throw (::SDOPackage::InvalidParameter,
             ::SDOPackage::NotAvailable,
             ::SDOPackage::InternalError)
  {
    // Convert Local to CORBA.
    // (The direction of the argument is 'in' or 'inout'.)
    ::SDOPackage::ConfigurationSet _configuration_set;
    local_to_corba(configuration_set, _configuration_set);

    // Execute the method. 
    ::CORBA::Boolean corba_ret;
    bool local_ret;
    corba_ret = m_obj->add_configuration_set(_configuration_set);

    // Convert CORBA to Local.
    // (The direction of the argument is 'out' or 'inout'.)

    // Generate the return value.
//    local_ret = corba_ret;
    corba_to_local(corba_ret, local_ret);
    return local_ret;
  }

  /*!
   * @brief remove_configuration_set 
   */ 
  bool ConfigurationProxy::remove_configuration_set(const ::std::string& config_id)
      throw (::SDOPackage::InvalidParameter,
             ::SDOPackage::NotAvailable,
             ::SDOPackage::InternalError)
  {
    // Convert Local to CORBA.
    // (The direction of the argument is 'in' or 'inout'.)
    char* _config_id;
    local_to_corba(config_id, _config_id);

    // Execute the method. 
    ::CORBA::Boolean corba_ret;
    bool local_ret;
    corba_ret = m_obj->remove_configuration_set(_config_id);

    // Convert CORBA to Local.
    // (The direction of the argument is 'out' or 'inout'.)

    // Generate the return value.
//    local_ret = corba_ret;
    corba_to_local(corba_ret, local_ret);
    return local_ret;
  }

  /*!
   * @brief activate_configuration_set 
   */ 
  bool ConfigurationProxy::activate_configuration_set(const ::std::string& config_id)
      throw (::SDOPackage::InvalidParameter,
             ::SDOPackage::NotAvailable,
             ::SDOPackage::InternalError)
  {
    // Convert Local to CORBA.
    // (The direction of the argument is 'in' or 'inout'.)
    char* _config_id;
    local_to_corba(config_id, _config_id);

    // Execute the method. 
    ::CORBA::Boolean corba_ret;
    bool local_ret;
    corba_ret = m_obj->activate_configuration_set(_config_id);

    // Convert CORBA to Local.
    // (The direction of the argument is 'out' or 'inout'.)

    // Generate the return value.
//    local_ret = corba_ret;
    corba_to_local(corba_ret, local_ret);
    return local_ret;
  }

}; // namespace SDOPackage 

extern "C"
{
  void ConfigurationProxyCORBAInit(coil::Properties& prop)
  {
    doil::CORBA::CORBAManager& mgr(doil::CORBA::CORBAManager::instance());
    mgr.registerProxyFactory("ConfigurationProxy",
                        doil::New< ::SDOPackage::ConfigurationProxy >,
                        doil::Delete< ::SDOPackage::ConfigurationProxy >);
  }
};

