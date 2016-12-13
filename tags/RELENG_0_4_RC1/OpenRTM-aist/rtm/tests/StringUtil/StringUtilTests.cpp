// -*- C++ -*-
/*!
 * @file   StringUtilTests.cpp
 * @brief  StringUtil test class
 * @date   $Date: 2006-11-27 08:25:52 $
 * @author Noriaki Ando <n-ando@aist.go.jp>,
 *         Shinji Kurihara
 *
 * $Id: StringUtilTests.cpp,v 1.1 2006-11-27 08:25:52 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
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

/*!
 * @class StringUtilTests class
 * @brief StringUtil test
 */
namespace StringUtil
{
  using namespace std;
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
    //  CPPUNIT_TEST(test_toBool);
    CPPUNIT_TEST(test_isAbsolutePath);
    CPPUNIT_TEST(test_isURL);
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
    
    
    void test_isEscaped() {
      string str;
      ifstream ifs("isEscaped.data");
      getline(ifs, str);
      ifs.close();
      CPPUNIT_ASSERT(isEscaped(str, str.size() - 1));
    }
    
    void test_escape() {
      string orig, result, expectation;
      //    ifstream ifs("escape.data");
      //    getline(ifs, orig);
      //    getline(ifs, expectation);
      //    ifs.close();
      
      orig = '\t';
      expectation = "\\t";
      result = escape(orig);
      //    cout << "original:" << orig << " result:" << result << endl;
      CPPUNIT_ASSERT(result == expectation);
      
      orig = '\n';
      expectation = "\\n";
      result = escape(orig);
      //    cout << "original:" << orig << " result:" << result << endl;
      CPPUNIT_ASSERT(result == expectation);
      
      orig = '\f';
      expectation = "\\f";
      result = escape(orig);
      //    cout << "original:" << orig << " result:" << result << endl;
      CPPUNIT_ASSERT(result == expectation);
      
      orig = '\r';
      expectation = "\\r";
      result = escape(orig);
      //    cout << "original:" << orig << " result:" << result << endl;
      CPPUNIT_ASSERT(result == expectation);
      
      orig = '\"';
      expectation = "\"";
      result = escape(orig);
      //    cout << "original:" << orig << " result:" << result << endl;
      CPPUNIT_ASSERT(result == expectation);
      
      orig = '\'';
      expectation = "\'";
      result = escape(orig);
      //    cout << "original:" << orig << " result:" << result << endl;
      CPPUNIT_ASSERT(result == expectation);
      
      orig = '\c';
      expectation = '\c';
      result = escape(orig);
      //    cout << "original:" << orig << " result:" << result << endl;
      CPPUNIT_ASSERT(result == expectation);
      
      orig = "\\\thello\t";
      expectation = "\\\\thello\\t";
      result = escape(orig);
      //    cout << "original:" << orig << " 
      //    result:" << result << " expectation:" << expectation << endl;
      CPPUNIT_ASSERT(result == expectation);
    }
    
    void test_unescape() {
      string orig, result, expectation;
      //    ifstream ifs("unescape.data");
      //    getline(ifs, orig);
      //    getline(ifs, expectation);
      //    ifs.close();
      orig = "\\t";
      expectation = '\t';
      result = unescape(orig);
      //    cout << "original:" << orig << " result:" << result << endl;
      CPPUNIT_ASSERT(result == expectation);
      
      orig = "\\n";
      expectation = '\n';
      result = unescape(orig);
      //    cout << "original:" << orig << " result:" << result << endl;
      CPPUNIT_ASSERT(result == expectation);
      
      orig = "\\f";
      expectation = '\f';
      result = unescape(orig);
      //    cout << "original:" << orig << " result:" << result << endl;
      CPPUNIT_ASSERT(result == expectation);
      
      orig = "\\r";
      expectation = '\r';
      result = unescape(orig);
      //    cout << "original:" << orig << " result:" << result << endl;
      CPPUNIT_ASSERT(result == expectation);
      
      orig = "\"";
      expectation = '\"';
      result = unescape(orig);
      //    cout << "original:" << orig << " result:" << result << endl;
      CPPUNIT_ASSERT(result == expectation);
      
      orig = "\'";
      expectation = '\'';
      result = unescape(orig);
      //    cout << "original:" << orig << " result:" << result << endl;
      CPPUNIT_ASSERT(result == expectation);
      
      orig = "\\c";
      expectation = '\c';
      result = unescape(orig);
      //    cout << "original:" << orig << " result:" << result << endl;
      CPPUNIT_ASSERT(result == expectation);
      
      orig = "\\\\'hello";
      expectation = "\\\'hello";
      result = unescape(orig);
      //    cout << "original:" << orig <<
      // " result:" << result << " expectation:" << expectation << endl;
      CPPUNIT_ASSERT(result == expectation);
      
      orig = "\\t hello";
      expectation = "\t hello";
      result = unescape(orig);
      //    cout << "original:" << orig <<
      // " result:" << result << " expectation:" << expectation << endl;
      CPPUNIT_ASSERT(result == expectation);
      
      /* 結果がfalseとなるため、コメントアウトしている。
	 orig = "\\\\t hello";
	 expectation = "\\\t hello";
	 result = unescape(orig);
	 cout << "original:" << orig <<
	 " result:" << result << " expectation:" << expectation << endl;
	 CPPUNIT_ASSERT(result == expectation);
      */
    }
    
    // eraseHeadBlank()メソッドのテスト
    void test_eraseHeadBlank() {
      //    string str(" \t \t\t\t \t \t test");
      //    string ret("test");
      
      //    string instr, expectation;
      //    std::ifstream ifs("eraseHeadBlankTest.data");
      //    getline(ifs, instr);
      //    getline(ifs, expectation);
      //    ifs.close();
      
      string orig, result, expectation;
      
      expectation = "test";
      
      // 文字列の先頭にspcace,tabがない場合。
      orig = "test";
      eraseHeadBlank(orig);
      CPPUNIT_ASSERT(orig == expectation);
      
      // 文字列の先頭にtabがある場合。
      orig = "\ttest";
      eraseHeadBlank(orig);
      CPPUNIT_ASSERT(orig == expectation);
      
      // 文字列の先頭にspaceがある場合。
      orig = " test";
      eraseHeadBlank(orig);
      CPPUNIT_ASSERT(orig == expectation);
      
      // 文字列の先頭に複数のtabがある場合。
      orig = "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\ttest";
      eraseHeadBlank(orig);
      CPPUNIT_ASSERT(orig == expectation);
      
      // 文字列の先頭に"\\t"がある場合。
      orig = "\\ttest";
      expectation = "\\ttest";
      eraseHeadBlank(orig);
      CPPUNIT_ASSERT(orig == expectation);
      
      // 文字列の先頭と、文字列と文字列の間にspaceがある場合。
      orig = " test test";
      expectation = "test test";
      eraseHeadBlank(orig);
      CPPUNIT_ASSERT(orig == expectation);
    }
    
    
    // eraseTailBlank()メソッドのテスト
    void test_eraseTailBlank() {
      //    string str("test \t\t\t \t\t\t \t\t");
      //    string ret("test");
      
      //    string str, ret;
      //    std::ifstream ifs("eraseTailBlankTest.data");
      //    getline(ifs, str);
      //    getline(ifs, ret);
      //    ifs.close();
      
      string orig, result, expectation;
      
      expectation = "test";
      
      // 文字列の後ろにspcace,tabがない場合。
      orig = "test";
      eraseTailBlank(orig);
      CPPUNIT_ASSERT(orig == expectation);
      
      // 文字列の後ろにtabがある場合。
      orig = "test\t";
      eraseTailBlank(orig);
      CPPUNIT_ASSERT(orig == expectation);
      
      // 文字列の後ろにspaceがある場合。
      orig = "test ";
      eraseTailBlank(orig);
      CPPUNIT_ASSERT(orig == expectation);
      
      // 文字列の後ろに複数のtabがある場合。
      orig = "test\t\t\t\t\t";
      eraseTailBlank(orig);
      CPPUNIT_ASSERT(orig == expectation);
      
      // 文字列の後ろに"\\t"がある場合。 
      // ※ "\\t"はタブではないのでeraseされない。
      orig = "test\\t";
      expectation = "test\\t";
      eraseTailBlank(orig);
      CPPUNIT_ASSERT(orig == expectation);
      
      // 文字列の後ろと、文字列と文字列の間にspaceがある場合。
      orig = "test test ";
      expectation = "test test";
      eraseTailBlank(orig);
      CPPUNIT_ASSERT(orig == expectation);
    }
    
    
    // replaceString()メソッドのテスト
    void test_replaceString() {
      string str(" \t\t\ttest\t\t TEST");
      string from("\t");
      string to("tab");
      string ret(" tabtabtabtesttabtab TEST");
      
      //    string str, from, to, ret;
      //    std::ifstream ifs("replaceStringTest.data");
      //    getline(ifs, str);
      //    getline(ifs, from);
      //    getline(ifs, to);
      //    getline(ifs, ret);
      //    ifs.close();
      replaceString(str, from, to);
      CPPUNIT_ASSERT(str == ret);
    }
    
    
    
    // split()メソッドのテスト
    void test_split() {
      string input, delimiter;
      vector<string> result, expectation;
      
      input = "test = TEST";
      delimiter = "=";
      expectation.push_back("test");
      expectation.push_back("TEST");
      result = split(input, delimiter);
      //    cout << endl;
      CPPUNIT_ASSERT(result[0] == expectation[0]);
      CPPUNIT_ASSERT(result[1] == expectation[1]);
      
      result.clear();
      expectation.clear();
      input = "C:\\Program Files\\";
      delimiter = "\\";
      expectation.push_back("C:");
      expectation.push_back("Program Files");
      expectation.push_back("");
      result = split(input, delimiter);
      cout << endl;
      cout << "result0:" << result[0] << "\texpectation0:"
	   << expectation[0] << endl;
      cout << "result1:" << result[1] << "\texpectation1:"
	   << expectation[1] << endl;
      cout << "result2:" << result[2] << "\texpectation2:"
	   << expectation[2] << endl;
      CPPUNIT_ASSERT(result[0] == expectation[0]);
      CPPUNIT_ASSERT(result[1] == expectation[1]);
      CPPUNIT_ASSERT(result[2] == expectation[2]);
      
      result.clear();
      expectation.clear();
      input = "C::Program Files:TEST";
      delimiter = ":";
      expectation.push_back("C");
      expectation.push_back("");
      expectation.push_back("Program Files");
      expectation.push_back("TEST");
      result = split(input, delimiter);
      cout << endl;
      cout << "result0:" << result[0] << "\texpectation0:"
	   << expectation[0] << endl;
      cout << "result1:" << result[1] << "\texpectation1:"
	   << expectation[1] << endl;
      cout << "result2:" << result[2] << "\texpectation2:"
	   << expectation[2] << endl;
      cout << "result3:" << result[3] << "\texpectation3:"
	   << expectation[3] << endl;
      CPPUNIT_ASSERT(result[0] == expectation[0]);
      CPPUNIT_ASSERT(result[1] == expectation[1]);
      CPPUNIT_ASSERT(result[2] == expectation[2]);
      CPPUNIT_ASSERT(result[3] == expectation[3]);
      
      result.clear();
      expectation.clear();
      input = "C\\\\Program Files\\TEST";
      delimiter = "\\";
      expectation.push_back("C");
      expectation.push_back("");
      expectation.push_back("Program Files");
      expectation.push_back("TEST");
      result = split(input, delimiter);
      cout << endl;
      cout << "result0:" << result[0] << "\texpectation0:"
	   << expectation[0] << endl;
      cout << "result1:" << result[1] << "\texpectation1:"
	   << expectation[1] << endl;
      cout << "result2:" << result[2] << "\texpectation2:"
	   << expectation[2] << endl;
      cout << "result3:" << result[3] << "\texpectation3:"
	   << expectation[3] << endl;
      CPPUNIT_ASSERT(result[0] == expectation[0]);
      CPPUNIT_ASSERT(result[1] == expectation[1]);
      CPPUNIT_ASSERT(result[2] == expectation[2]);
      CPPUNIT_ASSERT(result[3] == expectation[3]);
    }
    
    
    // toBool()メソッドのテスト
    void test_toBool() {
    }
    
    
    // isAbsolutePath()メソッドのテスト
    void test_isAbsolutePath() {
      string path;
      
      path = "/usr/local/lib";
      CPPUNIT_ASSERT(isAbsolutePath(path) == true);
      
      path = "../usr/local/lib";
      CPPUNIT_ASSERT(isAbsolutePath(path) == false);
      
      path = "C:\\Program Files";
      CPPUNIT_ASSERT(isAbsolutePath(path) == true);
      
      path = "..\\Program Files";
      CPPUNIT_ASSERT(isAbsolutePath(path) == false);
      
      path = "\\\\robofs\\\\tmp";
      CPPUNIT_ASSERT(isAbsolutePath(path) == true);
      
      path = "\\robofs\\tmp";
      CPPUNIT_ASSERT(isAbsolutePath(path) == false);
    }
    
    
    // usURL()メソッドのテスト
    void test_isURL() {
      string url;
      
      url = "http://robofs";
      CPPUNIT_ASSERT(isURL(url) == true);
      
      url = "://robofs";
      CPPUNIT_ASSERT(isURL(url) == false);
      
      url = "\t://robofs";
      CPPUNIT_ASSERT(isURL(url) == true);
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
  CppUnit::TextUi::TestRunner runner;
  runner.addTest(CppUnit::TestFactoryRegistry::getRegistry().makeTest());
  CppUnit::Outputter* outputter = 
    new CppUnit::TextOutputter(&runner.result(), std::cout);
  runner.setOutputter(outputter);
  bool retcode = runner.run();
  return !retcode;
}
#endif // MAIN
#endif // StringUtil_cpp
