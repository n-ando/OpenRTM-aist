// -*- C++ -*-
/*!
 * @file   LightweightRTObjectProxyTests.cpp
 * @brief  LightweightRTObjectProxy test class
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

#ifndef LightweightRTObjectProxy_cpp
#define LightweightRTObjectProxy_cpp

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>
#include <string>
#include <iostream>
#include <idl/SDOPackageSkel.h>
#include <idl/RTCSkel.h>
#include <LightweightRTObjectProxy.h>
#include <rtm/NVUtil.h>
#include <ISDOService.h>
#include <ISDOSystemElement.h>
#include <IOrganization.h>
#include <doil/corba/CORBAManager.h>


/*!
 * @class LightweightRTObjectProxyTests class
 * @brief LightweightRTObjectProxy test
 */
namespace LightweightRTObjectProxy
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
  class LightweightRTObjectMock
    : public virtual ::POA_RTC::LightweightRTObject
  {
  protected:
      ::std::vector<std::string> m_log;
  private:
  public :
      LightweightRTObjectMock(){}
      virtual ~LightweightRTObjectMock()
      {
      }

      void setLogger(Logger* logger)
      {
        m_logger = logger;
      }

    /*! 
     *
     */
    ::RTC::ReturnCode_t initialize()
    {
        if (m_logger != NULL) 
        {
            m_logger->log("initialize");
        }
    }
    /*! 
     *
     */
    ::RTC::ReturnCode_t finalize()
    {
    }
    /*! 
     *
     */
    ::CORBA::Boolean is_alive(::RTC::ExecutionContext_ptr exec_context)
    {
    }
    /*! 
     *
     */
    ::RTC::ReturnCode_t exit()
    {
    }
    /*! 
     *
     */
    ::RTC::ExecutionContextHandle_t attach_context(::RTC::ExecutionContext_ptr exec_context)
    {
    }
    /*! 
     *
     */
    ::RTC::ReturnCode_t detach_context(::RTC::ExecutionContextHandle_t exec_handle)
    {
    }
    /*! 
     *
     */
    ::RTC::ExecutionContext_ptr get_context(::RTC::ExecutionContextHandle_t exec_handle)
    {
    }
    /*! 
     *
     */
    ::RTC::ExecutionContextList* get_owned_contexts()
    {
    }
    /*! 
     *
     */
    ::RTC::ExecutionContextList* get_participating_contexts()
    {
    }
    /*! 
     *
     */
    ::RTC::ExecutionContextHandle_t get_context_handle(::RTC::ExecutionContext_ptr cxt)
    {
    }
    /*! 
     *
     */
    ::RTC::ReturnCode_t on_initialize()
    {
        if (m_logger != NULL) 
        {
            m_logger->log("on_initialize");
        }
    }
    /*! 
     *
     */
    ::RTC::ReturnCode_t on_finalize()
    {
    }
    /*! 
     *
     */
    ::RTC::ReturnCode_t on_startup(::RTC::ExecutionContextHandle_t exec_handle)
    {
    }
    /*! 
     *
     */
    ::RTC::ReturnCode_t on_shutdown(::RTC::ExecutionContextHandle_t exec_handle)
    {
    }
    /*! 
     *
     */
    ::RTC::ReturnCode_t on_activated(::RTC::ExecutionContextHandle_t exec_handle)
    {
    }
    /*! 
     *
     */
    ::RTC::ReturnCode_t on_deactivated(::RTC::ExecutionContextHandle_t exec_handle)
    {
    }
    /*! 
     *
     */
    ::RTC::ReturnCode_t on_aborting(::RTC::ExecutionContextHandle_t exec_handle)
    {
    }
    /*! 
     *
     */
    ::RTC::ReturnCode_t on_error(::RTC::ExecutionContextHandle_t exec_handle)
    {
    }
    /*! 
     *
     */
    ::RTC::ReturnCode_t on_reset(::RTC::ExecutionContextHandle_t exec_handle)
    {
    }
  private:
    Logger* m_logger;

  };

  class LightweightRTObjectProxyTests
   : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(LightweightRTObjectProxyTests);
    CPPUNIT_TEST(test_initialize);
    CPPUNIT_TEST_SUITE_END();
  
  private:
    CORBA::ORB_ptr m_pORB;
    PortableServer::POA_ptr m_pPOA;
  
  public:
  
    /*!
     * @brief Constructor
     */
    LightweightRTObjectProxyTests()
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
    ~LightweightRTObjectProxyTests()
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
    void test_initialize()
    {
      LightweightRTObjectMock* obj = new LightweightRTObjectMock();
      ::CORBA::Object_ptr ref = obj->_this();
      if(::CORBA::is_nil(ref))
      {
         std::cout<<"ref is nil.Abort test."<<std::endl;
         return;
      }
      ::RTC::CORBA::LightweightRTObjectProxy* ap 
                 = new ::RTC::CORBA::LightweightRTObjectProxy(ref);

      Logger logger;
      obj->setLogger(&logger);

      CPPUNIT_ASSERT_EQUAL(0, logger.countLog("initialize"));
      ap->initialize();
      CPPUNIT_ASSERT_EQUAL(1, logger.countLog("initialize"));

      

      delete ap;
      CORBA::release(ref);
    }
    /* test case */
    void test_case0()
    {
    }
  };
}; // namespace LightweightRTObjectProxy

/*
 * Register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(LightweightRTObjectProxy::LightweightRTObjectProxyTests);

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
#endif // LightweightRTObjectProxy_cpp
