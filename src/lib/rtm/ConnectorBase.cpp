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
  ConnectorInfo::ConnectorInfo(const char* name_, const char* id_,
                coil::vstring ports_, const coil::Properties& properties_)
    : name(name_), id(id_)
    , ports(std::move(ports_)), properties(properties_)
  {
  }
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
  ConnectorInfo::ConnectorInfo(const ConnectorInfo&) = default;

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
  ConnectorInfo::~ConnectorInfo() = default;
} //namespace RTC

