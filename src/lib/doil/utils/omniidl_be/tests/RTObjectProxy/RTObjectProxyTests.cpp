// -*- C++ -*-
/*!
 * @file   RTObjectProxyTests.cpp
 * @brief  RTObjectProxy test class
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

#ifndef RTObjectProxy_cpp
#define RTObjectProxy_cpp

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>
#include <string>
#include <iostream>
#include <idl/SDOPackageSkel.h>
#include <idl/RTCSkel.h>
#include <RTObjectProxy.h>
#include <rtm/NVUtil.h>
#include <ISDOService.h>
#include <ISDOSystemElement.h>
#include <IOrganization.h>
#include <doil/corba/CORBAManager.h>


/*!
 * @class RTObjectProxyTests class
 * @brief RTObjectProxy test
 */
namespace RTObjectProxy
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
  class RTObjectMock
    : public virtual ::POA_RTC::RTObject
  {
  protected:
      ::std::vector<std::string> m_log;
  private:
  public :
      RTObjectMock(){}
      virtual ~RTObjectMock()
      {
      }

      void setLogger(Logger* logger)
      {
        m_logger = logger;
      }

    /*! 
     *
     */
     ::RTC::ComponentProfile* get_component_profile()
     {
        if (m_logger != NULL) m_logger->log("get_component_profile");
     }
    /*! 
     *
     */
     ::RTC::PortServiceList* get_ports()
     {
        if (m_logger != NULL) m_logger->log("get_ports");
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
    ::SDOPackage::OrganizationList* get_owned_organizations()
    {
    }
    /*! 
     *
     */
    char* get_sdo_id()
    {
    }
    /*! 
     *
     */
    char* get_sdo_type()
    {
    }
    /*! 
     *
     */
    ::SDOPackage::DeviceProfile* get_device_profile()
    {
    }
    /*! 
     *
     */
    ::SDOPackage::ServiceProfileList* get_service_profiles()
    {
    }
    /*! 
     *
     */
    ::SDOPackage::ServiceProfile* get_service_profile(const char* id)
    {
    }
    /*! 
     *
     */
    ::SDOPackage::SDOService_ptr get_sdo_service(const char* id)
    {
    }
    /*! 
     *
     */
    ::SDOPackage::Configuration_ptr get_configuration()
    {
    }
    /*! 
     *
     */
    ::SDOPackage::Monitoring_ptr get_monitoring()
    {
    }
    /*! 
     *
     */
    ::SDOPackage::OrganizationList* get_organizations()
    {
    }
    /*! 
     *
     */
    ::SDOPackage::NVList* get_status_list()
    {
    }
    /*! 
     *
     */
    ::CORBA::Any* get_status(const char* nme)
    {
    }

    /*! 
     *
     */
    ::SDOPackage::ServiceProfile* get_service_profile(char* id)
    {
    }
  private:
    Logger* m_logger;

  };

  class RTObjectProxyTests
   : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(RTObjectProxyTests);
    CPPUNIT_TEST(test_get_component_profile);
    CPPUNIT_TEST(test_get_ports);
    CPPUNIT_TEST_SUITE_END();
  
  private:
    CORBA::ORB_ptr m_pORB;
    PortableServer::POA_ptr m_pPOA;
  
  public:
  
    /*!
     * @brief Constructor
     */
    RTObjectProxyTests()
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
    ~RTObjectProxyTests()
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
    void test_get_component_profile()
    {
      RTObjectMock* obj = new RTObjectMock();
      ::CORBA::Object_ptr ref = obj->_this();
      if(::CORBA::is_nil(ref))
      {
         std::cout<<"ref is nil.Abort test."<<std::endl;
         return;
      }
      ::RTC::CORBA::RTObjectProxy* ap 
                 = new ::RTC::CORBA::RTObjectProxy(ref);

      Logger logger;
      obj->setLogger(&logger);

      CPPUNIT_ASSERT_EQUAL(0, logger.countLog("get_component_profile"));
      ::RTC::Local::ComponentProfile local_ret;
      local_ret = ap->get_component_profile();
      CPPUNIT_ASSERT_EQUAL(1, logger.countLog("get_component_profile"));

      

      delete ap;
      CORBA::release(ref);
    }
    /*! 
     *
     *
     *
     */
    void test_get_ports()
    {
      doil::CORBA::CORBAManager& 
                            mgr(doil::CORBA::CORBAManager::instance());
      //std::cout <<"Manager Name==>"<< mgr.name() << std::endl;

      RTObjectMock* obj = new RTObjectMock();
      ::CORBA::Object_ptr ref = obj->_this();
      if(::CORBA::is_nil(ref))
      {
         std::cout<<"ref is nil.Abort test."<<std::endl;
         return;
      }
      
      ::RTC::CORBA::RTObjectProxy* ap 
                 = new ::RTC::CORBA::RTObjectProxy(ref);

      Logger logger;
      obj->setLogger(&logger);

      CPPUNIT_ASSERT_EQUAL(0, logger.countLog("get_ports"));
      ::RTC::Local::PortServiceList local_ret;
      local_ret = ap->get_ports();
      CPPUNIT_ASSERT_EQUAL(1, logger.countLog("get_ports"));

      delete ap;
      CORBA::release(ref);
    }
    /* test case */
    void test_case0()
    {
    }
  };
}; // namespace RTObjectProxy

/*
 * Register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(RTObjectProxy::RTObjectProxyTests);

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
#endif // RTObjectProxy_cpp
