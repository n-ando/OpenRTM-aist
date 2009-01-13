// -*- C++ -*-
/*!
 * @file   ExecutionContextProxyTests.cpp
 * @brief  ExecutionContextProxy test class
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

#ifndef ExecutionContextProxy_cpp
#define ExecutionContextProxy_cpp

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>
#include <string>
#include <iostream>
#include <sstream>
#include <idl/SDOPackageSkel.h>
#include <ExecutionContextProxy.h>
/*!
 * @class ExecutionContextProxyTests class
 * @brief ExecutionContextProxy test
 */
namespace ExecutionContextProxy
{
  /*!
   * 
   * 
   *
   */
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
  class ExecutionContextRtmMock
    : public virtual ::POA_RTC::ExecutionContext  
  {
  protected:
      std::vector<std::string> m_log;
  public :
      ExecutionContextRtmMock(){}
      virtual ~ExecutionContextRtmMock(){}

    /*! 
     *
     */
      void setLogger(Logger* logger)
      {
        m_logger = logger;
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
    if (!CORBA::is_nil(comp))
      {
//	CORBA_SeqUtil::push_back(m_profile.participants,
//				 RTC::RTObject::_narrow(comp));
	return RTC::RTC_OK;
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

  /*!
   * 
   * 
   *
   */
  class ExecutionContextProxyTests
   : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(ExecutionContextProxyTests);
//    CPPUNIT_TEST(test_case0);
    CPPUNIT_TEST(test_get_rate);
    CPPUNIT_TEST(test_set_rate);
    CPPUNIT_TEST_SUITE_END();
  
  private:
    CORBA::ORB_ptr m_pORB;
    PortableServer::POA_ptr m_pPOA;
  
  public:
  
    /*!
     * @brief Constructor
     */
    ExecutionContextProxyTests()
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
    ~ExecutionContextProxyTests()
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
    void test_get_rate()
    {

      ExecutionContextRtmMock* obj = new ExecutionContextRtmMock();
      ::CORBA::Object_ptr ref = obj->_this();
      if(::CORBA::is_nil(ref))
      {
         std::cout<<"ref is nil.Abort test."<<std::endl;
         return;
      }
      ::RTC::CORBA::ExecutionContextProxy* ap 
                 = new ::RTC::CORBA::ExecutionContextProxy(ref);

      Logger logger;
      obj->setLogger(&logger);

      double ret;
      CPPUNIT_ASSERT_EQUAL(0, logger.countLog("get_rate"));
      ret = ap->get_rate(); 
      CPPUNIT_ASSERT_EQUAL(1, logger.countLog("get_rate"));
      CPPUNIT_ASSERT_EQUAL(3.14159, ret);

      delete ap;
      CORBA::release(ref);

    }
  
    /*! 
     *
     *
     *
     */
    void test_set_rate()
    {

      ExecutionContextRtmMock* obj = new ExecutionContextRtmMock();
      ::CORBA::Object_ptr ref = obj->_this();
      if(::CORBA::is_nil(ref))
      {
         std::cout<<"ref is nil.Abort test."<<std::endl;
         return;
      }
      ::RTC::CORBA::ExecutionContextProxy* ap 
                 = new ::RTC::CORBA::ExecutionContextProxy(ref);

      Logger logger;
      obj->setLogger(&logger);

      double dbuf = 2.71828;
      ::RTC::Local::ReturnCode_t ret;
      CPPUNIT_ASSERT_EQUAL(0, logger.countLog("2.71828"));
      CPPUNIT_ASSERT_EQUAL(0, logger.countLog("set_rate"));
      ret = ap->set_rate(dbuf); 
      CPPUNIT_ASSERT_EQUAL(1, logger.countLog("set_rate"));
      CPPUNIT_ASSERT_EQUAL(::RTC::Local::BAD_PARAMETER, ret);
      CPPUNIT_ASSERT_EQUAL(1, logger.countLog("2.71828"));

      delete ap;
      CORBA::release(ref);

    }
    /* test case */
    void test_case0()
    {
    }
  };
}; // namespace ExecutionContextProxy

/*
 * Register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(ExecutionContextProxy::ExecutionContextProxyTests);

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
#endif // ExecutionContextProxy_cpp
