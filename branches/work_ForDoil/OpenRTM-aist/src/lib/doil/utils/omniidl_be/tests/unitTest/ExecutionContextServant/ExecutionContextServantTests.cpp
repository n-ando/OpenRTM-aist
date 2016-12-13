// -*- C++ -*-
/*!
 * @file   ExecutionContextServantTests.cpp
 * @brief  ExecutionContextServant test class
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

#ifndef ExecutionContextServant_cpp
#define ExecutionContextServant_cpp

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>
#include <ExecutionContextServant.h>
#include <doil/ImplBase.h>
#include <doil/ServantFactory.h>
#include <doil/corba/CORBAManager.h>
#include <doil/corba/CORBAServantBase.h>
#include <IExecutionContext.h>
#include <stubs/ExecutionContextImpl.h>
#include <stubs/Logger.h>

/*!
 * @class ExecutionContextServantTests class
 * @brief ExecutionContextServant test
 */
namespace ExecutionContextServant
{
  class ExecutionContextServantTests
   : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(ExecutionContextServantTests);
    CPPUNIT_TEST(test_call_is_running);
    CPPUNIT_TEST(test_call_start);
    CPPUNIT_TEST(test_call_stop);
    CPPUNIT_TEST(test_call_get_rate);
    CPPUNIT_TEST(test_call_set_rate);
    CPPUNIT_TEST(test_call_add_component);
    CPPUNIT_TEST(test_call_remove_component);
    CPPUNIT_TEST(test_call_activate_component);
    CPPUNIT_TEST(test_call_deactivate_component);
    CPPUNIT_TEST(test_call_reset_component);
    CPPUNIT_TEST(test_call_get_component_state);
    CPPUNIT_TEST(test_call_get_kind);
    //CPPUNIT_TEST(test_case0);
    CPPUNIT_TEST_SUITE_END();
  
  private:
    ::UnitTest::Servant::ExecutionContextImpl* Impl;
    ::UnitTest::Servant::Logger Log;
    ::doil::ServantBase* Servant;
    ::RTC::CORBA::ExecutionContextServant * CServant;

  
  public:
  
    /*!
     * @brief Constructor
     */
    ExecutionContextServantTests()
    {
        // registerFactory
        Impl = new UnitTest::Servant::ExecutionContextImpl(Log);
        doil::CORBA::CORBAManager::instance().registerFactory(Impl->id(),
            doil::New<RTC::CORBA::ExecutionContextServant>,
            doil::Delete<RTC::CORBA::ExecutionContextServant>);
        doil::ReturnCode_t ret = doil::CORBA::CORBAManager::instance().activateObject(Impl);
        Servant = doil::CORBA::CORBAManager::instance().toServant(Impl);
        CServant = dynamic_cast<RTC::CORBA::ExecutionContextServant*>(Servant);
    }
    
    /*!
     * @brief Destructor
     */
    ~ExecutionContextServantTests()
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
    void test_call_is_running()
    {
      CPPUNIT_ASSERT(CServant);

      std::string str("is_running");
      ::CORBA::Boolean result;
      result = CServant->is_running();
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not true", true, result);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not method name", Log.pop(), str);
    }
    void test_call_start()
    {
      CPPUNIT_ASSERT(CServant);

      std::string str("start");
      ::RTC::ReturnCode_t result;
      result = CServant->start();
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not true", ::RTC::RTC_OK, result);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not method name", Log.pop(), str);
    }
    void test_call_stop()
    {
      CPPUNIT_ASSERT(CServant);

      std::string str("stop");
      ::RTC::ReturnCode_t result;
      result = CServant->stop();
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not true", ::RTC::RTC_OK, result);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not method name", Log.pop(), str);
    }
    void test_call_get_rate()
    {
      CPPUNIT_ASSERT(CServant);

      std::string str("get_rate");
      ::CORBA::Double result;
      result = CServant->get_rate();
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not true", 100.0, result);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not method name", Log.pop(), str);
    }
    void test_call_set_rate()
    {
      CPPUNIT_ASSERT(CServant);

      std::string str("set_rate");
      ::RTC::ReturnCode_t result;
      result = CServant->set_rate(100.0);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not true", ::RTC::RTC_OK, result);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not method name", Log.pop(), str);
    }
    void test_call_add_component()
    {
      CPPUNIT_ASSERT(CServant);

      std::string str("add_component");
      ::RTC::ReturnCode_t result;
      result = CServant->add_component(NULL);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not true", ::RTC::RTC_OK, result);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not method name", Log.pop(), str);
    }
    void test_call_remove_component()
    {
      CPPUNIT_ASSERT(CServant);

      std::string str("remove_component");
      ::RTC::ReturnCode_t result;
      result = CServant->remove_component(NULL);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not true", ::RTC::RTC_OK, result);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not method name", Log.pop(), str);
    }
    void test_call_activate_component()
    {
      CPPUNIT_ASSERT(CServant);

      std::string str("activate_component");
      ::RTC::ReturnCode_t result;
      result = CServant->activate_component(NULL);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not true", ::RTC::RTC_OK, result);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not method name", Log.pop(), str);
    }
    void test_call_deactivate_component()
    {
      CPPUNIT_ASSERT(CServant);

      std::string str("deactivate_component");
      ::RTC::ReturnCode_t result;
      result = CServant->deactivate_component(NULL);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not true", ::RTC::RTC_OK, result);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not method name", Log.pop(), str);
    }
    void test_call_reset_component()
    {
      CPPUNIT_ASSERT(CServant);

      std::string str("reset_component");
      ::RTC::ReturnCode_t result;
      result = CServant->reset_component(NULL);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not true", ::RTC::RTC_OK, result);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not method name", Log.pop(), str);
    }
    void test_call_get_component_state()
    {
      CPPUNIT_ASSERT(CServant);

      std::string str("get_component_state");
      ::RTC::LifeCycleState result;
      result = CServant->get_component_state(NULL);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not true", ::RTC::CREATED_STATE, result);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not method name", Log.pop(), str);
    }
    void test_call_get_kind()
    {
      CPPUNIT_ASSERT(CServant);

      std::string str("get_kind");
      ::RTC::ExecutionKind result;
      result = CServant->get_kind();
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not true", ::RTC::PERIODIC, result);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not method name", Log.pop(), str);
    }
  
    /* test case */
    void test_case0()
    {
      CPPUNIT_FAIL("Automatic failue.");
    }
  };
}; // namespace ExecutionContextServant

/*
 * Register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(ExecutionContextServant::ExecutionContextServantTests);

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
#endif // ExecutionContextServant_cpp
