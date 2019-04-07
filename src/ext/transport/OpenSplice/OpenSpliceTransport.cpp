// -*- C++ -*-
/*!
 * @file  OpenSpliceOutPort.cpp
 * @brief OpenSpliceOutPort class
 * @date  $Date: 2019-01-31 03:08:03 $
 * @author Nobuhiko Miyamoto <n-miyamoto@aist.go.jp>
 *
 * Copyright (C) 2019
 *     Nobuhiko Miyamoto
 *     Robot Innovation Research Center,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *
 *     All rights reserved.
 *
 *
 */


#include "OpenSpliceTransport.h"
#include "OpenSpliceOutPort.h"
#include "OpenSpliceInPort.h"
#include "OpenSpliceMessageInfo.h"


extern "C"
{
  /*!
   * @if jp
   * @brief モジュール初期化関数
   * @else
   * @brief Module initialization
   * @endif
   */
  void OpenSpliceTransportInit(RTC::Manager* /*manager*/)
  {
    OpenSpliceInPortInit();
    OpenSpliceOutPortInit();
    
    OpenSpliceMessageInfoInit();
    
  }
  
};


