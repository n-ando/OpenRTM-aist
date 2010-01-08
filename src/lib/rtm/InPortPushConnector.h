// -*- C++ -*-
/*!
 * @file InPortPushConnector.h
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

#ifndef RTC_INPORTPUSHCONNECTOR_H
#define RTC_INPORTPUSHCONNECTOR_H

#include <rtm/InPortConnector.h>
#include <rtm/InPortConsumer.h>
#include <rtm/PublisherBase.h>

namespace RTC
{
  class InPortProvider;

  class InPortPushConnector
    : public InPortConnector
  {
  public:
    DATAPORTSTATUS_ENUM

    /*!
     * @if jp
     * @brief コンストラクタ
     *
     * InPortPushConnector は InPortConsumer の所有権を持つ。
     * したがって、InPortPushConnector 削除時には、InPortConsumerも同時に
     * 解体・削除される。
     *
     * @param info ConnectorInfo
     * @param consumer InPortConsumer
     *
     * @else
     * @brief Constructor
     *
     * InPortPushConnector assume ownership of InPortConsumer.
     * Therefore, InPortConsumer will be deleted when InPortPushConnector
     * is destructed.
     *
     * @param info ConnectorInfo
     * @param consumer InPortConsumer
     *
     * @endif
     */
    InPortPushConnector(ConnectorInfo info,
                        InPortProvider* provider,
                        ConnectorListeners& listeners,
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
    virtual ~InPortPushConnector();

    /*!
     * @if jp
     * @brief データの読み出し
     *
     * バッファからデータを読み出す
     *
     * @else
     *
     * @brief Reading data
     *
     * Read data from the buffer.
     *
     * @endif
     */
    virtual ReturnCode read(cdrMemoryStream& data);

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

    virtual void activate(){}; // do nothing
    virtual void deactivate(){}; // do nothing
  protected:
    /*!
     * @if jp
     * @brief Bufferの生成
     * @else
     * @brief create buffer
     * @endif
     */
    virtual CdrBufferBase* createBuffer(ConnectorInfo& info);

    /*!
     * @if jp
     * @brief 接続確立時にコールバックを呼ぶ
     * @else
     * @brief Invoke callback when connection is established
     * @endif
     */
    void onConnect();

    /*!
     * @if jp
     * @brief 接続切断時にコールバックを呼ぶ
     * @else
     * @brief Invoke callback when connection is destroied
     * @endif
     */
    void onDisconnect();

  private:
    /*!
     * @if jp
     * @brief InPortConsumer へのポインタ
     * @else
     * @brief the pointer to the InPortConsumer
     * @endif
     */
    InPortProvider* m_provider;

    /*!
     * @if jp
     * @brief ConnectorListenrs への参照
     * @else
     * @brief A reference to a ConnectorListener
     * @endif
     */
    ConnectorListeners& m_listeners;

    bool m_deleteBuffer;
  };
}; // namespace RTC

#endif  // RTC_PUSH_CONNECTOR_H
