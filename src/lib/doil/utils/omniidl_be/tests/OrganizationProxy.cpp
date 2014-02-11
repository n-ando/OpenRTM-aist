// -*- C++ -*-
/*!
 * @file OrganizationProxy.cpp 
 * @brief IOrganization CORBA proxy for doil
 * @date $Date$
 * @author This file was automatically generated form SDOPackage.idl 
 *         by omniidl/doil backend
 *
 * $Id$
 */

#include <doil/corba/CORBAManager.h>
#include <IOrganization.h>
#include <OrganizationProxy.h>
#include <SDOPackageTypeConversion.h>
#include <doil/corba/BasicTypeConversion.h>

namespace SDOPackage 
{
namespace CORBA 
{
  /*!
   * @brief ctor
   */ 
  OrganizationProxy::OrganizationProxy(::CORBA::Object_ptr obj)
   : ::doil::CORBA::CORBAProxyBase(obj),
     m_obj(::SDOPackage::Organization::_nil()),
     m_refcount(1)//   : m_obj(::SDOPackage::Organization::_nil())
  {
    m_obj = ::SDOPackage::Organization::_narrow(obj);
    if (::CORBA::is_nil(m_obj)) throw std::bad_alloc();
    m_obj = ::SDOPackage::Organization::_duplicate(m_obj);
  }

  /*!
   * @brief dtor
   */ 
  OrganizationProxy::~OrganizationProxy()
  {
    ::CORBA::release(m_obj);
  }

  
  /*!
   * @brief get_organization_id 
   */ 
  ::std::string OrganizationProxy::get_organization_id()
      throw (::SDOPackage::Local::InvalidParameter,
             ::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError)
  {
    // Convert Local to CORBA.
    // (The direction of the argument is 'in' or 'inout'.)

    // Execute the method. 
    char* corba_ret;
    ::std::string local_ret;
    corba_ret = m_obj->get_organization_id();

    // Convert CORBA to Local.
    // (The direction of the argument is 'out' or 'inout'.)

    // Generate the return value.
    corba_to_local(corba_ret, local_ret);
    ::CORBA::string_free(corba_ret); 
    return local_ret;
  }

  /*!
   * @brief get_organization_property 
   */ 
  ::SDOPackage::Local::OrganizationProperty OrganizationProxy::get_organization_property()
      throw (::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError)
  {
    // Convert Local to CORBA.
    // (The direction of the argument is 'in' or 'inout'.)

    // Execute the method. 
    ::SDOPackage::OrganizationProperty* corba_ret;
    ::SDOPackage::Local::OrganizationProperty local_ret;
    corba_ret = m_obj->get_organization_property();

    // Convert CORBA to Local.
    // (The direction of the argument is 'out' or 'inout'.)

    // Generate the return value.
    corba_to_local(*corba_ret, local_ret);
    delete corba_ret; 
    return local_ret;
  }

  /*!
   * @brief get_organization_property_value 
   */ 
  ::std::string OrganizationProxy::get_organization_property_value(const ::std::string& name)
      throw (::SDOPackage::Local::InvalidParameter,
             ::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError)
  {
    // Convert Local to CORBA.
    // (The direction of the argument is 'in' or 'inout'.)
    char* _name;
    local_to_corba(name, _name);

    // Execute the method. 
    ::CORBA::Any* corba_ret;
    ::std::string local_ret;
    corba_ret = m_obj->get_organization_property_value(_name);

    // Convert CORBA to Local.
    // (The direction of the argument is 'out' or 'inout'.)

    // Generate the return value.
    corba_to_local(*corba_ret, local_ret);
    delete corba_ret; 
    return local_ret;
  }

  /*!
   * @brief add_organization_property 
   */ 
  bool OrganizationProxy::add_organization_property(const ::SDOPackage::Local::OrganizationProperty& organization_property)
      throw (::SDOPackage::Local::InvalidParameter,
             ::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError)
  {
    // Convert Local to CORBA.
    // (The direction of the argument is 'in' or 'inout'.)
    ::SDOPackage::OrganizationProperty _organization_property;
    local_to_corba(organization_property, _organization_property);

    // Execute the method. 
    ::CORBA::Boolean corba_ret;
    bool local_ret;
    corba_ret = m_obj->add_organization_property(_organization_property);

    // Convert CORBA to Local.
    // (The direction of the argument is 'out' or 'inout'.)

    // Generate the return value.
//    local_ret = corba_ret;
    corba_to_local(corba_ret, local_ret);
    return local_ret;
  }

  /*!
   * @brief set_organization_property_value 
   */ 
  bool OrganizationProxy::set_organization_property_value(const ::std::string& name, const ::std::string& value)
      throw (::SDOPackage::Local::InvalidParameter,
             ::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError)
  {
    // Convert Local to CORBA.
    // (The direction of the argument is 'in' or 'inout'.)
    char* _name;
    ::CORBA::Any _value;
    local_to_corba(name, _name);
    local_to_corba(value, _value);

    // Execute the method. 
    ::CORBA::Boolean corba_ret;
    bool local_ret;
    corba_ret = m_obj->set_organization_property_value(_name, _value);

    // Convert CORBA to Local.
    // (The direction of the argument is 'out' or 'inout'.)

    // Generate the return value.
//    local_ret = corba_ret;
    corba_to_local(corba_ret, local_ret);
    return local_ret;
  }

  /*!
   * @brief remove_organization_property 
   */ 
  bool OrganizationProxy::remove_organization_property(const ::std::string& name)
      throw (::SDOPackage::Local::InvalidParameter,
             ::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError)
  {
    // Convert Local to CORBA.
    // (The direction of the argument is 'in' or 'inout'.)
    char* _name;
    local_to_corba(name, _name);

    // Execute the method. 
    ::CORBA::Boolean corba_ret;
    bool local_ret;
    corba_ret = m_obj->remove_organization_property(_name);

    // Convert CORBA to Local.
    // (The direction of the argument is 'out' or 'inout'.)

    // Generate the return value.
//    local_ret = corba_ret;
    corba_to_local(corba_ret, local_ret);
    return local_ret;
  }

  /*!
   * @brief get_owner 
   */ 
  ::SDOPackage::Local::ISDOSystemElement* OrganizationProxy::get_owner()
      throw (::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError)
  {
    // Convert Local to CORBA.
    // (The direction of the argument is 'in' or 'inout'.)

    // Execute the method. 
    ::SDOPackage::SDOSystemElement_ptr corba_ret;
    ::SDOPackage::Local::ISDOSystemElement* local_ret;
    corba_ret = m_obj->get_owner();

    // Convert CORBA to Local.
    // (The direction of the argument is 'out' or 'inout'.)

    // Generate the return value.
    corba_to_local(corba_ret, local_ret);
    ::CORBA::release(corba_ret);
    return local_ret;
  }

  /*!
   * @brief set_owner 
   */ 
  bool OrganizationProxy::set_owner(const ::SDOPackage::Local::ISDOSystemElement* sdo)
      throw (::SDOPackage::Local::InvalidParameter,
             ::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError)
  {
    // Convert Local to CORBA.
    // (The direction of the argument is 'in' or 'inout'.)
    ::SDOPackage::SDOSystemElement_ptr _sdo;
    local_to_corba(const_cast< ::SDOPackage::Local::ISDOSystemElement* >(sdo), _sdo);

    // Execute the method. 
    ::CORBA::Boolean corba_ret;
    bool local_ret;
    corba_ret = m_obj->set_owner(_sdo);

    // Convert CORBA to Local.
    // (The direction of the argument is 'out' or 'inout'.)

    // Generate the return value.
//    local_ret = corba_ret;
    corba_to_local(corba_ret, local_ret);
    return local_ret;
  }

  /*!
   * @brief get_members 
   */ 
  ::SDOPackage::Local::SDOList OrganizationProxy::get_members()
      throw (::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError)
  {
    // Convert Local to CORBA.
    // (The direction of the argument is 'in' or 'inout'.)

    // Execute the method. 
    ::SDOPackage::SDOList* corba_ret;
    ::SDOPackage::Local::SDOList local_ret;
    corba_ret = m_obj->get_members();

    // Convert CORBA to Local.
    // (The direction of the argument is 'out' or 'inout'.)

    // Generate the return value.
    corba_to_local(*corba_ret, local_ret);
    delete corba_ret; 
    return local_ret;
  }

  /*!
   * @brief set_members 
   */ 
  bool OrganizationProxy::set_members(const ::SDOPackage::Local::SDOList& sdos)
      throw (::SDOPackage::Local::InvalidParameter,
             ::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError)
  {
    // Convert Local to CORBA.
    // (The direction of the argument is 'in' or 'inout'.)
    ::SDOPackage::SDOList _sdos;
    local_to_corba(sdos, _sdos);

    // Execute the method. 
    ::CORBA::Boolean corba_ret;
    bool local_ret;
    corba_ret = m_obj->set_members(_sdos);

    // Convert CORBA to Local.
    // (The direction of the argument is 'out' or 'inout'.)

    // Generate the return value.
//    local_ret = corba_ret;
    corba_to_local(corba_ret, local_ret);
    return local_ret;
  }

  /*!
   * @brief add_members 
   */ 
  bool OrganizationProxy::add_members(const ::SDOPackage::Local::SDOList& sdo_list)
      throw (::SDOPackage::Local::InvalidParameter,
             ::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError)
  {
    // Convert Local to CORBA.
    // (The direction of the argument is 'in' or 'inout'.)
    ::SDOPackage::SDOList _sdo_list;
    local_to_corba(sdo_list, _sdo_list);

    // Execute the method. 
    ::CORBA::Boolean corba_ret;
    bool local_ret;
    corba_ret = m_obj->add_members(_sdo_list);

    // Convert CORBA to Local.
    // (The direction of the argument is 'out' or 'inout'.)

    // Generate the return value.
//    local_ret = corba_ret;
    corba_to_local(corba_ret, local_ret);
    return local_ret;
  }

  /*!
   * @brief remove_member 
   */ 
  bool OrganizationProxy::remove_member(const ::std::string& id)
      throw (::SDOPackage::Local::InvalidParameter,
             ::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError)
  {
    // Convert Local to CORBA.
    // (The direction of the argument is 'in' or 'inout'.)
    char* _id;
    local_to_corba(id, _id);

    // Execute the method. 
    ::CORBA::Boolean corba_ret;
    bool local_ret;
    corba_ret = m_obj->remove_member(_id);

    // Convert CORBA to Local.
    // (The direction of the argument is 'out' or 'inout'.)

    // Generate the return value.
//    local_ret = corba_ret;
    corba_to_local(corba_ret, local_ret);
    return local_ret;
  }

  /*!
   * @brief get_dependency 
   */ 
  ::SDOPackage::Local::DependencyType OrganizationProxy::get_dependency()
      throw (::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError)
  {
    // Convert Local to CORBA.
    // (The direction of the argument is 'in' or 'inout'.)

    // Execute the method. 
    ::SDOPackage::DependencyType corba_ret;
    ::SDOPackage::Local::DependencyType local_ret;
    corba_ret = m_obj->get_dependency();

    // Convert CORBA to Local.
    // (The direction of the argument is 'out' or 'inout'.)

    // Generate the return value.
    corba_to_local(corba_ret, local_ret);
    return local_ret;
  }

  /*!
   * @brief set_dependency 
   */ 
  bool OrganizationProxy::set_dependency(::SDOPackage::Local::DependencyType dependency)
      throw (::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError)
  {
    // Convert Local to CORBA.
    // (The direction of the argument is 'in' or 'inout'.)
    ::SDOPackage::DependencyType _dependency;
    local_to_corba(dependency, _dependency);

    // Execute the method. 
    ::CORBA::Boolean corba_ret;
    bool local_ret;
    corba_ret = m_obj->set_dependency(_dependency);

    // Convert CORBA to Local.
    // (The direction of the argument is 'out' or 'inout'.)

    // Generate the return value.
//    local_ret = corba_ret;
    corba_to_local(corba_ret, local_ret);
    return local_ret;
  }

}; // namespace CORBA
}; // namespace SDOPackage 

extern "C"
{
  void OrganizationProxyCORBAInit(coil::Properties& prop)
  {
    doil::CORBA::CORBAManager& mgr(doil::CORBA::CORBAManager::instance());
    mgr.registerProxyFactory("OrganizationProxy",
                        doil::New< ::SDOPackage::CORBA::OrganizationProxy >,
                        doil::Delete< ::SDOPackage::CORBA::OrganizationProxy >);
  }
};

