// -*- C++ -*-
/*!
 * @file  InPortConsumer.h
 * @brief InPortConsumer class
 * @date  $Date: 2007-12-31 03:08:03 $
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

#ifndef InPortConsumer_h
#define InPortConsumer_h

#include <rtm/NVUtil.h>
#include <rtm/CorbaConsumer.h>

namespace RTC
{
  /*!
   * @if jp
   *
   * @class InPortConsumer
   *
   * @brief InPortConsumer 抽象クラス
   *
   * 入力ポートコンシューマのための抽象インターフェースクラス
   * 各具象クラスは、以下の純粋仮想関数の実装を提供しなければならない。
   * - push(): データ送信
   * - clone(): ポートのコピー
   * - subscribeInterface(): データ送出通知への登録
   * - unsubscribeInterface(): データ送出通知の登録解除
   *
   * @since 0.4.0
   *
   * @else
   * @class InPortConsumer
   *
   * @brief InPortConsumer abstract class
   *
   * This is the abstract interface class for the input port Consumer.
   * Concrete classes must implement the following pure virtual functions.
   * - push(): Send data
   * - clone(): Copy ports
   * - subscribeInterface(): Subscribe the data send notification
   * - unsubscribeInterface(): Unsubscribe the data send notification
   *
   * @since 0.4.0
   *
   * @endif
   *
   */
  class InPortConsumer
  {
  public:
    /*!
     * @if jp
     * @brief コンストラクタ
     *
     * コンストラクタ
     *
     * @else
     * @brief Constructor
     *
     * Constructor
     *
     * @endif
     */
    //InPortConsumer();
    
    /*!
     * @if jp
     * @brief デストラクタ
     *
     * デストラクタ
     *
     * @else
     * @brief Destructor
     *
     * Destructor
     *
     * @endif
     */
    virtual ~InPortConsumer(){};
    
    /*!
     * @if jp
     * @brief 接続先へのデータ送信
     *
     * 接続先のポートへデータを送信するための純粋仮想関数。
     *
     * @else
     * @brief Send data to the destination port
     *
     * Pure virtual function to send data to the destination port.
     *
     * @endif
     */
    virtual void push() = 0;
    
    /*!
     * @if jp
     * @brief 当該ポートのコピー
     *
     * 当該ポートのコピーを生成するための純粋仮想関数。
     *
     * @return 複製された InPortConsumer オブジェクト
     *
     * @else
     * @brief Clone this port
     *
     * Pure virtual function to generate this clone port.
     *
     * @return The clone InPortConsumer object
     *
     * @endif
     */
    virtual InPortConsumer* clone() const = 0;
    
    /*!
     * @if jp
     * @brief データ送出通知受け取りへの登録
     *
     * 指定されたプロパティの内容に基づいて、データ送出通知の受け取りに登録する
     * ための純粋仮想関数。
     *
     * @param properties 登録時に参照するプロパティ
     *
     * @return 登録処理結果
     *
     * @else
     * @brief Subscribe the data send notification
     *
     * Pure virtual function to subscribe the data send notification
     * based on specified property information.
     *
     * @param properties Properties for reference when subscribing
     *
     * @return Subscription result
     *
     * @endif
     */
    virtual bool subscribeInterface(const SDOPackage::NVList& properties) = 0;
    
    /*!
     * @if jp
     * @brief データ送出通知受け取りからの登録解除
     *
     * データ送出通知の受け取りから登録解除するための純粋仮想関数。
     *
     * @param properties 登録解除時に参照するプロパティ
     *
     * @else
     * @brief Unsubscribe the data send notification
     *
     * Pure virtual function to unsubscribe the data send notification.
     *
     * @param properties Properties for reference when unsubscribing
     *
     * @endif
     */
    virtual void unsubscribeInterface(const SDOPackage::NVList& properties) = 0;
    
  protected:
    
  private:
    
  };
};     // namespace RTC
#endif // InPortConsumer_h
