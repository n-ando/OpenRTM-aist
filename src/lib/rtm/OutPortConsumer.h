// -*- C++ -*-
/*!
 * @file  OutPortConsumer.h
 * @brief OutPortConsumer class
 * @date  $Date: 2007-12-31 03:08:05 $
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

#ifndef OutPortConsumer_h
#define OutPortConsumer_h

#include <rtm/CorbaConsumer.h>
#include <rtm/NVUtil.h>

namespace RTC
{
  /*!
   * @if jp
   *
   * @class OutPortConsumer
   *
   * @brief OutPortConsumer 抽象クラス
   *
   * 出力ポートコンシューマのための抽象インターフェースクラス
   * 各具象クラスは、以下の純粋仮想関数の実装を提供しなければならない。
   * - pull(): データ受信
   * - subscribeInterface(): データ受信通知への登録
   * - unsubscribeInterface(): データ受信通知の登録解除
   *
   * @since 0.4.0
   *
   * @else
   * @class OutPortConsumer
   *
   * @brief OutPortConsumer abstract class
   *
   * This is the abstract interface class for the output port Consumer.
   * Concrete classes must implement the following pure virtual functions.
   * - pull(): Receive data
   * - subscribeInterface(): Subscribe to the data receive notification
   * - unsubscribeInterface(): Unsubscribe the data receive notification
   *
   * @since 0.4.0
   *
   * @endif
   */
  class OutPortConsumer
  {
  public:
    /***
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
    //    OutPortConsumer(){};
    
    /*!
     * @if jp
     *
     * @brief デストラクタ
     *
     * デストラクタ。
     *
     * @else
     * @brief Destructor
     *
     * Destructor
     *
     * @endif
     */
    virtual ~OutPortConsumer(void){};
    
    /*!
     * @if jp
     *
     * @brief データを受信する
     *
     * データ受信を実行するための純粋仮想関数。
     *
     * @else
     *
     * @brief Receive data
     *
     * Pure virtual function to receive data.
     *
     * @endif
     */
    virtual void pull() = 0;
    
    /*!
     * @if jp
     *
     * @brief データ受信通知への登録
     *
     * 指定されたプロパティ情報に基づいて、データ受信通知に登録するための
     * 純粋仮想関数。
     *
     * @param properties 登録用プロパティ
     *
     * @return 登録処理結果(登録成功:true、登録失敗:false)
     *
     * @else
     *
     * @brief Subscribe the data receive notification
     *
     * Pure virtual function to subscribe the data receive notification
     * based on specified property information.
     *
     * @param properties Properties for subscription
     *
     * @return Subscription result (Successful:true, Failed:false)
     *
     * @endif
     */
    virtual bool subscribeInterface(const SDOPackage::NVList& properties) = 0;
    
    /*!
     * @if jp
     *
     * @brief データ受信通知からの登録解除
     *
     * データ受信通知からの登録を解除するための純粋仮想関数。
     *
     * @param properties 登録解除用プロパティ
     *
     * @return 登録解除処理結果(登録解除成功:true、登録解除失敗:false)
     *
     * @else
     *
     * @brief Unsubscribe the data receive notification
     *
     * Pure virtual function to unsubscribe the data receive notification.
     *
     * @param properties Properties for unsubscription
     *
     * @return Unsubscription result (Successful:true, Failed:false)
     *
     * @endif
     */
    virtual void unsubscribeInterface(const SDOPackage::NVList& properties) = 0;
    
  protected:
    
  private:
    
  };
};     // namespace RTC
#endif // OutPortConsumer_h

