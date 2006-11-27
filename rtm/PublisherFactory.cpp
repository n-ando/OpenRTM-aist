// -*- C++ -*-
/*!
 * @file  PublisherFactory.cpp
 * @brief PublisherFactory class
 * @date  $Date: 2006-11-27 09:44:44 $
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
 * $Id: PublisherFactory.cpp,v 1.1 2006-11-27 09:44:44 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 */

#include <rtm/PublisherFactory.h>
#include <rtm/PublisherNew.h>
#include <rtm/PublisherPeriodic.h>
#include <rtm/PublisherFlush.h>
#include <rtm/Properties.h>
#include <rtm/InPortConsumer.h>

namespace RTC
{
  /*!
   * @if jp
   * @brief Publisher§Œ¿∏¿Æ
   * @else
   * @brief Create Publisher
   * @endif
   */
  PublisherBase* PublisherFactory::create(const char* name,
					  InPortConsumer& consumer,
					  const Properties& property)
  {
    if (std::string(name) == "New")
      {
	return new PublisherNew(consumer, property);
      }
    else if (std::string(name) == "Periodic")
      {
	return new PublisherPeriodic(consumer, property);
      }
    else if (std::string(name) == "Flush")
      {
	return new PublisherFlush(consumer, property);
      }
    return NULL;
  }
}; // namespace RTC
