// -*- C++ -*-
/*!
 * @file   ComponentActionProxyTests.cpp
 * @brief  ComponentActionProxy test class
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

#ifndef ComponentActionProxy_cpp
#define ComponentActionProxy_cpp

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>
#include <string>
#include <iostream>
#include <idl/SDOPackageSkel.h>
#include <idl/RTCSkel.h>
#include <ComponentActionProxy.h>
#include <rtm/NVUtil.h>
#include <ISDOService.h>
#include <ISDOSystemElement.h>
#include <IOrganization.h>
#include <doil/corba/CORBAManager.h>


/*!
 * @class ComponentActionProxyTests class
 * @brief ComponentActionProxy test
 */
namespace ComponentActionProxy
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
  class  ComponentActionMock
    : public virtual ::POA_RTC::ComponentAction
  {
  protected:
      ::std::vector<std::string> m_log;
  private:
    Logger* m_logger;
  public :
      ComponentActionMock(){}
      virtual ~ComponentActionMock()
      {
      }

      void setLogger(Logger* logger)
      {
        m_logger = logger;
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
  };

  class ComponentActionProxyTests
   : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(ComponentActionProxyTests);
    CPPUNIT_TEST(test_on_initialize);
    CPPUNIT_TEST(test_on_finalize);
    CPPUNIT_TEST(test_on_startup);
    CPPUNIT_TEST(test_on_shutdown);
    CPPUNIT_TEST(test_on_activated);
    CPPUNIT_TEST(test_on_deactivated);
    CPPUNIT_TEST(test_on_aborting);
    CPPUNIT_TEST(test_on_error);
    CPPUNIT_TEST(test_on_reset);
    CPPUNIT_TEST_SUITE_END();
  
  private:
    CORBA::ORB_ptr m_pORB;
    PortableServer::POA_ptr m_pPOA;
  
  public:
  
    /*!
     * @brief Constructor
     */
    ComponentActionProxyTests()
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
    ~ComponentActionProxyTests()
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
    void test_on_initialize()
    {
      ComponentActionMock* obj = new ComponentActionMock();
      ::CORBA::Object_ptr ref = obj->_this();
      if(::CORBA::is_nil(ref))
      {
         std::cout<<"ref is nil.Abort test."<<std::endl;
         return;
      }
      ::RTC::CORBA::ComponentActionProxy* ap 
                 = new ::RTC::CORBA::ComponentActionProxy(ref);

      Logger logger;
      obj->setLogger(&logger);

      CPPUNIT_ASSERT_EQUAL(0, logger.countLog("on_initialize"));
      const ::SDOPackage::Local::DeviceProfile porf;
      ap->on_initialize();
      CPPUNIT_ASSERT_EQUAL(1, logger.countLog("on_initialize"));

      

      delete ap;
      CORBA::release(ref);
    }
    /*! 
     *
     *
     *
     */
    void test_on_finalize()
    {

      ComponentActionMock* obj = new ComponentActionMock();
      ::CORBA::Object_ptr ref = obj->_this();
      if(::CORBA::is_nil(ref))
      {
         std::cout<<"ref is nil.Abort test."<<std::endl;
         return;
      }
      
      ::RTC::CORBA::ComponentActionProxy* ap 
                 = new ::RTC::CORBA::ComponentActionProxy(ref);

      Logger logger;
      obj->setLogger(&logger);

      CPPUNIT_ASSERT_EQUAL(0, logger.countLog("on_finalize"));
      ap->on_finalize();
      CPPUNIT_ASSERT_EQUAL(1, logger.countLog("on_finalize"));


      delete ap;
      CORBA::release(ref);
    }
    /*! 
     *
     *
     *
     */
    void test_on_startup()
    {
      doil::CORBA::CORBAManager& 
                            mgr(doil::CORBA::CORBAManager::instance());
      //std::cout <<"Manager Name==>"<< mgr.name() << std::endl;

      ComponentActionMock* obj = new ComponentActionMock();
      ::CORBA::Object_ptr ref = obj->_this();
      if(::CORBA::is_nil(ref))
      {
         std::cout<<"ref is nil.Abort test."<<std::endl;
         return;
      }
      ::RTC::CORBA::ComponentActionProxy* ap 
                 = new ::RTC::CORBA::ComponentActionProxy(ref);

      Logger logger;
      obj->setLogger(&logger);
      CPPUNIT_ASSERT_EQUAL(0, logger.countLog("on_startup"));

      ::RTC::Local::ExecutionContextHandle_t exec_handle;
      ap->on_startup(exec_handle);

      CPPUNIT_ASSERT_EQUAL(1, logger.countLog("on_startup"));

      delete ap;
      CORBA::release(ref);
    }
    /*! 
     *
     *
     *
     */
    void test_on_shutdown()
    {
      ComponentActionMock* obj = new ComponentActionMock();
      ::CORBA::Object_ptr ref = obj->_this();
      if(::CORBA::is_nil(ref))
      {
         std::cout<<"ref is nil.Abort test."<<std::endl;
         return;
      }
      ::RTC::CORBA::ComponentActionProxy* ap 
                 = new ::RTC::CORBA::ComponentActionProxy(ref);

      Logger logger;
      obj->setLogger(&logger);

      CPPUNIT_ASSERT_EQUAL(0, logger.countLog("on_shutdown"));
      ::RTC::Local::ExecutionContextHandle_t exec_handle;
      ap->on_shutdown(exec_handle);
      CPPUNIT_ASSERT_EQUAL(1, logger.countLog("on_shutdown"));

      delete ap;
      CORBA::release(ref);
    }
    /*! 
     *
     *
     *
     */
    void test_on_activated()
    {
      ComponentActionMock* obj = new ComponentActionMock();
      ::CORBA::Object_ptr ref = obj->_this();
      if(::CORBA::is_nil(ref))
      {
         std::cout<<"ref is nil.Abort test."<<std::endl;
         return;
      }
      ::RTC::CORBA::ComponentActionProxy* ap 
                 = new ::RTC::CORBA::ComponentActionProxy(ref);

      Logger logger;
      obj->setLogger(&logger);
      const ::std::string str = "test_remove_organization";

      CPPUNIT_ASSERT_EQUAL(0, logger.countLog("on_activated"));
      ::RTC::Local::ExecutionContextHandle_t exec_handle;
      ap->on_activated(exec_handle);
      CPPUNIT_ASSERT_EQUAL(1, logger.countLog("on_activated"));

      delete ap;
      CORBA::release(ref);
    }
    /*! 
     *
     *
     *
     */
    void test_on_deactivated()
    {
      ComponentActionMock* obj = new ComponentActionMock();
      ::CORBA::Object_ptr ref = obj->_this();
      if(::CORBA::is_nil(ref))
      {
         std::cout<<"ref is nil.Abort test."<<std::endl;
         return;
      }
      ::RTC::CORBA::ComponentActionProxy* ap 
                 = new ::RTC::CORBA::ComponentActionProxy(ref);

      Logger logger;
      obj->setLogger(&logger);

      ::SDOPackage::Local::ParameterList pl;
      CPPUNIT_ASSERT_EQUAL(0, 
                        logger.countLog("on_deactivated"));
      ::RTC::Local::ExecutionContextHandle_t exec_handle;
      ap->on_deactivated(exec_handle);
      CPPUNIT_ASSERT_EQUAL(1, 
                        logger.countLog("on_deactivated"));


      delete ap;
      CORBA::release(ref);
    }
    /*! 
     *
     *
     *
     */
    void test_on_aborting()
    {
      ComponentActionMock* obj = new ComponentActionMock();
      ::CORBA::Object_ptr ref = obj->_this();
      if(::CORBA::is_nil(ref))
      {
         std::cout<<"ref is nil.Abort test."<<std::endl;
         return;
      }
      ::RTC::CORBA::ComponentActionProxy* ap 
                 = new ::RTC::CORBA::ComponentActionProxy(ref);

      Logger logger;
      obj->setLogger(&logger);

      CPPUNIT_ASSERT_EQUAL(0, 
                  logger.countLog("on_aborting"));
      ::RTC::Local::ExecutionContextHandle_t exec_handle;
      ap->on_aborting(exec_handle);
      CPPUNIT_ASSERT_EQUAL(1, 
                  logger.countLog("on_aborting"));


      delete ap;
      CORBA::release(ref);
    }
    /*! 
     *
     *
     *
     */
    void test_on_error()
    {
      ComponentActionMock* obj = new ComponentActionMock();
      ::CORBA::Object_ptr ref = obj->_this();
      if(::CORBA::is_nil(ref))
      {
         std::cout<<"ref is nil.Abort test."<<std::endl;
         return;
      }
      ::RTC::CORBA::ComponentActionProxy* ap 
                 = new ::RTC::CORBA::ComponentActionProxy(ref);

      Logger logger;
      obj->setLogger(&logger);

      const ::std::string str = "test_get_configuration_parameter_value";
      ::std::string ret;
      CPPUNIT_ASSERT_EQUAL(0, 
                  logger.countLog("get_configuration_parameter_value"));
      ::RTC::Local::ExecutionContextHandle_t exec_handle;
      ap->on_error(exec_handle);
      CPPUNIT_ASSERT_EQUAL(1, 
                  logger.countLog("get_configuration_parameter_value"));

      delete ap;
      CORBA::release(ref);

    }
    /*! 
     *
     *
     *
     */
    void test_on_reset()
    {
      ComponentActionMock* obj = new ComponentActionMock();
      ::CORBA::Object_ptr ref = obj->_this();
      if(::CORBA::is_nil(ref))
      {
         std::cout<<"ref is nil.Abort test."<<std::endl;
         return;
      }
      ::RTC::CORBA::ComponentActionProxy* ap 
                 = new ::RTC::CORBA::ComponentActionProxy(ref);

      Logger logger;
      obj->setLogger(&logger);

      
      CPPUNIT_ASSERT_EQUAL(0, 
                        logger.countLog("on_reset"));
      ::RTC::Local::ExecutionContextHandle_t exec_handle;
      ap->on_reset(exec_handle);
      CPPUNIT_ASSERT_EQUAL(1, 
                        logger.countLog("on_reset"));


      delete ap;
      CORBA::release(ref);
    }
    /* test case */
    void test_case0()
    {
    }
  };
}; // namespace ComponentActionProxy

/*
 * Register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(ComponentActionProxy::ComponentActionProxyTests);

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
#endif // ComponentActionProxy_cpp
