// -*- C++ -*-
/*!
 * @file   ConfigurationServantTests.cpp
 * @brief  ConfigurationServant test class
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

#ifndef ConfigurationServant_cpp
#define ConfigurationServant_cpp

#include <iostream>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>
#include <doil/ImplBase.h>

/*!
 * @class ConfigurationServant Local Implementation class.
 * @brief ConfigurationServant test.
 */

/*!
 * @class ConfigurationServantTests class
 * @brief ConfigurationServant test
 */
namespace ConfigurationServant
{
  class ConfigurationServantTests
   : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(ConfigurationServantTests);
    CPPUNIT_TEST(test_case0);
    CPPUNIT_TEST_SUITE_END();
  
  private:
  
  public:
  
    /*!
     * @brief Constructor
     */
    ConfigurationServantTests()
    {
    }
    
    /*!
     * @brief Destructor
     */
    ~ConfigurationServantTests()
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
      CPPUNIT_FAIL("Automatic failue.");
    }
  };
}; // namespace ConfigurationServant

/*
 * Register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(ConfigurationServant::ConfigurationServantTests);

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
#endif // ConfigurationServant_cpp
