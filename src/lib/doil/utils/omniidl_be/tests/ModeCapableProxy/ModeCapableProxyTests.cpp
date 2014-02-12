// -*- C++ -*-
/*!
 * @file   ModeCapableProxyTests.cpp
 * @brief  ModeCapableProxy test class
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

#ifndef ModeCapableProxy_cpp
#define ModeCapableProxy_cpp

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>
#include <string>
#include <iostream>
#include <idl/SDOPackageSkel.h>
#include <idl/RTCSkel.h>
#include <ModeCapableProxy.h>
#include <rtm/NVUtil.h>
#include <ISDOService.h>
#include <ISDOSystemElement.h>
#include <IOrganization.h>
#include <doil/corba/CORBAManager.h>


/*!
 * @class ModeCapableProxyTests class
 * @brief ModeCapableProxy test
 */
namespace ModeCapableProxy
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
  class ModeCapableMock
    : public virtual ::POA_RTC::ModeCapable
  {
  protected:
      ::std::vector<std::string> m_log;
  private:
  public :
      ModeCapableMock(){}
      virtual ~ModeCapableMock()
      {
      }

      void setLogger(Logger* logger)
      {
        m_logger = logger;
      }

    /*! 
     *
     */
     ::RTC::Mode_ptr get_default_mode()
     {
        if (m_logger != NULL) m_logger->log("get_default_mode");
     }
    /*! 
     *
     */
     ::RTC::Mode_ptr get_current_mode()
     {
     }
    /*! 
     *
     */
     ::RTC::Mode_ptr get_current_mode_in_context(::RTC::ExecutionContext_ptr exec_context)
     {
     }
    /*! 
     *
     */
     ::RTC::Mode_ptr get_pending_mode()
     {
     }
    /*! 
     *
     */
     ::RTC::Mode_ptr get_pending_mode_in_context(::RTC::ExecutionContext_ptr exec_context)
     {
     }
    /*! 
     *
     */
     ::RTC::ReturnCode_t set_mode(::RTC::Mode_ptr new_mode, ::CORBA::Boolean immediate)
     {
     }
  private:
    Logger* m_logger;

  };

  class ModeCapableProxyTests
   : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(ModeCapableProxyTests);
    CPPUNIT_TEST(test_get_default_mode);
    CPPUNIT_TEST_SUITE_END();
  
  private:
    CORBA::ORB_ptr m_pORB;
    PortableServer::POA_ptr m_pPOA;
  
  public:
  
    /*!
     * @brief Constructor
     */
    ModeCapableProxyTests()
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
    ~ModeCapableProxyTests()
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
    void test_get_default_mode()
    {
      ModeCapableMock* obj = new ModeCapableMock();
      ::CORBA::Object_ptr ref = obj->_this();
      if(::CORBA::is_nil(ref))
      {
         std::cout<<"ref is nil.Abort test."<<std::endl;
         return;
      }
      ::RTC::CORBA::ModeCapableProxy* ap 
                 = new ::RTC::CORBA::ModeCapableProxy(ref);

      Logger logger;
      obj->setLogger(&logger);

      CPPUNIT_ASSERT_EQUAL(0, logger.countLog("get_default_mode"));
      ap->get_default_mode();
      CPPUNIT_ASSERT_EQUAL(1, logger.countLog("get_default_mode"));

      

      delete ap;
      CORBA::release(ref);
    }
    /* test case */
    void test_case0()
    {
    }
  };
}; // namespace ModeCapableProxy

/*
 * Register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(ModeCapableProxy::ModeCapableProxyTests);

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
#endif // ModeCapableProxy_cpp
