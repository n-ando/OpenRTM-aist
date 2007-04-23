// -*- C++ -*-
/*!
 * @file ConfigAdmin.h
 * @brief Configuration Administration classes
 * @date $Date: 2007-04-23 04:51:21 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2007
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: ConfigAdmin.h,v 1.1 2007-04-23 04:51:21 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 */

#ifndef ConfigAdmin_h
#define ConfigAdmin_h

#include <rtm/Properties.h>
#include <rtm/StringUtil.h>
#include <string>
#include <vector>
#include <iostream>


namespace RTC
{
  //============================================================
  // ConfigBase class
  //============================================================
  class ConfigBase
  {
  public:
    ConfigBase(const char* name_, const char* def_val)
      : name(name_), default_value(def_val) {}
    virtual ~ConfigBase(){};
    virtual bool update(const char* val) = 0;
    const char* name;
    const char* default_value;
  };
  
  
  //============================================================
  // Config template class
  //============================================================
  template <typename VarType,
	    typename TransFunc = bool (*)(VarType&, const char*)>
  class Config
    : public ConfigBase
  {
  public:
    Config(const char* name, VarType& var, const char* def_val,
	   TransFunc trans = stringTo)
      : ConfigBase(name, def_val), m_var(var), m_trans(trans)
    {
    }
    virtual ~Config(){}
    virtual bool update(const char* val)
    {
      if ((*m_trans)(m_var, val)) return true;
      (*m_trans)(m_var, default_value);
      return false;
    }
    
  protected:
    VarType& m_var;
    TransFunc m_trans;
  };


  //============================================================
  // ConfigAdmin class
  //============================================================
  class ConfigAdmin
  {
  public:
    ConfigAdmin(RTC::Properties& prop);


    ~ConfigAdmin();


    template <typename VarType>
    bool bindParameter(const char* param_name, VarType& var,
		       const char* def_val,
		       bool (*trans)(VarType&, const char*) = ::stringTo)
    {
      if (isExist(param_name)) return false;
      if (!::stringTo(var, def_val)) return false;
      m_params.push_back(new Config<VarType>(param_name, var, def_val, trans));
      return true;
    }


    void update(const char* config_set);
    

    void update(const char* config_set, const char* config_param);

    void update();
    

    bool isExist(const char* name);

    bool haveConfig(const char* config_id)
    {
      return (m_configsets.hasKey(config_id) == NULL) ? false : true;
    }

    bool isActive()
    {
      return m_active;
    }
    //    const std::vector<Properties*>* getConfigurationParameterValues();
    //    const Properties* getConfigurationParameterValue(const char* name);
    //    bool setConfigurationParameter(const char* name, const char* value);

    const std::vector<Properties*>& getConfigurationSets();
    const Properties& getConfigurationSet(const char* config_id);
    bool setConfigurationSetValues(const char* config_id,
				   const Properties& configuration_set);
    const Properties& getActiveConfigurationSet();
    bool addConfigurationSet(const Properties& configuration_set);
    bool removeConfigurationSet(const char* config_id);
    bool activateConfigurationSet(const char* config_id);



  private:

    ConfigAdmin(const ConfigAdmin& ca) : m_configsets(ca.m_configsets) {};
    ConfigAdmin& operator=(const ConfigAdmin& ca){return *this;};

    struct find_conf
    {
      std::string m_name;
      find_conf(const char* name) : m_name(name) {};
      bool operator()(ConfigBase* conf)
      {
	return m_name == conf->name;
      }
    };
    
    
    RTC::Properties& m_configsets;
    std::vector<ConfigBase*> m_params;
    std::string m_activeId;
    bool m_active;
    bool m_changed;
    std::vector<std::string> m_newConfig;
  };
}; // namespace RTC
#endif // ConfigAdmin_h
