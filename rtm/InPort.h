// -*- C++ -*-
/*!
 * @file InPort.h
 * @brief InPort template class
 * @date $Date: 2006-12-02 18:37:29 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2003-2005
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: InPort.h,v 1.5 2006-12-02 18:37:29 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.4  2006/11/07 09:26:12  n-ando
 * Renamed RtcInPort.h to InPort.h.
 *
 * Revision 1.3  2005/05/27 07:29:32  n-ando
 * - InPort/OutPort interface was changed.
 *   Exception RTM::InPort::Disconnected -> RTM:PortBase::Disconnected
 *
 * Revision 1.2  2005/05/16 06:12:15  n-ando
 * - Time variables of "m_Value" were initialized in constructors.
 *
 * Revision 1.1.1.1  2005/05/12 09:06:18  n-ando
 * Public release.
 *
 *
 */

#ifndef RtcInPort_h
#define RtcInPort_h

#include <string>
#include <vector>
#include <iostream>
#include <rtm/InPortBase.h>
#include <rtm/BufferBase.h>

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
   * InPort の実装である InPortAny<T> のテンプレートクラス。
   * <T> はRTCDataType.idl にて定義されている型で、メンバとして
   * Time 型の tm , および T型の data を持つ構造体でなくてはならない。
   * InPort は内部にリングバッファを持ち、外部から送信されたデータを順次
   * このリングバッファに格納する。リングバッファのサイズはデフォルトで64と
   * なっているが、コンストラクタ引数によりサイズを指定することができる。
   * データはフラグによって未読、既読状態が管理され、isNew(), getNewDataLen()
   * getNewList(), getNewListReverse() 等のメソッドによりハンドリングすることが
   * できる。
   *
   * @else
   *
   * @class InPortAny
   *
   * @brief OutPort template class
   *
   * This class template provides interfaces to input port.
   * Component developer can define input value, which act as input
   * port from other components, using this template.
   * This is class template. This class have to be incarnated class as port
   * value types. This value types are previously define RtComponent IDL.
   * ex. type T: TimedFload, TimedLong etc... 
   *
   * @endif
   */
  template <class DataType,
	    template <class DataType> class Buffer = NullBuffer >
  class InPort
    : public Buffer<DataType>
  {
  public:
    /*!
     * @if jp
     *
     * @brief InPortAny クラスコンストラクタ
     *
     * InPortAny<T> クラスのコンストラクタ。
     * パラメータとして与えられる T 型の変数にバインドされる。
     *
     * @param name InPort 名。InPortBase:name() により参照される。
     * @param value この InPort にバインドされる T 型の変数
     * @param bufsize InPort 内部のリングバッファのバッファ長
     *
     * @else
     *
     * @brief A constructor.
     *
     * Setting channel name and registering channel value.
     *
     * @param name A name of the InPort. This name is referred by
     *             InPortBase::name().
     * @param value A channel value related with the channel.
     * @param bufsize Buffer length of internal ring buffer of InPort 
     *
     * @endif
     */
    InPort(const char* name, DataType& value,
	   int bufsize=64, 
	   bool read_block = false, bool write_block = false,
	   int read_timeout = 0, int write_timeout = 0)
      : m_name(name), m_value(value),
	m_buffer(bufsize),
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
     * @brief InPortAny クラスデストラクタ
     *
     * InPortAny<T> クラスのデストラクタ。
     *
     * @else
     *
     * @brief A destructor
     *
     * @endif
     */
    virtual ~InPort(){};



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
     *   バッファ書き込み時に、OnWriteConvert の operator()() の戻り値が
     *   バッファに書き込まれる。
     * - setWriteTimeout() により書き込み時のタイムアウトが設定されている場合、
     *   タイムアウト時間だけバッファフル状態が解除するのを待ち、
     *   OnOverflowがセットされていればこれを呼び出して戻る。
     *
     * @else
     *
     * @brief 
     *
     * @endif
     */
    void write(const DataType& value)
    {
      if (m_OnWrite != NULL) (*m_OnWrite)(value);      

      long int timeout = m_writeTimeout;

      timeval tm_cur, tm_pre;
      gettimeofday(&tm_pre, NULL);

      // blocking and timeout wait
      while (m_writeBlock && m_buffer.isFull())
	{
	  if (m_writeTimeout < 0) 
	    {
	      usleep(TIMEOUT_TICK_USEC);
	      continue;
	    }

	  // timeout wait
	  gettimeofday(&tm_cur, NULL);
	  long int sec (tm_cur.tv_sec  - tm_pre.tv_sec);
	  long int usec(tm_cur.tv_usec - tm_pre.tv_usec);

	  timeout -= (sec * USEC_PER_SEC + usec);
	  if (timeout < 0) break;

	  tm_pre = tm_cur;
	  usleep(TIMEOUT_TICK_USEC);
	}

      if (m_buffer.isFull() && m_OnOverflow != NULL)
	{
	  (*m_OnOverflow)(value);
	  return;
	}

      if (m_OnWriteConvert == NULL) 
	{
	  m_buffer.put(value);
	}
      else
	{
	  m_buffer.put((*m_OnWriteConvert)(value));
	}
      return;
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
     *   バッファ書き込み時に、OnReadConvert の operator()() の戻り値が
     *   read()の戻り値となる。
     * - setReadTimeout() により読み出し時のタイムアウトが設定されている場合、
     *   バッファアンダーフロー状態が解除されるまでタイムアウト時間だけ待ち、
     *   OnUnderflowがセットされていればこれを呼び出して戻る
     *
     * @else
     *
     * @brief [CORBA interface] Put data on InPort
     *
     * @endif
     */
    DataType read()
    {
      if (m_OnRead != NULL) (*m_OnRead)();      

      long int timeout = m_readTimeout;

      timeval tm_cur, tm_pre;
      gettimeofday(&tm_pre, NULL);

      // blocking and timeout wait
      while (m_readBlock && m_buffer.isEmpty())
	{
	  if (m_readTimeout < 0)
	    {
	      usleep(TIMEOUT_TICK_USEC);
	      continue;
	    }

	  // timeout wait
	  gettimeofday(&tm_cur, NULL);
	  long int sec (tm_cur.tv_sec  - tm_pre.tv_sec);
	  long int usec(tm_cur.tv_usec - tm_pre.tv_usec);

	  timeout -= (sec * USEC_PER_SEC + usec);
	  if (timeout < 0) break;

	  tm_pre = tm_cur;
	  usleep(TIMEOUT_TICK_USEC);
	}

      if (m_buffer.isEmpty() && m_OnUnderflow != NULL)
	{
	  return (*m_OnUnderflow)();
	}

      if (m_OnReadConvert == NULL) 
	{
	  return m_buffer.get();
	}
      else
	{
	  return (*m_OnReadConvert)(m_buffer.get());
	}
      // never comes here
      return m_value;
    }



    /*!
     * @if jp
     *
     * @brief InPort 内のリングバッファの値を初期化
     *
     * InPort 内のリングバッファの値を初期化する。
     *
     * @else
     *
     * @brief Initialize ring buffer value of InPort
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
     * @brief Read into bound T-type data from current InPort
     *
     * @endif
     */
    void update()
    {
      try
	{
	  m_value = m_buffer->get();
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
     * @param rhs InPort バッファから値を読み込む T 型変数
     *
     * @else
     *
     * @brief Read from InPort buffer to type-T variable
     *
     * @param rhs type-T variable which is wrote from InPort buffer
     *
     * @endif
     */
    void operator>>(DataType& rhs)
    {
      rhs = read();
      return;
    }
    

    void operator<<(DataType& value)
    {
      write(value);
      return;
    }

    /*!
     * @if jp
     *
     * @brief 最新データが未読の新しいデータかどうかを調べる
     *
     * @else
     *
     * @brief Check the newest data is new data to be read.
     *
     * @endif
     */
    bool isNew()
    {
      return m_buffer.isNew();
    }

    bool isFull()
    {
      return m_buffer.isFull();
    }

    bool isEmpty()
    {
      return m_buffer.isEmpty();
    }
    
    
    /*!
     * @if jp
     *
     * @brief 未読の新しいデータ数を取得する
     *
     * @else
     *
     * @brief Get number of new data to be read.
     *
     * @endif
     */
    /*
    virtual int getNewDataLen()
    {
      return m_buffer->new_data_len();
    }
    */    
    
    /*!
     * @if jp
     *
     * @brief 未読の新しいデータを取得する
     *
     * @else
     *
     * @brief Get new data to be read.
     *
     * @endif
     */
    /*
    virtual std::vector<T> getNewList()
    {
      return m_buffer.get_new_list();
    }
    */
    
    /*!
     * @if jp
     *
     * @brief 未読の新しいデータを逆順(新->古)で取得する
     *
     * @else
     *
     * @brief Get new data to be read.
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
     * @brief InPort バッファにデータ入力時のコールバックの設定
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
     * @else
     *
     * @brief Get new data to be read.
     *
     * @endif
     */
    inline void setOnWrite(OnWrite* on_write)
    {
      m_OnWrite = on_write;
    }

    inline void setOnWriteConvert(OnWriteConvert* on_wconvert)
    {
      m_OnWriteConvert = on_wconvert;
    }

    inline void setOnRead(OnRead* on_read)
    {
      m_OnRead = on_read;
    }

    inline void setOnReadConvert(OnReadConvert* on_rconvert)
    {
      m_OnReadConvert = on_rconvert;
    }

    inline void setOnOverflow(OnOverflow* on_overflow)
    {
      m_OnOverflow = on_overflow;
    }

    inline void setOnUnderflow(OnUnderflow* on_underflow)
    {
      m_OnUnderflow = on_underflow;
    }


  private:
    /*!
     * @if jp
     * @brief ポート名
     * @else
     * @berif Port's name
     * @else
     */
    std::string m_name;

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
     * @brief バッファ
     * @else
     * @brief Buffer
     * @endif
     */
    Buffer<DataType> m_buffer;

    bool m_readBlock;
    long int m_readTimeout;
    bool m_writeBlock;
    long int m_writeTimeout;

    /*!
     * @if jp
     * @brief OnWrite コールバックファンクタへのポインタ
     * @else
     * @brief OnWrite callback functor pointer
     * @endif
     */
    OnWrite* m_OnWrite;

    /*!
     * @if jp
     * @brief OnWriteConvert コールバックファンクタへのポインタ
     * @else
     * @brief OnWriteConvert callback functor pointer
     * @endif
     */
    OnWriteConvert* m_OnWriteConvert;

    /*!
     * @if jp
     * @brief OnRead コールバックファンクタへのポインタ
     * @else
     * @brief OnRead callback functor pointer
     * @endif
     */
    OnRead* m_OnRead;

    /*!
     * @if jp
     * @brief OnReadConvert コールバックファンクタへのポインタ
     * @else
     * @brief OnReadConvert callback functor pointer
     * @endif
     */
    OnR    bool m_readBlock;
    long int m_readTimeout;
    bool m_writeBlock;
    long int m_writeTimeout;

    /*!
     * @if jp
     * @brief OnWrite コールバックファンクタへのポインタ
     * @else
     * @brief OnWrite callback functor pointer
     * @endif
     */
    OnWrite* m_OnWrite;

    /*!
     * @if jp
     * @brief OnWriteConvert コールバックファンクタへのポインタ
     * @else
     * @brief OnWriteConvert callback functor pointer
     * @endif
     */
    OnWriteConvert* m_OnWriteConvert;

    /*!
     * @if jp
     * @brief OnRead コールバックファンクタへのポインタ
     * @else
     * @brief OnRead callback functor pointer
     * @endif
     */
    OnRead* m_OnRead;

    /*!
     * @if jp
     * @brief OnReadConvert コールバックファンクタへのポインタ
     * @else
     * @brief OnReadConvert callback functor pointer
     * @endif
     */
    OnReadConvert* m_OnReadConvert;

    /*!
     * @if jp
     * @brief OnOverflow コールバックファンクタへのポインタ
     * @else
     * @brief OnOverflow callback functor pointer
     * @endif
     */
    OnOverflow* m_OnOverflow;

    /*!
     * @if jp
     * @brief OnUnderflow コールバックファンクタへのポインタ
     * @else
     * @brief OnUnderflow callback functor pointer
     *
     * @endif
     */
    OnUnderflow* m_OnUnderflow;

    /*!
     * @if jp
     * @brief OnOverflow コールバックファンクタへのポインタ
     * @else
     * @brief OnOverflow callback functor pointer
     * @endif
     */
    OnOverflow* m_OnOverflow;

    /*!
     * @if jp
     * @brief OnUnderflow コールバックファンクタへのポインタ
     * @else
     * @brief OnUnderflow callback functor pointer
     *
     * @endif
     */
    OnUnderflow* m_OnUnderflow;


    
  };
  
}; // End of namesepace RTM

#endif // RtcInPort_h
