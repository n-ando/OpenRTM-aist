// -*- C++ -*-

/*
 * $Log: OutPortCorbaProviderTests.cpp,v $
 * Revision 1.1  2008/02/25 13:13:35  arafune
 * The first commitment.
 *
 *
 */

#ifndef OutPortCorbaProvider_cpp
#define OutPortCorbaProvider_cpp

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>
#include <rtm/idl/BasicDataTypeSkel.h>
#include <rtm/RingBuffer.h>
#include <rtm/OutPortCorbaProvider.h>

/*!
 * @class OutPortCorbaProviderTests class
 * @brief OutPortCorbaProvider test
 */
namespace OutPortCorbaProvider
{
  int g_argc;
  std::vector<std::string> g_argv;

  class OutPortCorbaProviderTests
    : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(OutPortCorbaProviderTests);
    CPPUNIT_TEST(test_publishInterfaceProfile);
    CPPUNIT_TEST(test_get);
    CPPUNIT_TEST_SUITE_END();
	
  private:
    CORBA::ORB_var m_orb;
    PortableServer::POA_ptr m_poa;
		
  public:
	
    /*!
     * @brief Constructor
     */
    OutPortCorbaProviderTests()
    {
    }
		
    /*!
     * @brief Destructor
     */
    ~OutPortCorbaProviderTests()
    {
    }
		
    /*!
     * @brief Test initialization
     */
    virtual void setUp()
    {
      char* argv[g_argc];
      for (int i = 0; i < g_argc; i++) {
	argv[i] = (char *)g_argv[i].c_str();
      }
			
      m_orb = CORBA::ORB_init(g_argc, argv);
    }
		
    /*!
     * @brief Test finalization
     */
    virtual void tearDown()
    {
      //      if (m_orb != 0) {
      //	m_orb->destroy();
      //	m_orb = 0;
      //      }
    }

    /*!
     * @brief publishInterfaceProfile()メソッドのテスト
     * 
     * - dataport.data_typeプロパティを正しく取得できるか？
     * - dataport.interface_typeプロパティを正しく取得できるか？
     * - dataport.dataflow_typeプロパティを正しく取得できるか？
     * - dataport.subscription_typeプロパティを正しく取得できるか？
     */
    void test_publishInterfaceProfile()
    {
      RTC::RingBuffer<RTC::TimedFloat> buffer(10);
      RTC::OutPortCorbaProvider<RTC::TimedFloat>* provider
	= new RTC::OutPortCorbaProvider<RTC::TimedFloat>(buffer); // will be deleted automatically
		
      SDOPackage::NVList prop;
      provider->publishInterfaceProfile(prop);

      // dataport.data_typeプロパティを正しく取得できるか？
      {
	const char* value;
	NVUtil::find(prop, "dataport.data_type") >>= value;
	CPPUNIT_ASSERT_EQUAL(std::string("TimedFloat"), std::string(value));
      }
			
      // dataport.interface_typeプロパティを正しく取得できるか？
      {
	const char* value;
	NVUtil::find(prop, "dataport.interface_type") >>= value;
	CPPUNIT_ASSERT_EQUAL(std::string("CORBA_Any"), std::string(value));
      }
			
      // dataport.dataflow_typeプロパティを正しく取得できるか？
      {
	const char* value;
	NVUtil::find(prop, "dataport.dataflow_type") >>= value;
	CPPUNIT_ASSERT_EQUAL(std::string("Push, Pull"), std::string(value));
      }
			
      // dataport.subscription_typeプロパティを正しく取得できるか？
      {
	const char* value;
	NVUtil::find(prop, "dataport.subscription_type") >>= value;
	CPPUNIT_ASSERT_EQUAL(std::string("Flush, New, Periodic"), std::string(value));
      }

//      delete provider;
    }
		
    /*!
     * @brief get()メソッドのテスト
     * 
     * - バッファに書き込まれた値を、get()メソッドで正しく読み出せるか？
     */
    void test_get()
    {
      RTC::RingBuffer<RTC::TimedFloat> buffer(100);
      RTC::OutPortCorbaProvider<RTC::TimedFloat>* provider
	= new RTC::OutPortCorbaProvider<RTC::TimedFloat>(buffer); // will be deleted automatically
			
      RTC::TimedFloat* readValue = new RTC::TimedFloat;
      for (int i = 0; i < 10; ++i)
	{
	  RTC::TimedFloat writeValue;
	  writeValue.data = 3.14159 * i;
	  buffer.write(writeValue);

	  // バッファに書き込まれた値を、get()メソッドで正しく読み出せるか？			
//	  RTC::TimedFloat* readValue = new RTC::TimedFloat;
	  CORBA::Any_var any = provider->get();
	  any.in() >>= readValue;
	  CPPUNIT_ASSERT_EQUAL(writeValue.data, readValue->data);
	}
//      delete provider;
    }
  };
}; // namespace OutPortCorbaProvider

/*
 * Register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(OutPortCorbaProvider::OutPortCorbaProviderTests);

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
#endif // OutPortCorbaProvider_cpp
