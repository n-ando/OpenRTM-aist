// -*- C++ -*-
/*!
 * @file ManagerConfig.cpp
 * @brief RTC manager configuration
 * @date $Date: 2006-10-17 19:29:53 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2003-2005
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: ManagerConfig.cpp,v 1.2 2006-10-17 19:29:53 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.1  2006/10/17 10:21:31  n-ando
 * The first commitment.
 *
 *
 */

#include <rtm/ManagerConfig.h>
#include <ace/Get_Opt.h>
#include <fstream>
#include <iostream>
#include <ace/OS.h>
#include <rtm/DefaultConfiguration.h>

namespace RTC
{
  /*!
   * @if jp
   * @brief ManagerConfig コンストラクタ
   * @else
   * @brief ManagerConfig constructor
   * @endif
   */
  ManagerConfig::ManagerConfig()
  {
  }


  /*!
   * @if jp
   * @brief ManagerConfig コンストラクタ
   * @else
   * @brief ManagerConfig constructor
   * @endif
   */
  ManagerConfig::ManagerConfig(int argc, char** argv)
  {
    init(argc, argv);
  }


  /*!
   * @if jp
   * @brief ManagerConfig デストラクタ
   * @else
   * @brief ManagerConfig destructor
   * @endif
   */
  ManagerConfig::~ManagerConfig()
  {
  }


  /*!
   * @if jp
   * @brief 初期化
   * @else
   * @brief Initialization
   * @endif
   */
  Properties ManagerConfig::init()
  {
    if (findConfigFile())
      {
	Properties prop;
	std::ifstream f(m_configFile.c_str());
	prop.load(f);
	f.close();
	setSystemInformation(prop);
	return prop;
      }
    else
      {
	return Properties(default_config);
      }
  }

  Properties ManagerConfig::init(int argc, char** argv)
  {
    parseArgs(argc, argv);
    return init();
  }


  /*!
   * @if jp
   * @brief コマンド引数をパースする
   * @else
   * @brief Parse command arguments
   * @endif
   */
  void ManagerConfig::parseArgs(int argc, char** argv)
  {
    ACE_Get_Opt get_opts(argc, argv, "f:l:o:d", 0);
    int opt;
    
    //  if (argc == 0) return true;
    
    while ((opt = get_opts()) > 0)
      {
	switch (opt)
	  {
	    // Specify configuration file not default
	  case 'f':
	    m_configFile = get_opts.optarg;
	    break;
	  case 'l':
	    //	    m_configFile = get_opts.optarg;
	    break;
	  case 'o':
	    //	    m_configFile = get_opts.optarg;
	    break;
	    // Use default configuration settings
	  case 'd': 
	    //	    m_DebugMode = true;
	    break;
	  default:
	    ;
	  }
      }
    return;
  }


  /*!
   * @if jp
   * @brief Configuration file を探す
   * @else
   * @brief Find configuration file
   * @endif
   */
  bool ManagerConfig::findConfigFile()
  {
    // Check existance of configuration file given command arg
    if (m_configFile != "") 
      {
	if (fileExist(m_configFile))
	  {
	    return true;
	  }
      }
    
    // Search rtc configuration file from environment variable
    char* env = getenv(config_file_env);
    if (env != NULL)
      {
	if (fileExist(env))
	  {
	    m_configFile = env;
	    return true;
	  }
	}
    
    // Search rtc configuration file from default search path
    int i = 0;
    while (config_file_path[i] != NULL)
      {
	if (fileExist(config_file_path[i]))
	  {
	    m_configFile = config_file_path[i];
	    return true;
	  }
	++i;
      }
    
    return false;
  }
  

  /*!
   *
   * manager.os.name: 
   * manager.os.release:
   * maanger.os.version:
   * manager.os.arch:
   * manager.os.hostname:
   * manager.pid:
   *
   */
  void ManagerConfig::setSystemInformation(Properties& prop)
  { 
    //
    // Get system information by using ACE_OS::uname (UNIX/Windows)
    // 
    ACE_utsname  sysinfo;
    if (ACE_OS::uname(&sysinfo) != 0)
      {
	return;
      }
    
    //
    // Getting current proccess pid by using ACE_OS::getpid() (UNIX/Windows)
    //
    pid_t pid = ACE_OS::getpid();
    char pidc[8];
    sprintf(pidc, "%d", pid);
    
    prop.setProperty("manager.os.name",     sysinfo.sysname);
    prop.setProperty("manager.os.release",  sysinfo.release);
    prop.setProperty("maanger.os.version",  sysinfo.version);
    prop.setProperty("manager.os.arch",     sysinfo.machine);
    prop.setProperty("manager.os.hostname", sysinfo.nodename);
    prop.setProperty("manager.pid",         pidc);
    
    return;
  }
  
  
  /*!
   * @if jp
   * @brief ファイルが存在するかどうか確かめる
   * @else
   * @brief Check file existance
   * @endif
   */
  bool ManagerConfig::fileExist(const std::string& filename)
  {
    std::ifstream infile;
    infile.open(filename.c_str(), std::ios::in);
    // fial() 0: ok, !0: fail
    if (infile.fail() != 0) 
      {
	infile.close();
	return false;
      }
      else
	{
	  infile.close();
	  return true;
	}
    return false;
  }

}
