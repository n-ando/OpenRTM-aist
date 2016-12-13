// -*- C++ -*-
/*!
 * @file DataFlowComponentActionProxy.h 
 * @brief DataFlowComponentActionProxy CORBA proxy for doil
 * @date $Date$
 * @author This file was automatically generated from RTC.idl 
 *         by omniidl/doil backend
 *
 * $Id$
 */
#ifndef RTC_DATAFLOWCOMPONENTACTIONPROXY_H 
#define RTC_DATAFLOWCOMPONENTACTIONPROXY_H 

#include <coil/Properties.h>
#include <coil/Mutex.h>
#include <coil/Guard.h>
#include <doil/corba/CORBAManager.h>
#include <doil/corba/CORBAProxyBase.h>
#include <IDataFlowComponentAction.h>
#include <SDOPackageTypes.h>
#include <rtc/corba/idl/RTCSkel.h>


namespace RTC 
{

namespace CORBA 
{
  class DataFlowComponentActionProxy 
  : public virtual ::doil::CORBA::CORBAProxyBase,
    public virtual ::RTC::Local::IDataFlowComponentAction
  {
    typedef coil::Mutex Mutex;
    typedef coil::Guard<Mutex> Guard;
  public:
    DataFlowComponentActionProxy(::CORBA::Object_ptr obj);
    virtual ~DataFlowComponentActionProxy();

    virtual ::RTC::Local::ReturnCode_t on_execute(::RTC::Local::ExecutionContextHandle_t exec_handle)
      throw ();


    virtual ::RTC::Local::ReturnCode_t on_state_update(::RTC::Local::ExecutionContextHandle_t exec_handle)
      throw ();


    virtual ::RTC::Local::ReturnCode_t on_rate_changed(::RTC::Local::ExecutionContextHandle_t exec_handle)
      throw ();



    const char* id() {return "DataFlowComponentAction";}
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
    ::RTC::DataFlowComponentAction_ptr m_obj;
  private:
    std::string m_name;
    Mutex m_refcountMutex;
    int m_refcount;
  };

}; // namespace CORBA
}; // namespace RTC 

#ifndef RTC_DATAFLOWCOMPONENTACTIONSERVANT_H 


#endif // RTC_DATAFLOWCOMPONENTACTIONSERVANT_H

extern "C"
{
  void DataFlowComponentActionProxyCORBAInit(coil::Properties& prop);
};

#endif // RTC_DATAFLOWCOMPONENTACTIONPROXY_H
