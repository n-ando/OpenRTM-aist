// -*- C++ -*-
/*!
 * @file ModeProxy.cpp 
 * @brief IMode CORBA proxy for doil
 * @date $Date$
 * @author This file was automatically generated form RTC.idl 
 *         by omniidl/doil backend
 *
 * $Id$
 */

#include <doil/corba/CORBAManager.h>
#include <IMode.h>
#include <ModeProxy.h>
#include <RTCTypeConversion.h>
#include <doil/corba/BasicTypeConversion.h>

namespace RTC 
{
namespace CORBA 
{
  /*!
   * @brief ctor
   */ 
  ModeProxy::ModeProxy(::CORBA::Object_ptr obj)
   : ::doil::CORBA::CORBAProxyBase(obj),
     m_obj(::RTC::Mode::_nil()),
     m_refcount(1)//   : m_obj(::RTC::Mode::_nil())
  {
    m_obj = ::RTC::Mode::_narrow(obj);
    if (::CORBA::is_nil(m_obj)) throw std::bad_alloc();
    m_obj = ::RTC::Mode::_duplicate(m_obj);
  }

  /*!
   * @brief dtor
   */ 
  ModeProxy::~ModeProxy()
  {
    ::CORBA::release(m_obj);
  }

  
}; // namespace CORBA
}; // namespace RTC 

extern "C"
{
  void ModeProxyCORBAInit(coil::Properties& prop)
  {
    doil::CORBA::CORBAManager& mgr(doil::CORBA::CORBAManager::instance());
    mgr.registerProxyFactory("ModeProxy",
                        doil::New< ::RTC::CORBA::ModeProxy >,
                        doil::Delete< ::RTC::CORBA::ModeProxy >);
  }
};

