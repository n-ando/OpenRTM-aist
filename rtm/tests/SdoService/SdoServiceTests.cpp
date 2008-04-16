// -*- C++ -*-
/*!
 * @file   SdoServiceTests.cpp
 * @brief  SdoService test class
 * @date   $Date: 2006-11-27 08:38:37 $
 * @author Shinji Kurihara
 *         Noriaki Ando <n-ando@aist.go.jp>
 *
 * $Id$
 *
 */

/*
 * $Log: not supported by cvs2svn $
 *
 */

#ifndef SdoService_cpp
#define SdoService_cpp

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>

//#include <rtm/SdoService.h>

/*!
 * @class SdoServiceTests class
 * @brief SdoService test
 */
namespace SdoService
{
  //  using namespace SDOPackage;
  using namespace std;

  class SdoServiceTests
   : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(SdoServiceTests);
    CPPUNIT_TEST(test_getProfile);
    CPPUNIT_TEST(test_set_getName);
    CPPUNIT_TEST(test_set_getInterfaceType);
    CPPUNIT_TEST(test_set_getIdlDefinition);
    CPPUNIT_TEST(test_set_getProperties);
    CPPUNIT_TEST(test_set_getServiceRef);
    CPPUNIT_TEST_SUITE_END();
  
  private:
    //    SDOServiceProfile* m_pSSP;
  public:
  
    /*!
     * @brief Constructor
     */
    SdoServiceTests()
    {
    }
    
    /*!
     * @brief Destructor
     */
    ~SdoServiceTests()
    {
    }
  
    /*!
     * @brief Test initialization
     */
    virtual void setUp()
    {
      //      m_pSSP = new SDOServiceProfile();
    }
    
    /*!
     * @brief Test finalization
     */
    virtual void tearDown()
    {
      //      delete m_pSSP; 
    }
    /* tests for */
    void test_getProfile() {
    }
    
    /* tests for */
    void test_set_getName() {
    }
    
    /* tests for */
    void test_set_getInterfaceType() {
    }
    
    /* tests for */
    void test_set_getIdlDefinition() {
    }
    
    /* tests for */
    void test_set_getProperties() {
    }
    
    /* tests for */
    void test_set_getServiceRef() {
    }
  };
}; // namespace SdoService

/*
 * Register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(SdoService::SdoServiceTests);

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
#endif // SdoService_cpp
