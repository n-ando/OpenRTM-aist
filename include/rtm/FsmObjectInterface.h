// -*- C++ -*-
/*!
 * @file  FsmObjectInterface.h
 * @brief FsmObjectInterface interface class
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

#ifndef FsmObjectInterface_h
#define FsmObjectInterface_h

#include <rtm/RTCInterface.h>

namespace RTC
{
  namespace Interface
  {
    /*!
     * @if jp
     * @class FsmObjectInterface
     * @brief FsmObjectInterface インターフェースクラス
     * @else
     * @class FsmObjectInterface
     * @brief FsmObjectInterface interface class
     * @endif
     */
    class FsmObjectInterface
    {
    public:
      virtual ~FsmObjectInterface() {};
      virtual ReturnCode_t
      send_stimulus(const char* message,
		    ExecutionContextHandle_t exec_context) = 0;
    };
  };   // namespace Interface 
};     // namespace RTC
#endif // FsmObjectInterface_h
  
  
