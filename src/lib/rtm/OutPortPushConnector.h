/*! -*- C++ -*-
 *
 * @file OutPortPushConnector.h
 * @brief Push type connector class
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

#ifndef RTC_OUTPORTPUSHCONNECTOR_H
#define RTC_OUTPORTPUSHCONNECTOR_H

#include <rtm/OutPortConnector.h>
#include <rtm/InPortConsumer.h>
#include <rtm/PublisherBase.h>

namespace RTC
{
  class OutPortPushConnector
    : public OutPortConnector
  {
  public:
    DATAPORTSTATUS_ENUM

    /*!
     * @if jp
     * @brief コンストラクタ
     *
     * OutPortPushConnector は InPortConsumer の所有権を持つ。
     * したがって、OutPortPushConnector 削除時には、InPortConsumerも同時に
     * 解体・削除される。
     *
     * @param profile ConnectorProfile
     * @param consumer InPortConsumer
     *
     * @elsek
     * @brief Constructor
     *
     * OutPortPushConnector assume ownership of InPortConsumer.
     * Therefore, InPortConsumer will be deleted when OutPortPushConnector
     * is destructed.
     *
     * @param profile ConnectorProfile
     * @param consumer InPortConsumer
     *
     * @endif
     */
    OutPortPushConnector(Profile profile,
                         InPortConsumer* consumer,
                         CdrBufferBase* buffer = 0);

    /*!
     * @if jp
     * @brief デストラクタ
     *
     * disconnect() が呼ばれ、consumer, publisher, buffer が解体・削除される。
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
    virtual ~OutPortPushConnector();

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
    virtual void activate();

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
    virtual void deactivate();
    
  protected:
    /*!
     * @if jp
     * @brief Publisherの生成
     * @else
     * @brief create publisher
     * @endif
     */
    virtual PublisherBase* createPublisher(Profile& profile);

    /*!
     * @if jp
     * @brief Bufferの生成
     * @else
     * @brief create buffer
     * @endif
     */
    virtual CdrBufferBase* createBuffer(Profile& profile);

  private:
    /*!
     * @if jp
     * @brief InPortConsumer へのポインタ
     * @else
     * @brief the pointer to the InPortConsumer
     * @endif
     */
    InPortConsumer* m_consumer;

    /*!
     * @if jp
     * @brief Publisher へのポインタ
     * @else
     * @brief the pointer to the publisher
     * @endif
     */
    PublisherBase* m_publisher;

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

#endif  // RTC_PUSH_CONNECTOR_H
