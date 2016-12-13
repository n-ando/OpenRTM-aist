// -*- C++ -*-
/*!
 * @file RtcManager.cpp
 * @brief RT component manager class
 * @date $Date: 2005-09-07 05:13:34 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2003-2005
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: RtcManager.cpp,v 1.4 2005-09-07 05:13:34 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.3  2005/05/27 07:33:20  n-ando
 * - InPort/OutPort interface was changed.
 *   subscribe/unsubscribe were completely changed.
 *
 * Revision 1.2  2005/05/16 06:18:38  n-ando
 * - Define ACE_HAS_WINSOCK2 for Windows.
 * - Some sleep was added in RtcManager::runManager() main loop.
 *   The ORB's "perform_work" main loop needs a few us sleep.
 * - RtcManager's activation method was changed from "this->_this()" to
 *   "m_pPOA->activate_object(this)".
 *   Implicit object activation by using _this() is not recommended.
 *
 * Revision 1.1.1.1  2005/05/12 09:06:18  n-ando
 * Public release.
 *
 *
 */

#ifdef WIN32
#define ACE_HAS_WINSOCK2 0
#endif //WIN32

#include <iostream>
#include <stdlib.h>
#include <boost/regex.hpp>

// ACE includes
#include <ace/Thread.h>
#include <ace/Trace.h>

// RTM includes
#include "rtm/config_rtc.h"
#include "rtm/RtcManager.h"
#include "rtm/RtcNaming.h"
#include "rtm/RtcConfig.h"


RTM::RtcManager* g_pMgr;

static sig_atomic_t g_mgrActive = true;
extern "C" void handler (int)
{
  g_mgrActive = false;
}



namespace RTM
{
  using namespace std;
  
  //------------------------------------------------------------
  // RtcManager(): Constructor
  //------------------------------------------------------------
  RtcManager::RtcManager(int argc, char** argv)
    : m_apConfig(new RtcConfig(argc, argv)),
      m_apNaming(new RtcNaming),
	  m_Logbuf(), m_MedLogbuf(m_Logbuf), rtcout(m_MedLogbuf)
  {
    // ORB have to be initilialized  to use ORB function
    // ex. RtcNaming, POA, POAManager
    if (!initORB()) { 
      cerr << "Error: initORB()" << endl;
	  exit(1);
    } 

    //! POA have to be initialized to use POA
    //! ex. activate RtcManager servant
    if (!initPOA()) {
      cerr << "Error: initPOA()" << endl;
	  exit(1);
    }
	ACE_Trace::start_tracing();

	m_SigIntAction = new ACE_Sig_Action((ACE_SignalHandler) handler, SIGINT);
	//	m_SigHupAction = new ACE_Sig_Action((ACE_SignalHandler) handler, SIGHUP);
	//	m_SigKillAction = new ACE_Sig_Action((ACE_SignalHandler) handler, SIGKILL);
	//	m_SigSegvAction = new ACE_Sig_Action((ACE_SignalHandler) handler, SIGSEGV);

	// Set manager name
    m_ManagerName = string("Manager") + m_apConfig->getPid();


	// Initialize system logger
	if (!initLogger())
	  {
		cerr << "error: activateManager()" << endl;
	  }
  }
  
  //------------------------------------------------------------
  // ~RtcManager(): destructor
  //------------------------------------------------------------
  RtcManager::~RtcManager()
  {
	RTC_TRACE(("~RtcManager()"));

	if (m_pORB != NULL)
	  {
		m_pORB->shutdown(true);
	  }
  }

  void RtcManager::shutdown()
  {
	RTC_TRACE(("RtcManager::shutdown()"));
	shutdownAllComponents();

	m_apNaming->destroyManagerContext();
	
	return;
  }

  
  int RtcManager::open(void *args)
  {
	RTC_TRACE(("RtcManager::open()"));

	activate();

	return 0;;
  }

  int RtcManager::svc(void)
  {
	RTC_TRACE(("RtcManager::svc()"));

	runManager();

	return 0;
  }
  int RtcManager::close(unsigned long flags)
  {
	RTC_TRACE(("RtcManager::close()"));

	return 0;
  }

  //============================================================
  //
  // <<< CORBA interfaces >>>
  //
  //============================================================
  
  /*!------------------------------------------------------------
   * [CORBA interface] load module
   * @brief Load shared library of a component by path name,
   *        and invoke initialize function.
   *------------------------------------------------------------*/
  RtmRes RtcManager::load(const char* libname, const char* initfunc)
  {
	RTC_TRACE(("RtcManager::load(%s, %s)", libname, initfunc));
    string path(libname);
	string tmp_initfunc(initfunc);
    string full_path;
	
    if (!findPath(path, full_path))
      {
		RTC_ERROR(("Could not find component.", full_path.c_str()));
		// invalid libname
		return RTM_ERR;
      }
	
    string initfunc_name;
	if (tmp_initfunc.size() == 0)
	  {
		libnameToInitFunc(libname, initfunc, initfunc_name);
	  }
	else
	  {
		initfunc_name = tmp_initfunc;
	  }
	RTC_DEBUG(("Init function name: %s", initfunc_name.c_str()));
	
    // Open shared object (or DLL)
    int retval =  m_Lib[full_path]._dll.open(full_path.c_str());
	
    if (retval != 0)
      ACE_ERROR_RETURN ((LM_ERROR, "%p", "dll.open"), RTM_ERR);

    RtcComponentInit init_func;
	const char* c = initfunc_name.c_str();
    init_func = (RtcComponentInit) m_Lib[full_path]._dll.symbol(c);

    if (init_func == NULL)
      ACE_ERROR_RETURN ((LM_ERROR, "%p", "dll.symbol"), RTM_ERR);

    // Call component initialize function
    if (init_func(this))
      {
		RTC_DEBUG(("Init function( %s ) of %s was invoked.",
				   initfunc_name.c_str(), full_path.c_str()));
		return RTM_OK;
      }
	
	RTC_ERROR(("Init function( %s ) of %s was failed.",
			   initfunc_name.c_str(), full_path.c_str()));

    return RTM_ERR;
  }
  
  
  /*!------------------------------------------------------------
   * [CORBA interface] unload module
   * @brief Unload component shared object file
   *------------------------------------------------------------*/
  RtmRes RtcManager::unload(const char* pathname)
  {
    RTC_TRACE(("RtcManager::unload()"));

    return RTM_OK;
  }
  
  
  /*!------------------------------------------------------------
   * [CORBA interface] create_component
   * @brief Instansiate a component
   *------------------------------------------------------------*/
  RTCBase_ptr RtcManager::create_component(const char* module_name,
										   const char* category_name,
										   CORBA::String_out component_name)
  {
	RTC_TRACE(("RtcManager::create_component(%s, %s)",
			   module_name, category_name));
	string comp_name;
	RtcBase* comp = createComponent(string(module_name),
									string(category_name),
									comp_name);

    component_name = CORBA::string_dup(comp_name.c_str());
	RTC_DEBUG(("Component instance name is %s", comp_name.c_str()));

	// added 2004.11.7
	//	CORBA::PolicyList policies;
	//	policies.length(0);
	//	PortableServer::POAManager_var rootManager = m_pPOA->the_POAManager(); 
	//	PortableServer::POA_var pPOA;
	//	pPOA = m_pPOA->create_POA(comp_name.c_str(),
	//							   NULL, policies);


	if (comp != NULL)
	  {
		CORBA::Object_ptr obj = m_pPOA->servant_to_reference(comp);

		//		m_pPOA->the_POAManager()->activate();		
		RTC_DEBUG(("RtcManager::create_component(%s, %s) succeed.",
				   module_name, category_name));
		return RTCBase::_narrow(obj);
	  }
	else
	  {
		RTC_ERROR(("RtcManager::create_component() was waild."));
		return RTCBase::_nil();
	  }

	RTC_ERROR(("never come here."));
	return RTCBase::_nil();
  }
  
  
  //------------------------------------------------------------
  // delete_component: Delete component instance by instance name
  //------------------------------------------------------------
  RtmRes RtcManager::delete_component(const char* instance_name,
									  const char* category_name)
  {
	RTC_TRACE(("RtcManager::delete_component(%s, %s)",
			   instance_name, category_name));

    // delete component instance
	ACE_Guard<ACE_Thread_Mutex> guard(m_Components._mutex);
	m_Components._map[category_name][instance_name]->rtc_exit();
	
    return true;
  }
  
  
  //------------------------------------------------------------
  // component_factory_list: return component factory list
  //------------------------------------------------------------
  RTCFactoryList* RtcManager::factory_list()
  {
	RTC_TRACE(("RtcManager::factory_list()()"));

	ACE_Guard<ACE_Thread_Mutex> guard(m_FactoryMap._mutex);
	
	std::map<std::string, std::map<std::string, RtcFactoryBase*> >::iterator cat_it, cat_it_end;
	std::map<std::string, RtcFactoryBase*>::iterator comp_it, comp_it_end;

	cat_it     = m_FactoryMap._map.begin();
	cat_it_end = m_FactoryMap._map.end();
	int cnt(0);
	while (cat_it != cat_it_end)
	  {
		comp_it = (cat_it->second).begin();
		comp_it_end = (cat_it->second).end();

		while (comp_it != comp_it_end)
		  {
			++cnt;
			++comp_it;
		  }
		++cat_it;
	  }
	RTCFactoryList_var factory_list = new RTCFactoryList();
	factory_list->length(cnt);

	cnt = 0;
	cat_it     = m_FactoryMap._map.begin();
	while (cat_it != cat_it_end)
	  {
		comp_it = (cat_it->second).begin();
		comp_it_end = (cat_it->second).end();

		while (comp_it != comp_it_end)
		  {
			factory_list[cnt].name = CORBA::string_dup(comp_it->first.c_str());
			factory_list[cnt].category
			  = CORBA::string_dup(cat_it->first.c_str());
			++cnt;
			++comp_it;
		  }
		++cat_it;
	  }

    return factory_list._retn();
  }
  
  
  //------------------------------------------------------------
  // component_list: return component instance list
  //------------------------------------------------------------
  RTCBaseList* RtcManager::component_list()
  {
	RTC_TRACE(("RtcManager::component_list()()"));
	std::map<std::string,std::map<std::string, RtcBase*> >::iterator it_cat;
	std::map<std::string,std::map<std::string, RtcBase*> >::iterator it_cat_end;
	it_cat     = m_Components._map.begin();
	it_cat_end = m_Components._map.end();

	int cnt(0);
	while (it_cat != it_cat_end)
	  {
		map<string, RtcBase*>::iterator it_cmp;
		map<string, RtcBase*>::iterator it_cmp_end;
		it_cmp     = (it_cat->second).begin();
		it_cmp_end = (it_cat->second).end();

		while (it_cmp != it_cmp_end)
		  {
			++it_cmp;
			++cnt;
		  }
		++it_cat;
	  }

	RTCBaseList_var comp_list = new RTCBaseList();
	comp_list->length(cnt);

	cnt = 0;
	while (it_cat != it_cat_end)
	  {
		map<string, RtcBase*>::iterator it_cmp;
		map<string, RtcBase*>::iterator it_cmp_end;
		it_cmp     = (it_cat->second).begin();
		it_cmp_end = (it_cat->second).end();

		while (it_cmp != it_cmp_end)
		  {
			comp_list[cnt] = RTCBase::_narrow(getPOA()->servant_to_reference(it_cmp->second));
			++it_cmp;
			++cnt;
		  }
		++it_cat;
	  }

    return comp_list._retn();
  }
  
  
  //------------------------------------------------------------
  // command: Simple command interpreter
  //------------------------------------------------------------
  RtmRes RtcManager::command(const char* cmd, CORBA::String_out ret)
  {
    //  boost::reg_expression<char>
	//cmd_regex("([[:graph:]]+)[[:space:]]+([[:print:]]*?)");
    boost::regex args_regex("[[:space:]]",
							boost::regbase::normal | boost::regbase::icase);
    //  boost::match_results<const char*> match_results;
    vector<string>::iterator it;
    vector<string>::iterator it_end;
	
    vector<string> arglist;
    vector<string> retlist;
	
    RTC_DEBUG(("Command received: %s", cmd));
	
    string s(cmd);
	
    if (boost::regex_split(back_inserter(arglist), s, args_regex))
	  {
		// boost::regex_match(s, match_results, cmd_regex) ) {
		
		
		//! arg0          arg1 arg2 ....
		//! command_name [arglist]......
		string command_name(arglist[0]);
		arglist.erase(arglist.begin());
		
		it = arglist.begin();
		it_end = arglist.end();
#ifndef NO_LOGGING
		rtcout.level(RtcLogStream::RTL_DEBUG) << "Command: " << command_name;
		rtcout.level(RtcLogStream::RTL_DEBUG) << "Args: ";

		while (it != it_end)
		  {
			rtcout.level(RtcLogStream::RTL_DEBUG) << *it << endl;
			++it;
		  }
#endif
		
		//! Command invokation
		if (m_CmdMap.find(command_name) != m_CmdMap.end()) {
		  bool r  = (m_CmdMap[command_name])(arglist, retlist);
		  RTC_DEBUG(("Retval: %s", r == true ? "true" :"false"));
		} else {
		  RTC_ERROR(("Coommand not found."));
      }
  
	  
      string ret_string;
      it = retlist.begin();
      it_end = retlist.end();
	  
      while (it != it_end)
		{
		  ret_string = ret_string + (*it) + " ";
		  ++it;
		}
	  
      ret = CORBA::string_dup(ret_string.c_str());
    }
	
    return true;
  }
  
  
  
  //============================================================
  //
  // <<< Local interfaces >>>
  //
  //============================================================
  /*!------------------------------------------------------------
   * Initialize manager
   *------------------------------------------------------------*/
  void RtcManager::initManager()
  {
    createCommand("load", boost::bind(&RtcManager::loadCmd, this, _1, _2));
    createCommand("unload", boost::bind(&RtcManager::unloadCmd, this, _1, _2));
    createCommand("createcomp", boost::bind(&RtcManager::createComponentCmd, this, _1, _2));
    createCommand("lscomp", boost::bind(&RtcManager::listComponent, this, _1, _2));
    createCommand("lsmod", boost::bind(&RtcManager::listModule, this, _1, _2));
    createCommand("?", boost::bind(&RtcManager::commandListCmd, this, _1, _2));
	
	g_pMgr = this;
  }
  
  /*!------------------------------------------------------------
   * Manager main loop
   *------------------------------------------------------------*/
  void RtcManager::runManager()
  {
	// start POA manager
	m_pPOAManager->activate();
	
	if (CORBA::is_nil(m_pORB))
	  {
		RTC_ERROR(("Invalid ORB pointer."));
		exit(1);
	  }

	//	ORB main loop
	ACE_Time_Value tv(0, 1000); // (s, us)
	while (g_mgrActive)
	  {
		if (m_pORB->work_pending())
		  {
			m_pORB->perform_work();
		  }
		else
		  {
			// ORB main loop needs some sleep.
			ACE_OS::sleep(tv);
		  }
	  }
	shutdown();

	while (m_pORB->work_pending())
	  {
		if (m_pORB->work_pending())
		  m_pORB->perform_work();
	  }
	RTC_DEBUG(("No pending works of ORB. Shutting down POA and ORB."));
	m_pPOAManager->deactivate(true, true);
	RTC_DEBUG(("POA was deactivated."));
	m_pPOA->destroy(false, false);
	RTC_DEBUG(("POA was destroid."));
	m_pORB->shutdown(false);
	RTC_DEBUG(("ORB was shutdown."));
	m_pORB->destroy();
	RTC_DEBUG(("ORB was destroied."));
  }
  
  void RtcManager::runManagerNoBlocking()
  {
	RTC_TRACE(("RtcManager::runManagerNoBlocking()"));
	open(0);
  }
  
  
  /*!------------------------------------------------------------
   * Activate RTCManager as a CORBA servant itself
   *------------------------------------------------------------*/
  bool  RtcManager::activateManager()
  {
	RTC_TRACE(("RtcManager::activateManager()"));

    // Naming Object initialization
	RTC_DEBUG(("Name server: ", m_apConfig->getNameServer().c_str()));
	m_apNaming->initNaming(m_pORB);

    //! Create naming context of host layer
    bool retval;
    retval = m_apNaming->createHostContext(m_apConfig->getHostname().c_str());
    if (retval == false)
	  {
		RTC_ERROR(("Could not create host context on the Naming server: %s",
				   m_apConfig->getNameServer().c_str()));
		return false;
	  }

    retval = m_apNaming->createManagerContext(m_ManagerName);
    if (retval == false)
	  {
		RTC_ERROR(("Could not create manager context on the Naming server: %s",
				   m_apConfig->getNameServer().c_str()));
		return false;
	  }

    m_pPOA->activate_object(this);
	CORBA::Object_var obj = m_pPOA->servant_to_reference(this);
    retval = m_apNaming->bindManager(m_ManagerName, obj);

    if (retval == false)
	  {
		RTC_ERROR(("Could not bind manager object to the Naming server: %s",
				   m_apConfig->getNameServer().c_str()));
		return false;
	  }
	/*
	if (initMasterLogger())
	  {
		RTC_ERROR(("Could not initialize master logger"));
		return false;
	  }
	*/
    return true;
  }


  void RtcManager::initModuleProc(RtcModuleInitProc proc)
  {
	RTC_TRACE(("RtcManager::initModuleProc()"));

	proc(this);
  }
	

  
  /*------------------------------------------------------------
   * Create command on the command interpreter
   *------------------------------------------------------------*/
  bool RtcManager::createCommand(string cmdName, RtcMgrCmd rtcCmd)
  {
	RTC_TRACE(("RtcManager::createCommand( %s )", cmdName.c_str()));

    if (m_CmdMap.count(cmdName) > 0)
	  {
		m_CmdMap[cmdName] = rtcCmd;
	  }
	else 
	  {
		m_CmdMap[cmdName] = rtcCmd;
	  }
    return true;
  }
  
  
  /*------------------------------------------------------------
   * RegisterComponent
   *------------------------------------------------------------*/
  bool RtcManager::registerComponent(RtcModuleProfile& profile,
									 RtcNewFunc new_func,
									 RtcDeleteFunc delete_func)
  {
	RtcFactoryCXX* factory = new RtcFactoryCXX(profile, new_func, delete_func);
	
    return registerComponent(factory);
  }

  
  bool RtcManager::registerComponent(RtcFactoryBase* factory)
  {
	if (factory == NULL)
	  {
		return false;
	  }

	// Get implementation_id and category from given profile in the factory.
	RtcModuleProfile profile;
	profile = factory->profile();
	string impl_id(profile.getImplementationId());
	string category(profile.getCategory());
	
	ACE_Guard<ACE_Thread_Mutex> guard(m_FactoryMap._mutex);

    // Category/Module name should be unique.
    if (m_FactoryMap._map.find(category) != m_FactoryMap._map.end())
	  {
		if (m_FactoryMap._map[category].find(impl_id) 
			!= m_FactoryMap._map[category].end())
		  {
			return false;
		  }
	  }
	
    m_FactoryMap._map[category][impl_id] = factory;
	
    // Create naming context of category and module
    m_apNaming->createCategoryContext(category);
    m_apNaming->createModuleContext(profile.getImplementationId(), category);
	
    //! If component type is Static, instantiate MaxInstance objects.
    if (profile.getComponentType() == STATIC)
	  {
		int i;
		for (i = 0; i < profile.getMaxInstance(); ++i)
		  {
			char* instance_name;
			create_component(impl_id.c_str(), category.c_str(), instance_name);
			CORBA::string_free(instance_name);
		  }
	  }
	
    return true;
  }



  RtcBase* RtcManager::createComponent(const string& module_name,
									   const string& category_name,
									   string& comp_name)
  {
	RTC_TRACE(("RtcManager::createComponent(%s, %s)",
			   module_name.c_str(), category_name.c_str()));

    ACE_Guard<ACE_Thread_Mutex> guard(m_FactoryMap._mutex);

    //! Instantiate a component by module name (comp_name)
    //! _new is Factory function of the "Component Object"
	if (m_FactoryMap._map.find(category_name) == m_FactoryMap._map.end())
	  {
		RTC_ERROR(("No category of the module: %s", category_name.c_str()));
		return NULL;
	  }
	else
	  {
		if (m_FactoryMap._map[category_name].find(module_name)
			== m_FactoryMap._map[category_name].end())
		  {
			RTC_ERROR(("No module: %s", module_name.c_str()));
			return NULL;
		  }
	  }

	
	RtcFactoryBase* factory = m_FactoryMap._map[category_name][module_name];

	// current number of component: factory->number() + 1
	if ((factory->number() + 1) >= factory->profile().getMaxInstance())
	  {
		RTC_ERROR(("No more component cannot be created."));
		return NULL;
	  }

    RtcBase* comp;
	comp = factory->create(this);
	
	// Pass the module profile to created component
	comp->initModuleProfile(factory->profile());

    // Create component instance name and set propery itself.
	comp_name = comp->setComponentName(factory->number());
	string category(factory->profile().getCategory());

	{
	  ACE_Guard<ACE_Thread_Mutex> guard(m_Components._mutex);
	  m_Components._map[category][comp_name] = comp;
	}

	PortableServer::ObjectId_var id;
	id = m_pPOA->activate_object(comp);
	
    // Bind component object on the Naming Server
    // at a category that the component belongs at.
	comp->_this();
	if (comp->isLongNameEnable())
	  {
		m_apNaming->bindComponent(comp_name, module_name, category,
								  m_pPOA->servant_to_reference(comp));
	  }

	// Bind the component on alias at naming server
	if (comp->isAliasEnable())
	  {
		std::list<std::string>::iterator it, it_end;
		std::list<string> aliases = comp->getAliases();
		it     = aliases.begin();
		it_end = aliases.end();
		while (it != it_end)
		  {
			CORBA::Object_var obj = m_pPOA->servant_to_reference(comp);
			m_apNaming->bindObjectByFullPath(*it, obj);
			++it;
		  }
	  }

	{
	  ACE_Guard<ACE_Thread_Mutex> guard(m_Components._mutex);
	  m_Components._map[category][comp_name]->open(0);
	}

    return m_Components._map[category][comp_name];
  }  

  
  RtcBase* RtcManager::createComponent(const string& module_name,
									   const string& category_name)
  {
	RTC_TRACE(("RtcManager::createComponent(%s, %s)",
			   module_name.c_str(), category_name.c_str()));
	std::cout << "======================================================================" << std::endl;
	std::cout << " The calling method \"createComponent(module_name, instance_name)\"  "  << std::endl;
	std::cout << " is already obsolete!!! This method will disappear soon. Don't use it." << std::endl;
	std::cout << std::endl;
	std::cout << " Please use the following method instead:" <<std::endl;
	std::cout << "" <<std::endl;
	std::cout << " createComponent(module_name, category_name, instance_name)" << std::endl;
	std::cout << "" <<std::endl;
	std::cout << " module_name  : Input value. Set component's module name." << std::endl;
	std::cout << " category_name: Input value. Set component's category." << std::endl;
	std::cout << " instance_name: Output value. Set empty string object." << std::endl;
	std::cout << "======================================================================" <<std::endl;
	exit(0);
    string comp_name;
    return createComponent(module_name, category_name, comp_name);
  }


  void RtcManager::cleanupComponent(const string& instance_name,
									const string& category_name)
  {
	RTC_TRACE(("RtcManager::cleanupComponent(%s, %s)",
			   instance_name.c_str(), category_name.c_str()));

	ACE_Guard<ACE_Thread_Mutex> guard(m_Components._mutex);

	if (m_Components._map.count(category_name) > 0 &&
		m_Components._map[category_name].count(instance_name) > 0)
	  {
		RtcBase* comp;
		comp = m_Components._map[category_name][instance_name];
		std::string module_name(comp->getModuleProfile().getImplementationId());

		m_apNaming->unbindLocalComponent(category_name, 
										 module_name,
										 instance_name);
		std::list<std::string> aliases;
		aliases = comp->getAliases();
		if (aliases.size() > 0)
		  {
			std::list<std::string>::iterator it, it_end;
			it     = aliases.begin();
			it_end = aliases.end();

			while (it != it_end)
			  {
				RTC_DEBUG(("Delete alias: %s", (*it).c_str()));
				m_apNaming->unbindObjectByFullPath((*it));
				++it;
			  }
		  }
		m_Components._map[category_name].erase(instance_name);
		//		delete comp;
	  }

	RTC_DEBUG(("Cleanup component done."));
	return;
  }


  std::vector<RTCBase_ptr>
  RtcManager::findComponents(const string& comp_name)
  {
	RTC_TRACE(("RtcManager::findComponents( %s )", comp_name.c_str()));
	std::vector<RTCBase_ptr> comps;
	ObjectList objs;

	m_apNaming->findComponents(comp_name, objs);

	std::vector<CORBA::Object_ptr>::iterator it, it_end;
	it     = objs.begin();
	it_end = objs.end();

	for (it = objs.begin(); it != it_end; ++it)
	  {
		RTCBase_ptr tmp = RTCBase::_narrow(*it);
		if (!CORBA::is_nil(tmp))
		  {
			comps.push_back(tmp);
		  }
	  }
	return comps;
  }


  std::string RtcManager::bindInOut(RTCBase_ptr comp_in,
				    const std::string& inp_name,
				    RTCBase_ptr comp_out,
				    const std::string& outp_name,
				    RTM::SubscriptionType sub_type)
  {
	RTC_TRACE(("RtcManager::bindInOut(%s, %s, %s, %s)",
			   comp_in->instance_id(), inp_name.c_str(),
			   comp_out->instance_id(), outp_name.c_str()));

	InPort_ptr inpt;
	OutPort_ptr outpt;
	
	inpt  = comp_in->get_inport(inp_name.c_str());
	if (CORBA::is_nil(inpt)) return std::string("");
	outpt = comp_out->get_outport(outp_name.c_str());
	if (CORBA::is_nil(outpt)) return std::string("");

	char* uuid;
	RTM::SubscriptionProfile sub_prof;
	sub_prof.subscription_type = sub_type;

	if (outpt->subscribe(sub_prof) != RTM::RTM_OK)
	  {
		RTC_ERROR(("Subscription error."));
		return std::string("");
	  }
	
	RTC_DEBUG(("Subscription uuid: %s", CORBA::string_dup(sub_prof.id)));

	return std::string(sub_prof.id);
  }
 
  std::string RtcManager::bindInOutByName(const std::string& comp_name_in,
					  const std::string& inp_name,
					  const std::string& comp_name_out,
					  const std::string& outp_name,
					  RTM::SubscriptionType sub_type)
  {
	RTC_TRACE(("RtcManager::bindInOutByName(%s, %s, %s, %s)",
			  comp_name_in.c_str(), inp_name.c_str(),
			   comp_name_out.c_str(), outp_name.c_str()));

    std::vector<RTCBase_ptr> incomps;
    std::vector<RTCBase_ptr> outcomps;
    incomps  = findComponents(comp_name_in);
    outcomps = findComponents(comp_name_out);
    
    if (incomps.size() == 0)
      {
		RTC_ERROR(("No component ( %s ) which has ( %s ) not found.",
				   comp_name_in.c_str(), inp_name.c_str()));
		return std::string("");
      }
    else if (incomps.size() > 1)
      {
		RTC_ERROR(("Two or more components found ( %s ).",
				   comp_name_in.c_str()));
      }

    if (outcomps.size() == 0)
      {
		RTC_ERROR(("No component ( %s ) which has ( %s ) not found",
				   comp_name_out.c_str(), inp_name.c_str()));
		return std::string("");
      }
    else if (outcomps.size() > 1)
	  {
	    RTC_ERROR(("Two or more components found ( %s ).",comp_name_out.c_str()));
	  }
    
    std::string ret;
    ret = bindInOut(incomps[0], inp_name, outcomps[0], outp_name, sub_type);
    return ret;
  }
  
  
  //============================================================
  // Commands
  
  bool RtcManager::loadCmd(const vector<string>& cmd, vector<string>& retval)
  {
    if (cmd.size() != 2)
	  {
		return false;
	  }
    load(cmd[0].c_str(), cmd[1].c_str());
	
    return true;
  }
  
  
  
  bool RtcManager::unloadCmd(const vector<string>& cmd, vector<string>& retval)
  {
    if (cmd.size() != 1)
	  {
		return false;
	  }
    load(cmd[0].c_str(), cmd[1].c_str());
	
    return true;
  }
  
  bool RtcManager::createComponentCmd(const vector<string>& cmd,
								   vector<string>& retval)
  {
    if (cmd.size() != 2) {
      return false;
    }
	
    char* instance_name;
    bool ret = create_component(cmd[0].c_str(), cmd[1].c_str(), instance_name);
    retval.push_back(string(instance_name));
    return ret;
  }
  
  
  bool RtcManager::listComponent(const vector<string>& cmd,
								 vector<string>& retval)
  {
	ACE_Guard<ACE_Thread_Mutex> guard(m_Components._mutex);

	std::map<std::string,std::map<std::string, RtcBase*> >::iterator it_cat;
	std::map<std::string,std::map<std::string, RtcBase*> >::iterator it_cat_end;
	it_cat     = m_Components._map.begin();
	it_cat_end = m_Components._map.end();
	
    while (it_cat != it_cat_end)
	  {
		std::map<string, RtcBase*>::iterator it_cmp;
		std::map<string, RtcBase*>::iterator it_cmp_end;
		it_cmp     = m_Components._map[it_cat->first].begin();
		it_cmp_end = m_Components._map[it_cat->first].end();

		while (it_cmp != it_cmp_end)
		  {
			retval.push_back(it_cmp->first);
			++it_cmp;
		  }
		++it_cat;
	  }
	
    return true;
  }
  
  
  bool RtcManager::listModule(const vector<string>& cmd, vector<string>& retval)
  {
	/*
    RTC_TRACE(("listModule()"));
    map<string, RtcFactoryBase*>::iterator it = m_FactoryMap._map.begin();
    map<string, RtcFactoryBase*>::iterator it_end = m_FactoryMap._map.end();
	
    while (it != it_end)
	  {
		retval.push_back(it->first);
		++it;
	  }
	*/
    return true;
  }
  
  
  bool RtcManager::commandListCmd(const vector<string>& cmd, vector<string>& retval)
  {
    map<string, boost::function2<bool, vector<string>&, vector<string>&> >::iterator it;
	
    for (it = m_CmdMap.begin(); it != m_CmdMap.end(); ++it)
	  {
		retval.push_back(it->first);
	  }
	
    return true;
  }
  
  
  
  //============================================================
  //
  // <<< Private methods >>
  //
  //============================================================
  /*!------------------------------------------------------------
   * Initialize ORB and store ORB's reference
   *------------------------------------------------------------*/
  bool RtcManager::initORB()
  {
	RTC_TRACE(("RtcManager::initORB()"));
    // Initialize ORB
    try
	  {
		int _argc = m_apConfig->getOrbInitArgc();
		char** _argv = m_apConfig->getOrbInitArgv();
		m_pORB = CORBA::ORB_init(_argc, _argv);
	  }
    catch (...)
	  {
		RTC_ERROR(("exception: initORB(): unknown exception was caught."));
		return false;
	  }
    return true;
  }

  CORBA::ORB_var RtcManager::getORB()
  {
	RTC_TRACE(("RtcManager::getORB()"));

	return m_pORB;
  }
  
  
  /*!------------------------------------------------------------
   * Initialize POA and POA manager
   *------------------------------------------------------------*/
  bool RtcManager::initPOA()
  {
	RTC_TRACE(("RtcManager::initPOA()"));

    //------------------------------------------------------------
    // Resolve root POA initial reference and get POA manager
    CORBA::Object_var obj = m_pORB->resolve_initial_references("RootPOA");
    m_pPOA = PortableServer::POA::_narrow(obj);
    if (CORBA::is_nil(m_pPOA))
	  {
		RTC_ERROR(("Could not resolve RootPOA."));
		return false;
	  }
    m_pPOAManager = m_pPOA->the_POAManager();

	//	cerr << "POA Manager created" << endl;
    return true;
  }
  

  PortableServer::POA_var RtcManager::getPOA()
  {
	RTC_TRACE(("RtcManager::getPOA()"));

	return m_pPOA;
  }
  

  bool RtcManager::initLogger()
  {
	std::string logfile;
	m_pLoggerOutPort = new LogOutPort("logger_out", m_LoggerOut);
	m_pLogEmitter = new LogEmitter(*m_pLoggerOutPort, m_LoggerOut);

	logfile = m_apConfig->getLogFileName();
	if (logfile.size() < 1)
	  {
		logfile = "./rtm" + m_apConfig->getPid() + ".log";
	  }
	
	// Open logfile and set suffix
	m_Logbuf.open(logfile.c_str(), std::ios::out | ios::app);

	// Set suffix for logging htcBaeader.
	m_MedLogbuf.setSuffix(m_ManagerName);
	// 
	m_MedLogbuf.setDateFmt(m_apConfig->getLogTimeFormat());

	// Loglevel was set from configuration file.
	rtcout.setLogLevel(m_apConfig->getLogLevel());
	rtcout.setLogLock(m_apConfig->getLogLock());
#ifndef NO_LOGGING	
	rtcout << "OpenRTM-aist-0.2.0." << std::endl;
	rtcout << "Copyright (c) 2003-2004 OpenRTM-aist Project." << std::endl;
	rtcout << "RtcManager starting." << std::endl;
	rtcout << "Starting local logging." << std::endl;
#endif
	m_Logbuf.setSyncCallBack(*m_pLogEmitter);

	return true;
  }

  bool RtcManager::initMasterLogger()
  {
	// get master logger name from configuration
	std::string mlogger_name;
	//	mlogger_name = m_apConfig->getMasterLoggerName();
	mlogger_name = "/MasterLogger|rtc";


	// find master logger component from name server
	ObjectList mloggers;
	m_apNaming->findComponents(mlogger_name, mloggers);

	if (mloggers.size() == 0)
	  {
		RTC_DEBUG(("No MasterLogger was found. Loading MasterLogger."));
		loadMasterLogger();
		m_apNaming->findComponents(mlogger_name, mloggers);
		if (mloggers.size() == 0)
		  {
			RTC_ERROR(("Master logger was could not created."));
		  }
		return false;
	  }

	m_pMasterLogger = RTCBase::_narrow(mloggers[0]);

	InPort_var in_port = m_pMasterLogger->get_inport("logger_in");
	char* uuid;
	RTM::SubscriptionProfile sub_prof;
	sub_prof.subscription_type = RTM::OPS_NEW;
	RtmRes res = m_pLoggerOutPort->subscribe(sub_prof);

	if (res == RTM_ERR)
	  {
		RTC_ERROR(("Connection between local and master logger was failed."));
	  }

	return true;
  }


  void RtcManager::loadMasterLogger()
  {
	std::string name;
	this->load("MasterLogger.so", "MasterLoggerInit");
	this->createComponent("MasterLogger", "Service", name);

	return;
  }

  bool RtcManager::findPath(string path, string &full_path)
  {
	RTC_TRACE(("RtcManager::findPath( %s )", path.c_str()));

    full_path.erase();
	
#ifdef WIN32
    boost::regex path_regex("^[a-zA-Z]\\:\\\\.*");
#else
    boost::regex path_regex("^\\/.*");
#endif
    boost::smatch path_match;
	
    // Full path ?
    if (boost::regex_match(string(path), path_match, path_regex))
      {
		// Given pathname is full path name
		full_path = path;
		if (!ACE_OS::access(path.c_str(), F_OK))
		  {
			full_path = path;
			return true;
		  }
		return false;
      }
    else
      { // Find the file in default path list
		list<string>::iterator it = m_apConfig->getComponentLoadPath().begin();
		list<string>::iterator it_end = m_apConfig->getComponentLoadPath().end();
		
		// Search pathname in the library path list
		while (it != it_end)
		  {
			string tmp_path((*it) + "/" + path);

			if (!ACE_OS::access(tmp_path.c_str(), F_OK))
			  {
				full_path = tmp_path;

				return true;
			  }
			++it;
		  }
      }
	
    return false;
  }
  
  
  
  bool RtcManager::libnameToInitFunc(const char* libpath,
									 const char* initfunc,
									 string &initfunc_name)
  {
	RTC_TRACE(("RtcManager::libnameToInitFunc()"));

    if (libpath == NULL) return false;
	
    if (initfunc != NULL)
      {
		initfunc_name = initfunc;
		if (initfunc_name.size() > 0)
		  {
			return true;
		  }
		return false;
      }
	
    string libname(libpath);
    string::size_type pos = libname.find_last_of("/");
	
    if (pos == string::npos)
      {
		initfunc_name = libname + "Init";
		return true;
      }
	return false;
  }


  void RtcManager::shutdownAllComponents()
  {
	RTC_TRACE(("RtcManager::shutdownAllComponents()"));
	ACE_Time_Value tv(0, 1000); // (s, us)
	m_Components._mutex.acquire();

	std::map<std::string,std::map<std::string, RtcBase*> >::iterator it_cat;

	while (m_Components._map.begin() != m_Components._map.end())
	  {
		it_cat = m_Components._map.begin();

		while (   m_Components._map[it_cat->first].begin()
			   != m_Components._map[it_cat->first].end())
		  {
			map<string, RtcBase*>::iterator it_cmp;
			it_cmp     = m_Components._map[it_cat->first].begin();

			RtcBase* comp;
			comp = m_Components._map[it_cat->first].begin()->second;
			comp->rtc_kill();

			// Waiting for finishing RtcBase::forceExit()
			while (comp->getState() != RTM::RTComponent::RTC_EXITING);

			// Mutex is released for RtcManager::cleanupComponet()
			m_Components._mutex.release();
			ACE_OS::sleep(tv); // sleep 1ms
			// After here "comp" is invalid pointer to RtcBase.
			m_Components._mutex.acquire();
		  }
		m_Components._map.erase(it_cat);
	  }

	m_Components._mutex.release();
	RTC_DEBUG(("Delete all component ..... done."));
  }

		
  
}; // end of namespace RTM
