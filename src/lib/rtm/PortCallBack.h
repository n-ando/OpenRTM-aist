// -*- C++ -*-
/*!
 * @file PortCallBack.h
 * @brief PortCallBack class
 * @date $Date: 2007-12-31 03:08:05 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006-2008
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

#ifndef PortCallBack_h
#define PortCallBack_h

namespace RTC
{
  //============================================================
  // callback functor base classes
  /*!
   * @if jp
   * @class OnWrite
   * @brief write() 時のコールバック抽象クラス
   *
   * DataPortのバッファにデータがwrite()される直前に呼び出されるコールバック用
   * インターフェース。
   *
   * @param DataType バッファに書き込むデータ型
   *
   * @since 0.4.0
   *
   * @else
   * @class OnWrite
   * @brief Callback abstract class on write()
   *
   * This is the interface for callback invoked immediately before
   * data is done write() into the DataPort's buffer.
   *
   * @param DataType Data type to write into the buffer
   *
   * @since 0.4.0
   *
   * @endif
   */
  template <class DataType>
  struct OnWrite
  {
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
    virtual ~OnWrite(){}
    
    /*!
     * @if jp
     *
     * @brief コールバックメソッド
     *
     * バッファにデータが書き込まれる直前に呼び出されるコールバックメソッド
     *
     * @param value バッファに書き込まれるデータ
     *
     * @else
     *
     * @brief Callback method
     *
     * This is the callback method invoked immediately before data is written
     * into the buffer.
     *
     * @param value Data that is written into the buffer
     *
     * @endif
     */
    virtual void operator()(const DataType& value) = 0;
  };
  
  /*!
   * @if jp
   * @class OnWriteConvert
   * @brief write() 時のデータ変換コールバック抽象クラス
   *
   * InPort/OutPortのバッファにデータが write()される時に呼び出される
   * コールバック用インターフェース。
   * このコールバックの戻り値がバッファに格納される。
   *
   * @since 0.4.0
   *
   * @else
   * @class OnWriteConvert
   * @brief Data convert callback abstract class on write()
   *
   * This is the interface for callback invoked when data is done write()
   * into the InPort/OutPort's buffer.
   * The return value of this callback will be stored in the buffer.
   *
   * @since 0.4.0
   *
   * @endif
   */
  template <class DataType>
  struct OnWriteConvert
  {
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
    virtual ~OnWriteConvert(){}
    
    /*!
     * @if jp
     *
     * @brief コールバックメソッド
     *
     * バッファにデータが書き込まれる際に呼び出されるコールバックメソッド
     *
     * @param value 変換前データ
     *
     * @return 変換後データ
     *
     * @else
     *
     * @brief Callback method
     *
     * This is the callback method invoked when data is written into the
     * buffer.
     *
     * @param value Data before the convert
     *
     * @return Data after the convert
     *
     * @endif
     */
    virtual DataType operator()(const DataType& value) = 0;
  };
  
  /*!
   * @if jp
   * @class OnRead
   * @brief read() 時のコールバック抽象クラス
   *
   * InPort/OutPortのバッファからデータが read()される直線に呼び出される
   * コールバック用インターフェース。
   *
   * @since 0.4.0
   *
   * @else
   * @class OnRead
   * @brief Callback abstract class on read()
   *
   * This is the interface for callback invoked immediately before
   * data is done read() from the InPort/OutPort's buffer.
   *
   * @since 0.4.0
   *
   * @endif
   */
  template <class DataType>
  struct OnRead
  {
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
    virtual ~OnRead(){}
    
    /*!
     * @if jp
     *
     * @brief コールバックメソッド
     *
     * バッファからデータが読み出される直前に呼び出されるコールバックメソッド
     *
     * @else
     *
     * @brief Callback method
     *
     * This is the callback method invoked immediately before data is readout
     * from the buffer.
     *
     * @endif
     */
    virtual void operator()() = 0;
  };
  
  /*!
   * @if jp
   * @class OnReadConvert
   * @brief read() 時のデータ変換コールバック抽象クラス
   *
   * InPort/OutPortのバッファからデータが read()される際に呼び出される
   * コールバック用インターフェース。
   * このコールバックの戻り値がread()の戻り値となる。
   *
   * @since 0.4.0
   *
   * @else
   * @class OnReadConvert
   * @brief Data convert callback abstract class on read()
   *
   * This is the interface for callback invoked when data is done read()
   * from the InPort/OutPort's buffer.
   * The return value of this callback will be the return value of read().
   *
   * @since 0.4.0
   *
   * @endif
   */
  template <class DataType>
  struct OnReadConvert
  {
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
    virtual ~OnReadConvert(){}
    
    /*!
     * @if jp
     *
     * @brief コールバックメソッド
     *
     * バッファからデータが読み出される際に呼び出されるコールバックメソッド
     *
     * @else
     *
     * @brief Callback method
     *
     * This is the callback method invoked when data is readout from the
     * buffer.
     *
     * @endif
     */
    virtual DataType operator()(const DataType& value) = 0;
  };
  
  /*!
   * @if jp
   * @class OnOverflow
   * @brief バッファオーバーフロー時のコールバック抽象クラス
   *
   * InPort/OutPortのバッファにデータがput()される時、バッファオーバーフローが
   * 生じた場合に呼ばれるコールバックメソッド。
   *
   * @since 0.4.0
   *
   * @else
   * @class OnOverflow
   * @brief Callback abstract class when the buffer overflow occurs
   *
   * This is the callback method invoked when data is done put()
   * into the InPort/OutPort's buffer or when the buffer overflow occurs.
   *
   * @since 0.4.0
   *
   * @endif
   */
  template <class DataType>
  struct OnOverflow
  {
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
    virtual ~OnOverflow(){}
    
    /*!
     * @if jp
     *
     * @brief コールバックメソッド
     *
     * バッファオーバーフロー時に呼び出されるコールバックメソッド
     *
     * @param value バッファへ書き込むデータ
     *
     * @else
     *
     * @brief Callback method
     *
     * This is the callback method invoked when the buffer overflow occurs.
     *
     * @param value Data that is written into the buffer
     *
     * @endif
     */
    virtual void operator()(const DataType& value) = 0;
  };
  
  /*!
   * @if jp
   * @class OnUnderflow
   * @brief Underflow 時のコールバック抽象クラス
   *
   * @since 0.4.0
   *
   * InPort/OutPortのバッファにデータがread()される時に、読み出すべきデータが
   * ない場合に呼び出されるコールバックインタフェース。
   * このコールバックの戻り値がread()の戻り値となる。
   *
   * @else
   * @class OnUnderflow
   * @brief Callback abstract class on underflow
   *
   * @since 0.4.0
   *
   * This is the interface for callback invoked when data is done read()
   * into the InPort/OutPort's buffer and the readout data does not exist.
   * The return value of this callback will be the return value of read().
   *
   * @endif
   */
  template <class DataType>
  struct OnUnderflow
  {
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
    virtual ~OnUnderflow(){}
    
    /*!
     * @if jp
     *
     * @brief コールバックメソッド
     *
     * バッファアンダーフロー時に呼び出されるコールバックメソッド
     *
     * @return 代替となる読み出しデータ
     *
     * @else
     *
     * @brief Callback method
     *
     * This is the callback method invoked when the buffer underflow occurs.
     *
     * @return Substituted readout data
     *
     * @endif
     */
    virtual DataType operator()() = 0;
  };
  
  /*!
   * @if jp
   * @class OnWriteTimeout
   * @brief タイムアウト時のコールバック抽象クラス
   *
   * InPort/OutPortのバッファにデータをwrite()する際に、タイムアウトが発生した
   * 時に呼び出されるコールバックインタフェース。
   *
   * @since 0.4.0
   *
   * @else
   * @class OnWriteTimeout
   * @brief Callback abstract class on timeout
   *
   * This is the interface for callback invoked when data is done write()
   * into the InPort/OutPort's buffer and the timeout occurred.
   *
   * @since 0.4.0
   *
   * @endif
   */
  template <class DataType>
  struct OnWriteTimeout
  {
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
    virtual ~OnWriteTimeout(){}
    
    /*!
     * @if jp
     *
     * @brief コールバックメソッド
     *
     * タイムアウト発生時に呼び出されるコールバックメソッド
     *
     * @param value バッファへ書き込むデータ
     *
     * @else
     *
     * @brief Callback method
     *
     * This is the callback method invoked when the timeout occurs.
     *
     * @param value Data that is written into the buffer
     *
     * @endif
     */
    virtual void operator()(const DataType& value) = 0;
  };
  
  /*!
   * @if jp
   * @class OnReadTimeout
   * @brief タイムアウト時のコールバック抽象クラス
   *
   * InPort/OutPortのバッファにデータをread()する際に、タイムアウトが発生した
   * 時に呼び出されるコールバックインタフェース。
   *
   * @since 0.4.0
   *
   * @else
   * @class OnReadTimeout
   * @brief OnReadTimeout abstract class
   *
   * This is the interface for callback invoked when data is done read()
   * into the InPort/OutPort's buffer and the timeout occurred.
   *
   * @since 0.4.0
   *
   * @endif
   */
  template <class DataType>
  struct OnReadTimeout
  {
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
    virtual ~OnReadTimeout(){}
    
    /*!
     * @if jp
     *
     * @brief コールバックメソッド
     *
     * タイムアウト発生時に呼び出されるコールバックメソッド
     *
     * @return 代替となる読み出しデータ
     *
     * @else
     *
     * @brief Callback method
     *
     * This is the callback method invoked when the timeout occurs.
     *
     * @return Substituted readout data
     *
     * @endif
     */
    virtual DataType operator()() = 0;
  };

  class PublisherBase;
  class OnConnect
  {
    virtual ~OnConnect(){}
    virtual void operator()(const char* id, PublisherBase* publisher) = 0;
  };

  class OnDisconnect
  {
    virtual ~OnDisconnect(){}
    virtual void operator()(const char* id) = 0;
  };


};
#endif // PortCallBack_h
