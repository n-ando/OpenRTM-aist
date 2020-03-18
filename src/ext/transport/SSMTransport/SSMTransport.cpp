// -*- C++ -*-
/*!
 * @file  SSMOutPort.cpp
 * @brief SSMOutPort class
 * @date  $Date: 2020-03-10 03:08:03 $
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


#include <ssm.h>
#include "SSMTransport.h"
#include "SSMOutPort.h"
#include "SSMInPort.h"

namespace SSMRTM
{

  ManagerActionListener::ManagerActionListener()
  {

  }
  ManagerActionListener::~ManagerActionListener()
  {

  }
  void ManagerActionListener::preShutdown()
  {

  }
  void ManagerActionListener::postShutdown()
  {
    endSSM();
  }
  void ManagerActionListener::postReinit()
  {

  }

  void ManagerActionListener::preReinit()
  {

  }

}




extern "C"
{
  /*!
   * @if jp
   * @brief モジュール初期化関数
   * @else
   * @brief Module initialization
   * @endif
   */
  void SSMTransportInit(RTC::Manager* manager)
  {
    if(!initSSM())
    {
      return;
    }

    {
      RTC::OutPortConsumerFactory& factory(RTC::OutPortConsumerFactory::instance());
      factory.addFactory("ssm",
                        ::coil::Creator< ::RTC::OutPortConsumer,
                                          ::RTC::SSMInPort>,
                        ::coil::Destructor< ::RTC::OutPortConsumer,
                                            ::RTC::SSMInPort>);
    }

    {
      RTC::InPortConsumerFactory& factory(RTC::InPortConsumerFactory::instance());
      factory.addFactory("ssm",
                        ::coil::Creator< ::RTC::InPortConsumer,
                                          ::RTC::SSMOutPort>,
                        ::coil::Destructor< ::RTC::InPortConsumer,
                                            ::RTC::SSMOutPort>);
    }



    SSMRTM::ManagerActionListener *listener = new SSMRTM::ManagerActionListener();
    manager->addManagerActionListener(listener);
    
  }
  
}


