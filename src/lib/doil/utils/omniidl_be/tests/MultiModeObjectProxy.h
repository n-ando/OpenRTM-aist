// -*- C++ -*-
/*!
 * @file MultiModeObjectProxy.h 
 * @brief MultiModeObjectProxy CORBA proxy for doil
 * @date $Date$
 * @author This file was automatically generated from RTC.idl 
 *         by omniidl/doil backend
 *
 * $Id$
 */
#ifndef RTC_MULTIMODEOBJECTPROXY_H 
#define RTC_MULTIMODEOBJECTPROXY_H 

#include <coil/Properties.h>
#include <coil/Mutex.h>
#include <coil/Guard.h>
#include <doil/corba/CORBAManager.h>
#include <doil/corba/CORBAProxyBase.h>
#include <IMultiModeObject.h>
#include <LightweightRTObjectProxy.h>
#include <ModeCapableProxy.h>
#include <MultiModeComponentActionProxy.h>
#include <ComponentActionProxy.h>
#include <SDOPackageTypes.h>
#include <rtc/corba/idl/RTCSkel.h>


namespace RTC 
{
namespace CORBA 
{

  class MultiModeObjectProxy 
  : public virtual ::doil::CORBA::CORBAProxyBase,
    public virtual ::RTC::CORBA::LightweightRTObjectProxy,
    public virtual ::RTC::CORBA::ModeCapableProxy,
    public virtual ::RTC::CORBA::MultiModeComponentActionProxy,
    public virtual ::RTC::CORBA::ComponentActionProxy,
    public virtual ::RTC::Local::IMultiModeObject
  {
    typedef coil::Mutex Mutex;
    typedef coil::Guard<Mutex> Guard;
  public:
    MultiModeObjectProxy(::CORBA::Object_ptr obj);
    virtual ~MultiModeObjectProxy();


    const char* id() {return "MultiModeObject";}
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
    ::RTC::MultiModeObject_ptr m_obj;
  private:
    std::string m_name;
    Mutex m_refcountMutex;
    int m_refcount;
  };

}; // namespace CORBA
}; // namespace RTC 

#ifndef RTC_MULTIMODEOBJECTSERVANT_H 


#endif // RTC_MULTIMODEOBJECTSERVANT_H

extern "C"
{
  void MultiModeObjectProxyCORBAInit(coil::Properties& prop);
};

#endif // RTC_MULTIMODEOBJECTPROXY_H
