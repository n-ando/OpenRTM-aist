// -*- C++ -*-
/*!
 * @file   LightweightRTObjectServantTests.cpp
 * @brief  LightweightRTObjectServant test class
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

#ifndef LightweightRTObjectServant_cpp
#define LightweightRTObjectServant_cpp

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>
#include <LightweightRTObjectServant.h>
#include <doil/ServantBase.h>
#include <doil/corba/CORBAManager.h>
#include <stubs/LightweightRTObjectImpl.h>
#include <stubs/Logger.h>

/*!
 * @class LightweightRTObjectServantTests class
 * @brief LightweightRTObjectServant test
 */
namespace LightweightRTObjectServant
{
  class LightweightRTObjectServantTests
   : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(LightweightRTObjectServantTests);
    CPPUNIT_TEST(test_initialize);
    CPPUNIT_TEST(test_finalize);
    CPPUNIT_TEST(test_is_alive);
    CPPUNIT_TEST(test_exit);
    CPPUNIT_TEST(test_attach_context);
    CPPUNIT_TEST(test_detach_context);
    CPPUNIT_TEST(test_get_context);
    CPPUNIT_TEST(test_get_owned_contexts);
    CPPUNIT_TEST(test_get_participating_contexts);
    CPPUNIT_TEST(test_get_context_handle);
    //CPPUNIT_TEST(test_case0);
    CPPUNIT_TEST_SUITE_END();
  
  private:
    ::UnitTest::Servant::LightweightRTObjectImpl* Impl;
    ::UnitTest::Servant::Logger Log;
    ::doil::ServantBase* Servant;
    ::RTC::CORBA::LightweightRTObjectServant * CServant;

  
  public:
  
    /*!
     * @brief Constructor
     */
    LightweightRTObjectServantTests()
    {
        // registerFactory
        Impl = new UnitTest::Servant::LightweightRTObjectImpl(Log);
        doil::CORBA::CORBAManager::instance().registerFactory(Impl->id(),
            doil::New<RTC::CORBA::LightweightRTObjectServant>,
            doil::Delete<RTC::CORBA::LightweightRTObjectServant>);
        doil::ReturnCode_t ret = doil::CORBA::CORBAManager::instance().activateObject(Impl);
        Servant = doil::CORBA::CORBAManager::instance().toServant(Impl);
        CServant = dynamic_cast<RTC::CORBA::LightweightRTObjectServant*>(Servant);
    }
    
    /*!
     * @brief Destructor
     */
    ~LightweightRTObjectServantTests()
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
  
    void test_initialize()
    {
      CPPUNIT_ASSERT(CServant);

      std::string str("initialize");
      ::RTC::ReturnCode_t result;
      result = CServant->initialize();
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not true", RTC::RTC_OK, result);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not method name", Log.pop(), str);
    }
    void test_finalize()
    {
      CPPUNIT_ASSERT(CServant);

      std::string str("finalize");
      ::RTC::ReturnCode_t result;
      result = CServant->finalize();
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not true", RTC::RTC_OK, result);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not method name", Log.pop(), str);
    }
    void test_is_alive()
    {
      CPPUNIT_ASSERT(CServant);

      std::string str("is_alive");
      ::CORBA::Boolean result;
      result = CServant->is_alive(NULL);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not true", true, result);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not method name", Log.pop(), str);
    }
    void test_exit()
    {
      CPPUNIT_ASSERT(CServant);

      std::string str("exit");
      ::RTC::ReturnCode_t result;
      result = CServant->exit();
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not true", RTC::RTC_OK, result);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not method name", Log.pop(), str);
    }
    void test_attach_context()
    {
      CPPUNIT_ASSERT(CServant);

      std::string str("attach_context");
      ::RTC::ExecutionContextHandle_t result;
      result = CServant->attach_context(NULL);
      //CPPUNIT_ASSERT_EQUAL_MESSAGE("not true", RTC::RTC_OK, result);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not method name", Log.pop(), str);
    }
    void test_detach_context()
    {
      CPPUNIT_ASSERT(CServant);

      std::string str("detach_context");
      ::RTC::ExecutionContextHandle_t result;
      result = CServant->detach_context(NULL);
      //CPPUNIT_ASSERT_EQUAL_MESSAGE("not true", RTC::RTC_OK, result);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not method name", Log.pop(), str);
    }
    void test_get_context()
    {
      CPPUNIT_ASSERT(CServant);

      std::string str("get_context");
      RTC::ExecutionContext_ptr result;
      result = CServant->get_context(0);
      //CPPUNIT_ASSERT_EQUAL_MESSAGE("not true", RTC::RTC_OK, result);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not method name", Log.pop(), str);
    }
    void test_get_owned_contexts()
    {
      CPPUNIT_ASSERT(CServant);

      std::string str("get_owned_contexts");
      //::RTC::ExecutionContextList result;
      RTC::ExecutionContextList_var result;
      result = CServant->get_owned_contexts();
      //CPPUNIT_ASSERT_EQUAL_MESSAGE("not true", RTC::RTC_OK, result);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not method name", Log.pop(), str);
    }
    void test_get_participating_contexts()
    {
      CPPUNIT_ASSERT(CServant);

      std::string str("get_participating_contexts");
      //::RTC::ExecutionContextList result;
      RTC::ExecutionContextList_var result;
      result = CServant->get_participating_contexts();
      //CPPUNIT_ASSERT_EQUAL_MESSAGE("not true", RTC::RTC_OK, result);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not method name", Log.pop(), str);
    }
    void test_get_context_handle()
    {
      CPPUNIT_ASSERT(CServant);

      std::string str("get_context_handle");
      ::RTC::ExecutionContextHandle_t result;
      result = CServant->get_context_handle(NULL);
      //CPPUNIT_ASSERT_EQUAL_MESSAGE("not true", RTC::RTC_OK, result);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not method name", Log.pop(), str);
    }
    /* test case */
    void test_case0()
    {
      CPPUNIT_FAIL("Automatic failue.");
    }
  };
}; // namespace LightweightRTObjectServant

/*
 * Register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(LightweightRTObjectServant::LightweightRTObjectServantTests);

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
#endif // LightweightRTObjectServant_cpp
