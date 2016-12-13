// -*- C++ -*-
/*!
 * @file   FsmParticipantActionProxyTests.cpp
 * @brief  FsmParticipantActionProxy test class
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

#ifndef FsmParticipantActionProxy_cpp
#define FsmParticipantActionProxy_cpp

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>
#include <string>
#include <iostream>
#include <idl/SDOPackageSkel.h>
#include <idl/RTCSkel.h>
#include <FsmParticipantActionProxy.h>
#include <rtm/NVUtil.h>
#include <ISDOService.h>
#include <ISDOSystemElement.h>
#include <IOrganization.h>
#include <doil/corba/CORBAManager.h>


/*!
 * @class FsmParticipantActionProxyTests class
 * @brief FsmParticipantActionProxy test
 */
namespace FsmParticipantActionProxy
{
  class Logger
  {
  public:
    void log(const std::string& msg)
    {
      m_log.push_back(msg);
    }

    int countLog(const std::string& msg)
    {
      int count = 0;
      for (int i = 0; i < (int) m_log.size(); ++i)
        {
          if (m_log[i] == msg) ++count;
        }
     return count;
    }
		
  private:
    std::vector<std::string> m_log;
  };

  /*!
   * 
   * 
   *
   */
  class FsmParticipantActionMock
    : public virtual ::POA_RTC::FsmParticipantAction
  {
  protected:
      ::std::vector<std::string> m_log;
  private:
  public :
      FsmParticipantActionMock(){}
      virtual ~FsmParticipantActionMock()
      {
      }

      void setLogger(Logger* logger)
      {
        m_logger = logger;
      }

    /*! 
     *
     */
     ::RTC::ReturnCode_t on_action(::RTC::ExecutionContextHandle_t exec_handle)
     {
        if (m_logger != NULL) m_logger->log("on_action");
     }
  private:
    Logger* m_logger;

  };

  class FsmParticipantActionProxyTests
   : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(FsmParticipantActionProxyTests);
    CPPUNIT_TEST(test_on_action);
    CPPUNIT_TEST_SUITE_END();
  
  private:
    CORBA::ORB_ptr m_pORB;
    PortableServer::POA_ptr m_pPOA;
  
  public:
  
    /*!
     * @brief Constructor
     */
    FsmParticipantActionProxyTests()
    {
      int argc = 0;
      char** argv = NULL;
      m_pORB = CORBA::ORB_init(argc, argv);
      m_pPOA = PortableServer::POA::_narrow(
                       m_pORB->resolve_initial_references("RootPOA"));
      m_pPOA->the_POAManager()->activate();
    }
    
    /*!
     * @brief Destructor
     */
    ~FsmParticipantActionProxyTests()
    {
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
  
    /*! 
     *
     *
     *
     */
    void test_on_action()
    {
      FsmParticipantActionMock* obj = new FsmParticipantActionMock();
      ::CORBA::Object_ptr ref = obj->_this();
      if(::CORBA::is_nil(ref))
      {
         std::cout<<"ref is nil.Abort test."<<std::endl;
         return;
      }
      ::RTC::CORBA::FsmParticipantActionProxy* ap 
                 = new ::RTC::CORBA::FsmParticipantActionProxy(ref);

      Logger logger;
      obj->setLogger(&logger);

      CPPUNIT_ASSERT_EQUAL(0, logger.countLog("on_action"));
      ::RTC::ExecutionContextHandle_t exec_handle;
      ap->on_action(exec_handle);
      CPPUNIT_ASSERT_EQUAL(1, logger.countLog("on_action"));

      

      delete ap;
      CORBA::release(ref);
    }
    /* test case */
    void test_case0()
    {
    }
  };
}; // namespace FsmParticipantActionProxy

/*
 * Register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(FsmParticipantActionProxy::FsmParticipantActionProxyTests);

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
#endif // FsmParticipantActionProxy_cpp
