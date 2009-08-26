// -*- C++ -*-
/*!
 * @file Manager.h
 * @brief RTComponent manager class
 * @date $Date: 2008-03-06 06:58:40 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2003-2005
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id$
 *
 */

#include <rtm/Manager.h>
#include <rtm/ManagerConfig.h>
#include <rtm/ModuleManager.h>
#include <rtm/CorbaNaming.h>
#include <rtm/NamingManager.h>
#include <rtm/RTC.h>
#include <rtm/PeriodicExecutionContext.h>
#include <rtm/ExtTrigExecutionContext.h>
#include <rtm/OpenHRPExecutionContext.h>
#include <rtm/PeriodicECSharedComposite.h>
#include <rtm/RTCUtil.h>
#include <rtm/ManagerServant.h>
#include <fstream>
#include <iostream>
#include <coil/Properties.h>
#include <coil/stringutil.h>
#include <coil/Signal.h>
#include <coil/TimeValue.h>
#include <coil/Timer.h>
#include <coil/OS.h>
#include <rtm/FactoryInit.h>

#if defined(minor)
#undef minor
#endif


//static sig_atomic_t g_mgrActive = true;
extern "C" void handler (int)
{
  RTC::Manager::instance().terminate();
}

namespace RTC
{
  Manager* Manager::manager = NULL;
  coil::Mutex Manager::mutex;

  Manager::InstanceName::InstanceName(RTObject_impl* comp)
    : m_name(comp->getInstanceName())
  {}
  Manager::InstanceName::InstanceName(const char* name)
    : m_name(name)
  {}
  Manager::InstanceName::InstanceName(const std::string name)
    : m_name(name)
  {}
  bool Manager::InstanceName::operator()(RTObject_impl* comp)
  {
    return m_name == comp->getInstanceName();
  }

  
  /*!
   * @if jp
   * @brief Protected コンストラクタ
   * @else
   * @brief Protected Constructor
   * @endif
   */
  Manager::Manager()
    : m_initProc(NULL),
      m_logStreamBuf(), rtclog(&m_logStreamBuf),
      m_runner(NULL), m_terminator(NULL)
  {
    new coil::SignalAction((coil::SignalHandler) handler, SIGINT);
  }
  
  /*!
   * @if jp
   * @brief Protected コピーコンストラクタ
   * @else
   * @brief Protected Copy Constructor
   * @endif
   */
  Manager::Manager(const Manager& manager)
    : m_initProc(NULL),
      m_logStreamBuf(), rtclog(&m_logStreamBuf),
      m_runner(NULL), m_terminator(NULL)
  {
    new coil::SignalAction((coil::SignalHandler) handler, SIGINT);
  }
  
  /*!
   * @if jp
   * @brief マネージャの初期化
   * @else
   * @brief Initialize manager
   * @endif
   */
  Manager* Manager::init(int argc, char** argv)
  {
    // DCL for singleton
    if (!manager)
      {
	Guard guard(mutex);
	if (!manager)
	  {
	    manager = new Manager();
	    manager->initManager(argc, argv);
	    manager->initLogger();
	    manager->initORB();
	    manager->initNaming();
            manager->initFactories();
	    manager->initExecContext();
	    manager->initComposite();
	    manager->initTimer();
            manager->initManagerServant();
	  }
      }
    return manager;
  }
  
  /*!
   * @if jp
   * @brief マネージャのインスタンスの取得
   * @else
   * @brief Get instance of the manager
   * @endif
   */ 
  Manager& Manager::instance()
  {
    // DCL for singleton
    if (!manager)
      {
	Guard guard(mutex);
	if (!manager)
	  {
	    manager = new Manager();
	    manager->initManager(0, NULL);
	    manager->initLogger();
	    manager->initORB();
	    manager->initNaming();
            manager->initFactories();
	    manager->initExecContext();
	    manager->initComposite();
	    manager->initTimer();
	  }
      }
    return *manager;
  }
  
  /*!
   * @if jp
   * @brief マネージャ終了処理
   * @else
   * @brief Terminate Manager
   * @endif
   */ 
  void Manager::terminate()
  {
    if (m_terminator != NULL)
      m_terminator->terminate();
  }
  
  /*!
   * @if jp
   * @brief マネージャ・シャットダウン
   * @else
   * @brief Shutdown Manager
   * @endif
   */
  void Manager::shutdown()
  {
    RTC_TRACE(("Manager::shutdown()"));
    shutdownComponents();
    shutdownNaming();
    shutdownORB();
    shutdownManager();
    // 終了待ち合わせ
    if (m_runner != NULL)
      {
	m_runner->wait();
      }
    else
      {
	join();
      }
    shutdownLogger();
  }
  
  /*!
   * @if jp
   * @brief マネージャ終了処理の待ち合わせ
   * @else
   * @brief Wait for Manager's termination
   * @endif
   */ 
  void Manager::join()
  {
    RTC_TRACE(("Manager::wait()"));
    {
      Guard guard(m_terminate.mutex);
      ++m_terminate.waiting;
    }
    while (1)
      {
	{
	  Guard guard(m_terminate.mutex);
	  if (m_terminate.waiting > 1) break;
	}
        coil::usleep(100000);
      }
  }
  
  /*!
   * @if jp
   * @brief 初期化プロシージャのセット
   * @else
   * @brief Set initial procedure
   * @endif
   */ 
  void Manager::setModuleInitProc(ModuleInitProc proc)
  {
    m_initProc = proc;
  }
  
  /*!
   * @if jp
   * @brief Managerのアクティブ化
   * @else
   * @brief Activate the Manager
   * @endif
   */ 
  bool Manager::activateManager()
  {
    RTC_TRACE(("Manager::activateManager()"));
    
    try
      {
        if(CORBA::is_nil(this->getPOAManager()))
        {
          RTC_ERROR(("Could not get POA manager."));
          return false;
        }
	this->getPOAManager()->activate();
        RTC_TRACE(("POA Manager activated."));
      }
    catch (...)
      {
        RTC_ERROR(("POA Manager activatatin failed."));
	return false;
      }

    std::vector<std::string> mods;
    mods = coil::split(m_config["manager.modules.preload"], ",");

    for (int i(0), len(mods.size()); i < len; ++i)
      {
	std::string basename(coil::split(mods[i], ".").operator[](0));
	basename += "Init";
	try
	  {
	    m_module->load(mods[i], basename);
	  }
	catch (ModuleManager::Error& e)
	  {
	    RTC_ERROR(("Module load error: %s", e.reason.c_str()));
	  }
	catch (ModuleManager::NotFound& e)
	  {
	    RTC_ERROR(("Module not found: %s", e.name.c_str()));
	  }
	catch (...)
	  {
	    RTC_ERROR(("Unknown Exception"));
	  }
      }
    std::vector<std::string> comp;
    comp = coil::split(m_config["manager.components.precreate"], ",");
    for (int i(0), len(comp.size()); i < len; ++i)
      {
	this->createComponent(comp[i].c_str());
      }

    if (m_initProc != NULL)
      {
        m_initProc(this);
      }

    return true;
  }
  
  /*!
   * @if jp
   * @brief Managerの実行
   * @else
   * @brief Run the Manager
   * @endif
   */ 
  void Manager::runManager(bool no_block)
  {
    if (no_block)
      {
	RTC_TRACE(("Manager::runManager(): non-blocking mode"));
	m_runner = new OrbRunner(m_pORB);
	m_runner->open(0);
      }
    else
      {
	RTC_TRACE(("Manager::runManager(): blocking mode"));
	m_pORB->run();
	RTC_TRACE(("Manager::runManager(): ORB was terminated"));
	join();
      }
    return;
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
   * @brief Unload all modules
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
   * @brief Get a list of loaded modules
   * @endif
   */
  std::vector<coil::Properties> Manager::getLoadedModules()
  {
    RTC_TRACE(("Manager::getLoadedModules()"));
    return m_module->getLoadedModules();
  }
  
  /*!
   * @if jp
   * @brief ロード可能なモジュールリストを取得する
   * @else
   * @brief Get a list of loadable modules
   * @endif
   */
std::vector<coil::Properties> Manager::getLoadableModules()
  {    
    RTC_TRACE(("Manager::getLoadableModules()"));
    return m_module->getLoadableModules();
  }
  
  //============================================================
  // Component factory management
  //============================================================
  /*!
   * @if jp
   * @brief RTコンポーネント用ファクトリを登録する
   * @else
   * @brief Register RT-Component Factory
   * @endif
   */
  bool Manager::registerFactory(coil::Properties& profile,
				RtcNewFunc new_func,
				RtcDeleteFunc delete_func)
  {
    RTC_TRACE(("Manager::registerFactory(%s)", profile["type_name"].c_str()));
    FactoryBase* factory;
    factory = new FactoryCXX(profile, new_func, delete_func);
    try
      {    
	bool ret = m_factory.registerObject(factory);
	if (!ret) {
	  delete factory;
	  return false;
	}
	return true;
      }
    catch (...)
      {
	delete factory;
	return false;
      }
  }
  
  std::vector<coil::Properties> Manager::getFactoryProfiles()
  {
    std::vector<FactoryBase*> factories(m_factory.getObjects());
    std::vector<coil::Properties> props;
    for (int i(0), len(factories.size()); i < len; ++i)
      {
        props.push_back(factories[i]->profile());
      }
    return props;
  }
  
  /*!
   * @if jp
   * @brief ExecutionContext用ファクトリを登録する
   * @else
   * @brief Register ExecutionContext Factory
   * @endif
   */
  bool Manager::registerECFactory(const char* name,
				  ECNewFunc new_func,
				  ECDeleteFunc delete_func)
  {
    RTC_TRACE(("Manager::registerECFactory(%s)", name));
    try
      {    
	ECFactoryBase* factory;
	factory = new ECFactoryCXX(name, new_func, delete_func);
//	m_ecfactory.registerObject(factory);
//	return true;
	if(m_ecfactory.registerObject(factory))
        {
	  return true;
        }
      }
    catch (...)
      {
	return false;
      }
    return false;
  }
  
  /*!
   * @if jp
   * @brief ファクトリ全リストを取得する
   * @else
   * @brief Get the list of all Factories
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
   * @brief Create RT-Components
   * @endif
   */
  RTObject_impl* Manager::createComponent(const char* comp_args)
  {
    RTC_TRACE(("Manager::createComponent(%s)", comp_args));

    //------------------------------------------------------------
    // extract "comp_type" and "comp_prop" from comp_arg
    coil::Properties comp_prop, comp_id;
    if (!procComponentArgs(comp_args, comp_id, comp_prop)) return NULL;

    if (!comp_prop["exported_ports"].empty())
      comp_prop["conf.default.exported_ports"] = comp_prop["exported_ports"];

    //------------------------------------------------------------
    // Create Component
    FactoryBase* factory(m_factory.find(comp_id));
    if (factory == NULL)
      {
	RTC_ERROR(("Factory not found: %s",
                   comp_id["implementation_id"].c_str()));
	return NULL;
      }

    coil::Properties prop;
    prop = factory->profile();
    prop << comp_prop;

    const char* inherit_prop[] = {
      "exec_cxt.periodic.type",
      "exec_cxt.periodic.rate",
      "exec_cxt.evdriven.type",
      "naming.formats",
      "logger.enable",
      "logger.log_level",
      "naming.enable",
      "naming.type",
      "naming.formats",
      ""
    };

    for (int i(0); inherit_prop[i][0] != '\0'; ++i)
      {
        prop[inherit_prop[i]] = m_config[inherit_prop[i]];
      }
      
    RTObject_impl* comp;
    comp = factory->create(this);
    if (comp == NULL)
      {
	RTC_ERROR(("RTC creation failed: %s",
                   comp_id["implementaion_id"].c_str()));
	return NULL;
      }
    RTC_TRACE(("RTC created: %s", comp_id["implementaion_id"].c_str()));

    //------------------------------------------------------------
    // Load configuration file specified in "rtc.conf"
    //
    // rtc.conf:
    //   [category].[type_name].config_file = file_name
    //   [category].[instance_name].config_file = file_name
    configureComponent(comp, prop);

    // comp->setProperties(prop);
    
    //------------------------------------------------------------
    // Component initialization
    if (comp->initialize() != RTC::RTC_OK)
      {
	RTC_TRACE(("RTC initialization failed: %s",
                   comp_id["implementaion_id"].c_str()));
	comp->exit();
	RTC_TRACE(("%s was finalized", comp_id["implementaion_id"].c_str()));
	return NULL;
      }
    RTC_TRACE(("RTC initialization succeeded: %s",
               comp_id["implementaion_id"].c_str()));
    //------------------------------------------------------------
    // Bind component to naming service
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
  bool Manager::registerComponent(RTObject_impl* comp)
  {
    RTC_TRACE(("Manager::registerComponent(%s)", comp->getInstanceName()));
    // ### NamingManager のみで代用可能
    m_compManager.registerObject(comp);
    
    std::vector<std::string> names(comp->getNamingNames());
    
    for (int i(0), len(names.size()); i < len; ++i)
      {
	RTC_TRACE(("Bind name: %s", names[i].c_str()));
	m_namingManager->bindObject(names[i].c_str(), comp);
      }
    return true;
  }
  
  /*!
   * @if jp
   * @brief RTコンポーネントの登録を解除する
   * @else
   * @brief Unregister RT-Components
   * @endif
   */
  bool Manager::unregisterComponent(RTObject_impl* comp)
  {
    RTC_TRACE(("Manager::unregisterComponent(%s)", comp->getInstanceName()));
    // ### NamingManager のみで代用可能
    m_compManager.unregisterObject(comp->getInstanceName());
    
    std::vector<std::string> names(comp->getNamingNames());
    
    for (int i(0), len(names.size()); i < len; ++i)
      {
	RTC_TRACE(("Unbind name: %s", names[i].c_str()));
	m_namingManager->unbindObject(names[i].c_str());
      }
    return true;
  }
  

  ExecutionContextBase* Manager::createContext(const char* ec_args)
  {
    RTC_TRACE(("Manager::createContext()"));
    RTC_TRACE(("ExecutionContext type: %s", 
	       m_config.getProperty("exec_cxt.periodic.type").c_str()));

    std::string ec_id;
    coil::Properties ec_prop;
    if (!procContextArgs(ec_args, ec_id, ec_prop)) return NULL;

    ECFactoryBase* factory(m_ecfactory.find(ec_id.c_str()));
    if (factory == NULL)
      {
        RTC_ERROR(("Factory not found: %s", ec_id.c_str()));
        return NULL;
      }

    ExecutionContextBase* ec;
    ec = factory->create();
    return ec;
  }
  
  /*!
   * @if jp
   * @brief Manager に登録されているRTコンポーネントを削除する
   * @else
   * @brief Unregister RT-Components that have been registered to Manager
   * @endif
   */
  void Manager::deleteComponent(const char* instance_name)
  {
    RTC_TRACE(("Manager::deleteComponent(%s)", instance_name));
    RTObject_impl* comp;
    comp = m_compManager.find(instance_name);
    if (comp == NULL) return;

    coil::Properties comp_id;
    comp_id["vendor"] = comp->getProperties().getProperty("vendor");
    comp_id["category"] = comp->getProperties().getProperty("category");
    comp_id["implementation_id"] = comp->getProperties().getProperty("implementation_id");
    comp_id["version"] = comp->getProperties().getProperty("version");

    FactoryBase* factory(m_factory.find(comp_id));
    
    ReturnCode_t ret = comp->exit();

    if (factory == NULL)
      {
	return;
      }
    else
      {
	factory->destroy(comp);
      } 
  }
  
  /*!
   * @if jp
   * @brief Manager に登録されているRTコンポーネントを検索する
   * @else
   * @brief Get RT-Component's pointer
   * @endif
   */
  RTObject_impl* Manager::getComponent(const char* instance_name)
  {
    RTC_TRACE(("Manager::getComponent(%s)", instance_name));
    return m_compManager.find(instance_name);
  }
  
  /*!
   * @if jp
   * @brief Manager に登録されている全RTコンポーネントを取得する
   * @else
   * @brief Get all RT-Components registered in the Manager
   * @endif
   */
  std::vector<RTObject_impl*> Manager::getComponents()
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
  
  /*!
   * @if jp
   * @brief Manager が持つ POAManager を取得する
   * @else
   * @brief Get the pointer to the POAManager 
   * @endif
   */
  PortableServer::POAManager_ptr Manager::getPOAManager()
  {
    RTC_TRACE(("Manager::getPOAManager()"));
    return m_pPOAManager;
  }
  
  //============================================================
  // Protected functions
  //============================================================
  
  //============================================================
  // Manager initialization and finalization
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
    // load configurations
    ManagerConfig config(argc, argv);
    config.configure(m_config);
    m_config["logger.file_name"] = 
      formatString(m_config["logger.file_name"].c_str(), m_config);
    
    // initialize ModuleManager
    m_module = new ModuleManager(m_config);

    // initialize Terminator
    m_terminator = new Terminator(this);
    {
      Guard guard(m_terminate.mutex);
      m_terminate.waiting = 0;
    }
    
    // initialize Timer
    if (coil::toBool(m_config["timer.enable"], "YES", "NO", true))
      {
        coil::TimeValue tm(0, 100000);
	std::string tick(m_config["timer.tick"]);
	if (!tick.empty())
	  {
	    tm = atof(tick.c_str());
	    m_timer = new coil::Timer(tm);
	    m_timer->start();
	  }
      }
  }
  
  /*!
   * @if jp
   * @brief Manager の終了処理
   * @else
   * @brief Manager internal finalization
   * @endif
   */
  void Manager::shutdownManager()
  {
    RTC_TRACE(("Manager::shutdownManager()"));
  }
  
  //============================================================
  // Logger initialization and finalization
  //============================================================
  /*!
   * @if jp
   * @brief System logger の初期化
   * @else
   * @brief System logger initialization
   * @endif
   */
  bool Manager::initLogger()
  {
    rtclog.setLevel("SILENT");
    rtclog.setName("manager");
    
    if (!coil::toBool(m_config["logger.enable"], "YES", "NO", true))
      {
        return true;
      }

    std::vector<std::string> logouts;
    logouts = coil::split(m_config["logger.file_name"], ",");

    for (int i(0), len(logouts.size()); i < len; ++i)
      {
        std::string logfile(logouts[i]);
        if (logfile == "") continue;
	
        // Open logfile
        if (logfile == "STDOUT" || logfile == "stdout")
          {
            m_logStreamBuf.addStream(std::cout.rdbuf());
            continue;
          }
        
        std::filebuf* of = new std::filebuf();
        of->open(logfile.c_str(), std::ios::out | std::ios::app);

        if (!of->is_open())
          {
            std::cerr << "Error: cannot open logfile: "
                      << logfile << std::endl;
            delete of;
            continue;
          }
        m_logStreamBuf.addStream(of, true);
        m_logfiles.push_back(of);
      }
	

    // Set date format for log entry header
    rtclog.setDateFormat(m_config["logger.date_format"].c_str());
    
    // Loglevel was set from configuration file.
    rtclog.setLevel(m_config["logger.log_level"].c_str());
	
    // Log stream mutex locking mode
    coil::toBool(m_config["logger.stream_lock"],
                 "enable", "disable", false) ? 
      rtclog.enableLock() : rtclog.disableLock();
                 
	
    RTC_INFO(("%s", m_config["openrtm.version"].c_str()));
    RTC_INFO(("Copyright (C) 2003-2007"));
    RTC_INFO(("  Noriaki Ando"));
    RTC_INFO(("  Task-intelligence Research Group,"));
    RTC_INFO(("  Intelligent Systems Research Institute, AIST"));
    RTC_INFO(("Manager starting."));
    RTC_INFO(("Starting local logging."));

    return true;;
  }
  
  /*!
   * @if jp
   * @brief System Logger の終了処理
   * @else
   * @brief System Logger finalization
   * @endif
   */
  void Manager::shutdownLogger()
  {
    RTC_TRACE(("Manager::shutdownLogger()"));
    rtclog.flush();

    for (int i(0), len(m_logfiles.size()); i < len; ++i)
      {
        m_logfiles[i]->close();
        //        m_logStreamBuf.removeStream(m_logfiles[i]->rdbuf());
        delete m_logfiles[i];
      }
    if (!m_logfiles.empty())
      {
        m_logfiles.clear();
      }
  }
  
  //============================================================
  // ORB initialization and finalization
  //============================================================
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
	std::vector<std::string> args(coil::split(createORBOptions(), " "));
	// TAO's ORB_init needs argv[0] as command name.
	args.insert(args.begin(), "manager");
	char** argv = coil::toArgv(args);
	int argc(args.size());
	
	// ORB initialization
	m_pORB = CORBA::ORB_init(argc, argv);
	// Get the RootPOA
	CORBA::Object_var obj = m_pORB->resolve_initial_references("RootPOA");
	m_pPOA = PortableServer::POA::_narrow(obj);
	if (CORBA::is_nil(m_pPOA))
	  {
	    RTC_ERROR(("Could not resolve RootPOA."));
	    return false;
	  }
	// Get the POAManager
	m_pPOAManager = m_pPOA->the_POAManager();
      }
    catch (...)
      {
	RTC_ERROR(("Exception: Caught unknown exception in initORB()." ));
	return false;
      }
    return true;
  }
  
  /*!
   * @if jp
   * @brief ORB のコマンドラインオプション作成
   * @else
   * @brief ORB command option creation
   * @endif
   */
  std::string Manager::createORBOptions()
  {
    std::string opt(m_config["corba.args"]);
    std::string corba(m_config["corba.id"]);
    std::string endpoint(m_config["corba.endpoint"]);
    
    if (!endpoint.empty())
      {
	if (!opt.empty()) opt += " ";
	if (corba == "omniORB")   opt = "-ORBendPoint giop:tcp:" + endpoint;
	else if (corba == "TAO")  opt = "-ORBEndPoint iiop://" + endpoint;
	else if (corba == "MICO") opt = "-ORBIIOPAddr inet:" + endpoint;
      }
    return opt;
  }
  
  /*!
   * @if jp
   * @brief ORB の終了処理
   * @else
   * @brief ORB finalization
   * @endif
   */
  void Manager::shutdownORB()
  {
    RTC_TRACE(("Manager::shutdownORB()"));
    if(CORBA::is_nil(m_pORB))
      {
        return;
      }
    try
      {
      while (m_pORB->work_pending())
        {
	  RTC_PARANOID(("Pending work still exists."));
	  if (m_pORB->work_pending())
	    m_pORB->perform_work();
        }
        RTC_DEBUG(("No pending works of ORB. Shutting down POA and ORB."));
      }
    catch(...)
      { 
        RTC_ERROR(("Caught SystemException during perform_work."));
      }
    
    if (!CORBA::is_nil(m_pPOA))
      {
	try
	  {
	    if (!CORBA::is_nil(m_pPOAManager))
	      m_pPOAManager->deactivate(false, true);
	    RTC_DEBUG(("POA Manager was deactivated."));
	    m_pPOA->destroy(false, true);
	    m_pPOA = PortableServer::POA::_nil();
	    RTC_DEBUG(("POA was destroid."));
	  }
	catch (CORBA::SystemException& ex)
	  {
	    RTC_ERROR(("Exception cought during root POA destruction"));
	    RTC_ERROR(("CORBA::SystemException(minor=%d)", ex.minor()));
	  }
	catch (...)
	  {
	    RTC_ERROR(("Caught unknown exception during POA destruction."));
	  }
      }
    
    if (!CORBA::is_nil(m_pORB))
      {
	try
	  {
	    m_pORB->shutdown(true);
	    RTC_DEBUG(("ORB was shutdown."));
            //m_pORB->destroy();
	    RTC_DEBUG(("ORB was destroied."));
	    m_pORB = CORBA::ORB::_nil();
	  }
	catch (CORBA::SystemException& ex)
	  {
	    RTC_ERROR(("Exception caught during ORB shutdown"));
            RTC_ERROR(("CORBA::SystemException(minodor=%d)", ex.minor()));
	  }
	catch (...)
	  {
	    RTC_ERROR(("Caught unknown exception during ORB shutdown."));
	  }
      }
  }
  
  //============================================================
  // Naming initialization and finalization
  //============================================================
  /*!
   * @if jp
   * @brief NamingManager の初期化
   * @else
   * @brief NamingManager initialization
   * @endif
   */
  bool Manager::initNaming()
  {
    RTC_TRACE(("Manager::initNaming()"));
    
    m_namingManager = new NamingManager(this);
    
    // If NameService is disabled, return immediately
    if (!coil::toBool(m_config["naming.enable"], "YES", "NO", true)) return true;
    
    // NameServer registration for each method and servers
    std::vector<std::string> meth(coil::split(m_config["naming.type"], ","));
    
    for (int i(0), len_i(meth.size()); i < len_i; ++i)
      {
	std::vector<std::string> names;
	names = coil::split(m_config[meth[i] + ".nameservers"], ",");
	
	
	for (int j(0), len_j(names.size()); j < len_j; ++j)
	  {
	    RTC_TRACE(("Register Naming Server: %s/%s",		\
		       meth[i].c_str(), names[j].c_str()));	
	    m_namingManager->registerNameServer(meth[i].c_str(),
						names[j].c_str());
	  }
      }
    
    // NamingManager Timer update initialization
    if (coil::toBool(m_config["naming.update.enable"], "YES", "NO", true))
      {
        coil::TimeValue tm(10, 0); // default interval = 10sec for safty
	std::string intr(m_config["naming.update.interval"]);
	if (!intr.empty())
	  {
	    tm = atof(intr.c_str());
	  }
	if (m_timer != NULL)
	  {
	    m_timer->registerListenerObj(m_namingManager, 
					 &NamingManager::update, tm);
	  }
      }
    return true;
  }
  
  /*!
   * @if jp
   * @brief NamingManager の終了処理
   * @else
   * @brief NamingManager finalization
   * @endif
   */
  void Manager::shutdownNaming()
  {
    RTC_TRACE(("Manager::shutdownNaming()"));
    m_namingManager->unbindAll();
    delete m_namingManager;
  }
  
  //============================================================
  // Naming initialization and finalization
  //============================================================
  /*!
   * @if jp
   * @brief ExecutionContextManager の初期化
   * @else
   * @brief ExecutionContextManager initialization
   * @endif
   */
  bool Manager::initExecContext()
  {
    RTC_TRACE(("Manager::initExecContext()"));
    PeriodicExecutionContextInit(this);
    ExtTrigExecutionContextInit(this);
    OpenHRPExecutionContextInit(this);
    return true;
  }

  bool Manager::initComposite()
  {
    RTC_TRACE(("Manager::initComposite()"));
    PeriodicECSharedCompositeInit(this);

    return true;
  }
  
  bool Manager::initFactories()
  {
    RTC_TRACE(("Manager::initFactories()"));
    FactoryInit();
    return true;
  }

  /*!
   * @if jp
   * @brief Timer の初期化
   * @else
   * @brief Timer initialization
   * @endif
   */
  bool Manager::initTimer()
  {
    return true;
  }


  bool Manager::initManagerServant()
  {
    m_mgrservant = new RTM::ManagerServant();
    coil::Properties& prop(m_config.getNode("manager"));
    std::vector<std::string> names(coil::split(prop["naming_formats"], ","));

    for (int i(0), len(names.size()); i < len; ++i)
      {
        std::string mgr_name(formatString(names[i].c_str(), prop));
        m_namingManager->bindObject(mgr_name.c_str(), m_mgrservant);
      }

    std::ifstream otherref(m_config["manager.refstring_path"].c_str());
    if (otherref.fail() != 0)
      {
        otherref.close();
        std::ofstream reffile(m_config["manager.refstring_path"].c_str());
	RTM::Manager_var mgr_v(RTM::Manager::_duplicate(m_mgrservant->getObjRef()));
        CORBA::String_var str_var = m_pORB->object_to_string(mgr_v);
	reffile << str_var;
        reffile.close();
      }
    else
      {
        std::string refstring;
        otherref >> refstring;
        otherref.close();

        CORBA::Object_var obj = m_pORB->string_to_object(refstring.c_str());
        RTM::Manager_var mgr = RTM::Manager::_narrow(obj);
        //        if (CORBA::is_nil(mgr)) return false;
        //        mgr->set_child(m_mgrservant->getObjRef());
        //        m_mgrservant->set_owner(mgr);
      }

    return true;
  }
  
  /*!
   * @if jp
   * @brief NamingManager の終了処理
   * @else
   * @brief NamingManager finalization
   * @endif
   */
  void Manager::shutdownComponents()
  {
    RTC_TRACE(("Manager::shutdownComponents()"));
    std::vector<RTObject_impl*> comps;
    comps = m_namingManager->getObjects();
    for (int i(0), len(comps.size()); i < len; ++i)
      {
	try
	  {
	    comps[i]->exit();
	    coil::Properties p(comps[i]->getInstanceName());
	    p << comps[i]->getProperties();
            rtclog.lock();
	    rtclog.level(Logger::RTL_PARANOID) << p;
            rtclog.unlock();
	  }
	catch (...)
	  {
	    ;
	  }
      }
    for (CORBA::ULong i(0), len(m_ecs.size()); i < len; ++i)
      {
	try{
	  m_pPOA->deactivate_object(*m_pPOA->servant_to_id(m_ecs[i]));
	}
	catch (...)
	  {
	    ;
	  }
      }
  }
  
  /*!
   * @if jp
   * @brief RTコンポーネントの登録解除
   * @else
   * @brief Unregister RT-Components
   * @endif
   */
  void Manager::cleanupComponent(RTObject_impl* comp)
  {
    RTC_TRACE(("Manager::shutdownComponents()"));
    unregisterComponent(comp);
  }
  
  /*!
   * @if jp
   * @brief createComponentの引数を処理する
   * @else
   *
   * @endif
   */
  bool Manager::procComponentArgs(const char* comp_arg,
                                  coil::Properties& comp_id,
                                  coil::Properties& comp_conf)
  {
    std::vector<std::string> id_and_conf(coil::split(comp_arg, "?"));
    // arg should be "id?[conf]". id is mandatory, conf is optional
    if (id_and_conf.size() != 1 && id_and_conf.size() != 2)
      {
        RTC_ERROR(("Invalid arguments. Two or more '?' in arg : %s", comp_arg));
        return false;
      }
    if (id_and_conf[0].find(":") == std::string::npos)
      {
        id_and_conf[0].insert(0, "RTC:::");
        id_and_conf[0] += ":";
      }
    std::vector<std::string> id(coil::split(id_and_conf[0], ":"));

    // id should be devided into 1 or 5 elements
    // RTC:[vendor]:[category]:impl_id:[version] => 5
    if (id.size() != 5) 
      {
        RTC_ERROR(("Invalid RTC id format.: %s", id_and_conf[0].c_str()));
        return false;
      }

    const char* prof[] =
      {
        "RTC", "vendor", "category", "implementation_id", "version"
      };

    if (id[0] != prof[0])
      {
        RTC_ERROR(("Invalid id type: %s", id[0].c_str()));
        return false;
      }
    for (int i(1); i < 5; ++i)
      {
        comp_id[prof[i]] = id[i];
        RTC_TRACE(("RTC basic propfile %s: %s", prof[i], id[i].c_str()));
      }

    if (id_and_conf.size() == 2)
      {
        std::vector<std::string> conf(coil::split(id_and_conf[1], "&"));
        for (int i(0), len(conf.size()); i < len; ++i)
          {
            std::vector<std::string> keyval(coil::split(conf[i], "="));
            comp_conf[keyval[0]] = keyval[1];
            RTC_TRACE(("RTC property %s: %s", keyval[0].c_str(), keyval[1].c_str()));
          }
      }
    return true;
  }

  bool Manager::procContextArgs(const char* ec_args,
                                std::string& ec_id,
                                coil::Properties& ec_conf)
  {
    std::vector<std::string> id_and_conf(coil::split(ec_args, "?"));
    if (id_and_conf.size() != 1 && id_and_conf.size() != 2)
      {
        RTC_ERROR(("Invalid arguments. Two or more '?' in arg : %s", ec_args));
        return false;
      }
    if (id_and_conf[0].empty())
      {
        RTC_ERROR(("Empty ExecutionContext's name"));
        return false;
      }
    ec_id =id_and_conf[0];
    
    if (id_and_conf.size() == 2)
      {
        std::vector<std::string> conf(coil::split(id_and_conf[1], "&"));
        for (int i(0), len(conf.size()); i < len; ++i)
          {
            std::vector<std::string> k(coil::split(conf[i], "="));
            ec_conf[k[0]] = k[1];
            RTC_TRACE(("EC property %s: %s", k[0].c_str(), k[1].c_str()));
          }
      }
    return true;
  }
  
  /*!
   * @if jp
   * @brief RTコンポーネントのコンフィギュレーション処理
   * @else
   *
   * @endif
   */
  void Manager::configureComponent(RTObject_impl* comp, const coil::Properties& prop)
  {
    std::string category(comp->getCategory());
    std::string type_name(comp->getTypeName());
    std::string inst_name(comp->getInstanceName());
    
    std::string type_conf(category + "." + type_name + ".config_file");
    std::string name_conf(category + "." + inst_name + ".config_file");
    
    
    coil::Properties type_prop, name_prop;
    
    // Load "category.instance_name.config_file"
    if (!m_config[name_conf].empty())
      {
	std::ifstream conff(m_config[name_conf].c_str());
	if (!conff.fail())
	  {
	    name_prop.load(conff);
	  }
      }
    
    if (!m_config[type_conf].empty())
      {
	std::ifstream conff(m_config[type_conf].c_str());
	if (!conff.fail())
	  {
	    type_prop.load(conff);
	  }
      }
    // Merge Properties. type_prop is merged properties
    comp->getProperties() << prop;
    type_prop << name_prop;
    comp->getProperties() << type_prop;
    
    //------------------------------------------------------------
    // Format component's name for NameService
    std::string naming_formats;
    coil::Properties& comp_prop(comp->getProperties());
    
    naming_formats += m_config["naming.formats"];
    naming_formats += ", " + comp_prop["naming.formats"];
    naming_formats = coil::flatten(coil::unique_sv(coil::split(naming_formats, ",")));
    
    std::string naming_names;
    naming_names = formatString(naming_formats.c_str(), comp->getProperties());
    comp->getProperties()["naming.formats"] = naming_formats;
    comp->getProperties()["naming.names"] = naming_names;
  }
  
  /*!
   * @if jp
   * @brief プロパティ情報のマージ
   * @else
   * @brief Merge property information
   * @endif
   */
  bool Manager::mergeProperty(coil::Properties& prop, const char* file_name)
  {
    if (file_name == NULL)
      {
	RTC_ERROR(("Invalid configuration file name."));
	return false;
      }
    if (file_name[0] != '\0')
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
  
  /*!
   * @if jp
   * @brief NamingServer に登録する際の登録情報を組み立てる
   * @else
   * @brief Construct registration information when registering to Naming server
   * @endif
   */
  std::string Manager::formatString(const char* naming_format,
				    coil::Properties& prop)
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
	else if (c == '$')
	  {
	    count = 0;
	    ++it;
	    if (*it == '{' || *it == '(')
	      {
		++it;
		std::string env;
		for ( ; it != it_end && (*it) != '}' && (*it) != ')'; ++it)
		  {
		    env += *it;
		  }
		char* envval = coil::getenv(env.c_str());
		if (envval != NULL) str += envval;
	      }
	    else
	      {
		str.push_back(c);
	      }
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
		else if (c == 'h')  str += m_config["manager.os.hostname"];
		else if (c == 'M')  str += m_config["manager.name"];
		else if (c == 'p')  str += m_config["manager.pid"];
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
