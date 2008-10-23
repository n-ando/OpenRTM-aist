// -*- C++ -*-
/*!
 * @file   PublisherFactoryTests.cpp
 * @brief  PublisherFactory test class
 * @date   $Date: 2008/01/30 10:25:59 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * $Id$
 *
 */

/*
 * $Log: PublisherFactoryTests.cpp,v $
 * Revision 1.2  2008/01/30 10:25:59  arafune
 * The test_create was added.
 * Some tests were deleted.
 *
 * Revision 1.1  2007/12/20 07:50:17  arafune
 * *** empty log message ***
 *
 * Revision 1.2  2007/01/12 14:53:53  n-ando
 * The create() function's signature was changed.
 * InPortConsumer base class is now abstruct class. It needs concrete class.
 *
 * Revision 1.1  2006/12/18 06:50:59  n-ando
 * The first commitment.
 *
 *
 */

#ifndef PublisherFactory_cpp
#define PublisherFactory_cpp

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>
#include <coil/Properties.h>
#include <rtm/InPortConsumer.h>
#include <rtm/PublisherFactory.h>
#include <rtm/PublisherNew.h>
#include <rtm/PublisherPeriodic.h>
#include <rtm/PublisherFlush.h>

/*!
 * @class PublisherFactoryTests class
 * @brief PublisherFactory test
 */
namespace PublisherFactory
{
  class NullConsumer : public RTC::InPortConsumer
  {
  public:
	
    NullConsumer() : RTC::InPortConsumer()
    {
    }
		
    virtual ~NullConsumer()
    {
    }
		
    virtual void push()
    {
    }
		
    virtual RTC::InPortConsumer* clone() const
    {
      return new NullConsumer();
    }
		
    virtual bool subscribeInterface(const SDOPackage::NVList&)
    {
      return true;
    }
		
    virtual void unsubscribeInterface(const SDOPackage::NVList&)
    {
    }
  };

  class PublisherFactoryTests
    : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(PublisherFactoryTests);
    CPPUNIT_TEST(test_create);
    CPPUNIT_TEST_SUITE_END();
		
  public:
	
    /*!
     * @brief Constructor
     */
    PublisherFactoryTests()
    {
    }
		
    /*!
     * @brief Destructor
     */
    ~PublisherFactoryTests()
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
     * @brief create()メソッドのテスト
     * 
     * - "dataport.subscription_type"を指定しない場合、デフォルトとしてPublisherNewが生成されるか？
     * - "dataport.subscription_type"に"New"を指定した場合、PublisherNewが生成されるか？
     * - "dataport.subscription_type"に"Periodic"を指定した場合、PublisherPeriodicが生成されるか？
     * - "dataport.subscription_type"に"Flush"を指定した場合、PublisherFlushが生成されるか？
     */
    void test_create()
    {
      RTC::PublisherFactory factory;
      NullConsumer consumer;
    	
      // (1) "dataport.subscription_type"を指定しない場合、デフォルトとしてPublisherNewが生成されるか？
      coil::Properties propDefault;
      RTC::PublisherBase* publisherDefault = factory.create(&consumer, propDefault);
      CPPUNIT_ASSERT(dynamic_cast<RTC::PublisherNew*>(publisherDefault) != 0);
    	
      // (2) "dataport.subscription_type"に"New"を指定した場合、PublisherNewが生成されるか？
      coil::Properties propNew;
      propNew.setProperty("dataport.subscription_type", "New");
      RTC::PublisherBase* publisherNew = factory.create(&consumer, propNew);
      CPPUNIT_ASSERT(dynamic_cast<RTC::PublisherNew*>(publisherNew) != 0);
      publisherNew->release();
    	
      // (3) "dataport.subscription_type"に"Periodic"を指定した場合、PublisherPeriodicが生成されるか？
      coil::Properties propPeriodic;
      propPeriodic.setProperty("dataport.subscription_type", "Periodic");
      RTC::PublisherBase* publisherPeriodic = factory.create(&consumer, propPeriodic);
      CPPUNIT_ASSERT(dynamic_cast<RTC::PublisherPeriodic*>(publisherPeriodic) != 0);
      publisherPeriodic->release();
    	
      // (4) "dataport.subscription_type"に"Flush"を指定した場合、PublisherFlushが生成されるか？
      coil::Properties propFlush;
      propFlush.setProperty("dataport.subscription_type", "Flush");
      RTC::PublisherBase* publisherFlush = factory.create(&consumer, propFlush);
      CPPUNIT_ASSERT(dynamic_cast<RTC::PublisherFlush*>(publisherFlush) != 0);
    }
  };
}; // namespace PublisherFactory

/*
 * Register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(PublisherFactory::PublisherFactoryTests);

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
#endif // PublisherFactory_cpp
