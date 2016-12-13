// -*- C++ -*-
/*!
 * @file SDOProxy.cpp 
 * @brief ISDO CORBA proxy for doil
 * @date $Date$
 * @author This file was automatically generated form SDOPackage.idl 
 *         by omniidl/doil backend
 *
 * $Id$
 */

#include <doil/corba/CORBAManager.h>
#include <ISDO.h>
#include <SDOProxy.h>
#include <SDOPackageTypeConversion.h>
#include <doil/corba/BasicTypeConversion.h>

namespace SDOPackage 
{
namespace CORBA 
{
  /*!
   * @brief ctor
   */ 
  SDOProxy::SDOProxy(::CORBA::Object_ptr obj)
   : ::doil::CORBA::CORBAProxyBase(obj),
     m_obj(::SDOPackage::SDO::_nil()),
     m_refcount(1),
     ::SDOPackage::CORBA::SDOSystemElementProxy(obj)//   : m_obj(::SDOPackage::SDO::_nil()),
//     ::SDOPackage::SDOSystemElementProxy(obj)
  {
    m_obj = ::SDOPackage::SDO::_narrow(obj);
    if (::CORBA::is_nil(m_obj)) throw std::bad_alloc();
    m_obj = ::SDOPackage::SDO::_duplicate(m_obj);
  }

  /*!
   * @brief dtor
   */ 
  SDOProxy::~SDOProxy()
  {
    ::CORBA::release(m_obj);
  }

  
  /*!
   * @brief get_sdo_id 
   */ 
  ::std::string SDOProxy::get_sdo_id()
      throw (::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError)
  {
    // Convert Local to CORBA.
    // (The direction of the argument is 'in' or 'inout'.)

    // Execute the method. 
    char* corba_ret;
    ::std::string local_ret;
    corba_ret = m_obj->get_sdo_id();

    // Convert CORBA to Local.
    // (The direction of the argument is 'out' or 'inout'.)

    // Generate the return value.
    corba_to_local(corba_ret, local_ret);
    ::CORBA::string_free(corba_ret); 
    return local_ret;
  }

  /*!
   * @brief get_sdo_type 
   */ 
  ::std::string SDOProxy::get_sdo_type()
      throw (::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError)
  {
    // Convert Local to CORBA.
    // (The direction of the argument is 'in' or 'inout'.)

    // Execute the method. 
    char* corba_ret;
    ::std::string local_ret;
    corba_ret = m_obj->get_sdo_type();

    // Convert CORBA to Local.
    // (The direction of the argument is 'out' or 'inout'.)

    // Generate the return value.
    corba_to_local(corba_ret, local_ret);
    ::CORBA::string_free(corba_ret); 
    return local_ret;
  }

  /*!
   * @brief get_device_profile 
   */ 
  ::SDOPackage::Local::DeviceProfile SDOProxy::get_device_profile()
      throw (::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError)
  {
    // Convert Local to CORBA.
    // (The direction of the argument is 'in' or 'inout'.)

    // Execute the method. 
    ::SDOPackage::DeviceProfile* corba_ret;
    ::SDOPackage::Local::DeviceProfile local_ret;
    corba_ret = m_obj->get_device_profile();

    // Convert CORBA to Local.
    // (The direction of the argument is 'out' or 'inout'.)

    // Generate the return value.
    corba_to_local(*corba_ret, local_ret);
    delete corba_ret; 
    return local_ret;
  }

  /*!
   * @brief get_service_profiles 
   */ 
  ::SDOPackage::Local::ServiceProfileList SDOProxy::get_service_profiles()
      throw (::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError)
  {
    // Convert Local to CORBA.
    // (The direction of the argument is 'in' or 'inout'.)

    // Execute the method. 
    ::SDOPackage::ServiceProfileList* corba_ret;
    ::SDOPackage::Local::ServiceProfileList local_ret;
    corba_ret = m_obj->get_service_profiles();

    // Convert CORBA to Local.
    // (The direction of the argument is 'out' or 'inout'.)

    // Generate the return value.
    corba_to_local(*corba_ret, local_ret);
    delete corba_ret; 
    return local_ret;
  }

  /*!
   * @brief get_service_profile 
   */ 
  ::SDOPackage::Local::ServiceProfile SDOProxy::get_service_profile(const ::std::string& id)
      throw (::SDOPackage::Local::InvalidParameter,
             ::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError)
  {
    // Convert Local to CORBA.
    // (The direction of the argument is 'in' or 'inout'.)
    char* _id;
    local_to_corba(id, _id);

    // Execute the method. 
    ::SDOPackage::ServiceProfile* corba_ret;
    ::SDOPackage::Local::ServiceProfile local_ret;
    corba_ret = m_obj->get_service_profile(_id);

    // Convert CORBA to Local.
    // (The direction of the argument is 'out' or 'inout'.)

    // Generate the return value.
    corba_to_local(*corba_ret, local_ret);
    delete corba_ret; 
    return local_ret;
  }

  /*!
   * @brief get_sdo_service 
   */ 
  ::SDOPackage::Local::ISDOService* SDOProxy::get_sdo_service(const ::std::string& id)
      throw (::SDOPackage::Local::InvalidParameter,
             ::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError)
  {
    // Convert Local to CORBA.
    // (The direction of the argument is 'in' or 'inout'.)
    char* _id;
    local_to_corba(id, _id);

    // Execute the method. 
    ::SDOPackage::SDOService_ptr corba_ret;
    ::SDOPackage::Local::ISDOService* local_ret;
    corba_ret = m_obj->get_sdo_service(_id);

    // Convert CORBA to Local.
    // (The direction of the argument is 'out' or 'inout'.)

    // Generate the return value.
    corba_to_local(corba_ret, local_ret);
    ::CORBA::release(corba_ret);
    return local_ret;
  }

  /*!
   * @brief get_configuration 
   */ 
  ::SDOPackage::Local::IConfiguration* SDOProxy::get_configuration()
      throw (::SDOPackage::Local::InterfaceNotImplemented,
             ::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError)
  {
    // Convert Local to CORBA.
    // (The direction of the argument is 'in' or 'inout'.)

    // Execute the method. 
    ::SDOPackage::Configuration_ptr corba_ret;
    ::SDOPackage::Local::IConfiguration* local_ret;
    corba_ret = m_obj->get_configuration();

    // Convert CORBA to Local.
    // (The direction of the argument is 'out' or 'inout'.)

    // Generate the return value.
    corba_to_local(corba_ret, local_ret);
    ::CORBA::release(corba_ret);
    return local_ret;
  }

  /*!
   * @brief get_monitoring 
   */ 
  ::SDOPackage::Local::IMonitoring* SDOProxy::get_monitoring()
      throw (::SDOPackage::Local::InterfaceNotImplemented,
             ::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError)
  {
    // Convert Local to CORBA.
    // (The direction of the argument is 'in' or 'inout'.)

    // Execute the method. 
    ::SDOPackage::Monitoring_ptr corba_ret;
    ::SDOPackage::Local::IMonitoring* local_ret;
    corba_ret = m_obj->get_monitoring();

    // Convert CORBA to Local.
    // (The direction of the argument is 'out' or 'inout'.)

    // Generate the return value.
    corba_to_local(corba_ret, local_ret);
    ::CORBA::release(corba_ret);
    return local_ret;
  }

  /*!
   * @brief get_organizations 
   */ 
  ::SDOPackage::Local::OrganizationList SDOProxy::get_organizations()
      throw (::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError)
  {
    // Convert Local to CORBA.
    // (The direction of the argument is 'in' or 'inout'.)

    // Execute the method. 
    ::SDOPackage::OrganizationList* corba_ret;
    ::SDOPackage::Local::OrganizationList local_ret;
    corba_ret = m_obj->get_organizations();

    // Convert CORBA to Local.
    // (The direction of the argument is 'out' or 'inout'.)

    // Generate the return value.
    corba_to_local(*corba_ret, local_ret);
    delete corba_ret; 
    return local_ret;
  }

  /*!
   * @brief get_status_list 
   */ 
  ::SDOPackage::Local::NVList SDOProxy::get_status_list()
      throw (::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError)
  {
    // Convert Local to CORBA.
    // (The direction of the argument is 'in' or 'inout'.)

    // Execute the method. 
    ::SDOPackage::NVList* corba_ret;
    ::SDOPackage::Local::NVList local_ret;
    corba_ret = m_obj->get_status_list();

    // Convert CORBA to Local.
    // (The direction of the argument is 'out' or 'inout'.)

    // Generate the return value.
    corba_to_local(*corba_ret, local_ret);
    delete corba_ret; 
    return local_ret;
  }

  /*!
   * @brief get_status 
   */ 
  ::std::string SDOProxy::get_status(const ::std::string& nme)
      throw (::SDOPackage::Local::InvalidParameter,
             ::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError)
  {
    // Convert Local to CORBA.
    // (The direction of the argument is 'in' or 'inout'.)
    char* _nme;
    local_to_corba(nme, _nme);

    // Execute the method. 
    ::CORBA::Any* corba_ret;
    ::std::string local_ret;
    corba_ret = m_obj->get_status(_nme);

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
  void SDOProxyCORBAInit(coil::Properties& prop)
  {
    doil::CORBA::CORBAManager& mgr(doil::CORBA::CORBAManager::instance());
    mgr.registerProxyFactory("SDOProxy",
                        doil::New< ::SDOPackage::CORBA::SDOProxy >,
                        doil::Delete< ::SDOPackage::CORBA::SDOProxy >);
  }
};

