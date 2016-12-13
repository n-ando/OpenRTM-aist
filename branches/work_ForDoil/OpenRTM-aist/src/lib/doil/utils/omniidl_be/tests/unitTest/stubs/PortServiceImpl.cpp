// -*- C++ -*-
/*!
 * @file PortServiceImpl.h
 * @brief PortServiceImpl C++ implementation sample for doil
 * @date $Date$
 * @author 
 *
 * $Id$
 */


#include <stdio.h>
#include <PortServiceImpl.h>
#include <RTObjectImpl.h>
#include <ExecutionContextImpl.h>
#include <iostream>
#include <string>
#include <Logger.h>

namespace UnitTest
{
namespace Servant
{
  /*!
   * @if jp
   * @class PortServiceImpl
   * @brief PortServiceServant試験用インプリメントクラス
   * @else
   * @class PortServiceImpl
   * @brief PortService implementation class for PortServiceServant' unittest.
   * @endif
   */
   int PortServiceImpl::count = 0;

    PortServiceImpl::PortServiceImpl()
    {
      ++count;
      m_logger = new Logger();
    } 
    PortServiceImpl::PortServiceImpl(Logger& aLogger)
    {
      ++count;
      m_logger = &aLogger;
    } 

    PortServiceImpl::~PortServiceImpl()
    {
    }

    ::RTC::Local::PortProfile PortServiceImpl::get_port_profile()
      throw ()
    {
        if (m_logger != NULL) 
          {
            m_logger->push("get_port_profile");
          }
        ::RTC::Local::PortProfile ret;
        ret.port_ref = this;
        ret.owner = new UnitTest::Servant::RTObjectImpl();
        return ret;
    }

    ::RTC::Local::ConnectorProfileList PortServiceImpl::get_connector_profiles()
      throw ()
    {
        if (m_logger != NULL) 
          {
            m_logger->push("get_connector_profiles");
          }
        ::RTC::Local::ConnectorProfileList ret;
        return ret;
    }

    ::RTC::Local::ConnectorProfile PortServiceImpl::get_connector_profile(const ::std::string& connector_id)
      throw ()
    {
        if (m_logger != NULL) 
          {
            m_logger->push("get_connector_profile");
          }
        ::RTC::Local::ConnectorProfile ret;
        return ret;
    }

    ::RTC::Local::ReturnCode_t PortServiceImpl::connect(::RTC::Local::ConnectorProfile& connector_profile)
      throw ()
    {
        if (m_logger != NULL) 
          {
            m_logger->push("connect");
          }
        return RTC::Local::RTC_OK;
    }

    ::RTC::Local::ReturnCode_t PortServiceImpl::disconnect(const ::std::string& connector_id)
      throw ()
    {
        if (m_logger != NULL) 
          {
            m_logger->push("disconnect");
          }
        return RTC::Local::RTC_OK;
    }

    ::RTC::Local::ReturnCode_t PortServiceImpl::disconnect_all()
      throw ()
    {
        if (m_logger != NULL) 
          {
            m_logger->push("disconnect_all");
          }
        return RTC::Local::RTC_OK;
    }

    ::RTC::Local::ReturnCode_t PortServiceImpl::notify_connect(::RTC::Local::ConnectorProfile& connector_profile)
      throw ()
    {
        if (m_logger != NULL) 
          {
            m_logger->push("notify_connect");
          }
        return RTC::Local::RTC_OK;
    }

    ::RTC::Local::ReturnCode_t PortServiceImpl::notify_disconnect(const ::std::string& connector_id)
      throw ()
    {
        if (m_logger != NULL) 
          {
            m_logger->push("notify_disconnect");
          }
        return RTC::Local::RTC_OK;
    }


    
}; // namespace Local 
}; // namespace SDOPackage 
