// -*- C++ -*-
/*!
 * @file   OrganizationProxyTests.cpp
 * @brief  OrganizationProxy test class
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

#ifndef OrganizationProxy_cpp
#define OrganizationProxy_cpp

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>
#include <string>
#include <iostream>
#include <idl/SDOPackageSkel.h>
#include <OrganizationProxy.h>
#include <ISDOSystemElement.h>
#include <doil/corba/CORBAManager.h>
#include <doil/corba/CORBAProxyBase.h>

/*!
 * @class OrganizationProxyTests class
 * @brief OrganizationProxy test
 */
namespace OrganizationProxy
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
  class SDOSystemElementServantMock
   : public virtual ::POA_SDOPackage::SDOSystemElement,
     public virtual ::doil::CORBA::CORBAServantBase
  {
  public:
    SDOSystemElementServantMock(doil::ImplBase* impl)
     : ::doil::CORBA::CORBAServantBase(impl) 
    {
    }
    virtual ~SDOSystemElementServantMock()
    {
    }

    virtual ::SDOPackage::OrganizationList* get_owned_organizations()
    {
    }
  private:
    ::SDOPackage::Local::ISDOSystemElement* m_impl;
  };
  /*!
   * 
   * 
   *
   */
  class ISDOSystemElementMock
    : public virtual ::SDOPackage::Local::ISDOSystemElement
  {
  public:
    ISDOSystemElementMock()
      : m_refcount(0)
    {}
    virtual ~ISDOSystemElementMock(){}
    const char* id() {return "ISDOSystemElementMock";}
    const char* name() {return "ISDOSystemElementMock";}
    void incRef()
    {
      ++m_refcount;
    }
    void decRef()
    {
      --m_refcount;
      if (m_refcount == 0)
        delete this;
    }
    virtual ::SDOPackage::Local::OrganizationList get_owned_organizations()
      throw (::SDOPackage::Local::NotAvailable)
    {
        ::SDOPackage::Local::OrganizationList  list;
        return list;
    }
  private:
    std::string m_name;
    int m_refcount;
  };
  /*!
   * 
   * 
   *
   */
  class OrganizationRtmMock
    : public virtual ::POA_SDOPackage::Organization
  {
  protected:
      std::vector<std::string> m_log;
  public :
      OrganizationRtmMock(){}
      virtual ~OrganizationRtmMock(){}

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
    virtual char* get_organization_id()
    {
        if (m_logger != NULL)
        {
            m_logger->log("get_organization_id");
        }
        char m_str[] = "get_organization_id";
	CORBA::String_var sdo_id;
	sdo_id = CORBA::string_dup(m_str);
	return sdo_id._retn();
    }
    /*! 
     *
     */
    virtual SDOPackage::OrganizationProperty* get_organization_property()
    {
        if (m_logger != NULL)
        {
            m_logger->log("get_organization_property");
        }
      SDOPackage::OrganizationProperty *ret = new SDOPackage::OrganizationProperty();
      return ret;
    }
		
    /*! 
     *
     */
    virtual CORBA::Any* get_organization_property_value(const char* name)
    {
        if (m_logger != NULL)
        {
            m_logger->log("get_organization_property_value");
        }
        const char *m_str = "value";
        CORBA::Any corba_any; 
        corba_any <<= m_str;
        ::CORBA::Any* ret = new ::CORBA::Any (corba_any);
        return ret;
    }
		
    /*! 
     *
     */
/*
    virtual CORBA::Boolean set_organization_property(const SDOPackage::OrganizationProperty& organization_property)
    {
      return false;
    }
*/
		
    /*! 
     *
     */
    virtual CORBA::Boolean add_organization_property(const SDOPackage::OrganizationProperty& organization_property)
    {
        if (m_logger != NULL)
        {
            m_logger->log("add_organization_property");
        }
        return false;
    }
		
    /*! 
     *
     */
    virtual CORBA::Boolean set_organization_property_value(const char* name, const CORBA::Any& value)
    {
        if (m_logger != NULL)
        {
            m_logger->log("set_organization_property_value");
        }
      return false;
    }
		
    /*! 
     *
     */
    virtual CORBA::Boolean remove_organization_property(const char* name)
    {
        if (m_logger != NULL)
        {
            m_logger->log("remove_organization_property");
        }
      return false;
    }
		
    /*! 
     *
     */
    virtual SDOPackage::SDOSystemElement_ptr get_owner()
    {
        if (m_logger != NULL)
        {
            m_logger->log("get_owner");
        }
      return ::SDOPackage::SDOSystemElement::_nil();
    }
		
    /*! 
     *
     */
    virtual CORBA::Boolean set_owner(SDOPackage::SDOSystemElement_ptr sdo)
    {
        if (m_logger != NULL)
        {
            m_logger->log("set_owner");
        }
        return false;
    }
		
    /*! 
     *
     */
    virtual SDOPackage::SDOList* get_members()
    {
        if (m_logger != NULL)
        {
            m_logger->log("get_members");
        }
        SDOPackage::SDOList m_memberList;
        SDOPackage::SDOList_var sdos;
        sdos = new SDOPackage::SDOList(m_memberList);
        return sdos._retn();
    }
		
    /*! 
     *
     */
    virtual CORBA::Boolean set_members(const SDOPackage::SDOList& sdos)
    {
        if (m_logger != NULL)
        {
            m_logger->log("set_members");
        }
      return false;
    }
		
    /*! 
     *
     */
    virtual CORBA::Boolean add_members(const SDOPackage::SDOList& sdo_list)
    {
        if (m_logger != NULL)
        {
            m_logger->log("add_members");
        }
      return false;
    }
		
    /*! 
     *
     */
    virtual CORBA::Boolean remove_member(const char* id)
    {
        if (m_logger != NULL)
        {
            m_logger->log("remove_members");
        }
      return false;
    }
		
    /*! 
     *
     */
    virtual SDOPackage::DependencyType get_dependency()
    {
        if (m_logger != NULL)
        {
            m_logger->log("get_dependency");
        }
      return SDOPackage::NO_DEPENDENCY;
    }
		
    /*! 
     *
     */
    virtual CORBA::Boolean set_dependency(SDOPackage::DependencyType dependency)
    {
        if (m_logger != NULL)
        {
            m_logger->log("set_dependency");
        }
      return false;
    }
  private:
    Logger* m_logger;

  };

  class OrganizationProxyTests
   : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(OrganizationProxyTests);

    CPPUNIT_TEST(test_get_organization_id);
    CPPUNIT_TEST(test_get_organization_property);
    CPPUNIT_TEST(test_get_organization_property_value);
    CPPUNIT_TEST(test_add_organization_property);
    CPPUNIT_TEST(test_set_organization_property_value);
    CPPUNIT_TEST(test_remove_organization_property);
    CPPUNIT_TEST(test_get_owner);
    CPPUNIT_TEST(test_get_members);
    CPPUNIT_TEST(test_set_members);
    CPPUNIT_TEST(test_add_members);
    CPPUNIT_TEST(test_remove_member);
    CPPUNIT_TEST(test_get_dependency);
    CPPUNIT_TEST(test_set_dependency);

    CPPUNIT_TEST(test_set_owner);
//    CPPUNIT_TEST(test_case0);
    CPPUNIT_TEST_SUITE_END();
  
  private:
    CORBA::ORB_ptr m_pORB;
    PortableServer::POA_ptr m_pPOA;
  
  public:
  
    /*!
     * @brief Constructor
     */
    OrganizationProxyTests()
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
    ~OrganizationProxyTests()
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
    void test_set_owner()
    {
      doil::CORBA::CORBAManager& 
                            mgr(doil::CORBA::CORBAManager::instance());
      std::cout <<"Manager Name==>"<< mgr.name() << std::endl;

      OrganizationRtmMock* obj = new OrganizationRtmMock();
      ::CORBA::Object_ptr ref = obj->_this();
      if(::CORBA::is_nil(ref))
      {
         std::cout<<"ref is nil.Abort test."<<std::endl;
         return;
      }
      ::SDOPackage::CORBA::OrganizationProxy* ap 
                 = new ::SDOPackage::CORBA::OrganizationProxy(ref);

      Logger logger;
      obj->setLogger(&logger);

       
      bool ret; 
      ISDOSystemElementMock* sdo = new ISDOSystemElementMock();
      mgr.registerFactory(sdo->id(), 
                          doil::New<SDOSystemElementServantMock>,
                          doil::Delete<SDOSystemElementServantMock>);
      mgr.activateObject(sdo);
      CPPUNIT_ASSERT_EQUAL(0, logger.countLog("set_owner"));
      ret = ap->set_owner(sdo);
      CPPUNIT_ASSERT_EQUAL(1, logger.countLog("set_owner"));
      CPPUNIT_ASSERT_EQUAL(false, ret);

      delete ap;
      CORBA::release(ref);

    }
    /*! 
     *
     *
     *
     */
    void test_get_organization_id()
    {

      OrganizationRtmMock* obj = new OrganizationRtmMock();
      ::CORBA::Object_ptr ref = obj->_this();
      if(::CORBA::is_nil(ref))
      {
         std::cout<<"ref is nil.Abort test."<<std::endl;
         return;
      }
      ::SDOPackage::CORBA::OrganizationProxy* ap 
                 = new ::SDOPackage::CORBA::OrganizationProxy(ref);

      Logger logger;
      obj->setLogger(&logger);

       
      std::string ret; 
      std::string str("get_organization_id");
      CPPUNIT_ASSERT_EQUAL(0, logger.countLog("get_organization_id"));
      ret = ap->get_organization_id();
      CPPUNIT_ASSERT_EQUAL(1, logger.countLog("get_organization_id"));
      CPPUNIT_ASSERT_EQUAL(str, ret);

      delete ap;
      CORBA::release(ref);

    }
    /*! 
     *
     *
     *
     */
    void test_get_organization_property()
    {

      OrganizationRtmMock* obj = new OrganizationRtmMock();
      ::CORBA::Object_ptr ref = obj->_this();
      if(::CORBA::is_nil(ref))
      {
         std::cout<<"ref is nil.Abort test."<<std::endl;
         return;
      }
      ::SDOPackage::CORBA::OrganizationProxy* ap 
                 = new ::SDOPackage::CORBA::OrganizationProxy(ref);

      Logger logger;
      obj->setLogger(&logger);

       
      SDOPackage::Local::OrganizationProperty ret; 
      CPPUNIT_ASSERT_EQUAL(0, logger.countLog("get_organization_property"));
      ret = ap->get_organization_property();
      CPPUNIT_ASSERT_EQUAL(1, logger.countLog("get_organization_property"));
      //CPPUNIT_ASSERT_EQUAL(false, ret);

      delete ap;
      CORBA::release(ref);

    }
    /*! 
     *
     *
     *
     */
    void test_get_organization_property_value()
    {

      OrganizationRtmMock* obj = new OrganizationRtmMock();
      ::CORBA::Object_ptr ref = obj->_this();
      if(::CORBA::is_nil(ref))
      {
         std::cout<<"ref is nil.Abort test."<<std::endl;
         return;
      }
      ::SDOPackage::CORBA::OrganizationProxy* ap 
                 = new ::SDOPackage::CORBA::OrganizationProxy(ref);

      Logger logger;
      obj->setLogger(&logger);

       
      std::string ret; 
      std::string str("value");
      CPPUNIT_ASSERT_EQUAL(0, logger.countLog("get_organization_property_value"));
      ret = ap->get_organization_property_value("foo");
      CPPUNIT_ASSERT_EQUAL(1, logger.countLog("get_organization_property_value"));
      CPPUNIT_ASSERT_EQUAL(str, ret);

      delete ap;
      CORBA::release(ref);

    }
    /*! 
     *
     *
     *
     */
    void test_add_organization_property()
    {

      OrganizationRtmMock* obj = new OrganizationRtmMock();
      ::CORBA::Object_ptr ref = obj->_this();
      if(::CORBA::is_nil(ref))
      {
         std::cout<<"ref is nil.Abort test."<<std::endl;
         return;
      }
      ::SDOPackage::CORBA::OrganizationProxy* ap 
                 = new ::SDOPackage::CORBA::OrganizationProxy(ref);

      Logger logger;
      obj->setLogger(&logger);

       
      bool ret; 
      SDOPackage::Local::OrganizationProperty oprop;
      CPPUNIT_ASSERT_EQUAL(0, logger.countLog("add_organization_property"));
      ret = ap->add_organization_property(oprop);
      CPPUNIT_ASSERT_EQUAL(1, logger.countLog("add_organization_property"));
      CPPUNIT_ASSERT_EQUAL(false, ret);

      delete ap;
      CORBA::release(ref);

    }
    /*! 
     *
     *
     *
     */
    void test_set_organization_property_value()
    {

      OrganizationRtmMock* obj = new OrganizationRtmMock();
      ::CORBA::Object_ptr ref = obj->_this();
      if(::CORBA::is_nil(ref))
      {
         std::cout<<"ref is nil.Abort test."<<std::endl;
         return;
      }
      ::SDOPackage::CORBA::OrganizationProxy* ap 
                 = new ::SDOPackage::CORBA::OrganizationProxy(ref);

      Logger logger;
      obj->setLogger(&logger);

       
      bool ret; 
      std::string str1("foo");
      std::string str2("bar");
      
      CPPUNIT_ASSERT_EQUAL(0, logger.countLog("set_organization_property_value"));
      ret = ap->set_organization_property_value(str1,str2);
      CPPUNIT_ASSERT_EQUAL(1, logger.countLog("set_organization_property_value"));
      CPPUNIT_ASSERT_EQUAL(false, ret);

      delete ap;
      CORBA::release(ref);

    }
    /*! 
     *
     *
     *
     */
    void test_remove_organization_property()
    {
      OrganizationRtmMock* obj = new OrganizationRtmMock();
      ::CORBA::Object_ptr ref = obj->_this();
      if(::CORBA::is_nil(ref))
      {
         std::cout<<"ref is nil.Abort test."<<std::endl;
         return;
      }
      ::SDOPackage::CORBA::OrganizationProxy* ap 
                 = new ::SDOPackage::CORBA::OrganizationProxy(ref);

      Logger logger;
      obj->setLogger(&logger);

       
      bool ret; 
      std::string str1("foo");
      
      CPPUNIT_ASSERT_EQUAL(0, logger.countLog("remove_organization_property"));
      ret = ap->remove_organization_property(str1);
      CPPUNIT_ASSERT_EQUAL(1, logger.countLog("remove_organization_property"));
      CPPUNIT_ASSERT_EQUAL(false, ret);

      delete ap;
      CORBA::release(ref);


    }
    /*! 
     *
     *
     *
     */
    void test_get_owner()
    {

      OrganizationRtmMock* obj = new OrganizationRtmMock();
      ::CORBA::Object_ptr ref = obj->_this();
      if(::CORBA::is_nil(ref))
      {
         std::cout<<"ref is nil.Abort test."<<std::endl;
         return;
      }
      ::SDOPackage::CORBA::OrganizationProxy* ap 
                 = new ::SDOPackage::CORBA::OrganizationProxy(ref);

      Logger logger;
      obj->setLogger(&logger);

       
      //::SDOPackage::Local::ISDOSystemElement* ret; 
      CPPUNIT_ASSERT_EQUAL(0, logger.countLog("get_owner"));
      //ret = ap->get_owner();
      ap->get_owner();
      CPPUNIT_ASSERT_EQUAL(1, logger.countLog("get_owner"));
      //CPPUNIT_ASSERT_EQUAL(false, ret);

      delete ap;
      CORBA::release(ref);

    }
    /*! 
     *
     *
     *
     */
    void test_get_members()
    {

      OrganizationRtmMock* obj = new OrganizationRtmMock();
      ::CORBA::Object_ptr ref = obj->_this();
      if(::CORBA::is_nil(ref))
      {
         std::cout<<"ref is nil.Abort test."<<std::endl;
         return;
      }
      ::SDOPackage::CORBA::OrganizationProxy* ap 
                 = new ::SDOPackage::CORBA::OrganizationProxy(ref);

      Logger logger;
      obj->setLogger(&logger);

       
      ::SDOPackage::Local::SDOList ret; 
      CPPUNIT_ASSERT_EQUAL(0, logger.countLog("get_members"));
      ret = ap->get_members();
      CPPUNIT_ASSERT_EQUAL(1, logger.countLog("get_members"));
      //CPPUNIT_ASSERT_EQUAL(false, ret);

      delete ap;
      CORBA::release(ref);

    }
    /*! 
     *
     *
     *
     */
    void test_set_members()
    {

      OrganizationRtmMock* obj = new OrganizationRtmMock();
      ::CORBA::Object_ptr ref = obj->_this();
      if(::CORBA::is_nil(ref))
      {
         std::cout<<"ref is nil.Abort test."<<std::endl;
         return;
      }
      ::SDOPackage::CORBA::OrganizationProxy* ap 
                 = new ::SDOPackage::CORBA::OrganizationProxy(ref);

      Logger logger;
      obj->setLogger(&logger);

       
      bool ret; 
      ::SDOPackage::Local::SDOList sdos;
      CPPUNIT_ASSERT_EQUAL(0, logger.countLog("set_members"));
      ret = ap->set_members(sdos);
      CPPUNIT_ASSERT_EQUAL(1, logger.countLog("set_members"));
      CPPUNIT_ASSERT_EQUAL(false, ret);

      delete ap;
      CORBA::release(ref);

    }
    /*! 
     *
     *
     *
     */
    void test_add_members()
    {
      OrganizationRtmMock* obj = new OrganizationRtmMock();
      ::CORBA::Object_ptr ref = obj->_this();
      if(::CORBA::is_nil(ref))
      {
         std::cout<<"ref is nil.Abort test."<<std::endl;
         return;
      }
      ::SDOPackage::CORBA::OrganizationProxy* ap 
                 = new ::SDOPackage::CORBA::OrganizationProxy(ref);

      Logger logger;
      obj->setLogger(&logger);

       
      bool ret; 
      ::SDOPackage::Local::SDOList sdos;
      CPPUNIT_ASSERT_EQUAL(0, logger.countLog("add_members"));
      ret = ap->add_members(sdos);
      CPPUNIT_ASSERT_EQUAL(1, logger.countLog("add_members"));
      CPPUNIT_ASSERT_EQUAL(false, ret);

      delete ap;
      CORBA::release(ref);
    }
    /*! 
     *
     *
     *
     */
    void test_remove_member()
    {
      OrganizationRtmMock* obj = new OrganizationRtmMock();
      ::CORBA::Object_ptr ref = obj->_this();
      if(::CORBA::is_nil(ref))
      {
         std::cout<<"ref is nil.Abort test."<<std::endl;
         return;
      }
      ::SDOPackage::CORBA::OrganizationProxy* ap 
                 = new ::SDOPackage::CORBA::OrganizationProxy(ref);

      Logger logger;
      obj->setLogger(&logger);

       
      bool ret; 
      std::string str("foo");
      CPPUNIT_ASSERT_EQUAL(0, logger.countLog("remove_members"));
      ret = ap->remove_member(str);
      CPPUNIT_ASSERT_EQUAL(1, logger.countLog("remove_members"));
      CPPUNIT_ASSERT_EQUAL(false, ret);

      delete ap;
      CORBA::release(ref);

    }
    /*! 
     *
     *
     *
     */
    void test_get_dependency()
    {

      OrganizationRtmMock* obj = new OrganizationRtmMock();
      ::CORBA::Object_ptr ref = obj->_this();
      if(::CORBA::is_nil(ref))
      {
         std::cout<<"ref is nil.Abort test."<<std::endl;
         return;
      }
      ::SDOPackage::CORBA::OrganizationProxy* ap 
                 = new ::SDOPackage::CORBA::OrganizationProxy(ref);

      Logger logger;
      obj->setLogger(&logger);

       
      SDOPackage::Local::DependencyType ret; 
      CPPUNIT_ASSERT_EQUAL(0, logger.countLog("get_dependency"));
      ret = ap->get_dependency();
      CPPUNIT_ASSERT_EQUAL(1, logger.countLog("get_dependency"));
      CPPUNIT_ASSERT_EQUAL(SDOPackage::Local::NO_DEPENDENCY, ret);

      delete ap;
      CORBA::release(ref);

    }
    /*! 
     *
     *
     *
     */
    void test_set_dependency()
    {
      OrganizationRtmMock* obj = new OrganizationRtmMock();
      ::CORBA::Object_ptr ref = obj->_this();
      if(::CORBA::is_nil(ref))
      {
         std::cout<<"ref is nil.Abort test."<<std::endl;
         return;
      }
      ::SDOPackage::CORBA::OrganizationProxy* ap 
                 = new ::SDOPackage::CORBA::OrganizationProxy(ref);

      Logger logger;
      obj->setLogger(&logger);

       
      bool ret; 
      CPPUNIT_ASSERT_EQUAL(0, logger.countLog("set_dependency"));
      ret = ap->set_dependency(SDOPackage::Local::NO_DEPENDENCY);
      CPPUNIT_ASSERT_EQUAL(1, logger.countLog("set_dependency"));
      CPPUNIT_ASSERT_EQUAL(false, ret);

      delete ap;
      CORBA::release(ref);

    }
  
    /* test case */
    void test_case0()
    {
    }
  };
}; // namespace OrganizationProxy

/*
 * Register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(OrganizationProxy::OrganizationProxyTests);

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
#endif // OrganizationProxy_cpp
