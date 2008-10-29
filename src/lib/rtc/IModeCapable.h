// -*- C++ -*-
/*!
 * @file  ModeCapableInterface.h
 * @brief ModeCapableInterface class
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

#ifndef ModeCapableInterface_h
#define ModeCapableInterface_h

#include <rtm/RTCInterface.h>

namespace RTC
{
  namespace Interface
  {
    class ModeInterface;
    class ExecutionContext;
    /*!
     * @if jp
     * @class ModeCapableInterface
     * @brief ModeCapableInterface епеще╣
     * @else
     * @class ModeCapableInterface
     * @brief ModeCapableInterface class
     * @endif
     */
    class ModeCapableInterface
    {
    public:
      virtual ~ModeCapableInterface();
      virtual ModeInterface&
      get_default_mode() = 0;
      virtual ModeInterface&
      get_current_mode() = 0;
      virtual ModeInterface&
      get_current_mode_in_context(const ExecutionContextInterface& ec) = 0;
      virtual ModeInterface&
      get_pending_mode() = 0;
      virtual ModeInterface&
      get_pending_mode_in_context(const ExecutionContextInterface& ec) = 0;
      virtual ReturnCode_t
      set_mode(ModeInterface& new_mode, bool immediate) = 0;
    };
  };     // namespace Interface
};     // namespace RTC
#endif // ModeCapableInterface_h

