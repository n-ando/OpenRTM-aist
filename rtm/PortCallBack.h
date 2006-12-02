// -*- C++ -*-
/*!
 * @file PortCallBack.h
 * @brief PortCallBack class
 * @date $Date: 2006-12-02 18:51:18 $
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
 * $Id: PortCallBack.h,v 1.1 2006-12-02 18:51:18 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
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
   * DataPortのバッファにデータがwrite()される時に
   * このコールバックが呼ばれる。
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
    virtual void operator()(const DataType& value) = 0;
  };
  
  /*!
   * @if jp
   * @class OnWriteConvert
   * @brief write() 時のデータ変換コールバック抽象クラス
   *
   * InPortのバッファにデータが write()される時にこのコールバックが呼ばれ、
   * このコールバックの戻り値がバッファに格納される。
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
    virtual DataType operator()(const DataType& value) = 0;
  };
  
  /*!
   * @if jp
   * @class OnRead
   * @brief read() 時のコールバック抽象クラス
   *
   * DataPortのバッファからデータがread()される時に
   * このコールバックが呼ばれる。
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
    virtual void operator()() = 0;
  };
  
  /*!
   * @if jp
   * @class OnReadConvert
   * @brief read() 時のデータ変換コールバック抽象クラス
   *
   * InPortのバッファからデータが read()される時にこのコールバックが呼ばれ、
   * このコールバックの戻り値がread()の戻り値となる。
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
    virtual DataType operator()(const DataType& value) = 0;
  };
  
  /*!
   * @if jp
   * @class OnOverflow
   * @brief バッファオーバーフロー時のコールバック抽象クラス
   *
   * バッファにデータがput()される時、バッファオーバーフローが
   * 生じた場合にこのコールバックが呼ばれる。
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
    virtual void operator()(const DataType& value) = 0;
  };
  
  /*!
   * @if jp
   * @class OnUnderflow
   * @brief Underflow 時のコールバック抽象クラス
   *
   * InPortのバッファにデータがput()される時にこのコールバックが呼ばれる。
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
    virtual DataType operator()() = 0;
  };
  
};
#endif // PortCallBack_h
