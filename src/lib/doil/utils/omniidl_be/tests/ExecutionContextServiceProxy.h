// -*- C++ -*-
/*!
 * @file ExecutionContextServiceProxy.h 
 * @brief ExecutionContextServiceProxy CORBA proxy for doil
 * @date $Date$
 * @author This file was automatically generated from RTC.idl 
 *         by omniidl/doil backend
 *
 * $Id$
 */
#ifndef RTC_EXECUTIONCONTEXTSERVICEPROXY_H 
#define RTC_EXECUTIONCONTEXTSERVICEPROXY_H 

#include <coil/Properties.h>
#include <coil/Mutex.h>
#include <coil/Guard.h>
#include <doil/corba/CORBAManager.h>
#include <doil/corba/CORBAProxyBase.h>
#include <IExecutionContextService.h>
#include <ExecutionContextProxy.h>
#include <SDOServiceProxy.h>
#include <SDOPackageTypes.h>


namespace RTC 
{
namespace CORBA 
{

  class ExecutionContextServiceProxy 
  : public virtual ::doil::CORBA::CORBAProxyBase,
    public virtual ::RTC::CORBA::ExecutionContextProxy,
    public virtual ::SDOPackage::CORBA::SDOServiceProxy,
    public virtual ::RTC::Local::IExecutionContextService
  {
    typedef coil::Mutex Mutex;
    typedef coil::Guard<Mutex> Guard;
  public:
    ExecutionContextServiceProxy(::CORBA::Object_ptr obj);
    virtual ~ExecutionContextServiceProxy();

    virtual ::RTC::Local::ExecutionContextProfile get_profile()
      throw ();



    const char* id() {return "ExecutionContextService";}
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
    ::RTC::ExecutionContextService_ptr m_obj;
  private:
    std::string m_name;
    Mutex m_refcountMutex;
    int m_refcount;
  };

}; // namespace CORBA
}; // namespace RTC 

#ifndef RTC_EXECUTIONCONTEXTSERVICESERVANT_H 


#endif // RTC_EXECUTIONCONTEXTSERVICESERVANT_H

extern "C"
{
  void ExecutionContextServiceProxyCORBAInit(coil::Properties& prop);
};

#endif // RTC_EXECUTIONCONTEXTSERVICEPROXY_H
