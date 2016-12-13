// -*- C++ -*-
/*!
 * @file FsmObjectProxy.h 
 * @brief FsmObjectProxy CORBA proxy for doil
 * @date $Date$
 * @author This file was automatically generated from RTC.idl 
 *         by omniidl/doil backend
 *
 * $Id$
 */
#ifndef RTC_FSMOBJECTPROXY_H 
#define RTC_FSMOBJECTPROXY_H 

#include <coil/Properties.h>
#include <coil/Mutex.h>
#include <coil/Guard.h>
#include <doil/corba/CORBAManager.h>
#include <doil/corba/CORBAProxyBase.h>
#include <IFsmObject.h>
#include <SDOPackageTypes.h>
#include <rtc/corba/idl/RTCSkel.h>


namespace RTC 
{
namespace CORBA 
{

  class FsmObjectProxy 
  : public virtual ::doil::CORBA::CORBAProxyBase,
    public virtual ::RTC::Local::IFsmObject
  {
    typedef coil::Mutex Mutex;
    typedef coil::Guard<Mutex> Guard;
  public:
    FsmObjectProxy(::CORBA::Object_ptr obj);
    virtual ~FsmObjectProxy();

    virtual ::RTC::Local::ReturnCode_t send_stimulus(const ::std::string& message, ::RTC::Local::ExecutionContextHandle_t exec_handle)
      throw ();



    const char* id() {return "FsmObject";}
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
    ::RTC::FsmObject_ptr m_obj;
  private:
    std::string m_name;
    Mutex m_refcountMutex;
    int m_refcount;
  };

}; // namespace CORBA
}; // namespace RTC 

#ifndef RTC_FSMOBJECTSERVANT_H 


#endif // RTC_FSMOBJECTSERVANT_H

extern "C"
{
  void FsmObjectProxyCORBAInit(coil::Properties& prop);
};

#endif // RTC_FSMOBJECTPROXY_H
