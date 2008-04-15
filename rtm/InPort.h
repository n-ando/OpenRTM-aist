// -*- C++ -*-
/*!
 * @file InPort.h
 * @brief InPort template class
 * @date $Date: 2007-12-31 03:08:03 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2003-2008
 *     Noriaki Ando
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: InPort.h,v 1.6.4.4 2007-12-31 03:08:03 n-ando Exp $
 *
 */

#ifndef RtcInPort_h
#define RtcInPort_h

#include <string>
#include <vector>
#include <iostream>
#include <rtm/BufferBase.h>
#include <rtm/RingBuffer.h>
#include <rtm/PortCallBack.h>
#include <rtm/RTC.h>

#define TIMEOUT_TICK_USEC 10
#define USEC_PER_SEC 1000000

namespace RTC
{
  /*!
   * @if jp
   *
   * @class InPort
   *
   * @brief InPort テンプレートクラス
   * 
   * InPort の実装である InPort<T> のテンプレートクラス。
   * <T> はBasicDataType.idl にて定義されている型で、メンバとして
   * Time 型の tm , および T型の data を持つ構造体でなくてはならない。
   * InPort は内部にリングバッファを持ち、外部から送信されたデータを順次
   * このリングバッファに格納する。リングバッファのサイズはデフォルトで64と
   * なっているが、コンストラクタ引数によりサイズを指定することができる。
   * データはフラグによって未読、既読状態が管理され、isNew(), write(), read(),
   * isFull(), isEmpty() 等のメソッドによりハンドリングすることができる。
   *
   * @since 0.2.0
   *
   * @else
   *
   * @class InPort
   *
   * @brief InPort template class
   *
   * This is a template class that implements InPort.
   * <T> is the type defined in BasicDataType.idl and must be the structure which
   * has both Time type tm and type-T data as a member. InPort has a ring
   * buffer internally, and stores the received data externally in this buffer
   * one by one. The size of ring buffer can be specified according to 
   * the argument of constructor, though the default size is 64. Unread
   * data and data which is already read are managed with the flag, and the
   * data can be handled by the isNew(), write(), read(), isFull() and isEmpty()
   * method etc. 
   *
   * @since 0.2.0
   *
   * @endif
   */
  template <class DataType,
	    template <class DataType> class Buffer = RingBuffer >
  class InPort
    : public Buffer<DataType>
  {
  public:
    /*!
     * @if jp
     *
     * @brief コンストラクタ
     *
     * コンストラクタ。
     * パラメータとして与えられる T 型の変数にバインドされる。
     *
     * @param name InPort 名。InPortBase:name() により参照される。
     * @param value この InPort にバインドされる T 型の変数
     * @param bufsize InPort 内部のリングバッファのバッファ長(デフォルト値:64)
     * @param read_block 読込ブロックフラグ。
     *        データ読込時に未読データがない場合、次のデータ受信までブロックする
     *        かどうかを設定(デフォルト値:false)
     * @param write_block 書込ブロックフラグ。
     *        データ書込時にバッファがフルであった場合、バッファに空きができる
     *        までブロックするかどうかを設定(デフォルト値:false)
     * @param read_timeout 読込ブロックを指定していない場合の、データ読取タイム
     *        アウト時間(ミリ秒)(デフォルト値:0)
     * @param write_timeout 書込ブロックを指定していない場合の、データ書込タイム
     *        アウト時間(ミリ秒)(デフォルト値:0)
     *
     * @else
     *
     * @brief A constructor.
     *
     * constructor.
     * This is bound to type-T variable given as a parameter.
     *
     * @param name A name of the InPort. This name is referred by
     *             InPortBase::name().
     * @param value type-T variable that is bound to this InPort.
     * @param bufsize Buffer length of internal ring buffer of InPort
     *                (The default value:64)
     * @param read_block Flag of reading block.
     *                   When there are not unread data at reading data,
     *                   set whether to block data until receiving the next 
     *                   data. (The default value:false)
     * @param write_block Flag of writing block.
     *                    If the buffer was full at writing data, set whether 
     *                    to block data until the buffer has space. 
     *                    (The default value:false)
     * @param read_timeout Data reading timeout time (millisecond) 
     *                     when not specifying read blocking.
     *                     (The default value:0)
     * @param write_timeout Data writing timeout time (millisecond)
     *                      when not specifying writing block.
     *                      (The default value:0)
     *
     * @endif
     */
    InPort(const char* name, DataType& value,
	   int bufsize=64, 
	   bool read_block = false, bool write_block = false,
	   int read_timeout = 0, int write_timeout = 0)
      : Buffer<DataType>(bufsize),
	m_name(name), m_value(value),
	m_readBlock(read_block),   m_readTimeout(read_timeout),
	m_writeBlock(write_block), m_writeTimeout(write_timeout),
	m_OnWrite(NULL), m_OnWriteConvert(NULL),
	m_OnRead(NULL),  m_OnReadConvert(NULL),
	m_OnOverflow(NULL), m_OnUnderflow(NULL)
    {
    };
    
    /*!
     * @if jp
     *
     * @brief デストラクタ
     *
     * デストラクタ。
     *
     * @else
     *
     * @brief Destructor
     *
     * Destructor
     *
     * @endif
     */
    virtual ~InPort(){};
    
    /*!
     * @if jp
     *
     * @brief ポート名称を取得する。
     *
     * ポート名称を取得する。
     *
     * @return ポート名称
     *
     * @else
     *
     * @brief Get port name
     *
     * Get port name.
     *
     * @return The port name
     *
     * @endif
     */
    virtual const char* name()
    {
      return m_name.c_str();
    }
    
    /*!
     * @if jp
     *
     * @brief DataPort に値を書き込む
     *
     * DataPort に値を書き込む。
     *
     * - コールバックファンクタ OnWrite がセットされている場合、
     *   InPort が保持するバッファに書き込む前に OnWrite が呼ばれる。
     * - InPort が保持するバッファがオーバーフローを検出できるバッファであり、
     *   かつ、書き込む際にバッファがオーバーフローを検出した場合、
     *   コールバックファンクタ OnOverflow が呼ばれる。
     * - コールバックファンクタ OnWriteConvert がセットされている場合、
     *   バッファ書き込み時に、OnWriteConvert の operator() の戻り値が
     *   バッファに書き込まれる。
     * - setWriteTimeout() により書き込み時のタイムアウトが設定されている場合、
     *   タイムアウト時間だけバッファフル状態が解除するのを待ち、
     *   OnOverflowがセットされていればこれを呼び出して戻る。
     *
     * @param value 書込対象データ
     *
     * @return 書込処理結果(書込成功:true、書込失敗:false)
     *
     * @else
     *
     * @brief  Write the value to DataPort
     *
     * Write the value to DataPort
     *
     * - When callback functor OnWrite is already set, OnWrite will be
     *   invoked before writing into the buffer held by InPort.
     * - When the buffer held by InPort can detect the overflow,
     *   and when it detected the overflow at writing, callback functor
     *   OnOverflow will be invoked.
     * - When callback functor OnWriteConvert is set, the return value of
     *   operator() of OnWriteConvert will be written into the buffer 
     *   at the writing.
     * - When timeout of writing time is already set by setWriteTimeout(),
     *   it will wait for only timeout time until the state of the buffer full
     *   is reset, if OnOverflow is already set this will be invoked to 
     *   return.
     *
     * @param value The target data for the writing
     *
     * @return Writing result (Successful:true, Failed:false)
     *
     * @endif
     */
    bool write(const DataType& value)
    {
      if (m_OnWrite != NULL) (*m_OnWrite)(value);      
      
      long int timeout = m_writeTimeout;
      
      timeval tm_cur, tm_pre;
      ACE_Time_Value tt;
      tt = ACE_OS::gettimeofday();
      tm_pre = tt.operator timeval();
      
      // blocking and timeout wait
      while (m_writeBlock && this->isFull())
	{
	  if (m_writeTimeout < 0) 
	    {
	      usleep(TIMEOUT_TICK_USEC);
	      continue;
	    }
	  
	  // timeout wait
	  ACE_Time_Value tt;
	  tt = ACE_OS::gettimeofday();
	  tm_cur = tt.operator timeval();
	  long int sec (tm_cur.tv_sec  - tm_pre.tv_sec);
	  long int usec(tm_cur.tv_usec - tm_pre.tv_usec);
	  
	  timeout -= (sec * USEC_PER_SEC + usec);
	  if (timeout < 0) break;
	  
	  tm_pre = tm_cur;
	  usleep(TIMEOUT_TICK_USEC);
	}
      
      if (this->isFull() && m_OnOverflow != NULL)
	{
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
      return true;
    }
    
    /*!
     * @if jp
     *
     * @brief DataPort から値を読み出す
     *
     * DataPort から値を読み出す
     *
     * - コールバックファンクタ OnRead がセットされている場合、
     *   DataPort が保持するバッファから読み出す前に OnRead が呼ばれる。
     * - DataPort が保持するバッファがアンダーフローを検出できるバッファで、
     *   かつ、読み出す際にバッファがアンダーフローを検出した場合、
     *   コールバックファンクタ OnUnderflow が呼ばれる。
     * - コールバックファンクタ OnReadConvert がセットされている場合、
     *   バッファ書き込み時に、OnReadConvert の operator() の戻り値が
     *   read()の戻り値となる。
     * - setReadTimeout() により読み出し時のタイムアウトが設定されている場合、
     *   バッファアンダーフロー状態が解除されるまでタイムアウト時間だけ待ち、
     *   OnUnderflowがセットされていればこれを呼び出して戻る
     *
     * @return 読み出したデータ
     *
     * @else
     *
     * @brief Readout the value from DataPort
     *
     * Readout the value from DataPort
     *
     * - When Callback functor OnRead is already set, OnRead will be invoked
     *   before reading from the buffer held by DataPort.
     * - When the buffer held by DataPort can detect the underflow,
     *   and when it detected the underflow at reading, callback functor
     *   OnUnderflow will be invoked.
     * - When callback functor OnReadConvert is already set, the return value of
     *   operator() of OnReadConvert will be the return value of read().
     * - When timeout of reading is already set by setReadTimeout(),
     *   it waits for only timeout time until the state of the buffer underflow
     *   is reset, and if OnUnderflow is already set, this will be invoked to 
     *   return.
     *
     * @return Readout data
     *
     * @endif
     */
    DataType read()
    {
      if (m_OnRead != NULL) (*m_OnRead)();
      
      long int timeout = m_readTimeout;
      
      timeval tm_cur, tm_pre;
      ACE_Time_Value tt;
      tt = ACE_OS::gettimeofday();
      tm_pre = tt.operator timeval();
      
      // blocking and timeout wait
      while (m_readBlock && this->isEmpty())
	{
	  if (m_readTimeout < 0)
	    {
	      usleep(TIMEOUT_TICK_USEC);
	      continue;
	    }
	  
	  // timeout wait
	  ACE_Time_Value tt;
	  tt = ACE_OS::gettimeofday();
	  tm_cur = tt.operator timeval();
	  long int sec (tm_cur.tv_sec  - tm_pre.tv_sec);
	  long int usec(tm_cur.tv_usec - tm_pre.tv_usec);
	  
	  timeout -= (sec * USEC_PER_SEC + usec);
	  if (timeout < 0) break;
	  
	  tm_pre = tm_cur;
	  usleep(TIMEOUT_TICK_USEC);
	}
      
      if (this->isEmpty() && m_OnUnderflow != NULL)
	{
	  m_value = (*m_OnUnderflow)();
	  return m_value;
	}
      
      if (m_OnReadConvert == NULL) 
	{
	  m_value = this->get();
	  return m_value;
	}
      else
	{
	  m_value = (*m_OnReadConvert)(this->get());
	  return m_value;
	}
      // never comes here
      return m_value;
    }
    
    /*!
     * @if jp
     *
     * @brief InPort 内のリングバッファの値を初期化
     *
     * InPort 内のリングバッファの値を指定した値で初期化する。
     * (現状ではコメントアウト)
     *
     * @param value 初期化対象データ
     *
     * @else
     *
     * @brief Initialize the ring buffer value in InPort
     *
     * Initialize the ring buffer in InPort by specified value.
     * (Currently, commented out)
     *
     * @param value The target initialization data
     *
     * @endif
     */
    virtual void init(DataType& value)
    {
      //      m_buffer.init(value);
    }
    
    /*!
     * @if jp
     *
     * @brief バインドされた T 型の変数に InPort バッファの最新値を読み込む
     *
     * バインドされた T 型のデータに InPort の最新値を読み込む。
     * コンストラクタで T 型の変数と InPort がバインドされていなければならない。
     * このメソッドはポリモーフィックに使用される事を前提としているため、
     * 型に依存しない引数、戻り値となっている。
     *
     * @else
     *
     * @brief Read the newly value to type-T variable which is bound to InPort's
     *        buffer.
     *
     * Read the newly value to type-T data which is bound to InPort's buffer.
     * The type-T variable must be bound to InPort in constructor.
     * Since this method assumes to be used for polymorphic,
     * its argument and the return value do not depend on type.
     *
     * @endif
     */
    void update()
    {
      try
	{
	  m_value = this->get();
	}
      catch (...)
	{
	  if (m_OnUnderflow != NULL) (*m_OnUnderflow)();
	}
      return;
    };
    
    /*!
     * @if jp
     *
     * @brief T 型のデータへ InPort の最新値データを読み込む
     *
     * InPort に設定されている最新データを読み込み、
     * 指定されたデータ変数に設定する。
     *
     * @param rhs InPort バッファから値を読み込む T 型変数
     *
     * @else
     *
     * @brief Read the newly value data in InPort to type-T variable
     *
     * Read the newly data set in InPort and set to specified data variable.
     *
     * @param rhs The type-T variable to read from InPort's buffer
     *
     * @endif
     */
    void operator>>(DataType& rhs)
    {
      rhs = read();
      return;
    }
    
    /*!
     * @if jp
     *
     * @brief T 型のデータを DataPort へ書き込み
     *
     * 設定された T 型のデータをDataPortに書き込む。
     *
     * @param value DaraPort へ書き込む T 型変数
     *
     * @else
     *
     * @brief Write the type-T data to DataPort
     *
     * Write the given type-T data to DataPort.
     *
     * @param value The type-T variable to write to DaraPort
     *
     * @endif
     */
    void operator<<(DataType& value)
    {
      write(value);
      return;
    }
    
    /***
     * @if jp
     *
     * @brief 未読の新しいデータ数を取得する
     *
     * @else
     *
     * @brief Get number of new unread data
     *
     * @endif
     */
    /*
      virtual int getNewDataLen()
      {
      return m_buffer->new_data_len();
      }
    */
    
    /***
     * @if jp
     *
     * @brief 未読の新しいデータを取得する
     *
     * @else
     *
     * @brief Get new unread data
     *
     * @endif
     */
    /*
      virtual std::vector<T> getNewList()
      {
      return m_buffer.get_new_list();
      }
    */
    
    /***
     * @if jp
     *
     * @brief 未読の新しいデータを逆順(新->古)で取得する
     *
     * @else
     *
     * @brief Get new unread data backwards by date (new->old)
     *
     * @endif
     */
    /*
      virtual std::vector<T> getNewListReverse()
      {
      return m_buffer.get_new_rlist();
      }
    */
    
    /*!
     * @if jp
     *
     * @brief InPort バッファへデータ入力時のコールバックの設定
     *
     * InPort が持つバッファにデータがputされたときに呼ばれるコールバック
     * オブジェクトを設定する。設定されるコールバックオブジェクトは
     * InPort<DataType>::OnPutクラスを継承し、引数 const DataType& 、
     * 戻り値 void の operator() 関数が実装されている必要がある。
     *
     * struct MyOnPutCallback : public InPort<DataType> {<br>
     *   void operator()(const DataType data) {<br>
     *     処理<br>
     *   }<br>
     * };<br>
     * のようにコールバックオブジェクトを実装し、<br>
     * <br> 
     * m_inport.setOnPut(new MyOnPutCallback());<br>
     * のようにコールバックオブジェクトをセットする。
     *
     * @param on_write OnWrite&lt;DataType&gt;型のオブジェクト
     *
     * @else
     *
     * @brief Set callback for inputting data into the InPort buffer.
     *
     * Set the callback object invoked when data was put in the InPort's buffer.
     * The callback object which was set inherits InPort<DataType>::OnPut class,
     * and the method operator(), which has the argument "const DataType&"
     * and the return value "void", need to be implemented.
     *
     * Callback object should be implemented as follow:<br>
     * struct MyOnPutCallback : public InPort<DataType> {<br>
     *   void operator()(const DataType data) {<br>
     *     Operation<br>
     *   }<br>
     * };<br>
     * and should be set as follow:
     * <br> 
     * m_inport.setOnPut(new MyOnPutCallback());<br>
     *
     * @param on_write OnWrite&lt;DataType&gt; type object
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
     * @brief InPort バッファへデータ書き込み時のコールバックの設定
     *
     * InPort が持つバッファにデータ書き込まれる時に呼ばれるコールバック
     * オブジェクトを設定する。バッファにはコールバックオブジェクトの
     * 戻り値が設定される。
     * 
     * @param on_wconvert OnWriteConvert&lt;DataType&gt;型のオブジェクト
     *
     * @else
     *
     * @brief Set callback when data is written into the InPort buffer
     *
     * Set the callback object that is invoked when data is written into 
     * the InPort's buffer. The return value of the callback object is set to
     * the buffer.
     * 
     * @param on_wconvert OnWriteConvert&lt;DataType&gt; type object
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
     * @brief InPort バッファへデータ読み込み時のコールバックの設定
     *
     * InPort が持つバッファからデータが読み込まれる直前に呼ばれるコールバック
     * オブジェクトを設定する。
     * 
     * @param on_read OnRead&lt;DataType&gt;型のオブジェクト
     *
     * @else
     *
     * @brief Set callback when data is read from the InPort buffer
     *
     * Set the callback object that is invoked right before data is read from 
     * the InPort's buffer
     * 
     * @param on_read OnRead&lt;DataType&gt; type object
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
     * @brief InPort バッファへデータ読み出し時のコールバックの設定
     *
     * InPort が持つバッファからデータが読み出される際に呼ばれるコールバック
     * オブジェクトを設定する。コールバックオブジェクトの戻り値がread()メソッド
     * の呼出結果となる。
     * 
     * @param on_rconvert OnReadConvert&lt;DataType&gt;型のオブジェクト
     *
     * @else
     *
     * @brief Set callback when data is readout to the InPort buffer
     *
     * Set the callback object that is invoked when data is readout to
     * the InPort's buffer. The return value of callback object is the return
     * result of the read() method.
     * 
     * @param on_rconvert OnReadConvert&lt;DataType&gt; type object
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
     * @brief InPort バッファへバッファオーバーフロー時のコールバックの設定
     *
     * InPort が持つバッファでバッファオーバーフローが検出された際に呼び出される
     * コールバックオブジェクトを設定する。
     * 
     * @param on_overflow OnOverflow&lt;DataType&gt;型のオブジェクト
     *
     * @else
     *
     * @brief Set callback when the InPort buffer occurs overflow
     *
     * Set the callback object that is invoked when the buffer overflow was
     * detected in the InPort's buffer.
     * 
     * @param on_overflow OnOverflow&lt;DataType&gt; type object
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
     * @brief InPort バッファへバッファアンダーフロー時のコールバックの設定
     *
     * InPort が持つバッファでバッファアンダーフローが検出された際に呼び出される
     * コールバックオブジェクトを設定する。
     * 
     * @param on_underflow OnUnderflow&lt;DataType&gt;型のオブジェクト
     *
     * @else
     *
     * @brief Set callback when the InPort buffer occurs underflow.
     *
     * Set the callback object that is invoked when the buffer underflow was
     * detected in the InPort's buffer.
     * 
     * @param on_underflow OnUnderflow&lt;DataType&gt; type object
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
     * @brief ポート名
     * @else
     * @berif Port's name
     * @endif
     */
    std::string m_name;
    
    /*!
     * @if jp
     * @brief バインドされる T 型の変数への参照
     * @else
     * @brief The reference to type-T value bound this OutPort
     * @endif
     */
    DataType& m_value;
    
    /*!
     * @if jp
     * @brief バッファ
     * @else
     * @brief Buffer
     * @endif
     */
    //    Buffer<DataType> m_buffer;
    
    bool m_readBlock;
    long int m_readTimeout;
    bool m_writeBlock;
    long int m_writeTimeout;
    
    /*!
     * @if jp
     * @brief OnWrite コールバックファンクタへのポインタ
     * @else
     * @brief Pointer to OnWrite callback functor
     * @endif
     */
    OnWrite<DataType>* m_OnWrite;
    
    /*!
     * @if jp
     * @brief OnWriteConvert コールバックファンクタへのポインタ
     * @else
     * @brief Pointer to OnWriteConvert callback functor
     * @endif
     */
    OnWriteConvert<DataType>* m_OnWriteConvert;
    
    /*!
     * @if jp
     * @brief OnRead コールバックファンクタへのポインタ
     * @else
     * @brief Pointer to OnRead callback functor
     * @endif
     */
    OnRead<DataType>* m_OnRead;
    
    /*!
     * @if jp
     * @brief OnReadConvert コールバックファンクタへのポインタ
     * @else
     * @brief Pointer to OnReadConvert callback functor
     * @endif
     */
    OnReadConvert<DataType>* m_OnReadConvert;
    
    /*!
     * @if jp
     * @brief OnOverflow コールバックファンクタへのポインタ
     * @else
     * @brief Pointer to OnOverflow callback functor
     * @endif
     */
    OnOverflow<DataType>* m_OnOverflow;
    
    /*!
     * @if jp
     * @brief OnUnderflow コールバックファンクタへのポインタ
     * @else
     * @brief Pointer to OnUnderflow callback functor
     *
     * @endif
     */
    OnUnderflow<DataType>* m_OnUnderflow;
  };
}; // End of namesepace RTM

#endif // RtcInPort_h
