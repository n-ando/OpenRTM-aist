// -*- C++ -*-
/*!
 * @file   OutPortConnectorTests.cpp
 * @brief  OutPortConnector test class
 * @date   $Date: 2008/03/13 13:12:25 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 *
 * Copyright (C) 2006
 *     Noriaki Ando
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: InPortTests.cpp 817 2008-08-06 02:54:26Z n-ando $
 *
 */


#ifndef OutPortConnector_cpp
#define OutPortConnector_cpp

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>

#include <coil/Properties.h>

#include <rtm/idl/BasicDataTypeSkel.h>
#include <rtm/Typename.h>
#include <rtm/OutPortConnector.h>
#include <rtm/CdrBufferBase.h>
#include <rtm/CORBA_SeqUtil.h>
#include <rtm/NVUtil.h>
#include <rtm/ConnectorBase.h>
#include <rtm/DataPortStatus.h>
#include <rtm/InPortBase.h>
#include <rtm/OutPortBase.h>
#include <rtm/PortAdmin.h>

/*!
 * @class OutPortConnectorTests class
 * @brief OutPortConnector test
 */
namespace OutPortConnector
{
  class OutPortConnectorMock
    : public RTC::OutPortConnector
  {
  public:
      OutPortConnectorMock(ConnectorBase::Profile& profile)
        : RTC::OutPortConnector(profile)
      {
      }
      virtual ~OutPortConnectorMock()
      {
      }
      virtual ReturnCode disconnect()
      {
          return ::RTC::DataPortStatus::PORT_OK;
      }
      virtual ReturnCode read(cdrMemoryStream& data)
      {
          return ::RTC::DataPortStatus::PORT_OK;
      }
      virtual void activate()
      {
      }
      virtual void deactivate()
      {
      }
      virtual RTC::CdrBufferBase* getBuffer()
      {
          return m_buffer;
      }
      virtual ReturnCode write(const cdrMemoryStream& data)
      {
          return ::RTC::DataPortStatus::PORT_OK;
      }
  private:
      RTC::CdrBufferBase *m_buffer;
  };

  class OutPortConnectorTests
    : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(OutPortConnectorTests);
    CPPUNIT_TEST(test_case0);
    CPPUNIT_TEST_SUITE_END();
		
  private:
    CORBA::ORB_ptr m_pORB;
    PortableServer::POA_ptr m_pPOA;


  public:
	
    /*!
     * @brief Constructor
     */
    OutPortConnectorTests()
    {

        int argc(0);
        char** argv(NULL);
        m_pORB = CORBA::ORB_init(argc, argv);
        m_pPOA = PortableServer::POA::_narrow(
		    m_pORB->resolve_initial_references("RootPOA"));
        m_pPOA->the_POAManager()->activate();

    }
		
    /*!
     * @brief Destructor
     */
    ~OutPortConnectorTests()
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
     * @brief profile(),id(),name()メソッドのテスト
     * 
     */
    void test_case0()
    {

        RTC::InPortBase inport("OutPortConnectorTest1", toTypename<RTC::TimedFloat>());
        RTC::PortService_var port_ref1= inport.get_port_profile()->port_ref;
        RTC::OutPortBase outport("OutPortConnectorTest2", toTypename<RTC::TimedFloat>());
        RTC::PortService_var port_ref2= outport.get_port_profile()->port_ref;


        RTC::PortAdmin portAdmin(m_pORB,m_pPOA);
        portAdmin.registerPort(inport); 
        portAdmin.registerPort(outport); 

        RTC::ConnectorProfile cprof;
        cprof.connector_id = "id";
        cprof.name = CORBA::string_dup("OutPortConnectorTest");

        CORBA_SeqUtil::push_back(cprof.properties,
                                 NVUtil::newNV("dataport.interface_type",
					       "corba_cdr"));
        CORBA_SeqUtil::push_back(cprof.properties,
                                 NVUtil::newNV("dataport.dataflow_type",
					       "push"));
        CORBA_SeqUtil::push_back(cprof.properties,
                                 NVUtil::newNV("dataport.subscription_type",
					        "new"));

        cprof.ports.length(2);
        cprof.ports[0] = port_ref1;
        cprof.ports[1] = port_ref2;

        coil::Properties prop;
        NVUtil::copyToProperties(prop, cprof.properties);
        RTC::ConnectorBase::Profile profile(cprof.name,
                                       cprof.connector_id,
                                       CORBA_SeqUtil::refToVstring(cprof.ports),
                                       prop); 

        OutPortConnector::OutPortConnectorMock connector(profile);
        CPPUNIT_ASSERT_EQUAL(std::string(cprof.connector_id),std::string(connector.id()));
        CPPUNIT_ASSERT_EQUAL(std::string(cprof.name),std::string(connector.name()));
        RTC::ConnectorBase::Profile profile2 = connector.profile();
        CPPUNIT_ASSERT_EQUAL(profile.name,profile2.name);
        CPPUNIT_ASSERT_EQUAL(profile.id,profile2.id);
        CPPUNIT_ASSERT(profile.ports==profile2.ports);
        CPPUNIT_ASSERT_EQUAL(profile.properties.size(),
                             profile2.properties.size());
          
        CPPUNIT_ASSERT_EQUAL(profile.properties["dataport.interface_type"],
                             profile2.properties["dataport.interface_type"]);
        CPPUNIT_ASSERT_EQUAL(profile.properties["dataport.dataflow_type"],
                             profile2.properties["dataport.dataflow_type"]);
        CPPUNIT_ASSERT_EQUAL(profile.properties["dataport.subscription_type"],
                             profile2.properties["dataport.subscription_type"]);
        portAdmin.deletePort(inport);
        portAdmin.deletePort(outport);
    }
		
  };
}; // namespace InPort

/*
 * Register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(OutPortConnector::OutPortConnectorTests);

#ifdef LOCAL_MAIN
int main(int argc, char* argv[])
{

  FORMAT format = TEXT_OUT;
  int target = 0;
  std::string xsl;
  std::string ns;
  std::string fname;
  std::ofstream ofs;

  int i(1);
  while (i < argc)
    {
      std::string arg(argv[i]);
      std::string next_arg;
      if (i + 1 < argc) next_arg = argv[i + 1];
      else              next_arg = "";

      if (arg == "--text") { format = TEXT_OUT; break; }
      if (arg == "--xml")
	{
	  if (next_arg == "")
	    {
	      fname = argv[0];
	      fname += ".xml";
	    }
	  else
	    {
	      fname = next_arg;
	    }
	  format = XML_OUT;
	  ofs.open(fname.c_str());
	}
      if ( arg == "--compiler"  ) { format = COMPILER_OUT; break; }
      if ( arg == "--cerr"      ) { target = 1; break; }
      if ( arg == "--xsl"       )
	{
	  if (next_arg == "") xsl = "default.xsl"; 
	  else                xsl = next_arg;
	}
      if ( arg == "--namespace" )
	{
	  if (next_arg == "")
	    {
	      std::cerr << "no namespace specified" << std::endl;
	      exit(1); 
	    }
	  else
	    {
	      xsl = next_arg;
	    }
	}
      ++i;
    }
  CppUnit::TextUi::TestRunner runner;
  if ( ns.empty() )
    runner.addTest(CppUnit::TestFactoryRegistry::getRegistry().makeTest());
  else
    runner.addTest(CppUnit::TestFactoryRegistry::getRegistry(ns).makeTest());
  CppUnit::Outputter* outputter = 0;
  std::ostream* stream = target ? &std::cerr : &std::cout;
  switch ( format )
    {
    case TEXT_OUT :
      outputter = new CppUnit::TextOutputter(&runner.result(),*stream);
      break;
    case XML_OUT :
      std::cout << "XML_OUT" << std::endl;
      outputter = new CppUnit::XmlOutputter(&runner.result(),
					    ofs, "shift_jis");
      static_cast<CppUnit::XmlOutputter*>(outputter)->setStyleSheet(xsl);
      break;
    case COMPILER_OUT :
      outputter = new CppUnit::CompilerOutputter(&runner.result(),*stream);
      break;
    }
  runner.setOutputter(outputter);
  runner.run();
  return 0; // runner.run() ? 0 : 1;
}
#endif // MAIN
#endif // InPort_cpp
