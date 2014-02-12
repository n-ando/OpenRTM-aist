// -*- C++ -*-
/*!
 * @file MonitoringProxy.cpp 
 * @brief IMonitoring CORBA proxy for doil
 * @date $Date$
 * @author This file was automatically generated form SDOPackage.idl 
 *         by omniidl/doil backend
 *
 * $Id$
 */

#include <doil/corba/CORBAManager.h>
#include <IMonitoring.h>
#include <MonitoringProxy.h>
#include <SDOPackageTypeConversion.h>
#include <doil/corba/BasicTypeConversion.h>

namespace SDOPackage 
{
namespace CORBA 
{
  /*!
   * @brief ctor
   */ 
  MonitoringProxy::MonitoringProxy(::CORBA::Object_ptr obj)
   : ::doil::CORBA::CORBAProxyBase(obj),
     m_obj(::SDOPackage::Monitoring::_nil()),
     m_refcount(1)//   : m_obj(::SDOPackage::Monitoring::_nil())
  {
    m_obj = ::SDOPackage::Monitoring::_narrow(obj);
    if (::CORBA::is_nil(m_obj)) throw std::bad_alloc();
    m_obj = ::SDOPackage::Monitoring::_duplicate(m_obj);
  }

  /*!
   * @brief dtor
   */ 
  MonitoringProxy::~MonitoringProxy()
  {
    ::CORBA::release(m_obj);
  }

  
}; // namespace CORBA
}; // namespace SDOPackage 

extern "C"
{
  void MonitoringProxyCORBAInit(coil::Properties& prop)
  {
    doil::CORBA::CORBAManager& mgr(doil::CORBA::CORBAManager::instance());
    mgr.registerProxyFactory("MonitoringProxy",
                        doil::New< ::SDOPackage::CORBA::MonitoringProxy >,
                        doil::Delete< ::SDOPackage::CORBA::MonitoringProxy >);
  }
};

