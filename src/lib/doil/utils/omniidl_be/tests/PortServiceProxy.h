// -*- C++ -*-
/*!
 * @file PortServiceProxy.h 
 * @brief PortServiceProxy CORBA proxy for doil
 * @date $Date$
 * @author This file was automatically generated from RTC.idl 
 *         by omniidl/doil backend
 *
 * $Id$
 */
#ifndef RTC_PORTSERVICEPROXY_H 
#define RTC_PORTSERVICEPROXY_H 

#include <coil/Properties.h>
#include <coil/Mutex.h>
#include <coil/Guard.h>
#include <doil/corba/CORBAManager.h>
#include <doil/corba/CORBAProxyBase.h>
#include <IPortService.h>
#include <SDOServiceProxy.h>
#include <SDOPackageTypes.h>
#include <rtc/corba/idl/RTCSkel.h>


namespace RTC 
{
namespace CORBA 
{

  class PortServiceProxy 
  : public virtual ::doil::CORBA::CORBAProxyBase,
    public virtual ::SDOPackage::CORBA::SDOServiceProxy,
    public virtual ::RTC::Local::IPortService
  {
    typedef coil::Mutex Mutex;
    typedef coil::Guard<Mutex> Guard;
  public:
    PortServiceProxy(::CORBA::Object_ptr obj);
    virtual ~PortServiceProxy();

    virtual ::RTC::Local::PortProfile get_port_profile()
      throw ();


    virtual ::RTC::Local::ConnectorProfileList get_connector_profiles()
      throw ();


    virtual ::RTC::Local::ConnectorProfile get_connector_profile(const ::std::string& connector_id)
      throw ();


    virtual ::RTC::Local::ReturnCode_t connect(::RTC::Local::ConnectorProfile& connector_profile)
      throw ();


    virtual ::RTC::Local::ReturnCode_t disconnect(const ::std::string& connector_id)
      throw ();


    virtual ::RTC::Local::ReturnCode_t disconnect_all()
      throw ();


    virtual ::RTC::Local::ReturnCode_t notify_connect(::RTC::Local::ConnectorProfile& connector_profile)
      throw ();


    virtual ::RTC::Local::ReturnCode_t notify_disconnect(const ::std::string& connector_id)
      throw ();



    const char* id() {return "PortService";}
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
    ::RTC::PortService_ptr m_obj;
  private:
    std::string m_name;
    Mutex m_refcountMutex;
    int m_refcount;
  };

}; // namespace CORBA
}; // namespace RTC 

#ifndef RTC_PORTSERVICESERVANT_H 


#endif // RTC_PORTSERVICESERVANT_H

extern "C"
{
  void PortServiceProxyCORBAInit(coil::Properties& prop);
};

#endif // RTC_PORTSERVICEPROXY_H
