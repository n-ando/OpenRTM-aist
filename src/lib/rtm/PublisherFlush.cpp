// -*- C++ -*-
/*!
 * @file  PublisherFlush.cpp
 * @brief PublisherFlush class
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

#include <coil/Properties.h>
#include <rtm/PublisherFlush.h>
#include <rtm/InPortConsumer.h>

#ifdef WIN32
#pragma warning( pop )
#endif // WIN32

namespace RTC
{
  /*!
   * @if jp
   * @brief コンストラクタ
   * @else
   * @brief Constructor
   * @endif
   */
  PublisherFlush::PublisherFlush(InPortConsumer* consumer,
				 const coil::Properties& property)
    : m_consumer(consumer)
  {
  }

  /*!
   * @if jp
   * @brief デストラクタ
   * @else
   * @brief Destructor
   * @endif
   */
  PublisherFlush::~PublisherFlush()
  {
    delete m_consumer;
  }
  
  /*!
   * @if jp
   * @brief Observer関数
   * @else
   * @brief Observer function
   * @endif
   */
  void PublisherFlush::update()
  {
    m_consumer->push();
    return;
  }
}; // namespace RTC
