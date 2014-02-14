// -*- C++ -*-
/*!
 * @file   FsmObjectServantTests.cpp
 * @brief  FsmObjectServant test class
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

#ifndef FsmObjectServant_cpp
#define FsmObjectServant_cpp

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>
#include <FsmObjectServant.h>
#include <doil/ServantBase.h>
#include <doil/corba/CORBAManager.h>
#include <stubs/FsmObjectImpl.h>
#include <stubs/Logger.h>

/*!
 * @class FsmObjectServantTests class
 * @brief FsmObjectServant test
 */
namespace FsmObjectServant
{
  class FsmObjectServantTests
   : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(FsmObjectServantTests);
    CPPUNIT_TEST(test_call_send_stimulus);
    //CPPUNIT_TEST(test_case0);
    CPPUNIT_TEST_SUITE_END();
  
  private:
    ::UnitTest::Servant::FsmObjectImpl* Impl;
    ::UnitTest::Servant::Logger Log;
    ::doil::ServantBase* Servant;
    ::RTC::CORBA::FsmObjectServant * CServant;
  
  public:
  
    /*!
     * @brief Constructor
     */
    FsmObjectServantTests()
    {
        // registerFactory
        Impl = new UnitTest::Servant::FsmObjectImpl(Log);
        doil::CORBA::CORBAManager::instance().registerFactory(Impl->id(),
            doil::New<RTC::CORBA::FsmObjectServant>,
            doil::Delete<RTC::CORBA::FsmObjectServant>);
        doil::ReturnCode_t ret = doil::CORBA::CORBAManager::instance().activateObject(Impl);
        Servant = doil::CORBA::CORBAManager::instance().toServant(Impl);
        CServant = dynamic_cast<RTC::CORBA::FsmObjectServant*>(Servant);
    }
    
    /*!
     * @brief Destructor
     */
    ~FsmObjectServantTests()
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
    void test_call_send_stimulus()
    {
      CPPUNIT_ASSERT(CServant);

      std::string str("send_stimulus");
      ::RTC::ReturnCode_t result;
      ::RTC::Local::ExecutionContextHandle_t exec_handle;
      result = CServant->send_stimulus("bar",exec_handle);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not true", ::RTC::RTC_OK, result);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not method name", Log.pop(), str);
    }
  
    /* test case */
    void test_case0()
    {
      CPPUNIT_FAIL("Automatic failue.");
    }
  };
}; // namespace FsmObjectServant

/*
 * Register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(FsmObjectServant::FsmObjectServantTests);

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
#endif // FsmObjectServant_cpp
