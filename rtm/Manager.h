// -*- C++ -*-
/*!
 * @file Manager.h
 * @brief RTComponent manager class
 * @date $Date: 2006-10-25 17:28:05 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: Manager.h,v 1.2 2006-10-25 17:28:05 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.1  2006/10/17 10:21:24  n-ando
 * The first commitment.
 *
 *
 */

#ifndef Manager_h
#define Manager_h

#include <iostream>
#include <string>
#include <vector>

#include <ace/Synch.h>

#include <rtm/Factory.h>
#include <rtm/ObjectManager.h>

class Properties;
namespace RTC
{
  class RtcBase
  {
  public:
    const char* instance_id();
  };
};


namespace RTC
{

  class ModuleManager;

  class Manager
  {
  protected:
    Manager(){};
    Manager(const Manager& manager){};
      //      Manager& operator=(const Manager& manager){return manager;};
    
  public:
    /*!
     * @if jp
     * @brief マネージャの初期化
     *
     * マネージャを初期化する static メンバ関数。
     * マネージャをコマンドライン引数を与えて初期化する。
     * マネージャを使用する場合は、必ずこの初期化メンバ関数 init() を
     * 呼ばなければならない。
     * マネージャのインスタンスを取得する方法として、init(), instance() の
     * 2つの static メンバ関数が用意されているが、初期化はinit()でしか
     * 行われないため、Manager の生存期間の一番最初にはinit()を呼ぶ必要がある。
     *
     * @param argc コマンドライン引数の数
     * @param argv コマンドライン引数
     * 
     * @else
     * @brief Initializa manager
     *
     * This is the static member function to tintialize the Manager.
     * The Manager is initialized by given arguments.
     * At the starting the manager, this static member function "must" be
     * called from application program. The manager has two static functions
     * to get the instance, "init()" and "instance()". Since initializing
     * process is only performed by the "init()" function, the "init()" has
     * to be called at the beginning of the lifecycle of the Manager.
     * function.
     *
     * @param argc The number of command line argument. 
     * @param argv The array of the command line arguments.
     *
     * @endif
     */ 
    static Manager* init(int argc, char** argv);


    /*!
     * @if jp
     * @brief マネージャのインスタンスの取得
     *
     * マネージャのインスタンスを取得する static メンバ関数。
     * この関数を呼ぶ前に、必ずこの初期化メンバ関数 init() が呼ばれている
     * 必要がある。
     *
     * @return Manager の唯一のインスタンスの参照
     * 
     * @else
     *
     * @brief Get instance of the manager
     *
     * This is the static member function to get the instance of the Manager.
     * Before calling this function, ensure that the initialization function
     * "init()" is called.
     *
     * @return The only instance reference of the manager
     *
     * @endif
     */ 
    static Manager& instance();


    //============================================================
    // Module management
    //============================================================
    /*!
     * @if jp
     * @brief モジュールのロード
     *
     * コンポーネントのモジュールをロードして初期化関数を実行する。
     *
     * @param fname   モジュールファイル名
     * @param initfunc 初期化関数名
     * 
     * @else
     * @brief Load module
     *
     * Load module (shared library, DLL etc..) by file name,
     * and invoke initialize function.
     *
     * @param fname    The module file name
     * @param initfunc The initialize function name
     *
     * @endif
     */  
    void load(const char* fname, const char* initfunc);


    /*!
     * @if jp
     *
     * @brief モジュールのアンロード
     *
     * モジュールをアンロードする
     *
     * @param fname モジュールのファイル名
     * 
     * @else
     *
     * @brief Unload module
     *
     * Unload shared library.
     *
     * @param pathname Module file name
     *
     * @endif
     */ 

    void unload(const char* fname);


    /*!
     * @if jp
     *
     * @brief 全モジュールのアンロード
     *
     * モジュールをすべてアンロードする
     *
     * @else
     *
     * @brief Unload module
     *
     * Unload all loaded shared library.
     *
     * @endif
     */ 
    void unloadAll();
    

    /*!
     * @if jp
     * @brief ロード済みのモジュールリストを取得する
     * @else
     * @brief Get loaded module names
     * @endif
     */
    std::vector<std::string> Manager::getLoadedModules();
    

    /*!
     * @if jp
     * @brief ロード可能なモジュールリストを取得する
     * @else
     * @brief Get loadable module names
     * @endif
     */
    std::vector<std::string> getLoadableModules();

    //============================================================
    // Component Factory Management
    //============================================================
    /*!
     * @if jp
     * @brief RTコンポーネントファクトリを登録する
     * @else
     * @brief Register RT-Component Factory
     * @endif
     */
    bool registerFactory(Properties profile,
			 RtcNewFunc new_func,
			 RtcDeleteFunc delete_func);
    
    std::vector<std::string> getModulesFactories();
    
    //============================================================
    // Component management
    //============================================================
    RtcBase* createComponent(const char* module_name);

    bool registerComponent(RtcBase* comp);
    
    void deleteComponent(const char* instance_name);
    

    RtcBase* getComponent(const char* instance_name);
    
    std::vector<RtcBase*> getComponents();
    

  protected:
    void _init(int argc, char** argv);
    
    static Manager* manager;
    static ACE_Thread_Mutex mutex;
    
    
    
    Properties* m_config;
    ModuleManager* m_module;
    
    struct InstanceName
    {
      InstanceName(RtcBase* comp) : m_name(comp->instance_id()) {};
      InstanceName(const char* name) : m_name(name) {};
      bool operator()(RtcBase* comp)
      {
	return m_name == comp->instance_id();
      }
      std::string m_name;
    };

    typedef ObjectManager<std::string,
			  RtcBase,
			  InstanceName> ComponentManager;
    ComponentManager m_component;

    struct FactoryPredicate
    {
      FactoryPredicate(const char* name) : m_name(name){};
      FactoryPredicate(FactoryBase* factory)
	: m_name(factory->profile().getProperty("name")) {};
      bool operator()(FactoryBase* factory)
      {
	return m_name == factory->profile().getProperty("name");
      }
      std::string m_name;
    };
      
    typedef ObjectManager<const char*,
			  FactoryBase,
			  FactoryPredicate> FactoryManager;
    FactoryManager m_factory;

    struct ModuleFactories
    {
      void operator()(FactoryBase* f)
      {
	modlist.push_back(f->profile().getProperty("name"));
      }
      std::vector<std::string> modlist;
    };

  };
};

#endif // Manager_h
