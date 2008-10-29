// -*- C++ -*-
/*!
 * @file  FsmServiceInterface.h
 * @brief FsmServiceInterface class
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

#ifndef FsmServiceInterface_h
#define FsmServiceInterface_h

#include <rtm/RTCInterface.h>

namespace RTC
{
  namespace Interface
  {
    
    class FsmParticipantActionInterface;
    
    struct FsmBehaviorProfile
    {
      FsmParticipantActionInterface* comp;
      UniqueIdentifier id;
    };
    
    typedef std::vector<FsmBehaviorProfile*> FsmBehaviorProfileList;
    
    struct FsmProfile
    {
      FsmBehaviorProfileList behavior_profiles;
    };
    
    /*!
     * @if jp
     * @class FsmServiceInterface
     * @brief FsmServiceInterface епеще╣
     * @else
     * @class FsmServiceInterface
     * @brief FsmServiceInterface class
     * @endif
     */
    class FsmServiceInterface
    {
    public:
      virtual ~FsmServiceInterface() {};
      virtual const FsmProfile& get_fsm_profile() = 0;
      virtual ReturnCode_t set_fsm_profile(const FsmProfile& fsm_profile) = 0;
    };
  };   // namespace Interface
};     // namespace RTC
#endif // FsmServiceInterface_h

