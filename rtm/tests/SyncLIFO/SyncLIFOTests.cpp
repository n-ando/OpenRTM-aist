// -*- C++ -*-
/*!
 * @file   SyncLIFOTests.cpp
 * @brief  SyncLIFO test class
 * @date   $Date: 2007-09-19 02:37:17 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * $Id$
 *
 */

#ifndef SyncLIFO_cpp
#define SyncLIFO_cpp

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>

/*!
 * @class SyncLIFOTests class
 * @brief SyncLIFO test
 */
namespace SyncLIFO
{
  class SyncLIFOTests
   : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(SyncLIFOTests);
    CPPUNIT_TEST(test_case0);
    CPPUNIT_TEST_SUITE_END();
  
  private:
  
  public:
  
    /*!
     * @brief Constructor
     */
    SyncLIFOTests()
    {
    }
    
    /*!
     * @brief Destructor
     */
    ~SyncLIFOTests()
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
    void test_case0()
    {
    }
  };
}; // namespace SyncLIFO

/*
 * Register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(SyncLIFO::SyncLIFOTests);

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
#endif // SyncLIFO_cpp
