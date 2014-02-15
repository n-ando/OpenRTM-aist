// -*- C++ -*-
/*!
 * @file   OrganizationServantTests.cpp
 * @brief  OrganizationServant test class
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

#ifndef OrganizationServant_cpp
#define OrganizationServant_cpp

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>

#include <OrganizationServant.h>
#include <SDOSystemElementServant.h>

#include <doil/ServantBase.h>
#include <doil/corba/CORBAManager.h>

#include <stubs/OrganizationImpl.h>
#include <stubs/SDOSystemElementImpl.h>

#include <stubs/Logger.h>

/*!
 * @class OrganizationServantTests class
 * @brief OrganizationServant test
 */
namespace OrganizationServant
{
  class OrganizationServantTests
   : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(OrganizationServantTests);
    CPPUNIT_TEST(test_call_get_organization_id);
    CPPUNIT_TEST(test_call_get_organization_property);
    CPPUNIT_TEST(test_call_get_organization_property_value);
    CPPUNIT_TEST(test_call_add_organization_property);
    CPPUNIT_TEST(test_call_set_organization_property_value);
    CPPUNIT_TEST(test_call_remove_organization_property);
    CPPUNIT_TEST(test_call_get_owner);
    CPPUNIT_TEST(test_call_set_owner);
    CPPUNIT_TEST(test_call_get_members);
    CPPUNIT_TEST(test_call_set_members);
    CPPUNIT_TEST(test_call_add_members);
    CPPUNIT_TEST(test_call_remove_member);
    CPPUNIT_TEST(test_call_get_dependency);
    CPPUNIT_TEST(test_call_set_dependency);
    //CPPUNIT_TEST(test_case0);
    CPPUNIT_TEST_SUITE_END();
  
  private:
    ::UnitTest::Servant::OrganizationImpl* Impl;
    ::UnitTest::Servant::SDOSystemElementImpl* SSEImpl;
    ::UnitTest::Servant::Logger Log;
    ::doil::ServantBase* Servant;
    ::SDOPackage::CORBA::OrganizationServant * CServant;
  
  public:
  
    /*!
     * @brief Constructor
     */
    OrganizationServantTests()
    {
        // registerFactory
        Impl = new UnitTest::Servant::OrganizationImpl(Log);
        doil::CORBA::CORBAManager::instance().registerFactory(Impl->id(),
            doil::New<SDOPackage::CORBA::OrganizationServant>,
            doil::Delete<SDOPackage::CORBA::OrganizationServant>);
        doil::ReturnCode_t ret = doil::CORBA::CORBAManager::instance().activateObject(Impl);
        Servant = doil::CORBA::CORBAManager::instance().toServant(Impl);
        CServant = dynamic_cast<SDOPackage::CORBA::OrganizationServant*>(Servant);

        SSEImpl = new UnitTest::Servant::SDOSystemElementImpl(Log);
        doil::CORBA::CORBAManager::instance().registerFactory(SSEImpl->id(),
            doil::New<SDOPackage::CORBA::SDOSystemElementServant>,
            doil::Delete<SDOPackage::CORBA::SDOSystemElementServant>);
        ret = doil::CORBA::CORBAManager::instance().activateObject(SSEImpl);
    }
    
    /*!
     * @brief Destructor
     */
    ~OrganizationServantTests()
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
    void test_call_get_organization_id()
    {
      CPPUNIT_ASSERT(CServant);

      std::string str("get_organization_id");
      std::string str2("foo");
      ::std::string result;
      result = CServant->get_organization_id();
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not true", str2, result);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not method name", Log.pop(), str);
    }
    void test_call_get_organization_property()
    {
      CPPUNIT_ASSERT(CServant);

      std::string str("get_organization_property");
      ::SDOPackage::OrganizationProperty* result;
      result = CServant->get_organization_property();
      //CPPUNIT_ASSERT_EQUAL_MESSAGE("not true", ::RTC::RTC_OK, result);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not method name", Log.pop(), str);
    }

    void test_call_get_organization_property_value()
    {
      CPPUNIT_ASSERT(CServant);

      std::string str("get_organization_property_value");
      CORBA::Any* result;
      result = CServant->get_organization_property_value("foo");
      //CPPUNIT_ASSERT(!::CORBA::is_nil(result));
      //CPPUNIT_ASSERT_EQUAL_MESSAGE("not true", str2, result);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not method name", Log.pop(), str);
    }

    void test_call_add_organization_property()
    {
      CPPUNIT_ASSERT(CServant);

      std::string str("add_organization_property");
      ::CORBA::Boolean result;
      ::SDOPackage::OrganizationProperty organization_property;
      result = CServant->add_organization_property(organization_property);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not true", true, result);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not method name", Log.pop(), str);
    }

    void test_call_set_organization_property_value()
    {
      CPPUNIT_ASSERT(CServant);

      std::string str("set_organization_property_value");
      const std::string str1 = "bar";
      const std::string str2 = "foo";
      CORBA::Any any;
      any <<= str.c_str();
      ::CORBA::Boolean result;
      result = CServant->set_organization_property_value("bar",any);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not true", true, result);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not method name", Log.pop(), str);
    }

    void test_call_remove_organization_property()
    {
      CPPUNIT_ASSERT(CServant);

      std::string str("remove_organization_property");
      ::CORBA::Boolean result;
      result = CServant->remove_organization_property("bar");
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not true", true, result);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not method name", Log.pop(), str);
    }

    void test_call_get_owner()
    {
      CPPUNIT_ASSERT(CServant);

      std::string str("get_owner");
      SDOPackage::SDOSystemElement_var varOwner;
      SDOPackage::SDOSystemElement_ptr ptrOwner;
      varOwner = CServant->get_owner();
      //CPPUNIT_ASSERT(!::CORBA::is_nil(varOwner));
      //CPPUNIT_ASSERT_EQUAL_MESSAGE("not true", ::RTC::RTC_OK, result);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not method name", Log.pop(), str);
    }

    void test_call_set_owner()
    {
      CPPUNIT_ASSERT(CServant);

      std::string str("set_owner");
      ::CORBA::Boolean result;
      ::SDOPackage::SDOSystemElement_ptr sdo;
      result = CServant->set_owner(sdo);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not true", true, result);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not method name", Log.pop(), str);
    }

    void test_call_get_members()
    {
      CPPUNIT_ASSERT(CServant);

      std::string str("get_members");
      ::SDOPackage::SDOList* result;
      result = CServant->get_members();
      //CPPUNIT_ASSERT_EQUAL_MESSAGE("not true", ::RTC::RTC_OK, result);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not method name", Log.pop(), str);
    }

    void test_call_set_members()
    {
      CPPUNIT_ASSERT(CServant);

      std::string str("set_members");
      ::CORBA::Boolean result;
      ::SDOPackage::SDOList sdo_list;
      result = CServant->set_members(sdo_list);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not true", true, result);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not method name", Log.pop(), str);
    }

    void test_call_add_members()
    {
      CPPUNIT_ASSERT(CServant);

      std::string str("add_members");
      ::CORBA::Boolean result;
      ::SDOPackage::SDOList sdo_list;
      result = CServant->add_members(sdo_list);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not true", true, result);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not method name", Log.pop(), str);
    }

    void test_call_remove_member()
    {
      CPPUNIT_ASSERT(CServant);

      std::string str("remove_member");
      ::CORBA::Boolean result;
      result = CServant->remove_member("bar");
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not true", true, result);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not method name", Log.pop(), str);
    }

    void test_call_get_dependency()
    {
      CPPUNIT_ASSERT(CServant);

      std::string str("get_dependency");
      ::SDOPackage::DependencyType result;
      result = CServant->get_dependency();
      //CPPUNIT_ASSERT(!::CORBA::is_nil(result));
      //CPPUNIT_ASSERT_EQUAL_MESSAGE("not true", ::RTC::RTC_OK, result);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not method name", Log.pop(), str);
    }

    void test_call_set_dependency()
    {
      CPPUNIT_ASSERT(CServant);

      std::string str("set_dependency");
      ::CORBA::Boolean result;
      ::SDOPackage::DependencyType dependency;
      result = CServant->set_dependency(dependency);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not true", true, result);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not method name", Log.pop(), str);
    }
  
    /* test case */
    void test_case0()
    {
      CPPUNIT_FAIL("Automatic failue.");
    }
  };
}; // namespace OrganizationServant

/*
 * Register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(OrganizationServant::OrganizationServantTests);

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
#endif // OrganizationServant_cpp
