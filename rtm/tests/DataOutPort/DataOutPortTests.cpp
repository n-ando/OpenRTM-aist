// -*- C++ -*-
/*!
 * @file   DataOutPortTests.cpp
 * @brief  DataOutPort test class
 * @date   $Date: 2007-01-12 14:49:56 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * $Id$
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.1  2006/11/27 08:31:03  n-ando
 * TestSuites are devided into each directory.
 *
 *
 */

#ifndef DataOutPort_cpp
#define DataOutPort_cpp

#include <iostream>

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>

#include <rtm/idl/BasicDataTypeSkel.h>
#include <rtm/idl/RTCSkel.h>
#include <rtm/OutPort.h>
#include <rtm/DataOutPort.h>

/*!
 * @class DataOutPortTests class
 * @brief DataOutPort test
 */
namespace DataOutPort
{

  class DataOutPortTests
   : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(DataOutPortTests);
    CPPUNIT_TEST(test_write);
    CPPUNIT_TEST(test_profile);
    CPPUNIT_TEST(test_connect);
    CPPUNIT_TEST_SUITE_END();
  
  private:
    RTC::OutPort<RTC::TimedFloat> m_outport;
    RTC::TimedFloat m_tfloat;
    RTC::DataOutPort* m_doutport;
    RTC::Port_var m_portref;

    CORBA::ORB_ptr m_pORB;
    PortableServer::POA_ptr m_pPOA;
  public:
  
    /*!
     * @brief Constructor
     */
    DataOutPortTests()
      : m_outport("fout", m_tfloat)
    {
      int argc(0);
      char** argv(NULL);
      m_pORB = CORBA::ORB_init(argc, argv);
      m_pPOA = PortableServer::POA::_narrow(
	         m_pORB->resolve_initial_references("RootPOA"));
      m_pPOA->the_POAManager()->activate();

      m_doutport = new RTC::DataOutPort("DataOutPortTests", m_outport);

      m_portref = m_doutport->get_port_profile()->port_ref;
    }
    
    /*!
     * @brief Destructor
     */
    ~DataOutPortTests()
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
    void test_write()
    {
      m_tfloat.data = 1.23456;
      m_outport.write();
      RTC::TimedFloat data;
      m_outport.read(data);
      std::cout << data.data << std::endl;
    }

    void test_profile()
    {
      RTC::PortProfile* prof;
      prof = m_doutport->get_port_profile();

      std::cout << "port_name: " << prof->name << std::endl;
      std::cout << "if_name: " << prof->interfaces[0].instance_name
		<< std::endl;
      std::cout << "if_type: " << prof->interfaces[0].type_name << std::endl;
      std::cout << "if_polr: " << prof->interfaces[0].polarity << std::endl;
      std::cout << "IOR: " << m_pORB->object_to_string(prof->port_ref)
		<<std::endl;

      for (CORBA::ULong i = 0; i < prof->properties.length(); ++i)
	{
	  std::cout << "prop_name: " << prof->properties[i].name << std::endl;
	  std::cout << "prop_valu: "
		    <<  NVUtil::toString(prof->properties,
					 prof->properties[i].name)
		    << std::endl;
	}
    }

    void test_connect()
    {
      RTC::ConnectorProfile prof;
      prof.connector_id = "";
      prof.name = CORBA::string_dup("connector0");
      prof.ports.length(1);
      prof.ports[0] = m_portref;
      CORBA_SeqUtil::push_back(prof.properties,
			       NVUtil::newNV("dataport.interface_type",
					     "CORBA_Any"));
      CORBA_SeqUtil::push_back(prof.properties,
			       NVUtil::newNV("dataport.dataflow_type",
					     "Push"));
      CORBA_SeqUtil::push_back(prof.properties,
			       NVUtil::newNV("dataport.subscription_type",
					     "New"));
      m_doutport->connect(prof);

      std::cout << prof.connector_id << std::endl;
    }
  };
}; // namespace DataOutPort

/*
 * Register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(DataOutPort::DataOutPortTests);

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
#endif // DataOutPort_cpp
