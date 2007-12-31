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
 * $Id: PortCallBack.h,v 1.2.4.2 2007-12-31 03:08:05 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.2.4.1  2007/09/19 07:41:28  n-ando
 * Timeout callbacks were added.
 *
 * Revision 1.2  2007/01/21 12:56:35  n-ando
 * virtual dtors were defined.
 *
 * Revision 1.1  2006/12/02 18:51:18  n-ando
 * The first commitment.
 *
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
   * @class OnPut
   * @brief OnPut abstract class
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
   * @brief OnWriteConvert abstract class
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
   * @brief OnRead abstract class
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
   * @brief OnReadConvert abstract class
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
   * @brief OnOverflow abstract class
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
   * @brief OnUnderflow abstract class
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
   * @brief OnWriteTimeout abstract class
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
     * @endif
     */
    virtual DataType operator()() = 0;
  };
};
#endif // PortCallBack_h
