// -*- C++ -*-
/*!
 * @file 
 * @brief test class
 * @date $Date: 2006-11-22 11:43:22 $
 * @author Shinji Kurihara
 * $Id: CorbaConsumerTests.cpp,v 1.1 2006-11-22 11:43:22 kurihara Exp $
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

#include "../CorbaConsumer.h"
#include "Test.hh"

using namespace std;

int g_argc;
vector<string> g_argv;

/*!
 * @brief Test.idlで定義したinterfaceの実装クラス(サーバント)
 *    ConbaConsumer::setObject()に渡すためのテストクラス
 */
class Test_i : public POA_Test,
	       public PortableServer::RefCountServantBase
{
public:
  // コンストラクタ
  inline Test_i(){}

  // デストラクタ
  virtual ~Test_i(){}

  // hello()オペレーションの実装
  virtual void hello() {cout << "operation hello !!!" << endl;}
};


/*!
 * @brief ConsumerBaseクラス,Consumerクラスのテストクラス
 */
class CorbaConsumerTests
  : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(CorbaConsumerTests);
  CPPUNIT_TEST(test_ConsumerBase);
  //  CPPUNIT_TEST(test_Consumer);
  CPPUNIT_TEST_SUITE_END();

private:
  Test_ptr m_testObj;
  RTC::ConsumerBase* m_consBase;

  typedef RTC::Consumer<Test, Test::_ptr_type, Test::_var_type> TestConsumer;
  TestConsumer* m_cons;

public:
  
  /*!
   * @brief コンストラクタ
   *    (1) ORBの初期化
   *    (2) POAの初期化
   *    (3) サーバントクラスのインスタンス生成
   *    (4) サーバントの活性化、オブジェクトリファレンスの取得
   *    (5) POAManagerの活性化
   */
  CorbaConsumerTests()
  {
    char* argv[g_argc];
    for (int i = 0; i < g_argc; i++) {
      argv[i] = (char *)g_argv[i].c_str();
    }

    CORBA::ORB_var m_orb;
    PortableServer::POA_var m_poa;

    // (1) ORBの初期化
    m_orb = CORBA::ORB_init(g_argc, argv);
    CORBA::Object_var  obj = m_orb->resolve_initial_references("RootPOA");

    // (2) POAの初期化
    m_poa = PortableServer::POA::_narrow(obj);

    // (3) サーバントクラスのインスタンス生成
    Test_i* test = new Test_i();

    // (4) サーバントの活性化、オブジェクトリファレンスの取得
    m_testObj = test->_this();

    test->_remove_ref();

    PortableServer::POAManager_var pman = m_poa->the_POAManager();

    // (5) POAManagerの活性化
    pman->activate();
  }


  /*!
   * @brief デストラクタ
   */
  ~CorbaConsumerTests()
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
   * @brief ConsumerBaseクラスのテスト
   *    (1) ConsumerBaseクラスのインスタンス生成
   *    (2) setObject()メソッドを呼び,オブジェクトリファレンスの登録を行う。
   *    (3) getObject()メソッドを呼び、オブジェクトリファレンスの取得を行う。
   *    (4) 取得したオブジェクトリファレンスをTestクラスにnarrowする。
   *    (5）(4)でnarrowしたオブジェクトリファレンスを用いTestインタフェースの
   *        hello()オペレーション呼び出しを行う。
   *    (6) setObject()メソッドを呼び,オブジェクトリファレンスの登録を行う。
   *    (7) getObject()メソッドを呼び、オブジェクトリファレンスの取得を行う。
   *    (8) 取得したオブジェクトリファレンスをTestクラスにnarrowする。
   *    (9) hello()オペレーション呼び出し。
   *    (10) ConsumerBaseクラスのインスタンス破棄
   */
  void test_ConsumerBase() {
    bool result;

    // (1) ConsumerBaseクラスのインスタンス生成
    m_consBase = new RTC::ConsumerBase();

    // (2) setObject()メソッドを呼び,オブジェクトリファレンスの登録を行う。
    result = m_consBase->setObject(m_testObj);

    if(!result)
      cout << "setObject() is Failed." << endl;

    CORBA::Object_ptr getObj;

    // (3) getObject()メソッドを呼び、オブジェクトリファレンスの取得を行う。
    getObj = m_consBase->getObject();

    Test_var testObj;

    // (4) 取得したオブジェクトリファレンスをTestクラスにnarrowする。
    testObj = Test::_narrow(getObj);
    if(CORBA::is_nil(testObj))
      cout << "is_nil" << endl;

    // (5）(4)でnarrowしたオブジェクトリファレンスを用いTestインタフェースの
    //     hello()オペレーション呼び出しを行う。
    testObj->hello();


    // 再度setObject(),getObject()を呼ぶ。
    // (6) setObject()メソッドを呼び,オブジェクトリファレンスの登録を行う。
    result = m_consBase->setObject(m_testObj);

    // (7) getObject()メソッドを呼び、オブジェクトリファレンスの取得を行う。
    getObj = m_consBase->getObject();

    // (8) 取得したオブジェクトリファレンスをTestクラスにnarrowする。
    testObj = Test::_narrow(getObj);

    // (9) hello()オペレーション呼び出し。
    testObj->hello();

    // (10) ConsumerBaseクラスのインスタンス破棄
    delete m_consBase;
  }


  /*!
   * @brief Consumerクラスのテスト
   *    (1) Consumerクラスのインスタンス生成
   *    (2) setObject()メソッドを呼び,オブジェクトリファレンスの登録を行う。
   *    (3) getObject()メソッドを呼び、オブジェクトリファレンスの取得を行う。
   *    (4) 取得したオブジェクトリファレンスをTestクラスにnarrowする。
   *    (5）(4)でnarrowしたオブジェクトリファレンスを用いTestインタフェースの
   *        hello()オペレーション呼び出しを行う。
   *    (6) _ptr()メソッドを呼び、Testにnarrowされたオブジェクトを取得する。
   *    (7) (6)で取得したオブジェクトに対してhello()オペレーションを呼び出す。
   *    (8) Consumerクラスのインスタンス破棄
   */
  void test_Consumer() {
    bool result;

    // (1) Consumerクラスのインスタンス生成
    m_cons = new TestConsumer();

    // (2) setObject()メソッドを呼び,オブジェクトリファレンスの登録を行う。
    result = m_cons->setObject(m_testObj);

    CORBA::Object_ptr getObj;

    // (3) getObject()メソッドを呼び、オブジェクトリファレンスの取得を行う。
    getObj = m_cons->getObject();

    Test_var test;

    // (4) 取得したオブジェクトリファレンスをTestクラスにnarrowする。
    test = Test::_narrow(getObj);
    if(CORBA::is_nil(test))
      cout << "is_nil" << endl;

    // (5）(4)でnarrowしたオブジェクトリファレンスを用いTestインタフェースの
    //     hello()オペレーション呼び出しを行う。
    test->hello();


    Test::_ptr_type testObj;

    // (6) _ptr()メソッドを呼び、Testにnarrowされたオブジェクトを取得する。
    testObj = m_cons->_ptr();
    
    // (7) (6)で取得したオブジェクトに対してhello()オペレーションを呼び出す。
    testObj->hello();


    // 再度setObject(),getObject(),_ptr()を呼ぶ。
    result = m_cons->setObject(m_testObj);
    getObj = m_cons->getObject();
    test = Test::_narrow(getObj);
    test->hello();
    testObj = m_cons->_ptr();
    testObj->hello();

    // (8) Consumerクラスのインスタンス破棄
    delete m_cons;
  }

};


/*!
 * @brief register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(CorbaConsumerTests);



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
