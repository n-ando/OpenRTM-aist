// -*- C++ -*-
/*!
 * @file OutPort.h
 * @brief OutPort class
 * @date $Date: 2007-01-06 17:56:19 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006
 *     Noriaki Ando
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: OutPort.h,v 1.2 2007-01-06 17:56:19 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.1  2006/12/02 18:45:30  n-ando
 * The first commitment.
 *
 *
 */

#ifndef OutPort_h
#define OutPort_h
 
#include <rtm/BufferBase.h>
#include <rtm/RingBuffer.h>
#include <rtm/OutPortBase.h>
#include <rtm/PortCallBack.h>
#include <iostream>

namespace RTC
{
  /*!
   * @if jp
   *
   * @class OutPort
   *
   * @brief OutPort テンプレートクラス
   * 
   * OutPort テンプレートクラス、テンプレートの引数として、OutPortが
   * 扱うデータ型 DataType, OutPortのバッファ型 BufferType をとる。
   * OutPort<> クラスは、ミドルウエア側のインターフェースとして
   *
   * @else
   * 
   * @endif
   */
  template <class DataType,
	    template <class DataType> class Buffer = RingBuffer >
  class OutPort
    : public OutPortBase,
      public Buffer<DataType>
  {
  public:
    /*!
     * @if jp
     *
     * @brief OutPort<DataType, BufferType> クラスのコンストラクタ
     *
     * @else
     *
     * @brief Constructor
     *
     * @endif
     */
    OutPort(const char* name, DataType& value, long int length = 8)
      : OutPortBase(name), Buffer<DataType>(length),
	m_value(value),
	m_timeoutTick(1000), // timeout tick: 1ms
	m_readBlock(false), m_readTimeout(0),
	m_writeBlock(false), m_writeTimeout(0),
	m_OnWrite(NULL), m_OnWriteConvert(NULL),
	m_OnRead(NULL),  m_OnReadConvert(NULL),
	m_OnOverflow(NULL), m_OnUnderflow(NULL)
    {
    }
    
    virtual ~OutPort()
    {
    }

    /*!
     * @if jp
     *
     * @brief データ書き込み
     *
     * @else
     *
     * @brief Write data
     *
     * @endif
     */
    virtual bool write(const DataType& value)
    {
      if (m_OnWrite != NULL)
        {
	  (*m_OnWrite)(value);
        }
      
      long int timeout = m_writeTimeout;
      
      timeval tm_cur, tm_pre;
      gettimeofday(&tm_pre, NULL);
      
      // blocking and timeout wait
      long int count(0);
      while (m_writeBlock && this->isFull())
        {
	  if (m_writeTimeout < 0) 
	    {
	      usleep(m_timeoutTick);
	      continue;
	    }
	  
	  // timeout wait
	  gettimeofday(&tm_cur, NULL);
	  long int sec (tm_cur.tv_sec  - tm_pre.tv_sec);
	  long int usec(tm_cur.tv_usec - tm_pre.tv_usec);
	  
	  timeout -= (sec * usec_per_sec + usec);
	  if (timeout < 0) break;
	  
	  tm_pre = tm_cur;
	  usleep(m_timeoutTick);
	  ++count;
	}
      
      if (this->isFull())
        {
	  if (m_OnOverflow != NULL)
	    (*m_OnOverflow)(value);
	  return false;
	}
      
      if (m_OnWriteConvert == NULL) 
        {
	  this->put(value);
	}
      else
	{
	  this->put((*m_OnWriteConvert)(value));
	}
      notify();
      return true;
    }

    bool write()
    {
      return write(m_value);
    }

    bool operator<<(DataType& value)
    {
      return write(value);
    }

    /*!
     * @if jp
     *
     * @brief データ読み出し
     *
     * @else
     *
     * @brief Read data
     *
     * @endif
     */
    bool read(DataType& value)
    {
      if (m_OnRead != NULL) (*m_OnRead)();      
      
      long int timeout = m_readTimeout;
      
      timeval tm_cur, tm_pre;
      gettimeofday(&tm_pre, NULL);
      
      // blocking and timeout wait
      while (m_readBlock && this->isEmpty())
      {
	  if (m_readTimeout < 0)
	    {
	      usleep(m_timeoutTick);
	      continue;
	    }
	  
	  // timeout wait
	  gettimeofday(&tm_cur, NULL);
	  long int sec (tm_cur.tv_sec  - tm_pre.tv_sec);
	  long int usec(tm_cur.tv_usec - tm_pre.tv_usec);
	  
	  timeout -= (sec * usec_per_sec + usec);
	  if (timeout < 0) break;
	  
	  tm_pre = tm_cur;
	  usleep(m_timeoutTick);
	}
      
      if (this->isEmpty())
        {
          if (m_OnUnderflow != NULL)
            {
	      value = (*m_OnUnderflow)();
	      return false;
	    }
	  else
	    {
	      return false;
	    }
	}

      if (m_OnReadConvert == NULL) 
        {
	  value = this->get();
	  return true;
	}
      else
	{
	  value = (*m_OnReadConvert)(this->get());
	  return true;
	}
      // never comes here
      return false;
    }

    /*!
     * @if jp
     *
     * @brief read() のブロック・非ブロックモードのセット
     *
     * @else
     *
     * @brief Set read() block mode
     *
     * @endif
     */
    void setReadBlock(bool block)
    {
      m_readBlock = block;
    }

    /*!
     * @if jp
     *
     * @brief write() のブロック・非ブロックモードのセット
     *
     * @else
     *
     * @brief Set read() block mode
     *
     * @endif
     */
    void setWriteBlock(bool block)
    {
      m_writeBlock = block;
    }

    /*!
     * @if jp
     *
     * @brief read() のタイムアウト時間の設定
     * 
     * read() のタイムアウト時間を usec で設定する。
     * read() はブロックモードでなければならない。
     * @param timeout タイムアウト時間 [usec]
     *
     * @else
     *
     * @brief Set read() timeout
     *
     * @endif
     */
    void setReadTimeout(long int timeout)
    {
      m_readTimeout = timeout;
    }

    /*!
     * @if jp
     *
     * @brief write() のタイムアウト時間の設定
     * 
     * write() のタイムアウト時間を usec で設定する。
     * write() はブロックモードでなければならない。
     * @param timeout タイムアウト時間 [usec]
     *
     * @else
     *
     * @brief Set write() timeout
     *
     * @endif
     */
    void setWriteTimeout(long int timeout)
    {
      m_writeTimeout = timeout;
    }

    /*!
     * @if jp
     *
     * @brief OutWrite コールバックの設定
     *
     * @else
     *
     * @brief Set OnWrite callback
     *
     * @endif
     */
    inline void setOnWrite(OnWrite<DataType>* on_write)
    {
      m_OnWrite = on_write;
    }

    /*!
     * @if jp
     *
     * @brief OutWriteConvert コールバックの設定
     *
     * @else
     *
     * @brief Set OnWriteConvert callback
     *
     * @endif
     */
    inline void setOnWriteConvert(OnWriteConvert<DataType>* on_wconvert)
    {
      m_OnWriteConvert = on_wconvert;
    }

    /*!
     * @if jp
     *
     * @brief OutOverflow コールバックの設定
     *
     * @else
     *
     * @brief Set OnOverflow callback
     *
     * @endif
     */
    inline void setOnOverflow(OnOverflow<DataType>* on_overflow)
    {
      m_OnOverflow = on_overflow;
    }

    /*!
     * @if jp
     *
     * @brief OutRead コールバックの設定
     *
     * @else
     *
     * @brief Set OnRead callback
     *
     * @endif
     */
    inline void setOnRead(OnRead<DataType>* on_read)
    {
      m_OnRead = on_read;
    }

    /*!
     * @if jp
     *
     * @brief OutReadConvert コールバックの設定
     *
     * @else
     *
     * @brief Set OnReadConvert callback
     *
     * @endif
     */
    inline void setOnReadConvert(OnReadConvert<DataType>* on_rconvert)
    {
      m_OnReadConvert = on_rconvert;
    }

    /*!
     * @if jp
     *
     * @brief OutUnderflow コールバックの設定
     *
     * @else
     *
     * @brief Set OnUnderflow callback
     *
     * @endif
     */
    inline void setOnUnderflow(OnUnderflow<DataType>* on_underflow)
    {
      m_OnUnderflow = on_underflow;
    }    

  private:
    /*!
     * @if jp
     * @brief バインドされる T 型の変数への参照
     * @else
     * @brief reference to type-T value bound this OutPort
     * @endif
     */
    DataType& m_value;

    /*!
     * @if jp
     * @brief タイムアウトのポーリング周期　[usec]
     * @else
     * @brief reference to type-T value bound this OutPort
     * @endif
     */
    long int m_timeoutTick;

    /*!
     * @if jp
     * @brief read() のブロック・非ブロックモードフラグ
     * @else
     * @brief Flag of read()'s blocking/non-blocking mode
     * @endif
     */
    bool m_readBlock;

    /*!
     * @if jp
     * @brief read() の Timeout [usec]
     * @else
     * @brief Timeout of read()
     * @endif
     */
    long int m_readTimeout;

    /*!
     * @if jp
     * @brief read() のブロック・非ブロックモードフラグ
     * @else
     * @brief Flag of read()'s blocking/non-blocking mode
     * @endif
     */
    bool m_writeBlock;

    /*!
     * @if jp
     * @brief write() の Timeout [usec]
     * @else
     * @brief Timeout of write()
     * @endif
     */
    long int m_writeTimeout;

    /*!
     * @if jp
     * @brief OnWrite コールバックファンクタへのポインタ
     * @else
     * @brief OnWrite callback functor pointer
     * @endif
     */
    OnWrite<DataType>* m_OnWrite;

    /*!
     * @if jp
     * @brief OnWriteConvert コールバックファンクタへのポインタ
     * @else
     * @brief OnWriteConvert callback functor pointer
     * @endif
     */
    OnWriteConvert<DataType>* m_OnWriteConvert;

    /*!
     * @if jp
     * @brief OnRead コールバックファンクタへのポインタ
     * @else
     * @brief OnRead callback functor pointer
     * @endif
     */
    OnRead<DataType>* m_OnRead;

    /*!
     * @if jp
     * @brief OnReadConvert コールバックファンクタへのポインタ
     * @else
     * @brief OnReadConvert callback functor pointer
     * @endif
     */
    OnReadConvert<DataType>* m_OnReadConvert;

    /*!
     * @if jp
     * @brief OnOverflow コールバックファンクタへのポインタ
     * @else
     * @brief OnOverflow callback functor pointer
     * @endif
     */
    OnOverflow<DataType>* m_OnOverflow;

    /*!
     * @if jp
     * @brief OnUnderflow コールバックファンクタへのポインタ
     * @else
     * @brief OnUnderflow callback functor pointer
     *
     * @endif
     */
    OnUnderflow<DataType>* m_OnUnderflow;

    static const long int usec_per_sec = 1000000;

  };
}; // namespace RTC

#endif // OutPort_h
