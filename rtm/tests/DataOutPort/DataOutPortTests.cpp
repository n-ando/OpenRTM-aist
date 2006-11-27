// -*- C++ -*-
/*!
 * @file   DataOutPortTests.cpp
 * @brief  DataOutPort test class
 * @date   $Date: 2006-11-27 08:31:03 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * $Id: DataOutPortTests.cpp,v 1.1 2006-11-27 08:31:03 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 *
 */

#ifndef DataOutPort_cpp
#define DataOutPort_cpp

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>

/*!
 * @class DataOutPortTests class
 * @brief DataOutPort test
 */
namespace DataOutPort
{
  class DataOutPortTests
   : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(DataOutPortTests);
    CPPUNIT_TEST(test_case0);
    CPPUNIT_TEST_SUITE_END();
  
  private:
  
  public:
  
    /*!
     * @brief Constructor
     */
    DataOutPortTests()
    {
    }
    
    /*!
     * @brief Destructor
     */
    ~DataOutPortTests()
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
}; // namespace DataOutPort

/*
 * Register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(DataOutPort::DataOutPortTests);

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
#endif // DataOutPort_cpp
