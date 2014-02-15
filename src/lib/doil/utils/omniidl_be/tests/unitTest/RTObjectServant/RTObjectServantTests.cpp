// -*- C++ -*-
/*!
 * @file   RTObjectServantTests.cpp
 * @brief  RTObjectServant test class
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

#ifndef RTObjectServant_cpp
#define RTObjectServant_cpp

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>
#include <RTObjectServant.h>
#include <doil/ServantBase.h>
#include <doil/corba/CORBAManager.h>
#include <stubs/RTObjectImpl.h>
#include <stubs/Logger.h>

/*!
 * @class RTObjectServantTests class
 * @brief RTObjectServant test
 */
namespace RTObjectServant
{
  class RTObjectServantTests
   : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(RTObjectServantTests);
    CPPUNIT_TEST(test_call_get_component_profile);
    CPPUNIT_TEST(test_call_get_ports);
    //CPPUNIT_TEST(test_case0);
    CPPUNIT_TEST_SUITE_END();
  
  private:
    ::UnitTest::Servant::RTObjectImpl* Impl;
    ::UnitTest::Servant::Logger Log;
    ::doil::ServantBase* Servant;
    ::RTC::CORBA::RTObjectServant * CServant;
  
  public:
  
    /*!
     * @brief Constructor
     */
    RTObjectServantTests()
    {
        // registerFactory
        Impl = new UnitTest::Servant::RTObjectImpl(Log);
        doil::CORBA::CORBAManager::instance().registerFactory(Impl->id(),
            doil::New<RTC::CORBA::RTObjectServant>,
            doil::Delete<RTC::CORBA::RTObjectServant>);
        doil::ReturnCode_t ret = doil::CORBA::CORBAManager::instance().activateObject(Impl);
        Servant = doil::CORBA::CORBAManager::instance().toServant(Impl);
        CServant = dynamic_cast<RTC::CORBA::RTObjectServant*>(Servant);
    }
    
    /*!
     * @brief Destructor
     */
    ~RTObjectServantTests()
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


    void test_call_get_component_profile()
    {
      CPPUNIT_ASSERT(CServant);

      std::string str("get_component_profile");
      ::RTC::ComponentProfile *result;
      result = CServant->get_component_profile();
      //CPPUNIT_ASSERT_EQUAL_MESSAGE("not true", RTC::RTC_OK, result);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not method name", Log.pop(), str);
    }

    void test_call_get_ports()
    {
      CPPUNIT_ASSERT(CServant);

      std::string str("get_ports");
      ::RTC::PortServiceList *result;
      result = CServant->get_ports();
      //CPPUNIT_ASSERT_EQUAL_MESSAGE("not true", RTC::RTC_OK, result);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not method name", Log.pop(), str);
    }

  
    /* test case */
    void test_case0()
    {
      CPPUNIT_FAIL("Automatic failue.");
    }
  };
}; // namespace RTObjectServant

/*
 * Register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(RTObjectServant::RTObjectServantTests);

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
#endif // RTObjectServant_cpp
