// -*- C++ -*-
/*!
 * @file SDOImpl.h
 * @brief SDOImpl C++ implementation sample for doil
 * @date $Date$
 * @author 
 *
 * $Id$
 */


#include <stdio.h>
#include <SDOImpl.h>
#include <SDOServiceImpl.h>
#include <ConfigurationImpl.h>
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
   * @class SDOImpl
   * @brief SDOServant試験用インプリメントクラス
   * @else
   * @class SDOImpl
   * @brief SDO implementation class for LightweightRTObjecServant' unittest.
   * @endif
   */
   int SDOImpl::count = 0;

    SDOImpl::SDOImpl()
    {
      ++count;
      m_logger = new Logger();
      m_sdos = new UnitTest::Servant::SDOServiceImpl();
    } 
    SDOImpl::SDOImpl(Logger& aLogger)
    {
      ++count;
      m_logger = &aLogger;
    } 

    SDOImpl::~SDOImpl()
    {
    }

    ::std::string SDOImpl::get_sdo_id()
      throw (::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError)
    {
        if (m_logger != NULL) 
          {
            m_logger->push("get_sdo_id");
          }
        return "bar";
    }

    ::std::string SDOImpl::get_sdo_type()
      throw (::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError)
    {
        if (m_logger != NULL) 
          {
            m_logger->push("get_sdo_type");
          }
        return "bar";
    }

    ::SDOPackage::Local::DeviceProfile SDOImpl::get_device_profile()
      throw (::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError)
    {
        if (m_logger != NULL) 
          {
            m_logger->push("get_device_profile");
          }
        ::SDOPackage::Local::DeviceProfile prof;
        return prof;
    }

    ::SDOPackage::Local::ServiceProfileList SDOImpl::get_service_profiles()
      throw (::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError)
    {
        if (m_logger != NULL) 
          {
            m_logger->push("get_service_profiles");
          }
        ::SDOPackage::Local::ServiceProfileList profs;
        return profs;
    }

    ::SDOPackage::Local::ServiceProfile SDOImpl::get_service_profile(const ::std::string& id)
      throw (::SDOPackage::Local::InvalidParameter,
             ::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError)
    {
        if (m_logger != NULL) 
          {
            m_logger->push("get_service_profile");
          }

        ::SDOPackage::Local::NameValue nv;
         nv.name="foo";
         nv.value="bar";
std::cout<<"1"<<std::endl;
        ::SDOPackage::Local::ServiceProfile prof;
std::cout<<"2"<<std::endl;
        prof.id = "foo";
        prof.interface_type = "bar";
        prof.properties.push_back(nv);
        prof.service = m_sdos;
std::cout<<"3:"<<prof.service<<std::endl;
        return prof;
    }

    ::SDOPackage::Local::ISDOService* SDOImpl::get_sdo_service(const ::std::string& id)
      throw (::SDOPackage::Local::InvalidParameter,
             ::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError)
    {
        if (m_logger != NULL) 
          {
            m_logger->push("get_sdo_service");
          }
        ::SDOPackage::Local::ISDOService* ret = m_sdos;
        return m_sdos;
        return ret;
    }

    ::SDOPackage::Local::IConfiguration* SDOImpl::get_configuration()
      throw (::SDOPackage::Local::InterfaceNotImplemented,
             ::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError)
    {
        if (m_logger != NULL) 
          {
            m_logger->push("get_configuration");
          }
        ::SDOPackage::Local::IConfiguration * ret = new UnitTest::Servant::ConfigurationImpl() ;
        return ret;
    }

    ::SDOPackage::Local::IMonitoring* SDOImpl::get_monitoring()
      throw (::SDOPackage::Local::InterfaceNotImplemented,
             ::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError)
    {
        if (m_logger != NULL) 
          {
            m_logger->push("get_monitoring");
          }
        ::SDOPackage::Local::IMonitoring* ret;
        return ret;
    }

    ::SDOPackage::Local::OrganizationList SDOImpl::get_organizations()
      throw (::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError)
    {
        if (m_logger != NULL) 
          {
            m_logger->push("get_organizations");
          }
        ::SDOPackage::Local::OrganizationList ret;
        return ret;
    }

    ::SDOPackage::Local::NVList SDOImpl::get_status_list()
      throw (::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError)
    {
        if (m_logger != NULL) 
          {
            m_logger->push("get_status_list");
          }
        ::SDOPackage::Local::NVList ret;
        return ret;
    }


    ::std::string SDOImpl::get_status(const ::std::string& nme)
      throw (::SDOPackage::Local::InvalidParameter,
             ::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError)
    {
        if (m_logger != NULL) 
          {
            m_logger->push("get_status");
          }
        return "bar";
    }


    //
    ::SDOPackage::Local::OrganizationList SDOImpl::get_owned_organizations()
      throw (::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError)
    {
        if (m_logger != NULL) 
          {
            m_logger->push("get_owned_organizations");
          }
        ::SDOPackage::Local::OrganizationList ret;
        return ret;
    }




}; // namespace Local 
}; // namespace SDOPackage 
