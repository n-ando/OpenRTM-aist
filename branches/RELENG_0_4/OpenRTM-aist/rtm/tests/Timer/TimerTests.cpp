// -*- C++ -*-
/*!
 * @file   TimerTests.cpp
 * @brief  Timer test class
 * @date   $Date: 2008/01/31 05:33:29 $
 * 
 * Copyright (C) 2006
 *     Noriaki Ando
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 */

#ifndef Timer_cpp
#define Timer_cpp

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>

#include <string>
#include <sstream>
#include <rtm/Timer.h>

/*!
 * @class TimerTests class
 * @brief Timer test
 */
namespace Timer
{
  class TimerTests
    : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(TimerTests);
		
    CPPUNIT_TEST(test_registerListener);
    CPPUNIT_TEST(test_activate_multi_timers_continuously);
    CPPUNIT_TEST(test_activate_multi_timers_concurrently);
		
    CPPUNIT_TEST_SUITE_END();
		
  private:
    class Listener : public ListenerBase
    {
    public:
      Listener(const char* name = "", bool printMsg = false)
	: _name(name), _printMsg(printMsg), _count(0)
      {
      }
			
      virtual void invoke()
      {
	_count++;
				
	if (_printMsg) {
	  std::cout
	    << std::endl
	    << _name << ":invoked. (count = " << _count << ")"
	    << std::endl;
	}
      }
			
      const char* _name;
      bool _printMsg;
      int _count;
    };
		
  public:
    /*!
     * @brief Constructor
     */
    TimerTests()
    {
    }
		
    /*!
     * @brief Destructor
     */
    ~TimerTests()
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
     * @brief registerListener()メソッドのテスト
     * 
     * - タイマを起動し、あらかじめ登録されたリスナが意図どおりの時間間隔でコールバックされるか？
     * 
     */
    void test_registerListener()
    {
      TimeValue timerInterval(0, 100000); // 0.1 [sec]
      RTC::Timer timer(timerInterval);

      Listener listener;
      TimeValue listenerInterval(0, 1000000);
      timer.registerListener(&listener, listenerInterval);

      timer.start();
      sleep(10);
      timer.stop();

      // １秒に１回の呼出なので、１０回カウントされているはず。精度を考慮して、９〜１１回の範囲であることを確認する。
      CPPUNIT_ASSERT((9 <= listener._count) && (listener._count <= 11));
    }
		
    /*!
     * @brief 複数のタイマーを時間的に直列に動作させるテスト
     * 
     * - ２つのタイマーの動作が互いに干渉することなく、あらかじめ登録されたリスナが意図どおりの時間間隔でコールバックされるか？
     * 
     */
    void test_activate_multi_timers_continuously()
    {
      // １つめのタイマーを起動する
      TimeValue timerInterval1(0, 100000); // 0.1 [sec]
      RTC::Timer timer1(timerInterval1);

      Listener listener1("listener-1");
      TimeValue listenerInterval1(0, 1000000);
      timer1.registerListener(&listener1, listenerInterval1);

      timer1.start();
      sleep(10);
      timer1.stop();
			
      // ２つめのタイマーを起動する
      TimeValue timerInterval2(0, 100000); // 0.1 [sec]
      RTC::Timer timer2(timerInterval2);

      Listener listener2("listener-2");
      TimeValue listenerInterval2(0, 1000000);
      timer2.registerListener(&listener2, listenerInterval2);

      timer2.start();
      sleep(10);
      timer2.stop();

      // １秒に１回の呼出なので、１０回カウントされているはず。精度を考慮して、９〜１１回の範囲であることを確認する。
      CPPUNIT_ASSERT((9 <= listener1._count) && (listener1._count <= 11));
      CPPUNIT_ASSERT((9 <= listener2._count) && (listener2._count <= 11));
    }
		
    /*!
     * @brief 複数のタイマーを時間的に並列に動作させるテスト
     * 
     * - ２つのタイマーの動作が互いに干渉することなく、あらかじめ登録されたリスナが意図どおりの時間間隔でコールバックされるか？
     * 
     */
    void test_activate_multi_timers_concurrently()
    {
      // １つめのタイマーを生成する
      TimeValue timerInterval1(0, 100000); // 0.1 [sec]
      RTC::Timer timer1(timerInterval1);

      Listener listener1("listener-1");
      TimeValue listenerInterval1(0, 1000000);
      timer1.registerListener(&listener1, listenerInterval1);

      // ２つめのタイマーを生成する
      TimeValue timerInterval2(0, 100000); // 0.1 [sec]
      RTC::Timer timer2(timerInterval2);

      Listener listener2("listener-2");
      TimeValue listenerInterval2(0, 1000000);
      timer2.registerListener(&listener2, listenerInterval2);

      // ２つのタイマーを同時スタート・ストップさせる
      timer1.start();
      timer2.start();
      sleep(10);
      timer1.stop();
      timer2.stop();

      // １秒に１回の呼出なので、１０回カウントされているはず。精度を考慮して、９〜１１回の範囲であることを確認する。
      CPPUNIT_ASSERT((9 <= listener1._count) && (listener1._count <= 11));
      CPPUNIT_ASSERT((9 <= listener2._count) && (listener2._count <= 11));
    }
		
  };
}; // namespace Timer

/*
 * Register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(Timer::TimerTests);

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
#endif // Timer_cpp
