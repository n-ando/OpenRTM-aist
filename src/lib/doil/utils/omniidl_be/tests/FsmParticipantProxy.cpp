// -*- C++ -*-
/*!
 * @file FsmParticipantProxy.cpp 
 * @brief IFsmParticipant CORBA proxy for doil
 * @date $Date$
 * @author This file was automatically generated form RTC.idl 
 *         by omniidl/doil backend
 *
 * $Id$
 */

#include <doil/corba/CORBAManager.h>
#include <IFsmParticipant.h>
#include <FsmParticipantProxy.h>
#include <RTCTypeConversion.h>
#include <doil/corba/BasicTypeConversion.h>

namespace RTC 
{
namespace CORBA 
{
  /*!
   * @brief ctor
   */ 
  FsmParticipantProxy::FsmParticipantProxy(::CORBA::Object_ptr obj)
   : ::doil::CORBA::CORBAProxyBase(obj),
     m_obj(::RTC::FsmParticipant::_nil()),
     m_refcount(1),
     ::RTC::CORBA::LightweightRTObjectProxy(obj),
     ::RTC::CORBA::FsmParticipantActionProxy(obj),
     ::RTC::CORBA::ComponentActionProxy(obj)//   : m_obj(::RTC::FsmParticipant::_nil()),
//     ::RTC::LightweightRTObjectProxy(obj),
//     ::RTC::FsmParticipantActionProxy(obj),
//     ::RTC::ComponentActionProxy(obj)
  {
    m_obj = ::RTC::FsmParticipant::_narrow(obj);
    if (::CORBA::is_nil(m_obj)) throw std::bad_alloc();
    m_obj = ::RTC::FsmParticipant::_duplicate(m_obj);
  }

  /*!
   * @brief dtor
   */ 
  FsmParticipantProxy::~FsmParticipantProxy()
  {
    ::CORBA::release(m_obj);
  }

  
}; // namespace CORBA
}; // namespace RTC 

extern "C"
{
  void FsmParticipantProxyCORBAInit(coil::Properties& prop)
  {
    doil::CORBA::CORBAManager& mgr(doil::CORBA::CORBAManager::instance());
    mgr.registerProxyFactory("FsmParticipantProxy",
                        doil::New< ::RTC::CORBA::FsmParticipantProxy >,
                        doil::Delete< ::RTC::CORBA::FsmParticipantProxy >);
  }
};

