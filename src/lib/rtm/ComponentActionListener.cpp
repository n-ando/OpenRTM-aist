// -*- C++ -*-
/*!
 * @file ComponentActionListener.cpp
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

#include <rtm/ComponentActionListener.h>

namespace RTC
{

  //============================================================
  /*!
   * @if jp
   * @class PostComponentActionListener クラス
   * @else
   * @class PostComponentActionListener class
   * @endif
   */
  PostComponentActionListener::~PostComponentActionListener() = default;

  /*!
   * @if jp
   * @class PreComponentActionListener クラス
   * @else
   * @class PreComponentActionListener class
   * @endif
   */
  PreComponentActionListener::~PreComponentActionListener() = default;

  /*!
   * @if jp
   * @class PortActionListener クラス
   * @else
   * @class PortActionListener class
   * @endif
   */
  PortActionListener::~PortActionListener() = default;

  /*!
   * @if jp
   * @class ExecutionContextActionListener クラス
   * @else
   * @class ExecutionContextActionListener class
   * @endif
   */
  ExecutionContextActionListener::~ExecutionContextActionListener() = default;





  //============================================================
  /*!
   * @if jp
   * @class PreComponentActionListener ホルダクラス
   * @else
   * @class PreComponentActionListener holder class
   * @endif
   */
  PreComponentActionListenerHolder::PreComponentActionListenerHolder() = default;


  PreComponentActionListenerHolder::~PreComponentActionListenerHolder()
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


  void PreComponentActionListenerHolder::
  addListener(PreComponentActionListener* listener,
              bool autoclean)
  {
    std::lock_guard<std::mutex> guard(m_mutex);
    m_listeners.emplace_back(listener, autoclean);
  }


  void PreComponentActionListenerHolder::
  removeListener(PreComponentActionListener* listener)
  {
    std::lock_guard<std::mutex> guard(m_mutex);
    std::vector<Entry>::iterator it(m_listeners.begin());

    for (; it != m_listeners.end(); ++it)
      {
        if (it->first == listener)
          {
            if (it->second)
              {
                delete it->first;
              }
            m_listeners.erase(it);
            return;
          }
      }

  }


  void PreComponentActionListenerHolder::notify(UniqueId ec_id)
  {
    std::lock_guard<std::mutex> guard(m_mutex);
    for (auto & listener : m_listeners)
      {
        listener.first->operator()(ec_id);
      }
  }

  //============================================================
  /*!
   * @if jp
   * @class PostComponentActionListener ホルダクラス
   * @else
   * @class PostComponentActionListener holder class
   * @endif
   */
  PostComponentActionListenerHolder::PostComponentActionListenerHolder() = default;


  PostComponentActionListenerHolder::~PostComponentActionListenerHolder()
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


  void PostComponentActionListenerHolder::
  addListener(PostComponentActionListener* listener, bool autoclean)
  {
    std::lock_guard<std::mutex> guard(m_mutex);
    m_listeners.emplace_back(listener, autoclean);
  }


  void PostComponentActionListenerHolder::
  removeListener(PostComponentActionListener* listener)
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


  void PostComponentActionListenerHolder::notify(UniqueId ec_id,
                                                 ReturnCode_t ret)
  {
    std::lock_guard<std::mutex> guard(m_mutex);
    for (auto & listener : m_listeners)
      {
        listener.first->operator()(ec_id, ret);
      }
  }


  /*!
   * @if jp
   * @class PortActionListener ホルダクラス
   * @else
   * @class PortActionListener holder class
   * @endif
   */
  PortActionListenerHolder::PortActionListenerHolder() = default;


  PortActionListenerHolder::~PortActionListenerHolder()
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


  void PortActionListenerHolder::addListener(PortActionListener* listener,
                                             bool autoclean)
  {
    std::lock_guard<std::mutex> guard(m_mutex);
    m_listeners.emplace_back(listener, autoclean);
  }


  void PortActionListenerHolder::removeListener(PortActionListener* listener)
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


  void PortActionListenerHolder::notify(const RTC::PortProfile& pprofile)
  {
    std::lock_guard<std::mutex> guard(m_mutex);
    for (auto & listener : m_listeners)
      {
        listener.first->operator()(pprofile);
      }
  }



  /*!
   * @if jp
   * @class ExecutionContextActionListener ホルダクラス
   * @else
   * @class ExecutionContextActionListener holder class
   * @endif
   */
  ExecutionContextActionListenerHolder::ExecutionContextActionListenerHolder() = default;


  ExecutionContextActionListenerHolder::~ExecutionContextActionListenerHolder()
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


  void ExecutionContextActionListenerHolder::
  addListener(ExecutionContextActionListener* listener,
              bool autoclean)
  {
    std::lock_guard<std::mutex> guard(m_mutex);
    m_listeners.emplace_back(listener, autoclean);
  }


  void ExecutionContextActionListenerHolder::
  removeListener(ExecutionContextActionListener* listener)
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


  void ExecutionContextActionListenerHolder::notify(UniqueId ec_id)
  {
    std::lock_guard<std::mutex> guard(m_mutex);
    for (auto & listener : m_listeners)
      {
        listener.first->operator()(ec_id);
      }
  }

  /*!
   * @if jp
   * @class ComponentActionListeners
   * @else
   * @class ComponentActionListeners class
   * @endif
   */

    /*!
     * @if jp
     * @brief コンストラクタ
     * @else
     * @brief Constructor
     * @endif
     */
  ComponentActionListeners::ComponentActionListeners() = default;
    /*!
     * @if jp
     * @brief デストラクタ
     * @else
     * @brief Destructor
     * @endif
     */
  ComponentActionListeners::~ComponentActionListeners() = default;


  /*!
   * @if jp
   *
   * @brief リスナーの追加
   *
   * 指定の種類のPreComponentActionListenerを追加する。
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
  bool ComponentActionListeners::addListener(PreComponentActionListenerType type, PreComponentActionListener* listener, bool autoclean)
  {
      if (static_cast<uint8_t>(type) < preaction_.size())
      {
           preaction_[static_cast<uint8_t>(type)].addListener(listener, autoclean);
           return true;
      }
      return false;
  }

  /*!
   * @if jp
   *
   * @brief リスナーの追加
   *
   * 指定の種類のPostComponentActionListenerを追加する。
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
  bool ComponentActionListeners::addListener(PostComponentActionListenerType type, PostComponentActionListener* listener, bool autoclean)
  {
      if (static_cast<uint8_t>(type) < postaction_.size())
      {
           postaction_[static_cast<uint8_t>(type)].addListener(listener, autoclean);
           return true;
      }
      return false;
  }

  /*!
   * @if jp
   *
   * @brief リスナーの追加
   *
   * 指定の種類のPortActionListenerを追加する。
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
  bool ComponentActionListeners::addListener(PortActionListenerType type, PortActionListener* listener, bool autoclean)
  {
      if (static_cast<uint8_t>(type) < portaction_.size())
      {
           portaction_[static_cast<uint8_t>(type)].addListener(listener, autoclean);
           return true;
      }
      return false;
  }

  /*!
   * @if jp
   *
   * @brief リスナーの追加
   *
   * 指定の種類のExecutionContextActionListenerを追加する。
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
  bool ComponentActionListeners::addListener(ExecutionContextActionListenerType type, ExecutionContextActionListener* listener, bool autoclean)
  {
      if (static_cast<uint8_t>(type) < ecaction_.size())
      {
           ecaction_[static_cast<uint8_t>(type)].addListener(listener, autoclean);
           return true;
      }
      return false;
  }

  /*!
   * @if jp
   *
   * @brief リスナーの削除
   *
   * 指定の種類のPreComponentActionListenerを削除する。
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
  bool ComponentActionListeners::removeListener(PreComponentActionListenerType type, PreComponentActionListener* listener)
  {
      if (static_cast<uint8_t>(type) < preaction_.size())
      {
           preaction_[static_cast<uint8_t>(type)].removeListener(listener);
           return true;
      }
      return false;
  }

  /*!
   * @if jp
   *
   * @brief リスナーの削除
   *
   * 指定の種類のPreComponentActionListenerを削除する。
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
  bool ComponentActionListeners::removeListener(PostComponentActionListenerType type, PostComponentActionListener* listener)
  {
      if (static_cast<uint8_t>(type) < postaction_.size())
      {
           postaction_[static_cast<uint8_t>(type)].removeListener(listener);
           return true;
      }
      return false;
  }

  /*!
   * @if jp
   *
   * @brief リスナーの削除
   *
   * 指定の種類のPortActionListenerを削除する。
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
  bool ComponentActionListeners::removeListener(PortActionListenerType type, PortActionListener* listener)
  {
      if (static_cast<uint8_t>(type) < portaction_.size())
      {
           portaction_[static_cast<uint8_t>(type)].removeListener(listener);
           return true;
      }
      return false;
  }

  /*!
   * @if jp
   *
   * @brief リスナーの削除
   *
   * 指定の種類のExecutionContextActionListenerを削除する。
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
  bool ComponentActionListeners::removeListener(ExecutionContextActionListenerType type, ExecutionContextActionListener* listener)
  {
      if (static_cast<uint8_t>(type) < ecaction_.size())
      {
           ecaction_[static_cast<uint8_t>(type)].removeListener(listener);
           return true;
      }
      return false;
  }
} // namespace RTC

