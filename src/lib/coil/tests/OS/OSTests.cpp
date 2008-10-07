// -*- C++ -*-
/*!
 * @file   OSTests.cpp
 * @brief  OS test class
 * @date   $Date$ 
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * $Id$ 
 *
 */

/*
 * $Log$
 *
 */

#ifndef OS_cpp
#define OS_cpp

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>

#include <coil/OS.h>

/*!
 * @class OSTests class
 * @brief OS test
 */

/* Global Valiables */


namespace OS
{
  class OSTests
   : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(OSTests);
//    CPPUNIT_TEST(test_case0);
    CPPUNIT_TEST(test_simple_case);
    CPPUNIT_TEST(test_invalid_option);
    CPPUNIT_TEST(test_not_option);
    CPPUNIT_TEST(test_arg_option);
    CPPUNIT_TEST_SUITE_END();
  
  private:
  
  public:
  
    /*!
     * @brief Constructor
     */
    OSTests()
    {
    }
    
    /*!
     * @brief Destructor
     */
    ~OSTests()
    {
    }
  
    /*!
     * @brief Test initialization
     */
    virtual void setUp()
    {
//      opterr = 0;
    }
    
    /*!
     * @brief Test finalization
     */
    virtual void tearDown()
    { 
    }
  
    /* test case */
    void test_case0()
    {
      char * const vv[] = {
        (char *)"me",
        (char *)"-a",
        (char *)"Hoge",
        (char *)"-b",
        (char *)"--Huga",
        (char *)"-Foo",
        (char *)"-d",
        (char *)"Hey",
      };
      const char * opt = "a:bH::F:d";
      coil::GetOpt go(7, vv, opt, 0);
      int ii;
      while ((ii = go()) != -1) {
//          fprintf(stderr, "0x%X : optind[%d](%s), optarg : %s.\n", ii, optind, vv[optind], go.optarg);
      }
      fprintf(stderr, "ii : 0x%X.\n", ii);
    }

    void test_simple_case()
    {
      char * const vv[] = { (char *)"Hoge", (char *)"-a", (char *)"-b", (char *)"-c" };
      const char * opt = "abc";
      coil::GetOpt go(4, vv, opt, 0);
      int result;
      
//      optind = 1;  // reset searching getopt() 

      result = go();
      CPPUNIT_ASSERT_EQUAL((int)'a', result);
      CPPUNIT_ASSERT(!go.optarg);
      
      result = go();
      CPPUNIT_ASSERT_EQUAL((int)'b', result);
      CPPUNIT_ASSERT(!go.optarg);
      
      result = go();
      CPPUNIT_ASSERT_EQUAL((int)'c', result);
      CPPUNIT_ASSERT(!go.optarg);
      
      result = go();
      CPPUNIT_ASSERT_EQUAL(-1, result);
    }

    void test_invalid_option()
    {
      char * const vv[] = { (char *)"Hoge", (char *)"-a", (char *)"-b", (char *)"-c" };
      const char * opt = "ac";
      coil::GetOpt go(4, vv, opt, 0);
      int result;
      
//      optind = 1;  // reset searching getopt() 

      result = go();
      CPPUNIT_ASSERT_EQUAL((int)'a', result);
      CPPUNIT_ASSERT(!go.optarg);
      
      // opterr = 1;    // <-- Remove comment out to display error message.
      result = go();
      CPPUNIT_ASSERT_EQUAL((int)'?', result);
      CPPUNIT_ASSERT(!go.optarg);
      
      result = go();
      CPPUNIT_ASSERT_EQUAL((int)'c', result);
      CPPUNIT_ASSERT(!go.optarg);
      
      result = go();
      CPPUNIT_ASSERT_EQUAL(-1, result);
    }

    void test_not_option()
    {
      char * const vv[] = { (char *)"Hoge", (char *)"-a", (char *)"Huga", (char *)"-c" };
      const char * opt = "ac";
      coil::GetOpt go(4, vv, opt, 0);
      int result;
      
//      optind = 1;  // reset searching getopt() 

      result = go();
      CPPUNIT_ASSERT_EQUAL((int)'a', result);
      CPPUNIT_ASSERT(!go.optarg);
      
      result = go();
      CPPUNIT_ASSERT_EQUAL((int)'c', result);
      CPPUNIT_ASSERT(!go.optarg);
      
      result = go();
      CPPUNIT_ASSERT_EQUAL(-1, result);
    }

    void test_arg_option()
    {
      char * const vv[] = { (char *)"Hoge", (char *)"-a", (char *)"-Foe", (char *)"-c" };
      const char * opt = "aF:c";
      coil::GetOpt go(4, vv, opt, 0);
      int result;
      
//      optind = 1;  // reset searching getopt() 

      result = go();
      CPPUNIT_ASSERT_EQUAL((int)'a', result);
      CPPUNIT_ASSERT(!go.optarg);

      result = go();
      CPPUNIT_ASSERT_EQUAL((int)'F', result);
      CPPUNIT_ASSERT_EQUAL('o', go.optarg[0]);
      CPPUNIT_ASSERT_EQUAL('e', go.optarg[1]);
      CPPUNIT_ASSERT_EQUAL('\0', go.optarg[2]);

      result = go();
      CPPUNIT_ASSERT_EQUAL((int)'c', result);
      CPPUNIT_ASSERT(!go.optarg);
      
      result = go();
      CPPUNIT_ASSERT_EQUAL(-1, result);
    }

  };
}; // namespace OS

/*
 * Register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(OS::OSTests);

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
#endif // OS_cpp
