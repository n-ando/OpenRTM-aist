// -*- C++ -*-
/*!
 * @file   SDOProxyTests.cpp
 * @brief  SDOProxy test class
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

#ifndef SDOProxy_cpp
#define SDOProxy_cpp

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>
#include <string>
#include <iostream>
#include <idl/SDOPackageSkel.h>
#include <idl/RTCSkel.h>
#include <SDOProxy.h>
#include <rtm/NVUtil.h>
#include <ISDOService.h>
#include <ISDOSystemElement.h>
#include <IOrganization.h>
#include <doil/corba/CORBAManager.h>


/*!
 * @class SDOProxyTests class
 * @brief SDOProxy test
 */
namespace SDOProxy
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
  class SDOMock
    : public virtual ::POA_SDOPackage::SDO
  {
  protected:
      ::std::vector<std::string> m_log;
  private:
  public :
      SDOMock(){}
      virtual ~SDOMock()
      {
      }

      void setLogger(Logger* logger)
      {
        m_logger = logger;
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
    /*! 
     *
     */
    ::RTC::ExecutionContextList* get_owned_contexts()
    {
    }
    /*! 
     *
     */
    ::SDOPackage::OrganizationList* get_owned_organizations()
    {
    }

  private:
    Logger* m_logger;

  };

  class SDOProxyTests
   : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(SDOProxyTests);
    CPPUNIT_TEST(test_get_sdo_id);
    CPPUNIT_TEST_SUITE_END();
  
  private:
    CORBA::ORB_ptr m_pORB;
    PortableServer::POA_ptr m_pPOA;
  
  public:
  
    /*!
     * @brief Constructor
     */
    SDOProxyTests()
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
    ~SDOProxyTests()
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
    void test_get_sdo_id()
    {
      SDOMock* obj = new SDOMock();
      ::CORBA::Object_ptr ref = obj->_this();
      if(::CORBA::is_nil(ref))
      {
         std::cout<<"ref is nil.Abort test."<<std::endl;
         return;
      }
      ::SDOPackage::CORBA::SDOProxy* ap 
                 = new ::SDOPackage::CORBA::SDOProxy(ref);

      Logger logger;
      obj->setLogger(&logger);

      CPPUNIT_ASSERT_EQUAL(0, logger.countLog("get_sdo_id"));
      ap->get_sdo_id();
      CPPUNIT_ASSERT_EQUAL(1, logger.countLog("get_sdo_id"));

      

      delete ap;
      CORBA::release(ref);
    }
    /* test case */
    void test_case0()
    {
    }
  };
}; // namespace SDOProxy

/*
 * Register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(SDOProxy::SDOProxyTests);

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
#endif // SDOProxy_cpp
