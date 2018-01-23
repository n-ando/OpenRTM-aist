// -*- C++ -*-
/*!
 * @file DirectInPortBase.h
 * @brief DirectInPortBase class
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

#ifndef RTC_DIRECTINPORTBASE_H
#define RTC_DIRECTINPORTBASE_H



#include <coil/Mutex.h>



namespace RTC
{
	/*!
	* @if jp
	* @class DirectInPortBase
	* @brief direct接続用InPort基底クラス
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
  class DirectInPortBase : public DirectPortBase
  {
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
    DirectInPortBase(DataType& value):
        m_directNewData(false), m_value(value)
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
    virtual ~DirectInPortBase(void){};



    
    /*!
     * @if jp
     *
     * @brief 最新データが存在するか確認する
     * 
     * InPortに未読の最新データが到着しているかをbool値で返す。
     * InPortが未接続の場合、および接続コネクタのバッファがEmpty
     * の場合にはfalseを返す。
     *
     * @return true 未読の最新データが存在する
     *         false 未接続またはバッファにデータが存在しない。
     * 
     * @else
     *
     * @brief Check whether the data is newest
     * 
     * Check whether the data stored at a current buffer position is newest.
     *
     * @return Newest data check result
     *         ( true:Newest data. Data has not been readout yet.
     *          false:Past data．Data has already been readout.)
     * 
     * @endif
     */
    virtual bool isNew()
    {
      return m_directNewData;
    }

    /*!
     * @if jp
     *
     * @brief バッファが空かどうか確認する
     * 
     * InPortのバッファが空かどうかを bool 値で返す。
     * 空の場合は true, 未読データがある場合は false を返す。
     *
     * @return true  バッファは空
     *         false バッファに未読データがある
     * 
     * @else
     *
     * @brief Check whether the data is newest
     * 
     * Check whether the data stored at a current buffer position is newest.
     *
     * @return Newest data check result
     *         ( true:Newest data. Data has not been readout yet.
     *          false:Past data．Data has already been readout.)
     * 
     * @endif
     */
    virtual bool isEmpty()
    {
      return !m_directNewData;
    }

	/*!
	* @if jp
	* @brief データの書き込み
	*
	* @param data データ
	*
	* @else
	* @brief
	*
	* @param data
	*
	* @endif
	*/
    virtual void write(const DataType& data)
    {
    }


  protected:
    
    /*!
     * @if jp
     * @brief バインドされる T 型の変数への参照
     * @else
     * @brief The reference to type-T value bound this OutPort
     * @endif
     */
    DataType& m_value;
    mutable coil::Mutex m_valueMutex;
    

    /*!
     * @if jp
     * @brief ダイレクトデータ転送フラグ
     * @else
     * @brief A flag for direct data transfer
     * @endif
     */
    bool m_directNewData;
  };
}; // End of namesepace RTM

#endif // RTC_DIRECTINPORTBASE_H
