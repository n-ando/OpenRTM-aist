// -*- C++ -*-
/*!
 * @file   ExecutionContextServiceServantTests.cpp
 * @brief  ExecutionContextServiceServant test class
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

#ifndef ExecutionContextServiceServant_cpp
#define ExecutionContextServiceServant_cpp

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>
#include <ExecutionContextServiceServant.h>
#include <doil/ServantBase.h>
#include <doil/corba/CORBAManager.h>
#include <stubs/ExecutionContextServiceImpl.h>
#include <stubs/Logger.h>


/*!
 * @class ExecutionContextServiceServantTests class
 * @brief ExecutionContextServiceServant test
 */
namespace ExecutionContextServiceServant
{
  class ExecutionContextServiceServantTests
   : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(ExecutionContextServiceServantTests);
    CPPUNIT_TEST(test_call_get_profile);
    //CPPUNIT_TEST(test_case0);
    CPPUNIT_TEST_SUITE_END();
  
  private:
    ::UnitTest::Servant::ExecutionContextServiceImpl* Impl;
    ::UnitTest::Servant::Logger Log;
    ::doil::ServantBase* Servant;
    ::RTC::CORBA::ExecutionContextServiceServant * CServant;
  
  public:
  
    /*!
     * @brief Constructor
     */
    ExecutionContextServiceServantTests()
    {
        // registerFactory
        Impl = new UnitTest::Servant::ExecutionContextServiceImpl(Log);
        doil::CORBA::CORBAManager::instance().registerFactory(Impl->id(),
            doil::New<RTC::CORBA::ExecutionContextServiceServant>,
            doil::Delete<RTC::CORBA::ExecutionContextServiceServant>);
        doil::ReturnCode_t ret = doil::CORBA::CORBAManager::instance().activateObject(Impl);
        Servant = doil::CORBA::CORBAManager::instance().toServant(Impl);
        CServant = dynamic_cast<RTC::CORBA::ExecutionContextServiceServant*>(Servant);
    }
    
    /*!
     * @brief Destructor
     */
    ~ExecutionContextServiceServantTests()
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
  
    void test_call_get_profile()
    {
      CPPUNIT_ASSERT(CServant);

      std::string str("get_profile");
      ::RTC::ExecutionContextProfile* result;
      result = CServant->get_profile();
      //CPPUNIT_ASSERT_EQUAL_MESSAGE("not true", true, result);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not method name", Log.pop(), str);
    }
    /* test case */
    void test_case0()
    {
      CPPUNIT_FAIL("Automatic failue.");
    }
  };
}; // namespace ExecutionContextServiceServant

/*
 * Register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(ExecutionContextServiceServant::ExecutionContextServiceServantTests);

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
#endif // ExecutionContextServiceServant_cpp
