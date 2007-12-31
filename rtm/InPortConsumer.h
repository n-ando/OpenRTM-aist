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
 * $Id: InPortConsumer.h,v 1.4.4.1 2007-12-31 03:08:03 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.4  2007/01/09 09:56:01  n-ando
 * Include order has changed.
 *
 * Revision 1.3  2007/01/06 17:50:22  n-ando
 * Interface subscription/unsubscription functions (subscribeInterface()
 * and unsubscribeInterface()) are added.
 * The clone() function to clone the instance is added.
 *
 * Revision 1.2  2006/12/02 18:39:06  n-ando
 * InPortCorbaConsumer class moved to InPortCorbaConsumer.h
 *
 * Revision 1.1  2006/11/27 09:44:39  n-ando
 * The first commitment.
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
   * @brief InPortConsumer class
   * @endif
   */
  class InPortConsumer
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
     *
     * @endif
     */
    virtual void unsubscribeInterface(const SDOPackage::NVList& properties) = 0;
    
  protected:
    
  private:
    
  };
};     // namespace RTC
#endif // InPortConsumer_h
