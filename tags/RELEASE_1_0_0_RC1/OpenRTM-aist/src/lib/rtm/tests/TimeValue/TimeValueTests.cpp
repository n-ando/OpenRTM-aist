// -*- C++ -*-
/*!
 * @file   TimeValueTests.cpp
 * @brief  TimeValue test class
 * @date   $Date: 2008/02/21 14:08:13 $
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

#ifndef TimeValueTests_cpp
#define TimeValueTests_cpp

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>

#include <string>
#include <sstream>
#include <rtm/TimeValue.h>

/*!
 * @class TimeValueTests class
 * @brief TimeValue test
 */
class TimeValueTests
  : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(TimeValueTests);
	
  CPPUNIT_TEST(test_operator_minus);
  CPPUNIT_TEST(test_operator_plus);
  CPPUNIT_TEST(test_sign);
  CPPUNIT_TEST(test_toDouble);
  CPPUNIT_TEST(test_fromDouble);
	
  CPPUNIT_TEST_SUITE_END();
	
private:
	
public:
  /*!
   * @brief Constructor
   */
  TimeValueTests()
  {
  }
	
  /*!
   * @brief Destructor
   */
  ~TimeValueTests()
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
   * @brief operator-()のテスト
   * 
   * - 「左辺sec > 右辺sec」かつ「左辺usec > 右辺usec」の場合、正しく減算できるか？
   * - 「左辺sec > 右辺sec」かつ「左辺usec < 右辺usec」の場合、正しく減算できるか？
   * - 「左辺sec > 右辺sec」かつ「左辺usec == 右辺usec」の場合、正しく減算できるか？
   * - 「左辺sec < 右辺sec」かつ「左辺usec > 右辺usec」の場合、正しく減算できるか？
   * - 「左辺sec < 右辺sec」かつ「左辺usec < 右辺usec」の場合、正しく減算できるか？
   * - 「左辺sec < 右辺sec」かつ「左辺usec == 右辺usec」の場合、正しく減算できるか？
   * - 「左辺sec == 右辺sec」かつ「左辺usec > 右辺usec」の場合、正しく減算できるか？
   * - 「左辺sec == 右辺sec」かつ「左辺usec < 右辺usec」の場合、正しく減算できるか？
   * - 「左辺sec == 右辺sec」かつ「左辺usec == 右辺usec」の場合、正しく減算できるか？
   */
  void test_operator_minus()
  {
    // (1a) 「左辺sec > 右辺sec」かつ「左辺usec > 右辺usec」の場合、正しく減算できるか？
    TimeValue lhs1a(99, 999999);
    TimeValue rhs1a(98, 999998);
    TimeValue res1a = lhs1a - rhs1a;
    CPPUNIT_ASSERT_EQUAL(1L, res1a.tv_sec);
    CPPUNIT_ASSERT_EQUAL(1L, res1a.tv_usec);
		
    // (1b) 「左辺sec > 右辺sec」かつ「左辺usec < 右辺usec」の場合、正しく減算できるか？
    TimeValue lhs1b(99, 999998);
    TimeValue rhs1b(98, 999999);
    TimeValue res1b = lhs1b - rhs1b;
    CPPUNIT_ASSERT_EQUAL(0L, res1b.tv_sec);
    CPPUNIT_ASSERT_EQUAL(999999L, res1b.tv_usec);
		
    // (1c) 「左辺sec > 右辺sec」かつ「左辺usec == 右辺usec」の場合、正しく減算できるか？
    TimeValue lhs1c(99, 999999);
    TimeValue rhs1c(98, 999999);
    TimeValue res1c = lhs1c - rhs1c;
    CPPUNIT_ASSERT_EQUAL(1L, res1c.tv_sec);
    CPPUNIT_ASSERT_EQUAL(0L, res1c.tv_usec);
		
    // (2a) 「左辺sec < 右辺sec」かつ「左辺usec > 右辺usec」の場合、正しく減算できるか？
    TimeValue lhs2a(98, 999999);
    TimeValue rhs2a(99, 999998);
    TimeValue res2a = lhs2a - rhs2a;
    CPPUNIT_ASSERT_EQUAL(0L, res2a.tv_sec);
    CPPUNIT_ASSERT_EQUAL(-999999L, res2a.tv_usec);
		
    // (2b) 「左辺sec < 右辺sec」かつ「左辺usec < 右辺usec」の場合、正しく減算できるか？
    TimeValue lhs2b(98, 999998);
    TimeValue rhs2b(99, 999999);
    TimeValue res2b = lhs2b - rhs2b;
    CPPUNIT_ASSERT_EQUAL(-1L, res2b.tv_sec);
    CPPUNIT_ASSERT_EQUAL(-1L, res2b.tv_usec);
		
    // (2c) 「左辺sec < 右辺sec」かつ「左辺usec == 右辺usec」の場合、正しく減算できるか？
    TimeValue lhs2c(98, 999999);
    TimeValue rhs2c(99, 999999);
    TimeValue res2c = lhs2c - rhs2c;
    CPPUNIT_ASSERT_EQUAL(-1L, res2c.tv_sec);
    CPPUNIT_ASSERT_EQUAL(0L, res2c.tv_usec);
		
    // (3a) 「左辺sec == 右辺sec」かつ「左辺usec > 右辺usec」の場合、正しく減算できるか？
    TimeValue lhs3a(99, 999999);
    TimeValue rhs3a(99, 999998);
    TimeValue res3a = lhs3a - rhs3a;
    CPPUNIT_ASSERT_EQUAL(0L, res3a.tv_sec);
    CPPUNIT_ASSERT_EQUAL(1L, res3a.tv_usec);

    // (3b) 「左辺sec == 右辺sec」かつ「左辺usec < 右辺usec」の場合、正しく減算できるか？
    TimeValue lhs3b(99, 999998);
    TimeValue rhs3b(99, 999999);
    TimeValue res3b = lhs3b - rhs3b;
    CPPUNIT_ASSERT_EQUAL(0L, res3b.tv_sec);
    CPPUNIT_ASSERT_EQUAL(-1L, res3b.tv_usec);
		
    // (3c) 「左辺sec == 右辺sec」かつ「左辺usec == 右辺usec」の場合、正しく減算できるか？
    TimeValue lhs3c(99, 999999);
    TimeValue rhs3c(99, 999999);
    TimeValue res3c = lhs3c - rhs3c;
    CPPUNIT_ASSERT_EQUAL(0L, res3c.tv_sec);
    CPPUNIT_ASSERT_EQUAL(0L, res3c.tv_usec);
  }
	
  /*!
   * @brief operator+()メソッドのテスト
   * 
   * - usec-->secへの繰り上がりがない場合に、正しく加算できるか？
   * - usec-->secへの繰り上がりがある場合に、正しく加算できるか？
   */
  void test_operator_plus()
  {
    // (1) usec-->secへの繰り上がりがない場合に、正しく加算できるか？
    TimeValue lhs1(5, 500000);
    TimeValue rhs1(5, 499999);
    TimeValue res1 = lhs1 + rhs1;
    CPPUNIT_ASSERT_EQUAL(10L, res1.tv_sec);
    CPPUNIT_ASSERT_EQUAL(999999L, res1.tv_usec);
		
    // (2) usec-->secへの繰り上がりがある場合に、正しく加算できるか？
    TimeValue lhs2(5, 500000);
    TimeValue rhs2(5, 500000);
    TimeValue res2 = lhs2 + rhs2;
    CPPUNIT_ASSERT_EQUAL(11L, res2.tv_sec);
    CPPUNIT_ASSERT_EQUAL(0L, res2.tv_usec);
  }
	
  /*!
   * @brief sign()メソッドのテスト
   * 
   * - secオーダーのみで正と判定できる値の場合、正しく符号判定できるか？
   * - secオーダーのみで負と判定できる値の場合、正しく符号判定できるか？
   * - usecオーダーまで見て正と判定できる値の場合、正しく符号判定できるか？
   * - usecオーダーまで見て負と判定できる値の場合、正しく符号判定できるか？
   * - 値ゼロの場合、正しく符号判定できるか？
   */
  void test_sign()
  {
    // (1) secオーダーのみで正と判定できる値の場合、正しく符号判定できるか？
    TimeValue tv_positive_sec(1, -999999);
    CPPUNIT_ASSERT_EQUAL(1, tv_positive_sec.sign());
		
    // (2) secオーダーのみで負と判定できる値の場合、正しく符号判定できるか？
    TimeValue tv_negative_sec(-1, 999999);
    CPPUNIT_ASSERT_EQUAL(-1, tv_negative_sec.sign());
		
    // (3) usecオーダーまで見て正と判定できる値の場合、正しく符号判定できるか？
    TimeValue tv_positive_usec(0, 1);
    CPPUNIT_ASSERT_EQUAL(1, tv_positive_usec.sign());
		
    // (4) usecオーダーまで見て負と判定できる値の場合、正しく符号判定できるか？
    TimeValue tv_negative_usec(0, -1);
    CPPUNIT_ASSERT_EQUAL(-1, tv_negative_usec.sign());
		
    // (5) 値ゼロの場合、正しく符号判定できるか？
    TimeValue tv_zero(0, 0);
    CPPUNIT_ASSERT_EQUAL(0, tv_zero.sign());
  }
	
  /*!
   * @brief toDouble()メソッドのテスト
   * 
   * - 最小のマイクロ秒オーダーを含むTimeValue形式を、正しく浮動小数表現形式に変換できるか？
   * - 最大のマイクロ秒オーダーを含むTimeValue形式を、正しく浮動小数表現形式に変換できるか？
   * - マイクロ秒オーダーが０の場合のTimeValue形式を、正しく浮動小数表現形式に変換できるか？
   */
  void test_toDouble()
  {
    // (1) 最小のマイクロ秒オーダーを含むTimeValue形式を、正しく浮動小数表現形式に変換できるか？
    TimeValue tv1(1L, 1L);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(1.000001, tv1.toDouble(), 0.0000001);
		
    // (2) 最大のマイクロ秒オーダーを含むTimeValue形式を、正しく浮動小数表現形式に変換できるか？
    TimeValue tv2(0L, 999999L);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.999999, tv2.toDouble(), 0.0000001);
		
    // (3) マイクロ秒オーダーが０の場合のTimeValue形式を、正しく浮動小数表現形式に変換できるか？
    TimeValue tv3(0L, 0L);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.000000, tv3.toDouble(), 0.0000001);
  }
	
  /*!
   * @brief operator=(double)メソッドのテスト
   * 
   * - 最小のマイクロ秒オーダーを含む浮動小数点形式を、正しくTimeValue形式に変換できるか？
   * - 最大のマイクロ秒オーダーを含む浮動小数点形式を、正しくTimeValue形式に変換できるか？
   * - マイクロ秒オーダーが０の場合の浮動小数点形式を、正しくTimeValue形式に変換できるか？
   */
  void test_fromDouble()
  {
    // (1) 最小のマイクロ秒オーダーを含む浮動小数点形式を、正しくTimeValue形式に変換できるか？
    TimeValue tv1;
    tv1 = 1.000001;
    CPPUNIT_ASSERT_EQUAL(1L, tv1.tv_sec);
    CPPUNIT_ASSERT_EQUAL(1L, tv1.tv_usec);
		
    // (2) 最大のマイクロ秒オーダーを含む浮動小数点形式を、正しくTimeValue形式に変換できるか？
    TimeValue tv2;
    tv2 = 0.999999;
    CPPUNIT_ASSERT_EQUAL(0L, tv2.tv_sec);
    CPPUNIT_ASSERT_EQUAL(999999L, tv2.tv_usec);
		
    // (3) マイクロ秒オーダーが０の場合の浮動小数点形式を、正しくTimeValue形式に変換できるか？
    TimeValue tv3;
    tv3 = 0.000000;
    CPPUNIT_ASSERT_EQUAL(0L, tv3.tv_sec);
    CPPUNIT_ASSERT_EQUAL(0L, tv3.tv_usec);
  }
	
};

/*
 * Register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(TimeValueTests);

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
#endif // TimeValueTests_cpp
