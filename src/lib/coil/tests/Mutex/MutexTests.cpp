// -*- C++ -*-
/*!
 * @file   MutexTests.cpp
 * @brief  Mutex test class
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

#ifndef Mutex_cpp
#define Mutex_cpp

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>

/*!
 * @class MutexTests class
 * @brief Mutex test
 */
namespace Mutex
{
  class MutexTests
   : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(MutexTests);
    CPPUNIT_TEST(test_case0);
    CPPUNIT_TEST_SUITE_END();
  
  private:
  
  public:
  
    /*!
     * @brief Constructor
     */
    MutexTests()
    {
    }
    
    /*!
     * @brief Destructor
     */
    ~MutexTests()
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
}; // namespace Mutex

/*
 * Register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(Mutex::MutexTests);

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
#endif // Mutex_cpp
