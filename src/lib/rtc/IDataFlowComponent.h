// -*- C++ -*-
/*!
 * @file  DataFlowComponentInterface.h
 * @brief DataFlowComponentInterface interface class
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

#ifndef DataFlowComponentInterface_h
#define DataFlowComponentInterface_h

#include <rtm/RTCInterface.h>
#include <rtm/RTObjectInterface.h>
#include <rtm/DataFlowComponentActionInterface.h> 

namespace RTC
{
  namespace Interface
  {
    /*!
     * @if jp
     * @class DataFlowComponentInterface
     * @brief DataFlowComponentInterface インターフェースクラス
     * @else
     * @class DataFlowComponentInterface
     * @brief DataFlowComponentInterface class
     * @endif
     */
    class DataFlowComponentInterface
      : public virtual RTObjectInterface,
        public virtual DataFlowComponentActionInterface
    {
    public:
      virtual ~DataFlowComponentInterface() {};
    };
  };   // namespace Interface
};     // namespace RTC
#endif // DataFlowComponentInterface_h

