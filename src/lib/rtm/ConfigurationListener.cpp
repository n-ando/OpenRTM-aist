// -*- C++ -*-
/*!
 * @file ConfigurationListener.cpp
 * @brief Configuration related event listener classes
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

#include <rtm/ConfigurationListener.h>

namespace RTC
{

  //============================================================
  /*!
   * @if jp
   * @class ConfigurationParamListener クラス
   * @else
   * @class ConfigurationParamListener class
   * @endif
   */
  ConfigurationParamListener::~ConfigurationParamListener() = default;

  /*!
   * @if jp
   * @class ConfigurationSetNameListener クラス
   * @else
   * @class ConfigurationSetNameListener class
   * @endif
   */
  ConfigurationSetNameListener::~ConfigurationSetNameListener() = default;

  /*!
   * @if jp
   * @class ConfigurationSetListener クラス
   * @else
   * @class ConfigurationSetListener class
   * @endif
   */
  ConfigurationSetListener::~ConfigurationSetListener() = default;


  //============================================================
  /*!
   * @if jp
   * @class ConfigurationParamListener ホルダクラス
   * @else
   * @class ConfigurationParamListener holder class
   * @endif
   */
  ConfigurationParamListenerHolder::ConfigurationParamListenerHolder() = default;


  ConfigurationParamListenerHolder::~ConfigurationParamListenerHolder()
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


  void ConfigurationParamListenerHolder::
  addListener(ConfigurationParamListener* listener,
              bool autoclean)
  {
    std::lock_guard<std::mutex> guard(m_mutex);
    m_listeners.emplace_back(listener, autoclean);
  }


  void ConfigurationParamListenerHolder::
  removeListener(ConfigurationParamListener* listener)
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


  void ConfigurationParamListenerHolder::notify(const char* config_set_name,
                                                const char* config_param_name)
  {
    std::lock_guard<std::mutex> guard(m_mutex);
    for (auto & listener : m_listeners)
      {
        listener.first->operator()(config_set_name, config_param_name);
      }
  }


  //============================================================
  /*!
   * @if jp
   * @class ConfigurationSetListener ホルダクラス
   * @else
   * @class ConfigurationSetListener holder class
   * @endif
   */
  ConfigurationSetListenerHolder::ConfigurationSetListenerHolder() = default;


  ConfigurationSetListenerHolder::~ConfigurationSetListenerHolder()
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


  void ConfigurationSetListenerHolder::
  addListener(ConfigurationSetListener* listener,
              bool autoclean)
  {
    std::lock_guard<std::mutex> guard(m_mutex);
    m_listeners.emplace_back(listener, autoclean);
  }


  void ConfigurationSetListenerHolder::
  removeListener(ConfigurationSetListener* listener)
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


  void ConfigurationSetListenerHolder::
  notify(const coil::Properties& config_set)
  {
    std::lock_guard<std::mutex> guard(m_mutex);
    for (auto & listener : m_listeners)
      {
        listener.first->operator()(config_set);
      }
  }

  //============================================================
  /*!
   * @if jp
   * @class ConfigurationSetNameListener ホルダクラス
   * @else
   * @class ConfigurationSetNameListener holder class
   * @endif
   */
  ConfigurationSetNameListenerHolder::ConfigurationSetNameListenerHolder() = default;


  ConfigurationSetNameListenerHolder::~ConfigurationSetNameListenerHolder()
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


  void ConfigurationSetNameListenerHolder::
  addListener(ConfigurationSetNameListener* listener, bool autoclean)
  {
    std::lock_guard<std::mutex> guard(m_mutex);
    m_listeners.emplace_back(listener, autoclean);
  }


  void ConfigurationSetNameListenerHolder::
  removeListener(ConfigurationSetNameListener* listener)
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


  void ConfigurationSetNameListenerHolder::notify(const char* config_set_name)
  {
    std::lock_guard<std::mutex> guard(m_mutex);
    for (auto & listener : m_listeners)
      {
        listener.first->operator()(config_set_name);
      }
  }

  /*!
   * @if jp
   * @brief デストラクタ
   * @else
   * @brief Destructor
   * @endif
   */
  ConfigurationListeners::~ConfigurationListeners() = default;

  /*!
   * @if jp
   *
   * @brief リスナーの追加
   *
   * 指定の種類のConfigurationParamListenerを追加する。
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
  bool ConfigurationListeners::addListener(ConfigurationParamListenerType type, ConfigurationParamListener* listener, bool autoclean)
  {
      if(static_cast<uint8_t>(type) < configparam_.size())
      {
          configparam_[static_cast<uint8_t>(type)].addListener(listener, autoclean);
          return true;
      }
      return false;
  }
  /*!
   * @if jp
   *
   * @brief リスナーの削除
   *
   * 指定の種類のConfigurationParamListenerを削除する。
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
  bool ConfigurationListeners::removeListener(ConfigurationParamListenerType type, ConfigurationParamListener* listener)
  {
      if(static_cast<uint8_t>(type) < configparam_.size())
      {
          configparam_[static_cast<uint8_t>(type)].removeListener(listener);
          return true;
      }
      return false;
  }
  /*!
   * @if jp
   *
   * @brief リスナーの追加
   *
   * 指定の種類のConfigurationSetListenerを追加する。
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
  bool ConfigurationListeners::addListener(ConfigurationSetListenerType type, ConfigurationSetListener* listener, bool autoclean)
  {
      if(static_cast<uint8_t>(type) < configset_.size())
      {
          configset_[static_cast<uint8_t>(type)].addListener(listener, autoclean);
          return true;
      }
      return false;
  }
  /*!
   * @if jp
   *
   * @brief リスナーの削除
   *
   * 指定の種類のConfigurationSetListenerを削除する。
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
  bool ConfigurationListeners::removeListener(ConfigurationSetListenerType type, ConfigurationSetListener* listener)
  {
      if(static_cast<uint8_t>(type) < configset_.size())
      {
          configset_[static_cast<uint8_t>(type)].removeListener(listener);
          return true;
      }
      return false;
  }
  /*!
   * @if jp
   *
   * @brief リスナーの追加
   *
   * 指定の種類のConfigurationSetNameListenerを追加する。
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
  bool ConfigurationListeners::addListener(ConfigurationSetNameListenerType type, ConfigurationSetNameListener* listener, bool autoclean)
  {
      if(static_cast<uint8_t>(type) < configsetname_.size())
      {
          configsetname_[static_cast<uint8_t>(type)].addListener(listener, autoclean);
          return true;
      }
      return false;
  }
  /*!
   * @if jp
   *
   * @brief リスナーの削除
   *
   * 指定の種類のConfigurationSetNameListenerを削除する。
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
  bool ConfigurationListeners::removeListener(ConfigurationSetNameListenerType type, ConfigurationSetNameListener* listener)
  {
      if(static_cast<uint8_t>(type) < configsetname_.size())
      {
          configsetname_[static_cast<uint8_t>(type)].removeListener(listener);
          return true;
      }
      return false;
  }


} // namespace RTC


