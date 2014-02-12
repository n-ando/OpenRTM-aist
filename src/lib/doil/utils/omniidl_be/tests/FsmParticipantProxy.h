// -*- C++ -*-
/*!
 * @file FsmParticipantProxy.h 
 * @brief FsmParticipantProxy CORBA proxy for doil
 * @date $Date$
 * @author This file was automatically generated from RTC.idl 
 *         by omniidl/doil backend
 *
 * $Id$
 */
#ifndef RTC_FSMPARTICIPANTPROXY_H 
#define RTC_FSMPARTICIPANTPROXY_H 

#include <coil/Properties.h>
#include <coil/Mutex.h>
#include <coil/Guard.h>
#include <doil/corba/CORBAManager.h>
#include <doil/corba/CORBAProxyBase.h>
#include <IFsmParticipant.h>
#include <LightweightRTObjectProxy.h>
#include <FsmParticipantActionProxy.h>
#include <ComponentActionProxy.h>
#include <SDOPackageTypes.h>
#include <rtc/corba/idl/RTCSkel.h>


namespace RTC 
{
namespace CORBA 
{

  class FsmParticipantProxy 
  : public virtual ::doil::CORBA::CORBAProxyBase,
    public virtual ::RTC::CORBA::LightweightRTObjectProxy,
    public virtual ::RTC::CORBA::FsmParticipantActionProxy,
    public virtual ::RTC::CORBA::ComponentActionProxy,
    public virtual ::RTC::Local::IFsmParticipant
  {
    typedef coil::Mutex Mutex;
    typedef coil::Guard<Mutex> Guard;
  public:
    FsmParticipantProxy(::CORBA::Object_ptr obj);
    virtual ~FsmParticipantProxy();


    const char* id() {return "FsmParticipant";}
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
    ::RTC::FsmParticipant_ptr m_obj;
  private:
    std::string m_name;
    Mutex m_refcountMutex;
    int m_refcount;
  };

}; // namespace CORBA
}; // namespace RTC 

#ifndef RTC_FSMPARTICIPANTSERVANT_H 


#endif // RTC_FSMPARTICIPANTSERVANT_H

extern "C"
{
  void FsmParticipantProxyCORBAInit(coil::Properties& prop);
};

#endif // RTC_FSMPARTICIPANTPROXY_H
