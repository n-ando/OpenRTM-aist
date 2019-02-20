// -*- C++ -*-
/*!
 * @file  FastRTPSTransport.h
 * @brief FastRTPSTransport class
 * @date  $Date: 2019-02-04 03:08:03 $
 * @author Nobuhiko Miyamoto <n-miyamoto@aist.go.jp>
 *
 * Copyright (C) 2018
 *     Nobuhiko Miyamoto
 *     Robot Innovation Research Center,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *
 *     All rights reserved.
 *
 *
 */

#ifndef RTC_FASTRTPSTRANSPORT_H
#define RTC_FASTRTPSTRANSPORT_H



#include "FastRTPSOutPort.h"
#include "FastRTPSInPort.h"



extern "C"
{
  /*!
   * @if jp
   * @brief モジュール初期化関数
   *
   * FastRTPSOutPort、FastRTPSInPort のファクトリを登録する初期化関数。
   *
   * @else
   * @brief Module initialization
   *
   * 
   *
   * @endif
   */
  DLL_EXPORT void FastRTPSTransportInit(RTC::Manager* manager);
};

#endif // RTC_FASTRTPSTRANSPORT_H

