// -*- C++ -*-
/*!
 * @file ConfigAdmin.cpp
 * @brief Configuration Administration classes
 * @date $Date: 2007-12-31 03:08:02 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2007-2008
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
#include <algorithm>
#include <assert.h>
#include <string.h>

namespace RTC
{
  /*!
   * @if jp
   * @brief コンストラクタ
   * @else
   * @endif
   */
  ConfigAdmin::ConfigAdmin(coil::Properties& configsets)
    : m_configsets(configsets), m_activeId("default"),
      m_active(true), m_changed(false),
      m_updateCb(0), m_updateParamCb(0),
      m_setConfigSetCb(0), m_addConfigSetCb(0),
      m_removeConfigSetCb(0), m_activateSetCb(0)
  {
  }
  
  /*!
   * @if jp
   * @brief 仮想デストラクタ
   * @else
   * @brief Virtual destructor
   * @endif
   */
  ConfigAdmin::~ConfigAdmin(void)
  {
    for (int i(0), len(m_params.size()); i < len; ++i)
      {
	if (m_params[i] != NULL) { delete m_params[i]; }
      }
    m_params.clear();
    setOnUpdate(0);
    setOnUpdateParam(0);
    setOnSetConfigurationSet(0);
    setOnAddConfigurationSet(0);
    setOnRemoveConfigurationSet(0);
    setOnActivateSet(0);
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
    if (m_configsets.hasKey(config_set) == NULL) return;
    coil::Properties& prop(*(m_configsets.getNode(config_set)));
    
    for (int i(0), len(m_params.size()); i < len; ++i)
      {
	if (prop.hasKey(m_params[i]->name) != NULL)
	  {
	    m_params[i]->update(prop[m_params[i]->name].c_str());
            onUpdate(config_set);
	  }
      }
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
  void ConfigAdmin::update(void)
  {
    if (m_changed && m_active)
      {
	update(m_activeId.c_str());
	m_changed = false;
      }
    return;
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
    if ((config_set == 0) || (config_param == 0)) return;
    std::string key(config_set);
    key += "."; key += config_param;
    
    std::vector<ConfigBase*>::iterator it;
    it = std::find_if(m_params.begin(), m_params.end(),
		      find_conf(config_param));
    if (it != m_params.end())
      {
	(*it)->update(m_configsets[key].c_str());
        onUpdateParam(config_set, config_param);
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
    if (it != m_params.end())
      {
	return true;
      }
    return false;
  }
  
  //  const std::vector<Properties*>*
  //  ConfigAdmin::getConfigurationParameterValues()
  //  {
  //    return new std::vector<Properties*>();
  //  }
  //
  //
  //  const Properties*
  //  ConfigAdmin::getConfigurationParameterValue(const char* name)
  //  {
  //    return NULL;
  //  }
  //
  //
  //  bool ConfigAdmin::setConfigurationParameter(const char* name,
  //					      const char* value)
  //  {
  //    return true;
  //  }
  
  /*!
   * @if jp
   * @brief 全コンフィギュレーションセットの取得
   * @else
   * @brief Get all configuration sets
   * @endif
   */
  const std::vector<coil::Properties*>& ConfigAdmin::getConfigurationSets(void)
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
  const coil::Properties& ConfigAdmin::getConfigurationSet(const char* config_id)
  {
    coil::Properties* p(m_configsets.getNode(config_id));
    if (p == NULL) return m_emptyconf;
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
    if (config_set.getName() == '\0') return false;
    
    coil::Properties* p(m_configsets.getNode(config_set.getName()));
    assert(p != 0);
    *p << config_set;
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
  const coil::Properties& ConfigAdmin::getActiveConfigurationSet(void)
  {
    coil::Properties* p(m_configsets.getNode(m_activeId));
    if (p == NULL) return m_emptyconf;
    return *p;
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
    if (config_set.getName() == '\0') return false;
    if (m_configsets.hasKey(config_set.getName())) return false;
    
    std::string node(config_set.getName());
    
    // Create node
    m_configsets.createNode(node.c_str());
    
    coil::Properties* p(m_configsets.getNode(node.c_str()));
    assert(p != 0);
    *p << config_set;
    m_newConfig.push_back(node);
    
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
    //    if (strcmp(config_id, "default") == 0) return false;
    
    std::vector<std::string>::iterator it;
    it = std::find(m_newConfig.begin(), m_newConfig.end(), config_id);
    if (it == m_newConfig.end()) return false;
    
    coil::Properties* p(m_configsets.getNode(config_id));
    if (p != NULL) delete p;
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
    if (config_id == NULL) return false;
    if (!m_configsets.hasKey(config_id)) return false;
    m_activeId = config_id;
    m_active = true;
    m_changed = true;
    onActivateSet(config_id);
    return true;
  }

  void ConfigAdmin::setOnUpdate(OnUpdateCallback* cb)
  {
    if (m_updateCb != 0) delete m_updateCb;
    m_updateCb = cb;
  }

  void ConfigAdmin::setOnUpdateParam(OnUpdateParamCallback* cb)
  {
    if (m_updateParamCb != 0) delete m_updateParamCb;
    m_updateParamCb = cb;
  }

  void ConfigAdmin::setOnSetConfigurationSet(OnSetConfigurationSetCallback* cb)
  {
    if (m_setConfigSetCb != 0) delete m_setConfigSetCb;
    m_setConfigSetCb = cb;
  }

  void ConfigAdmin::setOnAddConfigurationSet(OnAddConfigurationAddCallback* cb)
  {
    if (m_addConfigSetCb != 0) delete m_addConfigSetCb;
    m_addConfigSetCb = cb;
  }

  void ConfigAdmin::setOnRemoveConfigurationSet(OnRemoveConfigurationSetCallback* cb)
  {
    if (m_removeConfigSetCb != 0) delete m_removeConfigSetCb;
    m_removeConfigSetCb = cb;
  }

  void ConfigAdmin::setOnActivateSet(OnActivateSetCallback* cb)
  {
    if (m_activateSetCb != 0) delete m_activateSetCb;
    m_activateSetCb = cb;
  }

  void ConfigAdmin::onUpdate(const char* config_set)
  {
    if (m_updateCb != 0)
      (*m_updateCb)(config_set);
  }
  void ConfigAdmin::onUpdateParam(const char* config_set, const char* config_param)
  {
    if (m_updateParamCb != 0)
      (*m_updateParamCb)(config_set, config_param);
  }
  void ConfigAdmin::onSetConfigurationSet(const coil::Properties& config_set)
  {
    if (m_setConfigSetCb != 0)
      (*m_setConfigSetCb)(config_set);
  }
  void ConfigAdmin::onAddConfigurationSet(const coil::Properties& config_set)
  {
    if (m_addConfigSetCb != 0)
      (*m_addConfigSetCb)(config_set);
  }
  void ConfigAdmin::onRemoveConfigurationSet(const char* config_id)
  {
    if (m_removeConfigSetCb != 0)
      (*m_removeConfigSetCb)(config_id);
  }
  void ConfigAdmin::onActivateSet(const char* config_id)
  {
    if (m_activateSetCb != 0)
      (*m_activateSetCb)(config_id);
  }
  

}; // namespace RTC
