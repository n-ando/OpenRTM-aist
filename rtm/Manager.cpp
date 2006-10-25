// -*- C++ -*-
/*!
 * @file Manager.h
 * @brief RTComponent manager class
 * @date $Date: 2006-10-25 17:27:57 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2003-2005
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: Manager.cpp,v 1.2 2006-10-25 17:27:57 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.1  2006/10/17 10:21:17  n-ando
 * The first commitment.
 *
 *
 */


#include <rtm/Manager.h>
#include <rtm/ManagerConfig.h>
#include <rtm/Properties.h>
#include <rtm/ModuleManager.h>


namespace RTC
{
  Manager* Manager::manager = 0;
  ACE_Thread_Mutex Manager::mutex;
  
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
	    manager->_init(argc, argv);
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
	  }
      }
    return *manager;
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
    return m_module->getLoadableModules();
  }

  //============================================================
  // Component factory management
  //============================================================
  bool Manager::registerFactory(Properties profile,
				RtcNewFunc new_func,
				RtcDeleteFunc delete_func)
  {
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


  std::vector<std::string> Manager::getModulesFactories()
  {
    ModuleFactories m;
    m_factory.for_each(m);
    return m.modlist;
  }


  void Manager::deleteComponent(const char* instance_name)
  {
    RtcBase* comp;
    //    comp = m_component.find(instance_name);

    //    m_naming->unregister(comp);
    //    m_activator->deactivate(comp);

    //    comp->finalize();
    //    m_component->unregisterObject(instance_name);
    delete comp;
  }

  //============================================================
  // Component management
  //============================================================
  RtcBase* Manager::createComponent(const char* module_name)
  {
    RtcBase* comp;
    comp = m_factory.find(module_name)->create(this);
    registerComponent(comp);
    return comp;
  }


  bool Manager::registerComponent(RtcBase* comp)
  {
    m_component.registerObject(comp);
    //    m_activator->activate(comp);
    //    m_naming->registerObject(comp);
    return true;
  }


  RtcBase* Manager::getComponent(const char* instance_name)
  {
    //    return m_component->find(instance_name);
  }


  std::vector<RtcBase*> Manager::getComponents()
  {
    return m_component.getObjects();
  }



  
  void Manager::_init(int argc, char** argv)
  {
    ManagerConfig config(argc, argv);
    m_config = new Properties(config.init());
    m_module = new RTC::ModuleManager(*m_config);


  }


};
