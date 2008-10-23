// -*- C++ -*-
/*!
 * @file   PublisherFlushTests.cpp
 * @brief  PublisherFlush test class
 * @date   $Date: 2008/01/23 09:20:42 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * $Id$
 *
 */

/*
 * $Log: PublisherFlushTests.cpp,v $
 * Revision 1.2  2008/01/23 09:20:42  arafune
 * modified some tests.
 *
 * Revision 1.1  2007/12/20 07:50:18  arafune
 * *** empty log message ***
 *
 * Revision 1.2  2007/01/12 14:54:32  n-ando
 * The constructor's signature was changed.
 * InPortConsumer base class is now abstruct class. It needs concrete class.
 *
 * Revision 1.1  2006/12/18 06:51:31  n-ando
 * The first commitment.
 *
 *
 */

#ifndef PublisherFlush_cpp
#define PublisherFlush_cpp

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>

#include <coil/Properties.h>
#include <rtm/InPortConsumer.h>
#include <rtm/PublisherFlush.h>

#include <sys/time.h>
/*!
 * @class PublisherFlushTests class
 * @brief PublisherFlush test
 */
namespace PublisherFlush
{
  class MockConsumer : public RTC::InPortConsumer
  {
  public:
	
    MockConsumer(long sleepTick = 0L)
      : RTC::InPortConsumer(), _sleepTick(sleepTick), _count(0)
    {
      resetDelayStartTime();
    }
		
    virtual ~MockConsumer() {}
		
    virtual void push()
    {
      timeval now;
      gettimeofday(&now, NULL);
			
      long delayTick =
	(now.tv_sec - _delayStartTime.tv_sec) * 1000000
	+ (now.tv_usec - _delayStartTime.tv_usec);
			
      _delayTicks.push_back(delayTick);
			
      resetDelayStartTime();

      usleep(_sleepTick);
      _count++;

      setReturnStartTime();
    }
		
    virtual RTC::InPortConsumer* clone() const
    {
      MockConsumer* clone = new MockConsumer();
      clone->_sleepTick = _sleepTick;
      return clone;
    }

    virtual bool subscribeInterface(const SDOPackage::NVList&)
    {
      return true;
    }
		
    virtual void unsubscribeInterface(const SDOPackage::NVList&)
    {
      return;
    }
		
    virtual void setDelayStartTime()
    {
      if (_delayStartTime.tv_sec == 0 && _delayStartTime.tv_usec == 0)
	{
	  gettimeofday(&_delayStartTime, NULL);
	}
    }
		
    virtual void recordReturnTick()
    {
      timeval now;
      gettimeofday(&now, NULL);
			
      long returnTick =
	(now.tv_sec - _returnStartTime.tv_sec) * 1000000
	+ (now.tv_usec - _returnStartTime.tv_usec);
			
      _returnTicks.push_back(returnTick);
    }
		
    virtual const std::vector<long>& getDelayTicks()
    {
      return _delayTicks;
    }
		
    virtual const std::vector<long>& getReturnTicks()
    {
      return _returnTicks;
    }
		
    virtual int getCount() const
    {
      return _count;
    }
		
  protected:
	
    long _sleepTick;
    timeval _delayStartTime;
    timeval _returnStartTime;
    std::vector<long> _delayTicks;
    std::vector<long> _returnTicks;
    int _count;
	
  protected:

    virtual void resetDelayStartTime()
    {
      _delayStartTime.tv_sec = 0;
      _delayStartTime.tv_usec = 0;
    }
		
    virtual void setReturnStartTime()
    {
      gettimeofday(&_returnStartTime, NULL);
    }
		
    virtual void resetReturnStartTime()
    {
      _returnStartTime.tv_sec = 0;
      _returnStartTime.tv_usec = 0;
    }
  };

  class PublisherFlushTests
    : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(PublisherFlushTests);
		
    CPPUNIT_TEST(test_update_immediacy);
		
    CPPUNIT_TEST_SUITE_END();
		
  private:
		
  public:
	
    /*!
     * @brief Constructor
     */
    PublisherFlushTests()
    {
    }
		
    /*!
     * @brief Destructor
     */
    ~PublisherFlushTests()
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
      sleep(1);
    }
		
    /*!
     * @brief update()メソッド呼出周辺の即時性のテスト
     * 
     * - Publisherのupdate()メソッド呼出後、所定時間内にConsumerのpush()メソッドが呼び出されるか？
     * - Consumerのpush()メソッド終了後、所定時間内にPublihserのupdate()メソッド呼出から復帰するか？
     * 
     * @attention リアルタイム性が保証されているわけでもなく、仕様上も呼出までの時間を明記しているわけではないので、ここでの所定時間はテスト作成者の主観によるものに過ぎない。
     */
    void test_update_immediacy()
    {
      long sleepTick = 100000; // 0.1 [sec]
			
      MockConsumer* consumer = new MockConsumer(sleepTick);
      coil::Properties prop;
      RTC::PublisherFlush publisher(consumer, prop);
			
      for (int i = 0; i < 10; i++)
	{
	  consumer->setDelayStartTime();
	  publisher.update();
	  consumer->recordReturnTick();
	}
			
      long permissibleDelayTick = 100000; // 0.1 [sec]
      const std::vector<long>& delayTicks = consumer->getDelayTicks();
      for (std::vector<long>::size_type i = 0; i < delayTicks.size(); i++)
	{
	  CPPUNIT_ASSERT(delayTicks[i] < permissibleDelayTick);
	}
			
      long permissibleReturnTick = 100000; // 0.1 [sec]
      const std::vector<long>& returnTicks = consumer->getReturnTicks();
      for (std::vector<long>::size_type i = 0; i < returnTicks.size(); i++)
	{
	  CPPUNIT_ASSERT(returnTicks[i] < permissibleReturnTick);
	}
    }
		
  };
}; // namespace PublisherFlush

/*
 * Register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(PublisherFlush::PublisherFlushTests);

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
#endif // PublisherFlush_cpp
