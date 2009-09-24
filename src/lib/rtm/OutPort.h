// -*- C++ -*-
/*!
 * @file OutPort.h
 * @brief OutPort class
 * @date $Date: 2007-12-31 03:08:05 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006-2009
 *     Noriaki Ando
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id$
 *
 */

#ifndef OutPort_h
#define OutPort_h

#include <iostream>
#include <string>

#include <coil/TimeValue.h>
#include <coil/Time.h>
#include <coil/TimeMeasure.h>
#include <coil/OS.h>

#include <rtm/RTC.h>
#include <rtm/Typename.h>
#include <rtm/OutPortBase.h>
#include <rtm/CdrBufferBase.h>
#include <rtm/PortCallBack.h>
#include <rtm/OutPortConnector.h>

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
   * 扱うデータ型 DataType をとる。
   *
   *
   *
   * OnWrite系コールバック (書込みに起因するイベントによりコールされる)
   *
   * - void OnWrite<DataType>::operator()(const DataType): 
   *     OutPort::write() を呼び出し書き込みを行う際にコールされる。
   *
   * - DataType OnWriteConvert<DataType>::operator()(const DataType): 
   *     OutPort::write() を呼び出し、データをバッファに書き込む前に呼ばれ
   *     データの変換を行う。operator()()の戻り値がシリアライズされバッファに
   *     書き込まれる。
   *
   *
   * OnBuffer系コールバック (バッファに起因するイベントによりコールされる)
   *
   * 2種類のコールバックファンクタのシグニチャ
   * BufferCallback::operator()(ConnectorId, cdrStream)
   * BufferReadCallback::operator()(ConnectorId)
   *
   * - void OnBufferWrite::operator()(ConnectorId, cdrStream):
   *     BufferBase::write() コール時に単純に呼び出されるコールバック。
   *     引数にはwrite()されるシリアライズ済みのデータが与えられる。        
   *   
   * - void OnBufferFull::operator()(ConnectorId, cdrStream):
   *     BufferBase::write() コール時に、バッファがいっぱいの場合に
   *     呼び出されるコールバック。コネクタのIDおよび書き込めなかったデータ
   *     が引数に与えられる。
   *
   * - void OnBufferWriteTimeout::operator()(ConnectorId, cdrStream):
   *     ConnectorBase::write() コール時に、バッファがいっぱいで書込みが
   *     タイムアウトした場合に呼び出されるコールバック。コネクタのID
   *     および書き込めなかったデータが引数に与えられる。
   *
   * - void OnBufferOverwrite::operator()(ConnectorId, cdrStream):
   *     BufferBase::write() コール時に、バッファが上書きモードに設定
   *     されており、バッファがいっぱいの場合に呼び出されるコールバック。
   *     コネクタのIDが引数に与えられる。
   *
   *
   * - void OnBufferRead::operator()(ConnectorId, cdrStream):
   *     BufferBase::read() コール時に単純に呼び出されるコールバック。
   *     引数には read() で返されるシリアライズ済みのデータが与えられる。
   *
   * - void OnBufferEmpty::operator()(ConnectorId): 
   *     コネクタがバッファを読みだす際に、バッファが空の場合に呼び出される。
   *     コネクタのIDが引数に与えられる。
   *
   * - void OnBufferReadTimeout::operator()(ConnectorId):
   *     コネクタがバッファを読みだす際に、バッファが空でかつ、読み出しが
   *     タイムアウトした場合に呼び出されるコールバック。コネクタのID
   *     が引数に与えられる。
   *
   *
   * OnConnect系コールバック (接続に起因するイベントによりコールされる)
   *
   * 2種類のコールバックファンクタのシグニチャ
   * ConnectCallback::operator()(ConnectorProfile)
   * DisconnectCallback::operator()(ConnectorId)
   * 
   * - void OnConnect::operator()(ConnectorProfile):
   *     ポートの接続時に呼び出されるコールバック。引数にConnectorProfile
   *     が与えられる。
   *
   * - void OnDisconnect::operator()(ConnectorId):
   *     ポートの接続切断時に呼び出されるコールバック。引数にコネクタID
   *     が与えられる。  
   *
   * - void OnConnectionLost::operator()(ConnectorId):
   *     ポートの接続がロストした場合に呼び出されるコールバック。
   *     引数にコネクタIDが与えられる。OutPortは、相手側InPortとの
   *     接続をロストした場合、接続を強制的に切断するので、
   *     引き続き OnDisconnect コールバックが呼び出される。
   *

   *
   *
   * - void OnSend:operator()(ConnectorId, cdrStream):
   *     データがInPortに対して送られる際に呼び出されるコールバック。
   *     引数にコネクタIDが与えられる。
   *
   * - void OnReceived::operator()(ConnectorId, cdrStream):
   *     データの送信および受信が完了した際に呼び出されるコールバック。
   *     引数には、コネクタIDが与えられる。
   *

   *
   *
   * OnSender系コールバック (送信側に起因するイベントによりコールされる)
   *   以下は、パブリッシャが存在する接続、すなわち dataflow type = push 
   *   のときのみ有効。
   *
   * - void OnSenderTimeout::operator()(ConnectorId, cdrStream):
   *     データがInPortに対して送られたが、送信がタイムアウトした際に
   *     呼び出されるコールバック。引数にコネクタIDが与えられる。
   *     InPortのプロバイダおよびコンシューマが対応している場合に限り有効。
   *
   * - void OnSenderError::operator()(ConnectorId, cdrStream):
   *     データがInPortに対して送られたが、何らかのエラーをInPort側が
   *     返した場合に呼び出されるコールバック。
   *     引数には、コネクタIDが与えられる。
   *
   *
   * OnReceiver系コールバック (受信側に起因するイベントによりコールされる)
   *   以下は、パブリッシャが存在する接続、すなわち dataflow type = push 
   *   のときのみ有効。
   * 
   * - void OnReceiverFull::operator()(ConnectorId, cdrStream):
   *     データがInPortに送られるものの、InPort側のバッファがいっぱいの場合に
   *     これを通知するために呼ばれるコールバック。
   *     引数には、コネクタIDが与えられる。
   *
   * - void OnReceiverTimeout::operator()(ConnectorId, cdrStream):
   *     データがInPortに送られるものの、InPort側のバッファがいっぱいで
   *     タイムアウトした場合にこれを通知するために呼ばれるコールバック。
   *     引数には、コネクタIDが与えられる。
   *
   * - void OnReceiverError::operator()(ConnectorId, cdrStream):
   *     データがInPortに送られるものの、InPort側で何らかのエラーを返した
   *     場合に呼び出されるコールバック。
   *     引数には、コネクタIDが与えられる。
   *
   *
   *
   *
   *
   * @since 0.2.0
   *
   * @else
   *
   * @brief OutPort template class
   * 
   * This is the OutPort template class. 
   * The data type "DateType" supported by OutPort and the buffer type
   * "BufferType" are used as template arguments.
   *
   * @since 0.2.0
   *
   * @endif
   */
  template <class DataType>
  class OutPort
    : public OutPortBase
  {
  public:
    /*!
     * @if jp
     *
     * @brief コンストラクタ
     *
     * コンストラクタ
     *
     * @param name ポート名
     * @param value このポートにバインドされるデータ変数
     * @param length バッファ長(デフォルト値:8)
     *
     * @else
     *
     * @brief Constructor
     *
     * Constructor
     *
     * @param name Port's name
     * @param value Data variable bound to this port
     * @param length Buffer length (The default value:8)
     *
     * @endif
     */
    OutPort(const char* name, DataType& value)
      : OutPortBase(name, toTypename<DataType>()), m_value(value),
        //	m_timeoutTick(1000), // timeout tick: 1ms
        //	m_readBlock(false), m_readTimeout(0),
        //	m_writeBlock(false), m_writeTimeout(0),
	m_onWrite(0), m_onWriteConvert(0)
        //	m_OnRead(NULL),  m_OnReadConvert(NULL),
        //	m_OnOverflow(NULL), m_OnUnderflow(NULL)
    {
    }
    
    /*!
     * @if jp
     *
     * @brief デストラクタ
     * 
     * デストラクタ
     * 
     * @else
     *
     * @brief Destructor
     * 
     * Destructor
     * 
     * @endif
     */
    virtual ~OutPort(void)
    {
    }
    
    /*!
     * @if jp
     *
     * @brief データ書き込み
     *
     * ポートへデータを書き込む。
     *
     * - コールバックファンクタ OnWrite がセットされている場合、
     *   OutPort が保持するバッファに書き込む前に OnWrite が呼ばれる。
     * - OutPort が保持するバッファがオーバーフローを検出できるバッファであり、
     *   かつ、書き込む際にバッファがオーバーフローを検出した場合、
     *   コールバックファンクタ OnOverflow が呼ばれる。
     * - コールバックファンクタ OnWriteConvert がセットされている場合、
     *   バッファ書き込み時に、 OnWriteConvert の operator() の戻り値が
     *   バッファに書き込まれる。
     *
     * @param value 書き込み対象データ
     *
     * @return 書き込み処理結果(書き込み成功:true、書き込み失敗:false)
     *
     * @else
     *
     * @brief Write data
     *
     * Write data in the port.
     *
     * - When callback functor OnWrite is already set, OnWrite will be
     *   invoked before writing into the buffer held by OutPort.
     * - When the buffer held by OutPort can detect the overflow,
     *   and when it detected the overflow at writing, callback functor
     *   OnOverflow will be invoked.
     * - When callback functor OnWriteConvert is already set, 
     *   the return value of operator() of OnWriteConvert will be written
     *   into the buffer at the writing.
     *
     * @param value The target data for writing
     *
     * @return Writing result (Successful:true, Failed:false)
     *
     * @endif
     */
    virtual bool write(DataType& value)
    {
      if (m_onWrite != NULL)
	{
	  (*m_onWrite)(value);
	}

      // check number of connectors
      size_t conn_size(m_connectors.size());
      if (!(conn_size > 0)) { return true; }
        
      // set timestamp
      coil::TimeValue tm(coil::gettimeofday());
      value.tm.sec  = tm.sec();
      value.tm.nsec = tm.usec() * 1000;

      // data -> (conversion) -> CDR stream
      m_cdr.rewindPtrs();
      if (m_onWriteConvert != NULL)
        {
          ((*m_onWriteConvert)(value)) >>= m_cdr;
        }
      else
        {
          value >>= m_cdr;
        }

      bool result(true);
      for (size_t i(0), len(conn_size); i < len; ++i)
        {
          ReturnCode ret;
          ret = m_connectors[i]->write(m_cdr);
          if (ret != PORT_OK)
            {
              result = false;
              if (ret == CONNECTION_LOST)
                {
                  disconnect(m_connectors[i]->id());
                }
            }
        }
      return result;
    }
    
    /*!
     * @if jp
     *
     * @brief データ書き込み
     *
     * ポートへデータを書き込む。
     * バインドされた変数に設定された値をポートに書き込む。
     *
     * @return 書き込み処理結果(書き込み成功:true、書き込み失敗:false)
     *
     * @else
     *
     * @brief Write data
     *
     * Write data to the port.
     * Write the value, which was set to the bound variable, to the port.
     *
     * @return Writing result (Successful:true, Failed:false)
     *
     * @endif
     */
    bool write()
    {
      return write(m_value);
    }
    
    /*!
     * @if jp
     *
     * @brief データ書き込み
     *
     * ポートへデータを書き込む。
     * 設定された値をポートに書き込む。
     *
     * @param value 書き込み対象データ
     *
     * @return 書き込み処理結果(書き込み成功:true、書き込み失敗:false)
     *
     * @else
     *
     * @brief Write data
     *
     * Write data to the port.
     * Write the set value to the port.
     *
     * @param value The target data for writing
     *
     * @return Writing result (Successful:true, Failed:false)
     *
     * @endif
     */
    bool operator<<(DataType& value)
    {
      return write(value);
    }
    
    
    /*!
     * @if jp
     *
     * @brief データ読み出し処理のブロックモードの設定
     *
     * 読み出し処理に対してブロックモードを設定する。
     * ブロックモードを指定した場合、読み出せるデータを受信するかタイムアウト
     * が発生するまで、read() メソッドの呼びだしがブロックされる。
     *
     * @param block ブロックモードフラグ
     *
     * @else
     *
     * @brief Set blocking mode of the data read processing
     *
     * Set the blocking mode for the readout.
     * When the block mode is specified, the invoke of read() method is
     * blocked until the readout data is received or timeout occurs.
     *
     * @param block Flag of blocking mode
     *
     * @endif
     */
//    void setReadBlock(bool block)
//    {
//      m_readBlock = block;
//    }
    
    /*!
     * @if jp
     *
     * @brief データ書き込み処理のブロックモードの設定
     *
     * 書き込み処理に対してブロックモードを設定する。
     * ブロックモードを指定した場合、バッファに書き込む領域ができるか
     * タイムアウトが発生するまで write() メソッドの呼びだしがブロックされる。
     *
     * @param block ブロックモードフラグ
     *
     * @else
     *
     * @brief Set blocking mode of the data writing processing
     *
     * Set the blocking mode for the writing.
     * When the block mode is specified, the invoke of write() method is
     * blocked until the area written into the buffer can be used or timeout
     * occurs.
     *
     * @param block Flag of blocking mode
     *
     * @endif
     */
//    void setWriteBlock(bool block)
//    {
//      m_writeBlock = block;
//    }
    
    /*!
     * @if jp
     *
     * @brief 読み出し処理のタイムアウト時間の設定
     * 
     * read() のタイムアウト時間を usec で設定する。
     * read() はブロックモードでなければならない。
     *
     * @param timeout タイムアウト時間 [usec]
     *
     * @else
     *
     * @brief Set timeout of the data read processing
     * 
     * Set the timeout period of read() with usec.
     * read() must be a block mode.
     *
     * @param timeout Timeout period[usec]
     *
     * @else
     *
     * @endif
     */
//    void setReadTimeout(long int timeout)
//    {
//      m_readTimeout = timeout;
//    }
    
    /*!
     * @if jp
     *
     * @brief 書き込み処理のタイムアウト時間の設定
     * 
     * write() のタイムアウト時間を usec で設定する。
     * write() はブロックモードでなければならない。
     *
     * @param timeout タイムアウト時間 [usec]
     *
     * @else
     *
     * @brief Set timeout of the data writing processing
     * 
     * Set the timeout period of write() with usec.
     * write() must be a block mode.
     *
     * @param timeout Timeout period[usec]
     *
     * @endif
     */
//    void setWriteTimeout(long int timeout)
//    {
//      m_writeTimeout = timeout;
//    }
    
    /*!
     * @if jp
     *
     * @brief OnWrite コールバックの設定
     *
     * write() 呼び出し時に、各コネクタに対してデータを書き込む直前に呼
     * ばれる OnWrite コールバックファンクタを設定する。この関数により
     * 設定されたファンクタオブジェクトの所有権は、呼び出し側が持つ。し
     * たがっ const て、このファンクタオブジェクトの解体責任は呼び出し側にある。
     * ファンクタの設定を解除する場合には引数に 0 を渡すことで、コール
     * バックが無効となる。
     *
     * @param on_write OnWrite コールバックファンクタ
     *
     * @else
     *
     * @brief Set OnWrite callback
     *
     * This operation sets the OnWrite callback functor that is called
     * just before write() operation call.  The ownership of the
     * functor object is owned by caller of this operation.  Therefore
     * caller have to destruct the callback functor object by itself.
     * Giving 0 as an argument for this operation, callback will be
     * disabled.
     *
     * @param on_write OnWrite callback functor
     *
     * @endif
     */
    inline void setOnWrite(OnWrite<DataType>* on_write)
    {
      m_onWrite = on_write;
    }
    
    /*!
     * @if jp
     *
     * @brief OnWriteConvert コールバックの設定
     *
     * write() 呼び出し時に、各コネクタに対してデータを書き込み直前に呼
     * ばれ、データ変換を行う OnWriteConvert コールバックファンクタを設
     * 定する。引数に直近で書き込まれたデータが与えられ、戻り値に実際に
     * コネクタまたはバッファに書き込まれるデータを返すファンクタを設定
     * する。この関数により設定されたファンクタオブジェクトの所有権は、
     * 呼び出し側が持つ。したがっ const て、このファンクタオブジェクト
     * の解体責任は呼び出し側にある。ファンクタの設定を解除する場合には
     * 引数に 0 を渡すことで、コールバックが無効となる。 データ書き込み
     * 時に呼ばれる OnWriteConvert コールバックファンクタを設定する。こ
     * のコールバック関数の処理結果が書き込まれる。このため書き込みデー
     * タのフィルタリングが可能となる。
     *
     * @param on_wconvert OnWriteConvert コールバックファンクタ
     *
     * @else
     *
     * @brief Set OnWriteConvert callback
     *
     * This operation sets the OnWriteConvert callback functor that
     * converts given data and is called just before write() operation
     * call. A recent data is given to argument and return data will
     * be written into connector or its buffer. The ownership of the
     * functor object is owned by caller of this operation.  Therefore
     * caller have to destruct the callback functor object by itself.
     * Giving 0 as an argument for this operation, callback will be
     * disabled.
     *
     * @param on_wconvert OnWriteConvert callback functor
     *
     * @endif
     */
    inline void setOnWriteConvert(OnWriteConvert<DataType>* on_wconvert)
    {
      m_onWriteConvert = on_wconvert;
    }
    
  private:
    std::string m_typename;
    /*!
     * @if jp
     * @brief バインドされる T 型の変数への参照
     * @else
     * @brief The reference to type-T variable that is bound.
     * @endif
     */
    DataType& m_value;
    
    /*!
     * @if jp
     * @brief タイムアウトのポーリング周期 [usec]
     * @else
     * @brief Polling cycle of time-out [usec]
     * @endif
     */
    //    long int m_timeoutTick;
    
    /*!
     * @if jp
     * @brief 読み込み処理時のブロック・非ブロックモードフラグ
     * @else
     * @brief Flag of read()'s blocking/non-blocking mode
     * @endif
     */
    //    bool m_readBlock;
    
    /*!
     * @if jp
     * @brief 読み込み処理のタイムアウト時間 [usec]
     * @else
     * @brief Timeout of read() [usec]
     * @endif
     */
    //    long int m_readTimeout;
    
    /*!
     * @if jp
     * @brief 書き込み処理時のブロック・非ブロックモードフラグ
     * @else
     * @brief Flag of write()'s blocking/non-blocking mode
     * @endif
     */
    //    bool m_writeBlock;
    
    /*!
     * @if jp
     * @brief 書き込み処理のタイムアウト時間 [usec]
     * @else
     * @brief Timeout of write() [usec]
     * @endif
     */
    //    long int m_writeTimeout;
    
    /*!
     * @if jp
     * @brief OnWrite コールバックファンクタへのポインタ
     * @else
     * @brief Pointer to OnWrite callback functor
     * @endif
     */
    OnWrite<DataType>* m_onWrite;
    
    /*!
     * @if jp
     * @brief OnWriteConvert コールバックファンクタへのポインタ
     * @else
     * @brief Pointer to OnWriteConvert callback functor
     * @endif
     */
    OnWriteConvert<DataType>* m_onWriteConvert;


    coil::TimeMeasure m_cdrtime;
    static const long int usec_per_sec = 1000000;
    cdrMemoryStream m_cdr;
  };
}; // namespace RTC

#endif // OutPort_h
