// -*- C++ -*-
/*!
 * @file PortConnectListener.h
 * @brief port's internal action listener classes
 * @date $Date$
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2011
 *     Noriaki Ando
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id$
 *
 */

#ifndef RTC_PORTCONNECTLISTENER_H
#define RTC_PORTCONNECTLISTENER_H

#include <mutex>
#include <rtm/RTC.h>
#include <rtm/idl/RTCSkel.h>

#include <vector>
#include <utility>
#include <array>

namespace RTC
{
  //============================================================
  /*!
   * @if jp
   * @brief PortConnectListener のタイプ
   *
   * - ON_NOTIFY_CONNECT:         notify_connect() 関数内呼び出し直後
   * - ON_NOTIFY_DISCONNECT:      notify_disconnect() 呼び出し直後
   * - ON_UNSUBSCRIBE_INTERFACES: notify_disconnect() 内のIF購読解除時
   *
   * @else
   * @brief The types of ConnectorDataListener
   *
   * - ON_NOTIFY_CONNECT:         right after entering into notify_connect()
   * - ON_NOTIFY_DISCONNECT:      right after entering into notify_disconnect()
   * - ON_UNSUBSCRIBE_INTERFACES: unsubscribing IF in notify_disconnect()
   *
   * @endif
   */
  enum class PortConnectListenerType : uint8_t
    {
      ON_NOTIFY_CONNECT,
      ON_NOTIFY_DISCONNECT,
      ON_UNSUBSCRIBE_INTERFACES,
      PORT_CONNECT_LISTENER_NUM
    };

  /*!
   * @if jp
   * @class PortConnectListener クラス
   * @brief PortConnectListener クラス
   *
   * 各アクションに対応するユーザーコードが呼ばれる直前のタイミング
   * でコールされるリスナクラスの基底クラス。
   *
   * - ON_NOTIFY_CONNECT:         notify_connect() 関数内呼び出し直後
   * - ON_NOTIFY_DISCONNECT:      notify_disconnect() 呼び出し直後
   * - ON_UNSUBSCRIBE_INTERFACES: notify_disconnect() 内のIF購読解除時
   *
   * @else
   * @class PortConnectListener class
   * @brief PortConnectListener class
   *
   * This class is abstract base class for listener classes that
   * provides callbacks for various events in rtobject.
   *
   * - ON_NOTIFY_CONNECT:         right after entering into notify_connect()
   * - ON_NOTIFY_DISCONNECT:      right after entering into notify_disconnect()
   * - ON_UNSUBSCRIBE_INTERFACES: unsubscribing IF in notify_disconnect()
   *
   * @endif
   */
  class PortConnectListener
  {
  public:
    /*!
     * @if jp
     *
     * @brief PortConnectListenerType を文字列に変換
     *
     * PortConnectListenerType を文字列に変換する
     *
     * @param type 変換対象 PortConnectListenerType
     *
     * @return 文字列変換結果
     *
     * @else
     *
     * @brief Convert PortConnectListenerType into the string.
     *
     * Convert PortConnectListenerType into the string.
     *
     * @param type The target PortConnectListenerType for transformation
     *
     * @return Trnasformation result of string representation
     *
     * @endif
     */
    static const char* toString(PortConnectListenerType type);

    /*!
     * @if jp
     * @brief デストラクタ
     * @else
     * @brief Destructor
     * @endif
     */
    virtual ~PortConnectListener();

    /*!
     * @if jp
     *
     * @brief 仮想コールバック関数
     *
     * PortConnectListener のコールバック関数
     *
     * @else
     *
     * @brief Virtual Callback function
     *
     * This is a the Callback function for PortConnectListener.
     *
     * @endif
     */
    virtual void operator()(const char* portname,
                            RTC::ConnectorProfile& profile) = 0;
  };


  //============================================================
  /*!
   * @if jp
   * @brief PortConnectRetListenerType のタイプ
   *
   * - ON_CONNECT_NEXTPORT:     notify_connect() 中のカスケード呼び出し直後
   * - ON_SUBSCRIBE_INTERFACES: notify_connect() 中のインターフェース購読直後
   * - ON_CONNECTED:            nofity_connect() 接続処理完了時に呼び出される
   * - ON_DISCONNECT_NEXT:      notify_disconnect() 中にカスケード呼び出し直後
   * - ON_DISCONNECTED:         notify_disconnect() リターン時
   *
   * @else
   * @brief The types of PortConnectRetListenerType
   *
   * - ON_CONNECT_NEXTPORT:     after cascade-call in notify_connect()
   * - ON_SUBSCRIBE_INTERFACES: after IF subscribing in notify_connect()
   * - ON_CONNECTED:            completed nofity_connect() connection process
   * - ON_DISCONNECT_NEXT:      after cascade-call in notify_disconnect()
   * - ON_DISCONNECTED:         completed notify_disconnect() disconnection
   *
   * @endif
   */
  enum class PortConnectRetListenerType : uint8_t
    {
      ON_PUBLISH_INTERFACES,
      ON_CONNECT_NEXTPORT,
      ON_SUBSCRIBE_INTERFACES,
      ON_CONNECTED,
      ON_DISCONNECT_NEXT,
      ON_DISCONNECTED,
      PORT_CONNECT_RET_LISTENER_NUM
    };

   /*!
   * @if jp
   * @class PortConnectRetListener クラス
   * @brief PortConnectRetListener クラス
   *
   * 各アクションに対応するユーザーコードが呼ばれる直前のタイミング
   * でコールされるリスなクラスの基底クラス。
   *
   * - ON_PUBLISH_INTERFACES:   notify_connect() 中のインターフェース公開直後
   * - ON_CONNECT_NEXTPORT:     notify_connect() 中のカスケード呼び出し直後
   * - ON_SUBSCRIBE_INTERFACES: notify_connect() 中のインターフェース購読直後
   * - ON_CONNECTED:            nofity_connect() 接続処理完了時に呼び出される
   * - ON_DISCONNECT_NEXT:      notify_disconnect() 中にカスケード呼び出し直後
   * - ON_DISCONNECTED:         notify_disconnect() リターン時
   *
   * @else
   * @class PortConnectRetListener class
   * @brief PortConnectRetListener class
   *
   * This class is abstract base class for listener classes that
   * provides callbacks for various events in rtobject.
   *
   * - ON_CONNECT_NEXTPORT:     after cascade-call in notify_connect()
   * - ON_SUBSCRIBE_INTERFACES: after IF subscribing in notify_connect()
   * - ON_CONNECTED:            completed nofity_connect() connection process
   * - ON_DISCONNECT_NEXT:      after cascade-call in notify_disconnect()
   * - ON_DISCONNECTED:         completed notify_disconnect() disconnection
   *
   * @endif
   */
  class PortConnectRetListener
  {
  public:
    /*!
     * @if jp
     *
     * @brief PortConnectRetListenerType を文字列に変換
     *
     * PortConnectRetListenerType を文字列に変換する
     *
     * @param type 変換対象 PortConnectRetListenerType
     *
     * @return 文字列変換結果
     *
     * @else
     *
     * @brief Convert PortConnectRetListenerType into string.
     *
     * Convert PortConnectRetListenerType into string.
     *
     * @param type The target PortConnectRetListenerType for transformation
     *
     * @return Trnasformation result of string representation
     *
     * @endif
     */
    static const char* toString(PortConnectRetListenerType type);

    /*!
     * @if jp
     * @brief デストラクタ
     * @else
     * @brief Destructor
     * @endif
     */
    virtual ~PortConnectRetListener();

    /*!
     * @if jp
     *
     * @brief 仮想コールバック関数
     *
     * PortConnectRetListener のコールバック関数
     *
     * @else
     *
     * @brief Virtual Callback function
     *
     * This is a the Callback function for PortConnectRetListener.
     *
     * @endif
     */
    virtual void operator()(const char* portname,
                            RTC::ConnectorProfile& profile,
                            ReturnCode_t ret) = 0;
  };

  //============================================================
  /*!
   * @if jp
   * @class PortConnectListenerHolder
   * @brief PortConnectListener ホルダクラス
   *
   * 複数の PortConnectListener を保持し管理するクラス。
   *
   * @else
   * @class PortConnectListenerHolder
   * @brief PortConnectListener holder class
   *
   * This class manages one ore more instances of
   * PortConnectListener class.
   *
   * @endif
   */
  class PortConnectListenerHolder
  {
    using Entry = std::pair<PortConnectListener*, bool>;
  public:
    /*!
     * @if jp
     * @brief コンストラクタ
     * @else
     * @brief Constructor
     * @endif
     */
    PortConnectListenerHolder();

    /*!
     * @if jp
     * @brief デストラクタ
     * @else
     * @brief Destructor
     * @endif
     */
    virtual ~PortConnectListenerHolder();

    /*!
     * @if jp
     *
     * @brief リスナーの追加
     *
     * リスナーを追加する。
     *
     * @param listener 追加するリスナ
     * @param autoclean true:デストラクタで削除する,
     *                  false:デストラクタで削除しない
     * @else
     *
     * @brief Add the listener.
     *
     * This method adds the listener.
     *
     * @param listener Added listener
     * @param autoclean true:The listener is deleted at the destructor.,
     *                  false:The listener is not deleted at the destructor.
     * @endif
     */
    void addListener(PortConnectListener* listener, bool autoclean);

    /*!
     * @if jp
     *
     * @brief リスナーの削除
     *
     * リスナを削除する。
     *
     * @param listener 削除するリスナ
     * @else
     *
     * @brief Remove the listener.
     *
     * This method removes the listener.
     *
     * @param listener Removed listener
     * @endif
     */
    void removeListener(PortConnectListener* listener);

    /*!
     * @if jp
     *
     * @brief リスナーへ通知する
     *
     * 登録されているリスナのコールバックメソッドを呼び出す。
     *
     * @param info ConnectorInfo
     * @else
     *
     * @brief Notify listeners.
     *
     * This calls the Callback method of the registered listener.
     *
     * @param info ConnectorInfo
     * @endif
     */
    void notify(const char* portname, RTC::ConnectorProfile& profile);

  private:
    std::vector<Entry> m_listeners;
    std::mutex m_mutex;
  };


  /*!
   * @if jp
   * @class PortConnectRetListenerHolder
   * @brief PortConnectRetListener ホルダクラス
   *
   * 複数の PortConnectRetListener を保持し管理するクラス。
   *
   * @else
   * @class PortConnectRetListenerHolder
   * @brief PortConnectRetListener holder class
   *
   * This class manages one ore more instances of
   * PortConnectRetListener class.
   *
   * @endif
   */
  class PortConnectRetListenerHolder
  {
    using Entry = std::pair<PortConnectRetListener*, bool>;
  public:
    /*!
     * @if jp
     * @brief コンストラクタ
     * @else
     * @brief Constructor
     * @endif
     */
    PortConnectRetListenerHolder();

    /*!
     * @if jp
     * @brief デストラクタ
     * @else
     * @brief Destructor
     * @endif
     */
    virtual ~PortConnectRetListenerHolder();

    /*!
     * @if jp
     *
     * @brief リスナーの追加
     *
     * リスナーを追加する。
     *
     * @param listener 追加するリスナ
     * @param autoclean true:デストラクタで削除する,
     *                  false:デストラクタで削除しない
     * @else
     *
     * @brief Add the listener.
     *
     * This method adds the listener.
     *
     * @param listener Added listener
     * @param autoclean true:The listener is deleted at the destructor.,
     *                  false:The listener is not deleted at the destructor.
     * @endif
     */
    void addListener(PortConnectRetListener* listener, bool autoclean);

    /*!
     * @if jp
     *
     * @brief リスナーの削除
     *
     * リスナを削除する。
     *
     * @param listener 削除するリスナ
     * @else
     *
     * @brief Remove the listener.
     *
     * This method removes the listener.
     *
     * @param listener Removed listener
     * @endif
     */
    void removeListener(PortConnectRetListener* listener);

    /*!
     * @if jp
     *
     * @brief リスナーへ通知する
     *
     * 登録されているリスナのコールバックメソッドを呼び出す。
     *
     * @param info ConnectorInfo
     * @param cdrdata データ
     * @else
     *
     * @brief Notify listeners.
     *
     * This calls the Callback method of the registered listener.
     *
     * @param info ConnectorInfo
     * @param cdrdata Data
     * @endif
     */
    void notify(const char* portname, RTC::ConnectorProfile& profile,
                ReturnCode_t ret);

  private:
    std::vector<Entry> m_listeners;
    std::mutex m_mutex;
  };

  /*!
   * @if jp
   * @class PortConnectListeners
   * @brief PortConnectListeners クラス
   *
   *
   * @else
   * @class PortConnectListeners
   * @brief PortConnectListeners class
   *
   *
   * @endif
   */
  class PortConnectListeners
  {
  public:
    /*!
     * @if jp
     * @brief コンストラクタ
     * @else
     * @brief Constructor
     * @endif
     */
    PortConnectListeners();
    /*!
     * @if jp
     * @brief デストラクタ
     * @else
     * @brief Destructor
     * @endif
     */
    ~PortConnectListeners();
    /*!
     * @if jp
     *
     * @brief リスナーの追加
     *
     * 指定の種類のPortConnectListenerを追加する。
     *
     * @param type リスナの種類
     * @param listener 追加するリスナ
     * @param autoclean true:デストラクタで削除する,
     *                  false:デストラクタで削除しない
     * @return false：指定の種類のリスナが存在しない
     * @else
     *
     * @brief Add the listener.
     *
     *
     *
     * @param type 
     * @param listener Added listener
     * @param autoclean true:The listener is deleted at the destructor.,
     *                  false:The listener is not deleted at the destructor.
     * @return
     * @endif
     */
    bool addListener(PortConnectListenerType type, PortConnectListener* listener, bool autoclean=true);
    /*!
     * @if jp
     *
     * @brief リスナーの削除
     *
     * 指定の種類のPortConnectListenerを削除する。
     *
     * @param type リスナの種類
     * @param listener 削除するリスナ
     * @return false：指定の種類のリスナが存在しない
     *
     * @else
     *
     * @brief Remove the listener.
     *
     *
     * @param type
     * @param listener
     * @return
     *
     * @endif
     */
    bool removeListener(PortConnectListenerType type, PortConnectListener* listener);
    /*!
     * @if jp
     *
     * @brief リスナーの追加
     *
     * 指定の種類のPortConnectRetListenerを追加する。
     *
     * @param type リスナの種類
     * @param listener 追加するリスナ
     * @param autoclean true:デストラクタで削除する,
     *                  false:デストラクタで削除しない
     * @return false：指定の種類のリスナが存在しない
     * @else
     *
     * @brief Add the listener.
     *
     *
     *
     * @param type 
     * @param listener Added listener
     * @param autoclean true:The listener is deleted at the destructor.,
     *                  false:The listener is not deleted at the destructor.
     * @return
     * @endif
     */
    bool addListener(PortConnectRetListenerType type, PortConnectRetListener* listener, bool autoclean=true);
    /*!
     * @if jp
     *
     * @brief リスナーの削除
     *
     * 指定の種類のPortConnectRetListenerを削除する。
     *
     * @param type リスナの種類
     * @param listener 削除するリスナ
     * @return false：指定の種類のリスナが存在しない
     *
     * @else
     *
     * @brief Remove the listener.
     *
     *
     * @param type
     * @param listener
     * @return
     *
     * @endif
     */
    bool removeListener(PortConnectRetListenerType type, PortConnectRetListener* listener);
    /*!
     * @if jp
     *
     * @brief リスナーへ通知する
     *
     * 指定の種類のPortConnectListenerのコールバック関数を呼び出す。
     *
     * @param type リスナの種類
     * @param portname ポート名
     * @param profile コネクタプロファイル
     * @return false：指定の種類のリスナが存在しない
     * @else
     *
     * @brief 
     *
     *
     * @param type 
     * @param portname 
     * @param profile
     * @return
     * @endif
     */
    inline bool notify(PortConnectListenerType type, const char* portname, RTC::ConnectorProfile& profile)
    {
        if (static_cast<uint8_t>(type) < portconnect_.size())
        {
            portconnect_[static_cast<uint8_t>(type)].notify(portname, profile);
            return true;
        }
        return false;
    }
    /*!
     * @if jp
     *
     * @brief リスナーへ通知する
     *
     * 指定の種類のPortConnectRetListenerのコールバック関数を呼び出す。
     *
     * @param type リスナの種類
     * @param portname ポート名
     * @param profile コネクタプロファイル
     * @param ret リターンコード
     * @return false：指定の種類のリスナが存在しない
     * @else
     *
     * @brief
     *
     *
     * @param type
     * @param portname
     * @param profile
     * @param ret
     * @return
     * @endif
     */
    inline bool notify(PortConnectRetListenerType type, const char* portname, RTC::ConnectorProfile& profile,
                ReturnCode_t ret)
    {
        if (static_cast<uint8_t>(type) < portconnret_.size())
        {
            portconnret_[static_cast<uint8_t>(type)].notify(portname, profile, ret);
            return true;
        }
        return false;
    }

  private:
    /*!
     * @if jp
     * @brief PortConnectListenerType リスナ配列
     * PortConnectListenerType リスナを格納
     * @else
     * @brief PortConnectListenerType listener array
     * The PortConnectListenerType listener is stored.
     * @endif
     */
    std::array<PortConnectListenerHolder, 
        static_cast<uint8_t>
        (PortConnectListenerType::PORT_CONNECT_LISTENER_NUM)>
        portconnect_;
    /*!
     * @if jp
     * @brief PortConnectRetTypeリスナ配列
     * PortConnectRetTypeリスナを格納
     * @else
     * @brief PortConnectRetType listener array
     * The PortConnectRetType listener is stored.
     * @endif
     */
    std::array<PortConnectRetListenerHolder,
        static_cast<uint8_t>
        (PortConnectRetListenerType::PORT_CONNECT_RET_LISTENER_NUM)>
        portconnret_;
  };


} // namespace RTC

#endif  // RTC_PORTCONNECTLISTENER_H
