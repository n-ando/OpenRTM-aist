// -*- C++ -*-
/*!
 * @file   PublisherFlushTests.cpp
 * @brief  PublisherFlush test class
 * @date   $Date: 2008/01/23 09:20:42 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * $Id$
 *
 */

/*
 * $Log: PublisherFlushTests.cpp,v $
 * Revision 1.2  2008/01/23 09:20:42  arafune
 * modified some tests.
 *
 * Revision 1.1  2007/12/20 07:50:18  arafune
 * *** empty log message ***
 *
 * Revision 1.2  2007/01/12 14:54:32  n-ando
 * The constructor's signature was changed.
 * InPortConsumer base class is now abstruct class. It needs concrete class.
 *
 * Revision 1.1  2006/12/18 06:51:31  n-ando
 * The first commitment.
 *
 *
 */

#ifndef PublisherFlush_cpp
#define PublisherFlush_cpp

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>

#include <rtm/InPortCorbaCdrConsumer.h>
#include <rtm/PublisherFlush.h>
#include <rtm/CdrRingBuffer.h>

#include <sys/time.h>
/*!
 * @class PublisherFlushTests class
 * @brief PublisherFlush test
 */
namespace PublisherFlush
{
  /*!
   * 
   * 
   */
  class InPortCorbaCdrConsumerMock
    : public RTC::InPortCorbaCdrConsumer
  {
  public:
      /*!
       * 
       * 
       */
      InPortCorbaCdrConsumerMock(void)
      {
          m_buffer = new RTC::CdrRingBuffer();
      }
      /*!
       * 
       * 
       */
      virtual ~InPortCorbaCdrConsumerMock()
      {
      }
      /*!
       * 
       * 
       */
      virtual ReturnCode put(const cdrMemoryStream& data)
      {
          if (m_buffer->full())
          {
std::cout<<"    BUFFER_FULL:"<<RTC::PublisherFlush::BUFFER_FULL<<std::endl;
               return RTC::PublisherFlush::BUFFER_FULL;
           }


           RTC::BufferStatus::Enum ret = m_buffer->write(data);

           switch(ret)
           {
               case RTC::BufferStatus::BUFFER_OK:
                   return RTC::PublisherFlush::PORT_OK;
                   break;
               case RTC::BufferStatus::BUFFER_ERROR:
                   return RTC::PublisherFlush::PORT_ERROR;
                   break;
               case RTC::BufferStatus::BUFFER_FULL:
                   return RTC::PublisherFlush::BUFFER_FULL;
                   break;
               case RTC::BufferStatus::BUFFER_EMPTY:
                   return RTC::PublisherFlush::BUFFER_EMPTY;
                   break;
               case RTC::BufferStatus::TIMEOUT:
                   return RTC::PublisherFlush::BUFFER_TIMEOUT;
                   break;
               default:
                   return RTC::PublisherFlush::UNKNOWN_ERROR;
           }
           return RTC::PublisherFlush::UNKNOWN_ERROR;
      }
      /*!
       * 
       * 
       */
      cdrMemoryStream get_m_put_data(void)
      {
          cdrMemoryStream cdr;
          m_buffer->read(cdr);

          return cdr;
      }
  private:
       RTC::CdrBufferBase* m_buffer;
       ::OpenRTM::CdrData  m_put_data;
  };

  class PublisherFlushTests
    : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(PublisherFlushTests);
		
    CPPUNIT_TEST(test_setConsumer);
    CPPUNIT_TEST(test_activate_deactivate_isActive);
    CPPUNIT_TEST(test_write);
//    CPPUNIT_TEST(test_update_immediacy);
		
    CPPUNIT_TEST_SUITE_END();
		
  private:
		
  public:
	
    /*!
     * @brief Constructor
     */
    PublisherFlushTests()
    {
    }
		
    /*!
     * @brief Destructor
     */
    ~PublisherFlushTests()
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
//      sleep(1);
    }
		
    /*!
     * @brief setConsumer()メソッドのテスト
     * 
     */
    void test_setConsumer(void)
    {
        RTC::InPortCorbaCdrConsumer *consumer0 
                                    = new RTC::InPortCorbaCdrConsumer();
        RTC::InPortCorbaCdrConsumer *consumer1 
                                     = new RTC::InPortCorbaCdrConsumer();
        RTC::PublisherFlush publisher;

        //NULLを渡した場合INVALID_ARGSとなることを確認する。
        CPPUNIT_ASSERT_EQUAL(RTC::PublisherFlush::INVALID_ARGS, 
                             publisher.setConsumer(NULL));

        //
        CPPUNIT_ASSERT_EQUAL(RTC::PublisherFlush::PORT_OK, 
                             publisher.setConsumer(consumer0));

        //
        CPPUNIT_ASSERT_EQUAL(RTC::PublisherFlush::PORT_OK, 
                             publisher.setConsumer(consumer1));

        delete consumer0;
        delete consumer1;
 
    }
    /*!
     * @brief activate(),deactivate(),isActiveメソッドのテスト
     * 
     */
    void test_activate_deactivate_isActive(void)
    {
        RTC::InPortCorbaCdrConsumer *consumer 
                                    = new RTC::InPortCorbaCdrConsumer();
        RTC::PublisherFlush publisher;
        publisher.setConsumer(consumer);

        CPPUNIT_ASSERT_EQUAL(false, 
                             publisher.isActive());
        
        CPPUNIT_ASSERT_EQUAL(RTC::PublisherFlush::PORT_OK, 
                             publisher.activate());

        CPPUNIT_ASSERT_EQUAL(true, 
                             publisher.isActive());
        
        //既に activate されている場合は 
        //activateすると
        //PORT_OK を返すことを確認する。
        CPPUNIT_ASSERT_EQUAL(RTC::PublisherFlush::PORT_OK, 
                             publisher.activate());

        CPPUNIT_ASSERT_EQUAL(true, 
                             publisher.isActive());
        
        CPPUNIT_ASSERT_EQUAL(RTC::PublisherFlush::PORT_OK, 
                             publisher.deactivate());

        CPPUNIT_ASSERT_EQUAL(false, 
                             publisher.isActive());
        
        //activate されていない状態で、
        //deactivateすると
        //PORT_OK を返すことを確認する。
        CPPUNIT_ASSERT_EQUAL(RTC::PublisherFlush::PORT_OK, 
                             publisher.deactivate());
        
        CPPUNIT_ASSERT_EQUAL(false, 
                             publisher.isActive());
        
        delete consumer;
    }
    /*!
     * @brief write()メソッドのテスト
     * 
     */
    void test_write(void)
    {
        InPortCorbaCdrConsumerMock *consumer 
                                    = new InPortCorbaCdrConsumerMock();

        RTC::PublisherFlush publisher;

        //Consumerを設定しない状態でwriteをコール
        {
        cdrMemoryStream cdr;
        12345 >>= cdr;
        CPPUNIT_ASSERT_EQUAL(RTC::PublisherFlush::PRECONDITION_NOT_MET, 
                             publisher.write(cdr,0,0));
        }

        publisher.setConsumer(consumer);

        //activateする前にwriteをコール
        {
        cdrMemoryStream cdr;
        12345 >>= cdr;
        CPPUNIT_ASSERT_EQUAL(RTC::PublisherFlush::PRECONDITION_NOT_MET, 
                             publisher.write(cdr,0,0));
        }
        publisher.activate();

        CORBA::Long testdata[8] = { 123,279,3106,31611,125563,
                                    125563,846459,2071690107, };

        for(int icc(0);icc<8;++icc)
        {
            cdrMemoryStream cdr;
            testdata[icc] >>= cdr;

            CPPUNIT_ASSERT_EQUAL(RTC::PublisherFlush::PORT_OK,
                                 publisher.write(cdr,0,0));

        }

        //full の状態でコール(full)
        {
        cdrMemoryStream cdr;
        12345 >>= cdr;
        CPPUNIT_ASSERT_EQUAL(RTC::PublisherFlush::BUFFER_FULL,
                                 publisher.write(cdr,0,0));
        }

        for(int icc(0);icc<8;++icc)
        {
            cdrMemoryStream data;
            data = consumer->get_m_put_data();
            CORBA::ULong inlen = data.bufSize();
            CPPUNIT_ASSERT_EQUAL(4,(int)inlen);

            CORBA::Octet oct[8];
            data.get_octet_array (oct, (int)inlen);
            long lval(0);
            for(int ic(0);ic<(int)inlen;++ic)
            {
                lval = lval+(int)(oct[ic]<<(ic*8));
            }
            CPPUNIT_ASSERT_EQUAL((long)testdata[icc],lval);
        }

        //deactivateしてからwriteをコール
        publisher.deactivate();
        {
        cdrMemoryStream cdr;
        12345 >>= cdr;
        CPPUNIT_ASSERT_EQUAL(RTC::PublisherFlush::PRECONDITION_NOT_MET, 
                             publisher.write(cdr,0,0));
        }
    }
    /*!
     * @brief update()メソッド呼出周辺の即時性のテスト
     * 
     * - Publisherのupdate()メソッド呼出後、所定時間内にConsumerのpush()メソッドが呼び出されるか？
     * - Consumerのpush()メソッド終了後、所定時間内にPublihserのupdate()メソッド呼出から復帰するか？
     * 
     * @attention リアルタイム性が保証されているわけでもなく、仕様上も呼出までの時間を明記しているわけではないので、ここでの所定時間はテスト作成者の主観によるものに過ぎない。
     */
/*
    void test_update_immediacy()
    {
      long sleepTick = 100000; // 0.1 [sec]
			
      MockConsumer* consumer = new MockConsumer(sleepTick);
      coil::Properties prop;
      RTC::PublisherFlush publisher(consumer, prop);
			
      for (int i = 0; i < 10; i++)
	{
	  consumer->setDelayStartTime();
	  publisher.update();
	  consumer->recordReturnTick();
	}
			
      long permissibleDelayTick = 100000; // 0.1 [sec]
      const std::vector<long>& delayTicks = consumer->getDelayTicks();
      for (std::vector<long>::size_type i = 0; i < delayTicks.size(); i++)
	{
	  CPPUNIT_ASSERT(delayTicks[i] < permissibleDelayTick);
	}
			
      long permissibleReturnTick = 100000; // 0.1 [sec]
      const std::vector<long>& returnTicks = consumer->getReturnTicks();
      for (std::vector<long>::size_type i = 0; i < returnTicks.size(); i++)
	{
	  CPPUNIT_ASSERT(returnTicks[i] < permissibleReturnTick);
	}
    }
*/
		
  };
}; // namespace PublisherFlush

/*
 * Register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(PublisherFlush::PublisherFlushTests);

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
#endif // PublisherFlush_cpp
