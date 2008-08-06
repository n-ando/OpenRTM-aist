// -*- C++ -*-
/*!
 * @file  ComponentActionInterface.h
 * @brief ComponentActionInterface interface class
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

#ifndef ComponentActionInterface_h
#define ComponentActionInterface_h

#include <rtm/RTCInterface.h>

namespace RTC
{
  namespace Interface
  {
    /*!
     * @if jp
     * @class ComponentActionInterface
     * @brief ComponentActionInterface インターフェースクラス
     * @else
     * @class ComponentActionInterface
     * @brief ComponentActionInterface interface class
     * @endif
     */
    class ComponentActionInterface
    {
    public:
      virtual ~ComponentActionInterface() {};
      
      virtual ReturnCode_t on_initialize() = 0;
      
      virtual ReturnCode_t on_finalize() = 0;
      
      virtual ReturnCode_t on_startup(ExecutionContextHandle_t ec_handle) = 0;
      virtual ReturnCode_t on_shutdown(ExecutionContextHandle_t ec_handle) = 0;
      virtual ReturnCode_t on_activated(ExecutionContextHandle_t ec_handle) = 0;
      virtual ReturnCode_t on_deactivated(ExecutionContextHandle_t ec_handle) = 0;
      virtual ReturnCode_t on_aborting(ExecutionContextHandle_t ec_handle) = 0;
      virtual ReturnCode_t on_error(ExecutionContextHandle_t ec_handle) = 0;
      virtual ReturnCode_t on_reset(ExecutionContextHandle_t ec_handle) = 0;
     };
  };   // namespace Interface
};     // namespace RTC
#endif // ComponentActionInterface_h

