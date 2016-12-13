// -*- C++ -*-
/*!
 * @file   MultiModeComponentActionServantTests.cpp
 * @brief  MultiModeComponentActionServant test class
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

#ifndef MultiModeComponentActionServant_cpp
#define MultiModeComponentActionServant_cpp

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>
#include <MultiModeComponentActionServant.h>
#include <doil/ServantBase.h>
#include <doil/corba/CORBAManager.h>
#include <stubs/MultiModeComponentActionImpl.h>
#include <stubs/Logger.h>

/*!
 * @class MultiModeComponentActionServantTests class
 * @brief MultiModeComponentActionServant test
 */
namespace MultiModeComponentActionServant
{
  class MultiModeComponentActionServantTests
   : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(MultiModeComponentActionServantTests);
    CPPUNIT_TEST(test_call_on_mode_changed);
    //CPPUNIT_TEST(test_case0);
    CPPUNIT_TEST_SUITE_END();
  
  private:
    ::UnitTest::Servant::MultiModeComponentActionImpl* Impl;
    ::UnitTest::Servant::Logger Log;
    ::doil::ServantBase* Servant;
    ::RTC::CORBA::MultiModeComponentActionServant * CServant;
  
  public:
  
    /*!
     * @brief Constructor
     */
    MultiModeComponentActionServantTests()
    {
        // registerFactory
        Impl = new UnitTest::Servant::MultiModeComponentActionImpl(Log);
        doil::CORBA::CORBAManager::instance().registerFactory(Impl->id(),
            doil::New<RTC::CORBA::MultiModeComponentActionServant>,
            doil::Delete<RTC::CORBA::MultiModeComponentActionServant>);
        doil::ReturnCode_t ret = doil::CORBA::CORBAManager::instance().activateObject(Impl);
        Servant = doil::CORBA::CORBAManager::instance().toServant(Impl);
        CServant = dynamic_cast<RTC::CORBA::MultiModeComponentActionServant*>(Servant);
    }
    
    /*!
     * @brief Destructor
     */
    ~MultiModeComponentActionServantTests()
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
    void test_call_on_mode_changed()
    {
      CPPUNIT_ASSERT(CServant);

      std::string str("on_mode_changed");
      ::RTC::ReturnCode_t result;
      ::RTC::Local::ExecutionContextHandle_t exec_handle;
      result = CServant->on_mode_changed(exec_handle);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not true", ::RTC::RTC_OK, result);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not method name", Log.pop(), str);
    }
  
    /* test case */
    void test_case0()
    {
      CPPUNIT_FAIL("Automatic failue.");
    }
  };
}; // namespace MultiModeComponentActionServant

/*
 * Register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(MultiModeComponentActionServant::MultiModeComponentActionServantTests);

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
#endif // MultiModeComponentActionServant_cpp
