// -*- C++ -*-
/*!
 * @file OrganizationProxy.h 
 * @brief OrganizationProxy CORBA proxy for doil
 * @date $Date$
 * @author This file was automatically generated from SDOPackage.idl 
 *         by omniidl/doil backend
 *
 * $Id$
 */
#ifndef SDOPACKAGE_ORGANIZATIONPROXY_H 
#define SDOPACKAGE_ORGANIZATIONPROXY_H 

#include <coil/Properties.h>
#include <coil/Mutex.h>
#include <coil/Guard.h>
#include <doil/corba/CORBAManager.h>
#include <doil/corba/CORBAProxyBase.h>
#include <IOrganization.h>
#include <rtc/corba/idl/SDOPackageSkel.h>


namespace SDOPackage 
{
namespace CORBA 
{
  class OrganizationProxy 
  : public virtual ::doil::CORBA::CORBAProxyBase,
    public virtual ::SDOPackage::Local::IOrganization
  {
    typedef coil::Mutex Mutex;
    typedef coil::Guard<Mutex> Guard;
  public:
    OrganizationProxy(::CORBA::Object_ptr obj);
    virtual ~OrganizationProxy();

    virtual ::std::string get_organization_id()
      throw (::SDOPackage::Local::InvalidParameter,
             ::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError);


    virtual ::SDOPackage::Local::OrganizationProperty get_organization_property()
      throw (::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError);


    virtual ::std::string get_organization_property_value(const ::std::string& name)
      throw (::SDOPackage::Local::InvalidParameter,
             ::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError);


    virtual bool add_organization_property(const ::SDOPackage::Local::OrganizationProperty& organization_property)
      throw (::SDOPackage::Local::InvalidParameter,
             ::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError);


    virtual bool set_organization_property_value(const ::std::string& name, const ::std::string& value)
      throw (::SDOPackage::Local::InvalidParameter,
             ::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError);


    virtual bool remove_organization_property(const ::std::string& name)
      throw (::SDOPackage::Local::InvalidParameter,
             ::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError);


    virtual ::SDOPackage::Local::ISDOSystemElement* get_owner()
      throw (::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError);


    virtual bool set_owner(const ::SDOPackage::Local::ISDOSystemElement* sdo)
      throw (::SDOPackage::Local::InvalidParameter,
             ::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError);


    virtual ::SDOPackage::Local::SDOList get_members()
      throw (::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError);


    virtual bool set_members(const ::SDOPackage::Local::SDOList& sdos)
      throw (::SDOPackage::Local::InvalidParameter,
             ::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError);


    virtual bool add_members(const ::SDOPackage::Local::SDOList& sdo_list)
      throw (::SDOPackage::Local::InvalidParameter,
             ::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError);


    virtual bool remove_member(const ::std::string& id)
      throw (::SDOPackage::Local::InvalidParameter,
             ::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError);


    virtual ::SDOPackage::Local::DependencyType get_dependency()
      throw (::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError);


    virtual bool set_dependency(::SDOPackage::Local::DependencyType dependency)
      throw (::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError);



    const char* id() {return "Organization";}
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
    ::SDOPackage::Organization_ptr m_obj;
  private:
    std::string m_name;
    Mutex m_refcountMutex;
    int m_refcount;
  };

}; // namespace CORBA
}; // namespace SDOPackage 

#ifndef SDOPACKAGE_ORGANIZATIONSERVANT_H 


#endif // SDOPACKAGE_ORGANIZATIONSERVANT_H

extern "C"
{
  void OrganizationProxyCORBAInit(coil::Properties& prop);
};

#endif // SDOPACKAGE_ORGANIZATIONPROXY_H
