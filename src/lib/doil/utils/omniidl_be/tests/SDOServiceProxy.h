// -*- C++ -*-
/*!
 * @file SDOServiceProxy.h 
 * @brief SDOServiceProxy CORBA proxy for doil
 * @date $Date$
 * @author This file was automatically generated from SDOPackage.idl 
 *         by omniidl/doil backend
 *
 * $Id$
 */
#ifndef SDOPACKAGE_SDOSERVICEPROXY_H 
#define SDOPACKAGE_SDOSERVICEPROXY_H 

#include <coil/Properties.h>
#include <coil/Mutex.h>
#include <coil/Guard.h>
#include <doil/corba/CORBAManager.h>
#include <doil/corba/CORBAProxyBase.h>
#include <ISDOService.h>
#include <rtc/corba/idl/SDOPackageSkel.h>


namespace SDOPackage 
{
namespace CORBA 
{

  class SDOServiceProxy 
  : public virtual ::doil::CORBA::CORBAProxyBase,
    public virtual ::SDOPackage::Local::ISDOService
  {
    typedef coil::Mutex Mutex;
    typedef coil::Guard<Mutex> Guard;
  public:
    SDOServiceProxy(::CORBA::Object_ptr obj);
    virtual ~SDOServiceProxy();


    const char* id() {return "SDOService";}
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
    ::SDOPackage::SDOService_ptr m_obj;
  private:
    std::string m_name;
    Mutex m_refcountMutex;
    int m_refcount;
  };

}; // namespace CORBA
}; // namespace SDOPackage 

#ifndef SDOPACKAGE_SDOSERVICESERVANT_H 


#endif // SDOPACKAGE_SDOSERVICESERVANT_H

extern "C"
{
  void SDOServiceProxyCORBAInit(coil::Properties& prop);
};

#endif // SDOPACKAGE_SDOSERVICEPROXY_H
