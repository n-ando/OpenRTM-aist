// -*- C++ -*-
/*!
 * @file Manager.h
 * @brief RTComponent manager class
 * @date $Date: 2007-01-12 14:32:36 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2003-2005
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: Manager.cpp,v 1.5 2007-01-12 14:32:36 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.4  2007/01/09 15:11:24  n-ando
 * Now RTObject is activated itself. The Manager does nothing.
 *
 * Revision 1.3  2006/11/06 01:31:50  n-ando
 * Some Manager's functions has been implemented.
 * - Component creation process
 * - System logger initialization
 *
 * Revision 1.2  2006/10/25 17:27:57  n-ando
 * Component factory registration and relative functions are implemented.
 *
 * Revision 1.1  2006/10/17 10:21:17  n-ando
 * The first commitment.
 *
 *
 */


#include <rtm/Manager.h>
#include <rtm/ManagerConfig.h>
#include <rtm/Properties.h>
#include <rtm/ModuleManager.h>
#include <rtm/CorbaNaming.h>
#include <rtm/CorbaObjectManager.h>
#include <rtm/NamingManager.h>
#include <rtm/RTC.h>
#include <rtm/StringUtil.h>

#include <fstream>
namespace RTC
{
  Manager* Manager::manager = 0;
  ACE_Thread_Mutex Manager::mutex;
  
  Manager::Manager()
    : m_Logbuf(), m_MedLogbuf(m_Logbuf), rtcout(m_MedLogbuf)
  {
    ;
  }
  Manager::Manager(const Manager& manager)
    : m_Logbuf(), m_MedLogbuf(m_Logbuf), rtcout(m_MedLogbuf)
  {
    ;
  }
  /*!
   * @if jp
   * @brief マネージャの初期化
   * @else
   * @brief Initializa manager
   * @endif
   */
  Manager* Manager::init(int argc, char** argv)
  {
    // DCL for singleton
    if (!manager)
      {
	ACE_Guard<ACE_Thread_Mutex> guard(mutex);
	if (!manager)
	  {
	    manager = new Manager();
	    manager->initManager(argc, argv);
	    manager->initLogger();
	    manager->initORB();
	    manager->initNaming();
	  }
      }
    return manager;
  }


  /*!
   * @if jp
   * @brief マネージャのインスタンスの取得
   * @else
   * @brief Get instance of the manager
   * @return The only instance reference of the manager
   * @endif
   */ 
  Manager& Manager::instance()
  {
    // DCL for singleton
    if (!manager)
      {
	ACE_Guard<ACE_Thread_Mutex> guard(mutex);
	if (!manager)
	  {
	    manager = new Manager();
	    manager->initManager(0, NULL);
	    manager->initLogger();
	    manager->initORB();
	    manager->initNaming();

	  }
      }
    return *manager;
  }


  bool Manager::activateManager()
  {
    RTC_TRACE(("Manager::activateManager()"));
    return true;
  }


  void Manager::runManager(bool no_block)
  {
    if (no_block) {RTC_TRACE(("Manager::runManager(): non-blocking mode"));}
    else          {RTC_TRACE(("Manager::runManager(): blocking mode"));}
    return;
  }


  void Manager::setInitProc(InitProc proc)
  {
    m_initProc = proc;
  }


  //============================================================
  // Module management
  //============================================================
  /*!
   * @if jp
   * @brief モジュールのロード
   * @else
   * @brief Load module
   * @endif
   */  
  void Manager::load(const char* fname, const char* initfunc)
  {
    RTC_TRACE(("Manager::load()"));
    m_module->load(fname, initfunc);
    return;
  }


  /*!
   * @if jp
   * @brief モジュールのアンロード
   * @else
   * @brief Unload module
   * @param pathname Module file name
   * @endif
   */
  void Manager::unload(const char* fname)
  {
    RTC_TRACE(("Manager::unload()"));
    m_module->unload(fname);
    return;
  }


  /*!
   * @if jp
   * @brief 全モジュールのアンロード
   * @else
   * @brief Unload module
   * @endif
   */ 
  void Manager::unloadAll()
  {
    RTC_TRACE(("Manager::unloadAll()"));
    m_module->unloadAll();
    return;
  }

  
  /*!
   * @if jp
   * @brief ロード済みのモジュールリストを取得する
   * @else
   * @brief Get loaded module names
   * @endif
   */
  std::vector<std::string> Manager::getLoadedModules()
  {
    RTC_TRACE(("Manager::getLoadedModules()"));
    return m_module->getLoadedModules();
  }


  /*!
   * @if jp
   * @brief ロード可能なモジュールリストを取得する
   * @else
   * @brief Get loadable module names
   * @endif
   */
  std::vector<std::string> Manager::getLoadableModules()
  {    
    RTC_TRACE(("Manager::getLoadableModules()"));
    return m_module->getLoadableModules();
  }

  //============================================================
  // Component factory management
  //============================================================
  /*!
   * @if jp
   * @brief RTコンポーネントファクトリを登録する
   * @else
   * @brief Register RT-Component Factory
   * @endif
   */
  bool Manager::registerFactory(Properties profile,
				RtcNewFunc new_func,
				RtcDeleteFunc delete_func)
  {
    RTC_TRACE(("Manager::registerFactory(%s)", profile.getProperty("type_name").c_str()));
    try
      {    
	m_factory.registerObject(new FactoryCXX(profile, new_func, delete_func));
	return true;
      }
    catch (...)
      {
	return false;
      }
  }
  
  
  /*!
   * @if jp
   * @brief ファクトリ全リストを取得する
   * @else
   * @brief Get the list of all RT-Component Factory
   * @endif
   */
  std::vector<std::string> Manager::getModulesFactories()
  {
    RTC_TRACE(("Manager::getModulesFactories()"));

    ModuleFactories m;
    return m_factory.for_each(m).modlist;
  }
  

  //============================================================
  // Component management
  //============================================================
  /*!
   * @if jp
   * @brief RTコンポーネントを生成する
   * @else
   * @brief Create RT-Component
   * @endif
   */
  RtcBase* Manager::createComponent(const char* module_name)
  {
    RTC_TRACE(("Manager::createComponent(%s)", module_name));
    // コンポーネントを生成
    RtcBase* comp;
    comp = m_factory.find(module_name)->create(this);

    //============================================================
    // プロパティファイルをロード
    // rtc.conf: category.compname.config_file = file_name
    {
      std::string conf_key(module_name);
      conf_key += ".config_file";
      std::cout << "+++ Module config file +++" << std::endl;
      std::cout << "conf key:  " << conf_key << std::endl;
      std::cout << "conf file: " << m_config->getProperty(conf_key.c_str()) << std::endl;
      // コンポーネントが持つプロパティに直接マージ
      // getProperties() は参照を返すので
      mergeProperty(comp->getProperties(),
		    m_config->getProperty(conf_key.c_str()).c_str());
    }

    // rtc.conf: category.compname0.config_file = file_name
    {
      std::string conf_key;
      conf_key  = comp->getTypeName();
      conf_key += ".";
      conf_key += comp->getInstanceName();
      conf_key += ".config_file";
      std::cout << "+++ Instance config file +++" << std::endl;
      std::cout << "conf key:  " << conf_key << std::endl;
      std::cout << "conf file: " << m_config->getProperty(conf_key.c_str()) << std::endl;
      // コンポーネントが持つプロパティに直接マージ
      // getProperties() は参照を返すので
      mergeProperty(comp->getProperties(),
		    m_config->getProperty(conf_key.c_str()).c_str());
    }

    comp->getProperties().list(std::cout);
    std::string naming_formats;

    naming_formats += comp->getProperties().getProperty("naming_formats");
    naming_formats += ", ";
    naming_formats += m_config->getProperty("naming_formats");
    naming_formats = flatten(unique_sv(split(naming_formats, ",")));

    comp->getProperties().setProperty("naming_formats",	naming_formats);
    std::string naming_names;
    naming_names = formatString(naming_formats.c_str(),
				comp->getProperties());
    std::cout << "naming_name: " << naming_names << std::endl;

    comp->getProperties().setProperty("naming_names", naming_names.c_str());

    comp->initialize();

    registerComponent(comp);
    return comp;
  }


  /*!
   * @if jp
   * @brief RTコンポーネントを直接 Manager に登録する
   * @else
   * @brief Register RT-Component directly without Factory
   * @endif
   */
  bool Manager::registerComponent(RtcBase* comp)
  {
    RTC_TRACE(("Manager::registerComponent(%s)", comp->getInstanceName()));
    m_compManager.registerObject(comp);
    //    m_objManager->activate(comp);

    std::vector<std::string> names(comp->getNamingNames());
    std::vector<std::string>::iterator it, it_end;
    std::cout << "n size(): " << names.size() << std::endl;

    it = names.begin();
    it_end = names.end();
    for ( ; it != it_end; ++it)
      {
	std::cout << "####bind####: " << *it << std::endl;
	m_namingManager->bindObject(it->c_str(),
				    comp);
      }
    return true;
  }


  /*!
   * @if jp
   * @brief Manager に登録されているRTコンポーネントを削除する
   * @else
   * @brief Unregister RT-Component that is registered in the Manager
   * @endif
   */
  void Manager::deleteComponent(const char* instance_name)
  {
    RTC_TRACE(("Manager::deleteComponent(%s)", instance_name));
    //    RtcBase* comp;
    //comp = m_component.find(instance_name);

    //    m_naming->unregister(comp);
    //    m_activator->deactivate(comp);

    //    comp->finalize();
    //    m_component->unregisterObject(instance_name);
    //    delete comp;
  }


  /*!
   * @if jp
   * @brief Manager に登録されているRTコンポーネントを取得する
   * @else
   * @brief Get RT-Component's pointer
   * @endif
   */
  RtcBase* Manager::getComponent(const char* instance_name)
  {
    RTC_TRACE(("Manager::getComponent(%s)", instance_name));
    //    return m_component->find(instance_name);
    return NULL;
  }


  /*!
   * @if jp
   * @brief Manager に登録されている全RTコンポーネントを取得する
   * @else
   * @brief Get all RT-Component's pointer
   * @endif
   */
  std::vector<RtcBase*> Manager::getComponents()
  {
    RTC_TRACE(("Manager::getComponents()"));
    return m_compManager.getObjects();
  }


  //============================================================
  // CORBA 関連
  //============================================================
  /*!
   * @if jp
   * @brief ORB のポインタを取得する
   * @else
   * @brief Get the pointer to the ORB
   * @endif
   */
  CORBA::ORB_ptr Manager::getORB()
  {
    RTC_TRACE(("Manager::getORB()"));
    return m_pORB;
  }


  /*!
   * @if jp
   * @brief Manager が持つ RootPOA のポインタを取得する
   * @else
   * @brief Get the pointer to the RootPOA 
   * @endif
   */
  PortableServer::POA_ptr Manager::getPOA()
  {
    RTC_TRACE(("Manager::getPOA()"));
    return m_pPOA;
  }

  PortableServer::POAManager_ptr Manager::getPOAManager()
  {
    RTC_TRACE(("Manager::getPOAManager()"));
    return m_pPOAManager;
  }

  


  //============================================================
  // Protected functions
  //============================================================
  /*!
   * @if jp
   * @brief Manager の内部初期化処理
   * @else
   * @brief Manager internal initialization
   * @endif
   */
  void Manager::initManager(int argc, char** argv)
  {
    ManagerConfig config(argc, argv);
    m_config = new Properties(config.init());
    m_config->setProperty("logger.file_name",
	  formatString(m_config->getProperty("logger.file_name").c_str(),
          *m_config));
    m_module = new ModuleManager(*m_config);
  }
  
  /*!
   * @if jp
   * @brief CORBA ORB の初期化処理
   * @else
   * @brief CORBA ORB initialization
   * @endif
   */
  bool Manager::initORB()
  {
    RTC_TRACE(("Manager::initORB()"));
    // Initialize ORB
    try
      {
	//	int _argc = m_apConfig->getOrbInitArgc();
	//	char** _argv = m_apConfig->getOrbInitArgv();
	int argc(0);
	char** argv(NULL);
	m_pORB = CORBA::ORB_init(argc, argv);

	// Get the RootPOA
	CORBA::Object_var obj = m_pORB->resolve_initial_references("RootPOA");
	m_pPOA = PortableServer::POA::_narrow(obj);
	if (CORBA::is_nil(m_pPOA))
	  {
	    //	RTC_ERROR(("Could not resolve RootPOA."));
	    return false;
	  }
	// Get the POAManager
	m_pPOAManager = m_pPOA->the_POAManager();
	m_objManager = new CorbaObjectManager(m_pORB, m_pPOA);
      }
    catch (...)
      {
	//	RTC_ERROR(("exception: initORB(): unknown exception was caught." ));
	return false;
      }
    return true;
  }

  /*!
   * @if jp
   * @brief NamingManager の初期化
   * @else
   * @brief NamingManager initialization
   * @endif
   */
  bool Manager::initNaming()
  {
    std::cout << "initNaming()" << std::endl;
    m_namingManager = new NamingManager();

    if (CORBA::is_nil(m_pORB))
      return false;

    std::vector<std::string> names;
    std::cout << m_config->getProperty("corba.nameservers") << std::endl;
    names = split(m_config->getProperty("corba.nameservers"), ",");
    std::vector<std::string>::iterator it, it_end;
    it = names.begin();
    it_end = names.end();
    for ( ; it != it_end; ++it)
      {
	NamingOnCorba* name;
	std::cout << "create nameserver proxy: " << it->c_str() << std::endl;
	name = new NamingOnCorba(m_pORB, it->c_str());
	m_namingManager->registerNaming(name);
      }
    return true;
  }

  bool Manager::initLogger()
  {
    std::string logfile;
    logfile = m_config->getProperty("logger.file_name");
    if (logfile == "") logfile = "./rtc.log";

    // Open logfile and set suffix
    m_Logbuf.open(logfile.c_str(), std::ios::out | ios::app);
    
    // Set suffix for log entry haeader.
    m_MedLogbuf.setSuffix(m_config->getProperty("manager.name"));
    // Set date format for log entry header
    m_MedLogbuf.setDateFmt(m_config->getProperty("logger.date_format"));
    
    // Loglevel was set from configuration file.
    rtcout.setLogLevel(m_config->getProperty("logger.log_level"));

    // Log stream mutex locking mode
    rtcout.setLogLock(toBool(m_config->getProperty("logger.stream_lock"),
			     "enable", "disable", false));
#ifndef NO_LOGGING	
    RTC_INFO((m_config->getProperty("openrtm.version").c_str()));
    RTC_INFO(("Manager starting."));
    RTC_INFO(("Starting local logging."));
    rtcout.level(LogStream::RTL_TRACE) 
      << "============================================================"
      << std::endl;
    m_config->list(rtcout.level(LogStream::RTL_TRACE));
    rtcout.level(LogStream::RTL_TRACE)
      << "============================================================"
      << std::endl;
#endif
	
    return true;;
  }


  bool Manager::mergeProperty(Properties& prop, const char* file_name)
  {
    if (file_name != "")
      {
	std::ifstream conff(file_name);
	if (!conff.fail())
	  {
	    prop.load(conff);
	    conff.close();
	    return true;
	  }
      }
    return false;
  }

  std::string Manager::formatString(const char* naming_format,
				    Properties& prop)
  {
    std::string name(naming_format), str("");
    std::string::iterator it, it_end;
    int count(0);

    it = name.begin();
    it_end = name.end();
    for ( ; it != it_end; ++it)
      {
	char c(*it);
	if (c == '%')
	  {
	    ++count;
	    if (!(count % 2)) str.push_back((*it));
	  }
	else
	  {
	    if (count > 0 && (count % 2))
	      {
		count = 0;
		if      (c == 'n')  str += prop["instance_name"];
		else if (c == 't')  str += prop["type_name"];
		else if (c == 'm')  str += prop["type_name"];
		else if (c == 'v')  str += prop["version"];
		else if (c == 'V')  str += prop["vendor"];
		else if (c == 'c')  str += prop["category"];
		else if (c == 'h')  str += (*m_config)["manager.os.hostname"];
		else if (c == 'M')  str += (*m_config)["manager.name"];
		else if (c == 'p')  str += (*m_config)["manager.pid"];
		else str.push_back(c);
	      }
	    else
	      {
		count = 0;
		str.push_back(c);
	      }
	  }
      }
    return str;
  }

};
