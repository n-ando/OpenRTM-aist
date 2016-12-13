// -*- C++ -*-
/*!
 * @file RTObjectProxy.h 
 * @brief RTObjectProxy CORBA proxy for doil
 * @date $Date$
 * @author This file was automatically generated from RTC.idl 
 *         by omniidl/doil backend
 *
 * $Id$
 */
#ifndef RTC_RTOBJECTPROXY_H 
#define RTC_RTOBJECTPROXY_H 

#include <coil/Properties.h>
#include <coil/Mutex.h>
#include <coil/Guard.h>
#include <doil/corba/CORBAManager.h>
#include <doil/corba/CORBAProxyBase.h>
#include <IRTObject.h>
#include <LightweightRTObjectProxy.h>
#include <SDOProxy.h>
#include <ComponentActionProxy.h>
#include <SDOSystemElementProxy.h>
#include <SDOPackageTypes.h>
#include <rtc/corba/idl/RTCSkel.h>


namespace RTC 
{
namespace CORBA 
{

  class RTObjectProxy 
  : public virtual ::doil::CORBA::CORBAProxyBase,
    public virtual ::RTC::CORBA::LightweightRTObjectProxy,
    public virtual ::SDOPackage::CORBA::SDOProxy,
    public virtual ::RTC::CORBA::ComponentActionProxy,
    public virtual ::SDOPackage::CORBA::SDOSystemElementProxy,
    public virtual ::RTC::Local::IRTObject
  {
    typedef coil::Mutex Mutex;
    typedef coil::Guard<Mutex> Guard;
  public:
    RTObjectProxy(::CORBA::Object_ptr obj);
    virtual ~RTObjectProxy();

    virtual ::RTC::Local::ComponentProfile get_component_profile()
      throw ();


    virtual ::RTC::Local::PortServiceList get_ports()
      throw ();



    const char* id() {return "RTObject";}
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
    ::RTC::RTObject_ptr m_obj;
  private:
    std::string m_name;
    Mutex m_refcountMutex;
    int m_refcount;
  };

}; // namespace CORBA
}; // namespace RTC 

#ifndef RTC_RTOBJECTSERVANT_H 


#endif // RTC_RTOBJECTSERVANT_H

extern "C"
{
  void RTObjectProxyCORBAInit(coil::Properties& prop);
};

#endif // RTC_RTOBJECTPROXY_H
