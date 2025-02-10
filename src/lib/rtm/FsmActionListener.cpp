// -*- C++ -*-
/*!
 * @file FsmActionListener.cpp
 * @brief Component action listener class
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

#include <rtm/FsmActionListener.h>

namespace RTC
{

  //============================================================
  /*!
   * @if jp
   * @class PostFsmActionListener クラス
   * @else
   * @class PostFsmActionListener class
   * @endif
   */
  PostFsmActionListener::~PostFsmActionListener() = default;

  /*!
   * @if jp
   * @class PreFsmActionListener クラス
   * @else
   * @class PreFsmActionListener class
   * @endif
   */
  PreFsmActionListener::~PreFsmActionListener() = default;

  /*!
   * @if jp
   * @class FsmProfileListener クラス
   * @else
   * @class PortActionListener class
   * @endif
   */
  FsmProfileListener::~FsmProfileListener() = default;

  /*!
   * @if jp
   * @class PortActionListener クラス
   * @else
   * @class PortActionListener class
   * @endif
   */
  FsmStructureListener::~FsmStructureListener() = default;

  /*!
   * @if jp
   * @class FsmActionListeners クラス
   * @else
   * @class FsmActionListeners class
   * @endif
   */
  FsmActionListeners::FsmActionListeners() = default;

  FsmActionListeners::~FsmActionListeners() = default;

  //============================================================
  /*!
   * @if jp
   * @class PreFsmActionListener ホルダクラス
   * @else
   * @class PreFsmActionListener holder class
   * @endif
   */
  PreFsmActionListenerHolder::PreFsmActionListenerHolder() = default;

  PreFsmActionListenerHolder::~PreFsmActionListenerHolder()
  {
    std::lock_guard<std::mutex> guard(m_mutex);
    for (auto & listener : m_listeners)
      {
        if (listener.second)
          {
            delete listener.first;
          }
      }
  }

  void PreFsmActionListenerHolder::
  addListener(PreFsmActionListener* listener,
              bool autoclean)
  {
    std::lock_guard<std::mutex> guard(m_mutex);
    m_listeners.emplace_back(listener, autoclean);
  }

  void PreFsmActionListenerHolder::
  removeListener(PreFsmActionListener* listener)
  {
    std::lock_guard<std::mutex> guard(m_mutex);
    std::vector<Entry>::iterator it(m_listeners.begin());

    for (; it != m_listeners.end(); ++it)
      {
        if ((*it).first == listener)
          {
            if ((*it).second)
              {
                delete (*it).first;
              }
            m_listeners.erase(it);
            return;
          }
      }
  }

  void PreFsmActionListenerHolder::notify(const char* state)
  {
    std::lock_guard<std::mutex> guard(m_mutex);
    for (auto & listener : m_listeners)
      {
        listener.first->operator()(state);
      }
  }

  //============================================================
  /*!
   * @if jp
   * @class PostFsmActionListener ホルダクラス
   * @else
   * @class PostFsmActionListener holder class
   * @endif
   */
  PostFsmActionListenerHolder::PostFsmActionListenerHolder() = default;

  PostFsmActionListenerHolder::~PostFsmActionListenerHolder()
  {
    std::lock_guard<std::mutex> guard(m_mutex);
    for (auto & listener : m_listeners)
      {
        if (listener.second)
          {
            delete listener.first;
          }
      }
  }

  void PostFsmActionListenerHolder::
  addListener(PostFsmActionListener* listener, bool autoclean)
  {
    std::lock_guard<std::mutex> guard(m_mutex);
    m_listeners.emplace_back(listener, autoclean);
  }

  void PostFsmActionListenerHolder::
  removeListener(PostFsmActionListener* listener)
  {
    std::lock_guard<std::mutex> guard(m_mutex);
    std::vector<Entry>::iterator it(m_listeners.begin());
    for (; it != m_listeners.end(); ++it)
      {
        if ((*it).first == listener)
          {
            if ((*it).second)
              {
                delete (*it).first;
              }
            m_listeners.erase(it);
            return;
          }
      }
  }

  void PostFsmActionListenerHolder::notify(const char* state,
                                           ReturnCode_t ret)
  {
    std::lock_guard<std::mutex> guard(m_mutex);
    for (auto & listener : m_listeners)
      {
        listener.first->operator()(state, ret);
      }
  }

  /*!
   * @if jp
   * @class FsmProfileListener ホルダクラス
   * @else
   * @class FsmProfileListener holder class
   * @endif
   */
  FsmProfileListenerHolder::FsmProfileListenerHolder() = default;

  FsmProfileListenerHolder::~FsmProfileListenerHolder()
  {
    std::lock_guard<std::mutex> guard(m_mutex);
    for (auto & listener : m_listeners)
      {
        if (listener.second)
          {
            delete listener.first;
          }
      }
  }

  void FsmProfileListenerHolder::addListener(FsmProfileListener* listener,
                                             bool autoclean)
  {
    std::lock_guard<std::mutex> guard(m_mutex);
    m_listeners.emplace_back(listener, autoclean);
  }

  void
  FsmProfileListenerHolder::removeListener(FsmProfileListener* listener)
  {
    std::lock_guard<std::mutex> guard(m_mutex);
    std::vector<Entry>::iterator it(m_listeners.begin());

    for (; it != m_listeners.end(); ++it)
      {
        if ((*it).first == listener)
          {
            if ((*it).second)
              {
                delete (*it).first;
              }
            m_listeners.erase(it);
            return;
          }
      }
  }

  void FsmProfileListenerHolder::notify(RTC::FsmProfile& profile)
  {
    std::lock_guard<std::mutex> guard(m_mutex);
    for (auto & listener : m_listeners)
      {
        listener.first->operator()(profile);
      }
  }

  /*!
   * @if jp
   * @class FsmStructureListener ホルダクラス
   * @else
   * @class FsmStructureListener holder class
   * @endif
   */
  FsmStructureListenerHolder::FsmStructureListenerHolder() = default;

  FsmStructureListenerHolder::~FsmStructureListenerHolder()
  {
    std::lock_guard<std::mutex> guard(m_mutex);
    for (auto & listener : m_listeners)
      {
        if (listener.second)
          {
            delete listener.first;
          }
      }
  }

  void FsmStructureListenerHolder::addListener(FsmStructureListener* listener,
                                               bool autoclean)
  {
    std::lock_guard<std::mutex> guard(m_mutex);
    m_listeners.emplace_back(listener, autoclean);
  }

  void
  FsmStructureListenerHolder::removeListener(FsmStructureListener* listener)
  {
    std::lock_guard<std::mutex> guard(m_mutex);
    std::vector<Entry>::iterator it(m_listeners.begin());

    for (; it != m_listeners.end(); ++it)
      {
        if ((*it).first == listener)
          {
            if ((*it).second)
              {
                delete (*it).first;
              }
            m_listeners.erase(it);
            return;
          }
      }
  }

  void FsmStructureListenerHolder::notify(RTC::FsmStructure& structure)
  {
    std::lock_guard<std::mutex> guard(m_mutex);
    for (auto & listener : m_listeners)
      {
        listener.first->operator()(structure);
      }
  }
  /*!
   * @if jp
   *
   * @brief リスナーの追加
   *
   * 指定の種類のPreFsmActionListenerを追加する。
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
  bool FsmActionListeners::addListener(PreFsmActionListenerType type, PreFsmActionListener* listener, bool autoclean)
  {
      if(static_cast<uint8_t>(type) < preaction_.size())
      {
          preaction_[static_cast<uint8_t>(type)].addListener(listener, autoclean);
          return true;
      }
      return false;
  }
  /*!
   * @if jp
   *
   * @brief リスナーの削除
   *
   * 指定の種類のPreFsmActionListenerを削除する。
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
  bool FsmActionListeners::removeListener(PreFsmActionListenerType type, PreFsmActionListener* listener)
  {
      if(static_cast<uint8_t>(type) < preaction_.size())
      {
          preaction_[static_cast<uint8_t>(type)].removeListener(listener);
          return true;
      }
      return false;
  }
  /*!
   * @if jp
   *
   * @brief リスナーの追加
   *
   * 指定の種類のPostFsmActionListenerを追加する。
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
  bool FsmActionListeners::addListener(PostFsmActionListenerType type, PostFsmActionListener* listener, bool autoclean)
  {
      if(static_cast<uint8_t>(type) < postaction_.size())
      {
          postaction_[static_cast<uint8_t>(type)].addListener(listener, autoclean);
          return true;
      }
      return false;
  }
  /*!
   * @if jp
   *
   * @brief リスナーの削除
   *
   * 指定の種類のPostFsmActionListenerを削除する。
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
  bool FsmActionListeners::removeListener(PostFsmActionListenerType type, PostFsmActionListener* listener)
  {
      if(static_cast<uint8_t>(type) < postaction_.size())
      {
          postaction_[static_cast<uint8_t>(type)].removeListener(listener);
          return true;
      }
      return false;
  }
  /*!
   * @if jp
   *
   * @brief リスナーの追加
   *
   * 指定の種類のFsmProfileListenerを追加する。
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
  bool FsmActionListeners::addListener(FsmProfileListenerType type, FsmProfileListener* listener, bool autoclean)
  {
      if(static_cast<uint8_t>(type) < profile_.size())
      {
          profile_[static_cast<uint8_t>(type)].addListener(listener, autoclean);
          return true;
      }
      return false;
  }
  /*!
   * @if jp
   *
   * @brief リスナーの削除
   *
   * 指定の種類のFsmProfileListenerを削除する。
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
  bool FsmActionListeners::removeListener(FsmProfileListenerType type, FsmProfileListener* listener)
  {
      if(static_cast<uint8_t>(type) < profile_.size())
      {
          profile_[static_cast<uint8_t>(type)].removeListener(listener);
          return true;
      }
      return false;
  }
  /*!
   * @if jp
   *
   * @brief リスナーの追加
   *
   * 指定の種類のFsmStructureListenerを追加する。
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
  bool FsmActionListeners::addListener(FsmStructureListenerType type, FsmStructureListener* listener, bool autoclean)
  {
      if(static_cast<uint8_t>(type) < structure_.size())
      {
          structure_[static_cast<uint8_t>(type)].addListener(listener, autoclean);
          return true;
      }
      return false;
  }
  /*!
   * @if jp
   *
   * @brief リスナーの削除
   *
   * 指定の種類のFsmStructureListenerを削除する。
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
  bool FsmActionListeners::removeListener(FsmStructureListenerType type, FsmStructureListener* listener)
  {
      if(static_cast<uint8_t>(type) < structure_.size())
      {
          structure_[static_cast<uint8_t>(type)].removeListener(listener);
          return true;
      }
      return false;
  }

} // namespace RTC


