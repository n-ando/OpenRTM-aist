// -*- C++ -*-
/*!
 * @file   RingBufferTests.cpp
 * @brief  RingBuffer test class
 * @date   $Date: 2008/01/24 01:52:14 $
 * @author Shinji Kurihara
 *         Noriaki Ando <n-ando@aist.go.jp>
 * 
 * Copyright (C) 2006
 *     Noriaki Ando
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id$
 *
 */

/*
 * $Log: RingBufferTests.cpp,v $
 * Revision 1.3  2008/01/24 01:52:14  tsakamoto
 * *** empty log message ***
 *
 * Revision 1.2  2008/01/11 11:27:11  arafune
 * *** empty log message ***
 *
 * Revision 1.1  2007/12/20 07:50:17  arafune
 * *** empty log message ***
 *
 * Revision 1.2  2006/12/02 18:53:08  n-ando
 * Some tests were added.
 *
 * Revision 1.1  2006/11/27 08:37:03  n-ando
 * TestSuites are devided into each directory.
 *
 *
 */

#ifndef RingBuffer_cpp
#define RingBuffer_cpp

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>

#include <string>
#include <sstream>
#include <rtm/RingBuffer.h>

//#define DEBUG

namespace RingBuffer
{
  /*!
   * @class RingBufferTests class
   * @brief RingBuffer test
   */
  class RingBufferTests
    : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(RingBufferTests);
		
    CPPUNIT_TEST(test_length);
    CPPUNIT_TEST(test_isFull);
    CPPUNIT_TEST(test_isEmpty);
    CPPUNIT_TEST(test_init);
    CPPUNIT_TEST(test_write_read);
    CPPUNIT_TEST(test_write_read_with_small_length);
    CPPUNIT_TEST(test_isNew);
		
    CPPUNIT_TEST_SUITE_END();
		
  private:
		
  public:
    /*!
     * @brief Constructor
     */
    RingBufferTests()
    {
    }
		
    /*!
     * @brief Destructor
     */
    ~RingBufferTests()
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
     * @brief length()メソッドのテスト
     * 
     * - コンストラクタで指定されたバッファ長が正しく取得できるか？
     */
    void test_length()
    {
      RTC::RingBuffer<int> buff(123);
      CPPUNIT_ASSERT_EQUAL((long int) 123, buff.length());
    }

    /*!
     * @brief isEmpty()メソッドのテスト
     * 
     * - バッファ初期化直後、空ではないと判定されるか？
     * - 最後にデータが読み取られた後、新しいデータが書き込みされていない場合、空と判定されるか？
     * - 最後にデータが読み取られた後、新しいデータが書き込みされた場合、空ではないと判定されるか？
     */
    void test_isEmpty()
    {
      long int length = 10;
      RTC::RingBuffer<int> buff(length);
			
      // (1) バッファ初期化直後、空ではないと判定されるか？
      int initialValue = 12345;
      buff.init(initialValue);
      CPPUNIT_ASSERT_EQUAL(false, buff.isEmpty());			
			
      // (2) 最後にデータが読み取られた後、新しいデータが書き込みされていない場合、空と判定されるか？
      int readValue;
      CPPUNIT_ASSERT_EQUAL(true, buff.read(readValue));
      CPPUNIT_ASSERT_EQUAL(true, buff.isEmpty());
			
      // (3) 最後にデータが読み取られた後、新しいデータが書き込みされた場合、空ではないと判定されるか？
      int writeValue = 98765;
      CPPUNIT_ASSERT_EQUAL(true, buff.write(writeValue));
      CPPUNIT_ASSERT_EQUAL(false, buff.isEmpty());
    }
		
    /*!
     * @brief isEmpty()メソッドのテスト
     * @attention 本テストは、RingBufferの実装仕様がリング状バッファ対応されたものに対するテスト内容になっている。
     * リング状バッファ対応前のRinguBufferでは本テストは失敗する。
     *
     * - 最後の１データを残して読み取り、空と判定されないことを確認する
     * - 最後の１データまで読み取り、空と判定されることを確認する
     */
    void _test_isEmpty()
    {
      // バッファを作成する
      long int length = 10;
      RTC::RingBuffer<int> buff(length);
			
      int value = 12345;
      buff.init(value);

      // (1) 最後の１データを残して読み取り、空と判定されないことを確認する
      for (long int i = 0; i < length - 1; i++) {
	int data;
	buff.read(data);
	CPPUNIT_ASSERT_EQUAL(false, buff.isEmpty());
      }

      // (2) 最後の１データまで読み取り、空と判定されることを確認する
      int data;
      buff.read(data);
      CPPUNIT_ASSERT_EQUAL(true, buff.isEmpty());
    }
		
    /*!
     * @brief isFull()メソッドのテスト
     * 
     * - バッファが空の場合、フル判定は偽となるか？
     * - 全バッファにデータが書き込まれている状態でも、フル判定は偽となるか？
     * - バッファに幾分データが書き込まれている状態で、フル判定は偽となるか？
     */
    void test_isFull()
    {
      // (1) バッファが空の場合、フル判定は偽となるか？
      int length1 = 10;
      RTC::RingBuffer<int> buff1(length1);
      CPPUNIT_ASSERT_EQUAL(false, buff1.isFull());
			
      // (2) 全バッファにデータが書き込まれている状態でも、フル判定は偽となるか？
      int length2 = 10;
      RTC::RingBuffer<int> buff2(length2);
      for (int i = 0; i < length2; i++) {
	buff2.write(i);
      }
      CPPUNIT_ASSERT_EQUAL(false, buff2.isFull());
			
      // (3) バッファに幾分データが書き込まれている状態で、フル判定は偽となるか？
      int length3 = 10;
      RTC::RingBuffer<int> buff3(length3);
      for (int i = 0; i < length3 / 2; i++) {
	buff3.write(i);
      }
      CPPUNIT_ASSERT_EQUAL(false, buff3.isFull());
    }
				
    /*!
     * @brief init()メソッドのテスト
     * 
     * - あらかじめデータで初期化した後、設定したデータを正しく読み出せるか？
     */
    void test_init()
    {
      // バッファを作成して、init()で初期化する
      long int length = 10;
      RTC::RingBuffer<int> buff(length);
			
      int value = 12345;
      buff.init(value);
			
      // 設定したデータを正しく読み出せるか？
      int expected = 12345;
      for (long int i = 0; i < length; i++) {
	int actual;
	buff.read(actual);
	CPPUNIT_ASSERT_EQUAL(expected, actual);
      }
    }

    /*!
     * @brief write()メソッドおよびread()メソッドのテスト
     * 
     * - バッファ空状態で１データ書込・読出を行い、書き込んだデータを正しく読み出せるか？
     * - 全バッファにデータが書き込まれている状態で１データ書込・読出を行い、書き込んだデータを正しく読み出せるか？
     * - 全バッファに幾分データが書き込まれている状態で１データ書込・読出を行い、書き込んだデータを正しく読み出せるか？
     */
    void test_write_read()
    {
      // (1) バッファ空状態で１データ書込・読出を行い、書き込んだデータを正しく読み出せるか？
      // バッファ作成し、空のままにする
      long int length1 = 10;
      RTC::RingBuffer<int> buff1(length1);
			
      // １データ書込・読出を行う
      for (int writeValue = 0; writeValue < 100; writeValue++) {
	// 書込み
	buff1.write(writeValue);
				
	// 読出し
	int readValue;
	buff1.read(readValue);
				
	// 書き込んだデータを正しく読み出せたか？
	CPPUNIT_ASSERT_EQUAL(writeValue, readValue);
      }
			
      // (2) 全バッファにデータが書き込まれている状態で１データ書込・読出を行い、書き込んだデータを正しく読み出せるか？
      // バッファ作成し、フル状態にする
      long int length2 = 10;
      RTC::RingBuffer<int> buff2(length2);
      for (int i = 0; i < length2; i++) {
	buff2.write(i + 123);
      }
			
      // １データ書込・読出を行う
      for (int writeValue = 0; writeValue < 100; writeValue++) {
	// 書込み
	buff2.write(writeValue);
				
	// 読出し
	int readValue;
	buff2.read(readValue);
				
	// 書き込んだデータを正しく読み出せたか？
	CPPUNIT_ASSERT_EQUAL(writeValue, readValue);
      }
			
      // (3) バッファに幾分データが書き込まれている状態で１データ書込・読出を行い、書き込んだデータを正しく読み出せるか？
      long int length3 = 10;
      RTC::RingBuffer<int> buff3(length3);
      for (int i = 0; i < length3 / 2; i++) {
	buff3.write(i + 123);
      }
			
      // １データ書込・読出を行う
      for (int writeValue = 0; writeValue < 100; writeValue++) {
	// 書込み
	buff3.write(writeValue);
				
	// 読出し
	int readValue;
	buff3.read(readValue);
				
	// 書き込んだデータを正しく読み出せたか？
	CPPUNIT_ASSERT_EQUAL(writeValue, readValue);
      }
    }
		
    /*!
     * @brief write()メソッドおよびread()メソッドのテスト（バッファ長２の場合）
     * 
     * - バッファ空状態で１データ書込・読出を行い、書き込んだデータを正しく読み出せるか？
     * - 全バッファにデータが書き込まれている状態で１データ書込・読出を行い、書き込んだデータを正しく読み出せるか？
     * - バッファに幾分データが書き込まれている状態で１データ書込・読出を行い、書き込んだデータを正しく読み出せるか？
     */
    void test_write_read_with_small_length()
    {
      // (1) バッファ空状態で１データ書込・読出を行い、書き込んだデータを正しく読み出せるか？
      // バッファ作成し、空のままにする
      long int length1 = 2;
      RTC::RingBuffer<int> buff1(length1);
			
      // １データ書込・読出を行う
      for (int writeValue = 0; writeValue < 100; writeValue++) {
	// 書込み
	buff1.write(writeValue);
				
	// 読出し
	int readValue;
	buff1.read(readValue);
				
	// 書き込んだデータを正しく読み出せたか？
	CPPUNIT_ASSERT_EQUAL(writeValue, readValue);
      }
			
      // (2) 全バッファにデータが書き込まれている状態で１データ書込・読出を行い、書き込んだデータを正しく読み出せるか？
      // バッファ作成し、フル状態にする
      long int length2 = 2;
      RTC::RingBuffer<int> buff2(length2);
      for (int i = 0; i < length2; i++) {
	buff2.write(i + 123);
      }
			
      // １データ書込・読出を行う
      for (int writeValue = 0; writeValue < 100; writeValue++) {
	// 書込み
	buff2.write(writeValue);
				
	// 読出し
	int readValue;
	buff2.read(readValue);
				
	// 書き込んだデータを正しく読み出せたか？
	CPPUNIT_ASSERT_EQUAL(writeValue, readValue);
      }
			
      // (3) バッファに幾分データが書き込まれている状態で１データ書込・読出を行い、書き込んだデータを正しく読み出せるか？
      long int length3 = 2;
      RTC::RingBuffer<int> buff3(length3);
      for (int i = 0; i < 1; i++) {
	buff3.write(i + 123);
      }
			
      // １データ書込・読出を行う
      for (int writeValue = 0; writeValue < 100; writeValue++) {
	// 書込み
	buff3.write(writeValue);
				
	// 読出し
	int readValue;
	buff3.read(readValue);
				
	// 書き込んだデータを正しく読み出せたか？
	CPPUNIT_ASSERT_EQUAL(writeValue, readValue);
      }
    }
		
    /*!
     * @brief isNew()メソッドのテスト
     * 
     * - バッファが空の状態で、isNew判定が偽になるか？
     * - 全バッファにデータが書き込まれている状態で、データ書込後のisNew判定が真になるか？
     * - 全バッファにデータが書き込まれている状態で、データ書込し、そのデータ読出を行った後のisNew判定が偽になるか？
     * - バッファに幾分データが書き込まれている状態で、データ書込後のisNew判定が真になるか？
     * - バッファに幾分データが書き込まれている状態で、データ書込し、そのデータ読出を行った後のisNew判定が偽になるか？
     */
    void test_isNew()
    {
      // (1) バッファが空の状態で、isNew判定が偽になるか？
      long int length1 = 10;
      RTC::RingBuffer<int> buff1(length1);
      CPPUNIT_ASSERT_EQUAL(false, buff1.isNew());
			
      // 全バッファにデータが書き込まれている状態で...
      long int length2 = 10;
      RTC::RingBuffer<int> buff2(length2);
			
      for (int i = 0; i < length2; i++) {
	// (2) ...データ書込後のisNew判定が真になるか？
	int writeValue = i + 123;
	buff2.write(writeValue);
	CPPUNIT_ASSERT_EQUAL(true, buff2.isNew());
				
	// (3) ...データ書込し、そのデータ読出を行った後のisNew判定が偽になるか？
	int readValue;
	buff2.read(readValue);
	CPPUNIT_ASSERT_EQUAL(false, buff2.isNew());
      }
			
      // バッファに幾分データが書き込まれている状態で...
      long int length3 = 10;
      RTC::RingBuffer<int> buff3(length3);
      for (int i = 0; i < length3 / 2; i++) {
	buff3.write(i + 456);
      }
			
      for (int i = 0; i < length3; i++) {
	// (4) ...データ書込後のisNew判定が真になるか？
	int writeValue = i + 123;
	buff3.write(writeValue);
	CPPUNIT_ASSERT_EQUAL(true, buff3.isNew());
				
	// (5) ...データ書込し、そのデータ読出を行った後のisNew判定が偽になるか？
	int readValue;
	buff3.read(readValue);
	CPPUNIT_ASSERT_EQUAL(false, buff3.isNew());
      }
    }
		
  };
}; // namespace RingBuffer

/*
 * Register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(RingBuffer::RingBufferTests);

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
#endif // RingBuffer_cpp
