// -*- C++ -*-
/*!
 * @file  MultiModeComponentActionInterface.h
 * @brief MultiModeComponentActionInterface class
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

#ifndef MultiModeComponentActionInterface_h
#define MultiModeComponentActionInterface_h

#include <rtm/RTCInterface.h>

namespace RTC
{
  namespace Interface
  {
    /*!
     * @if jp
     * @class MultiModeComponentActionInterface
     * @brief MultiModeComponentActionInterface クラス
     * @else
     * @class MultiModeComponentActionInterface
     * @brief MultiModeComponentActionInterface class
     * @endif
     */
    class MultiModeComponentActionInterface
    {
    public:
      /*!
       * @if jp
       * @brief デストラクタ
       * @else
       * @brief Destructor
       * @endif
       */
      virtual ~MultiModeComponentActionInterface() {};
      virtual ReturnCode_t on_mode_changed(ExecutionContextHandle_t ec_handle) = 0;
    };
  };   // namespace Interface
};     // namespace RTC
#endif // MultiModeComponentActionInterface_h

