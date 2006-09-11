#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>
#include "../RtcNaming.h"

using namespace RTM;
using namespace std;
// XXX をテストする [3]
class RtcNamingTest
  : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(RtcNamingTest);
  //  CPPUNIT_TEST(test_to_string);
  //  CPPUNIT_TEST(test_to_name);
  //CPPUNIT_TEST(test_bind);
  CPPUNIT_TEST(test_rebind);

  //  CPPUNIT_TEST(test_bind_by_string);
  //  CPPUNIT_TEST(test_bind_recursive);
  //  CPPUNIT_TEST(test_rebind_by_string);
  //  CPPUNIT_TEST(test_bind_context);
  //  CPPUNIT_TEST(test_bind_context_by_string);
  //  CPPUNIT_TEST(test_bind_context_recursive);
  //  CPPUNIT_TEST(test_rebind_context);
  //  CPPUNIT_TEST(test_rebind_context_by_string);
  //  CPPUNIT_TEST(test_resolve);
  //  CPPUNIT_TEST(test_resolve_by_string);
  //  CPPUNIT_TEST(test_unbind);
  //  CPPUNIT_TEST(test_unbind_by_string);
  //  CPPUNIT_TEST(test_new_context);
  //  CPPUNIT_TEST(test_bind_new_context);
  //  CPPUNIT_TEST(test_bind_new_context_by_string);
  //  CPPUNIT_TEST(test_destroy);
  //  CPPUNIT_TEST(test_list);
  //  CPPUNIT_TEST(test_to_url);
  //  CPPUNIT_TEST(test_resolve_string);
  CPPUNIT_TEST_SUITE_END();
private:
  
  RtcCorbaNaming* m_pCorbaNaming;
  CORBA::ORB_ptr m_pORB;
  
public:
  
  /*
   * コンストラクタ/デストラクタ [7]
   */
  RtcNamingTest()
  {

  }
  
  ~RtcNamingTest()
  {
  }
  
  /*
   * 初期化/後始末 [8]
   */
  virtual void setUp()
  {
    int argc(0);
    char* argv[1];
    argv[1] = "";
    char* name_server = "corbaloc::localhost:2809/NameService";
    m_pORB = CORBA::ORB_init(argc, argv);
    m_pCorbaNaming = new RtcCorbaNaming(m_pORB, name_server);
    

  }
  
  virtual void tearDown()
  { 
    m_pORB->destroy();
  }
  
  //======================================================================
  // bind() tests
  //======================================================================
  void test_bind()
  {
    m_pCorbaNaming->clearAll();
    sleep(3);

    std::vector<std::string> names;

    names.push_back(std::string("One.one_cxt/Two.two_cxt/Three.three_cxt/Four.four_cxt"));
    names.push_back(std::string("Mon.mon_cxt/Tus.tus_cxt/Wed.wed_cxt/Thur.thurfour_cxt/Fri.fri_cxt/Sat.sat_cxt/Sun.sun_cxt"));
    names.push_back(std::string("Hoge0"));
    names.push_back(std::string("Hoge1"));
    names.push_back(std::string("Hoge2"));
    names.push_back(std::string("Hoge3"));
    names.push_back(std::string("Hoge4"));
    names.push_back(std::string("Hoge5"));
    names.push_back(std::string("Hoge6"));
    names.push_back(std::string("zonu\\.a02\\.aist\\.go\\.jp.host_cxt/Manager123456.mgr_cxt/Manipulator.cat_cxt/Manipulator0.rtc"));

    //    names.push_back(std::string("zonu\\.a02\\.aist\\.go\\.jp.host_cxt/Manager123456.mgr_cxt/MobileRobot.cat_cxt/Kani1.rtc"));
    //    names.push_back(std::string("zonu\\.a02\\.aist\\.go\\.jp.host_cxt/Manager123456.mgr_cxt/MobileRobot.cat_cxt/Kani2.rtc"));
    
    for (CORBA::ULong i = 0; i < names.size(); ++i)
      {
	bind_test_sequence(names[i].c_str());
      }

    // testing for AlreadyBound exception
    std::string name("zonu\\.a02\\.aist\\.go\\.jp.host_cxt/Manager123456.mgr_cxt/MobileRobot.cat_cxt/Kani0.rtc");    
    bool flag(false);

    try
      {
	bind_test_sequence(name.c_str());
      }
    catch (RtcCorbaNaming::AlreadyBound& e)
      {
	flag = true;
      }
    CPPUNIT_ASSERT_MESSAGE("AlreadyBound should be throw", flag);
  }
  
  bool bind_test_sequence(const char* sname)
  {
    CORBA::Object_var obj;
    obj = m_pCorbaNaming->newContext();
    m_pCorbaNaming->bind(sname, obj, 1);
    bool flag(false);
   
    // bind again. AlreadyBound shoul be throw
    try
      {
	m_pCorbaNaming->bind(sname, m_pCorbaNaming->newContext(), 1);
      }
    catch (RtcCorbaNaming::AlreadyBound& e)
      {
	flag = true; // OK
      }
    catch (...)
      {
	CPPUNIT_ASSERT_MESSAGE("Invalid exception", 0);
      }
    CPPUNIT_ASSERT_MESSAGE("AlreadyBound should be throw", flag);

    // resolve test
    CORBA::Object_var new_obj;
    new_obj = m_pCorbaNaming->resolve(sname);

    CPPUNIT_ASSERT_MESSAGE("Resolve failed.", obj->_is_equivalent(new_obj));
    
    return true;
  }


  //======================================================================
  // rebind() tests
  //======================================================================
  void test_rebind()
  {
    m_pCorbaNaming->clearAll();
    sleep(3);

    std::vector<std::string> names;

    names.push_back(std::string("One.one_cxt/Two.two_cxt/Three.three_cxt/Four.four_cxt"));
    names.push_back(std::string("Mon.mon_cxt/Tus.tus_cxt/Wed.wed_cxt/Thur.thurfour_cxt/Fri.fri_cxt/Sat.sat_cxt/Sun.sun_cxt"));
    names.push_back(std::string("Hoge0"));
    names.push_back(std::string("Hoge1"));
    names.push_back(std::string("Hoge2"));
    names.push_back(std::string("Hoge3"));
    names.push_back(std::string("Hoge4"));
    names.push_back(std::string("Hoge5"));
    names.push_back(std::string("Hoge6"));
    names.push_back(std::string("zonu\\.a02\\.aist\\.go\\.jp.host_cxt/Manager123456.mgr_cxt/Manipulator.cat_cxt/Manipulator0.rtc"));
    names.push_back(std::string("zonu\\.a02\\.aist\\.go\\.jp.host_cxt/Manager123456.mgr_cxt/MobileRobot.cat_cxt/Kani1.rtc"));
    names.push_back(std::string("zonu\\.a02\\.aist\\.go\\.jp.host_cxt/Manager123456.mgr_cxt/MobileRobot.cat_cxt/Kani2.rtc"));
    names.push_back(std::string("zonu\\.a02\\.aist\\.go\\.jp.host_cxt/Manager654321.mgr_cxt/Manipulator.cat_cxt/Manipulator0.rtc"));
    names.push_back(std::string("zonu\\.a02\\.aist\\.go\\.jp.host_cxt/Manager654321.mgr_cxt/MobileRobot.cat_cxt/Kani1.rtc"));
    names.push_back(std::string("zonu\\.a02\\.aist\\.go\\.jp.host_cxt/Manager654321.mgr_cxt/MobileRobot.cat_cxt/Kani2.rtc"));
    
    bool flag(true);
    try
      {
	for (CORBA::ULong i = 0; i < names.size(); ++i)
	  {
	    rebind_test_sequence(names[i].c_str());
	  }
      }
    catch (...)
      {
	flag = false;
      }
    CPPUNIT_ASSERT_MESSAGE("Any exceptions should not be thrown", flag);
  }

  bool rebind_test_sequence(const char* sname)
  {
    CORBA::Object_var obj1;
    obj1 = m_pCorbaNaming->newContext();

    m_pCorbaNaming->rebind(sname, obj1, 1);

    CORBA::Object_var obj2;
    obj2 = m_pCorbaNaming->newContext();

    m_pCorbaNaming->rebind(sname, obj2, 1);

    // resolve test
    CORBA::Object_var new_obj;
    new_obj = m_pCorbaNaming->resolve(sname);

    CPPUNIT_ASSERT_MESSAGE("Resolve failed.", obj2->_is_equivalent(new_obj));
    if (obj2->_is_equivalent(new_obj))
      cout << "two object are equivalent" << endl;
    return true;
  }


  //======================================================================
  // destroy() tests
  //======================================================================
  void test_destroy()
  {
    m_pCorbaNaming->clearAll();
    CosNaming::BindingList_var     bl;
    CosNaming::BindingIterator_var bi;
    m_pCorbaNaming->list(m_pCorbaNaming->getRootContext(), 1, bl, bi);
    CPPUNIT_ASSERT_MESSAGE("clearAll() failed", bl->length() == 0);
  }

  void test_to_string()
  {
    CosNaming::Name name;
    name.length(4);
    name[0].id   = "One";
    name[0].kind = "one_cxt";
    name[1].id   = "Two";
    name[1].kind = "two_cxt";
    name[2].id   = "Three";
    name[2].kind = "three_cxt";
    name[3].id   = "Four";
    name[3].kind = "four_cxt";
    char* source = "One.one_cxt/Two.two_cxt/Three.three_cxt/Four.four_cxt";
    char* sname;
    sname = m_pCorbaNaming->toString(name);
    CPPUNIT_ASSERT_MESSAGE("Invalid string name", 0 == strcmp(sname, source));
  }

  void test_to_name()
  {
    std::string source("One.one_cxt/Two.two_cxt/Three.three_cxt/Four.four_cxt");
    CosNaming::Name name;
    name = m_pCorbaNaming->toName(source.c_str());
    CPPUNIT_ASSERT_MESSAGE("Invalid Name length", name.length() == 4);
    CPPUNIT_ASSERT_MESSAGE("One",       0 == strcmp("One",       name[0].id));
    CPPUNIT_ASSERT_MESSAGE("one_cxt",   0 == strcmp("one_cxt",   name[0].kind));
    CPPUNIT_ASSERT_MESSAGE("Two",       0 == strcmp("Two",       name[1].id));
    CPPUNIT_ASSERT_MESSAGE("two_cxt",   0 == strcmp("two_cxt",   name[1].kind));
    CPPUNIT_ASSERT_MESSAGE("Three",     0 == strcmp("Three",     name[2].id));
    CPPUNIT_ASSERT_MESSAGE("three_cxt", 0 == strcmp("three_cxt", name[2].kind));
    CPPUNIT_ASSERT_MESSAGE("Four",      0 == strcmp("Four",      name[3].id));
    CPPUNIT_ASSERT_MESSAGE("four_cxt",  0 == strcmp("four_cxt",  name[3].kind));
  }
};

/*
 * register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(RtcNamingTest); // [10]




int main(int argc, char* argv[])
{
    /* TestRunner を生成して run() を実行する。 */
    CppUnit::TextUi::TestRunner runner;

    runner.addTest(CppUnit::TestFactoryRegistry::getRegistry().makeTest());
    CppUnit::Outputter* outputter = 
      new CppUnit::TextOutputter(&runner.result(), std::cout);
    runner.setOutputter(outputter);
    
    /* ここに今後テストを追加していく。 */
    return runner.run();
}

