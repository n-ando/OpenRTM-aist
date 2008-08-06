// -*- C++ -*-
/*!
 * @file  DataFlowComponentActionInterface.h
 * @brief DataFlowComponentActionInterface interface class
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

#ifndef DataFlowComponentActionInterface_h
#define DataFlowComponentActionInterface_h

#include <rtm/RTCInterface.h>

namespace RTC
{
  namespace Interface
  {
    /*!
     * @if jp
     * @class DataFlowComponentActionInterface
     * @brief DataFlowComponentActionInterface インターフェースクラス
     * @else
     * @class DataFlowComponentActionInterface
     * @brief DataFlowComponentActionInterface class
     * @endif
     */
    class DataFlowComponentActionInterface
    {
    public:
      virtual ~DataFlowComponentActionInterface() {};
      virtual ReturnCode_t on_execute(ExecutionContextHandle_t ec_handle) = 0;
      virtual ReturnCode_t on_state_update(ExecutionContextHandle_t ec_handle) = 0;
      virtual ReturnCode_t on_rate_changed(ExecutionContextHandle_t ec_handle) = 0;
    };
  };   // namespace Interface
};     // namespace RTC
#endif // DataFlowComponentActionInterface_h

