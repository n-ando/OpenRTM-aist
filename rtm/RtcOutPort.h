// -*- C++ -*-
/*!
 * @file RtcOutPort.h
 * @brief OutPort template class
 * @date $Date: 2005-05-12 09:06:18 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2003-2005
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: RtcOutPort.h,v 1.1.1.1 2005-05-12 09:06:18 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 *
 */

#ifndef RtcOutPort_h
#define RtcOutPort_h

#define ACE_HAS_CLOCK_GETTIME

#include "rtm/RtcOutPortBase.h"
#include "rtm/idl/RTCDataTypeSkel.h"
#include <ace/OS.h>
#include <ace/Time_Value.h>
#include <iostream>

#define DEFAULT_BUFFER_SIZE 64

namespace RTM {
  /*!
   * @if jp
   *
   * @class OutPortAny
   *
   * @brief OutPort テンプレートクラス
   * 
   * OutPort の実装である OutPortAny<T> のテンプレートクラス。
   * <T> はRTCDataType.idl にて定義されている型で、メンバとして
   * Time 型の tm , および T型の data を持つ構造体でなくてはならない。
   *
   * @else
   *
   * @class InPortAny
   *
   * @brief OutPort template class
   *
   * This class: OutPortAny<T> which is a implementations of OutPort
   * This class template provides interfaces to output channel.
   * Component developer can define output value, which act as output
   * channel to other components, using this template.
   * This is class template. This class have to be incarnated class as channel
   * value types. This value types are previously define RtComponent IDL.
   * ex. type T: TimedFload, TimedLong etc... 
   *
   * @endif
   */
  template <class T> class OutPortAny
	: public OutPortBase
  {
  public:
	/*!
	 * @if jp
	 *
	 * @brief OutPortAny クラスコンストラクタ
	 *
	 * OutPortAny<T> クラスのコンストラクタ。
	 * パラメータとして与えられる T 型の変数にバインドされる。
	 *
	 * @param name OutPort 名。OutPortBase:name() により参照される。
	 * @param value この OutPort にバインドされる T 型の変数
	 * @param bufsize OutPort 内部のリングバッファのバッファ長
	 *
	 * @else
	 *
	 * @brief A constructor.
	 *
	 * Setting channel name and registering channel value.
	 *
	 * @param name A name of the OutPort. This name is referred by
	 *             OutPortBase::name().
	 * @param value A channel value related with the channel.
	 * @param bufsize Buffer length of internal ring buffer of OutPort 
	 *
	 * @endif
	 */
	OutPortAny(const char* name, T& value, int bufsize=DEFAULT_BUFFER_SIZE)
	  : m_Buffer(bufsize, value), m_Value(value)
	{
	  // Set PortProfile
	  m_Profile.name = CORBA::string_dup(name);
	  CORBA::Any var;
	  var <<= m_Value;
	  m_Profile.port_type = var.type();
	  
	  // Initializing ring buffer
	  for (int i = 0 ; i < m_Buffer.buff_length(); i++)
		{
		  m_Buffer.put(m_Value);
		}
	}
	
	/*!
	 * @if jp
	 *
	 * @brief OutPortAny クラスコンストラクタ
	 *
	 * OutPortAny<T> クラスのコンストラクタ。
	 * 
	 *
	 * @param name OutPort 名。OutPortBase:name() により参照される。
	 * @param bufsize OutPort 内部のリングバッファのバッファ長
	 *
	 * @else
	 *
	 * @brief A constructor.
	 *
	 * Setting channel name and registering channel value.
	 *
	 * @param name A name of the OutPort. This name is referred by
	 *             OutPortBase::name().
	 * @param bufsize Buffer length of internal ring buffer of OutPort 
	 *
	 * @endif
	 */
	OutPortAny(const char* name, int bufsize=DEFAULT_BUFFER_SIZE)
	  : m_Buffer(bufsize, m_Dummy), m_Value(m_Dummy)
	{
	  // Set PortProfile
	  m_Profile.name = CORBA::string_dup(name);
	  CORBA::Any var;
	  var <<= m_Value;
	  m_Profile.port_type = var.type();
	  
	  // Initializing ring buffer
	  for (int i = 0 ; i < m_Buffer.buff_length(); i++)
		{
		  m_Buffer.put(m_Value);
		}
	}
	
	
	/*!
	 * @if jp
	 *
	 * @brief OutPortAny クラスデストラクタ
	 *
	 * OutPortAny<T> クラスのデストラクタ。
	 *
	 * @else
	 *
	 * @brief A destructor
	 *
	 * @endif
	 */
	virtual ~OutPortAny(){};
	
	/*!
	 * @if jp
	 *
	 * @brief [CORBA interface] 現在の OutPort の最新の値を取得
	 *
	 * 現在の OutPort の最新の値を取得する
	 *
	 * @else
	 *
	 * @brief [CORBA interface] Get current data of OutPort
	 *
	 * @endif
	 */
	CORBA::Any* get()
	  throw (CORBA::SystemException)
	{
	  ACE_TRACE("OutPortBase::get()");
	  CORBA::Any_var tmp = new CORBA::Any();
	  tmp <<= m_Buffer.get_new();
	  return tmp._retn();
	}
	
	/*!
	 * @if jp
	 *
	 * @brief 現在の OutPort の値をサブスクライバに転送
	 *
	 * 現在の OutPort の値をサブスクライバに転送する
	 *
	 * @else
	 *
	 * @brief Push current data to subscribers
	 *
	 * @endif
	 */
	//	RtmRes push(const InPort_ptr& inport, SubscriptionID subsid)
	RtmRes push(const InPort_ptr& inport, std::string& subsid)
	{
	  ACE_TRACE("OutPortBase::push()");
	  
	  if (CORBA::is_nil(inport)) 
		{
		  ACE_DEBUG((LM_DEBUG, "Invalid object reference: inport"));
		  return RTM_ERR;
		}

	  try
		{
		  CORBA::Any val;
		  val <<= m_Buffer.get_new();
		  
		  if (inport != NULL)
			{
			  inport->put(val);
			}
		}
	  catch(CORBA::SystemException& e)
		{
		  //		  cout << "push(): CORBA System Exception." << endl;

		  // Subscribers already locked
		  unsubscribeNoLocked(subsid.c_str());
		  return RTM_ERR;
		}
	  catch(RTM::InPort::Disconnected& e)
		{
		  //		  ACE_DEBUG((LM_DEBUG, "Disconnected."));

		  // Subscribers already locked
		  unsubscribeNoLocked(subsid.c_str());
		  return RTM_ERR;
		}
	  return RTM_OK;
	}
	
	
	
	/*!
	 * @if jp
	 *
	 * @brief OutPort 内のリングバッファの値を初期化
	 *
	 * OutPort 内のリングバッファの値を初期化する。
	 *
	 * @else
	 *
	 * @brief Initialize ring buffer value of OutPort
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
	 * @brief バインドされた T 型のデータを OutPort の最新値として書き込む
	 *
	 * バインドされた T 型のデータを OutPort の最新値として書き込む。
	 * コンストラクタで T 型の変数と OutPort がバインドされている必要がある。
	 *
	 * @else
	 *
	 * @brief Write into current OutPort from bound T-type data
	 *
	 * @endif
	 */
	virtual void write()
	{
	  struct timespec ts;
	  ACE_OS::clock_gettime(CLOCK_REALTIME, &ts);
	  m_Value.tm.sec = ts.tv_sec;
	  m_Value.tm.nsec = ts.tv_nsec;
	  m_Buffer.put(m_Value);
	  updateall();
	};


	/*!
	 * @if jp
	 *
	 * @brief バインドされた T 型のデータを OutPort の最新値として書き込む
	 *
	 * バインドされた T 型のデータを OutPort の最新値として書き込む。
	 * コンストラクタで T 型の変数と OutPort がバインドされている必要がある。
	 * このメソッドはポリモーフィックに使用される事を前提としているため、
	 * 型に依存しない引数、戻り値となっている。
	 *
	 * @else
	 *
	 * @brief Write into current OutPort from bound T-type data
	 *
	 * @endif
	 */
	virtual void write_pm()
	{
	  write();
	};
	
	
	/*!
	 * @if jp
	 *
	 * @brief T 型のデータを OutPort の最新値として書き込む
	 *
	 * 引数として与えられた T 型のデータを OutPort の最新値として書き込む。
	 *
	 * @param value OutPort バッファに書き込む T 型の値
	 *
	 * @else
	 *
	 * @brief Writing a argument value to OutPort buffer
	 *
	 * Calling this method, argument value "T& value" is transferred to OutPort.
	 *
	 * @param value type-T value write into OutPort buffer
	 *
	 * @endif
	 */
	virtual void write(T value)
	{
	  struct timespec ts;
	  ACE_OS::clock_gettime(CLOCK_REALTIME, &ts);
	  value.tm.sec = ts.tv_sec;
	  value.tm.nsec = ts.tv_nsec;
	  m_Buffer.put(value);
	  updateall();
	};
	
	
	/*!
	 * @if jp
	 *
	 * @brief T 型のデータを OutPort の最新値として書き込む
	 *
	 * 引数として与えられた T 型のデータを OutPort の最新値として書き込む。
	 *
	 * @param value OutPort バッファに書き込む T 型の値
	 *
	 * @else
	 *
	 * @brief Writing a argument value to OutPort buffer
	 *
	 * Calling this method, argument value "T& value" is transferred to OutPort.
	 *
	 * @param value type-T value write into OutPort buffer
	 *
	 * @endif
	 */
	virtual void operator<<(T& value)
	{
	  struct timespec ts;
	  ACE_OS::clock_gettime(CLOCK_REALTIME, &ts);
	  value.tm.sec = ts.tv_sec;
	  value.tm.nsec = ts.tv_nsec;
	  m_Buffer.put(value);
	  updateall();
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
	T m_Dummy;
	
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

#endif // RtcOutputChannel_h
