// -*- C++ -*-
/*!
 * @file   MonitoringProxyTests.cpp
 * @brief  MonitoringProxy test class
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

#ifndef MonitoringProxy_cpp
#define MonitoringProxy_cpp

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>
#include <string>
#include <iostream>
#include <idl/SDOPackageSkel.h>
#include <idl/RTCSkel.h>
#include <MonitoringProxy.h>
#include <rtm/NVUtil.h>
#include <ISDOService.h>
#include <ISDOSystemElement.h>
#include <IOrganization.h>
#include <doil/corba/CORBAManager.h>


/*!
 * @class MonitoringProxyTests class
 * @brief MonitoringProxy test
 */
namespace MonitoringProxy
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
  class MonitoringMock
    : public virtual ::POA_SDOPackage::Monitoring
  {
  protected:
      ::std::vector<std::string> m_log;
  private:
  public :
      MonitoringMock(){}
      virtual ~MonitoringMock()
      {
      }

      void setLogger(Logger* logger)
      {
        m_logger = logger;
      }

  private:
    Logger* m_logger;

  };

  class MonitoringProxyTests
   : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(MonitoringProxyTests);
    //CPPUNIT_TEST(test_set_service_profile);
    CPPUNIT_TEST_SUITE_END();
  
  private:
    CORBA::ORB_ptr m_pORB;
    PortableServer::POA_ptr m_pPOA;
  
  public:
  
    /*!
     * @brief Constructor
     */
    MonitoringProxyTests()
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
    ~MonitoringProxyTests()
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
/*
    void test_set_service_profile()
    {
      std::cout <<"test_set_service_profile() entry "<<std::endl;
      doil::CORBA::CORBAManager& 
                            mgr(doil::CORBA::CORBAManager::instance());
      std::cout <<"Manager Name==>"<< mgr.name() << std::endl;

      MonitoringMock* obj = new MonitoringMock();
      ::CORBA::Object_ptr ref = obj->_this();
      if(::CORBA::is_nil(ref))
      {
         std::cout<<"ref is nil.Abort test."<<std::endl;
         return;
      }
      
      std::cout <<"test_set_service_profile() ref: "<<ref<<std::endl;
      ::SDOPackage::CORBA::MonitoringProxy* ap 
                 = new ::SDOPackage::CORBA::MonitoringProxy(ref);

      Logger logger;
      obj->setLogger(&logger);

      std::cout <<"test_set_service_profile() 030 "<<std::endl;
      CPPUNIT_ASSERT_EQUAL(0, logger.countLog("set_service_profile"));
      ::SDOPackage::Local::ServiceProfile porf;
      ISDOServiceMock service;

      std::cout <<"test_set_service_profile() 040 "<<std::endl;
      mgr.registerFactory(service.id(), 
                          doil::New<ISDOServiceServantMock>,
                          doil::Delete<ISDOServiceServantMock>);
      std::cout <<"test_set_service_profile() 050 "<<std::endl;
      mgr.activateObject(&service);

      porf.service = &service;
      const ::SDOPackage::Local::ServiceProfile _porf = porf;
      std::cout <<"test_set_service_profile() 060 "<<std::endl;
      ap->set_service_profile(_porf);
      std::cout <<"test_set_service_profile() 070 "<<std::endl;
      CPPUNIT_ASSERT_EQUAL(1, logger.countLog("set_service_profile"));

      std::cout <<"test_set_service_profile() 080 "<<std::endl;
      mgr.deactivateObject(&service);
      std::cout <<"test_set_service_profile() 080 "<<std::endl;

      delete ap;
      CORBA::release(ref);
      mgr.shutdown();
      std::cout <<"test_set_service_profile() ret "<<std::endl;
    }
*/
    /* test case */
    void test_case0()
    {
    }
  };
}; // namespace MonitoringProxy

/*
 * Register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(MonitoringProxy::MonitoringProxyTests);

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
#endif // MonitoringProxy_cpp
