// -*- C++ -*-
/*!
 * @file RtcInPort.h
 * @brief InPort template class
 * @date $Date: 2006-11-07 09:26:12 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2003-2005
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: InPort.h,v 1.4 2006-11-07 09:26:12 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
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

#include "rtm/RtcInPortBase.h"
#include "rtm/idl/RTCDataTypeSkel.h"
#include <iostream>

namespace RTM
{
  /*!
   * @if jp
   *
   * @class InPortAny
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
  template <class T> class InPortAny
	: public InPortBase
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
	InPortAny(const char* name, T& value, int bufsize=64)
	  : m_Buffer(bufsize), m_Value(value)
	{
	  // Set PortProfile
	  m_Profile.name = CORBA::string_dup(name);
	  CORBA::Any var;
	  var <<= m_Value;
	  m_Profile.port_type = var.type();

	  // Init time of data variable
	  m_Value.tm.sec = 0;
	  m_Value.tm.nsec = 0;
	  
	  // Initializing ring buffer
	  for (int i = 0 ; i <= m_Buffer.buff_length(); i++)
		{
		  m_Buffer.put(value);
		}
	};

	/*!
	 * @if jp
	 *
	 * @brief InPortAny クラスコンストラクタ
	 *
	 * InPortAny<T> クラスのコンストラクタ。
	 * 
	 *
	 * @param name InPort 名。InPortBase:name() により参照される。
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
	 * @param bufsize Buffer length of internal ring buffer of InPort 
	 *
	 * @endif
	 */
	InPortAny(const char* name, int bufsize=64)
	  : m_Buffer(bufsize), m_Value(m_Dummy)
	{
	  // Set PortProfile
	  m_Profile.name = CORBA::string_dup(name);
	  CORBA::Any var;
	  var <<= m_Value;
	  m_Profile.port_type = var.type();

	  // Init time of data variable
	  m_Value.tm.sec = 0;
	  m_Value.tm.nsec = 0;

	  // Initializing ring buffer
	  for (int i = 0 ; i <= m_Buffer.buff_length(); i++)
		{
		  m_Buffer.put(m_Value);
		}
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
	virtual ~InPortAny(){};

	/*!
	 * @if jp
	 *
	 * @brief [CORBA interface] InPort に値を与える
	 *
	 * InPort に値を put する。
	 *
	 * @else
	 *
	 * @brief [CORBA interface] Put data on InPort
	 *
	 * @endif
	 */
	virtual void put(const CORBA::Any& value)
	  throw (RTM::PortBase::Disconnected, CORBA::SystemException)
	{
	  T* tmp;

	  if (value >>= tmp)
		m_Buffer.put(*tmp);
	  return;
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
	virtual void initBuffer(T& value)
	{
	  for (int i = 0 ; i <= m_Buffer.buff_length(); i++)
		{
		  m_Buffer.put(value);
		}
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
	virtual void read_pm()
	{
	  m_Value = m_Buffer.get_new();
	  return;
	};
	
	/*!
	 * @if jp
	 *
	 * @brief バインドされた T 型の変数に InPort バッファの最新値を読み込む
	 *
	 * バインドされた T 型のデータに InPort の最新値を読み込む。
	 * コンストラクタで T 型の変数と InPort がバインドされていなければならない。
	 *
	 * @else
	 *
	 * @brief Read into bound T-type data from current InPort
	 *
	 * @endif
	 */
	virtual T read()
	{
	  m_Value = m_Buffer.get_new();
	  return m_Value;
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
	virtual bool operator>>(T& rhs)
	{
	  rhs = m_Buffer.get_new();
	  return true;
	};

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
	virtual bool isNew()
	{
	  return m_Buffer.is_new();
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
	virtual int getNewDataLen()
	{
	  return m_Buffer.new_data_len();
	}


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
	virtual std::vector<T> getNewList()
	{
	  return m_Buffer.get_new_list();
	}
	

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
	virtual std::vector<T> getNewListReverse()
	{
	  return m_Buffer.get_new_rlist();
	}
	

  private:
	/*!
	 * @if jp
	 * @brief バインドされる T 型の変数への参照
	 * @else
	 * @brief reference to type-T value bound this OutPort
	 * @endif
	 */
	T& m_Value;

	/*!
	 * @if jp
	 * @brief T 型のダミー変数
	 * @else
	 * @brief Dummy variable of type-T
	 * @endif
	 */
	T  m_Dummy;

	/*!
	 * @if jp
	 * @brief T 型の一時変数
	 * @else
	 * @brief Tempolary variable of type-T
	 * @endif
	 */
	T* m_Tmp;

	/*!
	 * @if jp
	 * @brief バッファ
	 * @else
	 * @brief Buffer
	 * @endif
	 */
	RingBuffer<T> m_Buffer;

  };
  
}; // End of namesepace RTM

#endif // RtcInPort_h
