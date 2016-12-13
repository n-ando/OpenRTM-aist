// -*- C++ -*-
/*!
 * @file   ModeCapableServantTests.cpp
 * @brief  ModeCapableServant test class
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

#ifndef ModeCapableServant_cpp
#define ModeCapableServant_cpp

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>

#include <ModeCapableServant.h>
#include <ModeServant.h>

#include <doil/ServantBase.h>
#include <doil/corba/CORBAManager.h>

#include <stubs/ModeCapableImpl.h>
#include <stubs/ModeImpl.h>

#include <stubs/Logger.h>

/*!
 * @class ModeCapableServantTests class
 * @brief ModeCapableServant test
 */
namespace ModeCapableServant
{
  class ModeCapableServantTests
   : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(ModeCapableServantTests);
    CPPUNIT_TEST(test_call_get_default_mode);
    CPPUNIT_TEST(test_call_get_current_mode);
    CPPUNIT_TEST(test_call_get_current_mode_in_context);
    CPPUNIT_TEST(test_call_get_pending_mode);
    CPPUNIT_TEST(test_call_get_pending_mode_in_context);
    CPPUNIT_TEST(test_call_set_mode);
    //CPPUNIT_TEST(test_case0);
    CPPUNIT_TEST_SUITE_END();
  
  private:
    ::UnitTest::Servant::ModeCapableImpl* Impl;
    ::UnitTest::Servant::ModeImpl* MImpl;

    ::UnitTest::Servant::Logger Log;
    ::doil::ServantBase* Servant;

    ::RTC::CORBA::ModeCapableServant * CServant;
  
  public:
  
    /*!
     * @brief Constructor
     */
    ModeCapableServantTests()
    {
        // registerFactory
        Impl = new UnitTest::Servant::ModeCapableImpl(Log);
        doil::CORBA::CORBAManager::instance().registerFactory(Impl->id(),
            doil::New<RTC::CORBA::ModeCapableServant>,
            doil::Delete<RTC::CORBA::ModeCapableServant>);
        doil::ReturnCode_t ret = doil::CORBA::CORBAManager::instance().activateObject(Impl);
        Servant = doil::CORBA::CORBAManager::instance().toServant(Impl);
        CServant = dynamic_cast<RTC::CORBA::ModeCapableServant*>(Servant);

        MImpl = new UnitTest::Servant::ModeImpl();
        doil::CORBA::CORBAManager::instance().registerFactory(MImpl->id(),
            doil::New<RTC::CORBA::ModeServant>,
            doil::Delete<RTC::CORBA::ModeServant>);
        ret = doil::CORBA::CORBAManager::instance().activateObject(MImpl);

    }
    
    /*!
     * @brief Destructor
     */
    ~ModeCapableServantTests()
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

    void test_call_get_default_mode()
    {
      CPPUNIT_ASSERT(CServant);

      std::string str("get_default_mode");
      ::RTC::Mode_var result;
      //::RTC::Mode result;
      result = CServant->get_default_mode();
      //CPPUNIT_ASSERT_EQUAL_MESSAGE("not true", ::RTC::RTC_OK, result);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not method name", Log.pop(), str);
    }
    void test_call_get_current_mode()
    {
      CPPUNIT_ASSERT(CServant);

      std::string str("get_current_mode");
      ::RTC::Mode_var result;
      result = CServant->get_current_mode();
      //CPPUNIT_ASSERT_EQUAL_MESSAGE("not true", ::RTC::RTC_OK, result);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not method name", Log.pop(), str);
    }
    void test_call_get_current_mode_in_context()
    {
      CPPUNIT_ASSERT(CServant);

      std::string str("get_current_mode_in_context");
      ::RTC::Mode_var result;
      result = CServant->get_current_mode_in_context(NULL);
      //CPPUNIT_ASSERT_EQUAL_MESSAGE("not true", ::RTC::RTC_OK, result);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not method name", Log.pop(), str);
    }
    void test_call_get_pending_mode()
    {
      CPPUNIT_ASSERT(CServant);

      std::string str("get_pending_mode");
      ::RTC::Mode_var result;
      result = CServant->get_pending_mode();
      //CPPUNIT_ASSERT_EQUAL_MESSAGE("not true", ::RTC::RTC_OK, result);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not method name", Log.pop(), str);
    }
    void test_call_get_pending_mode_in_context()
    {
      CPPUNIT_ASSERT(CServant);

      std::string str("get_pending_mode_in_context");
      ::RTC::Mode_var result;
      result = CServant->get_pending_mode_in_context(NULL);
      //CPPUNIT_ASSERT_EQUAL_MESSAGE("not true", ::RTC::RTC_OK, result);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not method name", Log.pop(), str);
    }
    void test_call_set_mode()
    {
      CPPUNIT_ASSERT(CServant);

      std::string str("set_mode");
      ::RTC::ReturnCode_t result;
      result = CServant->set_mode(NULL,true);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not true", ::RTC::RTC_OK, result);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not method name", Log.pop(), str);
    }
  
    /* test case */
    void test_case0()
    {
      CPPUNIT_FAIL("Automatic failue.");
    }
  };
}; // namespace ModeCapableServant

/*
 * Register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(ModeCapableServant::ModeCapableServantTests);

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
#endif // ModeCapableServant_cpp
