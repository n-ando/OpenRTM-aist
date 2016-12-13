// -*- C++ -*-
/*!
 * @file MonitoringProxy.h 
 * @brief MonitoringProxy CORBA proxy for doil
 * @date $Date$
 * @author This file was automatically generated from SDOPackage.idl 
 *         by omniidl/doil backend
 *
 * $Id$
 */
#ifndef SDOPACKAGE_MONITORINGPROXY_H 
#define SDOPACKAGE_MONITORINGPROXY_H 

#include <coil/Properties.h>
#include <coil/Mutex.h>
#include <coil/Guard.h>
#include <doil/corba/CORBAManager.h>
#include <doil/corba/CORBAProxyBase.h>
#include <IMonitoring.h>
#include <rtc/corba/idl/SDOPackageSkel.h>


namespace SDOPackage 
{
namespace CORBA 
{

  class MonitoringProxy 
  : public virtual ::doil::CORBA::CORBAProxyBase,
    public virtual ::SDOPackage::Local::IMonitoring
  {
    typedef coil::Mutex Mutex;
    typedef coil::Guard<Mutex> Guard;
  public:
    MonitoringProxy(::CORBA::Object_ptr obj);
    virtual ~MonitoringProxy();


    const char* id() {return "Monitoring";}
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
    ::SDOPackage::Monitoring_ptr m_obj;
  private:
    std::string m_name;
    Mutex m_refcountMutex;
    int m_refcount;
  };

}; // namespace CORBA
}; // namespace SDOPackage 

#ifndef SDOPACKAGE_MONITORINGSERVANT_H 


#endif // SDOPACKAGE_MONITORINGSERVANT_H

extern "C"
{
  void MonitoringProxyCORBAInit(coil::Properties& prop);
};

#endif // SDOPACKAGE_MONITORINGPROXY_H
