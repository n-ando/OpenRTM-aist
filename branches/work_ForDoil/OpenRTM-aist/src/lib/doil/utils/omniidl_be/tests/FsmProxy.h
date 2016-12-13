// -*- C++ -*-
/*!
 * @file FsmProxy.h 
 * @brief FsmProxy CORBA proxy for doil
 * @date $Date$
 * @author This file was automatically generated from RTC.idl 
 *         by omniidl/doil backend
 *
 * $Id$
 */
#ifndef RTC_FSMPROXY_H 
#define RTC_FSMPROXY_H 

#include <coil/Properties.h>
#include <coil/Mutex.h>
#include <coil/Guard.h>
#include <doil/corba/CORBAManager.h>
#include <doil/corba/CORBAProxyBase.h>
#include <IFsm.h>
#include <LightweightRTObjectProxy.h>
#include <ComponentActionProxy.h>
#include <SDOPackageTypes.h>
#include <rtc/corba/idl/RTCSkel.h>


namespace RTC 
{
namespace CORBA
{

  class FsmProxy 
  : public virtual ::doil::CORBA::CORBAProxyBase,
    public virtual ::RTC::CORBA::LightweightRTObjectProxy,
    public virtual ::RTC::CORBA::ComponentActionProxy,
    public virtual ::RTC::Local::IFsm
  {
    typedef coil::Mutex Mutex;
    typedef coil::Guard<Mutex> Guard;
  public:
    FsmProxy(::CORBA::Object_ptr obj);
    virtual ~FsmProxy();


    const char* id() {return "Fsm";}
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
    ::RTC::Fsm_ptr m_obj;
  private:
    std::string m_name;
    Mutex m_refcountMutex;
    int m_refcount;
  };

}; // namespace CORBA
}; // namespace RTC 

#ifndef RTC_FSMSERVANT_H 


#endif // RTC_FSMSERVANT_H

extern "C"
{
  void FsmProxyCORBAInit(coil::Properties& prop);
};

#endif // RTC_FSMPROXY_H
