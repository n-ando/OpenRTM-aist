// -*- C++ -*-
/*!
 * @file   SDOSystemElementServantTests.cpp
 * @brief  SDOSystemElementServant test class
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

#ifndef SDOSystemElementServant_cpp
#define SDOSystemElementServant_cpp

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>
#include <SDOSystemElementServant.h>
#include <doil/ServantBase.h>
#include <doil/corba/CORBAManager.h>
#include <stubs/SDOSystemElementImpl.h>
#include <stubs/Logger.h>

/*!
 * @class SDOSystemElementServantTests class
 * @brief SDOSystemElementServant test
 */
namespace SDOSystemElementServant
{
  class SDOSystemElementServantTests
   : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(SDOSystemElementServantTests);
    CPPUNIT_TEST(test_call_get_owned_organizations);
    //CPPUNIT_TEST(test_case0);
    CPPUNIT_TEST_SUITE_END();
  
  private:
    ::UnitTest::Servant::SDOSystemElementImpl* Impl;
    ::UnitTest::Servant::Logger Log;
    ::doil::ServantBase* Servant;
    ::SDOPackage::CORBA::SDOSystemElementServant * CServant;
  
  public:
  
    /*!
     * @brief Constructor
     */
    SDOSystemElementServantTests()
    {
        // registerFactory
        Impl = new UnitTest::Servant::SDOSystemElementImpl(Log);
        doil::CORBA::CORBAManager::instance().registerFactory(Impl->id(),
            doil::New<SDOPackage::CORBA::SDOSystemElementServant>,
            doil::Delete<SDOPackage::CORBA::SDOSystemElementServant>);
        doil::ReturnCode_t ret = doil::CORBA::CORBAManager::instance().activateObject(Impl);
        Servant = doil::CORBA::CORBAManager::instance().toServant(Impl);
        CServant = dynamic_cast<SDOPackage::CORBA::SDOSystemElementServant*>(Servant);
    }
    
    /*!
     * @brief Destructor
     */
    ~SDOSystemElementServantTests()
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

    void test_call_get_owned_organizations()
    { 
      CPPUNIT_ASSERT(CServant);

      std::string str("get_owned_organizations");
      ::SDOPackage::OrganizationList_var result;
      result = CServant->get_owned_organizations();
      //CPPUNIT_ASSERT_EQUAL_MESSAGE("not true", RTC::RTC_OK, result);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not method name", Log.pop(), str);
    }
  
    /* test case */
    void test_case0()
    {
      CPPUNIT_FAIL("Automatic failue.");
    }
  };
}; // namespace SDOSystemElementServant

/*
 * Register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(SDOSystemElementServant::SDOSystemElementServantTests);

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
#endif // SDOSystemElementServant_cpp
