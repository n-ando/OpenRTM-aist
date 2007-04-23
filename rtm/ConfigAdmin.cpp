// -*- C++ -*-
/*!
 * @file ConfigAdmin.cpp
 * @brief Configuration Administration classes
 * @date $Date: 2007-04-23 11:20:30 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2007
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: ConfigAdmin.cpp,v 1.2 2007-04-23 11:20:30 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.1  2007/04/23 04:51:16  n-ando
 * COnfiguration Admin class.
 *
 */


#include <rtm/ConfigAdmin.h>
#include <algorithm>
namespace RTC
{
  ConfigAdmin::ConfigAdmin(RTC::Properties& configsets)
    : m_configsets(configsets), m_activeId("default"),
      m_active(true), m_changed(false)
  {
  }
  
  
  ConfigAdmin::~ConfigAdmin()
  {
    for (int i(0), len(m_params.size()); i < len; ++i)
      {
	if (m_params[i] != NULL) delete m_params[i];
      }
    m_params.clear();
  }
  

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


  void ConfigAdmin::update()
  {
    if (m_changed && m_active)
      {
	update(m_activeId.c_str());
	m_changed = false;
      }
    return;
  }
  
  
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

  

  const std::vector<Properties*>& ConfigAdmin::getConfigurationSets()
  {
    return m_configsets.getLeaf();
  }


  const Properties& ConfigAdmin::getConfigurationSet(const char* config_id)
  {
    return *(m_configsets.getNode(config_id));
  }


  bool
  ConfigAdmin::setConfigurationSetValues(const char* config_id,
					 const RTC::Properties& configuration_set)
  {
    if (strcmp(configuration_set.getName(), config_id) != 0)
      {
	return false;
      } 
    if (!m_configsets.hasKey(config_id)) return false;
    *(m_configsets.getNode(config_id)) << configuration_set;
    
    m_changed = true;
    m_active = false;
    return true;
  }
  

  const Properties& ConfigAdmin::getActiveConfigurationSet()
  {
    return *(m_configsets.getNode(m_activeId));
  }


  bool ConfigAdmin::addConfigurationSet(const Properties& configset)
  {
    if (m_configsets.hasKey(configset.getName()))
      {
	return false;
      }

    std::string node(configset.getName());
    m_configsets[node.c_str()] = "";
    *(m_configsets.getNode(node.c_str())) << configset;
    m_newConfig.push_back(configset.getName());
    
    m_changed = true;
    m_active = false;
    return true;
  }


  bool ConfigAdmin::removeConfigurationSet(const char* config_id)
  {
    if (strcmp(config_id, "default") == 0) return false;

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
