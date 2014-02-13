// -*- C++ -*-
/*!
 * @file   ComponentActionServantTests.cpp
 * @brief  ComponentActionServant test class
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

#ifndef ComponentActionServant_cpp
#define ComponentActionServant_cpp

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>

/*!
 * @class ComponentActionServantTests class
 * @brief ComponentActionServant test
 */
namespace ComponentActionServant
{
  class ComponentActionServantTests
   : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(ComponentActionServantTests);
    CPPUNIT_TEST(test_call_on_initialize);
    CPPUNIT_TEST(test_call_on_finalize);
    CPPUNIT_TEST(test_call_on_startup);
    CPPUNIT_TEST(test_call_on_shutdown);
    CPPUNIT_TEST(test_call_on_activated);
    CPPUNIT_TEST(test_call_on_deactivated);
    CPPUNIT_TEST(test_call_on_aborting);
    CPPUNIT_TEST(test_call_on_error);
    CPPUNIT_TEST(test_call_on_reset);
    //CPPUNIT_TEST(test_case0);
    CPPUNIT_TEST_SUITE_END();
  
  private:
  
  public:
  
    /*!
     * @brief Constructor
     */
    ComponentActionServantTests()
    {
    }
    
    /*!
     * @brief Destructor
     */
    ~ComponentActionServantTests()
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
  
    void test_call_on_initialize()
    { 
    }
    void test_call_on_finalize()
    { 
    }
    void test_call_on_startup()
    { 
    }
    void test_call_on_shutdown()
    { 
    }
    void test_call_on_activated()
    { 
    }
    void test_call_on_deactivated()
    { 
    }
    void test_call_on_aborting()
    { 
    }
    void test_call_on_error()
    { 
    }
    void test_call_on_reset()
    { 
    }
    /* test case */
    void test_case0()
    {
      CPPUNIT_FAIL("Automatic failue.");
    }
  };
}; // namespace ComponentActionServant

/*
 * Register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(ComponentActionServant::ComponentActionServantTests);

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
#endif // ComponentActionServant_cpp
