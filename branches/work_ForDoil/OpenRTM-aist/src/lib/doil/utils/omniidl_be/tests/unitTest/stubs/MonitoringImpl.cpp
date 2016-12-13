// -*- C++ -*-
/*!
 * @file MonitoringImpl.h
 * @brief MonitoringImpl C++ implementation sample for doil
 * @date $Date$
 * @author 
 *
 * $Id$
 */


#include <stdio.h>
#include <MonitoringImpl.h>
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
   * @class MonitoringImpl
   * @brief MonitoringServant試験用インプリメントクラス
   * @else
   * @class MonitoringImpl
   * @brief Monitoring implementation class for LightweightRTObjecServant' unittest.
   * @endif
   */
   int MonitoringImpl::count = 0;

    MonitoringImpl::MonitoringImpl()
    {
      sprintf(m_name, "%s", id());
      ++count;
      m_logger = new Logger();
    } 
    MonitoringImpl::MonitoringImpl(Logger& aLogger)
    {
      sprintf(m_name, "%s", id());
      ++count;
      m_logger = &aLogger;
    } 

    MonitoringImpl::~MonitoringImpl()
    {
    }








}; // namespace Local 
}; // namespace SDOPackage 
