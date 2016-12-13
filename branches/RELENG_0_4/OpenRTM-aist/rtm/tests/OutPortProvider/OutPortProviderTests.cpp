// -*- C++ -*-

/*
 * $Log: OutPortProviderTests.cpp,v $
 * Revision 1.1  2008/02/21 12:51:22  arafune
 * The first commitment.
 *
 */

#ifndef OutPortProvider_cpp
#define OutPortProvider_cpp

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>
#include <rtm/OutPortProvider.h>

/*!
 * @class OutPortProviderTests class
 * @brief OutPortProvider test
 */
namespace OutPortProvider
{
  class OutPortProviderMock
    : public RTC::OutPortProvider
  {
  public:
    OutPortProviderMock(
			const std::string& portType,
			const std::string& dataType,
			const std::string& interfaceType,
			const std::string& dataFlowType,
			const std::string& subscriptionType)
    {
      setPortType(portType.c_str());
      setDataType(dataType.c_str());
      setInterfaceType(interfaceType.c_str());
      setDataFlowType(dataFlowType.c_str());
      setSubscriptionType(subscriptionType.c_str());
			
      NVUtil::appendStringValue(m_properties, "PROPERTY_NAME1", "PROPERTY_VALUE1");
      NVUtil::appendStringValue(m_properties, "PROPERTY_NAME2", "PROPERTY_VALUE2");
    }
  };
	
  int g_argc;
  std::vector<std::string> g_argv;

  class OutPortProviderTests
    : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(OutPortProviderTests);
    CPPUNIT_TEST(test_publishInterfaceProfile);
    CPPUNIT_TEST(test_publishInterface);
    CPPUNIT_TEST_SUITE_END();
		
  public:
	
    /*!
     * @brief Constructor
     */
    OutPortProviderTests()
    {
      char* argv[g_argc];
      for (int i = 0; i < g_argc; i++) {
	argv[i] = (char *)g_argv[i].c_str();
      }
	      
      CORBA::ORB_var orb = CORBA::ORB_init(g_argc, argv);
    }
		
    /*!
     * @brief Destructor
     */
    ~OutPortProviderTests()
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
     * @brief publishInterfaceProfile()メソッドのテスト。
     * 
     * - dataport.data_typeプロパティを正しく取得できるか？
     * - dataport.interface_typeプロパティを正しく取得できるか？
     * - dataport.dataflow_typeプロパティを正しく取得できるか？
     * - dataport.subscription_typeプロパティを正しく取得できるか？
     */
    void test_publishInterfaceProfile()
    {
      std::auto_ptr<RTC::OutPortProvider> provider(
						   new OutPortProviderMock(
									   "PORT_TYPE", "DATA_TYPE", "INTERFACE_TYPE",
									   "DATA_FLOW_TYPE", "SUBSCRIPTION_TYPE"));
			
      SDOPackage::NVList prop;
      provider->publishInterfaceProfile(prop);

      // dataport.data_typeプロパティを正しく取得できるか？
      {
	char* value;
	NVUtil::find(prop, "dataport.data_type") >>= value;
	CPPUNIT_ASSERT_EQUAL(std::string("DATA_TYPE"), std::string(value));
      }
			
      // dataport.interface_typeプロパティを正しく取得できるか？
      {
	char* value;
	NVUtil::find(prop, "dataport.interface_type") >>= value;
	CPPUNIT_ASSERT_EQUAL(std::string("INTERFACE_TYPE"), std::string(value));
      }
			
      // dataport.dataflow_typeプロパティを正しく取得できるか？
      {
	char* value;
	NVUtil::find(prop, "dataport.dataflow_type") >>= value;
	CPPUNIT_ASSERT_EQUAL(std::string("DATA_FLOW_TYPE"), std::string(value));
      }
			
      // dataport.subscription_typeプロパティを正しく取得できるか？
      {
	char* value;
	NVUtil::find(prop, "dataport.subscription_type") >>= value;
	CPPUNIT_ASSERT_EQUAL(std::string("SUBSCRIPTION_TYPE"), std::string(value));
      }
    }

    /*!
     * @brief publishInterface()メソッドのテスト
     * 
     * - 引数で渡したNameValueオブジェクトのインタフェースタイプが、ポートのそれと一致しない場合に、
     * Interface情報が取得されないことを確認する。
     * - 引数で渡したNameValueオブジェクトのインタフェースタイプが、ポートのそれと一致する場合に、
     * Interface情報を取得でき、それが期待値と一致することを確認する。
     */
    void test_publishInterface()
    {
      std::auto_ptr<RTC::OutPortProvider> provider(
						   new OutPortProviderMock(
									   "PORT_TYPE", "DATA_TYPE", "INTERFACE_TYPE",
									   "DATA_FLOW_TYPE", "SUBSCRIPTION_TYPE"));
			
      SDOPackage::NVList prop;
      provider->publishInterfaceProfile(prop);
			        
      // (1) インタフェースタイプが不一致の場合：
      SDOPackage::NVList prop_dummy = prop;
      for (CORBA::ULong i(0); i < prop_dummy.length(); ++i)
	{
	  if (std::string(prop_dummy[i].name) == std::string("dataport.interface_type"))
	    {
	      // インタフェースタイプが一致しないように、書き換える
	      prop_dummy[i].value <<= "DUMMY";
	    }
	}
			
      provider->publishInterface(prop_dummy);
			
      // インタフェース情報が取得されないことを確認する
      CPPUNIT_ASSERT_EQUAL(CORBA::Long(-1), NVUtil::find_index(prop_dummy, "PROPERTY_NAME1"));
      CPPUNIT_ASSERT_EQUAL(CORBA::Long(-1), NVUtil::find_index(prop_dummy, "PROPERTY_NAME2"));
			
      // (2) インタフェースタイプ一致の場合：
      provider->publishInterface(prop);
			
      // インタフェース情報が取得されることを確認する
      CORBA::Long index1 = NVUtil::find_index(prop, "PROPERTY_NAME1");
      CORBA::Long index2 = NVUtil::find_index(prop, "PROPERTY_NAME2");
      CPPUNIT_ASSERT(CORBA::Long(-1) != index1);
      CPPUNIT_ASSERT(CORBA::Long(-1) != index2);
			
      char* value1;
      prop[index1].value >>= value1;
      CPPUNIT_ASSERT_EQUAL(std::string("PROPERTY_VALUE1"), std::string(value1));

      char* value2;			
      prop[index2].value >>= value2;
      CPPUNIT_ASSERT_EQUAL(std::string("PROPERTY_VALUE2"), std::string(value2));
    }

  };
}; // namespace OutPortProvider

/*
 * Register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(OutPortProvider::OutPortProviderTests);

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
#endif // OutPortProvider_cpp
