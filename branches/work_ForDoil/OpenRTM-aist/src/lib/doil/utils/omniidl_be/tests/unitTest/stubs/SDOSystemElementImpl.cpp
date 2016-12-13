// -*- C++ -*-
/*!
 * @file SDOSystemElementImpl.h
 * @brief SDOSystemElementImpl C++ implementation sample for doil
 * @date $Date$
 * @author 
 *
 * $Id$
 */


#include <stdio.h>
#include <SDOSystemElementImpl.h>
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
   * @class SDOSystemElementImpl
   * @brief SDOSystemElementServant試験用インプリメントクラス
   * @else
   * @class SDOSystemElementImpl
   * @brief SDOSystemElement implementation class for LightweightRTObjecServant' unittest.
   * @endif
   */
   int SDOSystemElementImpl::count = 0;

    SDOSystemElementImpl::SDOSystemElementImpl()
    {
      sprintf(m_name, "%s", id());
      ++count;
      m_logger = new Logger();
    } 
    SDOSystemElementImpl::SDOSystemElementImpl(Logger& aLogger)
    {
      sprintf(m_name, "%s", id());
      ++count;
      m_logger = &aLogger;
    } 

    SDOSystemElementImpl::~SDOSystemElementImpl()
    {
    }

    ::SDOPackage::Local::OrganizationList SDOSystemElementImpl::get_owned_organizations()
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
