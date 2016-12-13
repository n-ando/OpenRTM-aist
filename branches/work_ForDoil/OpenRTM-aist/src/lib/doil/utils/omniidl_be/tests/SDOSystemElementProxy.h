// -*- C++ -*-
/*!
 * @file SDOSystemElementProxy.h 
 * @brief SDOSystemElementProxy CORBA proxy for doil
 * @date $Date$
 * @author This file was automatically generated from SDOPackage.idl 
 *         by omniidl/doil backend
 *
 * $Id$
 */
#ifndef SDOPACKAGE_SDOSYSTEMELEMENTPROXY_H 
#define SDOPACKAGE_SDOSYSTEMELEMENTPROXY_H 

#include <coil/Properties.h>
#include <coil/Mutex.h>
#include <coil/Guard.h>
#include <doil/corba/CORBAManager.h>
#include <doil/corba/CORBAProxyBase.h>
#include <ISDOSystemElement.h>
#include <rtc/corba/idl/SDOPackageSkel.h>


namespace SDOPackage 
{
namespace CORBA 
{

  class SDOSystemElementProxy 
  : public virtual ::doil::CORBA::CORBAProxyBase,
    public virtual ::SDOPackage::Local::ISDOSystemElement
  {
    typedef coil::Mutex Mutex;
    typedef coil::Guard<Mutex> Guard;
  public:
    SDOSystemElementProxy(::CORBA::Object_ptr obj);
    virtual ~SDOSystemElementProxy();

    virtual ::SDOPackage::Local::OrganizationList get_owned_organizations()
      throw (::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError);



    const char* id() {return "SDOSystemElement";}
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
    ::SDOPackage::SDOSystemElement_ptr m_obj;
  private:
    std::string m_name;
    Mutex m_refcountMutex;
    int m_refcount;
  };

}; // namespace CORBA
}; // namespace SDOPackage 

#ifndef SDOPACKAGE_SDOSYSTEMELEMENTSERVANT_H 


#endif // SDOPACKAGE_SDOSYSTEMELEMENTSERVANT_H

extern "C"
{
  void SDOSystemElementProxyCORBAInit(coil::Properties& prop);
};

#endif // SDOPACKAGE_SDOSYSTEMELEMENTPROXY_H
