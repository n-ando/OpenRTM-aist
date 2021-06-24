// -*- C++ -*-
/*!
 * @file ConfigAdmin.cpp
 * @brief Configuration Administration classes
 * @date $Date: 2007-12-31 03:08:02 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2007-2011
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id$
 *
 */

#include <rtm/ConfigAdmin.h>

#include <cassert>
#include <cstring>
#include <algorithm>

namespace RTC
{
  /*!
   * @if jp
   * @brief コールバックのセット
   * @else
   * @brief Setting callback
   * @endif
   */
  void ConfigBase::setCallback(ConfigAdmin* cadmin, CallbackFunc cbf)
  {
    m_admin = cadmin;
    m_callback = cbf;
  }

  /*!
   * @if jp
   * @brief 変数変更を知らせるオブザーバ関数
   * @else
   * @brief Observer function to notify variable changed
   * @endif
   */
  void ConfigBase::notifyUpdate(const char* key, const char* val)
  {
    if (m_admin == nullptr || m_callback == nullptr) return;
    (m_admin->*m_callback)(key, val);
  }

  /*!
   * @if jp
   * @brief コンストラクタ
   * @else
   * @endif
   */
  ConfigAdmin::ConfigAdmin(coil::Properties& configsets)
    : m_configsets(configsets), m_activeId("default"),
      m_active(true), m_changed(false)
  {
      m_configsets.createNode("default");
  }

  /*!
   * @if jp
   * @brief 仮想デストラクタ
   * @else
   * @brief Virtual destructor
   * @endif
   */
  ConfigAdmin::~ConfigAdmin()
  {
    for (auto & param : m_params)
      {
        delete param; 
      }
    m_params.clear();
  }

  /*!
   * @if jp
   * @brief コンフィギュレーションパラメータの解除
   * @else
   * @brief Unbinding configuration parameters
   * @endif
   */
  bool ConfigAdmin::unbindParameter(const char* param_name)
  {
    std::vector<ConfigBase*>::iterator it;
    it = std::find_if(m_params.begin(), m_params.end(),
                      find_conf(param_name));
    if (it == m_params.end())
      {
        return false;
      }
    m_params.erase(it);

    // configsets
    const std::vector<coil::Properties*>& leaf(m_configsets.getLeaf());


    for (auto prop : leaf)
      {
        if (prop->hasKey(param_name) != nullptr)
          {
            coil::Properties* p(prop->removeNode(param_name));
            delete p;
          }
      }

    return true;
  }


  /*!
   * @if jp
   * @brief コンフィギュレーションパラメータの更新
   *        (アクティブコンフィギュレーションセット)
   * @else
   * @brief Update the values of configuration parameters
   *        (Active configuration set)
   * @endif
   */
  void ConfigAdmin::update()
  {
    m_changedParam.clear();
    if (m_changed && m_active)
      {
        update(m_activeId.c_str());
        m_changed = false;
      }
    return;
  }


  /*!
   * @if jp
   * @brief コンフィギュレーションパラメータの更新(ID指定)
   * @else
   * @brief Update configuration parameter (By ID)
   * @endif
   */
  void ConfigAdmin::update(const char* config_set)
  {
    if (m_configsets.hasKey(config_set) == nullptr) { return; }
    // clear changed parameter list
    m_changedParam.clear();
    coil::Properties& prop(m_configsets.getNode(config_set));

    for (auto & param : m_params)
      {
        if (prop.hasKey(param->name) != nullptr)
          {
            // m_changedParam is updated here
            param->update(prop[param->name].c_str());
          }
      }
    onUpdate(config_set);
  }


  /*!
   * @if jp
   * @brief コンフィギュレーションパラメータの更新(名称指定)
   * @else
   * @brief Update the values of configuration parameters (By name)
   * @endif
   */
  void ConfigAdmin::update(const char* config_set, const char* config_param)
  {
    m_changedParam.clear();
    if ((config_set == nullptr) || (config_param == nullptr)) { return; }

    std::string key(config_set);
    key += "."; key += config_param;

    std::vector<ConfigBase*>::iterator it;
    it = std::find_if(m_params.begin(), m_params.end(),
                      find_conf(config_param));
    if (it != m_params.end())
      {
        (*it)->update(m_configsets[key].c_str());
        return;
      }
  }


  /*!
   * @if jp
   * @brief コンフィギュレーションパラメータの存在確認
   * @else
   * @brief Check the existence of configuration parameters
   * @endif
   */
  bool ConfigAdmin::isExist(const char* param_name)
  {
    std::vector<ConfigBase*>::iterator it;
    it = std::find_if(m_params.begin(), m_params.end(),
                      find_conf(param_name));
    return it != m_params.end();
  }


  /*!
   * @if jp
   * @brief 全コンフィギュレーションセットの取得
   * @else
   * @brief Get all configuration sets
   * @endif
   */
  const std::vector<coil::Properties*>& ConfigAdmin::getConfigurationSets()
  {
    return m_configsets.getLeaf();
  }

  /*!
   * @if jp
   * @brief 指定したIDのコンフィギュレーションセットの取得
   * @else
   * @brief Get a configuration set by specified ID
   * @endif
   */
  const coil::Properties&
  ConfigAdmin::getConfigurationSet(const char* config_id)
  {
    coil::Properties* p(m_configsets.findNode(config_id));
    if (p == nullptr) { return m_emptyconf; }
    return *p;
  }

  /*!
   * @if jp
   * @brief 指定したプロパティのコンフィギュレーションセットへの追加
   * @else
   * @brief Add to the configuration set from specified property
   * @endif
   */
  bool
  ConfigAdmin::setConfigurationSetValues(const coil::Properties& config_set)
  {
    std::string node(config_set.getName());
    if (node.empty()) { return false; }

    coil::Properties& p(m_configsets.getNode(node));

    p << config_set;
    m_changed = true;
    m_active = false;
    onSetConfigurationSet(config_set);
    return true;
  }

  /*!
   * @if jp
   * @brief アクティブ・コンフィギュレーションセットを取得
   * @else
   * @brief Get the active configuration set
   * @endif
   */
  const coil::Properties& ConfigAdmin::getActiveConfigurationSet()
  {
    coil::Properties& p(m_configsets.getNode(m_activeId));

    return p;
  }

  /*!
   * @if jp
   * @brief コンフィギュレーションセットに設定値を追加
   * @else
   * @brief Add the configuration value to the configuration set
   * @endif
   */
  bool ConfigAdmin::addConfigurationSet(const coil::Properties& config_set)
  {
    std::string node(config_set.getName());
    if (node.empty()) { return false; }
    if (m_configsets.hasKey(node.c_str()) != nullptr) { return false; }

    coil::Properties& p(m_configsets.getNode(node));
    p << config_set;
    m_newConfig.emplace_back(std::move(node));

    m_changed = true;
    m_active = false;
    onAddConfigurationSet(config_set);
    return true;
  }

  /*!
   * @if jp
   * @brief コンフィギュレーションセットの削除
   * @else
   * @brief Remove the configuration set
   * @endif
   */
  bool ConfigAdmin::removeConfigurationSet(const char* config_id)
  {
    if (strcmp(config_id, "default") == 0) return false;
    if (m_activeId == config_id) return false;

    // removeable config-set is only config-sets newly added
    std::vector<std::string>::iterator it;
    it = std::find(m_newConfig.begin(), m_newConfig.end(), config_id);
    if (it == m_newConfig.end()) { return false; }

    coil::Properties* p(m_configsets.removeNode(config_id));
    delete p; 
    m_newConfig.erase(it);

    m_changed = true;
    m_active = false;
    onRemoveConfigurationSet(config_id);
    return true;
  }

  /*!
   * @if jp
   * @brief コンフィギュレーションセットのアクティブ化
   * @else
   * @brief Activate the configuration set
   * @endif
   */
  bool ConfigAdmin::activateConfigurationSet(const char* config_id)
  {
    if (config_id == nullptr) { return false; }
    // '_<conf_name>' is special configuration set name
    if (config_id[0] == '_') { return false; }

    if (m_configsets.hasKey(config_id) == nullptr) { return false; }
    m_activeId = config_id;
    m_active = true;
    m_changed = true;
    onActivateSet(config_id);
    return true;
  }

  //------------------------------------------------------------
  // obsolete functions
  //
  void ConfigAdmin::setOnUpdate(OnUpdateCallback* cb)
  {
    std::cerr << "setOnUpdate function is obsolete." << std::endl;
    std::cerr << "Use addConfigurationSetNameListener instead." << std::endl;
    m_listeners.addListener(ConfigurationSetNameListenerType::ON_UPDATE_CONFIG_SET, cb, false);
  }

  void ConfigAdmin::setOnUpdateParam(OnUpdateParamCallback* cb)
  {
    std::cerr << "setOnUpdateParam function is obsolete." << std::endl;
    std::cerr << "Use addConfigurationParamListener instead." << std::endl;
    m_listeners.addListener(ConfigurationParamListenerType::ON_UPDATE_CONFIG_PARAM, cb, false);
  }

  void ConfigAdmin::setOnSetConfigurationSet(OnSetConfigurationSetCallback* cb)
  {
    std::cerr << "setOnSetConfigurationSet function is obsolete." << std::endl;
    std::cerr << "Use addConfigurationSetListener instead." << std::endl;
    m_listeners.addListener(ConfigurationSetListenerType::ON_SET_CONFIG_SET, cb, false);
  }

  void ConfigAdmin::setOnAddConfigurationSet(OnAddConfigurationAddCallback* cb)
  {
    std::cerr << "setOnAddConfigurationSet function is obsolete." << std::endl;
    std::cerr << "Use addConfigurationSetListener instead." << std::endl;
    m_listeners.addListener(ConfigurationSetListenerType::ON_ADD_CONFIG_SET, cb, false);
  }

  void
  ConfigAdmin::setOnRemoveConfigurationSet(OnRemoveConfigurationSetCallback* cb)
  {
    std::cerr <<
            "setOnRemoveConfigurationSet function is obsolete." <<std::endl;
    std::cerr << "Use addConfigurationSetNameListener instead." << std::endl;
    m_listeners.addListener(ConfigurationSetNameListenerType::ON_REMOVE_CONFIG_SET, cb, false);
  }

  void ConfigAdmin::setOnActivateSet(OnActivateSetCallback* cb)
  {
    std::cerr << "setOnActivateSet function is obsolete." << std::endl;
    std::cerr << "Use addConfigurationSetNameListener instead." << std::endl;
    m_listeners.addListener(ConfigurationSetNameListenerType::ON_ACTIVATE_CONFIG_SET, cb, false);
  }
  //
  // end of obsolete functions
  //------------------------------------------------------------

  /*!
   * @if jp
   * @brief ConfigurationParamListener を追加する
   * @else
   * @brief Adding ConfigurationParamListener
   * @endif
   */
  void ConfigAdmin::
  addConfigurationParamListener(ConfigurationParamListenerType type,
                                ConfigurationParamListener* listener,
                                bool autoclean)
  {
    m_listeners.addListener(type, listener, autoclean);
  }

  /*!
   * @if jp
   * @brief ConfigurationParamListener を削除する
   * @else
   * @brief Removing ConfigurationParamListener
   * @endif
   */
  void ConfigAdmin::
  removeConfigurationParamListener(ConfigurationParamListenerType type,
                                   ConfigurationParamListener* listener)
  {
    m_listeners.removeListener(type, listener);
  }

  /*!
   * @if jp
   * @brief ConfigurationSetListener を追加する
   * @else
   * @brief Adding ConfigurationSetListener
   * @endif
   */
  void ConfigAdmin::
  addConfigurationSetListener(ConfigurationSetListenerType type,
                              ConfigurationSetListener* listener,
                              bool autoclean)
  {
    m_listeners.addListener(type, listener, autoclean);
  }

  /*!
   * @if jp
   * @brief ConfigurationSetListener を削除する
   * @else
   * @brief Removing ConfigurationSetListener
   * @endif
   */
  void ConfigAdmin::
  removeConfigurationSetListener(ConfigurationSetListenerType type,
                                 ConfigurationSetListener* listener)
  {
    m_listeners.removeListener(type, listener);
  }

  /*!
   * @if jp
   * @brief ConfigurationSetNameListener を追加する
   * @else
   * @brief Adding ConfigurationSetNameListener
   * @endif
   */
  void ConfigAdmin::
  addConfigurationSetNameListener(ConfigurationSetNameListenerType type,
                                  ConfigurationSetNameListener* listener,
                                  bool autoclean)
  {
    m_listeners.addListener(type, listener, autoclean);
  }

  /*!
   * @if jp
   * @brief ConfigurationSetNameListener を削除する
   * @else
   * @brief Removing ConfigurationSetNameListener
   * @endif
   */
  void ConfigAdmin::
  removeConfigurationSetNameListener(ConfigurationSetNameListenerType type,
                                     ConfigurationSetNameListener* listener)
  {
    m_listeners.removeListener(type, listener);
  }

  //------------------------------------------------------------
  // protected functions
  /*!
   * @if jp
   * @brief コンフィギュレーションパラメータの更新(ID指定)時にコールされる
   * @else
   * @brief When the configuration parameter is updated, it is called.
   * @endif
   */
  void ConfigAdmin::onUpdate(const char* config_set)
  {
    m_listeners.notify(ConfigurationSetNameListenerType::ON_UPDATE_CONFIG_SET, config_set);
  }

  /*!
   * @if jp
   * @brief コンフィギュレーションパラメータの更新(名称指定)時にコールされる
   * @else
   * @brief When the configuration parameter is updated, it is called.
   * @endif
   */
  void
  ConfigAdmin::onUpdateParam(const char* config_param, const char* config_value)
  {
    m_changedParam.emplace_back(config_param);
    m_listeners.notify(ConfigurationParamListenerType::ON_UPDATE_CONFIG_PARAM, config_param,
                                                            config_value);
  }

  /*!
   * @if jp
   * @brief コンフィギュレーションセットへの追加時にコールされる
   * @else
   * @brief Called when the property is added to the configuration set
   * @endif
   */
  void ConfigAdmin::onSetConfigurationSet(const coil::Properties& config_set)
  {
    m_listeners.notify(ConfigurationSetListenerType::ON_SET_CONFIG_SET, config_set);
  }

  /*!
   * @if jp
   * @brief 設定値が追加されたときにコールされる。
   * @else
   * @brief Called when a set value is added to the configuration set
   * @endif
   */
  void ConfigAdmin::onAddConfigurationSet(const coil::Properties& config_set)
  {
    m_listeners.notify(ConfigurationSetListenerType::ON_ADD_CONFIG_SET, config_set);
  }

  /*!
   * @if jp
   * @brief セットが削除されてるときにコールされる。
   * @else
   * @brief Called when the configuration set has been deleted
   * @endif
   */
  void ConfigAdmin::onRemoveConfigurationSet(const char* config_id)
  {
    m_listeners.notify(ConfigurationSetNameListenerType::ON_REMOVE_CONFIG_SET, config_id);
  }

  /*!
   * @if jp
   * @brief セットがアクティブ化されたときにコールされる。
   * @else
   * @brief Called when the configuration set is made active
   * @endif
   */
  void ConfigAdmin::onActivateSet(const char* config_id)
  {
    m_listeners.notify(ConfigurationSetNameListenerType::ON_ACTIVATE_CONFIG_SET, config_id);
  }


} // namespace RTC
