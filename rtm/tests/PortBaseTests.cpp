// -*- C++ -*-
/*!
 * @file 
 * @brief Properties test class
 * @date $Date: 2006-11-08 01:19:07 $
 * @author Shinji Kurihara
 * $Id: PortBaseTests.cpp,v 1.1 2006-11-08 01:19:07 kurihara Exp $
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
#include "../PortBase.h"
#include "../RTObject.h"

using namespace RTC;
using namespace std;

int g_argc;
vector<string> g_argv;

// PortBaseクラスのテスト
class PortBaseTest
  : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(PortBaseTest);
  CPPUNIT_TEST(test_get_port_profile);
  CPPUNIT_TEST(test_get_connetctor_profiles);
  CPPUNIT_TEST(test_get_connetctor_profile);
  CPPUNIT_TEST(test_connet);
  CPPUNIT_TEST(test_disconnet);
  CPPUNIT_TEST(test_disconnet_all);
  //  CPPUNIT_TEST(test_setProfile);
  CPPUNIT_TEST(test_getProfile);
  CPPUNIT_TEST(test_setName);
  CPPUNIT_TEST(test_getName);
  CPPUNIT_TEST(test_setInterfaceProfiles);
  //  CPPUNIT_TEST(test_addInterfaceProfiles);
  //  CPPUNIT_TEST(test_getInterfaceProfiles);
  //  CPPUNIT_TEST(test_getInterfaceProfile);
  CPPUNIT_TEST(test_setPortRef);
  //  CPPUNIT_TEST(test_getPortRef);
  CPPUNIT_TEST(test_addConnectorProfile);
  //  CPPUNIT_TEST(test_eraseConnectorProfile);
  //  CPPUNIT_TEST(test_getConnectorProfileList);
  //  CPPUNIT_TEST(test_getConnectorProfile);
  CPPUNIT_TEST(test_setOwner);
  CPPUNIT_TEST(test_getOwner);
  CPPUNIT_TEST(test_setProperties);
  CPPUNIT_TEST(test_getProperties);
  CPPUNIT_TEST(test_getUUID);
  CPPUNIT_TEST_SUITE_END();

private:
  PortBase* m_ppb;
  CORBA::ORB_var          m_orb;
  PortableServer::POA_var m_poa;

  NVList m_nvlist;
  SDOPackage::NameValue m_nv;
  CORBA::Float m_cnctProfVal,m_portProfVal;
public:
  
  /*
   * コンストラクタ/デストラクタ
   */
  PortBaseTest()
  {
    /*
    char* argv[g_argc];
    for (int i = 0; i < g_argc; i++) {
      argv[i] = (char *)g_argv[i].c_str();
    }

    m_orb = CORBA::ORB_init(g_argc, argv);
    CORBA::Object_var  obj = m_orb->resolve_initial_references("RootPOA");
    m_poa = PortableServer::POA::_narrow(obj);
    PortableServer::POAManager_var pman = m_poa->the_POAManager();
    pman->activate();
    */
  }
  
  ~PortBaseTest()
  {
  }
  
  /*
   * 初期化/後始末
   */
  virtual void setUp()
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

    m_ppb = new PortBase(m_orb._retn(), m_poa._retn());

    // set PortInterfaceProfile
    PortInterfaceProfile pIProf;
    pIProf.instance_name = "PortInterfaceProfile-instance_name";
    pIProf.type_name = "PortInterfaceProfile-type_name";
    pIProf.polarity = REQUIRED;

    // set PortInterfaceProfileList
    PortInterfaceProfileList pIFProfList;
    pIFProfList.length(1);
    pIFProfList[0] = pIProf;

    // set ConnectorProfile
    ConnectorProfile cProf;
    cProf.name = "ConnectorProfile-name";
    cProf.connector_id = "connect_id0";
    m_nv.name = "ConnectorProfile-properties0-name";
    m_cnctProfVal = 1.1;
    m_nv.value <<= m_cnctProfVal;
    m_nvlist.length(1);
    m_nvlist[0] = m_nv;
    cProf.properties = m_nvlist;

    // set ConnectorProfileList
    ConnectorProfileList cProfList;
    cProfList.length(1);
    cProfList[0] = cProf;

    // set PortProfile
    PortProfile pProf;
    pProf.name = "inport0";
    pProf.interfaces = pIFProfList;
    pProf.connector_profiles = cProfList;
    m_nv.name = "PortProfile-properties0-name";
    m_portProfVal = 2.2;
    m_nv.value <<= m_portProfVal;
    m_nvlist[0] = m_nv;
    pProf.properties = m_nvlist;

    // set PortProfile
    m_ppb->setProfile(pProf);
  }
  
  virtual void tearDown()
  { 
    //    delete m_ppb;
  }


  /* tests for */
  void test_get_port_profile() {
    PortProfile* getProf;

    // get PortProfile
    getProf = m_ppb->get_port_profile();

    string setstr, getstr;

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


  /* tests for */
  void test_get_connetctor_profiles() {
    ConnectorProfileList* cpList;
    string setstr, getstr;

    // get ConnectorProfileList
    cpList = m_ppb->get_connector_profiles();
    
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


  /* tests for */
  void test_get_connetctor_profile() {
    ConnectorProfile* cProf;
    string setstr, getstr;

    // get ConnectorProfile
    cProf = m_ppb->get_connector_profile("connect_id0");
    
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


  /* tests for */
  void test_connet() {}


  /* tests for */
  void test_disconnet() {}


  /* tests for */
  void test_disconnet_all() {}


  /* tests for */
  void test_setProfile() {
    // test_get_port_profile() にてテスト
  }


  /* tests for */
  void test_getProfile() {
    PortProfile getProf;

    // get PortProfile
    getProf = m_ppb->getProfile();

    string setstr, getstr;

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

  /* tests for */
  void test_setName() {
    m_ppb->setName("inport0-changed");
    
    PortProfile getProf;
    // get PortProfile
    getProf = m_ppb->getProfile();

    string setstr, getstr;

    // check PortProfile.name
    getstr = getProf.name;
    setstr = "inport0-changed";
    CPPUNIT_ASSERT(getstr == setstr);
  }


  /* tests for */
  void test_getName() {
    const char* retval(m_ppb->getName());
    string setname, getname;
    setname = "inport0";
    getname = retval;
    CPPUNIT_ASSERT(getname == setname);
  }


  /* tests for */
  void test_setInterfaceProfiles() {
    // set PortInterfaceProfile
    PortInterfaceProfile pIProf;
    pIProf.instance_name = "PortInterfaceProfile-instance_name-changed";
    pIProf.type_name = "PortInterfaceProfile-type_name-changed";
    pIProf.polarity = REQUIRED;

    // set PortInterfaceProfileList
    PortInterfaceProfileList pIFProfList;
    pIFProfList.length(1);
    pIFProfList[0] = pIProf;
    m_ppb->setInterfaceProfiles(pIFProfList);

    
    PortInterfaceProfileList getList;
    // get PortInterfaceProfileList
    getList = m_ppb->getInterfaceProfiles();

    string getstr, setstr;

    // check PortInterfaceProfile
    getstr = getList[0].instance_name;
    setstr = "PortInterfaceProfile-instance_name-changed";
    CPPUNIT_ASSERT(getstr == setstr);

    getstr = getList[0].type_name;
    setstr = "PortInterfaceProfile-type_name-changed";
    CPPUNIT_ASSERT(getstr == setstr);

    CPPUNIT_ASSERT(getList[0].polarity == REQUIRED);


    // add InterfaceProfile
    pIProf.instance_name = "PortInterfaceProfile-instance_name-add";
    pIProf.type_name = "PortInterfaceProfile-type_name-add";
    pIProf.polarity = PROVIDED;

    m_ppb->addInterfaceProfile(pIProf);

    getList = m_ppb->getInterfaceProfiles();

    // check PortInterfaceProfile
    getstr = getList[1].instance_name;
    setstr = "PortInterfaceProfile-instance_name-add";
    CPPUNIT_ASSERT(getstr == setstr);

    getstr = getList[1].type_name;
    setstr = "PortInterfaceProfile-type_name-add";
    CPPUNIT_ASSERT(getstr == setstr);

    CPPUNIT_ASSERT(getList[1].polarity == PROVIDED);


    // get PortInterfaceProfile
    PortInterfaceProfile getProf;
    getProf = m_ppb->getInterfaceProfile("PortInterfaceProfile-instance_name-add");

    // check PortInterfaceProfile
    getstr = getProf.instance_name;
    setstr = "PortInterfaceProfile-instance_name-add";
    CPPUNIT_ASSERT(getstr == setstr);

    getstr = getProf.type_name;
    setstr = "PortInterfaceProfile-type_name-add";
    CPPUNIT_ASSERT(getstr == setstr);

    CPPUNIT_ASSERT(getProf.polarity == PROVIDED);
  }

  /* tests for */
  void test_addInterfaceProfiles() {
    // test_setInterfaceProfiles()にてテスト。
  }


  /* tests for */
  void test_getInterfaceProfiles() {
    // test_setInterfaceProfiles()にてテスト。
  }


  /* tests for */
  void test_getInterfaceProfile() {
    // test_setInterfaceProfiles()にてテスト。
  }

  /* tests for */
  void test_setPortRef() {
    Port_var port = m_ppb->_this();
    m_ppb->_remove_ref();

    // check setPortRef()
    m_ppb->setPortRef(port._retn());

    Port_ptr getP;
    PortProfile* pProf;
    // check getPortRef()
    getP = m_ppb->getPortRef();
    
    // Portのオペレーション呼び出しテスト
    pProf = getP->get_port_profile();

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


  /* tests for */
  void test_getPortRef() {
    // test_setPortRef()にてテスト。
  }


  /* tests for */
  void test_addConnectorProfile() {
    // set ConnectorProfile
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

    // test addConnectorProfile()
    m_ppb->addConnectorProfile(cProf);

    ConnectorProfileList cnctPList;
    // test getConnectorProfileList()
    cnctPList = m_ppb->getConnectorProfileList();

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

    // test eraseConnectorProfile()
    //    m_ppb->eraseConnectorProfile("hoge");
    m_ppb->eraseConnectorProfile("connect_id0");

    getProf = m_ppb->getConnectorProfile("connect_id0-add");

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


  /* tests for */
  void test_eraseConnectorProfile() {
    // test_addConnectorProfileList()にてテスト
  }


  /* tests for */
  void test_getConnectorProfileList() {
    // test_addConnectorProfileList()にてテスト
  }


  /* tests for */
  void test_getConnectorProfile() {
    // test_addConnectorProfileList()にてテスト
  }


  /* tests for */
  void test_setOwner() {
    /* // RTObjectインタフェースの実装が完了していない。
    RTObject_impl* rtobj;

    rtobj = new RTObject_impl(m_orb._retn(), m_poa._retn());

    RTObject_var p_rtobj = rtobj->_this();
    rtobj->_remove_ref();

    // check setOwner()
    m_ppb->setOwner(p_rtobj._retn());
    */

  }

  /* tests for */
  void test_getOwner() {}


  /* tests for */
  void test_setProperties() {
    NVList setlist, getlist;
    SDOPackage::NameValue nv;

    // test getProperties()
    getlist = m_ppb->getProperties();

    string getstr, setstr;
    CORBA::Float setval, retval;
    getlist[0].value >>= retval;

    getstr = getlist[0].name;
    setstr = m_nv.name;
    CPPUNIT_ASSERT(getstr == setstr);
    CPPUNIT_ASSERT(retval == m_portProfVal);

    // test setProperties()
    nv.name = "setProperties test";
    setval = 999.9;
    nv.value <<= setval;

    setlist.length(1);
    setlist[0] = nv;
    m_ppb->setProperties(setlist);
    
    getlist = m_ppb->getProperties();
    getlist[0].value >>= retval;

    getstr = getlist[0].name;
    setstr = nv.name;
    CPPUNIT_ASSERT(getstr == setstr);
    CPPUNIT_ASSERT(retval == setval);

  }


  /* tests for */
  void test_getProperties() {
    // test_setPropertiesにてテスト
  }


  /* tests for */
  void test_getUUID() {
    string getuuid = m_ppb->getUUID();
    cout << endl << "uuid: " << getuuid << endl;
  }

};


/*
 * register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(PortBaseTest);



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
