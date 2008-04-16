// -*- C++ -*-
/*!
 * @file   NVUtilTests.cpp
 * @brief  NVUtil test class
 * @date   $Date: 2006-11-27 08:26:13 $
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
 * $Log: not supported by cvs2svn $
 * Revision 1.3  2006/11/15 09:47:18  kurihara
 * tests for find(),isString(),toString() are added.
 *
 * Revision 1.1  2006/11/14 07:23:16  kurihara
 * test program for NVUtil module. first commit.
 *
 */

#ifndef NVUtil_cpp
#define NVUtil_cpp

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>

#include <rtm/NVUtil.h>

/*!
 * @class NVUtilTests class
 * @brief NVUtil test
 */
namespace NVUtil
{
  using namespace NVUtil;
  using namespace std;
  
  int g_argc;
  vector<string> g_argv;
  
  class NVUtilTests
    : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(NVUtilTests);
    CPPUNIT_TEST(test_newNV);
    //  CPPUNIT_TEST(test_newNVStr);
    CPPUNIT_TEST(test_newNVChar);
    CPPUNIT_TEST(test_newNVBool);
    CPPUNIT_TEST(test_newNVOctet);
    CPPUNIT_TEST(test_copy);
    CPPUNIT_TEST(test_find);
    CPPUNIT_TEST(test_isString);
    CPPUNIT_TEST(test_toString);
    CPPUNIT_TEST_SUITE_END();
    
  private:
    
  public:
    
    /*!
     * @brief Constructor
     */
    NVUtilTests()
    {
      CORBA::ORB_var orb;
      char* argv[g_argc];
      for (int i = 0; i < g_argc; i++) {
	argv[i] = (char *)g_argv[i].c_str();
      }
      
      orb = CORBA::ORB_init(g_argc, argv);
    }
    
    /*!
     * @brief Destructor
     */
    ~NVUtilTests()
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
     * @brief newNV(char*,Value)のテスト
     *   (1) newNV()を用いCORBA::Short型のデータとnameのNameValueを取得。
     *   (2) newNV()に渡したデータと取得したNameValueの要素を比較。
     *   (3) newNV()を用いCORBA::Long型のデータとnameのNameValueを取得。
     *   (4) newNV()に渡したデータと取得したNameValueの要素を比較。
     *   (5) newNV()を用いCORBA::Float型のデータとnameのNameValueを取得。
     *   (6) newNV()に渡したデータと取得したNameValueの要素を比較。
     *   (7) newNV()を用いCORBA::Double型のデータとnameのNameValueを取得。
     *   (8) newNV()に渡したデータと取得したNameValueの要素を比較。
     */
    void test_newNV() {
      CORBA::Short  setSt, getSt;
      CORBA::Long   setLg, getLg;
      CORBA::Float  setFt, getFt;
      CORBA::Double setDl, getDl;
      SDOPackage::NameValue nv;
      string setname, getname;
      
      // (1) newNV()を用いCORBA::Short型のデータとnameのNameValueを取得。
      setSt = 1;
      nv = newNV("short", setSt);
      
      // (2) newNV()に渡したデータと取得したNameValueの要素を比較。
      setname = "short";
      getname = nv.name;
      CPPUNIT_ASSERT(getname == setname);
      nv.value >>= getSt;
      CPPUNIT_ASSERT(setSt == getSt);
      
      
      
      // (3) newNV()を用いCORBA::Long型のデータとnameのNameValueを取得。
      setLg = 999999999;
      nv = newNV("long", setLg);
      
      // (4) newNV()に渡したデータと取得したNameValueの要素を比較。
      setname = "long";
      getname = nv.name;
      CPPUNIT_ASSERT(getname == setname);
      nv.value >>= getLg;
      CPPUNIT_ASSERT(setLg == getLg);
      
      
      
      // (5) newNV()を用いCORBA::Float型のデータとnameのNameValueを取得。
      setFt = 99999.9;
      nv = newNV("float", setFt);
      
      // (6) newNV()に渡したデータと取得したNameValueの要素を比較。
      setname = "float";
      getname = nv.name;
      CPPUNIT_ASSERT(getname == setname);
      nv.value >>= getFt;
      CPPUNIT_ASSERT(setFt == getFt);
      
      
      
      // (7) newNV()を用いCORBA::Double型のデータとnameのNameValueを取得。
      setDl = 9999999.999;
      nv = newNV("double", setDl);
      
      // (8) newNV()に渡したデータと取得したNameValueの要素を比較。
      setname = "double";
      getname = nv.name;
      CPPUNIT_ASSERT(getname == setname);
      nv.value >>= getDl;
      CPPUNIT_ASSERT(setDl == getDl);
    }
    
    
    /*!
     * @brief newNV(char*,char*)のテスト
     *    (1) const char*型のnameとvalueをnewNV()に渡し、NameValueを取得する。
     */
    void test_newNVStr() {
      SDOPackage::NameValue nv;
      const char* name  = "string";
      const char* value = "string-data";
      // (1) const char*型のnameとvalueをnewNV()に渡し、NameValueを取得する。
      nv = newNV(name, value);
    }
    
    
    /*!
     * @brief newNVChar()のテスト
     *   (1) CORBA::Char型のvalueとchar*型のnameをnewNVChar()に渡し、NameValueを取得する。
     *   (2) newNVChar()にセットしたnameと取得したNameValue.nameの比較。
     *   (3) newNVChar()にセットしたvalueと取得したNameValue.valueの比較。
     */
    void test_newNVChar() {
      CORBA::Char ch = 'A', getch;
      SDOPackage::NameValue nv;
      // (1) CORBA::Char型のvalueとchar*型のnameをnewNVChar()に渡し、NameValueを取得する。
      nv = newNVChar("char", ch);
      
      string setstr, getstr;
      
      // (2) newNVChar()にセットしたnameと取得したNameValue.nameの比較。
      setstr = "char";
      getstr = nv.name;
      CPPUNIT_ASSERT(getstr == setstr);
      
      // (3) newNVChar()にセットしたvalueと取得したNameValue.valueの比較。
      nv.value >>= CORBA::Any::to_char(getch);
      CPPUNIT_ASSERT(ch == getch);
    }
    
    
    /*!
     * @brief newNVBool()のテスト
     */
    void test_newNVBool() {
      SDOPackage::NameValue nv;
      CORBA::Boolean setval=false, retval;
      
      nv = newNVBool("bool", setval);
      
      string setstr, getstr;
      
      setstr = "bool";
      getstr = nv.name;
      CPPUNIT_ASSERT(getstr == setstr);
      
      nv.value >>= CORBA::Any::to_boolean(retval);
      CPPUNIT_ASSERT(setval == retval);
    }
    
    
    /*!
     * @brief newNVOctet()のテスト
     */
    void test_newNVOctet() {
      SDOPackage::NameValue nv;
      CORBA::Octet setval=030, getval;
      
      nv = newNVOctet("octet", setval);
      
      string setstr, getstr;
      
      setstr = "octet";
      getstr = nv.name;
      CPPUNIT_ASSERT(getstr == setstr);
      
      nv.value >>= CORBA::Any::to_octet(getval);
      CPPUNIT_ASSERT(setval == getval);
    }
    
    /*!
     * @brief copy()のテスト
     *   (1) RTC::Propertiesオブジェクトの生成
     *   (2）copy()にてPropertiesオブジェクトをnvlistにコピー
     *   (3) NVList[0].valueからデータを抽出
     *   (4) copy()により引数で与えたnvlistが書き換えられているかを確認。
     */
    void test_copy() {
      SDOPackage::NVList nvlist;
      
      map<string, string> mProp;
      // (1) RTC::Propertiesオブジェクトの生成
      // ※ Propertiesのコンストラクタでは引数で与えれたmapのキー値だけが保存される。
      mProp["potr-type"];
      RTC::Properties prop(mProp);
      
      
      // (2）copy()にてPropertiesオブジェクトをnvlistにコピー
      copy(nvlist, prop);
      
      
      // (3) NVList[0].valueからデータを抽出
      const char* getval;
      nvlist[0].value >>= getval;
      
      string setstr, getstr;
      
      
      // (4) copy()により引数で与えたnvlistが書き換えられているかを確認。
      setstr = "potr-type";
      getstr = nvlist[0].name;
      CPPUNIT_ASSERT(setstr == getstr);
      
      setstr = "";
      getstr = getval;
      CPPUNIT_ASSERT(setstr == getstr);
      
    }
    
    
    /*!
     * @brief find()のテスト
     *   (1) NVList要素のnameに"short",valueにshort型のデータをセット。
     *   (2) NVList要素のnameに"long",valueにlong型のデータをセット。
     *   (3) nvlistの中からNameValue.nameが"long"のNameValue.valueを取得。
     *   (4) nvlistの中からNameValue.nameが"short"のNameValue.valueを取得。
     */
    void test_find() {
      SDOPackage::NVList nvlist;
      CORBA::Any any;
      CORBA::Short setst,getst;
      CORBA::Long  setlg,getlg;
      
      nvlist.length(2);
      
      // (1) NVList要素のnameに"short",valueにshort型のデータをセット。
      setst = 1;
      nvlist[0].name = "short";
      nvlist[0].value <<= setst;
      
      // (2) NVList要素のnameに"long",valueにlong型のデータをセット。
      setlg =111;
      nvlist[1].name = "long";
      nvlist[1].value <<= setlg;
      
      // (3) nvlistの中からNameValue.nameが"long"のNameValue.valueを取得。
      any = find(nvlist, "long");
      any >>= getlg;
      CPPUNIT_ASSERT(setlg == getlg);
      
      // (4) nvlistの中からNameValue.nameが"short"のNameValue.valueを取得。
      any = find(nvlist, "short");
      any >>= getst;
      CPPUNIT_ASSERT(setst == getst);
    }
    
    
    /*!
     * @brief isString()のテスト
     *   (1) NVList要素のnameに"short",valueにshort型のデータをセット。
     *   (2) NVList要素のnameに"string",valueにstring型のデータをセット。
     *   (3) isString(nvlist,name)にて,指定されたnameのvalueの型がstringかどうかを判定。
     *   (4) isString(nvlist,name)にて,指定されたnameのvalueの型がstringかどうかを判定。
     */
    void test_isString() {
      bool result;
      SDOPackage::NVList nvlist;
      CORBA::Short setst;
      
      nvlist.length(2);
      
      // (1) NVList要素のnameに"short",valueにshort型のデータをセット。
      setst = 1;
      nvlist[0].name = "short";
      nvlist[0].value <<= setst;
      
      // (2) NVList要素のnameに"string",valueにstring型のデータをセット。
      string str("test");
      nvlist[1].name = "string";
      nvlist[1].value <<= str.c_str();
      
      // (3) isString(nvlist,name)にて,指定されたnameのvalueの型がstringかどうかを判定。
      result = isString(nvlist, "string");
      CPPUNIT_ASSERT(result == true);
      
      // (4) isString(nvlist,name)にて,指定されたnameのvalueの型がstringかどうかを判定。
      result = isString(nvlist, "short");
      CPPUNIT_ASSERT(result == false);
      
    }
    
    
    /*!
     * @brief toString()のテスト
     *   (1) NVList要素のnameに"short",valueにshort型のデータをセット。
     *   (2) NVList要素のnameに"string",valueにstring型のデータをセット。
     *   (3) toString(nvlist,name)にて,指定されたnameのvalueをstringで取得。
     *   (4) toString(nvlist,name)にて,指定されたnameのvalueをstringで取得。
     */
    void test_toString() {
      string result;
      SDOPackage::NVList nvlist;
      CORBA::Short setst;
      
      nvlist.length(2);
      
      // (1) NVList要素のnameに"short",valueにshort型のデータをセット。
      setst = 1;
      nvlist[0].name = "short";
      nvlist[0].value <<= setst;
      
      // (2) NVList要素のnameに"string",valueにstring型のデータをセット。
      string str("test"), setstr;
      nvlist[1].name = "string";
      nvlist[1].value <<= str.c_str();
      
      // (3) toString(nvlist,name)にて,指定されたnameのvalueをstringで取得。
      result = toString(nvlist, "string");
      setstr = "test";
      CPPUNIT_ASSERT(result == setstr);
      
      // Failure case:
      // 
      // (4) toString(nvlist,name)にて,指定されたnameのvalueをstringで取得。
      result = toString(nvlist, "short");
      setstr = "";
      CPPUNIT_ASSERT(result == setstr);
    }
    
  };
}; // namespace NVUtil

/*
 * Register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(NVUtil::NVUtilTests);

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
#endif // NVUtil_cpp
