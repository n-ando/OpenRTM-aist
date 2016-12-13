// -*- C++ -*-
/*!
 * @file MultiModeComponentActionProxy.cpp 
 * @brief IMultiModeComponentAction CORBA proxy for doil
 * @date $Date$
 * @author This file was automatically generated form RTC.idl 
 *         by omniidl/doil backend
 *
 * $Id$
 */

#include <doil/corba/CORBAManager.h>
#include <IMultiModeComponentAction.h>
#include <MultiModeComponentActionProxy.h>
#include <RTCTypeConversion.h>
#include <doil/corba/BasicTypeConversion.h>

namespace RTC 
{
namespace CORBA 
{
  /*!
   * @brief ctor
   */ 
  MultiModeComponentActionProxy::MultiModeComponentActionProxy(::CORBA::Object_ptr obj)
   : ::doil::CORBA::CORBAProxyBase(obj),
     m_obj(::RTC::MultiModeComponentAction::_nil()),
     m_refcount(1)//   : m_obj(::RTC::MultiModeComponentAction::_nil())
  {
    m_obj = ::RTC::MultiModeComponentAction::_narrow(obj);
    if (::CORBA::is_nil(m_obj)) throw std::bad_alloc();
    m_obj = ::RTC::MultiModeComponentAction::_duplicate(m_obj);
  }

  /*!
   * @brief dtor
   */ 
  MultiModeComponentActionProxy::~MultiModeComponentActionProxy()
  {
    ::CORBA::release(m_obj);
  }

  
  /*!
   * @brief on_mode_changed 
   */ 
  ::RTC::Local::ReturnCode_t MultiModeComponentActionProxy::on_mode_changed(::RTC::Local::ExecutionContextHandle_t exec_handle)
      throw ()
  {
    // Convert Local to CORBA.
    // (The direction of the argument is 'in' or 'inout'.)
    ::RTC::ExecutionContextHandle_t _exec_handle;
    local_to_corba(exec_handle, _exec_handle);

    // Execute the method. 
    ::RTC::ReturnCode_t corba_ret;
    ::RTC::Local::ReturnCode_t local_ret;
    corba_ret = m_obj->on_mode_changed(_exec_handle);

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
  void MultiModeComponentActionProxyCORBAInit(coil::Properties& prop)
  {
    doil::CORBA::CORBAManager& mgr(doil::CORBA::CORBAManager::instance());
    mgr.registerProxyFactory("MultiModeComponentActionProxy",
                        doil::New< ::RTC::CORBA::MultiModeComponentActionProxy >,
                        doil::Delete< ::RTC::CORBA::MultiModeComponentActionProxy >);
  }
};

