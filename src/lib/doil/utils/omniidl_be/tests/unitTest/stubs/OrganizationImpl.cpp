// -*- C++ -*-
/*!
 * @file OrganizationImpl.h
 * @brief OrganizationImpl C++ implementation sample for doil
 * @date $Date$
 * @author 
 *
 * $Id$
 */


#include <stdio.h>
#include <OrganizationImpl.h>
#include <iostream>
#include <sstream>
#include <string>
#include <Logger.h>

namespace UnitTest
{
namespace Servant
{
  /*!
   * @if jp
   * @class OrganizationImpl
   * @brief OrganizationServant試験用インプリメントクラス
   * @else
   * @class OrganizationImpl
   * @brief Organization implementation class for OrganizationServant' unittest.
   * @endif
   */
   int OrganizationImpl::count = 0;

    OrganizationImpl::OrganizationImpl()
    {
      ++count;
      m_logger = new Logger();
    } 
    OrganizationImpl::OrganizationImpl(Logger& aLogger)
    {
      ++count;
      m_logger = &aLogger;
    } 

    OrganizationImpl::~OrganizationImpl()
    {
    }

    ::std::string OrganizationImpl::get_organization_id()
      throw (::SDOPackage::Local::InvalidParameter,
             ::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError)
    {
        if (m_logger != NULL) 
          {
            m_logger->push("get_organization_id");
          }
        return "_id";
    }

    ::SDOPackage::Local::OrganizationProperty OrganizationImpl::get_organization_property()
      throw (::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError)
    {
        if (m_logger != NULL) 
          {
            m_logger->push("get_organization_property");
          }
        ::SDOPackage::Local::OrganizationProperty ret;
        return ret;
    }

    ::std::string OrganizationImpl::get_organization_property_value(const ::std::string& name)
      throw (::SDOPackage::Local::InvalidParameter,
             ::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError)
    {
        if (m_logger != NULL) 
          {
            m_logger->push("get_organization_property_value");
          }
        return name;
    }

    bool OrganizationImpl::add_organization_property(const ::SDOPackage::Local::OrganizationProperty& organization_property)
      throw (::SDOPackage::Local::InvalidParameter,
             ::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError)
    {
        if (m_logger != NULL) 
          {
            m_logger->push("add_organization_property");
          }
        return true;
    }

    bool OrganizationImpl::set_organization_property_value(const ::std::string&name, const ::std::string& value)
      throw (::SDOPackage::Local::InvalidParameter,
             ::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError)
    {
        if (m_logger != NULL) 
          {
            m_logger->push("set_organization_property_value");
          }
        return true;
    }

    bool OrganizationImpl::remove_organization_property(const ::std::string& name)
      throw (::SDOPackage::Local::InvalidParameter,
             ::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError)
    {
        if (m_logger != NULL) 
          {
            m_logger->push("remove_organization_property");
          }
        return true;
    }

    ::SDOPackage::Local::ISDOSystemElement* OrganizationImpl::get_owner()
      throw (::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError)
    {
        if (m_logger != NULL) 
          {
            m_logger->push("get_owner");
          }
        return NULL;
    }

    bool OrganizationImpl::set_owner(const ::SDOPackage::Local::ISDOSystemElement* sdo)
      throw (::SDOPackage::Local::InvalidParameter,
             ::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError)
    {
        if (m_logger != NULL) 
          {
            m_logger->push("set_owner");
          }
        return true;
    }

    ::SDOPackage::Local::SDOList OrganizationImpl::get_members()
      throw (::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError)
    {
        if (m_logger != NULL) 
          {
            m_logger->push("get_members");
          }
        ::SDOPackage::Local::SDOList ret;
        return ret;
    }

    bool OrganizationImpl::set_members(const ::SDOPackage::Local::SDOList& sdos)
      throw (::SDOPackage::Local::InvalidParameter,
             ::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError)
    {
        if (m_logger != NULL) 
          {
            m_logger->push("set_members");
          }
        return true;
    }

    bool OrganizationImpl::add_members(const ::SDOPackage::Local::SDOList& sdo_list)
      throw (::SDOPackage::Local::InvalidParameter,
             ::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError)
    {
        if (m_logger != NULL) 
          {
            m_logger->push("add_members");
          }
        return true;
    }

    bool OrganizationImpl::remove_member(const ::std::string& id)
      throw (::SDOPackage::Local::InvalidParameter,
             ::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError)
    {
        if (m_logger != NULL) 
          {
            m_logger->push("remove_member");
          }
        return true;
    }

    ::SDOPackage::Local::DependencyType OrganizationImpl::get_dependency()
      throw (::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError)
    {
        if (m_logger != NULL) 
          {
            m_logger->push("get_dependency");
          }
        ::SDOPackage::Local::DependencyType ret;
        return ret;
    }

    bool OrganizationImpl::set_dependency(::SDOPackage::Local::DependencyType dependency)
      throw (::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError)
    {
        if (m_logger != NULL) 
          {
            m_logger->push("set_dependency");
          }
        return true;
    }






}; // namespace Local 
}; // namespace SDOPackage 
