// -*- C++ -*-
/*!
 * @file  PublisherFactory.cpp
 * @brief PublisherFactory class
 * @date  $Date: 2007-01-06 18:00:25 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006
 *     Noriaki Ando
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: PublisherFactory.cpp,v 1.2 2007-01-06 18:00:25 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.1  2006/11/27 09:44:44  n-ando
 * The first commitment.
 *
 */

#include <rtm/PublisherFactory.h>
#include <rtm/PublisherNew.h>
#include <rtm/PublisherPeriodic.h>
#include <rtm/PublisherFlush.h>
#include <rtm/Properties.h>
#include <rtm/NVUtil.h>
#include <rtm/InPortConsumer.h>
#include <iostream>
#include <string>

namespace RTC
{
  /*!
   * @if jp
   * @brief Publisherを生成する。
   * @else
   * @brief Create Publisher
   * @endif
   */
  PublisherBase* PublisherFactory::create(InPortConsumer* consumer,
					  Properties& property)
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
}; // namespace RTC
