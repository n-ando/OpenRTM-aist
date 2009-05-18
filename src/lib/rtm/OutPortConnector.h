/*! -*- C++ -*-
 *
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

#ifndef RTC_OUTPORTCONNECTOR_H
#define RTC_OUTPORTCONNECTOR_H

#include <rtm/SystemLogger.h>
#include <rtm/ConnectorBase.h>

namespace RTC
{
  /*!
   * @if jp
   * @class OutPortConnector
   * @brief OutPortConnector 基底クラス
   *
   * OutPort の Push/Pull 各種 Connector を派生させるための
   * 基底クラス。
   *
   * @since 1.0.0
   *
   * @else
   * @class OutPortConnector
   * @brief IｎPortConnector base class
   *
   * The base class to derive subclasses for OutPort's Push/Pull Connectors
   *
   * @since 1.0.0
   *
   * @endif
   */
  class OutPortConnector
    : public ConnectorBase
  {
  public:
    DATAPORTSTATUS_ENUM

    /*!
     * @if jp
     * @brief コンストラクタ
     * @else
     * @brief Constructor
     * @endif
     */
    OutPortConnector(ConnectorBase::Profile& profile,
                     CdrBufferBase* buffer);

    /*!
     * @if jp
     * @brief デストラクタ
     * @else
     * @brief Destructor
     * @endif
     */
    virtual ~OutPortConnector();
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
    const Profile& profile();

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
    const char* id();

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
    const char* name();

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
    virtual CdrBufferBase* getBuffer();

    /*!
     * @if jp
     * @brief write 関数
     *
     * OutPort からデータを Buffer へ write する関数
     *
     * @else
     * @brief Destructor
     *
     * The write function to write data from OutPort to Buffer
     *
     * @endif
     */
    virtual ReturnCode write(const cdrMemoryStream& data) = 0;

  protected:
    Logger rtclog;
    Profile m_profile;
    CdrBufferBase* m_buffer;
  };
}; // namespace RTC

#endif // RTC_CONNECTORBASE_H
