// -*- C++ -*-
/*!
 * @file  FsmParticipantInterface.h
 * @brief FsmParticipantInterface interface class
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

#ifndef FsmParticipantInterface_h
#define FsmParticipantInterface_h

#include <rtm/RTObjectInterface.h>
#include <rtm/FsmParticipantActionInterface.h>

namespace RTC
{
  namespace Interface
  {
    /*!
     * @if jp
     * @class FsmParticipantInterface
     * @brief FsmParticipantInterface インターフェースクラス
     * @else
     * @class FsmParticipantInterface
     * @brief FsmParticipantInterface interface class
     * @endif
     */
    class FsmParticipantInterface
      : public virtual RTObjectInterface,
        public virtual FsmParticipantActionInterface
    {
  public:
      virtual ~FsmParticipantInterface() {};
    };
  };   // namesoace Interface
};     // namespace RTC
#endif // FsmParticipantInterface_h

