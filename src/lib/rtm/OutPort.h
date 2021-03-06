﻿// -*- C++ -*-
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

#ifndef RTC_OUTPORT_H
#define RTC_OUTPORT_H

#include <coil/TimeValue.h>
#include <coil/Time.h>
#include <coil/TimeMeasure.h>
#include <coil/OS.h>

#include <rtm/RTC.h>
#include <rtm/Typename.h>
#include <rtm/OutPortBase.h>
#include <rtm/CdrBufferBase.h>
#include <rtm/PortCallback.h>
#include <rtm/OutPortConnector.h>
#include <rtm/Timestamp.h>
#include <rtm/DirectOutPortBase.h>

#include <functional>
#include <string>
#include <vector>


/*!
 * @if jp
 * @brief データにタイムスタンプをセットする
 *
 * データポートのデータに対してタイムスタンプをセットする。データポート
 * のデータは構造体のメンバーとして tm.sec, tm.nsec を持つ必要がある。
 *
 * @param data タイムスタンプをセットするデータ。実行後実行時のタイムス
 *             タンプがセットされる
 *
 * @else
 * @brief Setting timestamp to data
 *
 * This function sets timestamp to data of data port. This data should
 * have tm.sec, tm.nsec as members of the structure.
 *
 * @param data Data to be set timestamp. After executing this
 *             function, current timestamp is set to the data.
 *
 * @endif
 */
template <class DataType>
void setTimestamp(DataType& data)
{
      // set timestamp
      coil::TimeValue tm(coil::gettimeofday());
      data.tm.sec  = tm.sec();
      data.tm.nsec = tm.usec() * 1000;
}

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
	  : public OutPortBase, DirectOutPortBase<DataType>
  {
	  typedef coil::Guard<coil::Mutex> Guard;
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
#if defined(__GNUC__) && (__GNUC__ <= 3 && __GNUC_MINOR__ <= 3)
      : OutPortBase(name, ::CORBA_Util::toRepositoryIdOfStruct<DataType>()),
#else
      : OutPortBase(name, ::CORBA_Util::toRepositoryId<DataType>()),
#endif
	  DirectOutPortBase<DataType>(value),
	  m_value(value), m_onWrite(0), m_onWriteConvert(0),
	  m_directNewData(false), m_directValue(value)
    {

      this->addConnectorDataListener(ON_BUFFER_WRITE,
                                     new Timestamp<DataType>("on_write"));
      this->addConnectorDataListener(ON_SEND,
                                     new Timestamp<DataType>("on_send"));

	  m_directport = this;

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
      RTC_TRACE(("DataType write()"));

      if (m_onWrite != NULL)
        {
          (*m_onWrite)(value);
          RTC_TRACE(("OnWrite called"));
        }


      bool result(true);
      std::vector<const char *> disconnect_ids;
      {
        Guard guard(m_connectorsMutex);
        // check number of connectors
        size_t conn_size(m_connectors.size());
        if (!(conn_size > 0)) { return false; }

        m_status.resize(conn_size);

        for (size_t i(0), len(conn_size); i < len; ++i)
          {

            ReturnCode ret;
			if (!m_connectors[i]->pullDirectMode())
			{
				if (m_onWriteConvert != NULL)
				{
					RTC_DEBUG(("m_connectors.OnWriteConvert called"));
					DataType tmp = (*m_onWriteConvert)(value);
					ret = m_connectors[i]->write(tmp);
				}
				else
				{
					RTC_DEBUG(("m_connectors.write called"));
					ret = m_connectors[i]->write(value);
				}
			}
			else
			{
				Guard guard(m_valueMutex);
				if (m_onWriteConvert != NULL)
				{
					RTC_DEBUG(("m_connectors.OnWriteConvert called"));
					m_directValue = ((*m_onWriteConvert)(value));
				}
				else
				{
					m_directValue = value;
				}
				m_directNewData = true;
				ret = PORT_OK;
			}
            m_status[i] = ret;

            if (ret == PORT_OK) { continue; }

            result = false;

            if (ret == CONNECTION_LOST)
              {
                const char* id(m_connectors[i]->profile().id.c_str());
                RTC_WARN(("connection_lost id: %s", id));
                if (m_onConnectionLost != 0)
                  {
                    RTC::ConnectorProfile prof(findConnProfile(id));
                    (*m_onConnectionLost)(prof);
                  }
                disconnect_ids.push_back(id);
              }
          }
      }
      std::for_each(disconnect_ids.begin(), disconnect_ids.end(),
                    std::bind1st(std::mem_fun(&PortBase::disconnect), this));
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
     * @brief 特定のコネクタへの書き込みステータスを得る
     *
     * OutPort は接続ごとに Connector と呼ばれる仮想データチャネルを持
     * つ。write() 関数はこれら Connector に対してデータを書き込むが、
     * 各 Connector は書き込みごとにステータスを返す。write() 関数では、
     * すべての Connector が正常終了したときのみ true を返し、それ以外
     * では false を返却する。この関数は write() が false の場合ステー
     * タスを調べるのに使用することができる。
     *
     * @param index Connector の index
     * @return ステータス
     *
     * @else
     *
     * @brief Getting specified connector's writing status
     *
     * An OutPort has Connectors that are virtual data stream channel
     * for each connection.  "write()" function write into these
     * Connectors, and each Connector returns writing-status.  write()
     * function will return a true value if all Connectors return
     * normal status, and a false value will be returned if at least
     * one Connector failed.  This function can be used to inspect
     * each return status
     *
     * @param index Connector index
     * @return Writing status
     *
     * @endif
     */
    DataPortStatus::Enum getStatus(int index)
    {
      return m_status[index];
    }
    /*!
     * @if jp
     *
     * @brief 特定のコネクタへの書き込みステータスリストを得る
     *
     * OutPort は接続ごとに Connector と呼ばれる仮想データチャネルを持
     * つ。write() 関数はこれら Connector に対してデータを書き込むが、
     * 各 Connector は書き込みごとにステータスを返す。write() 関数では、
     * すべての Connector が正常終了したときのみ true を返し、それ以外
     * では false を返却する。この関数は write() が false の場合ステー
     * タスを調べるのに使用することができる。
     *
     * @return ステータスリスト
     *
     * @else
     *
     * @brief Getting specified connector's writing status list
     *
     * An OutPort has Connectors that are virtual data stream channel
     * for each connection.  "write()" function write into these
     * Connectors, and each Connector returns writing-status.  write()
     * function will return a true value if all Connectors return
     * normal status, and a false value will be returned if at least
     * one Connector failed.  This function can be used to inspect
     * each return status
     *
     * @return Writing status list
     *
     * @endif
     */
    DataPortStatusList getStatusList()
    {
      return m_status;
    }

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

	/*!
	* @if jp
	*
	* @brief データをダイレクトに読み込む
	*
	* @param data 読み込むデータ
	*
	* @else
	*
	* @brief 
	*
	* @param data
	*
	* @endif
	*/
	virtual void read(DataType& data)
	{
		Guard guard(m_valueMutex);
		m_directNewData = false;
		data = m_directValue;
	}
	virtual bool isEmpty()
	{
		return !m_directNewData;
	}
	virtual bool isNew()
	{
		return m_directNewData;
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

    DataPortStatusList m_status;

    CORBA::Long m_propValueIndex;

    coil::Mutex m_valueMutex;
    bool m_directNewData;
    DataType m_directValue;
  };
};  // namespace RTC

#endif  // RTC_OUTPORT_H
