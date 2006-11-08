/*! -*- C++ -*-
 *
 * @file RingBuffer.h
 * @brief Ring buffer template class
 * @date $Date: 2006-11-08 20:09:20 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2003-2006
 *     Noriaki Ando
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: RingBuffer.h,v 1.3 2006-11-08 20:09:20 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.2  2006/11/07 09:30:14  n-ando
 * RtcRingBuffer.h was renamed to RingBuffer.h
 *
 * Revision 1.1.1.1  2005/05/12 09:06:18  n-ando
 * Public release.
 *
 *
 */


#ifndef RingBuffer_h
#define RingBuffer_h

#include <vector>
#include <iostream>
#include <ace/Synch.h>

namespace RTC
{
  
  /*!
   * @if jp
   *
   * @class RingBuffer
   *
   * @brief RingBuffer テンプレートクラス
   * 
   * 任意の型に対してリングバッファを提供する RingBuffer テンプレートクラス。
   * 任意の長さのバッファ長を持つことが出来る。
   * 最新値、最古値の取り出し、任意の場所の変数の取り出しが行える。
   *
   * @else
   *
   * @class RingBuffer
   *
   * @brief RingBuffer template class
   *
   * RingBuffer template class which provides for any types variable.
   * This ring buffer is able to have any length of buffer.
   * You can get newest and oldest value, value in any position of buffer.
   *
   * @endif
   */
  
  template <class T> class RingBuffer
  {
  public:
    /*!
     * @if jp
     *
     * @brief RingBuffer クラスコンストラクタ
     *
     * RingBuffer<T> クラスのコンストラクタ。
     * パラメータとして与えられる T 型の変数のバッファを生成する。
     *
     * @param length バッファ長
     *
     * @else
     *
     * @brief RingBuffer constructor.
     *
     * RingBuffer<T> class constructor.
     * This constructor create the buffer with "length".
     *
     * @param length Buffer length
     *
     * @endif
     */
    RingBuffer(int length)
      : m_Oldest(0), m_Newest(length)
    {
      if (length > 1)
	{
	  m_Length = length;
	}
      else
	{
	  m_Length = 2;
	}
      m_Buffer.resize(m_Length);
    }
    
    /*!
     * @if jp
     *
     * @brief RingBuffer クラスコンストラクタ
     *
     * RingBuffer<T> クラスのコンストラクタ。
     * パラメータとして与えられる T 型の変数のバッファを生成する。
     *
     * @param length バッファ長
     * @param inival 初期化値
     *
     * @else
     *
     * @brief RingBuffer constructor.
     *
     * RingBuffer<T> class constructor.
     * This constructor create the buffer with "length".
     *
     * @param length Buffer length
     * @param inival Initial value
     *
     * @endif
     */
    RingBuffer(int length, T inival)
      : m_Oldest(0), m_Newest(length)
    {
      if (length > 1)
	{
	  m_Length = length;
	}
      else
	{
	  m_Length = 2;
	}
      
      m_Buffer.resize(m_Length);
      
      for (int i = 0; i < m_Length; i++)
	{
	  m_Buffer[i] = inival;
	}
    }
    
    /*!
     * @if jp
     *
     * @brief RingBuffer に値を格納する
     *
     * RingBuffer に引数の値を格納する。
     *
     * @param value 格納する T 型の値
     *
     * @else
     *
     * @brief Store given value into the RingBuffer
     *
     * Store given argument value into the RingBuffer.
     *
     * @param value Stored value
     *
     * @endif
     */
    inline void put(const T& value)
    {

      if (m_wPtrOld == m_rPtrNew)
	{
	  onOverflow(value);
	}
      m_Buffer[m_wPtrOld].write(value);
      
      ACE_Guard<ACE_Thread_Mutex> guard(m_Mutex);
      m_wPtrNew = m_wPtrOld;
      m_writePtrOld = (++m_writePtrOld) % m_length;
      
    }
    
    /*!
     * @if jp
     *
     * @brief 最新の値を取得する
     *
     * RingBuffer 中の最新の値を取得する。
     *
     * @else
     *
     * @brief Get the newset value
     *
     * Get the newest value stored in the RingBuffer.
     *
     * @endif
     */
    inline const T& get_new()
    {
      ACE_Guard<ACE_Thread_Mutex> guard(m_Mutex);
      
      return m_Buffer[m_Newest].read();
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
    inline std::vector<T> get_new_rlist()
    {
      ACE_Guard<ACE_Thread_Mutex> guard(m_Mutex);
      
      std::vector<T> data;
      int cnt(0);
      for (int i(m_Newest);
	   m_Buffer[i].is_new() && cnt < m_Length;
	   ++cnt, --i < 0 ? (i = m_Length - 1) : 0)
	{
	  data.push_back(m_Buffer[i].read());
	}
      
      return data;
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
    inline std::vector<T> get_new_list()
    {
      ACE_Guard<ACE_Thread_Mutex> guard(m_Mutex);
      
      std::vector<T> data;
      int len(new_data_len());
      data.resize(len);
      int npos;
      npos = m_Newest - (len - 1) < 0 ?
	m_Newest - (len - 1) + m_Length  : m_Newest - (len - 1);
      int cnt(0);
      for ( ; cnt < len; ++cnt, ++npos > m_Length - 1 ? npos = 0 : 0)
	{
	  data[cnt] = m_Buffer[npos].read();
	}
      
      return data;
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
    inline int new_data_len()
    {
      ACE_Guard<ACE_Thread_Mutex> guard(m_Mutex);
      
      int cnt(0);
      for (int i(m_Newest);
	   m_Buffer[i].is_new() && cnt < m_Length;
	   ++cnt, --i < 0 ? (i = m_Length - 1) : 0)
	{;}
      
      return cnt;
    }
    
    
    /*!
     * @if jp
     *
     * @brief 最古の値を取得する
     *
     * RingBuffer 中の最古の値を取得する。
     *
     * @else
     *
     * @brief Get the oldest value
     *
     * Get the oldest value stored in the RingBuffer.
     *
     * @endif
     */
    inline T& get_old()
    {
      ACE_Guard<ACE_Thread_Mutex> guard(m_Mutex);
      
      return m_Buffer[m_Oldest].read();
    }
    
    /*!
     * @if jp
     *
     * @brief 最新の値から pos 個古い値を取得する
     *
     * RingBuffer 中の最新の値から pos 個古い値を取得する。
     *
     * @else
     *
     * @brief Get pos-th older value from the newest value
     *
     * Get pos-th older value from the newset value stored in the RingBuffer.
     *
     * @endif
     */
    virtual T& get_back(int pos)
    {
      ACE_Guard<ACE_Thread_Mutex> guard(m_Mutex);
      pos = pos % m_Length;
      
      return m_Buffer[(m_Length + m_Newest - pos) % m_Length].read();
    }
    
    /*!
     * @if jp
     *
     * @brief 最古の値から pos 個新しい値を取得する
     *
     * RingBuffer 中の最古の値から pos 個新しい値を取得する。
     *
     * @else
     *
     * @brief Get pos-th newer value from the oldest value
     *
     * Get pos-th newer value from the oldest value stored in the RingBuffer.
     *
     * @endif
     */
    inline T& get_front(int pos)
    {
      ACE_Guard<ACE_Thread_Mutex> guard(m_Mutex);
      pos = pos % m_Length;
      
      return m_Buffer[(m_Oldest + pos) % m_Length].read();
    }
    
    /*!
     * @if jp
     *
     * @brief バッファ長を取得する
     *
     * 現在のバッファ超を取得する
     *
     * @else
     *
     * @brief Get buffer length
     *
     * Get buffer length
     *
     * @endif
     */
    inline int buff_length()
    {
      return m_Length;
    }
    
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
    inline bool is_new()
    {
      return m_Buffer[m_Newest].is_new();
    }
    
    
  protected:
    /*!
     * @if jp
     * @brief Mutex
     * @else
     * @brief Mutex
     * @endif
     */
    ACE_Thread_Mutex m_Mutex;
    
    /*!
     * @if jp
     * @brief バッファ長
     * @else
     * @brief Buffer length
     * @endif
     */
    int m_Length;
    
    /*!
     * @if jp
     * @brief バッファ配列
     * @else
     * @brief Buffer sequence
     * @endif
     */
    template <class D> class Data
    {
    public:
      Data() : _data(), _is_new(false){;}
      inline Data& operator=(const D& other)
      {
	this->_data = other;
	this->_is_new = true;
	return *this;
      }
      inline void write(const D& other)
      {
	this->_is_new = true;
	this->_data = other;
      }
      inline D& read()
      {
	this->_is_new = false;
	return this->_data;
      }
      inline bool is_new()
      {
	return _is_new;
      }
    protected:
      D _data;
      bool _is_new;
    };
    std::vector<Data<T> > m_Buffer;
    
    /*!
     * @if jp
     * @brief 最新値のバッファ位置
     * @else
     * @brief Position of newset value stored in
     * @endif
     */
    int m_Newest;
    
    /*!
     * @if jp
     * @brief 最古値のバッファ位置
     * @else
     * @brief Position of oldest value stored in
     * @endif
     */
    int m_Oldest;

    int m_wPtrNew;
    int m_wPtrOld;
    int m_rPtrNew;
    int m_rPtrOld;
  };
  
};


#endif // RtcRingBuffer_h
