// -*- C++ -*-
/*!
 * @file  PublisherFactory.cpp
 * @brief PublisherFactory class
 * @date  $Date: 2007-12-31 03:08:06 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006-2008
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

#ifdef WIN32
#pragma warning( push )
#pragma warning( disable : 4267 )
#pragma warning( disable : 4290 )
#pragma warning( disable : 4311 )
#pragma warning( disable : 4312 )
#endif // WIN32

#include <rtm/PublisherFactory.h>
#include <rtm/PublisherNew.h>
#include <rtm/PublisherPeriodic.h>
#include <rtm/PublisherFlush.h>
#include <coil/Properties.h>
#include <rtm/NVUtil.h>
#include <rtm/InPortConsumer.h>
#include <iostream>
#include <string>


#ifdef WIN32
#pragma warning( pop )
#endif // WIN32

namespace RTC
{
  /*!
   * @if jp
   * @brief Publisher¤ÎÀ¸À®
   * @else
   * @brief Create the Publishers
   * @endif
   */
  PublisherBase* PublisherFactory::create(InPortConsumer* consumer,
					  coil::Properties& property)
  {
    std::string pub_type;
    pub_type = property.getProperty("dataport.subscription_type", "New");
    
    if (pub_type == "New")
      {
	return new PublisherNew(consumer, property);
      }
    else if (pub_type == "Periodic")
      {
	return new PublisherPeriodic(consumer, property);
      }
    else if (pub_type == "Flush")
      {
	return new PublisherFlush(consumer, property);
      }
    return NULL;
  }
  
  /*!
   * @if jp
   * @brief Publisher¤ÎÇË´þ
   * @else
   * @brief Destroy the Publishers
   * @endif
   */
  void PublisherFactory::destroy(PublisherBase* publisher)
  {
    publisher->release();
    delete publisher;
  }
}; // namespace RTC
