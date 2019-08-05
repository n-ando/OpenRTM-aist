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

} // namespace RTC


