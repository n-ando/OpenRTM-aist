// -*- C++ -*-
/*!
 * @file FsmParticipantActionProxy.cpp 
 * @brief IFsmParticipantAction CORBA proxy for doil
 * @date $Date$
 * @author This file was automatically generated form RTC.idl 
 *         by omniidl/doil backend
 *
 * $Id$
 */

#include <doil/corba/CORBAManager.h>
#include <IFsmParticipantAction.h>
#include <FsmParticipantActionProxy.h>
#include <RTCTypeConversion.h>
#include <doil/corba/BasicTypeConversion.h>

namespace RTC 
{
namespace CORBA
{
  /*!
   * @brief ctor
   */ 
  FsmParticipantActionProxy::FsmParticipantActionProxy(::CORBA::Object_ptr obj)
   : ::doil::CORBA::CORBAProxyBase(obj),
     m_obj(::RTC::FsmParticipantAction::_nil()),
     m_refcount(1)//   : m_obj(::RTC::FsmParticipantAction::_nil())
  {
    m_obj = ::RTC::FsmParticipantAction::_narrow(obj);
    if (::CORBA::is_nil(m_obj)) throw std::bad_alloc();
    m_obj = ::RTC::FsmParticipantAction::_duplicate(m_obj);
  }

  /*!
   * @brief dtor
   */ 
  FsmParticipantActionProxy::~FsmParticipantActionProxy()
  {
    ::CORBA::release(m_obj);
  }

  
  /*!
   * @brief on_action 
   */ 
  ::RTC::Local::ReturnCode_t FsmParticipantActionProxy::on_action(::RTC::Local::ExecutionContextHandle_t exec_handle)
      throw ()
  {
    // Convert Local to CORBA.
    // (The direction of the argument is 'in' or 'inout'.)
    ::RTC::ExecutionContextHandle_t _exec_handle;
    local_to_corba(exec_handle, _exec_handle);

    // Execute the method. 
    ::RTC::ReturnCode_t corba_ret;
    ::RTC::Local::ReturnCode_t local_ret;
    corba_ret = m_obj->on_action(_exec_handle);

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
  void FsmParticipantActionProxyCORBAInit(coil::Properties& prop)
  {
    doil::CORBA::CORBAManager& mgr(doil::CORBA::CORBAManager::instance());
    mgr.registerProxyFactory("FsmParticipantActionProxy",
                        doil::New< ::RTC::CORBA::FsmParticipantActionProxy >,
                        doil::Delete< ::RTC::CORBA::FsmParticipantActionProxy >);
  }
};

