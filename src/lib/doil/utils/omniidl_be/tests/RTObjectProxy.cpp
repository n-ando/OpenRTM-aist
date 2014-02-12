// -*- C++ -*-
/*!
 * @file RTObjectProxy.cpp 
 * @brief IRTObject CORBA proxy for doil
 * @date $Date$
 * @author This file was automatically generated form RTC.idl 
 *         by omniidl/doil backend
 *
 * $Id$
 */

#include <doil/corba/CORBAManager.h>
#include <IRTObject.h>
#include <RTObjectProxy.h>
#include <RTCTypeConversion.h>
#include <doil/corba/BasicTypeConversion.h>

namespace RTC 
{
namespace CORBA 
{
  /*!
   * @brief ctor
   */ 
  RTObjectProxy::RTObjectProxy(::CORBA::Object_ptr obj)
   : ::doil::CORBA::CORBAProxyBase(obj),
     m_obj(::RTC::RTObject::_nil()),
     m_refcount(1),
     ::RTC::CORBA::LightweightRTObjectProxy(obj),
     ::SDOPackage::CORBA::SDOProxy(obj),
     ::RTC::CORBA::ComponentActionProxy(obj),
     ::SDOPackage::CORBA::SDOSystemElementProxy(obj)//   : m_obj(::RTC::RTObject::_nil()),
//     ::RTC::LightweightRTObjectProxy(obj),
//     ::SDOPackage::SDOProxy(obj),
//     ::RTC::ComponentActionProxy(obj),
//     ::SDOPackage::SDOSystemElementProxy(obj)
  {
    m_obj = ::RTC::RTObject::_narrow(obj);
    if (::CORBA::is_nil(m_obj)) throw std::bad_alloc();
    m_obj = ::RTC::RTObject::_duplicate(m_obj);
  }

  /*!
   * @brief dtor
   */ 
  RTObjectProxy::~RTObjectProxy()
  {
    ::CORBA::release(m_obj);
  }

  
  /*!
   * @brief get_component_profile 
   */ 
  ::RTC::Local::ComponentProfile RTObjectProxy::get_component_profile()
      throw ()
  {
    // Convert Local to CORBA.
    // (The direction of the argument is 'in' or 'inout'.)

    // Execute the method. 
    ::RTC::ComponentProfile* corba_ret;
    ::RTC::Local::ComponentProfile local_ret;
    corba_ret = m_obj->get_component_profile();

    // Convert CORBA to Local.
    // (The direction of the argument is 'out' or 'inout'.)

    // Generate the return value.
    corba_to_local(*corba_ret, local_ret);
    delete corba_ret; 
    return local_ret;
  }

  /*!
   * @brief get_ports 
   */ 
  ::RTC::Local::PortServiceList RTObjectProxy::get_ports()
      throw ()
  {
    // Convert Local to CORBA.
    // (The direction of the argument is 'in' or 'inout'.)

    // Execute the method. 
    ::RTC::PortServiceList* corba_ret;
    ::RTC::Local::PortServiceList local_ret;
    corba_ret = m_obj->get_ports();

    // Convert CORBA to Local.
    // (The direction of the argument is 'out' or 'inout'.)

    // Generate the return value.
    corba_to_local(*corba_ret, local_ret);
    delete corba_ret; 
    return local_ret;
  }

}; // namespace CORBA
}; // namespace RTC 

extern "C"
{
  void RTObjectProxyCORBAInit(coil::Properties& prop)
  {
    doil::CORBA::CORBAManager& mgr(doil::CORBA::CORBAManager::instance());
    mgr.registerProxyFactory("RTObjectProxy",
                        doil::New< ::RTC::CORBA::RTObjectProxy >,
                        doil::Delete< ::RTC::CORBA::RTObjectProxy >);
  }
};

