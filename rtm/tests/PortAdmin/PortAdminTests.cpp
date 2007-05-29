// -*- C++ -*-
/*!
 * @file   PortAdminTests.cpp
 * @brief  PortAdmin test class
 * @date   $Date: 2007-04-13 15:05:03 $
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
 * $Id: PortAdminTests.cpp,v 1.3 2007-04-13 15:05:03 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.2  2007/01/12 14:44:36  n-ando
 * Some fixes for distribution control.
 *
 * Revision 1.1  2006/11/27 08:34:18  n-ando
 * TestSuites are devided into each directory.
 *
 * Revision 1.2  2006/11/14 02:21:09  kurihara
 *
 * test_deletePortByName() and test_finalizePorts() were added.
 *
 * Revision 1.1  2006/11/13 04:18:45  kurihara
 *
 * test program for PortAdmin class.
 *
 */

#ifndef PortAdmin_cpp
#define PortAdmin_cpp

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>

#include <vector>
#include <string>

#include <rtm/PortAdmin.h>

/*!
 * @class PortAdminTests class
 * @brief PortAdmin test
 */
namespace PortAdmin
{
  using namespace RTC;
  using namespace std;
  
  int g_argc;
  vector<string> g_argv;
  
  class PortBase
	: public RTC::PortBase
  {
  protected:
	virtual RTC::ReturnCode_t publishInterfaces(RTC::ConnectorProfile&)
	{
	  return RTC::RTC_OK;
	}
	virtual RTC::ReturnCode_t subscribeInterfaces(const RTC::ConnectorProfile&)
	{
	  return RTC::RTC_OK;
	}
	virtual void unsubscribeInterfaces(const RTC::ConnectorProfile&)
	{
	}
  };


  class PortAdminTests
    : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(PortAdminTests);
    CPPUNIT_TEST(test_getPortList);
    CPPUNIT_TEST(test_getPortRef);
    CPPUNIT_TEST(test_getPort);
    CPPUNIT_TEST(test_registerPort);
    CPPUNIT_TEST(test_deletePort);
    CPPUNIT_TEST(test_deletePortByName);
    CPPUNIT_TEST(test_finalizePorts);
    CPPUNIT_TEST_SUITE_END();
    
  private:
	RTC::PortAdmin* m_ppadm;
	PortBase* m_ppb;
	PortBase* m_ppb2;
    CORBA::ORB_ptr          m_orb;
    PortableServer::POA_ptr m_poa;
    
  public:
    
    /*!
     * @brief Constructor
     */
    PortAdminTests()
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
     * @brief Destructor
     */
    ~PortAdminTests()
    {
    }
    
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
      m_ppadm = new RTC::PortAdmin(m_orb, m_poa);
      
      // PortBaseクラスのインスタンス生成
      m_ppb = new PortBase();
      
      // PortBaseクラスのインスタンス生成
      m_ppb2 = new PortBase();
      
      // PortProfileの登録
      m_ppb->setName("port0");
      m_ppb2->setName("port1");
      
      // PortBaseオブジェクトの登録
      m_ppadm->registerPort(*m_ppb);
      m_ppadm->registerPort(*m_ppb2);
    }
    
    /*!
     * @brief Test finalization
     */
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
	  RTC::PortBase* pb;
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
     *   ※ Port_ptrはsetUp()にてregisterPort()を用いて登録済みである。(2つのポートを登録。)
     *   (1) deletePort()呼び出し。
     *   (2) getPortList()にてPortListを取得。
     *   (3) (1)の処理が正しく行われているかを確認。
     */
    void test_deletePort() {
      
      // (1) deletePort()呼び出し。
      m_ppadm->deletePort(*m_ppb2);
      
      // (2) getPortList()にてPortListを取得。
      PortList* getPList;
      getPList = m_ppadm->getPortList();
      
      cout << getPList->length() << endl;
      
      
      // (3) (1)の処理が正しく行われているかを確認。
      PortProfile *getProf0, *getProf1;
      // 取得したPortBaseオブジェクト−オペレーション呼び出し。
      getProf0 = (*getPList)[0]->get_port_profile();
      string setstr, getstr;
      getstr = getProf0->name;
      setstr = "port0";
      CPPUNIT_ASSERT(getstr == setstr);
      
      
      // Failure case :
      //    setUp()で2つのポートを登録しており、(1)で一つ削除したので、ここでの処理は
      //    エラーとなるはずである。
      getProf1 = (*getPList)[1]->get_port_profile();
      getstr = getProf1->name;
      setstr = "port1";
      CPPUNIT_ASSERT(getstr == setstr);
    }
    
    
    /*!
     * @brief tests for deletePortByName()
     *   ※ Port_ptrはsetUp()にてregisterPort()を用いて登録済みである。(2つのポートを登録。)
     *    (1) getPortList()にてPortListを取得し登録されているPortの数を確認。
     *    (2）deletePortByName()にて"port1"の名前を持つPortの削除を行う。
     *    (3) getPortList()にてPortListを取得し登録されているPortの数を確認。
     */
    void test_deletePortByName() {
      PortList* getPList;
      
      // (1) getPortList()にてPortListを取得し登録されているPortの数を確認。
      getPList = m_ppadm->getPortList();
      cout << getPList->length() << endl;
      
      m_ppadm->deletePortByName("port1");
      
      // (3) getPortList()にてPortListを取得し登録されているPortの数を確認。
      getPList = m_ppadm->getPortList();
      cout << getPList->length() << endl;
    }
    
    
    /*!
     * @brief tests for finalizePorts()
     *   (1) getPortList()にてPortListを取得し登録されているPortの数を確認。
     *   (2) finalizePorts()の呼び出し。
     *   (3) getPortList()にてPortListを取得し登録されているPortの数を確認。
     */
    void test_finalizePorts() {
      PortList* getPList;
      
      // (1) getPortList()にてPortListを取得し登録されているPortの数を確認。
      getPList = m_ppadm->getPortList();
      cout << getPList->length() << endl;
      
      
      // (2) finalizePorts()の呼び出し。
      m_ppadm->finalizePorts();
      
      
      // (3) getPortList()にてPortListを取得し登録されているPortの数を確認。
      getPList = m_ppadm->getPortList();
      cout << getPList->length() << endl;
    }
    
    
  };
}; // namespace PortAdmin

/*
 * Register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(PortAdmin::PortAdminTests);

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
#endif // PortAdmin_cpp
