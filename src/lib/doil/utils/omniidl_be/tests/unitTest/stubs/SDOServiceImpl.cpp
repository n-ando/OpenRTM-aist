// -*- C++ -*-
/*!
 * @file SDOServiceImpl.h
 * @brief SDOServiceImpl C++ implementation sample for doil
 * @date $Date$
 * @author 
 *
 * $Id$
 */


#include <stdio.h>
#include <SDOServiceImpl.h>
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
   * @class SDOServiceImpl
   * @brief SDOServiceServant試験用インプリメントクラス
   * @else
   * @class SDOServiceImpl
   * @brief SDOService implementation class for LightweightRTObjecServant' unittest.
   * @endif
   */
   int SDOServiceImpl::count = 0;

    SDOServiceImpl::SDOServiceImpl()
    {
      ++count;
      m_logger = new Logger();
    } 
    SDOServiceImpl::SDOServiceImpl(Logger& aLogger)
    {
      ++count;
      m_logger = &aLogger;
    } 

    SDOServiceImpl::~SDOServiceImpl()
    {
    }








}; // namespace Local 
}; // namespace SDOPackage 
