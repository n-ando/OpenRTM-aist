// -*- C++ -*-
/*!
 * @file SDOSystemElementProxy.cpp 
 * @brief ISDOSystemElement CORBA proxy for doil
 * @date $Date$
 * @author This file was automatically generated form SDOPackage.idl 
 *         by omniidl/doil backend
 *
 * $Id$
 */

#include <doil/corba/CORBAManager.h>
#include <ISDOSystemElement.h>
#include <SDOSystemElementProxy.h>
#include <SDOPackageTypeConversion.h>
#include <doil/corba/BasicTypeConversion.h>

namespace SDOPackage 
{
namespace CORBA 
{
  /*!
   * @brief ctor
   */ 
  SDOSystemElementProxy::SDOSystemElementProxy(::CORBA::Object_ptr obj)
   : ::doil::CORBA::CORBAProxyBase(obj),
     m_obj(::SDOPackage::SDOSystemElement::_nil()),
     m_refcount(1)//   : m_obj(::SDOPackage::SDOSystemElement::_nil())
  {
    m_obj = ::SDOPackage::SDOSystemElement::_narrow(obj);
    if (::CORBA::is_nil(m_obj)) throw std::bad_alloc();
    m_obj = ::SDOPackage::SDOSystemElement::_duplicate(m_obj);
  }

  /*!
   * @brief dtor
   */ 
  SDOSystemElementProxy::~SDOSystemElementProxy()
  {
    ::CORBA::release(m_obj);
  }

  
  /*!
   * @brief get_owned_organizations 
   */ 
  ::SDOPackage::Local::OrganizationList SDOSystemElementProxy::get_owned_organizations()
      throw (::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError)
  {
    // Convert Local to CORBA.
    // (The direction of the argument is 'in' or 'inout'.)

    // Execute the method. 
    ::SDOPackage::OrganizationList* corba_ret;
    ::SDOPackage::Local::OrganizationList local_ret;
    corba_ret = m_obj->get_owned_organizations();

    // Convert CORBA to Local.
    // (The direction of the argument is 'out' or 'inout'.)

    // Generate the return value.
    corba_to_local(*corba_ret, local_ret);
    delete corba_ret; 
    return local_ret;
  }

}; // namespace CORBA
}; // namespace SDOPackage 

extern "C"
{
  void SDOSystemElementProxyCORBAInit(coil::Properties& prop)
  {
    doil::CORBA::CORBAManager& mgr(doil::CORBA::CORBAManager::instance());
    mgr.registerProxyFactory("SDOSystemElementProxy",
                        doil::New< ::SDOPackage::CORBA::SDOSystemElementProxy >,
                        doil::Delete< ::SDOPackage::CORBA::SDOSystemElementProxy >);
  }
};

