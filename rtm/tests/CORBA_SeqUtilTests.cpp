// -*- C++ -*-
/*!
 * @file 
 * @brief Properties test class
 * @date $Date: 2006-10-31 13:10:51 $
 * @author Shinji Kurihara
 * $Id: CORBA_SeqUtilTests.cpp,v 1.1 2006-10-31 13:10:51 kurihara Exp $
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

#include "../CORBA_SeqUtil.h"
#include "SeqUtilTests.hh"

using namespace std;

// CORBA_SeqUtil.hのテスト
class CORBA_SeqUtilTests
  : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(CORBA_SeqUtilTests);
  CPPUNIT_TEST(test_for_each);
  CPPUNIT_TEST(test_find);
  CPPUNIT_TEST(test_push_back);
  CPPUNIT_TEST(test_push_back_list);
  //  CPPUNIT_TEST(test_insert);
  CPPUNIT_TEST(test_front);
  CPPUNIT_TEST(test_back);
  CPPUNIT_TEST(test_erase);
  CPPUNIT_TEST(test_erase_if);
  CPPUNIT_TEST(test_clear);
  CPPUNIT_TEST_SUITE_END();

private:
  NameValue nv;
  NVList nvlist;
  CORBA::Short  st, rst;
  CORBA::Long   lg, rlg;
  CORBA::Float  ft, rft;
  CORBA::Double dl, rdl;
  
public:
  
  /*
   * コンストラクタ/デストラクタ
   */
  CORBA_SeqUtilTests()
  {
    
  }
  
  ~CORBA_SeqUtilTests()
  {
  }
  
  /*
   * 初期化/後始末
   */
  virtual void setUp()
  {
    nvlist.length(4);
    
    st = 10;
    lg = 100;
    ft = 111.1;
    dl = 22222222.222;

    nv.name = "short";
    nv.value <<= st;
    nvlist[0] = nv;

    nv.name = "long";
    nv.value <<= lg;
    nvlist[1] = nv;

    nv.name = "float";
    nv.value <<= ft;
    nvlist[2] = nv;

    nv.name = "double";
    nv.value <<= dl;
    nvlist[3] = nv;

    rst = 0;
    rlg = 0;
    rft = 0.0;
    rdl = 0.0;
  }
  
  virtual void tearDown()
  { 
  }


  /* tests for */
  void test_for_each() {
    CORBA_SeqUtil::for_each(nvlist, for_eachFunc("test"));
  }


  /* tests for */
  void test_find() {
    CORBA::Long index;

    index = CORBA_SeqUtil::find(nvlist, findFuncStr("double"));
    CPPUNIT_ASSERT((CORBA::Long)3 == index);

    index = CORBA_SeqUtil::find(nvlist, findFuncStr("float"));
    CPPUNIT_ASSERT((CORBA::Long)2 == index);

    index = CORBA_SeqUtil::find(nvlist, findFuncStr("long"));
    CPPUNIT_ASSERT((CORBA::Long)1 == index);

    index = CORBA_SeqUtil::find(nvlist, findFuncStr("short"));
    CPPUNIT_ASSERT((CORBA::Long)0 == index);
  }


  /* tests for */
  void test_push_back() {
    nv.name = "short";
    CORBA::Short st2, rst2;
    st2 = 20;
    nv.value <<= st2;
    string setstr, retstr;
    
    for (int i = 0; i < 100; i++) {
      CORBA_SeqUtil::push_back(nvlist, nv);
    }
    
    setstr = "short";
    retstr = nvlist[0].name;
    nvlist[0].value >>= rst;
    CPPUNIT_ASSERT(setstr == retstr);
    CPPUNIT_ASSERT(st == rst);
    
    setstr = "long";
    retstr = nvlist[1].name;
    nvlist[1].value >>= rlg;
    CPPUNIT_ASSERT(setstr == retstr);
    CPPUNIT_ASSERT(lg == rlg);
    
    setstr = "float";
    retstr = nvlist[2].name;
    nvlist[2].value >>= rft;
    CPPUNIT_ASSERT(setstr == retstr);
    CPPUNIT_ASSERT(ft == rft);
    
    setstr = "double";
    retstr = nvlist[3].name;
    nvlist[3].value >>= rdl;
    CPPUNIT_ASSERT(setstr == retstr);
    CPPUNIT_ASSERT(dl == rdl);
    
    setstr = "short";
    for (int i = 4; i < 104; i++) {
      retstr = nvlist[i].name;
      nvlist[i].value >>= rst2;
      CPPUNIT_ASSERT(setstr == retstr);
      CPPUNIT_ASSERT(st2 == rst2);
    }
  }


  /* tests for */
  void test_push_back_list() {
    NameValue nv2;
    NVList nvlist2;
    CORBA::Short  st2;
    CORBA::Long   lg2;
    CORBA::Float  ft2;
    CORBA::Double dl2;
    string setstr, retstr;
    
    nvlist2.length(4);
    
    st2 = 32767;
    lg2 = 999999999;
    ft2 = 999999.9;
    dl2 = 99999999999.99;

    nv2.name = "short2";
    nv2.value <<= st2;
    nvlist2[0] = nv2;

    nv2.name = "long2";
    nv2.value <<= lg2;
    nvlist2[1] = nv2;

    nv2.name = "float2";
    nv2.value <<= ft2;
    nvlist2[2] = nv2;

    nv2.name = "double2";
    nv2.value <<= dl2;
    nvlist2[3] = nv2;
    
    CORBA_SeqUtil::push_back_list(nvlist, nvlist2);

    setstr = "short";
    retstr = nvlist[0].name;
    nvlist[0].value >>= rst;
    CPPUNIT_ASSERT(setstr == retstr);
    CPPUNIT_ASSERT(st == rst);
    
    setstr = "long";
    retstr = nvlist[1].name;
    nvlist[1].value >>= rlg;
    CPPUNIT_ASSERT(setstr == retstr);
    CPPUNIT_ASSERT(lg == rlg);
    
    setstr = "float";
    retstr = nvlist[2].name;
    nvlist[2].value >>= rft;
    CPPUNIT_ASSERT(setstr == retstr);
    CPPUNIT_ASSERT(ft == rft);
    
    setstr = "double";
    retstr = nvlist[3].name;
    nvlist[3].value >>= rdl;
    CPPUNIT_ASSERT(setstr == retstr);
    CPPUNIT_ASSERT(dl == rdl);

    setstr = "short2";
    retstr = nvlist[4].name;
    nvlist[4].value >>= rst;
    CPPUNIT_ASSERT(setstr == retstr);
    CPPUNIT_ASSERT(st2 == rst);
    
    setstr = "long2";
    retstr = nvlist[5].name;
    nvlist[5].value >>= rlg;
    CPPUNIT_ASSERT(setstr == retstr);
    CPPUNIT_ASSERT(lg2 == rlg);
    
    setstr = "float2";
    retstr = nvlist[6].name;
    nvlist[6].value >>= rft;
    CPPUNIT_ASSERT(setstr == retstr);
    CPPUNIT_ASSERT(ft2 == rft);
    
    setstr = "double2";
    retstr = nvlist[7].name;
    nvlist[7].value >>= rdl;
    CPPUNIT_ASSERT(setstr == retstr);
    CPPUNIT_ASSERT(dl2 == rdl);

  }


  /* tests for */
  void test_insert() {
    string setstr, retstr;
    nv.name = "short-insert";
    CORBA::Short st2, rst2;
    st2 = 20;
    nv.value <<= st2;
    CORBA::ULong index;

    index = nvlist.length();
    // 例外発生!!!!!!!
    CORBA_SeqUtil::insert(nvlist, nv, index);
    

    setstr = "short-insert";
    retstr = nvlist[0].name;
    nvlist[0].value >>= rst2;
    CPPUNIT_ASSERT(setstr == retstr);
    CPPUNIT_ASSERT(st2 == rst2);

    setstr = "short";
    retstr = nvlist[1].name;
    nvlist[1].value >>= rst;
    CPPUNIT_ASSERT(setstr == retstr);
    CPPUNIT_ASSERT(st == rst);
    
    setstr = "long";
    retstr = nvlist[2].name;
    nvlist[2].value >>= rlg;
    CPPUNIT_ASSERT(setstr == retstr);
    CPPUNIT_ASSERT(lg == rlg);
    
    setstr = "float";
    retstr = nvlist[3].name;
    nvlist[3].value >>= rft;
    CPPUNIT_ASSERT(setstr == retstr);
    CPPUNIT_ASSERT(ft == rft);
    
    setstr = "double";
    retstr = nvlist[4].name;
    nvlist[4].value >>= rdl;
    CPPUNIT_ASSERT(setstr == retstr);
    CPPUNIT_ASSERT(dl == rdl);
  }


  /* tests for */
  void test_front() {
    string setstr, retstr;
    CORBA::Short retval;
    NameValue retnv;

    for (int i = 0; i < 100; i++) {
      retnv = CORBA_SeqUtil::front<NVList, NameValue>(nvlist);

      setstr = "short";
      retstr = retnv.name;
      retnv.value >>= retval;
      
      CPPUNIT_ASSERT(retval == st);
    }
  }


  /* tests for */
  void test_back() {
    string setstr, retstr;
    CORBA::Double retval;
    NameValue retnv;

    for (int i = 0; i < 100; i++) {
      retnv = CORBA_SeqUtil::back<NVList, NameValue>(nvlist);

      setstr = "double";
      retstr = retnv.name;
      retnv.value >>= retval;

      CPPUNIT_ASSERT(retval == dl);
    }
  }

  /* tests for */
  void test_erase() {
    string setstr, retstr;
    CORBA::ULong index; // OK.

    // Success case
    //    index = 0;
    /*
    CORBA_SeqUtil::erase(nvlist, index);
    
    setstr = "long";
    retstr = nvlist[0].name;
    nvlist[0].value >>= rlg;
    CPPUNIT_ASSERT(setstr == retstr);
    CPPUNIT_ASSERT(lg == rlg);
    
    setstr = "float";
    retstr = nvlist[1].name;
    nvlist[1].value >>= rft;
    CPPUNIT_ASSERT(setstr == retstr);
    CPPUNIT_ASSERT(ft == rft);
    
    setstr = "double";
    retstr = nvlist[2].name;
    nvlist[2].value >>= rdl;
    CPPUNIT_ASSERT(setstr == retstr);
    CPPUNIT_ASSERT(dl == rdl);
    */

    /*
    index = 1;
    CORBA_SeqUtil::erase(nvlist, index);
    
    setstr = "short";
    retstr = nvlist[0].name;
    nvlist[0].value >>= rst;
    CPPUNIT_ASSERT(setstr == retstr);
    CPPUNIT_ASSERT(st == rst);
    
    setstr = "float";
    retstr = nvlist[1].name;
    nvlist[1].value >>= rft;
    CPPUNIT_ASSERT(setstr == retstr);
    CPPUNIT_ASSERT(ft == rft);
    
    setstr = "double";
    retstr = nvlist[2].name;
    nvlist[2].value >>= rdl;
    CPPUNIT_ASSERT(setstr == retstr);
    CPPUNIT_ASSERT(dl == rdl);
    */

    index = 6; // 何も削除されない。
    CORBA_SeqUtil::erase(nvlist, index);

    setstr = "short";
    retstr = nvlist[0].name;
    nvlist[0].value >>= rst;
    CPPUNIT_ASSERT(setstr == retstr);
    CPPUNIT_ASSERT(st == rst);
    
    setstr = "long";
    retstr = nvlist[1].name;
    nvlist[1].value >>= rlg;
    CPPUNIT_ASSERT(setstr == retstr);
    CPPUNIT_ASSERT(lg == rlg);
    
    setstr = "float";
    retstr = nvlist[2].name;
    nvlist[2].value >>= rft;
    CPPUNIT_ASSERT(setstr == retstr);
    CPPUNIT_ASSERT(ft == rft);
  }


  /* tests for */
  void test_erase_if() {
    string setstr, retstr;

    // 何も削除されない。
    CORBA_SeqUtil::erase_if(nvlist, erase_ifFunc("test"));
    setstr = "short";
    retstr = nvlist[0].name;
    nvlist[0].value >>= rst;
    CPPUNIT_ASSERT(setstr == retstr);
    CPPUNIT_ASSERT(st == rst);
    
    setstr = "long";
    retstr = nvlist[1].name;
    nvlist[1].value >>= rlg;
    CPPUNIT_ASSERT(setstr == retstr);
    CPPUNIT_ASSERT(lg == rlg);
    
    setstr = "float";
    retstr = nvlist[2].name;
    nvlist[2].value >>= rft;
    CPPUNIT_ASSERT(setstr == retstr);
    CPPUNIT_ASSERT(ft == rft);
    
    setstr = "double";
    retstr = nvlist[3].name;
    nvlist[3].value >>= rdl;
    CPPUNIT_ASSERT(setstr == retstr);
    CPPUNIT_ASSERT(dl == rdl);



    CORBA_SeqUtil::erase_if(nvlist, erase_ifFunc("double"));
    setstr = "short";
    retstr = nvlist[0].name;
    nvlist[0].value >>= rst;
    CPPUNIT_ASSERT(setstr == retstr);
    CPPUNIT_ASSERT(st == rst);
    
    setstr = "long";
    retstr = nvlist[1].name;
    nvlist[1].value >>= rlg;
    CPPUNIT_ASSERT(setstr == retstr);
    CPPUNIT_ASSERT(lg == rlg);
    
    setstr = "float";
    retstr = nvlist[2].name;
    nvlist[2].value >>= rft;
    CPPUNIT_ASSERT(setstr == retstr);
    CPPUNIT_ASSERT(ft == rft);



    CORBA_SeqUtil::erase_if(nvlist, erase_ifFunc("short"));
    setstr = "long";
    retstr = nvlist[0].name;
    nvlist[0].value >>= rlg;
    CPPUNIT_ASSERT(setstr == retstr);
    CPPUNIT_ASSERT(lg == rlg);
    
    setstr = "float";
    retstr = nvlist[1].name;
    nvlist[1].value >>= rft;
    CPPUNIT_ASSERT(setstr == retstr);
    CPPUNIT_ASSERT(ft == rft);



    CORBA_SeqUtil::erase_if(nvlist, erase_ifFunc("long"));
    setstr = "float";
    retstr = nvlist[0].name;
    nvlist[0].value >>= rft;
    CPPUNIT_ASSERT(setstr == retstr);
    CPPUNIT_ASSERT(ft == rft);


    CORBA_SeqUtil::erase_if(nvlist, erase_ifFunc("float"));
    cout << endl << "Length after having called erase_if(): " << nvlist.length() << endl;
  }


  /* tests for */
  void test_clear() {
    CORBA_SeqUtil::clear(nvlist);
    cout << endl << "Length after having called clear(): " << nvlist.length() << endl;
  }

protected:

  struct nv_name
  {
    nv_name(const char* name) : m_name(name) {};
    bool operator()(const NameValue& nv)
    {
      return m_name == std::string(nv.name);
    }
    std::string m_name;
  };

  struct for_eachFunc
  {
    for_eachFunc(const char* name) : m_name(name) {};
    bool operator()(const NameValue& nv)
    {
      cout << nv.name << " " << m_name << endl;
      CORBA::Short  rst;
      CORBA::Long   rlg;
      CORBA::Float  rft;
      CORBA::Double rdl;

      if (nv.value.type() == CORBA::_tc_short) {
	nv.value >>= rst;
	cout << rst << endl;
      }
      else if (nv.value.type() == CORBA::_tc_long) {
	nv.value >>= rlg;
	cout << rlg << endl;
      }
      else if (nv.value.type() == CORBA::_tc_float) {
	nv.value >>= rft;
	cout << rft << endl;
      }
      else if (nv.value.type() == CORBA::_tc_double) {
	nv.value >>= rdl;
	cout << rdl << endl;
      }

      return m_name == std::string(nv.name);
    }
    std::string m_name;
  };
  
  struct findFuncStr
  {
    findFuncStr(const char* name) : m_name(name) {};
    bool operator()(const NameValue& nv)
    {
      return m_name == std::string(nv.name);
    }
    std::string m_name;
  };

  struct erase_ifFunc
  {
    erase_ifFunc(const char* name) : m_name(name) {};
    bool operator()(const NameValue& nv)
    {
      return m_name == std::string(nv.name);
    }
    std::string m_name;
  };

  /*
  template<typename T>
  struct findFuncData
  {
    findFuncData(const T data) : m_data(data) {};
    bool operator()(const NameValue& nv)
    {
      CORBA::Short  rst;
      CORBA::Long   rlg;
      CORBA::Float  rft;
      CORBA::Double rdl;
      if (data.type() == CORBA::_tc_short && nv.value.type() == CORBA::_tc_short) {
	nv.value >>= rst;
	return m_data == rst;
      }
      else if (data.type() == CORBA::_tc_long && nv.value.type() == CORBA::_tc_long) {
	nv.value >>= rlg;
	return m_data == rlg;
      }
      else if (data.type() == CORBA::_tc_float && nv.value.type() == CORBA::_tc_float) {
	nv.value >>= rft;
	return m_data == rft;
      }
      else if (data.type() == CORBA::_tc_double && nv.value.type() == CORBA::_tc_double) {
	nv.value >>= rdl;
	return m_data == rdl;
      }
      return false;
    }
    T m_data;
  };
  */

  /*
    template<typename T, typename CorbaSequence>
  struct sequence_data
  {
    sequence_data(const T data) : m_data(data) {};

    bool operator()(const CorbaSequence& cseq)
    {
      return m_data == std::string(nv.name);
    }
    std::string m_name;
  };
  */
};


/*
 * register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(CORBA_SeqUtilTests);



int main(int argc, char* argv[])
{
    CppUnit::TextUi::TestRunner runner;

    runner.addTest(CppUnit::TestFactoryRegistry::getRegistry().makeTest());
    CppUnit::Outputter* outputter = 
      new CppUnit::TextOutputter(&runner.result(), std::cout);
    runner.setOutputter(outputter);
   
    return runner.run();
}
