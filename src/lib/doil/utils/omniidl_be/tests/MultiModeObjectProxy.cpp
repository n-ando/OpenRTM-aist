// -*- C++ -*-
/*!
 * @file MultiModeObjectProxy.cpp 
 * @brief IMultiModeObject CORBA proxy for doil
 * @date $Date$
 * @author This file was automatically generated form RTC.idl 
 *         by omniidl/doil backend
 *
 * $Id$
 */

#include <doil/corba/CORBAManager.h>
#include <IMultiModeObject.h>
#include <MultiModeObjectProxy.h>
#include <RTCTypeConversion.h>
#include <doil/corba/BasicTypeConversion.h>

namespace RTC 
{
namespace CORBA 
{
  /*!
   * @brief ctor
   */ 
  MultiModeObjectProxy::MultiModeObjectProxy(::CORBA::Object_ptr obj)
   : ::doil::CORBA::CORBAProxyBase(obj),
     m_obj(::RTC::MultiModeObject::_nil()),
     m_refcount(1),
     ::RTC::CORBA::LightweightRTObjectProxy(obj),
     ::RTC::CORBA::ModeCapableProxy(obj),
     ::RTC::CORBA::MultiModeComponentActionProxy(obj),
     ::RTC::CORBA::ComponentActionProxy(obj)//   : m_obj(::RTC::MultiModeObject::_nil()),
//     ::RTC::LightweightRTObjectProxy(obj),
//     ::RTC::ModeCapableProxy(obj),
//     ::RTC::MultiModeComponentActionProxy(obj),
//     ::RTC::ComponentActionProxy(obj)
  {
    m_obj = ::RTC::MultiModeObject::_narrow(obj);
    if (::CORBA::is_nil(m_obj)) throw std::bad_alloc();
    m_obj = ::RTC::MultiModeObject::_duplicate(m_obj);
  }

  /*!
   * @brief dtor
   */ 
  MultiModeObjectProxy::~MultiModeObjectProxy()
  {
    ::CORBA::release(m_obj);
  }

  
}; // namespace CORBA
}; // namespace RTC 

extern "C"
{
  void MultiModeObjectProxyCORBAInit(coil::Properties& prop)
  {
    doil::CORBA::CORBAManager& mgr(doil::CORBA::CORBAManager::instance());
    mgr.registerProxyFactory("MultiModeObjectProxy",
                        doil::New< ::RTC::CORBA::MultiModeObjectProxy >,
                        doil::Delete< ::RTC::CORBA::MultiModeObjectProxy >);
  }
};

