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

#ifndef RTC_CONNECTORBASE_H
#define RTC_CONNECTORBASE_H

#include <coil/stringutil.h>
#include <coil/Properties.h>

#include <rtm/RTC.h>
#include <rtm/CdrBufferBase.h>
#include <rtm/DataPortStatus.h>
#include <rtm/SystemLogger.h>

namespace RTC
{
  /*!
   * @if jp
   * @class ConnectorInfo クラス
   * @brief ConnectorInfo クラス
   *
   * @class ConnectorInfo class
   * @brief ConnectorInfo class
   *
   * @endif
   */
  class ConnectorInfo
  {
  public:
    ConnectorInfo(const char* name_, const char* id_,
                  coil::vstring ports_, coil::Properties properties_)
      : name(name_), id(id_)
      , ports(ports_), properties(properties_)
    {
    }
    ConnectorInfo()
    {
    }
    std::string name;
    std::string id;
    coil::vstring ports;
    coil::Properties properties;
  };

  typedef std::vector<ConnectorInfo> ConnectorInfoList;

  class ConnectorBase;
  typedef std::vector<ConnectorBase*> ConnectorList;
  

  /*!
   * @if jp
   * @class ConnectorBase
   * @brief Connector 基底クラス
   *
   * InPort/OutPort, Push/Pull 各種 Connector を派生させるための
   * 基底クラス。
   *
   * @since 1.0.0
   *
   * @else
   * @class ConnectorBase
   * @brief Connector Base class
   *
   * The base class to derive subclasses for InPort/OutPort,
   * Push/Pull Connectors
   *
   * @since 1.0.0
   *
   * @endif
   */
  class ConnectorBase
    : public DataPortStatus
  {
  public:
    DATAPORTSTATUS_ENUM

    /*!
     * @if jp
     * @class Profile
     * @brief Connector profile ローカル構造体
     *
     * ConnectorBase およびその派生クラスで扱う ConnectorProfile 構造体。
     *
     * @since 1.0.0
     *
     * @else
     * @class Profile
     * @brief local representation of Connector profile
     *
     * ConnectorProfile struct for ConnectorBase and its subclasses.
     *
     * @since 1.0.0
     *
     * @endif
     */



    /*!
     * @if jp
     * @brief デストラクタ
     * @else
     * @brief Destructor
     * @endif
     */
    virtual ~ConnectorBase(){};

   /*!
     * @if jp
     * @brief Profile 取得
     *
     * Connector Profile を取得する
     *
     * @else
     * @brief Getting Profile
     *
     * This operation returns Connector Profile
     *
     * @endif
     */
    virtual const ConnectorInfo& profile() = 0;

    /*!
     * @if jp
     * @brief Connector ID 取得
     *
     * Connector ID を取得する
     *
     * @else
     * @brief Getting Connector ID
     *
     * This operation returns Connector ID
     *
     * @endif
     */
    virtual const char* id() = 0;

    /*!
     * @if jp
     * @brief Connector 名取得
     *
     * Connector 名を取得する
     *
     * @else
     * @brief Getting Connector name
     *
     * This operation returns Connector name
     *
     * @endif
     */
    virtual const char* name() = 0;

    /*!
     * @if jp
     * @brief 接続解除関数
     *
     * Connector が保持している接続を解除する
     *
     * @else
     * @brief Disconnect connection
     *
     * This operation disconnect this connection
     *
     * @endif
     */
    virtual ReturnCode disconnect() = 0;

    /*!
     * @if jp
     * @brief Buffer を所得する
     *
     * Connector が保持している Buffer を返す
     *
     * @else
     * @brief Getting Buffer
     *
     * This operation returns this connector's buffer
     *
     * @endif
     */
    virtual CdrBufferBase* getBuffer() = 0;

    virtual void activate() = 0;
    virtual void deactivate() = 0;

  private:
    // non-copyable class
    //    ConnectorBase(const ConnectorBase& x);
    //    ConnectorBase& operator=(const ConnectorBase& x);
  };
}; // namespace RTC

#endif // RTC_CONNECTORBASE_H
