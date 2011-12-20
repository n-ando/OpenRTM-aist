// -*- C++ -*-
/*!
 * @file   DataInPortTests.cpp
 * @brief  DataInPort test class
 * @date   $Date: 2008/04/02 11:04:52 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * $Id$
 *
 */

/*
 * $Log: DataInPortTests.cpp,v $
 * Revision 1.2  2008/04/02 11:04:52  arafune
 * Added some tests.
 *
 * Revision 1.1  2007/12/20 07:50:18  arafune
 * *** empty log message ***
 *
 * Revision 1.2  2007/01/12 14:49:42  n-ando
 * The constructor signature of DataInPort was changed.
 *
 * Revision 1.1  2006/11/27 08:30:56  n-ando
 * TestSuites are devided into each directory.
 *
 *
 */

#ifndef DataInPort_cpp
#define DataInPort_cpp

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>

#include <idl/BasicDataTypeSkel.h>
#include <idl/RTCSkel.h>
#include <coil/stringutil.h>
#include <rtm/InPort.h>
#include <rtm/DataInPort.h>

/*!
 * @class DataInPortTests class
 * @brief DataInPort test
 */
namespace DataInPort
{
  template <class DataType, template <class DataType> class Buffer>
  class DataInPortMock
    : public RTC::DataInPort
  {
  public:
    DataInPortMock(
		   const char* name,
		   RTC::InPort<DataType, Buffer>& inport,
		   coil::Properties& prop)
      : RTC::DataInPort(name, inport, prop)
    {
    }
		
    // public override for test
    virtual RTC::ReturnCode_t publishInterfaces_public(
						       RTC::ConnectorProfile& connector_profile)
    {
      return RTC::DataInPort::publishInterfaces(connector_profile);
    }
		
    // public override for test
    virtual RTC::ReturnCode_t subscribeInterfaces_public(
							 const RTC::ConnectorProfile& connector_profile)
    {
      return RTC::DataInPort::subscribeInterfaces(connector_profile);
    }
		
    // public override for test
    virtual void unsubscribeInterfaces_public(
					      const RTC::ConnectorProfile& connector_profile)
    {
      RTC::DataInPort::unsubscribeInterfaces(connector_profile);
    }
		
  };

  class OutPortAnyMock
    : public virtual POA_RTC::OutPortAny,
      public virtual PortableServer::RefCountServantBase
  {
  public:
    OutPortAnyMock(const CORBA::Any& data) : m_data(data), m_calledCount(0) {}
    virtual CORBA::Any* get() { ++m_calledCount; return new CORBA::Any(m_data); }
    int getCalledCount() const { return m_calledCount; }
		
  private:
    int m_calledCount;
    CORBA::Any m_data;
  };

  class DataInPortTests
    : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(DataInPortTests);
    CPPUNIT_TEST(test_get_port_profile);
    CPPUNIT_TEST(test_publishInterfaces_CORBA_Any);
//    CPPUNIT_TEST(test_publishInterfaces_TCP_Any);
    CPPUNIT_TEST(test_subscribeInterfaces_CORBA_Any);
    CPPUNIT_TEST(test_connect);
    CPPUNIT_TEST_SUITE_END();
		
  private:
    CORBA::ORB_ptr m_pORB;
    PortableServer::POA_ptr m_pPOA;
  
  public:
		
    /*!
     * @brief Constructor
     */
    DataInPortTests()
    {
    }
		
    /*!
     * @brief Destructor
     */
    ~DataInPortTests()
    {
    }
		
    /*!
     * @brief Test initialization
     */
    virtual void setUp()
    {
      int argc = 0;
      char** argv = 0;

      m_pORB = CORBA::ORB_init(argc, argv);
      m_pPOA = PortableServer::POA::_narrow(
					    m_pORB->resolve_initial_references("RootPOA"));
      m_pPOA->the_POAManager()->activate();

      coil::usleep(100000);
    }
		
    /*!
     * @brief Test finalization
     */
    virtual void tearDown()
    {
      //      if (m_pORB != 0) {
      //	m_pORB->destroy();
      //	m_pORB = 0;
      //      }
    }
		
    /*!
     * @brief get_port_profile()メソッドのテスト
     * 
     * - PortProfileの名称を正しく取得できるか？
     * - "port.port_type"プロパティは正しく取得されるか？
     * - "dataport.data_type"プロパティは正しく取得されるか？
     * - "dataport.interface_type"プロパティは正しく取得されるか？
     * - "dataport.subscription_type"プロパティは正しく取得されるか？
     */
    void test_get_port_profile()
    {
      // DataInPortを生成する
      RTC::TimedFloat inPortBindValue;
      RTC::InPort<RTC::TimedFloat>* pInPort =
	new RTC::InPort<RTC::TimedFloat>("name of InPort", inPortBindValue); // will be deleted automatically

      coil::Properties dataInPortProps;
      RTC::DataInPort* pDataInPort =
	new RTC::DataInPort("name of DataInPort", *pInPort, dataInPortProps); // will be deleted automatically
			

      // PortProfileを取得する
      RTC::PortProfile* pPortProfile = pDataInPort->get_port_profile();
			
      // - PortProfileの名称が正しく取得されるか？
      CPPUNIT_ASSERT_EQUAL(std::string("name of DataInPort"),
			   std::string(pPortProfile->name));
				
      // "port.port_type"プロパティは正しく取得されるか？
      CPPUNIT_ASSERT_EQUAL(std::string("DataInPort"),
			   NVUtil::toString(pPortProfile->properties, "port.port_type"));
			
      // "dataport.data_type"プロパティは正しく取得されるか？
      CPPUNIT_ASSERT_EQUAL(std::string("TimedFloat"),
			   NVUtil::toString(pPortProfile->properties, "dataport.data_type"));
			
      // "dataport.interface_type"プロパティは正しく取得されるか？
      // OutPortCorbaProvider --> CORBA_Any
      // OutPortTcpSockProvider --> TCP_Any
      CPPUNIT_ASSERT_EQUIVALENT("CORBA_Any",
				NVUtil::toString(pPortProfile->properties, "dataport.interface_type"));
			
      // "dataport.subscription_type"プロパティは正しく取得されるか？
      CPPUNIT_ASSERT_EQUIVALENT("Any",
				NVUtil::toString(pPortProfile->properties, "dataport.subscription_type"));

      delete pDataInPort;
      delete pInPort;
    }

    /*!
     * @brief インタフェースタイプがCORBA_Anyの場合の、publishInterfaces()メソッドのテスト
     * 
     * - "dataport.corba_any.inport_ref"プロパティを取得できるか？
     */
    void test_publishInterfaces_CORBA_Any()
    {
      // DataInPortを生成する
      RTC::TimedFloat inPortBindValue;
      RTC::InPort<RTC::TimedFloat>* pInPort =
	new RTC::InPort<RTC::TimedFloat>("name of InPort", inPortBindValue); // will be deleted automatically
			
      coil::Properties dataInPortProps;
      DataInPortMock<RTC::TimedFloat, RTC::RingBuffer>* pDataInPort =
	new DataInPortMock<RTC::TimedFloat, RTC::RingBuffer>(
							     "name of DataInPort", *pInPort, dataInPortProps); // will be deleted automatically
			
      // CORBA_Any, Push, Newの組合せを指定してpublishInterfaces()を呼出す
      RTC::ConnectorProfile connProf;
      connProf.connector_id = "id";
      connProf.name = CORBA::string_dup("name");
      CORBA_SeqUtil::push_back(connProf.properties,
			       NVUtil::newNV("dataport.interface_type", "CORBA_Any"));
      CORBA_SeqUtil::push_back(connProf.properties,
			       NVUtil::newNV("dataport.dataflow_type", "Push"));
      CORBA_SeqUtil::push_back(connProf.properties,
			       NVUtil::newNV("dataport.subscription_type", "Any"));
      CPPUNIT_ASSERT_EQUAL(RTC::RTC_OK,
			   pDataInPort->publishInterfaces_public(connProf));
			
      // "dataport.corba_any.inport_ref"プロパティを取得できるか？
      RTC::InPortAnyRef inPortAnyRef;
      NVUtil::find(connProf.properties,
		   "dataport.corba_any.inport_ref") >>= inPortAnyRef;
      CPPUNIT_ASSERT(! CORBA::is_nil(inPortAnyRef));
      delete pDataInPort;
      delete pInPort;
    }
		
    /*!
     * @brief インタフェースタイプがTCP_Anyの場合の、publishInterfaces()メソッドのテスト
     * 
     * - "dataport.tcp_any.inport_addr"プロパティを取得できるか？
     */
    void test_publishInterfaces_TCP_Any()
    {
      // DataOutPortを生成する
      RTC::TimedFloat inPortBindValue;
      RTC::InPort<RTC::TimedFloat>* pInPort =
	new RTC::InPort<RTC::TimedFloat>("name of InPort", inPortBindValue); // will be deleted automatically
			
      coil::Properties dataInPortProps;
      DataInPortMock<RTC::TimedFloat, RTC::RingBuffer>* pDataInPort =
	new DataInPortMock<RTC::TimedFloat, RTC::RingBuffer>(
							     "name of DataInPort", *pInPort, dataInPortProps); // will be deleted automatically
			
      // TCP_Any, Pull, Periodicの組合せを指定してpublishInterfaces()を呼出す
      RTC::ConnectorProfile connProf;
      connProf.connector_id = "id";
      connProf.name = CORBA::string_dup("name");
      CORBA_SeqUtil::push_back(connProf.properties,
			       NVUtil::newNV("dataport.interface_type", "TCP_Any"));
      CORBA_SeqUtil::push_back(connProf.properties,
			       NVUtil::newNV("dataport.dataflow_type", "Push"));
      CORBA_SeqUtil::push_back(connProf.properties,
			       NVUtil::newNV("dataport.subscription_type", "Any"));
      CPPUNIT_ASSERT_EQUAL(RTC::RTC_OK,
			   pDataInPort->publishInterfaces_public(connProf));
			
      // "dataport.tcp_any.inport_addr"プロパティを取得できるか？
      CORBA::Long index = NVUtil::find_index(
					     connProf.properties, "dataport.tcp_any.inport_addr");
      CPPUNIT_ASSERT(index > 0);
      delete pDataInPort;
      delete pInPort;
    }

    /*!
     * @brief インタフェースタイプがCORBA_Anyの場合の、subscribeInterfaces()メソッドのテスト
     */
    void test_subscribeInterfaces_CORBA_Any()
    {
      // DataInPortを生成する
      RTC::TimedFloat inPortBindValue;
      RTC::InPort<RTC::TimedFloat>* pInPort =
	new RTC::InPort<RTC::TimedFloat>("name of InPort", inPortBindValue); // will be deleted automatically
			
      coil::Properties dataInPortProps;
      DataInPortMock<RTC::TimedFloat, RTC::RingBuffer>* pDataInPort =
	new DataInPortMock<RTC::TimedFloat, RTC::RingBuffer>(
							     "name of DataInPort", *pInPort, dataInPortProps); // will be deleted automatically
			
      // ConnectorProfileに、接続に必要となるプロパティをセットする
      RTC::ConnectorProfile connProf;
      connProf.connector_id = "id";
      connProf.name = CORBA::string_dup("name");
      CORBA_SeqUtil::push_back(connProf.properties,
			       NVUtil::newNV("dataport.interface_type", "CORBA_Any"));
      CORBA_SeqUtil::push_back(connProf.properties,
			       NVUtil::newNV("dataport.dataflow_type", "Push"));
      CORBA_SeqUtil::push_back(connProf.properties,
			       NVUtil::newNV("dataport.subscription_type", "New"));
				
      RTC::TimedFloat value; value.data = 3.14159;
      CORBA::Any valueAny; valueAny <<= value;
      OutPortAnyMock* pOutPortAny = new OutPortAnyMock(valueAny);
      CORBA_SeqUtil::push_back(connProf.properties,
			       NVUtil::newNV("dataport.corba_any.outport_ref",
					     RTC::OutPortAny::_duplicate(pOutPortAny->_this())));
			
      // subscribeInterfaces()メソッドを呼び出す
      // （これによりDataInPortがOutPortAnyへの参照を取得して、接続が完了する）
      CPPUNIT_ASSERT_EQUAL(RTC::RTC_OK,
			   pDataInPort->subscribeInterfaces_public(connProf));
      delete pDataInPort;
      delete pInPort;
    }

    /*!
     * @brief connect()メソッドのテスト（DataInPort単体）
     * 
     * - ConectorProfileのconnector_idが正しく設定されるか？
     * - "dataport.corba_any.inport_ref"プロパティに正しくInPortオブジェクトの参照が設定されるか？
     */
    void test_connect()
    {
      // DataInPortを生成する
      RTC::TimedFloat inPortBindValue;
      RTC::InPort<RTC::TimedFloat>* pInPort =
	new RTC::InPort<RTC::TimedFloat>("name of InPort", inPortBindValue); // will be deleted automatically

      coil::Properties dataInPortProps;
      DataInPortMock<RTC::TimedFloat, RTC::RingBuffer>* pDataInPort =
	new DataInPortMock<RTC::TimedFloat, RTC::RingBuffer>(
							     "name of DataInPort", *pInPort, dataInPortProps); // will be deleted automatically

      // 接続プロファイルを作成する
      RTC::ConnectorProfile connProf;
      connProf.connector_id = ""; // 意図的にブランクにしておく
      connProf.name = "connector0";
      connProf.ports.length(1);
      connProf.ports[0] = pDataInPort->get_port_profile()->port_ref;
      CORBA_SeqUtil::push_back(connProf.properties,
			       NVUtil::newNV("dataport.interface_type", "CORBA_Any"));
      CORBA_SeqUtil::push_back(connProf.properties,
			       NVUtil::newNV("dataport.dataflow_type", "Push"));
      CORBA_SeqUtil::push_back(connProf.properties,
			       NVUtil::newNV("dataport.subscription_type", "New"));
			
      // 接続する
      pDataInPort->connect(connProf);
			
      // 接続IDがセットされていることを確認する
      CPPUNIT_ASSERT(std::string(connProf.connector_id) != std::string(""));
			
      // "dataport.corba_any.inport_ref"プロパティを取得できるか？
      RTC::InPortAnyRef inPortAnyRef;
      NVUtil::find(connProf.properties,
		   "dataport.corba_any.inport_ref") >>= inPortAnyRef;
      CPPUNIT_ASSERT(! CORBA::is_nil(inPortAnyRef));

      // "dataport.corba_any.inport_ref"プロパティに設定されている参照が、InPortの参照であることを確認する
      // InPortの参照を用いてput()を呼び出してテスト用の値を渡す
      RTC::TimedFloat putValue;
      putValue.data = 3.14159;
      CORBA::Any putValueAny;
      putValueAny <<= putValue;
      inPortAnyRef->put(putValueAny);
			
      // InPortオブジェクトに（参照ではなく）直接アクセスして値を読み取り、
      // 先ほど参照を用いてputされた値と一致することを確認する
      RTC::TimedFloat readValue = pInPort->read();
      CPPUNIT_ASSERT_EQUAL(putValue.data, readValue.data);
      delete pDataInPort;
      delete pInPort;
    }
    
  private:
		
    void CPPUNIT_ASSERT_EQUIVALENT(const std::string& lhs, const std::string& rhs)
    {
      std::vector<std::string> lhsValues = coil::split(lhs, ",");
      std::vector<std::string> rhsValues = coil::split(rhs, ",");
			
      // 要素数が異なれば、中身を見るまでもなく同一ではないと判定できる
      if (lhsValues.size() != rhsValues.size())
	{
	  CPPUNIT_ASSERT_EQUAL(lhs, rhs);
	}
			
      // 要素数は同じなので、中身を逐一比較する
      sort(lhsValues.begin(), lhsValues.end());
      sort(rhsValues.begin(), rhsValues.end());
      std::vector<std::string>::size_type size = lhsValues.size();
      for (std::vector<std::string>::size_type i = 0; i < size; ++i)
	{
	  if (lhsValues[i] != rhsValues[i])
	    {
	      CPPUNIT_ASSERT_EQUAL(lhs, rhs);
	    }
	}
			
      // ここまでたどり着いたのであれば、同一と判定される
      return;
    }
		
  };
}; // namespace DataInPort

/*
 * Register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(DataInPort::DataInPortTests);

#ifdef LOCAL_MAIN
int main(int argc, char* argv[])
{

  FORMAT format = TEXT_OUT;
  int target = 0;
  std::string xsl;
  std::string ns;
  std::string fname;
  std::ofstream ofs;

  int i(1);
  while (i < argc)
    {
      std::string arg(argv[i]);
      std::string next_arg;
      if (i + 1 < argc) next_arg = argv[i + 1];
      else              next_arg = "";

      if (arg == "--text") { format = TEXT_OUT; break; }
      if (arg == "--xml")
	{
	  if (next_arg == "")
	    {
	      fname = argv[0];
	      fname += ".xml";
	    }
	  else
	    {
	      fname = next_arg;
	    }
	  format = XML_OUT;
	  ofs.open(fname.c_str());
	}
      if ( arg == "--compiler"  ) { format = COMPILER_OUT; break; }
      if ( arg == "--cerr"      ) { target = 1; break; }
      if ( arg == "--xsl"       )
	{
	  if (next_arg == "") xsl = "default.xsl"; 
	  else                xsl = next_arg;
	}
      if ( arg == "--namespace" )
	{
	  if (next_arg == "")
	    {
	      std::cerr << "no namespace specified" << std::endl;
	      exit(1); 
	    }
	  else
	    {
	      xsl = next_arg;
	    }
	}
      ++i;
    }
  CppUnit::TextUi::TestRunner runner;
  if ( ns.empty() )
    runner.addTest(CppUnit::TestFactoryRegistry::getRegistry().makeTest());
  else
    runner.addTest(CppUnit::TestFactoryRegistry::getRegistry(ns).makeTest());
  CppUnit::Outputter* outputter = 0;
  std::ostream* stream = target ? &std::cerr : &std::cout;
  switch ( format )
    {
    case TEXT_OUT :
      outputter = new CppUnit::TextOutputter(&runner.result(),*stream);
      break;
    case XML_OUT :
      std::cout << "XML_OUT" << std::endl;
      outputter = new CppUnit::XmlOutputter(&runner.result(),
					    ofs, "shift_jis");
      static_cast<CppUnit::XmlOutputter*>(outputter)->setStyleSheet(xsl);
      break;
    case COMPILER_OUT :
      outputter = new CppUnit::CompilerOutputter(&runner.result(),*stream);
      break;
    }
  runner.setOutputter(outputter);
  runner.run();
  return 0; // runner.run() ? 0 : 1;
}
#endif // MAIN
#endif // DataInPort_cpp
