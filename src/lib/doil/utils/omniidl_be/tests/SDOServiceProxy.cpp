// -*- C++ -*-
/*!
 * @file SDOServiceProxy.cpp 
 * @brief ISDOService CORBA proxy for doil
 * @date $Date$
 * @author This file was automatically generated form SDOPackage.idl 
 *         by omniidl/doil backend
 *
 * $Id$
 */

#include <doil/corba/CORBAManager.h>
#include <ISDOService.h>
#include <SDOServiceProxy.h>
#include <SDOPackageTypeConversion.h>
#include <doil/corba/BasicTypeConversion.h>

namespace SDOPackage 
{
namespace CORBA 
{
  /*!
   * @brief ctor
   */ 
  SDOServiceProxy::SDOServiceProxy(::CORBA::Object_ptr obj)
   : ::doil::CORBA::CORBAProxyBase(obj),
     m_obj(::SDOPackage::SDOService::_nil()),
     m_refcount(1)//   : m_obj(::SDOPackage::SDOService::_nil())
  {
    m_obj = ::SDOPackage::SDOService::_narrow(obj);
    if (::CORBA::is_nil(m_obj)) throw std::bad_alloc();
    m_obj = ::SDOPackage::SDOService::_duplicate(m_obj);
  }

  /*!
   * @brief dtor
   */ 
  SDOServiceProxy::~SDOServiceProxy()
  {
    ::CORBA::release(m_obj);
  }

  
}; // namespace CORBA
}; // namespace SDOPackage 

extern "C"
{
  void SDOServiceProxyCORBAInit(coil::Properties& prop)
  {
    doil::CORBA::CORBAManager& mgr(doil::CORBA::CORBAManager::instance());
    mgr.registerProxyFactory("SDOServiceProxy",
                        doil::New< ::SDOPackage::CORBA::SDOServiceProxy >,
                        doil::Delete< ::SDOPackage::CORBA::SDOServiceProxy >);
  }
};

