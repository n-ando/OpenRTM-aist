// -*- C++ -*-
/*!
 * @file LightweightRTObjectProxy.cpp 
 * @brief ILightweightRTObject CORBA proxy for doil
 * @date $Date$
 * @author This file was automatically generated form RTC.idl 
 *         by omniidl/doil backend
 *
 * $Id$
 */

#include <doil/corba/CORBAManager.h>
#include <ILightweightRTObject.h>
#include <LightweightRTObjectProxy.h>
#include <RTCTypeConversion.h>
#include <doil/corba/BasicTypeConversion.h>

namespace RTC 
{
namespace CORBA 
{
  /*!
   * @brief ctor
   */ 
  LightweightRTObjectProxy::LightweightRTObjectProxy(::CORBA::Object_ptr obj)
   : ::doil::CORBA::CORBAProxyBase(obj),
     m_obj(::RTC::LightweightRTObject::_nil()),
     m_refcount(1),
     ::RTC::CORBA::ComponentActionProxy(obj)//   : m_obj(::RTC::LightweightRTObject::_nil()),
//     ::RTC::ComponentActionProxy(obj)
  {
    m_obj = ::RTC::LightweightRTObject::_narrow(obj);
    if (::CORBA::is_nil(m_obj)) throw std::bad_alloc();
    m_obj = ::RTC::LightweightRTObject::_duplicate(m_obj);
  }

  /*!
   * @brief dtor
   */ 
  LightweightRTObjectProxy::~LightweightRTObjectProxy()
  {
    ::CORBA::release(m_obj);
  }

  
  /*!
   * @brief initialize 
   */ 
  ::RTC::Local::ReturnCode_t LightweightRTObjectProxy::initialize()
      throw ()
  {
    // Convert Local to CORBA.
    // (The direction of the argument is 'in' or 'inout'.)

    // Execute the method. 
    ::RTC::ReturnCode_t corba_ret;
    ::RTC::Local::ReturnCode_t local_ret;
    corba_ret = m_obj->initialize();

    // Convert CORBA to Local.
    // (The direction of the argument is 'out' or 'inout'.)

    // Generate the return value.
    corba_to_local(corba_ret, local_ret);
    return local_ret;
  }

  /*!
   * @brief finalize 
   */ 
  ::RTC::Local::ReturnCode_t LightweightRTObjectProxy::finalize()
      throw ()
  {
    // Convert Local to CORBA.
    // (The direction of the argument is 'in' or 'inout'.)

    // Execute the method. 
    ::RTC::ReturnCode_t corba_ret;
    ::RTC::Local::ReturnCode_t local_ret;
    corba_ret = m_obj->finalize();

    // Convert CORBA to Local.
    // (The direction of the argument is 'out' or 'inout'.)

    // Generate the return value.
    corba_to_local(corba_ret, local_ret);
    return local_ret;
  }

  /*!
   * @brief is_alive 
   */ 
  bool LightweightRTObjectProxy::is_alive(const ::RTC::Local::IExecutionContext* exec_context)
      throw ()
  {
    // Convert Local to CORBA.
    // (The direction of the argument is 'in' or 'inout'.)
    ::RTC::ExecutionContext_ptr _exec_context;
    local_to_corba(const_cast< ::RTC::Local::IExecutionContext* >(exec_context), _exec_context);

    // Execute the method. 
    ::CORBA::Boolean corba_ret;
    bool local_ret;
    corba_ret = m_obj->is_alive(_exec_context);

    // Convert CORBA to Local.
    // (The direction of the argument is 'out' or 'inout'.)

    // Generate the return value.
//    local_ret = corba_ret;
    corba_to_local(corba_ret, local_ret);
    return local_ret;
  }

  /*!
   * @brief exit 
   */ 
  ::RTC::Local::ReturnCode_t LightweightRTObjectProxy::exit()
      throw ()
  {
    // Convert Local to CORBA.
    // (The direction of the argument is 'in' or 'inout'.)

    // Execute the method. 
    ::RTC::ReturnCode_t corba_ret;
    ::RTC::Local::ReturnCode_t local_ret;
    corba_ret = m_obj->exit();

    // Convert CORBA to Local.
    // (The direction of the argument is 'out' or 'inout'.)

    // Generate the return value.
    corba_to_local(corba_ret, local_ret);
    return local_ret;
  }

  /*!
   * @brief attach_context 
   */ 
  ::RTC::Local::ExecutionContextHandle_t LightweightRTObjectProxy::attach_context(const ::RTC::Local::IExecutionContext* exec_context)
      throw ()
  {
    // Convert Local to CORBA.
    // (The direction of the argument is 'in' or 'inout'.)
    ::RTC::ExecutionContext_ptr _exec_context;
    local_to_corba(const_cast< ::RTC::Local::IExecutionContext* >(exec_context), _exec_context);

    // Execute the method. 
    ::RTC::ExecutionContextHandle_t corba_ret;
    ::RTC::Local::ExecutionContextHandle_t local_ret;
    corba_ret = m_obj->attach_context(_exec_context);

    // Convert CORBA to Local.
    // (The direction of the argument is 'out' or 'inout'.)

    // Generate the return value.
//    local_ret = corba_ret;
    corba_to_local(corba_ret, local_ret);
    return local_ret;
  }

  /*!
   * @brief detach_context 
   */ 
  ::RTC::Local::ReturnCode_t LightweightRTObjectProxy::detach_context(::RTC::Local::ExecutionContextHandle_t exec_handle)
      throw ()
  {
    // Convert Local to CORBA.
    // (The direction of the argument is 'in' or 'inout'.)
    ::RTC::ExecutionContextHandle_t _exec_handle;
    local_to_corba(exec_handle, _exec_handle);

    // Execute the method. 
    ::RTC::ReturnCode_t corba_ret;
    ::RTC::Local::ReturnCode_t local_ret;
    corba_ret = m_obj->detach_context(_exec_handle);

    // Convert CORBA to Local.
    // (The direction of the argument is 'out' or 'inout'.)

    // Generate the return value.
    corba_to_local(corba_ret, local_ret);
    return local_ret;
  }

  /*!
   * @brief get_context 
   */ 
  ::RTC::Local::IExecutionContext* LightweightRTObjectProxy::get_context(::RTC::Local::ExecutionContextHandle_t exec_handle)
      throw ()
  {
    // Convert Local to CORBA.
    // (The direction of the argument is 'in' or 'inout'.)
    ::RTC::ExecutionContextHandle_t _exec_handle;
    local_to_corba(exec_handle, _exec_handle);

    // Execute the method. 
    ::RTC::ExecutionContext_ptr corba_ret;
    ::RTC::Local::IExecutionContext* local_ret;
    corba_ret = m_obj->get_context(_exec_handle);

    // Convert CORBA to Local.
    // (The direction of the argument is 'out' or 'inout'.)

    // Generate the return value.
    corba_to_local(corba_ret, local_ret);
    ::CORBA::release(corba_ret);
    return local_ret;
  }

  /*!
   * @brief get_owned_contexts 
   */ 
  ::RTC::Local::ExecutionContextList LightweightRTObjectProxy::get_owned_contexts()
      throw ()
  {
    // Convert Local to CORBA.
    // (The direction of the argument is 'in' or 'inout'.)

    // Execute the method. 
    ::RTC::ExecutionContextList* corba_ret;
    ::RTC::Local::ExecutionContextList local_ret;
    corba_ret = m_obj->get_owned_contexts();

    // Convert CORBA to Local.
    // (The direction of the argument is 'out' or 'inout'.)

    // Generate the return value.
    corba_to_local(*corba_ret, local_ret);
    delete corba_ret; 
    return local_ret;
  }

  /*!
   * @brief get_participating_contexts 
   */ 
  ::RTC::Local::ExecutionContextList LightweightRTObjectProxy::get_participating_contexts()
      throw ()
  {
    // Convert Local to CORBA.
    // (The direction of the argument is 'in' or 'inout'.)

    // Execute the method. 
    ::RTC::ExecutionContextList* corba_ret;
    ::RTC::Local::ExecutionContextList local_ret;
    corba_ret = m_obj->get_participating_contexts();

    // Convert CORBA to Local.
    // (The direction of the argument is 'out' or 'inout'.)

    // Generate the return value.
    corba_to_local(*corba_ret, local_ret);
    delete corba_ret; 
    return local_ret;
  }

  /*!
   * @brief get_context_handle 
   */ 
  ::RTC::Local::ExecutionContextHandle_t LightweightRTObjectProxy::get_context_handle(const ::RTC::Local::IExecutionContext* cxt)
      throw ()
  {
    // Convert Local to CORBA.
    // (The direction of the argument is 'in' or 'inout'.)
    ::RTC::ExecutionContext_ptr _cxt;
    local_to_corba(const_cast< ::RTC::Local::IExecutionContext* >(cxt), _cxt);

    // Execute the method. 
    ::RTC::ExecutionContextHandle_t corba_ret;
    ::RTC::Local::ExecutionContextHandle_t local_ret;
    corba_ret = m_obj->get_context_handle(_cxt);

    // Convert CORBA to Local.
    // (The direction of the argument is 'out' or 'inout'.)

    // Generate the return value.
//    local_ret = corba_ret;
    corba_to_local(corba_ret, local_ret);
    return local_ret;
  }

}; // namespace CORBA
}; // namespace RTC 

extern "C"
{
  void LightweightRTObjectProxyCORBAInit(coil::Properties& prop)
  {
    doil::CORBA::CORBAManager& mgr(doil::CORBA::CORBAManager::instance());
    mgr.registerProxyFactory("LightweightRTObjectProxy",
                        doil::New< ::RTC::CORBA::LightweightRTObjectProxy >,
                        doil::Delete< ::RTC::CORBA::LightweightRTObjectProxy >);
  }
};

