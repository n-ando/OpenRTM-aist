// -*- C++ -*-
/*!
 * @file ModeCapableProxy.h 
 * @brief ModeCapableProxy CORBA proxy for doil
 * @date $Date$
 * @author This file was automatically generated from RTC.idl 
 *         by omniidl/doil backend
 *
 * $Id$
 */
#ifndef RTC_MODECAPABLEPROXY_H 
#define RTC_MODECAPABLEPROXY_H 

#include <coil/Properties.h>
#include <coil/Mutex.h>
#include <coil/Guard.h>
#include <doil/corba/CORBAManager.h>
#include <doil/corba/CORBAProxyBase.h>
#include <IModeCapable.h>
#include <SDOPackageTypes.h>
#include <rtc/corba/idl/RTCSkel.h>


namespace RTC 
{
namespace CORBA 
{

  class ModeCapableProxy 
  : public virtual ::doil::CORBA::CORBAProxyBase,
    public virtual ::RTC::Local::IModeCapable
  {
    typedef coil::Mutex Mutex;
    typedef coil::Guard<Mutex> Guard;
  public:
    ModeCapableProxy(::CORBA::Object_ptr obj);
    virtual ~ModeCapableProxy();

    virtual ::RTC::Local::IMode* get_default_mode()
      throw ();


    virtual ::RTC::Local::IMode* get_current_mode()
      throw ();


    virtual ::RTC::Local::IMode* get_current_mode_in_context(const ::RTC::Local::IExecutionContext* exec_context)
      throw ();


    virtual ::RTC::Local::IMode* get_pending_mode()
      throw ();


    virtual ::RTC::Local::IMode* get_pending_mode_in_context(const ::RTC::Local::IExecutionContext* exec_context)
      throw ();


    virtual ::RTC::Local::ReturnCode_t set_mode(const ::RTC::Local::IMode* new_mode, bool immediate)
      throw ();



    const char* id() {return "ModeCapable";}
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
    ::RTC::ModeCapable_ptr m_obj;
  private:
    std::string m_name;
    Mutex m_refcountMutex;
    int m_refcount;
  };

}; // namespace CORBA
}; // namespace RTC 

#ifndef RTC_MODECAPABLESERVANT_H 


#endif // RTC_MODECAPABLESERVANT_H

extern "C"
{
  void ModeCapableProxyCORBAInit(coil::Properties& prop);
};

#endif // RTC_MODECAPABLEPROXY_H
