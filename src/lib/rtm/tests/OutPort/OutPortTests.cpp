// -*- C++ -*-
/*!
 * @file   OutPortTests.cpp
 * @brief  OutPort test class
 * @date   $Date: 2008/02/19 08:13:36 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * $Id$
 *
 */

/*
 * $Log: OutPortTests.cpp,v $
 * Revision 1.2  2008/02/19 08:13:36  arafune
 * Some tests were added and orthogonalized.
 *
 * Revision 1.1  2007/12/20 07:50:18  arafune
 * *** empty log message ***
 *
 * Revision 1.2  2006/12/02 18:52:54  n-ando
 * Some tests were added.
 *
 * Revision 1.1  2006/11/29 04:26:28  n-ando
 * CppUnit tests for OutPort.
 *
 *
 */

#ifndef OutPort_cpp
#define OutPort_cpp

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>

#include <rtm/OutPort.h>
#include <rtm/BufferBase.h>

#define WTIMEOUT_USEC 1000000
#define USEC_PER_SEC 1000000

/*!
 * @class OutPortTests class
 * @brief OutPort test
 */
namespace OutPort
{
  template <class DataType>
  class FullBuffer
    : public RTC::NullBuffer<DataType>
  {
  public:
    FullBuffer(long int length) {};
    virtual bool isFull() const
    {
      return true;
    }
  };
	
  template <class DataType>
  class OnOverflowMock
    : public RTC::OnOverflow<DataType>
  {
  public:
    virtual void operator()(const DataType& value)
    {
      m_value = value;
    }
    DataType m_value;
  };
	
  template <class DataType>
  class OnWriteMock
    : public RTC::OnWrite<DataType>
  {
  public:
    virtual void operator()(const DataType& value)
    {
      m_value = value;
    }
    DataType m_value;
  };
	
  class OnWriteConvertMock
    : public RTC::OnWriteConvert<double>
  {
  public:
    OnWriteConvertMock(double amplitude)
      : m_amplitude(amplitude) {}
    virtual double operator()(const double& value)
    {
      return m_amplitude * value;
    }
    double m_amplitude;
  };
	
  class OutPortTests
    : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(OutPortTests);
    CPPUNIT_TEST(test_write_and_read);
    CPPUNIT_TEST(test_write_OnWrite);
    CPPUNIT_TEST(test_write_OnWrite_full);
    CPPUNIT_TEST(test_write_OnOverflow);
    CPPUNIT_TEST(test_write_OnOverflow_not_full);
    CPPUNIT_TEST(test_write_OnWriteConvert);
    CPPUNIT_TEST(test_write_timeout);
    CPPUNIT_TEST_SUITE_END();
		
  public:
	
    /*!
     * @brief Constructor
     */
    OutPortTests()
    {
    }
		
    /*!
     * @brief Destructor
     */
    ~OutPortTests()
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
     * @brief write()メソッドとread()メソッドのテスト
     * 
     * - write()で書き込んだ値が、read()で正しく読み出されるか？
     */
    void test_write_and_read()
    {
      double bindValue;
      RTC::OutPort<double>* outPort
	= new RTC::OutPort<double>("OutPort", bindValue, 8);
			
      for (int i = 0; i < 100; ++i)
	{
	  double writeValue = i * 3.14159265;
	  CPPUNIT_ASSERT(outPort->write(writeValue));
				
	  double readValue;
	  CPPUNIT_ASSERT(outPort->read(readValue));
				
	  // write()で書き込んだ値が、read()で正しく読み出されるか？
	  CPPUNIT_ASSERT_EQUAL(writeValue, readValue);
	}
      delete outPort;
    }
		
    /*!
     * @brief write()メソッドのOnWriteコールバック呼出テスト
     * 
     * - あらかじめ設定されたOnWriteコールバックが正しく呼び出されるか？
     */
    void test_write_OnWrite()
    {
      double bindValue;
      RTC::OutPort<double>* outPort
	= new RTC::OutPort<double>("OutPort", bindValue, 8);
			
      OnWriteMock<double> onWrite;
      onWrite.m_value = 0;
      outPort->setOnWrite(&onWrite);
			
      // write()メソッドは成功するか？
      double writeValue = 3.14159265;
      CPPUNIT_ASSERT(outPort->write(writeValue));
			
      // あらかじめ設定されたOnWriteコールバックが正しく呼び出されたか？
      CPPUNIT_ASSERT_EQUAL(writeValue, onWrite.m_value);
      delete outPort;
    }
		
    /*!
     * @brief バッファフル時のwrite()メソッドのOnWriteコールバック呼出テスト
     * 
     * - あらかじめ設定されたOnWriteコールバックが正しく呼び出されるか？
     */
    void test_write_OnWrite_full()
    {
      double bindValue;
      RTC::OutPort<double, FullBuffer>* outPort
	= new RTC::OutPort<double, FullBuffer>("OutPort", bindValue, 8);
			
      OnWriteMock<double> onWrite;
      onWrite.m_value = 0;
      outPort->setOnWrite(&onWrite);
			
      // バッファフルによりwrite()メソッドは意図どおり失敗するか？
      double writeValue = 3.14159265;
      CPPUNIT_ASSERT(! outPort->write(writeValue));
			
      // あらかじめ設定されたOnWriteコールバックが正しく呼び出されたか？
      CPPUNIT_ASSERT_EQUAL(writeValue, onWrite.m_value);
      delete outPort;
    }
		
    /*!
     * @brief write()メソッドのOnOverflowコールバック呼出テスト
     * 
     * - OutPortに割り当てされたバッファがフルの場合に、あらかじめ設定されたOnOverflowコールバックが正しく呼び出されるか？
     */
    void test_write_OnOverflow()
    {
      // 常にフル状態であるバッファを用いてOutPortオブジェクトを生成する
      double bindValue;
      RTC::OutPort<double, FullBuffer>* outPort
	= new RTC::OutPort<double, FullBuffer>("OutPort", bindValue, 8);
			
      OnOverflowMock<double> onOverflow;
      onOverflow.m_value = 0;
      outPort->setOnOverflow(&onOverflow);

      // バッファフルによりwrite()メソッドは意図どおり失敗するか？
      double writeValue = 3.14159265;
      CPPUNIT_ASSERT(! outPort->write(writeValue));
			
      // OutPortに割り当てされたバッファがフルの場合に、あらかじめ設定されたOnOverflowコールバックが正しく呼び出されたか？
      CPPUNIT_ASSERT_EQUAL(writeValue, onOverflow.m_value);
      delete outPort;
    }

    /*!
     * @brief バッファフルでない時の、write()メソッドのOnOverflowコールバック呼出テスト
     * 
     * - バッファフルでない場合、OnOverflowコールバックが意図どおり未呼出のままか？
     */
    void test_write_OnOverflow_not_full()
    {
      double bindValue;
      RTC::OutPort<double>* outPort
	= new RTC::OutPort<double>("OutPort", bindValue, 8);

      OnOverflowMock<double> onOverflow;
      onOverflow.m_value = 0;
      outPort->setOnOverflow(&onOverflow);

      // write()メソッドは成功するか？
      double writeValue = 3.14159265;
      CPPUNIT_ASSERT(outPort->write(writeValue));
			
      // バッファフルでない場合、OnOverflowコールバックが意図どおり未呼出のままか？
      CPPUNIT_ASSERT_EQUAL((double) 0, onOverflow.m_value);
      delete outPort;
    }
		
    void test_write_OnWriteConvert()
    {
      double bindValue;
      RTC::OutPort<double>* outPort
	= new RTC::OutPort<double>("OutPort", bindValue, 8);
			
      double amplitude = 1.41421356;
      OnWriteConvertMock onWriteConvert(amplitude);
      outPort->setOnWriteConvert(&onWriteConvert);
			
      for (int i = 0; i < 100; ++i)
	{
	  double writeValue = i * 3.14159265;
	  CPPUNIT_ASSERT(outPort->write(writeValue));
				
	  double readValue;
	  CPPUNIT_ASSERT(outPort->read(readValue));
				
	  // write()で書き込んだ値が、read()で正しく読み出されるか？
	  double expectedValue = amplitude * writeValue;
	  CPPUNIT_ASSERT_EQUAL(expectedValue, readValue);
	}
      delete outPort;
    }
		
    /*!
     * @brief write()メソッドのタイムアウト処理テスト
     * 
     * - OutPortに割り当てされたバッファがフルの場合に、指定した時間どおりにwrite()メソッドがタイムアウトするか？
     * - OutPortに割り当てられたバッファがフルの場合に、write()メソッドが意図どおり失敗するか？
     */
    void test_write_timeout()
    {
      // 常にフル状態であるバッファを用いてOutPortオブジェクトを生成する
      double bindValue;
      RTC::OutPort<double, FullBuffer>* outPort
	= new RTC::OutPort<double, FullBuffer>("OutPort", bindValue, 8);
			
      // OutPortオブジェクトに対して、ブロッキングモードONを指定する
      outPort->setWriteBlock(true);
			
      // OutPortオブジェクトに対して、タイムアウト値を指定する
      outPort->setWriteTimeout(WTIMEOUT_USEC);
			
      timeval tm_pre;
      gettimeofday(&tm_pre, 0);
			
      for (int i = 0; i < 10; ++i) {
				
	double writeValue = i * 3.14159265;
				
	// OutPortに割り当てられたバッファがフルの場合に、write()メソッドが意図どおり失敗するか？
	CPPUNIT_ASSERT(! outPort->write(writeValue));
				
	// OutPortに割り当てされたバッファがフルの場合に、指定した時間どおりにwrite()メソッドがタイムアウトしているか？
	timeval tm_cur;
	gettimeofday(&tm_cur, 0);
				
	timeval tm_diff;
	timersub(&tm_cur, &tm_pre, &tm_diff);
				
	double interval = (double) tm_diff.tv_sec
	  + (double) tm_diff.tv_usec / USEC_PER_SEC;
					
	tm_pre = tm_cur;
				
	CPPUNIT_ASSERT_DOUBLES_EQUAL(
				     (double) WTIMEOUT_USEC / USEC_PER_SEC, interval,
				     0.1 * WTIMEOUT_USEC/USEC_PER_SEC);
      }
      delete outPort;
    }
		
  };
}; // namespace OutPort

/*
 * Register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(OutPort::OutPortTests);

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
#endif // OutPort_cpp
