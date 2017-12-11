// -*- C++ -*-
/*!
 * @file   stringutilTests.cpp
 * @brief  stringutil test class
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

#ifndef stringutil_cpp
#define stringutil_cpp

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>

#include <coil/stringutil.h>
      class A
      {
      public:
        int intval;
      };

/*!
 * @class stringutilTests class
 * @brief stringutil test
 */
namespace stringutil
{
  class stringutilTests
   : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(stringutilTests);
    CPPUNIT_TEST(test_toUpper);
    CPPUNIT_TEST(test_toLower);
    CPPUNIT_TEST(test_togetlinePortable);
    CPPUNIT_TEST(test_isEscaped);
    CPPUNIT_TEST(test_escape);
    CPPUNIT_TEST(test_unescape);
    CPPUNIT_TEST(test_eraseHeadBlank);
    CPPUNIT_TEST(test_eraseTailBlank);
    CPPUNIT_TEST(test_replaceString);
    CPPUNIT_TEST(test_split);
    CPPUNIT_TEST(test_toBool);
    CPPUNIT_TEST(test_isAbsolutePath);
    CPPUNIT_TEST(test_isURL);
    CPPUNIT_TEST(test_isIPv4);
    CPPUNIT_TEST(test_isIPv6);
    CPPUNIT_TEST(test_otos);
    CPPUNIT_TEST(test_stringTo);
    CPPUNIT_TEST(test_stringToBool);
    CPPUNIT_TEST(test_ptrToHex);
    CPPUNIT_TEST(test_hexToPtr);
    CPPUNIT_TEST(test_unique_sv);
    CPPUNIT_TEST(test_flatten);
    CPPUNIT_TEST(test_toArgv);
    CPPUNIT_TEST(test_sprintf);
    CPPUNIT_TEST_SUITE_END();
  
  private:
  
  public:
  
    /*!
     * @brief Constructor
     */
    stringutilTests()
    {
    }
    
    /*!
     * @brief Destructor
     */
    ~stringutilTests()
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
  
    /* test case */
    void test_toUpper()
    {
    }
    void test_toLower()
    {
    }
    void test_togetlinePortable()
    {
    }
    void test_isEscaped()
    {
    }
    void test_escape()
    {
    }
    void test_unescape()
    {
    }
    void test_eraseHeadBlank()
    {
    }
    void test_eraseTailBlank()
    {
    }
    void test_replaceString()
    {
    }
    void test_split()
    {
    }
    void test_toBool()
    {
    }
    void test_isAbsolutePath()
    {
    }
    void test_isURL()
    {
    }
    void test_isIPv4()
    {
      std::string addr;
      addr = "255.250.255.255"; // OK
      CPPUNIT_ASSERT_EQUAL(coil::isIPv4(addr), true);
      addr = "0.0.0.0"; // OK
      CPPUNIT_ASSERT_EQUAL(coil::isIPv4(addr), true);
      addr = "192.168.0.1"; // OK
      CPPUNIT_ASSERT_EQUAL(coil::isIPv4(addr), true);
      addr = "192.168.100.0"; // OK
      CPPUNIT_ASSERT_EQUAL(coil::isIPv4(addr), true);

      addr = "255.250.255"; // NG
      CPPUNIT_ASSERT_EQUAL(coil::isIPv4(addr), false);
      addr = "255,250.255.0"; // NG
      CPPUNIT_ASSERT_EQUAL(coil::isIPv4(addr), false);
      addr = "192.168.0.256"; // NG
      CPPUNIT_ASSERT_EQUAL(coil::isIPv4(addr), false);
      addr = "ff.ff.ff.ff"; // NG
      CPPUNIT_ASSERT_EQUAL(coil::isIPv4(addr), false);
      addr = "xx.yy.zz.00"; // NG
      CPPUNIT_ASSERT_EQUAL(coil::isIPv4(addr), false);

      addr = "255.250.255.255:92183"; // OK
      CPPUNIT_ASSERT_EQUAL(coil::isIPv4(addr), true);
      addr = "0.0.0.0:97763"; // OK
      CPPUNIT_ASSERT_EQUAL(coil::isIPv4(addr), true);
      addr = "192.168.0.1:98657"; // OK
      CPPUNIT_ASSERT_EQUAL(coil::isIPv4(addr), true);
      addr = "192.168.100.0:4689"; // OK
      CPPUNIT_ASSERT_EQUAL(coil::isIPv4(addr), true);

      addr = "255.250.255:8686"; // NG
      CPPUNIT_ASSERT_EQUAL(coil::isIPv4(addr), false);
      addr = "255,250.255.0:86545"; // NG
      CPPUNIT_ASSERT_EQUAL(coil::isIPv4(addr), false);
      addr = "1293:192.168.0.1"; // NG
      CPPUNIT_ASSERT_EQUAL(coil::isIPv4(addr), false);
      addr = "ff.ff.ff.ff.ff:9763"; // NG
      CPPUNIT_ASSERT_EQUAL(coil::isIPv4(addr), false);
      addr = "xx.yy.zz.00:98767"; // NG
      CPPUNIT_ASSERT_EQUAL(coil::isIPv4(addr), false);
    }
    void test_isIPv6()
    {
      std::string addr;
      addr = "fe80:0:0:0:21c:42ff:fe87:d3d4"; // OK
      CPPUNIT_ASSERT_EQUAL(coil::isIPv6(addr), true);
      addr = "::1"; // OK
      CPPUNIT_ASSERT_EQUAL(coil::isIPv6(addr), true);
      addr = "fe80::21c:42ff:fe87:d3d4"; // OK
      CPPUNIT_ASSERT_EQUAL(coil::isIPv6(addr), true);

      addr = "fe80::21c:42ff:fe87:1ffff"; // NG
      CPPUNIT_ASSERT_EQUAL(coil::isIPv6(addr), false);
      addr = "ffe80::21c:42ff:fe87:d3d4"; // NG
      CPPUNIT_ASSERT_EQUAL(coil::isIPv6(addr), false);

      addr = "[fe80:0:0:0:21c:42ff:fe87:d3d4]"; // OK
      CPPUNIT_ASSERT_EQUAL(coil::isIPv6(addr), true);
      addr = "[::1]:9679"; // OK
      CPPUNIT_ASSERT_EQUAL(coil::isIPv6(addr), true);
      addr = "[fe80::21c:42ff:fe87:d3d4]:7657"; // OK
      CPPUNIT_ASSERT_EQUAL(coil::isIPv6(addr), true);

      addr = "[ffe80::21c:42ff:fe87:d3d4]:5678"; // NG
      CPPUNIT_ASSERT_EQUAL(coil::isIPv6(addr), false);
      addr = "fe80::21c:42ff:fe87:d3d4]:87654"; // NG
      CPPUNIT_ASSERT_EQUAL(coil::isIPv6(addr), false);
    }
    void test_otos()
    {
    }
    void test_stringTo()
    {
    }
    void test_stringToBool()
    {
      bool val;
      if (coil::stringTo(val, "1")) { CPPUNIT_ASSERT_EQUAL(val, true); }
      else                    { CPPUNIT_FAIL("conversion failed: 1"); }
      if (coil::stringTo(val, "0")) { CPPUNIT_ASSERT_EQUAL(val, false); }
      else                    { CPPUNIT_FAIL("conversion failed: 0"); }

      if (coil::stringTo(val, "true"))  { CPPUNIT_ASSERT_EQUAL(val, true); }
      else                        { CPPUNIT_FAIL("conversion failed: true"); }
      if (coil::stringTo(val, "false")) { CPPUNIT_ASSERT_EQUAL(val, false); }
      else                        { CPPUNIT_FAIL("conversion failed: false"); }

      if (coil::stringTo(val, "TRUE"))  { CPPUNIT_ASSERT_EQUAL(val, true); }
      else                        { CPPUNIT_FAIL("conversion failed: TRUE"); }
      if (coil::stringTo(val, "FALSE")) { CPPUNIT_ASSERT_EQUAL(val, false); }
      else                        { CPPUNIT_FAIL("conversion failed: FALSE"); }

      if (coil::stringTo(val, "TrUe"))  { CPPUNIT_ASSERT_EQUAL(val, true); }
      else                        { CPPUNIT_FAIL("conversion failed: TrUe"); }
      if (coil::stringTo(val, "fAlsE")) { CPPUNIT_ASSERT_EQUAL(val, false); }
      else                        { CPPUNIT_FAIL("conversion failed: fAlsE"); }

      if (coil::stringTo(val, "yes"))  { CPPUNIT_ASSERT_EQUAL(val, true); }
      else                       { CPPUNIT_FAIL("conversion failed: yes"); }
      if (coil::stringTo(val, "no"))   { CPPUNIT_ASSERT_EQUAL(val, false); }
      else                       { CPPUNIT_FAIL("conversion failed: no"); }

      if (coil::stringTo(val, "YES"))  { CPPUNIT_ASSERT_EQUAL(val, true); }
      else                       { CPPUNIT_FAIL("conversion failed: YES"); }
      if (coil::stringTo(val, "NO"))   { CPPUNIT_ASSERT_EQUAL(val, false); }
      else                       { CPPUNIT_FAIL("conversion failed: NO"); }

      if (coil::stringTo(val, "on"))  { CPPUNIT_ASSERT_EQUAL(val, true); }
      else                      { CPPUNIT_FAIL("conversion failed: on"); }
      if (coil::stringTo(val, "off")) { CPPUNIT_ASSERT_EQUAL(val, false); }
      else                      { CPPUNIT_FAIL("conversion failed: off"); }

      if (coil::stringTo(val, "ON"))  { CPPUNIT_ASSERT_EQUAL(val, true); }
      else                      { CPPUNIT_FAIL("conversion failed: ON"); }
      if (coil::stringTo(val, "OFF")) { CPPUNIT_ASSERT_EQUAL(val, false); }
      else                      { CPPUNIT_FAIL("conversion failed: OFF"); }

      if (coil::stringTo(val, "hoge")) { CPPUNIT_FAIL("conversion failed: ON"); }
      if (coil::stringTo(val, "muNya")) { CPPUNIT_FAIL("conversion failed: ON"); }
      if (coil::stringTo(val, "12345")) { CPPUNIT_FAIL("conversion failed: ON"); }
    }
    void test_ptrToHex()
    {
      A* a = new A();
      std::string ptrstr = coil::ptrToHex(a);
      char cbuf[11];
      sprintf(cbuf, "0x%x", reinterpret_cast<uintptr_t>(a));
      CPPUNIT_ASSERT_MESSAGE(cbuf, (ptrstr == cbuf));
      delete a;
    }

    void test_hexToPtr()
    {
      A* a0 = new A();
      a0->intval = 98765;
      std::string ptrstr = coil::ptrToHex(a0);
      char cbuf[11];
      sprintf(cbuf, "0x%x", reinterpret_cast<uintptr_t>(a0));
      CPPUNIT_ASSERT_MESSAGE(cbuf, (ptrstr == cbuf));

      A* a1;
      CPPUNIT_ASSERT(coil::hexToPtr(a1, ptrstr));
      CPPUNIT_ASSERT((a0 == a1));
      CPPUNIT_ASSERT((a1->intval == 98765));

      a1->intval = 12345;
      CPPUNIT_ASSERT((a0->intval == 12345));

      delete a0;
    }
    void test_unique_sv()
    {
    }
    void test_flatten()
    {
    }
    void test_toArgv()
    {
    }
    void test_sprintf()
    {
    }

  };
}; // namespace stringutil

/*
 * Register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(stringutil::stringutilTests);

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
#endif // stringutil_cpp
