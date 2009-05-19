/*! -*- C++ -*-
 *
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
    InPortPullConnector(Profile profile,
                        OutPortConsumer* consumer,
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

    virtual void activate(){}; // do nothing
    virtual void deactivate(){}; // do nothing
  protected:
    CdrBufferBase* createBuffer(Profile& profile);
    
  private:
    OutPortConsumer* m_consumer;
  };
}; // namespace RTC

#endif  // RTC_PULL_CONNECTOR_H
