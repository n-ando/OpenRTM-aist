// -*- C++ -*-
/*!
 * @file  RTCInterface.h
 * @brief RTC Interfaces
 * @date  $Date$
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2008
 *     Noriaki Ando
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id$
 *
 */

#ifndef RTCInterface_h
#define RTCInterface_h

#include <vector>
#include <utility>

namespace RTC
{
  /*!
   * @if jp
   * @namespace RTC::Interface
   *
   * @brief RTC ローカルインターフェース
   *
   * RTC ローカルインターフェース定義
   *
   * @else
   *
   * @namespace RTC::Interface
   *
   * @brief RTC Local Interface
   *
   * RTC Local Interface Definition
   *
   * @endif
   */
  namespace Interface
  {
    enum ReturnCode_t
      {
	RTC_OK,
	RTC_ERROR,
	BAD_PARAMETER,
	UNSUPPORTED,
	OUT_OF_RESOURCES,
	PRECONDITION_NOT_MET
      };
    
#define EXECUTION_HANDLE_TYPE_NATIVE long
    
    typedef EXECUTION_HANDLE_TYPE_NATIVE ExecutionContextHandle_t;
    typedef EXECUTION_HANDLE_TYPE_NATIVE ECHandle_t;
    typedef char * UniqueIdentifier;
    
    typedef std::vector<std::pair<std::string, std::string> > NVList;
    
    class ExecutionContextInterface;
    typedef std::vector<ExecutionContextInterface*> ExecutionContextList;
    
    struct LightweightRTObjectInterface;
  };   // namespace Interface
};     // namespace RTC
#endif // RTCInterface_h

