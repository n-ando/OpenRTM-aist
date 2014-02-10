// -*- C++ -*-
/*!
 * @file ConfigurationProxy.h 
 * @brief ConfigurationProxy CORBA proxy for doil
 * @date $Date$
 * @author This file was automatically generated from SDOPackage.idl 
 *         by omniidl/doil backend
 *
 * $Id$
 */
#ifndef SDOPACKAGE_CONFIGURATIONPROXY_H 
#define SDOPACKAGE_CONFIGURATIONPROXY_H 

#include <coil/Properties.h>
#include <coil/Mutex.h>
#include <coil/Guard.h>
#include <doil/corba/CORBAManager.h>
#include <doil/corba/CORBAProxyBase.h>
#include <IConfiguration.h>
#include <rtc/corba/idl/SDOPackageSkel.h>

namespace SDOPackage 
{
namespace CORBA 
{

  class ConfigurationProxy 
  : public virtual ::doil::CORBA::CORBAProxyBase,
    public virtual ::SDOPackage::Local::IConfiguration
  {
    typedef coil::Mutex Mutex;
    typedef coil::Guard<Mutex> Guard;
  public:
    ConfigurationProxy(::CORBA::Object_ptr obj);
    virtual ~ConfigurationProxy();

    virtual bool set_device_profile(const ::SDOPackage::Local::DeviceProfile& dProfile)
      throw (::SDOPackage::Local::InvalidParameter,
             ::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError);


    virtual bool set_service_profile(const ::SDOPackage::Local::ServiceProfile& sProfile)
      throw (::SDOPackage::Local::InvalidParameter,
             ::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError);


    virtual bool add_organization(const ::SDOPackage::Local::IOrganization* org)
      throw (::SDOPackage::Local::InvalidParameter,
             ::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError);


    virtual bool remove_service_profile(const ::std::string& id)
      throw (::SDOPackage::Local::InvalidParameter,
             ::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError);


    virtual bool remove_organization(const ::std::string& organization_id)
      throw (::SDOPackage::Local::InvalidParameter,
             ::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError);


    virtual ::SDOPackage::Local::ParameterList get_configuration_parameters()
      throw (::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError);


    virtual ::SDOPackage::Local::NVList get_configuration_parameter_values()
      throw (::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError);


    virtual ::std::string get_configuration_parameter_value(const ::std::string& name)
      throw (::SDOPackage::Local::InvalidParameter,
             ::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError);


    virtual bool set_configuration_parameter(const ::std::string& name, const ::std::string& value)
      throw (::SDOPackage::Local::InvalidParameter,
             ::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError);


    virtual ::SDOPackage::Local::ConfigurationSetList get_configuration_sets()
      throw (::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError);


    virtual ::SDOPackage::Local::ConfigurationSet get_configuration_set(const ::std::string& config_id)
      throw (::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError);


    virtual bool set_configuration_set_values(const ::std::string& config_id, const ::SDOPackage::Local::ConfigurationSet& configuration_set)
      throw (::SDOPackage::Local::InvalidParameter,
             ::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError);


    virtual ::SDOPackage::Local::ConfigurationSet get_active_configuration_set()
      throw (::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError);


    virtual bool add_configuration_set(const ::SDOPackage::Local::ConfigurationSet& configuration_set)
      throw (::SDOPackage::Local::InvalidParameter,
             ::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError);


    virtual bool remove_configuration_set(const ::std::string& config_id)
      throw (::SDOPackage::Local::InvalidParameter,
             ::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError);


    virtual bool activate_configuration_set(const ::std::string& config_id)
      throw (::SDOPackage::Local::InvalidParameter,
             ::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError);



    const char* id() {return "Configuration";}
    const char* name() {return m_name.c_str();}
    void incRef()
    {
      Guard guard(m_refcountMutex);
      ++m_refcount;
    }
    void decRef()
    {
      Guard guard(m_refcountMutex);
      --m_refcount;
      if (m_refcount == 0)
        delete this;
    }

  private:
    ::SDOPackage::Configuration_ptr m_obj;
  private:
    std::string m_name;
    Mutex m_refcountMutex;
    int m_refcount;
  };

}; // namespace CORBA
}; // namespace SDOPackage 

#ifndef SDOPACKAGE_CONFIGURATIONSERVANT_H 


#endif // SDOPACKAGE_CONFIGURATIONSERVANT_H

extern "C"
{
  void ConfigurationProxyCORBAInit(coil::Properties& prop);
};

#endif // SDOPACKAGE_CONFIGURATIONPROXY_H
