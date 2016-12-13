// -*- C++ -*-
/*!
 * @file FsmObjectProxy.cpp 
 * @brief IFsmObject CORBA proxy for doil
 * @date $Date$
 * @author This file was automatically generated form RTC.idl 
 *         by omniidl/doil backend
 *
 * $Id$
 */

#include <doil/corba/CORBAManager.h>
#include <IFsmObject.h>
#include <FsmObjectProxy.h>
#include <RTCTypeConversion.h>
#include <doil/corba/BasicTypeConversion.h>

namespace RTC 
{
namespace CORBA 
{
  /*!
   * @brief ctor
   */ 
  FsmObjectProxy::FsmObjectProxy(::CORBA::Object_ptr obj)
   : ::doil::CORBA::CORBAProxyBase(obj),
     m_obj(::RTC::FsmObject::_nil()),
     m_refcount(1)//   : m_obj(::RTC::FsmObject::_nil())
  {
    m_obj = ::RTC::FsmObject::_narrow(obj);
    if (::CORBA::is_nil(m_obj)) throw std::bad_alloc();
    m_obj = ::RTC::FsmObject::_duplicate(m_obj);
  }

  /*!
   * @brief dtor
   */ 
  FsmObjectProxy::~FsmObjectProxy()
  {
    ::CORBA::release(m_obj);
  }

  
  /*!
   * @brief send_stimulus 
   */ 
  ::RTC::Local::ReturnCode_t FsmObjectProxy::send_stimulus(const ::std::string& message, ::RTC::Local::ExecutionContextHandle_t exec_handle)
      throw ()
  {
    // Convert Local to CORBA.
    // (The direction of the argument is 'in' or 'inout'.)
    char* _message;
    ::RTC::ExecutionContextHandle_t _exec_handle;
    local_to_corba(message, _message);
    local_to_corba(exec_handle, _exec_handle);

    // Execute the method. 
    ::RTC::ReturnCode_t corba_ret;
    ::RTC::Local::ReturnCode_t local_ret;
    corba_ret = m_obj->send_stimulus(_message, _exec_handle);

    // Convert CORBA to Local.
    // (The direction of the argument is 'out' or 'inout'.)

    // Generate the return value.
    corba_to_local(corba_ret, local_ret);
    return local_ret;
  }

}; // namespace CORBA
}; // namespace RTC 

extern "C"
{
  void FsmObjectProxyCORBAInit(coil::Properties& prop)
  {
    doil::CORBA::CORBAManager& mgr(doil::CORBA::CORBAManager::instance());
    mgr.registerProxyFactory("FsmObjectProxy",
                        doil::New< ::RTC::CORBA::FsmObjectProxy >,
                        doil::Delete< ::RTC::CORBA::FsmObjectProxy >);
  }
};

