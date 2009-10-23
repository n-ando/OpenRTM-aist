// -*- C++ -*-
/*!
 * @file OutPortPullConnector.h
 * @brief OutPortPull type connector class
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

#ifndef RTC_OUTPORTPULLCONNECTOR_H
#define RTC_OUTPORTPULLCONNECTOR_H

#include <rtm/OutPortConnector.h>

namespace RTC
{
  class OutPortProvider;

  class OutPortPullConnector
    : public OutPortConnector
  {
  public:
    DATAPORTSTATUS_ENUM

    /*!
     * @if jp
     * @brief コンストラクタ
     *
     * OutPortPullConnector は OutPortProvider の所有権を持つ。
     * したがって、OutPortPullConnector 削除時には、OutPortProvider も同時に
     * 解体・削除される。
     *
     * @param profile pointer to a ConnectorProfile
     * @param provider pointer to an OutPortProvider
     * @param buffer pointer to a buffer
     *
     * @elsek
     * @brief Constructor
     *
     * OutPortPullConnector assume ownership of InPortConsumer.
     * Therefore, OutPortProvider will be deleted when OutPortPushConnector
     * is destructed.
     *
     * @param profile pointer to a ConnectorProfile
     * @param provider pointer to an OutPortProvider
     * @param buffer pointer to a buffer
     *
     * @endif
     */
    OutPortPullConnector(ConnectorInfo info,
                         OutPortProvider* provider,
                         CdrBufferBase* buffer = 0);

    /*!
     * @if jp
     * @brief デストラクタ
     *
     * disconnect() が呼ばれ、provider, buffer が解体・削除される。
     *
     * @else
     *
     * @brief Destructor
     *
     * This operation calls disconnect(), which destructs and deletes
     * the consumer, the publisher and the buffer.
     *
     * @endif
     */
    virtual ~OutPortPullConnector();

    /*!
     * @if jp
     * @brief データの書き込み
     *
     * Publisherに対してデータを書き込み、これにより対応するInPortへ
     * データが転送される。
     *
     * @else
     *
     * @brief Writing data
     *
     * This operation writes data into publisher and then the data
     * will be transferred to correspondent InPort.
     *
     * @endif
     */
    virtual ReturnCode write(const cdrMemoryStream& data);

    /*!
     * @if jp
     * @brief 接続解除
     *
     * consumer, publisher, buffer が解体・削除される。
     *
     * @else
     *
     * @brief disconnect
     *
     * This operation destruct and delete the consumer, the publisher
     * and the buffer.
     *
     * @endif
     */
    virtual ReturnCode disconnect();

    /*!
     * @if jp
     * @brief Buffer を取得する
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
     * @brief アクティブ化
     *
     * このコネクタをアクティブ化する
     *
     * @else
     *
     * @brief Connector activation
     *
     * This operation activates this connector
     *
     * @endif
     */
    virtual void activate(){}; // do nothing

    /*!
     * @if jp
     * @brief 非アクティブ化
     *
     * このコネクタを非アクティブ化する
     *
     * @else
     *
     * @brief Connector deactivation
     *
     * This operation deactivates this connector
     *
     * @endif
     */
    virtual void deactivate(){}; // do nothing
  protected:

    /*!
     * @if jp
     * @brief OutPortProvider へのポインタ
     * @else
     * @brief the pointer to the OutPortProvider
     * @endif
     */
    OutPortProvider* m_provider;

    /*!
     * @if jp
     * @brief Buffer へのポインタ
     * @else
     * @brief the pointer to the buffer
     * @endif
     */
    CdrBufferBase* m_buffer;
  };
}; // namespace RTC

#endif  // RTC_PULL_CONNECTOR_H
