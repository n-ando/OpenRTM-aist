// -*- C++ -*-
/*!
 * @file Manager.h
 * @brief RTComponent manager class
 * @date $Date: 2007-04-26 15:36:54 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: Manager.h,v 1.9 2007-04-26 15:36:54 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.8  2007/04/23 04:53:29  n-ando
 * Component instantiation processes were divided into some functions.
 *
 * Revision 1.7  2007/04/17 09:22:08  n-ando
 * Namespace of Timer class was changed from ::Timer to RTC::Timer.
 *
 * Revision 1.6  2007/04/13 18:02:14  n-ando
 * Some configuration properties handling processes were changed.
 *
 * Revision 1.5  2007/01/21 09:54:30  n-ando
 * A trivial bug fix.
 *
 * Revision 1.4  2007/01/14 19:42:37  n-ando
 * The activate() function now performs POA manager activation and
 * invoking ModuleInitProc.
 * Debugging messages are now output to system logger.
 *
 * Revision 1.3  2006/11/06 01:31:57  n-ando
 * Some Manager's functions has been implemented.
 * - Component creation process
 * - System logger initialization
 *
 * Revision 1.2  2006/10/25 17:28:05  n-ando
 * Component factory registration and relative functions are implemented.
 *
 * Revision 1.1  2006/10/17 10:21:24  n-ando
 * The first commitment.
 *
 *
 */

#ifndef Manager_h
#define Manager_h

#include <rtm/RTC.h>

#include <iostream>
#include <string>
#include <vector>

#include <ace/Synch.h>
#include <ace/Task.h>

#include <rtm/Factory.h>
#include <rtm/ECFactory.h>
#include <rtm/ObjectManager.h>
#include <rtm/RTObject.h>
#include <rtm/SystemLogger.h>

class Properties;

namespace RTC
{
  class CorbaNaming;
  class ModuleManager;
  class NamingManager;
  class CorbaObjectManager;
  class Manager;
  class Timer;

  typedef void (*ModuleInitProc)(Manager* manager);  

  class Manager
  {
  protected:
    /*!
     * @if jp
     * @brief Protected コンストラクタ
     * @else
     * @brief Protected Constructor
     * @endif
     */
    Manager();


    /*!
     * @if jp
     * @brief Protected コピーコンストラクタ
     * @else
     * @brief Protected Copy Constructor
     * @endif
     */
    Manager(const Manager& manager);
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
     * ※マネージャの初期化処理
     * - initManager: 引数処理、configファイルの読み込み、サブシステム初期化
     * - initLogger: Logger初期化
     * - initORB: ORB 初期化
     * - initNaming: NamingService 初期化
     * - initExecutionContext: ExecutionContext factory 初期化
     * - initTimer: Timer 初期化
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
    // Manager
    //============================================================



    void terminate();
    void shutdown();
    void join();
    
    Logbuf& getLogbuf() {return m_Logbuf;}
    Properties& getConfig() { return m_config;}
    
    
    
    
    /*!
     * @if jp
     *
     * @brief 初期化プロシージャのセット
     *
     * このオペレーションはユーザが行うモジュール等の初期化プロシージャ
     * を設定する。ここで設定されたプロシージャは、マネージャが初期化され、
     * アクティブ化された後、適切なタイミングで実行される。
     *
     * @param proc 初期化プロシージャの関数ポインタ
     *
     * @else
     *
     * @brief Run the Manager
     *
     * This operation sets the initial procedure call to process module
     * initialization, other user defined initialization and so on.
     * The given procedure will be called at the proper timing after the 
     * manager initialization, activation and run.
     *
     * @param proc A function pointer to the initial procedure call
     *
     * @endif
     */
    void setModuleInitProc(ModuleInitProc proc);


    /*!
     * @if jp
     *
     * @brief Managerのアクティブ化
     *
     * このオペレーションは以下の処理を行う
     * - CORBA POAManager のアクティブ化
     * - マネージャCORBAオブジェクトのアクティブ化
     * - Manager オブジェクトへのオブジェクト参照の登録
     *
     * このオペレーションは、マネージャの初期化後、runManager()
     * の前に呼ぶ必要がある。
     *
     * @else
     *
     * @brief Activate Manager
     *
     * This operation do the following,
     * - Activate CORBA POAManager
     * - Activate Manager CORBA object
     * - Bind object reference of the Manager to the nameserver
     *
     * This operationo should be invoked after Manager:init(),
     * and before tunManager().
     *
     * @endif
     */
    bool activateManager();

    /*!
     * @if jp
     *
     * @brief Managerの実行
     *
     * このオペレーションはマネージャのメインループを実行する。
     * このメインループ内では、CORBA ORBのイベントループ等が
     * 処理される。デフォルトでは、このオペレーションはブロックし、
     * Manager::destroy() が呼ばれるまで処理を戻さない。
     * 引数 no_block が true に設定されている場合は、内部でイベントループ
     * を処理するスレッドを起動し、ブロックせずに処理を戻す。
     *
     * @param no_block false: ブロッキングモード, true: ノンブロッキングモード
     *
     * @else
     *
     * @brief Run the Manager
     *
     * This operation processes the main event loop of the Manager.
     * In this main loop, CORBA's ORB event loop or other processes
     * are performed. As the default behavior, this operation is going to
     * blocking mode and never returns until manager::destroy() is called.
     * When the given argument "no_block" is set to "true", this operation
     * creates a thread to process the event loop internally, and it doesn't
     * block and returns.
     *
     * @param no_block false: Blocking mode, true: non-blocking mode.
     *
     * @endif
     */
    void runManager(bool no_block = false);
    



    //============================================================
    // Module management
    //============================================================
    /*!
     * @if jp
     * @brief [CORBA interface] モジュールのロード
     *
     * コンポーネントのモジュールをロードして初期化関数を実行する。
     *
     * @param fname   モジュールファイル名
     * @param initfunc 初期化関数名
     * 
     * @else
     *
     * @brief [CORBA interface] Load module
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
    std::vector<std::string> getLoadedModules();
    

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
    bool registerFactory(Properties& profile,
			 RtcNewFunc new_func,
			 RtcDeleteFunc delete_func);
    
    bool registerECFactory(const char* name,
			   ECNewFunc new_func,
			   ECDeleteFunc delete_func);
    
    /*!
     * @if jp
     * @brief ファクトリ全リストを取得する
     * @else
     * @brief Get the list of all RT-Component Factory
     * @endif
     */
    std::vector<std::string> getModulesFactories();
    
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
    RtcBase* createComponent(const char* module_name);
    void cleanupComponent(RtcBase* comp);
    /*!
     * @if jp
     * @brief RTコンポーネントを直接 Manager に登録する
     * @else
     * @brief Register RT-Component directly without Factory
     * @endif
     */
    bool registerComponent(RtcBase* comp);
    bool unregisterComponent(RtcBase* comp);


    bool bindExecutionContext(RtcBase* comp);

    /*!
     * @if jp
     * @brief Manager に登録されているRTコンポーネントを削除する
     * @else
     * @brief Unregister RT-Component that is registered in the Manager
     * @endif
     */
    void deleteComponent(const char* instance_name);
    
    /*!
     * @if jp
     * @brief Manager に登録されているRTコンポーネントを取得する
     * @else
     * @brief Get RT-Component's pointer
     * @endif
     */
    RtcBase* getComponent(const char* instance_name);
    
    /*!
     * @if jp
     * @brief Manager に登録されている全RTコンポーネントを取得する
     * @else
     * @brief Get all RT-Component's pointer
     * @endif
     */
    std::vector<RtcBase*> getComponents();
    

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
    CORBA::ORB_ptr getORB();

    /*!
     * @if jp
     * @brief Manager が持つ RootPOA のポインタを取得する
     * @else
     * @brief Get the pointer to the RootPOA 
     * @endif
     */
    PortableServer::POA_ptr getPOA();
    PortableServer::POAManager_ptr getPOAManager();


    //============================================================
    // Protected functions
    //============================================================
  protected:
    
    //============================================================
    // Manager initialize and finalization
    //============================================================
    /*!
     * @if jp
     * @brief Manager の内部初期化処理
     * @else
     * @brief Manager internal initialization
     * @endif
     */
    void initManager(int argc, char** argv);


    /*!
     * @if jp
     * @brief Manager の終了処理
     * @else
     * @brief Manager internal finalization
     * @endif
     */
    void shutdownManager();


    //============================================================
    // Logger initialize and terminator
    //============================================================
    /*!
     * @if jp
     * @brief System logger の初期化
     * @else
     * @brief System logger initialization
     * @endif
     */
    bool initLogger();


    /*!
     * @if jp
     * @brief System Logger の終了処理
     * @else
     * @brief System Logger finalization
     * @endif
     */
    void shutdownLogger();


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
    bool initORB();
    
    
    /*!
     * @if jp
     * @brief ORB のコマンドラインオプション作成
     * @else
     * @brief ORB command option creation
     * @endif
     */
    std::string createORBOptions();
    
    
    /*!
     * @if jp
     * @brief ORB の終了処理
     * @else
     * @brief ORB finalization
     * @endif
     */
    void shutdownORB();

   
    //============================================================
    // NamingService initialization and finalization
    //============================================================
    /*!
     * @if jp
     * @brief NamingManager の初期化
     * @else
     * @brief NamingManager initialization
     * @endif
     */
    bool initNaming();
    void shutdownNaming();


    //============================================================
    // Component management
    //============================================================
    void shutdownComponents();


    void configureComponent(RtcBase* comp);


    bool initExecContext();

    bool initTimer();

    bool mergeProperty(Properties& prop, const char* file_name);
    std::string formatString(const char* naming_format,
			     Properties& prop);
    
    //============================================================
    // protected 変数
    //============================================================

    //------------------------------------------------------------
    // static var
    //------------------------------------------------------------
    /*!
     * @if jp
     * @brief 唯一の Manager へのポインタ
     * @else
     * @brief The pointer to the Manager
     * @endif
     */
    static Manager* manager;

    /*!
     * @if jp
     * @brief 唯一の Manager へのポインタに対する mutex
     * @else
     * @brief The mutex of the pointer to the Manager 
     * @endif
     */
    static ACE_Thread_Mutex mutex;
    

    //------------------------------------------------------------
    // CORBA var
    //------------------------------------------------------------
    /*!
     * @if jp
     * @brief ORB へのポインタ
     * @else
     * @brief The pointer to the ORB
     * @endif
     */
    CORBA::ORB_var m_pORB;

    /*!
     * @if jp
     * @brief POA へのポインタ
     * @else
     * @brief The pointer to the POA
     * @endif
     */
    PortableServer::POA_var m_pPOA;

    /*!
     * @if jp
     * @brief POAManager へのポインタ
     * @else
     * @brief The pointer to the POAManager
     * @endif
     */
    PortableServer::POAManager_var m_pPOAManager;


    //------------------------------------------------------------
    // Manager's variable
    //------------------------------------------------------------
    /*!
     * @if jp
     * @brief ユーザ初期化関数へのポインタ
     * @else
     * @brief User's initialization function's pointer
     * @endif
     */
    ModuleInitProc m_initProc;

    /*!
     * @if jp
     * @brief Manager の configuration を格納する Properties
     * @else
     * @brief Managaer's configuration Properties
     * @endif
     */
    Properties m_config;

    /*!
     * @if jp
     * @brief ModuleManager へのポインタ
     * @else
     * @brief The pointer to the ModuleManager
     * @endif
     */
    ModuleManager* m_module;
    
    /*!
     * @if jp
     * @brief ModuleManager へのポインタ
     * @else
     * @brief The pointer to the ModuleManager
     * @endif
     */
    NamingManager* m_namingManager;

    CorbaObjectManager* m_objManager;

    /*!
     * @if jp
     * @brief Timer Object
     * @else
     * @brief Timer Object
     * @endif
     */
    Timer* m_timer;


    //------------------------------------------------------------
    // Logger
    //------------------------------------------------------------
    /*!
     * @if jp
     * @brief ロガーバッファ
     * @else
     * @brief Logger buffer
     * @endif
     */
    Logbuf m_Logbuf;

    /*!
     * @if jp
     * @brief ロガー仲介バッファ
     * @else
     * @brief Logger mediation buffer
     * @endif
     */
    MedLogbuf m_MedLogbuf;

    /*!
     * @if jp
     * @brief ロガーストリーム
     * @else
     * @brief Logger stream
     * @endif
     */
    LogStream rtcout;
    

    //============================================================
    // コンポーネントマネージャ
    //============================================================
    // ObjectManager へ渡す述語クラス
    struct InstanceName
    {
      InstanceName(RtcBase* comp) : m_name(comp->getInstanceName()) {};
      InstanceName(const char* name) : m_name(name) {};
      bool operator()(RtcBase* comp)
      {
	return m_name == comp->getInstanceName();
      }
      std::string m_name;
    };

    typedef ObjectManager<const char*,
			  RtcBase,
			  InstanceName> ComponentManager;
    /*!
     * @if jp
     * @brief コンポーネントマネージャ
     * @else
     * @brief The ComponentManager
     * @endif
     */
    ComponentManager m_compManager;


    //============================================================
    // コンポーネントファクトリ
    //============================================================
    // コンポーネントファクトリへ渡す述語クラス
    struct FactoryPredicate
    {
      FactoryPredicate(const char* name) : m_name(name){};
      FactoryPredicate(FactoryBase* factory)
	: m_name(factory->profile()["implementation_id"]) {};
      bool operator()(FactoryBase* factory)
      {
	return m_name == factory->profile()["implementation_id"];
      }
      std::string m_name;
    };
    /*!
     * @if jp
     * @brief コンポーネントファクトリ
     * @else
     * @brief The ComponentFactory
     * @endif
     */
    typedef ObjectManager<const char*,
			  FactoryBase,
			  FactoryPredicate> FactoryManager;
    /*!
     * @if jp
     * @brief ComponentManager
     * @else
     * @brief The ComponentManager
     * @endif
     */
    FactoryManager m_factory;

    //============================================================
    // ExecutionContextファクトリ
    //============================================================
    // ECファクトリへ渡す述語クラス
    struct ECFactoryPredicate
    {
      ECFactoryPredicate(const char* name) : m_name(name){};
      ECFactoryPredicate(ECFactoryBase* factory)
	: m_name(factory->name()) {};
      bool operator()(ECFactoryBase* factory)
      {
	return m_name == factory->name();
      }
      std::string m_name;
    };
    typedef ObjectManager<const char*,
			  ECFactoryBase,
			  ECFactoryPredicate> ECFactoryManager;
    ECFactoryManager m_ecfactory;
    std::vector<ExecutionContextBase*> m_ecs;


    // ファクトリ名をリストアップするためのファンクタ
    struct ModuleFactories
    {
      void operator()(FactoryBase* f)
      {
	modlist.push_back(f->profile().getProperty("implementation_id"));
      }
      std::vector<std::string> modlist;
    };


    //------------------------------------------------------------
    // ORB runner
    //------------------------------------------------------------
    class OrbRunner
      : public ACE_Task<ACE_MT_SYNCH>
    {
    public:
      OrbRunner(CORBA::ORB_ptr orb) : m_pORB(orb)
      {
	open(0);
      };
      virtual int open(void *args)
      {
	activate();
	return 0;
      }
      virtual int svc(void)
      {
	m_pORB->run();
	Manager::instance().shutdown();
	return 0;
      }
      virtual int close(unsigned long flags)
      {
	return 0;
      }
    private:
      CORBA::ORB_ptr m_pORB;
      
    };
    OrbRunner* m_runner;


    //------------------------------------------------------------
    // Manager Terminator
    //------------------------------------------------------------
    class Terminator
      : public ACE_Task<ACE_MT_SYNCH>
    {
    public:
      Terminator(Manager* manager) : m_manager(manager) {};
      void terminate()
      {
	open(0);
      }
      virtual int open(void *args)
      {
	activate();
	return 0;
      }
      virtual int svc(void)
      {
	Manager::instance().shutdown();
	return 0;
      }
      Manager* m_manager;
    };

    Terminator* m_terminator;

    struct Term
    {
      int waiting;
      ACE_Thread_Mutex mutex;
    };
    Term m_terminate;



  }; // class Manager
}; // namespace RTC

#endif // Manager_h
