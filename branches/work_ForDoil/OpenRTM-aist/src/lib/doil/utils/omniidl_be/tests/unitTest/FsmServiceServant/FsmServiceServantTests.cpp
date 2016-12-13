// -*- C++ -*-
/*!
 * @file   FsmServiceServantTests.cpp
 * @brief  FsmServiceServant test class
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

#ifndef FsmServiceServant_cpp
#define FsmServiceServant_cpp

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>
#include <FsmServiceServant.h>
#include <doil/ServantBase.h>
#include <doil/corba/CORBAManager.h>
#include <stubs/FsmServiceImpl.h>
#include <stubs/Logger.h>

/*!
 * @class FsmServiceServantTests class
 * @brief FsmServiceServant test
 */
namespace FsmServiceServant
{
  class FsmServiceServantTests
   : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(FsmServiceServantTests);
    CPPUNIT_TEST(test_call_get_fsm_profile);
    CPPUNIT_TEST(test_call_set_fsm_profile);
    //CPPUNIT_TEST(test_case0);
    CPPUNIT_TEST_SUITE_END();
  
  private:
    ::UnitTest::Servant::FsmServiceImpl* Impl;
    ::UnitTest::Servant::Logger Log;
    ::doil::ServantBase* Servant;
    ::RTC::CORBA::FsmServiceServant * CServant;
  
  public:
  
    /*!
     * @brief Constructor
     */
    FsmServiceServantTests()
    {
        // registerFactory
        Impl = new UnitTest::Servant::FsmServiceImpl(Log);
        doil::CORBA::CORBAManager::instance().registerFactory(Impl->id(),
            doil::New<RTC::CORBA::FsmServiceServant>,
            doil::Delete<RTC::CORBA::FsmServiceServant>);
        doil::ReturnCode_t ret = doil::CORBA::CORBAManager::instance().activateObject(Impl);
        Servant = doil::CORBA::CORBAManager::instance().toServant(Impl);
        CServant = dynamic_cast<RTC::CORBA::FsmServiceServant*>(Servant);
    }
    
    /*!
     * @brief Destructor
     */
    ~FsmServiceServantTests()
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

    void test_call_get_fsm_profile()
    {
      CPPUNIT_ASSERT(CServant);

      std::string str("get_fsm_profile");
      ::RTC::FsmProfile* result;
      result = CServant->get_fsm_profile();
      //CPPUNIT_ASSERT_EQUAL_MESSAGE("not true", ::RTC::RTC_OK, result);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not method name", Log.pop(), str);
    }
    void test_call_set_fsm_profile()
    {
      CPPUNIT_ASSERT(CServant);

      std::string str("set_fsm_profile");
      ::RTC::ReturnCode_t result;
      ::RTC::FsmProfile fsm_profile;
      result = CServant->set_fsm_profile(fsm_profile);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not true", ::RTC::RTC_OK, result);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not method name", Log.pop(), str);
    }
  
    /* test case */
    void test_case0()
    {
      CPPUNIT_FAIL("Automatic failue.");
    }
  };
}; // namespace FsmServiceServant

/*
 * Register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(FsmServiceServant::FsmServiceServantTests);

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
#endif // FsmServiceServant_cpp
