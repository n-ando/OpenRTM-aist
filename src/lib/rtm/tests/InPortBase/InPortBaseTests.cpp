// -*- C++ -*-
/*!
 * @file   InPortBaseTests.cpp
 * @brief  InPortBase test class
 * @date   $Date: 2008/02/21 07:36:39 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * $Id: InPortBaseTests.cpp 1007 2008-10-31 01:35:29Z fsi-katami $
 *
 */

/*
 * $Log: InPortBaseTests.cpp,v $
 *
 *
 */

#ifndef InPortBase_cpp
#define InPortBase_cpp

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>

#include <rtm/idl/BasicDataTypeSkel.h>
#include <rtm/RTC.h>
#include <rtm/Typename.h>
#include <rtm/InPortBase.h>
#include <rtm/CdrBufferBase.h>
#include <rtm/PortAdmin.h>

/*!
 * @class InPortBaseTests class
 * @brief InPortBase test
 */
namespace InPortBase
{
  /*!
   * 
   * 
   */
  class InPortBaseMock
    : public RTC::InPortBase
  {
  public:
      /*!
       * 
       * 
       */
      InPortBaseMock(const char* name, const char* data_type)
        : RTC::InPortBase(name , data_type)
      {
          rtclog.setLevel("PARANOID");
      }
      /*!
       * 
       * 
       */
      virtual ~InPortBaseMock()
      {
      }
      /*!
       * 
       * 
       */
      RTC::CdrBufferBase* getThebuffer()
      {
          return m_thebuffer;
      }
      /*!
       * 
       * 
       */
      coil::vstring getProviderTypes()
      {
          return m_providerTypes;
      }
      /*!
       * 
       * 
       */
      coil::vstring gerConsumerTypes()
      {
          return m_consumerTypes;
      }
      /*!
       * 
       * 
       */
      void exeInitConsumers()
      {
          initConsumers();
      }
      /*!
       * 
       * 
       */
      void exeInitProviders()
      {
          initProviders();
      }
      /*!
       * 
       * 
       */
      void setSinglebuffer()
      {
          m_singlebuffer = true;
      }
      /*!
       * 
       * 
       */
      void setMultibuffer()
      {
          m_singlebuffer = false;
      }
      /*!
       * 
       * 
       */
      virtual RTC::ReturnCode_t publishInterfaces_public(RTC::ConnectorProfile& connector_profile)
      {
          RTC::ReturnCode_t ret = RTC::InPortBase::publishInterfaces(connector_profile);
          return ret;
      }
      /*!
       * 
       * 
       */
     RTC::InPortConnector*
     createConnector_public(RTC::ConnectorProfile& cprof, 
                            coil::Properties& prop,
                            RTC::InPortProvider* provider)
     {
         return RTC::InPortBase::createConnector(cprof, prop, provider);
     }
  };
  class InPortBaseTests
    : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(InPortBaseTests);

    CPPUNIT_TEST(test_constructor);
    CPPUNIT_TEST(test_init);
    CPPUNIT_TEST(test_initProviders);
    CPPUNIT_TEST(test_initConsumers);
    CPPUNIT_TEST(test_activateInterfaces_deactivateInterfaces);
    CPPUNIT_TEST_SUITE_END();
	
  private:
    CORBA::ORB_ptr m_pORB;
    PortableServer::POA_ptr m_pPOA;

  public:
	
    /*!
     * @brief Constructor
     */
    InPortBaseTests()
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
    ~InPortBaseTests()
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
     * @brief コンスラクタのテスト
     * 
     */
    void test_constructor()
    {
        InPortBaseMock inport("InPortBaseTest", toTypename<RTC::TimedFloat>());

        RTC::PortAdmin portAdmin(m_pORB,m_pPOA);
        portAdmin.registerPort(inport); 
        
        RTC::PortProfile profile = inport.getPortProfile();
        coil::Properties prop = NVUtil::toProperties(profile.properties);
        CPPUNIT_ASSERT_EQUAL(std::string("DataInPort"), prop["port.port_type"] );
        CPPUNIT_ASSERT_EQUAL(std::string(toTypename<RTC::TimedFloat>()),
                             prop["dataport.data_type"] );
        CPPUNIT_ASSERT_EQUAL(std::string("Any"),
                             prop["dataport.subscription_type"]);

        portAdmin.deletePort(inport);
    }
    /*!
     * @brief init()メソッドのテスト
     * 
     */
    void test_init()
    {
        //
        //
        //
        {
        InPortBaseMock inport("InPortBaseTest", toTypename<RTC::TimedFloat>());

        RTC::PortAdmin portAdmin(m_pORB,m_pPOA);
        portAdmin.registerPort(inport); 
        
        CPPUNIT_ASSERT(0==inport.getThebuffer());
        RTC::PortProfile profile = inport.getPortProfile();
        coil::Properties prop = NVUtil::toProperties(profile.properties);
        CPPUNIT_ASSERT_EQUAL(std::string(""),
                             prop["dataport.dataflow_type"]);
        CPPUNIT_ASSERT_EQUAL(std::string(""),
                             prop["dataport.interface_type"]);

        coil::vstring pstr = inport.getProviderTypes();
        CPPUNIT_ASSERT_EQUAL((size_t)0, pstr.size());
        coil::vstring cstr = inport.gerConsumerTypes();
        CPPUNIT_ASSERT_EQUAL((size_t)0, cstr.size());
        inport.init();

        //m_singlebufferがtrueの場合m_thebufferが取得される
        CPPUNIT_ASSERT(0!=inport.getThebuffer());

        profile = inport.getPortProfile();
        prop = NVUtil::toProperties(profile.properties);

        //getPortProfileのpropertiesに以下が追加される
        CPPUNIT_ASSERT_EQUAL(std::string("push,pull"),
                             prop["dataport.dataflow_type"]);
        CPPUNIT_ASSERT_EQUAL(std::string("corba_cdr"),
                             prop["dataport.interface_type"]);
 
        //ProviderTypes,ConsumerTypesが取得される
        pstr = inport.getProviderTypes();
        CPPUNIT_ASSERT_EQUAL(std::string("corba_cdr"),
                             pstr[0]);
        cstr = inport.gerConsumerTypes();
        CPPUNIT_ASSERT_EQUAL(std::string("corba_cdr"),
                             cstr[0]);


        portAdmin.deletePort(inport);
        }
        //
        //
        //
        {
        InPortBaseMock inport("InPortBaseTest", toTypename<RTC::TimedFloat>());

        RTC::PortAdmin portAdmin(m_pORB,m_pPOA);
        portAdmin.registerPort(inport); 
        
        CPPUNIT_ASSERT(0==inport.getThebuffer());
        RTC::PortProfile profile = inport.getPortProfile();
        coil::Properties prop = NVUtil::toProperties(profile.properties);
        CPPUNIT_ASSERT_EQUAL(std::string(""),
                             prop["dataport.dataflow_type"]);
        CPPUNIT_ASSERT_EQUAL(std::string(""),
                             prop["dataport.interface_type"]);

        coil::vstring pstr = inport.getProviderTypes();
        CPPUNIT_ASSERT_EQUAL((size_t)0, pstr.size());
        coil::vstring cstr = inport.gerConsumerTypes();
        CPPUNIT_ASSERT_EQUAL((size_t)0, cstr.size());

        inport.setMultibuffer();
        inport.init();

        CPPUNIT_ASSERT(0==inport.getThebuffer());

        profile = inport.getPortProfile();
        prop = NVUtil::toProperties(profile.properties);

        //getPortProfileのpropertiesに以下が追加される
        CPPUNIT_ASSERT_EQUAL(std::string("push,pull"),
                             prop["dataport.dataflow_type"]);
        CPPUNIT_ASSERT_EQUAL(std::string("corba_cdr"),
                             prop["dataport.interface_type"]);
 
        //ProviderTypes,ConsumerTypesが取得される
        pstr = inport.getProviderTypes();
        CPPUNIT_ASSERT_EQUAL(std::string("corba_cdr"),
                             pstr[0]);
        cstr = inport.gerConsumerTypes();
        CPPUNIT_ASSERT_EQUAL(std::string("corba_cdr"),
                             cstr[0]);

        portAdmin.deletePort(inport);
        }
    }
    /*!
     * @brief initProviders()メソッドのテスト
     * 
     */
    void test_initProviders()
    {
        InPortBaseMock inport("InPortBaseTest", toTypename<RTC::TimedFloat>());

        RTC::PortAdmin portAdmin(m_pORB,m_pPOA);
        portAdmin.registerPort(inport); 
        
        RTC::PortProfile profile = inport.getPortProfile();
        coil::Properties prop = NVUtil::toProperties(profile.properties);
        CPPUNIT_ASSERT_EQUAL(std::string(""),
                             prop["dataport.dataflow_type"]);
        CPPUNIT_ASSERT_EQUAL(std::string(""),
                             prop["dataport.interface_type"]);

        coil::vstring pstr = inport.getProviderTypes();
        CPPUNIT_ASSERT_EQUAL((size_t)0, pstr.size());
        inport.exeInitProviders();


        profile = inport.getPortProfile();
        prop = NVUtil::toProperties(profile.properties);

        //getPortProfileのpropertiesに以下が追加される
        CPPUNIT_ASSERT_EQUAL(std::string("push"),
                             prop["dataport.dataflow_type"]);
        CPPUNIT_ASSERT_EQUAL(std::string("corba_cdr"),
                             prop["dataport.interface_type"]);
 
        //ProviderTypes,ConsumerTypesが取得される
        pstr = inport.getProviderTypes();
        CPPUNIT_ASSERT((size_t)0!= pstr.size());
        CPPUNIT_ASSERT_EQUAL(std::string("corba_cdr"),
                             pstr[0]);

        portAdmin.deletePort(inport);
    }
    /*!
     * @brief initConsumers()メソッドのテスト
     * 
     */
    void test_initConsumers()
    {
        InPortBaseMock inport("InPortBaseTest", toTypename<RTC::TimedFloat>());

        RTC::PortAdmin portAdmin(m_pORB,m_pPOA);
        portAdmin.registerPort(inport); 

        RTC::PortProfile profile = inport.getPortProfile();
        coil::Properties prop = NVUtil::toProperties(profile.properties);
        CPPUNIT_ASSERT_EQUAL(std::string(""),
                             prop["dataport.dataflow_type"]);
        CPPUNIT_ASSERT_EQUAL(std::string(""),
                             prop["dataport.interface_type"]);

        coil::vstring cstr = inport.gerConsumerTypes();
        CPPUNIT_ASSERT_EQUAL((size_t)0, cstr.size());

        inport.exeInitConsumers();

        profile = inport.getPortProfile();
        prop = NVUtil::toProperties(profile.properties);

        //getPortProfileのpropertiesに以下が追加される
        CPPUNIT_ASSERT_EQUAL(std::string("pull"),
                             prop["dataport.dataflow_type"]);
        CPPUNIT_ASSERT_EQUAL(std::string("corba_cdr"),
                             prop["dataport.interface_type"]);
 
        //ProviderTypes,ConsumerTypesが取得される
        cstr = inport.gerConsumerTypes();
        CPPUNIT_ASSERT((size_t)0!= cstr.size());
        CPPUNIT_ASSERT_EQUAL(std::string("corba_cdr"),
                             cstr[0]);

        portAdmin.deletePort(inport);

    }
    /*!
     * @brief activateInterfaces()メソッドのテスト
     * 
     */
    void test_activateInterfaces_deactivateInterfaces(void)
    {
        InPortBaseMock inport("InPortBaseTest", toTypename<RTC::TimedFloat>());
        inport.init();
        RTC::PortAdmin portAdmin(m_pORB,m_pPOA);
        portAdmin.registerPort(inport); 
        RTC::ConnectorProfile prof;
        prof.connector_id = "id0";
        prof.name = CORBA::string_dup("InPortBaseTest0");
        prof.ports.length(1);
        prof.ports[0] = inport.get_port_profile()->port_ref;
        CORBA_SeqUtil::push_back(prof.properties,
                                 NVUtil::newNV("dataport.interface_type",
                                 "corba_cdr"));
        CORBA_SeqUtil::push_back(prof.properties,
                                 NVUtil::newNV("dataport.dataflow_type",
                                 "push"));
        CORBA_SeqUtil::push_back(prof.properties,
                                 NVUtil::newNV("dataport.subscription_type",
                                 "new"));
        inport.publishInterfaces_public(prof);
        prof.connector_id = "id1";
        prof.name = CORBA::string_dup("InPortBaseTest1");
        inport.publishInterfaces_public(prof);

        inport.activateInterfaces();
        inport.deactivateInterfaces();

        portAdmin.deletePort(inport);
    }

    
  };
}; // namespace OutPortBase

/*
 * Register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(InPortBase::InPortBaseTests);

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
#endif // OutPortBase_cpp
