// -*- C++ -*-
/*!
 * @file DirectOutPortBase.h
 * @brief DirectOutPortBase class
 * @date $Date: 2018-1-23 03:08:05 $
 * @author Nobuhiko Miyamoto <n-miyamoto@aist.go.jp>
 *
 * Copyright (C) 2018
 *     Nobuhiko Miyamoto
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 *
 */

#ifndef RTC_DIRECTOUTPORTBASE_H
#define RTC_DIRECTOUTPORTBASE_H


#include <coil/Mutex.h>
#include <rtm/DirectPortBase.h>




namespace RTC
{
  /*!
   * @if jp
   * @class DirectOutPortBase
   * @brief direct接続用OutPort基底クラス
   *
   *
   * @since 1.2.0
   *
   * @else
   * @class DirectOutPortBase
   * @brief 
   *
   * 
   *
   * @since 1.2.0
   *
   * @endif
   */
  template <class DataType>
  class DirectOutPortBase : public DirectPortBase
  {
	  typedef coil::Guard<coil::Mutex> Guard;
  public:
	/*!
     * @if jp
     * @brief コンストラクタ
     *
     * @param value
     *
     * @else
     * @brief Constructor
     *
     * @param value
     *
     * @endif
     */
	DirectOutPortBase(DataType& value)
	{
	}
	/*!
	* @if jp
	* @brief デストラクタ
	*
	*
	* @else
	* @brief Destructor
	*
	*
	* @endif
	*/
	virtual ~DirectOutPortBase(void)
	{
	}
	/*!
	* @if jp
	* @brief データの取得
	* 
	* @param data データを格納する変数
	*
	* @else
	* @brief 
	*
	* @param data
	*
	* @endif
	*/
	virtual void read(DataType& data)
	{
	}
	/*!
	* @if jp
	* @brief 新規データの存在確認
	*
	* @return true：新規データあり
	*
	* @else
	* @brief
	*
	* @return
	*
	* @endif
	*/
	virtual bool isNew()
	{
		return false;
	}
	/*!
	* @if jp
	* @brief 新規データが無いことを確認
	*
	* @return true：新規データなし
	*
	* @else
	* @brief
	*
	* @return
	*
	* @endif
	*/
	virtual bool isEmpty()
	{
		return true;
	}
    
  protected:
  };
}; // namespace RTC

#endif // RTC_DIRECTOUTPORTBASE_H
