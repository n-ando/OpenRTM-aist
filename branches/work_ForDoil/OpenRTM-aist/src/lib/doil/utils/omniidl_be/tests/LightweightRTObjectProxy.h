// -*- C++ -*-
/*!
 * @file LightweightRTObjectProxy.h 
 * @brief LightweightRTObjectProxy CORBA proxy for doil
 * @date $Date$
 * @author This file was automatically generated from RTC.idl 
 *         by omniidl/doil backend
 *
 * $Id$
 */
#ifndef RTC_LIGHTWEIGHTRTOBJECTPROXY_H 
#define RTC_LIGHTWEIGHTRTOBJECTPROXY_H 

#include <coil/Properties.h>
#include <coil/Mutex.h>
#include <coil/Guard.h>
#include <doil/corba/CORBAManager.h>
#include <doil/corba/CORBAProxyBase.h>
#include <ILightweightRTObject.h>
#include <ComponentActionProxy.h>
#include <SDOPackageTypes.h>


namespace RTC 
{
namespace CORBA 
{

  class LightweightRTObjectProxy 
  : public virtual ::doil::CORBA::CORBAProxyBase,
    public virtual ::RTC::CORBA::ComponentActionProxy,
    public virtual ::RTC::Local::ILightweightRTObject
  {
    typedef coil::Mutex Mutex;
    typedef coil::Guard<Mutex> Guard;
  public:
    LightweightRTObjectProxy(::CORBA::Object_ptr obj);
    virtual ~LightweightRTObjectProxy();

    virtual ::RTC::Local::ReturnCode_t initialize()
      throw ();


    virtual ::RTC::Local::ReturnCode_t finalize()
      throw ();


    virtual bool is_alive(const ::RTC::Local::IExecutionContext* exec_context)
      throw ();


    virtual ::RTC::Local::ReturnCode_t exit()
      throw ();


    virtual ::RTC::Local::ExecutionContextHandle_t attach_context(const ::RTC::Local::IExecutionContext* exec_context)
      throw ();


    virtual ::RTC::Local::ReturnCode_t detach_context(::RTC::Local::ExecutionContextHandle_t exec_handle)
      throw ();


    virtual ::RTC::Local::IExecutionContext* get_context(::RTC::Local::ExecutionContextHandle_t exec_handle)
      throw ();


    virtual ::RTC::Local::ExecutionContextList get_owned_contexts()
      throw ();


    virtual ::RTC::Local::ExecutionContextList get_participating_contexts()
      throw ();


    virtual ::RTC::Local::ExecutionContextHandle_t get_context_handle(const ::RTC::Local::IExecutionContext* cxt)
      throw ();



    const char* id() {return "LightweightRTObject";}
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
    ::RTC::LightweightRTObject_ptr m_obj;
  private:
    std::string m_name;
    Mutex m_refcountMutex;
    int m_refcount;
  };

}; // namespace CORBA
}; // namespace RTC 

#ifndef RTC_LIGHTWEIGHTRTOBJECTSERVANT_H 


#endif // RTC_LIGHTWEIGHTRTOBJECTSERVANT_H

extern "C"
{
  void LightweightRTObjectProxyCORBAInit(coil::Properties& prop);
};

#endif // RTC_LIGHTWEIGHTRTOBJECTPROXY_H
