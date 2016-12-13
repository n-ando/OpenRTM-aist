// -*- C++ -*-
/*!
 * @file RtcManager.h
 * @brief RTComponent manager class
 * @date $Date: 2005-05-16 06:19:56 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2003-2005
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: RtcManager.h,v 1.2 2005-05-16 06:19:56 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.1.1.1  2005/05/12 09:06:18  n-ando
 * Public release.
 *
 *
 */

#ifndef RtcManager_h
#define RtcManager_h


// CORBA includes
//#include <RTC.h>

// STL includes
#include <list>
#include <map>
#include <memory>
#include <string>
#include <vector>
#include <fstream>

// ACE includes
#include <ace/DLL.h>
#include <ace/Signal.h>

// Boost includes
#include <boost/function.hpp>
#include <boost/bind.hpp>

// CORBA stub include
#include "rtm/idl/RTCManagerSkel.h"
#include "rtm/idl/RTCManagerStub.h"
#include "rtm/RtcModuleProfile.h"
#include "rtm/RtcBase.h"
#include "rtm/RtcFactory.h"
#include "rtm/RtcSystemLogger.h"

// RTM includes

namespace RTM
{
  
  // Use std:: namespace
  using namespace std;
  
  // Pre-declaration of classes
  
  class RtcManager;
  class RtcNaming;
  class RtcConfig;
  
#define RtcMgrCmd boost::function2<bool, vector<string>&, vector<string>& > 
  
  typedef void (*RtcModuleInitProc)(RtcManager* manager);  
  
  /*!
   * @if jp
   *
   * @class RtcManager
   *
   * @brief RTComponent マネージャクラス
   *
   * RtcManager はコンポーネントのロード、生成、破棄などのライフサイクルを管理
   * する。またコンポーネントに対して各種サービスを提供する。
   *
   * @else
   *
   * @class RtcManager
   *
   * @brief RTComponent manager class.
   *
   * RtcManager manages life cycle of RTComponent for example, loading
   * component library, creating component, deleting component etc.
   * This manager also provide some services for RTComponents.
   *
   * @endif
   */
  class EXPORTS RtcManager :
    public virtual POA_RTM::RTCManager, 
							public virtual PortableServer::RefCountServantBase,
														   public ACE_Task<ACE_MT_SYNCH>
  {
	
  public:
	/*!
	 * @if jp
	 * @brief RtcManager クラスコンストラクタ
	 *
	 * 通常コマンドライン引数を引数としてとる。
	 *
	 * @else
	 *
	 * @brief A constructor of Rtcmanager class.
	 *
	 * Usually constructor is given command line arguments.
	 *
	 * @endif
	 */
    RtcManager(int argc, char** argv);
	void shutdown();
	/*!
	 * @if jp
	 * @brief RtcManager クラスデストラクタ
	 * @else
	 * @brief A destructor of Rtcmanager class.
	 * @endif
	 */    
    virtual ~RtcManager();
	
	/*!
	 * @if jp
	 * @brief マネージャタスクをスタートさせる
	 * @else
	 * @brief Start manager task.
	 * @endif
	 */    
	int open(void *args);
	
	/*!
	 * @if jp
	 * @brief サービスのスレッド関数
	 * @else
	 * @brief Thread function of service
	 * @endif
	 */    
	int svc(void);

	int close(unsigned long flags);
	
    //============================================================
    //
    // <<< CORBA interfaces >>>
    //
    //============================================================
	
	
	/*!
	 * @if jp
	 * @brief [CORBA interface] モジュールのロード
	 *
	 * コンポーネントのモジュールをロードして初期化関数を実行する。
	 *
	 * @param pathname コンポーネントモジュールファイル名
	 * @param initfunc 初期化関数名
	 * 
	 * @else
	 * @brief [CORBA interface] Load module
	 *
     * Load shared library of a component by path name, and invoke initialize
	 * function.
	 *
	 * @param pathname Component module file name
	 * @param initfunc Initialize function name
	 *
	 * @endif
	 */  
    virtual RtmRes load(const char* pathname, const char* initfunc);
	
	/*!
	 * @if jp
	 * @brief [CORBA interface] モジュールのアンロード
	 *
	 * コンポーネントのモジュールをアンロードする
	 *
	 * @param pathnae コンポーネントモジュールのファイル名
	 * 
	 * @else
	 * @brief [CORBA interface] Unload module
	 *
     * Unload shared library of a component module.
	 *
	 * @param pathname Component module file name
	 *
	 * @endif
	 */  
    virtual RtmRes unload(const char* pathname);
	
	/*!
	 * @if jp
	 * @brief [CORBA interface] コンポーネントの生成
	 *
	 * コンポーネントのインスタンスを生成する
	 *
	 * @param comp_name コンポーネントモジュール名
	 * @param comp_name インスタンス名 (戻値)
	 * 
	 * @else
	 * @brief [CORBA interface] Create component instance
	 *
     * Create component instance with component module name.
	 *
	 * @param comp_name Component module name
	 * @param comp_name Instance name (return value)
	 *
	 * @endif
	 */  
    virtual RTCBase_ptr create_component(const char* module_name,
										 const char* category_name,
										 CORBA::String_out instance_name);
	
	/*!
	 * @if jp
	 * @brief [CORBA interface] コンポーネントの削除
	 *
	 * コンポーネントのインスタンスを削除する
	 *
	 * @param instance_name インスタンス名
	 * @param category_name カテゴリ名
	 * 
	 * @else
	 * @brief [CORBA interface] Delete component instance
	 *
     * Delete component instance with instance name
	 *
	 * @param instance_name Instance name
	 * @param category_name Category name
	 *
	 * @endif
	 */  
    virtual RtmRes delete_component(const char* instance_name,
									const char* category_name);
	
	/*!
	 * @if jp
	 * @brief [CORBA interface] コンポーネント Factory リストの取得
	 *
	 * コンポーネント Factory のリストを取得する
	 *
	 * @else
	 * @brief [CORBA interface] Get component factory list
	 *
     * Get component factory list.
	 *
	 * @endif
	 */  
    virtual RTCFactoryList* factory_list();
	
	/*!
	 * @if jp
	 * @brief [CORBA interface] コンポーネントリストの取得
	 *
	 * コンポーネントのリストを取得する
	 *
	 * @else
	 * @brief [CORBA interface] Get component list
	 *
     * Get component list.
	 *
	 * @endif
	 */  
    virtual RTCBaseList* component_list();
	
	/*!
	 * @if jp
	 * @brief [CORBA interface] 簡易インタプリタ
	 *
	 * マネージャの簡易インタプリタコマンドの実行
	 *
	 * @else
	 * @brief [CORBA interface] Simple interpreter
	 *
     * Execute simple interpreter.
	 *
	 * @endif
	 */  
    virtual RtmRes command(const char* cmd, CORBA::String_out ret);
	
    // end of CORBA interface definition
    //============================================================
	
	
	
    //============================================================
    //
    // <<< Local interfaces >>>
    //
    //============================================================
	/*!
	 * @if jp
	 * @brief マネージャの初期化
	 *
	 * @else
	 * @brief Initialize manager
	 *
	 * @endif
	 */ 
    void initManager();
	
	/*!
	 * @if jp
	 * @brief マネージャの実行
	 *
	 * @else
	 * @brief Run manager
	 *
	 * @endif
	 */ 
    void runManager();
	
	/*!
	 * @if jp
	 * @brief マネージャの実行(非ブロックモード)
	 *
	 * @else
	 * @brief Run manager (No blocking mode)
	 *
	 * @endif
	 */ 
    void runManagerNoBlocking();
	
	/*!
	 * @if jp
	 * @brief マネージャサーバントのアクティブ化
	 *
	 * @else
	 * @brief Activate manager servant
	 *
	 * @endif
	 */ 
    bool activateManager();
	
	/*!
	 * @if jp
	 * @brief モジュール初期化ルーチンの実行
	 *
	 * @else
	 * @brief Invoke module initialize routine
	 *
	 * @endif
	 */ 
	void initModuleProc(RtcModuleInitProc proc);
	
	/*!
	 * @if jp
	 * @brief 簡易インタプリタコマンドの登録
	 *
	 * @else
	 * @brief Register simple interpreter command function
	 *
	 * @endif
	 */ 
    bool createCommand(string cmd,
					   boost::function2<bool,
					   vector<string>&, vector<string>&>  func);
	
	/*!
	 * @if jp
	 * @brief コンポーネントファクトリの登録
	 *
	 * @else
	 * @brief Register component factory
	 *
	 * @endif
	 */ 
    bool registerComponent(RtcModuleProfile& profile,
						   RtcNewFunc new_func,
						   RtcDeleteFunc delete_func);
	
	/*!
	 * @if jp
	 * @brief コンポーネントファクトリの登録
	 *
	 * @else
	 * @brief Register component factory
	 *
	 * @endif
	 */ 
	bool registerComponent(RtcFactoryBase* factory);
	
	
	/*!
	 * @if jp
	 * @brief コンポーネント生成
	 *
	 * @else
	 * @brief Create component
	 *
	 * @endif
	 */ 
    RtcBase* createComponent(const string& module_name,
							 const string& category_name,
							 string& comp_name);
	
	/*!
	 * @if jp
	 * @brief コンポーネント生成
	 *
	 * @else
	 * @brief Create component
	 *
	 * @endif
	 */ 
    RtcBase* createComponent(const string& module_name,
							 const string& category_name);

	
	/*!
	 * @if jp
	 * @brief コンポーネント削除のための処理
	 *
	 * @else
	 * @brief Creanup component
	 *
	 * @endif
	 */ 
    void cleanupComponent(const string& instance_name,
						  const string& category_name);
	
	
	/*!
	 * @if jp
	 * @brief コンポーネント検索
	 *
	 * @else
	 * @brief find component
	 *
	 * @endif
	 */ 
    std::vector<RTCBase_ptr> findComponents(const string& comp_name);
	
	/*!
	 * @if jp
	 * @brief InPort と OutPort を接続
	 *
	 * @else
	 * @brief Bind InPort with OutPort
	 *
	 * @endif
	 */ 
    std::string bindInOut(RTCBase_ptr comp_in,
						  const std::string& inp_name,
						  RTCBase_ptr comp_out,
						  const std::string& outp_name,
						  RTM::SubscriptionType sub_type = RTM::OPS_NEW);
	/*!
	 * @if jp
	 * @brief InPort と OutPort を名前により接続
	 *
	 * @else
	 * @brief Bind InPort with OutPort by name
	 *
	 * @endif
	 */ 
    std::string bindInOutByName(const std::string& comp_name_in,
								const std::string& inp_name,
								const std::string& comp_name_out,
								const std::string& outp_name,
								RTM::SubscriptionType sub_type = RTM::OPS_NEW);
	
	/*!
	 * @if jp
	 * @brief ORB のポインタを取得
	 *
	 * @else
	 * @brief Get pointer to ORB
	 *
	 * @endif
	 */ 
    CORBA::ORB_var getORB();
	
	/*!
	 * @if jp
	 * @brief POA のポインタを取得
	 *
	 * @else
	 * @brief Get pointer to POA
	 *
	 * @endif
	 */ 
    PortableServer::POA_var getPOA();

	RtcLogbuf& getLogbuf() {return m_Logbuf;}
	RtcConfig& getConfig() {return (*m_apConfig);}


	
    //============================================================
    // Commands
	
    bool loadCmd(const vector<string>& cmd, vector<string>& retval);
    bool unloadCmd(const vector<string>& cmd, vector<string>& retval);
    bool createComponentCmd(const vector<string>& cmd, vector<string>& retval);
    bool listComponent(const vector<string>& cmd, vector<string>& retval);
    bool listModule(const vector<string>& cmd, vector<string>& retval);
    bool commandListCmd(const vector<string>& cmd, vector<string>& retval);

  private:
    /*!
     * Initialize ORB and store ORB's reference
     */
    bool initORB();
	
    /*!
     * Initialize POA and POA manager
     */
    bool initPOA();

	bool initLogger();
	bool initMasterLogger();
	void loadMasterLogger();

	
    /*!
     * Find library path
     */
    bool findPath(string path, string &full_path);
	
    /*!
     * Make initialize function name from libname
     */
    bool libnameToInitFunc(const char* libname,
						   const char* initfunc,
						   string &initfunc_name);
	
	void shutdownAllComponents();
	
  private:
	/*!
	 * @if jp
	 * @brief RtcConfig へのポインタ
	 * @else
	 * @brief Pointer to RtcConfig
	 * @endif
	 */
    auto_ptr<RtcConfig> m_apConfig;
	
	/*!
	 * @if jp
	 * @brief RtcNaming へのポインタ
	 * @else
	 * @brief Pointer to RtcNaming
	 * @endif
	 */
    auto_ptr<RtcNaming> m_apNaming;
	
	/*!
	 * @if jp
	 * @brief ORB へのポインタ
	 * @else
	 * @brief Pointer to ORB
	 * @endif
	 */
    CORBA::ORB_var m_pORB;
	
	/*!
	 * @if jp
	 * @brief POA へのポインタ
	 * @else
	 * @brief Pointer to POA
	 * @endif
	 */
    PortableServer::POA_var m_pPOA;
	
	/*!
	 * @if jp
	 * @brief POAManager へのポインタ
	 * @else
	 * @brief Pointer to POAManager
	 * @endif
	 */
    PortableServer::POAManager_var m_pPOAManager;
	
  	/*!
	 * @if jp
	 * @brief 簡易インタプリタのコマンドマップ
	 * @else
	 * @brief Command map for simple interpreter
	 * @endif
	 */
    map<string, boost::function2<bool, vector<string>&, vector<string>&> > m_CmdMap;
	
  	/*!
	 * @if jp
	 * @brief コンポーネントモジュールロードパス
	 * @else
	 * @brief Component module load path
	 * @endif
	 */
    list<string> m_LibraryLoadPath;
	
    //! Component factory and destructor map
	/*    struct Factory {
		  
	RtcModuleProfile _profile;
	RtcNewFunc _new;
	RtcDeleteFunc _delete;
	int _num;
    };
	*/
	
 	/*!
	 * @if jp
	 * @brief コンポーネントファクトリマップ構造体
	 * @else
	 * @brief Component factory map
	 * @endif
	 */
	struct FactoryMap {
	  //! Mutex
      ACE_Thread_Mutex _mutex;
	  //! Moulde name <=> Factory
	  std::map<std::string, std::map<std::string, RtcFactoryBase*> > _map;
	};
	
 	/*!
	 * @if jp
	 * @brief コンポーネントファクトリマップ
	 * @else
	 * @brief Component factory map
	 * @endif
	 */
	FactoryMap m_FactoryMap;
	
 	/*!
	 * @if jp
	 * @brief コンポーネントモジュール構造体
	 * @else
	 * @brief Component module structre
	 * @endif
	 */
    struct DLL {
      int _refCount;
      ACE_DLL _dll;
    };
	
 	/*!
	 * @if jp
	 * @brief コンポーネントモジュールマップ
	 * @else
	 * @brief Component module map
	 * @endif
	 */
    map<string, DLL> m_Lib; // Library name <=> DLL manager

	ACE_Sig_Action* m_SigAction;
	ACE_Sig_Action* m_SigHupAction;
	ACE_Sig_Action* m_SigIntAction;
	ACE_Sig_Action* m_SigKillAction;
	ACE_Sig_Action* m_SigSegvAction;
	ACE_Sig_Action* m_SigBusAction;

  public:
 	/*!
	 * @if jp
	 * @brief コンポーネントインスタンスデータベース構造体
	 * @else
	 * @brief Component instance database
	 * @endif
	 */
    struct ComponentMap {
	  //! Mutex
      ACE_Thread_Mutex _mutex;
      std::map<string, std::map<string, RtcBase*> > _map;
    };
 	/*!
	 * @if jp
	 * @brief コンポーネントインスタンスデータベースマップ
	 *
	 * m_Components._map[_category_name_][_instance_name_]
	 *
	 * @else
	 * @brief Component instance database map
	 * @endif
	 */
    ComponentMap m_Components;
	
 	/*!
	 * @if jp
	 * @brief コンポーネントモジュール初期化関数
	 * @else
	 * @brief Component module initialization function
	 * @endif
	 */
    typedef bool (*RtcComponentInit)(RtcManager* manager);
	
 	/*!
	 * @if jp
	 * @brief マネージャ名
	 * @else
	 * @brief Manager name
	 * @endif
	 */
    string m_ManagerName;

 	/*!
	 * @if jp
	 * @brief ロガーバッファ
	 * @else
	 * @brief Logger buffer
	 * @endif
	 */
	RtcLogbuf m_Logbuf;
 	/*!
	 * @if jp
	 * @brief ロガー仲介バッファ
	 * @else
	 * @brief Logger mediation buffer
	 * @endif
	 */
	RtcMedLogbuf m_MedLogbuf;
 	/*!
	 * @if jp
	 * @brief ロガーストリーム
	 * @else
	 * @brief Logger stream
	 * @endif
	 */
	RtcLogStream rtcout;

	TimedString m_LoggerOut;
	typedef OutPortAny<TimedString> LogOutPort;
	LogOutPort* m_pLoggerOutPort;

	class LogEmitter
	  : public RtcSyncCallback
	{
	public:
	  LogEmitter(OutPortAny<TimedString>& port, TimedString& var)
		: m_OutPort(port), m_Var(var)
	  {
	  }
	  virtual int operator()(const char* s)
	  {
		m_Var.data = CORBA::string_dup(s);
		m_OutPort.write();
		return true;
	  }
	protected:
	  OutPortAny<TimedString>& m_OutPort;
	  TimedString& m_Var;
	};
	
	LogEmitter* m_pLogEmitter;
	RTCBase_var m_pMasterLogger; 	
  };


}; // end of namespace RTM

#endif // RtcManager_h
