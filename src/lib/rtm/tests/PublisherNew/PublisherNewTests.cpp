// -*- C++ -*-
/*!
 * @file   PublisherNewTests.cpp
 * @brief  PublisherNew test class
 * @date   $Date: 2008/01/23 09:19:31 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * $Id$
 *
 */

/*
 * $Log: PublisherNewTests.cpp,v $
 * Revision 1.2  2008/01/23 09:19:31  arafune
 * added some tests.
 *
 * Revision 1.1  2007/12/20 07:50:16  arafune
 * *** empty log message ***
 *
 * Revision 1.2  2007/01/12 14:54:39  n-ando
 * The constructor's signature was changed.
 * InPortConsumer base class is now abstruct class. It needs concrete class.
 *
 * Revision 1.1  2006/12/18 06:51:43  n-ando
 * The first commitment.
 *
 *
 */

#ifndef PublisherNew_cpp
#define PublisherNew_cpp

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>

#include <coil/Properties.h>
#include <rtm/InPortConsumer.h>
#include <rtm/PublisherNew.h>
#include <coil/Time.h>


/*!
 * @class PublisherNewTests class
 * @brief PublisherNew test
 */
namespace PublisherNew
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
      coil::usleep(_sleepTick);
			
      timeval now;
      coil::gettimeofday(&now, NULL);
			
      long delayTick =
	(now.tv_sec - _delayStartTime.tv_sec) * 1000000
	+ (now.tv_usec - _delayStartTime.tv_usec);
			
      _delayTicks.push_back(delayTick);
			
      resetDelayStartTime();
			
      _count++;
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
		
    virtual void resetDelayStartTime()
    {
      _delayStartTime.tv_sec = 0;
      _delayStartTime.tv_usec = 0;
    }
		
    virtual void setDelayStartTime()
    {
      if (_delayStartTime.tv_sec == 0 && _delayStartTime.tv_usec == 0)
	{
	  coil::gettimeofday(&_delayStartTime, NULL);
	}
    }
		
    virtual const std::vector<long>& getDelayTicks()
    {
      return _delayTicks;
    }
	
    virtual int getCount() const
    {
      return _count;
    }
		
  protected:
	
    long _sleepTick;
    timeval _delayStartTime;
    std::vector<long> _delayTicks;
    int _count;
  };
	
  class PublisherNewTests
    : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(PublisherNewTests);

    CPPUNIT_TEST(test_update_large_interval);
    CPPUNIT_TEST(test_update_small_interval);
    CPPUNIT_TEST(test_release);

    CPPUNIT_TEST_SUITE_END();
		
  private:

  public:
    /*!
     * @brief Constructor
     */
    PublisherNewTests()
    {
    }
		
    /*!
     * @brief Destructor
     */
    ~PublisherNewTests()
    {
    }
		
    /*!
     * @brief Test initialization
     */
    virtual void setUp()
    {
      coil::usleep(1000000);
    }
		
    /*!
     * @brief Test finalization
     */
    virtual void tearDown()
    { 
    }
		
    /*!
     * @brief update()メソッドのテスト
     * 
     * - 「Publisherのupdate()メソッド呼出間隔」>「Consumerのpush()メソッド処理時間」の場合に、update()呼出からpush()呼出までの時間間隔が、所定時間内に収まっているか？
     * 
     * @attention リアルタイム性が保証されているわけでもなく、仕様上も呼出までの時間を明記しているわけではないので、ここでの所定時間はテスト作成者の主観によるものに過ぎない。
     */
    void test_update_large_interval()
    {
      long sleepTick = 100000; // 0.1[sec]
      long intervalTick = sleepTick * 10;
			
      MockConsumer* consumer = new MockConsumer(sleepTick);
      coil::Properties prop;
      RTC::PublisherNew publisher(consumer, prop);
			
      for (int i = 0; i < 10; i++)
	{
	  consumer->setDelayStartTime();
	  publisher.update();
	  coil::usleep(intervalTick);
	}
			
      // Consumer呼出が完了するであろうタイミングまで待つ
      coil::usleep(5000000); // 5 [sec]
			
      // update()呼出からpush()呼出までの時間間隔が、所定時間内に収まっているか？
      // （リアルタイム性が保証されているわけでもなく、仕様上も呼出までの時間を明記しているわけではないので、
      // ここでの所定時間はテスト作成者の主観によるものに過ぎない。）
      long permissibleDelay = sleepTick + 100000;
      const std::vector<long>& delayTicks = consumer->getDelayTicks();
      for (std::vector<long>::size_type i = 0; i < delayTicks.size(); i++)
	{
	  //std::cout << "delay tick = " << delayTicks[i] << std::endl;
	  CPPUNIT_ASSERT(delayTicks[i] < permissibleDelay);
	}
      publisher.release();
    }
		
    /*!
     * @brief update()メソッドのテスト
     * 
     * - 「Publisherのupdate()メソッド呼出間隔」<「Consumerのpush()メソッド処理時間」の場合に、update()呼出が溜ってしまうことなく、update()呼出からpush()呼出までの時間間隔が、所定時間内に収まっているか？
     * 
     * @attention リアルタイム性が保証されているわけでもなく、仕様上も呼出までの時間を明記しているわけではないので、ここでの所定時間はテスト作成者の主観によるものに過ぎない。
     */
    void test_update_small_interval()
    {
      long sleepTick = 100000; // 0.1[sec]
      long intervalTick = sleepTick / 10;
			
      MockConsumer* consumer = new MockConsumer(sleepTick);
      coil::Properties prop;
      RTC::PublisherNew publisher(consumer, prop);
			
      for (int i = 0; i < 1000; i++)
	{
	  consumer->setDelayStartTime();
	  publisher.update();
	  coil::usleep(intervalTick);
	}
			
      // Consumer呼出が完了するであろうタイミングまで待つ
      coil::usleep(5000000); // 5 [sec]
			
      // update()呼出からpush()呼出までの時間間隔が、所定時間内に収まっているか？
      // （リアルタイム性が保証されているわけでもなく、仕様上も呼出までの時間を明記しているわけではないので、
      // ここでの所定時間はテスト作成者の主観によるものに過ぎない。）
      long permissibleDelay = sleepTick + 100000;
      const std::vector<long>& delayTicks = consumer->getDelayTicks();
      for (std::vector<long>::size_type i = 0; i < delayTicks.size(); i++)
	{
	  //std::cout << "delay tick = " << delayTicks[i] << std::endl;
	  CPPUNIT_ASSERT(delayTicks[i] < permissibleDelay);
	}
      publisher.release();
    }
		
    /*!
     * @brief release()メソッドのテスト
     * 
     * - release()メソッド呼出によりPublisherの動作を確実に停止できるか？
     */
    void test_release()
    {
      MockConsumer* consumer = new MockConsumer(1000000); // 1 [sec]
      coil::Properties prop;
      RTC::PublisherNew publisher(consumer, prop);
			
      // update()を呼出して、Consumerを呼び出させる
      publisher.update();
      coil::usleep(3000000); // Consumerを呼出す時間を与える
      publisher.release();
			
      CPPUNIT_ASSERT_EQUAL(1, consumer->getCount());
			
      // 再度update()を呼出し、Consumerを呼出しうる時間を与える。
      // （実際には、前段のrelease()によりPublisherが停止済みであり、
      // update()呼出は何ら影響を与えないことを予期している。）
      publisher.update();
      coil::usleep(3000000);

      // Consumer呼出回数が変わっていないこと、つまりPublisherの動作が停止していることを確認する
      CPPUNIT_ASSERT_EQUAL(1, consumer->getCount());
    }
		
  };
}; // namespace PublisherNew

/*
 * Register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(PublisherNew::PublisherNewTests);

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
#endif // PublisherNew_cpp
