// -*- C++ -*-
/*!
 * @file ModeCapableProxy.cpp 
 * @brief IModeCapable CORBA proxy for doil
 * @date $Date$
 * @author This file was automatically generated form RTC.idl 
 *         by omniidl/doil backend
 *
 * $Id$
 */

#include <doil/corba/CORBAManager.h>
#include <IModeCapable.h>
#include <ModeCapableProxy.h>
#include <RTCTypeConversion.h>
#include <doil/corba/BasicTypeConversion.h>

namespace RTC 
{
namespace CORBA 
{
  /*!
   * @brief ctor
   */ 
  ModeCapableProxy::ModeCapableProxy(::CORBA::Object_ptr obj)
   : ::doil::CORBA::CORBAProxyBase(obj),
     m_obj(::RTC::ModeCapable::_nil()),
     m_refcount(1)//   : m_obj(::RTC::ModeCapable::_nil())
  {
    m_obj = ::RTC::ModeCapable::_narrow(obj);
    if (::CORBA::is_nil(m_obj)) throw std::bad_alloc();
    m_obj = ::RTC::ModeCapable::_duplicate(m_obj);
  }

  /*!
   * @brief dtor
   */ 
  ModeCapableProxy::~ModeCapableProxy()
  {
    ::CORBA::release(m_obj);
  }

  
  /*!
   * @brief get_default_mode 
   */ 
  ::RTC::Local::IMode* ModeCapableProxy::get_default_mode()
      throw ()
  {
    // Convert Local to CORBA.
    // (The direction of the argument is 'in' or 'inout'.)

    // Execute the method. 
    ::RTC::Mode_ptr corba_ret;
    ::RTC::Local::IMode* local_ret;
    corba_ret = m_obj->get_default_mode();

    // Convert CORBA to Local.
    // (The direction of the argument is 'out' or 'inout'.)

    // Generate the return value.
    corba_to_local(corba_ret, local_ret);
    ::CORBA::release(corba_ret);
    return local_ret;
  }

  /*!
   * @brief get_current_mode 
   */ 
  ::RTC::Local::IMode* ModeCapableProxy::get_current_mode()
      throw ()
  {
    // Convert Local to CORBA.
    // (The direction of the argument is 'in' or 'inout'.)

    // Execute the method. 
    ::RTC::Mode_ptr corba_ret;
    ::RTC::Local::IMode* local_ret;
    corba_ret = m_obj->get_current_mode();

    // Convert CORBA to Local.
    // (The direction of the argument is 'out' or 'inout'.)

    // Generate the return value.
    corba_to_local(corba_ret, local_ret);
    ::CORBA::release(corba_ret);
    return local_ret;
  }

  /*!
   * @brief get_current_mode_in_context 
   */ 
  ::RTC::Local::IMode* ModeCapableProxy::get_current_mode_in_context(const ::RTC::Local::IExecutionContext* exec_context)
      throw ()
  {
    // Convert Local to CORBA.
    // (The direction of the argument is 'in' or 'inout'.)
    ::RTC::ExecutionContext_ptr _exec_context;
    local_to_corba(const_cast< ::RTC::Local::IExecutionContext* >(exec_context), _exec_context);

    // Execute the method. 
    ::RTC::Mode_ptr corba_ret;
    ::RTC::Local::IMode* local_ret;
    corba_ret = m_obj->get_current_mode_in_context(_exec_context);

    // Convert CORBA to Local.
    // (The direction of the argument is 'out' or 'inout'.)

    // Generate the return value.
    corba_to_local(corba_ret, local_ret);
    ::CORBA::release(corba_ret);
    return local_ret;
  }

  /*!
   * @brief get_pending_mode 
   */ 
  ::RTC::Local::IMode* ModeCapableProxy::get_pending_mode()
      throw ()
  {
    // Convert Local to CORBA.
    // (The direction of the argument is 'in' or 'inout'.)

    // Execute the method. 
    ::RTC::Mode_ptr corba_ret;
    ::RTC::Local::IMode* local_ret;
    corba_ret = m_obj->get_pending_mode();

    // Convert CORBA to Local.
    // (The direction of the argument is 'out' or 'inout'.)

    // Generate the return value.
    corba_to_local(corba_ret, local_ret);
    ::CORBA::release(corba_ret);
    return local_ret;
  }

  /*!
   * @brief get_pending_mode_in_context 
   */ 
  ::RTC::Local::IMode* ModeCapableProxy::get_pending_mode_in_context(const ::RTC::Local::IExecutionContext* exec_context)
      throw ()
  {
    // Convert Local to CORBA.
    // (The direction of the argument is 'in' or 'inout'.)
    ::RTC::ExecutionContext_ptr _exec_context;
    local_to_corba(const_cast< ::RTC::Local::IExecutionContext* >(exec_context), _exec_context);

    // Execute the method. 
    ::RTC::Mode_ptr corba_ret;
    ::RTC::Local::IMode* local_ret;
    corba_ret = m_obj->get_pending_mode_in_context(_exec_context);

    // Convert CORBA to Local.
    // (The direction of the argument is 'out' or 'inout'.)

    // Generate the return value.
    corba_to_local(corba_ret, local_ret);
    ::CORBA::release(corba_ret);
    return local_ret;
  }

  /*!
   * @brief set_mode 
   */ 
  ::RTC::Local::ReturnCode_t ModeCapableProxy::set_mode(const ::RTC::Local::IMode* new_mode, bool immediate)
      throw ()
  {
    // Convert Local to CORBA.
    // (The direction of the argument is 'in' or 'inout'.)
    ::RTC::Mode_ptr _new_mode;
    ::CORBA::Boolean _immediate;
    local_to_corba(const_cast< ::RTC::Local::IMode* >(new_mode), _new_mode);
//    _immediate = immediate;
    local_to_corba(immediate, _immediate);

    // Execute the method. 
    ::RTC::ReturnCode_t corba_ret;
    ::RTC::Local::ReturnCode_t local_ret;
    corba_ret = m_obj->set_mode(_new_mode, _immediate);

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
  void ModeCapableProxyCORBAInit(coil::Properties& prop)
  {
    doil::CORBA::CORBAManager& mgr(doil::CORBA::CORBAManager::instance());
    mgr.registerProxyFactory("ModeCapableProxy",
                        doil::New< ::RTC::CORBA::ModeCapableProxy >,
                        doil::Delete< ::RTC::CORBA::ModeCapableProxy >);
  }
};

