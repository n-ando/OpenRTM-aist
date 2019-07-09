// -*- C++ -*-
/*!
 * @file PortConnectListener.cpp
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

#include <rtm/PortConnectListener.h>

namespace RTC
{

  //============================================================
  /*!
   * @if jp
   * @brief PortConnectListenerType を文字列に変換
   * @else
   * @brief Convert PortConnectListenerType into the string.
   * @endif
   */
  const char*
  PortConnectListener::toString(PortConnectListenerType type)
  {
    static const char* const typeString[] =
      {
        "ON_NOTIFY_CONNECT",
        "ON_NOTIFY_DISCONNECT",
        "ON_UNSUBSCRIBE_INTERFACES",
        ""
      };
    type = type < PORT_CONNECT_LISTENER_NUM ? type : PORT_CONNECT_LISTENER_NUM;
    return typeString[type];
  }

  /*!
   * @if jp
   * @class PortConnectListener クラス
   * @else
   * @class PortConnectListener class
   * @endif
   */
  PortConnectListener::~PortConnectListener() {}

  /*!
   * @if jp
   * @brief PortConnectRetListenerType を文字列に変換
   * @else
   * @brief Convert PortConnectRetListenerType into the string.
   * @endif
   */
  const char*
  PortConnectRetListener::toString(PortConnectRetListenerType type)
  {
    static const char* const typeString[] =
      {
        "ON_PUBLISH_INTERFACES",
        "ON_CONNECT_NEXTPORT",
        "ON_SUBSCRIBE_INTERFACES",
        "ON_CONNECTED",
        "ON_DISCONNECT_NEXT",
        "ON_DISCONNECTED",
        ""
      };
    type = type < PORT_CONNECT_RET_LISTENER_NUM ?
      type : PORT_CONNECT_RET_LISTENER_NUM;
      return typeString[type];
  }

  /*!
   * @if jp
   * @class PortConnectRetListener クラス
   * @else
   * @class PortConnectRetListener class
   * @endif
   */
  PortConnectRetListener::~PortConnectRetListener() {}

  //============================================================
  /*!
   * @if jp
   * @class PortConnectListener ホルダクラス
   * @else
   * @class PortConnectListener holder class
   * @endif
   */
  PortConnectListenerHolder::PortConnectListenerHolder()
  {
  }


  PortConnectListenerHolder::~PortConnectListenerHolder()
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


  void PortConnectListenerHolder::addListener(PortConnectListener* listener,
                                              bool autoclean)
  {
    std::lock_guard<std::mutex> guard(m_mutex);
    m_listeners.emplace_back(listener, autoclean);
  }


  void PortConnectListenerHolder::removeListener(PortConnectListener* listener)
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


  void PortConnectListenerHolder::notify(const char* portname,
                                         RTC::ConnectorProfile& profile)
  {
    std::lock_guard<std::mutex> guard(m_mutex);
    for (auto & listener : m_listeners)
      {
        listener.first->operator()(portname, profile);
      }
  }

  //============================================================
  /*!
   * @if jp
   * @class PortConnectRetListener ホルダクラス
   * @else
   * @class PortConnectRetListener holder class
   * @endif
   */
  PortConnectRetListenerHolder::PortConnectRetListenerHolder()
  {
  }


  PortConnectRetListenerHolder::~PortConnectRetListenerHolder()
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


  void PortConnectRetListenerHolder::
  addListener(PortConnectRetListener* listener, bool autoclean)
  {
    std::lock_guard<std::mutex> guard(m_mutex);
    m_listeners.emplace_back(listener, autoclean);
  }


  void PortConnectRetListenerHolder::
  removeListener(PortConnectRetListener* listener)
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


  void PortConnectRetListenerHolder::notify(const char* portname,
                                            RTC::ConnectorProfile& profile,
                                            ReturnCode_t ret)
  {
    std::lock_guard<std::mutex> guard(m_mutex);
    for (auto & listener : m_listeners)
      {
        listener.first->operator()(portname, profile, ret);
      }
  }

  /*!
   * @if jp
   * @class PortConnectListeners クラス
   * @else
   * @class PortConnectListeners  class
   * @endif
   */
  PortConnectListeners::PortConnectListeners()
  {
  }

  PortConnectListeners::~PortConnectListeners()
  {
  }

} // namespace RTC

