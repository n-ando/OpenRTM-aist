// -*- C++ -*-
/*!
 * @file   SDOServantTests.cpp
 * @brief  SDOServant test class
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

#ifndef SDOServant_cpp
#define SDOServant_cpp

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>

#include <SDOServant.h>
#include <SDOServiceServant.h>
#include <ConfigurationServant.h>
#include <MonitoringServant.h>

#include <doil/ServantBase.h>
#include <doil/corba/CORBAManager.h>

#include <stubs/SDOImpl.h>
#include <stubs/SDOServiceImpl.h>
#include <stubs/ConfigurationImpl.h>
#include <stubs/MonitoringImpl.h>

#include <stubs/Logger.h>

/*!
 * @class SDOServantTests class
 * @brief SDOServant test
 */
namespace SDOServant
{
  class SDOServantTests
   : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(SDOServantTests);
    CPPUNIT_TEST(test_call_get_sdo_id);
    CPPUNIT_TEST(test_call_get_sdo_type);
    CPPUNIT_TEST(test_call_get_device_profile);
    CPPUNIT_TEST(test_call_get_service_profiles);

    CPPUNIT_TEST(test_call_get_service_profile);
    CPPUNIT_TEST(test_call_get_sdo_service);
    CPPUNIT_TEST(test_call_get_configuration);
    CPPUNIT_TEST(test_call_get_monitoring);

    CPPUNIT_TEST(test_call_get_organizations);
    CPPUNIT_TEST(test_call_get_status_list);
    CPPUNIT_TEST(test_call_get_status);
    //CPPUNIT_TEST(test_case0);
    CPPUNIT_TEST_SUITE_END();
  
  private:
    ::UnitTest::Servant::SDOImpl* Impl;
    ::UnitTest::Servant::SDOServiceImpl* SSImpl;
    ::UnitTest::Servant::ConfigurationImpl* CImpl;
    ::UnitTest::Servant::MonitoringImpl* MImpl;

    ::UnitTest::Servant::Logger Log;

    ::doil::ServantBase* Servant;
    ::SDOPackage::CORBA::SDOServant * CServant;
    ::SDOPackage::CORBA::SDOServiceServant * CSServant;
    ::SDOPackage::CORBA::ConfigurationServant * CCServant;
    ::SDOPackage::CORBA::MonitoringServant * MServant;
  
  public:
  
    /*!
     * @brief Constructor
     */
    SDOServantTests()
    {
        // registerFactory
        Impl = new UnitTest::Servant::SDOImpl(Log);
        doil::CORBA::CORBAManager::instance().registerFactory(Impl->id(),
            doil::New<SDOPackage::CORBA::SDOServant>,
            doil::Delete<SDOPackage::CORBA::SDOServant>);
        doil::ReturnCode_t ret = doil::CORBA::CORBAManager::instance().activateObject(Impl);
        Servant = doil::CORBA::CORBAManager::instance().toServant(Impl);
        CServant = dynamic_cast<SDOPackage::CORBA::SDOServant*>(Servant);

        SSImpl = new UnitTest::Servant::SDOServiceImpl();
        doil::CORBA::CORBAManager::instance().registerFactory(SSImpl->id(),
            doil::New<SDOPackage::CORBA::SDOServiceServant>,
            doil::Delete<SDOPackage::CORBA::SDOServiceServant>);
        doil::ReturnCode_t ret2 = doil::CORBA::CORBAManager::instance().activateObject(SSImpl);
        //Servant = doil::CORBA::CORBAManager::instance().toServant(SSImpl);
        //CSServant = dynamic_cast<SDOPackage::CORBA::SDOServiceServant*>(Servant);

        CImpl = new UnitTest::Servant::ConfigurationImpl();
        doil::CORBA::CORBAManager::instance().registerFactory(CImpl->id(),
            doil::New<SDOPackage::CORBA::ConfigurationServant>,
            doil::Delete<SDOPackage::CORBA::ConfigurationServant>);
        doil::CORBA::CORBAManager::instance().activateObject(CImpl);
        //Servant = doil::CORBA::CORBAManager::instance().toServant(CImpl);
        //CCServant = dynamic_cast<SDOPackage::CORBA::ConfigurationServant*>(Servant);

        MImpl = new UnitTest::Servant::MonitoringImpl();
        doil::CORBA::CORBAManager::instance().registerFactory(MImpl->id(),
            doil::New<SDOPackage::CORBA::MonitoringServant>,
            doil::Delete<SDOPackage::CORBA::MonitoringServant>);
        doil::CORBA::CORBAManager::instance().activateObject(MImpl);
    }
    
    /*!
     * @brief Destructor
     */
    ~SDOServantTests()
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
    void test_call_get_sdo_id()
    {
      CPPUNIT_ASSERT(CServant);

      std::string str("get_sdo_id");
      std::string str2("bar");
      ::std::string result;
      result = CServant->get_sdo_id();
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not true", str2, result);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not method name", Log.pop(), str);
    }
    void test_call_get_sdo_type()
    {
      CPPUNIT_ASSERT(CServant);

      std::string str("get_sdo_type");
      std::string str2("bar");
      ::std::string result;
      result = CServant->get_sdo_type();
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not true", str2, result);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not method name", Log.pop(), str);
    }
    void test_call_get_device_profile()
    {
      CPPUNIT_ASSERT(CServant);

      std::string str("get_device_profile");
      ::SDOPackage::DeviceProfile* result;
      result = CServant->get_device_profile();
      //CPPUNIT_ASSERT_EQUAL_MESSAGE("not true", "bar", result);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not method name", Log.pop(), str);
    }
    void test_call_get_service_profiles()
    {
      CPPUNIT_ASSERT(CServant);

      std::string str("get_service_profiles");
      ::SDOPackage::ServiceProfileList* result;
      result = CServant->get_service_profiles();
      //CPPUNIT_ASSERT_EQUAL_MESSAGE("not true", "bar", result);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not method name", Log.pop(), str);
    }
    void test_call_get_service_profile()
    {
      CPPUNIT_ASSERT(CServant);

      std::string str("get_service_profile");
      ::SDOPackage::ServiceProfile* result;
      result = CServant->get_service_profile("foo");
      //CPPUNIT_ASSERT_EQUAL_MESSAGE("not true", "bar", result);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not method name", Log.pop(), str);
    }
    void test_call_get_sdo_service()
    {
      CPPUNIT_ASSERT(CServant);

      std::string str("get_sdo_service");
      ::SDOPackage::SDOService_ptr result;
      result = CServant->get_sdo_service("foo");
      //CPPUNIT_ASSERT_EQUAL_MESSAGE("not true", "bar", result);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not method name", Log.pop(), str);
    }
    void test_call_get_configuration()
    {
      CPPUNIT_ASSERT(CServant);

      std::string str("get_configuration");
      ::SDOPackage::Configuration_ptr result;
      result = CServant->get_configuration();
      //CPPUNIT_ASSERT_EQUAL_MESSAGE("not true", "bar", result);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not method name", Log.pop(), str);
    }
    void test_call_get_monitoring()
    {
      CPPUNIT_ASSERT(CServant);

      std::string str("get_monitoring");
      ::SDOPackage::Monitoring_ptr result;
      result = CServant->get_monitoring();
      //CPPUNIT_ASSERT_EQUAL_MESSAGE("not true", "bar", result);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not method name", Log.pop(), str);
    }
    void test_call_get_organizations()
    {
      CPPUNIT_ASSERT(CServant);

      std::string str("get_organizations");
      ::SDOPackage::OrganizationList_var result;
      result = CServant->get_organizations();
      //CPPUNIT_ASSERT_EQUAL_MESSAGE("not true", "bar", result);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not method name", Log.pop(), str);
    }
    void test_call_get_status_list()
    {
      CPPUNIT_ASSERT(CServant);

      std::string str("get_status_list");
      ::SDOPackage::NVList* result;
      result = CServant->get_status_list();
      //CPPUNIT_ASSERT_EQUAL_MESSAGE("not true", "bar", result);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not method name", Log.pop(), str);
    }
    void test_call_get_status()
    {
      CPPUNIT_ASSERT(CServant);

      std::string str("get_status");
      CORBA::Any* result;
      result = CServant->get_status("foo");
      //CPPUNIT_ASSERT_EQUAL_MESSAGE("not true", "bar", result);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not method name", Log.pop(), str);
    }
  
    /* test case */
    void test_case0()
    {
      CPPUNIT_FAIL("Automatic failue.");
    }
  };
}; // namespace SDOServant

/*
 * Register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(SDOServant::SDOServantTests);

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
#endif // SDOServant_cpp
