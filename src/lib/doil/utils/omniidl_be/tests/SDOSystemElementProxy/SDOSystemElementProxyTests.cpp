// -*- C++ -*-
/*!
 * @file   SDOSystemElementProxyTests.cpp
 * @brief  SDOSystemElementProxy test class
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

#ifndef SDOSystemElementProxy_cpp
#define SDOSystemElementProxy_cpp

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>
#include <string>
#include <iostream>
#include <idl/SDOPackageSkel.h>
#include <idl/RTCSkel.h>
#include <SDOSystemElementProxy.h>
#include <rtm/NVUtil.h>
#include <ISDOService.h>
#include <ISDOSystemElement.h>
#include <IOrganization.h>
#include <doil/corba/CORBAManager.h>


/*!
 * @class SDOSystemElementProxyTests class
 * @brief SDOSystemElementProxy test
 */
namespace SDOSystemElementProxy
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
  class SDOSystemElementMock
    : public virtual ::POA_SDOPackage::SDOSystemElement
  {
  protected:
      ::std::vector<std::string> m_log;
  private:
  public :
      SDOSystemElementMock(){}
      virtual ~SDOSystemElementMock()
      {
      }

      void setLogger(Logger* logger)
      {
        m_logger = logger;
      }

    /*! 
     *
     */
     ::SDOPackage::OrganizationList* get_owned_organizations()
     {
        if (m_logger != NULL) m_logger->log("get_owned_organizationse");
     }
  private:
    Logger* m_logger;

  };

  class SDOSystemElementProxyTests
   : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(SDOSystemElementProxyTests);
    CPPUNIT_TEST(test_get_owned_organizations);
    CPPUNIT_TEST_SUITE_END();
  
  private:
    CORBA::ORB_ptr m_pORB;
    PortableServer::POA_ptr m_pPOA;
  
  public:
  
    /*!
     * @brief Constructor
     */
    SDOSystemElementProxyTests()
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
    ~SDOSystemElementProxyTests()
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
    void test_get_owned_organizations()
    {
      SDOSystemElementMock* obj = new SDOSystemElementMock();
      ::CORBA::Object_ptr ref = obj->_this();
      if(::CORBA::is_nil(ref))
      {
         std::cout<<"ref is nil.Abort test."<<std::endl;
         return;
      }
      ::SDOPackage::CORBA::SDOSystemElementProxy* ap 
                 = new ::SDOPackage::CORBA::SDOSystemElementProxy(ref);

      Logger logger;
      obj->setLogger(&logger);

      CPPUNIT_ASSERT_EQUAL(0, logger.countLog("get_owned_organizations"));
      const ::SDOPackage::Local::DeviceProfile porf;
      ap->get_owned_organizations();
      CPPUNIT_ASSERT_EQUAL(1, logger.countLog("get_owned_organizations"));

      

      delete ap;
      CORBA::release(ref);
    }
    /* test case */
    void test_case0()
    {
    }
  };
}; // namespace SDOSystemElementProxy

/*
 * Register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(SDOSystemElementProxy::SDOSystemElementProxyTests);

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
#endif // SDOSystemElementProxy_cpp
