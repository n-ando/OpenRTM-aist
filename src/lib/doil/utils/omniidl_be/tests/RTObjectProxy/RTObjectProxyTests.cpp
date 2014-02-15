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
#include <queue>
#include <idl/SDOPackageSkel.h>
#include <idl/RTCSkel.h>
#include <RTObjectProxy.h>
#include <rtm/NVUtil.h>

#include <ISDOService.h>
#include <ISDOSystemElement.h>
#include <IComponentAction.h>
#include <IExecutionContext.h>
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
    int push(std::string& str)
    {
        m_q.push(str);
        return m_q.size();
    }
    int push(const char* str)
    {
        m_q.push(str);
        return m_q.size();
    }
    std::string pop()
    {
        std::string str("");
        if (m_q.empty()) return str;

        str = m_q.front();
        m_q.pop();
        return str;
    }
    int size() { return m_q.size(); }
		
  private:
    std::vector<std::string> m_log;
    std::queue<std::string> m_q;
  };

  class ExecutionContextMock
   : public virtual ::POA_RTC::ExecutionContext,
     public virtual ::doil::CORBA::CORBAServantBase
  {
  public:
    ExecutionContextMock(doil::ImplBase* impl)
    : ::doil::CORBA::CORBAServantBase(impl), m_impl(NULL)
    {
      m_impl = dynamic_cast< ::RTC::Local::IExecutionContext* >(impl);
    }
    virtual ~ExecutionContextMock()
    {
    }

    virtual ::CORBA::Boolean is_running()
    {
        return true;
    }
    virtual ::RTC::ReturnCode_t start()
    {
        return ::RTC::RTC_OK;
    }
    virtual ::RTC::ReturnCode_t stop()
    {
        return ::RTC::RTC_OK;
    }
    virtual ::CORBA::Double get_rate()
    {
    }
    virtual ::RTC::ReturnCode_t set_rate(::CORBA::Double rate)
    {
        return ::RTC::RTC_OK;
    }
    virtual ::RTC::ReturnCode_t add_component(::RTC::LightweightRTObject_ptr comp)
    {
        return ::RTC::RTC_OK;
    }
    virtual ::RTC::ReturnCode_t remove_component(::RTC::LightweightRTObject_ptr comp)
    {
        return ::RTC::RTC_OK;
    }
    virtual ::RTC::ReturnCode_t activate_component(::RTC::LightweightRTObject_ptr comp)
    {
        return ::RTC::RTC_OK;
    }
    virtual ::RTC::ReturnCode_t deactivate_component(::RTC::LightweightRTObject_ptr comp)
    {
        return ::RTC::RTC_OK;
    }
    virtual ::RTC::ReturnCode_t reset_component(::RTC::LightweightRTObject_ptr comp)
    {
        return ::RTC::RTC_OK;
    }
    virtual ::RTC::LifeCycleState get_component_state(::RTC::LightweightRTObject_ptr comp)
    {
    }
    virtual ::RTC::ExecutionKind get_kind()
    {
    }

  private:
    ::RTC::Local::IExecutionContext* m_impl;
  };
  /*!
   * 
   * 
   *
   */
  class ExecutionContextImpl
   : public virtual doil::ImplBase,
     public virtual RTC::Local::IComponentAction,
     public virtual RTC::Local::IExecutionContext
  {
  public:
    ExecutionContextImpl()
    {
    } 
    ExecutionContextImpl(Logger& aLogger)
    {
    } 

    virtual ~ExecutionContextImpl()
    {
    } 

    virtual bool is_running()
      throw ()
      {
        return true;
      }

    virtual ::RTC::Local::ReturnCode_t start()
      throw ()
      {
        return RTC::Local::RTC_OK;
      }

    virtual ::RTC::Local::ReturnCode_t stop()
      throw ()
      {
        return RTC::Local::RTC_OK;
      }

    virtual double get_rate()
      throw ()
      {
        return 0.0;
      }

    virtual ::RTC::Local::ReturnCode_t set_rate(double rate)
      throw ()
      {
        return RTC::Local::RTC_OK;
      }

    virtual ::RTC::Local::ReturnCode_t add_component(const ::RTC::Local::ILightweightRTObject* comp)
      throw ()
      {
        return RTC::Local::RTC_OK;
      }

    virtual ::RTC::Local::ReturnCode_t remove_component(const ::RTC::Local::ILightweightRTObject* comp)
      throw ()
      {
        return RTC::Local::RTC_OK;
      }

    virtual ::RTC::Local::ReturnCode_t activate_component(const ::RTC::Local::ILightweightRTObject* comp)
      throw ()
      {
        return RTC::Local::RTC_OK;
      }

    virtual ::RTC::Local::ReturnCode_t deactivate_component(const ::RTC::Local::ILightweightRTObject* comp)
      throw ()
      {
        return RTC::Local::RTC_OK;
      }

    virtual ::RTC::Local::ReturnCode_t reset_component(const ::RTC::Local::ILightweightRTObject* comp)
      throw ()
      {
        return RTC::Local::RTC_OK;
      }

    virtual ::RTC::Local::LifeCycleState get_component_state(const ::RTC::Local::ILightweightRTObject* comp)
      throw ()
      {
      }

    virtual ::RTC::Local::ExecutionKind get_kind()
      throw ()
      {
      }

    //
    virtual ::RTC::Local::ReturnCode_t on_initialize()
      throw ()
      {
        return RTC::Local::RTC_OK;
      }

    virtual ::RTC::Local::ReturnCode_t on_finalize()
      throw ()
      {
        return RTC::Local::RTC_OK;
      }

    virtual ::RTC::Local::ReturnCode_t on_startup(::RTC::Local::ExecutionContextHandle_t exec_handle)
      throw ()
      {
        return RTC::Local::RTC_OK;
      }

    virtual ::RTC::Local::ReturnCode_t on_shutdown(::RTC::Local::ExecutionContextHandle_t exec_handle)
      throw ()
      {
        return RTC::Local::RTC_OK;
      }

    virtual ::RTC::Local::ReturnCode_t on_activated(::RTC::Local::ExecutionContextHandle_t exec_handle)
      throw ()
      {
        return RTC::Local::RTC_OK;
      }

    virtual ::RTC::Local::ReturnCode_t on_deactivated(::RTC::Local::ExecutionContextHandle_t exec_handle)
      throw ()
      {
        return RTC::Local::RTC_OK;
      }

    virtual ::RTC::Local::ReturnCode_t on_aborting(::RTC::Local::ExecutionContextHandle_t exec_handle)
      throw ()
      {
        return RTC::Local::RTC_OK;
      }

    virtual ::RTC::Local::ReturnCode_t on_error(::RTC::Local::ExecutionContextHandle_t exec_handle)
      throw ()
      {
        return RTC::Local::RTC_OK;
      }

    virtual ::RTC::Local::ReturnCode_t on_reset(::RTC::Local::ExecutionContextHandle_t exec_handle)
      throw ()
      {
        return RTC::Local::RTC_OK;
      }

    const char* id() { return "ExecutionContext"; }
    const char* name() { return "ExecutionContext"; }
    void incRef() { refcount++; }
    void decRef() { refcount--; }
  private:
    static int count;
    char m_name[32];
    int refcount;
    Logger *m_logger;
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
        if (m_logger != NULL)
          { 
            m_logger->push("get_component_profile");
          }
        ::RTC::ComponentProfile_var prof;
        prof = new ::RTC::ComponentProfile();
        return prof._retn();
     }
    /*! 
     *
     */
     ::RTC::PortServiceList* get_ports()
     {
        if (m_logger != NULL)
          { 
            m_logger->push("get_ports");
          }
        ::RTC::PortServiceList_var ports;
        ports = new ::RTC::PortServiceList();
        return ports._retn();
     }
//
//
//

    /*! 
     *
     */
    ::RTC::ReturnCode_t on_initialize()
    {
        if (m_logger != NULL) 
          {
            m_logger->push("on_initialize");
          }
        return RTC::RTC_OK;
    }
    /*! 
     *
     */
    ::RTC::ReturnCode_t on_finalize()
    {
        if (m_logger != NULL) 
          {
            m_logger->push("on_finalize");
          }
        return RTC::RTC_OK;
    }
    /*! 
     *
     */
    ::RTC::ReturnCode_t on_startup(::RTC::ExecutionContextHandle_t exec_handle)
    {
        if (m_logger != NULL) 
          {
            m_logger->push("on_startup");
          }
        return RTC::RTC_OK;
    }
    /*! 
     *
     */
    ::RTC::ReturnCode_t on_shutdown(::RTC::ExecutionContextHandle_t exec_handle)
    {
        if (m_logger != NULL) 
          {
            m_logger->push("on_shutdown");
          }
        return RTC::RTC_OK;
    }
    /*! 
     *
     */
    ::RTC::ReturnCode_t on_activated(::RTC::ExecutionContextHandle_t exec_handle)
    {
        if (m_logger != NULL) 
          {
            m_logger->push("on_activated");
          }
        return RTC::RTC_OK;
    }
    /*! 
     *
     */
    ::RTC::ReturnCode_t on_deactivated(::RTC::ExecutionContextHandle_t exec_handle)
    {
        if (m_logger != NULL) 
          {
            m_logger->push("on_deactivated");
          }
        return RTC::RTC_OK;
    }
    /*! 
     *
     */
    ::RTC::ReturnCode_t on_aborting(::RTC::ExecutionContextHandle_t exec_handle)
    {
        if (m_logger != NULL) 
          {
            m_logger->push("on_aborting");
          }
        return RTC::RTC_OK;
    }
    /*! 
     *
     */
    ::RTC::ReturnCode_t on_error(::RTC::ExecutionContextHandle_t exec_handle)
    {
        if (m_logger != NULL) 
          {
            m_logger->push("on_error");
          }
        return RTC::RTC_OK;
    }
    /*! 
     *
     */
    ::RTC::ReturnCode_t on_reset(::RTC::ExecutionContextHandle_t exec_handle)
    {
        if (m_logger != NULL) 
          {
            m_logger->push("on_reset");
          }
        return RTC::RTC_OK;
    }

//
//
//

    /*! 
     *
     */
    ::RTC::ReturnCode_t initialize()
    {
        if (m_logger != NULL) 
          {
            m_logger->push("initialize");
          }
        return RTC::RTC_OK;
    }
    /*! 
     *
     */
    ::RTC::ReturnCode_t finalize()
    {
        if (m_logger != NULL) 
          {
            m_logger->push("finalize");
          }
        return RTC::RTC_OK;
    }
    /*! 
     *
     */
    ::CORBA::Boolean is_alive(::RTC::ExecutionContext_ptr exec_context)
    {
        if (m_logger != NULL) 
          {
            m_logger->push("is_alive");
          }
        return true;
    }
    /*! 
     *
     */
    ::RTC::ReturnCode_t exit()
    {
        if (m_logger != NULL) 
          {
            m_logger->push("exit");
          }
        return RTC::RTC_OK;
    }
    /*! 
     *
     */
    ::RTC::ExecutionContextHandle_t attach_context(::RTC::ExecutionContext_ptr exec_context)
    {
        if (m_logger != NULL) 
          {
            m_logger->push("attach_context");
          }
        ::RTC::ExecutionContextHandle_t ret;
        return ret;
    }
    /*! 
     *
     */
    ::RTC::ReturnCode_t detach_context(::RTC::ExecutionContextHandle_t exec_handle)
    {
        if (m_logger != NULL) 
          {
            m_logger->push("detach_context");
          }
        return RTC::RTC_OK;
    }
    /*! 
     *
     */
    ::RTC::ExecutionContext_ptr get_context(::RTC::ExecutionContextHandle_t exec_handle)
    {
        if (m_logger != NULL) 
          {
            m_logger->push("get_context");
          }
        ::RTC::ExecutionContext_var ret;
        return ret._retn();
    }
    /*! 
     *
     */
    ::RTC::ExecutionContextList* get_owned_contexts()
    {
        if (m_logger != NULL) 
          {
            m_logger->push("get_owned_contexts");
          }
	::RTC::ExecutionContextList_var ret;
	ret = new ::RTC::ExecutionContextList();
	return ret._retn();
    }
    /*! 
     *
     */
    ::RTC::ExecutionContextList* get_participating_contexts()
    {
        if (m_logger != NULL) 
          {
            m_logger->push("get_participating_contexts");
          }
	::RTC::ExecutionContextList_var ret;
	ret = new ::RTC::ExecutionContextList();
	return ret._retn();
    }
    /*! 
     *
     */
    ::RTC::ExecutionContextHandle_t get_context_handle(::RTC::ExecutionContext_ptr cxt)
    {
        if (m_logger != NULL) 
          {
            m_logger->push("get_context_handle");
          }
        ::RTC::ExecutionContextHandle_t ret;
        return ret;
    }

//
//
//
    /*! 
     *
     */
    ::SDOPackage::OrganizationList* get_owned_organizations()
    {
        if (m_logger != NULL) 
          {
            m_logger->push("get_owned_organizations");
          }
	::SDOPackage::OrganizationList_var ret;
	ret = new ::SDOPackage::OrganizationList();
	return ret._retn();
    }

//
//
//

    /*! 
     *
     */
    char* get_sdo_id()
    {
        char m_str[] = "bar";
        char *ret = m_str;
        if (m_logger != NULL) 
          {
            m_logger->push("get_sdo_id");
          }
        return ret;
    }
    /*! 
     *
     */
    char* get_sdo_type()
    {
        char str[] = "bar";
        char *ret = str;
        if (m_logger != NULL) 
          {
            m_logger->push("get_sdo_type");
          }
        return ret;
    }
    /*! 
     *
     */
    ::SDOPackage::DeviceProfile* get_device_profile()
    {
        if (m_logger != NULL) 
          {
            m_logger->push("get_device_profile");
          }
	::SDOPackage::DeviceProfile_var ret;
	ret = new ::SDOPackage::DeviceProfile();
	return ret._retn();
    }
    /*! 
     *
     */
    ::SDOPackage::ServiceProfileList* get_service_profiles()
    {
        if (m_logger != NULL) 
          {
            m_logger->push("get_service_profiles");
          }
	::SDOPackage::ServiceProfileList_var ret;
	ret = new ::SDOPackage::ServiceProfileList();
	return ret._retn();
    }
    /*! 
     *
     */
    ::SDOPackage::ServiceProfile* get_service_profile(const char* id)
    {
        if (m_logger != NULL) 
          {
            m_logger->push("get_service_profile");
          }
	::SDOPackage::ServiceProfile_var ret;
	ret = new ::SDOPackage::ServiceProfile();
	return ret._retn();
    }
    /*! 
     *
     */
    ::SDOPackage::SDOService_ptr get_sdo_service(const char* id)
    {
        if (m_logger != NULL) 
          {
            m_logger->push("get_sdo_service");
          }
	::SDOPackage::SDOService_var ret;
	//ret = new ::SDOPackage::SDOService();
	return ret._retn();
    }
    /*! 
     *
     */
    ::SDOPackage::Configuration_ptr get_configuration()
    {
        if (m_logger != NULL) 
          {
            m_logger->push("get_configuration");
          }
	::SDOPackage::Configuration_var ret;
	//ret = new ::SDOPackage::Configuration();
	return ret._retn();
    }
    /*! 
     *
     */
    ::SDOPackage::Monitoring_ptr get_monitoring()
    {
        if (m_logger != NULL) 
          {
            m_logger->push("get_monitoring");
          }
	::SDOPackage::Monitoring_var ret;
	//ret = new ::SDOPackage::Monitoring();
	return ret._retn();
    }
    /*! 
     *
     */
    ::SDOPackage::OrganizationList* get_organizations()
    {
        if (m_logger != NULL) 
          {
            m_logger->push("get_organizations");
          }
	::SDOPackage::OrganizationList_var ret;
	ret = new ::SDOPackage::OrganizationList();
	return ret._retn();
    }
    /*! 
     *
     */
    ::SDOPackage::NVList* get_status_list()
    {
        if (m_logger != NULL) 
          {
            m_logger->push("get_status_list");
          }
	::SDOPackage::NVList_var ret;
	ret = new ::SDOPackage::NVList();
	return ret._retn();
    }
    /*! 
     *
     */
    ::CORBA::Any* get_status(const char* nme)
    {
        if (m_logger != NULL) 
          {
            m_logger->push("get_status");
          }
	::CORBA::Any_var ret;
	ret = new ::CORBA::Any();
	return ret._retn();
    }

//
//
//
    /*! 
     *
    */
/*.
    ::SDOPackage::ServiceProfile* get_service_profile(char* id)
    {
    }
*/
  private:
    Logger* m_logger;

  };

  class RTObjectProxyTests
   : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(RTObjectProxyTests);
    CPPUNIT_TEST(test_get_component_profile);
    CPPUNIT_TEST(test_get_ports);
    CPPUNIT_TEST(test_on_initialize);
    CPPUNIT_TEST(test_on_finalize);
    CPPUNIT_TEST(test_on_startup);
    CPPUNIT_TEST(test_on_shutdown);
    CPPUNIT_TEST(test_on_activated);
    CPPUNIT_TEST(test_on_deactivated);
    CPPUNIT_TEST(test_on_aborting);
    CPPUNIT_TEST(test_on_error);
    CPPUNIT_TEST(test_on_reset);

    CPPUNIT_TEST(test_initialize);
    CPPUNIT_TEST(test_finalize);
    CPPUNIT_TEST(test_is_alive);
    CPPUNIT_TEST(test_exit);
    CPPUNIT_TEST(test_attach_context);
    CPPUNIT_TEST(test_detach_context);
    CPPUNIT_TEST(test_get_context);
    CPPUNIT_TEST(test_get_owned_contexts);
    CPPUNIT_TEST(test_get_participating_contexts);
    CPPUNIT_TEST(test_get_context_handle);

    CPPUNIT_TEST(test_get_owned_organizations);

    CPPUNIT_TEST(test_get_sdo_id);
    CPPUNIT_TEST(test_get_sdo_type);
    CPPUNIT_TEST(test_get_device_profile);
    CPPUNIT_TEST(test_get_service_profiles);
    CPPUNIT_TEST(test_get_service_profile);
    CPPUNIT_TEST(test_get_sdo_service);
    CPPUNIT_TEST(test_get_configuration);
    CPPUNIT_TEST(test_get_monitoring);
    CPPUNIT_TEST(test_get_organizations);
    CPPUNIT_TEST(test_get_status_list);
    CPPUNIT_TEST(test_get_status);


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

      std::string str("get_component_profile");
      //CPPUNIT_ASSERT_EQUAL(0, logger.pop("get_component_profile"));
      ::RTC::Local::ComponentProfile local_ret;
      local_ret = ap->get_component_profile();
      //CPPUNIT_ASSERT_EQUAL(1, logger.pop("get_component_profile"));
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not method name", logger.pop(), str);
      //CPPUNIT_ASSERT_EQUAL_MESSAGE("not true", RTC::Local::RTC_OK, result);

      

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
      //doil::CORBA::CORBAManager& 
      //                      mgr(doil::CORBA::CORBAManager::instance());
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

      std::string str("get_ports");
      //CPPUNIT_ASSERT_EQUAL(0, logger.pop("get_ports"));
      ::RTC::Local::PortServiceList local_ret;
      local_ret = ap->get_ports();
      //CPPUNIT_ASSERT_EQUAL(1, logger.pop("get_ports"));
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not method name", logger.pop(), str);
      //CPPUNIT_ASSERT_EQUAL_MESSAGE("not true", RTC::Local::RTC_OK, result);

      delete ap;
      CORBA::release(ref);
    }
    /*! 
     *
     *
     *
     */
    void test_on_initialize()
    {
      //doil::CORBA::CORBAManager& 
      //                      mgr(doil::CORBA::CORBAManager::instance());
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

      std::string str("on_initialize");
      //CPPUNIT_ASSERT_EQUAL(0, logger.pop("get_ports"));
      ::RTC::Local::ReturnCode_t result;
      result = ap->on_initialize();
      //CPPUNIT_ASSERT_EQUAL(1, logger.pop("get_ports"));
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not method name", logger.pop(), str);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not true", RTC::Local::RTC_OK, result);

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
      //doil::CORBA::CORBAManager& 
      //                      mgr(doil::CORBA::CORBAManager::instance());
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
      std::string str("on_finalize");

      ::RTC::Local::ReturnCode_t result;
      result = ap->on_finalize();
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not method name", logger.pop(), str);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not true", RTC::Local::RTC_OK, result);

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
      //doil::CORBA::CORBAManager& 
      //                      mgr(doil::CORBA::CORBAManager::instance());
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
      std::string str("on_startup");

      ::RTC::Local::ReturnCode_t result;
      ::RTC::Local::ExecutionContextHandle_t exec_handle;
      result = ap->on_startup(exec_handle);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not method name", logger.pop(), str);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not true", RTC::Local::RTC_OK, result);

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
      //doil::CORBA::CORBAManager& 
      //                      mgr(doil::CORBA::CORBAManager::instance());
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
      std::string str("on_shutdown");

      ::RTC::Local::ReturnCode_t result;
      ::RTC::Local::ExecutionContextHandle_t exec_handle;
      result = ap->on_shutdown(exec_handle);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not method name", logger.pop(), str);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not true", RTC::Local::RTC_OK, result);

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
      //doil::CORBA::CORBAManager& 
      //                      mgr(doil::CORBA::CORBAManager::instance());
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
      std::string str("on_activated");

      ::RTC::Local::ExecutionContextHandle_t exec_handle;
      ::RTC::Local::ReturnCode_t result;
      result = ap->on_activated(exec_handle);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not method name", logger.pop(), str);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not true", RTC::Local::RTC_OK, result);

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
      //doil::CORBA::CORBAManager& 
      //                      mgr(doil::CORBA::CORBAManager::instance());
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
      std::string str("on_deactivated");

      ::RTC::Local::ExecutionContextHandle_t exec_handle;
      ::RTC::Local::ReturnCode_t result;
      result = ap->on_deactivated(exec_handle);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not method name", logger.pop(), str);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not true", RTC::Local::RTC_OK, result);

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
      //doil::CORBA::CORBAManager& 
      //                      mgr(doil::CORBA::CORBAManager::instance());
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
      std::string str("on_aborting");

      ::RTC::Local::ExecutionContextHandle_t exec_handle;
      ::RTC::Local::ReturnCode_t result;
      result = ap->on_aborting(exec_handle);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not method name", logger.pop(), str);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not true", RTC::Local::RTC_OK, result);

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
      //doil::CORBA::CORBAManager& 
      //                      mgr(doil::CORBA::CORBAManager::instance());
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
      std::string str("on_error");

      ::RTC::Local::ReturnCode_t result;
      ::RTC::Local::ExecutionContextHandle_t exec_handle;
      result = ap->on_error(exec_handle);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not method name", logger.pop(), str);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not true", RTC::Local::RTC_OK, result);

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
      //doil::CORBA::CORBAManager& 
      //                      mgr(doil::CORBA::CORBAManager::instance());
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
      std::string str("on_reset");

      ::RTC::Local::ExecutionContextHandle_t exec_handle;
      ::RTC::Local::ReturnCode_t result;
      result = ap->on_reset(exec_handle);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not method name", logger.pop(), str);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not true", RTC::Local::RTC_OK, result);

      delete ap;
      CORBA::release(ref);
    }

    /*! 
     *
     *
     *
     */
    void test_initialize()
    {
      //doil::CORBA::CORBAManager& 
      //                      mgr(doil::CORBA::CORBAManager::instance());
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
      std::string str("initialize");

      ::RTC::Local::ReturnCode_t result;
      result = ap->initialize();
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not method name", logger.pop(), str);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not true", RTC::Local::RTC_OK, result);

      delete ap;
      CORBA::release(ref);
    }
    /*! 
     *
     *
     *
     */
    void test_finalize()
    {
      //doil::CORBA::CORBAManager& 
      //                      mgr(doil::CORBA::CORBAManager::instance());
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
      std::string str("finalize");

      ::RTC::Local::ReturnCode_t result;
      result = ap->finalize();
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not method name", logger.pop(), str);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not true", RTC::Local::RTC_OK, result);

      delete ap;
      CORBA::release(ref);
    }
    /*! 
     *
     *
     *
     */
    void test_is_alive()
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

      ExecutionContextImpl exec;
      mgr.registerFactory(exec.id(), 
                          doil::New<ExecutionContextMock>,
                          doil::Delete<ExecutionContextMock>);
      mgr.activateObject(&exec);


      std::string str("is_alive");

      ::RTC::Local::IExecutionContext* exec_context = &exec;
      bool result;
      result = ap->is_alive(exec_context);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not method name", logger.pop(), str);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not true", true, result);

      delete ap;
      CORBA::release(ref);
    }
    /*! 
     *
     *
     *
     */
    void test_exit()
    {
      //doil::CORBA::CORBAManager& 
      //                      mgr(doil::CORBA::CORBAManager::instance());
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
      std::string str("exit");

      ::RTC::Local::ReturnCode_t result;
      result = ap->exit();
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not method name", logger.pop(), str);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not true", RTC::Local::RTC_OK, result);

      delete ap;
      CORBA::release(ref);
    }
    /*! 
     *
     *
     *
     */
    void test_attach_context()
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

      ExecutionContextImpl exec;
      mgr.registerFactory(exec.id(), 
                          doil::New<ExecutionContextMock>,
                          doil::Delete<ExecutionContextMock>);
      mgr.activateObject(&exec);

      std::string str("attach_context");

      ::RTC::Local::IExecutionContext* exec_context = &exec;
      ::RTC::ExecutionContextHandle_t result;
      result = ap->attach_context(exec_context);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not method name", logger.pop(), str);
      //CPPUNIT_ASSERT_EQUAL_MESSAGE("not true", true, result);

      delete ap;
      CORBA::release(ref);
    }
    /*! 
     *
     *
     *
     */
    void test_detach_context()
    {
      //doil::CORBA::CORBAManager& 
      //                      mgr(doil::CORBA::CORBAManager::instance());
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

      std::string str("detach_context");

      ::RTC::Local::ReturnCode_t result;
      result = ap->detach_context(0);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not method name", logger.pop(), str);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not true", RTC::Local::RTC_OK, result);

      delete ap;
      CORBA::release(ref);
    }
    /*! 
     *
     *
     *
     */
    void test_get_context()
    {
      //doil::CORBA::CORBAManager& 
      //                      mgr(doil::CORBA::CORBAManager::instance());
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

      std::string str("get_context");

      ::RTC::Local::IExecutionContext* result;
      result = ap->get_context(0);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not method name", logger.pop(), str);
      //CPPUNIT_ASSERT_EQUAL_MESSAGE("not true", RTC::Local::RTC_OK, result);

      delete ap;
      CORBA::release(ref);
    }
    /*! 
     *
     *
     *
     */
    void test_get_owned_contexts()
    {
      //doil::CORBA::CORBAManager& 
      //                      mgr(doil::CORBA::CORBAManager::instance());
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

      std::string str("get_owned_contexts");

      ::RTC::Local::ExecutionContextList result;
      result = ap->get_owned_contexts();
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not method name", logger.pop(), str);
      //CPPUNIT_ASSERT_EQUAL_MESSAGE("not true", RTC::Local::RTC_OK, result);

      delete ap;
      CORBA::release(ref);
    }
    /*! 
     *
     *
     *
     */
    void test_get_participating_contexts()
    {
      //doil::CORBA::CORBAManager& 
      //                      mgr(doil::CORBA::CORBAManager::instance());
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

      std::string str("get_participating_contexts");

      ::RTC::Local::ExecutionContextList result;
      result = ap->get_participating_contexts();
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not method name", logger.pop(), str);
      //CPPUNIT_ASSERT_EQUAL_MESSAGE("not true", RTC::Local::RTC_OK, result);

      delete ap;
      CORBA::release(ref);
    }
    /*! 
     *
     *
     *
     */
    void test_get_context_handle()
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

      ExecutionContextImpl exec;
      mgr.registerFactory(exec.id(), 
                          doil::New<ExecutionContextMock>,
                          doil::Delete<ExecutionContextMock>);
      mgr.activateObject(&exec);

      std::string str("get_context_handle");

      ::RTC::Local::IExecutionContext* exec_context = &exec;
      ::RTC::ExecutionContextHandle_t result;
      result = ap->get_context_handle(exec_context);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not method name", logger.pop(), str);
      //CPPUNIT_ASSERT_EQUAL_MESSAGE("not true", true, result);

      delete ap;
      CORBA::release(ref);
    }

    /*! 
     *
     *
     *
     */
    void test_get_owned_organizations()
    {
      //doil::CORBA::CORBAManager& 
      //                      mgr(doil::CORBA::CORBAManager::instance());
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


      std::string str("get_owned_organizations");

      ::SDOPackage::Local::OrganizationList result;
      result = ap->get_owned_organizations();
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not method name", logger.pop(), str);
      //CPPUNIT_ASSERT_EQUAL_MESSAGE("not true", true, result);

      delete ap;
      CORBA::release(ref);
    }

    /*! 
     *
     *
     *
     */
    void test_get_sdo_id()
    {
      //doil::CORBA::CORBAManager& 
      //                      mgr(doil::CORBA::CORBAManager::instance());
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


      std::string str("get_sdo_id");
      std::string str2("bar");

      std::string result;
      //result = ap->get_sdo_id();
      //ap->get_sdo_id();
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not method name", logger.pop(), str);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not true", str2, result);

      delete ap;
      CORBA::release(ref);
    }
    /*! 
     *
     *
     *
     */
    void test_get_sdo_type()
    {
      //doil::CORBA::CORBAManager& 
      //                      mgr(doil::CORBA::CORBAManager::instance());
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


      std::string str("get_sdo_type");
      std::string str2("bar");

      std::string result;
      //result = ap->get_sdo_type();
      //ap->get_sdo_type();
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not method name", logger.pop(), str);
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not true", str2, result);

      delete ap;
      CORBA::release(ref);
    }
    /*! 
     *
     *
     *
     */
    void test_get_device_profile()
    {
      //doil::CORBA::CORBAManager& 
      //                      mgr(doil::CORBA::CORBAManager::instance());
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


      std::string str("get_device_profile");

      ::SDOPackage::Local::DeviceProfile result;
      result = ap->get_device_profile();
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not method name", logger.pop(), str);
      //CPPUNIT_ASSERT_EQUAL_MESSAGE("not true", str2, result);

      delete ap;
      CORBA::release(ref);
    }
    /*! 
     *
     *
     *
     */
    void test_get_service_profiles()
    {
      //doil::CORBA::CORBAManager& 
      //                      mgr(doil::CORBA::CORBAManager::instance());
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


      std::string str("get_service_profiles");

      ::SDOPackage::Local::ServiceProfileList result;
      result = ap->get_service_profiles();
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not method name", logger.pop(), str);
      //CPPUNIT_ASSERT_EQUAL_MESSAGE("not true", str2, result);

      delete ap;
      CORBA::release(ref);
    }
    /*! 
     *
     *
     *
     */
    void test_get_service_profile()
    {
      //doil::CORBA::CORBAManager& 
      //                      mgr(doil::CORBA::CORBAManager::instance());
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


      std::string str("get_service_profile");

      ::SDOPackage::Local::ServiceProfile result;
      result = ap->get_service_profile("foo");
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not method name", logger.pop(), str);
      //CPPUNIT_ASSERT_EQUAL_MESSAGE("not true", str2, result);

      delete ap;
      CORBA::release(ref);
    }
    /*! 
     *
     *
     *
     */
    void test_get_sdo_service()
    {
      //doil::CORBA::CORBAManager& 
      //                      mgr(doil::CORBA::CORBAManager::instance());
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


      std::string str("get_sdo_service");

      ::SDOPackage::Local::ISDOService * result;
      result = ap->get_sdo_service("foo");
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not method name", logger.pop(), str);
      //CPPUNIT_ASSERT_EQUAL_MESSAGE("not true", str2, result);

      delete ap;
      CORBA::release(ref);
    }
    /*! 
     *
     *
     *
     */
    void test_get_configuration()
    {
      //doil::CORBA::CORBAManager& 
      //                      mgr(doil::CORBA::CORBAManager::instance());
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


      std::string str("get_configuration");

      ::SDOPackage::Local::IConfiguration* result;
      result = ap->get_configuration();
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not method name", logger.pop(), str);
      //CPPUNIT_ASSERT_EQUAL_MESSAGE("not true", str2, result);

      delete ap;
      CORBA::release(ref);
    }
    /*! 
     *
     *
     *
     */
    void test_get_monitoring()
    {
      //doil::CORBA::CORBAManager& 
      //                      mgr(doil::CORBA::CORBAManager::instance());
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


      std::string str("get_monitoring");

      ::SDOPackage::Local::IMonitoring* result;
      result = ap->get_monitoring();
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not method name", logger.pop(), str);
      //CPPUNIT_ASSERT_EQUAL_MESSAGE("not true", str2, result);

      delete ap;
      CORBA::release(ref);
    }
    /*! 
     *
     *
     *
     */
    void test_get_organizations()
    {
      //doil::CORBA::CORBAManager& 
      //                      mgr(doil::CORBA::CORBAManager::instance());
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


      std::string str("get_organizations");

      ::SDOPackage::Local::OrganizationList result;
      result = ap->get_organizations();
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not method name", logger.pop(), str);
      //CPPUNIT_ASSERT_EQUAL_MESSAGE("not true", str2, result);

      delete ap;
      CORBA::release(ref);
    }
    /*! 
     *
     *
     *
     */
    void test_get_status_list()
    {
      //doil::CORBA::CORBAManager& 
      //                      mgr(doil::CORBA::CORBAManager::instance());
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


      std::string str("get_status_list");

      ::SDOPackage::Local::NVList result;
      result = ap->get_status_list();
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not method name", logger.pop(), str);
      //CPPUNIT_ASSERT_EQUAL_MESSAGE("not true", str2, result);

      delete ap;
      CORBA::release(ref);
    }
    /*! 
     *
     *
     *
     */
    void test_get_status()
    {
      //doil::CORBA::CORBAManager& 
      //                      mgr(doil::CORBA::CORBAManager::instance());
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


      std::string str("get_status");

      //::SDOPackage::Local::NVList result;
      ap->get_status("foo");
      CPPUNIT_ASSERT_EQUAL_MESSAGE("not method name", logger.pop(), str);
      //CPPUNIT_ASSERT_EQUAL_MESSAGE("not true", str2, result);

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
