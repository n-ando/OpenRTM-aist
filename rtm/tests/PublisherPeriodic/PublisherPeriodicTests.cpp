// -*- C++ -*-
/*!
 * @file   PublisherPeriodicTests.cpp
 * @brief  PublisherPeriodic test class
 * @date   $Date: 2008/01/28 13:52:19 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * $Id$
 *
 */

/*
 * $Log: PublisherPeriodicTests.cpp,v $
 * Revision 1.2  2008/01/28 13:52:19  arafune
 * Some tests were added.
 *
 * Revision 1.1  2007/12/20 07:50:17  arafune
 * *** empty log message ***
 *
 * Revision 1.2  2007/01/12 14:54:45  n-ando
 * The constructor's signature was changed.
 * InPortConsumer base class is now abstruct class. It needs concrete class.
 *
 * Revision 1.1  2006/12/18 06:51:55  n-ando
 * The first commitment.
 *
 *
 */

#ifndef PublisherPeriodic_cpp
#define PublisherPeriodic_cpp

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>

#include <iostream>
#include <rtm/Properties.h>
#include <rtm/InPortConsumer.h>
#include <rtm/PublisherPeriodic.h>


/*!
 * @class PublisherPeriodicTests class
 * @brief PublisherPeriodic test
 */
namespace PublisherPeriodic
{
  class MockConsumer : public RTC::InPortConsumer
  {
  public:
	
    MockConsumer() : RTC::InPortConsumer()
    {
      clearLastTime();
    }
		
    virtual ~MockConsumer() {}
		
    virtual void push()
    {
      timeval now;
      gettimeofday(&now, NULL);
			
      if (! isLastTimeCleared())
	{
	  long interval =
	    (now.tv_sec - _lastTime.tv_sec) * 1000000
	    + (now.tv_usec - _lastTime.tv_usec);
				
	  _intervalTicks.push_back(interval);
	}
			
      _lastTime = now;
    }
		
    virtual RTC::InPortConsumer* clone() const
    {
      MockConsumer* clone = new MockConsumer();
      copy(_intervalTicks.begin(), _intervalTicks.end(), clone->_intervalTicks.begin());
      clone->_lastTime = _lastTime;
			
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
	
    virtual const std::vector<long>& getIntervalTicks() const
    {
      return _intervalTicks;
    }
		
    virtual int getCount() const
    {
      return static_cast<int>(_intervalTicks.size());
    }
		
  private:
	
    std::vector<long> _intervalTicks;
    timeval _lastTime;
		
  private:
	
    void clearLastTime()
    {
      _lastTime.tv_sec = 0;
      _lastTime.tv_usec = 0;
    }
		
    bool isLastTimeCleared()
    {
      return (_lastTime.tv_sec == 0) && (_lastTime.tv_usec == 0);
    }
  };
	
  class CounterConsumer : public RTC::InPortConsumer
  {
  public:
	
    CounterConsumer(CounterConsumer* component = NULL)
      : RTC::InPortConsumer(), _count(0), _component(component)	{}
		
    virtual ~CounterConsumer() {}
		
    virtual void push()
    {
      _count++;
			
      if (_component != NULL)
	{
	  _component->push();
	}
    }
		
    virtual RTC::InPortConsumer* clone() const
    {
      CounterConsumer* clone = new CounterConsumer();
      clone->_count = _count;
      clone->_component = _component;
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

    virtual int getCount() const
    {
      return _count;
    }
	
  private:
	
    int _count;
    CounterConsumer* _component;
  };

  class PublisherPeriodicTests
    : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(PublisherPeriodicTests);
		
    // CPPUNIT_TEST(test_destructor);
    // CPPUNIT_TEST(test_interval_accuracy);
    // CPPUNIT_TEST(test_release);
		
    CPPUNIT_TEST_SUITE_END();
		
  public:
	
    /*!
     * @brief Constructor
     */
    PublisherPeriodicTests()
    {
    }
		
    /*!
     * @brief Destructor
     */
    ~PublisherPeriodicTests()
    {
    }
		
    /*!
     * @brief Test initialization
     */
    virtual void setUp()
    {
      usleep(1000000);
    }
    
    /*!
     * @brief Test finalization
     */
    virtual void tearDown()
    { 
    }
		
    /*!
     * @brief デストラクタのテスト
     * 
     * - デストラクタ呼出により、release()メソッドを呼び出さずともPublisherの動作が問題なく停止するか？
     */
    void test_destructor()
    {
      CounterConsumer* consumer1 = new CounterConsumer();

      { // Publisherのインスタンススコープ開始
	CounterConsumer* consumer2 = new CounterConsumer(consumer1);
	RTC::Properties prop;
	prop.setProperty("dataport.push_rate", "10"); // 10 [Hz]
	RTC::PublisherPeriodic publisher(consumer2, prop);
	// 5 [sec]だけ動作させる
	usleep(5000000);
				
      } // デストラクタを呼び出す（スコープを終了させる）
			
      usleep(1000000); // 完全停止するまで待つ
			
      // この時点での呼出回数を記録する
      int countReleased = consumer1->getCount();
			
      // さらにConsumerがコールバックされ得る時間を与える
      usleep(5000000); // 5 [sec]
			
      // この時点での呼出回数を取得し、先に記録しておいた回数から変化がない
      // （つまり、Publisherの動作が停止している）ことを確認する
      int countSleeped = consumer1->getCount();
      CPPUNIT_ASSERT_EQUAL(countReleased, countSleeped);
    }
		
    /*!
     * @brief release()メソッドのテスト
     * 
     * - release()メソッド呼出によりPublisherの動作が停止するか？
     */
    void test_release()
    {
      CounterConsumer* consumer = new CounterConsumer();
      RTC::Properties prop;
      prop.setProperty("dataport.push_rate", "10"); // 10 [Hz]
      RTC::PublisherPeriodic publisher(consumer, prop);
			
      // 5 [sec]だけ動作させる
      usleep(5000000);
			
      // Publisherの動作を停止させる
      publisher.release();
      usleep(1000000); // 完全停止するまで待つ
			
      // この時点での呼出回数を記録する
      int countReleased = consumer->getCount();
			
      // さらにConsumerがコールバックされ得る時間を与える
      usleep(5000000); // 5 [sec]
			
      // この時点での呼出回数を取得し、先に記録しておいた回数から変化がない
      // （つまり、Publisherの動作が停止している）ことを確認する
      int countSleeped = consumer->getCount();
      CPPUNIT_ASSERT_EQUAL(countReleased, countSleeped);
    }
		
    /*!
     * @brief PublisherによるConsumer呼出間隔精度のテスト
     * 
     * - Publisherに指定した時間間隔で、正しくConsumerがコールバックされるか？
     */
    void test_interval_accuracy()
    {
      MockConsumer* consumer = new MockConsumer();
      RTC::Properties prop;
      prop.setProperty("dataport.push_rate", "10"); // 10 [Hz]
      RTC::PublisherPeriodic publisher(consumer, prop);
			
      // 5 [sec]だけ動作させる
      usleep(5000000);
			
      // Publisherの動作を停止させる
      publisher.release();
      usleep(1000000); // 完全停止するまで待つ
			
      // 指定した時間間隔で正しくConsumerがコールバックされているか？
      long permissibleTickMin = static_cast<long>(100000 * 0.9);
      long permissibleTickMax = static_cast<long>(100000 * 1.1);
      const std::vector<long> intervalTicks = consumer->getIntervalTicks();
      CPPUNIT_ASSERT(intervalTicks.size() > 0);

      for (std::vector<long>::size_type i = 0; i < intervalTicks.size(); i++)
	{
	  long tick = intervalTicks[i];
	  CPPUNIT_ASSERT((permissibleTickMin <= tick) && (tick <= permissibleTickMax));
	}
    }
  };
}; // namespace PublisherPeriodic

/*
 * Register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(PublisherPeriodic::PublisherPeriodicTests);

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
#endif // PublisherPeriodic_cpp
