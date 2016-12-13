// -*- C++ -*-
/*!
 * @file FsmProxy.cpp 
 * @brief IFsm CORBA proxy for doil
 * @date $Date$
 * @author This file was automatically generated form RTC.idl 
 *         by omniidl/doil backend
 *
 * $Id$
 */

#include <doil/corba/CORBAManager.h>
#include <IFsm.h>
#include <FsmProxy.h>
#include <RTCTypeConversion.h>
#include <doil/corba/BasicTypeConversion.h>

namespace RTC 
{
namespace CORBA
{
  /*!
   * @brief ctor
   */ 
  FsmProxy::FsmProxy(::CORBA::Object_ptr obj)
   : ::doil::CORBA::CORBAProxyBase(obj),
     m_obj(::RTC::Fsm::_nil()),
     m_refcount(1),
     ::RTC::CORBA::LightweightRTObjectProxy(obj),
     ::RTC::CORBA::ComponentActionProxy(obj)//   : m_obj(::RTC::Fsm::_nil()),
//     ::RTC::LightweightRTObjectProxy(obj),
//     ::RTC::ComponentActionProxy(obj)
  {
    m_obj = ::RTC::Fsm::_narrow(obj);
    if (::CORBA::is_nil(m_obj)) throw std::bad_alloc();
    m_obj = ::RTC::Fsm::_duplicate(m_obj);
  }

  /*!
   * @brief dtor
   */ 
  FsmProxy::~FsmProxy()
  {
    ::CORBA::release(m_obj);
  }

  
}; // namespace CORBA
}; // namespace RTC 

extern "C"
{
  void FsmProxyCORBAInit(coil::Properties& prop)
  {
    doil::CORBA::CORBAManager& mgr(doil::CORBA::CORBAManager::instance());
    mgr.registerProxyFactory("FsmProxy",
                        doil::New< ::RTC::CORBA::FsmProxy >,
                        doil::Delete< ::RTC::CORBA::FsmProxy >);
  }
};

