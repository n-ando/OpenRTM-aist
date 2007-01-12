// -*- C++ -*-
/*!
 * @file   PortBaseTests.cpp
 * @brief  PortBase test class
 * @date   $Date: 2007-01-12 14:44:43 $
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
 * $Id: PortBaseTests.cpp,v 1.2 2007-01-12 14:44:43 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.1  2006/11/27 08:35:12  n-ando
 * TestSuites are devided into each directory.
 *
 * Revision 1.2  2006/11/13 12:30:06  kurihara
 *
 * document is added.
 *
 * Revision 1.1  2006/11/08 01:19:07  kurihara
 *
 * test program for PortBase class.
 *
 */

#ifndef PortBase_cpp
#define PortBase_cpp

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>

#include <vector>
#include <string>
#include <rtm/PortBase.h>
#include <rtm/RTObject.h>

/*!
 * @class PortBaseTests class
 * @brief PortBase test
 */
namespace PortBase
{
  class PortBase
	: public RTC::PortBase
  {
  public:
	const std::string getUUID() const
	{
	  return RTC::PortBase::getUUID();
	}
  protected:
	virtual RTC::ReturnCode_t publishInterfaces(RTC::ConnectorProfile&)
	{
	  return RTC::OK;
	}
	virtual RTC::ReturnCode_t subscribeInterfaces(const RTC::ConnectorProfile&)
	{
	  return RTC::OK;
	}
	virtual void unsubscribeInterfaces(const RTC::ConnectorProfile&)
	{
	}
  };

  using namespace RTC;
  using namespace std;
  int g_argc;
  vector<string> g_argv;

  class PortBaseTests
    : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(PortBaseTests);
    CPPUNIT_TEST(test_get_port_profile);
    CPPUNIT_TEST(test_get_connector_profiles);
    CPPUNIT_TEST(test_get_connector_profile);
    CPPUNIT_TEST(test_connect);
    CPPUNIT_TEST(test_disconnect);
    CPPUNIT_TEST(test_disconnect_all);
    //  CPPUNIT_TEST(test_setProfile);
    //  CPPUNIT_TEST(test_getProfile);
    //    CPPUNIT_TEST(test_setName);
    //    CPPUNIT_TEST(test_getName);
    //    CPPUNIT_TEST(test_setInterfaceProfiles);
    //  CPPUNIT_TEST(test_addInterfaceProfiles);
    //  CPPUNIT_TEST(test_getInterfaceProfiles);
    //  CPPUNIT_TEST(test_getInterfaceProfile);
    CPPUNIT_TEST(test_setPortRef);
    //  CPPUNIT_TEST(test_getPortRef);
    //  CPPUNIT_TEST(test_addConnectorProfile);
    //  CPPUNIT_TEST(test_eraseConnectorProfile);
    //  CPPUNIT_TEST(test_getConnectorProfileList);
    //  CPPUNIT_TEST(test_getConnectorProfile);
    CPPUNIT_TEST(test_setOwner);
    CPPUNIT_TEST(test_getOwner);
	//    CPPUNIT_TEST(test_setProperties);
	//    CPPUNIT_TEST(test_getProperties);
    CPPUNIT_TEST(test_getUUID);
    CPPUNIT_TEST_SUITE_END();
    
  private:
    PortBase* m_ppb;
    CORBA::ORB_ptr          m_orb;
    PortableServer::POA_ptr m_poa;
    
    SDOPackage::NVList m_nvlist;
    SDOPackage::NameValue m_nv;
    CORBA::Float m_cnctProfVal,m_portProfVal;
  public:
    
    /*!
     * @brief Constructor
     */
    PortBaseTests()
    {
    }
    
    /*!
     * @brief Destructor
     */
    ~PortBaseTests()
    {
    }
    
    /*!
     * @brief 初期化
     *    (1) ORBの初期化,POAのactivate
     *    (2) PortBaseのインスタンス生成
     *    (3) PortInterfaceProfileオブジェクト要素のセット
     *    (4) PortInterfaceProfileListオブジェクト要素
     *        (PortProfileの要素)のセット
     *    (5) ConnectorProfileオブジェクト要素のセット
     *    (6) ConnectorProfileListオブジェクト要素(PortProfileの要素)のセット
     *    (7) PortProfileオブジェクト要素のセット
     *    (8) PortProfileオブジェクトのセット
     */
    virtual void setUp()
    {
      char* argv[g_argc];
      for (int i = 0; i < g_argc; i++) {
	argv[i] = (char *)g_argv[i].c_str();
      }
      
      // (1) ORBの初期化,POAのactivate
      m_orb = CORBA::ORB_init(g_argc, argv);
      CORBA::Object_var  obj = m_orb->resolve_initial_references("RootPOA");
      m_poa = PortableServer::POA::_narrow(obj);
      PortableServer::POAManager_var pman = m_poa->the_POAManager();
      pman->activate();
      
      // (2) PortBaseのインスタンス生成
      m_ppb = new PortBase();
      
      // (3) PortInterfaceProfileオブジェクト要素(PortProfileの要素)のセット
      PortInterfaceProfile pIProf;
      pIProf.instance_name = "PortInterfaceProfile-instance_name";
      pIProf.type_name = "PortInterfaceProfile-type_name";
      pIProf.polarity = REQUIRED;
      
      // (4) PortInterfaceProfileListオブジェクト要素のセット
      PortInterfaceProfileList pIFProfList;
      pIFProfList.length(1);
      pIFProfList[0] = pIProf;
      
      // (5) ConnectorProfileオブジェクト要素のセット
      ConnectorProfile cProf;
      cProf.name = "ConnectorProfile-name";
      cProf.connector_id = "connect_id0";
      m_nv.name = "ConnectorProfile-properties0-name";
      m_cnctProfVal = 1.1;
      m_nv.value <<= m_cnctProfVal;
      m_nvlist.length(1);
      m_nvlist[0] = m_nv;
      cProf.properties = m_nvlist;
      
      // (6) ConnectorProfileListオブジェクト要素(PortProfileの要素)のセット
      ConnectorProfileList cProfList;
      cProfList.length(1);
      cProfList[0] = cProf;
      
      // (7) PortProfileオブジェクト要素のセット
      PortProfile pProf;
      pProf.name = "inport0";
      pProf.interfaces = pIFProfList;
      pProf.connector_profiles = cProfList;
      m_nv.name = "PortProfile-properties0-name";
      m_portProfVal = 2.2;
      m_nv.value <<= m_portProfVal;
      m_nvlist[0] = m_nv;
      pProf.properties = m_nvlist;
      
      // (8) PortProfileオブジェクトのセット
      //### m_ppb->setProfile(pProf);
    }
    
    /*!
     * @brief Test finalization
     */
    virtual void tearDown()
    { 
    }
    
    /*!
     * @brief get_port_profile()のテスト
     *    ※ PortProfileはsetUp()で登録済みである。
     *    (1) get_port_profile()にてPortProfile*を取得
     *    (2) セットしたPortProfileと取得したPortProfileの要素を比較
     */
    void test_get_port_profile() {
      PortProfile* getProf;
      
      // (1) get_port_profile()にてPortProfile*を取得
      getProf = m_ppb->get_port_profile();
      
      string setstr, getstr;
      // (2) セットしたPortProfileと取得したPortProfileの要素を比較
      // check PortProfile.name
      getstr = getProf->name;
      setstr = "inport0";
      CPPUNIT_ASSERT(getstr == setstr);
      
      // check PortProfile.interfaces
      getstr = getProf->interfaces[0].instance_name;
      setstr = "PortInterfaceProfile-instance_name";
      CPPUNIT_ASSERT(getstr == setstr);
      
      getstr = getProf->interfaces[0].type_name;
      setstr = "PortInterfaceProfile-type_name";
      CPPUNIT_ASSERT(getstr == setstr);
      
      CPPUNIT_ASSERT(getProf->interfaces[0].polarity == REQUIRED);
      
      // check PortProfile.connector_profiles
      getstr = getProf->connector_profiles[0].name;
      setstr = "ConnectorProfile-name";
      CPPUNIT_ASSERT(getstr == setstr);
      
      getstr = getProf->connector_profiles[0].connector_id;
      setstr = "connect_id0";
      CPPUNIT_ASSERT(getstr == setstr);
      
      getstr = getProf->connector_profiles[0].properties[0].name;
      setstr = "ConnectorProfile-properties0-name";
      CPPUNIT_ASSERT(getstr == setstr);
      
      CORBA::Float retval;
      getProf->connector_profiles[0].properties[0].value >>= retval;
      CPPUNIT_ASSERT(retval == m_cnctProfVal);
      
      // check PortProfile.properties
      getstr = getProf->properties[0].name;
      setstr = "PortProfile-properties0-name";
      CPPUNIT_ASSERT(getstr == setstr);
      
      getProf->properties[0].value >>= retval;
      CPPUNIT_ASSERT(retval == m_portProfVal);
    }
    
    
    /*!
     * @brief get_connector_profiles()のテスト
     *    ※ ConnectorProfileListはPortProfileの要素であり、
     *       setUp()で登録済みである。
     *    (1）get_connector_profiles()にてConnectorProfileListを取得
     *    (2) セットしたConnectorProfileと取得したConnectorProfileListの
     *        要素であるConnectorProfileの要素を比較。
     */
    void test_get_connector_profiles() {
      ConnectorProfileList* cpList;
      string setstr, getstr;
      
      // get ConnectorProfileList
      cpList = m_ppb->get_connector_profiles();
      
      // (2) セットしたConnectorProfileと取得したConnectorProfileListの
      //     要素である
      //      ConnectorProfileの要素を比較。
      // check ConnectorProfile.name
      setstr = "ConnectorProfile-name";
      getstr = (*cpList)[0].name;
      CPPUNIT_ASSERT(getstr == setstr);
      
      // check ConnectorProfile.connector_id
      setstr = "connect_id0";
      getstr = (*cpList)[0].connector_id;
      CPPUNIT_ASSERT(getstr == setstr);
      
      // check ConnectorProfile.properties.name
      setstr = "ConnectorProfile-properties0-name";
      getstr = (*cpList)[0].properties[0].name;
      CPPUNIT_ASSERT(getstr == setstr);
      
      // check ConnectorProfile.properties.value
      CORBA::Float retval;
      (*cpList)[0].properties[0].value >>= retval;
      CPPUNIT_ASSERT(m_cnctProfVal == retval);
    }
    
    
    /*!
     * @brief get_connector_profile()のテスト
     *    ※ ConnectorProfileはConnectorProfileListの要素であり、
     *       ConnectorProfileListはPortProfileの要素である。
     *       PortProfileはsetUp()で登録済みである。
     *    (1) get_connector_profileにてConnectorProfileを取得。
     *    (2) セットしたConnectorProfileと取得したConnectorProfileを比較。
     */
    void test_get_connector_profile() {
      ConnectorProfile* cProf;
      string setstr, getstr;
      
      // (1) get_connector_profileにてConnectorProfileを取得。
      cProf = m_ppb->get_connector_profile("connect_id0");
      
      // セットしたConnectorProfileと取得したConnectorProfileを比較。
      // check ConnectorProfile.name
      setstr = "ConnectorProfile-name";
      getstr = cProf->name;
      CPPUNIT_ASSERT(getstr == setstr);
      
      // check ConnectorProfile.connector_id
      setstr = "connect_id0";
      getstr = cProf->connector_id;
      CPPUNIT_ASSERT(getstr == setstr);
      
      // check ConnectorProfile.properties.name
      setstr = "ConnectorProfile-properties0-name";
      getstr = cProf->properties[0].name;
      CPPUNIT_ASSERT(getstr == setstr);
      
      // check ConnectorProfile.properties.value
      CORBA::Float retval;
      cProf->properties[0].value >>= retval;
      CPPUNIT_ASSERT(m_cnctProfVal == retval);
      
      ReturnCode_t result;
      
      result = m_ppb->connect(*cProf);
      
      if (result == OK)
	cout << "connect result OK. " << endl;
      else if (result == ERROR)
	cout << "connect result ERROR. " << endl;
      else if (result == BAD_PARAMETER)
	cout << "connect result BAD_PARAMETER. " << endl;
      else if (result == UNSUPPORTED)
	cout << "connect result UNSUPPORTED. " << endl;
      else if (result == OUT_OF_RESOURCES)
	cout << "connect result OUT_OF_RESOURCES. " << endl;
      else if (result == PRECONDITION_NOT_MET)
	cout << "connect result PRECONDITION_NOT_MET. " << endl;
    }
    
    
    /*!
     * @brief connect()のテスト
     *   未テスト
     */
    void test_connect() {}
    
    
    /*!
     * @brief disconnect()のテスト
     *   未テスト
     */
    void test_disconnect() {}
    
    
    /*!
     * @brief disconnect_all()のテスト
     *   未テスト
     */
    void test_disconnect_all() {}
    
    
    /*!
     * @brief setProfile()のテスト
     *   test_get_port_profile() にてテスト済み
     */
    void test_setProfile() {}
    
    
    /*!
     * @brief getProfile()のテスト
     *   ※ PortProfileはsetUp()で登録済みである。
     *   (1) getProfile()にてPortProfileを取得。
     *   (2) セットしたPortProfileと取得したそれとの要素を比較。
     */
    /*
    void test_getProfile() {
      PortProfile getProf;
      
      // (1) getProfile()にてPortProfileを取得。
      // ### getProf = m_ppb->getProfile();
      
      string setstr, getstr;
      
      // (2) セットしたPortProfileと取得したそれとの要素を比較。
      // check PortProfile.name
      getstr = getProf.name;
      setstr = "inport0";
      CPPUNIT_ASSERT(getstr == setstr);
      
      // check PortProfile.interfaces
      getstr = getProf.interfaces[0].instance_name;
      setstr = "PortInterfaceProfile-instance_name";
      CPPUNIT_ASSERT(getstr == setstr);
      
      getstr = getProf.interfaces[0].type_name;
      setstr = "PortInterfaceProfile-type_name";
      CPPUNIT_ASSERT(getstr == setstr);
      
      CPPUNIT_ASSERT(getProf.interfaces[0].polarity == REQUIRED);
      
      // check PortProfile.connector_profiles
      getstr = getProf.connector_profiles[0].name;
      setstr = "ConnectorProfile-name";
      CPPUNIT_ASSERT(getstr == setstr);
      
      getstr = getProf.connector_profiles[0].connector_id;
      setstr = "connect_id0";
      CPPUNIT_ASSERT(getstr == setstr);
      
      getstr = getProf.connector_profiles[0].properties[0].name;
      setstr = "ConnectorProfile-properties0-name";
      CPPUNIT_ASSERT(getstr == setstr);
      
      CORBA::Float retval;
      getProf.connector_profiles[0].properties[0].value >>= retval;
      CPPUNIT_ASSERT(retval == m_cnctProfVal);
      
      // check PortProfile.properties
      getstr = getProf.properties[0].name;
      setstr = "PortProfile-properties0-name";
      CPPUNIT_ASSERT(getstr == setstr);
      
      getProf.properties[0].value >>= retval;
      CPPUNIT_ASSERT(retval == m_portProfVal);
    }
    */
    
    /*!
     * @brief setName()のテスト
     *   ※ PortProfileはsetUp()にて登録済みである。
     *   (1) setName()にてPortProfile.nameをセット。
     *   (2) getProfile()にてPortProfileを取得。
     *   (3) (1)でセットしたnameと(2)で取得したPortProfile.nameを比較。
     */
    /*
    void test_setName() {
      // (1) setName()にてPortProfile.nameをセット。
      m_ppb->setName("inport0-changed");
      
      PortProfile getProf;
      
      // (2) getProfile()にてPortProfileを取得。
      getProf = m_ppb->getProfile();
      
      string setstr, getstr;
      
      // (3) (1)でセットしたnameと(2)で取得したPortProfile.nameを比較。
      getstr = getProf.name;
      setstr = "inport0-changed";
      CPPUNIT_ASSERT(getstr == setstr);
    }
    */
    
    /*!
     * @brief  getName()のテスト
     *   ※ PortProfileはsetUp()にて登録済みである。
     *   (1) geName()にてPortProfile.nameを取得。
     *   (2) セット済みのPortProfile.nameと(1)で取得したnameを比較。
     */
    /*
    void test_getName() {
      // (1) geName()にてPortProfile.nameを取得。
      const char* retval(m_ppb->getName());
      
      string setname, getname;
      
      // (2) セット済みのPortProfile.nameと(1)で取得したnameを比較。
      setname = "inport0";
      getname = retval;
      CPPUNIT_ASSERT(getname == setname);
    }
    */
    
    /*!
     * @brief setInterfaceProfiles()のテスト
     *   (1) PortInterfaceProfileオブジェクト要素のセット。
     *   (2) (1)でセットしたPortInterfaceProfileをPortInterfaceProfileListに
     *       セット。
     *   (3）setInterfaceProfiles()にてPortInterfaceProfileListをセット。
     *   (4) getInterfaceProfiles()にてPortInterfaceProfileListを取得。
     *   (5) (3)でセットしたPortInterfaceProfileListの要素と、
     *       (4)で取得したそれとを比較。
     *   (6) addInterfaceProfile()にてPortInterfaceProfileを追加。
     *   (7) getInterfaceProfiles()にてPortInterfaceProfileListを取得。
     *   (8) (6)で追加したPortInterfaceProfileListの要素と、
     *       (7)で取得したそれとを比較。
     *   (9) getInterfaceProfile(name)にてPortInterfaceProfileを取得。
     *   (10) (6)で追加したPortInterfaceProfileListの要素と、
     *        (9)で取得したそれとを比較。
     */
    /*
    void test_setInterfaceProfiles() {
      // (1) PortInterfaceProfileオブジェクト要素のセット。
      PortInterfaceProfile pIProf;
      pIProf.instance_name = "PortInterfaceProfile-instance_name-changed";
      pIProf.type_name = "PortInterfaceProfile-type_name-changed";
      pIProf.polarity = REQUIRED;
      
      
      // (2) (1)でセットしたPortInterfaceProfileをPortInterfaceProfileList
      // にセット。
      PortInterfaceProfileList pIFProfList;
      pIFProfList.length(1);
      pIFProfList[0] = pIProf;
      
      
      // (3）setInterfaceProfiles()にてPortInterfaceProfileListをセット。
      m_ppb->setInterfaceProfiles(pIFProfList);
      
      
      // (4) getInterfaceProfiles()にてPortInterfaceProfileListを取得。
      PortInterfaceProfileList getList;
      getList = m_ppb->getInterfaceProfiles();
      
      
      // (5) (3)でセットしたPortInterfaceProfileListの要素と、
      // (4)で取得したそれとを比較。
      string getstr, setstr;
      getstr = getList[0].instance_name;
      setstr = "PortInterfaceProfile-instance_name-changed";
      CPPUNIT_ASSERT(getstr == setstr);
      
      getstr = getList[0].type_name;
      setstr = "PortInterfaceProfile-type_name-changed";
      CPPUNIT_ASSERT(getstr == setstr);
      
      CPPUNIT_ASSERT(getList[0].polarity == REQUIRED);
      
      
      // (6) addInterfaceProfile()にてPortInterfaceProfileを追加。
      pIProf.instance_name = "PortInterfaceProfile-instance_name-add";
      pIProf.type_name = "PortInterfaceProfile-type_name-add";
      pIProf.polarity = PROVIDED;
      m_ppb->addInterfaceProfile(pIProf);
      
      
      // (7) getInterfaceProfiles()にてPortInterfaceProfileListを取得。
      getList = m_ppb->getInterfaceProfiles();
      
      
      // (8) (6)で追加したPortInterfaceProfileListの要素と、
      // (7)で取得したそれとを比較。
      getstr = getList[1].instance_name;
      setstr = "PortInterfaceProfile-instance_name-add";
      CPPUNIT_ASSERT(getstr == setstr);
      
      getstr = getList[1].type_name;
      setstr = "PortInterfaceProfile-type_name-add";
      CPPUNIT_ASSERT(getstr == setstr);
      
      CPPUNIT_ASSERT(getList[1].polarity == PROVIDED);
      
      
      // (9) getInterfaceProfile(name)にてPortInterfaceProfileを取得。
      PortInterfaceProfile getProf;
      getProf = m_ppb->getInterfaceProfile("PortInterfaceProfile-instance_name-add");
      
      // (10) (6)で追加したPortInterfaceProfileListの要素と、(9)で取得したそれとを比較。
      getstr = getProf.instance_name;
      setstr = "PortInterfaceProfile-instance_name-add";
      CPPUNIT_ASSERT(getstr == setstr);
      
      getstr = getProf.type_name;
      setstr = "PortInterfaceProfile-type_name-add";
      CPPUNIT_ASSERT(getstr == setstr);
      
      CPPUNIT_ASSERT(getProf.polarity == PROVIDED);
    }
    */
    /*!
     * @brief addInterfaceProfiles()のテスト
     *   test_setInterfaceProfiles()にてテスト済み。
     */
    void test_addInterfaceProfiles() {}
    
    
    /*!
     * @brief getInterfaceProfiles()のテスト
     *   test_setInterfaceProfiles()にてテスト済み。
     */
    void test_getInterfaceProfiles() {}
    
    
    /*!
     * @brief getInterfaceProfile()のテスト
     *   test_setInterfaceProfiles()にてテスト済み。
     */
    void test_getInterfaceProfile() {}
    
    
    
    /*!
     * @brief  setPortRef()のテスト
     *   ※ PortProfileはsetUp()にて登録済み。
     *   (1) setPortRef()にてPortBaseオブジェクトの参照をセット。
     *   (2) getPortRef()にてPortインタフェースのオブジェクト参照を取得。
     *   (3) (2)で取得したオブジェクト参照を用いPortインタフェースの
     *       オペレーション呼び出しテスト。
     *   (4) (3)のオペレーション呼び出しにて取得したPortProfileの要素と
     *       setUp()でセットしたそれとを比較。
     */
    void test_setPortRef() {
      Port_var port = m_ppb->_this();
      m_ppb->_remove_ref();
      
      // (1) setPortRef()にてPortBaseオブジェクトの参照をセット。
      m_ppb->setPortRef(port._retn());
      
      
      // (2) getPortRef()にてPortインタフェースのオブジェクト参照を取得。
      Port_ptr getP;
      PortProfile* pProf;
      getP = m_ppb->getPortRef();
      
      
      // (3) (2)で取得したオブジェクト参照を用いPortインタフェースのオペレーション呼び出しテスト。
      pProf = getP->get_port_profile();
      
      
      // (4) (3)のオペレーション呼び出しにて取得したPortProfileの要素とsetUp()で
      //     セットしたそれとを比較。
      string setstr, getstr;
      getstr = pProf->name;
      setstr = "inport0";
      CPPUNIT_ASSERT(getstr == setstr);
      
      getstr = pProf->interfaces[0].instance_name;
      setstr = "PortInterfaceProfile-instance_name";
      CPPUNIT_ASSERT(getstr == setstr);
      
      getstr = pProf->interfaces[0].type_name;
      setstr = "PortInterfaceProfile-type_name";
      CPPUNIT_ASSERT(getstr == setstr);
      
      CORBA::Float getval;
      pProf->properties[0].value >>= getval;
      CPPUNIT_ASSERT(m_portProfVal == getval);
      
      getstr = pProf->properties[0].name;
      setstr = "PortProfile-properties0-name";
      CPPUNIT_ASSERT(getstr == setstr);
    }
    
    
    /*!
     * @brief getPortRefのテスト
     *   test_setPortRef()にてテスト済み。
     */
    void test_getPortRef() {}
    
    
    /*!
     * @brief addConnectorProfile()のテスト
     *   ※ PortProfileはsetUp()で登録済み。
     *   (1) ConnectorProfileオブジェクト要素のセット
     *   (2) (1)でセットしたConnectorProfileをaddConnectorProfile()にて追加。
     *   (3）ConnectorProfileListの取得。
     *   (4) (2)で追加したConnectorProfileと(3)で取得したそれとを比較。
     *   (5) eraseConnectorProfile(id)にて,引数で指定したidを持つ
     *       ConnectorProfileをConnectorProfileListから削除する。
     *   (6) (5)で削除後のConnectorProfileListを取得
     *   (7) (6)で取得したConnectorProfileListの要素を確認。
     */
    /*
    void test_addConnectorProfile() {
      // (1) ConnectorProfileオブジェクト要素のセット
      ConnectorProfile cProf,getProf;
      cProf.name = "ConnectorProfile-name-add";
      cProf.connector_id = "connect_id0-add";
      
      SDOPackage::NameValue nv;
      NVList nvlist;
      CORBA::Double db, retdb;
      nv.name = "ConnectorProfile-properties0-name-add";
      db = 9999999.999;
      nv.value <<= db;
      nvlist.length(1);
      nvlist[0] = nv;
      cProf.properties = nvlist;
      
      
      // (2) (1)でセットしたConnectorProfileをaddConnectorProfile()にて追加。
      m_ppb->addConnectorProfile(cProf);
      
      
      // (3）ConnectorProfileListの取得。
      ConnectorProfileList cnctPList;
      cnctPList = m_ppb->getConnectorProfileList();
      
      
      // (4) (2)で追加したConnectorProfileと(3)で取得したそれとを比較。
      string setstr, getstr;
      getstr = cnctPList[1].name;
      setstr = cProf.name;
      CPPUNIT_ASSERT(getstr == setstr);
      
      getstr = cnctPList[1].connector_id;
      setstr = cProf.connector_id;
      CPPUNIT_ASSERT(getstr == setstr);
      
      getstr = cnctPList[1].properties[0].name;
      setstr = nv.name;
      CPPUNIT_ASSERT(getstr == setstr);
      
      cnctPList[1].properties[0].value >>= retdb;
      CPPUNIT_ASSERT(retdb == db);
      
      
      // (5) eraseConnectorProfile(id)にて,引数で指定したidを持つ
      //     ConnectorProfileをConnectorProfileListから削除する。
      // test eraseConnectorProfile()
      // Failure case: 登録していないIDでeraseConnectorProfile()を
      // 呼ぶとアボートする。
      //    m_ppb->eraseConnectorProfile("hoge");
      m_ppb->eraseConnectorProfile("connect_id0");
      
      
      // (6) (5)で削除後のConnectorProfileListを取得。
      getProf = m_ppb->getConnectorProfile("connect_id0-add");
      
      
      // (7) (6)で取得したConnectorProfileListの要素を確認。
      getstr = getProf.name;
      setstr = getProf.name;
      CPPUNIT_ASSERT(getstr == setstr);
      
      getstr = getProf.connector_id;
      setstr = getProf.connector_id;
      CPPUNIT_ASSERT(getstr == setstr);
      
      getstr = getProf.properties[0].name;
      setstr = nv.name;
      CPPUNIT_ASSERT(getstr == setstr);
      
      getProf.properties[0].value >>= retdb;
      CPPUNIT_ASSERT(retdb == db);
    }
    */
    
    /*!
     * @brief  eraseConnectorProfile()のテスト
     *   test_addConnectorProfileList()にてテスト済み。
     */
    void test_eraseConnectorProfile() {}
    
    
    /*!
     * @brief getConnectorProfileList()のテスト
     *   test_addConnectorProfileList()にてテスト済み。
     */
    void test_getConnectorProfileList() {}
    
    
    /*!
     * @brief getConnectorProfile()のテスト
     *   test_addConnectorProfileList()にてテスト済み。
     */
    void test_getConnectorProfile() {}
    
    
    /*!
     * @brief setOwner()
     *   RTObjectインタフェースの実装が完了していない。
     */
    void test_setOwner() {
      /*
	RTObject_impl* rtobj;
	
	rtobj = new RTObject_impl(m_orb, m_poa);
	
	RTObject_var p_rtobj = rtobj->_this();
	rtobj->_remove_ref();
	
	// check setOwner()
	m_ppb->setOwner(p_rtobj._retn());
      */
      
    }
    
    /*!
     * @brief getOwner()のテスト
     */
    void test_getOwner() {}
    
    
    /*!
     * @brief setProperties()のテスト
     *   ※ PortProfileはsetUp()で登録済みである。
     *   (1) getProperties()にてPortProfile.propertyを取得。
     *   (2) (1)で取得したpropertyの要素とsetUp()でセットしたそれとを比較。
     *   (3) setProperties()にてPortProfile.propertyをセット
     *   (4) getProperties()にてPortProfile.propertyを取得。
     *   (5) (3)でセットしたPortProfile.propertyと(4)で取得したそれとを比較。
     */
	/*
    void test_setProperties() {
      NVList setlist, getlist;
      SDOPackage::NameValue nv;
      
      // (1) getProperties()にてPortProfile.propertyを取得。
      getlist = m_ppb->getProperties();
      
      
      // (2) (1)で取得したpropertyの要素とsetUp()でセットしたそれとを比較。
      string getstr, setstr;
      CORBA::Float setval, retval;
      getlist[0].value >>= retval;
      
      getstr = getlist[0].name;
      setstr = m_nv.name;
      CPPUNIT_ASSERT(getstr == setstr);
      CPPUNIT_ASSERT(retval == m_portProfVal);
      
      
      // (3) setProperties()にてPortProfile.propertyをセット
      nv.name = "setProperties test";
      setval = 999.9;
      nv.value <<= setval;
      
      setlist.length(1);
      setlist[0] = nv;
      m_ppb->setProperties(setlist);
      
      
      // (4) getProperties()にてPortProfile.propertyを取得。
      getlist = m_ppb->getProperties();
      
      
      // (5) (3)でセットしたPortProfile.propertyと(4)で取得したそれとを比較。
      getlist[0].value >>= retval;
      
      getstr = getlist[0].name;
      setstr = nv.name;
      CPPUNIT_ASSERT(getstr == setstr);
      CPPUNIT_ASSERT(retval == setval);
      
    }
    */
    
    /*!
     * @brief getProperties()のテスト
     *   test_setPropertiesにてテスト済み。
     */
	/*
    void test_getProperties() {}
    */
    
    /*!
     * @brief  getUUID()のテスト
     *   (1) getUUID()にてUUIDの取得。
     *   (2) 取得したUUIDを標準出力に出力。
     */
    void test_getUUID() {
      // (1) getUUID()にてUUIDの取得。
      string getuuid = m_ppb->getUUID();
      
      // (2) 取得したUUIDを標準出力に出力。
      cout << endl << "uuid: " << getuuid << endl;
    }
    
  };
}; // namespace PortBase

/*
 * Register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(PortBase::PortBaseTests);

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
#endif // PortBase_cpp
