// -*- C++ -*-
/*!
 * @file   DataFlowComponentActionProxyTests.cpp
 * @brief  DataFlowComponentActionProxy test class
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

#ifndef DataFlowComponentActionProxy_cpp
#define DataFlowComponentActionProxy_cpp

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>
#include <string>
#include <iostream>
#include <idl/SDOPackageSkel.h>
#include <idl/RTCSkel.h>
#include <DataFlowComponentActionProxy.h>
#include <rtm/NVUtil.h>
#include <ISDOService.h>
#include <ISDOSystemElement.h>
#include <IOrganization.h>
#include <doil/corba/CORBAManager.h>


/*!
 * @class DataFlowComponentActionProxyTests class
 * @brief DataFlowComponentActionProxy test
 */
namespace DataFlowComponentActionProxy
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

  class OrganizationServantMock
   : public virtual ::POA_SDOPackage::Organization,
     public virtual ::doil::CORBA::CORBAServantBase
  {
  public:
    OrganizationServantMock(doil::ImplBase* impl)
    : ::doil::CORBA::CORBAServantBase(impl), m_impl(NULL) 
    {
      m_impl = dynamic_cast< ::SDOPackage::Local::IOrganization* >(impl);
    }
    virtual ~OrganizationServantMock(){}
    virtual char* get_organization_id(){return "OrganizationServantMock";}
    virtual ::SDOPackage::OrganizationProperty* get_organization_property()
    {
      ::SDOPackage::OrganizationProperty_var ret 
                            = new ::SDOPackage::OrganizationProperty ();
      return ret._retn();
    }
    virtual ::CORBA::Any* get_organization_property_value(const char* name)
    {
	CORBA::Any_var value;
	value = new CORBA::Any();
	return value._retn();
//      return new ::CORBA::Any();
    }
    virtual ::CORBA::Boolean add_organization_property(
          const ::SDOPackage::OrganizationProperty& organization_property)
    {
	return true;
    }
/*
    virtual ::CORBA::Boolean set_organization_property(
          const ::SDOPackage::OrganizationProperty& organization_property)
    {
	return true;
    }
*/
    virtual ::CORBA::Boolean set_organization_property_value(
          const char* name, const CORBA::Any& value)
    {
	return true;
    }
    virtual ::CORBA::Boolean remove_organization_property(const char* name)
    {
	return true;
    }
    virtual ::SDOPackage::SDOSystemElement_ptr get_owner()
    {
        return m_varOwner._retn();
    }
    virtual ::CORBA::Boolean set_owner(
          ::SDOPackage::SDOSystemElement_ptr sdo)
    { 
        return true; 
    }
    virtual ::SDOPackage::SDOList* get_members()
    {
//        ::SDOPackage::SDOList* ret = new ::SDOPackage::SDOList ();
//	return ret;
	::SDOPackage::SDOList_var sdos;
	sdos = new ::SDOPackage::SDOList(m_memberList);
	return sdos._retn();
    }
    virtual CORBA::Boolean set_members(
          const ::SDOPackage::SDOList& sdos)
    {
	m_memberList = sdos;
	return true;
    }
    virtual CORBA::Boolean add_members(
          const ::SDOPackage::SDOList& sdo_list)
    {
        return true; 
    }
    virtual CORBA::Boolean remove_member(const char* id){return true;}
    virtual ::SDOPackage::DependencyType get_dependency()
    {
        return m_dependency;
    }
    virtual CORBA::Boolean set_dependency(
          ::SDOPackage::DependencyType dependency) 
    { 
	m_dependency = dependency;
        return true; 
    }


  private:
    ::SDOPackage::Local::IOrganization* m_impl;
    ::SDOPackage::SDOSystemElement_var m_varOwner;
    ::SDOPackage::DependencyType m_dependency;
    ::SDOPackage::SDOList m_memberList;
  };

  /*!
   * 
   * 
   *
   */
  class ISDOServiceServantMock
   : public virtual ::POA_SDOPackage::SDOService,
     public virtual ::doil::CORBA::CORBAServantBase
  {
  public:
    ISDOServiceServantMock(doil::ImplBase* impl)
    : ::doil::CORBA::CORBAServantBase(impl)
    {
      m_impl = dynamic_cast< ::SDOPackage::Local::ISDOService* >(impl);
    }
    virtual ~ISDOServiceServantMock(){}


  private:
    ::SDOPackage::Local::ISDOService* m_impl;
  };
  /*!
   * 
   * 
   *
   */
  class ISDOServiceMock
    : public virtual ::SDOPackage::Local::ISDOService
  {
  public:
    ISDOServiceMock()
      : m_refcount(0)
    {}
    virtual ~ISDOServiceMock(){}
    const char* id() {return "ISDOServiceMock";}
    const char* name() {return "ISDOServiceMock";}
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

  private:
    std::string m_name;
    int m_refcount;
  };
  /*!
   * 
   * 
   *
   */
  class IOrganizationMock
    : public virtual ::SDOPackage::Local::IOrganization
  {
  public:
    IOrganizationMock()
      : m_refcount(0)
    {}
    virtual ~IOrganizationMock(){}

    virtual ::std::string get_organization_id()
      throw (::SDOPackage::Local::InvalidParameter,
             ::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError)
    {
        return "IOrganizationMock";
    }

    virtual ::SDOPackage::Local::OrganizationProperty get_organization_property()
      throw (::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError)
    {
       ::SDOPackage::Local::OrganizationProperty ret;
       return ret;
    }

    virtual ::std::string get_organization_property_value(const ::std::string& name)
      throw (::SDOPackage::Local::InvalidParameter,
             ::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError)
    {
        return "IOrganizationMock";
    }
    virtual bool add_organization_property(const ::SDOPackage::Local::OrganizationProperty& organization_property)
      throw (::SDOPackage::Local::InvalidParameter,
             ::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError)
    {
        return true;       
    }
/*
    virtual bool set_organization_property(const ::SDOPackage::Local::OrganizationProperty& organization_property)
      throw (::SDOPackage::Local::InvalidParameter,
             ::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError)
    {
        return true;       
    }
*/

    virtual bool set_organization_property_value(const ::std::string&name, const ::std::string& value)
      throw (::SDOPackage::Local::InvalidParameter,
             ::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError)
    {
        return true;       
    }

    virtual bool remove_organization_property(const ::std::string& name)
      throw (::SDOPackage::Local::InvalidParameter,
             ::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError)
    {
        return true;       
    }

    virtual ::SDOPackage::Local::ISDOSystemElement* get_owner()
      throw (::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError)
    {
        return NULL;
    }

    virtual bool set_owner(const ::SDOPackage::Local::ISDOSystemElement* sdo)
      throw (::SDOPackage::Local::InvalidParameter,
             ::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError)
    {
        return true;
    }

    virtual ::SDOPackage::Local::SDOList get_members()
      throw (::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError)
    {
        ::SDOPackage::Local::SDOList ret; 
        return ret;
    }

    virtual bool set_members(const ::SDOPackage::Local::SDOList& sdos)
      throw (::SDOPackage::Local::InvalidParameter,
             ::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError)
    {
        return true;
    }

    virtual bool add_members(const ::SDOPackage::Local::SDOList& sdo_list)
      throw (::SDOPackage::Local::InvalidParameter,
             ::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError)
    {
        return true;
    }

    virtual bool remove_member(const ::std::string& id)
      throw (::SDOPackage::Local::InvalidParameter,
             ::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError)
    {
        return true;
    }

    virtual ::SDOPackage::Local::DependencyType get_dependency()
      throw (::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError)
    {
        return m_dependency;
    }

    virtual bool set_dependency(::SDOPackage::Local::DependencyType dependency)
      throw (::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError)
    {
        m_dependency = dependency;
        return true;
    }


    const char* id() {return "IOrganizationMock";}
    const char* name() {return "IOrganizationMock";}
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

  private:
    std::string m_name;
    int m_refcount;
    ::SDOPackage::Local::DependencyType m_dependency;
   };
  /*!
   * 
   * 
   *
   */
  class DataFlowComponentActionMock
    : public virtual ::POA_RTC::DataFlowComponentAction
  {
  protected:
      ::std::vector<std::string> m_log;
  private:
    Logger* m_logger;
  public :
      DataFlowComponentActionMock(){}
      virtual ~DataFlowComponentActionMock()
      {
      }

      void setLogger(Logger* logger)
      {
        m_logger = logger;
      }

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

  };

  class DataFlowComponentActionProxyTests
   : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(DataFlowComponentActionProxyTests);
    CPPUNIT_TEST(test_on_execute);
    CPPUNIT_TEST(test_on_state_update);
    CPPUNIT_TEST(test_on_rate_changed);
    CPPUNIT_TEST_SUITE_END();
  
  private:
    CORBA::ORB_ptr m_pORB;
    PortableServer::POA_ptr m_pPOA;
  
  public:
  
    /*!
     * @brief Constructor
     */
    DataFlowComponentActionProxyTests()
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
    ~DataFlowComponentActionProxyTests()
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
    void test_on_execute()
    {
      DataFlowComponentActionMock* obj = new DataFlowComponentActionMock();
      ::CORBA::Object_ptr ref = obj->_this();
      if(::CORBA::is_nil(ref))
      {
         std::cout<<"ref is nil.Abort test."<<std::endl;
         return;
      }
      ::RTC::CORBA::DataFlowComponentActionProxy* ap 
                 = new ::RTC::CORBA::DataFlowComponentActionProxy(ref);

      Logger logger;
      obj->setLogger(&logger);

      CPPUNIT_ASSERT_EQUAL(0, logger.countLog("on_execute"));
      ::RTC::Local::ExecutionContextHandle_t exec_handle;
      ap->on_execute(exec_handle);
      CPPUNIT_ASSERT_EQUAL(1, logger.countLog("on_execute"));

      

      delete ap;
      CORBA::release(ref);
    }
    /*! 
     *
     *
     *
     */
    void test_on_state_update()
    {
      DataFlowComponentActionMock* obj = new DataFlowComponentActionMock();
      ::CORBA::Object_ptr ref = obj->_this();
      if(::CORBA::is_nil(ref))
      {
         std::cout<<"ref is nil.Abort test."<<std::endl;
         return;
      }
      ::RTC::CORBA::DataFlowComponentActionProxy* ap 
                 = new ::RTC::CORBA::DataFlowComponentActionProxy(ref);

      Logger logger;
      obj->setLogger(&logger);

      CPPUNIT_ASSERT_EQUAL(0, logger.countLog("on_state_update"));
      ::RTC::Local::ExecutionContextHandle_t exec_handle;
      ap->on_state_update(exec_handle);
      CPPUNIT_ASSERT_EQUAL(1, logger.countLog("on_state_update"));

      

      delete ap;
      CORBA::release(ref);
    }
    /*! 
     *
     *
     *
     */
    void test_on_rate_changed()
    {
      DataFlowComponentActionMock* obj = new DataFlowComponentActionMock();
      ::CORBA::Object_ptr ref = obj->_this();
      if(::CORBA::is_nil(ref))
      {
         std::cout<<"ref is nil.Abort test."<<std::endl;
         return;
      }
      ::RTC::CORBA::DataFlowComponentActionProxy* ap 
                 = new ::RTC::CORBA::DataFlowComponentActionProxy(ref);

      Logger logger;
      obj->setLogger(&logger);

      CPPUNIT_ASSERT_EQUAL(0, logger.countLog("on_rate_change"));
      ::RTC::Local::ExecutionContextHandle_t exec_handle;
      ap->on_rate_changed(exec_handle);
      CPPUNIT_ASSERT_EQUAL(1, logger.countLog("on_rate_change"));

      

      delete ap;
      CORBA::release(ref);
    }
    /* test case */
    void test_case0()
    {
    }
  };
}; // namespace DataFlowComponentActionProxy

/*
 * Register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(DataFlowComponentActionProxy::DataFlowComponentActionProxyTests);

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
#endif // DataFlowComponentActionProxy_cpp
