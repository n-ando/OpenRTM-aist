// -*- C++ -*-
/*!
 * @file  MultiModeObjectInterface.h
 * @brief MultiModeObjectInterface class
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

#ifndef MultiModeObjectInterface_h
#define MultiModeObjectInterface_h

#include <rtm/RTCInterface.h>
#include <rtm/ModeCapableInterface.h>
#include <rtm/MultModeComponentActionInterface.h>

namespace RTC
{
  namespace Interface
  {
    /*!
     * @if jp
     * @class MultiModeObjectInterface
     * @brief MultiModeObjectInterface クラス
     * @else
     * @class MultiModeObjectInterface
     * @brief MultiModeObjectInterface class
     * @endif
     */
    class MultiModeObjectInterface
      : public virtual RTObjectInterface,
        public virtual ModeCapableInterface,
        public virtual MultiModeComponentAction
    {
    public:
      /*!
       * @if jp
       * @brief デストラクタ
       * @else
       * @brief Destructor
       * @endif
       */
      virtual ~MultiModeObjectInterface() {};
      virtual ReturnCode_t on_mode_changed(ExecutionContextHandle_t ec_handle) = 0;
    };
  };   // namespace Interface
};     // namespace RTC
#endif // MultiModeObjectInterface_h

