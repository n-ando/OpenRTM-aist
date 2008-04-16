// -*- C++ -*-
/*!
 * @file   DataInOutPortTests.cpp
 * @brief  DataInOutPort test class
 * @date   $Date: 2007-01-06 18:04:51 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * $Id$
 *
 */

/*
 * $Log: not supported by cvs2svn $
 *
 */

#ifndef DataInOutPort_cpp
#define DataInOutPort_cpp

#include <iostream>

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>

#include <rtm/idl/BasicDataTypeSkel.h>
#include <rtm/idl/RTCSkel.h>
#include <rtm/DataOutPort.h>
#include <rtm/OutPort.h>
#include <rtm/DataInPort.h>
#include <rtm/InPort.h>

/*!
 * @class DataInOutPortTests class
 * @brief DataInOutPort test
 */
namespace DataInOutPort
{  
  template <class DataType>
  struct HogeCovnert : public RTC::OnReadConvert<DataType>
  {
    DataType operator()(const DataType& value)
    {
      DataType d(value);
      d.data = value.data * value.data;
      return d;
    }
  };

  class DataInOutPortTests
   : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(DataInOutPortTests);
    CPPUNIT_TEST(test_connect);
    CPPUNIT_TEST_SUITE_END();
  
  private:
    RTC::OutPort<RTC::TimedFloat> m_outport;
    RTC::TimedFloat m_ofloat;
    RTC::DataOutPort* m_doutport;
    RTC::Port_var m_oportref;

    RTC::InPort<RTC::TimedFloat> m_inport;
    RTC::TimedFloat m_ifloat;
    RTC::DataInPort* m_dinport;
    RTC::Port_var m_iportref;

    HogeCovnert<RTC::TimedFloat>* m_conv;
    CORBA::ORB_ptr m_pORB;
    PortableServer::POA_ptr m_pPOA;
  public:
  
    /*!
     * @brief Constructor
     */
    DataInOutPortTests()
      : m_outport("fout", m_ofloat),
	m_inport("fin", m_ifloat)
    {
      m_conv = new HogeCovnert<RTC::TimedFloat>();
      //      m_inport.setOnReadConvert(m_conv);

      int argc(0);
      char** argv(NULL);
      m_pORB = CORBA::ORB_init(argc, argv);
      m_pPOA = PortableServer::POA::_narrow(
		    m_pORB->resolve_initial_references("RootPOA"));
      m_pPOA->the_POAManager()->activate();

      m_doutport = new RTC::DataOutPort("DataOutPort", m_outport);
      m_oportref = m_doutport->get_port_profile()->port_ref;

      m_dinport = new RTC::DataInPort("DataInPort", m_inport);
      m_iportref = m_dinport->get_port_profile()->port_ref;

    }
    
    /*!
     * @brief Destructor
     */
    ~DataInOutPortTests()
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
  
    /* test case */
    void test_connect()
    {
      RTC::ConnectorProfile prof;
      prof.connector_id = "";
      prof.name = CORBA::string_dup("connector0");
      prof.ports.length(2);
      prof.ports[0] = m_oportref;
      prof.ports[1] = m_iportref;
      CORBA_SeqUtil::push_back(prof.properties,
			       NVUtil::newNV("dataport.interface_type",
					     "CORBA_Any"));
      CORBA_SeqUtil::push_back(prof.properties,
			       NVUtil::newNV("dataport.dataflow_type",
					     "Push"));
      CORBA_SeqUtil::push_back(prof.properties,
			       NVUtil::newNV("dataport.subscription_type",
					     "New"));
      m_dinport->connect(prof);
      
      RTC::ConnectorProfileList* iprof;
      iprof = m_dinport->get_connector_profiles();

      RTC::ConnectorProfileList* oprof;
      oprof = m_doutport->get_connector_profiles();

#ifdef DEBUG
      std::cout << "Returned  connector ID"
		<< prof.connector_id << std::endl;
      std::cout << "InPort's  connector ID" 
		<< (*iprof)[0].connector_id << std::endl;
      std::cout << "OutPort's connector ID"
		<< (*oprof)[0].connector_id << std::endl;
#endif
      std::string c_id, i_id, o_id;
      c_id = prof.connector_id;
      i_id = (*iprof)[0].connector_id;
      o_id = (*oprof)[0].connector_id;

      CPPUNIT_ASSERT(c_id == o_id);
      CPPUNIT_ASSERT(c_id == i_id);
      CPPUNIT_ASSERT(o_id == i_id);

      for (int i = 0; i < 100; ++i)
	{
	  m_ofloat.data = 1.234567 * i;
	  m_outport.write();

	  m_inport.read();
#ifdef DEBUG
	  sleep(1);
	  std::cout <<  m_ofloat.data << " <=> " << m_ifloat.data << std::endl;
#endif
	  CPPUNIT_ASSERT(m_ofloat.data == m_ifloat.data);
	}




    }
  };
}; // namespace DataInOutPort

/*
 * Register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(DataInOutPort::DataInOutPortTests);

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
#endif // DataInOutPort_cpp
