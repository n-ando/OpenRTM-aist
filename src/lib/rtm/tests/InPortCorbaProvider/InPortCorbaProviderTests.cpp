// -*- C++ -*-

/*
 * $Log: InPortCorbaProviderTests.cpp,v $
 * Revision 1.1  2008/03/10 13:43:26  arafune
 * The first commitment.
 *
 *
 */

#ifndef InPortCorbaProvider_cpp
#define InPortCorbaProvider_cpp

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>
#include <rtm/InPortCorbaProvider.h>
#include <rtm/idl/BasicDataTypeSkel.h>
#include <rtm/RingBuffer.h>
#include <rtm/StringUtil.h>

/*!
 * @class InPortCorbaProviderTests class
 * @brief InPortCorbaProvider test
 */
namespace InPortCorbaProvider
{
  int g_argc;
  std::vector<std::string> g_argv;

  class InPortCorbaProviderTests
    : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(InPortCorbaProviderTests);
    CPPUNIT_TEST(test_publishInterfaceProfile);
    CPPUNIT_TEST(test_publishInterface_matched_interfaceType);
    CPPUNIT_TEST(test_publishInterface_unmatched_interfaceType);
    CPPUNIT_TEST(test_put);
    CPPUNIT_TEST_SUITE_END();
		
  public:
	
    /*!
     * @brief Constructor
     */
    InPortCorbaProviderTests()
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
    ~InPortCorbaProviderTests()
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
     * @brief publishInterfaceProfile()メソッドのテスト
     * 
     * - "dataport.data_type"プロパティを正しく取得できるか？
     * - "dataport.interface_type"プロパティを正しく取得できるか？
     * - "dataport.dataflow_type"プロパティを正しく取得できるか？
     * - "dataport.subscription_type"プロパティを正しく取得できるか？
     */
    void test_publishInterfaceProfile()
    {
      RTC::RingBuffer<RTC::TimedFloat> buffer(100);
      RTC::InPortCorbaProvider<RTC::TimedFloat>* provider
	= new RTC::InPortCorbaProvider<RTC::TimedFloat>(buffer); // will be deleted automatically
			
      SDOPackage::NVList profile;
      provider->publishInterfaceProfile(profile);
			
      // "dataport.data_type"プロパティを正しく取得できるか？
      CPPUNIT_ASSERT_EQUAL(std::string("TimedFloat"),
			   NVUtil::toString(profile, "dataport.data_type"));
			
      // "dataport.interface_type"プロパティを正しく取得できるか？
      CPPUNIT_ASSERT_EQUAL(std::string("CORBA_Any"),
			   NVUtil::toString(profile, "dataport.interface_type"));
			
      // "dataport.dataflow_type"プロパティを正しく取得できるか？
      CPPUNIT_ASSERT_EQUIVALENT(std::string("Push, Pull"),
				NVUtil::toString(profile, "dataport.dataflow_type"));
			
      // "dataport.subscription_type"プロパティを正しく取得できるか？
      CPPUNIT_ASSERT_EQUIVALENT(std::string("Any"),
				NVUtil::toString(profile, "dataport.subscription_type"));
      delete provider;
    }
		
    /*!
     * @brief （インタフェース・タイプが適合する場合の）publishInterface()メソッドのテスト
     * 
     * - "dataport.corba_any.inport_ref"プロパティを正しく取得できるか？
     */
    void test_publishInterface_matched_interfaceType()
    {
      RTC::RingBuffer<RTC::TimedFloat> buffer(100);
      RTC::InPortCorbaProvider<RTC::TimedFloat>* provider
	= new RTC::InPortCorbaProvider<RTC::TimedFloat>(buffer); // will be deleted automatically
			
      // インタフェース・タイプが適合するように設定したうえで、インタフェース情報を取得する
      SDOPackage::NVList properties;
      NVUtil::appendStringValue(properties, "dataport.interface_type", "CORBA_Any");
      provider->publishInterface(properties);

      // "dataport.corba_any.inport_ref"プロパティを正しく取得できるか？
      RTC::InPortAnyRef inPortAnyRef;
      NVUtil::find(properties, "dataport.corba_any.inport_ref") >>= inPortAnyRef;
      CPPUNIT_ASSERT(! CORBA::is_nil(inPortAnyRef));
      delete provider;
    }
		
    /*!
     * @brief （インタフェース・タイプが適合しない場合の）publishInterface()メソッドのテスト
     * 
     * - "dataport.corba_any.inport_ref"プロパティは、意図どおり取得されていないか？
     */
    void test_publishInterface_unmatched_interfaceType()
    {
      RTC::RingBuffer<RTC::TimedFloat> buffer(100);
      RTC::InPortCorbaProvider<RTC::TimedFloat>* provider
	= new RTC::InPortCorbaProvider<RTC::TimedFloat>(buffer); // will be deleted automatically
			
      // インタフェース・タイプが適合しないように設定したうえで、インタフェース情報を取得する
      SDOPackage::NVList properties;
      NVUtil::appendStringValue(properties, "dataport.interface_type", "UNMATCHED_INTERFACE_TYPE");
      provider->publishInterface(properties);
			
      // "dataport.corba_any.inport_ref"プロパティは、意図どおり取得されていないか？
      CPPUNIT_ASSERT_EQUAL(CORBA::Long(-1),
			   NVUtil::find_index(properties, "dataport.corba_any.inport_ref"));
      delete provider;
    }
		
    /*!
     * @brief put()メソッドのテスト
     * 
     * - put()メソッドを通して書き込んだ値が、正しくバッファに書き込まれているか？
     */
    void test_put()
    {
      RTC::RingBuffer<RTC::TimedFloat> buffer(100);
      RTC::InPortCorbaProvider<RTC::TimedFloat>* provider
	= new RTC::InPortCorbaProvider<RTC::TimedFloat>(buffer); // will be deleted automatically
			
      // 値をInPortCorbaProviderを通して書き込む
      RTC::TimedFloat putValue;
      putValue.data = 3.14159;
      CORBA::Any putValueAny;
      putValueAny <<= putValue;
      provider->put(putValueAny);
			
      // バッファから値を取り出して、正しく書き込まれたことを確認する
      RTC::TimedFloat readValue;
      buffer.read(readValue);
      CPPUNIT_ASSERT_EQUAL(putValue.data, readValue.data);
      delete provider;
    }
		
  private:
	
    void CPPUNIT_ASSERT_EQUIVALENT(const std::string& lhs, const std::string& rhs)
    {
      std::vector<std::string> lhsValues = split(lhs, ",");
      std::vector<std::string> rhsValues = split(rhs, ",");
			
      // 要素数が異なれば、中身を見るまでもなく同一ではないと判定できる
      if (lhsValues.size() != rhsValues.size())
	{
	  CPPUNIT_ASSERT_EQUAL(lhs, rhs);
	}
			
      // 要素数は同じなので、中身を逐一比較する
      sort(lhsValues.begin(), lhsValues.end());
      sort(rhsValues.begin(), rhsValues.end());
      std::vector<std::string>::size_type size = lhsValues.size();
      for (std::vector<std::string>::size_type i = 0; i < size; ++i)
	{
	  if (lhsValues[i] != rhsValues[i])
	    {
	      CPPUNIT_ASSERT_EQUAL(lhs, rhs);
	    }
	}
			
      // ここまでたどり着いたのであれば、同一と判定される
      return;
    }
		
  };
}; // namespace InPortCorbaProvider

/*
 * Register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(InPortCorbaProvider::InPortCorbaProviderTests);

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
#endif // InPortCorbaProvider_cpp
