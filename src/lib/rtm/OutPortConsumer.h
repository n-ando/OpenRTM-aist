// -*- C++ -*-
/*!
 * @file  OutPortConsumer.h
 * @brief OutPortConsumer class
 * @date  $Date: 2007-12-31 03:08:05 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006-2009
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

#ifndef RTC_OUTPORTCONSUMER_H
#define RTC_OUTPORTCONSUMER_H

#include <coil/Factory.h>
#include <rtm/DataPortStatus.h>
#include <rtm/CdrBufferBase.h>

namespace SDOPackage
{
  class NVList;
};

namespace coil
{
  class Properties;
};

namespace RTC
{
  class ConnectorListeners;
  class ConnectorInfo;

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
    : public DataPortStatus
  {
  public:
    DATAPORTSTATUS_ENUM
    
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
     * @brief 設定初期化
     *
     * OutPortConsumerの各種設定を行う。実装クラスでは、与えられた
     * Propertiesから必要な情報を取得して各種設定を行う。この init() 関
     * 数は、OutPortProvider生成直後および、接続時にそれぞれ呼ばれる可
     * 能性がある。したがって、この関数は複数回呼ばれることを想定して記
     * 述されるべきである。
     * 
     * @param prop 設定情報
     *
     * @else
     *
     * @brief Initializing configuration
     *
     * This operation would be called to configure in initialization.
     * In the concrete class, configuration should be performed
     * getting appropriate information from the given Properties data.
     * This function might be called right after instantiation and
     * connection sequence respectivly.  Therefore, this function
     * should be implemented assuming multiple call.
     *
     * @param prop Configuration information
     *
     * @endif
     */
    virtual void init(coil::Properties& prop) = 0;

    /*!
     * @if jp
     * @brief バッファをセットする
     *
     * OutPortConsumerがデータを取り出すバッファをセットする。
     * すでにセットされたバッファがある場合、以前のバッファへの
     * ポインタに対して上書きされる。
     * OutPortProviderはバッファの所有権を仮定していないので、
     * バッファの削除はユーザの責任で行わなければならない。
     *
     * @param buffer OutPortProviderがデータを取り出すバッファへのポインタ
     *
     * @else
     * @brief Setting outside buffer's pointer
     *
     * A pointer to a buffer from which OutPortProvider retrieve data.
     * If already buffer is set, previous buffer's pointer will be
     * overwritten by the given pointer to a buffer.  Since
     * OutPortProvider does not assume ownership of the buffer
     * pointer, destructor of the buffer should be done by user.
     * 
     * @param buffer A pointer to a data buffer to be used by OutPortProvider
     *
     * @endif
     */
    virtual void setBuffer(CdrBufferBase* buffer) = 0;
    virtual void setListener(ConnectorInfo& info,
                             ConnectorListeners* listeners) = 0;

    /*!
     * @if jp
     *
     * @brief データを受信する
     *
     * データ受信を実行するための純粋仮想関数。
     * 具象クラスでは、それぞれの方法でリモートのOutPortからデータを
     * 受信するロジックを実装する。
     * 受信に関する状態に応じて以下の戻り値を返す。
     *
     * @param data 受信データ
     * @return PORT_OK         正常終了
     *         BUFFER_TIMEOUT  タイムアウトした
     *         RECV_EMPTY      取得先のバッファが空である。
     *         CONNECTION_LOST 接続が切断された
     *         PORT_ERROR      エラー
     *         UNKNOWN_ERROR   本来ありえないエラー
     *
     * @else
     *
     * @brief Receive data
     *
     * Pure virtual function to receive data.
     *
     * @endif
     */
    virtual ReturnCode get(cdrMemoryStream& data) = 0;

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

    /*!
     * @if jp
     * @brief Interface接続用Functor
     * @else
     * @brief Functor to subscribe the interface
     * @endif
     */
    struct subscribe
    {
      subscribe(const SDOPackage::NVList& prop) : m_prop(prop) {}
      void operator()(OutPortConsumer* consumer)
      {
        consumer->subscribeInterface(m_prop);
      }
      const SDOPackage::NVList& m_prop;
    };
    
    /*!
     * @if jp
     * @brief Interface接続解除用Functor
     * @else
     * @brief Functor to unsubscribe the interface
     * @endif
     */
    struct unsubscribe
    {
      unsubscribe(const SDOPackage::NVList& prop) : m_prop(prop) {}
      void operator()(OutPortConsumer* consumer)
      {
        consumer->unsubscribeInterface(m_prop);
      }
      const SDOPackage::NVList& m_prop;
    };
  };

  typedef ::coil::GlobalFactory<OutPortConsumer> OutPortConsumerFactory;

};     // namespace RTC
#endif // OutPortConsumer_h

