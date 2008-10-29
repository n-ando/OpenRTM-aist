// -*- C++ -*-
/*!
 * @file  ModeInterface.h
 * @brief ModeInterface interface class
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

#ifndef ModeInterface_h
#define ModeInterface_h

#include <rtm/RTCInterface.h>

namespace RTC
{
  namespace Interface
  {
    /*!
     * @if jp
     * @class ModeInterface
     * @brief ModeInterface епеще╣
     * @else
     * @class ModeInterface
     * @brief ModeInterface class
     * @endif
     */
    class ModeInterface
    {
    public:
      virtual ~ModeInterface() {};
    };
  };   // namespace Interface
};     // namespace RTC
#endif // ModeInterface_h

