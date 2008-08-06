// -*- C++ -*-
/*!
 * @file  LightweightRTObjectInterface.h
 * @brief LightweightRTObjectInterface interface class
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

#ifndef LightweightRTObjectInterface_h
#define LightweightRTObjectInterface_h

#include <rtm/RTCInterface.h>
#include <rtm/ComponentActionInterface.h>

namespace RTC
{
  namespace Interface
  {
    /*!
     * @if jp
     * @class LightweightRTObjectInterface
     * @brief LightweightRTObjectInterface インターフェースクラス
     * @else
     * @class LightweightRTObjectInterface
     * @brief LightweightRTObjectInterface interface class
     * @endif
     */
    class LightweightRTObjectInterface
      : public virtual ComponentActionInterface
    {
    public:
      virtual ~LightweightRTObjectInterface() {};
      virtual bool is_alive(const ExecutionContextInterface& ec) const = 0;
      virtual ReturnCode_t initialize() = 0;
      virtual ReturnCode_t finalize() = 0;
      virtual ReturnCode_t exit() = 0;

      virtual ExecutionContextHandle_t
      attach_context(const ExecutionContextInterface& ec) = 0;
      virtual ReturnCode_t detach_context(ExecutionContextHandle_t ec_handle) = 0;
      virtual ExecutionContextInterface&
      get_context(ExecutionContextHandle_t ec_handle) = 0;
      virtual ExecutionContextList& get_owned_contexts() = 0;
      virtual ExecutionContextList& get_participating_contexts() = 0;
    };
  };   // namespace Interface
};     // namespace RTC
#endif // LightweightRTObjectInterface_h
