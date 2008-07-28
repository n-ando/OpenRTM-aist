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

namespace RTC
{
  /*!
   * @if jp
   * @brief コンストラクタ
   * @else
   * @endif
   */
  ConfigAdmin::ConfigAdmin(RTC::Properties& configsets)
    : m_configsets(configsets), m_activeId("default"),
      m_active(true), m_changed(false)
  {
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
    for (int i(0), len(m_params.size()); i < len; ++i)
      {
	if (m_params[i] != NULL) delete m_params[i];
      }
    m_params.clear();
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
    RTC::Properties& prop(*(m_configsets.getNode(config_set)));
    
    for (int i(0), len(m_params.size()); i < len; ++i)
      {
	if (prop.hasKey(m_params[i]->name) != NULL)
	  {
	    m_params[i]->update(prop[m_params[i]->name].c_str());
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
  void ConfigAdmin::update()
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
  const std::vector<Properties*>& ConfigAdmin::getConfigurationSets()
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
  const Properties& ConfigAdmin::getConfigurationSet(const char* config_id)
  {
    Properties* p(m_configsets.getNode(config_id));
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
  ConfigAdmin::setConfigurationSetValues(const char* config_id,
					 const RTC::Properties& config_set)
  {
    if (strcmp(config_set.getName(), config_id) != 0) return false;
    if (!m_configsets.hasKey(config_id))              return false;
    
    Properties* p(m_configsets.getNode(config_id));
    assert(p != NULL);
    *p << config_set;
    
    m_changed = true;
    m_active = false;
    return true;
  }
  
  /*!
   * @if jp
   * @brief アクティブ・コンフィギュレーションセットを取得
   * @else
   * @brief Get the active configuration set
   * @endif
   */
  const Properties& ConfigAdmin::getActiveConfigurationSet()
  {
    Properties* p(m_configsets.getNode(m_activeId));
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
  bool ConfigAdmin::addConfigurationSet(const Properties& configset)
  {
    if (m_configsets.hasKey(configset.getName())) return false;
    
    std::string node(configset.getName());
    
    // Create node
    m_configsets.createNode(node.c_str());
    
    Properties* p(m_configsets.getNode(node.c_str()));
    assert(p != NULL);
    *p << configset;
    m_newConfig.push_back(node);
    
    m_changed = true;
    m_active = false;
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
    
    Properties* p(m_configsets.getNode(config_id));
    if (p != NULL) delete p;
    m_newConfig.erase(it);
    
    m_changed = true;
    m_active = false;
    
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
    return true;
  }
}; // namespace RTC
