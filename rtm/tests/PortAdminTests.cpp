// -*- C++ -*-
/*!
 * @file 
 * @brief Properties test class
 * @date $Date: 2006-11-13 04:18:45 $
 * @author Shinji Kurihara
 * $Id: PortAdminTests.cpp,v 1.1 2006-11-13 04:18:45 kurihara Exp $
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

#include <vector>
#include <string>

#include "../PortAdmin.h"

using namespace RTC;
using namespace std;

int g_argc;
vector<string> g_argv;

// PortAdminクラスのテスト
class PortAdminTest
  : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(PortAdminTest);
  CPPUNIT_TEST(test_getPortList);
  CPPUNIT_TEST(test_getPortRef);
  CPPUNIT_TEST(test_getPort);
  CPPUNIT_TEST(test_registerPort);
  CPPUNIT_TEST(test_deletePort);
  CPPUNIT_TEST(test_deletePortByName);
  CPPUNIT_TEST(test_finalizePorts);
  CPPUNIT_TEST_SUITE_END();

private:
  PortAdmin* m_ppadm;
  PortBase* m_ppb;
  PortBase* m_ppb2;
  CORBA::ORB_ptr          m_orb;
  PortableServer::POA_ptr m_poa;
  
public:
  
  /*!
   * @brief コンストラクタ/デストラクタ
   *   ORBの初期化,POAのactivateを行う。
   */
  PortAdminTest()
  {
    char* argv[g_argc];
    for (int i = 0; i < g_argc; i++) {
      argv[i] = (char *)g_argv[i].c_str();
    }

    m_orb = CORBA::ORB_init(g_argc, argv);
    CORBA::Object_var  obj = m_orb->resolve_initial_references("RootPOA");
    m_poa = PortableServer::POA::_narrow(obj);
    PortableServer::POAManager_var pman = m_poa->the_POAManager();
    pman->activate();

  }
  
  /*!
   * デストラクタ
   */
  ~PortAdminTest() {}
  
  /*!
   * @brief 初期化/後始末
   * ここでは以下の処理を行っている。
   *  (1) PortAdminクラス、PortBaseクラスのインスタンス生成
   *  (2) PortBaseクラスにPortProfileを登録
   *  (3) PortAdminクラスにPortBaseオブジェクトを登録
   */
  virtual void setUp()
  {
    // PortAdminクラスのインスタンス生成
    m_ppadm = new PortAdmin(m_orb, m_poa);

    // PortBaseクラスのインスタンス生成
    m_ppb = new PortBase(m_orb, m_poa);

    // PortBaseクラスのインスタンス生成
    m_ppb2 = new PortBase(m_orb, m_poa);

    // PortProfileの登録
    PortProfile pProf0, pProf1;
    pProf0.name = "port0";
    m_ppb->setProfile(pProf0);
    pProf1.name = "port1";
    m_ppb2->setProfile(pProf1);

    // PortBaseオブジェクトの登録
    m_ppadm->registerPort(*m_ppb);
    m_ppadm->registerPort(*m_ppb2);
  }
  
  virtual void tearDown()
  {
    //    delete m_ppb;
    // PortAdminインスタンスの破棄
    delete m_ppadm;
  }


  /*!
   * @brief getPortList()のテスト
   *    getPortList()でPortListのポインタを取得し、そのポインタを用いPortインタフェースの
   *    オペレーション呼び出しを行っている。
   *    PortListは事前にsetUp()メソッドで登録している。
   */
  void test_getPortList() {
    PortList* getPList;
    // getPortList()のテスト
    getPList = m_ppadm->getPortList();

    PortProfile *getProf0, *getProf1;
    // 取得したPortインタフェースのオペレーション呼び出し。
    getProf0 = (*getPList)[0]->get_port_profile();

    string setstr, getstr;
    getstr = getProf0->name;
    setstr = "port0";
    CPPUNIT_ASSERT(getstr == setstr);

    getProf1 = (*getPList)[1]->get_port_profile();
    getstr = getProf1->name;
    setstr = "port1";
    CPPUNIT_ASSERT(getstr == setstr);
  }


  /*!
   * @brief getPortRef()のテスト
   *   (1) get_PortRef()でPortのオブジェクトリファレンス取得
   *   (2) 取得したオブジェクトリファレンスを用いPortオペレーションの呼び出しを行う。
   *   ※ PortのオブジェクトリファレンスはsetUp()にて登録している。
   */
  void test_getPortRef() {
    Port_var getP;
    string getstr, setstr;
    PortProfile *getProf;

    //========= Failure case ================
    // 登録していないPortProfile.nameでgetPortRef()を呼ぶとnillが返される。OK.
    //    getP = m_ppadm->getPortRef("");
    //    if (CORBA::is_nil(getP))
    //      cout << "getP is nil." << endl;
    //    getP = m_ppadm->getPortRef("test");
    //    if (CORBA::is_nil(getP))
    //      cout << "getP is nil." << endl;
    //========================================================

    // getPortRef()のテスト
    getP = m_ppadm->getPortRef("port1");

    if (CORBA::is_nil(getP))
      cout << "getP is nil." << endl;

    getProf = getP->get_port_profile();
    getstr = getProf->name;
    setstr = "port1";
    CPPUNIT_ASSERT(getstr == setstr);


    // test  getPortRef()
    getP = m_ppadm->getPortRef("port0");

    if (CORBA::is_nil(getP))
      cout << "getP is nil." << endl;

    getProf = getP->get_port_profile();
    getstr = getProf->name;
    setstr = "port0";
    CPPUNIT_ASSERT(getstr == setstr);
  }


  /*!
   * @brief getPort()のテスト
   *   (1) getPort()にてPortBaseへのポインタを取得
   *   (2) 取得したポインタを用い、PortBaseクラスのメソッド呼び出しを行う。
   *   ※ PortBaseクラスのポインタはsetUp()で登録済みである。
   */
  void test_getPort() {
    PortBase* pb;
    PortProfile* getProf;
    string setstr, getstr;

    // Failure case: unknown exception例外発生。
    //    pb = m_ppadm->getPort("");
    //    pb = m_ppadm->getPort("test"); // 登録していないname

    // test getPort()
    pb = m_ppadm->getPort("port1");
    getProf = pb->get_port_profile();
    setstr = "port1";
    getstr = getProf->name;
    CPPUNIT_ASSERT(setstr == getstr);

    // test getPort()
    pb = m_ppadm->getPort("port0");
    getProf = pb->get_port_profile();
    setstr = "port0";
    getstr = getProf->name;
    CPPUNIT_ASSERT(setstr == getstr);
  }


  /*!
   * @brief tests for registerPort()
   */
  void test_registerPort() {
    // setUp()にてテスト。
  }


  /*!
   * @brief deletePort()のテスト
   *   (1) deletePort()呼び出し。
   *   (2) getPortList()にて、(1)の処理が正しく行われているかを確認。
   */
  void test_deletePort() {

    // deletePort()呼び出し。
    m_ppadm->deletePort(*m_ppb);

    // PortListの取得
    PortList* getPList;
    getPList = m_ppadm->getPortList();

    cout << getPList->length() << endl;

    /*
    PortProfile *getProf0, *getProf1;
    // 取得したPortBaseオブジェクト−オペレーション呼び出し。
    getProf0 = (*getPList)[0]->get_port_profile();
    string setstr, getstr;
    getstr = getProf0->name;
    setstr = "port0";
    CPPUNIT_ASSERT(getstr == setstr);

    getProf1 = (*getPList)[1]->get_port_profile();
    getstr = getProf1->name;
    setstr = "port1";
    CPPUNIT_ASSERT(getstr == setstr);
    */
  }


  /*!
   * @brief tests for deletePortByName()
   */
  void test_deletePortByName() {
  }


  /*!
   * @brief tests for finalizePorts()
   */
  void test_finalizePorts() {
  }

};


/*
 * register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(PortAdminTest);



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
