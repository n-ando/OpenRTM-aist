// -*- C++ -*-
/*!
 * @file   DataInPortTests.cpp
 * @brief  DataInPort test class
 * @date   $Date: 2006-11-27 08:30:56 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * $Id: DataInPortTests.cpp,v 1.1 2006-11-27 08:30:56 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 *
 */

#ifndef DataInPort_cpp
#define DataInPort_cpp

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>

#include <rtm/idl/BasicDataTypeSkel.h>
#include <rtm/DataInPort.h>

/*!
 * @class DataInPortTests class
 * @brief DataInPort test
 */
namespace DataInPort
{
  class DataInPortTests
   : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(DataInPortTests);
    CPPUNIT_TEST(test_case0);
    CPPUNIT_TEST_SUITE_END();
  
  private:
  
  public:
  
    /*!
     * @brief Constructor
     */
    DataInPortTests()
    {
    }
    
    /*!
     * @brief Destructor
     */
    ~DataInPortTests()
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
}; // namespace DataInPort

/*
 * Register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(DataInPort::DataInPortTests);

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
#endif // DataInPort_cpp
