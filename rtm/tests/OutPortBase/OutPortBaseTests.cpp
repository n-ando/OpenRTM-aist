// -*- C++ -*-
/*!
 * @file   OutPortBaseTests.cpp
 * @brief  OutPortBase test class
 * @date   $Date: 2008/02/21 07:36:39 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * $Id$
 *
 */

/*
 * $Log: OutPortBaseTests.cpp,v $
 * Revision 1.2  2008/02/21 07:36:39  arafune
 * Some tests were added.
 *
 * Revision 1.1  2007/12/20 07:50:17  arafune
 * *** empty log message ***
 *
 * Revision 1.1  2006/12/02 18:55:54  n-ando
 * *** empty log message ***
 *
 *
 */

#ifndef OutPortBase_cpp
#define OutPortBase_cpp

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>

#include <rtm/PublisherBase.h>
#include <rtm/OutPortBase.h>

/*!
 * @class OutPortBaseTests class
 * @brief OutPortBase test
 */
namespace OutPortBase
{
  class PublisherA
    : public RTC::PublisherBase
  {
  public:
    PublisherA(std::string& footPrints) : m_footPrints(footPrints) {};
    virtual ~PublisherA() { 
      m_footPrints += "a"; 
    }

    void update() { m_footPrints += "A"; }
	  
    std::string& m_footPrints;
    // std::string m_footPrints;
  };
	
  class PublisherB
    : public RTC::PublisherBase
  {
  public:
    std::string& m_footPrints;
    // std::string m_footPrints;
    PublisherB(std::string& footPrints) : m_footPrints(footPrints) {};
    virtual ~PublisherB() { 
      m_footPrints += "b"; 
    }
    void update() { m_footPrints += "B"; }
  };
	
  class PublisherC
    : public RTC::PublisherBase
  {
  public:
    std::string& m_footPrints;
    //    std::string m_footPrints;
    PublisherC(std::string& footPrints) : m_footPrints(footPrints) {};
    virtual ~PublisherC() {
      m_footPrints += "c";
    }
    void update() { m_footPrints += "C"; }
  };
	
  class PublisherD
    : public RTC::PublisherBase
  {
  public:
    std::string& m_footPrints;
    // std::string m_footPrints;
    PublisherD(std::string& footPrints) : m_footPrints(footPrints) {};
    virtual ~PublisherD() {
      m_footPrints += "d";
    }
    void update() { m_footPrints += "D"; }
  };

  class OutPortMock
    : public RTC::OutPortBase
  {
  public:
    OutPortMock(const char* name) : OutPortBase(name) {}
  };
	
  class OutPortBaseTests
    : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(OutPortBaseTests);
    CPPUNIT_TEST(test_name);
    CPPUNIT_TEST(test_attach);
    // CPPUNIT_TEST(test_attach_back);
    //CPPUNIT_TEST(test_attach_front);
    //	CPPUNIT_TEST(test_attach_mix);
    CPPUNIT_TEST(test_detach);
    CPPUNIT_TEST(test_destructor);
    CPPUNIT_TEST_SUITE_END();
	
  public:
	
    /*!
     * @brief Constructor
     */
    OutPortBaseTests()
    {
    }
		
    /*!
     * @brief Destructor
     */
    ~OutPortBaseTests()
    {
    }
		
    /*!
     * @brief Test initialization
     */
    virtual void setUp()
    {
    }
		
    /*!
     * @brief Test finalization
     */
    virtual void tearDown()
    { 
    }
		
    /*!
     * @brief name()メソッドのテスト
     * 
     * - ポート名を正しく取得できるか？
     */
    void test_name()
    {
      OutPortMock outPort("Hello, World!");
      CPPUNIT_ASSERT_EQUAL(std::string("Hello, World!"), std::string(outPort.name()));
    }
		
    /*!
     * @brief attach()メソッドのテスト
     * 
     * - attach()メソッドを用いて複数のPublisherを順番に登録した後にnotify()を呼び出し、
     * 登録されている各Publisherが登録順にコールバックされるか？
     */
    void test_attach()
    {
			
      std::string footPrints;
      OutPortMock outPort("MyOutPort");
      outPort.attach("A", new PublisherA(footPrints));
      outPort.attach("B", new PublisherB(footPrints));
      outPort.attach("C", new PublisherC(footPrints));
      outPort.attach("D", new PublisherD(footPrints));
      outPort.notify();
			
      CPPUNIT_ASSERT_EQUAL(std::string("ABCD"), footPrints);
    }
		
    /*!
     * @brief attach_back()メソッドのテスト
     * 
     * - attach_back()メソッドを用いて複数のPublisherを順番に登録した後にnotify()を呼び出し、
     * 登録されている各Publisherが登録順にコールバックされるか？
     */
    void test_attach_back()
    {
      OutPortMock outPort("MyOutPort");
			
      std::string footPrints;
      outPort.attach_back("A", new PublisherA(footPrints));
      outPort.attach_back("B", new PublisherB(footPrints));
      outPort.attach_back("C", new PublisherC(footPrints));
      outPort.attach_back("D", new PublisherD(footPrints));
      outPort.notify();
			
      CPPUNIT_ASSERT_EQUAL(std::string("ABCD"), footPrints);
    }
		
    /*!
     * @brief attach_front()メソッドのテスト
     * 
     * - attach_front()メソッドを用いて複数のPublisherを順番に登録した後にnotify()を呼び出し、
     * 登録されている各Publisherが登録順の逆順にコールバックされるか？
     */
    void test_attach_front()
    {
      OutPortMock outPort("MyOutPort");
			
      std::string footPrints;
      outPort.attach_front("A", new PublisherA(footPrints));
      outPort.attach_front("B", new PublisherB(footPrints));
      outPort.attach_front("C", new PublisherC(footPrints));
      outPort.attach_front("D", new PublisherD(footPrints));
      outPort.notify();
			
      CPPUNIT_ASSERT_EQUAL(std::string("DCBA"), footPrints);
    }
		
    /*!
     * @brief attach_back()メソッドとattach_front()メソッドを組み合わせたテスト
     * 
     * - attach_back()メソッドとattach_front()メソッドを用いて複数のPublisherを登録した後に
     * notify()を呼び出し、登録されている各Publisherが意図どおりの順にコールバックされるか？
     */
    void test_attach_mix()
    {
      OutPortMock outPort("MyOutPort");
			
      std::string footPrints;
      outPort.attach_back("A", new PublisherA(footPrints)); // A
      outPort.attach_back("B", new PublisherB(footPrints)); // AB
      outPort.attach_front("C", new PublisherC(footPrints)); // CAB
      outPort.attach_front("D", new PublisherD(footPrints)); // DCAB
      outPort.notify();
			
      CPPUNIT_ASSERT_EQUAL(std::string("DCAB"), footPrints);
    }
		
    /*!
     * @brief detach()メソッドのテスト
     * 
     * - はじめに複数のPublisherを登録し、その後、１つずつ登録解除していき、意図どおりに指定したPublihserが登録解除されているか？
     */
    void test_detach()
    {
      OutPortMock outPort("MyOutPort");
      std::string footPrints;
			
      // はじめに複数のPublisherを登録しておく
      outPort.attach("A", new PublisherA(footPrints));
      outPort.attach("B", new PublisherB(footPrints));
      outPort.attach("C", new PublisherC(footPrints));
      outPort.attach("D", new PublisherD(footPrints));
      outPort.notify();
      CPPUNIT_ASSERT_EQUAL(std::string("ABCD"), footPrints);
			
      // PublisherAを登録解除してnotify()を呼出した際、登録解除されていない各Publisherのみが意図どおりの順序で呼び出されるか？
      footPrints.clear();
      std::auto_ptr<RTC::PublisherBase> pubA(outPort.detach("A"));
      outPort.notify();
      CPPUNIT_ASSERT_EQUAL(std::string("BCD"), footPrints);
			
      // PublisherBを登録解除してnotify()を呼出した際、登録解除されていない各Publisherのみが意図どおりの順序で呼び出されるか？
      footPrints.clear();
      std::auto_ptr<RTC::PublisherBase> pubB(outPort.detach("B"));
      outPort.notify();
      CPPUNIT_ASSERT_EQUAL(std::string("CD"), footPrints);
			
      // PublisherDを登録解除してnotify()を呼出した際、登録解除されていない各Publisherのみが意図どおりの順序で呼び出されるか？
      footPrints.clear();
      std::auto_ptr<RTC::PublisherBase> pubD(outPort.detach("D"));
      outPort.notify();
      CPPUNIT_ASSERT_EQUAL(std::string("C"), footPrints);
			
      // PublisherCを登録解除してnotify()を呼出した際、登録解除されていない各Publisherのみが意図どおりの順序で呼び出されるか？
      footPrints.clear();
      std::auto_ptr<RTC::PublisherBase> pubC(outPort.detach("C"));
      outPort.notify();
      CPPUNIT_ASSERT_EQUAL(std::string(""), footPrints);
    }
    
    /*!
     * @brief デストラクタのテスト
     * 
     * - 登録されている各Publisherが破棄されるか？
     */
    void test_destructor()
    {
      std::string footPrints;
      {
	OutPortMock outPort("MyOutPort");
	outPort.attach("A", new PublisherA(footPrints));
	outPort.attach("B", new PublisherB(footPrints));
	outPort.attach("C", new PublisherC(footPrints));
	outPort.attach("D", new PublisherD(footPrints));
				
	// この時点でフットプリントは何もないはず
	CPPUNIT_ASSERT_EQUAL(std::string(""), footPrints);
      } // destructor呼出し
			
      // 各デストラクタが呼び出されているか？
      CPPUNIT_ASSERT_EQUAL(std::string("abcd"), footPrints);
    }
    
  };
}; // namespace OutPortBase

/*
 * Register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(OutPortBase::OutPortBaseTests);

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
#endif // OutPortBase_cpp
