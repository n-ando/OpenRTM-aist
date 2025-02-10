// -*- C++ -*-
/*!
 * @file  ROSTransport.h
 * @brief ROSTransport class
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

#ifndef RTC_ROSTRANSPORT_H
#define RTC_ROSTRANSPORT_H


#include <rtm/Manager.h>

namespace ROSRTM
{
  class ManagerActionListener : public RTM::ManagerActionListener
  {
  public:
      ManagerActionListener();
      ~ManagerActionListener() override;
      void preShutdown() override;
      void postShutdown() override;
      void postReinit() override;
      void preReinit() override;
  };
}

extern "C"
{
  /*!
   * @if jp
   * @brief モジュール初期化関数
   *
   * ROSOutPort、ROSInPort のファクトリを登録する初期化関数。
   *
   * @else
   * @brief Module initialization
   *
   * 
   *
   * @endif
   */
  DLL_EXPORT void ROSTransportInit(RTC::Manager* manager);
}

#endif // RTC_ROSTRANSPORT_H

