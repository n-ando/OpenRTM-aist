// -*- C++ -*-
/*!
 * @file TimeValue.h
 * @brief TimeValue class
 * @date $Date: 2007-10-06 12:27:35 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2007-2008
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: TimeValue.h,v 1.1.2.3 2007-10-06 12:27:35 n-ando Exp $
 *
 */

#ifndef TimeValue_h
#define TimeValue_h

#include <iostream>
#include <ace/OS_NS_time.h>

#define TIMEVALUE_ONE_SECOND_IN_USECS 1000000 // 1 [sec] = 1000000 [usec]


/*!
 * @if jp
 * @class TimeValue
 * @brief 時間計算用クラス
 * 
 * 指定した時間値を保持するためのクラス。
 * 時間値に対する各種計算用オペレーションを提供する。
 *
 * @since 0.4.0
 *
 * @else
 * @class TimeValue
 * @brief Class for time calculation
 * 
 * This is a class to hold the specified time value.
 * This class provides the operations for various calculations of 
 * the time value.
 *
 * @since 0.4.0
 *
 * @endif
 */
struct TimeValue
  : public timeval
{
  /*!
   * @if jp
   *
   * @brief コンストラクタ
   * 
   * コンストラクタ
   * 指定された秒，マイクロ秒で初期化する。
   *
   * @param sec 秒(デフォルト値:ゼロ)
   * @param usec マイクロ秒(デフォルト値:ゼロ)
   * 
   * @else
   *
   * @brief Constructor
   * 
   * Constructor
   * Initialize with the specified second and micro second.
   *
   * @param sec Second(The default value:0)
   * @param usec Micro second(The default value:0)
   * 
   * @endif
   */
  TimeValue(long sec=0, long usec=0)
  {
    tv_sec = sec;
    tv_usec = usec;
    normalize();
  }
  
  /*!
   * @if jp
   *
   * @brief 時間減算
   * 
   * 設定された時間から引数で与えられた時間を減算する。
   *
   * @param tm 減算時間
   * 
   * @return 減算結果
   * 
   * @else
   *
   * @brief Time subtraction
   * 
   * Subtract the time given by the argument from the set time.
   *
   * @param tm Subtracted time
   * 
   * @return Subtraction result
   * 
   
   * @endif
   */
  TimeValue operator-(TimeValue& tm)
  {
    TimeValue res;
    if (tv_sec >= tm.tv_sec) // +
      {
	if (tv_usec >= tm.tv_usec) // 繰り下がり無し
	  {
	    res.tv_sec  = tv_sec  - tm.tv_sec;  // -
	    res.tv_usec = tv_usec - tm.tv_usec; // +
	  }
	else // tv_usec < tm.tv_usec 繰り下がり有り
	  {
	    res.tv_sec  = tv_sec  - tm.tv_sec - 1;
	    res.tv_usec = (tv_usec + 1000000) - tm.tv_usec;
	  }
      }
    else // tv_sec < tm.tv_sec // -
      {
	if (tm.tv_usec >= tv_usec) // 繰り下がり無し
	  {
	    res.tv_sec  = - (tm.tv_sec  - tv_sec); // +
	    res.tv_usec = - (tm.tv_usec - tv_usec);  // +
	  }
	else // tm.tv_usec < tv_usec 繰り下がり有り
	  {
	    res.tv_sec  = - (tm.tv_sec - tv_sec  - 1);
	    res.tv_usec = - (tm.tv_usec + 1000000) + tv_usec;
	  }
      }
    res.normalize();
    return res;
  }
  
  /*!
   * @if jp
   *
   * @brief 時間加算
   * 
   * 設定された時間に引数で与えられた時間を加算する。
   *
   * @param tm 加算時間
   * 
   * @return 加算結果
   * 
   * @else
   *
   * @brief Time addition
   * 
   * Add the time given by the argument to the set time.
   *
   * @param tm Added time
   * 
   * @return Addition result
   * 
   * @endif
   */
  TimeValue operator+(TimeValue& tm)
  {
    TimeValue res;
    res.tv_sec  = tv_sec  + tm.tv_sec;
    res.tv_usec = tv_usec + tm.tv_usec;
    if (res.tv_usec >= 1000000)
      {
	++res.tv_sec;
	res.tv_usec -= 1000000;
      }
    res.normalize();
    return res;
  }
  
  /*!
   * @if jp
   *
   * @brief double型→時間型変換
   * 
   * 引数で与えられたdouble型を時間型に変換する。
   *
   * @param time 変換元値
   * 
   * @return 変換結果
   * 
   * @else
   *
   * @brief Convert double type into time type
   * 
   * Convert double type given by the argument into time type.
   *
   * @param time the original value
   * 
   * @return Conversion result
   * 
   * @endif
   */
  TimeValue operator=(double time)
  {
    tv_sec = (long)time;
    tv_usec = (long)((time - (double)tv_sec)*1000000.0 + 0.5);
    normalize();
    return *this;
  }
  
  /*!
   * @if jp
   *
   * @brief 時間型→double型変換
   * 
   * 保持している内容をdouble型に変換する。
   *
   * @return double型変換結果
   * 
   * @else
   *
   * @brief Convert time type into double type
   * 
   * Convert held information into double type.
   *
   * @return Result for conversion of double type
   * 
   * @endif
   */
  double toDouble()
  {
    normalize();
    return (double)tv_sec + ((double)tv_usec/1000000.0);
  }
  
  /*!
   * @if jp
   * 
   * @brief 符号判定
   * 
   * 保持している内容の符号を判定する。
   * 
   * @return 正ならば1を、負ならば-1を、0ならば0
   * 
   * @else
   *  
   * @brief Sign judgment
   * 
   * Judge sign of the held contents
   * 
   * @return 1 if the return value is Plus sign, -1 if Minus, and 0 if 0.
   * 
   * @endif
   */
  int sign()
  {
    if (tv_sec > 0) return 1;
    if (tv_sec < 0) return -1;
    if (tv_usec > 0) return 1;
    if (tv_usec < 0) return -1;
    return 0;
  }
  
private:
  
  /*!
   * @if jp
   * 
   * @brief 正規化
   * 
   * 値の表現を正準形式に正規化する。
   * 
   * @else
   * 
   * @brief Normalize
   * 
   * Normalize the value expression into a canonical form.
   * 
   * @endif
   */
  void normalize()
  {
    if (tv_usec >= TIMEVALUE_ONE_SECOND_IN_USECS)
      {
	do
	  {
	    ++tv_sec;
	    tv_usec -= TIMEVALUE_ONE_SECOND_IN_USECS;
	  }
	while (tv_usec >= TIMEVALUE_ONE_SECOND_IN_USECS);
      }
    else if (tv_usec <= -TIMEVALUE_ONE_SECOND_IN_USECS)
      {
	do
	  {
	    --tv_sec;
	    tv_usec += TIMEVALUE_ONE_SECOND_IN_USECS;
	  }
	while (tv_usec <= -TIMEVALUE_ONE_SECOND_IN_USECS);
      }
    
    if (tv_sec >= 1 && tv_usec < 0)
      {
	--tv_sec;
	tv_usec += TIMEVALUE_ONE_SECOND_IN_USECS;
      }
    else if (tv_sec < 0 && tv_usec > 0)
      {
	++tv_sec;
	tv_usec -= TIMEVALUE_ONE_SECOND_IN_USECS;
      }
  }
  
  //  friend std::ostream& operator<<(std::ostream& lhs, const TimeValue& rhs);
};

/***
    std::ostream& operator<<(std::ostream& lhs, const TimeValue& rhs)
    {
    double res;
    res = (double)rhs.tv_sec + ((double)rhs.tv_usec/1000000.0);
    lhs << res;
    return lhs;
    }
*/

#endif // TimeValue_h
