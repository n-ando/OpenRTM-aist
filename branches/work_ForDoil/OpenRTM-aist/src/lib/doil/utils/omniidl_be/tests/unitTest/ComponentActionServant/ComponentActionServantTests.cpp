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

#include <unistd.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>
#include <ComponentActionServant.h>
#include <doil/ServantBase.h>
#include <doil/corba/CORBAManager.h>
#include <stubs/ComponentActionImpl.h>
#include <stubs/Logger.h>

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
    ::UnitTest::Servant::ComponentActionImpl* Impl;
    ::UnitTest::Servant::Logger Log;
    ::doil::ServantBase* Servant;
    ::RTC::CORBA::ComponentActionServant * CServant;
  
  public:
  
    /*!
     * @brief Constructor
     */
    ComponentActionServantTests()
    {
        // registerFactory
        Impl = new UnitTest::Servant::ComponentActionImpl(Log);
        doil::CORBA::CORBAManager::instance().registerFactory(Impl->id(),
            doil::New<RTC::CORBA::ComponentActionServant>,
            doil::Delete<RTC::CORBA::ComponentActionServant>);
        doil::ReturnCode_t ret = doil::CORBA::CORBAManager::instance().activateObject(Impl);
        Servant = doil::CORBA::CORBAManager::instance().toServant(Impl);
        CServant = dynamic_cast<RTC::CORBA::ComponentActionServant*>(Servant);
    }
    
    /*!
     * @brief Destructor
     */
    ~ComponentActionServantTests()
    {
      delete Impl;
      Impl = 0;
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
      CPPUNIT_ASSERT(CServant);

      std::string str("on_initialize");
      ::RTC::ReturnCode_t result;
      result = CServant->on_initialize();
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not true", RTC::RTC_OK, result);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not method name", Log.pop(), str);
    }
    void test_call_on_finalize()
    { 
      CPPUNIT_ASSERT(CServant);

      std::string str("on_finalize");
      ::RTC::ReturnCode_t result;
      result = CServant->on_finalize();
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not true", RTC::RTC_OK, result);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not method name", Log.pop(), str);
    }
    void test_call_on_startup()
    { 
      CPPUNIT_ASSERT(CServant);

      std::string str("on_startup");
      ::RTC::ReturnCode_t result;
      ::RTC::ExecutionContextHandle_t exec_handle;
      result = CServant->on_startup(exec_handle);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not true", RTC::RTC_OK, result);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not method name", Log.pop(), str);
    }
    void test_call_on_shutdown()
    { 
      CPPUNIT_ASSERT(CServant);

      std::string str("on_shutdown");
      ::RTC::ReturnCode_t result;
      ::RTC::ExecutionContextHandle_t exec_handle;
      result = CServant->on_shutdown(exec_handle);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not true", RTC::RTC_OK, result);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not method name", Log.pop(), str);
    }
    void test_call_on_activated()
    { 
      CPPUNIT_ASSERT(CServant);

      std::string str("on_activated");
      ::RTC::ReturnCode_t result;
      ::RTC::ExecutionContextHandle_t exec_handle;
      result = CServant->on_activated(exec_handle);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not true", RTC::RTC_OK, result);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not method name", Log.pop(), str);
    }
    void test_call_on_deactivated()
    { 
      CPPUNIT_ASSERT(CServant);

      std::string str("on_deactivated");
      ::RTC::ReturnCode_t result;
      ::RTC::ExecutionContextHandle_t exec_handle;
      result = CServant->on_deactivated(exec_handle);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not true", RTC::RTC_OK, result);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not method name", Log.pop(), str);
    }
    void test_call_on_aborting()
    { 
      CPPUNIT_ASSERT(CServant);

      std::string str("on_aborting");
      ::RTC::ExecutionContextHandle_t exec_handle;
      ::RTC::ReturnCode_t result;
      result = CServant->on_aborting(exec_handle);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not method name", Log.pop(), str);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not true", RTC::RTC_OK, result);
    }
    void test_call_on_error()
    { 
      CPPUNIT_ASSERT(CServant);

      std::string str("on_error");
      ::RTC::ReturnCode_t result;
      ::RTC::ExecutionContextHandle_t exec_handle;
      result = CServant->on_error(exec_handle);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not true", RTC::RTC_OK, result);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not method name", Log.pop(), str);
    }
    void test_call_on_reset()
    { 
      CPPUNIT_ASSERT(CServant);

      std::string str("on_reset");
      ::RTC::ReturnCode_t result;
      ::RTC::ExecutionContextHandle_t exec_handle;
      result = CServant->on_reset(exec_handle);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not true", RTC::RTC_OK, result);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not method name", Log.pop(), str);
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
