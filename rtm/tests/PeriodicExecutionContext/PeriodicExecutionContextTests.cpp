// -*- C++ -*-
/*!
 * @file   PeriodicExecutionContextTests.cpp
 * @brief  PeriodicExecutionContext test class
 * @date   $Date: 2007-04-13 15:04:39 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * $Id$
 *
 */

#ifndef PeriodicExecutionContext_cpp
#define PeriodicExecutionContext_cpp

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>

#include <rtm/idl/RTCSkel.h>
#include <rtm/PeriodicExecutionContext.h>
#include <rtm/CORBA_SeqUtil.h>

/*!
 * @class PeriodicExecutionContextTests class
 * @brief PeriodicExecutionContext test
 */
namespace PeriodicExecutionContext
{
  using namespace RTC;
  class DFP
    : public virtual POA_RTC::DataFlowComponent, 
      public virtual PortableServer::RefCountServantBase
  {
  public:
    RTC::DataFlowComponent_ptr _ref;
    RTC::ExecutionContextList m_eclist;
    bool m_error;
    DFP()
      : m_error(false)
    {
      _ref = this->_this();
    }
    virtual ~DFP(){}
    RTC::DataFlowComponent_ptr getRef()
    {
      return RTC::DataFlowComponent::_duplicate(_ref);
    }
    void gotoError()
    {
      m_error = true;
    }
    
    virtual ReturnCode_t initialize()
    {
      return RTC::RTC_OK;
    }
    virtual ReturnCode_t finalize()
    {
      return RTC::RTC_OK;
    }
    virtual ReturnCode_t exit()
    {
      return RTC::RTC_OK;
    }
    virtual CORBA::Boolean is_alive()
    {
      return true;
    }
    virtual RTC::ExecutionContextList* get_contexts()
    {
      RTC::ExecutionContextList_var eclist;
      eclist = new RTC::ExecutionContextList(m_eclist);
      return eclist._retn();
    }
    virtual UniqueId 
    set_execution_context_service(const ExecutionContextService_ptr ec)
    {
      CORBA_SeqUtil::push_back(m_eclist, ec);
      return m_eclist.length() - 1;
    }
    virtual ComponentProfile* get_component_profile()
    {
      RTC::ComponentProfile_var prof(new RTC::ComponentProfile());
      return prof._retn();
    }
    virtual PortList* get_ports()
    {
      RTC::PortList_var ports(new PortList());
      ports->length(0);
      return ports._retn();
    }
    virtual ExecutionContextServiceList* get_execution_context_services()
    {
      RTC::ExecutionContextServiceList_var ec;
      ec = new ExecutionContextServiceList();
      ec->length(0);
      return ec._retn();
    }
    virtual ReturnCode_t on_initialize()
    {
      std::cout << "on_initialize()" << std::endl;
      return RTC::RTC_OK;
    }
    virtual ReturnCode_t on_finalize()
    {
      std::cout << "on_finalize()" << std::endl;
      return RTC::RTC_OK;
    }
    virtual ReturnCode_t on_startup(UniqueId ec_id)
    {
      std::cout << "on_startup()" << std::endl;
      return RTC::RTC_OK;
    }
    virtual ReturnCode_t on_shutdown(UniqueId ec_id)
    {
      std::cout << "on_shutdown()" << std::endl;
      return RTC::RTC_OK;
    }
    virtual ReturnCode_t on_activated(UniqueId ec_id)
    {
      std::cout << "on_activated()" << std::endl;
      return RTC::RTC_OK;
    }
    virtual ReturnCode_t on_deactivated(UniqueId ec_id)
    {
      std::cout << "on_deactivated()" << std::endl;
      return RTC::RTC_OK;
    }
    virtual ReturnCode_t on_aborting(UniqueId ec_id)
    {
      std::cout << "on_aborting()" << std::endl;
      return RTC::RTC_OK;
    }
    virtual ReturnCode_t on_error(UniqueId ec_id)
    {
      std::cout << "on_error()" << std::endl;
      return RTC::RTC_OK;
    }
    virtual ReturnCode_t on_reset(UniqueId ec_id)
    {
      std::cout << "on_reset()" << std::endl;
      return RTC::RTC_OK;
    }

    virtual ReturnCode_t on_execute(UniqueId ec_id)
    {
      std::cout << "on_execute()" << std::endl;
      if (m_error) 
	{
	  m_error = false;
	  return RTC::RTC_ERROR;
	}
      return RTC::RTC_OK;
    }
    virtual ReturnCode_t on_state_update(UniqueId ec_id)
    {
      std::cout << "on_state_update()" << std::endl;
      return RTC::RTC_OK;
    }
    virtual ReturnCode_t on_rate_changed(UniqueId ec_id)
    {
      std::cout << "on_rate_changed()" << std::endl;
      return RTC::RTC_OK;
    }

    virtual SDOPackage::OrganizationList* get_owned_organizations()
      throw (SDOPackage::NotAvailable)
    {
      return NULL;
    }
    virtual char* get_sdo_id()
      throw (SDOPackage::NotAvailable, SDOPackage::InternalError)
    {
      return NULL;
    }
    virtual char* get_sdo_type()
      throw (SDOPackage::NotAvailable, SDOPackage::InternalError)
    {
      return NULL;
    }
    virtual SDOPackage::DeviceProfile* get_device_profile()
      throw (SDOPackage::NotAvailable, SDOPackage::InternalError)
    {
      return NULL;
    }
    virtual SDOPackage::ServiceProfileList* get_service_profiles()
      throw (SDOPackage::InvalidParameter, SDOPackage::NotAvailable,
	     SDOPackage::InternalError)
    {
      return NULL;
    }
    virtual SDOPackage::ServiceProfile* get_service_profile(const char* id)
      throw (SDOPackage::InvalidParameter, SDOPackage::NotAvailable,
	     SDOPackage::InternalError)
    {
      return NULL;
    }
    virtual SDOPackage::SDOService_ptr get_sdo_service(const char* id)
      throw (SDOPackage::InvalidParameter, SDOPackage::NotAvailable,
	     SDOPackage::InternalError)
    {
      return SDOPackage::SDOService::_nil();
    }
    virtual SDOPackage::Configuration_ptr get_configuration()
      throw (SDOPackage::InterfaceNotImplemented, SDOPackage::NotAvailable,
	     SDOPackage::InternalError)
    {
      return SDOPackage::Configuration::_nil();
    }
    virtual SDOPackage::Monitoring_ptr get_monitoring()
      throw (SDOPackage::InterfaceNotImplemented, SDOPackage::NotAvailable,
	     SDOPackage::InternalError)
    {
      return SDOPackage::Monitoring::_nil();
    }
    virtual SDOPackage::OrganizationList* get_organizations()
      throw (SDOPackage::NotAvailable, SDOPackage::InternalError)
    {
      return NULL;
    }
    virtual SDOPackage::NVList* get_status_list()
      throw (SDOPackage::NotAvailable, SDOPackage::InternalError)
    {
      return NULL;
    }
    virtual CORBA::Any* get_status(const char* name)
      throw (SDOPackage::InvalidParameter, SDOPackage::NotAvailable,
	     SDOPackage::InternalError)
    {
      return NULL;
    }

  };


  class PeriodicExecutionContextTests
   : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(PeriodicExecutionContextTests);
    CPPUNIT_TEST(test_case0);
    CPPUNIT_TEST_SUITE_END();
  
  private:
    CORBA::ORB_ptr m_pORB;
    PortableServer::POA_ptr m_pPOA;
    DFP* m_dfp;
    RTC::PeriodicExecutionContext* m_pec;

  public:
  
    /*!
     * @brief Constructor
     */
    PeriodicExecutionContextTests()
    {
      int argc(0);
      char** argv(NULL);
      m_pORB = CORBA::ORB_init(argc, argv);
      m_pPOA = PortableServer::POA::_narrow(
			    m_pORB->resolve_initial_references("RootPOA"));
      m_pPOA->the_POAManager()->activate();

      m_dfp = new DFP();
      m_pec = new RTC::PeriodicExecutionContext(m_dfp->_ref, 10);
      m_pec->add(m_dfp->getRef());
      m_pec->start();
    }
    
    /*!
     * @brief Destructor
     */
    ~PeriodicExecutionContextTests()
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
  
    const char* getState(RTC::LifeCycleState state)
    {
      switch (state)
	{
	case RTC::INACTIVE_STATE:
	  return "INACTIVE_STATE";
	  break;
	case RTC::ACTIVE_STATE:
	  return "ACTIVE_STATE";
	  break;
	case RTC::ERROR_STATE:
	  return "ERROR_STATE";
	  break;
	case RTC::UNKNOWN_STATE:
	  return "UNKNOWN_STATE";
	  break;
	default:
	  return "INVALID_STATE";
	  break;
	}
    }

    /* test case */
    void test_case0()
    {
      std::cout << "rate: " << m_pec->get_rate() << std::endl;

      std::cout << "rate: " << m_pec->get_rate() << std::endl;
      std::cout << "kind: " << m_pec->get_kind() << std::endl;


      for (int i = 0; i < 3; ++i)
	{
	  RTC::LifeCycleState state;
	  state = m_pec->get_component_state(m_dfp->getRef());
	  std::cout << getState(state) << std::endl;
	  //RTC::LightweightRTObject::_duplicate(m_dfp->_ref)) << std::endl;
	  sleep(1);
	}
      RTC::ReturnCode_t ret;
      m_pec->set_rate(1);
      ret = m_pec->activate_component(m_dfp->getRef());
      std::cout << ret << std::endl;
      for (int i = 0; i < 3; ++i)
	{
	  RTC::LifeCycleState state;
	  state = m_pec->get_component_state(m_dfp->getRef());
	  std::cout << getState(state) << std::endl;
	  //RTC::LightweightRTObject::_duplicate(m_dfp->_ref)) << std::endl;
	  sleep(1);
	}
      m_pec->set_rate(10);
      ret = m_pec->activate_component(m_dfp->getRef());
      std::cout << ret << std::endl;
      for (int i = 0; i < 3; ++i)
	{
	  RTC::LifeCycleState state;
	  state = m_pec->get_component_state(m_dfp->getRef());
	  std::cout << getState(state) << std::endl;
	  //RTC::LightweightRTObject::_duplicate(m_dfp->_ref)) << std::endl;
	  sleep(1);
	}
      ret = m_pec->deactivate_component(m_dfp->getRef());
      for (int i = 0; i < 3; ++i)
	{
	  RTC::LifeCycleState state;
	  state = m_pec->get_component_state(m_dfp->getRef());
	  std::cout << getState(state) << std::endl;
	  //RTC::LightweightRTObject::_duplicate(m_dfp->_ref)) << std::endl;
	  sleep(1);
	}
      ret = m_pec->stop();
      for (int i = 0; i < 3; ++i)
	{
	  RTC::LifeCycleState state;
	  state = m_pec->get_component_state(m_dfp->getRef());
	  std::cout << getState(state) << std::endl;
	  //RTC::LightweightRTObject::_duplicate(m_dfp->_ref)) << std::endl;
	  sleep(1);
	}
      m_pec->activate_component(m_dfp->getRef());
      ret = m_pec->start();
      for (int i = 0; i < 3; ++i)
	{
	  RTC::LifeCycleState state;
	  state = m_pec->get_component_state(m_dfp->getRef());
	  std::cout << getState(state) << std::endl;
	  //RTC::LightweightRTObject::_duplicate(m_dfp->_ref)) << std::endl;
	  sleep(1);
	}
      m_dfp->gotoError();
      for (int i = 0; i < 3; ++i)
	{
	  RTC::LifeCycleState state;
	  state = m_pec->get_component_state(m_dfp->getRef());
	  std::cout << getState(state) << std::endl;
	  //RTC::LightweightRTObject::_duplicate(m_dfp->_ref)) << std::endl;
	  sleep(1);
	}
      std::cout << "RESET" << std::endl;
      m_pec->reset_component(m_dfp->getRef());
      for (int i = 0; i < 3; ++i)
	{
	  RTC::LifeCycleState state;
	  state = m_pec->get_component_state(m_dfp->getRef());
	  std::cout << getState(state) << std::endl;
	  //RTC::LightweightRTObject::_duplicate(m_dfp->_ref)) << std::endl;
	  sleep(1);
	}
      std::cout << "ACTIVATE" << std::endl;
      m_pec->activate_component(m_dfp->getRef());
      for (int i = 0; i < 3; ++i)
	{
	  RTC::LifeCycleState state;
	  state = m_pec->get_component_state(m_dfp->getRef());
	  std::cout << getState(state) << std::endl;
	  //RTC::LightweightRTObject::_duplicate(m_dfp->_ref)) << std::endl;
	  sleep(1);
	}


    }
  };
}; // namespace PeriodicExecutionContext

/*
 * Register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(PeriodicExecutionContext::PeriodicExecutionContextTests);

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
#endif // PeriodicExecutionContext_cpp
