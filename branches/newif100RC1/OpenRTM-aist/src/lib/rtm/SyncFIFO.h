// -*- C++ -*-
/*!
 * @file SyncFIFO.h
 * @brief Synchronous FIFO Buffer class
 * @date $Date: 2007-09-21 09:25:18 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2007
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

#ifndef SyncFIFO_h
#define SyncFIFO_h

#include <iostream>
#include <vector>
#include <algorithm>

#include <rtm/BufferBase.h>

namespace RTC
{
  template <class DataType>
  class SyncFIFO
    : public BufferBase<DataType>
  {
  public:
    SyncFIFO(int size = 3)
      : m_buffer(NULL), m_size(size),
	m_buffer_org(NULL), m_size_org(0),
	m_wpos(0), m_wnext(1),
	m_rpos(0), m_rnext(1),
	m_wbegin(m_wnext), m_wend(m_rpos),
	m_rbegin(m_rnext), m_rend(m_wpos)
    {
      if (m_buffer == NULL)
	{
	  m_buffer = new DataType[m_size];
	}
    }
    
    virtual ~SyncFIFO(void)
    {
      if (m_buffer_org == NULL)
	{
	  delete [] m_buffer;
	}
      else
	{
	  delete [] m_buffer_org;
	}
    };
    
    virtual void init(const DataType& data)
    {
      if (m_buffer)
	{
	  for (int i(0); i < m_size; ++i)
	    {
	      write(data);
	    }
	}
    }
    
    
    virtual void clear()
    {
      m_wpos  = 0;
      m_wnext = 1;
      m_rpos  = 0;
      m_rnext = 1;
    }
    
    virtual bool setBuffer(DataType* buffer, int size)
    {
      if (!buffer) return false;
      if (size < 0) return false;
      
      m_size_org   = m_size;
      m_buffer_org = m_buffer;
      m_size       = size;
      m_buffer     = buffer;
      clear();
      return true;
    }
    
    virtual DataType* unsetBuffer()
    {
      DataType* tmp(m_buffer);
      m_size = m_size_org;
      m_buffer = m_buffer_org;
      return tmp;
    }
    
    virtual DataType* getBuffer() const
    {
      return m_buffer;
    }
    
    virtual long int length() const
    {
      return m_size;
    }
    
    virtual bool write(const DataType& data)
    {
      if (isFull())
	{
	  overflow(data);
	  return false;
	}
      put(data);
      pbump(1);
      return true;
    }
    
    virtual int writable()
    {
      return (m_size + m_wend - m_wbegin) % m_size;
    }
    
    virtual void put(const DataType& data)
    {
      m_buffer[m_wpos] = data;
    }
    
    virtual int putn(DataType* data, int size)
    {
      if (!data) return -1;
      if (size < 0) return -1;

      int len(size);
      if (size > this->writable()) len = this->writable();

      for (int i(0); i < len; ++i)
	{
	  m_buffer[m_wpos + i] = data[i];
	}
      pbump(len);

      return len; 
    }
    
    virtual void putNext(const DataType& data)
    {
      this->pbump(1);
      this->put(data);
    }
    
    virtual bool isFull() const
    {
      return m_wnext == m_rpos;
    }
    
    virtual void pbump(int n)
    {
      //      Guard guard(m_wmutex);
      m_wpos = (m_wpos + n) % m_size;
      m_wnext = (m_wnext + n) % m_size;
    }
    
    virtual void overflow(const DataType& data)
    {
    }
    
    //============================================================
    // 読出し関連関数
    //============================================================
    virtual bool read(DataType& data)
    {
      if (isEmpty())
	{
	  this->underflow();
	  return false;
	}
      
      data = get();
      gbump(1);
      return true;
    }
    
    virtual int readable() const
    {
      return (m_size + m_rend - m_rbegin + 1) % m_size;
    }
    
    virtual const DataType& get()
    {
      return m_buffer[m_rpos];
    }
    
    virtual void gbump(int n)
    {
      m_rpos = (m_rpos + n) % m_size;
      m_rnext = (m_rnext + n) % m_size;
    }
    
    virtual const DataType& getNext()
    {
      this->gbump(1);
      return this->get();
    }
    
    virtual int getn(DataType* data, int size)
    {
      if (!data) return -1;
      if (size < 0) return -1;

      int len(size);
      if (size > this->readable()) len = this->readable();

      for (int i(0); i < len; ++i)
	{
	  data[i] = m_buffer[m_rpos + i];
	}
      gbump(len);

      return len; 
    }
    
    virtual bool isEmpty() const
    {
      return m_rpos == m_wpos;
    }
    
    virtual void underflow()
    {
      ;
    }
    
    
    
    
  protected:
    virtual DataType* wptr()
    {
      return &m_buffer[m_wpos];
    }

    virtual DataType* wnext()
    {
      return &m_buffer[m_wnext];
    }

    virtual DataType* wbegin()
    {
      return &m_buffer[m_wbegin];
    }

    virtual DataType* wend()
    {
      return &m_buffer[m_wend];
    }

    virtual DataType* rptr()
    {
      return &m_buffer[m_rpos];
    }

    virtual DataType* rnext()
    {
      return &m_buffer[m_rnext];
    }

    virtual DataType* rbegin()
    {
      return &m_buffer[m_rbegin];
    }

    virtual DataType* rend()
    {
      return &m_buffer[m_rend];
    }


    DataType* m_buffer;
    int m_size;
    
    DataType* m_buffer_org;
    int m_size_org;
    
    // 現在の書き込み位置
    int m_wpos;
    // 現在の次の書き込み位置
    int m_wnext;
    int m_rpos, m_rnext;
    int &m_wbegin, &m_wend;
    int &m_rbegin, &m_rend;
    
  }; // class SyncFIFO
};

#endif // SyncFIFO_h
