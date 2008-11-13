// -*- C++ -*-
/*!
 * @file   ManagerTests.cpp
 * @brief  Manager test class
 * @date   $Date: 2008/05/12 03:58:45 $
 *
 * $Id: ManagerTests.cpp,v 1.2 2008/05/12 03:58:45 arafune Exp $
 *
 */

/*
 * $Log: ManagerTests.cpp,v $
 * Revision 1.2  2008/05/12 03:58:45  arafune
 * Added some tests.
 * Rearranged tests in a different order.
 *
 * Revision 1.1  2008/05/09 12:01:44  arafune
 * The first commitment.
 *
 *
 */

#ifndef ManagerTests_cpp
#define ManagerTests_cpp

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>

#include <coil/Task.h>
#include <coil/DynamicLib.h>

#include <rtm/Manager.h>
#include <rtm/RTObject.h>
#include <rtm/ECFactory.h>
#include <rtm/PeriodicExecutionContext.h>
#include <rtm/ExtTrigExecutionContext.h>
#include <rtm/NamingManager.h>

/*!
 * @class ManagerTests class
 * @brief Manager test
 */
namespace Tests
{
  class Logger
  {
  public:
    void log(const std::string& msg)
    {
      m_log.push_back(msg);
    }
		
    int countLog(const std::string& msg)
    {
      int count = 0;
      for (int i = 0; i < (int) m_log.size(); ++i)
	{
	  if (m_log[i] == msg) ++count;
	}
      return count;
    }
		
  private:
    std::vector<std::string> m_log;
  };
	
	
  class ManagerMock : public RTC::Manager
  {
  public: // for test
    static void clearInstance()
    {
      manager = NULL;
    }
  };
	
	
  class ModuleMock
  {
  public:
    static void setLogger(Logger* logger)
    {
      m_logger = logger;
    }
		
    static void InitProc(RTC::Manager* manager)
    {
      if (m_logger != NULL) m_logger->log("InitProc");
    }
	
  private:
    static Logger* m_logger;
  };
	
  Logger* ModuleMock::m_logger = NULL;
	
	
  class RTObjectMock
    : virtual public RTC::RTObject_impl
  {
  public:
    RTObjectMock(CORBA::ORB_ptr orb, PortableServer::POA_ptr poa)
      : RTC::RTObject_impl(orb, poa), m_logger(NULL)
    {
    }
		
    virtual RTC::ReturnCode_t initialize()
      throw (CORBA::SystemException)
    {
      if (m_logger != NULL) m_logger->log("initialize");
      return RTC::RTC_OK;
    }
		
    void setLogger(Logger* logger)
    {
      m_logger = logger;
    }
		
  private:
    Logger* m_logger;
  };


  class DataFlowComponentMock
    : virtual public RTC::RTObject_impl
  {
  public:
    DataFlowComponentMock(CORBA::ORB_ptr orb, PortableServer::POA_ptr poa)
      : RTC::RTObject_impl(orb, poa)
    {
    }
		
    RTC::UniqueId attach_executioncontext(RTC::ExecutionContext_ptr exec_context)
      throw (CORBA::SystemException)
    {
      return RTC::RTObject_impl::attach_context(exec_context);
    }
  };
	
  RTC::RtcBase* CreateDataFlowComponentMock(RTC::Manager* manager)
  {
    CORBA::ORB_ptr orb = manager->getORB();
    PortableServer::POA_ptr poa = manager->getPOA();
    DataFlowComponentMock* comp = new DataFlowComponentMock(orb, poa);
    comp->setObjRef(comp->_this());
    return comp;
  }

  void DeleteDataFlowComponentMock(RTC::RtcBase* rtc)
  {
    if (rtc != NULL) rtc->_remove_ref();
  }
	
	
  class ManagerTests
    : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(ManagerTests);
	  

    CPPUNIT_TEST(test_init_without_arguments);
    CPPUNIT_TEST(test_instance);
    CPPUNIT_TEST(test_instance_without_init);
    CPPUNIT_TEST(test_terminate_immediately_after_the_initialization);
    CPPUNIT_TEST(test_terminate_after_the_activation);
    CPPUNIT_TEST(test_getLogbuf);
    CPPUNIT_TEST(test_getConfig);
    CPPUNIT_TEST(test_setModuleInitProc);
//    CPPUNIT_TEST(test_runManager_no_block);
//    CPPUNIT_TEST(test_runManager_block);

    CPPUNIT_TEST(test_load);
    CPPUNIT_TEST(test_unload);
    CPPUNIT_TEST(test_unloadAll);
    CPPUNIT_TEST(test_registerFactory);
    CPPUNIT_TEST(test_registerECFactory);
    CPPUNIT_TEST(test_getModulesFactories);
//    CPPUNIT_TEST(test_cleanupComponent);
//    CPPUNIT_TEST(test_getComponents);
		
    // ※現在、各テスト間の独立性を完全に確保できていないため、下記テストは実施順序を変更しないこと。
    //   また、テスト内容を変更したり、他テストを追加したりする場合は、必ずしもテスト間の独立性が
    //   保たれない点に留意すること。なお、独立性が保てないのは、omniORBを用いた場合に、
    //   CORBA::ORB::destroy()が失敗する場合があり、次テスト時のCORBA::ORB_init()呼出が
    //   新ORBインスタンスを返さない場合があるため。詳しい原因は現時点では不明。
    //
//    CPPUNIT_TEST(test_createComponent_DataFlowComponent);
    //CPPUNIT_TEST(test_createComponent_Non_DataFlowComponent);
//    CPPUNIT_TEST(test_createComponent_failed_in_bindExecutionContext);
    //CPPUNIT_TEST(test_createComponent_with_illegal_module_name);

    CPPUNIT_TEST_SUITE_END();
	
  private:
    RTC::Manager* m_mgr;
	
  private:
    bool isFound(const std::vector<std::string>& list, const std::string& target)
    {
      return ! (list.end() == std::find(list.begin(), list.end(), target));
    }

    CosNaming::NamingContext_var getRootContext(const std::string& name_server)
    {
      std::string nsName
	= std::string("corbaloc::")
	+ name_server
	+ std::string("/NameService");
			
      CORBA::Object_var obj = m_mgr->getORB()->string_to_object(nsName.c_str());
      CosNaming::NamingContext_var rootContext = CosNaming::NamingContext::_narrow(obj);
      if (CORBA::is_nil(rootContext))
	{
	  throw std::bad_alloc();
	}
			
      return rootContext;
    }
		
    bool canResolve(const char* name_server, const char* id, const char* kind)
    {
      CosNaming::NamingContext_var nc = getRootContext(name_server);
			
      CosNaming::Name name;
      name.length(1);
      name[0].id = id;
      name[0].kind = kind;
			
      CORBA::Object_ptr obj;
      try
	{
	  obj = nc->resolve(name);
	}
      catch (CosNaming::NamingContext::NotFound e)
	{
	  return false;
	}
      return !CORBA::is_nil(obj);
    }
	
  public:
    /*!
     * @brief Constructor
     */
    ManagerTests()
    {
    }
		    
    /*!
     * @brief Destructor
     */
    virtual ~ManagerTests()
    {
    }
		  
    /*!
     * @brief Test initialization
     */
    virtual void setUp()
    {
      ManagerMock::clearInstance();
      m_mgr = NULL;
      coil::usleep(100000);
    }
    
    /*!
     * @brief Test finalization
     */
    virtual void tearDown()
    {
      coil::usleep(100000);
      /*
      if (m_mgr != NULL)
	{
	  try
	    {
	      CORBA::ORB_ptr orb = m_mgr->getORB();
	      if (! CORBA::is_nil(orb))
		{
		  orb->destroy();
		  sleep(3);
		}
	    }
	  catch (...) {}
	}
      */
    }
		
    /*!
     * @brief init()メソッドのテスト
     * 
     * - コマンドライン引数なしでinit()を正常に呼出して、インスタンスを取得できるか？
     */
    void test_init_without_arguments()
    {
      // コマンドライン引数なしでinit()を正常に呼出して、インスタンスを取得できるか？
      m_mgr = RTC::Manager::init(0, NULL);
      CPPUNIT_ASSERT(m_mgr != NULL);
      //      m_mgr->terminate();
    }
		
    /*!
     * @brief instance()メソッドのテスト
     * 
     * - instance()を通じて取得したインスタンスは、init()時に得たインスタンスと同一か？
     */
    void test_instance()
    {
      int argc = 0;
      char* argv[] = {};
			
      m_mgr = RTC::Manager::init(argc, argv);
      CPPUNIT_ASSERT(m_mgr != NULL);
			
      // instance()を通じて取得したインスタンスは、init()時に得たインスタンスと同一か？
      RTC::Manager& instance = RTC::Manager::instance();
      CPPUNIT_ASSERT_EQUAL(m_mgr, &instance);
    }
		
    /*!
     * @brief instance()メソッドのテスト
     * 
     * - 事前にinit()を呼出さずにinstance()を呼出した場合、正常にインスタンスが生成されるか？
     */
    void test_instance_without_init()
    {
      // 事前にinit()を呼出さずにinstance()を呼出した場合、正常にインスタンスが生成されるか？
      RTC::Manager::instance();
    }
		
    /*!
     * @brief terminate()メソッドのテスト
     * 
     * - 初期化後すぐにterminate()を呼出し、正常に終了できるか？
     */
    void test_terminate_immediately_after_the_initialization()
    {
      // 初期化を行う
      int argc = 0;
      char* argv[] = {};
			
      m_mgr = RTC::Manager::init(argc, argv);
      CPPUNIT_ASSERT(m_mgr != NULL);
      CPPUNIT_ASSERT(m_mgr->getORB() != NULL);
      CPPUNIT_ASSERT(m_mgr->getPOA() != NULL);
			
      // 初期化後すぐにterminate()を呼出し、正常に終了できるか？
      CPPUNIT_ASSERT(! CORBA::is_nil(m_mgr->getORB()));
      CPPUNIT_ASSERT(! CORBA::is_nil(m_mgr->getPOA()));
      m_mgr->terminate();
      coil::sleep(3); 
      CPPUNIT_ASSERT(CORBA::is_nil(m_mgr->getORB()));
      CPPUNIT_ASSERT(CORBA::is_nil(m_mgr->getPOA()));
      m_mgr = NULL;
    }
		
    /*!
     * @brief terminate()メソッドのテスト
     * 
     * - active化の後でterminate()を呼出し、正常に終了できるか？
     */
    void test_terminate_after_the_activation()
    {
      // 初期化を行う
      int argc = 0;
      char* argv[] = {};
			
      m_mgr = RTC::Manager::init(argc, argv);
      CPPUNIT_ASSERT(m_mgr != NULL);
      CPPUNIT_ASSERT(m_mgr->getORB() != NULL);
//      CPPUNIT_ASSERT(m_mgr->getPOA() != NULL);
//      CPPUNIT_ASSERT(m_mgr->getPOAManager() != NULL);
      CPPUNIT_ASSERT(! CORBA::is_nil(m_mgr->getPOA()));
      CPPUNIT_ASSERT(! CORBA::is_nil(m_mgr->getPOAManager()));
			
      // active化する
      CPPUNIT_ASSERT(m_mgr->activateManager());
			
      // active化の後でterminate()を呼出し、正常に終了できるか？
      CPPUNIT_ASSERT(! CORBA::is_nil(m_mgr->getORB()));
      CPPUNIT_ASSERT(! CORBA::is_nil(m_mgr->getPOA()));
      m_mgr->terminate();
      coil::sleep(3); 
      CPPUNIT_ASSERT(CORBA::is_nil(m_mgr->getORB()));
      CPPUNIT_ASSERT(CORBA::is_nil(m_mgr->getPOA()));
    }
		
    void test_shutdown()
    {
      // terminate()を通じて呼び出されるメソッドであるため、直接のテスト対象とはしない
    }
		
    void test_join()
    {
      // shutdown()の中で使用されるメソッドであるため、直接のテスト対象とはしない
      // ※そもそも、なぜpublicメソッドになっているのだろうか？
    }
		
    /*!
     * @brief getLogbuf()メソッドのテスト
     * 
     * - ログバッファを正しく取得でき、さらにオープンされているか？
     */
    void test_getLogbuf()
    {
      // 初期化を行う
//      int argc = 1;
      int argc = 3;
      char* argv[] = { "ManagerTests","-f","fixture1.conf" };
			
      m_mgr = RTC::Manager::init(argc, argv);
      CPPUNIT_ASSERT(m_mgr != NULL);
			
      // ログバッファを正しく取得でき、さらにオープンされているか？
      RTC::Logbuf& logbuf = m_mgr->getLogbuf();
      CPPUNIT_ASSERT(logbuf.is_open());
    }
		
    /*!
     * @brief getConfig()メソッドのテスト
     * 
     * - confファイルで指定した各種設定を、getConfig()を通じて正しく取得できるか？
     */
    void test_getConfig()
    {
      // 初期化を行う
//      int argc = 1;
//      char* argv[] = { "-f","fixture2.conf" };
      int argc = 3;
      char* argv[] = { "ManagerTests","-f","fixture2.conf" };
			
      m_mgr = RTC::Manager::init(argc, argv);
      CPPUNIT_ASSERT(m_mgr != NULL);
			
      // confファイルで指定した各種設定を、getConfig()を通じて正しく取得できるか？
      coil::Properties& properties = m_mgr->getConfig();
      CPPUNIT_ASSERT_EQUAL(std::string("YES"),
			   properties.getProperty("logger.enable"));
      CPPUNIT_ASSERT_EQUAL(std::string("fixture2.log"),
			   properties.getProperty("logger.file_name"));
    }
		
    /*!
     * @brief setModuleInitProc()メソッドのテスト
     * 
     * - アクティブ化により、設定した初期化プロシージャが正しく呼び出されるか？
     */
    void test_setModuleInitProc()
    {
      // Mockの準備
      Logger logger;
      ModuleMock::setLogger(&logger);
			
      // 初期化を行う
      int argc = 0;
      char* argv[] = {};
			
      m_mgr = RTC::Manager::init(argc, argv);
      CPPUNIT_ASSERT(m_mgr != NULL);
			
      // 初期化プロシージャを登録する
      m_mgr->setModuleInitProc(&ModuleMock::InitProc);
			
      // アクティブ化により、設定した初期化プロシージャが正しく呼び出されるか？
      CPPUNIT_ASSERT_EQUAL(0, logger.countLog("InitProc"));
      CPPUNIT_ASSERT(m_mgr->activateManager());
      CPPUNIT_ASSERT_EQUAL(1, logger.countLog("InitProc"));
    }
		
    void test_activateManager()
    {
      // 他テスト中で使用されているため省略する
    }
		
    /*!
     * @brief runManager()メソッドのテスト（非ブロッキングモード）
     * 
     * - POAManagerがアクティブ化されるか？
     */
    void test_runManager_no_block()
    {
std::cout<<"test_runManager_no_block:---"<<std::endl;
      // 初期化を行う
      int argc = 0;
      char* argv[] = {};
      m_mgr = RTC::Manager::init(argc, argv);
      CPPUNIT_ASSERT(m_mgr != NULL);

      // オブジェクトを生成して、参照を得る
      CORBA::ORB_ptr orb = m_mgr->getORB();
      CPPUNIT_ASSERT(! CORBA::is_nil(orb));
      PortableServer::POA_ptr poa = m_mgr->getPOA();
      CPPUNIT_ASSERT(! CORBA::is_nil(poa));

      RTObjectMock* rto = new RTObjectMock(orb, poa);
      CPPUNIT_ASSERT(rto != NULL);

      PortableServer::ObjectId_var rtoId = poa->activate_object(rto);

      RTC::DataFlowComponent_ptr rtoRef
	= RTC::DataFlowComponent::_narrow(poa->id_to_reference(rtoId));
      CPPUNIT_ASSERT(! CORBA::is_nil(rtoRef));

      // テスト用にロガーを設定しておく
      Logger logger;
      rto->setLogger(&logger);
			
      // 非ブロッキングモードでマネージャを作動させる
      CPPUNIT_ASSERT(m_mgr->activateManager());
      m_mgr->runManager(true); // true:非ブロッキング，false:ブロッキング

      // runManager()によりPOAManagerが正しくactive化されているか？
      // （取得したオブジェクト参照に対してメソッド呼出を行い、
      // リモート側が呼出されたことによりPOAManagerのアクティブ化を確認する）
      CPPUNIT_ASSERT_EQUAL(0, logger.countLog("initialize"));
      rtoRef->initialize();
      coil::sleep(3);
      CPPUNIT_ASSERT_EQUAL(1, logger.countLog("initialize"));
//      m_mgr->shutdown();
std::cout<<"test_runManager_no_block:30:---"<<std::endl;
      m_mgr->terminate();
      coil::sleep(3);
std::cout<<"test_runManager_no_block:e:---"<<std::endl;
    }
		
    /*!
     * @brief runManager()メソッドのテスト（ブロッキングモード）
     * 
     * - POAManagerがアクティブ化されるか？
     */
    void test_runManager_block()
    {
      // 初期化を行う
      int argc = 0;
      char* argv[] = {};
			
      m_mgr = RTC::Manager::init(argc, argv);
      CPPUNIT_ASSERT(m_mgr != NULL);
			
      // オブジェクトを生成して、参照を得る
      CORBA::ORB_ptr orb = m_mgr->getORB();
      CPPUNIT_ASSERT(! CORBA::is_nil(orb));
      PortableServer::POA_ptr poa = m_mgr->getPOA();
      CPPUNIT_ASSERT(! CORBA::is_nil(poa));
			
      RTObjectMock* rto = new RTObjectMock(orb, poa);
      CPPUNIT_ASSERT(rto != NULL);
			
      PortableServer::ObjectId_var rtoId = poa->activate_object(rto);
			
      RTC::DataFlowComponent_ptr rtoRef
	= RTC::DataFlowComponent::_narrow(poa->id_to_reference(rtoId));
      CPPUNIT_ASSERT(! CORBA::is_nil(rtoRef));
			
      // テスト用にロガーを設定しておく
      Logger logger;
      rto->setLogger(&logger);

      // ブロッキングモードでマネージャを作動させる
      CPPUNIT_ASSERT(m_mgr->activateManager());
      CPPUNIT_ASSERT_EQUAL(0, logger.countLog("initialize"));
      {
	InvokerMock invoker(rtoRef, m_mgr);
	m_mgr->runManager(false); // true:非ブロッキング，false:ブロッキング
	coil::sleep(3);
      }
      CPPUNIT_ASSERT_EQUAL(1, logger.countLog("initialize"));
//      m_mgr->shutdown();
      coil::usleep(3000000);
    }
		
    class InvokerMock
      : public coil::Task
    {
    public:
      InvokerMock(const RTC::DataFlowComponent_ptr& rtoRef, RTC::Manager* mgr)
      {
	m_rtoRef = RTC::DataFlowComponent::_duplicate(rtoRef);
	m_mgr = mgr;
	activate();
      }
			
      ~InvokerMock()
      {
	wait();	
      }
			
      virtual int svc(void)
      {
	m_rtoRef->initialize();
	sleep(1);
				
	// ブロックされているrunManager呼出をブロック解除する
	m_mgr->getORB()->shutdown(true);
	m_mgr->join();
				
	return 0;
      }
		
    private:
      RTC::DataFlowComponent_ptr m_rtoRef;
      RTC::Manager* m_mgr;
    };
		
    /*!
     * @brief load()メソッドのテスト
     * 
     * - 指定したモジュールをロードして、指定の初期化関数が正しく呼び出されるか？
     */
    void test_load()
    {
      // 初期化を行う
//      int argc = 1;
//      char* argv[] = { "-f fixture3.conf" };
      int argc = 3;
      char* argv[] = { "ManagerTests","-f","fixture3.conf" };
			
      m_mgr = RTC::Manager::init(argc, argv);
      CPPUNIT_ASSERT(m_mgr != NULL);

      // Managerとは別に、確認用にモジュールへのシンボルを取得しておく
      typedef int (*FUNC_GETINITPROCCOUNT)();
      typedef void (*FUNC_RESETINITPROCCOUNT)();
      coil::DynamicLib loader("./DummyModule.so");

      FUNC_GETINITPROCCOUNT pGetInitProcCount
	= (FUNC_GETINITPROCCOUNT) loader.symbol("getInitProcCount");
      CPPUNIT_ASSERT(pGetInitProcCount != NULL);
			
      FUNC_RESETINITPROCCOUNT pResetInitProcCount
	= (FUNC_RESETINITPROCCOUNT) loader.symbol("resetInitProcCount");
      CPPUNIT_ASSERT(pResetInitProcCount != NULL);
			
      (*pResetInitProcCount)(); // カウンタクリア
			
      // モジュールロードにより、指定した初期化関数が呼び出されるか？
      CPPUNIT_ASSERT_EQUAL(0, (*pGetInitProcCount)());
      // std::string moduleName = m_mgr->load("DummyModule.so", "InitProc");
      m_mgr->load("DummyModule.so", "InitProc");
      // CPPUNIT_ASSERT(isFound(m_mgr->getLoadedModules(), moduleName));
      // CPPUNIT_ASSERT_EQUAL(1, (*pGetInitProcCount)());
    }
		
    /*!
     * @brief unload()メソッドのテスト
     * 
     * - いったんloadしたモジュールを、正しくunloadできるか？
     */
    void test_unload()
    {
      // 初期化を行う
      int argc = 1;
      char* argv[] = { "-f fixture3.conf" };
			
      m_mgr = RTC::Manager::init(argc, argv);
      CPPUNIT_ASSERT(m_mgr != NULL);

      // Managerとは別に、確認用にモジュールへのシンボルを取得しておく
      typedef int (*FUNC_GETINITPROCCOUNT)();
      typedef void (*FUNC_RESETINITPROCCOUNT)();
      coil::DynamicLib loader("./DummyModule.so");
			
      FUNC_GETINITPROCCOUNT pGetInitProcCount
	= (FUNC_GETINITPROCCOUNT) loader.symbol("getInitProcCount");
      CPPUNIT_ASSERT(pGetInitProcCount != NULL);

      FUNC_RESETINITPROCCOUNT pResetInitProcCount
	= (FUNC_RESETINITPROCCOUNT) loader.symbol("resetInitProcCount");
      CPPUNIT_ASSERT(pResetInitProcCount != NULL);
			
      (*pResetInitProcCount)(); // カウンタクリア
			
      // いったんloadしておく
      CPPUNIT_ASSERT_EQUAL(0, (*pGetInitProcCount)());
      m_mgr->load("DummyModule.so", "InitProc");
      // std::string moduleName = m_mgr->load("DummyModule.so", "InitProc");
      // CPPUNIT_ASSERT(isFound(m_mgr->getLoadedModules(), moduleName));
      // CPPUNIT_ASSERT_EQUAL(1, (*pGetInitProcCount)());
			
      // いったんloadしたモジュールを、正しくunloadできるか？
      // m_mgr->unload(moduleName.c_str());
      // CPPUNIT_ASSERT(! isFound(m_mgr->getLoadedModules(), moduleName));
    }
		
    /*!
     * @brief unloadAll()メソッドのテスト
     * 
     * - unloadAll()により、ロードしたモジュールがすべてアンロードされるか？
     */
    void test_unloadAll()
    {
      // 初期化を行う
//      int argc = 1;
//      char* argv[] = { "-f fixture3.conf" };
      int argc = 3;
      char* argv[] = { "ManagerTests","-f","fixture3.conf" };
			
      m_mgr = RTC::Manager::init(argc, argv);
      CPPUNIT_ASSERT(m_mgr != NULL);

      // Managerとは別に、確認用にモジュールへのシンボルを取得しておく
      typedef int (*FUNC_GETINITPROCCOUNT)();
      typedef void (*FUNC_RESETINITPROCCOUNT)();
			
      coil::DynamicLib loader1("./DummyModule.so");
      coil::DynamicLib loader2("./DummyModule2.so");
			
      FUNC_GETINITPROCCOUNT pGetInitProcCount1
	= (FUNC_GETINITPROCCOUNT) loader1.symbol("getInitProcCount");
      CPPUNIT_ASSERT(pGetInitProcCount1 != NULL);

      FUNC_RESETINITPROCCOUNT pResetInitProcCount1
	= (FUNC_RESETINITPROCCOUNT) loader1.symbol("resetInitProcCount");
      CPPUNIT_ASSERT(pResetInitProcCount1 != NULL);

      FUNC_GETINITPROCCOUNT pGetInitProcCount2
	= (FUNC_GETINITPROCCOUNT) loader2.symbol("getInitProcCount");
      CPPUNIT_ASSERT(pGetInitProcCount2 != NULL);

      FUNC_RESETINITPROCCOUNT pResetInitProcCount2
	= (FUNC_RESETINITPROCCOUNT) loader2.symbol("resetInitProcCount");
      CPPUNIT_ASSERT(pResetInitProcCount2 != NULL);
			
      (*pResetInitProcCount1)(); // カウンタクリア
      (*pResetInitProcCount2)(); // カウンタクリア
			
      // いったんloadしておく
      CPPUNIT_ASSERT_EQUAL(0, (*pGetInitProcCount1)());
      CPPUNIT_ASSERT_EQUAL(0, (*pGetInitProcCount2)());

      // std::string moduleName1 = m_mgr->load("DummyModule.so", "InitProc");
      // std::string moduleName2 = m_mgr->load("DummyModule2.so", "InitProc");
      m_mgr->load("DummyModule.so", "InitProc");
      m_mgr->load("DummyModule2.so", "InitProc");

      // CPPUNIT_ASSERT(isFound(m_mgr->getLoadedModules(), moduleName1));
      // CPPUNIT_ASSERT(isFound(m_mgr->getLoadedModules(), moduleName2));

      // CPPUNIT_ASSERT_EQUAL(1, (*pGetInitProcCount1)());
      // CPPUNIT_ASSERT_EQUAL(1, (*pGetInitProcCount2)());
			
      // unloadAll()により、ロードしたモジュールがすべてアンロードされるか？
      m_mgr->unloadAll();
      // CPPUNIT_ASSERT(! isFound(m_mgr->getLoadedModules(), moduleName1));
      // CPPUNIT_ASSERT(! isFound(m_mgr->getLoadedModules(), moduleName2));
    }
		
    void test_getLoadedModules()
    {
      // 他テスト内で使用されているので省略する
    }
		
    void test_getLoadableModules()
    {
      // テスト対象のクラス側が未実装につき、テストも未実装
    }
		
    /*!
     * @brief registerFactory()メソッドのテスト
     * 
     * - Factoryを正常に登録できるか？
     */
    void test_registerFactory()
    {
      // 初期化を行う
      int argc = 0;
      char* argv[] = {};
			
      m_mgr = RTC::Manager::init(argc, argv);
      CPPUNIT_ASSERT(m_mgr != NULL);
			
      // Factoryを正常に登録できるか？
      coil::Properties properties;
      properties.setProperty("implementation_id", "ID");

      CPPUNIT_ASSERT(! isFound(m_mgr->getModulesFactories(), "ID"));
      CPPUNIT_ASSERT(m_mgr->registerFactory(
					    properties, CreateDataFlowComponentMock, DeleteDataFlowComponentMock));
      CPPUNIT_ASSERT(isFound(m_mgr->getModulesFactories(), "ID"));
    }
		
    /*!
     * @brief registerECFactory()
     * 
     * - 正常にECFactoryを登録できるか？
     */
    void test_registerECFactory()
    {
      // 初期化を行う
      int argc = 0;
      char* argv[] = {};
			
      m_mgr = RTC::Manager::init(argc, argv);
      CPPUNIT_ASSERT(m_mgr != NULL);
			
      // 正常にECFactoryを登録できるか？
      CPPUNIT_ASSERT(m_mgr->registerECFactory(
					      "PeriodicEC",
					      RTC::ECCreate<RTC::PeriodicExecutionContext>,
					      RTC::ECDelete<RTC::PeriodicExecutionContext>));
			
      // 登録済みのECFactoryと同一の名称で登録を試みた場合、意図どおり登録失敗するか？
      CPPUNIT_ASSERT(! m_mgr->registerECFactory(
						"PeriodicEC",
						RTC::ECCreate<RTC::PeriodicExecutionContext>,
						RTC::ECDelete<RTC::PeriodicExecutionContext>));
    }
		
    /*!
     * @brief getModulesFactories()メソッドのテスト
     * 
     * - 登録されているFactoryの（"implementation_id"プロパティの）リストを正しく取得できるか？
     */
    void test_getModulesFactories()
    {
      // 初期化を行う
      int argc = 0;
      char* argv[] = {};
			
      m_mgr = RTC::Manager::init(argc, argv);
      CPPUNIT_ASSERT(m_mgr != NULL);
			
      // 複数のFactoryを登録しておく
      coil::Properties properties1;
      properties1.setProperty("implementation_id", "ID 1");
      CPPUNIT_ASSERT(m_mgr->registerFactory(
					    properties1, CreateDataFlowComponentMock, DeleteDataFlowComponentMock));

      coil::Properties properties2;
      properties2.setProperty("implementation_id", "ID 2");
      CPPUNIT_ASSERT(m_mgr->registerFactory(
					    properties2, CreateDataFlowComponentMock, DeleteDataFlowComponentMock));
				
      // 登録されているFactoryの（"implementation_id"プロパティの）リストを正しく取得できるか？
      CPPUNIT_ASSERT_EQUAL(2, (int) m_mgr->getModulesFactories().size());
      CPPUNIT_ASSERT(isFound(m_mgr->getModulesFactories(), "ID 1"));
      CPPUNIT_ASSERT(isFound(m_mgr->getModulesFactories(), "ID 2"));
    }
		
    /*!
     * @brief createComponent()メソッドのテスト（DataFlowComponentの場合）
     * 
     * - 正しくコンポーネントを生成できるか？
     */
    void test_createComponent_DataFlowComponent()
    {
      // 初期化を行う
//      int argc = 1;
//      char* argv[] = { "-f fixture4.conf" };
      int argc = 3;
      char* argv[] = { "ManagerTests","-f","fixture4.conf" };
			
      m_mgr = RTC::Manager::init(argc, argv);
      CPPUNIT_ASSERT(m_mgr != NULL);
      CPPUNIT_ASSERT(! CORBA::is_nil(m_mgr->getORB()));
      CPPUNIT_ASSERT(! CORBA::is_nil(m_mgr->getPOA()));
      CPPUNIT_ASSERT(! CORBA::is_nil(m_mgr->getPOAManager()));

      // 非ブロッキングモードでマネージャを作動させる
      CPPUNIT_ASSERT(m_mgr->activateManager());
      m_mgr->runManager(true); // true:非ブロッキング，false:ブロッキング
			
      // Factoryを登録しておく
      coil::Properties properties;
      properties.setProperty("implementation_id", "DataFlowComponentFactory");
      properties.setProperty("type_name", "DataFlowComponent");
      CPPUNIT_ASSERT(m_mgr->registerFactory(
					    properties, CreateDataFlowComponentMock, DeleteDataFlowComponentMock));
			
      // ECFactoryを登録しておく
      CPPUNIT_ASSERT(m_mgr->registerECFactory(
					      "PeriodicEC",
					      RTC::ECCreate<RTC::PeriodicExecutionContext>,
					      RTC::ECDelete<RTC::PeriodicExecutionContext>));
			
      // 正しくコンポーネントを生成できるか？
      RTC::RtcBase* comp = m_mgr->createComponent("DataFlowComponentFactory");
      CPPUNIT_ASSERT(comp != NULL);
      CPPUNIT_ASSERT(dynamic_cast<DataFlowComponentMock*>(comp) != NULL);
      CPPUNIT_ASSERT(! CORBA::is_nil(comp->_this()));
      CPPUNIT_ASSERT_EQUAL(
			   std::string("DataFlowComponent0"), // ※末尾の0はNumberingPolicyにより付加される
			   std::string(comp->getInstanceName()));
			
      // コンポーネントに、意図どおりExecutionContextがアタッチされているか？
      RTC::ExecutionContextList* ecList = comp->get_owned_contexts();
      CPPUNIT_ASSERT(ecList != NULL);
      CPPUNIT_ASSERT_EQUAL(1, (int) ecList->length());
			
      // 生成されたコンポーネントは、正しくネームサービスに登録されているか？
      // ※fixture4.confの各設定に合わせている点に注意
      RTC::NamingManager nmgr(m_mgr);
      const char* name_server = "localhost:2809";
      nmgr.registerNameServer("corba", name_server);
      CPPUNIT_ASSERT(canResolve(name_server, "DataFlowComponent0", "rtc"));
      m_mgr->terminate();
      coil::usleep(3000000);
    }

    void test_createComponent_Non_DataFlowComponent()
    {
      // 現時点では、Manager側がDataFlowComponentのみに対応しているため、テスト省略する
    }
		
    /*!
     * @brief createComponent()メソッドのテスト
     * 
     * - 登録されていないモジュール名を指定してコンポーネント生成を試みて、意図どおりNULLで戻るか？
     * - モジュール名にNULLを指定してコンポーネント生成を試みて、意図どおりNULLで戻るか？
     */
    void test_createComponent_with_illegal_module_name()
    {
      // 初期化を行う
      int argc = 0;
      char* argv[] = {};
			
      m_mgr = RTC::Manager::init(argc, argv);
      CPPUNIT_ASSERT(m_mgr != NULL);
      CPPUNIT_ASSERT(! CORBA::is_nil(m_mgr->getORB()));
      CPPUNIT_ASSERT(! CORBA::is_nil(m_mgr->getPOA()));
      CPPUNIT_ASSERT(! CORBA::is_nil(m_mgr->getPOAManager()));

      // 登録されていないモジュール名を指定してコンポーネント生成を試みて、意図どおりNULLで戻るか？
      RTC::RtcBase* comp1 = m_mgr->createComponent("illegal_module_name");
      CPPUNIT_ASSERT(comp1 == NULL);
			
      // モジュール名にNULLを指定してコンポーネント生成を試みて、意図どおりNULLで戻るか？
      RTC::RtcBase* comp2 = m_mgr->createComponent(NULL);
      CPPUNIT_ASSERT(comp2 == NULL);
    }
		
    void test_createComponent_failed_in_bindExecutionContext()
    {
      // 初期化を行う
//      int argc = 1;
//      char* argv[] = { "-f fixture4.conf" };
      int argc = 3;
      char* argv[] = { "ManagerTests","-f","fixture4.conf" };
			
      m_mgr = RTC::Manager::init(argc, argv);
      CPPUNIT_ASSERT(m_mgr != NULL);
      CPPUNIT_ASSERT(! CORBA::is_nil(m_mgr->getORB()));
      CPPUNIT_ASSERT(! CORBA::is_nil(m_mgr->getPOA()));
      CPPUNIT_ASSERT(! CORBA::is_nil(m_mgr->getPOAManager()));

      // 非ブロッキングモードでマネージャを作動させる
      CPPUNIT_ASSERT(m_mgr->activateManager());
      m_mgr->runManager(true); // true:非ブロッキング，false:ブロッキング
			
      // Factoryを登録しておく
      coil::Properties properties;
      properties.setProperty("implementation_id", "DataFlowComponentFactory");
      properties.setProperty("type_name", "DataFlowComponent");
      CPPUNIT_ASSERT(m_mgr->registerFactory(
					    properties, CreateDataFlowComponentMock, DeleteDataFlowComponentMock));
			
      // bindExecutionContext()で失敗するように、意図的にECFactoryを登録せずにおく
			
      // コンポーネント生成を試みて、意図どおりNULLで戻るか？
      RTC::RtcBase* comp = m_mgr->createComponent("DataFlowComponentFactory");
      CPPUNIT_ASSERT(comp == NULL);
      m_mgr->terminate();
      coil::usleep(3000000);
    }
		
    /*!
     * @brief cleanupComponent()メソッドのテスト
     * 
     * - 登録したコンポーネントが、ネームサービスから正しく登録解除されるか？
     * - 登録したコンポーネントが、Managerから正しく登録解除されるか？
     */
    void test_cleanupComponent()
    {
      // 初期化を行う
//      int argc = 1;
//      char* argv[] = { "-f fixture4.conf" };
      int argc = 3;
      char* argv[] = { "ManagerTests","-f","fixture4.conf" };
			
      m_mgr = RTC::Manager::init(argc, argv);
      CPPUNIT_ASSERT(m_mgr != NULL);
      CPPUNIT_ASSERT(! CORBA::is_nil(m_mgr->getORB()));
      CPPUNIT_ASSERT(! CORBA::is_nil(m_mgr->getPOA()));
      CPPUNIT_ASSERT(! CORBA::is_nil(m_mgr->getPOAManager()));

      // 非ブロッキングモードでマネージャを作動させる
      CPPUNIT_ASSERT(m_mgr->activateManager());
      m_mgr->runManager(true); // true:非ブロッキング，false:ブロッキング
			
      // Factoryを登録しておく
      coil::Properties properties;
      properties.setProperty("implementation_id", "DataFlowComponentFactory");
      properties.setProperty("type_name", "DataFlowComponent");
      CPPUNIT_ASSERT(m_mgr->registerFactory(
					    properties, CreateDataFlowComponentMock, DeleteDataFlowComponentMock));
			
      // ECFactoryを登録しておく
      CPPUNIT_ASSERT(m_mgr->registerECFactory(
					      "PeriodicEC",
					      RTC::ECCreate<RTC::PeriodicExecutionContext>,
					      RTC::ECDelete<RTC::PeriodicExecutionContext>));

      // 確認用にネームサービスへのアクセス手段としてNamingManagerを準備しておく
      // ※fixture4.confの各設定に合わせている点に注意
      RTC::NamingManager nmgr(m_mgr);
      const char* name_server = "localhost:2809";
      nmgr.registerNameServer("corba", name_server);
			
      // 正しくコンポーネントを生成できるか？
      RTC::RtcBase* comp = m_mgr->createComponent("DataFlowComponentFactory");

      CPPUNIT_ASSERT(comp != NULL);
      CPPUNIT_ASSERT(dynamic_cast<DataFlowComponentMock*>(comp) != NULL);
      CPPUNIT_ASSERT(! CORBA::is_nil(comp->_this()));
      CPPUNIT_ASSERT_EQUAL(
			   std::string("DataFlowComponent0"), // ※末尾の0はNumberingPolicyにより付加される
			   std::string(comp->getInstanceName()));
			
      // コンポーネントに、意図どおりExecutionContextがアタッチされているか？
      RTC::ExecutionContextList* ecList = comp->get_owned_contexts();
      CPPUNIT_ASSERT(ecList != NULL);
      CPPUNIT_ASSERT_EQUAL(1, (int) ecList->length());
			
      // cleanupComponent()により、正しく登録解除されるか？
      // - 登録したコンポーネントが、ネームサービスから正しく登録解除されるか？
      // - 登録したコンポーネントが、Managerから正しく登録解除されるか？
      CPPUNIT_ASSERT(canResolve(name_server, "DataFlowComponent0", "rtc"));
      CPPUNIT_ASSERT_EQUAL(comp, m_mgr->getComponent("DataFlowComponent0"));
      m_mgr->cleanupComponent(comp);
      CPPUNIT_ASSERT(! canResolve(name_server, "DataFlowComponent0", "rtc"));
      CPPUNIT_ASSERT(m_mgr->getComponent("DataFlowComponent0") == NULL);

//m_mgr->getORB()->shutdown(true);
//m_mgr->shutdown();
      m_mgr->terminate();
      coil::usleep(3000000);
    }
		
    void test_registerComponent()
    {
      // Manager::createComponent()内で使用されているので、ここではテスト省略する
    }
		
    void test_unregisterComponent()
    {
      // Manager::cleanupComponent()内で使用されているので、ここではテスト省略する
    }
		
    void test_bindExecutionContext()
    {
      // Manager::createComponent()内で使用されているので、ここではテスト省略する
    }
		
    void test_deleteComponent()
    {
      // Manager側が未実装につきテストも未実装
    }
		
    void test_getComponent()
    {
      // 他テスト内で使用されているので、そちらで兼ねるものとして、ここではテスト省略する
    }
		
    /*!
     * @brief getComponents()メソッドのテスト
     * 
     * - getComponents()で、生成したすべてのコンポーネントを取得できるか？
     * - 登録解除したコンポーネントが、正しく一覧から除外されているか？
     */
    void test_getComponents()
    {
      // 初期化を行う
//      int argc = 1;
//      char* argv[] = { "-f fixture4.conf" };
      int argc = 3;
      char* argv[] = { "ManagerTests","-f","fixture4.conf" };
			
      m_mgr = RTC::Manager::init(argc, argv);
      CPPUNIT_ASSERT(m_mgr != NULL);
      CPPUNIT_ASSERT(! CORBA::is_nil(m_mgr->getORB()));
      CPPUNIT_ASSERT(! CORBA::is_nil(m_mgr->getPOA()));
      CPPUNIT_ASSERT(! CORBA::is_nil(m_mgr->getPOAManager()));

      // 非ブロッキングモードでマネージャを作動させる
      CPPUNIT_ASSERT(m_mgr->activateManager());
      m_mgr->runManager(true); // true:非ブロッキング，false:ブロッキング
			
      // Factoryを登録しておく
      coil::Properties properties;
      properties.setProperty("implementation_id", "DataFlowComponentFactory");
      properties.setProperty("type_name", "DataFlowComponent");
      CPPUNIT_ASSERT(m_mgr->registerFactory(
					    properties, CreateDataFlowComponentMock, DeleteDataFlowComponentMock));
			
      // ECFactoryを登録しておく
      CPPUNIT_ASSERT(m_mgr->registerECFactory(
					      "PeriodicEC",
					      RTC::ECCreate<RTC::PeriodicExecutionContext>,
					      RTC::ECDelete<RTC::PeriodicExecutionContext>));
			
      // 複数のコンポーネントを生成しておく
      RTC::RtcBase* comp1 = m_mgr->createComponent("DataFlowComponentFactory");
      CPPUNIT_ASSERT(comp1 != NULL);
      CPPUNIT_ASSERT(dynamic_cast<DataFlowComponentMock*>(comp1) != NULL);
      CPPUNIT_ASSERT(! CORBA::is_nil(comp1->_this()));

      RTC::RtcBase* comp2 = m_mgr->createComponent("DataFlowComponentFactory");
      CPPUNIT_ASSERT(comp2 != NULL);
      CPPUNIT_ASSERT(dynamic_cast<DataFlowComponentMock*>(comp2) != NULL);
      CPPUNIT_ASSERT(! CORBA::is_nil(comp2->_this()));
			
      CPPUNIT_ASSERT(comp1 != comp2);
			
      // getComponents()で、生成したすべてのコンポーネントを取得できるか？
      std::vector<RTC::RtcBase*> comps = m_mgr->getComponents();
      CPPUNIT_ASSERT_EQUAL(2, (int) comps.size());
      CPPUNIT_ASSERT(std::find(comps.begin(), comps.end(), comp1) != comps.end());
      CPPUNIT_ASSERT(std::find(comps.begin(), comps.end(), comp2) != comps.end());
			
      // コンポーネントを１つだけ登録解除した場合、解除したものが一覧から除外されているか？
      m_mgr->cleanupComponent(comp1);
      comps = m_mgr->getComponents();
      CPPUNIT_ASSERT(std::find(comps.begin(), comps.end(), comp1) == comps.end());
      CPPUNIT_ASSERT(std::find(comps.begin(), comps.end(), comp2) != comps.end());
      m_mgr->terminate();
      coil::usleep(3000000);
    }
		
    void test_getORB()
    {
      // 他テスト内で使用されているので、ここではテスト省略する
    }
		
    void test_getPOA()
    {
      // 他テスト内で使用されているので、ここではテスト省略する
    }
		
    void test_getPOAManager()
    {
      // 他テスト内で使用されているので、ここではテスト省略する
    }
		
  };
}; // namespace Tests

/*
 * Register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(Tests::ManagerTests);

#ifdef LOCAL_MAIN
int main(int argc, char* argv[])
{

  FORMAT format = TEXT_OUT;
  int target = 0;
  std::string xsl;
  std::string ns;
  std::string fname;
  std::ofstream ofs;

  int i(1);
  while (i < argc)
    {
      std::string arg(argv[i]);
      std::string next_arg;
      if (i + 1 < argc) next_arg = argv[i + 1];
      else              next_arg = "";

      if (arg == "--text") { format = TEXT_OUT; break; }
      if (arg == "--xml")
	{
	  if (next_arg == "")
	    {
	      fname = argv[0];
	      fname += ".xml";
	    }
	  else
	    {
	      fname = next_arg;
	    }
	  format = XML_OUT;
	  ofs.open(fname.c_str());
	}
      if ( arg == "--compiler"  ) { format = COMPILER_OUT; break; }
      if ( arg == "--cerr"      ) { target = 1; break; }
      if ( arg == "--xsl"       )
	{
	  if (next_arg == "") xsl = "default.xsl"; 
	  else                xsl = next_arg;
	}
      if ( arg == "--namespace" )
	{
	  if (next_arg == "")
	    {
	      std::cerr << "no namespace specified" << std::endl;
	      exit(1); 
	    }
	  else
	    {
	      xsl = next_arg;
	    }
	}
      ++i;
    }
  CppUnit::TextUi::TestRunner runner;
  if ( ns.empty() )
    runner.addTest(CppUnit::TestFactoryRegistry::getRegistry().makeTest());
  else
    runner.addTest(CppUnit::TestFactoryRegistry::getRegistry(ns).makeTest());
  CppUnit::Outputter* outputter = 0;
  std::ostream* stream = target ? &std::cerr : &std::cout;
  switch ( format )
    {
    case TEXT_OUT :
      outputter = new CppUnit::TextOutputter(&runner.result(),*stream);
      break;
    case XML_OUT :
      std::cout << "XML_OUT" << std::endl;
      outputter = new CppUnit::XmlOutputter(&runner.result(),
					    ofs, "shift_jis");
      static_cast<CppUnit::XmlOutputter*>(outputter)->setStyleSheet(xsl);
      break;
    case COMPILER_OUT :
      outputter = new CppUnit::CompilerOutputter(&runner.result(),*stream);
      break;
    }
  runner.setOutputter(outputter);
  runner.run();
  return 0; // runner.run() ? 0 : 1;
}
#endif // MAIN
#endif // ManagerTests_cpp
