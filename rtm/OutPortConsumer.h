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
 * $Id: OutPortConsumer.h,v 1.3.4.1 2007-12-31 03:08:05 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.3  2007/01/06 17:57:14  n-ando
 * Interface subscription/unsubscription functions (subscribeInterface()
 * and unsubscribeInterface()) are added.
 *
 * Revision 1.2  2006/12/02 18:46:55  n-ando
 * OutPortCorbaConsumer class was moved to OutPortCorbaConsumer.h
 *
 * Revision 1.1  2006/11/27 09:44:41  n-ando
 * The first commitment.
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
   * @brief OutPortConsumer class
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
     * @endif
     */
    virtual ~OutPortConsumer(){};
    
    /*!
     * @if jp
     *
     * @brief データを受信する
     *
     * データ受信を実行するための純粋仮想関数。
     *
     * @else
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
     * @endif
     */
    virtual void unsubscribeInterface(const SDOPackage::NVList& properties) = 0;
    
  protected:
    
  private:
    
  };
};     // namespace RTC
#endif // OutPortConsumer_h

