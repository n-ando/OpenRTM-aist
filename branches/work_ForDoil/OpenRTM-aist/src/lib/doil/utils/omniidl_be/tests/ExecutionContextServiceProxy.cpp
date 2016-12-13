// -*- C++ -*-
/*!
 * @file ExecutionContextServiceProxy.cpp 
 * @brief IExecutionContextService CORBA proxy for doil
 * @date $Date$
 * @author This file was automatically generated form RTC.idl 
 *         by omniidl/doil backend
 *
 * $Id$
 */

#include <iostream>
#include <doil/corba/CORBAManager.h>
#include <IExecutionContextService.h>
#include <ExecutionContextServiceProxy.h>
#include <RTCTypeConversion.h>
#include <doil/corba/BasicTypeConversion.h>

namespace RTC 
{
namespace CORBA 
{
  /*!
   * @brief ctor
   */ 
  ExecutionContextServiceProxy::ExecutionContextServiceProxy(::CORBA::Object_ptr obj)
   : ::doil::CORBA::CORBAProxyBase(obj),
     m_obj(::RTC::ExecutionContextService::_nil()),
     m_refcount(1),
     ::RTC::CORBA::ExecutionContextProxy(obj),
     ::SDOPackage::CORBA::SDOServiceProxy(obj)//   : m_obj(::RTC::ExecutionContextService::_nil()),
//     ::RTC::ExecutionContextProxy(obj),
//     ::SDOPackage::SDOServiceProxy(obj)
  {
    m_obj = ::RTC::ExecutionContextService::_narrow(obj);
    if (::CORBA::is_nil(m_obj)) throw std::bad_alloc();
    m_obj = ::RTC::ExecutionContextService::_duplicate(m_obj);
  }

  /*!
   * @brief dtor
   */ 
  ExecutionContextServiceProxy::~ExecutionContextServiceProxy()
  {
    ::CORBA::release(m_obj);
  }

  
  /*!
   * @brief get_profile 
   */ 
  ::RTC::Local::ExecutionContextProfile ExecutionContextServiceProxy::get_profile()
      throw ()
  {
    // Convert Local to CORBA.
    // (The direction of the argument is 'in' or 'inout'.)

    // Execute the method. 
    ::RTC::ExecutionContextProfile* corba_ret;
    ::RTC::Local::ExecutionContextProfile local_ret;
    corba_ret = m_obj->get_profile();
    // Convert CORBA to Local.
    // (The direction of the argument is 'out' or 'inout'.)

    // Generate the return value.
    corba_to_local(*corba_ret, local_ret);
    delete corba_ret; 
    return local_ret;
  }

}; // namespace CORBA
}; // namespace RTC 

extern "C"
{
  void ExecutionContextServiceProxyCORBAInit(coil::Properties& prop)
  {
    doil::CORBA::CORBAManager& mgr(doil::CORBA::CORBAManager::instance());
    mgr.registerProxyFactory("ExecutionContextServiceProxy",
                        doil::New< ::RTC::CORBA::ExecutionContextServiceProxy >,
                        doil::Delete< ::RTC::CORBA::ExecutionContextServiceProxy >);
  }
};

