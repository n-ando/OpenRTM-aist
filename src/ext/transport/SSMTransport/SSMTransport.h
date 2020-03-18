// -*- C++ -*-
/*!
 * @file  SSMTransport.h
 * @brief SSMTransport class
 * @date  $Date: 2020-03-11 03:08:03 $
 * @author Nobuhiko Miyamoto <n-miyamoto@aist.go.jp>
 *
 * Copyright (C) 2020
 *     Nobuhiko Miyamoto
 *     Robot Innovation Research Center,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *
 *     All rights reserved.
 *
 *
 */

#ifndef RTC_SSMTRANSPORT_H
#define RTC_SSMTRANSPORT_H



#include <rtm/Manager.h>


namespace SSMRTM
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
   * SSMOutPort、SSMInPort のファクトリを登録する初期化関数。
   *
   * @else
   * @brief Module initialization
   *
   * 
   *
   * @endif
   */
  DLL_EXPORT void SSMTransportInit(RTC::Manager* manager);
}

#endif // RTC_SSMTRANSPORT_H

