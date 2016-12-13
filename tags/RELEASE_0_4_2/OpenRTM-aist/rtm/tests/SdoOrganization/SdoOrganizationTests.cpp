// -*- C++ -*-
/*!
 * @file   SdoOrganizationTests.cpp
 * @brief  SdoOrganization test class
 * @date   $Date: 2006-11-27 08:37:43 $
 * @author Shinji Kurihara
 *         Noriaki Ando <n-ando@aist.go.jp>
 *
 * * Copyright (C) 2006
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

#ifndef SdoOrganization_cpp
#define SdoOrganization_cpp

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>

#include <rtm/SdoOrganization.h>


/*!
 * @class SdoOrganizationTests class
 * @brief SdoOrganization test
 */
namespace SdoOrganization
{
  using namespace SDOPackage;
  using namespace std;
  
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
    
    /*!
     * @brief Constructor
     */
    SdoOrganizationTests()
    {
    }
    
    /*!
     * @brief Destructor
     */
    ~SdoOrganizationTests()
    {
    }
    
    /*!
     * @brief Test initialization
     */
    virtual void setUp()
    {
      m_pOi = new Organization_impl();
    }
    
    /*!
     * @brief Test finalization
     */
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
      //    char* strg;
      
      CORBA::Short rst;
      CORBA::Long rlg;
      CORBA::Float rft;
      CORBA::Double rdb;
      //    char* rstrg;
      
      NVList nvList;
      NameValue nv;
      string str;
      
      try {
	// プロパティの取得 length 0のプロパティが返される。
	get_prop = m_pOi->get_organization_property();
	cout << endl << "get property length: " << get_prop->properties.length() << endl;
	
	
	// 空のOrganizationPropertyをセットする。 OK.
	ret = m_pOi->set_organization_property(set_prop);
	
	
	nv.name = "hoge";
	ft = 11.111;
	nv.value <<= ft;
	
	nvList.length(1);
	nvList[0] = nv;
	
	set_prop.properties = nvList;
	// プロパティのセット
	ret = m_pOi->set_organization_property(set_prop);
	
	// プロパティの取得 length 1のプロパティリストを持つOrganizationPropertyが返される。
	get_prop = m_pOi->get_organization_property();
	cout << "get property length: " << get_prop->properties.length() << endl;
	
	str = (get_prop->properties[0]).name;
	(get_prop->properties[0]).value >>= rft;
	CPPUNIT_ASSERT(str == "hoge");
	CPPUNIT_ASSERT(rft == ft);
	
	
	nv.name = "hogehoge";
	ft = 22.2;
	nv.value <<= ft;
	
	nvList.length(1);
	nvList[0] = nv;
	
	set_prop.properties = nvList;
	// プロパティのセット
	ret = m_pOi->set_organization_property(set_prop);
	
	// プロパティの取得
	get_prop = m_pOi->get_organization_property();
	cout << "get property length: " << get_prop->properties.length() << endl;
	
	
	str = ((get_prop->properties[0]).name);
	(get_prop->properties[0]).value >>= rft;
	CPPUNIT_ASSERT(str == "hogehoge");
	CPPUNIT_ASSERT(rft == ft);
	
	//      nvList.length(5);
	nvList.length(4);
	
	cout << "short" << endl;
	nv.name = "short";
	st = 1;
	nv.value <<= st;
	nvList[0] = nv;
	
	cout << "long" << endl;
	nv.name = "long";
	lg = 2222;
	nv.value <<= lg;
	nvList[1] = nv;
	
	cout << "float" << endl;
	nv.name = "float";
	ft = 33.3;
	nv.value <<= ft;
	nvList[2] = nv;
	
	cout << "double" << endl;
	nv.name = "double";
	db = 3.3;
	nv.value <<= db;
	nvList[3] = nv;
	
	//      nv.name = "char";
	//      strg = "STRING";
	//      nv.value <<= CORBA::Any::from_char('C'); // ここでセグメントエラー発生
	//      cout << "char" << endl;
	//      nvList[4] = nv;
	
	
	//      cout << "string" << endl;
	//      nv.name = "string";
	//      strg = "STRING";
	//      char * p = "STRING";
	//      nv.value <<= CORBA::Any::from_string(p,7); // ここでセグメントエラー発生
	//      nvList[4] = nv;
	
	cout << "set_prop.properties" << endl;
	set_prop.properties = nvList;
	
	cout << "set in" << endl;
	ret = m_pOi->set_organization_property(set_prop);
	cout << "set out" << endl;
	
	get_prop = m_pOi->get_organization_property();
	cout << "get property length: " << get_prop->properties.length() << endl;
	
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
	
	//      str = ((get_prop->properties[4]).name);
	//      (get_prop->properties[4]).value >>= (CORBA::Any::to_char(rch));
	//      CPPUNIT_ASSERT(str == "char");
	//      CPPUNIT_ASSERT(rch == ch);
	
	//      str = ((get_prop->properties[4]).name);
	//      char * retp;
	//      (get_prop->properties[4]).value >>= CORBA::Any::to_string(retp,7);
	//      CPPUNIT_ASSERT(str == "string");
	//      CPPUNIT_ASSERT(*retp == *p);
	
      }
      catch (InvalidParameter ip) {
	cout << "InvalidParameter exception." << endl;
      }
      catch (NotAvailable na) {
	cout << "NotAvailable exception." << endl;
      }
      catch (InternalError ip) {
	cout << "InternalError exception." << endl;
      }
      catch (...) {
	cout << "othrer exception." << endl;
      }
    }
    
    
    /* tests for */
    void test_set_get_organization_property_value() {
      //    OrganizationProperty set_prop;
      //    CORBA::Boolean ret;
      //    CORBA::Short st;
      //    CORBA::Long lg;
      //    CORBA::Float ft;
      //    CORBA::Double db;
      //    NVList nvList;
      //    NameValue nv;
      //    string str;
      
      // ※ OrganizationPropertyのpropertiesが複数の要素を持つ場合,正しいvalueが返ってこない。
      //    propertiesの要素が一つの場合は問題ない。
      //    nvList.length(4);
      //    nvList.length(1);
      
      /*
	cout << "short" << endl;
	nv.name = "short";
	st = 123;
	nv.value <<= st;
	nvList[0] = nv;
	
	cout << "long" << endl;
	nv.name = "long";
	lg = 12345;
	nv.value <<= lg;
	nvList[1] = nv;
	//    nvList[0] = nv;
	//    set_prop.properties = nvList;
	//    ret = m_pOi->set_organization_property(set_prop);
	
	cout << "float" << endl;
	nv.name = "float";
	ft = 33.3;
	nv.value <<= ft;
	nvList[2] = nv;
	
	cout << "double" << endl;
	nv.name = "double";
	db = 3.3;
	nv.value <<= db;
	nvList[3] = nv;
	
	cout << "set_prop.properties" << endl;
	set_prop.properties = nvList;
	
	cout << "set in" << endl;
	ret = m_pOi->set_organization_property(set_prop);
	cout << "set out" << endl;
      */
      
      
      
      //    CORBA::Any* any;
      //    CORBA::Double retval;
      //    CORBA::Short retval;
      //    any = m_pOi->get_organization_property_value("double");
      //    (*any) >>= retval;
      
      //    cout << "retval: " << retval << endl;
      
      // Failure case
      //    CPPUNIT_ASSERT(db == retval);
      
      
      
      // OrganizationPropertyをセットしていない状況でset_organization_property_value()を呼び、
      // get_organization_property_value()を呼ぶとabortする。
      //    CORBA::Any setval;
      //    CORBA::Boolean result;
      //    CORBA::Long relong;
      //    lg = 12345;
      //    setval <<= lg;
      //    result = m_pOi->set_organization_property_value("long", setval);
      //    if (!result)
      //      cout << "error: set_organization_property_value." << endl;
      
      //    CORBA::Any* any;
      //    cout << "get in" << endl;
      //    any = m_pOi->get_organization_property_value("long");    // ここでabortする。
      //    cout << "get out" << endl;
      
      //    (*any) >>= relong;
      //    cout << "retval: " << relong << endl;
      
    }
    
    
    /* tests for */
    void test_remove_organization_property() {
      
      // remove_organization_property()が実装されていない。
      try {
	CORBA::Boolean result = m_pOi->remove_organization_property("short");
	if (!result) {
	  cout << "Couldn't remove name: short" << endl;
	}
	
      }
      catch (InvalidParameter ip) {
	cout << "InvalidParameter exception." << endl;
      }
      catch (NotAvailable na) {
	cout << "NotAvailable exception." << endl;
      }
      catch (InternalError ip) {
	cout << "InternalError exception." << endl;
      }
      catch (...) {
	cout << "othrer exception." << endl;
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
      
      // Success case.
      // default return value is 0.
      depType = m_pOi->get_dependency();
      cout << "depType: " << depType << endl;
      CPPUNIT_ASSERT(depType == 0);
      
      m_pOi->set_dependency(NO_DEPENDENCY);
      // returned value is 2.
      depType = m_pOi->get_dependency();
      CPPUNIT_ASSERT(depType == 2);
      cout << "depType: " << depType << endl;
      
      // Failure case.
      //    m_pOi->set_dependency(0); // コンパイルエラー
      //    CPPUNIT_ASSERT(depType == 3);
      //    cout << "depType: " << depType << endl;
    }
    
  };
}; // namespace SdoOrganization

/*
 * Register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(SdoOrganization::SdoOrganizationTests);

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
#endif // SdoOrganization_cpp
