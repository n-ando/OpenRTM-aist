// -*- C++ -*-
/*!
 * @file   StringUtilTests.cpp
 * @brief  StringUtil test class
 * @date   $Date: 2008/01/10 01:49:58 $
 * @author Noriaki Ando <n-ando@aist.go.jp>,
 *         Shinji Kurihara
 *
 * $Id$
 *
 */

/*
 * $Log: StringUtilTests.cpp,v $
 * Revision 1.2  2008/01/10 01:49:58  arafune
 * *** empty log message ***
 *
 * Revision 1.1  2007/12/20 07:50:16  arafune
 * *** empty log message ***
 *
 * Revision 1.1  2006/11/27 08:25:52  n-ando
 * TestSuites are devided into each directory.
 *
 * Revision 1.2  2006/10/23 07:38:37  n-ando
 * Some fixes for split() tests.
 *
 * Revision 1.1  2006/10/23 06:10:17  kurihara
 *
 * test program for StringUtil class.
 *
 *
 */

#ifndef StringUtil_cpp
#define StringUtil_cpp

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>

#include <fstream>
#include <iostream>
#include <rtm/StringUtil.h>

namespace StringUtil
{
  using namespace std;
  /*!
   * @class StringUtilTests
   * @brief StringUtil test
   */
  class StringUtilTests
    : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(StringUtilTests);
		
    CPPUNIT_TEST(test_isEscaped);
    CPPUNIT_TEST(test_escape);
    CPPUNIT_TEST(test_unescape);
    CPPUNIT_TEST(test_eraseHeadBlank);
    CPPUNIT_TEST(test_eraseTailBlank);
    CPPUNIT_TEST(test_replaceString);
    CPPUNIT_TEST(test_split);
    CPPUNIT_TEST(test_toBool);
    CPPUNIT_TEST(test_isAbsolutePath);
    CPPUNIT_TEST(test_isURL);
    CPPUNIT_TEST(test_unique_sv);
    CPPUNIT_TEST(test_flatten);
		
    CPPUNIT_TEST_SUITE_END();
		
  private:
	
  public:
		    
    /*!
     * @brief Constructor
     */
    StringUtilTests()
    {
    }
		
    /*!
     * @brief Destructor
     */
    ~StringUtilTests()
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
     * @brief isEscaped()メソッドのテスト
     * 
     * <ul>
     * <li>エスケープされている文字列に対して、正しくエスケープされていると判定できるか？</li>
     * <li>エスケープされていない文字列に対して、正しくエスケープされていないと判定できるか？</li>
     * </ul>
     */
    void test_isEscaped()
    {
      vector<string> escapedStrs;
      escapedStrs.push_back("\\t");
      escapedStrs.push_back("\\n");
      escapedStrs.push_back("\\f");
      escapedStrs.push_back("\\r");

      for (unsigned int i = 0; i < escapedStrs.size(); i++) {
	string str = escapedStrs[i];
	CPPUNIT_ASSERT(isEscaped(str, str.length() - 1));
      }
			
      vector<string> noescapedStrs;
      noescapedStrs.push_back("\t");
      noescapedStrs.push_back("\n");
      noescapedStrs.push_back("\f");
      noescapedStrs.push_back("\r");

      for (unsigned int i = 0; i < noescapedStrs.size(); i++) {
	string str = noescapedStrs[i];
	CPPUNIT_ASSERT(! isEscaped(str, str.length() - 1));
      }
    }
		
    /*!
     * @brief espace()メソッドのテスト
     * 
     * <ul>
     * <li>HTは正しくエスケープされるか？</li>
     * <li>LFは正しくエスケープされるか？</li>
     * <li>CRは正しくエスケープされるか？</li>
     * <li>FFは正しくエスケープされるか？</li>
     * <li>バックスラッシュ文字は正しくエスケープされるか？</li>
     * </ul>
     */
    void test_escape()
    {
      // (1) \tは正しくエスケープされるか？
      string target1 = "\t";
      string expected1 = "\\t";
      CPPUNIT_ASSERT_EQUAL(expected1, escape(target1));
			
      // (2) \nは正しくエスケープされるか？
      string target2 = "\n";
      string expected2 = "\\n";
      CPPUNIT_ASSERT_EQUAL(expected2, escape(target2));

      // (3) \fは正しくエスケープされるか？
      string target3 = "\f";
      string expected3 = "\\f";
      CPPUNIT_ASSERT_EQUAL(expected3, escape(target3));

      // (4) \rは正しくエスケープされるか？
      string target4 = "\r";
      string expected4 = "\\r";
      CPPUNIT_ASSERT_EQUAL(expected4, escape(target4));
			
      // (5) エスケープ対象外であるダブルクォートは、エスケープされずそのままか？
      string target5 = "\"";
      string expected5 = "\"";
      CPPUNIT_ASSERT_EQUAL(expected5, escape(target5));
			
      // (6) エスケープ対象外であるシングルクォートは、エスケープされずそのままか？
      string target6 = "'";
      string expected6 = "'";
      CPPUNIT_ASSERT_EQUAL(expected6, escape(target6));
			
      // (7) \（バックスラッシュ文字）は、正しくエスケープされるか？
      string target7 = "\\";
      string expected7 = "\\\\";
      CPPUNIT_ASSERT_EQUAL(expected7, escape(target7));
			
      // (8) エスケープ対象の文字を複数含む文字列は、正しくエスケープされるか？
      string target8 = "\tHello!\t";
      string expected8 = "\\tHello!\\t";
      CPPUNIT_ASSERT_EQUAL(expected8, escape(target8));
    }
		
    /*!
     * @brief unescape()メソッドのテスト
     * 
     * <ul>
     * <li>"\t"は正しくアンエスケープされるか？</li>
     * <li>"\n"は正しくアンエスケープされるか？</li>
     * <li>"\f"は正しくアンエスケープされるか？</li>
     * <li>"\r"は正しくアンエスケープされるか？</li>
     * <li>シングルクォート（'）は正しくアンエスケープされるか？</li>
     * <li>ダブルクォート（"）は正しくアンエスケープされるか？</li>
     * </ul>
     */
    void test_unescape()
    {
      // (1) \tは正しくアンエスケープされるか？
      string target1 = "\\t";
      string expected1 = "\t";
      CPPUNIT_ASSERT_EQUAL(expected1, unescape(target1));
			
      // (2) \nは正しくアンエスケープされるか？
      string target2 = "\\n";
      string expected2 = "\n";
      CPPUNIT_ASSERT_EQUAL(expected2, unescape(target2));

      // (3) \fは正しくアンエスケープされるか？
      string target3 = "\\f";
      string expected3 = "\f";
      CPPUNIT_ASSERT_EQUAL(expected3, unescape(target3));

      // (4) \rは正しくアンエスケープされるか？
      string target4 = "\\r";
      string expected4 = "\r";
      CPPUNIT_ASSERT_EQUAL(expected4, unescape(target4));
			
      // (5) ダブルクォートは、正しくエスケープされるか？
      string target5 = "\\\"";
      string expected5 = "\"";
      CPPUNIT_ASSERT_EQUAL(expected5, unescape(target5));
			
      // (6) シングルクォートは、正しくエスケープされるか？
      string target6 = "\\'";
      string expected6 = "'";
      CPPUNIT_ASSERT_EQUAL(expected6, unescape(target6));
			
      // (7) \（バックスラッシュ文字）は、正しくエスケープされるか？
      string target7 = "\\\\";
      string expected7 = "\\";
      CPPUNIT_ASSERT_EQUAL(expected7, unescape(target7));
			
      // (8) アンエスケープ対象の文字を複数含む文字列は、正しくアンエスケープされるか？
      string target8 = "\\tHello!\\t";
      string expected8 = "\tHello!\t";
      CPPUNIT_ASSERT_EQUAL(expected8, unescape(target8));
    }
		
    /*!
     * @brief eraseHeadBlank()メソッドのテスト
     * 
     * <ul>
     * <li>先頭に空白文字を含まない場合、変化せずにそのままか？</li>
     * <li>先頭にスペースを１文字だけ含む場合、正しく除去されるか？</li>
     * <li>先頭にスペースを複数文字含む場合、正しく除去されるか？</li>
     * <li>先頭にタブを１つだけ含む場合、正しく除去されるか？</li>
     * <li>先頭にタブを複数含む場合、正しく除去されるか？</li>
     * <li>先頭にスペースとタブが混在して含まれる場合、正しく除去されるか？</li>
     * </ul>
     */
    void test_eraseHeadBlank()
    {
      // (1) 先頭に空白文字を含まない場合、変化せずにそのままか？
      string target1 = "Hello, World! ";
      string expected1 = "Hello, World! ";
      eraseHeadBlank(target1);
      CPPUNIT_ASSERT_EQUAL(expected1, target1);
			
      // (2) 先頭にスペースを１文字だけ含む場合、正しく除去されるか？
      string target2 = " Hello, World! ";
      string expected2 = "Hello, World! ";
      eraseHeadBlank(target2);
      CPPUNIT_ASSERT_EQUAL(expected2, target2);
			
      // (3) 先頭にスペースを複数文字含む場合、正しく除去されるか？
      string target3 = "     Hello, World! ";
      string expected3 = "Hello, World! ";
      eraseHeadBlank(target3);
      CPPUNIT_ASSERT_EQUAL(expected3, target3);
			
      // (4) 先頭にタブを１つだけ含む場合、正しく除去されるか？
      string target4 = "\tHello, World! ";
      string expected4 = "Hello, World! ";
      eraseHeadBlank(target4);
      CPPUNIT_ASSERT_EQUAL(expected4, target4);
			
      // (5) 先頭にタブを複数含む場合、正しく除去されるか？
      string target5 = "\t\t\tHello, World! ";
      string expected5 = "Hello, World! ";
      eraseHeadBlank(target5);
      CPPUNIT_ASSERT_EQUAL(expected5, target5);
			
      // (6) 先頭にスペースとタブが混在して含まれる場合、正しく除去されるか？
      string target6 = " \t\t  \t Hello, World! ";
      string expected6 = "Hello, World! ";
      eraseHeadBlank(target6);
      CPPUNIT_ASSERT_EQUAL(expected6, target6);
    }
		
    /*!
     * @brief eraseTailBlank()メソッドのテスト
     * 
     * <ul>
     * <li>最後尾に空白文字を含まない場合、変換されずにそのまま残るか？</li>
     * <li>最後尾にスペースを１文字だけ含む場合、正しく除去されるか？</li>
     * <li>最後尾にスペースを複数文字含む場合、正しく除去されるか？</li>
     * <li>最後尾にタブを１文字だけ含む場合、正しく除去されるか？</li>
     * <li>最後尾にタブを複数含む場合、正しく除去されるか？</li>
     * <li>最後尾にスペースとタブを混在して含む場合、正しく除去されるか？</li>
     * </ul>
     */
    void test_eraseTailBlank()
    {
      // (1) 最後尾に空白文字を含まない場合、変換されずにそのまま残るか？
      string target1 = " Hello, World!";
      string expected1 = " Hello, World!";
      eraseTailBlank(target1);
      CPPUNIT_ASSERT_EQUAL(expected1, target1);
			
      // (2) 最後尾にスペースを１文字だけ含む場合、正しく除去されるか？
      string target2 = " Hello, World! ";
      string expected2 = " Hello, World!";
      eraseTailBlank(target2);
      CPPUNIT_ASSERT_EQUAL(expected2, target2);
			
      // (3) 最後尾にスペースを複数文字含む場合、正しく除去されるか？
      string target3 = " Hello, World!   ";
      string expected3 = " Hello, World!";
      eraseTailBlank(target3);
      CPPUNIT_ASSERT_EQUAL(expected3, target3);
			
      // (4) 最後尾にタブを１文字だけ含む場合、正しく除去されるか？
      string target4 = " Hello, World!\t";
      string expected4 = " Hello, World!";
      eraseTailBlank(target4);
      CPPUNIT_ASSERT_EQUAL(expected4, target4);
			
      // (5) 最後尾にタブを複数含む場合、正しく除去されるか？
      string target5 = " Hello, World!\t\t\t";
      string expected5 = " Hello, World!";
      eraseTailBlank(target5);
      CPPUNIT_ASSERT_EQUAL(expected5, target5);
			
      // (6) 最後尾にスペースとタブを混在して含む場合、正しく除去されるか？
      string target6 = " Hello, World!\t\t \t   \t ";
      string expected6 = " Hello, World!";
      eraseTailBlank(target6);
      CPPUNIT_ASSERT_EQUAL(expected6, target6);
    }
		
    /*!
     * @brief replaceString()メソッドのテスト
     * 
     * <ul>
     * <li>置換前１文字、置換後１文字の場合、正しく置換できるか？</li>
     * <li>置換前１文字、置換後複数文字の場合、正しく置換できるか？</li>
     * <li>置換前複数文字、置換後１文字の場合、正しく置換できるか？</li>
     * <li>置換前複数文字、置換後複数文字の場合、正しく置換できるか？</li>
     * </ul>
     */
    void test_replaceString()
    {
      // (1) 置換前１文字、置換後１文字の場合、正しく置換できるか？
      string target1 = "*Hello,*World!*";
      string expected1 = " Hello, World! ";
      replaceString(target1, "*", " ");
      CPPUNIT_ASSERT_EQUAL(expected1, target1);
			
      // (2) 置換前１文字、置換後複数文字の場合、正しく置換できるか？
      string target2 = "*Hello,*World!*";
      string expected2 = " - Hello, - World! - ";
      replaceString(target2, "*", " - ");
      CPPUNIT_ASSERT_EQUAL(expected2, target2);

      // (3) 置換前複数文字、置換後１文字の場合、正しく置換できるか？
      string target3 = "*|-Hello,*|-World!*|-";
      string expected3 = " Hello, World! ";
      replaceString(target3, "*|-", " ");
      CPPUNIT_ASSERT_EQUAL(expected3, target3);
			
      // (4) 置換前複数文字、置換後複数文字の場合、正しく置換できるか？
      string target4 = "*|-Hello,*|-World!*|-";
      string expected4 = " - Hello, - World! - ";
      replaceString(target4, "*|-", " - ");
      CPPUNIT_ASSERT_EQUAL(expected4, target4);
    }
		
    /*!
     * @brief split()メソッドのテスト
     * 
     * <ul>
     * <li>デリミタが１文字の場合、正しく分割できるか？</li>
     * <li>デリミタが複数文字の場合、正しく分割できるか？</li>
     * <li>分割された文字列断片のうち、文字列長０のものは除去されるか？</li>
     * </ul>
     */
    void test_split()
    {
      // (1) デリミタが１文字の場合、正しく分割できるか？
      string target1 = "It's|a|small|world.";
      string expected1[] = {"It's", "a", "small", "world."};
      vector<string> splited1 = split(target1, "|");
      CPPUNIT_ASSERT_EQUAL(4, (int) splited1.size());
      CPPUNIT_ASSERT_EQUAL(expected1[0], splited1[0]);
      CPPUNIT_ASSERT_EQUAL(expected1[1], splited1[1]);
      CPPUNIT_ASSERT_EQUAL(expected1[2], splited1[2]);
      CPPUNIT_ASSERT_EQUAL(expected1[3], splited1[3]);
			
      // (2) デリミタが複数文字の場合、正しく分割できるか？
      string target2 = "It's*-*a*-*small*-*world.";
      string expected2[] = {"It's", "a", "small", "world."};
      vector<string> splited2 = split(target2, "*-*");
      CPPUNIT_ASSERT_EQUAL(4, (int) splited2.size());
      CPPUNIT_ASSERT_EQUAL(expected2[0], splited2[0]);
      CPPUNIT_ASSERT_EQUAL(expected2[1], splited2[1]);
      CPPUNIT_ASSERT_EQUAL(expected2[2], splited2[2]);
      CPPUNIT_ASSERT_EQUAL(expected2[3], splited2[3]);
			
      // (3) 分割された文字列断片のうち、文字列長０のものは除去されるか？
      string target3 = "@It's@@a@@@small@@@@world.@@@@@";
      string expected3[] = {"It's", "a", "small", "world."};
      vector<string> splited3 = split(target3, "@");
      CPPUNIT_ASSERT_EQUAL(4, (int) splited3.size());
      CPPUNIT_ASSERT_EQUAL(expected3[0], splited3[0]);
      CPPUNIT_ASSERT_EQUAL(expected3[1], splited3[1]);
      CPPUNIT_ASSERT_EQUAL(expected3[2], splited3[2]);
      CPPUNIT_ASSERT_EQUAL(expected3[3], splited3[3]);
    }
		
    /*!
     * @brief toBool()メソッドのテスト
     * 
     * <ul>
     * <li>true表現文字列に一致し、デフォルトがtrueの場合に、正しくtrueとなるか？</li>
     * <li>true表現文字列に一致し、デフォルトがfalseの場合に、正しくtrueとなるか？</li>
     * <li>false表現文字列に一致し、デフォルトがtrueの場合に、正しくfalseとなるか？</li>
     * <li>false表現文字列に一致し、デフォルトがfalseの場合に、正しくfalseとなるか？</li>
     * <li>true/falseいずれの表現文字列にも一致せず、デフォルトがtrueの場合に、正しくtrueとなるか？</li>
     * <li>true/falseいずれの表現文字列にも一致せず、デフォルトがfalseの場合に、正しくfalseとなるか？</li>
     * </ul>
     */
    void test_toBool()
    {
      string T = "TRUE";
      string F = "FALSE";
			
      // (1) true表現文字列に一致し、デフォルトがtrueの場合に、正しくtrueとなるか？
      CPPUNIT_ASSERT_EQUAL(true, toBool("TRUE", T, F, true));
			
      // (2) true表現文字列に一致し、デフォルトがfalseの場合に、正しくtrueとなるか？
      CPPUNIT_ASSERT_EQUAL(true, toBool("TRUE", T, F, false));
			
      // (3) false表現文字列に一致し、デフォルトがtrueの場合に、正しくfalseとなるか？
      CPPUNIT_ASSERT_EQUAL(false, toBool("FALSE", T, F, true));
			
      // (4) false表現文字列に一致し、デフォルトがfalseの場合に、正しくfalseとなるか？
      CPPUNIT_ASSERT_EQUAL(false, toBool("FALSE", T, F, false));
			
      // (5) true/falseいずれの表現文字列にも一致せず、デフォルトがtrueの場合に、正しくtrueとなるか？
      CPPUNIT_ASSERT_EQUAL(true, toBool("UNKNOWN", T, F, true));
			
      // (6) true/falseいずれの表現文字列にも一致せず、デフォルトがfalseの場合に、正しくfalseとなるか？
      CPPUNIT_ASSERT_EQUAL(false, toBool("UNKNOWN", T, F, false));
    }
		
    /*!
     * @brief isAbsolutePath()メソッドのテスト
     * 
     * <ul>
     * <li>先頭文字が「/」の場合、絶対パスと判定されるか？</li>
     * <li>先頭３文字が「../」の場合、相対パスと判定されるか？</li>
     * <li>先頭３文字が、アルファベット + 「:\」の場合、絶対パスと判定されるか？</li>
     * <li>先頭３文字が「..\」の場合、相対パスと判定されるか？</li>
     * <li>先頭２文字が「\\」の場合、絶対パスと判定されるか？</li>
     * </ul>
     */
    void test_isAbsolutePath()
    {
      // (1) 先頭文字が「/」の場合、絶対パスと判定されるか？
      CPPUNIT_ASSERT_EQUAL(true, isAbsolutePath("/usr/local/lib"));
			
      // (2) 先頭３文字が「../」の場合、相対パスと判定されるか？
      CPPUNIT_ASSERT_EQUAL(false, isAbsolutePath("../usr/local/lib"));
			
      // (3) 先頭３文字が、アルファベット + 「:\」の場合、絶対パスと判定されるか？
      CPPUNIT_ASSERT_EQUAL(true, isAbsolutePath("C:\\Program Files"));
			
      // (4) 先頭３文字が「..\」の場合、相対パスと判定されるか？
      CPPUNIT_ASSERT_EQUAL(false, isAbsolutePath("..\\Program Files"));
			
      // (5) 先頭２文字が「\\」の場合、絶対パスと判定されるか？
      CPPUNIT_ASSERT_EQUAL(true, isAbsolutePath("\\\\server01"));
    }
		
    /*!
     * @brief isURL()メソッドのテスト
     * 
     * <ul>
     * <li>1文字以上の文字列 + 「://」で始まる場合に、URLとして判定されるか？</li>
     * <li>「://」で始まる場合に、URLではないと判定されるか？</li>
     * </ul>
     */
    void test_isURL()
    {
      // (1) 1文字以上の文字列＋「://」で始まる場合に、URLとして判定されるか？
      CPPUNIT_ASSERT_EQUAL(true, isURL("http://domain"));
			
      // (2) 「://」で始まる場合に、URLではないと判定されるか？
      CPPUNIT_ASSERT_EQUAL(false, isURL("://domain"));
    }
		
    /*!
     * @brief unique_sv()メソッドのテスト
     * 
     * <ul>
     * <li>重複を持つ文字列ベクタに対して、重複を正しく除去できるか？</li>
     * </ul>
     */
    void test_unique_sv()
    {
      // 重複を持つベクタを作成する
      vector<string> overlappedStrs;
      overlappedStrs.push_back("unique1");
      overlappedStrs.push_back("overlapped1");
      overlappedStrs.push_back("unique2");
      overlappedStrs.push_back("overlapped1");
      overlappedStrs.push_back("overlapped2");
      overlappedStrs.push_back("overlapped2");
      overlappedStrs.push_back("unique3");
			
      // 重複除去後の期待値となるベクタを作成する
      vector<string> expectedStrs;
      expectedStrs.push_back("unique1");
      expectedStrs.push_back("overlapped1");
      expectedStrs.push_back("unique2");
      expectedStrs.push_back("overlapped2");
      expectedStrs.push_back("unique3");
			
      // 重複除去処理を行う
      vector<string> uniqueStrs = unique_sv(overlappedStrs);
      sort(uniqueStrs.begin(), uniqueStrs.end());
      sort(expectedStrs.begin(), expectedStrs.end());
			
      // 重複は正しく除去されたか？期待値と比較してチェックする
      CPPUNIT_ASSERT_EQUAL(expectedStrs.size(), uniqueStrs.size());
      for (vector<string>::size_type i = 0; i < expectedStrs.size(); i++) {
	CPPUNIT_ASSERT_EQUAL(expectedStrs[i], uniqueStrs[i]);
      }
    }
		
    /*!
     * @brief flatten()メソッドのテスト
     * 
     * <ul>
     * <li>タブを含む文字列について、正しく出力されるか？</li>
     * <li>カンマを含む文字列について、正しく出力されるか？（カンマがエスケープされることはない仕様を前提として）</li>
     * </ul>
     */
    void test_flatten()
    {
      vector<string> values;
      values.push_back("value"); // 通常の文字列
      values.push_back("\ttabbed\t"); // タブを含む文字列
      values.push_back("hello, world"); // カンマを含む文字列
			
      string flattened = flatten(values);
      string expected = "value, \ttabbed\t, hello, world";
      CPPUNIT_ASSERT_EQUAL(expected, flattened);
    }
		
  };
}; // namespace StringUtil

/*
 * Register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(StringUtil::StringUtilTests);

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
#endif // StringUtil_cpp
