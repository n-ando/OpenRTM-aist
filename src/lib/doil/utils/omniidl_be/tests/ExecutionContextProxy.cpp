// -*- C++ -*-
/*!
 * @file ExecutionContextProxy.cpp 
 * @brief IExecutionContext CORBA proxy for doil
 * @date $Date$
 * @author This file was automatically generated form RTC.idl 
 *         by omniidl/doil backend
 *
 * $Id$
 */

#include <doil/corba/CORBAManager.h>
#include <IExecutionContext.h>
#include <ExecutionContextProxy.h>
#include <RTCTypeConversion.h>
#include <doil/corba/BasicTypeConversion.h>

namespace RTC 
{
namespace CORBA 
{
  /*!
   * @brief ctor
   */ 
  ExecutionContextProxy::ExecutionContextProxy(::CORBA::Object_ptr obj)
   : ::doil::CORBA::CORBAProxyBase(obj),
     m_obj(::RTC::ExecutionContext::_nil()),
     m_refcount(1)//   : m_obj(::RTC::ExecutionContext::_nil())
  {
    m_obj = ::RTC::ExecutionContext::_narrow(obj);
    if (::CORBA::is_nil(m_obj)) throw std::bad_alloc();
    m_obj = ::RTC::ExecutionContext::_duplicate(m_obj);
  }

  /*!
   * @brief dtor
   */ 
  ExecutionContextProxy::~ExecutionContextProxy()
  {
    ::CORBA::release(m_obj);
  }

  
  /*!
   * @brief is_running 
   */ 
  bool ExecutionContextProxy::is_running()
      throw ()
  {
    // Convert Local to CORBA.
    // (The direction of the argument is 'in' or 'inout'.)

    // Execute the method. 
    ::CORBA::Boolean corba_ret;
    bool local_ret;
    corba_ret = m_obj->is_running();

    // Convert CORBA to Local.
    // (The direction of the argument is 'out' or 'inout'.)

    // Generate the return value.
//    local_ret = corba_ret;
    corba_to_local(corba_ret, local_ret);
    return local_ret;
  }

  /*!
   * @brief start 
   */ 
  ::RTC::Local::ReturnCode_t ExecutionContextProxy::start()
      throw ()
  {
    // Convert Local to CORBA.
    // (The direction of the argument is 'in' or 'inout'.)

    // Execute the method. 
    ::RTC::ReturnCode_t corba_ret;
    ::RTC::Local::ReturnCode_t local_ret;
    corba_ret = m_obj->start();

    // Convert CORBA to Local.
    // (The direction of the argument is 'out' or 'inout'.)

    // Generate the return value.
    corba_to_local(corba_ret, local_ret);
    return local_ret;
  }

  /*!
   * @brief stop 
   */ 
  ::RTC::Local::ReturnCode_t ExecutionContextProxy::stop()
      throw ()
  {
    // Convert Local to CORBA.
    // (The direction of the argument is 'in' or 'inout'.)

    // Execute the method. 
    ::RTC::ReturnCode_t corba_ret;
    ::RTC::Local::ReturnCode_t local_ret;
    corba_ret = m_obj->stop();

    // Convert CORBA to Local.
    // (The direction of the argument is 'out' or 'inout'.)

    // Generate the return value.
    corba_to_local(corba_ret, local_ret);
    return local_ret;
  }

  /*!
   * @brief get_rate 
   */ 
  double ExecutionContextProxy::get_rate()
      throw ()
  {
    // Convert Local to CORBA.
    // (The direction of the argument is 'in' or 'inout'.)

    // Execute the method. 
    ::CORBA::Double corba_ret;
    double local_ret;
    corba_ret = m_obj->get_rate();

    // Convert CORBA to Local.
    // (The direction of the argument is 'out' or 'inout'.)

    // Generate the return value.
//    local_ret = corba_ret;
    corba_to_local(corba_ret, local_ret);
    return local_ret;
  }

  /*!
   * @brief set_rate 
   */ 
  ::RTC::Local::ReturnCode_t ExecutionContextProxy::set_rate(double rate)
      throw ()
  {
    // Convert Local to CORBA.
    // (The direction of the argument is 'in' or 'inout'.)
    ::CORBA::Double _rate;
//    _rate = rate;
    local_to_corba(rate, _rate);

    // Execute the method. 
    ::RTC::ReturnCode_t corba_ret;
    ::RTC::Local::ReturnCode_t local_ret;
    corba_ret = m_obj->set_rate(_rate);

    // Convert CORBA to Local.
    // (The direction of the argument is 'out' or 'inout'.)

    // Generate the return value.
    corba_to_local(corba_ret, local_ret);
    return local_ret;
  }

  /*!
   * @brief add_component 
   */ 
  ::RTC::Local::ReturnCode_t ExecutionContextProxy::add_component(const ::RTC::Local::ILightweightRTObject* comp)
      throw ()
  {
    // Convert Local to CORBA.
    // (The direction of the argument is 'in' or 'inout'.)
    ::RTC::LightweightRTObject_ptr _comp;
    local_to_corba(const_cast< ::RTC::Local::ILightweightRTObject* >(comp), _comp);

    // Execute the method. 
    ::RTC::ReturnCode_t corba_ret;
    ::RTC::Local::ReturnCode_t local_ret;
    corba_ret = m_obj->add_component(_comp);

    // Convert CORBA to Local.
    // (The direction of the argument is 'out' or 'inout'.)

    // Generate the return value.
    corba_to_local(corba_ret, local_ret);
    return local_ret;
  }

  /*!
   * @brief remove_component 
   */ 
  ::RTC::Local::ReturnCode_t ExecutionContextProxy::remove_component(const ::RTC::Local::ILightweightRTObject* comp)
      throw ()
  {
    // Convert Local to CORBA.
    // (The direction of the argument is 'in' or 'inout'.)
    ::RTC::LightweightRTObject_ptr _comp;
    local_to_corba(const_cast< ::RTC::Local::ILightweightRTObject* >(comp), _comp);

    // Execute the method. 
    ::RTC::ReturnCode_t corba_ret;
    ::RTC::Local::ReturnCode_t local_ret;
    corba_ret = m_obj->remove_component(_comp);

    // Convert CORBA to Local.
    // (The direction of the argument is 'out' or 'inout'.)

    // Generate the return value.
    corba_to_local(corba_ret, local_ret);
    return local_ret;
  }

  /*!
   * @brief activate_component 
   */ 
  ::RTC::Local::ReturnCode_t ExecutionContextProxy::activate_component(const ::RTC::Local::ILightweightRTObject* comp)
      throw ()
  {
    // Convert Local to CORBA.
    // (The direction of the argument is 'in' or 'inout'.)
    ::RTC::LightweightRTObject_ptr _comp;
    local_to_corba(const_cast< ::RTC::Local::ILightweightRTObject* >(comp), _comp);

    // Execute the method. 
    ::RTC::ReturnCode_t corba_ret;
    ::RTC::Local::ReturnCode_t local_ret;
    corba_ret = m_obj->activate_component(_comp);

    // Convert CORBA to Local.
    // (The direction of the argument is 'out' or 'inout'.)

    // Generate the return value.
    corba_to_local(corba_ret, local_ret);
    return local_ret;
  }

  /*!
   * @brief deactivate_component 
   */ 
  ::RTC::Local::ReturnCode_t ExecutionContextProxy::deactivate_component(const ::RTC::Local::ILightweightRTObject* comp)
      throw ()
  {
    // Convert Local to CORBA.
    // (The direction of the argument is 'in' or 'inout'.)
    ::RTC::LightweightRTObject_ptr _comp;
    local_to_corba(const_cast< ::RTC::Local::ILightweightRTObject* >(comp), _comp);

    // Execute the method. 
    ::RTC::ReturnCode_t corba_ret;
    ::RTC::Local::ReturnCode_t local_ret;
    corba_ret = m_obj->deactivate_component(_comp);

    // Convert CORBA to Local.
    // (The direction of the argument is 'out' or 'inout'.)

    // Generate the return value.
    corba_to_local(corba_ret, local_ret);
    return local_ret;
  }

  /*!
   * @brief reset_component 
   */ 
  ::RTC::Local::ReturnCode_t ExecutionContextProxy::reset_component(const ::RTC::Local::ILightweightRTObject* comp)
      throw ()
  {
    // Convert Local to CORBA.
    // (The direction of the argument is 'in' or 'inout'.)
    ::RTC::LightweightRTObject_ptr _comp;
    local_to_corba(const_cast< ::RTC::Local::ILightweightRTObject* >(comp), _comp);

    // Execute the method. 
    ::RTC::ReturnCode_t corba_ret;
    ::RTC::Local::ReturnCode_t local_ret;
    corba_ret = m_obj->reset_component(_comp);

    // Convert CORBA to Local.
    // (The direction of the argument is 'out' or 'inout'.)

    // Generate the return value.
    corba_to_local(corba_ret, local_ret);
    return local_ret;
  }

  /*!
   * @brief get_component_state 
   */ 
  ::RTC::Local::LifeCycleState ExecutionContextProxy::get_component_state(const ::RTC::Local::ILightweightRTObject* comp)
      throw ()
  {
    // Convert Local to CORBA.
    // (The direction of the argument is 'in' or 'inout'.)
    ::RTC::LightweightRTObject_ptr _comp;
    local_to_corba(const_cast< ::RTC::Local::ILightweightRTObject* >(comp), _comp);

    // Execute the method. 
    ::RTC::LifeCycleState corba_ret;
    ::RTC::Local::LifeCycleState local_ret;
    corba_ret = m_obj->get_component_state(_comp);

    // Convert CORBA to Local.
    // (The direction of the argument is 'out' or 'inout'.)

    // Generate the return value.
    corba_to_local(corba_ret, local_ret);
    return local_ret;
  }

  /*!
   * @brief get_kind 
   */ 
  ::RTC::Local::ExecutionKind ExecutionContextProxy::get_kind()
      throw ()
  {
    // Convert Local to CORBA.
    // (The direction of the argument is 'in' or 'inout'.)

    // Execute the method. 
    ::RTC::ExecutionKind corba_ret;
    ::RTC::Local::ExecutionKind local_ret;
    corba_ret = m_obj->get_kind();

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
  void ExecutionContextProxyCORBAInit(coil::Properties& prop)
  {
    doil::CORBA::CORBAManager& mgr(doil::CORBA::CORBAManager::instance());
    mgr.registerProxyFactory("ExecutionContextProxy",
                        doil::New< ::RTC::CORBA::ExecutionContextProxy >,
                        doil::Delete< ::RTC::CORBA::ExecutionContextProxy >);
  }
};

