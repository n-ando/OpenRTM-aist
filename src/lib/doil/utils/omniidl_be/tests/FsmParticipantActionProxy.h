// -*- C++ -*-
/*!
 * @file FsmParticipantActionProxy.h 
 * @brief FsmParticipantActionProxy CORBA proxy for doil
 * @date $Date$
 * @author This file was automatically generated from RTC.idl 
 *         by omniidl/doil backend
 *
 * $Id$
 */
#ifndef RTC_FSMPARTICIPANTACTIONPROXY_H 
#define RTC_FSMPARTICIPANTACTIONPROXY_H 

#include <coil/Properties.h>
#include <coil/Mutex.h>
#include <coil/Guard.h>
#include <doil/corba/CORBAManager.h>
#include <doil/corba/CORBAProxyBase.h>
#include <IFsmParticipantAction.h>
#include <SDOPackageTypes.h>
#include <rtc/corba/idl/RTCSkel.h>


namespace RTC 
{
namespace CORBA
{

  class FsmParticipantActionProxy 
  : public virtual ::doil::CORBA::CORBAProxyBase,
    public virtual ::RTC::Local::IFsmParticipantAction
  {
    typedef coil::Mutex Mutex;
    typedef coil::Guard<Mutex> Guard;
  public:
    FsmParticipantActionProxy(::CORBA::Object_ptr obj);
    virtual ~FsmParticipantActionProxy();

    virtual ::RTC::Local::ReturnCode_t on_action(::RTC::Local::ExecutionContextHandle_t exec_handle)
      throw ();



    const char* id() {return "FsmParticipantAction";}
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
    ::RTC::FsmParticipantAction_ptr m_obj;
  private:
    std::string m_name;
    Mutex m_refcountMutex;
    int m_refcount;
  };

}; // namespace CORBA
}; // namespace RTC 

#ifndef RTC_FSMPARTICIPANTACTIONSERVANT_H 


#endif // RTC_FSMPARTICIPANTACTIONSERVANT_H

extern "C"
{
  void FsmParticipantActionProxyCORBAInit(coil::Properties& prop);
};

#endif // RTC_FSMPARTICIPANTACTIONPROXY_H
