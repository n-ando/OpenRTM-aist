// -*- C++ -*-
/*!
 * @file ConnectorBase.h
 * @brief Connector base class
 * @date $Date$
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2009
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

#include <rtm/ConnectorBase.h>

namespace RTC
{
  /*!
   * @if jp
   *
   * @brief コンストラクタ
   *
   * コンストラクタ
   *
   * @else
   *
   * @brief Constructor
   *
   * Constructor
   *
   * @endif
   */
  ConnectorInfo::ConnectorInfo(const ConnectorInfo& info)
  {
      name = info.name;
      id = info.id;
      ports = info.ports;
      properties = info.properties;


  }

  /*!
   * @if jp
   *
   * @brief デストラクタ
   *
   * デストラクタ
   *
   * @else
   *
   * @brief Destructor
   *
   * Destructor
   *
   * @endif
   */
  ConnectorInfo::~ConnectorInfo()
  {
  }
} //namespace RTC

