// -*- C++ -*-
/*!
 * @file ComponentActionProxy.h 
 * @brief ComponentActionProxy CORBA proxy for doil
 * @date $Date$
 * @author This file was automatically generated from RTC.idl 
 *         by omniidl/doil backend
 *
 * $Id$
 */
#ifndef RTC_COMPONENTACTIONPROXY_H 
#define RTC_COMPONENTACTIONPROXY_H 

#include <coil/Properties.h>
#include <coil/Mutex.h>
#include <coil/Guard.h>
#include <doil/corba/CORBAManager.h>
#include <doil/corba/CORBAProxyBase.h>
#include <IComponentAction.h>
#include <SDOPackageTypes.h>
#include <rtc/corba/idl/RTCSkel.h>


namespace RTC 
{
namespace CORBA 
{

  class ComponentActionProxy 
  : public virtual ::doil::CORBA::CORBAProxyBase,
    public virtual ::RTC::Local::IComponentAction
  {
    typedef coil::Mutex Mutex;
    typedef coil::Guard<Mutex> Guard;
  public:
    ComponentActionProxy(::CORBA::Object_ptr obj);
    virtual ~ComponentActionProxy();

    virtual ::RTC::Local::ReturnCode_t on_initialize()
      throw ();


    virtual ::RTC::Local::ReturnCode_t on_finalize()
      throw ();


    virtual ::RTC::Local::ReturnCode_t on_startup(::RTC::Local::ExecutionContextHandle_t exec_handle)
      throw ();


    virtual ::RTC::Local::ReturnCode_t on_shutdown(::RTC::Local::ExecutionContextHandle_t exec_handle)
      throw ();


    virtual ::RTC::Local::ReturnCode_t on_activated(::RTC::Local::ExecutionContextHandle_t exec_handle)
      throw ();


    virtual ::RTC::Local::ReturnCode_t on_deactivated(::RTC::Local::ExecutionContextHandle_t exec_handle)
      throw ();


    virtual ::RTC::Local::ReturnCode_t on_aborting(::RTC::Local::ExecutionContextHandle_t exec_handle)
      throw ();


    virtual ::RTC::Local::ReturnCode_t on_error(::RTC::Local::ExecutionContextHandle_t exec_handle)
      throw ();


    virtual ::RTC::Local::ReturnCode_t on_reset(::RTC::Local::ExecutionContextHandle_t exec_handle)
      throw ();



    const char* id() {return "ComponentAction";}
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
    ::RTC::ComponentAction_ptr m_obj;
  private:
    std::string m_name;
    Mutex m_refcountMutex;
    int m_refcount;
  };

}; // namespace CORBA
}; // namespace RTC 

#ifndef RTC_COMPONENTACTIONSERVANT_H 


#endif // RTC_COMPONENTACTIONSERVANT_H

extern "C"
{
  void ComponentActionProxyCORBAInit(coil::Properties& prop);
};

#endif // RTC_COMPONENTACTIONPROXY_H
