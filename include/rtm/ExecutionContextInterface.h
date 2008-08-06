// -*- C++ -*-
/*!
 * @file  ExecutionContextInterface.h
 * @brief ExecutionContextInterface interface class
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

#ifndef ExecutionContextInterface_h
#define ExecutionContextInterface_h

#include <rtm/RTCInterface.h>


namespace RTC
{
  namespace Interface
  {
    enum LifeCycleState
      {
	CREATED_STATE,
	INACTIVE_STATE,
	ACTIVE_STATE,
	ERROR_STATE
      };
    
    enum ExecutionKind
      {
	PERIODIC,
	EVENT_DRIVEN,
	OTHER
      };

    class LightweightRTObjectInterface;
    class RTObjectInterface;
    typedef std::vector<RTObjectInterface*> RTCList;
        
    struct ExecutionContextProfile
    {
      ExecutionKind kind;
      double rate;
      RTObjectInterface* owner;
      RTCList participants;
      NVList properties;
    };
   
    /*!
     * @if jp
     * @class ExecutionContextInterface
     * @brief ExecutionContextInterface епеще╣
     * @else
     * @class ExecutionContextInterface
     * @brief ExecutionContextInterface class
     * @endif
     */
    class ExecutionContextInterface
    {
    public:
      virtual ~ExecutionContextInterface() {};

      virtual bool is_running() const = 0;

      virtual ReturnCode_t start() = 0;

      virtual ReturnCode_t stop() = 0;

      virtual double get_rate() const = 0;

      virtual ReturnCode_t set_rate(double rate) = 0;

      virtual ReturnCode_t
      add_component(LightweightRTObjectInterface& comp) = 0;

      virtual ReturnCode_t
      remove_component(LightweightRTObjectInterface& comp) = 0;

      virtual ReturnCode_t
      activate_component(LightweightRTObjectInterface& comp) = 0;

      virtual ReturnCode_t
      deactivate_component(LightweightRTObjectInterface& comp) = 0;

      virtual ReturnCode_t
      reset_component(LightweightRTObjectInterface& comp) = 0;

      virtual LifeCycleState
      get_component_state(LightweightRTObjectInterface& comp) = 0;

      virtual ExecutionKind
      get_kind() const = 0;

      virtual const ExecutionContextProfile&
      get_profile() const = 0;
    };
  };   // namespace Interface
};     // namespace RTC
#endif // ExecutionContextInterface_h

