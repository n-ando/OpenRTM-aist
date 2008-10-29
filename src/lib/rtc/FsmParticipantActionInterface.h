// -*- C++ -*-
/*!
 * @file  FsmParticipantActionInterface.h
 * @brief FsmParticipantActionInterface class
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

#ifndef FsmParticipantActionInterface_h
#define FsmParticipantActionInterface_h

#include <rtm/RTCInterface.h>

namespace RTC
{
  namespace Interface
  {
    /*!
     * @if jp
     * @class FsmParticipantActionInterface
     * @brief FsmParticipantActionInterface インターフェースクラス
     * @else
     * @class FsmParticipantActionInterface
     * @brief FsmParticipantActionInterface interface class
     * @endif
     */
    class FsmParticipantActionInterface
    {
    public:
      /*!
       * @if jp
       * @brief デストラクタ
       * @else
       * @brief Destructor
       * @endif
       */
      virtual ~FsmParticipantActionInterface() {};
    };
  };   // namespace Interface
};     // namespace RTC
#endif // FsmParticipantActionInterface_h

