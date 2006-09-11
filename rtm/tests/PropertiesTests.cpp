#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>
#include <fstream>
#include "../Properties.h"

using namespace std;
// XXX をテストする [3]
class PropertiesTest
  : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(PropertiesTest);
  CPPUNIT_TEST(test_properties);
  CPPUNIT_TEST_SUITE_END();
private:
  
  Properties* m_pProp;
  
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
    m_pProp = new Properties();
  }
  
  virtual void tearDown()
  { 
    delete m_pProp;
  }
  
  //======================================================================
  // bind() tests
  //======================================================================
  void test_properties()
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
      "rtc.manager.lanaguage", "C++",
      "rtc.manager.subsystems", "Camera, Manipulator, Force Sensor",
      "rtc.component.conf.path", "C:\\Program\\ Files\\OpenRTM-aist",
      "rtc.manager.opening_message", "\"Hello World\"",
      ""};

    Properties def_prop(props);
    
    std::ofstream of1("defaults.conf");
    def_prop.store(of1, "defaults settings");
    of1.close();
    
    std::ifstream if1("defaults.conf");
    m_pProp->load(if1);
    std::ofstream of2("new.conf");
    m_pProp->store(of2, "defaults settings");
    of2.close();
    m_pProp->store(std::cout, "defaults settings");
      
    
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
