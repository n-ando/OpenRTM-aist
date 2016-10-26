// -*- C++ -*-
/*!
 * @file FsmActionListener.h
 * @brief component action listener class
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

#ifndef RTC_FSMACTIONLISTENER_H
#define RTC_FSMACTIONLISTENER_H

#include <vector>
#include <utility>
#include <coil/Mutex.h>
#include <coil/Guard.h>
#include <rtm/RTC.h>
#include <rtm/idl/RTCSkel.h>
#include <rtm/ConnectorBase.h>

namespace RTC
{
  struct FsmStructure
  {
  };
  /*!
   * @if jp
   *
   * FSMコンポーネントに関する種々の振る舞いをフックするためのリスナ定
   * 義。リスナには大きく分けると、
   *
   * - FSMそのものの動作をフックするためのリスナ
   * - FSMに関するメタデータ変更等の動作をフックするためのリスナ
   *
   * の2種類に分けられる。
   *
   * - PreFsmActionListener
   * - PostFsmActionListener
   * - FsmProfileListner
   * - FsmStructureListener
   */

  //============================================================
  /*!
   * @if jp
   * @brief PreFsmActionListener のタイプ
   *
   * - PRE_ON_INIT:          on_init 直前
   * - PRE_ON_ENTRY:         on_entry 直前
   * - PRE_ON_DO:            on_do 直前
   * - PRE_ON_EXIT:          on_exit 直前
   * - PRE_ON_STATE_CHANGE:  状態遷移直前
   *
   * @else
   * @brief The types of ConnectorDataListener
   * 
   * @endif
   */

  enum PreFsmActionListenerType
    {
      PRE_ON_INIT,
      PRE_ON_ENTRY,
      PRE_ON_DO,
      PRE_ON_EXIT,
      PRE_ON_STATE_CHANGE,
      PRE_FSM_ACTION_LISTENER_NUM
    };

  /*!
   * @if jp
   * @class PreFsmActionListener クラス
   * @brief PreFsmActionListener クラス
   *
   * - on_init()
   * - on_entry()
   * - on_do()
   * - on_exit()
   * - on_state_update()
   *
   * 各アクションに対応するユーザーコードが呼ばれる直前のタイミング
   * でコールされるリスナクラスの基底クラス。
   *
   * - PRE_ON_INIT:
   * - PRE_ON_ENTRY:
   * - PRE_ON_DO:
   * - PRE_ON_EXIT:
   * - PRE_ON_STATE_CHANGE:
   *
   * @else
   * @class PreFsmActionListener class
   * @brief PreFsmActionListener class
   *
   * This class is abstract base class for listener classes that
   * provides callbacks for various events in rtobject.
   *
   * @endif
   */
  class PreFsmActionListener
  {
  public:
    /*!
     * @if jp
     *
     * @brief PreFsmActionListenerType を文字列に変換
     *
     * PreFsmActionListenerType を文字列に変換する
     *
     * @param type 変換対象 PreFsmActionListenerType
     *
     * @return 文字列変換結果
     *
     * @else
     *
     * @brief Convert PreFsmActionListenerType into the string.
     *
     * Convert PreFsmActionListenerType into the string.
     *
     * @param type The target PreFsmActionListenerType for transformation
     *
     * @return Trnasformation result of string representation
     *
     * @endif
     */
    static const char* toString(PreFsmActionListenerType type)
    {
      static const char* typeString[] =
        {
          "PRE_ON_INIT",
          "PRE_ON_ENTRY",
          "PRE_ON_DO",
          "PRE_ON_EXIT",
          "PRE_ON_STATE_CHANGE",
          "PRE_FSM_ACTION_LISTENER_NUM"
        };
      if (type < PRE_FSM_ACTION_LISTENER_NUM) { return typeString[type]; }
      return "";
    }

    /*!
     * @if jp
     * @brief デストラクタ
     * @else
     * @brief Destructor
     * @endif
     */
    virtual ~PreFsmActionListener();

    /*!
     * @if jp
     *
     * @brief 仮想コールバック関数
     *
     * PreFsmActionListener のコールバック関数
     *
     * @else
     *
     * @brief Virtual Callback function
     *
     * This is a the Callback function for PreFsmActionListener.
     *
     * @endif
     */
    virtual void operator()(const char*) = 0;
  };


  //============================================================
  /*!
   * @if jp
   * @brief PostCompoenntActionListener のタイプ
   *
   * - POST_ON_INIT:
   * - POST_ON_ENTRY:
   * - POST_ON_DO:
   * - POST_ON_EXIT:
   * - POST_ON_STATE_CHANGE:
   *
   * @else
   * @brief The types of ConnectorDataListener
   * 
   * @endif
   */
  enum PostFsmActionListenerType
    {
      POST_ON_INIT,
      POST_ON_ENTRY,
      POST_ON_DO,
      POST_ON_EXIT,
      POST_ON_STATE_CHANGE,
      POST_FSM_ACTION_LISTENER_NUM
    };


  /*!
   * @if jp
   * @class PostFsmActionListener クラス
   * @brief PostFsmActionListener クラス
   *
   * OMG RTC仕様で定義されている以下のコンポーネントアクショントについ
   * て、
   *
   * - on_init()
   * - on_entry()
   * - on_do()
   * - on_exit()
   * - on_state_change()
   *
   * 各アクションに対応するユーザーコードが呼ばれる直前のタイミング
   * でコールされるリスなクラスの基底クラス。
   *
   * - POST_ON_INIT:
   * - POST_ON_ENTRY:
   * - POST_ON_DO:
   * - POST_ON_EXIT:
   * - POST_ON_STATE_CHANGE:
   *
   * @else
   * @class PostFsmActionListener class
   * @brief PostFsmActionListener class
   *
   * This class is abstract base class for listener classes that
   * provides callbacks for various events in rtobject.
   *
   * @endif
   */
  class PostFsmActionListener
  {
  public:
    /*!
     * @if jp
     *
     * @brief PostFsmActionListenerType を文字列に変換
     *
     * PostFsmActionListenerType を文字列に変換する
     *
     * @param type 変換対象 PostFsmActionListenerType
     *
     * @return 文字列変換結果
     *
     * @else
     *
     * @brief Convert PostFsmActionListenerType into the string.
     *
     * Convert PostFsmActionListenerType into the string.
     *
     * @param type The target PostFsmActionListenerType for transformation
     *
     * @return Trnasformation result of string representation
     *
     * @endif
     */
    static const char* toString(PostFsmActionListenerType type)
    {
      static const char* typeString[] =
        {
          "POST_ON_INIT",
          "POST_ON_ENTRY",
          "POST_ON_DO",
          "POST_ON_EXIT",
          "POST_ON_STATE_CHANGE",
          "POST_FSM_ACTION_LISTENER_NUM"
        };
      if (type < POST_FSM_ACTION_LISTENER_NUM)
        {
          return typeString[type];
        }
      return "";
    }

    /*!
     * @if jp
     * @brief デストラクタ
     * @else
     * @brief Destructor
     * @endif
     */
    virtual ~PostFsmActionListener();

    /*!
     * @if jp
     *
     * @brief 仮想コールバック関数
     *
     * PostFsmActionListener のコールバック関数
     *
     * @else
     *
     * @brief Virtual Callback function
     *
     * This is a the Callback function for PostFsmActionListener.
     *
     * @endif
     */
    virtual void operator()(const char* state,
                            ReturnCode_t ret) = 0;
  };

  //============================================================
  /*!
   * @if jp
   * @brief FsmProfileListener のタイプ
   *
   * - SET_FSM_PROFILE       : FSM Profile設定時
   * - GET_FSM_PROFILE       : FSM Profile取得時
   * - ADD_FSM_STATE         : FSMにStateが追加された
   * - REMOVE_FSM_STATE      : FSMからStateが削除された
   * - ADD_FSM_TRANSITION    : FSMに遷移が追加された
   * - REMOVE_FSM_TRANSITION : FSMから遷移が削除された
   * - BIND_FSM_EVENT        : FSMにイベントがバインドされた
   * - UNBIND_FSM_EVENT      : FSMにイベントがアンバインドされた
   *
   * @else
   * @brief The types of FsmProfileListener
   *
   * - SET_FSM_PROFILE       : Setting FSM Profile
   * - GET_FSM_PROFILE       : Getting FSM Profile
   * - ADD_FSM_STATE         : A State added to the FSM
   * - REMOVE_FSM_STATE      : A State removed from FSM
   * - ADD_FSM_TRANSITION    : A transition added to the FSM
   * - REMOVE_FSM_TRANSITION : A transition removed from FSM
   * - BIND_FSM_EVENT        : An event bounded to the FSM
   * - UNBIND_FSM_EVENT      : An event unbounded to the FSM
   *
   * @endif
   */
  enum FsmProfileListenerType
    {
      SET_FSM_PROFILE,
      GET_FSM_PROFILE,
      ADD_FSM_STATE,
      REMOVE_FSM_STATE,
      ADD_FSM_TRANSITION,
      REMOVE_FSM_TRANSITION,
      BIND_FSM_EVENT,
      UNBIND_FSM_EVENT,
      FSM_PROFILE_LISTENER_NUM
    };

  /*!
   * @if jp
   * @class FsmProfileListener クラス
   * @brief FsmProfileListener クラス
   *
   * 各アクションに対応するユーザーコードが呼ばれる直前のタイミング
   * でコールされるリスなクラスの基底クラス。
   *
   * - ADD_PORT:
   * - REMOVE_PORT:
   *
   * @else
   * @class FsmProfileListener class
   * @brief FsmProfileListener class
   *
   * This class is abstract base class for listener classes that
   * provides callbacks for various events in rtobject.
   *
   * @endif
   */
  class FsmProfileListener
  {
  public:
    /*!
     * @if jp
     *
     * @brief FsmProfileListenerType を文字列に変換
     *
     * FsmProfileListenerType を文字列に変換する
     *
     * @param type 変換対象 FsmProfileListenerType
     * @return 文字列変換結果
     *
     * @else
     *
     * @brief Convert FsmProfileListenerType into the string.
     *
     * Convert FsmProfileListenerType into the string.
     *
     * @param type The target FsmProfileListenerType for transformation
     * @return Trnasformation result of string representation
     *
     * @endif
     */
    static const char* toString(FsmProfileListenerType type)
    {
      static const char* typeString[] =
        {
          "SET_FSM_PROFILE",
          "GET_FSM_PROFILE",
          "ADD_FSM_STATE",
          "REMOVE_FSM_STATE",
          "ADD_FSM_TRANSITION",
          "REMOVE_FSM_TRANSITION",
          "BIND_FSM_EVENT",
          "UNBIND_FSM_EVENT",
          "FSM_PROFILE_LISTENER_NUM"
        };
      if (type < FSM_PROFILE_LISTENER_NUM) { return typeString[type]; }
      return "";
    }

    /*!
     * @if jp
     * @brief デストラクタ
     * @else
     * @brief Destructor
     * @endif
     */
    virtual ~FsmProfileListener();

    /*!
     * @if jp
     *
     * @brief 仮想コールバック関数
     *
     * FsmProfileListener のコールバック関数
     *
     * @else
     *
     * @brief Virtual Callback function
     *
     * This is a the Callback function for FsmProfileListener
     *
     * @endif
     */
    virtual void operator()(const ::RTC::FsmProfile& fsmprof) = 0;
  };


  //============================================================
  /*!
   * @if jp
   * @brief FsmStructureListener のタイプ
   *
   * - SET_FSM_STRUCTURE: FSM構造の設定
   * - GET_FSM_STRUCTURE: FSM構造の取得
   *
   * @else
   * @brief The types of FsmStructureListener
   *
   * - SET_FSM_STRUCTURE: Setting FSM structure
   * - GET_FSM_STRUCTURE: Getting FSM structure
   *
   * @endif
   */
  enum FsmStructureListenerType
    {
      SET_FSM_STRUCTURE,
      GET_FSM_STRUCTURE,
      FSM_STRUCTURE_LISTENER_NUM
    };

  /*!
   * @if jp
   * @class FsmStructureListener クラス
   * @brief FsmStructureListener クラス
   *
   * 各アクションに対応するユーザーコードが呼ばれる直前のタイミング
   * でコールされるリスなクラスの基底クラス。
   *
   * @else
   * @class FsmStructureListener class
   * @brief FsmStructureListener class
   *
   * This class is abstract base class for listener classes that
   * provides callbacks for various events in rtobject.
   *
   * @endif
   */
  class FsmStructureListener
  {
  public:
    /*!
     * @if jp
     *
     * @brief FsmStructureListenerType を文字列に変換
     *
     * FsmStructureListenerType を文字列に変換する
     *
     * @param type 変換対象 FsmStructureListenerType
     *
     * @return 文字列変換結果
     *
     * @else
     *
     * @brief Convert FsmStructureListenerType into the string.
     *
     * Convert FsmStructureListenerType into the string.
     *
     * @param type The target FsmStructureListenerType for transformation
     *
     * @return Trnasformation result of string representation
     *
     * @endif
     */
    static const char* toString(FsmStructureListenerType type)
    {
      static const char* typeString[] =
        {
          "SET_FSM_STRUCTURE",
          "GET_FSM_STRUCTURE",
          "FSM_STRUCTURE_LISTENER_NUM"
        };
      if (type < FSM_STRUCTURE_LISTENER_NUM) { return typeString[type]; }
      return "";
    }

    /*!
     * @if jp
     * @brief デストラクタ
     * @else
     * @brief Destructor
     * @endif
     */
    virtual ~FsmStructureListener();

    /*!
     * @if jp
     *
     * @brief 仮想コールバック関数
     *
     * FsmStructureListener のコールバック関数
     *
     * @else
     *
     * @brief Virtual Callback function
     *
     * This is a the Callback function for FsmStructureListener
     *
     * @endif
     */
    virtual void operator()(::RTC::FsmStructure& pprof) = 0;
  };


  //============================================================
  // Holder classes
  //============================================================
  /*!
   * @if jp
   * @class PreFsmActionListenerHolder
   * @brief PreFsmActionListener ホルダクラス
   *
   * 複数の PreFsmActionListener を保持し管理するクラス。
   *
   * @else
   * @class PreFsmActionListenerHolder
   * @brief PreFsmActionListener holder class
   *
   * This class manages one ore more instances of
   * PreFsmActionListener class.
   *
   * @endif
   */
  class PreFsmActionListenerHolder
  {
    typedef std::pair<PreFsmActionListener*, bool> Entry;
    typedef coil::Guard<coil::Mutex> Guard;
  public:
    /*!
     * @if jp
     * @brief コンストラクタ
     * @else
     * @brief Constructor
     * @endif
     */
    PreFsmActionListenerHolder();
    
    /*!
     * @if jp
     * @brief デストラクタ
     * @else
     * @brief Destructor
     * @endif
     */
    virtual ~PreFsmActionListenerHolder();
    
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
    void addListener(PreFsmActionListener* listener, bool autoclean);
    
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
    void removeListener(PreFsmActionListener* listener);

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
    void notify(const char* state);
      
  private:
    std::vector<Entry> m_listeners;
    coil::Mutex m_mutex;
  };


  /*!
   * @if jp
   * @class PostFsmActionListenerHolder
   * @brief PostFsmActionListener ホルダクラス
   *
   * 複数の PostFsmActionListener を保持し管理するクラス。
   *
   * @else
   * @class PostFsmActionListenerHolder
   * @brief PostFsmActionListener holder class
   *
   * This class manages one ore more instances of
   * PostFsmActionListener class.
   *
   * @endif
   */
  class PostFsmActionListenerHolder
  {
    typedef std::pair<PostFsmActionListener*, bool> Entry;
    typedef coil::Guard<coil::Mutex> Guard;
  public:
    /*!
     * @if jp
     * @brief コンストラクタ
     * @else
     * @brief Constructor
     * @endif
     */
    PostFsmActionListenerHolder();
    /*!
     * @if jp
     * @brief デストラクタ
     * @else
     * @brief Destructor
     * @endif
     */
    virtual ~PostFsmActionListenerHolder();
    
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
    void addListener(PostFsmActionListener* listener, bool autoclean);
    
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
    void removeListener(PostFsmActionListener* listener);
    
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
    void notify(const char* state, ReturnCode_t ret);
    
  private:
    std::vector<Entry> m_listeners;
    coil::Mutex m_mutex;
  };


  //============================================================
  /*!
   * @if jp
   * @class FsmProfileListenerHolder
   * @brief FsmProfileListener ホルダクラス
   *
   * 複数の FsmProfileListener を保持し管理するクラス。
   *
   * @else
   * @class FsmProfileListenerHolder
   * @brief FsmProfileListener holder class
   *
   * This class manages one ore more instances of
   * FsmProfileListener class.
   *
   * @endif
   */
  class FsmProfileListenerHolder
  {
    typedef std::pair<FsmProfileListener*, bool> Entry;
    typedef coil::Guard<coil::Mutex> Guard;
  public:
    /*!
     * @if jp
     * @brief コンストラクタ
     * @else
     * @brief Constructor
     * @endif
     */
    FsmProfileListenerHolder();
    /*!
     * @if jp
     * @brief デストラクタ
     * @else
     * @brief Destructor
     * @endif
     */
    virtual ~FsmProfileListenerHolder();

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
    void addListener(FsmProfileListener* listener, bool autoclean);

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
    void removeListener(FsmProfileListener* listener);

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
    void notify(RTC::FsmProfile& profile);

  private:
    std::vector<Entry> m_listeners;
    coil::Mutex m_mutex;
  };

  /*!
   * @if jp
   * @class FsmStructureListenerHolder
   * @brief FsmStructureListener ホルダクラス
   *
   * 複数の FsmStructureListener を保持し管理するクラス。
   *
   * @else
   * @class FsmStructureListenerHolder
   * @brief FsmStructureListener holder class
   *
   * This class manages one ore more instances of
   * FsmStructureListener class.
   *
   * @endif
   */
  class FsmStructureListenerHolder
  {
    typedef std::pair<FsmStructureListener*, bool> Entry;
    typedef coil::Guard<coil::Mutex> Guard;
  public:
    /*!
     * @if jp
     * @brief コンストラクタ
     * @else
     * @brief Constructor
     * @endif
     */
    FsmStructureListenerHolder();
    /*!
     * @if jp
     * @brief デストラクタ
     * @else
     * @brief Destructor
     * @endif
     */
    virtual ~FsmStructureListenerHolder();

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
    void addListener(FsmStructureListener* listener, bool autoclean);

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
    void removeListener(FsmStructureListener* listener);

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
    void notify(RTC::FsmStructure& structure);

  private:
    std::vector<Entry> m_listeners;
    coil::Mutex m_mutex;
  };

  //============================================================
  /*!
   * @if jp
   * @class FsmActionListeners
   * @brief FsmActionListeners クラス
   *
   *
   * @else
   * @class FsmActionListeners
   * @brief FsmActionListeners class
   *
   *
   * @endif
   */
  class FsmActionListeners
  {
  public:
    /*!
     * @if jp
     * @brief PreFsmActionListenerTypeリスナ配列
     * PreFsmActionListenerTypeリスナを格納
     * @else
     * @brief PreFsmActionListenerType listener array
     * The PreFsmActionListenerType listener is stored. 
     * @endif
     */
    PreFsmActionListenerHolder 
    preaction_[PRE_FSM_ACTION_LISTENER_NUM];
    /*!
     * @if jp
     * @brief PostFsmActionTypeリスナ配列
     * PostFsmActionTypeリスナを格納
     * @else
     * @brief PostFsmActionType listener array
     * The PostFsmActionType listener is stored.
     * @endif
     */
    PostFsmActionListenerHolder 
    postaction_[POST_FSM_ACTION_LISTENER_NUM];
    /*!
     * @if jp
     * @brief FsmProfileTypeリスナ配列
     * FsmProfileTypeリスナを格納
     * @else
     * @brief FsmProfileType listener array
     * The FsmProfileType listener is stored.
     * @endif
     */
    FsmProfileListenerHolder
    profile_[FSM_PROFILE_LISTENER_NUM];
    /*!
     * @if jp
     * @brief FsmStructureTypeリスナ配列
     * FsmStructureTypeリスナを格納
     * @else
     * @brief FsmStructureType listener array
     * The FsmStructureType listener is stored.
     * @endif
     */
    FsmStructureListenerHolder
    structure_[FSM_STRUCTURE_LISTENER_NUM];
  };

}; // namespace RTC

#endif // RTC_FSMACTIONLISTENER_H
