// -*- C++ -*-
/*!
 * @file   PortServiceServantTests.cpp
 * @brief  PortServiceServant test class
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

#ifndef PortServiceServant_cpp
#define PortServiceServant_cpp

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>
#include <PortServiceServant.h>
#include <doil/ServantBase.h>
#include <doil/corba/CORBAManager.h>
#include <stubs/PortServiceImpl.h>
#include <stubs/Logger.h>

/*!
 * @class PortServiceServantTests class
 * @brief PortServiceServant test
 */
namespace PortServiceServant
{
  class PortServiceServantTests
   : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(PortServiceServantTests);
    CPPUNIT_TEST(test_call_get_port_profile);
    CPPUNIT_TEST(test_call_get_connector_profiles);
    CPPUNIT_TEST(test_call_get_connector_profile);
    CPPUNIT_TEST(test_call_connect);
    CPPUNIT_TEST(test_call_disconnect);
    CPPUNIT_TEST(test_call_disconnect_all);
    CPPUNIT_TEST(test_call_notify_connect);
    CPPUNIT_TEST(test_call_notify_disconnect);
    //CPPUNIT_TEST(test_case0);
    CPPUNIT_TEST_SUITE_END();
  
  private:
    ::UnitTest::Servant::PortServiceImpl* Impl;
    ::UnitTest::Servant::Logger Log;
    ::doil::ServantBase* Servant;
    ::RTC::CORBA::PortServiceServant * CServant;
  
  public:
  
    /*!
     * @brief Constructor
     */
    PortServiceServantTests()
    {
        // registerFactory
        Impl = new UnitTest::Servant::PortServiceImpl(Log);
        doil::CORBA::CORBAManager::instance().registerFactory(Impl->id(),
            doil::New<RTC::CORBA::PortServiceServant>,
            doil::Delete<RTC::CORBA::PortServiceServant>);
        doil::ReturnCode_t ret = doil::CORBA::CORBAManager::instance().activateObject(Impl);
        Servant = doil::CORBA::CORBAManager::instance().toServant(Impl);
        CServant = dynamic_cast<RTC::CORBA::PortServiceServant*>(Servant);
    }
    
    /*!
     * @brief Destructor
     */
    ~PortServiceServantTests()
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
  
    void test_call_get_port_profile()
    {
      CPPUNIT_ASSERT(CServant);

      std::string str("get_port_profile");
      ::RTC::PortProfile *result;
      result = CServant->get_port_profile();
      //CPPUNIT_ASSERT_EQUAL_MESSAGE("not true", RTC::RTC_OK, result);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not method name", Log.pop(), str);
    }
    void test_call_get_connector_profiles()
    {
      CPPUNIT_ASSERT(CServant);

      std::string str("get_connector_profiles");
      ::RTC::ConnectorProfileList *result;
      result = CServant->get_connector_profiles();
      //CPPUNIT_ASSERT_EQUAL_MESSAGE("not true", RTC::RTC_OK, result);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not method name", Log.pop(), str);
    }
    void test_call_get_connector_profile()
    {
      CPPUNIT_ASSERT(CServant);

      std::string str("get_connector_profile");
      std::string str2("foo");
      ::RTC::ConnectorProfile *result;
      result = CServant->get_connector_profile(str2.c_str());
      //CPPUNIT_ASSERT_EQUAL_MESSAGE("not true", RTC::RTC_OK, result);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not method name", Log.pop(), str);
    }
    void test_call_connect()
    {
      CPPUNIT_ASSERT(CServant);

      std::string str("connect");
      ::RTC::ConnectorProfile connector_profile;
      ::RTC::ReturnCode_t result;
      result = CServant->connect(connector_profile);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not true", RTC::RTC_OK, result);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not method name", Log.pop(), str);
    }
    void test_call_disconnect()
    {
      CPPUNIT_ASSERT(CServant);

      std::string str("disconnect");
      std::string str2("foo");
      ::RTC::ReturnCode_t result;
      result = CServant->disconnect(str2.c_str());
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not true", RTC::RTC_OK, result);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not method name", Log.pop(), str);
    }
    void test_call_disconnect_all()
    {
      CPPUNIT_ASSERT(CServant);

      std::string str("disconnect_all");
      ::RTC::ReturnCode_t result;
      result = CServant->disconnect_all();
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not true", RTC::RTC_OK, result);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not method name", Log.pop(), str);
    }
    void test_call_notify_connect()
    {
      CPPUNIT_ASSERT(CServant);

      std::string str("notify_connect");
      ::RTC::ConnectorProfile connector_profile;
      ::RTC::ReturnCode_t result;
      result = CServant->notify_connect(connector_profile);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not true", RTC::RTC_OK, result);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not method name", Log.pop(), str);
    }
    void test_call_notify_disconnect()
    {
      CPPUNIT_ASSERT(CServant);

      std::string str("notify_disconnect");
      std::string str2("foo");
      ::RTC::ReturnCode_t result;
      result = CServant->notify_disconnect(str2.c_str());
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not true", RTC::RTC_OK, result);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not method name", Log.pop(), str);
    }

    /* test case */
    void test_case0()
    {
      CPPUNIT_FAIL("Automatic failue.");
    }
  };
}; // namespace PortServiceServant

/*
 * Register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(PortServiceServant::PortServiceServantTests);

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
#endif // PortServiceServant_cpp
