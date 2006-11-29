// -*- C++ -*-
/*!
 * @file   OutPortTests.cpp
 * @brief  OutPort test class
 * @date   $Date: 2006-11-29 04:26:28 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * $Id: OutPortTests.cpp,v 1.1 2006-11-29 04:26:28 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 *
 */

#ifndef OutPort_cpp
#define OutPort_cpp

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>

/*!
 * @class OutPortTests class
 * @brief OutPort test
 */
namespace OutPort
{
  class OutPortTests
   : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(OutPortTests);
    CPPUNIT_TEST(test_case0);
    CPPUNIT_TEST_SUITE_END();
  
  private:
  
  public:
  
    /*!
     * @brief Constructor
     */
    OutPortTests()
    {
    }
    
    /*!
     * @brief Destructor
     */
    ~OutPortTests()
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
}; // namespace OutPort

/*
 * Register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(OutPort::OutPortTests);

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
#endif // OutPort_cpp
