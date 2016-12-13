// -*- C++ -*-
/*!
 * @file OrganizationImpl.h
 * @brief OrganizationImpl C++ implementation sample for doil
 * @date $Date$
 * @author 
 *
 * $Id$
 */

#ifndef ORGANIZATION_IMPL_H
#define ORGANIZATION_IMPL_H


#include <doil/ImplBase.h>
#include <IOrganization.h>
#include <Logger.h>

namespace UnitTest
{
namespace Servant
{

  /*!
   * @if jp
   * @class OrganizationImpl
   * @brief Organization試験用インプリメントクラス
   * @else
   * @class OrganizationImpl
   * @brief Organization implementation class for OrganizationServant' unittest.
   * @endif
   */

  class OrganizationImpl
   : public virtual doil::ImplBase,
     public virtual ::SDOPackage::Local::IOrganization

  {
  public:
    OrganizationImpl();
    OrganizationImpl(Logger& aLogger);

    virtual ~OrganizationImpl();
    
    virtual ::std::string get_organization_id()
      throw (::SDOPackage::Local::InvalidParameter,
             ::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError);

    virtual ::SDOPackage::Local::OrganizationProperty get_organization_property()
      throw (::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError);

    virtual ::std::string get_organization_property_value(const ::std::string& name)
      throw (::SDOPackage::Local::InvalidParameter,
             ::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError);

    virtual bool add_organization_property(const ::SDOPackage::Local::OrganizationProperty& organization_property)
      throw (::SDOPackage::Local::InvalidParameter,
             ::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError);

    virtual bool set_organization_property_value(const ::std::string&name, const ::std::string& value)
      throw (::SDOPackage::Local::InvalidParameter,
             ::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError);

    virtual bool remove_organization_property(const ::std::string& name)
      throw (::SDOPackage::Local::InvalidParameter,
             ::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError);

    virtual ::SDOPackage::Local::ISDOSystemElement* get_owner()
      throw (::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError);

    virtual bool set_owner(const ::SDOPackage::Local::ISDOSystemElement* sdo)
      throw (::SDOPackage::Local::InvalidParameter,
             ::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError);

    virtual ::SDOPackage::Local::SDOList get_members()
      throw (::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError);

    virtual bool set_members(const ::SDOPackage::Local::SDOList& sdos)
      throw (::SDOPackage::Local::InvalidParameter,
             ::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError);

    virtual bool add_members(const ::SDOPackage::Local::SDOList& sdo_list)
      throw (::SDOPackage::Local::InvalidParameter,
             ::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError);

    virtual bool remove_member(const ::std::string& id)
      throw (::SDOPackage::Local::InvalidParameter,
             ::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError);

    virtual ::SDOPackage::Local::DependencyType get_dependency()
      throw (::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError);

    virtual bool set_dependency(::SDOPackage::Local::DependencyType dependency)
      throw (::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError);


    const char* id() { return "Organization"; }
    const char* name() { return m_name; }
    void incRef() { refcount++; }
    void decRef() { refcount--; }
  private:
    static int count;
    char m_name[32];
    int refcount;
    Logger *m_logger;
  };

}; // namespace Servant
}; // namespace UnitTest

#endif  // 
