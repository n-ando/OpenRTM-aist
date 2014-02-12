// -*- C++ -*-
/*!
 * @file   ExecutionContextServiceProxyTests.cpp
 * @brief  ExecutionContextServiceProxy test class
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

#ifndef ExecutionContextServiceProxy_cpp
#define ExecutionContextServiceProxy_cpp

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>
#include <string>
#include <iostream>
#include <idl/SDOPackageSkel.h>
#include <idl/RTCSkel.h>
#include <ExecutionContextServiceProxy.h>
#include <rtm/NVUtil.h>
#include <ISDOService.h>
#include <ISDOSystemElement.h>
#include <IOrganization.h>
#include <doil/corba/CORBAManager.h>


/*!
 * @class ExecutionContextServiceProxyTests class
 * @brief ExecutionContextServiceProxy test
 */
namespace ExecutionContextServiceProxy
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
  class ExecutionContextServiceMock
    : public virtual ::POA_RTC::ExecutionContextService
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
      ExecutionContextServiceMock(){}
      virtual ~ExecutionContextServiceMock()
      {
      }

      void setLogger(Logger* logger)
      {
        m_logger = logger;
      }

    /*! 
     *
     */
     ::RTC::ExecutionContextProfile* get_profile()
       throw (CORBA::SystemException,
             ::SDOPackage::InvalidParameter, 
             ::SDOPackage::NotAvailable, 
             ::SDOPackage::InternalError)
     {
        if (m_logger != NULL) m_logger->log("get_profile");
        return NULL;
     }
    /*! 
     *
     */
  ::CORBA::Boolean is_running()
  {
    return false;
  }
  

    /*! 
     *
     */
  ::RTC::ReturnCode_t start()
  {
    return RTC::RTC_OK;
  }
  

    /*! 
     *
     */
  ::RTC::ReturnCode_t stop()
  {
    return RTC::RTC_OK;
  }
  
  
    /*! 
     *
     */
    ::CORBA::Double get_rate()
    {
        if (m_logger != NULL)
        {
            m_logger->log("get_rate");
        }
        return (CORBA::Double)3.14159;
    }
  
  
    /*! 
     *
     */
    ::RTC::ReturnCode_t set_rate(::CORBA::Double rate)
    {
        if (m_logger != NULL)
        {
            m_logger->log("set_rate");
            ::std::ostringstream os;
            os<<rate; 
            m_logger->log(os.str());
        }

        return RTC::BAD_PARAMETER;
    }
  

    /*! 
     *
     */
  ::RTC::ReturnCode_t activate_component(::RTC::LightweightRTObject_ptr comp)
  {
    return RTC::RTC_OK;
  }
  

    /*! 
     *
     */
  ::RTC::ReturnCode_t deactivate_component(::RTC::LightweightRTObject_ptr comp)
  {
    return RTC::RTC_OK;
  }
  

    /*! 
     *
     */
  ::RTC::ReturnCode_t reset_component(::RTC::LightweightRTObject_ptr comp)
  {
    return RTC::RTC_OK;
  }
  
  
    /*! 
     *
     */
  ::RTC::LifeCycleState get_component_state(::RTC::LightweightRTObject_ptr comp)
  {
    return RTC::INACTIVE_STATE;
  }
  
  
    /*! 
     *
     */
  ::RTC::ExecutionKind get_kind()
  {
//    return m_profile.kind;
  }
    /*! 
     *
     */
    ::RTC::ReturnCode_t add_component(::RTC::LightweightRTObject_ptr comp)
    {
        if (m_logger != NULL)
        {
            m_logger->log("add_component");
//            ::std::ostringstream os;
//            os<<rate; 
//            m_logger->log(os.str());
        }
        return RTC::BAD_PARAMETER;
    }
  
  
    /*! 
     *
     */
  ::RTC::ReturnCode_t remove_component(::RTC::LightweightRTObject_ptr comp)
  {
    CORBA::ULong index;
//    index = CORBA_SeqUtil::find(m_profile.participants,
//		find_objref<RTObject_ptr>(RTC::RTObject::_narrow(comp)));
				
    if (index < 0) return RTC::BAD_PARAMETER;
//    CORBA_SeqUtil::erase(m_profile.participants, index);
    return RTC::RTC_OK;
  }
  private:
    Logger* m_logger;

  };

  class ExecutionContextServiceProxyTests
   : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(ExecutionContextServiceProxyTests);
    CPPUNIT_TEST(test_get_profile);
    CPPUNIT_TEST_SUITE_END();
  
  private:
    CORBA::ORB_ptr m_pORB;
    PortableServer::POA_ptr m_pPOA;
  
  public:
  
    /*!
     * @brief Constructor
     */
    ExecutionContextServiceProxyTests()
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
    ~ExecutionContextServiceProxyTests()
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
    void test_get_profile()
    {
      ExecutionContextServiceMock* obj = new ExecutionContextServiceMock();
      ::CORBA::Object_ptr ref = obj->_this();
      if(::CORBA::is_nil(ref))
      {
         std::cout<<"ref is nil.Abort test."<<std::endl;
         return;
      }
      ::RTC::CORBA::ExecutionContextServiceProxy* ap 
                 = new ::RTC::CORBA::ExecutionContextServiceProxy(ref);

      Logger logger;
      obj->setLogger(&logger);

      CPPUNIT_ASSERT_EQUAL(0, logger.countLog("get_profile"));
      const ::SDOPackage::Local::DeviceProfile porf;
      ap->get_profile();
      CPPUNIT_ASSERT_EQUAL(1, logger.countLog("get_profile"));

      

      delete ap;
      CORBA::release(ref);
    }
    /* test case */
    void test_case0()
    {
    }
  };
}; // namespace ExecutionContextServiceProxy

/*
 * Register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(ExecutionContextServiceProxy::ExecutionContextServiceProxyTests);

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
#endif // ExecutionContextServiceProxy_cpp
