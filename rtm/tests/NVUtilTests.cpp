// -*- C++ -*-
/*!
 * @file 
 * @brief test for NVUtil module.
 * @date $Date: 2006-11-14 07:23:16 $
 * @author Shinji Kurihara
 * $Id: NVUtilTests.cpp,v 1.1 2006-11-14 07:23:16 kurihara Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 */

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>

#include "../NVUtil.h"

using namespace NVUtil;
using namespace std;

// NVUtil module のテスト
class NVUtilTests
  : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(NVUtilTests);
  CPPUNIT_TEST(test_newNV);
  CPPUNIT_TEST(test_newNVStr);
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
   * @brief コンストラクタ
   */
  NVUtilTests()
  {
  }


  /*!
   * @brief デストラクタ
   */
  ~NVUtilTests()
  {
  }
  
  /*!
   * @brief 初期化
   */
  virtual void setUp()
  {
  }
  

  /*!
   * @brief 後始処理
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
   */
  void test_newNVChar() {
  }


  /*!
   * @brief newNVBool()のテスト
   */
  void test_newNVBool() {}


  /*!
   * @brief newNVOctet()のテスト
   */
  void test_newNVOctet() {}


  /*!
   * @brief copy()のテスト
   */
  void test_copy() {}


  /*!
   * @brief find()のテスト
   */
  void test_find() {}


  /*!
   * @brief isString()のテスト
   */
  void test_isString() {}


  /*!
   * @brief toString()のテスト
   */
  void test_toString() {}

};


/*!
 * @brief register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(NVUtilTests);



int main(int argc, char* argv[])
{
    CppUnit::TextUi::TestRunner runner;

    runner.addTest(CppUnit::TestFactoryRegistry::getRegistry().makeTest());
    CppUnit::Outputter* outputter = 
      new CppUnit::TextOutputter(&runner.result(), std::cout);
    runner.setOutputter(outputter);
   
    return runner.run();
}
