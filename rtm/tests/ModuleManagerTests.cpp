// -*- C++ -*-
/*!
 * @file ModuleManagerTests.cpp
 * @brief ModuleManager class test
 * @date $Date: 2006-09-20 08:52:19 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: ModuleManagerTests.cpp,v 1.1 2006-09-20 08:52:19 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 *
 */

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>
#include <fstream>
#include "../ModuleManager.h"
#include "../Properties.h"

using namespace std;

class ModuleManagerTest
  : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(ModuleManagerTest);
  CPPUNIT_TEST(test_findFile);
  CPPUNIT_TEST(test_fileExist);
  CPPUNIT_TEST(test_getInitFuncName);
  CPPUNIT_TEST(test_load);
  CPPUNIT_TEST(test_getLoadedModules);
  CPPUNIT_TEST_SUITE_END();
private:
  
  ModuleManager* m_pModMgr;
  
public:
  
  /*
   * コンストラクタ/デストラクタ [7]
   */
  ModuleManagerTest()
  {

  }
  
  ~ModuleManagerTest()
  {
  }
  
  /*
   * 初期化/後始末 [8]
   */
  virtual void setUp()
  {
    const char* default_properties[] = {
      "manager.modules.config_ext", "so",
      "manager.modules.config_path", "/etc/rtc",
      "manager.modules.detect_loadable", "Yes",
      "manager.modules.load_path", "/usr/lib, /usr/local/lib, /usr/local/lib/rtc",
      "manager.modules.init_func_suffix", "Init",
      "manager.modules.init_func_prefix", "",
      "manager.modules.abs_path_allowed", "Yes",
      "manager.modules.download_allowed", "Yes",
      "manager.modules.download_dir", "/tmp/rtc",
      "manager.modules.download_cleanup", "Yes",
      "manager.modules.preload", "",
      ""
    };

    Properties prop(default_properties);
    m_pModMgr = new ModuleManager(prop);
  }
  
  virtual void tearDown()
  { 
    delete m_pModMgr;
  }
  

  void test_fileExist()
  {
    bool result;

    // Success case
    result = m_pModMgr->fileExist("/etc/hosts");
    CPPUNIT_ASSERT_MESSAGE("fileExist failed", result);

    result = m_pModMgr->fileExist("./ModuleManagerTests.cpp");
    CPPUNIT_ASSERT_MESSAGE("fileExist failed", result);

    result = m_pModMgr->fileExist("../ModuleManager.cpp");
    CPPUNIT_ASSERT_MESSAGE("fileExist failed", result);

    result = m_pModMgr->fileExist("../tests/ModuleManagerTests.cpp");
    CPPUNIT_ASSERT_MESSAGE("fileExist failed", result);


    // Failure case
    result = m_pModMgr->fileExist("/etc/munya/hoge");
    CPPUNIT_ASSERT_MESSAGE("fileExist error", !result);

    result = m_pModMgr->fileExist("./aaaaaaaaaaaaaaaaaaaaaaaaaaaa");
    CPPUNIT_ASSERT_MESSAGE("fileExist error", !result);

    result = m_pModMgr->fileExist("../../../../../../../../../a");
    CPPUNIT_ASSERT_MESSAGE("fileExist error", !result);

    result = m_pModMgr->fileExist("C:\\Program Files\\munya");
    CPPUNIT_ASSERT_MESSAGE("fileExist error", !result);

  }

  void test_findFile()
  {
    std::string result;
    std::vector<std::string> path;
    path.push_back("/lib");
    path.push_back("/usr/lib");
    path.push_back("/usr/local/lib");

    result = m_pModMgr->findFile("libm.so", path);
    //    std::cout << result << std::endl;
    CPPUNIT_ASSERT_MESSAGE("fileFile error: libm.so",
			   result == "/usr/lib/libm.so");

    result = m_pModMgr->findFile("libc.so", path);
    CPPUNIT_ASSERT_MESSAGE("fileFile error: libc.so",
			   result == "/usr/lib/libc.so");

    result = m_pModMgr->findFile("libACE.so", path);
    CPPUNIT_ASSERT_MESSAGE("fileFile error: libACE.so",
			   result == "/usr/local/lib/libACE.so");

    result = m_pModMgr->findFile("hosts", path);
    CPPUNIT_ASSERT_MESSAGE("fileFile error: hosts",
			   result == "");

    result = m_pModMgr->findFile("munyamunya", path);
    CPPUNIT_ASSERT_MESSAGE("fileFile error: munyamunya",
			   result == "");

  }


  void test_getInitFuncName()
  {
    std::string result;

    result = m_pModMgr->getInitFuncName("Manipulator");
    CPPUNIT_ASSERT_MESSAGE("getInitFuncName error: Manipulator",
			   result == "ManipulatorInit");

    result = m_pModMgr->getInitFuncName("PHANToM");
    CPPUNIT_ASSERT_MESSAGE("getInitFuncName error: PHANToM",
			   result == "PHANToMInit");

  }

  //======================================================================
  // load() tests
  //======================================================================
  void test_load()
  {
    std::vector<std::string> loadpath;
    loadpath = m_pModMgr->getLoadPath();

    for (unsigned int i = 0 ; i < loadpath.size(); ++i)
      {
	//	std::cout << "loadpath: " << loadpath[i] << std::endl;
      }


    std::string libname;
    try
      {
	libname = m_pModMgr->load("libm.so");
	//	std::cout << "test_load: " << libname << std::endl;
      }
    catch (ModuleManager::Error& e)
      {
	std::cout << "Error " << e.reason << std::endl;
      }
    catch (ModuleManager::NotFound& e)
      {
	std::cout << "NotFound " << e.name << std::endl;
      }
    catch (...)
      {
	std::cout << "other exception" << std::endl;
      }

    typedef double (*cosine)(double);
    typedef double (*sine)(double);

    cosine _cos;
    sine   _sin;

    _cos = (cosine) m_pModMgr->symbol(libname, "cos");
    //    std::cout << (*_cos)(0.0) << std::endl;
    //    std::cout << (*_cos)(3.141592653589793238462643383279/2) << std::endl;
    CPPUNIT_ASSERT_MESSAGE("load error: cos(0.0)",
			   (*_cos)(0.0) == 1.0);
    CPPUNIT_ASSERT_MESSAGE("load error: cos(pi/2)",
			   (*_cos)(3.141592653589793238462643383279/2) < 0.01);

    _sin = (sine) m_pModMgr->symbol(libname, "sin");
    //    std::cout << (*_sin)(0.0) << std::endl;
    //    std::cout << (*_sin)(3.141592653589793238462643383279/2) << std::endl;
    CPPUNIT_ASSERT_MESSAGE("load error: sin(0.0)",
			   (*_sin)(0.0) == 0.0);
    CPPUNIT_ASSERT_MESSAGE("load error: sin(pi/2)",
			   (*_sin)(3.141592653589793238462643383279/2) == 1.0);

    m_pModMgr->unload(libname);
  }

  void test_getLoadedModules()
  {
    std::string name;
    name = m_pModMgr->load("/usr/lib/libm.so");
    //    std::cout << "load(): " << name << std::endl;
    name = m_pModMgr->load("libc.so");
    //    std::cout << "load(): " << name << std::endl;
    name = m_pModMgr->load("/usr/local/lib/libACE.so");
    //    std::cout << "load(): " << name << std::endl;
    name = m_pModMgr->load("libboost_regex.so");
    //    std::cout << "load(): " << name << std::endl;
    name = m_pModMgr->load("/usr/local/lib/libomniORB4.so");
    //    std::cout << "load(): " << name << std::endl;

    std::vector<std::string> module;
    
    module = m_pModMgr->getLoadedModules();

    for (unsigned int i = 0; i < module.size(); i++)
      {
	//	std::cout << "test_getLoadedModules(): " << module[i] << std::endl;
      }
#define FOUND(path) find(module.begin(), module.end(), path) != module.end()

    CPPUNIT_ASSERT_MESSAGE("getLoadedModules error: /usr/lib/libm.so",
			   FOUND("/usr/lib/libm.so"));

    CPPUNIT_ASSERT_MESSAGE("getLoadedModules error: /usr/lib/libc.so",
			   FOUND("/usr/lib/libc.so"));

    CPPUNIT_ASSERT_MESSAGE("getLoadedModules error: /usr/local/lib/libACE.so",
			   FOUND("/usr/local/lib/libACE.so"));

    CPPUNIT_ASSERT_MESSAGE("getLoadedModules error: /usr/local/lib/libboost_regex.so",
			   FOUND("/usr/local/lib/libboost_regex.so"));

    CPPUNIT_ASSERT_MESSAGE("getLoadedModules error: /usr/local/lib/libomniORB4.so",
			   FOUND("/usr/local/lib/libomniORB4.so"));


    // UnloadAll() test
    m_pModMgr->unloadAll();

    module = m_pModMgr->getLoadedModules();

    // list of loaded modules should be size 0;
    CPPUNIT_ASSERT_MESSAGE("unloadAll error:",
			   module.size() == 0);

  }

};
/*
 * register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(ModuleManagerTest);




int main(int argc, char* argv[])
{
    CppUnit::TextUi::TestRunner runner;

    runner.addTest(CppUnit::TestFactoryRegistry::getRegistry().makeTest());
    CppUnit::Outputter* outputter = 
      new CppUnit::TextOutputter(&runner.result(), std::cout);
    runner.setOutputter(outputter);
   
    return runner.run();
}
