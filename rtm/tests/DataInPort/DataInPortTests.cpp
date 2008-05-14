// -*- C++ -*-
/*!
 * @file   DataInPortTests.cpp
 * @brief  DataInPort test class
 * @date   $Date: 2007-01-12 14:49:42 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * $Id$
 *
 */

#ifndef DataInPort_cpp
#define DataInPort_cpp

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>

#include <rtm/idl/BasicDataTypeSkel.h>
#include <rtm/idl/RTCSkel.h>
#include <rtm/DataInPort.h>
#include <rtm/InPort.h>

/*!
 * @class DataInPortTests class
 * @brief DataInPort test
 */
namespace DataInPort
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
    

  class DataInPortTests
   : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(DataInPortTests);
    //    CPPUNIT_TEST(test_read);
    CPPUNIT_TEST(test_profile);
    CPPUNIT_TEST(test_connect);
    CPPUNIT_TEST_SUITE_END();
  
  private:
    RTC::InPort<RTC::TimedFloat> m_inport;
    RTC::TimedFloat m_tfloat;
    RTC::DataInPort* m_dinport;
    RTC::Port_var m_portref;
    HogeCovnert<RTC::TimedFloat>* m_conv;
    CORBA::ORB_ptr m_pORB;
    PortableServer::POA_ptr m_pPOA;
    
  public:
  
    /*!
     * @brief Constructor
     */
    DataInPortTests()
      : m_inport("fin", m_tfloat)
    {
      m_conv = new HogeCovnert<RTC::TimedFloat>();
      m_inport.setOnReadConvert(m_conv);
      int argc(0);
      char** argv(NULL);
      m_pORB = CORBA::ORB_init(argc, argv);
      m_pPOA = PortableServer::POA::_narrow(
			    m_pORB->resolve_initial_references("RootPOA"));
      m_pPOA->the_POAManager()->activate();
   
      m_dinport = new RTC::DataInPort("DataInPortTest", m_inport);

      //      PortableServer::ObjectId_var oid;
      //      oid = m_pPOA->activate_object(m_doutport);
      m_portref = m_dinport->get_port_profile()->port_ref;
    }
    
    /*!
     * @brief Destructor
     */
    ~DataInPortTests()
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
    void test_case0()
    {
    }
    
    void test_profile()
    {
      RTC::PortProfile* prof;
      prof = m_dinport->get_port_profile();
      
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
      m_dinport->connect(prof);

      std::cout << prof.connector_id << std::endl;

      for (CORBA::ULong i = 0; i < prof.properties.length(); ++i)
	{
	  std::cout << "prop_name: " << prof.properties[i].name << std::endl;
	  if (NVUtil::isString(prof.properties, prof.properties[i].name))
	    {
	      std::cout << "prop_valu: "
			<<  NVUtil::toString(prof.properties,
					     prof.properties[i].name)
			<< std::endl;
	    }
	  else
	    {
	      std::string s(CORBA::string_dup(prof.properties[i].name));
	      if (s == "dataport.corba_any.inport_ref")
		{
		  CORBA::Object_ptr o;
		  RTC::Port_ptr p;
		  RTC::InPortAny_ptr ip;
		  prof.properties[i].value >>= o;
		  prof.properties[i].value >>= p;
		  prof.properties[i].value >>= ip;
		  //		  prof.properties[i].value >>= i;
		  
		  std::cout << "prop_valu: "
			    <<  m_pORB->object_to_string(o)
			    << std::endl;
		  std::cout << "prop_valu: "
			    <<  m_pORB->object_to_string(p)
			    << std::endl;
		  std::cout << "prop_valu: "
			    <<  m_pORB->object_to_string(ip)
			    << std::endl;
		  /*
		  std::cout << "prop_valu: "
			    <<  m_pORB->object_to_string(i)
			    << std::endl;
		  */


		  for (int j = 0; j < 1000; ++j)
		    {
		      RTC::TimedFloat fdata;
		      fdata.data = j;
		      CORBA::Any_var adata(new CORBA::Any());
		      adata <<= fdata;
		      
		      ip->put(adata);
		      
		      RTC::TimedFloat data;
		      data = m_inport.read();
		      
		      std::cout << data.data << std::endl;
		    }
		}
	    }
	}
    }

  };
}; // namespace DataInPort

/*
 * Register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(DataInPort::DataInPortTests);

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
#endif // DataInPort_cpp
