// -*- C++ -*-
/*!
 * @file ExecutionContextProxy.h 
 * @brief ExecutionContextProxy CORBA proxy for doil
 * @date $Date$
 * @author This file was automatically generated from RTC.idl 
 *         by omniidl/doil backend
 *
 * $Id$
 */
#ifndef RTC_EXECUTIONCONTEXTPROXY_H 
#define RTC_EXECUTIONCONTEXTPROXY_H 

#include <coil/Properties.h>
#include <coil/Mutex.h>
#include <coil/Guard.h>
#include <doil/corba/CORBAManager.h>
#include <doil/corba/CORBAProxyBase.h>
#include <IExecutionContext.h>
#include <SDOPackageTypes.h>
#include <rtc/corba/idl/RTCSkel.h>


namespace RTC 
{
namespace CORBA 
{

  class ExecutionContextProxy 
  : public virtual ::doil::CORBA::CORBAProxyBase,
    public virtual ::RTC::Local::IExecutionContext
  {
    typedef coil::Mutex Mutex;
    typedef coil::Guard<Mutex> Guard;
  public:
    ExecutionContextProxy(::CORBA::Object_ptr obj);
    virtual ~ExecutionContextProxy();

    virtual bool is_running()
      throw ();


    virtual ::RTC::Local::ReturnCode_t start()
      throw ();


    virtual ::RTC::Local::ReturnCode_t stop()
      throw ();


    virtual double get_rate()
      throw ();


    virtual ::RTC::Local::ReturnCode_t set_rate(double rate)
      throw ();


    virtual ::RTC::Local::ReturnCode_t add_component(const ::RTC::Local::ILightweightRTObject* comp)
      throw ();


    virtual ::RTC::Local::ReturnCode_t remove_component(const ::RTC::Local::ILightweightRTObject* comp)
      throw ();


    virtual ::RTC::Local::ReturnCode_t activate_component(const ::RTC::Local::ILightweightRTObject* comp)
      throw ();


    virtual ::RTC::Local::ReturnCode_t deactivate_component(const ::RTC::Local::ILightweightRTObject* comp)
      throw ();


    virtual ::RTC::Local::ReturnCode_t reset_component(const ::RTC::Local::ILightweightRTObject* comp)
      throw ();


    virtual ::RTC::Local::LifeCycleState get_component_state(const ::RTC::Local::ILightweightRTObject* comp)
      throw ();


    virtual ::RTC::Local::ExecutionKind get_kind()
      throw ();



    const char* id() {return "ExecutionContext";}
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
    ::RTC::ExecutionContext_ptr m_obj;
  private:
    std::string m_name;
    Mutex m_refcountMutex;
    int m_refcount;
  };

}; // namespace CORBA
}; // namespace RTC 

#ifndef RTC_EXECUTIONCONTEXTSERVANT_H 


#endif // RTC_EXECUTIONCONTEXTSERVANT_H

extern "C"
{
  void ExecutionContextProxyCORBAInit(coil::Properties& prop);
};

#endif // RTC_EXECUTIONCONTEXTPROXY_H
