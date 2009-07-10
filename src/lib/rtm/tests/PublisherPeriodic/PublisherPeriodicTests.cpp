// -*- C++ -*-
/*!
 * @file   PublisherPeriodicTests.cpp
 * @brief  PublisherPeriodic test class
 * @date   $Date: 2008/01/28 13:52:19 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * $Id$
 *
 */

/*
 * $Log: PublisherPeriodicTests.cpp,v $
 * Revision 1.2  2008/01/28 13:52:19  arafune
 * Some tests were added.
 *
 * Revision 1.1  2007/12/20 07:50:17  arafune
 * *** empty log message ***
 *
 * Revision 1.2  2007/01/12 14:54:45  n-ando
 * The constructor's signature was changed.
 * InPortConsumer base class is now abstruct class. It needs concrete class.
 *
 * Revision 1.1  2006/12/18 06:51:55  n-ando
 * The first commitment.
 *
 *
 */

#ifndef PublisherPeriodic_cpp
#define PublisherPeriodic_cpp

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>

#include <iostream>
#include <coil/Properties.h>
#include <coil/Time.h>
#include <rtm/InPortConsumer.h>
#include <rtm/InPortCorbaCdrConsumer.h>
#include <rtm/PublisherPeriodic.h>
#include <rtm/CdrRingBuffer.h>
#include <rtm/idl/ManagerSkel.h>


/*!
 * @class PublisherPeriodicTests class
 * @brief PublisherPeriodic test
 */
namespace PublisherPeriodic
{
  /*!
   * 
   * 
   */
  class PublisherPeriodicMock
    : public RTC::PublisherPeriodic
  {
  public:
    PublisherPeriodicMock(void)
    {
        ;
    }
    virtual ~PublisherPeriodicMock(void)
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
                   return RTC::PublisherPeriodic::BUFFER_FULL;
              }

              RTC::BufferStatus::Enum ret = m_buffer->write(data);

              switch(ret)
              {
                   case RTC::BufferStatus::BUFFER_OK:
                       return RTC::PublisherPeriodic::PORT_OK;
                       break;
                   case RTC::BufferStatus::BUFFER_ERROR:
                       return RTC::PublisherPeriodic::PORT_ERROR;
                       break;
                   case RTC::BufferStatus::BUFFER_FULL:
                       return RTC::PublisherPeriodic::BUFFER_FULL;
                       break;
                   case RTC::BufferStatus::BUFFER_EMPTY:
                       return RTC::PublisherPeriodic::BUFFER_EMPTY;
                       break;
                   case RTC::BufferStatus::TIMEOUT:
                       return RTC::PublisherPeriodic::BUFFER_TIMEOUT;
                       break;
                   default:
                       return RTC::PublisherPeriodic::UNKNOWN_ERROR;
               }
               return RTC::PublisherPeriodic::UNKNOWN_ERROR;
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
  class MockConsumer : public RTC::InPortConsumer
  {
  public:
	
    MockConsumer() : RTC::InPortConsumer()
    {
      clearLastTime();
    }
		
    virtual ~MockConsumer() {}
		
    virtual void push()
    {
      timeval now;
      coil::gettimeofday(&now, NULL);
			
      if (! isLastTimeCleared())
	{
	  long interval =
	    (now.tv_sec - _lastTime.tv_sec) * 1000000
	    + (now.tv_usec - _lastTime.tv_usec);
				
	  _intervalTicks.push_back(interval);
	}
			
      _lastTime = now;
    }
		
    virtual RTC::InPortConsumer* clone() const
    {
      MockConsumer* clone = new MockConsumer();
      copy(_intervalTicks.begin(), _intervalTicks.end(), clone->_intervalTicks.begin());
      clone->_lastTime = _lastTime;
			
      return clone;
    }

    virtual bool subscribeInterface(const SDOPackage::NVList&)
    {
      return true;
    }
		
    virtual void unsubscribeInterface(const SDOPackage::NVList&)
    {
      return;
    }
	
    virtual const std::vector<long>& getIntervalTicks() const
    {
      return _intervalTicks;
    }
		
    virtual int getCount() const
    {
      return static_cast<int>(_intervalTicks.size());
    }
		
    virtual void init(coil::Properties& prop)
    {
    }
    virtual InPortConsumer::ReturnCode put(const cdrMemoryStream& data)
    {
        return (InPortConsumer::ReturnCode)0 ;
    }
    virtual void publishInterfaceProfile(SDOPackage::NVList& properties)
    {
    }
  private:
	
    std::vector<long> _intervalTicks;
    timeval _lastTime;
		
  private:
	
    void clearLastTime()
    {
      _lastTime.tv_sec = 0;
      _lastTime.tv_usec = 0;
    }
		
    bool isLastTimeCleared()
    {
      return (_lastTime.tv_sec == 0) && (_lastTime.tv_usec == 0);
    }
  };
	
  class CounterConsumer : public RTC::InPortConsumer
  {
  public:
	
    CounterConsumer(CounterConsumer* component = NULL)
      : RTC::InPortConsumer(), _count(0), _component(component)	{}
		
    virtual ~CounterConsumer() {}
		
    virtual void push()
    {
      _count++;
			
      if (_component != NULL)
	{
	  _component->push();
	}
    }
		
    virtual RTC::InPortConsumer* clone() const
    {
      CounterConsumer* clone = new CounterConsumer();
      clone->_count = _count;
      clone->_component = _component;
      return clone;
    }

    virtual bool subscribeInterface(const SDOPackage::NVList&)
    {
      return true;
    }
		
    virtual void unsubscribeInterface(const SDOPackage::NVList&)
    {
      return;
    }

    virtual int getCount() const
    {
      return _count;
    }
	
    virtual void init(coil::Properties& prop)
    {
    }
    virtual InPortConsumer::ReturnCode put(const cdrMemoryStream& data)
    {
        return (InPortConsumer::ReturnCode)0 ;
    }
    virtual void publishInterfaceProfile(SDOPackage::NVList& properties)
    {
    }
  private:
	
    int _count;
    CounterConsumer* _component;
  };

  class PublisherPeriodicTests
    : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(PublisherPeriodicTests);
		
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
		
  public:
	
    /*!
     * @brief Constructor
     */
    PublisherPeriodicTests()
    {
    }
		
    /*!
     * @brief Destructor
     */
    ~PublisherPeriodicTests()
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

        PublisherPeriodicMock publisher;
        RTC::PublisherBase::ReturnCode retcode;
        coil::Properties prop;

        //Propertiesが空の状態でも正常に動作することを確認する
        retcode = publisher.init(prop);
        CPPUNIT_ASSERT_EQUAL(RTC::PublisherPeriodic::PORT_OK, retcode);

        prop.setProperty("publisher.push_policy","new");
        prop.setProperty("thread_type","bar");
        prop.setProperty("measurement.exec_time","default");
        prop.setProperty("measurement.period_count","1");
        prop.setProperty("publisher.push_rate","1000.0");

        //thread_type が不正の場合 INVALID_ARGS を返すことを確認する。
        retcode = publisher.init(prop);
        CPPUNIT_ASSERT_EQUAL(RTC::PublisherPeriodic::INVALID_ARGS, retcode);

        //以下のpropertiesの設定で動作することを確認する。
        prop.setProperty("publisher.push_policy","all");
        prop.setProperty("publisher.skip_count","0");
        prop.setProperty("thread_type","default");
        prop.setProperty("measurement.exec_time","enable");
        prop.setProperty("measurement.exec_count","0");
        prop.setProperty("measurement.period_time","enable");
        prop.setProperty("measurement.period_count","0");
        prop.setProperty("publisher.push_rate","");
        retcode = publisher.init(prop);
        CPPUNIT_ASSERT_EQUAL(RTC::PublisherPeriodic::PORT_OK, retcode);

        prop.setProperty("publisher.push_policy","fifo");
        prop.setProperty("publisher.skip_count","1");
        prop.setProperty("thread_type","default");
        prop.setProperty("measurement.exec_time","disable");
        prop.setProperty("measurement.exec_count","1");
        prop.setProperty("measurement.period_time","disable");
        prop.setProperty("measurement.period_count","1");
        prop.setProperty("publisher.push_rate","");
        retcode = publisher.init(prop);
        CPPUNIT_ASSERT_EQUAL(RTC::PublisherPeriodic::PORT_OK, retcode);

        prop.setProperty("publisher.push_policy","skip");
        prop.setProperty("publisher.skip_count","-1");
        prop.setProperty("thread_type","default");
        prop.setProperty("measurement.exec_time","bar");
        prop.setProperty("measurement.exec_count","-1");
        prop.setProperty("measurement.period_time","bar");
        prop.setProperty("measurement.period_count","-1");
        prop.setProperty("publisher.push_rate","");
        retcode = publisher.init(prop);
        CPPUNIT_ASSERT_EQUAL(RTC::PublisherPeriodic::PORT_OK, retcode);

        prop.setProperty("publisher.push_policy","new");
        prop.setProperty("publisher.skip_count","foo");
        prop.setProperty("thread_type","default");
        prop.setProperty("measurement.exec_time","enable");
        prop.setProperty("measurement.exec_count","foo");
        prop.setProperty("measurement.period_time","enable");
        prop.setProperty("measurement.period_count","foo");
        prop.setProperty("publisher.push_rate","");
        retcode = publisher.init(prop);
        CPPUNIT_ASSERT_EQUAL(RTC::PublisherPeriodic::PORT_OK, retcode);

        prop.setProperty("publisher.push_policy","bar");
        prop.setProperty("publisher.skip_count","0");
        prop.setProperty("thread_type","default");
        prop.setProperty("measurement.exec_time","enable");
        prop.setProperty("measurement.exec_count","0");
        prop.setProperty("measurement.period_time","enable");
        prop.setProperty("measurement.period_count","0");
        prop.setProperty("publisher.push_rate","");
        retcode = publisher.init(prop);
        CPPUNIT_ASSERT_EQUAL(RTC::PublisherPeriodic::PORT_OK, retcode);

        prop.setProperty("publisher.push_policy","all");
        prop.setProperty("publisher.skip_count","0");
        prop.setProperty("thread_type","default");
        prop.setProperty("measurement.exec_time","enable");
        prop.setProperty("measurement.exec_count","0");
        prop.setProperty("measurement.period_time","enable");
        prop.setProperty("measurement.period_count","0");
        prop.setProperty("publisher.push_rate","0");
        retcode = publisher.init(prop);
        CPPUNIT_ASSERT_EQUAL(RTC::PublisherPeriodic::PORT_OK, retcode);

        prop.setProperty("publisher.push_policy","all");
        prop.setProperty("publisher.skip_count","0");
        prop.setProperty("thread_type","default");
        prop.setProperty("measurement.exec_time","enable");
        prop.setProperty("measurement.exec_count","0");
        prop.setProperty("measurement.period_time","enable");
        prop.setProperty("measurement.period_count","0");
        prop.setProperty("publisher.push_rate","-1");
        retcode = publisher.init(prop);
        CPPUNIT_ASSERT_EQUAL(RTC::PublisherPeriodic::PORT_OK, retcode);

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
        RTC::PublisherPeriodic publisher;

        //NULLを渡した場合INVALID_ARGSとなることを確認する。
        CPPUNIT_ASSERT_EQUAL(RTC::PublisherPeriodic::INVALID_ARGS, 
                             publisher.setConsumer(NULL));

        //
        CPPUNIT_ASSERT_EQUAL(RTC::PublisherPeriodic::PORT_OK, 
                             publisher.setConsumer(consumer0));

        //
        CPPUNIT_ASSERT_EQUAL(RTC::PublisherPeriodic::PORT_OK, 
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
        RTC::PublisherPeriodic publisher;

        //NULLを渡した場合INVALID_ARGSとなることを確認する。
        CPPUNIT_ASSERT_EQUAL(RTC::PublisherPeriodic::INVALID_ARGS, 
                             publisher.setBuffer(NULL));

        //
        CPPUNIT_ASSERT_EQUAL(RTC::PublisherPeriodic::PORT_OK, 
                             publisher.setBuffer(buffer0));

        //
        CPPUNIT_ASSERT_EQUAL(RTC::PublisherPeriodic::PORT_OK, 
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
        RTC::PublisherPeriodic publisher;
        publisher.setConsumer(consumer);

        //init() せずに activate() をコールした場合をi
        //PRECONDITION_NOT_MET 返すことを確認する。
        CPPUNIT_ASSERT_EQUAL(RTC::PublisherPeriodic::PRECONDITION_NOT_MET, 
                             publisher.activate());

        //init() せずに deactivate() をコールした場合をi
        //PRECONDITION_NOT_MET 返すことを確認する。
        CPPUNIT_ASSERT_EQUAL(RTC::PublisherPeriodic::PRECONDITION_NOT_MET, 
                             publisher.deactivate());

        //init()
        coil::Properties prop;
        prop.setProperty("publisher.push_policy","all");
        prop.setProperty("publisher.skip_count","0");
        prop.setProperty("thread_type","default");
        prop.setProperty("measurement.exec_time","enable");
        prop.setProperty("measurement.exec_count","0");
        prop.setProperty("measurement.period_time","enable");
        prop.setProperty("measurement.period_count","0");
        prop.setProperty("publisher.push_rate","");
        publisher.init(prop);

        
        //setBuffer() せずに activate() をコールした場合をi
        //PRECONDITION_NOT_MET 返すことを確認する。
        CPPUNIT_ASSERT_EQUAL(RTC::PublisherPeriodic::PRECONDITION_NOT_MET, 
                             publisher.activate());

        //setBuffer()
        RTC::CdrBufferBase* buffer = new RTC::CdrRingBuffer();
        publisher.setBuffer(buffer);


        CPPUNIT_ASSERT_EQUAL(false, 
                             publisher.isActive());
        
        CPPUNIT_ASSERT_EQUAL(RTC::PublisherPeriodic::PORT_OK, 
                             publisher.activate());

        CPPUNIT_ASSERT_EQUAL(true, 
                             publisher.isActive());

        //既に activate されている場合は 
        //activateすると
        //PORT_OK を返すことを確認する。
        CPPUNIT_ASSERT_EQUAL(RTC::PublisherPeriodic::PORT_OK, 
                             publisher.activate());

        CPPUNIT_ASSERT_EQUAL(true, 
                             publisher.isActive());
        
        CPPUNIT_ASSERT_EQUAL(RTC::PublisherPeriodic::PORT_OK, 
                             publisher.deactivate());

        CPPUNIT_ASSERT_EQUAL(false, 
                             publisher.isActive());
        
        //activate されていない状態で、
        //deactivateすると
        //PORT_OK を返すことを確認する。
        CPPUNIT_ASSERT_EQUAL(RTC::PublisherPeriodic::PORT_OK, 
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
        PublisherPeriodicMock publisher;

        coil::Properties prop;
        prop.setProperty("publisher.push_policy","all");
        prop.setProperty("publisher.skip_count","0");
        prop.setProperty("thread_type","default");
        prop.setProperty("measurement.exec_time","enable");
        prop.setProperty("measurement.exec_count","0");
        prop.setProperty("measurement.period_time","enable");
        prop.setProperty("measurement.period_count","0");
        prop.setProperty("publisher.push_rate","");
        publisher.init(prop);

        publisher.setConsumer(consumer);
        publisher.setBuffer(buffer);
        publisher.activate();

        for(int icc(0);icc<8;++icc)
        {
            cdrMemoryStream cdr;
            icc >>= cdr;

            CPPUNIT_ASSERT_EQUAL(RTC::PublisherPeriodic::PORT_OK,
                                 publisher.write(cdr,0,0));

        }

        coil::usleep(10000);
        //provider 側のバッファ full の状態でコール(full)
        {
        cdrMemoryStream cdr;
        8 >>= cdr;
        CPPUNIT_ASSERT_EQUAL(RTC::PublisherPeriodic::PORT_OK,
                                 publisher.write(cdr,0,0));
        coil::usleep(10000);
        }
        {
        cdrMemoryStream cdr;
        9 >>= cdr;
        CPPUNIT_ASSERT_EQUAL(RTC::PublisherPeriodic::BUFFER_FULL,
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

        coil::usleep(20000);
        //provider 側のバッファ full ではない状態でコール
        {
        cdrMemoryStream cdr;
        10 >>= cdr;
        CPPUNIT_ASSERT_EQUAL(RTC::PublisherPeriodic::PORT_OK,
                                 publisher.write(cdr,0,0));
        coil::usleep(10000);
        }
        {
        cdrMemoryStream cdr;
        11 >>= cdr;
        CPPUNIT_ASSERT_EQUAL(RTC::PublisherPeriodic::PORT_OK,
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
        PublisherPeriodicMock publisher;

        coil::Properties prop;
        prop.setProperty("publisher.push_policy","all");
        prop.setProperty("publisher.skip_count","0");
        prop.setProperty("thread_type","default");
        prop.setProperty("measurement.exec_time","enable");
        prop.setProperty("measurement.exec_count","0");
        prop.setProperty("measurement.period_time","enable");
        prop.setProperty("measurement.period_count","0");
        prop.setProperty("publisher.push_rate","");
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
                CPPUNIT_ASSERT_EQUAL(RTC::PublisherPeriodic::PORT_OK,
                                     ret);
            }
            else
            {
                CPPUNIT_ASSERT_EQUAL(RTC::PublisherPeriodic::BUFFER_FULL,
                                     ret);
            }
            coil::usleep(10000);

        }

        //consumer と provider 両方の buffer が full 状態のため、
        // この weite データは抜ける。
        {
        cdrMemoryStream cdr;
        16 >>= cdr;
        CPPUNIT_ASSERT_EQUAL(RTC::PublisherPeriodic::BUFFER_FULL,
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

        coil::usleep(10000);
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
        17 >>= cdr;
        CPPUNIT_ASSERT_EQUAL(RTC::PublisherPeriodic::PORT_OK,
                                 publisher.write(cdr,0,0));
        coil::usleep(20000);
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
        CPPUNIT_ASSERT_EQUAL((long)17,lval);
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
        PublisherPeriodicMock publisher;

        coil::Properties prop;
        prop.setProperty("publisher.push_policy","fifo");
        prop.setProperty("publisher.skip_count","0");
        prop.setProperty("thread_type","default");
        prop.setProperty("measurement.exec_time","enable");
        prop.setProperty("measurement.exec_count","0");
        prop.setProperty("measurement.period_time","enable");
        prop.setProperty("measurement.period_count","0");
        prop.setProperty("publisher.push_rate","100");
        publisher.init(prop);

        publisher.setConsumer(consumer);
        publisher.setBuffer(buffer);
        publisher.activate();

        for(int icc(0);icc<8;++icc)
        {
            cdrMemoryStream cdr;
            icc >>= cdr;

            CPPUNIT_ASSERT_EQUAL(RTC::PublisherPeriodic::PORT_OK,
                                 publisher.write(cdr,0,0));

        }

        coil::usleep(80000);
        //provider 側のバッファ full の状態でコール(full)
        {
        cdrMemoryStream cdr;
        8 >>= cdr;
        CPPUNIT_ASSERT_EQUAL(RTC::PublisherPeriodic::PORT_OK,
                                 publisher.write(cdr,0,0));
        coil::usleep(20000);
        }
        {
        cdrMemoryStream cdr;
        9 >>= cdr;
        CPPUNIT_ASSERT_EQUAL(RTC::PublisherPeriodic::BUFFER_FULL,
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
        coil::usleep(40000);

        //provider 側のバッファ full ではない状態でコール
        {
        cdrMemoryStream cdr;
        10 >>= cdr;
        CPPUNIT_ASSERT_EQUAL(RTC::PublisherPeriodic::PORT_OK,
                                 publisher.write(cdr,0,0));
        coil::usleep(30000);
        }
        {
        cdrMemoryStream cdr;
        11 >>= cdr;
        CPPUNIT_ASSERT_EQUAL(RTC::PublisherPeriodic::PORT_OK,
                                 publisher.write(cdr,0,0));
        coil::usleep(20000);
        }
        {
        cdrMemoryStream cdr;
        12 >>= cdr;
        CPPUNIT_ASSERT_EQUAL(RTC::PublisherPeriodic::PORT_OK,
                                 publisher.write(cdr,0,0));
        coil::usleep(20000);
        }
        {
        cdrMemoryStream cdr;
        13 >>= cdr;
        CPPUNIT_ASSERT_EQUAL(RTC::PublisherPeriodic::BUFFER_FULL,
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
        coil::usleep(20000);
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
            CPPUNIT_ASSERT_EQUAL((long)icc+12,lval);
        }


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
        PublisherPeriodicMock publisher;

        coil::Properties prop;
        prop.setProperty("publisher.push_policy","fifo");
        prop.setProperty("publisher.skip_count","0");
        prop.setProperty("thread_type","default");
        prop.setProperty("measurement.exec_time","enable");
        prop.setProperty("measurement.exec_count","0");
        prop.setProperty("measurement.period_time","enable");
        prop.setProperty("measurement.period_count","0");
        prop.setProperty("publisher.push_rate","100");
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
                CPPUNIT_ASSERT_EQUAL(RTC::PublisherPeriodic::PORT_OK,
                                     ret);
            }
            else
            {
                CPPUNIT_ASSERT_EQUAL(RTC::PublisherPeriodic::BUFFER_FULL,
                                     ret);
            }
            coil::usleep(20000);

        }

        //consumer と provider 両方の buffer が full 状態のため、
        // この weite データは抜ける。
        {
        cdrMemoryStream cdr;
        16 >>= cdr;
        CPPUNIT_ASSERT_EQUAL(RTC::PublisherPeriodic::BUFFER_FULL,
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

        coil::usleep(80000);
        // この weite データは転送される。
        for(int icc(0);icc<8;++icc)
        {
            cdrMemoryStream cdr;
            (17+icc) >>= cdr;
            RTC::PublisherBase::ReturnCode ret;
            ret = publisher.write(cdr,0,0);
            if(icc<1)
            {
                CPPUNIT_ASSERT_EQUAL(RTC::PublisherPeriodic::PORT_OK,
                                     ret);
            }
            else
            {
                CPPUNIT_ASSERT_EQUAL(RTC::PublisherPeriodic::BUFFER_FULL,
                                     ret);
            }
            coil::usleep(10000);
        }
        coil::usleep(80000);
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
        coil::usleep(10000);
        {
        cdrMemoryStream cdr;
        25 >>= cdr;
        CPPUNIT_ASSERT_EQUAL(RTC::PublisherPeriodic::PORT_OK,
                                 publisher.write(cdr,0,0));
        coil::usleep(10000);
        }
        coil::usleep(80000);
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
            CPPUNIT_ASSERT_EQUAL((long)icc+17,lval);
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
        PublisherPeriodicMock publisher;

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

            CPPUNIT_ASSERT_EQUAL(RTC::PublisherPeriodic::PORT_OK,
                                 publisher.write(cdr,0,0));

            coil::usleep(10000);
        }

        //provider 側のバッファ full の状態でコール(full)
        {
        cdrMemoryStream cdr;
        16 >>= cdr;
        CPPUNIT_ASSERT_EQUAL(RTC::PublisherPeriodic::PORT_OK,
                                 publisher.write(cdr,0,0));
        coil::usleep(10000);
        }
        {
        cdrMemoryStream cdr;
        17 >>= cdr;
        CPPUNIT_ASSERT_EQUAL(RTC::PublisherPeriodic::PORT_OK,
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

        coil::usleep(40000);
        //provider 側のバッファ full ではない状態でコール
        {
        cdrMemoryStream cdr;
        18 >>= cdr;
        CPPUNIT_ASSERT_EQUAL(RTC::PublisherPeriodic::PORT_OK,
                                 publisher.write(cdr,0,0));
        coil::usleep(10000);
        }
        {
        cdrMemoryStream cdr;
        19 >>= cdr;
        CPPUNIT_ASSERT_EQUAL(RTC::PublisherPeriodic::PORT_OK,
                                 publisher.write(cdr,0,0));
        coil::usleep(10000);
        }

        //データ抜けががないことを確認する。
        CPPUNIT_ASSERT_EQUAL(6,
                              consumer->get_m_put_data_len());
        for(int icc(0);icc<6;++icc)
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
        PublisherPeriodicMock publisher;

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
        for(int icc(0);icc<25;++icc)
        {
            cdrMemoryStream cdr;
            icc >>= cdr;

            RTC::PublisherBase::ReturnCode ret;
            ret = publisher.write(cdr,0,0);
            if(icc<18)
            {
                CPPUNIT_ASSERT_EQUAL(RTC::PublisherPeriodic::PORT_OK,
                                     ret);
            }
            else
            {
                CPPUNIT_ASSERT_EQUAL(RTC::PublisherPeriodic::BUFFER_FULL,
                                     ret);
            }
            coil::usleep(20000);

        }

        //consumer と provider 両方の buffer が full 状態のため、
        // この weite データは抜ける。
        {
        cdrMemoryStream cdr;
        25 >>= cdr;
        CPPUNIT_ASSERT_EQUAL(RTC::PublisherPeriodic::BUFFER_FULL,
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

        coil::usleep(20000);
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
        coil::usleep(20000);
        {
        cdrMemoryStream cdr;
        26 >>= cdr;
        CPPUNIT_ASSERT_EQUAL(RTC::PublisherPeriodic::PORT_OK,
                                 publisher.write(cdr,0,0));
        coil::usleep(10000);
        }
        {
        cdrMemoryStream cdr;
        27 >>= cdr;
        CPPUNIT_ASSERT_EQUAL(RTC::PublisherPeriodic::PORT_OK,
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
        CPPUNIT_ASSERT_EQUAL((long)26,lval);
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
        PublisherPeriodicMock publisher;

        coil::Properties prop;
        prop.setProperty("publisher.push_policy","new");
        prop.setProperty("publisher.skip_count","0");
        prop.setProperty("thread_type","default");
        prop.setProperty("measurement.exec_time","enable");
        prop.setProperty("measurement.exec_count","0");
        prop.setProperty("measurement.period_time","enable");
        prop.setProperty("measurement.period_count","0");
        prop.setProperty("publisher.push_rate","100");
        publisher.init(prop);

        publisher.setConsumer(consumer);
        publisher.setBuffer(buffer);
        publisher.activate();

        //8件のデータは転送されない
        //最新データの7は転送される。
        for(int icc(0);icc<8;++icc)
        {
            cdrMemoryStream cdr;
            icc >>= cdr;

            CPPUNIT_ASSERT_EQUAL(RTC::PublisherPeriodic::PORT_OK,
                                 publisher.write(cdr,0,0));

        }

  
        coil::usleep(10000);
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
        coil::usleep(10000);
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
        PublisherPeriodicMock publisher;

        coil::Properties prop;
        prop.setProperty("publisher.push_policy","all");
        prop.setProperty("publisher.skip_count","0");
        prop.setProperty("thread_type","default");
        prop.setProperty("measurement.exec_time","enable");
        prop.setProperty("measurement.exec_count","0");
        prop.setProperty("measurement.period_time","enable");
        prop.setProperty("measurement.period_count","0");
        publisher.init(prop);

        //
        {
        cdrMemoryStream cdr;
        123 >>= cdr;
        CPPUNIT_ASSERT_EQUAL(RTC::PublisherPeriodic::PRECONDITION_NOT_MET,
                                 publisher.write(cdr,0,0));
        coil::usleep(10000);
        }

        //
        publisher.setBuffer(buffer);
        {
        cdrMemoryStream cdr;
        123 >>= cdr;
        CPPUNIT_ASSERT_EQUAL(RTC::PublisherPeriodic::PRECONDITION_NOT_MET,
                                 publisher.write(cdr,0,0));
        coil::usleep(10000);
        }

        //
        publisher.setConsumer(consumer);
        {
        cdrMemoryStream cdr;
        123 >>= cdr;
        CPPUNIT_ASSERT_EQUAL(RTC::PublisherPeriodic::PORT_OK,
                                 publisher.write(cdr,0,0));
        coil::usleep(10000);
        }

        delete consumer;
        delete buffer;

    }
    /*!
     * @brief デストラクタのテスト
     * 
     * - デストラクタ呼出により、release()メソッドを呼び出さずともPublisherの動作が問題なく停止するか？
     */
/*
    void test_destructor()
    {
      CounterConsumer* consumer1 = new CounterConsumer();

      { // Publisherのインスタンススコープ開始
	CounterConsumer* consumer2 = new CounterConsumer(consumer1);
	coil::Properties prop;
	prop.setProperty("dataport.push_rate", "10"); // 10 [Hz]
	RTC::PublisherPeriodic publisher(consumer2, prop);
	// 5 [sec]だけ動作させる
	coil::usleep(5000000);
				
      } // デストラクタを呼び出す（スコープを終了させる）
			
      coil::usleep(1000000); // 完全停止するまで待つ
			
      // この時点での呼出回数を記録する
      int countReleased = consumer1->getCount();
			
      // さらにConsumerがコールバックされ得る時間を与える
      coil::usleep(5000000); // 5 [sec]
			
      // この時点での呼出回数を取得し、先に記録しておいた回数から変化がない
      // （つまり、Publisherの動作が停止している）ことを確認する
      int countSleeped = consumer1->getCount();
      CPPUNIT_ASSERT_EQUAL(countReleased, countSleeped);
    }
*/
		
    /*!
     * @brief release()メソッドのテスト
     * 
     * - release()メソッド呼出によりPublisherの動作が停止するか？
     */
/*
    void test_release()
    {
      CounterConsumer* consumer = new CounterConsumer();
      coil::Properties prop;
      prop.setProperty("dataport.push_rate", "10"); // 10 [Hz]
      RTC::PublisherPeriodic publisher(consumer, prop);
			
      // 5 [sec]だけ動作させる
      coil::usleep(5000000);
			
      // Publisherの動作を停止させる
      publisher.release();
      coil::usleep(1000000); // 完全停止するまで待つ
			
      // この時点での呼出回数を記録する
      int countReleased = consumer->getCount();
			
      // さらにConsumerがコールバックされ得る時間を与える
      coil::usleep(5000000); // 5 [sec]
			
      // この時点での呼出回数を取得し、先に記録しておいた回数から変化がない
      // （つまり、Publisherの動作が停止している）ことを確認する
      int countSleeped = consumer->getCount();
      CPPUNIT_ASSERT_EQUAL(countReleased, countSleeped);
    }
*/
		
    /*!
     * @brief PublisherによるConsumer呼出間隔精度のテスト
     * 
     * - Publisherに指定した時間間隔で、正しくConsumerがコールバックされるか？
     */
/*
    void test_interval_accuracy()
    {
      MockConsumer* consumer = new MockConsumer();
      coil::Properties prop;
      prop.setProperty("dataport.push_rate", "10"); // 10 [Hz]
      RTC::PublisherPeriodic publisher(consumer, prop);
			
      // 5 [sec]だけ動作させる
      coil::usleep(5000000);
			
      // Publisherの動作を停止させる
      publisher.release();
      coil::usleep(1000000); // 完全停止するまで待つ
			
      // 指定した時間間隔で正しくConsumerがコールバックされているか？
      long permissibleTickMin = static_cast<long>(100000 * 0.9);
      long permissibleTickMax = static_cast<long>(100000 * 1.1);
      const std::vector<long> intervalTicks = consumer->getIntervalTicks();
      CPPUNIT_ASSERT(intervalTicks.size() > 0);

      for (std::vector<long>::size_type i = 0; i < intervalTicks.size(); i++)
	{
	  long tick = intervalTicks[i];
	  CPPUNIT_ASSERT((permissibleTickMin <= tick) && (tick <= permissibleTickMax));
	}
    }
*/
  };
}; // namespace PublisherPeriodic

/*
 * Register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(PublisherPeriodic::PublisherPeriodicTests);

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
#endif // PublisherPeriodic_cpp
