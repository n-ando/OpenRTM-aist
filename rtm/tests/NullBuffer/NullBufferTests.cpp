// -*- C++ -*-
/*!
 * @file   NullBufferTests.cpp
 * @brief  NullBuffer test class
 * @date   $Date: 2008/01/24 01:52:05 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * $Id$
 *
 */

/*
 * $Log: NullBufferTests.cpp,v $
 * Revision 1.6  2008/01/24 01:52:05  tsakamoto
 * *** empty log message ***
 *
 * Revision 1.5  2007/12/26 02:40:08  arafune
 * *** empty log message ***
 *
 * Revision 1.4  2007/12/26 01:57:06  arafune
 * *** empty log message ***
 *
 * Revision 1.3  2007/12/25 11:45:47  arafune
 * *** empty log message ***
 *
 * Revision 1.2  2007/12/25 11:36:48  arafune
 * *** empty log message ***
 *
 * Revision 1.1  2007/12/20 07:50:18  arafune
 * *** empty log message ***
 *
 * Revision 1.1  2006/12/02 18:54:50  n-ando
 * *** empty log message ***
 *
 *
 */

#ifndef NullBuffer_cpp
#define NullBuffer_cpp

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>
#include <iostream>
#include <rtm/BufferBase.h>

namespace NullBuffer
{
  struct Data
  {
    int    int_data;
    double double_data;
  };

  template <class DataType>
  class MyBuffer
    : public RTC::NullBuffer<DataType>
  {
  public:
    virtual void put(const DataType& data)
    {
      RTC::NullBuffer<DataType>::put(data);
    }

    virtual const DataType& get()
    {
      return RTC::NullBuffer<DataType>::get();
    }

    virtual DataType& getRef()
    {
      return RTC::NullBuffer<DataType>::getRef();
    }
  };

  /*!
   * @class NullBufferTests class
   * @brief NullBuffer test
   */
  class NullBufferTests
    : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(NullBufferTests);
    CPPUNIT_TEST(test_wr_int);
    CPPUNIT_TEST(test_wr_char);
    CPPUNIT_TEST(test_wr_struct);
    CPPUNIT_TEST(test_isFull);
    CPPUNIT_TEST(test_isFull_NeverFull);
    CPPUNIT_TEST(test_isEmpty);
    CPPUNIT_TEST(test_isEmpty_NeverEmpty);
    CPPUNIT_TEST(test_pg_int);
    CPPUNIT_TEST(test_pg_char);
    CPPUNIT_TEST(test_put_struct);
    CPPUNIT_TEST_SUITE_END();
  
  private:
    RTC::BufferBase<int>*  m_intBuf;
    RTC::BufferBase<char>* m_charBuf;
    RTC::BufferBase<Data>* m_dataBuf;

  public:
    /*!
     * @brief Constructor
     */
    NullBufferTests()
    {
      m_intBuf  = new MyBuffer<int>();
      m_charBuf = new MyBuffer<char>();
      m_dataBuf = new MyBuffer<Data>();
    }

    /*!
     * @brief Destructor
     */
    ~NullBufferTests()
    {
      delete m_intBuf;
      delete m_charBuf;
      delete m_dataBuf;
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
     * @brief int型データのwrite/readチェック
     *
     * - int型データを書き込めるか？
     * - 書き込んだint型データ正常に読み出せるか？
     */
    void test_wr_int()
    {
      for (int i = 0; i < 100; ++i)
	{
	  // 書き込みが成功することを確認する
	  CPPUNIT_ASSERT(m_intBuf->write(i));

	  // 書き込んだデータを読み出して、書き込んだデータと一致することを確認する
	  int intvar;
	  CPPUNIT_ASSERT(m_intBuf->read(intvar));
	  CPPUNIT_ASSERT_EQUAL(i, intvar);
	}
    }

    /*!
     * @brief char型データのwrite/readチェック
     *
     * - char型データを書き込めるか？
     * - 書き込んだchar型データ正常に読み出せるか？
     */
    void test_wr_char()
    {
      for (int i = 0; i < 100; ++i)
	{
	  // 書き込みが成功することを確認する
	  CPPUNIT_ASSERT(m_charBuf->write(i));

	  // 書き込んだデータを読み出して、書き込んだデータと一致することを確認する
	  char charvar;
	  CPPUNIT_ASSERT(m_charBuf->read(charvar));
	  CPPUNIT_ASSERT_EQUAL(i, static_cast<int>(charvar));
	}
    }

    /*!
     * @brief オブジェクトデータのwrite/readチェック
     *
     * - オブジェクトデータを書き込めるか？
     * - 書き込んだオブジェクトデータ正常に読み出せるか？
     */
    void test_wr_struct()
    {
      for (int i = 0; i < 100; ++i)
	{
	  Data data;
	  data.int_data = i;
	  data.double_data = i / 3.141592653589793238462643383279;

	  // 書き込みが成功することを確認する
	  CPPUNIT_ASSERT(m_dataBuf->write(data));

	  // 書き込んだデータを読み出して、書き込んだデータと一致することを確認する
	  Data dvar;
	  CPPUNIT_ASSERT(m_dataBuf->read(dvar));
	  CPPUNIT_ASSERT_EQUAL(data.int_data, dvar.int_data);
	  CPPUNIT_ASSERT_EQUAL(data.double_data, dvar.double_data);
	}
    }

    /*!
     * @brief isFull()メソッド　初期状態のチェック
     *
     * - 初期状態でフルではないか？
     */
    void test_isFull()
    {
      CPPUNIT_ASSERT(!m_intBuf->isFull());
      CPPUNIT_ASSERT(!m_charBuf->isFull());
      CPPUNIT_ASSERT(!m_dataBuf->isFull());
    }

    /*!
     * @brief isFull()メソッド　バッファ長超えチェック
     *
     * - バッファ長さを超える書き込みを行っても決してフルにならないか？
     */
    void test_isFull_NeverFull()
    {
      // バッファ長さを越えるデータを書き込む
      for (int i = 0; i < m_intBuf->length() + 100; i++)
	{
	  m_intBuf->write(12345 + i);
	}
	        
      // フルになっていないことを確認する
      CPPUNIT_ASSERT(!m_intBuf->isFull());
    }
	    
    /*!
     * @brief isEmpty()メソッド　初期状態のチェック
     *
     * - 初期状態で空ではないか？
     */
    void test_isEmpty()
    {
      CPPUNIT_ASSERT(!m_intBuf->isEmpty());
      CPPUNIT_ASSERT(!m_charBuf->isEmpty());
      CPPUNIT_ASSERT(!m_dataBuf->isEmpty());
    }

    /*!
     * @brief isEmpty()メソッド　バッファ超えチェック
     *
     * - バッファ長さを越えるデータの読み込みを行っても空にならないか？
     */
    void test_isEmpty_NeverEmpty()
    {
      // バッファ長を超えるデータを読み出す
      int data;
      for (int i = 0; i < m_intBuf->length() + 100; i++)
	{
	  m_intBuf->read(data);
	}
	        
      // 空ではないことを確認する
      CPPUNIT_ASSERT(!m_intBuf->isEmpty());
    }

    /*!
     * @brief int型データのput/getチェック
     *
     * - 書き込んだデータを正常に取得できるか？
     */
    void test_pg_int()
    {
      MyBuffer<int>* buf = dynamic_cast<MyBuffer<int>*>(m_intBuf);
			
      for (int i = 0; i < 100; ++i)
	{
	  buf->put(i);
	  CPPUNIT_ASSERT_EQUAL(i, buf->get());
	}
    }

    /*!
     * @brief char型データのput/getチェック
     *
     * - 書き込んだデータを正常に取得できるか？
     */
    void test_pg_char()
    {
      MyBuffer<char>* buf = dynamic_cast<MyBuffer<char>*>(m_charBuf);
			
      for (int i = 0; i < 100; ++i)
	{
	  buf->put(i);
	  CPPUNIT_ASSERT_EQUAL(i, static_cast<int>(buf->get()));
	}
    }

    /*!
     * @brief オブジェクト型データのput/getチェック</p
     *
     * - 書き込んだデータを正常に取得できるか？
     */
    void test_put_struct()
    {
      MyBuffer<Data>* buf = dynamic_cast<MyBuffer<Data>*>(m_dataBuf);
			
      for (int i = 0; i < 100; ++i)
	{
	  Data data;
	  data.int_data = i;
	  data.double_data = i / 3.141592653589793238462643383279;

	  buf->put(data);

	  CPPUNIT_ASSERT_EQUAL(data.int_data, buf->get().int_data);
	  CPPUNIT_ASSERT_EQUAL(data.double_data, buf->get().double_data);
	} 
    }
		
  };
}; // namespace NullBuffer

/*
 * Register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(NullBuffer::NullBufferTests);

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
#endif // NullBuffer_cpp
