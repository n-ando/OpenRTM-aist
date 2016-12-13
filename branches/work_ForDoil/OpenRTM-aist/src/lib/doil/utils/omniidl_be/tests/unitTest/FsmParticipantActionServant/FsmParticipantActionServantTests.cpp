// -*- C++ -*-
/*!
 * @file   FsmParticipantActionServantTests.cpp
 * @brief  FsmParticipantActionServant test class
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

#ifndef FsmParticipantActionServant_cpp
#define FsmParticipantActionServant_cpp

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>
#include <FsmParticipantActionServant.h>
#include <doil/ServantBase.h>
#include <doil/corba/CORBAManager.h>
#include <stubs/FsmParticipantActionImpl.h>
#include <stubs/Logger.h>

/*!
 * @class FsmParticipantActionServantTests class
 * @brief FsmParticipantActionServant test
 */
namespace FsmParticipantActionServant
{
  class FsmParticipantActionServantTests
   : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(FsmParticipantActionServantTests);
    CPPUNIT_TEST(test_call_on_action);
    //CPPUNIT_TEST(test_case0);
    CPPUNIT_TEST_SUITE_END();
  
  private:
    ::UnitTest::Servant::FsmParticipantActionImpl* Impl;
    ::UnitTest::Servant::Logger Log;
    ::doil::ServantBase* Servant;
    ::RTC::CORBA::FsmParticipantActionServant * CServant;
  
  public:
  
    /*!
     * @brief Constructor
     */
    FsmParticipantActionServantTests()
    {
        // registerFactory
        Impl = new UnitTest::Servant::FsmParticipantActionImpl(Log);
        doil::CORBA::CORBAManager::instance().registerFactory(Impl->id(),
            doil::New<RTC::CORBA::FsmParticipantActionServant>,
            doil::Delete<RTC::CORBA::FsmParticipantActionServant>);
        doil::ReturnCode_t ret = doil::CORBA::CORBAManager::instance().activateObject(Impl);
        Servant = doil::CORBA::CORBAManager::instance().toServant(Impl);
        CServant = dynamic_cast<RTC::CORBA::FsmParticipantActionServant*>(Servant);
    }
    
    /*!
     * @brief Destructor
     */
    ~FsmParticipantActionServantTests()
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
  
    void test_call_on_action()
    {
      CPPUNIT_ASSERT(CServant);

      std::string str("on_action");
      ::RTC::ReturnCode_t result;
      ::RTC::Local::ExecutionContextHandle_t exec_handle;
      result = CServant->on_action(exec_handle);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not true", ::RTC::RTC_OK, result);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not method name", Log.pop(), str);
    }
    /* test case */
    void test_case0()
    {
      CPPUNIT_FAIL("Automatic failue.");
    }
  };
}; // namespace FsmParticipantActionServant

/*
 * Register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(FsmParticipantActionServant::FsmParticipantActionServantTests);

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
#endif // FsmParticipantActionServant_cpp
