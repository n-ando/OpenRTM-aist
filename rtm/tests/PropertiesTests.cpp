// -*- C++ -*-
/*!
 * @file PropertiesTests.cpp
 * @brief Properties test class
 * @date $Date: 2006-10-16 13:12:21 $
 * @author Shinji Kurihara
 * $Id: PropertiesTests.cpp,v 1.2 2006-10-16 13:12:21 kurihara Exp $
 *
 */

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>
#include <fstream>
#include "../Properties.h"

using namespace std;

typedef std::map<std::string, std::string>::iterator Itr;

// XXX をテストする [3]
class PropertiesTest
  : public CppUnit::TestFixture, public RTC::Properties
{
  CPPUNIT_TEST_SUITE(PropertiesTest);
  CPPUNIT_TEST(test_Properties);
  CPPUNIT_TEST(test_Properties_map);
  CPPUNIT_TEST(test_Properties_char);
  CPPUNIT_TEST(test_eraseHeadBlank);
  CPPUNIT_TEST(test_eraseTailBlank);
  CPPUNIT_TEST(test_replaceStr);
  CPPUNIT_TEST(test_splitKeyValue);
  CPPUNIT_TEST_SUITE_END();

private:
  map<string, string> m_map;
  vector<string>      m_keys;
  
public:
  
  /*
   * コンストラクタ/デストラクタ [7]
   */
  PropertiesTest()
  {
    
  }
  
  ~PropertiesTest()
  {
  }
  
  /*
   * 初期化/後始末 [8]
   */
  virtual void setUp()
  {
    m_map["rtc.openrtm.version"]         = "0.4.0";
    m_map["rtc.openrtm.release"]         = "aist";
    m_map["rtc.openrtm.vendor"]          = "AIST";
    m_map["rtc.openrtm.author"]          = "Noriaki Ando";
    m_map["rtc.manager.nameserver"]      = "zonu.a02.aist.go.jp";
    m_map["rtc.manager.debug.level"]     = "PARANOID";
    m_map["rtc.manager.orb"]             = "omniORB";
    m_map["rtc.manager.orb.options"]     = "IIOPAddrPort, -ORBendPoint, giop:tcp:";
    m_map["rtc.manager.arch"]            = "i386";
    m_map["rtc.manager.os"]              = "FreeBSD";
    m_map["rtc.manager.os.release"]      = "6.1-RELEASE";
    m_map["rtc.manager.language"]        = "Python";
    m_map["rtc.manager.subsystems"]      = "Camera, Manipulator, Force Sensor";
    m_map["rtc.component.conf.path"]     = "C:\\\\Program\\\\ Files\\\\OpenRTM-aist";
    m_map["rtc.manager.opening_message"] = "\"Hello RT World\"";

    Itr it    (m_map.begin());
    Itr it_end(m_map.end());

    while(it != it_end) {
      m_keys.push_back(it->first);
      ++it;
    }
  }
  
  virtual void tearDown()
  { 
  }

  /* tests for Properties constructor.*/
  void test_storeMethod(std::ifstream& if1) {
    string p1,p2;

    getline(if1,p1);
    p2 = "# defaults settings";
    CPPUNIT_ASSERT(p1 == p2);

    getline(if1,p1);
    p2 = "rtc.component.conf.path = C:\\\\Program\\\\ Files\\\\OpenRTM-aist";
    CPPUNIT_ASSERT(p1 == p2);

    getline(if1,p1);
    p2 = "rtc.manager.arch = i386";
    CPPUNIT_ASSERT(p1 == p2);

    getline(if1,p1);
    p2 = "rtc.manager.debug.level = PARANOID";
    CPPUNIT_ASSERT(p1 == p2);

    getline(if1,p1);
    p2 = "rtc.manager.language = Python";
    CPPUNIT_ASSERT(p1 == p2);

    getline(if1,p1);
    p2 = "rtc.manager.nameserver = zonu.a02.aist.go.jp";
    CPPUNIT_ASSERT(p1 == p2);

    getline(if1,p1);
    p2 = "rtc.manager.opening_message = \\\"Hello RT World\\\"";
    CPPUNIT_ASSERT(p1 == p2);

    getline(if1,p1);
    p2 = "rtc.manager.orb = omniORB";
    CPPUNIT_ASSERT(p1 == p2);

    getline(if1,p1);
    p2 = "rtc.manager.orb.options = IIOPAddrPort, -ORBendPoint, giop:tcp:";
    CPPUNIT_ASSERT(p1 == p2);

    getline(if1,p1);
    p2 = "rtc.manager.os = FreeBSD";
    CPPUNIT_ASSERT(p1 == p2);

    getline(if1,p1);
    p2 = "rtc.manager.os.release = 6.1-RELEASE";
    CPPUNIT_ASSERT(p1 == p2);

    getline(if1,p1);
    p2 = "rtc.manager.subsystems = Camera, Manipulator, Force Sensor";
    CPPUNIT_ASSERT(p1 == p2);

    getline(if1,p1);
    p2 = "rtc.openrtm.author = Noriaki Ando";
    CPPUNIT_ASSERT(p1 == p2);

    getline(if1,p1);
    p2 = "rtc.openrtm.release = aist";
    CPPUNIT_ASSERT(p1 == p2);

    getline(if1,p1);
    p2 = "rtc.openrtm.vendor = AIST";
    CPPUNIT_ASSERT(p1 == p2);

    getline(if1,p1);
    p2 = "rtc.openrtm.version = 0.4.0";
    CPPUNIT_ASSERT(p1 == p2);
  }


  // getProperty()のメソッドのテスト
  // ※ このテストでは、setProperty()メソッドの後に呼ばれると仮定し、"rtc.manager.language"と
  //    "rtc.manager.opening_message"をそれぞれ"Python","\"Hello RT World\""としている。
  void test_getProperty(RTC::Properties& pProp) {
    string prof_key, prof_val;

    prof_key = "rtc.openrtm.version";
    prof_val = "0.4.0";
    CPPUNIT_ASSERT(pProp.getProperty(prof_key) == prof_val);

    prof_key = "rtc.openrtm.release";
    prof_val = "aist";
    CPPUNIT_ASSERT(pProp.getProperty(prof_key) == prof_val);

    prof_key = "rtc.openrtm.vendor";
    prof_val = "AIST";
    CPPUNIT_ASSERT(pProp.getProperty(prof_key) == prof_val);

    prof_key = "rtc.openrtm.author";
    prof_val = "Noriaki Ando";
    CPPUNIT_ASSERT(pProp.getProperty(prof_key) == prof_val);

    prof_key = "rtc.manager.nameserver";
    prof_val = "zonu.a02.aist.go.jp";
    CPPUNIT_ASSERT(pProp.getProperty(prof_key) == prof_val);

    prof_key = "rtc.manager.debug.level";
    prof_val = "PARANOID";
    CPPUNIT_ASSERT(pProp.getProperty(prof_key) == prof_val);

    prof_key = "rtc.manager.orb";
    prof_val = "omniORB";
    CPPUNIT_ASSERT(pProp.getProperty(prof_key) == prof_val);

    prof_key = "rtc.manager.orb.options";
    prof_val = "IIOPAddrPort, -ORBendPoint, giop:tcp:";
    CPPUNIT_ASSERT(pProp.getProperty(prof_key) == prof_val);

    prof_key = "rtc.manager.arch";
    prof_val = "i386";
    CPPUNIT_ASSERT(pProp.getProperty(prof_key) == prof_val);

    prof_key = "rtc.manager.os";
    prof_val = "FreeBSD";
    CPPUNIT_ASSERT(pProp.getProperty(prof_key) == prof_val);

    prof_key = "rtc.manager.os.release";
    prof_val = "6.1-RELEASE";
    CPPUNIT_ASSERT(pProp.getProperty(prof_key) == prof_val);

    prof_key = "rtc.manager.language";
    prof_val = "Python";
    CPPUNIT_ASSERT(pProp.getProperty(prof_key) == prof_val);

    prof_key = "rtc.manager.subsystems";
    prof_val = "Camera, Manipulator, Force Sensor";
    CPPUNIT_ASSERT(pProp.getProperty(prof_key) == prof_val);

    prof_key = "rtc.component.conf.path";
    prof_val = "C:\\\\Program\\\\ Files\\\\OpenRTM-aist";
    CPPUNIT_ASSERT(pProp.getProperty(prof_key) == prof_val);

    prof_key = "rtc.manager.opening_message";
    prof_val = "\"Hello RT World\"";
    CPPUNIT_ASSERT(pProp.getProperty(prof_key) == prof_val);
  }


  // propertyNames()メソッドのテスト。
  // このメソッドも、このテストではsetProperty()の後に呼ばれると仮定している。
  void test_propertyNames(vector<string> vs) {
    vector<string>::iterator it_key    (m_keys.begin());
    vector<string>::iterator it_key_end(m_keys.end());

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
    target = "\"Hello World\"";
    CPPUNIT_ASSERT(pProp.setProperty(key, value) == target);

    key    = "rtc.manager.language";
    value  ="Python";
    target = "C++";
    CPPUNIT_ASSERT(pProp.setProperty(key, value) == target);
  }







  //===========================================================================
  // bind() tests for Properties::Properties()
  // 引数を取らないコンストラクタの場合のテスト
  //===========================================================================
  void test_Properties()
  {
    RTC::Properties pProp;
    
    // プロパティリストをファイルから読み込む。 load()のテスト
    std::ifstream if1("defaults.conf");
    pProp.load(if1);
    if1.close();

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
    test_getProperty(pProp);

    // プロパティリストをファイルに書き込む。
    std::ofstream of2("new.conf");
    pProp.store(of2, "defaults settings");
    of2.close();


    // store()によりファイルに書き込まれたプロパティリストの確認。 store()のテスト
    std::ifstream if2("new.conf");
    test_storeMethod(if2);
    if2.close();
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
    props["rtc.component.conf.path"]     = "C:\\Program\\ Files\\OpenRTM-aist";
    props["rtc.manager.opening_message"] = "\"Hello World\"";

    
    RTC::Properties pProp(props);
    
    // プロパティリストをファイルから読み込む。 load()のテスト
    std::ifstream if1("defaults.conf");
    pProp.load(if1);
    if1.close();

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
    test_getProperty(pProp);

    // プロパティリストをファイルに書き込む。
    std::ofstream of2("new.conf");
    pProp.store(of2, "defaults settings");
    of2.close();

    // store()によりファイルに書き込まれたプロパティリストの確認。 store()のテスト
    std::ifstream if2("new.conf");
    test_storeMethod(if2);
    if2.close();
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
      "rtc.component.conf.path", "C:\\Program\\ Files\\OpenRTM-aist",
      "rtc.manager.opening_message", "\"Hello World\"",
      ""};

    RTC::Properties pProp(props);

    //===================================================================================
    // test: constructorArgs -> write-to-"defaults.conf"(method: store) -> 
    //       read-from-"defaults.conf"(method: load) -> write-to-"new.conf"(method: save)
    //===================================================================================
    //    std::ofstream of1("defaults.conf");
    //    pProp.store(of1, "defaults settings");
    //    of1.close();
    
    // プロパティリストをファイルから読み込む。 load()のテスト
    std::ifstream if1("defaults.conf");
    pProp.load(if1);
    if1.close();

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
    test_getProperty(pProp);

    // プロパティリストをファイルに書き込む。
    std::ofstream of2("new.conf");
    pProp.store(of2, "defaults settings");
    of2.close();

    // store()によりファイルに書き込まれたプロパティリストの確認。 store()のテスト
    std::ifstream if2("new.conf");
    test_storeMethod(if2);
    if2.close();
  }


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


  // splitKeyValue()メソッドのテスト
  void test_splitKeyValue() {
    //    string str("test:C:\\TEST\\test");
    //    string key,value;                  // key,valueはsplitKeyValue()の中で値が代入される。
    //    string retk("test");               // splitKeyValue()呼び出し後のkeyの期待される値
    //    string retv("C:\\TEST\\test");     // splitKeyValue()呼び出し後のvalueの期待される値

    string str, key, value, retk, retv;
    std::ifstream ifs("splitKeyValueTest.data");
    getline(ifs, str);
    getline(ifs, retk);
    getline(ifs, retv);
    ifs.close();

    splitKeyValue(str, key, value);

    CPPUNIT_ASSERT(key == retk);
    CPPUNIT_ASSERT(value == retv);
  }

};


/*
 * register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(PropertiesTest);




int main(int argc, char* argv[])
{
    CppUnit::TextUi::TestRunner runner;

    runner.addTest(CppUnit::TestFactoryRegistry::getRegistry().makeTest());
    CppUnit::Outputter* outputter = 
      new CppUnit::TextOutputter(&runner.result(), std::cout);
    runner.setOutputter(outputter);
   
    return runner.run();
}
