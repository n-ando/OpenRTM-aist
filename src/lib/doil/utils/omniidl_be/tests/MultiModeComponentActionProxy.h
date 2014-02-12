// -*- C++ -*-
/*!
 * @file MultiModeComponentActionProxy.h 
 * @brief MultiModeComponentActionProxy CORBA proxy for doil
 * @date $Date$
 * @author This file was automatically generated from RTC.idl 
 *         by omniidl/doil backend
 *
 * $Id$
 */
#ifndef RTC_MULTIMODECOMPONENTACTIONPROXY_H 
#define RTC_MULTIMODECOMPONENTACTIONPROXY_H 

#include <coil/Properties.h>
#include <coil/Mutex.h>
#include <coil/Guard.h>
#include <doil/corba/CORBAManager.h>
#include <doil/corba/CORBAProxyBase.h>
#include <IMultiModeComponentAction.h>
#include <SDOPackageTypes.h>
#include <rtc/corba/idl/RTCSkel.h>


namespace RTC 
{
namespace CORBA 
{

  class MultiModeComponentActionProxy 
  : public virtual ::doil::CORBA::CORBAProxyBase,
    public virtual ::RTC::Local::IMultiModeComponentAction
  {
    typedef coil::Mutex Mutex;
    typedef coil::Guard<Mutex> Guard;
  public:
    MultiModeComponentActionProxy(::CORBA::Object_ptr obj);
    virtual ~MultiModeComponentActionProxy();

    virtual ::RTC::Local::ReturnCode_t on_mode_changed(::RTC::Local::ExecutionContextHandle_t exec_handle)
      throw ();



    const char* id() {return "MultiModeComponentAction";}
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
    ::RTC::MultiModeComponentAction_ptr m_obj;
  private:
    std::string m_name;
    Mutex m_refcountMutex;
    int m_refcount;
  };

}; // namespace CORBA
}; // namespace RTC 

#ifndef RTC_MULTIMODECOMPONENTACTIONSERVANT_H 


#endif // RTC_MULTIMODECOMPONENTACTIONSERVANT_H

extern "C"
{
  void MultiModeComponentActionProxyCORBAInit(coil::Properties& prop);
};

#endif // RTC_MULTIMODECOMPONENTACTIONPROXY_H
