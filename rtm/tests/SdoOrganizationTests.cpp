// -*- C++ -*-
/*!
 * @file 
 * @brief Properties test class
 * @date $Date: 2006-11-09 05:29:12 $
 * @author Shinji Kurihara
 * $Id: SdoOrganizationTests.cpp,v 1.1 2006-11-09 05:29:12 kurihara Exp $
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

#include "../SdoOrganization.h"

using namespace SDOPackage;
using namespace std;

int g_argc;
vector<string> g_argv;

// SdoOrganization_impl クラスのテスト
class SdoOrganizationTests
  : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(SdoOrganizationTests);
  CPPUNIT_TEST(test_get_organization_id);
  CPPUNIT_TEST(test_set_get_organization_property);
  CPPUNIT_TEST(test_set_get_organization_property_value);
  CPPUNIT_TEST(test_remove_organization_property);
  CPPUNIT_TEST(test_set_get_owner);
  CPPUNIT_TEST(test_set_get_members);
  CPPUNIT_TEST(test_add_members);
  CPPUNIT_TEST(test_remove_member);
  CPPUNIT_TEST(test_set_get_dependency);
  CPPUNIT_TEST_SUITE_END();

private:
  Organization_impl* m_pOi;
  char* m_id;

public:
  
  /*
   * コンストラクタ/デストラクタ
   */
  SdoOrganizationTests()
  {
    char* argv[g_argc];
    for (int i = 0; i < g_argc; i++) {
      argv[i] = (char *)g_argv[i].c_str();
    }

    CORBA::ORB_var orb;
    orb = CORBA::ORB_init(g_argc, argv);    
  }
  
  ~SdoOrganizationTests()
  {
  }
  
  /*
   * 初期化/後始末
   */
  virtual void setUp()
  {
    m_pOi = new Organization_impl();
  }
  
  virtual void tearDown()
  { 
    delete m_pOi;
  }

  /* tests for char* get_organization_id() */
  void test_get_organization_id() {
    m_id = m_pOi->get_organization_id();
  }


  /* tests for OrganizationProperty* get_organization_property()
   *           CORBA::Boolean set_organization_property(OrganizationProperty& org_property)
   */
  void test_set_get_organization_property() {
    OrganizationProperty_var get_prop;
    OrganizationProperty set_prop;
    CORBA::Boolean ret;
    CORBA::Short st;
    CORBA::Long lg;
    CORBA::Float ft;
    CORBA::Double db;
    CORBA::Char ch;
    char* strg; // string

    CORBA::Short rst;
    CORBA::Long rlg;
    CORBA::Float rft;
    CORBA::Double rdb;
    CORBA::Char rch;
    char* rstrg; // string

    NVList nvList;
    NameValue nv;
    string str;

    try {
      // プロパティの取得 length 0のプロパティが返される。
      get_prop = m_pOi->get_organization_property();

      // 空のOrganizationPropertyをセットする。 OK.
      ret = m_pOi->set_organization_property(set_prop);


      nvList.length(1);

      // float data
      nv.name = "float1";
      ft = 11.111;
      nv.value <<= ft;
      nvList[0] = nv;
      set_prop.properties = nvList;

      // プロパティのセット
      ret = m_pOi->set_organization_property(set_prop);
      
      // プロパティの取得 length 1のプロパティリストを持つOrganizationPropertyが返される。
      get_prop = m_pOi->get_organization_property();
      
      str = (get_prop->properties[0]).name;
      (get_prop->properties[0]).value >>= rft;
      CPPUNIT_ASSERT(str == "float1");
      CPPUNIT_ASSERT(rft == ft);
      

      //======== set_organization_property()で上書きされるかのテスト ====================
      nv.name = "float2";
      ft = 22.2;
      nv.value <<= ft;
      nvList[0] = nv;
      set_prop.properties = nvList;

      // プロパティのセット
      ret = m_pOi->set_organization_property(set_prop);
      
      // プロパティの取得
      get_prop = m_pOi->get_organization_property();
      
      str = ((get_prop->properties[0]).name);
      (get_prop->properties[0]).value >>= rft;
      CPPUNIT_ASSERT(str == "float2");
      CPPUNIT_ASSERT(rft == ft);
      //=================================================================================


      //===== OrganizationProperty.propertiesの要素が複数の場合のテスト ========
      nvList.length(6);

      // set short data 
      nv.name = "short";
      st = 1;
      nv.value <<= st;
      nvList[0] = nv;

      // set long data
      nv.name = "long";
      lg = 2222;
      nv.value <<= lg;
      nvList[1] = nv;

      // set flaot data
      nv.name = "float";
      ft = 33.3;
      nv.value <<= ft;
      nvList[2] = nv;

      // set double data
      nv.name = "double";
      db = 3.3;
      nv.value <<= db;
      nvList[3] = nv;

      // set char data
      nv.name = "char";
      ch = 'C';
      nv.value <<= CORBA::Any::from_char(ch);
      nvList[4] = nv;

      // set string data
      nv.name = "string";
      strg = "test data";
      nv.value <<= CORBA::Any::from_string(strg,7);
      nvList[5] = nv;

      set_prop.properties = nvList;


      // test set_organization_property()
      ret = m_pOi->set_organization_property(set_prop);


      // test get_organization_property()
      get_prop = m_pOi->get_organization_property();


      str = ((get_prop->properties[0]).name);
      (get_prop->properties[0]).value >>= rst;
      CPPUNIT_ASSERT(str == "short");
      CPPUNIT_ASSERT(rst == st);

      str = ((get_prop->properties[1]).name);
      (get_prop->properties[1]).value >>= rlg;
      CPPUNIT_ASSERT(str == "long");
      CPPUNIT_ASSERT(rlg == lg);

      str = ((get_prop->properties[2]).name);
      (get_prop->properties[2]).value >>= rft;
      CPPUNIT_ASSERT(str == "float");
      CPPUNIT_ASSERT(rft == ft);

      str = ((get_prop->properties[3]).name);
      (get_prop->properties[3]).value >>= rdb;
      CPPUNIT_ASSERT(str == "double");
      CPPUNIT_ASSERT(rdb == db);

      str = ((get_prop->properties[4]).name);
      (get_prop->properties[4]).value >>= (CORBA::Any::to_char(rch));
      CPPUNIT_ASSERT(str == "char");
      CPPUNIT_ASSERT(rch == ch);

      str = ((get_prop->properties[5]).name);
      (get_prop->properties[5]).value >>= (CORBA::Any::to_string(rstrg,7));
      CPPUNIT_ASSERT(str == "string");
      string setstr, getstr;
      setstr = strg;
      getstr = rstrg;
      CPPUNIT_ASSERT(getstr == setstr);
      //==================================================================

    }
    catch (InvalidParameter ip) {
      cout << "InvalidParameter exception. set/get_organization_property" << endl;
    }
    catch (NotAvailable na) {
      cout << "NotAvailable exception. set/get_organization_property" << endl;
    }
    catch (InternalError ip) {
      cout << "InternalError exception. set/get_organization_property" << endl;
    }
    catch (...) {
      cout << "othrer exception. set/get_organization_property" << endl;
    }
  }


  /* tests for */
  void test_set_get_organization_property_value() {
    OrganizationProperty set_prop;
    CORBA::Boolean ret;
    CORBA::Short st;
    CORBA::Long lg;
    CORBA::Float ft;
    CORBA::Double db;
    NVList nvList;
    NameValue nv;
    string str;

    nvList.length(4);

    nv.name = "short";
    st = 123;
    nv.value <<= st;
    nvList[0] = nv;

    nv.name = "long";
    lg = 12345;
    nv.value <<= lg;
    nvList[1] = nv;
    
    nv.name = "float";
    ft = 33.3;
    nv.value <<= ft;
    nvList[2] = nv;
    
    nv.name = "double";
    db = 3.3;
    nv.value <<= db;
    nvList[3] = nv;

    set_prop.properties = nvList;
    
    ret = m_pOi->set_organization_property(set_prop);


    CORBA::Any* any;
    CORBA::Short retst;
    CORBA::Long retlg;
    CORBA::Float retft;
    CORBA::Double retdb;

    //    CORBA::Short retval;
    any = m_pOi->get_organization_property_value("double");
    (*any) >>= retdb;
    CPPUNIT_ASSERT(db == retdb);

    any = m_pOi->get_organization_property_value("short");
    (*any) >>= retst;
    CPPUNIT_ASSERT(st == retst);

    any = m_pOi->get_organization_property_value("long");
    (*any) >>= retlg;
    CPPUNIT_ASSERT(lg == retlg);

    any = m_pOi->get_organization_property_value("float");
    (*any) >>= retft;
    CPPUNIT_ASSERT(ft == retft);


    CORBA::Any setval;
    CORBA::Boolean result;
    CORBA::Long relong;
    lg = 12345;
    setval <<= lg;
    result = m_pOi->set_organization_property_value("long", setval);
    if (!result)
      cout << "error: set_organization_property_value." << endl;

    any = m_pOi->get_organization_property_value("long");    // ここでabortする。

    (*any) >>= relong;
    CPPUNIT_ASSERT(relong == lg);
  }


  /* tests for */
  void test_remove_organization_property() {
    // OrbanizationPropertyのセット
    test_set_get_organization_property();

    try {
      CORBA::Boolean result = m_pOi->remove_organization_property("short");
      if (!result) {
	cout << "Couldn't remove name: short" << endl;
      }
      
    }
    catch (InvalidParameter ip) {
      cout << "InvalidParameter exception. remove_organization_property" << endl;
    }
    catch (NotAvailable na) {
      cout << "NotAvailable exception. remove_organization_property" << endl;
    }
    catch (InternalError ip) {
      cout << "InternalError exception. remove_organization_property" << endl;
    }
    catch (...) {
      cout << "othrer exception. remove_organization_property" << endl;
    }

  }


  /* tests for */
  void test_set_get_owner() {
  }


  /* tests for */
  void test_set_get_members() {
  }


  /* tests for */
  void test_add_members() {
  }


  /* tests for */
  void test_remove_member() {
  }


  /* tests for */
  void test_set_get_dependency() {
    DependencyType depType;

    // Failure case.
    //    depType = m_pOi->get_dependency();
    //    CPPUNIT_ASSERT(depType == 0);

    m_pOi->set_dependency(NO_DEPENDENCY);
    // returned value is 2.
    depType = m_pOi->get_dependency();
    CPPUNIT_ASSERT(depType == 2);

    // Failure case.
    //    m_pOi->set_dependency(0); // コンパイルエラー
    //    CPPUNIT_ASSERT(depType == 3);
    //    cout << "depType: " << depType << endl;
  }

};


/*
 * register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(SdoOrganizationTests);



int main(int argc, char* argv[])
{
  g_argc = argc;
  for (int i = 0; i < argc; i++) {
    g_argv.push_back(argv[i]);
  }
  
  CppUnit::TextUi::TestRunner runner;
  
  runner.addTest(CppUnit::TestFactoryRegistry::getRegistry().makeTest());
  CppUnit::Outputter* outputter = 
    new CppUnit::TextOutputter(&runner.result(), std::cout);
  runner.setOutputter(outputter);
  
  return runner.run();
}
