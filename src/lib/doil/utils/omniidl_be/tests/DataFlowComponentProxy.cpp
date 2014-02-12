// -*- C++ -*-
/*!
 * @file DataFlowComponentProxy.cpp 
 * @brief IDataFlowComponent CORBA proxy for doil
 * @date $Date$
 * @author This file was automatically generated form RTC.idl 
 *         by omniidl/doil backend
 *
 * $Id$
 */

#include <doil/corba/CORBAManager.h>
#include <IDataFlowComponent.h>
#include <DataFlowComponentProxy.h>
#include <RTCTypeConversion.h>
#include <doil/corba/BasicTypeConversion.h>

namespace RTC 
{
namespace CORBA 
{
  /*!
   * @brief ctor
   */ 
  DataFlowComponentProxy::DataFlowComponentProxy(::CORBA::Object_ptr obj)
   : ::doil::CORBA::CORBAProxyBase(obj),
     m_obj(::RTC::DataFlowComponent::_nil()),
     m_refcount(1),
     ::RTC::CORBA::LightweightRTObjectProxy(obj),
     ::RTC::CORBA::DataFlowComponentActionProxy(obj),
     ::RTC::CORBA::ComponentActionProxy(obj)//   : m_obj(::RTC::DataFlowComponent::_nil()),
//     ::RTC::LightweightRTObjectProxy(obj),
//     ::RTC::DataFlowComponentActionProxy(obj),
//     ::RTC::ComponentActionProxy(obj)
  {
    m_obj = ::RTC::DataFlowComponent::_narrow(obj);
    if (::CORBA::is_nil(m_obj)) throw std::bad_alloc();
    m_obj = ::RTC::DataFlowComponent::_duplicate(m_obj);
  }

  /*!
   * @brief dtor
   */ 
  DataFlowComponentProxy::~DataFlowComponentProxy()
  {
    ::CORBA::release(m_obj);
  }

  
}; // namespace CORBA
}; // namespace RTC 

extern "C"
{
  void DataFlowComponentProxyCORBAInit(coil::Properties& prop)
  {
    doil::CORBA::CORBAManager& mgr(doil::CORBA::CORBAManager::instance());
    mgr.registerProxyFactory("DataFlowComponentProxy",
                        doil::New< ::RTC::CORBA::DataFlowComponentProxy >,
                        doil::Delete< ::RTC::CORBA::DataFlowComponentProxy >);
  }
};

