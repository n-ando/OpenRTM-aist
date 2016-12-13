// -*- C++ -*-
/*!
 * @file DataFlowComponentProxy.h 
 * @brief DataFlowComponentProxy CORBA proxy for doil
 * @date $Date$
 * @author This file was automatically generated from RTC.idl 
 *         by omniidl/doil backend
 *
 * $Id$
 */
#ifndef RTC_DATAFLOWCOMPONENTPROXY_H 
#define RTC_DATAFLOWCOMPONENTPROXY_H 

#include <coil/Properties.h>
#include <coil/Mutex.h>
#include <coil/Guard.h>
#include <doil/corba/CORBAManager.h>
#include <doil/corba/CORBAProxyBase.h>
#include <IDataFlowComponent.h>
#include <LightweightRTObjectProxy.h>
#include <DataFlowComponentActionProxy.h>
#include <ComponentActionProxy.h>
#include <SDOPackageTypes.h>


namespace RTC 
{

namespace CORBA 
{
  class DataFlowComponentProxy 
  : public virtual ::doil::CORBA::CORBAProxyBase,
    public virtual ::RTC::CORBA::LightweightRTObjectProxy,
    public virtual ::RTC::CORBA::DataFlowComponentActionProxy,
    public virtual ::RTC::CORBA::ComponentActionProxy,
    public virtual ::RTC::Local::IDataFlowComponent
  {
    typedef coil::Mutex Mutex;
    typedef coil::Guard<Mutex> Guard;
  public:
    DataFlowComponentProxy(::CORBA::Object_ptr obj);
    virtual ~DataFlowComponentProxy();


    const char* id() {return "DataFlowComponent";}
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
    ::RTC::DataFlowComponent_ptr m_obj;
  private:
    std::string m_name;
    Mutex m_refcountMutex;
    int m_refcount;
  };

}; // namespace CORBA
}; // namespace RTC 

#ifndef RTC_DATAFLOWCOMPONENTSERVANT_H 


#endif // RTC_DATAFLOWCOMPONENTSERVANT_H

extern "C"
{
  void DataFlowComponentProxyCORBAInit(coil::Properties& prop);
};

#endif // RTC_DATAFLOWCOMPONENTPROXY_H
