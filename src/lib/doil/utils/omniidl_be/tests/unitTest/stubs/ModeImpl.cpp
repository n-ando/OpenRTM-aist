// -*- C++ -*-
/*!
 * @file ModeImpl.h
 * @brief ModeImpl C++ implementation sample for doil
 * @date $Date$
 * @author 
 *
 * $Id$
 */


#include <stdio.h>
#include <ModeImpl.h>
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
   * @class ModeImpl
   * @brief ModeServant試験用インプリメントクラス
   * @else
   * @class ModeImpl
   * @brief Mode implementation class for ModeServant' unittest.
   * @endif
   */
   int ModeImpl::count = 0;

    ModeImpl::ModeImpl()
    {
      ++count;
      m_logger = new Logger();
    } 
    ModeImpl::ModeImpl(Logger& aLogger)
    {
      ++count;
      m_logger = &aLogger;
    } 

    ModeImpl::~ModeImpl()
    {
    }







}; // namespace Local 
}; // namespace SDOPackage 
