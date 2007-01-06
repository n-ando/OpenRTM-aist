// -*- C++ -*-
/*!
 * @file RingBuffer.h
 * @brief Defautl Buffer class
 * @date $Date: 2007-01-06 18:02:49 $
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
 * $Id: RingBuffer.h,v 1.4 2007-01-06 18:02:49 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 *
 */

#ifndef RingBuffer_h
#define RingBuffer_h

#include <vector>
#include <algorithm>
//#include <ace/Synch.h>
#include <rtm/BufferBase.h>

namespace RTC
{
  template <class DataType>
  class RingBuffer
    : public BufferBase<DataType>
  {
  public:
    RingBuffer(long int length)
      : m_length(length < 2 ? 2 : length - 1),
	m_oldPtr(0),
	m_newPtr(length < 2 ? 2 : length - 1)
    {
      m_buffer.resize(m_length);
    }

    /*!
     * @if jp
     *
     * @brief 仮想デストラクタ
     * 
     * @else
     *
     * @brief virtual destractor
     *
     * @endif
     */
    virtual ~RingBuffer(){};
    

    void init(DataType& data)
    {
      for (long int i = 0; i < m_length; ++i)
	{
	  put(data);
	}
    }

    /*!
     * @if jp
     *
     * @brief バッファの長さを取得する
     * 
     * @else
     *
     * @brief Get the buffer length
     *
     * @endif
     */
    virtual long int length() const
    {
      return m_length;
    }

    /*!
     * @if jp
     *
     * @brief バッファにデータを書き込む
     * 
     * @else
     *
     * @brief Write data into the buffer
     *
     * @endif
     */
    virtual bool write(const DataType& value)
    {
      put(value);
      return true;
    }

    /*!
     * @if jp
     *
     * @brief バッファにデータを書き込む
     * 
     * @else
     *
     * @brief Write data into the buffer
     *
     * @endif
     */
    virtual bool read(DataType& value)
    {
      value = get();
      return true;
    }

    /*!
     * @if jp
     *
     * @brief バッファがfullである
     * 
     * @else
     *
     * @brief True if the buffer is full, else false.
     *
     * @endif
     */
    virtual bool isFull() const
    {
      return false;
    }
    /*!
     * @if jp
     *
     * @brief バッファがemptyである
     * 
     * @else
     *
     * @brief True if the buffer is empty, else false.
     *
     * @endif
     */
    virtual bool isEmpty() const
    {
      return !(this->isNew());
    }

    bool isNew() const
    {
      return m_buffer[m_newPtr].isNew();
    }

  protected:
    /*!
     * @if jp
     *
     * @brief バッファにデータを書き込む
     * 
     * @else
     *
     * @brief Write data into the buffer
     *
     * @endif
     */
    virtual void put(const DataType& data)
    {
      m_buffer[m_oldPtr].write(data);
      //      ACE_Guard<ACE_Thread_Mutex> guard(m_Mutex);
      m_newPtr = m_oldPtr;
      m_oldPtr = (++m_oldPtr) % m_length;
    }

    /*!
     * @if jp
     *
     * @brief バッファからデータを取得する
     * 
     * @else
     *
     * @brief Get data from the buffer
     *
     * @endif
     */
    virtual const DataType& get()
    {
      return m_buffer[m_newPtr].read();
    }

    /*!
     * @if jp
     *
     * @brief 次に書き込むバッファの参照を取得する
     * 
     * @else
     *
     * @brief Get the buffer's reference to be written the next
     *
     * @endif
     */
    virtual DataType& getRef()
    {
      return m_buffer[m_newPtr].data;
    }

  private:
    long int m_length;
    long int m_oldPtr;
    long int m_newPtr;

    /*!
     * @if jp
     * @brief バッファ配列
     * @else
     * @brief Buffer sequence
     * @endif
     */
    template <class D>
    class Data
    {
    public:
      Data() : data(), is_new(false){;}
      inline Data& operator=(const D& other)
      {
        this->data = other;
        this->is_new = true;
        return *this;
      }
      inline void write(const D& other)
      {
        this->is_new = true;
        this->data = other;
      }
      inline D& read()
      {
        this->is_new = false;
        return this->data;
      }
      inline bool isNew() const
      {
        return is_new;
      }
      D    data;
      bool is_new;
    };

    std::vector<Data<DataType> > m_buffer;

  };
}; // namespace RTC

#endif // RingBuffer_h
