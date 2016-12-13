// -*- C++ -*-
/*!
 * @file   DataFlowComponentActionServantTests.cpp
 * @brief  DataFlowComponentActionServant test class
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

#ifndef DataFlowComponentActionServant_cpp
#define DataFlowComponentActionServant_cpp

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>
#include <DataFlowComponentActionServant.h>
#include <doil/ServantBase.h>
#include <doil/corba/CORBAManager.h>
#include <stubs/DataFlowComponentActionImpl.h>
#include <stubs/Logger.h>

/*!
 * @class DataFlowComponentActionServantTests class
 * @brief DataFlowComponentActionServant test
 */
namespace DataFlowComponentActionServant
{
  class DataFlowComponentActionServantTests
   : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(DataFlowComponentActionServantTests);
    CPPUNIT_TEST(test_call_on_execute);
    CPPUNIT_TEST(test_call_on_state_update);
    CPPUNIT_TEST(test_call_on_rate_changed);
    //CPPUNIT_TEST(test_case0);
    CPPUNIT_TEST_SUITE_END();
  
  private:
    ::UnitTest::Servant::DataFlowComponentActionImpl* Impl;
    ::UnitTest::Servant::Logger Log;
    ::doil::ServantBase* Servant;
    ::RTC::CORBA::DataFlowComponentActionServant * CServant;
  
  public:
  
    /*!
     * @brief Constructor
     */
    DataFlowComponentActionServantTests()
    {
        // registerFactory
        Impl = new UnitTest::Servant::DataFlowComponentActionImpl(Log);
        doil::CORBA::CORBAManager::instance().registerFactory(Impl->id(),
            doil::New<RTC::CORBA::DataFlowComponentActionServant>,
            doil::Delete<RTC::CORBA::DataFlowComponentActionServant>);
        doil::ReturnCode_t ret = doil::CORBA::CORBAManager::instance().activateObject(Impl);
        Servant = doil::CORBA::CORBAManager::instance().toServant(Impl);
        CServant = dynamic_cast<RTC::CORBA::DataFlowComponentActionServant*>(Servant);
    }
    
    /*!
     * @brief Destructor
     */
    ~DataFlowComponentActionServantTests()
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
  
    void test_call_on_execute()
    {
      CPPUNIT_ASSERT(CServant);

      std::string str("on_execute");
      ::RTC::ExecutionContextHandle_t exec_handle;
      ::RTC::ReturnCode_t result;
      result = CServant->on_execute(exec_handle);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not true", RTC::RTC_OK, result);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not method name", Log.pop(), str);
    }
    void test_call_on_state_update()
    {
      CPPUNIT_ASSERT(CServant);

      std::string str("on_state_update");
      ::RTC::ExecutionContextHandle_t exec_handle;
      ::RTC::ReturnCode_t result;
      result = CServant->on_state_update(exec_handle);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not true", RTC::RTC_OK, result);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not method name", Log.pop(), str);
    }
    void test_call_on_rate_changed()
    {
      CPPUNIT_ASSERT(CServant);

      std::string str("on_rate_changed");
      ::RTC::ExecutionContextHandle_t exec_handle;
      ::RTC::ReturnCode_t result;
      result = CServant->on_rate_changed(exec_handle);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not true", RTC::RTC_OK, result);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not method name", Log.pop(), str);
    }
    /* test case */
    void test_case0()
    {
      CPPUNIT_FAIL("Automatic failue.");
    }
  };
}; // namespace DataFlowComponentActionServant

/*
 * Register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(DataFlowComponentActionServant::DataFlowComponentActionServantTests);

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
#endif // DataFlowComponentActionServant_cpp
