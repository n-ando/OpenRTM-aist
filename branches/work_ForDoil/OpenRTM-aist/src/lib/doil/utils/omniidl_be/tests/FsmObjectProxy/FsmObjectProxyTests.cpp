// -*- C++ -*-
/*!
 * @file   FsmObjectProxyTests.cpp
 * @brief  FsmObjectProxy test class
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

#ifndef FsmObjectProxy_cpp
#define FsmObjectProxy_cpp

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>
#include <string>
#include <iostream>
#include <idl/SDOPackageSkel.h>
#include <idl/RTCSkel.h>
#include <FsmObjectProxy.h>
#include <rtm/NVUtil.h>
#include <ISDOService.h>
#include <ISDOSystemElement.h>
#include <IOrganization.h>
#include <doil/corba/CORBAManager.h>


/*!
 * @class FsmObjectProxyTests class
 * @brief FsmObjectProxy test
 */
namespace FsmObjectProxy
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
  class FsmObjectMock
    : public virtual ::POA_RTC::FsmObject
  {
  protected:
      ::std::vector<std::string> m_log;
  private:
      ::std::string m_name;
      ::std::string m_code;
      ::std::string m_val;
      ::SDOPackage::Parameter m_par;
      ::SDOPackage::StringList m_stlist;
      ::SDOPackage::EnumerationType m_etype;
      ::CORBA::Any m_any;
  public :
      FsmObjectMock(){}
      virtual ~FsmObjectMock()
      {
      }

      void setLogger(Logger* logger)
      {
        m_logger = logger;
      }

    /*! 
     *
     */
     ::RTC::ReturnCode_t send_stimulus(const char* message, ::RTC::ExecutionContextHandle_t exec_handle)
     {
        if (m_logger != NULL) m_logger->log("send_stimulus");
     }
  private:
    Logger* m_logger;

  };

  class FsmObjectProxyTests
   : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(FsmObjectProxyTests);
    CPPUNIT_TEST(test_send_stimulus);
    CPPUNIT_TEST_SUITE_END();
  
  private:
    CORBA::ORB_ptr m_pORB;
    PortableServer::POA_ptr m_pPOA;
  
  public:
  
    /*!
     * @brief Constructor
     */
    FsmObjectProxyTests()
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
    ~FsmObjectProxyTests()
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
    void test_send_stimulus()
    {
      FsmObjectMock* obj = new FsmObjectMock();
      ::CORBA::Object_ptr ref = obj->_this();
      if(::CORBA::is_nil(ref))
      {
         std::cout<<"ref is nil.Abort test."<<std::endl;
         return;
      }
      ::RTC::CORBA::FsmObjectProxy* ap 
                 = new ::RTC::CORBA::FsmObjectProxy(ref);

      Logger logger;
      obj->setLogger(&logger);

      CPPUNIT_ASSERT_EQUAL(0, logger.countLog("send_stimulus"));
      const ::SDOPackage::Local::DeviceProfile porf;
      const ::std::string str = "test";
      ::RTC::Local::ExecutionContextHandle_t exec_handle ;
      ap->send_stimulus(str,exec_handle);
      CPPUNIT_ASSERT_EQUAL(1, logger.countLog("send_stimulus"));

      

      delete ap;
      CORBA::release(ref);
    }
    /* test case */
    void test_case0()
    {
    }
  };
}; // namespace FsmObjectProxy

/*
 * Register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(FsmObjectProxy::FsmObjectProxyTests);

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
#endif // FsmObjectProxy_cpp
