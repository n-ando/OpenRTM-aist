// -*- C++ -*-
/*!
 * @file   PropertiesTests.cpp
 * @brief  Properties test class
 * @date   $Date: 2006-11-27 08:23:25 $
 * @author Noriaki Ando <n-ando@aist.go.jp>,
 *         Shinji Kurihara
 *
 *  $Id$
 *
 */

#ifndef Properties_cpp
#define Properties_cpp

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>
#include <fstream>
#include <rtm/Properties.h>

/*!
 * @class PropertiesTests class
 * @brief Properties test
 */
using namespace std;

typedef std::map<std::string, std::string>::iterator Itr;

namespace Properties
{
  class PropertiesTests
   : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(PropertiesTests);
    
    // Properties()でインスタンスを生成した場合のテスト
    CPPUNIT_TEST(test_Properties);
    
    // Properties(const std::map<std::string, std::string>& defaults)で
    // インスタンスを生成した場合のテスト
    CPPUNIT_TEST(test_Properties_map);
    
    // Properties(const char* defaults[], long num = LONG_MAX)で
    // インスタンスを生成した場合のテスト
    CPPUNIT_TEST(test_Properties_char);
    
    // list()のテスト
    CPPUNIT_TEST(test_list);
    
    // load()のテスト
    CPPUNIT_TEST(test_load);
    
    // store()のテスト
    CPPUNIT_TEST(test_store);
    
    // splitKeyValue()のテスト
    CPPUNIT_TEST(test_splitKeyValue);
    
    CPPUNIT_TEST_SUITE_END();
    
  private:
    RTC::Properties* m_prop;
    
  public:
    
    /*!
     * @brief Constructor
     */
    PropertiesTests()
    {
    }
    
    /*!
     * @brief Destructor
     */
    ~PropertiesTests()
    {
    }
    
    /*!
     * @brief Test initialization
     */
    virtual void setUp()
    {
    }
    
    /*!
     * @brief Test finalization
     */
    virtual void tearDown()
    { 
    }
    
    //===========================================================================
    // bind() tests for Properties::Properties()
    // 引数を取らないコンストラクタの場合のテスト
    //===========================================================================
    void test_Properties()
    {
      RTC::Properties pProp;
      
      //===================================================================================
      // test: getProperty() method.
      //===================================================================================
      test_getPropertyNoDefaultValue(pProp);
      
      //===================================================================================
      // test: setProperty() method.
      //===================================================================================
      test_setProperty(pProp);
      
      //===================================================================================
      // test: getProperty() method.
      //===================================================================================
      test_getPropertyAfterSetPropertyNoDefaultValue(pProp);
      
      //===================================================================================
      // test: propertyNames() method.
      //===================================================================================
      test_propertyNames(pProp.propertyNames());
      
      // プロパティリストをファイルに書き込む。
      std::ofstream of2("new.conf");
      pProp.store(of2, "new settings");
      of2.close();
      // store()によりファイルに書き込まれたプロパティリストの確認。 store()のテスト
      test_storedDataNoDefaultValue();
    }
    
    
    
    //=============================================================================================
    // bind() tests for Properties::Properties(const std::map<std::string, std::string>& defaults)
    // mapを引数に取るコンストラクタの場合のテスト
    //============================================================================================
    void test_Properties_map()
    {
      map<string, string> props;
      props["rtc.openrtm.version"]         = "0.4.0";
      props["rtc.openrtm.release"]         = "aist";
      props["rtc.openrtm.vendor"]          = "AIST";
      props["rtc.openrtm.author"]          = "Noriaki Ando";
      props["rtc.manager.nameserver"]      = "zonu.a02.aist.go.jp";
      props["rtc.manager.debug.level"]     = "PARANOID";
      props["rtc.manager.orb"]             = "omniORB";
      props["rtc.manager.orb.options"]     = "IIOPAddrPort, -ORBendPoint, giop:tcp:";
      props["rtc.manager.arch"]            = "i386";
      props["rtc.manager.os"]              = "FreeBSD";
      props["rtc.manager.os.release"]      = "6.1-RELEASE";
      props["rtc.manager.language"]        = "C++";
      props["rtc.manager.subsystems"]      = "Camera, Manipulator, Force Sensor";
      props["rtc.component.conf.path"]     = "C:\\\\Program\\\\ Files\\\\OpenRTM-aist";
      props["rtc.manager.opening_message"] = "\"Hello World\"";
      
      
      RTC::Properties pProp(props);
      
      //===================================================================================
      // test: getProperty() method.
      //===================================================================================
      test_getPropertyDefault(pProp);
      
      // プロパティリストをファイルから読み込む。 load()のテスト
      //    std::ifstream if1("defaults.conf");
      //    pProp.load(if1);
      //    if1.close();
      
      //===================================================================================
      // test: setProperty() method.
      //===================================================================================
      test_setProperty(pProp);
      
      //===================================================================================
      // test: propertyNames() method.
      //===================================================================================
      test_propertyNames(pProp.propertyNames());
      
      //===================================================================================
      // test: getProperty() method.
      //===================================================================================
      test_getPropertyAfterSetProperty(pProp);
      
      // プロパティリストをファイルに書き込む。
      std::ofstream of2("new.conf");
      pProp.store(of2, "new settings");
      of2.close();
      // store()によりファイルに書き込まれたプロパティリストの確認。 store()のテスト
      test_storedData();
    }
    
    
    
    //============================================================================
    // bind() tests  for Properties::Properties(const char* defaults[], long num)
    // char*[]を引数に取るコンストラクタの場合のテスト
    //============================================================================
    void test_Properties_char()
    {
      const char* props[] = {
	"rtc.openrtm.version", "0.4.0",
	"rtc.openrtm.release", "aist",
	"rtc.openrtm.vendor", "AIST",
	"rtc.openrtm.author", "Noriaki Ando",
	"rtc.manager.nameserver", "zonu.a02.aist.go.jp",
	"rtc.manager.debug.level", "PARANOID",
	"rtc.manager.orb", "omniORB",
	"rtc.manager.orb.options", "IIOPAddrPort, -ORBendPoint, giop:tcp:",
	"rtc.manager.arch", "i386",
	"rtc.manager.os", "FreeBSD",
	"rtc.manager.os.release", "6.1-RELEASE",
	"rtc.manager.language", "C++",
	"rtc.manager.subsystems", "Camera, Manipulator, Force Sensor",
	"rtc.component.conf.path", "C:\\\\Program\\\\ Files\\\\OpenRTM-aist",
	"rtc.manager.opening_message", "\"Hello World\"",
	""};
      
      RTC::Properties pProp(props);
      
      //===================================================================================
      // test: getProperty() method.
      //===================================================================================
      test_getPropertyDefault(pProp);
      
      //===================================================================================
      // test: constructorArgs -> write-to-"defaults.conf"(method: store) -> 
      //       read-from-"defaults.conf"(method: load) -> write-to-"new.conf"(method: save)
      //===================================================================================
      //    std::ofstream of1("defaults.conf");
      //    pProp.store(of1, "defaults settings");
      //    of1.close();
      
      // プロパティリストをファイルから読み込む。 load()のテスト
      //    std::ifstream if1("defaults.conf");
      //    pProp.load(if1);
      //    if1.close();
      
      //===================================================================================
      // test: getProperty() method.
      //===================================================================================
      test_getPropertyDefault(pProp);
      
      //===================================================================================
      // test: setProperty() method.
      //===================================================================================
      test_setProperty(pProp);
      
      //===================================================================================
      // test: propertyNames() method.
      //===================================================================================
      test_propertyNames(pProp.propertyNames());
      
      //===================================================================================
      // test: getProperty() method.
      //===================================================================================
      test_getPropertyAfterSetProperty(pProp);
      
      // プロパティリストをファイルに書き込む。
      std::ofstream of2("new.conf");
      pProp.store(of2, "new settings");
      of2.close();
      // store()によりファイルに書き込まれたプロパティリストの確認。 store()のテスト
      test_storedData();
    }
    
    
    
    // splitKeyValue()メソッドのテスト
    void test_splitKeyValue() {
      class P : public RTC::Properties
      {
      public:
	void splitKeyValue_protected(const std::string& str, std::string& key,
				     std::string& value)
	{
	  splitKeyValue(str, key, value);
	}
      };
      P p;
      string str, key, value, retk, retv;
      std::ifstream ifs("splitKeyValueTest.data");
      getline(ifs, str);
      getline(ifs, retk);
      getline(ifs, retv);
      ifs.close();
      
      p.splitKeyValue_protected(str, key, value);
      
      CPPUNIT_ASSERT(key == retk);
      CPPUNIT_ASSERT(value == retv);
    }
    
    
    void test_list() {
      m_prop = new RTC::Properties();
      
      // プロパティリストをファイルから読み込む。 load()のテスト
      std::ifstream ifl("defaults.conf");
      m_prop->load(ifl);
      ifl.close();
      
      cout << endl;
      m_prop->list(std::cout);
      delete m_prop;
    }
    
    
    void test_load() {
      m_prop = new RTC::Properties();
      
      // プロパティリストをファイルから読み込む。 load()のテスト
      std::ifstream ifl("defaults.conf");
      m_prop->load(ifl);
      ifl.close();
      
      test_getPropertyDefault();
      
      delete m_prop;
    }
    
    
    
    // store()メソッドのテスト
    void test_store() {
      
      m_prop = new RTC::Properties();
      
      std::ifstream iff1("storedRead.conf");
      m_prop->load(iff1);
      iff1.close();
      
      // プロパティリストをファイルに書き込む。 store()のテスト
      std::ofstream off("stored.conf");
      m_prop->store(off, "stored data");
      off.close();
      test_checkStoredData();
      
      delete m_prop;
    }
    
    
    
    // store()メソッドのテスト
    void test_checkStoredData() {
      string p1,p2;
      
      std::ifstream iff("store-test.data");
      
      string str;
      vector<string> prop;
      
      while(getline(iff,str)) {
	prop.push_back(str);
      }
      
      iff.close();
      
      // store()によりファイルに書き込まれたプロパティリスト
      std::ifstream if1("stored.conf");
      
      vector<string> vs;
      vs.push_back("# stored data");
      vs.push_back("rtc.component.conf.path = " + prop[0]);
      vs.push_back("rtc.manager.arch = " + prop[1]);
      vs.push_back("rtc.manager.debug.level = " + prop[2]);
      vs.push_back("rtc.manager.language = " + prop[3]);
      vs.push_back("rtc.manager.nameserver = " + prop[4]);
      vs.push_back("rtc.manager.opening_message = " + prop[5]);
      vs.push_back("rtc.manager.orb = " + prop[6]);
      vs.push_back("rtc.manager.orb.options = " + prop[7]);
      vs.push_back("rtc.manager.os = " + prop[8]);
      vs.push_back("rtc.manager.os.release = " + prop[9]);
      vs.push_back("rtc.manager.subsystems = " + prop[10]);
      vs.push_back("rtc.openrtm.author = " + prop[11]);
      vs.push_back("rtc.openrtm.release = " + prop[12]);
      vs.push_back("rtc.openrtm.vendor = " + prop[13]);
      vs.push_back("rtc.openrtm.version = " + prop[14]);
      
      vector<string>::iterator it    (vs.begin());
      vector<string>::iterator it_end(vs.end());
      
      while (it != it_end) {
	getline(if1,p1);
	CPPUNIT_ASSERT(p1 == (*it));
	++it;
      }
      
      if1.close();
    }
    
    
    
    // store()メソッドのテストtest_Properties()用
    void test_storedDataNoDefaultValue() {
      string p1,p2;
      
      // store()によりファイルに書き込まれたプロパティリスト
      std::ifstream if1("new.conf");
      
      vector<string> vs;
      vs.push_back("# new settings");
      vs.push_back("rtc.component.conf.path = ");
      vs.push_back("rtc.manager.arch = ");
      vs.push_back("rtc.manager.debug.level = ");
      vs.push_back("rtc.manager.language = Python");
      vs.push_back("rtc.manager.nameserver = ");
      vs.push_back("rtc.manager.opening_message = \"Hello RT World\"");
      vs.push_back("rtc.manager.orb = ");
      vs.push_back("rtc.manager.orb.options = ");
      vs.push_back("rtc.manager.os = ");
      vs.push_back("rtc.manager.os.release = ");
      vs.push_back("rtc.manager.subsystems = ");
      vs.push_back("rtc.openrtm.author = ");
      vs.push_back("rtc.openrtm.release = ");
      vs.push_back("rtc.openrtm.vendor = ");
      vs.push_back("rtc.openrtm.version = ");
      
      vector<string>::iterator it    (vs.begin());
      vector<string>::iterator it_end(vs.end());
      
      
      while (it != it_end) {
	getline(if1,p1);
	CPPUNIT_ASSERT(p1 == (*it));
	++it;
      }
      
      if1.close();
    }
    
    
    
    // store()メソッドのテスト
    void test_storedData() {
      string p1,p2;
      
      // store()によりファイルに書き込まれたプロパティリスト
      std::ifstream if1("new.conf");
      
      vector<string> vs;
      vs.push_back("# new settings");
      vs.push_back("rtc.component.conf.path = C:\\\\Program\\\\ Files\\\\OpenRTM-aist");
      vs.push_back("rtc.manager.arch = i386");
      vs.push_back("rtc.manager.debug.level = PARANOID");
      vs.push_back("rtc.manager.language = Python");
      vs.push_back("rtc.manager.nameserver = zonu.a02.aist.go.jp");
      vs.push_back("rtc.manager.opening_message = \"Hello RT World\"");
      vs.push_back("rtc.manager.orb = omniORB");
      vs.push_back("rtc.manager.orb.options = IIOPAddrPort, -ORBendPoint, giop:tcp:");
      vs.push_back("rtc.manager.os = FreeBSD");
      vs.push_back("rtc.manager.os.release = 6.1-RELEASE");
      vs.push_back("rtc.manager.subsystems = Camera, Manipulator, Force Sensor");
      vs.push_back("rtc.openrtm.author = Noriaki Ando");
      vs.push_back("rtc.openrtm.release = aist");
      vs.push_back("rtc.openrtm.vendor = AIST");
      vs.push_back("rtc.openrtm.version = 0.4.0");
      
      vector<string>::iterator it    (vs.begin());
      vector<string>::iterator it_end(vs.end());
      
      while (it != it_end) {
	getline(if1,p1);
	CPPUNIT_ASSERT(p1 == (*it));
	++it;
      }
      
      if1.close();
    }
    
    
    
    // getProperty()のメソッドのテスト test_Properties()用
    // Propertiesクラスのオブジェクト生成時にデフォルト値を与えてない場合。
    void test_getPropertyNoDefaultValue(RTC::Properties& pProp) {
      
      // getProperty()で得られる値の期待値リスト
      map<string, string> prof;
      prof["rtc.openrtm.version"] = "";
      prof["rtc.openrtm.release"] = "";
      prof["rtc.openrtm.vendor"] = "";
      prof["rtc.openrtm.author"] = "";
      prof["rtc.manager.nameserver"] = "";
      prof["rtc.manager.debug.level"] = "";
      prof["rtc.manager.orb"] = "";
      prof["rtc.manager.orb.options"] = "";
      prof["rtc.manager.arch"] = "";
      prof["rtc.manager.os"] = "";
      prof["rtc.manager.os.release"] = "";
      prof["rtc.manager.language"] = "";
      prof["rtc.manager.subsystems"] = "";
      prof["rtc.component.conf.path"] = "";
      prof["rtc.manager.opening_message"] = "";
      
      map<string, string>::iterator it    (prof.begin());
      map<string, string>::iterator it_end(prof.end());
      
      while(it != it_end) {
	CPPUNIT_ASSERT(pProp.getProperty(it->first) == it->second);
	++it;
      }
    }
    
    
    
    // getProperty()のメソッドのテスト test_load()のためのメソッド
    void test_getPropertyDefault() {
      
      // getProperty()で得られる値の期待値リスト
      map<string, string> prof;
      prof["rtc.openrtm.version"] = "0.4.0";
      prof["rtc.openrtm.release"] = "aist";
      prof["rtc.openrtm.vendor"] = "AIST";
      prof["rtc.openrtm.author"] = "Noriaki Ando";
      prof["rtc.manager.nameserver"] = "zonu.a02.aist.go.jp";
      prof["rtc.manager.debug.level"] = "PARANOID";
      prof["rtc.manager.orb"] = "omniORB";
      prof["rtc.manager.orb.options"] = "IIOPAddrPort, -ORBendPoint, giop:tcp:";
      prof["rtc.manager.arch"] = "i386";
      prof["rtc.manager.os"] = "FreeBSD";
      prof["rtc.manager.os.release"] = "6.1-RELEASE";
      prof["rtc.manager.language"] = "C++";
      prof["rtc.manager.subsystems"] = "Camera, Manipulator, Force Sensor";
      prof["rtc.component.conf.path"] = "C:\\\\Program\\\\ Files\\\\OpenRTM-aist";
      prof["rtc.manager.opening_message"] = "\"Hello \" World\"";
      
      map<string, string>::iterator it    (prof.begin());
      map<string, string>::iterator it_end(prof.end());
      
      while(it != it_end) {
	CPPUNIT_ASSERT(m_prop->getProperty(it->first) == it->second);
	++it;
      }
      
    }
    
    
    
    // getProperty()のメソッドのテスト
    void test_getPropertyDefault(RTC::Properties& pProp) {
      
      // getProperty()で得られる値の期待値リスト
      map<string, string> prof;
      prof["rtc.openrtm.version"] = "0.4.0";
      prof["rtc.openrtm.release"] = "aist";
      prof["rtc.openrtm.vendor"] = "AIST";
      prof["rtc.openrtm.author"] = "Noriaki Ando";
      prof["rtc.manager.nameserver"] = "zonu.a02.aist.go.jp";
      prof["rtc.manager.debug.level"] = "PARANOID";
      prof["rtc.manager.orb"] = "omniORB";
      prof["rtc.manager.orb.options"] = "IIOPAddrPort, -ORBendPoint, giop:tcp:";
      prof["rtc.manager.arch"] = "i386";
      prof["rtc.manager.os"] = "FreeBSD";
      prof["rtc.manager.os.release"] = "6.1-RELEASE";
      prof["rtc.manager.language"] = "C++";
      prof["rtc.manager.subsystems"] = "Camera, Manipulator, Force Sensor";
      prof["rtc.component.conf.path"] = "C:\\\\Program\\\\ Files\\\\OpenRTM-aist";
      prof["rtc.manager.opening_message"] = "\"Hello World\"";
      
      map<string, string>::iterator it    (prof.begin());
      map<string, string>::iterator it_end(prof.end());
      
      while(it != it_end) {
	CPPUNIT_ASSERT(pProp.getProperty(it->first) == it->second);
	++it;
      }
    }
    
    
    
    // getProperty()のメソッドのテスト test_Properties()用
    // ※ このテストでは、setProperty()メソッドの後に呼ばれると仮定し、"rtc.manager.language"と
    //    "rtc.manager.opening_message"をそれぞれ"Python","\"Hello RT World\""としている。
    void test_getPropertyAfterSetPropertyNoDefaultValue(RTC::Properties& pProp) {
      
      // getProperty()で得られる値の期待値リスト
      map<string, string> prof;
      prof["rtc.openrtm.version"] = "";
      prof["rtc.openrtm.release"] = "";
      prof["rtc.openrtm.vendor"] = "";
      prof["rtc.openrtm.author"] = "";
      prof["rtc.manager.nameserver"] = "";
      prof["rtc.manager.debug.level"] = "";
      prof["rtc.manager.orb"] = "";
      prof["rtc.manager.orb.options"] = "";
      prof["rtc.manager.arch"] = "";
      prof["rtc.manager.os"] = "";
      prof["rtc.manager.os.release"] = "";
      prof["rtc.manager.language"] = "Python";
      prof["rtc.manager.subsystems"] = "";
      prof["rtc.component.conf.path"] = "";
      prof["rtc.manager.opening_message"] = "\"Hello RT World\"";
      
      map<string, string>::iterator it    (prof.begin());
      map<string, string>::iterator it_end(prof.end());
      
      while(it != it_end) {
	CPPUNIT_ASSERT(pProp.getProperty(it->first) == it->second);
	++it;
      }
    }
    
    
    
    // getProperty()のメソッドのテスト
    // ※ このテストでは、setProperty()メソッドの後に呼ばれると仮定し、"rtc.manager.language"と
    //    "rtc.manager.opening_message"をそれぞれ"Python","\"Hello RT World\""としている。
    void test_getPropertyAfterSetProperty(RTC::Properties& pProp) {
      
      // getProperty()で得られる値の期待値リスト
      map<string, string> prof;
      prof["rtc.openrtm.version"] = "0.4.0";
      prof["rtc.openrtm.release"] = "aist";
      prof["rtc.openrtm.vendor"] = "AIST";
      prof["rtc.openrtm.author"] = "Noriaki Ando";
      prof["rtc.manager.nameserver"] = "zonu.a02.aist.go.jp";
      prof["rtc.manager.debug.level"] = "PARANOID";
      prof["rtc.manager.orb"] = "omniORB";
      prof["rtc.manager.orb.options"] = "IIOPAddrPort, -ORBendPoint, giop:tcp:";
      prof["rtc.manager.arch"] = "i386";
      prof["rtc.manager.os"] = "FreeBSD";
      prof["rtc.manager.os.release"] = "6.1-RELEASE";
      prof["rtc.manager.language"] = "Python";
      prof["rtc.manager.subsystems"] = "Camera, Manipulator, Force Sensor";
      prof["rtc.component.conf.path"] = "C:\\\\Program\\\\ Files\\\\OpenRTM-aist";
      prof["rtc.manager.opening_message"] = "\"Hello RT World\"";
      
      map<string, string>::iterator it    (prof.begin());
      map<string, string>::iterator it_end(prof.end());
      
      while(it != it_end) {
	CPPUNIT_ASSERT(pProp.getProperty(it->first) == it->second);
	++it;
      }
    }
    
    
    
    // propertyNames()メソッドのテスト。
    // このメソッドも、このテストではsetProperty()の後に呼ばれると仮定している。
    void test_propertyNames(vector<string> vs) {
      
      // プロパティのキーのリスト
      vector<string> keys;
      keys.push_back("rtc.openrtm.version");
      keys.push_back("rtc.openrtm.release");
      keys.push_back("rtc.openrtm.vendor");
      keys.push_back("rtc.openrtm.author");
      keys.push_back("rtc.manager.nameserver");
      keys.push_back("rtc.manager.debug.level");
      keys.push_back("rtc.manager.orb");
      keys.push_back("rtc.manager.orb.options");
      keys.push_back("rtc.manager.arch");
      keys.push_back("rtc.manager.os");
      keys.push_back("rtc.manager.os.release");
      keys.push_back("rtc.manager.language");
      keys.push_back("rtc.manager.subsystems");
      keys.push_back("rtc.component.conf.path");
      keys.push_back("rtc.manager.opening_message");
      
      vector<string>::iterator it_key    (keys.begin());
      vector<string>::iterator it_key_end(keys.end());
      
      while (it_key != it_key_end) {
	vector<string>::iterator it_vs    (vs.begin());
	vector<string>::iterator it_vs_end(vs.end());
	int flag = 0;
	while (it_vs != it_vs_end) {
	  if ((*it_key) == (*it_vs))
	    flag = 1;
	  ++it_vs;
	}
	
	CPPUNIT_ASSERT_MESSAGE("Not found key.", flag == 1);
	++it_key;
      }
    }
    
    
    
    // setProperty()メソッドのテスト
    void test_setProperty(RTC::Properties& pProp) {
      string key, value, target;
      
      key    = "rtc.manager.opening_message";
      value  = "\"Hello RT World\"";
      target = pProp.getProperty("rtc.manager.opening_message");
      CPPUNIT_ASSERT(pProp.setProperty(key, value) == target);
      
      key    = "rtc.manager.language";
      value  ="Python";
      target = pProp.getProperty("rtc.manager.language");
      CPPUNIT_ASSERT(pProp.setProperty(key, value) == target);
    }
    
    
    
    /*
    // eraseHeadBlank()メソッドのテスト
    void test_eraseHeadBlank() {
    //    string str(" \t \t\t\t \t \t test");
    //    string ret("test");
    
    string str, ret;
    std::ifstream ifs("eraseHeadBlankTest.data");
    getline(ifs, str);
    getline(ifs, ret);
    ifs.close();
    
    eraseHeadBlank(str);
    
    CPPUNIT_ASSERT(str == ret);
    }
    
    
    // eraseTailBlank()メソッドのテスト
    void test_eraseTailBlank() {
    //    string str("test \t\t\t \t\t\t \t\t");
    //    string ret("test");
    
    string str, ret;
    std::ifstream ifs("eraseTailBlankTest.data");
    getline(ifs, str);
    getline(ifs, ret);
    ifs.close();
    
    eraseTailBlank(str);
    
    CPPUNIT_ASSERT(str == ret);
    }
    
    
    // replaceStr()メソッドのテスト
    void test_replaceStr() {
    //    string str(" \t\t\ttest\t\t TEST");
    //    string from("\t");
    //    string to("tab");
    //    string ret(" tabtabtabtesttabtab TEST");
    
    string str, from, to, ret;
    std::ifstream ifs("replaceStrTest.data");
    getline(ifs, str);
    getline(ifs, from);
    getline(ifs, to);
    getline(ifs, ret);
    ifs.close();
    replaceStr(str, from, to);
    CPPUNIT_ASSERT(str == ret);
    }
    */
    
  };
}; // namespace Properties

/*
 * Register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(Properties::PropertiesTests);

#ifdef LOCAL_MAIN
int main(int argc, char* argv[])
{
  CppUnit::TextUi::TestRunner runner;
  runner.addTest(CppUnit::TestFactoryRegistry::getRegistry().makeTest());
  CppUnit::Outputter* outputter = 
    new CppUnit::TextOutputter(&runner.result(), std::cout);
  runner.setOutputter(outputter);
  bool retcode = runner.run();
  return !retcode;
}
#endif // MAIN
#endif // Properties_cpp
