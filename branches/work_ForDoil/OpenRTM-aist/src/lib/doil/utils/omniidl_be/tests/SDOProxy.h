// -*- C++ -*-
/*!
 * @file SDOProxy.h 
 * @brief SDOProxy CORBA proxy for doil
 * @date $Date$
 * @author This file was automatically generated from SDOPackage.idl 
 *         by omniidl/doil backend
 *
 * $Id$
 */
#ifndef SDOPACKAGE_SDOPROXY_H 
#define SDOPACKAGE_SDOPROXY_H 

#include <coil/Properties.h>
#include <coil/Mutex.h>
#include <coil/Guard.h>
#include <doil/corba/CORBAManager.h>
#include <doil/corba/CORBAProxyBase.h>
#include <ISDO.h>
#include <SDOSystemElementProxy.h>
#include <rtc/corba/idl/SDOPackageSkel.h>


namespace SDOPackage 
{
namespace CORBA 
{

  class SDOProxy 
  : public virtual ::doil::CORBA::CORBAProxyBase,
    public virtual ::SDOPackage::CORBA::SDOSystemElementProxy,
    public virtual ::SDOPackage::Local::ISDO
  {
    typedef coil::Mutex Mutex;
    typedef coil::Guard<Mutex> Guard;
  public:
    SDOProxy(::CORBA::Object_ptr obj);
    virtual ~SDOProxy();

    virtual ::std::string get_sdo_id()
      throw (::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError);


    virtual ::std::string get_sdo_type()
      throw (::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError);


    virtual ::SDOPackage::Local::DeviceProfile get_device_profile()
      throw (::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError);


    virtual ::SDOPackage::Local::ServiceProfileList get_service_profiles()
      throw (::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError);


    virtual ::SDOPackage::Local::ServiceProfile get_service_profile(const ::std::string& id)
      throw (::SDOPackage::Local::InvalidParameter,
             ::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError);


    virtual ::SDOPackage::Local::ISDOService* get_sdo_service(const ::std::string& id)
      throw (::SDOPackage::Local::InvalidParameter,
             ::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError);


    virtual ::SDOPackage::Local::IConfiguration* get_configuration()
      throw (::SDOPackage::Local::InterfaceNotImplemented,
             ::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError);


    virtual ::SDOPackage::Local::IMonitoring* get_monitoring()
      throw (::SDOPackage::Local::InterfaceNotImplemented,
             ::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError);


    virtual ::SDOPackage::Local::OrganizationList get_organizations()
      throw (::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError);


    virtual ::SDOPackage::Local::NVList get_status_list()
      throw (::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError);


    virtual ::std::string get_status(const ::std::string& nme)
      throw (::SDOPackage::Local::InvalidParameter,
             ::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError);



    const char* id() {return "SDO";}
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
    ::SDOPackage::SDO_ptr m_obj;
  private:
    std::string m_name;
    Mutex m_refcountMutex;
    int m_refcount;
  };

}; // namespace CORBA
}; // namespace SDOPackage 

#ifndef SDOPACKAGE_SDOSERVANT_H 


#endif // SDOPACKAGE_SDOSERVANT_H

extern "C"
{
  void SDOProxyCORBAInit(coil::Properties& prop);
};

#endif // SDOPACKAGE_SDOPROXY_H
