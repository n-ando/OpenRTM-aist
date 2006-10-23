// -*- C++ -*-
/*!
 * @file ObjectManagerTests.cpp
 * @brief ObjectManager class test
 * @date $Date: 2006-10-23 09:37:57 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: ObjectManagerTests.cpp,v 1.1 2006-10-23 09:37:57 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 *
 */

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>
#include <string>
#include "../ObjectManager.h"

using namespace std;

class A
{
public:
  A(std::string _name) : name(_name) {};
  std::string name;
};

template <class T>
class Comp
{
public:
  Comp(std::string _name) : name(_name) {};
  Comp(T* obj) : name(obj->name) {};
  bool operator()(A* obj)
  {
    return obj->name == name;
  }
  std::string name;
};


class ObjectManagerTest
  : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(ObjectManagerTest);
  CPPUNIT_TEST(test_objmgr);
  CPPUNIT_TEST_SUITE_END();
private:
  typedef ObjectManager<std::string, A, Comp<A> > AMgr;
  AMgr* m_pObjMgr;
  
public:
  
  /*
   * コンストラクタ/デストラクタ [7]
   */
  ObjectManagerTest()
  {

  }
  
  ~ObjectManagerTest()
  {
  }
  
  /*
   * 初期化/後始末 [8]
   */
  virtual void setUp()
  {
    m_pObjMgr = new AMgr();
  }
  
  virtual void tearDown()
  { 
    delete m_pObjMgr;
  }
  

  void test_objmgr()
  {
    m_pObjMgr->registerObject(new A("hoge0"));
    m_pObjMgr->registerObject(new A("hoge1"));
    m_pObjMgr->registerObject(new A("hoge2"));
    m_pObjMgr->registerObject(new A("hoge3"));
    m_pObjMgr->registerObject(new A("hoge4"));
    std::cout << std::endl;
    std::cout << (m_pObjMgr->find("hoge0"))->name << std::endl;
    std::cout << (m_pObjMgr->find("hoge1"))->name << std::endl;
    std::cout << (m_pObjMgr->find("hoge2"))->name << std::endl;
    std::cout << (m_pObjMgr->find("hoge3"))->name << std::endl;
    std::cout << (m_pObjMgr->find("hoge4"))->name << std::endl;

    std::vector<A*> objs;
    objs = m_pObjMgr->getObjects();

    std::cout << objs.size() << std::endl;

    for (std::vector<A*>::iterator i = objs.begin(); i != objs.end(); ++i)
      {
	std::cout << (*i)->name << std::endl;
      }

    const char* name[] = {"hoge0", "hoge1", "hoge2", "hoge3", "hoge4"};

    for (int j = 0; j < 5; ++j)
      {
	A* delobj;
	delobj = m_pObjMgr->unregisterObject(name[j]);
	std::cout << "delete: " << delobj->name <<  std::endl;
	delete delobj;
	
	objs = m_pObjMgr->getObjects();
	std::cout << "rest objects: " << objs.size() << "-> ";
	for (std::vector<A*>::iterator i = objs.begin(); i != objs.end(); ++i)
	  {
	    std::cout << (*i)->name << ",  ";
	  }
	std::cout << std::endl;
      }
    std::cout << std::endl;

    try
      {
	m_pObjMgr->find("hoge0");
	CPPUNIT_ASSERT_MESSAGE("NoSuchObject should be thrown!!", false);
      }
    catch (AMgr::NoSuchObject& e)
      {
	std::cout << e.reason << std::endl;
	std::cout << "find() throws NoSuchObject exception properly." << std::endl;
      }

    try
      {
	m_pObjMgr->unregisterObject("hoge0");
	CPPUNIT_ASSERT_MESSAGE("NoSuchObject should be thrown!!", false);
      }
    catch (AMgr::NoSuchObject& e)
      {
	std::cout << e.reason << std::endl;
	std::cout << "unregisterObject() throws NoSuchObject exception properly." << std::endl;
      }
  }

};
/*
 * register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(ObjectManagerTest);

int main(int argc, char* argv[])
{
    CppUnit::TextUi::TestRunner runner;

    runner.addTest(CppUnit::TestFactoryRegistry::getRegistry().makeTest());
    CppUnit::Outputter* outputter = 
      new CppUnit::TextOutputter(&runner.result(), std::cout);
    runner.setOutputter(outputter);
   
    return runner.run();
}
