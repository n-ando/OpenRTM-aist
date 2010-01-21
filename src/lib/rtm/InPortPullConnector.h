// -*- C++ -*-
/*!
 * @file InPortPullConnector.h
 * @brief InPortPull type connector class
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

#include <rtm/InPortConnector.h>
#include <rtm/InPortProvider.h>
#include <rtm/PublisherBase.h>
#include <rtm/DataPortStatus.h>

namespace RTC
{
  class OutPortConsumer;
  class ConnectorListeners;

  /*!
   * @if jp
   * @class InPortPullConnector
   * @brief InPortPullConnector 基底クラス
   *
   * InPort の Push 型データフローのための Connector
   *
   * @since 1.0.0
   *
   * @else
   * @class InPortPullConnector
   * @brief InPortPullConnector base class
   *
   * A connector class for pull type dataflow of InPort
   *
   * @since 1.0.0
   *
   * @endif
   */
  class InPortPullConnector
    : public InPortConnector
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
    InPortPullConnector(ConnectorInfo info,
                        OutPortConsumer* consumer,
                        ConnectorListeners& listeners,
                        CdrBufferBase* buffer = 0);

    /*!
     * @if jp
     * @brief デストラクタ
     * @else
     * @brief Destructor
     * @endif
     */
    virtual ~InPortPullConnector();

    /*!
     * @if jp
     * @brief read 関数
     *
     * Buffer からデータを InPort へ read する関数
     *
     * @else
     * @brief Destructor
     *
     * The read function to read data from buffer to InPort
     *
     * @endif
     */
    virtual ReturnCode read(cdrMemoryStream& data);

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
     * @brief Bufferの生成
     * @else
     * @brief create buffer
     * @endif
     */
    CdrBufferBase* createBuffer(ConnectorInfo& info);

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
     * @brief OutPortConsumer へのポインタ
     * @else
     * @brief the pointer to the OutPortConsumer
     * @endif
     */
    OutPortConsumer* m_consumer;
    
    /*!
     * @if jp
     * @brief ConnectorListenrs への参照
     * @else
     * @brief A reference to a ConnectorListener
     * @endif
     */
    ConnectorListeners& m_listeners;
  };
}; // namespace RTC

#endif  // RTC_PULL_CONNECTOR_H
