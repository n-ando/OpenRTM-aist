// -*- C++ -*-
/*!
 * @file   ObjectManagerTests.cpp
 * @brief  ObjectManager test class
 * @date   $Date: 2006-11-27 08:26:00 $
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
 * $Id: ObjectManagerTests.cpp,v 1.1 2006-11-27 08:26:00 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.2  2006/10/24 03:08:15  kurihara
 *
 * test program for ObjectManager class
 *
 */

#ifndef ObjectManager_cpp
#define ObjectManager_cpp

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>

#include <fstream>
#include <string>

#include <rtm/ObjectManager.h>

/*!
 * @class ObjectManagerTests class
 * @brief ObjectManager test
 */
namespace ObjectManagerTests
{
  using namespace std;
  
  class A
  {
  public:
    A(string _name) : name(_name) {};
    string name;
  };
  
  
  template <class T>
  class Comp
  {
  public:
    Comp(string _name) : name(_name) {};
    Comp(T* obj) : name(obj->name) {};
    bool operator()(A* obj)
    {
      return obj->name == name;
    }
    string name;
  };
  
  class ObjectManagerTests
    : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(ObjectManagerTests);
    CPPUNIT_TEST(test_registerObject);
    CPPUNIT_TEST(test_unregisterObject);
    CPPUNIT_TEST(test_find);
    CPPUNIT_TEST(test_getObjects);
    //  CPPUNIT_TEST(test_for_each);
    CPPUNIT_TEST_SUITE_END();
    
  private:
    typedef ObjectManager<string, A, Comp<A> > AMgr;
    AMgr* m_pObjMgr;
  public:
    
    /*!
     * @brief Constructor
     */
    ObjectManagerTests()
    {
    }
    
    /*!
     * @brief Destructor
     */
    ~ObjectManagerTests()
    {
    }
    
    /*!
     * @brief Test initialization
     */
    virtual void setUp()
    {
      m_pObjMgr = new AMgr();
      const char* name[] = {"test0","test1","test2","test3","test4"};
      try{
	for (int i = 0; i < 5; i++)
	  m_pObjMgr->registerObject(new A(name[i]));
      }
      catch(AMgr::AlreadyRegistered& ar) {
	cout << "registerObject: " << ar.reason << endl << endl;
      }
      
      string str;
      A* aObj;
      try{
	str = "test4";
	aObj = m_pObjMgr->unregisterObject(str);
	CPPUNIT_ASSERT(aObj->name == str);
      }
      catch(AMgr::NoSuchObject& nso) {
	cout << "unregisterObject: " << nso.reason << " : " << str << endl;
      }
      catch(AMgr::SystemError& se) {
	cout << se.reason << endl;
      }
    }
    
    /*!
     * @brief Test finalization
     */
    virtual void tearDown()
    { 
      delete m_pObjMgr;
    }
    
    /* tests for void registerObject(Object* obj) */
    void test_registerObject() {
      const char* name[] = {"test0","test1","test2","test3","test4"};
      int i;
      try{
	for (i = 0; i < 5; i++)
	  m_pObjMgr->registerObject(new A(name[i]));
      }
      catch(AMgr::AlreadyRegistered& ar) {
	cout << "registerObject: " << ar.reason << " : " << name[i] << endl << endl;
      }
    }
    
    
    /* tests for Object* unregisterObject(const Identifier& id) */
    void test_unregisterObject() {
      A* aObj;
      string str;
      
      cout << endl << "test unregisterObject." << endl;
      try{
	str = "test4";
	aObj = m_pObjMgr->unregisterObject(str);
	CPPUNIT_ASSERT(aObj->name == str);
      }
      catch(AMgr::NoSuchObject& nso) {
	cout << "unregisterObject: " << nso.reason << " : " << str << endl;
      }
      catch(AMgr::SystemError& se) {
	cout << se.reason << endl;
      }
      
      try{
	str = "test";
	aObj = m_pObjMgr->unregisterObject(str);
	CPPUNIT_ASSERT(aObj->name == str);
      }
      catch(AMgr::NoSuchObject& nso) {
	cout << "unregisterObject: " << nso.reason << " : " << str << endl;
      }
      catch(AMgr::SystemError& se) {
	cout << se.reason << endl;
      }
      
      try{
	str = "";
	aObj = m_pObjMgr->unregisterObject(str);
	CPPUNIT_ASSERT(aObj->name == str);
      }
      catch(AMgr::NoSuchObject& nso) {
	cout << "unregisterObject: " << nso.reason << " : " << str << endl;
      }
      catch(AMgr::SystemError& se) {
	cout << se.reason << endl;
      }
      
    }
    
    
    /* tests for Object* find(const Identifier& id) */
    void test_find() {
      A* aObj;
      string str;
      
      cout << endl << "test find." << endl;
      try{
	str = "test0";
	aObj = m_pObjMgr->find(str);
	CPPUNIT_ASSERT(aObj->name == str);
      }
      catch(AMgr::NoSuchObject& nso) {
	cout << "find: " << nso.reason << " : " << str << endl;
      }
      catch(AMgr::SystemError& se) {
	cout << se.reason << endl;
      }
      
      try{
	str = "test4";
	aObj = m_pObjMgr->find(str);
	CPPUNIT_ASSERT(aObj->name == str);
      }
      catch(AMgr::NoSuchObject& nso) {
	cout << "find: " << nso.reason << " : " << str << endl;
      }
      catch(AMgr::SystemError& se) {
	cout << se.reason << endl;
      }
      
      try{
	str = "";
	aObj = m_pObjMgr->find(str);
	CPPUNIT_ASSERT(aObj->name == str);
      }
      catch(AMgr::NoSuchObject& nso) {
	cout << "find: " << nso.reason << " : " << str << endl;
      }
      catch(AMgr::SystemError& se) {
	cout << se.reason << endl;
      }
      
    }
    
    
    /* tests for std::vector<Object*> getObjects() const */
    void test_getObjects() {
      const char* name[] = {"test0","test1","test2","test3","test4"};
      vector<A*> va;
      va = m_pObjMgr->getObjects();
      cout << "va size: " << va.size() << endl;
      for (int i = 0; i < (int)va.size(); i++)
	CPPUNIT_ASSERT(va[i]->name == name[i]);
    }
    
    
    /* tests for template <class Pred> void for_each(Pred p) */
    void test_for_each() {
      Comp<string> comp("test0");
      m_pObjMgr->for_each(comp);
      //    CPPUNIT_ASSERT();
    }
  };
}; // namespace ObjectManager

/*
 * Register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(ObjectManagerTests::ObjectManagerTests);

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
#endif // ObjectManager_cpp
