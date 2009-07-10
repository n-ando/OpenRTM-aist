// -*- C++ -*-
/*!
 * @file   PublisherNewTests.cpp
 * @brief  PublisherNew test class
 * @date   $Date: 2008/01/23 09:19:31 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * $Id$
 *
 */

/*
 * $Log: PublisherNewTests.cpp,v $
 * Revision 1.2  2008/01/23 09:19:31  arafune
 * added some tests.
 *
 * Revision 1.1  2007/12/20 07:50:16  arafune
 * *** empty log message ***
 *
 * Revision 1.2  2007/01/12 14:54:39  n-ando
 * The constructor's signature was changed.
 * InPortConsumer base class is now abstruct class. It needs concrete class.
 *
 * Revision 1.1  2006/12/18 06:51:43  n-ando
 * The first commitment.
 *
 *
 */

#ifndef PublisherNew_cpp
#define PublisherNew_cpp

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>

#include <coil/Properties.h>
#include <rtm/InPortConsumer.h>
#include <rtm/PublisherNew.h>
#include <coil/Time.h>
#include <rtm/CORBA_SeqUtil.h>
#include <rtm/NVUtil.h>
#include <rtm/InPortCorbaCdrConsumer.h>
#include <rtm/CdrRingBuffer.h>

/*!
 * @class PublisherNewTests class
 * @brief PublisherNew test
 */
namespace PublisherNew
{
  /*!
   * 
   * 
   */
  class PublisherNewMock
    : public RTC::PublisherNew
  {
  public:
    PublisherNewMock(void)
    {
        ;
    }
    virtual ~PublisherNewMock(void)
    {
        ;
    }
  };
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
          m_test_mode = 0;
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
          if(m_test_mode == 0)
          {
              if (m_buffer->full())
              {
                   return RTC::PublisherNew::BUFFER_FULL;
              }

              RTC::BufferStatus::Enum ret = m_buffer->write(data);

              switch(ret)
              {
                   case RTC::BufferStatus::BUFFER_OK:
                       return RTC::PublisherNew::PORT_OK;
                       break;
                   case RTC::BufferStatus::BUFFER_ERROR:
                       return RTC::PublisherNew::PORT_ERROR;
                       break;
                   case RTC::BufferStatus::BUFFER_FULL:
                       return RTC::PublisherNew::BUFFER_FULL;
                       break;
                   case RTC::BufferStatus::BUFFER_EMPTY:
                       return RTC::PublisherNew::BUFFER_EMPTY;
                       break;
                   case RTC::BufferStatus::TIMEOUT:
                       return RTC::PublisherNew::BUFFER_TIMEOUT;
                       break;
                   default:
                       return RTC::PublisherNew::UNKNOWN_ERROR;
               }
               return RTC::PublisherNew::UNKNOWN_ERROR;
          }
          else if(m_test_mode == 1)
          {
               std::string str("test");
               throw str;
          }
          else
          {
          }
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
      /*!
       * 
       * 
       */
      int get_m_put_data_len(void)
      {
          int ic;
          ic = (int)m_buffer->readable();

          return ic;
      }

      /*!
       * 
       * 
       */
      void set_m_mode(int mode)
      {
          m_test_mode = mode;
      }
  private:
       RTC::CdrBufferBase* m_buffer;
       ::OpenRTM::CdrData  m_put_data;
       int m_test_mode;
  };
	
  class PublisherNewTests
    : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(PublisherNewTests);

    CPPUNIT_TEST(test_init);
    CPPUNIT_TEST(test_setConsumer);
    CPPUNIT_TEST(test_setBuffer);
    CPPUNIT_TEST(test_activate_deactivate_isActive);
    CPPUNIT_TEST(test_pushAll);
    CPPUNIT_TEST(test_pushAll_2);
    CPPUNIT_TEST(test_pushFifo);
    CPPUNIT_TEST(test_pushFifo_2);
    CPPUNIT_TEST(test_pushSkip);
    CPPUNIT_TEST(test_pushSkip_2);
    CPPUNIT_TEST(test_pushNew);
    CPPUNIT_TEST(test_write);

    CPPUNIT_TEST_SUITE_END();
		
  private:

  public:
    /*!
     * @brief Constructor
     */
    PublisherNewTests()
    {
    }
		
    /*!
     * @brief Destructor
     */
    ~PublisherNewTests()
    {
    }
		
    /*!
     * @brief Test initialization
     */
    virtual void setUp()
    {
//      coil::usleep(1000000);
    }
		
    /*!
     * @brief Test finalization
     */
    virtual void tearDown()
    { 
    }
		
    /*!
     * @brief init()メソッドのテスト
     * 
     */
    void test_init(void)
    {
        PublisherNewMock publisher;
        RTC::PublisherBase::ReturnCode retcode;
        coil::Properties prop;

        //Propertiesが空の状態でも正常に動作することを確認する
        retcode = publisher.init(prop);
        CPPUNIT_ASSERT_EQUAL(RTC::PublisherNew::PORT_OK, retcode);

        prop.setProperty("publisher.push_policy","new");
        prop.setProperty("thread_type","bar");
        prop.setProperty("measurement.exec_time","default");
        prop.setProperty("measurement.period_count","1");

        //thread_type が不正の場合 INVALID_ARGS を返すことを確認する。
        retcode = publisher.init(prop);
        CPPUNIT_ASSERT_EQUAL(RTC::PublisherNew::INVALID_ARGS, retcode);

        //以下のpropertiesの設定で動作することを確認する。
        prop.setProperty("publisher.push_policy","all");
        prop.setProperty("publisher.skip_count","0");
        prop.setProperty("thread_type","default");
        prop.setProperty("measurement.exec_time","enable");
        prop.setProperty("measurement.exec_count","0");
        prop.setProperty("measurement.period_time","enable");
        prop.setProperty("measurement.period_count","0");
        retcode = publisher.init(prop);
        CPPUNIT_ASSERT_EQUAL(RTC::PublisherNew::PORT_OK, retcode);

        prop.setProperty("publisher.push_policy","fifo");
        prop.setProperty("publisher.skip_count","1");
        prop.setProperty("thread_type","default");
        prop.setProperty("measurement.exec_time","disable");
        prop.setProperty("measurement.exec_count","1");
        prop.setProperty("measurement.period_time","disable");
        prop.setProperty("measurement.period_count","1");
        retcode = publisher.init(prop);
        CPPUNIT_ASSERT_EQUAL(RTC::PublisherNew::PORT_OK, retcode);

        prop.setProperty("publisher.push_policy","skip");
        prop.setProperty("publisher.skip_count","-1");
        prop.setProperty("thread_type","default");
        prop.setProperty("measurement.exec_time","bar");
        prop.setProperty("measurement.exec_count","-1");
        prop.setProperty("measurement.period_time","bar");
        prop.setProperty("measurement.period_count","-1");
        retcode = publisher.init(prop);
        CPPUNIT_ASSERT_EQUAL(RTC::PublisherNew::PORT_OK, retcode);

        prop.setProperty("publisher.push_policy","new");
        prop.setProperty("publisher.skip_count","foo");
        prop.setProperty("thread_type","default");
        prop.setProperty("measurement.exec_time","enable");
        prop.setProperty("measurement.exec_count","foo");
        prop.setProperty("measurement.period_time","enable");
        prop.setProperty("measurement.period_count","foo");
        retcode = publisher.init(prop);
        CPPUNIT_ASSERT_EQUAL(RTC::PublisherNew::PORT_OK, retcode);

        prop.setProperty("publisher.push_policy","bar");
        prop.setProperty("publisher.skip_count","0");
        prop.setProperty("thread_type","default");
        prop.setProperty("measurement.exec_time","enable");
        prop.setProperty("measurement.exec_count","0");
        prop.setProperty("measurement.period_time","enable");
        prop.setProperty("measurement.period_count","0");
        retcode = publisher.init(prop);
        CPPUNIT_ASSERT_EQUAL(RTC::PublisherNew::PORT_OK, retcode);

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
        RTC::PublisherNew publisher;

        //NULLを渡した場合INVALID_ARGSとなることを確認する。
        CPPUNIT_ASSERT_EQUAL(RTC::PublisherNew::INVALID_ARGS, 
                             publisher.setConsumer(NULL));

        //
        CPPUNIT_ASSERT_EQUAL(RTC::PublisherNew::PORT_OK, 
                             publisher.setConsumer(consumer0));

        //
        CPPUNIT_ASSERT_EQUAL(RTC::PublisherNew::PORT_OK, 
                             publisher.setConsumer(consumer1));

        delete consumer0;
        delete consumer1;
    }
    /*!
     * @brief setBuffer()メソッドのテスト
     * 
     */
    void test_setBuffer(void)
    {
        RTC::CdrBufferBase* buffer0 = new RTC::CdrRingBuffer();
        RTC::CdrBufferBase* buffer1 = new RTC::CdrRingBuffer();
        RTC::PublisherNew publisher;

        //NULLを渡した場合INVALID_ARGSとなることを確認する。
        CPPUNIT_ASSERT_EQUAL(RTC::PublisherNew::INVALID_ARGS, 
                             publisher.setBuffer(NULL));

        //
        CPPUNIT_ASSERT_EQUAL(RTC::PublisherNew::PORT_OK, 
                             publisher.setBuffer(buffer0));

        //
        CPPUNIT_ASSERT_EQUAL(RTC::PublisherNew::PORT_OK, 
                             publisher.setBuffer(buffer1));

        delete buffer0;
        delete buffer1;
    }
    /*!
     * @brief activate(),deactivate(),isActiveメソッドのテスト
     * 
     */
    void test_activate_deactivate_isActive(void)
    {
        RTC::InPortCorbaCdrConsumer *consumer 
                                    = new RTC::InPortCorbaCdrConsumer();
        RTC::PublisherNew publisher;
        publisher.setConsumer(consumer);

        CPPUNIT_ASSERT_EQUAL(false, 
                             publisher.isActive());
        
        CPPUNIT_ASSERT_EQUAL(RTC::PublisherNew::PORT_OK, 
                             publisher.activate());

        CPPUNIT_ASSERT_EQUAL(true, 
                             publisher.isActive());
        
        //既に activate されている場合は 
        //activateすると
        //PORT_OK を返すことを確認する。
        CPPUNIT_ASSERT_EQUAL(RTC::PublisherNew::PORT_OK, 
                             publisher.activate());

        CPPUNIT_ASSERT_EQUAL(true, 
                             publisher.isActive());
        
        CPPUNIT_ASSERT_EQUAL(RTC::PublisherNew::PORT_OK, 
                             publisher.deactivate());

        CPPUNIT_ASSERT_EQUAL(false, 
                             publisher.isActive());
        
        //activate されていない状態で、
        //deactivateすると
        //PORT_OK を返すことを確認する。
        CPPUNIT_ASSERT_EQUAL(RTC::PublisherNew::PORT_OK, 
                             publisher.deactivate());
        
        CPPUNIT_ASSERT_EQUAL(false, 
                             publisher.isActive());
        
        delete consumer;
    }
    /*!
     * @brief write(), pushAll() メソッドのテスト
     *
     * -provider 側のバッファ full 状態でもデータ抜けががないことを確認する。
     */
    void test_pushAll(void)
    {
        InPortCorbaCdrConsumerMock *consumer 
                                    = new InPortCorbaCdrConsumerMock();
        RTC::CdrBufferBase* buffer = new RTC::CdrRingBuffer();
        PublisherNewMock publisher;

        coil::Properties prop;
        prop.setProperty("publisher.push_policy","all");
        prop.setProperty("publisher.skip_count","0");
        prop.setProperty("thread_type","default");
        prop.setProperty("measurement.exec_time","enable");
        prop.setProperty("measurement.exec_count","0");
        prop.setProperty("measurement.period_time","enable");
        prop.setProperty("measurement.period_count","0");
        publisher.init(prop);

        publisher.setConsumer(consumer);
        publisher.setBuffer(buffer);
        publisher.activate();

        for(int icc(0);icc<8;++icc)
        {
            cdrMemoryStream cdr;
            icc >>= cdr;

            CPPUNIT_ASSERT_EQUAL(RTC::PublisherNew::PORT_OK,
                                 publisher.write(cdr,0,0));

        }

        //provider 側のバッファ full の状態でコール(full)
        {
        cdrMemoryStream cdr;
        8 >>= cdr;
        CPPUNIT_ASSERT_EQUAL(RTC::PublisherNew::PORT_OK,
                                 publisher.write(cdr,0,0));
        coil::usleep(10000);
        }
        {
        cdrMemoryStream cdr;
        9 >>= cdr;
        CPPUNIT_ASSERT_EQUAL(RTC::PublisherNew::BUFFER_FULL,
                                 publisher.write(cdr,0,0));
        coil::usleep(10000);
        }

        //provider 側のバッファから 4 件取得
        //(full ではない状態にする )
        for(int icc(0);icc<4;++icc)
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
            CPPUNIT_ASSERT_EQUAL((long)icc,lval);
        }

        //provider 側のバッファ full ではない状態でコール
        {
        cdrMemoryStream cdr;
        10 >>= cdr;
        CPPUNIT_ASSERT_EQUAL(RTC::PublisherNew::BUFFER_FULL,
                                 publisher.write(cdr,0,0));
        coil::usleep(10000);
        }
        {
        cdrMemoryStream cdr;
        11 >>= cdr;
        CPPUNIT_ASSERT_EQUAL(RTC::PublisherNew::PORT_OK,
                                 publisher.write(cdr,0,0));
        coil::usleep(10000);
        }

        //データ抜けががないことを確認する。
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
            CPPUNIT_ASSERT_EQUAL((long)icc+4,lval);
        }
        publisher.deactivate();
        
        delete buffer;
        delete consumer;
        
    }
    /*!
     * @brief write(), pushAll() メソッドのテスト
     *
     * -
     */
    void test_pushAll_2(void)
    {
        InPortCorbaCdrConsumerMock *consumer 
                                    = new InPortCorbaCdrConsumerMock();
        RTC::CdrBufferBase* buffer = new RTC::CdrRingBuffer();
        PublisherNewMock publisher;

        coil::Properties prop;
        prop.setProperty("publisher.push_policy","all");
        prop.setProperty("publisher.skip_count","0");
        prop.setProperty("thread_type","default");
        prop.setProperty("measurement.exec_time","enable");
        prop.setProperty("measurement.exec_count","0");
        prop.setProperty("measurement.period_time","enable");
        prop.setProperty("measurement.period_count","0");
        publisher.init(prop);

        publisher.setConsumer(consumer);
        publisher.setBuffer(buffer);
        publisher.activate();

        for(int icc(0);icc<16;++icc)
        {
            cdrMemoryStream cdr;
            icc >>= cdr;

            RTC::PublisherBase::ReturnCode ret;
            ret = publisher.write(cdr,0,0);
            if(icc<9)
            {
                CPPUNIT_ASSERT_EQUAL(RTC::PublisherNew::PORT_OK,
                                     ret);
            }
            else
            {
                CPPUNIT_ASSERT_EQUAL(RTC::PublisherNew::BUFFER_FULL,
                                     ret);
            }
            coil::usleep(10000);

        }

        //consumer と provider 両方の buffer が full 状態のため、
        // この weite データは抜ける。
        {
        cdrMemoryStream cdr;
        16 >>= cdr;
        CPPUNIT_ASSERT_EQUAL(RTC::PublisherNew::BUFFER_FULL,
                                 publisher.write(cdr,0,0));
        coil::usleep(10000);
        }

        //データを確認する。
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
            CPPUNIT_ASSERT_EQUAL((long)icc,lval);
        }

        //consumer の buffer が full 状態のため、
        // この weite データは抜ける。
        {
        cdrMemoryStream cdr;
        17 >>= cdr;
        CPPUNIT_ASSERT_EQUAL(RTC::PublisherNew::BUFFER_FULL,
                                 publisher.write(cdr,0,0));
        coil::usleep(10000);
        }
        //データを確認する。
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
            CPPUNIT_ASSERT_EQUAL((long)icc+8,lval);
        }
        {
        cdrMemoryStream cdr;
        18 >>= cdr;
        CPPUNIT_ASSERT_EQUAL(RTC::PublisherNew::PORT_OK,
                                 publisher.write(cdr,0,0));
        coil::usleep(10000);
        }
        //データを確認する。
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
        CPPUNIT_ASSERT_EQUAL((long)18,lval);
        }

        coil::usleep(10000);
        publisher.deactivate();
        
        delete buffer;
        delete consumer;
        
    }
    /*!
     * @brief pushFifo()メソッドのテスト
     * 
     */
    void test_pushFifo(void)
    {
        InPortCorbaCdrConsumerMock *consumer 
                                    = new InPortCorbaCdrConsumerMock();
        RTC::CdrBufferBase* buffer = new RTC::CdrRingBuffer();
        PublisherNewMock publisher;

        coil::Properties prop;
        prop.setProperty("publisher.push_policy","fifo");
        prop.setProperty("publisher.skip_count","0");
        prop.setProperty("thread_type","default");
        prop.setProperty("measurement.exec_time","enable");
        prop.setProperty("measurement.exec_count","0");
        prop.setProperty("measurement.period_time","enable");
        prop.setProperty("measurement.period_count","0");
        publisher.init(prop);

        publisher.setConsumer(consumer);
        publisher.setBuffer(buffer);
        publisher.activate();

        for(int icc(0);icc<8;++icc)
        {
            cdrMemoryStream cdr;
            icc >>= cdr;

            CPPUNIT_ASSERT_EQUAL(RTC::PublisherNew::PORT_OK,
                                 publisher.write(cdr,0,0));

        }

        coil::usleep(100000);
        //provider 側のバッファ full の状態でコール(full)
        {
        cdrMemoryStream cdr;
        8 >>= cdr;
        CPPUNIT_ASSERT_EQUAL(RTC::PublisherNew::PORT_OK,
                                 publisher.write(cdr,0,0));
        coil::usleep(50000);
        }
        {
        cdrMemoryStream cdr;
        9 >>= cdr;
        CPPUNIT_ASSERT_EQUAL(RTC::PublisherNew::BUFFER_FULL,
                                 publisher.write(cdr,0,0));
        coil::usleep(10000);
        }

        //provider 側のバッファから 4 件取得
        //(full ではない状態にする )
        for(int icc(0);icc<4;++icc)
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
            CPPUNIT_ASSERT_EQUAL((long)icc,lval);
        }

        //provider 側のバッファ full ではない状態でコール
        {
        cdrMemoryStream cdr;
        10 >>= cdr;
        CPPUNIT_ASSERT_EQUAL(RTC::PublisherNew::BUFFER_FULL,
                                 publisher.write(cdr,0,0));
        coil::usleep(30000);
        }
        {
        cdrMemoryStream cdr;
        11 >>= cdr;
        CPPUNIT_ASSERT_EQUAL(RTC::PublisherNew::PORT_OK,
                                 publisher.write(cdr,0,0));
        coil::usleep(10000);
        }
        {
        cdrMemoryStream cdr;
        12 >>= cdr;
        CPPUNIT_ASSERT_EQUAL(RTC::PublisherNew::PORT_OK,
                                 publisher.write(cdr,0,0));
        coil::usleep(10000);
        }
        {
        cdrMemoryStream cdr;
        13 >>= cdr;
        CPPUNIT_ASSERT_EQUAL(RTC::PublisherNew::PORT_OK,
                                 publisher.write(cdr,0,0));
        coil::usleep(10000);
        }

        //データ抜けががないことを確認する。
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
            CPPUNIT_ASSERT_EQUAL((long)icc+4,lval);
        }

        //この時点で consumer 側のバッファにデータが 2 件格納されている状態

        coil::usleep(10000);
        publisher.deactivate();
        delete buffer;
        delete consumer;
        
    }
    /*!
     * @brief write(), pushFifo() メソッドのテスト
     *
     * -
     */
    void test_pushFifo_2(void)
    {
        InPortCorbaCdrConsumerMock *consumer 
                                    = new InPortCorbaCdrConsumerMock();
        RTC::CdrBufferBase* buffer = new RTC::CdrRingBuffer();
        PublisherNewMock publisher;

        coil::Properties prop;
        prop.setProperty("publisher.push_policy","fifo");
        prop.setProperty("publisher.skip_count","0");
        prop.setProperty("thread_type","default");
        prop.setProperty("measurement.exec_time","enable");
        prop.setProperty("measurement.exec_count","0");
        prop.setProperty("measurement.period_time","enable");
        prop.setProperty("measurement.period_count","0");
        publisher.init(prop);

        publisher.setConsumer(consumer);
        publisher.setBuffer(buffer);
        publisher.activate();

        //consumer と provider 両方の buffer を full 状態にする
        for(int icc(0);icc<16;++icc)
        {
            cdrMemoryStream cdr;
            icc >>= cdr;

            RTC::PublisherBase::ReturnCode ret;
            ret = publisher.write(cdr,0,0);
            if(icc<9)
            {
                CPPUNIT_ASSERT_EQUAL(RTC::PublisherNew::PORT_OK,
                                     ret);
            }
            else
            {
                CPPUNIT_ASSERT_EQUAL(RTC::PublisherNew::BUFFER_FULL,
                                     ret);
            }
            coil::usleep(10000);

        }

        //consumer と provider 両方の buffer が full 状態のため、
        // この weite データは抜ける。
        {
        cdrMemoryStream cdr;
        16 >>= cdr;
        CPPUNIT_ASSERT_EQUAL(RTC::PublisherNew::BUFFER_FULL,
                                 publisher.write(cdr,0,0));
        coil::usleep(10000);
        }

        //データを確認する。
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
            CPPUNIT_ASSERT_EQUAL((long)icc,lval);
        }

        //consumer の buffer が full 状態のため、
        // この weite データは抜ける。
        {
        cdrMemoryStream cdr;
        17 >>= cdr;
        CPPUNIT_ASSERT_EQUAL(RTC::PublisherNew::BUFFER_FULL,
                                 publisher.write(cdr,0,0));
        coil::usleep(10000);
        }
        // この weite データは転送される。
        for(int icc(0);icc<7;++icc)
        {
            cdrMemoryStream cdr;
            (18+icc) >>= cdr;
            CPPUNIT_ASSERT_EQUAL(RTC::PublisherNew::PORT_OK,
                                 publisher.write(cdr,0,0));
            coil::usleep(10000);
        }
        //データを確認する。
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
            CPPUNIT_ASSERT_EQUAL((long)icc+8,lval);
        }
        {
        cdrMemoryStream cdr;
        26 >>= cdr;
        CPPUNIT_ASSERT_EQUAL(RTC::PublisherNew::PORT_OK,
                                 publisher.write(cdr,0,0));
        coil::usleep(10000);
        }
        //データを確認する。
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
        CPPUNIT_ASSERT_EQUAL((long)18,lval);
        }


        coil::usleep(10000);
        publisher.deactivate();
        
        delete buffer;
        delete consumer;
        
    }
    /*!
     * @brief pushSklip()メソッドのテスト
     * 
     */
    void test_pushSkip(void)
    {
        InPortCorbaCdrConsumerMock *consumer 
                                    = new InPortCorbaCdrConsumerMock();
        RTC::CdrBufferBase* buffer = new RTC::CdrRingBuffer();
        PublisherNewMock publisher;

        coil::Properties prop;
        prop.setProperty("publisher.push_policy","skip");
        prop.setProperty("publisher.skip_count","1");
        prop.setProperty("thread_type","default");
        prop.setProperty("measurement.exec_time","enable");
        prop.setProperty("measurement.exec_count","0");
        prop.setProperty("measurement.period_time","enable");
        prop.setProperty("measurement.period_count","0");
        publisher.init(prop);

        publisher.setConsumer(consumer);
        publisher.setBuffer(buffer);
        publisher.activate();

        for(int icc(0);icc<16;++icc)
        {
            cdrMemoryStream cdr;
            icc >>= cdr;

            CPPUNIT_ASSERT_EQUAL(RTC::PublisherNew::PORT_OK,
                                 publisher.write(cdr,0,0));

        }

        //provider 側のバッファ full の状態でコール(full)
        {
        cdrMemoryStream cdr;
        8 >>= cdr;
        CPPUNIT_ASSERT_EQUAL(RTC::PublisherNew::PORT_OK,
                                 publisher.write(cdr,0,0));
        coil::usleep(10000);
        }
        {
        cdrMemoryStream cdr;
        9 >>= cdr;
        CPPUNIT_ASSERT_EQUAL(RTC::PublisherNew::PORT_OK,
                                 publisher.write(cdr,0,0));
        coil::usleep(10000);
        }

        //provider 側のバッファから 4 件取得
        //(full ではない状態にする )
        for(int icc(0);icc<4;++icc)
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
            CPPUNIT_ASSERT_EQUAL((long)icc*2+1,lval);
        }

        //provider 側のバッファ full ではない状態でコール
        {
        cdrMemoryStream cdr;
        10 >>= cdr;
        CPPUNIT_ASSERT_EQUAL(RTC::PublisherNew::BUFFER_FULL,
                                 publisher.write(cdr,0,0));
        coil::usleep(10000);
        }
        {
        cdrMemoryStream cdr;
        11 >>= cdr;
        CPPUNIT_ASSERT_EQUAL(RTC::PublisherNew::PORT_OK,
                                 publisher.write(cdr,0,0));
        coil::usleep(10000);
        }

        //データ抜けががないことを確認する。
        for(int icc(0);icc<2;++icc)
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
            CPPUNIT_ASSERT_EQUAL((long)icc*2+9,lval);
        }
       
        coil::usleep(100000);
        publisher.deactivate();
        delete buffer;
        delete consumer;
    }
    /*!
     * @brief write(), pushSkip() メソッドのテスト
     *
     * -
     */
    void test_pushSkip_2(void)
    {
        InPortCorbaCdrConsumerMock *consumer 
                                    = new InPortCorbaCdrConsumerMock();
        RTC::CdrBufferBase* buffer = new RTC::CdrRingBuffer();
        PublisherNewMock publisher;

        coil::Properties prop;
        prop.setProperty("publisher.push_policy","skip");
        prop.setProperty("publisher.skip_count","1");
        prop.setProperty("thread_type","default");
        prop.setProperty("measurement.exec_time","enable");
        prop.setProperty("measurement.exec_count","0");
        prop.setProperty("measurement.period_time","enable");
        prop.setProperty("measurement.period_count","0");
        publisher.init(prop);

        publisher.setConsumer(consumer);
        publisher.setBuffer(buffer);
        publisher.activate();

        //consumer と provider 両方の buffer を full 状態にする
        for(int icc(0);icc<24;++icc)
        {
            cdrMemoryStream cdr;
            icc >>= cdr;

            RTC::PublisherBase::ReturnCode ret;
            ret = publisher.write(cdr,0,0);
            if(icc<18)
            {
                CPPUNIT_ASSERT_EQUAL(RTC::PublisherNew::PORT_OK,
                                     ret);
            }
            else
            {
                CPPUNIT_ASSERT_EQUAL(RTC::PublisherNew::BUFFER_FULL,
                                     ret);
            }
            coil::usleep(10000);

        }

        //consumer と provider 両方の buffer が full 状態のため、
        // この weite データは抜ける。
        {
        cdrMemoryStream cdr;
        24 >>= cdr;
        CPPUNIT_ASSERT_EQUAL(RTC::PublisherNew::BUFFER_FULL,
                                 publisher.write(cdr,0,0));
        coil::usleep(10000);
        }

        //データを確認する。
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
            CPPUNIT_ASSERT_EQUAL((long)icc*2+1,lval);
        }

        //consumer の buffer が full 状態のため、
        // この weite データは抜ける。
        {
        cdrMemoryStream cdr;
        25 >>= cdr;
        CPPUNIT_ASSERT_EQUAL(RTC::PublisherNew::BUFFER_FULL,
                                 publisher.write(cdr,0,0));
        coil::usleep(10000);
        }
        //データを確認する。
        int len =consumer->get_m_put_data_len();
        CPPUNIT_ASSERT_EQUAL(4,len);
        for(int icc(0);icc<len;++icc)
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
            CPPUNIT_ASSERT_EQUAL((long)icc*2+17,lval);
        }
        {
        cdrMemoryStream cdr;
        26 >>= cdr;
        CPPUNIT_ASSERT_EQUAL(RTC::PublisherNew::PORT_OK,
                                 publisher.write(cdr,0,0));
        coil::usleep(10000);
        }
        {
        cdrMemoryStream cdr;
        27 >>= cdr;
        CPPUNIT_ASSERT_EQUAL(RTC::PublisherNew::PORT_OK,
                                 publisher.write(cdr,0,0));
        coil::usleep(10000);
        }
        //データを確認する。
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
        CPPUNIT_ASSERT_EQUAL((long)27,lval);
        }

        coil::usleep(10000);
        publisher.deactivate();
        
        delete buffer;
        delete consumer;
        
    }
    /*!
     * @brief pushNew()メソッドのテスト
     * 
     */
    void test_pushNew(void)
    {
        InPortCorbaCdrConsumerMock *consumer 
                                    = new InPortCorbaCdrConsumerMock();
        RTC::CdrBufferBase* buffer = new RTC::CdrRingBuffer();
        PublisherNewMock publisher;

        coil::Properties prop;
        prop.setProperty("publisher.push_policy","new");
        prop.setProperty("publisher.skip_count","0");
        prop.setProperty("thread_type","default");
        prop.setProperty("measurement.exec_time","enable");
        prop.setProperty("measurement.exec_count","0");
        prop.setProperty("measurement.period_time","enable");
        prop.setProperty("measurement.period_count","0");
        publisher.init(prop);

        publisher.setConsumer(consumer);
        publisher.setBuffer(buffer);
        publisher.activate();

        //8件のデータは転送されない
        ////最新データの7は転送される。
        for(int icc(0);icc<8;++icc)
        {
            cdrMemoryStream cdr;
            icc >>= cdr;

            CPPUNIT_ASSERT_EQUAL(RTC::PublisherNew::PORT_OK,
                                 publisher.write(cdr,0,0));

        }


        //provider 側のバッファから取得
        //
        int len = consumer->get_m_put_data_len() -1;
        for(int icc(0);icc<len;++icc)
        {
            cdrMemoryStream data;
            data = consumer->get_m_put_data();
            CORBA::ULong inlen = data.bufSize();
            CPPUNIT_ASSERT_EQUAL(4,(int)inlen);
        }
        //最新データが転送されていることを確認する。
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
        CPPUNIT_ASSERT_EQUAL((long)7,lval);
        }

        coil::usleep(10000);
        publisher.deactivate();
        delete buffer;
        delete consumer;
    }
    /*!
     * @brief write()メソッドのテスト
     * 
     * - 手順を無視して write した場合
     */
    void test_write(void)
    {
        InPortCorbaCdrConsumerMock *consumer 
                                    = new InPortCorbaCdrConsumerMock();
        RTC::CdrBufferBase* buffer = new RTC::CdrRingBuffer();
        PublisherNewMock publisher;

        coil::Properties prop;
        prop.setProperty("publisher.push_policy","all");
        prop.setProperty("publisher.skip_count","0");
        prop.setProperty("thread_type","default");
        prop.setProperty("measurement.exec_time","enable");
        prop.setProperty("measurement.exec_count","0");
        prop.setProperty("measurement.period_time","enable");
        prop.setProperty("measurement.period_count","0");
        publisher.init(prop);

        {
        cdrMemoryStream cdr;
        123 >>= cdr;
        CPPUNIT_ASSERT_EQUAL(RTC::PublisherNew::PRECONDITION_NOT_MET,
                                 publisher.write(cdr,0,0));
        coil::usleep(10000);
        }
        publisher.setBuffer(buffer);
        {
        cdrMemoryStream cdr;
        123 >>= cdr;
        CPPUNIT_ASSERT_EQUAL(RTC::PublisherNew::PRECONDITION_NOT_MET,
                                 publisher.write(cdr,0,0));
        coil::usleep(10000);
        }
        publisher.setConsumer(consumer);
        {
        cdrMemoryStream cdr;
        123 >>= cdr;
        CPPUNIT_ASSERT_EQUAL(RTC::PublisherNew::PRECONDITION_NOT_MET,
                                 publisher.write(cdr,0,0));
        coil::usleep(10000);
        }
        publisher.activate();

        {
        cdrMemoryStream cdr;
        123 >>= cdr;
        CPPUNIT_ASSERT_EQUAL(RTC::PublisherNew::PORT_OK,
                                 publisher.write(cdr,0,0));
        coil::usleep(10000);
        }

        consumer->set_m_mode(1);
        {
        cdrMemoryStream cdr;
        123 >>= cdr;
        CPPUNIT_ASSERT_EQUAL(RTC::PublisherNew::PORT_OK,
                                 publisher.write(cdr,0,0));
        coil::usleep(10000);
        }
        {
        cdrMemoryStream cdr;
        123 >>= cdr;
        CPPUNIT_ASSERT_EQUAL(RTC::PublisherNew::CONNECTION_LOST,
                                 publisher.write(cdr,0,0));
        coil::usleep(10000);
        }

        delete consumer;
        delete buffer;

    }
    /*!
     * @brief update()メソッドのテスト
     * 
     * - 「Publisherのupdate()メソッド呼出間隔」>「Consumerのpush()メソッド処理時間」の場合に、update()呼出からpush()呼出までの時間間隔が、所定時間内に収まっているか？
     * 
     * @attention リアルタイム性が保証されているわけでもなく、仕様上も呼出までの時間を明記しているわけではないので、ここでの所定時間はテスト作成者の主観によるものに過ぎない。
     */
/*
    void test_update_large_interval()
    {
      long sleepTick = 100000; // 0.1[sec]
      long intervalTick = sleepTick * 10;
			
      MockConsumer* consumer = new MockConsumer(sleepTick);
      coil::Properties prop;
      RTC::PublisherNew publisher(consumer, prop);
			
      for (int i = 0; i < 10; i++)
	{
	  consumer->setDelayStartTime();
	  publisher.update();
	  coil::usleep(intervalTick);
	}
			
      // Consumer呼出が完了するであろうタイミングまで待つ
      coil::usleep(5000000); // 5 [sec]
			
      // update()呼出からpush()呼出までの時間間隔が、所定時間内に収まっているか？
      // （リアルタイム性が保証されているわけでもなく、仕様上も呼出までの時間を明記しているわけではないので、
      // ここでの所定時間はテスト作成者の主観によるものに過ぎない。）
      long permissibleDelay = sleepTick + 100000;
      const std::vector<long>& delayTicks = consumer->getDelayTicks();
      for (std::vector<long>::size_type i = 0; i < delayTicks.size(); i++)
	{
	  //std::cout << "delay tick = " << delayTicks[i] << std::endl;
	  CPPUNIT_ASSERT(delayTicks[i] < permissibleDelay);
	}
      publisher.release();
    }
*/		
    /*!
     * @brief update()メソッドのテスト
     * 
     * - 「Publisherのupdate()メソッド呼出間隔」<「Consumerのpush()メソッド処理時間」の場合に、update()呼出が溜ってしまうことなく、update()呼出からpush()呼出までの時間間隔が、所定時間内に収まっているか？
     * 
     * @attention リアルタイム性が保証されているわけでもなく、仕様上も呼出までの時間を明記しているわけではないので、ここでの所定時間はテスト作成者の主観によるものに過ぎない。
     */
/*
    void test_update_small_interval()
    {
      long sleepTick = 100000; // 0.1[sec]
      long intervalTick = sleepTick / 10;
			
      MockConsumer* consumer = new MockConsumer(sleepTick);
      coil::Properties prop;
      RTC::PublisherNew publisher(consumer, prop);
			
      for (int i = 0; i < 1000; i++)
	{
	  consumer->setDelayStartTime();
	  publisher.update();
	  coil::usleep(intervalTick);
	}
			
      // Consumer呼出が完了するであろうタイミングまで待つ
      coil::usleep(5000000); // 5 [sec]
			
      // update()呼出からpush()呼出までの時間間隔が、所定時間内に収まっているか？
      // （リアルタイム性が保証されているわけでもなく、仕様上も呼出までの時間を明記しているわけではないので、
      // ここでの所定時間はテスト作成者の主観によるものに過ぎない。）
      long permissibleDelay = sleepTick + 100000;
      const std::vector<long>& delayTicks = consumer->getDelayTicks();
      for (std::vector<long>::size_type i = 0; i < delayTicks.size(); i++)
	{
	  //std::cout << "delay tick = " << delayTicks[i] << std::endl;
	  CPPUNIT_ASSERT(delayTicks[i] < permissibleDelay);
	}
      publisher.release();
    }
*/
		
    /*!
     * @brief release()メソッドのテスト
     * 
     * - release()メソッド呼出によりPublisherの動作を確実に停止できるか？
     */
/*
    void test_release()
    {
      MockConsumer* consumer = new MockConsumer(1000000); // 1 [sec]
      coil::Properties prop;
      RTC::PublisherNew publisher(consumer, prop);
			
      // update()を呼出して、Consumerを呼び出させる
      publisher.update();
      coil::usleep(3000000); // Consumerを呼出す時間を与える
      publisher.release();
			
      CPPUNIT_ASSERT_EQUAL(1, consumer->getCount());
			
      // 再度update()を呼出し、Consumerを呼出しうる時間を与える。
      // （実際には、前段のrelease()によりPublisherが停止済みであり、
      // update()呼出は何ら影響を与えないことを予期している。）
      publisher.update();
      coil::usleep(3000000);

      // Consumer呼出回数が変わっていないこと、つまりPublisherの動作が停止していることを確認する
      CPPUNIT_ASSERT_EQUAL(1, consumer->getCount());
    }
*/
		
  };
}; // namespace PublisherNew

/*
 * Register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(PublisherNew::PublisherNewTests);

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
#endif // PublisherNew_cpp
