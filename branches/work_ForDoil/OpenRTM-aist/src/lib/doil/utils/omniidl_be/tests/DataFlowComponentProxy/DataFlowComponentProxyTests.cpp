// -*- C++ -*-
/*!
 * @file   DataFlowComponentProxyTests.cpp
 * @brief  DataFlowComponentProxy test class
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

#ifndef DataFlowComponentProxy_cpp
#define DataFlowComponentProxy_cpp

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>
#include <string>
#include <iostream>
#include <idl/SDOPackageSkel.h>
#include <idl/RTCSkel.h>
#include <DataFlowComponentProxy.h>
#include <rtm/NVUtil.h>
#include <ISDOService.h>
#include <ISDOSystemElement.h>
#include <IOrganization.h>
#include <doil/corba/CORBAManager.h>


/*!
 * @class DataFlowComponentProxyTests class
 * @brief DataFlowComponentProxy test
 */
namespace DataFlowComponentProxy
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
  class DataFlowComponentMock
    : public virtual ::POA_RTC::DataFlowComponent
  {
  protected:
      ::std::vector<std::string> m_log;
  private:
  public :
      DataFlowComponentMock(){}
      virtual ~DataFlowComponentMock()
      {
      }

      void setLogger(Logger* logger)
      {
        m_logger = logger;
      }

  private:
    Logger* m_logger;
    /*! 
     *
     */
    ::RTC::ReturnCode_t on_execute(::RTC::ExecutionContextHandle_t exec_handle)
    {
        if (m_logger != NULL) 
        {
            m_logger->log("on_execute");
        }
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
    /*! 
     *
     */
    ::RTC::ReturnCode_t on_state_update(::RTC::ExecutionContextHandle_t exec_handle)
    {
        if (m_logger != NULL) 
        {
            m_logger->log("on_state_update");
        }
    }
    /*! 
     *
     */
    ::RTC::ReturnCode_t on_rate_changed(::RTC::ExecutionContextHandle_t exec_handle)
    {
        if (m_logger != NULL) 
        {
            m_logger->log("on_rate_changed");
        }
    }

    /*! 
     *
     */
    ::RTC::ReturnCode_t initialize()
    {
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
    bool is_alive(const ::RTC::ExecutionContext* exec_context)
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
    ::RTC::ExecutionContextHandle_t attach_context(const ::RTC::ExecutionContext* exec_context)
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
    ::RTC::ExecutionContextHandle_t get_context_handle(const ::RTC::ExecutionContext* cxt)
    {
    }


  };

  class DataFlowComponentProxyTests
   : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(DataFlowComponentProxyTests);
    CPPUNIT_TEST_SUITE_END();
  
  private:
    CORBA::ORB_ptr m_pORB;
    PortableServer::POA_ptr m_pPOA;
  
  public:
  
    /*!
     * @brief Constructor
     */
    DataFlowComponentProxyTests()
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
    ~DataFlowComponentProxyTests()
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
  
    /* test case */
    void test_case0()
    {
    }
  };
}; // namespace DataFlowComponentProxy

/*
 * Register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(DataFlowComponentProxy::DataFlowComponentProxyTests);

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
#endif // DataFlowComponentProxy_cpp
